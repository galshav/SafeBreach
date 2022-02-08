from typing import List
import subprocess


# Microsoft build engine.
class MSBuild:
    def __init__(self, msbuild_path: str) -> None:
        self._msbuild_path = msbuild_path


    def compile(self, path_to_sln: str) -> None:
        assert 0 == subprocess.call([self._msbuild_path, path_to_sln, "/t:Clean,Build"]), "Can not compile executable."


# Microsoft compiler.
class CL:
    def __init__(self, compiler_path: str) -> None:
        pass


    def compile(self, source_files: list[str]) -> None:
        pass