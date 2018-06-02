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
	void recieveTransaction(Transaction Tx, CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256> publicKey);
	void recieveBlock(Block block, CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256> publicKey);
	void checkTransaction(bool& ok, Transaction& Tx);
	void checkedBlock(bool& ok, Block& block);
	void createTx();
	CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256> getpkey(void) { return this->publicKey; }
	vector<byte> sign(string dataToSend);
	bool checkSignature(vector<byte> sig, string dataToSign);
protected:
	Node * prev, *post;
	CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256> publicKey, privateKey;
	vector <Transaction> UTXO;
	stack<Block> blockchain;
	vector <Transaction> newTransactions;
	queue <Transaction> nonConfirmedTransactions;
	bool miner;
	Block actualBlock;
};

