#include "Drawer.h"



void setUpVertex(vector<float>& vertex);
bool notPlaced(vector<float>& vertex);
Drawer::Drawer(vector<Node>& nodes)
{


	vector<float> vertex;
	srand(time(nullptr));
	linkVertexAndNode(nodes);
	for (Node& node : nodes) 
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
		gfNode.y = vertex[index+1];
		index += 2;
	}
	this->loadAssets();
}

Drawer::~Drawer()
{
	this->unloadAssets();
	this->windows.clear();
	this->GraficNodes.clear();
}

void Drawer::createInformationWindow(ALLEGRO_DISPLAY * displ, void * node)
{
	shared_ptr<NodeInfo> temp(new NodeInfo);
	temp->display = displ;
	temp->graficNode = (GraficNode *)node;
	
	float w = al_get_display_width(displ), h = al_get_display_height(displ);
	float xOffset = 20;
	float yOffset = 50;
	int i = -1;
	float boxHeight = 50;
	shared_ptr<WrittenBox> PublicKey(new WrittenBox(xOffset, yOffset * (i += 2), w - xOffset * 2, boxHeight, 15, "Private Key:", "font.ttf", "white"))
		, PrivateKey(new WrittenBox(xOffset, yOffset * (i += 2), w - xOffset * 2, boxHeight, 15, "Public Key:", "font.ttf", "white"))
		, NodeType(new WrittenBox(xOffset, yOffset * (i += 2), w - xOffset * 2, boxHeight, 15, "Node Type:", "font.ttf", "white"))
		, Money(new WrittenBox(xOffset, yOffset * (i += 2), w - xOffset * 2, boxHeight, 15, "Money:", "font.ttf", "white"))
		, Transacction(new WrittenBox(xOffset, yOffset * (i += 2), w - xOffset * 2, boxHeight, 15, "Make Transaction", "font.ttf", "white"))
		, FakeTransaction(new WrittenBox(xOffset, yOffset * (i += 2), w - xOffset * 2, boxHeight, 15, "Make Fake Transaction", "font.ttf", "white"));

	Transacction->TransformIntoButton("green", nullptr, 0);
	temp->titles.push_back(PrivateKey);
	temp->titles.push_back(PublicKey);
	temp->titles.push_back(NodeType);
	temp->titles.push_back(Money);
	temp->titles.push_back(Transacction);
	temp->titles.push_back(FakeTransaction);
	i = 0;

	//shared_ptr<WrittenBox> PublicKeyValue(new WrittenBox(xOffset, yOffset * (i += 2), w - xOffset * 2, boxHeight, 15, to_string(temp->graficNode->node->getpkey()), "font.ttf", "white"))
	shared_ptr<WrittenBox> PublicKeyValue(new WrittenBox(xOffset, yOffset * (i += 2), w - xOffset * 2, boxHeight, 15, to_string(temp->graficNode->node->getNum()), "font.ttf", "white")) //DEBUG
		, PrivateKeyValue(new WrittenBox(xOffset, yOffset * (i += 2), w - xOffset * 2, boxHeight, 15, "", "font.ttf", "white"))
		, nodeTypeValue(new WrittenBox(xOffset, yOffset * (i += 2), w - xOffset * 2, boxHeight, 15, "Miner", "font.ttf", "white"))
		, MoneyValue(new WrittenBox(xOffset, yOffset * (i += 2), w - xOffset * 2, boxHeight, 15, "0", "font.ttf", "white"))
		;
	temp->values.push_back(PublicKeyValue);
	temp->values.push_back(PrivateKeyValue);
	temp->values.push_back(nodeTypeValue);
	temp->values.push_back(MoneyValue);

	this->windows.push_back(temp);
}

GraficNode * Drawer::NodePressed(int x, int y)
{
	for (GraficNode& gfNode : GraficNodes) {
		if (RADIUS >= sqrt((gfNode.x - x)*(gfNode.x - x) + (gfNode.y - y)*(gfNode.y - y)))
			return &gfNode;
	}
	return nullptr;
}

void Drawer::buttonPressed(int x, int y, ALLEGRO_DISPLAY * displ)
{
	//for (shared_ptr<NodeInfo>& nodeInfo : this->windows) {
	//	for (shared_ptr < WrittenBox > &wbox : nodeInfo->titles) {
	//		if (wbox->checkIfPressed(x, y) && displ == nodeInfo->display)
	//			//nodeInfo->graficNode->node->createTrans();
	//	}
	//}
}

void Drawer::closeInformationWindow(ALLEGRO_DISPLAY * display)
{
	for (int i = 0; i < windows.size(); i++) {
		if (windows[i]->display == display) {
			windows.erase(windows.begin() + i);
			break;
		}
	}
}

