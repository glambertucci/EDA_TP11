#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>


namespace Allegro {
	// Modos de inicializacion de allegro:
	// Modo Basic: Inicializa display,keyboard, Font, Primitives.
	// Modo Full: Inicializa todos los addons.
	// Modo Events: Inicializa lo mismo que el modo Basic pero agrega eventos, mouse y timer.
	// Modo Empty: Hay que inicializar todo manual luego de que se cree el objeto.
	enum class InitMode
	{
		Basic, Full, Events, Empty
	};

	const unsigned int NoValue = 0;
}

// Clase Padre de todos los addons, define los metodos para verificar que se instalaron con exito
class Addon {
public:
	bool getSuccess() { return success; }
protected:
	void initSuccess() { this->success = true; }
	bool success = false;
};





class ImageAddon : public Addon {
public:
	ImageAddon() { if (al_init_image_addon()) this->initSuccess(); }
	~ImageAddon() { al_shutdown_image_addon(); }
};





class AudioAddon : public Addon {
public:
	AudioAddon() { if (al_install_audio() && al_init_acodec_addon()) this->initSuccess(); }
	~AudioAddon() { al_uninstall_audio(); }
};





class FontAddon : public Addon {
public:
	FontAddon() { if (al_init_font_addon() && al_init_ttf_addon()) this->initSuccess(); }
	~FontAddon() { al_shutdown_font_addon(); al_shutdown_ttf_addon(); }
};





class KeyboardAddon : public Addon {
public:
	KeyboardAddon() { if (al_install_keyboard()) this->initSuccess(); }
	~KeyboardAddon() { al_uninstall_keyboard(); }
};





class DisplayAddon : public Addon {
public:
	DisplayAddon(float x = Allegro::NoValue, float y = Allegro::NoValue) {
		if (x != Allegro::NoValue && y != Allegro::NoValue)	display = al_create_display(x, y);
		if (x == Allegro::NoValue || y == Allegro::NoValue)	this->initSuccess();
		if (x != Allegro::NoValue && y != Allegro::NoValue && display != nullptr)	this->initSuccess();
	}

	void setDisplayColor(ALLEGRO_COLOR color) { al_clear_to_color(color); }
	void updateDisplay() { al_flip_display(); }

	ALLEGRO_DISPLAY * getDisplay() { return display; }
	~DisplayAddon() { if (display != nullptr) al_destroy_display(display); }
private:
	ALLEGRO_DISPLAY * display = nullptr;
};





class MouseAddon : public Addon {
public:
	MouseAddon() { if (al_install_mouse()) this->initSuccess(); }
	~MouseAddon() { al_uninstall_mouse(); }
};





class TimerAddon : public Addon {
public:
	TimerAddon() { this->initSuccess(); }
	TimerAddon(float fps) { if (refresh = al_create_timer(1 / fps)) this->initSuccess(); }
	ALLEGRO_TIMER * getRefreshTimer() { return refresh; }
	~TimerAddon() { if (refresh != nullptr) al_destroy_timer(refresh); }
private:
	ALLEGRO_TIMER * refresh = nullptr;		// Este timer se encarga de los fps de la pantalla
};





class PrimitivesAddon : public Addon {
public:
	PrimitivesAddon() { if (al_init_primitives_addon()) this->initSuccess(); }
	~PrimitivesAddon() { al_shutdown_primitives_addon(); }
};





class EventsAddon : public Addon {
public:
	EventsAddon() { if (eventQueue = al_create_event_queue()) this->initSuccess(); }

	void registerEventSource(MouseAddon * mouse) { al_register_event_source(eventQueue, al_get_mouse_event_source()); }
	void registerEventSource(KeyboardAddon * keyboard) { al_register_event_source(eventQueue, al_get_keyboard_event_source()); }
	void registerEventSource(DisplayAddon * display) { al_register_event_source(eventQueue, al_get_display_event_source(display->getDisplay())); }
	void registerEventSource(TimerAddon * timer) { al_register_event_source(eventQueue, al_get_timer_event_source(timer->getRefreshTimer())); }

	~EventsAddon() { if (eventQueue != nullptr) al_destroy_event_queue(eventQueue); }
private:
	ALLEGRO_EVENT_QUEUE * eventQueue = nullptr;
};