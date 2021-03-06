#include "TransactionHelper.h"
#define ERR -1

int sum(vector<monl> casho);
monl findMoneyIndex(Node& nod, int index);
int findOnlyMoney(Node& nod);
Output * findCorrectOutput(Node& nod, unsigned int index);



int addInput(Node& nod, Transaction &Tx, int cash)
{
	unsigned int index = 0;
	vector<monl> cash_;
	int vuelto=0;
	do {
		monl temp = findMoneyIndex(nod, (int)index);
		if (temp.money > 0)
		{
			cash_.push_back(temp);
			vuelto = sum(cash_) - cash;
			if (vuelto >= 0) {
				for (int i = 0; i < cash_.size(); i++) {
					Input temp_;
					temp_.output = findCorrectOutput(nod, (unsigned int)index);
					temp_.signature = nod.sign(findCorrectOutput(nod, index)->getGPString());
					Tx.inputs.push_back(temp_);
				}
			}
		}
		index++;
		break;
	} while (sum(cash_) < cash);
	return vuelto;
}

void addOutput(Node& nod, Transaction &Tx, int cash)
{
	Output temp(nod.getpkey(), cash);
	Tx.outputs.push_back(temp);
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
		mani += findOnlyMoney(nod);
		if (mani > -1) break;
		if (mani >= cash)funds = true;
	} while (mani < cash);
	if (nod.Guipesos >= cash)
		return true;
	return false;
}


monl findMoneyIndex(Node& nod, int index) { //Find que devuelve monl;
	unsigned int a = 0;//Osea devuelve la plata y el lugar donde esta la plata
	monl retval = { ERR,ERR };
	for (Transaction& trans : nod.getUTXO())
	{
		if (trans.getoup().size() == 2)
		{
			Output out = trans.getoup()[0];

			if (nod.isMyPublicKey(out.getPublicKey()))
				if ((a++) == index)
					return { (int)out.getGP(), index };
		}
	}
	return  retval;
}

int findOnlyMoney(Node& nod) {//Find que devuelve solo plata
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
Output * findCorrectOutput(Node& nod, unsigned int index) {
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