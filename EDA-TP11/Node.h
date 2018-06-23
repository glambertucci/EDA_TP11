#pragma once
#include <vector>
#include <stack>
#include <queue>
#include <chrono>

#include "CryptoHelper.h"

#include "cryptopp/cryptlib.h"
#include "cryptopp/osrng.h"
#include "cryptopp/eccrypto.h"
#include "cryptopp/oids.h"
#include "cryptopp/hex.h"
#include "cryptopp/sha3.h"

#include "Transaction.h"
#include "Block.h"

#define MINCEROS 3
using namespace std;

class Node
{
public:
	Node(int a);
	~Node();
	void recieveTransaction(Transaction Tx);
	void checkTransaction(bool& ok, Transaction& Tx);
	void addTransaction(Transaction &Tx);
	void sendLastTransaction();
	//Te devuelve la primera  transaccion sin verifiacr
	Transaction * getUncheckedTransaction();
	//Destruye la primer transaccion sin verificar
	void destroyTransacction();

	void sendLastBlock();
	Block * getUncheckedBlock();
	void recieveBlock(Block block);
	void checkBlock(bool& ok, Block& block);
	void addBlock(Block& block);


	bool isMyPublicKey(ECDSA<ECP, SHA256>::PublicKey publicKey);
	ECDSA<ECP, SHA256>::PublicKey getpkey(void) { return this->publicKey; }
	int getNum(void) { return num; }//DEBUG
	bool isMyNum(int a) { return (a == num); }//DEBUG
	vector<byte> sign(string dataToSend);
	bool checkSignature(vector<byte> sig, string dataToSign, ECDSA<ECP, SHA256>::PublicKey publicKey);
	vector <Transaction> getUTXO() { return this->UTXO; }

	void setNextNode(Node* node) { this->post = node; }
	void setPrevNode(Node* node) { this->prev = node; }
	Node * getNextNode() { return post; }
	Node * getPrevNode() { return prev; }

	void setTransactionTimestamp();
	chrono::high_resolution_clock::time_point getTransactionTimeStamp() { return transactionTimestamp; }
	chrono::high_resolution_clock::time_point getBlockTimestamp() { return blockTimestamp; }
protected:
	int num;
	Node * prev, *post;
	ECDSA<ECP, SHA256>::PrivateKey privateKey;
	ECDSA<ECP, SHA256>::PublicKey publicKey;
	vector <Transaction> UTXO;
	stack<Block> blockchain;
	vector <Transaction> newTransactions;
	queue <Transaction> nonConfirmedTransactions;
	bool miner;
	Block actualBlock;
	Block nonConfirmedBlock;
	chrono::high_resolution_clock::time_point transactionTimestamp,blockTimestamp;
};

