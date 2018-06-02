#pragma once
#include <vector>

//#include "cryptlib.h"
//#include "osrng.h"
//#include "eccrypto.h"
//#include "oids.h"
//#include "hex.h"
//#include "sha3.h"

#include "Input.h"
#include "Output.h"

using namespace std;
class Transaction
{
public:
	Transaction();
	~Transaction();
private:
	/*CryptoPP::SHA256 hashID;*/
	vector <Input> inputs;
	vector <Output> outputs;
};

