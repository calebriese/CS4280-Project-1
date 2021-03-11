CC 	 = g++
CFLAGS   = -std=c++11 
TARGET   = scanner
SOURCE = main.cpp testScanner.cpp scanner.cpp scanner.h testScanner.h token.h
OUTPUT = $(TARGET)
 
$(TARGET): $(OBJFILES)  
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS) 

clean: 
	rm -f $(TARGET) $(TARGETb) *.o
