mkdir -p ./build_test
cd ./build_test
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
