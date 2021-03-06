#include <iostream>
#include <list>

using std::cout;
using std::cin;
using std::endl;
using std::list;

//amount of edges
const int E = 14; 
//amount of nodes
const int V = 8; 

struct edge
{
	int weight;
	int v1, v2;
};

void sort(edge* g, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int min = i;
		for (int j = i; j < size; j++)
		{
			if (g[min].weight > g[j].weight)
			{
				min = j;
			}
		}
		edge temp;
		temp.v1 = g[i].v1; temp.v2 = g[i].v2; temp.weight = g[i].weight;
		g[i].v1 = g[min].v1; g[i].v2 = g[min].v2; g[i].weight = g[min].weight;
		g[min].v1 = temp.v1; g[min].v2 = temp.v2; g[min].weight = temp.weight;
	}
}

void main()
{
	int y = E - V + 1;

	//--Kruskal--
	edge g[E] = 
	{ 
		{2,1,2},{1,2,3},{7,3,5},{2,5,8},
		{2,7,8},{1,6,7},{5,4,6},{4,1,4},
		{1,2,4},{2,2,5},{2,5,7},{1,4,7},
		{6,1,7},{8,2,8} 
	};
	sort(g, E);

	list<edge> ostovByKruskal;
	int node[V];
	for (int i = 0; i < V; ++i)
	{
		node[i] = i;
	}
	for (int i = 0; i < E; ++i)
	{
		int a = g[i].v1;
		int b = g[i].v2;
		if (node[a-1] != node[b-1])
		{
			ostovByKruskal.push_back({ 0,a,b });
			int oldNode = node[b-1];
			int newNode = node[a-1];
			for (int j = 0; j < V; ++j)
			{
				if (node[j] == oldNode)
				{
					node[j] = newNode;
				}
			}
		}
	}

	cout << "edges for ostov by Kruskal:\n";
	for (list<edge>::iterator i = ostovByKruskal.begin(); i != ostovByKruskal.end(); ++i)
	{
		cout << "[ " << (*i).v1 << "-" << (*i).v2 << " ]" << endl;
	}

	cout << endl;

	//--Prim--
	edge t[E] =
	{
		{2,1,2},{1,2,3},{7,3,5},{2,5,8},
		{2,7,8},{1,6,7},{5,4,6},{4,1,4},
		{1,2,4},{2,2,5},{2,5,7},{1,4,7},
		{6,1,7},{8,2,8}
	};
	
	int adjMatrix[V][V];
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			adjMatrix[i][j] = -1;
		}
	}
	for (int i = 0; i < E; i++)
	{
		adjMatrix[t[i].v1-1][t[i].v2-1] = t[i].weight;
		adjMatrix[t[i].v2-1][t[i].v1-1] = t[i].weight;
	}

	int currentNode = 1;
	list<edge> ostovByPrim;
	list<int> nodesInOstov;
	nodesInOstov.push_back(currentNode);
	for (int i = 0; i < V - 1; i++)
	{
		int min = INT_MAX;
		int minNode;
		for (int j = 1; j < V; j++)
		{
			for (list<int>::iterator node = nodesInOstov.begin(); node != nodesInOstov.end(); ++node)
			{
				if ((adjMatrix[*node-1][j] < min) && (adjMatrix[*node-1][j] != -1))
				{
					min = adjMatrix[*node-1][j];
					minNode = j + 1;
					currentNode = *node;
				}
			}
		}
		ostovByPrim.push_back({ 0,currentNode, minNode });
		nodesInOstov.push_back(minNode);
		for (int j = 0; j < V; j++)
		{
			adjMatrix[j][minNode-1] = -1;
		}
	}
	cout << "edges for ostov by Prim:\n";
	for (list<edge>::iterator i = ostovByPrim.begin(); i != ostovByPrim.end(); ++i)
	{
		cout << "[ " << (*i).v1 << "-" << (*i).v2 << " ]" << endl;
	}
}