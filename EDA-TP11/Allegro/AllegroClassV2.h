#pragma once
#include "AllegroAddons.h"

/*
IDEA :: Tengo un vector de una estructura llamada 'DATA'. DATA esta compuesta por un puntero a void y un int, que me indica que es.
		De esta forma puedo tener todo tipo de infomacion de manera dinamica.

IDEA :: Tengo generadores de Bitmaps, font, etc que se inicializan con shared pointers, cosa no hay que preocuparse por eliminarlos despues
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
};
