#pragma once
#include <vector>

//#include "cryptlib.h"
//#include "osrng.h"
//#include "eccrypto.h"
//#include "oids.h"
//#include "hex.h"
//#include "sha3.h"
#include "Node.h"
#include "Input.h"
#include "Output.h"

using namespace std;
class Transaction
{
public:
	Transaction();
	int addInput(Node& nod, int cash); // Devuelve el vuelto
	void addOutput(Node& nod, int cash);
	vector <Input> getinp() { return this->inputs; }
	vector <Output> getoup() { return this->outputs; }
	~Transaction();
	/*CryptoPP::SHA256 hashID;*/
	vector <Input> inputs;
	vector <Output> outputs;
};
struct monl {
	int money;
	int index;
};

bool hasFunds(Node& nod, int mani);