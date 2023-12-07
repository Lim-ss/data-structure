#ifndef _BITREE_CPP_
#define _BITREE_CPP_
//二叉树相关的实现代码 
#include <stdio.h>
#include <stdlib.h>
#include <stack>



//定义存放数据的类型,假设是可以存放多个数据的结构体类型 
typedef struct{
	int id;
	int value; 
} ElemType; 

//定义二叉树的结点 
typedef struct tnode{
	ElemType data;
	struct tnode *lchild;
	struct tnode *rchild;
} bNode;

//声明
void cPrintNode(bNode *a);
bNode* TreeDeleteByValue(bNode *root,int value);
void TreePathSearch(bNode *root,int id);
void TreePathSearch(bNode *root,int id,std::stack<int>* stack_path_reverse);
int TreeFindCommonAncestor(bNode *root,int id1,int id2);
int TreeCalMaxSubMin(bNode *root);

#include "showGT.h"  //展示树和图的API 

/***-下面的代码是四种不同的构建二叉树的算法，已经输入信息的不同而不同 ***/ 
//构造二叉树（二叉排序树），输入长度为len的整数数组value
//value数组第0个元素为根的value，后续value依次和根比较，若比根小，就和根的左子树比较；否则和右子树比较；
//依次类推，若比较时遇到左子树或右子树为空，则以该value值构建新的树节点，并称为对应的左子树或右子树。 
bNode *buildBTreeByValue(int *value,int len){
	bNode *root = (bNode *)malloc(sizeof(bNode));
	if (!root) exit(0);
	int idx = 0;
	root->data.id = idx;
	root->data.value = value[idx];	
	root->lchild = root->rchild = NULL;
	cPrintNode(root);
	
	for(idx=1;idx<len;++idx){
		//生成新节点 
		bNode *t = (bNode *)malloc(sizeof(bNode));
		if (!t) exit(0);
		t->data.id = idx;
		t->data.value = value[idx];
		t->lchild = t->rchild = NULL;
		cPrintNode(t);		
		
		//查找新节点在二叉树的准确位置 
		bNode *q; //p的双亲结点 
		for(bNode *p=root;p;(value[idx] < p->data.value)? p = p->lchild:p = p->rchild)
			q = p;
		(value[idx]<q->data.value)? q->lchild = t: q->rchild = t;  //将新节点链入二叉树
		printf(", 其父节点地址 %lx",q);
	}	
	return root;
} 

//构造二叉树,输入长度为len的数组edge和value,下标即为结点编号id，
//edge[id]表示编号为id的结点的双亲结点的编号(0~len-1) ，根结点的双亲编号为-1 
//value数组记录了结点的数据域value值
//算法思想：为每个结点构造一个结点，将它们的地址存在一个指针数组中；然后依据edge将这些结点链接成二叉树 
bNode *buildBTreeByEdge(int *value, int *edge, int len){
	//首先需要检查edge数组是否代表一棵二叉树：唯一的-1，0~len-1每个树至多出现2次,edge[i]!=i.这里省略 
	bNode **allnodes= (bNode **)malloc(sizeof(bNode *)*len);//len个指针
	if (!allnodes) exit(0);
	for(int i=0;i<len;++i){
		allnodes[i] = (bNode *)malloc(sizeof(bNode));
		if (!(allnodes[i])) exit(0);
		allnodes[i]->data.id = i;
		allnodes[i]->data.value = value[i];
		allnodes[i]->lchild = allnodes[i]->rchild = NULL;
	} 
	
	bNode *root;
	for(int i=0;i<len;++i){//二叉树不唯一，左右子树可以互换，优先构造左子树 
		if (edge[i]!=-1)
			(allnodes[edge[i]]->lchild == NULL)? allnodes[edge[i]]->lchild = allnodes[i]: allnodes[edge[i]]->rchild = allnodes[i];
		else
			root = allnodes[i];
	}
	return root; 
} 

