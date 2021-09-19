mkdir -p out
cd out
cmake -D CMAKE_BUILD_TYPE=Release ..
make -j $(nproc --all)
cd ..
