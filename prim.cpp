#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
/**********边表************/
class EdgeNode
{
public:
	int adjvex;
	int cost;
	int head;
	EdgeNode *next;
	EdgeNode(int _head, int _adj, int _cost,EdgeNode *n = NULL) : head(_head), adjvex(_adj), cost(_cost), next(n) {}
};
/*=========顶点表============*/
class VertexNode
{
public:
	int data;
	EdgeNode *firstEdge;
	VertexNode()
	{
		firstEdge = NULL;
	}
};
/*********自定义比较函数(优先队列使用)************/
class mycompare
{
	bool reverse;
public:
	mycompare(const bool &re = true)
	{
		reverse = re;	
	}
	bool operator() (EdgeNode *a, EdgeNode *b) const
	{
		//从小到大排列， 优先队列,!mycompare，按照cost的从小到大排列
		if(reverse) return (a->cost > b->cost); 
		else {
			return (a->cost < b->cost);
			//从小到大排列， 优先队列,!mycompare，按照cost的从大到小排列
		}

	}

};
/*********无向图的数据结构*************/
class Graph 
{
public:
/*********初始化图的邻接表数据***************/
	Graph()
	{
		ifstream fin("pp.txt");
		string line;
		stringstream stream;
		if(getline(fin, line))
		{
			stream.clear();
			stream << line;
			stream >> numVertexes;
			stream >> numEdges;
		}
		init_adjList();
		while(getline(fin, line))
		{
			int vertex, adjacent,  _cost;
			stream.clear();
			stream << line;
			stream >> vertex;
			stream >> adjacent;
			stream >> _cost;
			addEdge(vertex, adjacent, _cost);			
		}
	}
/********初始化邻接表的顶点表*******/
	void init_adjList()
	{
		adjList.resize(numVertexes);
		for(int i = 0; i < numVertexes; i++)
		{	
			adjList[i].data = i;
		}		
	}


/************加边，头插法*****************/
	void addEdge(int a, int b, int _cost)
	{
		EdgeNode *enode1 = new EdgeNode(a-1, b-1, _cost, NULL);
		EdgeNode *enode2 = new EdgeNode(b-1, a-1, _cost, NULL);
		adjList[a-1].data = a-1;
		enode1->next = adjList[a-1].firstEdge;
		adjList[a-1].firstEdge = enode1;
		adjList[b-1].data = b-1;
		enode2->next = adjList[b-1].firstEdge;
		adjList[b-1].firstEdge = enode2;
	}
/************打印看结果************/
	void print()
	{
		ofstream fout;
		fout.open("primoutput.txt");
		for(int i = 0; i < numVertexes; i++)
		{
			fout << "vertex:" << adjList[i].data << " adj:" ;
			EdgeNode *tmp = new EdgeNode(0, 0, 0 );
			tmp = adjList[i].firstEdge;
			while(tmp)
			{
				fout << tmp->adjvex << "cost: " << tmp->cost << " ";
				tmp = tmp->next;
			}
			fout << endl;
		}
	}
/*********************************/
public:
	int numVertexes; //顶点数目
	int numEdges;	 //边数目
	vector<VertexNode> adjList;   //图的邻接表
};
/***********prim算法实现**********/
class Prims
{
public:
	Prims(Graph graph)
	{
		int s = 0;
		length = graph.numVertexes; //顶点数目
		tree.resize(length); 
		marked.push_back(s); //将初始顶点加入最小生成树中
		pq.push(graph.adjList[s].firstEdge); //将初始顶点的第一条边加入队列
		while(!pq.empty())
		{
			EdgeNode *p = new EdgeNode(0,0,0);
			p = graph.adjList[s].firstEdge;
			while(p)
			{
				if(!is_marked(p->adjvex))
				{
					pq.push(p);
				}
				p = p->next;
			}

			EdgeNode *p1 = new EdgeNode(0,0,0);
			p1 = pq.top();
			pq.pop();
			s = p1->adjvex;
			if(!is_marked(s)) //如果没有加入进最小生成树
			{
				marked.push_back(p1->adjvex);
				tree[p1->head].push_back(p1->adjvex); //将边加入最小生成数
				sum += p1->cost;  //cost的累加
			}
		
		}

	}
/*******************判断是否加入最小生成树***************/	
	bool is_marked(int a)
	{
	
		for(int i = 0; i < marked.size(); i++)
		{
			if(marked[i] == a)
			{
				return true;
			}
		}
		return false;
	}
/***************输出看结果**************/
	void write()
	{
		ofstream fout;
		fout.open("tree.txt");
		for(int i = 0; i < length; i++)
		{
			fout << "tree[" << i << "]: " ;
			for(int j = 0; j < tree[i].size(); j++)
			{
				fout << tree[i][j] << " ";
			}
			fout << endl;
		}
	}


public:
	int length;
	int sum = 0;
	vector<int> marked;//最小生成树木的顶点表
	vector<vector<int> > tree; //最小生成树的边 ,数组存储
	priority_queue<EdgeNode*, vector<EdgeNode*>, mycompare> pq; //优先队列
};


int main()
{
	Graph graph;
	graph.print();
	Prims _prims(graph);
	_prims.write();
	cout << "sum: " << _prims.sum << endl;
	return 0;
}





