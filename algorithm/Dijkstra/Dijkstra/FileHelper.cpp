#include "FileHelper.h"

#define FILE_PATH "E:/各种课程的作业/arithmetic/Dijkstra/Debug/graph.txt"  // 文件路径

int readFile(char *ch) {

	FILE *fp;  // 文件指针 
	//char ch;
	int len = 0;
	// 判断文件是否能够正确创建/打开 
	if ((fp = fopen(FILE_PATH, "r")) == NULL) {
		perror(FILE_PATH);
		return -1;
	}
	while ((ch[len] = fgetc(fp)) != EOF)
	{
		len++;
	}
	fclose(fp);

	return len;
}