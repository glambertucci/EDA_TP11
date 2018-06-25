
#include "Allegro/AllegroWindow.h"
#include "Drawer.h"
#include "Allegro/AllegroClassV2.h"
#include "Allegro/AllegroFactory.h"
#include "Allegro/AllegroAddons.h"
#include "Allegro/WritableBox.h"
#include "GraphicHelper.h"

#include "Graph.h"

int main(int argc, char ** argv) 
{
	AllegroClassV2 allegro(Allegro::InitMode::Full,1300,1000,10);
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
	bool trueTransaction;

	WrittenBox makeTrans(0, 0, 300, 50, 20, "Make Transaction", "font.ttf", "black");
	makeTrans.TransformIntoButton("white", "green", 5);
	bool makeTransAPressedOnce = false;

	WrittenBox makeFakeTrans(al_get_display_width(al_get_current_display()) - 300, 0, 300, 50, 20, "Make Fake Transaction", "font.ttf", "black");
	makeFakeTrans.TransformIntoButton("white", "green", 5);
	bool makeFrakeTransPressedOnce = false;

	AllegroWindow transactionWindow(1000, 800,"Transaction Manager");

	WrittenBox TransactionNodeA(200, 100, 100, 50, 20, "Source", "font.ttf", "black");
	TransactionNodeA.TransformIntoButton("white", "black", 0);
	transactionWindow.addDrawing(TransactionNodeA.getBitmap(), TransactionNodeA.getX(), TransactionNodeA.getY());
	bool nodeAPressedOnce = false;
	Node * nodeA = nullptr;

	WrittenBox TransactionNodeB(700, 100, 100, 50, 20, "Dest", "font.ttf","black");
	TransactionNodeB.TransformIntoButton("white", "black", 0);
	transactionWindow.addDrawing(TransactionNodeB.getBitmap(), TransactionNodeB.getX(), TransactionNodeB.getY());
	Node * nodeB = nullptr;
	bool nodeBPressedOnce = false;

	WritableBox cash(KeyboardMode::Numeric, 300, 400, 20, 20, "font.ttf", "black");
	cash.setBackgroundColor("white");
	transactionWindow.addDrawing(cash.getBitmap(), cash.getX(), cash.getY());

	WrittenBox confirmTransaction(100, 600, 800, 100, 30, "confirm Transaction", "font.ttf", "black");
	confirmTransaction.TransformIntoButton("white", "black", 0);
	transactionWindow.addDrawing(confirmTransaction.getBitmap(), confirmTransaction.getX(), confirmTransaction.getY());


	while (!leave) {
		eventFactory.getEvent();
		switch (eventFactory.getEventType()) {
		case ALLEGRO_EVENT_TIMER:
			web.run();
			if (transactionWindow.isOpen()) {
				transactionWindow.setAsMain();
				transactionWindow.update();
			}
			
			allegro.setMainDisplay();
			allegro.setDisplayColor("black");
			drawer.Draw();
			makeTrans.draw();
			makeFakeTrans.draw();
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
				
				if (transactionWindow.isOpen() && TransactionNodeA.isPressed()) 
					getNodeForTransaction(&nodeA, drawer, transactionWindow, TransactionNodeA, mouse);
				else if (transactionWindow.isOpen() && TransactionNodeB.isPressed()) 
					getNodeForTransaction(&nodeB, drawer, transactionWindow, TransactionNodeB, mouse);
				else {
					void * temp = drawer.NodePressed(mouse.x, mouse.y);
					if (temp) {
						ALLEGRO_DISPLAY * tempDisp = displayFactory.create(500, 800, false);
						eventFactory.registerEventSource(al_get_display_event_source(tempDisp));
						drawer.createInformationWindow(tempDisp, temp);
					}
					else {
						if (makeTrans.checkIfPressed(mouse.x, mouse.y)) {
							trueTransaction = true;
							transactionWindow.setName("Transaction");
							openWindow(transactionWindow, eventFactory);
							makeTrans.unpressButton();
						}
						else if (makeFakeTrans.checkIfPressed(mouse.x, mouse.y)) {
							trueTransaction = false;
							transactionWindow.setName("Fake Transaction");
							openWindow(transactionWindow, eventFactory);
							makeFakeTrans.unpressButton();
						}
					}
				}
			}
			else if (transactionWindow == mouse.display) {
				TransactionNodeA.checkIfPressed(mouse.x, mouse.y);
				TransactionNodeB.checkIfPressed(mouse.x, mouse.y);
				confirmTransaction.checkIfPressed(mouse.x, mouse.y);
				if (confirmTransaction.isPressed()) {
					if (nodeA != nullptr && nodeB != nullptr && cash.getText().size() > 0) {
						if (web.createTransaction(nodeA, nodeB, atoi(cash.getText().c_str()), trueTransaction)) {
							transactionWindow.removeDrawing(drawer.getNodeBitmap(nodeA));
							transactionWindow.removeDrawing(drawer.getNodeBitmap(nodeB));
							transactionWindow.close();
							TransactionNodeB.unpressButton();
							TransactionNodeA.unpressButton();
							cash.clearText();
							nodeA = nullptr;
							nodeB = nullptr;
						}
						else cout << "not enough funds";
					}
					else
						confirmTransaction.unpressButton();
				}


			}
			else
				drawer.buttonPressed(mouse.x, mouse.y, mouse.display);
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			ALLEGRO_DISPLAY_EVENT display = eventFactory.getDisplayEvent();
			if (transactionWindow == display.source) {
				transactionWindow.removeDrawing(drawer.getNodeBitmap(nodeA));
				transactionWindow.removeDrawing(drawer.getNodeBitmap(nodeB));
				cash.clearText();
				TransactionNodeB.unpressButton();
				TransactionNodeA.unpressButton();
				nodeA = nullptr;
				nodeB = nullptr;
				closeWindow(transactionWindow, eventFactory);
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

