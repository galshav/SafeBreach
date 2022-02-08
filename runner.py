import subprocess
import os
from build_tools import MSBuild


def main():
    # Deploy stubdll in %systemroot%/System32 (can also be %systemroot% from what i saw using sysinternals procmon).
    # SOME DEPLOY LOGIC HERE / EXTRACT FROM PE RESOURCE / DOWNLOAD FROM WEB, etc..
    
    # Build the given solution according to the required method.
    # this can be controlled using env variable (InstallByRegistryModify or InstallByWinAPI)
    os.environ["InstallByWinAPI"] = "1"
    #os.environ["InstallByWinAPI"] = "1"
    msbuild = MSBuild('C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Msbuild\\Current\\Bin\\amd64\\MSBuild.exe')
    msbuild.compile()

    # run
    subprocess.call(["PortMonitors.exe", "1"])


if "__main__" == __name__:
    main()