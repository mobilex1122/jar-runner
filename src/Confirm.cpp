#include "Confirm.h"
#include <FL/Enumerations.H>
#include <FL/Fl_Text_Display.H>



Confirm::Confirm(int width, int height, const char* text, const char* title) : Fl_Window(width, height, title) {
    // Create a box to display information
    contiune = false;

    Fl_Text_Display *text_display = new Fl_Text_Display(5, 5, width - 10, height - 40);
    text_display->buffer(new Fl_Text_Buffer());
    text_display->textsize(12);
    text_display->color(FL_BACKGROUND_COLOR);
    text_display->buffer()->append(text);
    text_display->wrap_mode(Fl_Text_Display::WRAP_AT_BOUNDS, 0);
    // Create a close button
    Fl_Button* no_button = new Fl_Button(5, height - 25, width / 2 - 10, 20, "No");
    no_button->labelsize(12);
    no_button->callback(no_callback, this); // Set the callback to close the popup


    Fl_Button* yes_button = new Fl_Button((width / 2) + 5, height - 25, width / 2 - 10, 20, "Yes");
    yes_button->labelsize(12);
    yes_button->callback(yes_callback, this);



    end(); // Finalize the window
    set_modal();
}

bool Confirm::showAndWait() {
    show();
    Fl::run();
    return contiune;
}

void Confirm::no_callback(Fl_Widget* widget, void* data) {
    Confirm* popup = (Confirm*)data;
    popup->contiune = false;
    popup->hide(); // Hide the popup window
}
void Confirm::yes_callback(Fl_Widget* widget, void* data) {
    Confirm* popup = (Confirm*)data;
    popup->contiune = true;

    popup->hide(); // Hide the popup window
}
