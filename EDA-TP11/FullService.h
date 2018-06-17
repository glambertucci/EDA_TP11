#pragma once
#include "Node.h"
class FullService :
	public Node
{
public:
	FullService() {
		this->miner = true;
		this->post = nullptr;
		this->prev = nullptr;
	}
	~FullService(){}
};

