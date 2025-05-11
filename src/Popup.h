// Popup.h
#ifndef POPUP_H
#define POPUP_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>

class Popup : public Fl_Window {
public:
    Popup(int width, int height, const char* text, const char* title);
    static void close_callback(Fl_Widget* widget, void* data);
};

#endif // POPUP_H
