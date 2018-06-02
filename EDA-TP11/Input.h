#pragma once
#include <vector>

//#include "cryptopp/cryptlib.h"
//#include "cryptopp/osrng.h"
//#include "cryptopp/eccrypto.h"
//#include "cryptopp/oids.h"
//#include "cryptopp/hex.h"
//#include "cryptopp/sha3.h"


#include "Output.h"

using namespace std;

class Input
{
public:
	Input();
	//~Input();																						
private:
	OutputPointer * output;		// Creo que es un puntero al output.
	vector<byte> signature;												
																						
};


