#include "Node.h"



Node::Node(int a)
{
	this->num = a;
}


Node::~Node()
{
}

void Node::recieveTransaction(Transaction Tx)
{
	this->nonConfirmedTransactions.push(Tx);
}

void Node::recieveBlock(Block block)
{
	nonConfirmedBlock = block;
}

void Node::checkTransaction(bool & ok, Transaction & Tx)
{
	for (Input& input : Tx.inputs) {					
		ok = checkSignature(input.signature, input.output->getGPString(), input.output->getPublicKey());
		if (!ok)
			break;
	}
	if (ok) {
		addTransaction(Tx);
	}
}

void Node::addTransaction(Transaction & Tx)
{
	this->newTransactions.push_back(Tx);
}

void Node::sendLastTransaction()
{
	/*
		Esto va a funcionar de la siguiente forma, en el main solo van a crear transacciones mediante graph y van a verificarlas mediante checkTx
		NO SE VA A LLAMAR A RECIEVE TRANS EN EL MAIN
	*/

	if (this->newTransactions.size() > 0) {
		
		this->post->recieveTransaction(this->newTransactions[newTransactions.size() - 1]);
		this->prev->recieveTransaction(this->newTransactions[newTransactions.size() - 1]);
	}


}

Transaction * Node::getUncheckedTransaction()
{
	if (nonConfirmedTransactions.size() > 0)
		return &this->nonConfirmedTransactions.front();
	else
		return nullptr;
}

void Node::destroyTransacction()
{
	if (nonConfirmedTransactions.size() > 0)
		this->nonConfirmedTransactions.pop();
}

void Node::sendLastBlock()
{
	//blockTimestamp = chrono::high_resolution_clock::now();
	this->prev->recieveBlock(actualBlock);
	this->post->recieveBlock(actualBlock);
}

Block * Node::getUncheckedBlock()
{
	return &nonConfirmedBlock;
}

void Node::checkBlock(bool & ok, Block & block)
{
	bool TxOk = false;
	stack<Transaction> transactInBlock = block.getBlock();
	
	while (transactInBlock.size() != 0) {
		Transaction temp = transactInBlock.top();
		transactInBlock.pop();
		checkTransaction(TxOk, temp);
		if (!TxOk) {
			ok = false;
			return;
		}
	}
	if (ok)
		addBlock(block);
}

void Node::addBlock(Block & block)
{
	blockchain.push(block);
}

bool Node::isMyPublicKey(ECDSA<ECP, SHA256>::PublicKey publicKey)
{
	string hashCheck = "Guido sos re tonto";

	vector<byte> signature = this->sign(hashCheck);

	return this->checkSignature(signature,hashCheck,publicKey);
}

vector<byte> Node::sign(string dataToSign) {
	vector<byte> signature = getSignature(privateKey, dataToSign); 
	return signature;

}
bool Node::checkSignature(vector<byte> sig,string dataToSign, ECDSA<ECP, SHA256>::PublicKey publicKey)
{
	return verifySignature(publicKey, dataToSign, sig); 
}

void Node::setTransactionTimestamp()
{
	transactionTimestamp = chrono::high_resolution_clock::now();
}
