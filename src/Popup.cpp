// Popup.cpp
#include "Popup.h"
#include <FL/Enumerations.H>
#include <iostream>
#include <string>


Popup::Popup(int width, int height, const char* text, const char* title) : Fl_Window(width, height, title) {
    // Create a box to display information
    Fl_Text_Display *text_display = new Fl_Text_Display(5, 5, width - 10, height - 40);
    text_display->buffer(new Fl_Text_Buffer());
    text_display->textsize(12); 

    text_display->color(FL_BACKGROUND_COLOR);
    text_display->buffer()->append(text);
    // Create a close button
    Fl_Button* close_button = new Fl_Button((width - 80) / 2, height - 25, 80, 20, "OK");
    close_button->labelsize(12);
    close_button->callback(close_callback, this); // Set the callback to close the popup



    end(); // Finalize the window
    set_modal();
    show();
}

void Popup::close_callback(Fl_Widget* widget, void* data) {
    Popup* popup = (Popup*)data;
    popup->hide(); // Hide the popup window
}
