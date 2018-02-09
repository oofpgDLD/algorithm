#pragma once
#include<stdio.h>
#include<stdlib.h>
#include "string.h"

#define MAXSIZE 200

typedef struct MATRIX
{
	int weight;
}DMatrix[MAXSIZE][MAXSIZE];

typedef struct GRAPH
{
	int VerNumb;	//������
	int ArcNumb;	//����
	int Vertex[MAXSIZE]; //��������
	int weight[MAXSIZE]; //����Ȩ��
	DMatrix Matrix;
}Graph;

void CreatGraph_ByConsol(Graph &graph);
void CreatGraph_ByFile(Graph &graph);
void Show_Graph(Graph &graph);
void IintGraph(Graph &graph);