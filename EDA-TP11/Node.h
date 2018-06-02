#pragma once
#include <vector>
#include <stack>
#include <queue>

#include "Transaction.h"
#include "Block.h"

using namespace std;

class Node
{
public:
	Node();
	~Node();
private:
	Node * prev, * post;
	ECDSA <ECD, SHA256> publicKey, privateKey;
	vector <Transaction> UTXO;
	stack<Block> blockchain;
	vector <Transaction> newTransactions;
	queue <Transaction> nonConfirmedTransactions;
	Block actualBlock;
};

