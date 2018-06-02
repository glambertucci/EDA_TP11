#include "Transaction.h"
#include "Node.h"
#include <vector>



Transaction::Transaction()
{
}

void Transaction::addInput(Node& nod, int cash)
{
	unsigned int index = 0;
	vector<monl> cash_;
	do {
		monl temp = find(nod.getpkey());
		if (temp.money > 0)
		{
			cash_.push_back(temp);
			if (sum(cash_) >= cash) {
				for (int i = 0; i < cash_.size(); i++) {
					this->inputs.push_back({findOutput(cash_[i],nod.getpkey()),nod.sign(findOutput()})//Deberia pasarle el string de no s eque pero ni idea y todo re tumach y demasiado ahre
				}
			}
		}
	} while (sum(cash_) < cash);
}
Transaction::~Transaction()
{
}
int sum(vector<monl> casho) {
	int temp=0;
	for (monl& a : casho) {
		temp += a.money;
	}
	return temp;
}


bool hasfunds(Node& nod, int mani) {
	int cash;
	bool funds = false;
	do {
		mani += find(nod.getpkey)());
					if (mani > -1) break;
					if (mani >= cash)funds = true;
	} while (mani < cash);
	return funds;
}

monl find(CryptoPP::ECDSA <CryptoPP::ECP, CryptoPP::SHA256>,) {

}