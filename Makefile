Options = -Wall -Wpedantic

SrcDir = src
BinDir = bin
Intermidiates = $(BinDir)/intermediates

$(BinDir)/log_generator.a : $(Intermidiates)/log_generator.o
	ar ru $(BinDir)/log_generator.a $(Intermidiates)/log_generator.o
	
$(Intermidiates)/log_generator.o : $(SrcDir)/log_generator.cpp $(SrcDir)/log_generator.h
	g++ -o $(Intermidiates)/log_generator.o -c $(SrcDir)/log_generator.cpp $(Options)