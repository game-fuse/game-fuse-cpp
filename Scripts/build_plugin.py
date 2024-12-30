import argparse
import os
import shutil
import sys
import json
from pathlib import Path
import subprocess
from typing import NamedTuple
from enum import Enum

class Colors(Enum):
    """ANSI color codes"""
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BLUE = '\033[94m'
    RESET = '\033[0m'

class BuildPaths(NamedTuple):
    """Container for all paths used in the build process"""
    plugin: Path
    build_dir: Path
    ue_path: Path
    runuat: Path
    release_zip: Path
    prebuilt_zip: Path

def colorize(text: str, color: Colors) -> str:
    """Wrap text in color codes"""
    return f"{color.value}{text}{Colors.RESET.value}"

def print_info(msg: str):
    print(colorize(msg, Colors.GREEN))

def print_path(msg: str):
        print(colorize(msg, Colors.BLUE))

def print_warning(msg: str):
    print(colorize(msg, Colors.YELLOW), file=sys.stderr)

def print_error(msg: str):
    print(colorize(msg, Colors.RED), file=sys.stderr)

def int_version(version: str) -> str:
    """Format version string with padding (XX.YY.ZZZ)"""
    try:
        x, y, z = map(int, version.split('.'))
        return f"{x:02d}{y:02d}{z:03d}"
    except ValueError:
        raise ValueError("Version must be in format X.Y.Z with numbers only")

def validate_ue_version(version: str) -> bool:
    """Validate Unreal Engine version format (e.g., 5.4)"""
    try:
        major, minor = map(int, version.split('.'))
        return True
    except ValueError:
        return False

def validate_version(version: str) -> bool:
    """Validate plugin version format (X.Y.Z)"""
    try:
        major, minor, patch = map(int, version.split('.'))
        return True
    except ValueError:
        return False

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

def parse_args() -> argparse.Namespace:
    """Parse command line arguments"""
    parser = argparse.ArgumentParser(description='Build and package an Unreal Engine plugin')
    parser.add_argument('--plugin-path', required=True, type=Path,
                       help='Path to the .uplugin file')
    parser.add_argument('--build-dir', required=True, type=Path,
                       help='Directory for intermediate build outputs')
    parser.add_argument('--output-dir', required=True, type=Path,
                       help='Directory where final .zip files will be copied')
    parser.add_argument('--ue-version', required=True,
                       help='Unreal Engine version (e.g., 5.4)')
    parser.add_argument('--plugin-name', required=True,
                       help='Name of the plugin')
    parser.add_argument('--version', required=True,
                       help='Plugin version (e.g., 2.2.81)')
    parser.add_argument('--include-prebuilt', action='store_true',
                       help='Include prebuilt binaries in the output (default: False)')
    
    args = parser.parse_args()
    
    # Log all input parameters
    print_info("Build Plugin Parameters:")
    print_path(f"Plugin Path: {args.plugin_path}")
    print_path(f"Build Directory: {args.build_dir}")
    print_path(f"Output Directory: {args.output_dir}")
    print_path(f"UE Version: {args.ue_version}")
    print_path(f"Plugin Name: {args.plugin_name}")
    print_path(f"Version: {args.version}")
    
    # Validate UE version format
    if not validate_ue_version(args.ue_version):
        print_error(f"Invalid UE version format: {args.ue_version}")
        print_error("UE version must be in format X.Y (e.g., 5.4)")
        sys.exit(1)
        
    # Validate plugin version format
    if not validate_version(args.version):
        print_error(f"Invalid plugin version format: {args.version}")
        print_error("Version must be in format X.Y.Z (e.g., 2.2.81)")
        sys.exit(1)

    # Create output directory if it doesn't exist
    try:
        args.output_dir.mkdir(parents=True, exist_ok=True)
    except Exception as e:
        print_error(f"Failed to create output directory: {args.output_dir}")
        print_error(f"Error: {str(e)}")
        sys.exit(1)
        
    return args

def setup_paths(args: argparse.Namespace) -> BuildPaths:
    """Initialize and validate all required paths"""
    plugin_path = args.plugin_path.resolve()
    
    # Include UE version in build directory name
    versioned_build_dir = args.build_dir / f"UE_{args.ue_version}"
    build_dir = versioned_build_dir.resolve()
    
    try:
        ue_path = get_engine_path(args.ue_version)
    except FileNotFoundError as e:
        print_error(str(e))
        sys.exit(1)
        
    runuat = ue_path / "Engine/Build/BatchFiles/RunUAT.bat"
    
    # Create release zip files in the output directory with new naming convention
    release_zip = args.output_dir / f"GameFuse_{args.ue_version}_v{args.version}.zip"
    prebuilt_zip = args.output_dir / f"GameFuse_{args.ue_version}_v{args.version}_PrebuiltBinaries.zip"
    
    # Create build directory if it doesn't exist
    try:
        build_dir.mkdir(parents=True, exist_ok=True)
    except Exception as e:
        print_error(f"Failed to create build directory: {build_dir}")
        print_error(f"Error: {str(e)}")
        sys.exit(1)
    
    return BuildPaths(
        plugin=plugin_path,
        build_dir=build_dir,
        ue_path=ue_path,
        runuat=runuat,
        release_zip=release_zip,
        prebuilt_zip=prebuilt_zip
    )

