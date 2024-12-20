import argparse
import os
import subprocess
import glob
from pathlib import Path

def get_engine_path(version):
    # Common installation paths for Epic Games
    base_paths = [
        Path("G:/Program Files/Epic Games"),
        Path("C:/Program Files/Epic Games")
    ]
    
    for base_path in base_paths:
        engine_path = base_path / f"UE_{version}"
        if engine_path.exists():
            return engine_path
        
        # Also try without UE_ prefix
        engine_path = base_path / version
        if engine_path.exists():
            return engine_path
    
    print("Searched in the following locations:")
    for base_path in base_paths:
        print(f"- {base_path / f'UE_{version}'}")
        print(f"- {base_path / version}")
    
    raise FileNotFoundError(f"Could not find Unreal Engine {version} installation. Please ensure it is installed in one of the standard locations.")

def find_uproject():
    # Get the project path (assuming this script is in Plugins/game-fuse-cpp/Scripts)
    script_dir = Path(os.path.dirname(os.path.abspath(__file__)))
    project_root = script_dir.parent.parent.parent
    
    # Search for .uproject files
    uproject_files = list(project_root.glob("*.uproject"))
    
    if not uproject_files:
        raise FileNotFoundError("No .uproject file found in the project directory")
    
    if len(uproject_files) > 1:
        print("Multiple .uproject files found. Using the first one:", uproject_files[0])
    
    return uproject_files[0]

def build_project(engine_path, project_file):
    print("Building project...")
    
    # Construct the UBT command
    ubt_path = engine_path / "Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.dll"
    
    if not ubt_path.exists():
        print(f"Error: Could not find UnrealBuildTool at {ubt_path}")
        return False
    
    # Get project name without extension
    project_name = project_file.stem
    
    # Build the command arguments
    cmd = [
        "dotnet",
        str(ubt_path),
        f"{project_name}Editor",
        "Development",
        "Win64",
        "-Project=" + str(project_file),
        "-WaitMutex"
    ]
    
    try:
        print(f"Build command: {' '.join(cmd)}")
        result = subprocess.run(cmd, capture_output=True, text=True)
        
        # Print output
        print("\nBuild Output:")
        print(result.stdout)
        
        if result.stderr:
            print("\nBuild Errors:")
            print(result.stderr)
        
        return result.returncode == 0
        
    except subprocess.SubprocessError as e:
        print(f"Error building project: {e}")
        return False

def run_tests(ue_version, test_name):
    try:
        # Get the engine path
        engine_path = get_engine_path(ue_version)
        
        # Find the project file
        project_file = find_uproject()
        
        # Build the project first
        if not build_project(engine_path, project_file):
            print("Project build failed. Aborting tests.")
            return False
        
        # Construct the command
        cmd_path = engine_path / "Engine/Binaries/Win64/UnrealEditor-Cmd.exe"
        
        # Check if the executable exists
        if not cmd_path.exists():
            print(f"Error: Could not find UnrealEditor-Cmd.exe at {cmd_path}")
            print("Please verify your Unreal Engine installation")
            return False
        
        # Build the command arguments
        cmd = [
            str(cmd_path),
            str(project_file),
            f"-execcmds=Automation RunTests {test_name};Quit",
            "-stdout",
            "-unattended",
            "-NOSPLASH",
            "-NullRHI"
        ]
        
        # Run the command
        print(f"Running tests with Unreal Engine {ue_version}...")
        print(f"Project file: {project_file}")
        print(f"Test name: {test_name}")
        print(f"Command path exists: {cmd_path.exists()}")
        print(f"Command: {' '.join(cmd)}")
        
        try:
            result = subprocess.run(cmd, capture_output=True, text=True)
            
            # Print output
            print("\nOutput:")
            print(result.stdout)
            
            if result.stderr:
                print("\nErrors:")
                print(result.stderr)
            
            # Check return code
            if result.returncode != 0:
                print(f"\nTests failed with return code {result.returncode}")
                return False
            
            print("\nTests completed successfully")
            return True
            
        except subprocess.SubprocessError as e:
            print(f"Failed to execute command: {e}")
            print(f"Command was: {' '.join(cmd)}")
            return False
        
    except FileNotFoundError as e:
        print(f"Error: {e}")
        return False
    except Exception as e:
        print(f"An error occurred: {e}")
        print(f"Exception type: {type(e)}")
        import traceback
        traceback.print_exc()
        return False

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Run Unreal Engine tests")
    parser.add_argument("version", help="Unreal Engine version (e.g., 5.4)")
    parser.add_argument("test_name", help="Name of the test to run (e.g., GameFuseTests)")
    
    args = parser.parse_args()
    success = run_tests(args.version, args.test_name)
    
    # Exit with appropriate code
    exit(0 if success else 1)