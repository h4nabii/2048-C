SHELL = pwsh.exe
.SHELLFLAGS = -NoProfile -Command

# ===== 配置 =====
SRC         = src
OUT         = dist
MAIN        = 2048

CC          = clang
CFLAGS      = -std=c17 -Wall -Wextra -g
INCLUDES    = -I$(SRC)
CHARSET     = -finput-charset=UTF-8

SRC_FILE    = $(SRC)/$(MAIN).c
BOARD_FILE  = $(SRC)/board/board.c
RENDER_FILE = $(SRC)/render/render.c
# 代码几乎都在头文件里，头文件必须作为依赖，否则改了不会被重编
SRC_HEADERS = $(wildcard $(SRC)/*.h) $(wildcard $(SRC)/public/*.h) $(wildcard $(SRC)/board/*.h) $(wildcard $(SRC)/render/*.h)
OUT_FILE    = $(OUT)/$(MAIN).exe

# ===== 目标 =====
all: $(OUT_FILE)

$(OUT_FILE): $(SRC_FILE) $(BOARD_FILE) $(RENDER_FILE) $(SRC_HEADERS) | $(OUT)
	$(CC) $(CFLAGS) $(INCLUDES) $(CHARSET) $(SRC_FILE) $(BOARD_FILE) $(RENDER_FILE) -o $(OUT_FILE)

$(OUT):
	New-Item -ItemType Directory -Force -Path $(OUT) | Out-Null

clean:
	if (Test-Path $(OUT)\$(MAIN).exe) { Remove-Item -Force $(OUT)\$(MAIN).exe }

rebuild: clean all

run: all
	$(OUT_FILE)

.PHONY: all clean rebuild run