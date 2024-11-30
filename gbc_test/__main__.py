import os
from gbc_test.test_generator import get_all_dirs, get_all_files_in_dir
from gbc_test.test_runner import TestRunner
from gbc_test.config import CFG
from gbc_test.print_data import TestResultPrinter

cfg = CFG()
cfg.recompile()

tests_base_dir = get_all_dirs(cfg.tests_dir)

tests: dict[str, list[str]] = {}
for test in tests_base_dir:
    tests[test] = get_all_files_in_dir(os.path.join("./tests", test))

test_runner = TestRunner(cfg)
r = test_runner(tests)
# old = TestResultPrinter.load_data_from_file("aa.dat")
# TestResultPrinter.compare_results(old, r)

TestResultPrinter.print_data(r)