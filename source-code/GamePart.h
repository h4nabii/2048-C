/*
	GAME2048
	version 4
	GamePart.h
*/

//游戏相关函数声明
void game2048(int * score, int ifTest);											//游戏主函数
int getCommand();																//获取游戏指令
void printEnd();																//打印失败界面
void printBlocks(int N[][4], int * score, int * highestScore);					//打印方块
void addBlocks(int N[][4]);														//添加方块
int moveBlocks(int N[][4], int mode);											//移动方块
int addUpBlocks(int N[][4], int mode, int * score);								//加和方块
bool testIfEnd(int N[][4]);														//测试结束
const int MOVE_UP = 1, MOVE_DOWN = 2, MOVE_LEFT = 3, MOVE_RIGHT = 4;

//******************************************************************************************

//打印方块
void printBlocks(int N[][4], int * score, int * highestScore) 
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	printf("|******|******|******|******|  最高分：%d\n", ((*highestScore > *score) ? (*highestScore) : (*score)));
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
			if (N[i][j] == 0)
			{
				SetConsoleTextAttribute(hOut, 
					BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
				printf("|      ");
			}
			else
			{
				SetConsoleTextAttribute(hOut,
					BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);	
				printf("|");
				switch (N[i][j])
				{
				case(2):
					SetConsoleTextAttribute(hOut, 
						BACKGROUND_RED | BACKGROUND_INTENSITY |
						FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);	
					printf(" %-5d", N[i][j]);
					break;
				case(4):
					SetConsoleTextAttribute(hOut, BACKGROUND_RED |
						FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf(" %-5d", N[i][j]);
					break;
				case(8):
					SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY |
						FOREGROUND_BLUE);	
					printf(" %-5d", N[i][j]);
					break;
				case(16):
					SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_GREEN |
						FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf(" %-5d", N[i][j]);
					break;
				case(32):
					SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_INTENSITY |
						FOREGROUND_BLUE);															
					printf(" %-5d", N[i][j]);
					break;
				case(64):
					SetConsoleTextAttribute(hOut, BACKGROUND_GREEN |	
						FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf(" %-5d", N[i][j]);
					break;
				case(128):
					SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | BACKGROUND_INTENSITY |	
						FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf(" %-5d", N[i][j]);
					break;
				case(256):
					SetConsoleTextAttribute(hOut, BACKGROUND_BLUE |
						FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf(" %-5d", N[i][j]);
					break;
				case(512):
					SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY |
						FOREGROUND_BLUE);	
					printf(" %-5d", N[i][j]);
					break;
				case(1024):
					SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE |
						FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf(" %-5d", N[i][j]);
					break;
				case(2048):
					SetConsoleTextAttribute(hOut,
						BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY |
						FOREGROUND_BLUE);
					printf(" %-5d", N[i][j]);
					break;
				case(4096):
					SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | BACKGROUND_GREEN |	
						FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
				default:
					printf(" %-5d", N[i][j]);
					break;
				}
			}
		SetConsoleTextAttribute(hOut,
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		if (j == 0)
			printf("|  分数  ：%d\n", *score);
		else
			printf("|\n");
		printf("|******|******|******|******|\n");
	}
	printf(" * 用WASD控制  * Q退出\n");
	printf(" * 关闭输入法或切换成英文以获得最佳游戏体验\n");
}

//添加方块
void addBlocks(int N[][4])
{
	int i, j;
	bool dup;
	int addBlockNumber;
	int randBlockNumber;

	do
	{
		dup = false;
		randBlockNumber = rand() % 20;

		if (randBlockNumber >= 0 && randBlockNumber <= 15)
			addBlockNumber = 2;
		if (randBlockNumber >= 16 && randBlockNumber <= 20)
			addBlockNumber = 4;

		i = (rand() % 4);
		j = (rand() % 4);

		if (N[i][j] == 0)
			N[i][j] = addBlockNumber;
		else
			dup = true;

	} while (dup);
}

