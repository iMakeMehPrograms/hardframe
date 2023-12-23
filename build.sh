#!/usr/bin/zsh

delete_files=''
configure_cmake=''
dont_build=''
run_code=''
cleanup=''

for arg in "$@" ; do
    if [[ "$arg" = 'delete' ]] ; then
        delete_files=1
    fi
    if [[ "$arg" = 'config' ]] ; then
        configure_cmake=1
    fi
    if [[ "$arg" = 'nobuild' ]] ; then
        dont_build=1
    fi
    if [[ "$arg" = 'run' ]] ; then
        run_code=1
    fi
    if [[ "$arg" = 'clean' ]] ; then
        cleanup=1
    fi
done

if [[ "$delete_files" ]]
then
echo "Deleting files..."
rm -r ./build/*
fi

if [[ "$configure_cmake" ]]
then
echo "Generating config..."
cmake -B build -S . -D CMAKE_INSTALL_PREFIX=install
fi

if [[ "$dont_build" ]]
then
echo "Skipping build process.."
else
echo "Building binary..."
cmake --build build --target all
fi

if [[ "$cleanup" ]]
then
echo "Cleaning extra files..."
rm ./build/lib/*.a
fi

if [[ "$run_code" ]]
then
echo "Executing binary..."
./build/bin/hardframe-test
fi