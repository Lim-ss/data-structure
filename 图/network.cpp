#ifndef _NETWORK_CPP_
#define _NETWORK_CPP_

#include <iostream>
#include <queue>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXVERTEX 100
#define MAXEDGE 20000

// 顶点结构体
typedef struct Vertex
{
	int id;				  // 顶点编号（唯一）
	int w;				  // 顶点权值
	int degree;			  // 顶点的度,有向图时代表出度
	int edges[MAXVERTEX]; // 边的编号
} Vertex;

// 边结构体
typedef struct Edge
{
	int id; // 边的编号（唯一）
	int h;	// 边头顶点编号
	int t;	// 边尾顶点编号
	int w;	// 权值
} Edge;

// 图结构体
typedef struct Graph
{
	Vertex v[MAXVERTEX]; // 顶点数组
	Edge e[MAXEDGE];	 // 边数组
	int nv;				 // 顶点数
	int ne;				 // 边数
	bool dirctional;	 // t:有向图，f:无向图
	bool weighted;		 // t:带权图，f:等权图
} Graph;

#include "showgt.h"

// 生成一个随机图，包括n个顶点，每个顶点和其它顶点连边的概率为p
void randgengraph(int n, float p, bool directional, bool weighted, const char *filename, int seed)
{
	srand(seed);
	char *content = (char *)malloc(5000000);
	if (!content)
	{
		printf("分配存储空间失败！\n");
		exit(0);
	}
	FILE *fp = fopen(filename, "wb");
	if (!fp)
	{
		printf("生成图文件%s时失败!\n", filename);
		exit(0);
	}
	long offset = 0; // content当前的写入位置
	int ne = 0;		 // 生成边数
	for (int i = 0; i < n; i++)
		offset += sprintf(content + offset, "%3d %5d\n", i, rand() % 100); // 写入顶点的编号和顶点随机权值
	int pn = (int)(10000 * p);
	if (directional)
	{ // 有向图
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (i != j && rand() % 10000 < pn)
				{
					offset += sprintf(content + offset, "%3d %3d %4d\n", i, j, weighted ? rand() % 100 : 1);
					ne++;
				}
	}
	else
	{ // 无向图
		for (int i = 0; i < n; i++)
			for (int j = i; j < n; j++)
				if (i != j && rand() % 10000 < pn)
				{
					offset += sprintf(content + offset, "%3d %3d %4d\n", i, j, weighted ? rand() % 100 : 1);
					ne++;
				}
	}
	char ch[40];
	int sz = sprintf(ch, "%d %7d %5s %5s\n", n, ne, weighted ? "true" : "flase", directional ? "true" : "flase");
	fwrite(&ch, sz, 1, fp);			// 写入图的顶点数和边数
	fwrite(content, offset, 1, fp); // 写入图的顶点和边的信息
	fclose(fp);
	free(content);
}

// 从文件中读入图，在内存中生成图的表示
void initGraphFromFile(Graph *g, const char *gfile)
{
	FILE *fp = fopen(gfile, "r");
	if (!fp)
	{
		printf("读取图数据文件出错！\n");
		exit(0);
	}
	char bv[10];
	// 读取图的基本信息
	fscanf(fp, "%u%u%s", &(g->nv), &(g->ne), bv);
	// printf("%d %d %s", g->ne, g->nv, bv);
	g->weighted = strcmp(bv, "true") == 0 ? true : false;
	fscanf(fp, "%s", bv);
	g->dirctional = strcmp(bv, "true") == 0 ? true : false;
	// 读取顶点信息
	for (int i = 0; i < g->nv; i++)
	{
		fscanf(fp, "%d%d", &(g->v[i].id), &(g->v[i].w));
		g->v[i].degree = 0;
		// printf("顶点%d-权%d\n", g->v[i].id, g->v[i].w);
	}
	// 读取边信息
	for (unsigned long i = 0; i < g->ne; i++)
	{
		fscanf(fp, "%u%u%d", &(g->e[i].h), &(g->e[i].t), &(g->e[i].w));
		// printf("边:%u-%u=>%d\n", g->e[i].h, g->e[i].t, g->e[i].w);
		g->e[i].id = i;
		unsigned h, t;
		h = g->e[i].h;
		t = g->e[i].t;
		g->v[h].edges[g->v[h].degree++] = i;
		if (g->dirctional == false)
			g->v[t].edges[g->v[t].degree++] = i;
	}
	fclose(fp);
}

