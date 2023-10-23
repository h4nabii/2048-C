SRC = source-code
MAIN = 2048

make: $(SRC)/$(MAIN).cpp
	g++ $(SRC)/$(MAIN).cpp -o $(MAIN)