#type: ignore
from gbc_test.test_runner import TestResult
import os

from typing import List, Dict
from tabulate import tabulate, SEPARATING_LINE
from termcolor import colored


class TestResultPrinter:
    @staticmethod
    def print_data(results: Dict[str, List[TestResult]]):
        """
        Print test results in a tabular format using tabulate library
        """
        for section, test_results in results.items():
            table_data: list[list[str]] = []

            table_data.append([section, "", "", "", ""])
            table_data.append(SEPARATING_LINE)

            table_data.append(
                [
                    "Test Name",
                    "Passed",
                    "Num Instructions",
                    "Avg Total Cost",
                    "Avg Total Cost (without IO)",
                ]
            )
            table_data.append(SEPARATING_LINE)

            for result in sorted(test_results):
                passed_str = (
                    colored("Yes", "green") if result.passed else colored("No", "red")
                )

                table_data.append(
                    [
                        result.name,
                        passed_str,
                        result.num_instructions,
                        f"{result.avg_total_cost:.2f}",
                        f"{result.avg_total_cost_wout_io:.2f}",
                    ]
                )

            print(tabulate(table_data, headers="firstrow", tablefmt="plain"))
            print("\n")

    @staticmethod
    def save_data_to_file(results: Dict[str, List[TestResult]], filename: str):
        """
        Save test results to a CSV file
        """
        with open(filename, "w") as file:
            for section, test_results in results.items():
                file.write(f"Section: {section}\n")
                for result in test_results:
                    file.write(
                        f"{result.name},{result.passed},{result.num_instructions},{result.avg_total_cost},{result.avg_total_cost_wout_io}\n"
                    )

    @staticmethod
    def load_data_from_file(filename: str) -> Dict[str, List[TestResult]]:
        """
        Load test results from a CSV file
        """
        if not os.path.exists(filename):
            return {}

        results: Dict[str, List[TestResult]] = {}
        with open(filename, "r") as file:
            section = None
            for line in file:
                if line.startswith("Section:"):
                    section = line.strip().split(":")[1].strip()
                    results[section] = []
                else:
                    parts = line.strip().split(",")
                    if len(parts) == 5:
                        (
                            name,
                            passed,
                            num_instructions,
                            avg_total_cost,
                            avg_total_cost_wout_io,
                        ) = parts
                        passed = passed == "True"
                        num_instructions = int(num_instructions)
                        avg_total_cost = float(avg_total_cost)
                        avg_total_cost_wout_io = float(avg_total_cost_wout_io)
                        results[section].append(
                            TestResult(
                                name,
                                passed,
                                num_instructions,
                                avg_total_cost,
                                avg_total_cost_wout_io,
                            )
                        )
        return results

    @staticmethod
    def compare_results(
        previous: Dict[str, List[TestResult]], current: Dict[str, List[TestResult]]
    ):
        """
        Compare current test results with previous results
        """
        for section, current_results in current.items():
            table_data = []

            # table_data.append([section, "", "", "", ""])
            table_data.append(SEPARATING_LINE)

            table_data.append(
                [
                    "Test Name",
                    "Passed",
                    "Num Instructions",
                    "Avg Total Cost",
                    "Avg Total Cost (without IO)",
                ]
            )
            table_data.append(SEPARATING_LINE)

            passed_num_instructions = []
            passed_total_cost = []
            passed_total_cost_wo_io = []
            passed_count = 0

            instruction_changes = []
            total_cost_changes = []
            total_cost_wo_io_changes = []

            for current_result in sorted(current_results):
                prev_result = next(
                    (
                        r
                        for section_tests in previous.values()
                        for r in section_tests
                        if r.name == current_result.name
                    ),
                    None,
                )

                passed_str = (
                    colored("Yes", "green")
                    if current_result.passed
                    else colored("No", "red")
                )

                num_instructions_display = str(current_result.num_instructions)
                total_cost_display = f"{current_result.avg_total_cost:.2f}"
                total_cost_wo_io_display = (
                    f"{current_result.avg_total_cost_wout_io:.2f}"
                )

                if current_result.passed:
                    passed_num_instructions.append(current_result.num_instructions)
                    passed_total_cost.append(current_result.avg_total_cost)
                    passed_total_cost_wo_io.append(
                        current_result.avg_total_cost_wout_io
                    )
                    passed_count += 1

                if prev_result and current_result.passed and prev_result.passed:
                    if current_result.num_instructions != prev_result.num_instructions:
                        change = (
                            current_result.num_instructions
                            - prev_result.num_instructions
                        )
                        instruction_changes.append(change)
                        num_instructions_display += colored(
                            f" ({change:+d})", "green" if change < 0 else "red"
                        )

                    if current_result.avg_total_cost != prev_result.avg_total_cost:
                        change = (
                            current_result.avg_total_cost - prev_result.avg_total_cost
                        )
                        total_cost_changes.append(change)
                        total_cost_display += colored(
                            f" ({change:+.2f})", "green" if change < 0 else "red"
                        )

                    if (
                        current_result.avg_total_cost_wout_io
                        != prev_result.avg_total_cost_wout_io
                    ):
                        change = (
                            current_result.avg_total_cost_wout_io
                            - prev_result.avg_total_cost_wout_io
                        )
                        total_cost_wo_io_changes.append(change)

                table_data.append(
                    [
                        current_result.name,
                        passed_str,
                        num_instructions_display,
                        total_cost_display,
                        total_cost_wo_io_display,
                    ]
                )

            if passed_count > 0:
                instr_change_avg = (
                    sum(instruction_changes) / len(instruction_changes)
                    if instruction_changes
                    else 0
                )
                total_cost_change_avg = (
                    sum(total_cost_changes) / len(total_cost_changes)
                    if total_cost_changes
                    else 0
                )
                total_cost_wo_io_change_avg = (
                    sum(total_cost_wo_io_changes) / len(total_cost_wo_io_changes)
                    if total_cost_wo_io_changes
                    else 0
                )

                instr_change_color = "red" if instr_change_avg > 0 else "green"
                total_cost_change_color = (
                    "red" if total_cost_change_avg > 0 else "green"
                )

                table_data.append(SEPARATING_LINE)
                table_data.append(
                    [
                        f"{section} passed Tests Average",
                        f"{passed_count}/{len(current_results)}",
                        f"{sum(passed_num_instructions) / passed_count:.2f} "
                        + (
                            colored(f"({instr_change_avg:+.1f})", instr_change_color)
                            if instruction_changes
                            else ""
                        ),
                        f"{sum(passed_total_cost) / passed_count:.2f} "
                        + (
                            colored(
                                f"({total_cost_change_avg:+.2f})",
                                total_cost_change_color,
                            )
                            if total_cost_changes
                            else ""
                        ),
                        f"{sum(passed_total_cost_wo_io) / passed_count:.2f}"
                        + (
                            colored(
                                f" ({total_cost_wo_io_change_avg:+.2f})",
                                "red" if total_cost_wo_io_change_avg > 0 else "green",
                            )
                            if total_cost_wo_io_changes
                            else ""
                        ),
                    ]
                )

            # Print the table
            print(section)
            print(tabulate(table_data, headers="firstrow", tablefmt="plain"))
            print("\n")
