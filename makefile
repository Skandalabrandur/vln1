all:
	g++ -w -I customLibraries/ -I UI/ -I models/ -I services/ -o main customLibraries/*.cpp UI/*.cpp models/*.cpp services/*.cpp main.cpp
