import re
from dataclasses import dataclass
import subprocess


class PragmaTestParseError(Exception):
    """Custom exception for pragma test parsing errors."""

    pass


@dataclass
class TestCase:
    input_text: list[str]
    expected_output: list[str]


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


test_files = ["./testy/custom/basic1.gbl"]
vm_path = "./maszyna_wirtualna/maszyna-wirtualna"
gblc_path = "./gembalalangc/target/debug/gembalalangc"


def run_test(compiled_file: str, test_case: TestCase):
    pass


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

    test_results = parse_pragma_tests(test_file)

    for i, result in enumerate(test_results, 1):
        command = [vm_path, "a"]
        process = subprocess.Popen(
            command,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
        )

        input_data = '\n'.join(result.input_text)
        stdout, stderr = process.communicate(input_data)

        
        output = stdout.strip().split('\n')

        for i, o in enumerate(output):
            if result.expected_output[i] != o:
                print("ERROR")
                break
        else:
            print("all test passed")