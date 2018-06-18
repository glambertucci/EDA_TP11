#pragma once
#include <vector>
#include <math.h>
#include "Allegro/AllegroClassV2.h"
#include "Allegro/WrittenBox.h"
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
	ALLEGRO_BITMAP * image = nullptr;

};


typedef struct NodeInfo
{
	ALLEGRO_DISPLAY* display;
	GraficNode * graficNode;
	vector<shared_ptr<WrittenBox>> titles;
	vector<shared_ptr<WrittenBox>> values;
	~NodeInfo() { al_destroy_display(display); titles.clear(); values.clear(); }
};

class Drawer
{
public:
	Drawer(vector<Node>& nodes);
	~Drawer();
	//Carga de informacion de und determinado nodo a una pantalla
	void createInformationWindow(ALLEGRO_DISPLAY * displ, void * node);
	//Si se clickea sobre un nodo, esta funcion devuelve un puntero al nodo presionado
	GraficNode* NodePressed(int x, int y);
	// En el programa de verdad deberia devolver un puntero al nodo, o su public key, asi graph sabe todo. Lo mejor seria una estructura
	void buttonPressed(int x, int y, ALLEGRO_DISPLAY * displ);
	// Cierra una ventana de informacion dada su display
	void closeInformationWindow(ALLEGRO_DISPLAY * display);
	// Dibuja sobre la pantalla de inforamcion
	void DrawInformationWindows();
	// Actualiza los datos de la pantalla de inforamcion
	void updateInformationWindows();
	// Dibuja los nodos
	void Draw();
	
private:
	void loadAssets();
	void unloadAssets();
	void linkVertexAndNode(vector<Node>&nodes);
	vector<GraficNode> GraficNodes;
	vector <shared_ptr<NodeInfo>> windows;

};

