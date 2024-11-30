from dataclasses import dataclass
import subprocess
from gbc_test.config import CFG
import re
import os


@dataclass(frozen=True)
class TestCase:
    name: str
    input_text: list[str]
    expected_output: list[str]


@dataclass(frozen=True)
class TestResult:
    name: str
    passed: bool
    num_instructions: int
    avg_total_cost: float
    avg_total_cost_wout_io: float

    def __lt__(self, other):
         return self.name < other.name



class TestRunner:
    def __init__(self, cfg: CFG) -> None:
        self.cfg = cfg

    def __call__(self, tests: dict[str, list[str]]) -> dict[str, list[TestResult]]:
        results = {}
        for k, v in tests.items():
            results[k] = self.run_test_set(v)
        return results
    
    def run_test_set(self, test_files: list[str]) -> list[TestResult]:
        results: list[TestResult] = []
        script_dir = os.path.dirname(os.path.abspath(__file__))

        for test_file in test_files:
            compiled_name = os.path.join(script_dir, "./build/a.mr")
            r = self._compile(test_file, compiled_name)
            if r:
                test_cases = self.parse_pragma_tests(test_file)
                if len(test_cases) == 0:
                    continue
                r = self.run_test(compiled_name, test_cases)
                results.append(r)
            else:
                print(f"Cant compile {test_file}")
        results.sort()
        return results


    def _compile(self, in_file: str, out_file: str) -> bool:
        command = [self.cfg.gblc_path, in_file, "-o", out_file]
        process = subprocess.Popen(
            command,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
        )
        stdout, stderr = process.communicate()

        rtn = process.wait()

        if rtn != 0:
            return False
        return True

    def parse_pragma_tests(self, file_path: str) -> list[TestCase]:
        with open(file_path, "r") as file:
            source_code = file.read()

        valid_pragma_pattern = (
            r"^#\s*pragma\s+test\s*(?:in\([^)]*\))?\s*(?:out\([^)]*\))?$"
        )

        full_pragma_pattern = (
            r"#\s*pragma\s+test\s*(?:in\((.*?)\))?\s*(?:out\((.*?)\))?"
        )

        test_cases: list[TestCase] = []

        for line in source_code.split("\n"):
            line = line.strip()

            if not line:
                continue

            if line.startswith("#pragma test"):
                if not re.match(valid_pragma_pattern, line):
                    print(f"File {file_path} invalid or no pragma test")
                    return []

                match = re.search(full_pragma_pattern, line)
                if match:
                    input_args = match.group(1)
                    output_args = match.group(2)

                    input_text = []
                    if input_args:
                        input_text = [
                            arg.strip(" \"'")
                            for arg in input_args.split(",")
                            if arg.strip()
                        ]

                    expected_output = []
                    if output_args:
                        expected_output = [
                            arg.strip(" \"'")
                            for arg in output_args.split(",")
                            if arg.strip()
                        ]

                    test_case = TestCase(
                        name=os.path.basename(file_path),
                        input_text=input_text, expected_output=expected_output
                    )

                    test_cases.append(test_case)

            elif line.startswith("#pragma "):
                if not line.startswith("#pragma test"):
                    print(f"File {file_path} invalid or no pragma test")
                    return []

            

        return test_cases

    def run_test(self, compiled_file: str, test_cases: list[TestCase]) -> TestResult:
        num_instructions: int = 0
        avg_cost: float = 0.0
        avg_cost_wout_io: float = 0.0

        name = ""
        for i, test_case in enumerate(test_cases):
            name = test_case.name
            print(f"running {name}")
            command = [self.cfg.vm_path, compiled_file]
            result = subprocess.Popen(
                command,
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
            )

            input_data = "\n".join(test_case.input_text)
            
            try:
                stdout, stderr = result.communicate(input_data, timeout=5)
            except subprocess.TimeoutExpired:
                result.kill()
                stdout, stderr = result.communicate()  
                print(f"test {name} took too long and was killed. stderr: {stderr}")
                return TestResult(name, False, 0, 0.0, 0.0)

            if result.returncode != 0:
                print(f"test {name} failed with return code {result.returncode}. stderr: {stderr}")
                return TestResult(name, False, 0, 0.0, 0.0)


            output = stdout.strip().split("\n")

            regex_instructions = r"liczba rozkazów: (\d+)"
            regex_cost = r"koszt: (\d+)"
            regex_io_cost = r"w tym i/o: (\d+)"

            r_inst = re.search(regex_instructions, stderr)
            r_cost = re.search(regex_cost, stderr)
            r_io_cost = re.search(regex_io_cost, stderr)
            if r_inst is None or r_cost is None or r_io_cost is None:
                print(f"Failed to parse results of{name} .")
                
                return TestResult(name,False, 0, 0.0, 0.0)

            num_instructions = int(r_inst.group(1))

            current_cost = int(r_cost.group(1))
            current_io_cost = int(r_io_cost.group(1))

            current_cost_wout_io = current_cost - current_io_cost

            avg_cost = (avg_cost + current_cost) / (i + 1)
            avg_cost_wout_io = (avg_cost_wout_io + current_cost_wout_io) / (i + 1)

            for i, o in enumerate(output):
                if test_case.expected_output[i] != o:
                    print(f"expected output of {name} is\n{test_case.expected_output}\nbut got\n{output} .")
                    return TestResult(name,False, 0, 0.0, 0.0)

        return TestResult(name, True, num_instructions, avg_cost, avg_cost_wout_io)
