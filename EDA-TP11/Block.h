#pragma once
#include <cstdint>
#include <stack>

#include "Transaction.h"

using namespace std;
class Block
{
public:
	Block();
	~Block();
	stack <Transaction> getBlock() { return block; }
private:
	stack <Transaction> block;
	//CryptoPP::SHA256 previusBlock;
	uint32_t number;
	uint32_t timestamp;
	uint32_t nonce;
};

