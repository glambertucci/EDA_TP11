#pragma once
#include <vector>

#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>
#include <cryptopp/eccrypto.h>
#include <cryptopp/oids.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha3.h>
#include <memory>
using namespace std;

typedef struct OutputPointer {
	CryptoPP::SHA256 HashID;		// Hash de la UTXO de donde saco la plata
	unsigned int position;			// Posicion del output en el UTXO de donde saco la plata

};


class Output
{
public:
	Output();
	~Output();
private:
	double guiPesos; 
	vector<byte> signature;
};

