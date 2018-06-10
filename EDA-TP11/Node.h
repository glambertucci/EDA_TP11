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
	void recieveTransaction(Transaction Tx);
	void checkTransaction(bool& ok, Transaction& Tx);
	void addTransaction(Transaction &Tx);
	void sendLastTransaction();

	void recieveBlock(Block block);
	void checkedBlock(bool& ok, Block& block);
	void addBlock(Block& block);


	bool isMyPublicKey(CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256>publicKey);
	CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256> getpkey(void) { return this->publicKey; }
	vector<byte> sign(string dataToSend);
	bool checkSignature(vector<byte> sig, string dataToSign, CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256> publicKey);
	vector <Transaction> getUTXO() { return this->UTXO; }

	void setNextNode(Node* node) { this->post = node; }
	void setPrevNode(Node* node) { this->prev = node; }
protected:
	Node * prev, *post;
	CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256> publicKey, privateKey;
	vector <Transaction> UTXO;
	stack<Block> blockchain;
	vector <Transaction> newTransactions;
	queue <Transaction> nonConfirmedTransactions;
	bool miner;
	Block actualBlock;
	Block nonConfirmedBlock;
};

