threshold: threshold_cipher.cpp threshold_cipher.hpp
	g++ -c -o threshold_cipher.o threshold_cipher.cpp

main: threshold_cipher.o main.cpp
	g++ -o ./main.out threshold_cipher.o main.cpp