//递归算法：构造二叉树,输入长度为len=2n+1的数组prelist，二叉树的节点数量为n 
//先序序列prelist[i],若序列中遇到空结点，其值为NULLNODE，prelist中有n+1个NULLNODE 
#define NULLNODE -9999 
bNode *buildBTreeByPrelist(int *prelist,int len){
	bNode *t;
	static int idx = 0; //递归中每次调用自身都需要访问的“特殊”变量用静态变量或全局变量 
	if (prelist[idx] == NULLNODE){
		idx++;
		return NULL;
	}
	if (!(t=(bNode *)malloc(sizeof(bNode *)))) exit(0);
	t->data.value = prelist[idx];
	t->data.id = idx;
	idx++; //准备访问prelist[idx]的下一个数据构建结点,idx无法放入形参列表 
	t->lchild = buildBTreeByPrelist(prelist,len);
	t->rchild = buildBTreeByPrelist(prelist,len);		
	return t;
}//如果prelist中的数据无法全部放入到一棵二叉树，如何检测？（构造结束后 idx<len-1) 
//学习形参列表中无法表示子问题的“特征时”时，采用全局变量或静态变量来处理

//递归算法(先序遍历)：构造二叉树 ，输入先序序列pre和中序序列in，以及两个序列各自的上界pu,iu和下界pl,il
bNode *buildBTreeByPI(int *pre, int pl, int pu, int *in, int il, int iu){
	printf("\n%d-%d,%d-%d",pl,pu,il,iu);
	int il1,iu1,il2,iu2,pl1,pl2,pu1,pu2; //根节点把中序序列分成两个子序列，同样得到先徐序列的两个子序列，这是子序列的下标 
	if (pu-pl!=iu-il) exit(0); //检查输入参数 
	if (pu-pl<0) return NULL;  //若序列为空，返回空结点/空树 
	bNode *t = (bNode *)malloc(sizeof(bNode));
	if (!t) exit(0);
	t->data.value = pre[pl];
	t->data.id = pl;
	for(int i=il;i<=iu;++i){
		if (in[i]==pre[pl]){
			iu1 = i-1;
			il1 = il;
			il2 = i+1;
			iu2 = iu;  //完成中序序列in的切割
			pl1 = pl+1;
			pu1 = pl+(iu1-il1+1);
			pl2 = pu1+1;
			pu2 = pu; //完成先徐序列pre的切割 
		}
	}
	t->lchild = buildBTreeByPI(pre,pl1,pu1,in,il1,iu1);
	t->rchild = buildBTreeByPI(pre,pl2,pu2,in,il2,iu2);
	return t; 
} 

/*** 二叉树的其它基本操作  ***/ 
//查找给定结点p的父节点 , t非空时，表示已经找到，就不需要递归调用，直接返回 
bNode *parent(bNode *root, bNode *p){
	bNode *t = NULL;
	if (!root || root==p) return NULL;//根无父节点，空树也没有p的父节点 
	
	if ( p && (root->lchild==p || root->rchild==p)) return root;
	if (root->lchild && !t) t = parent(root->lchild,p);
	if (root->rchild && !t) t = parent(root->rchild,p);
	return t; 
} 

//由结点的id（可以改成其它数据域的值）查找结点，返回结点指针 。(先序遍历） 
bNode *locateByID(bNode *root, int id){
	if (!root) return NULL;
	if (root->data.id==id) return root; 
	bNode *t = locateByID(root->lchild,id);
	if (t) return t;
	return locateByID(root->rchild,id);
}

//采用后序遍历销毁树。思考：可以用先序遍历吗？ 
void DestroyBTree(bNode *root){
	if(root == NULL) return;
	if (root->lchild) {DestroyBTree(root->lchild);root->lchild=NULL;}
	if (root->rchild) {DestroyBTree(root->rchild);root->rchild=NULL;}
	if (!root->lchild && !root->rchild) free(root);
}

/***-下面的代码是结点访问函数 visit() 的不同实现方式，实现对单个结点的处理，函数名通常作为二叉树遍历函数的参数 ***/ 
//打印某个结点的信息,依据Elemtype的定义而修改,简单版本（不输出存储地址） 
void bPrintNode(bNode *a){ 
	printf("\n(id = %2d) = %5d",a->data.id,a->data.value); 
}

//打印某个结点的信息,依据Elemtype的定义而修改,详细版本（输出存储地址） 
void cPrintNode(bNode *a){ 
	printf("\n*(addr = %lx):(id=%2d)= %5d",a,a->data.id,a->data.value); 
}

//测试函数值，结点数据域的value值+1
void add1(bNode *a){
	a->data.value += 1;
} 

