#pragma once
#include <vector>
#include <math.h>
#include "Allegro/AllegroClassV2.h"
#include "Node.h"

#define DISTANCE_THRESHOLD (50)

using namespace std;
class Drawer
{
public:
	Drawer(vector<Node>& nodes);
	~Drawer();
	void Draw();
private:
	vector<float> vertex;
};

