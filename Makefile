all: compile link
compile:
	g++ -std=c++17 -I external/include -c main.cpp
link:
	g++ main.o -o main -L external/lib -l sfml-graphics -l sfml-window -l sfml-system