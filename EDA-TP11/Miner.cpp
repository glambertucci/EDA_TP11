#include "Miner.h"

void Miner::mining(Transaction Tx, CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256> publicKey)
{
	string toHash = to_string(actualBlock.getNumber()) + to_string(actualBlock.getTimeStamp()) + to_string(actualBlock.getNonce());
	stack <Transaction> txStack = actualBlock.getBlock();
	for(int i = 0 ; i <(txStack.size()); i++)
	{
		toHash += to_string((txStack.top());
	}

}

Miner::~Miner()
{
}
