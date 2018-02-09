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
	int VerNumb;	//顶点数
	int ArcNumb;	//边数
	int Vertex[MAXSIZE]; //顶点向量
	int weight[MAXSIZE]; //顶点权重
	DMatrix Matrix;
}Graph;

void CreatGraph_ByConsol(Graph &graph);
void CreatGraph_ByFile(Graph &graph);
void Show_Graph(Graph &graph);
void IintGraph(Graph &graph);