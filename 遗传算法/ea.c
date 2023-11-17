// �Ŵ��㷨������Ż������ͨ���㷨
// ������Ľ�x��ʾΪ0-1����Ȼ���������ŵĶ����ƴ���ʹ��Ŀ�꺯��ֵf(x)�ﵽ��С

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** �㷨�������� **/
// ����0-1���ĳ��ȣ������ڱ�ʾ��ľ���
#define SLEN 200

// �������������
#define MAXGEN 50

// �������
#define mProb 1.0 / SLEN

// ��Ⱥ������Ⱥ���С���Ӵ�������ż����ͨ������Ⱦɫ�����ɺ��ʱ��һ���������������
#define PSIZE 10
#define CSIZE 20
#define SIZE (PSIZE + CSIZE)

// һ����Ķ���
typedef struct
{
	int x[SLEN]; // x:����Ա�����0-1��
	double xo;//������x
	double y;	 // y=f(x),Ҫ�Ż������Ŀ�꺯��ֵ
} Solution;

// ����һ���⼯/�����飺��֮ΪȺ��population
Solution pop[SIZE];				  // �⼯���������Ӵ����洢������
Solution *parent = pop;			  // ��ǰ����Ҳ���Ǹ���
Solution *children = pop + PSIZE; // �Ӵ��⼯

// ��������
void printPop(Solution *p, const char *str);

// ��0-1��x����Ϊʵ��*xo ,�ٶ�����4bits��SLEN-4bitsΪС�����ֳ���
void decode(int *x, double *xo)
{
	// todo
	// �������ֻ���10����
	*xo = 0;
	*xo += 8 * x[0] + 4 * x[1] + 2 * x[2] + 1 * x[3];
	// С�����ֻ���10����
	double t = 1.0;
	for (int i = 0; i < SLEN - 4; i++)
	{
		t = t / 2.0;
		*xo += t * x[i + 4];
	}
	return;
}

// ����y=f(x) ,  0-1��x�ĳ��� SLEN
// ���ӣ���y=x*x-3x+2����Сֵ ��������������4bits��С������SLEN-4bits
double func1(int *x)
{
	double xo;
	decode(x, &xo);				 // ��0-1��x����������Ľ�xo
	return xo * xo - 4 * xo + 2; // ����Ŀ�꺯��ֵ
}

double func2(int * x)
{
	double xo;
	decode(x, &xo);				 // ��0-1��x����������Ľ�xo
	return - xo * xo * xo + 3 * xo * xo + xo + 3; // ����Ŀ�꺯��ֵ
	//return xo;
}


// ���㸸���Ӵ����н��Ŀ�꺯��ֵy �������˺���ָ�룬֧�ָ��������Ż�
void evaluate(Solution *Pop, double func(int *))
{
	double xo;
	for (int i = 0; i < SIZE; i++)
	{
		(Pop + i)->y = func((Pop + i)->x);
		decode((Pop+i)->x,&((Pop+i)->xo));
	}
	return;
}

// �㷨��ʼ�������������⼯����Ŀռ䣬�������currentPop�еĽ⣬��������yֵ
void initialize()
{
	for (int i = 0; i < SIZE; ++i)
	{								   // ��ʼ����һ������
		for (int j = 0; j < SLEN; ++j) // ��ÿ�����0-1�����������
			parent[i].x[j] = rand() % 2;
		
	}
}

// �Ӹ�����ѡ�������⣬ͨ���ӽ����������Ӵ�����
// ����������ͨ��PKѡ�����������ѡ��
void crossover()
{ // ��������
	int k = 0;
	int exchangePosition;
	int parent1, parent2;
	while (k < CSIZE)
	{
		// ���ȷ����������Ⱦɫ�彻��λ��
		exchangePosition = rand() % SLEN;
		// ���ѡ��������������
		parent1 = rand() % PSIZE;
		parent2 = rand() % PSIZE;
		while (parent1 == parent2)
		{
			parent2 = rand() % PSIZE; // ������������ͬ
		}
		// ���������Ӵ�����������λ��ǰ��������Ӵ�
		for (int i = 0; i < exchangePosition; i++)
		{
			children[k].x[i] = parent[parent1].x[i];
			children[k + 1].x[i] = parent[parent2].x[i];
		}
		for (int i = exchangePosition; i < SLEN; i++)
		{
			children[k].x[i] = parent[parent2].x[i];
			children[k + 1].x[i] = parent[parent1].x[i];
		}
		k = k + 2;
	}
}

// ���Ӵ��еĸ�����б��죺�������ΪmProb
// ��ν�������x[j]��ȡֵ 0-1������ 0 <--> 1
void mutate()
{ // ��������
	for (int i = 0; i < CSIZE; ++i)
		for (int j = 0; j < SLEN; ++j)
			if ((rand() % 100000) / 100000.0 < mProb)
				children[i].x[j] = 1 - children[i].x[j];
}

// ��currentPop��offspring��ѡ����һ�����壬�ж���ѡ���㷨������ͨ�������Ȱ�����Ⱥ������õı������� ��Ȼ��
// ����1��ѡ����õ�PSIZE��Ϊ��һ�����ض�ѡ��
// ����2����ÿ������һ��ѡ����ʣ�yֵС���ã��ı�ѡ��ĸ��ʾ͸ߣ�Ȼ�����ݴ˸��ʷֲ��������PSIZE��
// ����3������ѡ�����ѡ��k�����໥pk��������õķ�����һ��������ѡ��PSIZE�� ����ɾ����ѡ���˵ģ�
void select(int k)
{				  // ѡ������ �����ý���ѡ��
	double besty; // ������ѡ�������Ӵ���yֵ
	int best;	  // ������ѡ��������Ӵ��±�
	int n;    //�����������ѡ�����
	Solution tmp[PSIZE];
	for (int i = 0; i < PSIZE; ++i)
	{ // һ��һ���Ӵ�ѡ��
		n = rand()%SIZE;//����õ�һ�����
		besty = pop[n].y;
		best = n;
		for(int j = 1;j<k;j++)
		{
			n = rand()%SIZE;
			if(pop[n].y < besty)
			{
				besty = pop[n].y;
				best = n;
			}
		}
		memcpy(&(tmp[i]), &(pop[best]), sizeof(Solution)); // ѡ������Ľ⣬���Ƶ���ʱ�⼯��
	}
	memcpy(pop, tmp, sizeof(Solution) * PSIZE);
}

// ���Ⱥ�����Ϣ
void printPop(Solution *p, const char *str)
{
	printf("%s/�⼯��Ϣ����: \n", str);
	for (int i = 0; i < PSIZE; ++i)
	{
		printf("���� %3d : y=%10.6lf=f(", i, p[i].y);
		printf("%f",p[i].xo);
		//for (int j = 0; j < SLEN; ++j)
		//	printf("%d", p[i].x[j]);
		printf(")\n");
	}
}

int main()
{
	int seed = 991;
	srand(seed); // ������������ӣ�ʹ���㷨�����������
	initialize();
	printf("�� %d �� ", 0);
	evaluate(pop, func1);//ѡ��ǰ�ȼ������н��y
	printPop(pop, "��ǰȺ��");

	for (int gen = 1; gen < MAXGEN; gen++)
	{
		crossover();
		mutate();
		evaluate(pop, func1);//ѡ��ǰ�ȼ������н��y
		select(3);
		//debug
		printf("�� %d �� ",gen);
		printPop(pop,"��ǰȺ��");
	}
	printf("�� %d �� ", MAXGEN);
	printPop(parent, "����Ⱥ��");
	return 1;
}
