#pragma once
#include <vector>


#include "Input.h"
#include "Output.h"

using namespace std;
class Transaction
{
public:
	Transaction();

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

