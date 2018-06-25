#pragma once
#include "Allegro/AllegroWindow.h"
#include "Drawer.h"
#include "Allegro/WrittenBox.h"
#include "Node.h"
#include <chrono>

void getNodeForTransaction(Node** node, Drawer& drawer, AllegroWindow& transactionWindow, WrittenBox& transactionNode, ALLEGRO_MOUSE_EVENT& mouse);

void openWindow(AllegroWindow& window, AllegroEventFactory&eventFactory);

void closeWindow(AllegroWindow&window, AllegroEventFactory&eventFactory);

void doubleClick(Node** node, Drawer& drawer, AllegroWindow& transactionWindow, WrittenBox& transactionNode, ALLEGRO_MOUSE_EVENT& mouse, bool& pressedOnce);