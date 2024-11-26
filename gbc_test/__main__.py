import re
from dataclasses import dataclass
import subprocess


test_files = ["./testy/custom/basic1.gbl", "./testy/custom/basic2.gbl", "./testy/custom/proc1.gbl"]
vm_path = "./maszyna_wirtualna/maszyna-wirtualna"
gblc_path = "./gembalalangc/target/debug/gembalalangc"


@dataclass(frozen=True)
class TestCase:
    input_text: list[str]
    expected_output: list[str]


@dataclass(frozen=True)
class TestResult:
    passed: bool
    num_instructions: int
    avg_total_cost: float
    avg_total_cost_wout_io: float


def parse_pragma_tests(file_path: str) -> list[TestCase]:
    with open(file_path, "r") as file:
        source_code = file.read()

    valid_pragma_pattern = r"^#\s*pragma\s+test\s*(?:in\([^)]*\))?\s*(?:out\([^)]*\))?$"

    full_pragma_pattern = r"#\s*pragma\s+test\s*(?:in\((.*?)\))?\s*(?:out\((.*?)\))?"

    test_cases: list[TestCase] = []

    for line in source_code.split("\n"):
        line = line.strip()

        if not line:
            continue

        if line.startswith("#pragma test"):
            if not re.match(valid_pragma_pattern, line):

                # not valid pragma test

                # test_cases.append(
                #     PragmaTestParseError(f"Invalid pragma test directive: {line}")
                # )
                continue

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
                    input_text=input_text, expected_output=expected_output
                )

                test_cases.append(test_case)

        elif line.startswith("#pragma "):
            if not line.startswith("#pragma test"):
                pass
                # pasrse srror

    return test_cases


def run_test(compiled_file: str, test_cases: list[TestCase]) -> TestResult:
    num_instructions: int = 0
    avg_cost: float = 0.0
    avg_cost_wout_io: float = 0.0
    for i, test_case in enumerate(test_cases):
        command = [vm_path, compiled_file]
        process = subprocess.Popen(
            command,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
        )

        input_data = "\n".join(test_case.input_text)
        stdout, stderr = process.communicate(input_data)

        rtn = process.wait(10.0)
        if rtn != 0:
            return TestResult(False, 0, 0.0, 0.0)

        output = stdout.strip().split("\n")

        regex_instructions = r"liczba rozkazów: (\d+)"
        regex_cost = r"koszt: (\d+)"
        regex_io_cost = r"w tym i/o: (\d+)"

        r_inst = re.search(regex_instructions, stderr)
        r_cost = re.search(regex_cost, stderr)
        r_io_cost = re.search(regex_io_cost, stderr)
        if r_inst is None or r_cost is None or r_io_cost is None:
            return TestResult(False, 0, 0.0, 0.0)

        num_instructions = int(r_inst.group(1))

        current_cost = int(r_cost.group(1))
        current_io_cost = int(r_io_cost.group(1))

        current_cost_wout_io = current_cost - current_io_cost

        avg_cost = (avg_cost + current_cost) / (i + 1)
        avg_cost_wout_io = (avg_cost_wout_io + current_cost_wout_io) / (i + 1)

        for i, o in enumerate(output):
            if test_case.expected_output[i] != o:
                print(output)
                return TestResult(False, 0, 0.0, 0.0)

    return TestResult(True, num_instructions, avg_cost, avg_cost_wout_io)


def compile(in_file: str, out_file: str) -> bool:
    command = [gblc_path, in_file, "-o", out_file]
    process = subprocess.Popen(
        command,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    _, _ = process.communicate()

    rtn = process.wait()

    if rtn != 0:
        return False
    return True


for test_file in test_files:
    if not compile(test_file, "a"):
        print(f"failed to compile {test_file}")
        test_results = TestResult(False, 0, 0.0, 0.0)
    else:
        test_cases = parse_pragma_tests(test_file)
        test_results = run_test("a", test_cases)
    print(test_results)