//移动方块
int moveBlocks(int N[][4], int mode) {
	int lastOne, thisOne, haveMove = 0;
	int up = 0, down = 0, left = 0, right = 0;
	switch (mode) 
	{
	case(MOVE_UP):
		up = 1;
		break;
	case(MOVE_DOWN):
		down = 1;
		break;
	case(MOVE_LEFT):
		left = 1;
		break;
	case(MOVE_RIGHT):
		right = 1;
		break;
	default:
		break;
	}
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 3; i++)
		{
			lastOne = N[j*(up + down) + i * left + (3 - i)*right]
				[j*(right + left) + i * up + (3 - i)*down];
			thisOne = N[j*(up + down) + (i + 1)*left + (2 - i)*right]
				[j*(right + left) + (i + 1)*up + (2 - i)*down];

			if (lastOne == 0 && thisOne != 0)
			{
				lastOne = thisOne;
				thisOne = 0;
				N[j*(up + down) + i * left + (3 - i)*right]
					[j*(right + left) + i * up + (3 - i)*down] = lastOne;
				N[j*(up + down) + (i + 1)*left + (2 - i)*right]
					[j*(right + left) + (i + 1)*up + (2 - i)*down] = thisOne;
				haveMove++;
			}
		}
	return haveMove;
}

//加和方块
int addUpBlocks(int N[][4], int mode, int * score) {
	int lastOne, thisOne, haveAdd = 0;
	int up = 0, down = 0, left = 0, right = 0;

	switch (mode) 
	{
	case(MOVE_UP):
		up = 1;
		break;
	case(MOVE_DOWN):
		down = 1;
		break;
	case(MOVE_LEFT):
		left = 1;
		break;
	case(MOVE_RIGHT):
		right = 1;
		break;
	default:
		break;
	}

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 3; i++) {
			lastOne = N[j*(up + down) + i * left + (3 - i)*right][j*(right + left) + i * up + (3 - i)*down];
			thisOne = N[j*(up + down) + (i + 1)*left + (2 - i)*right][j*(right + left) + (i + 1)*up + (2 - i)*down];

			if (lastOne == thisOne && lastOne != 0 && thisOne != 0) {
				haveAdd++;
				lastOne = 2 * thisOne;
				*score += (2 * thisOne);
				thisOne = 0;
				N[j*(up + down) + i * left + (3 - i)*right][j*(right + left) + i * up + (3 - i)*down] = lastOne;
				N[j*(up + down) + (i + 1)*left + (2 - i)*right][j*(right + left) + (i + 1)*up + (2 - i)*down] = thisOne;
			}


		}
	}
	return haveAdd;
}


//获取游戏指令
int getCommand()
{
	int doChoice;
	do
	{
		doChoice = _getch();
	} while ((doChoice != 'w') && (doChoice != 's') && (doChoice != 'a') && (doChoice != 'd') && (doChoice != 'q'));

	switch (doChoice)
	{
	case('w'):
		return 1;
		break;
	case('s'):
		return 2;
		break;
	case('a'):
		return 3;
		break;
	case('d'):
		return 4;
		break;
	case('q'):
		return 0;
		break;
	default:
		return 0;
		break;
	}
}

//测试结束
bool testIfEnd(int N[][4])
{
	int up, down, left, right;
	int lastOne, thisOne;
	bool end = true;
	bool noBlank = true;

	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			if (N[i][j] == 0) 
			{
				noBlank = false;
				end = false;
			}

	for (int k = 0; k < 4; k++)
	{
		up = 0, down = 0, left = 0, right = 0;
		switch (k)
		{
		case(0):
			up = 1;
			break;
		case(1):
			down = 1;
			break;
		case(2):
			left = 1;
			break;
		case(3):
			right = 1;
			break;
		}

		if (noBlank)
			for (int j = 0; j < 4; j++)
				for (int i = 0; i < 3; i++)
				{
					lastOne = N[j*(up + down) + i * left + (3 - i)*right]
						[j*(right + left) + i * up + (3 - i)*down];
					thisOne = N[j*(up + down) + (i + 1) * left + (2 - i)*right]
						[j*(right + left) + (i + 1)*up + (2 - i)*down];
					if (lastOne == thisOne) 
						end = false;
				}
	}
	return end;
}

