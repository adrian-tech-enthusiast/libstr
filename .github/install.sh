#!/bin/bash

# @file install.sh
# @brief Script for installing shared libraries and header files locally.
#
# This script automates the installation of shared libraries and header files
# into system directories for local development or deployment. It utilizes helper
# functions from "helper.sh" to perform these tasks.
#
# Global Settings:
# - PROJECT_PATH: The root path of the project.
# - BIN_PATH: Path where executable binaries will be stored.
# - INCLUDE_PATH: Path where header files will be installed.


# Determine the directory of the script
SCRIPT_DIR=$(dirname "$(readlink -f "$0")");
# Load helper functions
source "$SCRIPT_DIR/helper.sh";

# Global Settings.
PROJECT_PATH=$(pwd);
BIN_PATH="$PROJECT_PATH/bin";
INCLUDE_PATH="$PROJECT_PATH/include";

# Install library locally.
install_library_localy "$BIN_PATH" "$INCLUDE_PATH";