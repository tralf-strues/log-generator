Options = -Wall -Wpedantic

SrcDir = src
BinDir = bin

$(BinDir)\log_generator.a : $(BinDir)\log_generator.o
	ar ru $(BinDir)\log_generator.a $(BinDir)\log_generator.o
	
$(BinDir)\log_generator.o : $(SrcDir)\log_generator.cpp $(SrcDir)\log_generator.h
	g++ -o $(BinDir)\log_generator.o -c $(SrcDir)\log_generator.cpp $(Options)