//打印失败界面
void printEnd()
{
	printf("                                          \n");
	printf("|****************************************|\n");
	printf("|                                        |\n");
	printf("|                 你输了！               |\n");
	printf("|                                        |\n");
	printf("|              1：再来一次               |\n");
	printf("|                                        |\n");
	printf("|              0：返回主页               |\n");
	printf("|                                        |\n");
	printf("|****************************************|\n\n");
}

//游戏主函数
void game2048(int * score, int ifTest)
{	
	bool end;
	int doChoice;
	int blockNumber[4][4];
	int addNumber = 0, moveNumber = 0;
	int quit = 0;
	int surequit = 0;

	int highestScore = 0;
	int * pHighestScore;
	pHighestScore = &highestScore;

	FILE * scoreFile;
	errno_t fileErr;

	int counter;							//测试数据数量时读取数据的储存变量
	int quantityOfData = 0;					//数据数量

	fileErr = fopen_s(&scoreFile, "SAVE\\SCORE\\score.txt", "r");

	fscanf_s(scoreFile, "%d", &counter);
	while (counter != 0)									//计数据数量
	{
		for (int i = 0; i < 6; i++)
			fscanf_s(scoreFile, "%d", &counter);
		
		quantityOfData++;
		fscanf_s(scoreFile, "%d", &counter);
	}

	fclose(scoreFile);

	if (quantityOfData != 0)								//若有数据
	{

		int * scoreData = (int *)malloc(7 * quantityOfData * sizeof(int));

		fileErr = fopen_s(&scoreFile, "SAVE\\SCORE\\score.txt", "r");

		for (int i = 0; i < quantityOfData; i++)			//读取数据
		{
			fscanf_s(scoreFile, "%d", scoreData + 7 * i);
			
			if (scoreData + 7 * i != 0)
				for (int j = 1; j < 7; j++)
					fscanf_s(scoreFile, "%d", scoreData + (7 * i + j));
		}

		fclose(scoreFile);

		for (int i = 0; i < quantityOfData; i++)
			if (highestScore < *(scoreData + 7 * i))
				highestScore = *(scoreData + 7 * i);

	}
	else													//若无数据
	{
		highestScore = 0;
	}

	*score = 0;

	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			blockNumber[i][j] = 0;


	if (ifTest)
	{
		for (int j = 0; j < 4; j++)
			for (int i = 0; i < 4; i++)
				blockNumber[i][j] = (int)pow(2.00, (double)i + (double)j * 4 + 1);
		
		blockNumber[3][3] = 0;
	}
	else
	{
		addBlocks(blockNumber);
	}

	do
	{
		printBlocks(blockNumber, score, pHighestScore);

		if (ifTest)
			doChoice = 4;
		else
			doChoice = getCommand();
		
		if (doChoice == 0)
		{
			system("cls");
			printf("                                          \n");
			printf("|****************************************|\n");
			printf("|                                        |\n");
			printf("|                                        |\n");
			printf("|               确定退出？               |\n");
			printf("|                                        |\n");
			printf("|               1：退出                  |\n");
			printf("|                                        |\n");
			printf("|               0：返回                  |\n");
			printf("|                                        |\n");
			printf("|                                        |\n");
			printf("|                                        |\n");
			printf("|                                        |\n");
			printf("|                                        |\n");
			printf("|                                        |\n");
			printf("|                                        |\n");
			printf("|                                        |\n");
			printf("|                                        |\n");
			printf("|                                        |\n");
			printf("|                                        |\n");
			printf("|****************************************|\n\n");
			surequit = getNumberChoice(0,1);
			
			if (surequit == 1)
			{
				end = true;
				quit = true;
			}
			else
			{
				end = false;
				quit = false;
			}
		}

		if (!surequit)
		{
			for (int i = 0; i < 4; i++)
			{
				if (i == 2)
					addNumber += addUpBlocks(blockNumber, doChoice, score);
				else
					moveNumber += moveBlocks(blockNumber, doChoice);
			}
			while ((addNumber + moveNumber) != 0)
			{
				addBlocks(blockNumber);
				addNumber = 0, moveNumber = 0;
			}

			if (doChoice != 0)
				end = testIfEnd(blockNumber);
		}

	} while (!end);

	printBlocks(blockNumber, score, pHighestScore);

	if (!ifTest && !quit)
		saveScore(*score);
}
