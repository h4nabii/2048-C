#pragma once

typedef struct {
  int height;
  int width;
  int *cell;
} Board;

/**
 * 创建棋盘实例
 * @param h 高度（行数）
 * @param w 宽度（列数）
 * @return 新创建的棋盘实例指针，如果创建失败返回 NULL
 */
Board *board_create(int h, int w);

/**
 * 销毁棋盘实例
 * @param board 要销毁的棋盘实例指针
 * @return 成功返回 0，失败返回 -1
 */
int board_destroy(Board *board);

/**
 * 将棋盘数据拷贝到二维数组
 * @param board 棋盘实例指针
 * @param numbers 用于存储棋盘数据的二维数组
 */
void board_cast(Board *board, int numbers[][4]);

/**
 * 初始化棋盘
 * @param board 棋盘实例指针
 * @param test_mode 是否为测试模式，非零表示测试模式，零表示普通模式
 */
void board_setup(Board *board, int test_mode);

/**
 * 检查棋盘位置是否在有效范围内
 * @param board 棋盘实例指针
 * @param i 行索引
 * @param j 列索引
 * @return 如果位置在有效范围内返回非零，否则返回 0
 */
int board_check_pos_range(Board *board, int i, int j);

/**
 * 获取棋盘指定位置的值
 * @param board 棋盘实例指针
 * @param i 行索引
 * @param j 列索引
 * @return 如果位置有效返回对应的值，否则返回 -1
 */
int board_get(Board *board, int i, int j);

/**
 * 设置棋盘指定位置的值
 * @param board 棋盘实例指针
 * @param i 行索引
 * @param j 列索引
 * @param value 要设置的值
 * @return 如果位置有效返回 0，否则返回 -1
 */
int board_set(Board *board, int i, int j, int value);

/**
 * 检查棋盘是否已满
 * @param board 棋盘实例指针
 * @return 如果棋盘已满返回非零，否则返回 0
 */
int board_is_full(Board *board);

/**
 * 在棋盘的空位置随机添加一个新方块，值为 2 或 4
 * @param board 棋盘实例指针
 * @return 成功返回 0，失败返回 -1
 */
int board_random_add(Board *board);
