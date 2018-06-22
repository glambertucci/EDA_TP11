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
