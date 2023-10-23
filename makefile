SRC = source-code
MAIN = 2048
OUTPUT_CHARSET = GBK

make: $(SRC)/$(MAIN).cpp
	g++ $(SRC)/$(MAIN).cpp -o $(MAIN) -fexec-charset=$(OUTPUT_CHARSET)