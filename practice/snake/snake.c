
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#pragma comment(lib, "winmm.lib")

/// @brief 首页
void firstPage()
{
	printf("\t\t\t\t 欢迎来到贪吃蛇！\n\n");
	printf("\t\t\t\t 开始游戏 - 输入空格！\n\n");
	printf("\t\t\t\t 退出游戏 - 输入 q ！\n\n");
}
/// @brief 播放背景音乐；
/// @param path 背景音乐路径， 只支持wav;
void playsound(char * path)
{
	PlaySound(path, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
void opration()
{
	char ch;
	// 检测输入的值
	while (1)
	{
		ch = _getch();
		if (ch == ' ')
		{
			break;
		}
		if (ch == 'q')
		{
			//突出
			exit(0);
		}
	}

}

int main()
{
	//首页
	firstPage();
	//播放声音
	playsound("C:/Users/lvpeng/QTworkspacse/cpping/practice/snake.wav");
	//等待操作
	opration();
	// 开始游戏
	// 关闭声音
	PlaySound(NULL, NULL, NULL);
	system("cls");
	printf("游戏开始");

	system("pause");
	return 0;
}