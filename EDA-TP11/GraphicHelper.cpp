#include "GraphicHelper.h"

void getNodeForTransaction(Node ** node, Drawer & drawer, AllegroWindow & transactionWindow, WrittenBox& transactionNode, ALLEGRO_MOUSE_EVENT& mouse)
{
	void * tt = drawer.NodePressed(mouse.x, mouse.y);
	if (tt != nullptr) {
			transactionWindow.removeDrawing(drawer.getNodeBitmap(*node));
			*node = drawer.NodePressed(mouse.x, mouse.y)->node;
			transactionWindow.addDrawing(drawer.getNodeBitmap(*node), transactionNode.getX()+150, transactionNode.getY(), 50, 50);
			transactionNode.unpressButton();
	}
}

void openWindow(AllegroWindow & window, AllegroEventFactory & eventFactory)
{
	window.open();
	eventFactory.registerEventSource(window.getEventSource());
}

void closeWindow(AllegroWindow & window, AllegroEventFactory & eventFactory)
{
	eventFactory.unregisterEventSource(window.getEventSource());
	window.close();
}

void doubleClick(Node ** node, Drawer & drawer, AllegroWindow & transactionWindow, WrittenBox & transactionNode, ALLEGRO_MOUSE_EVENT & mouse, bool & pressedOnce)
{
	static chrono::high_resolution_clock::time_point pointA;
	chrono::duration<float> duration = pointA - chrono::high_resolution_clock::now();
	if (pressedOnce && 0 <= duration.count() && (duration.count() * 1000) <= 1000) {
		getNodeForTransaction(node, drawer, transactionWindow, transactionNode, mouse);
		pressedOnce = false;
	}
	else {
		pointA = chrono::high_resolution_clock::now();
		pressedOnce = true;
	}

}
