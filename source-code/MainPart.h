/*
	GAME2048
	version 4
	MainPart.h
*/

//主页相关函数声明
void printGreeting(int ifColorTest);						//打印欢迎界面
void menuGreeting();										//打印菜单界面
int getNumberChoice(int start, int end);					//获取数字选择

//******************************************************************************************

//打印欢迎界面
void printGreeting(int ifColorTest)
{
	system("cls");
	printf("                                          \n");
	printf("|****************************************|\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|               游戏：2048               |\n");
	printf("|                                        |\n");

	printf(ifColorTest == 1 ? "|         1：开始(颜色测试模式)          |\n" : "|                1：开始                 |\n");

	printf("|                                        |\n");
	printf("|                2：菜单                 |\n");
	printf("|                                        |\n");
	printf("|                0：退出                 |\n");
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
}

// 获取数字选择
int getNumberChoice(int start, int end)
{
	int ans;
	int wrong;
	do
	{
		ans = _getch();
		if (((ans - 48) >= start) && ((ans - 48) <= end))
		{
			wrong = 0;
			return ans - 48;
		}
		else
		{
			wrong = 1;
		}
	}
	while (wrong == 1);
	return 0;
}

//打印菜单界面
void menuGreeting()
{
	system("cls");
	printf("                                          \n");
	printf("|****************************************|\n");
	printf("|                                        |\n");
	printf("|                                        |\n");
	printf("|               游戏：2048               |\n");
	printf("|                                        |\n");
	printf("|               1：分数记录              |\n");
	printf("|                                        |\n");
	printf("|               2：设置                  |\n");
	printf("|                                        |\n");
	printf("|               0：退出                  |\n");
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
}
