all: compile link
compile:
	g++ -std=c++17 -I external/include includes ./main.cpp -o main.o
link:
	g++ main.o -o main -L external/lib -l sfml-graphics -l sfml-window -l sfml-system  