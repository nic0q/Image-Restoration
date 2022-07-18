FLAGS= -O2 -g

all: test_ImageProcessor test_Optimizer test_Image Objective.o Optimizer.o main visualize
# 				El problema de generar la imagen restaurada debiese estar en una clase "ImageRestoration"
Image.o: Image.cpp Image.h 
	g++ $(FLAGS) -c Image.cpp 

Objective.o: Objective.cpp Objective.h
	g++ $(FLAGS) -c Objective.cpp

Optimizer.o: Optimizer.cpp Optimizer.h
	g++ $(FLAGS) -c Optimizer.cpp

ImageProcessor.o: ImageProcessor.cpp ImageProcessor.h
	g++ $(FLAGS) -c ImageProcessor.cpp 

main: Objective.o Optimizer.o main.cpp Image.o ImageProcessor.o
	g++ $(FLAGS) -o main main.cpp Objective.o Optimizer.o Image.o ImageProcessor.o

visualize: Objective.o Optimizer.o visualize.cpp Image.o ImageProcessor.o
	g++ $(FLAGS) -o visualize visualize.cpp Objective.o Optimizer.o Image.o ImageProcessor.o 

test_Image: Image.o test_Image.cpp
	g++ $(FLAGS) -o test_Image test_Image.cpp Image.o

test_Objetive: Objective.o test_Objective.cpp
	g++ $(FLAGS) -o test_Objective test_Objective.cpp Objective.o 

test_ImageProcessor: test_ImageProcessor.cpp Image.o ImageProcessor.o 
	g++ $(FLAGS) -o test_ImageProcessor ImageProcessor.o test_ImageProcessor.cpp Image.o 

test_Optimizer: Objective.o Optimizer.o test_Optimizer.cpp Image.o ImageProcessor.o
	g++ $(FLAGS) -o test_Optimizer test_Optimizer.cpp Objective.o Optimizer.o Image.o ImageProcessor.o

clean:
	rm -f *.o main visualize test_Objective test_Optimizer test_ImageProcessor test_Image *.txt

test_optim:	# Muestra el test Optimizer sin generar imagen
	ipython crearTxt.py
	./test_ImageProcessor
	./test_Optimizer

test_main:	# Muestrar el main principal con las iteraciones y el tiempo que tarda
	ipython crearTxt.py
	./main
	ipython cargaTxt.py

run:	# Muestra 1 imagen restaurada y corrompida en matplotlib
	ipython crearTxt.py
	./test_ImageProcessor
	./visualize
	ipython cargaTxt.py

view:	# Visualizar el resultado
	ipython cargaTxt.py