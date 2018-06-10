#include "Transaction.h"
#include "Node.h"
#include <vector>
#define ERR -1



Transaction::Transaction()
{
}

int Transaction::addInput(Node& nod, int cash)
{
	unsigned int index = 0;
	vector<monl> cash_;
	int vuelto;
	do {
		monl temp = find(nod,(int)index);
		if (temp.money > 0)
		{
			cash_.push_back(temp);
			vuelto = sum(cash_) - cash;
			if (vuelto >= 0) {
				for (int i = 0; i < cash_.size(); i++) {
				
					Input temp_;
					temp_.output = find(nod, (unsigned int)index);
					temp_.signature = nod.sign(find(nod, index)->getGPString()); // CACA
					this->inputs.push_back(temp_);
				}
			}
		}
		index++;
	} while (sum(cash_) < cash);

	return vuelto;
}
void Transaction::addOutput(Node & nod, int cash)
{
	Output temp(nod.getpkey(), cash);
	this->outputs.push_back(temp);
}
Transaction::~Transaction()
{
}
int sum(vector<monl> casho) { //Suma toda la plata en el vector
	int temp = 0;
	for (monl& a : casho) {
		temp += a.money;
	}
	return temp;
}


bool hasFunds(Node& nod, int cash) {//Busca fondos en el vector de nodos hasta que me alcance para pagar la cuota del itba
	int mani = 0;
	bool funds = false;
	do {
		mani += find(nod.getpkey);
		if (mani > -1) break;
		if (mani >= cash)funds = true;
	} while (mani < cash);
	return funds;
}
monl find(Node& nod, int index) { //Find que devuelve monl;
	unsigned int a = 0;//Osea devuelve la plata y el lugar donde esta la plata
	monl retval = { ERR,ERR };
	for (Transaction& trans : nod.getUTXO())
	{
		if (trans.getoup().size() == 2)
		{
			Output out = trans.getoup()[0];

			if (nod.isMyPublicKey(out.getPublicKey()))
				if ((a++) == index)
					return { out.getGP(), index };
		}
	}
	return  retval;
}

int find(Node& nod) {//Find que devuelve solo plata
	unsigned int money = 0;
	for (Transaction & trans : nod.getUTXO()) {
		if (trans.getoup().size() == 2) {
			Output out = trans.getoup()[0];
			if (nod.isMyPublicKey(out.getPublicKey())) {
				money += out.getGP();
			}
		}
	}
	return money;
}
Output * find(Node& nod, unsigned int index) {
	unsigned int temp = 0;
	for (Transaction& trans : nod.getUTXO()) {
		if (trans.getoup().size() == 2) {
			Output out = trans.getoup()[0];
			if ((temp++) == index) {
				return &(trans.getoup()[0]);
			}
		}
	}
	return nullptr;
}