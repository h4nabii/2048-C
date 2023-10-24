SRC = source-code
OUT = dist
MAIN = 2048
OUT_CHARSET = GBK

make: $(SRC)/$(MAIN).c $(OUT)
	gcc $(SRC)/$(MAIN).c -o $(OUT)/$(MAIN) -fexec-charset=$(OUT_CHARSET)

$(OUT):
	mkdir $(OUT)