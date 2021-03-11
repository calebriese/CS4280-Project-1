CC 	 = g++
CFLAGS   = -std=c++11 
TARGET   = scanner
OBJFILES =
SOURCE = main.cpp testScanner.cpp scanner.cpp scanner.h testScanner.h token.h
OUTPUT = $(TARGET) $(TARGETb)

all: $(OUTPUT)
 
$(TARGET): $(OBJFILES)  
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS) 

$(TARGETb): $(OBJFILES)
	$(CC) -o $(TARGETb) $(SOURCEb) $(CFLAGS) 

clean: 
	rm -f $(TARGET) $(TARGETb) *.o adder_log output.log
