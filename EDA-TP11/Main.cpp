#include "Drawer.h"
#include "Allegro/AllegroClassV2.h"

int main(int argc, char ** argv) 
{
	AllegroClassV2 allegro(Allegro::InitMode::Basic,2000,1800);

	vector<Node> nodes;

	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());
	nodes.push_back(Node());

	Drawer drawer(nodes);

	drawer.Draw();
	allegro.updateDisplay();

	getchar();
}

