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
		this->nodes[i].setNextNode(&(nodes[i + 1]));
		this->nodes[i].setPrevNode(&(nodes[i - 1]));
	}
}

void Graph::run()
{

}

void Graph::shuffleNodes()
{
	for (int i = 0; i < ((this->nodes.size()) / 2); i++)
	{
		swap(this->nodes[rand() % nodes.size()], this->nodes[rand() % nodes.size()]);
	}
}

void Graph::createTransaction(unsigned int source, unsigned int dest, unsigned int lukeDollars) {
	if (hasFunds(this->nodes[source], (int)lukeDollars))
	{
		Transaction tx;
		int vuelto = tx.addInput(this->nodes[source], lukeDollars);
		if (vuelto > 0) {
			tx.addOutput(this->nodes[source], vuelto);
		}
		tx.addOutput(this->nodes[dest], lukeDollars);

		nodes[source].recieveTransaction(tx);
	}
}
Graph::~Graph()
{
	cout << "Eda sux" << endl;
}
