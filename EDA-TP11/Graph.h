#pragma once
#include <vector>

#include "Node.h"

using namespace std;
class Graph
{
public:
	Graph(unsigned int nodes);
	~Graph();
	void checkAndSendTransactions();
	void checkAndSendBlocks();
	void checkAndRecieveTransactions();
	void checkAndRecieveBlocks();
	void createTransaction(unsigned int source, unsigned int dest, unsigned int lukeDollars);
private:
	vector <Node> nodes;
};