/***-下面的代码是实现先序遍历、中序遍历和后序遍历的模板，大多数二叉树的操作基于对它们的修改 ***/ 
//先序遍历二叉树
void preTraverseTree(bNode *root,void (*ptrf)(bNode *a)){
	if (root){//递归出口 
		(*ptrf)(root); 
		preTraverseTree(root->lchild,(*ptrf));
		preTraverseTree(root->rchild,(*ptrf));
	}
}

//中序遍历二叉树  
void inTraverseTree(bNode *root,void (*ptrf)(bNode *a)){
	if (root){ //递归出口 
		inTraverseTree(root->lchild,(*ptrf));
		(*ptrf)(root);	
		inTraverseTree(root->rchild,(*ptrf));
	}
}

//后序遍历二叉树 
void postTraverseTree(bNode *root,void (*ptrf)(bNode *a)){
	if (root){//递归出口	
		postTraverseTree(root->lchild,(*ptrf));
		postTraverseTree(root->rchild,(*ptrf));
		(*ptrf)(root);
	}
}

/***-下面的代码用于线索化二叉树：层序遍历结果以链表(链式队列)形式输出 ***/ 
//以下构成一个链式队列，存放二叉树的结点的地址，用于层序遍历二叉树 
struct qNode{ //队列结点 
	bNode *ptr;  //队列的节点包括的数据域是二叉树结点的指针 
	struct qNode *next; //队列的下一个结点，队列是单链表 
};

typedef struct queue{
	struct qNode *front;
	struct qNode *rear;
}linkQueue;

//从二叉树生成层序遍历的队列：分层线索化。输入二叉树，输出队列
//将该队列当成单链表遍历一次，可以实现层序遍历
//该算法也可以稍作修改即得到“层序遍历”算法（尝试一下） 
linkQueue *ToHiraQueue(bNode *root){
	linkQueue *hQueue = (linkQueue *)malloc(sizeof(linkQueue));
	if (!hQueue) exit(0);
	if (!root){
		hQueue->front = NULL;
		hQueue->rear = NULL;
		return hQueue;
	}
	
	struct qNode *head; //线索化过程中的队头(不能修改hQueue->front，防止丢失)，队尾直接用hQueue->rear 
	struct qNode *t = (struct qNode *)malloc(sizeof(struct qNode)); //创建队列哨兵结点（头结点，不存放有效数据的结点） 
	if (!t) exit(0);
	hQueue->front = hQueue->rear = head = t; //此时是空队列 
	 
	//root入队
	t = (struct qNode *)malloc(sizeof(struct qNode)); //创建队列结点 
	if (!t) exit(0);
	t->ptr = root;  //数据域赋值，指针next可以不用赋值(why?) 
	hQueue->rear->next = t;
	hQueue->rear = t;
	
	while(head != hQueue->rear){//队列不空 ,head是哨兵结点，数据无效，有效数据从head->next开始 
		head = head->next; //出队（模拟出队，因为要返回线索化的队列，所以不能修改队列的头指针)	
		//printf("de-%lx,",head->ptr);	//打印语句，调试用，查看入队、出队过程 
		if (head->ptr->lchild) { //head->next存放数据（结点）的左孩子非空，构建新队列结点，入队 
			t = (struct qNode *)malloc(sizeof(struct qNode));
			if (!t) exit(0);
			t->ptr = head->ptr->lchild;	//新结点的数据域赋值 
			hQueue->rear->next = t; //新节点接到队列尾部	
			hQueue->rear = t;	
			//printf("en-%lx,",t->ptr); //打印语句，调试用，查看入队、出队过程 
		}
		if (head->ptr->rchild) { //head存放数据（结点）的右孩子非空，构建新队列结点，入队 
			t = (struct qNode *)malloc(sizeof(struct qNode));
			if (!t) exit(0);
			t->ptr = head->ptr->rchild;	//新结点的数据域赋值 
			hQueue->rear->next = t; //新节点接到队列尾部	
			hQueue->rear = t;	
			//printf("en-%lx,",t->ptr);//打印语句，调试用，查看入队、出队过程 
		}	
	} 
	return hQueue;
} //思考如何实现先序/中序/后序遍历的线索化？并输出线索化后的队列

