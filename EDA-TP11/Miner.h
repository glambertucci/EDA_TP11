#pragma once
#include "Node.h"
class Miner :
	public Node
{
public:
	Miner() {
		this->miner = true;
		this->post = nullptr;
		this->prev = nullptr;
	}
	void recieveTransaction(Transaction Tx, CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256> publicKey);

	~Miner();
};

