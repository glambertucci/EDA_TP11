#pragma once
#include <vector>

#include "cryptopp/cryptlib.h"
#include "cryptopp/osrng.h"
#include "cryptopp/eccrypto.h"
#include "cryptopp/oids.h"
#include "cryptopp/hex.h"
#include "cryptopp/sha3.h"

using namespace std;
using namespace CryptoPP;

class Output
{
public:
	Output(ECDSA<ECP, SHA256>::PublicKey publicKey, double guiPesos) { this->publicKey = publicKey; this->guiPesos = guiPesos; }
	Output();
	~Output();
	ECDSA<ECP, SHA256>::PublicKey getPublicKey() { return this->publicKey; }
	double getGP() { return this->guiPesos; }
	string getGPString() { return to_string(guiPesos); }
private:
	double guiPesos; 
	ECDSA<ECP, SHA256>::PublicKey publicKey;

};


