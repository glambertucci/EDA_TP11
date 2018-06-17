#pragma once
#include <vector>

#include "Node.h"

using namespace std;
class Graph
{
public:
	Graph(unsigned int nodes);
	~Graph();
	void shuffleNodes();
	void checkAndSendTransactions();
	void checkAndSendBlocks();
	void checkAndRecieveTransactions();
	void checkAndRecieveBlocks();
	void createTransaction(unsigned int source, unsigned int dest, unsigned int lukeDollars);
	void run();
private:
	vector <Node> nodes;
};

