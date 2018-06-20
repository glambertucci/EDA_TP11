
#include "Allegro/AllegroWindow.h"
#include "Drawer.h"
#include "Allegro/AllegroClassV2.h"
#include "Allegro/AllegroFactory.h"
#include "Allegro/AllegroAddons.h"
#include "Allegro/WritableBox.h"

#include "Graph.h"

int main(int argc, char ** argv) 
{
	AllegroClassV2 allegro(Allegro::InitMode::Full,1900,1000,60);
	//Parseo
	int nodesQuantity = 10;

	Graph web(nodesQuantity);
	vector<Node> nodes;
	web.shuffleNodes();
	web.get_nodes(nodes);
	Drawer drawer(nodes);
	ALLEGRO_DISPLAY * mainDisp = al_get_current_display();
	AllegroDisplayFactory displayFactory;
	AllegroEventFactory eventFactory(allegro.getEventQueue());
	bool leave = false;

	WrittenBox makeTrans(0, 0, 200, 50, 20, "Make Transaction", "font.ttf", "black");
	makeTrans.TransformIntoButton("white", "green", 5);

	AllegroWindow transactionWindow(1000, 800,"Transaction Manager");

	WrittenBox TransactionNodeA(200, 100, 100, 50, 20, "Source", "font.ttf", "black");
	TransactionNodeA.TransformIntoButton("white", "black", 0);
	transactionWindow.addBox(TransactionNodeA);
	Node * nodeA = nullptr;

	WrittenBox TransactionNodeB(700, 100, 100, 50, 20, "Dest", "font.ttf","black");
	TransactionNodeB.TransformIntoButton("white", "black", 0);
	transactionWindow.addBox(TransactionNodeB);
	Node * nodeB = nullptr;

	WritableBox cash(KeyboardMode::Numeric, 450, 400, 20, 20, "font.ttf", "black");
	cash.setBackgroundColor("white");
	transactionWindow.addBox(cash);

	WrittenBox confirmTransaction(400, 600, 200, 100, 30, "confirm Transaction", "font.ttf", "black");
	confirmTransaction.TransformIntoButton("white", "black", 0);
	transactionWindow.addBox(confirmTransaction);


	while (!leave) {
		eventFactory.getEvent();
		switch (eventFactory.getEventType()) {
		case ALLEGRO_EVENT_TIMER:
			web.run();
			transactionWindow.setAsMain();
			transactionWindow.update();

			allegro.setMainDisplay();
			allegro.setDisplayColor("black");
			drawer.Draw();
			makeTrans.draw();
			drawer.DrawInformationWindows();
			allegro.updateDisplay();

			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if ((transactionWindow == eventFactory.getKeyboardEvent().display))
				cash.input(eventFactory.getKeyboardEvent());
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			ALLEGRO_MOUSE_EVENT mouse = eventFactory.getMouseEvent();
			if (mouse.display == mainDisp) {
				
				if (transactionWindow.isOpen() && TransactionNodeA.isPressed()) {
					nodeA = drawer.NodePressed(mouse.x, mouse.y)->node;
				}
				else if (transactionWindow.isOpen() && TransactionNodeB.isPressed()) {
					nodeB = drawer.NodePressed(mouse.x, mouse.y)->node;
				}
				else {
					void * temp = drawer.NodePressed(mouse.x, mouse.y);
					if (temp) {
						ALLEGRO_DISPLAY * tempDisp = displayFactory.create(500, 800, false);
						eventFactory.registerEventSource(al_get_display_event_source(tempDisp));
						drawer.createInformationWindow(tempDisp, temp);
					}
					else {
						if (makeTrans.checkIfPressed(mouse.x, mouse.y)) {
							transactionWindow.open();
							eventFactory.registerEventSource(transactionWindow.getEventSource());
						}
					}
				}
			}
			else if (transactionWindow == mouse.display) {
				TransactionNodeA.checkIfPressed(mouse.x, mouse.y);
				TransactionNodeB.checkIfPressed(mouse.x, mouse.y);
				confirmTransaction.checkIfPressed(mouse.x, mouse.y);
				if (confirmTransaction.isPressed() && nodeA != nullptr && nodeB != nullptr && cash.getText().size() > 0) {
					if (web.createTransaction(nodeA, nodeB, atoi(cash.getText().c_str()))) {
						eventFactory.unregisterEventSource(transactionWindow.getEventSource());
						transactionWindow.close();
						nodeA = nullptr;
						nodeB = nullptr;
					}
					else cout << "Not enough funds";
				}


			}
			else
				drawer.buttonPressed(mouse.x, mouse.y, mouse.display);
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			ALLEGRO_DISPLAY_EVENT display = eventFactory.getDisplayEvent();
			if (transactionWindow == display.source) {
				eventFactory.unregisterEventSource(transactionWindow.getEventSource());
				transactionWindow.close();
				nodeA = nullptr;
				nodeB = nullptr;
			}
			else if (display.source != mainDisp) {
				eventFactory.unregisterEventSource(al_get_display_event_source(display.source));
				drawer.closeInformationWindow(display.source);
			}
			else
				leave = true;
			break;
		}
	}



	
}

