#include "Drawer.h"



void setUpVertex(vector<float>& vertex);
bool notPlaced(vector<ALLEGRO_VERTEX>&vertex);
Drawer::Drawer(vector<Node>& nodes)
{
	srand(time(nullptr));
	for (Node& node : nodes)							// Creo los nodos
		setUpVertex(this->vertex);

	do {
		vector<unsigned int> replace;
		for (float& vertex1 : this->vertex){
			for (float& vertex2 : this->vertex) {
				if (sqrt(pow(vertex1.x - vertex2.x, 2) + pow(vertex1.y - vertex2.y, 2)) < DISTANCE_THRESHOLD) {
					vertex1.x = rand() % (int)al_get_display_width(al_get_current_display());
					vertex1.y = rand() % (int)al_get_display_height(al_get_current_display());
				}
			}
		}
	} while (notPlaced(this->vertex));
}

Drawer::~Drawer()
{
}

void Drawer::Draw()
{
	float * vert = new float[this->vertex.size()];
	for (int i = 0; i < this->vertex.size(); i++)
		vert[i] = this->vertex[i];

	al_draw_polygon(vert, this->vertex.size() / 2, ALLEGRO_LINE_JOIN_BEVEL, al_color_name("blue"), 10, 1.0);

	delete vert;
}

bool notPlaced(vector<ALLEGRO_VERTEX>&vertex) {
	bool retValue = false;

	for (ALLEGRO_VERTEX& node1 : vertex)
		for (ALLEGRO_VERTEX& node2 : vertex) {
			if (sqrt(pow(node1.x - node2.x, 2) + pow(node1.y - node2.y, 2)) < DISTANCE_THRESHOLD) {
				retValue = true;
				break;
			}
			if (retValue)
				break;
		}
	return retValue;
}

void setUpVertex(vector<float>& vertex) {
	vertex.push_back(rand() % (int)al_get_display_width(al_get_current_display()));		// X
	vertex.push_back(rand() % (int)al_get_display_height(al_get_current_display()));	// Y
}