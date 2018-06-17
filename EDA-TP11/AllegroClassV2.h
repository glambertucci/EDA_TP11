#pragma once
#include "AllegroAddons.h"
#include "AllegroFactory.h"


/*
		Tengo que hacer un helper de eventos para desligar a la clase allegro de todo esto
*/

class AllegroClassV2
{
public:
	// Constructor Automatizado: le podes ingresar un modo y otros valores para olvidarte de la inicializacion de allegro.
	AllegroClassV2(Allegro::InitMode mode, float width = Allegro::NoValue, float height = Allegro::NoValue, float fps = Allegro::NoValue);
	// Constructor manual, solo inicializa allegro, si queres inicializar otro addon, hacelo a mano con las funciones que ofrece la clase.
	AllegroClassV2();
	// Destructor: elimina todo lo que se haya creado dinamicamente.
	~AllegroClassV2();


	// Funciones de Events
	void registerAllAvailableEventsSource();						// Se fija los Addons instalados y registra las event sources de estos
	void registerEventSource(ALLEGRO_VIDEO * video);
	void registerEventSource(ALLEGRO_DISPLAY *disp);
	void registerEventSource(ALLEGRO_TIMER * timer);

	void unregisterEventSource(ALLEGRO_VIDEO * video);
	void unregisterEventSource(ALLEGRO_DISPLAY *disp);
	void unregisterEventSource(ALLEGRO_TIMER * timer);

	ALLEGRO_EVENT_QUEUE * getEventQueue();

	// Funciones de Display
	void setDisplayColor(ALLEGRO_COLOR color);
	void setDisplayColor(const char * color);
	void updateDisplay();


	// instaladores
	void initImageAddon();
	void initAudioAddon();
	void initFontAddon();
	void initKeyboardAddon();
	void initDisplayAddon(float x = Allegro::NoValue, float y = Allegro::NoValue);						// Inicializa el display, si no se le pasan argumentos, no hace nada.
	void initMouseAddon();
	void initEventsAddon();
	void initTimerAddon(float fps);									// Inicializa al timer con un timer de refreshrate para la pantalla
	void initTimerAddon();											// Lo hace sin craer ningun timer
	void initPrimitivesAddon();
	void initVideoAddon();

	// eliminadores
	void uninstallImageAddon();
	void uninstallAudioAddon();
	void uninstallFontAddon();
	void uninstallKeyboardAddon();
	void uninstallDisplayAddon();
	void uninstallMouseAddon();
	void uninstallEventsAddon();
	void uninstallTimerAddon();
	void uninstallPrimitivesAddon();
	void uninstallVideoAddon();
private:
	bool success = false;

	// Addons de allegro
	ImageAddon * imageAddon = nullptr;
	AudioAddon * audioAddon = nullptr;
	FontAddon * fontAddon = nullptr;
	KeyboardAddon * keyboardAddon = nullptr;
	DisplayAddon * displayAddon = nullptr;
	MouseAddon * mouseAddon = nullptr;
	EventsAddon * eventsAddon = nullptr;
	TimerAddon * timerAddon = nullptr;
	PrimitivesAddon * primitivesAddon = nullptr;
	VideoAddon * videoAddon = nullptr;
};