// 生成一个空图
Graph *initGraph(bool directional, bool weighted)
{
	Graph *g = (Graph *)malloc(sizeof(Graph));
	g->nv = g->ne = 0;
	g->dirctional = directional;
	g->weighted = weighted;
	return g;
}

// 打印邻接表的信息
void printgraph(Graph *g)
{
	printf("图的基本信息:顶点数(%u)-边数(%lu)-%s-%s\n", g->nv, g->ne, g->weighted ? "加权图" : "等权图", g->dirctional ? "有向图" : "无向图");
	for (int i = 0; i < g->nv; i++)
	{
		printf("ID(%u)-度(%d)-权(%d)-边表 t(eid|w):%u", g->v[i].id, g->v[i].degree, g->v[i].w, g->v[i].id);
		for (int j = 0; j < g->v[i].degree; j++)
		{
			unsigned long e = g->v[i].edges[j];
			if (g->v[i].id == g->e[e].h)
				printf("->%u(%d)", g->e[e].t, g->e[e].w);
			else
				printf("->%u(%d)", g->e[e].h, g->e[e].w);
		}
		printf("\n");
	}
}

// 查找给定编号的顶点，返回其顶点数组下标
int getVexIdx(Graph *g, int id)
{
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return i;
	printf("input wrong vertex id in getVexIdx()!\n");
	exit(0);
}

// 查找给定编号的顶点，返回其权值
int getVexW(Graph *g, int id)
{
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return g->v[i].w;
	printf("input wrong vertex id in getVexW()!\n");
	exit(0);
}

// 查找给定编号的顶点，返回其度
int getVexDegree(Graph *g, int id)
{
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return g->v[i].degree;
	printf("input wrong vertex id in getVexDegree()!\n");
	exit(0);
}

// 查找给定编号的顶点,返回其所有边
int *getEdgesByNode(Graph *g, int id, int *ne)
{
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
		{
			*ne = g->v[i].degree;
			return g->v[i].edges;
		}
	printf("input wrong vertex id in getEdgesByNode()!\n");
	exit(0);
}

// 查找给定编号的边，返回其边数组下标
int getEdgeIdx(Graph *g, int id)
{
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
			return i;
	printf("input wrong edge id in getEdgeIdx()!\n");
	exit(0);
}

// 查找给定编号的边，返回其权值
int getEdgeW(Graph *g, int id)
{
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
			return g->e[i].w;
	printf("input wrong edge id in getEdgeW()!\n");
	exit(0);
}

// 查找给定编号的边，返回其两个顶点
void getVexByEdge(Graph *g, int id, int *h, int *t)
{
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
		{
			*h = g->e[i].h;
			*t = g->e[i].t;
		}
	printf("input wrong edge id in getVexByEdge()!\n");
	exit(0);
}

// 通过权值查找顶点编号
int locateVex(Graph *g, int w)
{
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].w == w)
			return g->v[i].id;
	return -1;
}

// 通过权值查找边编号
int locateEdge(Graph *g, int w)
{
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].w == w)
			return g->e[i].id;
	return -1;
}

// 设置顶点权值
void setVexW(Graph *g, int id, int w)
{
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			g->v[i].w = w;
	printf("input wrong vertex id in setVexW()!\n");
	exit(0);
}

// 设置边权值
void setEdgeW(Graph *g, int id, int w)
{
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
			g->e[i].w = w;
	printf("input wrong edge id in setEdgeW()!\n");
	exit(0);
}

// 删除边
void deleteEdge(Graph *g, int id)
{
	int index = getEdgeIdx(g, id); // 边索引
	// 减去边相连顶点的度
	int h_index = getVexIdx(g, g->e[index].h); // 边头节点索引
	int t_index = getVexIdx(g, g->e[index].t); // 边尾节点索引
	if (g->dirctional == true)				   // 有向图
	{
		for (int i = 0; i < g->v[h_index].degree; i++)
		{
			if (g->v[h_index].edges[i] == id) // 删除点相邻的边信息，将结尾的填过来
			{
				g->v[h_index].edges[i] = g->v[h_index].edges[g->v[h_index].degree - 1];
			}
			g->v[h_index].degree--;
		}
	}
	else // 无向图
	{
		for (int i = 0; i < g->v[h_index].degree; i++)
		{
			if (g->v[h_index].edges[i] == id) // 删除点相邻的边信息，将结尾的填过来
			{
				g->v[h_index].edges[i] = g->v[h_index].edges[g->v[h_index].degree - 1];
			}
			g->v[h_index].degree--;
		}
		for (int i = 0; i < g->v[t_index].degree; i++)
		{
			if (g->v[t_index].edges[i] == id) // 删除点相邻的边信息，将结尾的填过来
			{
				g->v[t_index].edges[i] = g->v[t_index].edges[g->v[t_index].degree - 1];
			}
			g->v[t_index].degree--;
		}
	}
	// 将最后一个边填到数组的空缺位置
	g->e[index].id = g->e[g->ne - 1].id;
	g->e[index].h = g->e[g->ne - 1].h;
	g->e[index].t = g->e[g->ne - 1].t;
	g->e[index].w = g->e[g->ne - 1].w;
	g->ne--;
}