def update_uplugin_version(plugin_path: Path, version: str, ue_version: str):
    """Update the version information in the .uplugin file"""
    try:
        # Read the current .uplugin file
        with open(plugin_path, 'r', encoding='utf-8') as f:
            plugin_data = json.load(f)
        
        # Store original data for comparison
        original_version_name = plugin_data.get('VersionName', 'Not set')
        original_engine = plugin_data.get('EngineVersion', 'Not set')
        original_version = plugin_data.get('Version', 'Not set')
        
        # Update version information
        plugin_data['VersionName'] = version
        plugin_data['EngineVersion'] = ue_version
        plugin_data['Version'] = int_version(version)
        
        # Create backup of original file
        backup_path = plugin_path.with_suffix('.uplugin.bak')
        shutil.copy2(plugin_path, backup_path)
        
        # Write updated data back to .uplugin file
        with open(plugin_path, 'w', encoding='utf-8') as f:
            json.dump(plugin_data, f, indent=2)
        
        print_info("Updated .uplugin file:")
        print_path(f"Version: {original_version_name} -> {version}")
        print_path(f"Engine: {original_engine} -> {ue_version}")
        print_path(f"Integer Version: {original_version} -> {int_version(version)}")
        print_info(f"Backup created at: {backup_path}")
        
    except json.JSONDecodeError as e:
        print_error(f"Error parsing .uplugin file: {e}")
        sys.exit(1)
    except Exception as e:
        print_error(f"Error updating .uplugin file: {e}")
        sys.exit(1)

def validate_paths(paths: BuildPaths):
    """Check if required paths exist"""
    if not paths.plugin.exists():
        print_error(f"Error: Plugin path does not exist: {paths.plugin}")
        sys.exit(1)
        
    if not paths.runuat.exists():
        print_error(f"Error: RunUAT.bat not found at: {paths.runuat}")
        print_warning(f"Please ensure the UE path is correct")
        sys.exit(1)

def run_command(cmd: list[str], error_msg: str):
    """Run a command and handle errors"""
    try:
        print_info(f"Running command: {' '.join(cmd)}")
        result = subprocess.run(cmd, check=True, capture_output=True, text=True)
        if result.stdout:
            print(result.stdout)
    except subprocess.CalledProcessError as e:
        print_error(f"{error_msg}:")
        print_error(f"Command failed with exit code: {e.returncode}")
        if e.stdout:
            print_error("Standard output:")
            print(e.stdout)
        if e.stderr:
            print_error("Error output:")
            print(e.stderr)
        print_error(f"Failed command: {' '.join(cmd)}")
        sys.exit(1)
    except Exception as e:
        print_error(f"Unexpected error running command:")
        print_error(str(e))
        print_error(f"Command was: {' '.join(cmd)}")
        sys.exit(1)

def build_plugin(paths: BuildPaths):
    """Build the plugin using RunUAT"""
    print_info("Starting build process...")
    cmd = [
        str(paths.runuat),
        "BuildPlugin",
        f"-Plugin={paths.plugin}",
        f"-Package={paths.build_dir}",
        "-TargetPlatforms=Win64"
    ]
    run_command(cmd, "Plugin build failed")

def create_packages(paths: BuildPaths, include_prebuilt: bool = False):
    """Create the release and prebuilt packages"""
    print_info("Creating packages...")
    
    # Create unique temporary directories using timestamp
    import time
    timestamp = int(time.time())
    temp_with_binaries = Path(f"temp_with_binaries_{timestamp}")
    temp_without_binaries = Path(f"temp_without_binaries_{timestamp}")
    
    # Create Package directory if it doesn't exist
    paths.release_zip.parent.mkdir(parents=True, exist_ok=True)
    
    # Clean up any existing temp directories
    for temp_dir in [temp_with_binaries, temp_without_binaries]:
        if temp_dir.exists():
            shutil.rmtree(temp_dir)
        temp_dir.mkdir()
    
    # Copy files to both directories
    print_info("Copying files...")
    for item in paths.build_dir.glob("*"):
        if item.name == "Package":  # Skip the Package directory
            continue
        if item.is_file():
            shutil.copy2(item, temp_with_binaries)
            shutil.copy2(item, temp_without_binaries)
        else:
            shutil.copytree(item, temp_with_binaries / item.name)
            shutil.copytree(item, temp_without_binaries / item.name)
    
    # Remove Binaries and Intermediate from base version
    for folder in ["Binaries", "Intermediate"]:
        folder_path = temp_without_binaries / folder
        if folder_path.exists():
            shutil.rmtree(folder_path)
    
    # Create zip files
    print_info("Creating zip archives...")
    shutil.make_archive(paths.release_zip.with_suffix(''), 'zip', temp_without_binaries)
    if include_prebuilt:
        print_info("Including prebuilt binaries package...")
        shutil.make_archive(paths.prebuilt_zip.with_suffix(''), 'zip', temp_with_binaries)
    else:
        print_info("Skipping prebuilt binaries package...")
    
    # Clean up temp directories
    shutil.rmtree(temp_with_binaries)
    shutil.rmtree(temp_without_binaries)
    
    print_info(f"Created package at: {paths.release_zip}")
    if include_prebuilt:
        print_info(f"Created prebuilt package at: {paths.prebuilt_zip}")

def main():
    """Main execution function"""
    try:
        args = parse_args()
        paths = setup_paths(args)
        
        # Validate paths
        validate_paths(paths)
        
        # Update .uplugin version information
        print_info(f"\nUpdating plugin version information...")
        update_uplugin_version(paths.plugin, args.version, args.ue_version)
        
        # Display build information
        print_info(f"\nBuilding plugin: {args.plugin_name} version {args.version}")
        print_path(f"Using Unreal Engine at: {paths.ue_path}")
        print_info(f"Output directory: {paths.build_dir}")
        
        # Build the plugin
        print_info(f"\nBuilding plugin...")
        build_plugin(paths)
        
        # Create packages
        print_info(f"\nCreating packages...")
        create_packages(paths, args.include_prebuilt)
        
        print_info(f"\nBuild completed successfully!")
        
    except Exception as e:
        print_error(f"Build failed: {str(e)}")
        sys.exit(1)

if __name__ == "__main__":
    main()