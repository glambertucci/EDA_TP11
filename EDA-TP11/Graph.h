#pragma once
#include <vector>
#include "FullService.h"
#include "Miner.h"
#include "timer.h"
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
	int lastSuccesNode = 0;
	void get_nodes(vector <Node>& nodes_) {
		nodes_ = this->nodes;
		for (int i = 0; i < nodes_.size(); i++) {
			if (nodes_[i].miner) {
				this->Miners.push_back(i);//arma el vector de mineros.
			}
		}
	};
	vector <int> Miners;
	vector <Node> nodes;

private:


	vector <Timer> timers;
	void firstblock(vector <Node>& nodes);//Arma el primer bloque
};