// 删除顶点，同时与其关联的边全部删除，记得调用 deleteEdge() 哟~
void deleteVex(Graph *g, int id)
{
	int index = getVexIdx(g, id);
	// 下面这种做法是错误的，因为删除与点相邻的边时，这个点的degree和临边数组一直在变
	//  for (int i = 0; i < g->v[index].degree;i++)
	//  {
	//  	deleteEdge(g, g->v[index].edges[i]);
	//  }
	// 应该每删除一条边再判断一下是不是没了，每次只删第一条
	while (g->v[index].degree != 0)
	{
		printf("degree1=%d\n", g->v[index].degree);
		deleteEdge(g, g->v[index].edges[0]);
		printf("debug:删除一条边\n");
		printf("degree2=%d\n", g->v[index].degree);
	}
	if (g->dirctional == true) // 有向图的时候还需要删除指向改顶点的边
	{
		int i = 0;
		while (i < g->ne && g->ne != 0)
		{
			if (g->e[i].t == id) // 找到了需要删除的边
			{
				deleteEdge(g, g->e[i].id);
				i = 0;
			}
			else
			{
				i++;
			}
		}
	}
	// 最后一个顶点往前移动补充数组
	g->v[index].id = g->v[g->nv - 1].id;
	g->v[index].degree = g->v[g->nv - 1].degree;
	g->v[index].w = g->v[g->nv - 1].w;
	// g->v[index].edges = g->v[g->nv-1].edges;//数组不能直接赋值
	for (int i = 0; i < g->v[g->nv - 1].degree; i++)
	{
		g->v[index].edges[i] = g->v[g->nv - 1].edges[i];
	}
	g->nv--;
}

// 增加顶点，返回新创建的顶点的id
int addVex(Graph *g, int w)
{
	// 找一个没用过的id
	int new_id;
	for (int i = 0; i < g->nv + 1; i++) // 从0~nv中一定能找到一个没用到的
	{
		int j;
		for (j = 0; j < g->nv; j++)
		{
			if (g->v[j].id == i)
				break;
		}
		if (j < g->nv) // 说明提前退出内层循环，撞id了
			continue;  // 试试下一个i
		else
		{
			new_id = i;
			break;
		}
	}
	g->v[g->nv].id = new_id;
	g->v[g->nv].degree = 0;
	g->v[g->nv].w = w;
	// g->v[g->nv].edges 不用管，因为degree为0
	g->nv++;
	return new_id;
}

// 增加边,返回新创建的边的id
int addEdge(Graph *g, int w, int h, int t)
{
	// 找一个没用过的id
	int new_id;
	for (int i = 0; i < g->ne + 1; i++) // 从0~ne中一定能找到一个没用到的
	{
		int j;
		for (j = 0; j < g->ne; j++)
		{
			if (g->e[j].id == i)
				break;
		}
		if (j < g->ne) // 说明提前退出内层循环，撞id了
			continue;  // 试试下一个i
		else
		{
			new_id = i;
			break;
		}
	}
	int h_index = getVexIdx(g, h);
	int t_index = getVexIdx(g, t);
	for (int i = 0; i < g->v[h_index].degree; i++) // 检查h顶点是否已经有连接到t的边，无向图和有向图都只用判断h一侧
	{

		if (g->e[g->v[h_index].edges[i]].t == t)
		{
			printf("edge already exist!\n");
			exit(0);
		}
	}
	g->v[h_index].edges[g->v[h_index].degree] = new_id;
	g->v[h_index].degree++;
	if (g->dirctional == false) // 如果是无向图，则边尾顶点也要更新
	{
		g->v[t_index].edges[g->v[t_index].degree] = new_id;
		g->v[t_index].degree++;
	}
	g->e[g->ne].id = new_id;
	g->e[g->ne].h = h;
	g->e[g->ne].t = t;
	g->e[g->ne].w = w;
	g->ne++;
	return new_id;
}

