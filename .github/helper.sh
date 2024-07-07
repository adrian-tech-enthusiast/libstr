#!/bin/bash
#
# @file helper.sh
# @brief Helper functions for building and managing the project.
#
# This script contains various helper functions that are used for building the project,
# managing build directories, and creating shared and static libraries. These functions
# are meant to be sourced by other scripts, such as build.sh, to facilitate common tasks.
#
# @usage
# Source this script in other bash scripts to use the provided functions:
#   source /path/to/helper.sh;
#
# Functions provided:
# - get_files_to_compile: Retrieves a list of header and source files to compile.
# - clean_directory: Cleans up a specified directory.
# - build_app: Builds the main application executable.
# - create_libraries: Creates shared and static libraries from source files.
# - install_library_localy: Installs shared libraries and header files locally.
# - remove_precompiled_headers: Removes precompiled header files from a specified directory.
# - clean_project_precompiled_headers: Cleans precompiled header files from the project directories.


# Function to get the list of code files to compile.
#
# Arguments:
#   $1 - Space-separated list of directories to search for code files.
#
# Outputs:
#   Space-separated list of .h and .c files found in the specified directories.
#
# Usage:
#   files_to_compile=$(get_files_to_compile "$SEARCH_PATHS");
get_files_to_compile() {
  local code_search_paths=$1;
  local header_files=$(find $code_search_paths -maxdepth 3 -type f -name "*.h" ! -path '*/\.*' | sort);
  local source_files=$(find $code_search_paths -maxdepth 3 -type f -name "*.c" ! -path '*/\.*' | sort);
  echo "$header_files $source_files";
}

# Function to clean up a directory.
#
# Arguments:
#   $1 - Directory to clean up.
#
# Usage:
#   clean_directory "$DIR_PATH";
clean_directory() {
  local dir=$1;
  rm -rf "$dir" && mkdir -p "$dir";
}

# Function to build the project.
#
# Arguments:
#   $1 - Space-separated list of files to compile.
#   $2 - Path to the build directory.
#   $3 - Name of the application to be created.
#   $4 - Space-separated list of dependencies for the build.
#   $5 - Path to the directory where the binary should be moved.
#
# Usage:
#   build_app "$FILES_TO_COMPILE" "$BUILD_PATH" "$APP_NAME" "$DEPENDENCIES" "$BIN_PATH";
build_app() {
  # Get arguments.
  local files_to_compile=$1;
  local build_path=$2;
  local app_name=$3;
  local dependencies=$4;
  local bin_path=$5;
  local current_path=$(pwd);

  # clean up build and bin folder.
  clean_directory "$build_path";
  clean_directory "$bin_path";

  # Go to the build path.
  cd "$build_path" || exit;

  # Compile the given files.
  gcc -O3 -march=native -g -fpic -save-temps -Wall -Werror -pedantic-errors -o "$app_name" $files_to_compile $dependencies;
  if [ $? -ne 0 ]; then
    echo "Compile Failed!";
    exit 1;
  fi

  # Add executable permistions to the build app;
  local app_file="$build_path/$app_name";
  if [ -f "$app_file" ]; then
    chmod +x "$app_file";
  fi

  # Move executables to the bin directory.
  mv $app_name $bin_path || exit;

  # Go back to where we were before.
  cd "$current_path" || exit;
}

