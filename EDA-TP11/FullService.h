#pragma once
#include "Node.h"
class FullService :
	public Node
{
public:
	FullService(int a) : Node(a){
		this->miner = false;
		this->post = nullptr;
		this->prev = nullptr;
	}
	~FullService(){}
};

