#include "AdjacencyMatrix.h"
#include "FileHelper.h"

#define FILE_WAY 2
#define CONSOL_WAY 1

typedef struct S_ARC
{
	int iFirst = 0;
	int iSecond = 0;
	int iWeight = 0;
}Arc;

typedef struct S_READBUFF
{
	int VerNumb;	//顶点数
	int ArcNumb;	//边数
	int Vertex[MAXSIZE] = {0}; //顶点向量
	Arc *arc;
	int success = 0;
}ReadBuff;

void IintGraph(Graph &graph)
{
	graph.VerNumb = 0;
	graph.ArcNumb = 0;

	for (int i = 0; i < MAXSIZE; i++)
	{
		graph.Vertex[i] = 0;
	}
	for (int i = 0; i < MAXSIZE; i++)
	{
		for (int j = 0; j < MAXSIZE; j++)
		{
			graph.Matrix[i][j].weight = 0;
		}
	}
}

void AddVertex(Graph &graph, int way, ReadBuff &readbuff)
{
	if (way == CONSOL_WAY)
	{
		printf("输入顶点数量:");
		scanf("%d", &graph.VerNumb);
		printf("输入各顶点的值:");
	}
	else if (way == FILE_WAY)
	{
		graph.VerNumb = readbuff.VerNumb;
	}

	for (int i = 0;i<graph.VerNumb;i++)
	{
		if (way == CONSOL_WAY)
		{
			scanf("%d", &graph.Vertex[i]);
		}
		else if (way == FILE_WAY)
		{
			graph.Vertex[i] = readbuff.Vertex[i];
		}
	}
}
//匹配
int Locat_vertex(Graph &graph, int vertex)
{
	for (int i = 0; i < graph.VerNumb; i++)
	{
		if (graph.Vertex[i] == vertex)
			return i;
	}
	return -1;
}

void AddArcs(Graph &graph, int way, ReadBuff &readbuff)
{
	if (way == CONSOL_WAY)
	{
		printf("输入弧的数量:");
		scanf("%d", &graph.ArcNumb);
	}
	else if (way == FILE_WAY)
	{
		graph.ArcNumb = readbuff.ArcNumb;
	}

	int iFirst = 0;
	int iSecond = 0;
	int iRow = 0;
	int iCol = 0;
	int iWeight = 0;
	
	for (int i = 0; i<graph.ArcNumb; i++)
	{
		if (way == CONSOL_WAY)
		{
			printf("输入各条弧的值(顶点1，顶点2，权重):");
			scanf("%d", &iFirst);
			scanf("%d", &iSecond);
			scanf("%d", &iWeight);
		}
		else if (way == FILE_WAY)
		{
			iFirst = readbuff.arc[i].iFirst;
			iSecond = readbuff.arc[i].iSecond;
			iWeight = readbuff.arc[i].iWeight;
		}

		iRow = Locat_vertex(graph, iFirst);
		iCol = Locat_vertex(graph, iSecond);

		graph.Matrix[iRow][iCol].weight = iWeight;
		graph.Matrix[iCol][iRow].weight = iWeight;
	}
}

void Show_Graph(Graph &graph)
{
	printf("无向图：\r\n");

	for (int row = 0; row < graph.VerNumb; row++)
	{
		for (int col = 0; col < graph.VerNumb; col++)
		{
			printf("%d\t", graph.Matrix[row][col].weight);
		}
		printf("\r\n");
	}

}

int charToInt(char c, int hightBit)
{
	int num = 0;
	num = hightBit * 10;
	num = num + int(c - '0');
	return num;
}

void InitReadBuff(ReadBuff &readbuff)
{
	char c[MAXSIZE];
	readbuff.VerNumb = 0;
	readbuff.ArcNumb = 0;
	int arcs_value;

	readFile(c);

	char * vertex_number_ptr = strstr(c, "vertex_number=");
	char * vertex_value_ptr = strstr(c, "vertex_value=");
	char * arcs_number_ptr = strstr(c, "arcs_number=");
	char * arcs_value_ptr = strstr(c, "arcs_value=");

	if (vertex_number_ptr != NULL)
	{
		vertex_number_ptr = vertex_number_ptr + strlen("vertex_number=");
	}
	
	for (int i = 0; vertex_number_ptr[i] != '\n'; i++)
	{
		readbuff.VerNumb = charToInt(vertex_number_ptr[i], readbuff.VerNumb);
	}

	if (vertex_value_ptr != NULL)
	{
		vertex_value_ptr = vertex_value_ptr + strlen("vertex_value=");
	}
	for (int i = 0,j= 0; vertex_value_ptr[i] != '\n'; i++)
	{
		if (vertex_value_ptr[i] == ',')
		{
			j++;
			readbuff.Vertex[j] = 0;
		}else
			readbuff.Vertex[j] = charToInt(vertex_value_ptr[i], readbuff.Vertex[j]);
	}

	if (arcs_number_ptr != NULL)
	{
		arcs_number_ptr = arcs_number_ptr + strlen("arcs_number=");
	}
	for (int i = 0; arcs_number_ptr[i] != '\n'; i++)
	{
		readbuff.ArcNumb = charToInt(arcs_number_ptr[i], readbuff.ArcNumb);
	}

	if (arcs_value_ptr != NULL)
	{
		arcs_value_ptr = arcs_value_ptr + strlen("arcs_value=");
	}
	readbuff.arc = (Arc *)malloc(readbuff.ArcNumb*sizeof(Arc));
	readbuff.arc[0].iFirst = 0;
	readbuff.arc[0].iSecond = 0;
	readbuff.arc[0].iWeight = 0;
	for (int i = 0,j = 0,k = 0; arcs_value_ptr[i] != '\n' && arcs_value_ptr[i] != EOF; i++)
	{
		if (arcs_value_ptr[i] == ',')
		{
			j++;
		}else if (arcs_value_ptr[i] == ';')
		{
			j = 0;
			k++;
			//readbuff.arc = (Arc *)realloc(readbuff.arc, sizeof(Arc) + sizeof(readbuff.arc));
			readbuff.arc[k].iFirst = 0;
			readbuff.arc[k].iSecond = 0;
			readbuff.arc[k].iWeight = 0;
		}else
		{
			if (j == 0)
				readbuff.arc[k].iFirst = charToInt(arcs_value_ptr[i], readbuff.arc[k].iFirst);
			if (j == 1)
				readbuff.arc[k].iSecond = charToInt(arcs_value_ptr[i], readbuff.arc[k].iSecond);
			if (j == 2)
				readbuff.arc[k].iWeight = charToInt(arcs_value_ptr[i], readbuff.arc[k].iWeight);
		}
	}
}

void CreatGraph_ByConsol(Graph &graph)
{
	ReadBuff readbuff;
	printf("开始创建无向图:\r\n");
	AddVertex(graph, CONSOL_WAY, readbuff);
	AddArcs(graph, CONSOL_WAY, readbuff);
}

void CreatGraph_ByFile(Graph &graph)
{
	ReadBuff readbuff;
	InitReadBuff(readbuff);
	AddVertex(graph, FILE_WAY, readbuff);
	AddArcs(graph, FILE_WAY, readbuff);
}
