#pragma once
#include <vector>

//#include "cryptopp/cryptlib.h"
//#include "cryptopp/osrng.h"
//#include "cryptopp/eccrypto.h"
//#include "cryptopp/oids.h"
//#include "cryptopp/hex.h"
//#include "cryptopp/sha3.h"

using namespace std;

typedef struct OutputPointer {
	//CryptoPP::SHA256 HashID;		// Hash de la UTXO de donde saco la plata
	unsigned int position;			// Posicion del output en el UTXO de donde saco la plata

};


class Output
{
public:
	Output();
	~Output();
	vector<byte> getsig() { return this->signature; }
	double getgp() { return this->guiPesos; }
	string getstring() {
		string a; //Literalmente lo mas negro que existe
		a += guiPesos;
		for (int i = 0; i < signature.size(); i++)
			a += signature[i];
		return a;
	}
private:
	double guiPesos; 
	vector<byte> signature;

};


