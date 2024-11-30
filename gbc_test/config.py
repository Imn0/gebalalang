from dataclasses import dataclass
import os
import subprocess


@dataclass(frozen=True)
class CFG:
    _main_test_dir = "./tests"
    _vm_path = "../maszyna_wirtualna/maszyna-wirtualna"
    _gblc_path = "../gembalalangc/target/debug/gembalalangc"
    _test_dir = "./tests"

    @property
    def main_test_dir(self) -> str:
        script_dir = os.path.dirname(os.path.abspath(__file__))
        return os.path.join(script_dir, self._main_test_dir)

    @property
    def vm_path(self) -> str:
        script_dir = os.path.dirname(os.path.abspath(__file__))
        return os.path.join(script_dir, self._vm_path)

    @property
    def gblc_path(self) -> str:
        script_dir = os.path.dirname(os.path.abspath(__file__))
        return os.path.join(script_dir, self._gblc_path)

    @property
    def tests_dir(self) -> str:
        script_dir = os.path.dirname(os.path.abspath(__file__))
        return os.path.join(script_dir, self._test_dir)

    def recompile(self):
        cmd = ["cargo","build", "--manifest-path=gembalalangc/Cargo.toml"]
        process = subprocess.run(
            cmd,
        )
