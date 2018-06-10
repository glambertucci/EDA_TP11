#pragma once
#include <vector>

//#include "cryptopp/cryptlib.h"
//#include "cryptopp/osrng.h"
//#include "cryptopp/eccrypto.h"
//#include "cryptopp/oids.h"
//#include "cryptopp/hex.h"
//#include "cryptopp/sha3.h"

using namespace std;


class Output
{
public:
	Output(CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256> publicKey, double guiPesos) { this->publicKey = publicKey; this->guiPesos = guiPesos; }
	Output();
	~Output();
	CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256> getPublicKey() { return this->publicKey; }
	double getGP() { return this->guiPesos; }
	string getGPString() { return to_string(guiPesos); }
private:
	double guiPesos; 
	CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256> publicKey;

};


