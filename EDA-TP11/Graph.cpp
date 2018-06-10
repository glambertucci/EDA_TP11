#include "Graph.h"
#include "Transaction.h"
#include <vector>
Graph::Graph(unsigned int node)
{
	// Crea todos los nodos y hace el grafo
	for (int i = 0; i < node; i++)
		this->nodes.push_back(Node());
	for (int i = 1; i < node-1; i++)
	{
		this->nodes[i].setNextNode( &(nodes[i + 1]));
		this->nodes[i].setPrevNode(&(nodes[i - 1]));
	}

	//this->nodes[0].prevn = &(nodes[node -1]);
	//this->nodes[0].nextn = &(nodes[1]);
	//this->nodes[node - 1].prev = &(nodes[node - 2]);
	//this->nodes[node - 1].nextn = &(nodes[0]);

}

void Graph::createTransaction(unsigned int source, unsigned int dest, unsigned int lukeDollars) {
	if (hasfunds(this->nodes[source], (int)lukeDollars))
	{
		Transaction tx;
		tx.addInput(this->nodes[source], lukeDollars);
		tx.addOutput(this->nodes[source], lukeDollars);
		tx.addOutput(this->nodes[dest], lukeDollars);
	}
}
Graph::~Graph()
{
	cout << "Eda sux" << endl;
}
