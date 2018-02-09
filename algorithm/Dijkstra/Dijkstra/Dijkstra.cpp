// Dijkstra.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AdjacencyMatrix.h"
#include "FileHelper.h"

void dijkstra(Graph &graph);

int out[MAXSIZE];
int lastNode = 0;

int main()
{
	Graph graph;
	IintGraph(graph);
	CreatGraph_ByFile(graph);
	//Show_Graph(graph);

	//Graph graph;
	//IintGraph(graph);
	//CreatGraph_ByConsol(graph);
	//Show_Graph(graph);

	dijkstra(graph);
	for (int i = 0;i<MAXSIZE;i++)
	{
		printf("%d\r\n", graph.weight[i]);
	}

	while ('b' != getchar())
	{
		;
	}
    return 0;
}

void init(Graph &graph)
{
	for (int i=0;i<graph.VerNumb;i++)
	{
		if(i == 0)
			graph.weight[i] = 0;
		else
			graph.weight[i] = 65535;
		out[i] = 0;
	}
}

void dijkstra(Graph &graph)
{
	init(graph);
	while (true)
	{
		bool bp = true;
		int minNode = 0;
		int minDist = 65535;
		for (int i = 0; i<graph.VerNumb; i++)
		{
			if (graph.Matrix[lastNode][i].weight != 0 && out[i] >= 0)
			{
				if (graph.weight[i] > graph.Matrix[lastNode][i].weight + graph.weight[lastNode])
				{
					graph.weight[i] = graph.Matrix[lastNode][i].weight + graph.weight[lastNode];
				}
				if (graph.weight[i] < minDist)
				{
					minDist = graph.weight[i];
					minNode = i;
				}
			}
		}
		lastNode = minNode;
		out[lastNode] = -1;

		for (int i = 0; i<graph.VerNumb; i++)
		{
			if (out[i] >= 0)
			{
				bp = false;
			}
		}
		if (bp)
		{
			break;
		}
	}
}
