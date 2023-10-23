SRC = source-code
MAIN = 2048
OUTPUT_CHARSET = GBK

make: $(SRC)/$(MAIN).c
	gcc $(SRC)/$(MAIN).c -o $(MAIN) -fexec-charset=$(OUTPUT_CHARSET)