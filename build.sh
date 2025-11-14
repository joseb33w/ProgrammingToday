#!/bin/bash

# Build script for Enhanced Calculator

echo "Building Enhanced Calculator..."

# Check if GTK4 is installed
if ! pkg-config --exists gtk4; then
    echo "Error: GTK4 is not installed!"
    echo "Install it with: brew install gtk4 (macOS) or apt-get install libgtk-4-dev (Linux)"
    exit 1
fi

# Compile the GTK application
gcc $(pkg-config --cflags gtk4) -o hello_gtk hello_gtk.c $(pkg-config --libs gtk4)

if [ $? -eq 0 ]; then
    echo "Build successful! Run with: ./hello_gtk"
else
    echo "Build failed!"
    exit 1
fi

