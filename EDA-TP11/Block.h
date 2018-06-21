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
	uint32_t getNumber() { return number; }
	uint32_t getTimeStamp() { return timestamp; }
	uint32_t getNonce() { return nonce; }

private:
	stack <Transaction> block;
	//CryptoPP::SHA256 previusBlock;
	uint32_t number;
	uint32_t timestamp;
	uint32_t nonce;
};

