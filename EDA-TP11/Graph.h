#pragma once
#include <vector>

#include "Node.h"

using namespace std;
class Graph
{
public:
	Graph(unsigned int nodes);
	~Graph();

	void run();
	void shuffleNodes();
	void checkAndSendTransactions();		
	void checkAndSendBlocks();
	void checkAndRecieveTransactions();
	void checkAndRecieveBlocks();
	bool createTransaction(Node* source, Node * dest, unsigned int lukeDollars, bool realTrans);

	void get_nodes(vector <Node>& nodes_) { nodes_ = this->nodes; };
private:
	vector <Node> nodes;
	void firstblock(vector <Node>& nodes);//Arma el primer bloque
};

