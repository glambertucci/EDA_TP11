#pragma once
#include <vector>
#include <stack>
#include <queue>

#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>
#include <cryptopp/eccrypto.h>
#include <cryptopp/oids.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha3.h>

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
	CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256> publicKey, privateKey;
	vector <Transaction> UTXO;
	stack<Block> blockchain;
	vector <Transaction> newTransactions;
	queue <Transaction> nonConfirmedTransactions;
	Block actualBlock;
};

