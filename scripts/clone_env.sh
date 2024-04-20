#!/bin/bash

# Create the directory 'third-party' if it doesn't exist
mkdir -p third-party

# Clone CImg repository
echo "Cloning CImg repository..."
git clone https://github.com/GreycLab/CImg third-party/CImg

# Clone libjpeg repository
echo "Cloning libjpeg repository..."
git clone https://github.com/kornelski/libjpeg third-party/libjpeg

# Change directory to libjpeg
cd third-party/libjpeg

# Run the configure script
echo "Running configure script..."
./configure
make -j
make test
cd ../../

echo "Cloning and configuration completed."
