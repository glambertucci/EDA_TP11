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
	void createTransaction(unsigned int source, unsigned int dest, unsigned int lukeDollars);

	void get_nodes(vector <Node>& nodes_) { nodes_ = this->nodes; };
private:
	vector <Node> nodes;
};

