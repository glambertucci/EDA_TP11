#pragma once
#include <vector>
#include <math.h>
#include "AllegroClassV2.h"
#include "WrittenBox.h"
#include "Node.h"
#include <memory>
#include <chrono>

#define DISTANCE_THRESHOLD (200)
#define X_MAX_THRESHOLD (200)
#define X_MIN_THRESHOLD (200)
#define Y_MAX_THRESHOLD (200)
#define Y_MIN_THRESHOLD (200)
#define RADIUS (50)
#define STROKE_SIZE (2)

using namespace std;

typedef struct GraficNode {
	float x, y;
	GraficNode * prev, * post;

	Node * node;

};


typedef struct NodeInfo
{
	ALLEGRO_DISPLAY* display;
	GraficNode * node;
	vector<shared_ptr<WrittenBox>> titles;
	vector<shared_ptr<WrittenBox>> values;
	~NodeInfo() { al_destroy_display(display); titles.clear(); values.clear(); }
};

class Drawer
{
public:
	Drawer(vector<Node>& nodes);
	~Drawer();
	void createInformationWindow(ALLEGRO_DISPLAY * displ, void * node);
	GraficNode* NodePressed(int x, int y);
	// En el programa de verdad deberia devolver un puntero al nodo, o su public key, asi graph sabe todo. Lo mejor seria una estructura
	void buttonPressed(int x, int y, ALLEGRO_DISPLAY * displ);
	void closeInformationWindow(ALLEGRO_DISPLAY * display);
	void DrawInformationWindows();
	void updateInformationWindows();

	void Draw();
private:
	void linkVertexAndNode(vector<Node>&nodes);
	vector<GraficNode> GraficNodes;
	vector <shared_ptr<NodeInfo>> windows;

};

