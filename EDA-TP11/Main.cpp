#include "Drawer.h"
#include "Allegro/AllegroClassV2.h"
#include "Allegro/AllegroFactory.h"
#include "Allegro/AllegroAddons.h"
#include "Graph.h"

int main(int argc, char ** argv) 
{
	AllegroClassV2 allegro(Allegro::InitMode::Full,2700,1500,60);
	//Parseo
	int nodesQuantity = 10;

	Graph web(nodesQuantity);
	vector<Node> nodes;
	web.shuffleNodes();
	web.get_nodes(nodes);
	Drawer drawer(nodes);
	ALLEGRO_DISPLAY * mainDisp = al_get_current_display();
	AllegroDisplayFactory displayFactory;
	//AllegroKeyboardFactory keyboardFactory;
	bool leave = false;
	ALLEGRO_EVENT ev;
	
//	WritableBox *cash = keyboardFactory.createWritableBox(KeyboardMode::Numeric, 0, 0, 15, 10, "font.ttf", "white");

	while (!leave) {
		if (al_get_next_event(allegro.getEventQueue(), &ev)) {
			switch (ev.type) {
			case ALLEGRO_EVENT_TIMER:
				web.run();
				al_set_target_backbuffer(mainDisp);
				al_clear_to_color(al_color_name("black"));
				drawer.Draw();
				drawer.DrawInformationWindows();
				allegro.updateDisplay();
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
				//cash->input(ev);
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				if (ev.mouse.display == mainDisp) {
					void * temp = drawer.NodePressed(ev.mouse.x, ev.mouse.y);
					if (temp) {
						ALLEGRO_DISPLAY * tempDisp = displayFactory.create(500, 800, false);
						allegro.registerEventSource(tempDisp);
						drawer.createInformationWindow(tempDisp, temp);
					}
				}
				else
					drawer.buttonPressed(ev.mouse.x, ev.mouse.y, ev.mouse.display);
				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:

				if (ev.display.source != mainDisp) {
					allegro.unregisterEventSource(ev.display.source);
					drawer.closeInformationWindow(ev.display.source);
				}
				else
					leave = true;
				break;
			}
		}

	}



	
}

