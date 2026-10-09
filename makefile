SHELL = pwsh.exe
.SHELLFLAGS = -NoProfile -Command

# ===== 配置 =====
SRC         = source-code
OUT         = dist
MAIN        = 2048

CC          = clang
CFLAGS      = -std=c17 -Wall -Wextra -g
CHARSET     = -finput-charset=UTF-8

SRC_FILE    = $(SRC)/$(MAIN).c
OUT_FILE    = $(OUT)/$(MAIN).exe

# ===== 目标 =====
all: $(OUT_FILE)

$(OUT_FILE): $(SRC_FILE) | $(OUT)
	$(CC) $(CFLAGS) $(CHARSET) $(SRC_FILE) -o $(OUT_FILE)

$(OUT):
	New-Item -ItemType Directory -Force -Path $(OUT) | Out-Null

clean:
	if (Test-Path $(OUT)\$(MAIN).exe) { Remove-Item -Force $(OUT)\$(MAIN).exe }

rebuild: clean all

run: all
	$(OUT_FILE)

.PHONY: all clean rebuild run