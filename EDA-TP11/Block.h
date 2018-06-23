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
	void setNonce(uint32_t nc) { this->nonce = nc; }
	void setTimeStamp(uint32_t ts) { this->timestamp = ts; }
	void setNumber(uint32_t num) { this->number = num; }
	void setHash(vector<byte> hs) { this->previusBlock = hs; }

private:
	stack <Transaction> block;
	vector<byte> previusBlock;
	uint32_t number;
	uint32_t timestamp;
	uint32_t nonce;
};

