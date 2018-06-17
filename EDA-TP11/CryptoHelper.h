#pragma once
#include "cryptopp/cryptlib.h"
#include "cryptopp/osrng.h"
#include "cryptopp/eccrypto.h"
#include "cryptopp/oids.h"
#include "cryptopp/hex.h"
#include "cryptopp/sha3.h"

#include <vector>

using namespace std;

using namespace CryptoPP;


ECDSA<ECP, SHA256>::PrivateKey generatePrivKey(void);
vector<byte> getSignature(ECDSA<ECP, SHA256>::PrivateKey &privKey, string &data);
bool verifySignature(ECDSA<ECP, SHA256>::PublicKey &pubKey, string &data, vector<byte> &signature);