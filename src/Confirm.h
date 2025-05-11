
#ifndef CONFIRM_H
#define CONFIRM_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>

class Confirm : public Fl_Window {
public:
    Confirm(int width, int height, const char* text, const char* title);
    static void no_callback(Fl_Widget* widget, void* data);
    static void yes_callback(Fl_Widget* widget, void* data);
    bool showAndWait();
private:
    bool contiune = false;
};

#endif // POPUP_H