# Function to create shared and static libraries.
#
# Arguments:
#   $1 - Space-separated list of files to compile.
#   $2 - Path to the build directory.
#   $3 - Base name of the library to be created.
#   $4 - Space-separated list of dependencies for the build.
#   $5 - Path to the directory where the libraries should be moved.
#
# Usage:
#   create_libraries "$FILES_TO_COMPILE" "$BUILD_PATH" "$LIBRARY_NAME" "$DEPENDENCIES" "$BIN_PATH";
create_libraries() {
  # Get arguments.
  local files_to_compile=$1;
  local build_path=$2;
  local library_name=$3;
  local dependencies=$4;
  local bin_path=$5;
  local current_path=$(pwd);

  # Clean up build folder and previous compiled libraries.
  clean_directory "$build_path";
  rm -rf "$bin_path/$library_name.so";
  rm -rf "$bin_path/$library_name.a";

  # Go to the build path.
  cd "$build_path" || exit;

  # Build the objects for the library.
  gcc -O3 -shared -march=native -g -fpic -save-temps -Wall -Werror -pedantic-errors $files_to_compile $dependencies;
  if [ $? -ne 0 ]; then
    echo "Compile Failed!";
    exit 1;
  fi

  # Get the object files to include in the library;
  local obj_files=$(find $build_path -type f -name "*.o" ! -path '*/\.*' | sort);

  # Create single shared library file from the object module(s).
  gcc -shared -Wno-undef -Wl,-soname,$library_name.so -o $library_name.so $obj_files $dependencies -L$build_path;
  if [ $? -ne 0 ]; then
    echo "Compile Failed!";
    exit 1;
  fi

  # Create the static library (archive) from the object files using the ar tool.
  ar rcs "$build_path/$library_name.a" $obj_files;

  # Move executables to the bin directory.
  mv "$build_path/$library_name.so" "$bin_path" || exit;
  mv "$build_path/$library_name.a" "$bin_path" || exit;

  # Go back to where we were before.
  cd "$current_path" || exit;
}

# Function to installs shared libraries and header files locally.
#
# Arguments:
#   $1: Path to the directory containing shared library files (*.so).
#   $2: Path to the directory containing header files (*.h).
#
# Usage:
#   install_library_localy "/path/to/libraries" "/path/to/headers";
install_library_localy() {
  # Get arguments.
  local bin_path="$1"
  local include_path="$2"

  # Check if paths are provided
  if [[ -z "$bin_path" || -z "$include_path" ]]; then
    echo "Error: Both library and header paths must be provided.";
    exit 1;
  fi

  # Ensure the script has appropriate privileges.
  if [[ $EUID -ne 0 ]]; then
    echo "Error: This script must be run as root to install libraries."
    exit 1
  fi

  # Install shared library files to "/usr/local/lib" folder.
  local library_files=$(find "$bin_path" -maxdepth 3 -type f -name "*.so" ! -path '*/\.*' | sort);
  for file in $library_files; do
    # Extract the name of the .so file and print a friendly message.
    library_name=$(basename "$file");
    echo "Installing $library_name library into '/usr/local/lib/'..."
    # Install the library.
    cp "$file" /usr/local/lib/;
  done

  # Install header files to /usr/local/include.
  local include_files=$(find "$include_path" -maxdepth 3 -type f -name "*.h" ! -path '*/\.*' | sort);
  for file in $include_files; do
    # Extract the name of the .h file and print a friendly message.
    header_name=$(basename "$file");
    echo "Installing $header_name header into '/usr/local/include/'..."
    cp "$file" /usr/local/include/;
  done
}

# Function to remove precompiled header files from a specified directory.
#
# Arguments:
#   $1: Path to the directory to clean.
#
# Usage:
#   remove_precompiled_headers "/path/to/directory";
remove_precompiled_headers() {
   # Get arguments.
   local dir_path="$1";

   # Ger the list of precompiled header files to remove.
   local precompiled_files=$(find "$dir_path" -maxdepth 3 -type f -name "*.h.gch" ! -path '*/\.*' | sort);

   # Remove precompiled header files.
   for file in $precompiled_files; do
     local precompiled_file_name=$(basename "$file");
     echo "Removing precompiled header file $precompiled_file_name from $dir_path...";
     rm -rf "$file";
   done
}

# Function to clean precompiled header files from the project directories.
#
# Arguments:
#   $1: Path to the root of the project.
#
# Usage:
#   clean_project_precompiled_headers "/path/to/project";
clean_project_precompiled_headers() {
  # Get arguments.
  local project_path=$1;

  # Validate the project path argument.
  if [[ -z "$project_path" ]]; then
    echo "Error: Project path must be provided.";
    exit 1;
  fi

  # Remove precompiled header files from specified directories.
  remove_precompiled_headers "$project_path/src";
  remove_precompiled_headers "$project_path/include";
  remove_precompiled_headers "$project_path/tests";
}
