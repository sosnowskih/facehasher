/**
 * gui.cpp
 * CS 201
 * Henryk Sosnowski and Bryan Beus
 * October 12, 2019
 * Outputs data for facehasher into a GUI display
 */

#include "facehasher.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/FL_JPEG_Image.H>
#include <FL/Fl_Shared_Image.H>

#pragma comment(lib, "fltk.lib")
#pragma comment(lib, "fltk_images.lib")
#pragma comment(lib, "libpng16.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "comctl32.lib")


void OnCloseCallback(Fl_Widget* w, void* data) {
	Fl_Window* window = (Fl_Window*)data;
	if (window) window->hide();
}

void CameraCallback(Fl_Widget* w, void* data) {
	image_capture();
	Fl_Box* imgbox = (Fl_Box*)data;
	imgbox->redraw();

	Fl_JPEG_Image* image = new Fl_JPEG_Image("image.jpg");
	imgbox->image(image);
}


int main(int argc, char** argv) {
	fl_register_images();
	Fl_Window* window = new Fl_Window(1240, 640, "Facehasher");

	const int ControlHeight = 25;

	Fl_JPEG_Image* image = new Fl_JPEG_Image("image.jpg");
	Fl_Box* imgbox = new Fl_Box(20, 10, 700, 500);
	imgbox->image(image);


	Fl_Box* box = new Fl_Box(720, 40, 370, 70, "Press any key to take a Picture.");
	box->box(FL_UP_BOX);
	box->labelfont(FL_BOLD + FL_ITALIC);
	box->labelsize(24);
	box->labeltype(FL_SHADOW_LABEL);


	Fl_Button* camBtn = new Fl_Button(720, 120, 250, ControlHeight, "Take Picture");
	camBtn->callback(CameraCallback, (void*)imgbox);


	Fl_Button* closeBtn = new Fl_Button(720, 200, 250, ControlHeight, "Close Window");
	closeBtn->callback(OnCloseCallback, (void*)window);


	window->end();
	window->show(argc, argv);
	return Fl::run();
}
