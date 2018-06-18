#pragma once
#include "Node.h"
class FullService :
	public Node
{
public:
	FullService(int a) : Node(a){
		this->miner = true;
		this->post = nullptr;
		this->prev = nullptr;
	}
	~FullService(){}
};

