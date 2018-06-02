#include "Graph.h"
using namespace std;

Graph::Graph(unsigned int node)
{
	// Crea todos los nodos y hace el grafo
	for (int i = 0; i < node; i++)
		this->nodes.push_back(Node());

	for (int i = 1; i < node-1; i++)
	{
		this->nodes[i].nextn = &(nodes[i + 1]);
		this->nodes[i].prevn = &(nodes[i - 1]);
	}

	this->nodes[0].prevn = &(nodes[node -1]);
	this->nodes[0].nextn = &(nodes[1]);
	this->nodes[node - 1].prev = &(nodes[node - 2]);
	this->nodes[node - 1].nextn = &(nodes[0]);

}


Graph::~Graph()
{
}
