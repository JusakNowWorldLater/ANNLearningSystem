NECESSARY_FILES = main.o node.o layer.o perceptron.o gskfunctions.o

.SUFFIXES: .cpp .h 

FLAGS = -std=c++11 -IHeader 

main:$(NECESSARY_FILES) 
	g++  $(NECESSARY_FILES) -o $@

main.o:Source/main.cpp Source/perceptron.cpp Source/layer.cpp Source/layer.cpp Source/gskfunctions.cpp
	g++ $(FLAGS) -c Source/main.cpp 

perceptron.o:Source/perceptron.cpp Source/layer.cpp
	g++ $(FLAGS) -c Source/perceptron.cpp

layer.o:Source/layer.cpp Source/node.cpp
	g++ $(FLAGS) -c Source/layer.cpp

node.o:Source/node.cpp 
	g++ $(FLAGS) -c Source/node.cpp

gskfunctions.o:Source/gskfunctions.cpp
	g++ $(FLAGS) -c Source/gskfunctions.cpp