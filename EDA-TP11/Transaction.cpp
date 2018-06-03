#include "Transaction.h"
#include "Node.h"
#include <vector>
#define ERR -1


Transaction::Transaction()
{
}

void Transaction::addInput(Node& nod, int cash)
{
	unsigned int index = 0;
	vector<monl> cash_;
	do {
		monl temp = find(nod,(int)index++);
		if (temp.money > 0)
		{
			cash_.push_back(temp);
			if (sum(cash_) >= cash) {
				for (int i = 0; i < cash_.size(); i++) {
					this->inputs.push_back({ find(nod,(unsigned int)cash_[i].index), });//Deberia pasarle el string de no s eque pero ni idea y todo re tumach y demasiado ahre
				}
			}
		}
	} while (sum(cash_) < cash);
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


bool hasfunds(Node& nod, int cash) {//Busca fondos en el vector de nodos hasta que me alcance para pagar la cuota del itba
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

			if (nod.checkSignature(out.getsig(), out.getstring()))
				if ((a++) == index)
					return { out.getgp(), index };
		}
	}
	return  retval;
}

int find(Node& nod) {//Find que devuelve solo plata
	unsigned int money = 0;
	for (Transaction & trans : nod.getUTXO()) {
		if (trans.getoup().size() == 2) {
			Output out = trans.getoup()[0];
			if (nod.checkSignature(out.getsig(), out.getstring())) {
				money += out.getgp();
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