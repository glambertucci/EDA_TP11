#include "Node.h"



Node::Node()
{
}


Node::~Node()
{
}

vector<byte>  Node::sign(string dataToSign) {
	/*Se firmar� un conjunto de datos de manera que cualquier usuario pueda verificar que la firma es v�lida*/
	vector<byte> signature = getSignature(this->privateKey, dataToSign); //Firmamos un mensaje con la private key generada.

}
bool Node::checkSignature(vector<byte> sig,string dataToSign)
{
	return  verifySignature(this->publicKey, dataToSign, sig); //Cualquier podr� chequear la validez de la firma (checksig=true)
}