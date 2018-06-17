#pragma once
#include "Node.h"
#include "Transaction.h"
#include <vector>
#include "Input.h"
#include "Output.h"

int addInput(Node& nod, Transaction &Tx, int cash); // Devuelve el vuelto
void addOutput(Node& nod, Transaction &Tx, int cash);
bool hasFunds(Node& nod, int mani);

