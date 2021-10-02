if [ ! -d "out" ] 
then
  mkdir -p out
fi
cd out
cmake -D CMAKE_BUILD_TYPE=Release ..
make -j $(nproc --all)
cd ..
