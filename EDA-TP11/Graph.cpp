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
	this->checkAndSendTransactions();
	this->checkAndRecieveTransactions();
	this->checkAndSendBlocks();
	this->checkAndRecieveBlocks();

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
		Transaction * temp = node.getUncheckedTransaction();
		if (temp != nullptr) {
			node.checkTransaction(ok, *temp);
			node.destroyTransacction();
		}
	}
}

void Graph::checkAndRecieveBlocks()
{
	for (Node& node : nodes) {
		bool ok = false;
		Block temp = *(node.getUncheckedBlock());
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

	if (check.size() == nodes.size()) {//me fijo si es el ultimo
		int num = check[check.size() - 1];
		vector<Node>::iterator last = find_if(nodes.begin(), nodes.end(), [num](Node& node) {return (node.getNum() == num); });//agarro el ultimo nodo y lo uno al primero
		num = check[0];
		vector<Node>::iterator first = find_if(nodes.begin(), nodes.end(), [num](Node& node) {return (node.getNum() == num); });
		Node *last_ =&*last;
		last_->setNextNode(&*first);
		return;
	}

	int num = node->getNum();
	if (find(check.begin(), check.end(), num) != check.end()) {//sino agarro el NUMERO SECRETO (SHHHH) del nodo y me fijo si ya fue agregado a grafo
		int pos = rand() % nodes.size();//si lo fue busco un nodo al azar, remuevo el ultimo nodo y hago que el nodo anterior apunte a un nodo aleatorio
		check.pop_back();
		prev->setNextNode(&nodes[pos]);
		correctGraph(prev,node, nodes, check);
	}
	else {
		check.push_back(num);
		correctGraph(node->getNextNode(), node, nodes, check);
	}

}

bool Graph::createTransaction(Node* source, Node * dest, unsigned int lukeDollars, bool realTrans) {
	if (realTrans) {
		if (hasFunds(*source, (int)lukeDollars))
		{
			Transaction tx;
			int vuelto = addInput(*source, tx, lukeDollars);
			if (vuelto > 0) {
				addOutput(*source, tx, vuelto);
			}
			addOutput(*dest, tx, lukeDollars);

			source->recieveTransaction(tx);
			return true;
		}
		return false;
	}
	else {

	}
}


Graph::~Graph()
{
}
void Graph::firstblock(vector <Node>& nodes) {//Arma el primer bloque
	Block temp;
	vector<byte>ceros;
	for (int i = 0; i < 32; i++)
		ceros.push_back(0);
	temp.setNonce(0);
	temp.setNumber(0);
	temp.setTimeStamp(time(NULL));
	temp.setHash(ceros);
	Transaction temp2;
	Output temp3;
	temp3.setGP(40397224.0);
	temp3.setPublicKey(nodes[0].getpkey());
	temp2.outputs.push_back(temp3);

	for (Node& node : nodes) {
		node.addBlock(temp);		
	}
}