void deleteEven(Graph *g)
{
	int i = 0;
	while (i < g->ne && g->ne != 0)
	{
		if ((g->e[i].w) % 2 == 00) // 找到了权为偶数的边
		{
			deleteEdge(g, g->e[i].id);
			i = 0;
		}
		else
		{
			i++;
		}
	}
}
void DFSTraverse(Graph *g, void (*visitFunction)(Graph *g, int v));
void BFSTraverse(Graph *g, void (*visitFunction)(Graph *g, int v));
void Dijkstra(Graph *g, int id);
void visitFunction_print(Graph *g, int v);
int Connected_number(Graph *g);
int main()
{
	Graph *g = (Graph *)malloc(sizeof(Graph));
	if (!g)
	{
		printf("error\n");
		exit(0);
	}
	randgengraph(10, 0.2, true, true, "graph.txt", 4);
	initGraphFromFile(g, "graph.txt");
	printgraph(g);
	saveGraph(g, "net.html");

	// 深度优先遍历
	//DFSTraverse(g, visitFunction_print);
	// 广度优先遍历
	//BFSTraverse(g,visitFunction_print);
	// 求最短路径
	Dijkstra(g, 2);
	// 求联通分量（无向图）
	//printf("联通分量为:%d\n", Connected_number(g));

	//  基本操作测试
	/*
	int newVex = addVex(g, 30);
	printf("新增顶点编号为%d\n", newVex);
	saveGraph(g, "net新增顶点10.html");

	int newEdge1 = addEdge(g, 45, 10, 1);
	int newEdge2 = addEdge(g, 44, 2, 10);
	printf("新增边编号为%d\n", newEdge1);
	printf("新增边编号为%d\n", newEdge2);
	saveGraph(g, "net新增边10——1,2——10.html");

	deleteVex(g, 6);
	saveGraph(g, "net删除顶点6.html");

	deleteEven(g);
	saveGraph(g, "net偶数权值边.html");
	*/
}
#endif
void DFSTraverse(Graph *g, void (*visitFunction)(Graph *g, int v))
{
	if (g->nv == 0)
		return;
	bool *visitedList = (bool *)malloc(sizeof("bool") * g->nv); // visitedList里存的是顶点的index不是id
	if (visitedList == NULL)
	{
		printf("malloc failure");
		exit(-1);
	}
	std::stack<int> fringe;
	for (int i = 0; i < g->nv; i++)
	{
		visitedList[i] = false;
	}
	for (int v = 0; v < g->nv; v++)
	{
		if (visitedList[v] == false)
		{
			fringe.push(v);
			//std::cout<<"push "<<v<<std::endl;
			while (fringe.size() != 0)
			{
				int u = fringe.top();
				fringe.pop();
				if (visitedList[u] == true)
				{
					continue;
				}
				visitedList[u] = true;
				visitFunction(g, u);
				//std::cout<<"pop "<<u<<std::endl;
				for (int i = 0; i < g->v[u].degree; i++)
				{
					int neighbor_index = getVexIdx(g, g->e[g->v[u].edges[i]].t);
					if (visitedList[neighbor_index] == false)
					{
						fringe.push(neighbor_index);
						//std::cout<<"push "<<neighbor_index<<std::endl;
					}
				}
			}
		}
	}
	free(visitedList);
}
void BFSTraverse(Graph *g, void (*visitFunction)(Graph *g, int v))
{
	if (g->nv == 0)
		return;
	bool *visitedList = (bool *)malloc(sizeof("bool") * g->nv); // visitedList里存的是顶点的index不是id
	if (visitedList == NULL)
	{
		printf("malloc failure");
		exit(-1);
	}
	std::queue<int> fringe;
	for (int i = 0; i < g->nv; i++)
	{
		visitedList[i] = false;
	}
	for (int v = 0; v < g->nv; v++)
	{
		if (visitedList[v] == false)
		{
			visitedList[v] = true;
			visitFunction(g, v);
			fringe.push(v);
			while (fringe.size() != 0)
			{
				int u = fringe.front();
				fringe.pop();
				for (int i = 0; i < g->v[u].degree; i++)
				{
					int neighbor_index = getVexIdx(g, g->e[g->v[u].edges[i]].t);
					if (visitedList[neighbor_index] == false)
					{
						visitedList[neighbor_index] = true;
						visitFunction(g, neighbor_index);
						fringe.push(neighbor_index);
					}
				}
			}
		}
	}
	free(visitedList);
}

