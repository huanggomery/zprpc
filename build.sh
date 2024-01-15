#!/bin/bash

protoc zprpc/pb/rpc_protocol.proto --cpp_out=./
protoc example/pb/calculate.proto --cpp_out=./

# Array containing the list of header files to copy
header_files=(
    "zprpc/include/rpc_channel.h"
    "zprpc/include/rpc_config.h"
    "zprpc/include/rpc_controller.h"
    "zprpc/include/rpc_service.h"
)

# Flag to check if copy operation fails
copy_failed=false

# Run xmake to build the project
xmake

# Check if xmake build succeeded
if [ $? -eq 0 ]; then
    # Check if the user provided a destination path for the library
    if [ $# -eq 0 ]; then
        # Create the directory if it doesn't exist
        sudo mkdir -p /usr/local/lib/
        sudo mkdir -p /usr/local/include/zprpc/

        # If no path is provided, copy the generated static library to the default /usr/local/lib using sudo
        sudo cp ./lib/libzprpc.a /usr/local/lib/
        echo "Library copied to the default path /usr/local/lib/"

        # If no path is provided, copy the necessary headers to the default /usr/local/include/zprpc/ using sudo
        for file in "${header_files[@]}"; do
            if sudo cp -r "$file" /usr/local/include/zprpc/; then
                echo "Copied $file successfully"
            else
                echo "Failed to Copy $file"
                copy_failed=true
            fi
        done
        echo "Headers copied to the default path /usr/local/include/zprpc/"
    else
        # Create the directory if it doesn't exist
        sudo mkdir -p "$1/lib/"
        sudo mkdir -p "$1/include/zprpc/"

        # If a path is provided, copy the generated static library to the specified path using sudo
        sudo cp ./lib/libzprpc.a "$1/lib/"
        echo "Library copied to the specified path: $1/lib/"

        # If a path is provided, copy the necessary headers to the specified path using sudo
        for file in "${header_files[@]}"; do
            if sudo cp -r "$file" "$1/include/zprpc/"; then
                echo "Copied $file successfully"
            else
                echo "Failed to Copy $file"
                copy_failed=true
            fi
        done
        echo "Headers copied to the specified path: $1/include/zprpc/"
    fi

    if [ "$copy_failed" = true ]; then
        echo "Build failed due to copy errors."
    else
        echo "Build completed successfully!"
    fi
else
    echo "Build failed. Please check the errors."
fi