void Drawer::Draw()
{
	for (GraficNode& gfNode : GraficNodes) {
		al_draw_line(gfNode.x, gfNode.y, gfNode.post->x, gfNode.post->y, al_color_name("blue"), 3.0);
	}

	/// NO BORRAR EL CODIGO COMENTADO DE ESTA FUNCION


	//for (GraficNode& gfNode : GraficNodes) {
	//	//chrono::duration<float> timePassed = std::chrono::high_resolution_clock::now() - gfNode.node->getTransactionTimeStamp();
	//	//if ((timePassed.count() * 1000) > 0 && (timePassed.count() * 1000) <= (3 * 1000 * 1000)) {
	//		//float increaseFactor = timePassed.count() * 1000;

	//		//increaseFactor = ((-8 * increaseFactor) / (3000.0)) + 8;


	//		//al_draw_line(gfNode.x, gfNode.y, gfNode.post->x, gfNode.post->y, al_color_name("green"), 3.0 + increaseFactor);
	//		//al_draw_line(gfNode.x, gfNode.y, gfNode.prev->x, gfNode.prev->y, al_color_name("green"), 3.0 + increaseFactor);

	//	}
	//}

	for (GraficNode& gfNode : GraficNodes) {
		al_draw_scaled_bitmap(gfNode.image, 0, 0, al_get_bitmap_width(gfNode.image), al_get_bitmap_height(gfNode.image), gfNode.x - RADIUS, gfNode.y - RADIUS, 2 * RADIUS, 2 * RADIUS, 0);
		//al_draw_filled_circle(gfNode.x, gfNode.y, RADIUS, al_color_name("hotpink"));
	}

	//for (GraficNode& gfNode : GraficNodes) {

	//	chrono::duration<float> timePassed = std::chrono::high_resolution_clock::now() - gfNode.node->getTransactionTimeStamp();
	//	if ((timePassed.count() * 1000) > 0 && (timePassed.count() * 1000) <= (3 * 1000 * 1000)) {
	//		float increaseFactor = timePassed.count() * 1000;

	//		increaseFactor = ((-15 * increaseFactor) / (3000.0)) + 15;


	//		al_draw_filled_circle(gfNode.x, gfNode.y, RADIUS + increaseFactor, al_color_name("hotpink"));

	//	}
	//	
	//}
}

void Drawer::loadAssets()
{
	for (int i = 1; i <= this->GraficNodes.size(); i++) {
		string file = "Faces/" + to_string(i) + ".jpg";
		GraficNodes[i - 1].image = al_load_bitmap(file.c_str());
 	}
}

void Drawer::unloadAssets()
{
	for (GraficNode& node : GraficNodes) 
		al_destroy_bitmap(node.image);
}

void Drawer::DrawInformationWindows()
{
	ALLEGRO_DISPLAY * main = al_get_current_display();
	updateInformationWindows();

	for (shared_ptr< NodeInfo>& nodeInfo : this->windows) {
		al_set_target_backbuffer(nodeInfo->display);
		al_clear_to_color(al_color_name("black"));

		for (shared_ptr<WrittenBox>& wbox : nodeInfo->titles)
			wbox->draw();
		for (shared_ptr<WrittenBox>& wbox : nodeInfo->values)
			wbox->draw();
		al_flip_display();
	}
	al_set_target_backbuffer(main);
}

void Drawer::updateInformationWindows()
{
	for (shared_ptr< NodeInfo>& nodeInfo : this->windows) {
		string publicKey = to_string(nodeInfo->graficNode->node->getNum());  //DEBUG
		string OldPublickKey = nodeInfo->values[0]->getText();
		if (publicKey.compare(OldPublickKey))
			nodeInfo->values[0]->setText(publicKey);
		// Hay que hacer lo mismo para todo lo demas, pero no tengo las funciones aca.
	}
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
		this->GraficNodes.push_back(temp);
	}

	for (GraficNode& gfNode : GraficNodes) {
		
			Node * temp = gfNode.node->getNextNode();
			int index = 0;
			//while (!temp->isMyPublicKey(nodes[index].getpkey()))//DEBUG
			while (!temp->isMyNum(nodes[index].getNum()))
			{
				index++;
			};
			gfNode.post = &GraficNodes[index];
	}
	for (GraficNode& gfNode : GraficNodes) {
			Node * temp = gfNode.node->getPrevNode();
			int index = 0;
			//while (!temp->isMyPublicKey(nodes[index].getpkey())) {//DEBUG
			while (!temp->isMyNum(nodes[index].getNum())){
				index++;
			};
			gfNode.prev = &GraficNodes[index];
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