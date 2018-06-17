#include "Drawer.h"



void setUpVertex(vector<float>& vertex);
bool notPlaced(vector<float>& vertex);
Drawer::Drawer(vector<Node>& nodes)
{
	vector<float> vertex;
	srand(time(nullptr));
	linkVertexAndNode(nodes);
	for (Node& node : nodes)							// Creo los nodos
		setUpVertex(vertex);

	do {
		vector<unsigned int> replace;

		for (int i = 0; i+2 < vertex.size(); i+=2) {
			for (int a = 0; a+2 < vertex.size(); a+=2) {
				if (a != i) {
					if (sqrt(pow(vertex[i] - vertex[a], 2) + pow(vertex[i+1] - vertex[a+1], 2)) < DISTANCE_THRESHOLD) {
						vertex[i] = X_MIN_THRESHOLD + rand() % (int)(al_get_display_width(al_get_current_display()) - X_MAX_THRESHOLD - X_MIN_THRESHOLD);
						vertex[i+1] = Y_MIN_THRESHOLD + rand() % (int)(al_get_display_height(al_get_current_display()) - Y_MAX_THRESHOLD - Y_MIN_THRESHOLD);
					}
				}
			}
		}
	} while (notPlaced(vertex));

	int index = 0;

	for (GraficNode & gfNode : GraficNodes) {
		gfNode.x = vertex[index];
		gfNode.x = vertex[index+1];
		index += 2;
	}
}

Drawer::~Drawer()
{
}

void Drawer::Draw()
{
	for (GraficNode& gfNode : GraficNodes) {
		al_draw_line(gfNode.x, gfNode.y, gfNode.post->x, gfNode.post->y, al_color_name("blue"), 1.0);
	}
	for (GraficNode& gfNode : GraficNodes) {
		al_draw_filled_circle(gfNode.x, gfNode.y, RADIUS, al_color_name("hotpink"));
	}
	//float * vert = new float[this->vertex.size()];
	//for (int i = 0; i < this->vertex.size(); i++)
	//	vert[i] = this->vertex[i];

	//al_draw_polygon(vert, this->vertex.size() / 2, ALLEGRO_LINE_JOIN_BEVEL, al_color_name("blue"), STROKE_SIZE, 1.0);

	//for (int i = 0; i + 2<= this->vertex.size(); i += 2)
	//	al_draw_filled_circle(vert[i], vert[i + 1], RADIUS, al_color_name("hotpink"));

	//delete vert;
}

void Drawer::linkVertexAndNode(vector<Node>& nodes)
{
	for (Node& node : nodes) {
		GraficNode temp;
		temp.node = &node;
		temp.x = 0;
		temp.y = 0;
		temp.post = nullptr;
		temp.prev = nullptr;
	}

	for (GraficNode& gfNode : GraficNodes) {
		for (Node& node : nodes) {
			Node * temp = gfNode.node->getNextNode();
			int index = 0;
			while (!temp->isMyPublicKey(nodes[index++].getpkey()));
			gfNode.post = &GraficNodes[index];
		}
	}
	for (GraficNode& gfNode : GraficNodes) {
		for (Node& node : nodes) {
			Node * temp = gfNode.node->getPrevNode();
			int index = 0;
			while (!temp->isMyPublicKey(nodes[index++].getpkey()));
			gfNode.post = &GraficNodes[index];
		}
	}

}

bool notPlaced(vector<float>& vertex) {
	bool retValue = false;

	for (int i = 0; i + 2 < vertex.size(); i += 2) {
		for (int a = 0; a + 2 < vertex.size(); a += 2) {
			if (a != i) {
				if (sqrt(pow(vertex[i] - vertex[a], 2) + pow(vertex[i + 1] - vertex[a + 1], 2)) < DISTANCE_THRESHOLD) {
					retValue = true;
					break;
				}
			}
		}
		if (retValue)
			break;
	}
	return retValue;
}

void setUpVertex(vector<float>& vertex) {
	vertex.push_back(X_MIN_THRESHOLD + rand() % (int)(al_get_display_width(al_get_current_display()) - X_MAX_THRESHOLD - X_MIN_THRESHOLD));		// X
	vertex.push_back(Y_MIN_THRESHOLD + rand() % (int)(al_get_display_height(al_get_current_display()) - Y_MAX_THRESHOLD - Y_MIN_THRESHOLD));	// Y
}