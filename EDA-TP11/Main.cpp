#include "Drawer.h"
#include "Allegro/AllegroClassV2.h"
#include "Graph.h"

int main(int argc, char ** argv) 
{
	AllegroClassV2 allegro(Allegro::InitMode::Basic,2000,1800);
	//Parseo
	int nodesQuantity = 10;

	Graph web(nodesQuantity);
	vector<Node> nodes;
	web.shuffleNodes();
	web.get_nodes(nodes);
	Drawer drawer(nodes);
	drawer.Draw();
	allegro.updateDisplay();
	do{
		web.run();


	} while ();



	getchar();
}

