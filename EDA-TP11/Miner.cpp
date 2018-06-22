#include "Miner.h"

void Miner::mining(Transaction Tx, CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256> publicKey)
{
	//string toHash = actualBlock.getNumber() + actualBlock.getTimeStamp() + actualBlock.getNonce();
	//stack <Transaction> txStack = actualBlock.getBlock();
	//for(int i = 0 ; i <(txStack.size()); i++)
	//{
	//	toHash += to_string((txStack.top()).hashI);
	//}

}

Miner::~Miner()
{
}
