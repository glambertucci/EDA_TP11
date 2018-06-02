#pragma once
#include <vector>

#include "Input.h"
#include "Output.h"

using namespace std;
class Transaction
{
public:
	Transaction();
	~Transaction();
private:
	SHA256 hashID;
	vector <Input> inputs;
	vector <Output> outputs;
};

