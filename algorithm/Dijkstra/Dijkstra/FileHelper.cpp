#include "FileHelper.h"

#define FILE_PATH "E:/���ֿγ̵���ҵ/arithmetic/Dijkstra/Debug/graph.txt"  // �ļ�·��

int readFile(char *ch) {

	FILE *fp;  // �ļ�ָ�� 
	//char ch;
	int len = 0;
	// �ж��ļ��Ƿ��ܹ���ȷ����/�� 
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