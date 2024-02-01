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

// ����ṹ��
typedef struct Vertex
{
	int id;				  // �����ţ�Ψһ��
	int w;				  // ����Ȩֵ
	int degree;			  // ����Ķ�,����ͼʱ�������
	int edges[MAXVERTEX]; // �ߵı��
} Vertex;

// �߽ṹ��
typedef struct Edge
{
	int id; // �ߵı�ţ�Ψһ��
	int h;	// ��ͷ������
	int t;	// ��β������
	int w;	// Ȩֵ
} Edge;

// ͼ�ṹ��
typedef struct Graph
{
	Vertex v[MAXVERTEX]; // ��������
	Edge e[MAXEDGE];	 // ������
	int nv;				 // ������
	int ne;				 // ����
	bool dirctional;	 // t:����ͼ��f:����ͼ
	bool weighted;		 // t:��Ȩͼ��f:��Ȩͼ
} Graph;

#include "showgt.h"

// ����һ�����ͼ������n�����㣬ÿ������������������ߵĸ���Ϊp
void randgengraph(int n, float p, bool directional, bool weighted, const char *filename, int seed)
{
	srand(seed);
	char *content = (char *)malloc(5000000);
	if (!content)
	{
		printf("����洢�ռ�ʧ�ܣ�\n");
		exit(0);
	}
	FILE *fp = fopen(filename, "wb");
	if (!fp)
	{
		printf("����ͼ�ļ�%sʱʧ��!\n", filename);
		exit(0);
	}
	long offset = 0; // content��ǰ��д��λ��
	int ne = 0;		 // ���ɱ���
	for (int i = 0; i < n; i++)
		offset += sprintf(content + offset, "%3d %5d\n", i, rand() % 100); // д�붥��ı�źͶ������Ȩֵ
	int pn = (int)(10000 * p);
	if (directional)
	{ // ����ͼ
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (i != j && rand() % 10000 < pn)
				{
					offset += sprintf(content + offset, "%3d %3d %4d\n", i, j, weighted ? rand() % 100 : 1);
					ne++;
				}
	}
	else
	{ // ����ͼ
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
	fwrite(&ch, sz, 1, fp);			// д��ͼ�Ķ������ͱ���
	fwrite(content, offset, 1, fp); // д��ͼ�Ķ���ͱߵ���Ϣ
	fclose(fp);
	free(content);
}

// ���ļ��ж���ͼ�����ڴ�������ͼ�ı�ʾ
void initGraphFromFile(Graph *g, const char *gfile)
{
	FILE *fp = fopen(gfile, "r");
	if (!fp)
	{
		printf("��ȡͼ�����ļ�����\n");
		exit(0);
	}
	char bv[10];
	// ��ȡͼ�Ļ�����Ϣ
	fscanf(fp, "%u%u%s", &(g->nv), &(g->ne), bv);
	// printf("%d %d %s", g->ne, g->nv, bv);
	g->weighted = strcmp(bv, "true") == 0 ? true : false;
	fscanf(fp, "%s", bv);
	g->dirctional = strcmp(bv, "true") == 0 ? true : false;
	// ��ȡ������Ϣ
	for (int i = 0; i < g->nv; i++)
	{
		fscanf(fp, "%d%d", &(g->v[i].id), &(g->v[i].w));
		g->v[i].degree = 0;
		// printf("����%d-Ȩ%d\n", g->v[i].id, g->v[i].w);
	}
	// ��ȡ����Ϣ
	for (unsigned long i = 0; i < g->ne; i++)
	{
		fscanf(fp, "%u%u%d", &(g->e[i].h), &(g->e[i].t), &(g->e[i].w));
		// printf("��:%u-%u=>%d\n", g->e[i].h, g->e[i].t, g->e[i].w);
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

// ����һ����ͼ
Graph *initGraph(bool directional, bool weighted)
{
	Graph *g = (Graph *)malloc(sizeof(Graph));
	g->nv = g->ne = 0;
	g->dirctional = directional;
	g->weighted = weighted;
	return g;
}

// ��ӡ�ڽӱ����Ϣ
void printgraph(Graph *g)
{
	printf("ͼ�Ļ�����Ϣ:������(%u)-����(%lu)-%s-%s\n", g->nv, g->ne, g->weighted ? "��Ȩͼ" : "��Ȩͼ", g->dirctional ? "����ͼ" : "����ͼ");
	for (int i = 0; i < g->nv; i++)
	{
		printf("ID(%u)-��(%d)-Ȩ(%d)-�߱� t(eid|w):%u", g->v[i].id, g->v[i].degree, g->v[i].w, g->v[i].id);
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

// ���Ҹ�����ŵĶ��㣬�����䶥�������±�
int getVexIdx(Graph *g, int id)
{
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return i;
	printf("input wrong vertex id in getVexIdx()!\n");
	exit(0);
}

// ���Ҹ�����ŵĶ��㣬������Ȩֵ
int getVexW(Graph *g, int id)
{
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return g->v[i].w;
	printf("input wrong vertex id in getVexW()!\n");
	exit(0);
}

// ���Ҹ�����ŵĶ��㣬�������
int getVexDegree(Graph *g, int id)
{
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			return g->v[i].degree;
	printf("input wrong vertex id in getVexDegree()!\n");
	exit(0);
}

// ���Ҹ�����ŵĶ���,���������б�
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

// ���Ҹ�����ŵıߣ�������������±�
int getEdgeIdx(Graph *g, int id)
{
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
			return i;
	printf("input wrong edge id in getEdgeIdx()!\n");
	exit(0);
}

// ���Ҹ�����ŵıߣ�������Ȩֵ
int getEdgeW(Graph *g, int id)
{
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
			return g->e[i].w;
	printf("input wrong edge id in getEdgeW()!\n");
	exit(0);
}

// ���Ҹ�����ŵıߣ���������������
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

// ͨ��Ȩֵ���Ҷ�����
int locateVex(Graph *g, int w)
{
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].w == w)
			return g->v[i].id;
	return -1;
}

// ͨ��Ȩֵ���ұ߱��
int locateEdge(Graph *g, int w)
{
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].w == w)
			return g->e[i].id;
	return -1;
}

// ���ö���Ȩֵ
void setVexW(Graph *g, int id, int w)
{
	for (int i = 0; i < g->nv; i++)
		if (g->v[i].id == id)
			g->v[i].w = w;
	printf("input wrong vertex id in setVexW()!\n");
	exit(0);
}

// ���ñ�Ȩֵ
void setEdgeW(Graph *g, int id, int w)
{
	for (int i = 0; i < g->ne; i++)
		if (g->e[i].id == id)
			g->e[i].w = w;
	printf("input wrong edge id in setEdgeW()!\n");
	exit(0);
}

// ɾ����
void deleteEdge(Graph *g, int id)
{
	int index = getEdgeIdx(g, id); // ������
	// ��ȥ����������Ķ�
	int h_index = getVexIdx(g, g->e[index].h); // ��ͷ�ڵ�����
	int t_index = getVexIdx(g, g->e[index].t); // ��β�ڵ�����
	if (g->dirctional == true)				   // ����ͼ
	{
		for (int i = 0; i < g->v[h_index].degree; i++)
		{
			if (g->v[h_index].edges[i] == id) // ɾ�������ڵı���Ϣ������β�������
			{
				g->v[h_index].edges[i] = g->v[h_index].edges[g->v[h_index].degree - 1];
			}
			g->v[h_index].degree--;
		}
	}
	else // ����ͼ
	{
		for (int i = 0; i < g->v[h_index].degree; i++)
		{
			if (g->v[h_index].edges[i] == id) // ɾ�������ڵı���Ϣ������β�������
			{
				g->v[h_index].edges[i] = g->v[h_index].edges[g->v[h_index].degree - 1];
			}
			g->v[h_index].degree--;
		}
		for (int i = 0; i < g->v[t_index].degree; i++)
		{
			if (g->v[t_index].edges[i] == id) // ɾ�������ڵı���Ϣ������β�������
			{
				g->v[t_index].edges[i] = g->v[t_index].edges[g->v[t_index].degree - 1];
			}
			g->v[t_index].degree--;
		}
	}
	// �����һ���������Ŀ�ȱλ��
	g->e[index].id = g->e[g->ne - 1].id;
	g->e[index].h = g->e[g->ne - 1].h;
	g->e[index].t = g->e[g->ne - 1].t;
	g->e[index].w = g->e[g->ne - 1].w;
	g->ne--;
}

// ɾ�����㣬ͬʱ��������ı�ȫ��ɾ�����ǵõ��� deleteEdge() Ӵ~
void deleteVex(Graph *g, int id)
{
	int index = getVexIdx(g, id);
	// �������������Ǵ���ģ���Ϊɾ��������ڵı�ʱ��������degree���ٱ�����һֱ�ڱ�
	//  for (int i = 0; i < g->v[index].degree;i++)
	//  {
	//  	deleteEdge(g, g->v[index].edges[i]);
	//  }
	// Ӧ��ÿɾ��һ�������ж�һ���ǲ���û�ˣ�ÿ��ֻɾ��һ��
	while (g->v[index].degree != 0)
	{
		printf("degree1=%d\n", g->v[index].degree);
		deleteEdge(g, g->v[index].edges[0]);
		printf("debug:ɾ��һ����\n");
		printf("degree2=%d\n", g->v[index].degree);
	}
	if (g->dirctional == true) // ����ͼ��ʱ����Ҫɾ��ָ��Ķ���ı�
	{
		int i = 0;
		while (i < g->ne && g->ne != 0)
		{
			if (g->e[i].t == id) // �ҵ�����Ҫɾ���ı�
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
	// ���һ��������ǰ�ƶ���������
	g->v[index].id = g->v[g->nv - 1].id;
	g->v[index].degree = g->v[g->nv - 1].degree;
	g->v[index].w = g->v[g->nv - 1].w;
	// g->v[index].edges = g->v[g->nv-1].edges;//���鲻��ֱ�Ӹ�ֵ
	for (int i = 0; i < g->v[g->nv - 1].degree; i++)
	{
		g->v[index].edges[i] = g->v[g->nv - 1].edges[i];
	}
	g->nv--;
}

// ���Ӷ��㣬�����´����Ķ����id
int addVex(Graph *g, int w)
{
	// ��һ��û�ù���id
	int new_id;
	for (int i = 0; i < g->nv + 1; i++) // ��0~nv��һ�����ҵ�һ��û�õ���
	{
		int j;
		for (j = 0; j < g->nv; j++)
		{
			if (g->v[j].id == i)
				break;
		}
		if (j < g->nv) // ˵����ǰ�˳��ڲ�ѭ����ײid��
			continue;  // ������һ��i
		else
		{
			new_id = i;
			break;
		}
	}
	g->v[g->nv].id = new_id;
	g->v[g->nv].degree = 0;
	g->v[g->nv].w = w;
	// g->v[g->nv].edges ���ùܣ���ΪdegreeΪ0
	g->nv++;
	return new_id;
}

// ���ӱ�,�����´����ıߵ�id
int addEdge(Graph *g, int w, int h, int t)
{
	// ��һ��û�ù���id
	int new_id;
	for (int i = 0; i < g->ne + 1; i++) // ��0~ne��һ�����ҵ�һ��û�õ���
	{
		int j;
		for (j = 0; j < g->ne; j++)
		{
			if (g->e[j].id == i)
				break;
		}
		if (j < g->ne) // ˵����ǰ�˳��ڲ�ѭ����ײid��
			continue;  // ������һ��i
		else
		{
			new_id = i;
			break;
		}
	}
	int h_index = getVexIdx(g, h);
	int t_index = getVexIdx(g, t);
	for (int i = 0; i < g->v[h_index].degree; i++) // ���h�����Ƿ��Ѿ������ӵ�t�ıߣ�����ͼ������ͼ��ֻ���ж�hһ��
	{

		if (g->e[g->v[h_index].edges[i]].t == t)
		{
			printf("edge already exist!\n");
			exit(0);
		}
	}
	g->v[h_index].edges[g->v[h_index].degree] = new_id;
	g->v[h_index].degree++;
	if (g->dirctional == false) // ���������ͼ�����β����ҲҪ����
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
		if ((g->e[i].w) % 2 == 00) // �ҵ���ȨΪż���ı�
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

	// ������ȱ���
	//DFSTraverse(g, visitFunction_print);
	// ������ȱ���
	//BFSTraverse(g,visitFunction_print);
	// �����·��
	Dijkstra(g, 2);
	// ����ͨ����������ͼ��
	//printf("��ͨ����Ϊ:%d\n", Connected_number(g));

	//  ������������
	/*
	int newVex = addVex(g, 30);
	printf("����������Ϊ%d\n", newVex);
	saveGraph(g, "net��������10.html");

	int newEdge1 = addEdge(g, 45, 10, 1);
	int newEdge2 = addEdge(g, 44, 2, 10);
	printf("�����߱��Ϊ%d\n", newEdge1);
	printf("�����߱��Ϊ%d\n", newEdge2);
	saveGraph(g, "net������10����1,2����10.html");

	deleteVex(g, 6);
	saveGraph(g, "netɾ������6.html");

	deleteEven(g);
	saveGraph(g, "netż��Ȩֵ��.html");
	*/
}
#endif
void DFSTraverse(Graph *g, void (*visitFunction)(Graph *g, int v))
{
	if (g->nv == 0)
		return;
	bool *visitedList = (bool *)malloc(sizeof("bool") * g->nv); // visitedList�����Ƕ����index����id
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
	bool *visitedList = (bool *)malloc(sizeof("bool") * g->nv); // visitedList�����Ƕ����index����id
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
// ���ָ��id�Ķ���ֱ��������ж������С����
void Dijkstra(Graph *g, int id)
{
	int index = getVexIdx(g, id);
	int size = g->nv;
	int finish_number = 0;									// �Ѿ�������·�����յ�������������ж�ʲôʱ������㷨
	bool *S = (bool *)malloc(sizeof(bool) * size);			// �洢�Ѿ�������·�����յ�ļ���,�±�Ϊ����,true�����Ѿ����
	float *D = (float *)malloc(sizeof(float) * size);		// �洢Դ�㵽�յ���ʱ��̵�·������,�±�Ϊ����
	int *predecessor = (int *)malloc(sizeof(int *) * size); // �洢�ڵ��ǰ���ڵ㣬�±������Ԫ�ض�������
	for (int i = 0; i < size; i++)
	{
		S[i] = false;
		D[i] = std::numeric_limits<float>::infinity();
	}
	S[index] = true; // ����Դ��
	D[index] = 0;
	predecessor[index] = -1; // ����û��ǰ����˵��ΪԴ��
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
					index = i; // �ҵ�����S�����У�Ŀǰ·����̵Ķ��������
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
				continue; // ����ھ��Ѿ���S�У��Ͳ���Ҫ��ȥ�ж��ˣ������п���
			if (D[neighbor_index] > D[index] + edge_wight)
			{
				D[neighbor_index] = D[index] + edge_wight;
				predecessor[neighbor_index] = index;
			}
		}
	}
	// ���ҽ��������Դ�㵽�������·���;���
	for (int i = 0; i < size; i++)
	{
		int pre = i; // ǰ��
		printf("Դ�㵽idΪ%d�Ķ������:%.f\n", g->v[i].id, D[i]);
		printf("·��Ϊ:");
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
		// ����ͼ����������ͨ����
		printf("����������ͼ\n");
		exit(-1);
	}
	if (g->nv == 0)
		return 0;
	bool *visitedList = (bool *)malloc(sizeof("bool") * g->nv); // visitedList�����Ƕ����index����id
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
