#!/usr/bin/zsh

if [[ $3 = "delete" ]]
then
echo "Deleting files..."
rm -r ./build/*
fi

if [[ $2 = "config" ]]
then
echo "Generating config..."
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=install
fi

echo "Building binary..."
cmake --build build --target all

if [[ $1 = "run" ]]
then
echo "Executing binary..."
./build/bin/hardframe-test
fi