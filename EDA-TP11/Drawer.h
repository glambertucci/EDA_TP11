#pragma once
#include <vector>
#include <math.h>
#include "Allegro/AllegroClassV2.h"
#include "Node.h"

#define DISTANCE_THRESHOLD (200)
#define X_MAX_THRESHOLD (200)
#define X_MIN_THRESHOLD (200)
#define Y_MAX_THRESHOLD (200)
#define Y_MIN_THRESHOLD (200)
#define RADIUS (25)
#define STROKE_SIZE (2)

using namespace std;

typedef struct GraficNode {
	Node * node;
	GraficNode * prev, * post;
	float x, y;
};

class Drawer
{
public:
	Drawer(vector<Node>& nodes);
	~Drawer();
	void Draw();
private:
	void linkVertexAndNode(vector<Node>&nodes);
	vector<GraficNode> GraficNodes;

};

