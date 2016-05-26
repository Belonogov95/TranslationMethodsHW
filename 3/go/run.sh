make clean
make
./calc < $1 > prog.cpp
g++ prog.cpp -o prog
./prog



