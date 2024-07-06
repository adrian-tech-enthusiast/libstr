#!/bin/bash
#
# @file build.sh
# @brief Script to build the main application and create libraries.
#
# This script sets up the environment and builds the main application executable
# and the associated shared and static libraries. It uses helper functions defined
# in helper.sh for various build-related tasks.
#
# @usage
# Run this script from the root of your project:
#   ./build.sh;
#
# Global settings:
# - BASE_NAME: Base name for the project.
# - PROJECT_PATH: Root path of the project.
# - TEST_DEPENDENCIES: Dependencies for tests.
# - LIBRARY_DEPENDENCIES: Dependencies for libraries.
# - LIBRARY_CODE_SEARCH_PATHS: Search paths for library code.
# - TEST_CODE_SEARCH_PATHS: Search paths for test code.
# - BASE_BUILD_PATH: Base build directory.
# - LIBRARY_BUILD_PATH: Build directory for libraries.
# - TEST_BUILD_PATH: Build directory for tests.
# - BIN_PATH: Output directory for binaries.
# - APP_NAME: Name of the main application.

# Determine the directory of the script
SCRIPT_DIR=$(dirname "$(readlink -f "$0")");
# Load helper functions
source "$SCRIPT_DIR/helper.sh";

# Global Settings.
BASE_NAME='libstr';   # Base name for the project.
PROJECT_PATH=$(pwd);  # Root path of the project.

# Dependencies for tests and library (add as needed).
TEST_DEPENDENCIES='';
LIBRARY_DEPENDENCIES='';

# Search paths for library and test code.
LIBRARY_CODE_SEARCH_PATHS="$PROJECT_PATH/include $PROJECT_PATH/src";
TEST_CODE_SEARCH_PATHS="$LIBRARY_CODE_SEARCH_PATHS $PROJECT_PATH/tests";

# Build paths.
BASE_BUILD_PATH="$PROJECT_PATH/build";
LIBRARY_BUILD_PATH="$BASE_BUILD_PATH/library";
TEST_BUILD_PATH="$BASE_BUILD_PATH/test";

# Output paths.
BIN_PATH="$PROJECT_PATH/bin";
APP_NAME="$BASE_NAME.app";

# Clean up build directory before start the build.
clean_directory "$BASE_BUILD_PATH";

# Build the main app.
app_files_to_compile=$(get_files_to_compile "$TEST_CODE_SEARCH_PATHS");
build_app "$app_files_to_compile" $TEST_BUILD_PATH $APP_NAME "$TEST_DEPENDENCIES" $BIN_PATH;

# Create shared and static libraries.
library_files_to_compile=$(get_files_to_compile "$LIBRARY_CODE_SEARCH_PATHS");
create_libraries "$library_files_to_compile" $LIBRARY_BUILD_PATH $BASE_NAME "$LIBRARY_DEPENDENCIES" $BIN_PATH;

# Test the APP execution.
"$BIN_PATH/$APP_NAME";