void visitFunction_print(Graph *g, int v)
{
	printf("%d\n", g->v[v].id);
}
// 输出指定id的顶点分别到其他所有顶点的最小距离
void Dijkstra(Graph *g, int id)
{
	int index = getVexIdx(g, id);
	int size = g->nv;
	int finish_number = 0;									// 已经求得最短路径的终点的数量，用于判断什么时候结束算法
	bool *S = (bool *)malloc(sizeof(bool) * size);			// 存储已经求得最短路径的终点的集合,下标为索引,true代表已经求得
	float *D = (float *)malloc(sizeof(float) * size);		// 存储源点到终点暂时最短的路径长度,下标为索引
	int *predecessor = (int *)malloc(sizeof(int *) * size); // 存储节点的前驱节点，下标和数组元素都是索引
	for (int i = 0; i < size; i++)
	{
		S[i] = false;
		D[i] = std::numeric_limits<float>::infinity();
	}
	S[index] = true; // 加入源点
	D[index] = 0;
	predecessor[index] = -1; // 代表没有前驱，说明为源点
	finish_number++;
	for (int i = 0; i < g->v[index].degree; i++)
	{
		int neighbor_index = getEdgeIdx(g, g->e[g->v[index].edges[i]].t);
		int edge_wight = g->e[g->v[index].edges[i]].w;
		if (D[neighbor_index] > D[index] + edge_wight)
		{
			D[neighbor_index] = D[index] + edge_wight;
			predecessor[neighbor_index] = index;
		}
	}
	while (finish_number < size)
	{
		float min = std::numeric_limits<float>::infinity();
		for (int i = 0; i < size; i++)
		{
			if (S[i] == false)
			{
				if (min > D[i])
				{
					min = D[i];
					index = i; // 找到不在S集合中，目前路径最短的顶点的索引
				}
			}
		}
		S[index] = true;
		finish_number++;
		for (int i = 0; i < g->v[index].degree; i++)
		{
			int neighbor_index = getEdgeIdx(g, g->e[g->v[index].edges[i]].t);
			int edge_wight = g->e[g->v[index].edges[i]].w;
			if (S[neighbor_index] == true)
				continue; // 如果邻居已经在S中，就不需要再去判断了，这句可有可无
			if (D[neighbor_index] > D[index] + edge_wight)
			{
				D[neighbor_index] = D[index] + edge_wight;
				predecessor[neighbor_index] = index;
			}
		}
	}
	// 查找结束，逐个源点到各顶点的路径和距离
	for (int i = 0; i < size; i++)
	{
		int pre = i; // 前驱
		printf("源点到id为%d的顶点距离:%.f\n", g->v[i].id, D[i]);
		printf("路径为:");
		printf(" %d", g->v[i].id);
		while ((pre = predecessor[pre]) != -1)
		{
			printf(" <- %d", g->v[pre].id);
		}
		printf("\n");
	}
	free(S);
	free(D);
	free(predecessor);
}

int Connected_number(Graph *g)
{
	if (g->dirctional == true)
	{
		// 有向图，不能求联通分量
		printf("请输入无向图\n");
		exit(-1);
	}
	if (g->nv == 0)
		return 0;
	bool *visitedList = (bool *)malloc(sizeof("bool") * g->nv); // visitedList里存的是顶点的index不是id
	if (visitedList == NULL)
	{
		printf("malloc failure");
		exit(-1);
	}
	std::queue<int> fringe;
	for (int i = 0; i < g->nv; i++)
	{
		visitedList[i] = false;
	}
	int connected_number = 0;
	for (int v = 0; v < g->nv; v++)
	{
		if (visitedList[v] == false)
		{
			connected_number++;
			visitedList[v] = true;
			fringe.push(v);
			while (fringe.size() != 0)
			{
				int u = fringe.front();
				fringe.pop();
				for (int i = 0; i < g->v[u].degree; i++)
				{
					int neighbor_index = getVexIdx(g, (g->e[g->v[u].edges[i]].t == u)?(g->e[g->v[u].edges[i]].h):(g->e[g->v[u].edges[i]].t));
					if (visitedList[neighbor_index] == false)
					{
						visitedList[neighbor_index] = true;
						fringe.push(neighbor_index);
					}
				}
			}
		}
	}
	free(visitedList);
	return connected_number;
}
