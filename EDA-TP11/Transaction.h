#pragma once
#include <vector>

#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>
#include <cryptopp/eccrypto.h>
#include <cryptopp/oids.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha3.h>

#include "Input.h"
#include "Output.h"

using namespace std;
class Transaction
{
public:
	Transaction();
	void addInput(Node& nod, int cash);
	void addOutput(Node& nod, int cash);
	~Transaction();
private:
	CryptoPP::SHA256 hashID;
	vector <Input> inputs;
	vector <Output> outputs;
};
struct monl {
	int money;
	int index;
};

bool hasfunds(Node& nod, int mani);