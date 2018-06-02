#include "AllegroClassV2.h"


AllegroClassV2::AllegroClassV2(Allegro::InitMode mode, float width, float height, float fps)
{
	if (al_init())
		this->success = true;

	switch (mode) {
	case Allegro::InitMode::Full:
		if (success)
			initAudioAddon();
		if (success)
			initImageAddon();
	case Allegro::InitMode::Events:
		if (success)
			initEventsAddon();
		if (success)
			initMouseAddon();
		if (success && fps == Allegro::NoValue)
			initTimerAddon();
		else if (success)
			initTimerAddon(fps);
	case Allegro::InitMode::Basic:
		if (success)
			initDisplayAddon(width, height);
		if (success)
			initKeyboardAddon();
		if (success)
			initFontAddon();
		if (success)
			initPrimitivesAddon();
	case Allegro::InitMode::Empty:
		break;
	}

	if (success && (mode == Allegro::InitMode::Full || mode == Allegro::InitMode::Events) )
		registerAllAvailableEventsSource();
}

AllegroClassV2::AllegroClassV2()
{
	if (al_init())
		this->success = true;
}

void AllegroClassV2::initImageAddon()
{
	if (imageAddon == nullptr) {
		this->imageAddon = new ImageAddon();
		this->success = imageAddon->getSuccess();
	}
}

void AllegroClassV2::initAudioAddon()
{
	if (audioAddon == nullptr) {
		this->audioAddon = new AudioAddon();
		this->success = audioAddon->getSuccess();
	}
}

void AllegroClassV2::initFontAddon()
{
	if (fontAddon == nullptr) {
		this->fontAddon = new FontAddon();
		this->success = fontAddon->getSuccess();
	}
}

void AllegroClassV2::initKeyboardAddon()
{
	if (keyboardAddon == nullptr) {
		this->keyboardAddon = new KeyboardAddon();
		this->success = keyboardAddon->getSuccess();
	}
}

void AllegroClassV2::initDisplayAddon(float x, float y)
{
	if (displayAddon == nullptr) {
		this->displayAddon = new DisplayAddon(x, y);
		this->success = displayAddon->getSuccess();
	}
}

void AllegroClassV2::initMouseAddon()
{
	if (mouseAddon == nullptr) {
		this->mouseAddon = new MouseAddon();
		this->success = mouseAddon->getSuccess();
	}
}

void AllegroClassV2::initEventsAddon()
{
	if (eventsAddon == nullptr) {
		this->eventsAddon = new EventsAddon();
		this->success = eventsAddon->getSuccess();
	}
}

void AllegroClassV2::initTimerAddon(float fps)
{
	if (this->timerAddon == nullptr) {
		this->timerAddon = new TimerAddon(fps);
		this->success = timerAddon->getSuccess();
	}
}

void AllegroClassV2::initTimerAddon()
{
	if (this->timerAddon == nullptr) {
		this->timerAddon = new TimerAddon();
		this->success = timerAddon->getSuccess();
	}
}

void AllegroClassV2::initPrimitivesAddon()
{
	if (primitivesAddon == nullptr) {
		this->primitivesAddon = new PrimitivesAddon();
		this->success = primitivesAddon->getSuccess();
	}
}

void AllegroClassV2::uninstallImageAddon()
{
	if (imageAddon != nullptr)
		delete imageAddon;
}

void AllegroClassV2::uninstallAudioAddon()
{
	if (audioAddon != nullptr)
		delete audioAddon;
}

void AllegroClassV2::uninstallFontAddon()
{
	if (fontAddon != nullptr)
		delete fontAddon;
}

void AllegroClassV2::uninstallKeyboardAddon()
{
	if (keyboardAddon != nullptr)
		delete keyboardAddon;
}

void AllegroClassV2::uninstallDisplayAddon()
{
	if (displayAddon != nullptr)
		delete displayAddon;
}

void AllegroClassV2::uninstallMouseAddon()
{
	if (mouseAddon != nullptr)
		delete mouseAddon;
}

void AllegroClassV2::uninstallEventsAddon()
{
	if (eventsAddon != nullptr)
		delete eventsAddon;
}

void AllegroClassV2::uninstallTimerAddon()
{
	if (timerAddon != nullptr)
		delete timerAddon;
}

void AllegroClassV2::uninstallPrimitivesAddon()
{
	if (primitivesAddon != nullptr)
		delete primitivesAddon;
}

void AllegroClassV2::registerAllAvailableEventsSource()
{
	if (eventsAddon != nullptr) {
		if (this->timerAddon != nullptr)
			eventsAddon->registerEventSource(timerAddon);
		if (this->keyboardAddon != nullptr)
			eventsAddon->registerEventSource(keyboardAddon);
		if (this->mouseAddon != nullptr)
			eventsAddon->registerEventSource(mouseAddon);
		if (this->displayAddon != nullptr)
			eventsAddon->registerEventSource(displayAddon);
	}
}

void AllegroClassV2::setDisplayColor(ALLEGRO_COLOR color)
{
	displayAddon->setDisplayColor(color);
}

void AllegroClassV2::setDisplayColor(const char * color)
{
	displayAddon->setDisplayColor(al_color_name(color));
}

void AllegroClassV2::updateDisplay()
{
	displayAddon->updateDisplay();
}


AllegroClassV2::~AllegroClassV2()
{
	this->uninstallImageAddon();
	this->uninstallAudioAddon();
	this->uninstallFontAddon();
	this->uninstallKeyboardAddon();
	this->uninstallDisplayAddon();
	this->uninstallMouseAddon();
	this->uninstallEventsAddon();
	this->uninstallTimerAddon();
	this->uninstallPrimitivesAddon();
}
