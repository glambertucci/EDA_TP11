#include "Graph.h"
#include "TransactionHelper.h"
#include <vector>
void correctGraph(Node * node, Node * prev, vector<Node>& nodes, vector<int>& check);
void correctGraphBackwards(Node * node, Node * prev, int first);
Graph::Graph(unsigned int node)
{
	// Crea todos los nodos y hace el grafo
	for (int i = 0; i < node; i++)
		this->nodes.push_back(Node(i));
	for (int i = 0; i < node; i++)
	{
		if (i == 0) {
			this->nodes[i].setNextNode(&(nodes[i + 1]));
			this->nodes[i].setPrevNode(&(nodes[node-1]));
		}
		else if (i == node - 1) {
			this->nodes[i].setNextNode(&(nodes[0]));
			this->nodes[i].setPrevNode(&(nodes[i - 1]));
		}
		else {
			this->nodes[i].setNextNode(&(nodes[i + 1]));
			this->nodes[i].setPrevNode(&(nodes[i - 1]));
		}
	}
}

void Graph::run()
{

}

void Graph::shuffleNodes()
{
	srand(time(NULL));
	for (int i = 0; i < ((this->nodes.size())); i++)
	{
		int a = rand() % nodes.size();
		int b = rand() % nodes.size();
		while (a==b)
			a = rand() % nodes.size();
		swap(this->nodes[a], this->nodes[b]);
	}

	vector<int> check;
	correctGraph(&nodes[0], nullptr, nodes, check);
	correctGraphBackwards(&nodes[0], nullptr, nodes[0].getNum());
}

void Graph::checkAndSendTransactions()
{
	for (Node& node : this->nodes) {
		node.sendLastTransaction();		// Esta funcion deberia tener algo para que no se mande todo el tiempo
	}
}

void Graph::checkAndSendBlocks()
{
	for (Node& node : nodes) {
		node.sendLastBlock();
	}
}

void Graph::checkAndRecieveTransactions()
{
	for (Node& node : nodes) {
		bool ok = false;
		Transaction temp = *node.getUncheckedTransaction();
		node.checkTransaction(ok, temp);
		node.destroyTransacction();
	}
}

void Graph::checkAndRecieveBlocks()
{
	for (Node& node : nodes) {
		bool ok = false;
		Block temp = *node.getUncheckedBlock();
		node.checkBlock(ok, temp);
		//Tengo que "pisar" a ese bloque, o crear uno nuevo, no se
	}
}

void correctGraphBackwards(Node * node, Node * prev, int first) {
	static int i = 0;
	if ((first != node->getNum()) || (i++)== 0)
		correctGraphBackwards(node->getNextNode(), node, first);
	if (prev != nullptr)
		node->setPrevNode(prev);
}

void correctGraph(Node * node,Node * prev, vector<Node>& nodes, vector<int>& check) {

	if (check.size() == nodes.size()) {
		int num = check[check.size() - 1];
		vector<Node>::iterator last = find_if(nodes.begin(), nodes.end(), [num](Node& node) {return (node.getNum() == num); });
		num = check[0];
		vector<Node>::iterator first = find_if(nodes.begin(), nodes.end(), [num](Node& node) {return (node.getNum() == num); });
		Node *last_ =&*last;
		last_->setNextNode(&*first);

		return;
	}

	int num = node->getNum();
	if (find(check.begin(), check.end(), num) != check.end()) {
		int pos = rand() % nodes.size();
		check.pop_back();
		prev->setNextNode(&nodes[pos]);
		correctGraph(prev,node, nodes, check);
	}
	else {
		check.push_back(num);
		correctGraph(node->getNextNode(), node, nodes, check);
	}

}

void Graph::createTransaction(unsigned int source, unsigned int dest, unsigned int lukeDollars) {
	if (hasFunds(this->nodes[source], (int)lukeDollars))
	{
		Transaction tx;
		int vuelto = addInput(this->nodes[source],tx, lukeDollars);
		if (vuelto > 0) {
			addOutput(this->nodes[source],tx, vuelto);
		}
		addOutput(this->nodes[dest], tx, lukeDollars);

		nodes[source].recieveTransaction(tx);
	}
}

Graph::~Graph()
{
}