/*** 下面是一些典型应用 ***/ 
//求二叉树的高度/深度 
int deepth(bNode *root){
	if (!root) return 0;
	int d = deepth(root->lchild);
	int n = deepth(root->rchild);
	return (d>n)? d+1 : n+1; 
}

//求二叉树度为2的结点数目 
int node2(bNode *root){
	int c=0;
	if (!root) return 0;
	if (root->lchild && root->rchild) c=1;	
	return c+node2(root->lchild)+node2(root->rchild);
}

//求二叉树度为1的结点数目  
int node1(bNode *root){
	int c=0;
	if (!root) return 0;
	if ((!root->lchild && root->rchild) ||(root->lchild && !root->rchild))  c=1;	
	return c+node1(root->lchild)+node1(root->rchild);
}

//求二叉树度为0的结点数目 (叶子结点数目） 
int node0(bNode *root){
	if (!root) return 0;
	if (!root->lchild && !root->rchild) return 1;	
	return node0(root->lchild)+node0(root->rchild);
}

//求二叉树度为0的结点数目的value之和 
int value0(bNode *root){
	if (!root) return 0;
	if (!root->lchild && !root->rchild) return root->data.value;	
	return value0(root->lchild)+value0(root->rchild);
}

int main(){
	

	int val[]={22,32,6,12,75,9,13,41,7,16,17};
	int val2[] = {3,4,5,8,1,9,11,10,7,0};
	int n = 11;
	
	printf("\n测试二叉树生成 value:");
	bNode *t1 = buildBTreeByValue(val,n); //测试由值数组生成二叉树 
	//preTraverseTree(t1,add1); //测试先序遍历 
	inTraverseTree(t1,cPrintNode);  //测试中序遍历 
	//postTraverseTree(t1,cPrintNode);//测试后续遍历 

	//作业部分测试
	printf("\n作业部分测试:\n");
	//TreeDeleteByValue(t1,8);
	TreePathSearch(t1,7);
	int c = TreeFindCommonAncestor(t1,70,8);
	printf("共同的祖先id = %d\n",c);
	int d = TreeCalMaxSubMin(t1);
	printf("max-min=%d\n",d);


/*	DestroyBTree(t1);
		
	printf("\n测试二叉树生成 edge :");
	int edge[7]={5,6,6,1,2,2,-1}; //增加边数组 
	t1 = buildBTreeByEdge(val,edge,n); //测试由值数组和边生成二叉树 
	preTraverseTree(t1,bPrintNode); //测试先序遍历 
	inTraverseTree(t1,add1);  //测试中序遍历 
	postTraverseTree(t1,cPrintNode);//测试后续遍历 
	DestroyBTree(t1);
	
	printf("\n测试二叉树生成 Prelist:");
	int prelist[15]={17,32,41,-9999,-9999,-9999,13,7,-9999,-9999,16,22,-9999,-9999,-9999};
	t1 = buildBTreeByPrelist(prelist,15);
	preTraverseTree(t1,cPrintNode); //测试先序遍历 
	inTraverseTree(t1,cPrintNode);  //测试中序遍历 
	postTraverseTree(t1,bPrintNode);//测试后续遍历 
	
	//测试层序线索化
	printf("\n测试层序线索化:");
	linkQueue *qlist =  ToHiraQueue(t1);
	for(struct qNode *p = qlist->front;p!=qlist->rear;p = p->next)
		printf("%d, ",p->next->ptr->data.value); //打印线索化链表 
	printf("\n");
	
	//测试结点查找和求父节点 
	printf("\n测试结点查找和求父节点:");
	bNode *tn = locateByID(t1,2);
	if (!tn) 
		printf("\n没找到结点");
	else{
		cPrintNode(tn);
		printf("\n父节点为："); 
		tn=parent(t1,tn);
		if (!tn)
			printf("没找到");
		else
			cPrintNode(tn); 
	}	
	DestroyBTree(t1);
	
	//测试先序序列和中序序列构造二叉树
	printf("\n测试二叉树生成 PI:");
	int pre[]={17,32,41,13,7,16,22};
	int in[]={41,32,17,7,13,22,16};
	t1=buildBTreeByPI(pre,0,n-1,in,0,n-1); 
	if (t1){ 
		preTraverseTree(t1,cPrintNode); //测试先序遍历 
		inTraverseTree(t1,cPrintNode);  //测试中序遍历 
		postTraverseTree(t1,cPrintNode);//测试后续遍历 
	}
*/	
	saveTree(t1,"sg.html"); 
	
	//典型应用测试
	
	// printf("\n树高度 %d ",deepth(t1)); 
	// printf("\n树度为2的结点数目 %d ",node2(t1)); 
	// printf("\n树度为0的结点数目 %d ",node0(t1)); 
	// printf("\n树度为1的结点数目 %d ",node1(t1));
	// printf("\n树度为0的结点value之和 %d ",value0(t1)); 
	
	DestroyBTree(t1);
	return 1;
}
//以下四个函数是作业需要完成的部分
bNode* TreeDeleteByValue(bNode *root,int value)
{
	/*
		删除节点value=x 的节点及其子树
	*/
	if(root ==NULL)
	return NULL;
	if(root->data.value == value)//该节点自身需要删除
	{
		DestroyBTree(root->lchild);//该函数内部实现在老师的基础上做了修改，使之能接受空指针而不会出问题
		DestroyBTree(root->rchild);
		free(root);
		return NULL;
	}
	else//该节点需要保留
	{
		root->lchild = TreeDeleteByValue(root->lchild,value);
		root->rchild = TreeDeleteByValue(root->rchild,value);
		return root;
	}
}
int TreeFindCommonAncestor(bNode *root,int id1,int id2)
{
	std::stack<int> stack_path_reverse1;
	std::stack<int> stack_path_reverse2;
	TreePathSearch(root,id1,&stack_path_reverse1);
	TreePathSearch(root,id2,&stack_path_reverse2);
	if(stack_path_reverse1.size() == 0 || stack_path_reverse2.size() == 0)
	return -1;//没有共同祖先
	bNode* commonAncestor = root;
	while(stack_path_reverse1.size() != 0 && stack_path_reverse2.size() != 0)
	{
		if(stack_path_reverse1.top() == stack_path_reverse2.top())//下一条路相同
		{
			if(stack_path_reverse1.top() == 0)
			commonAncestor = commonAncestor->lchild;
			else
			commonAncestor = commonAncestor->rchild;
			stack_path_reverse1.pop();
			stack_path_reverse2.pop();
		}
		else//下一条路不同
		{
			break;
		}
	}
	return (commonAncestor->data.id);
}
void TreePathSearch(bNode *root,int id)
{
	std::stack<int> stack_path;//已经走过的路径，0表示左走，1表示右走
	std::stack<bNode*> stack_node;//前面的节点
	if(root == NULL || root->data.id == id) return;
	bNode * p = root;
	int last_operation = 0;//0表示上次向下走，1代表上次从左分支向上走，2代表上次从右分支向上走
	while(1)
	{
		if(p->data.id == id)//找到了目标节点，跳出循环
			break;
		if(last_operation == 0)//上次往下走，这次优先往左下走
		{
			if(p->lchild != NULL)//可以往下走
			{
				stack_path.push(0);
				stack_node.push(p);
				p = p->lchild;
				last_operation = 0;
			}
			else if(p->rchild != NULL)//左边没路,往右下走
			{
				stack_path.push(1);
				stack_node.push(p);
				p = p->rchild;
				last_operation = 0;
			}
			else//两边都走不了，往回走
			{
				if(stack_path.size() == 0)
				{
					break;//已经无法回头
				}
				if(stack_node.top()->lchild == p)
				{
					last_operation = 1;//从左侧返回
				}
				else
				{
					last_operation = 2;//从右侧返回
				}
				stack_path.pop();
				p = stack_node.top();
				stack_node.pop();
			}
		}
		else if(last_operation == 1)//上次从左返回，这次尝试往右下走
		{
			if(p->rchild != NULL)//可以往右下走
			{
				stack_path.push(1);
				stack_node.push(p);
				p = p->rchild;
				last_operation = 0;
			}
			else//只能往回走了
			{
				if(stack_path.size() == 0)
				{
					break;//已经无法回头
				}
				if(stack_node.top()->lchild == p)
				{
					last_operation = 1;//从左侧返回
				}
				else
				{
					last_operation = 2;//从右侧返回
				}
				stack_path.pop();
				p = stack_node.top();
				stack_node.pop();
			}
		}
		else//last_operation==2,上次从右侧返回，这次只能返回
		{
			if(stack_path.size() == 0)
				{
					break;//已经无法回头
				}
				if(stack_node.top()->lchild == p)
				{
					last_operation = 1;//从左侧返回
				}
				else
				{
					last_operation = 2;//从右侧返回
				}
				stack_path.pop();
				p = stack_node.top();
				stack_node.pop();
		}
	}
	//到此为止如果stack_path不是空的，说明中途退出了，找到了目标节点
	std::stack<int> stack_path_reverse;
	while(stack_path.size() != 0)//将栈倒过来方便输出
	{
		stack_path_reverse.push(stack_path.top());
		stack_path.pop();
	}
	printf("路径为:");
	while(stack_path_reverse.size() != 0)//输出
	{
		if(stack_path_reverse.top() == 0)
		printf("左");
		else
		printf("右");
		stack_path_reverse.pop();
	}
	printf("\n");
}
void TreePathSearch(bNode *root,int id,std::stack<int>* stack_path_reverse)
{
	//函数重载,将结果stack_path_reverse改为由外部输入，可以把结果带到函数外
	std::stack<int> stack_path;//已经走过的路径，0表示左走，1表示右走
	std::stack<bNode*> stack_node;//前面的节点
	if(root == NULL || root->data.id == id) return;
	bNode * p = root;
	int last_operation = 0;//0表示上次向下走，1代表上次从左分支向上走，2代表上次从右分支向上走
	while(1)
	{
		if(p->data.id == id)//找到了目标节点，跳出循环
			break;
		if(last_operation == 0)//上次往下走，这次优先往左下走
		{
			if(p->lchild != NULL)//可以往下走
			{
				stack_path.push(0);
				stack_node.push(p);
				p = p->lchild;
				last_operation = 0;
			}
			else if(p->rchild != NULL)//左边没路,往右下走
			{
				stack_path.push(1);
				stack_node.push(p);
				p = p->rchild;
				last_operation = 0;
			}
			else//两边都走不了，往回走
			{
				if(stack_path.size() == 0)
				{
					break;//已经无法回头
				}
				if(stack_node.top()->lchild == p)
				{
					last_operation = 1;//从左侧返回
				}
				else
				{
					last_operation = 2;//从右侧返回
				}
				stack_path.pop();
				p = stack_node.top();
				stack_node.pop();
			}
		}
		else if(last_operation == 1)//上次从左返回，这次尝试往右下走
		{
			if(p->rchild != NULL)//可以往右下走
			{
				stack_path.push(1);
				stack_node.push(p);
				p = p->rchild;
				last_operation = 0;
			}
			else//只能往回走了
			{
				if(stack_path.size() == 0)
				{
					break;//已经无法回头
				}
				if(stack_node.top()->lchild == p)
				{
					last_operation = 1;//从左侧返回
				}
				else
				{
					last_operation = 2;//从右侧返回
				}
				stack_path.pop();
				p = stack_node.top();
				stack_node.pop();
			}
		}
		else//last_operation==2,上次从右侧返回，这次只能返回
		{
			if(stack_path.size() == 0)
				{
					break;//已经无法回头
				}
				if(stack_node.top()->lchild == p)
				{
					last_operation = 1;//从左侧返回
				}
				else
				{
					last_operation = 2;//从右侧返回
				}
				stack_path.pop();
				p = stack_node.top();
				stack_node.pop();
		}
	}
	//到此为止如果stack_path不是空的，说明中途退出了，找到了目标节点
	while(stack_path.size() != 0)//将栈倒过来方便输出
	{
		(*stack_path_reverse).push(stack_path.top());
		stack_path.pop();
	}
	/*
	printf("路径为:");
	while(stack_path_reverse.size() != 0)//输出
	{
		if(stack_path_reverse.top() == 0)
		printf("左");
		else
		printf("右");
		stack_path_reverse.pop();
	}
	printf("\n");
	*/
}
int TreeCalMaxSubMin(bNode *root)
{ 
	if(root ==  NULL)
	return 0;
	static int max = root->data.value;
	static int min = root->data.value;
	if(root->data.value > max) max = root->data.value;
	if(root->data.value < min) min = root->data.value;
	TreeCalMaxSubMin(root->lchild);
	TreeCalMaxSubMin(root->rchild);
	return (max - min);
}
#endif
