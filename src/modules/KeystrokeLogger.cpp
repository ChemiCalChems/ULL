#include <QtWidgets/QLabel>
#include "../Module.hpp"
#include <iostream>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>


struct KeyLoggerModule : Module {
	QLabel keystrokeLabel, mousemovementLabel;
	unsigned long long keystrokes = 0;
	unsigned long long mouseMovements = 0;
	unsigned long long mouseClicks = 0;
	
	void run() {
		Display* display = XOpenDisplay(NULL);
		Window win;
		win = DefaultRootWindow(display);


		XIEventMask* m = new XIEventMask;
	
		/* Select for motion events */
		m->deviceid = XIAllMasterDevices;
		m->mask_len = XIMaskLen(XI_LASTEVENT);
		m->mask = (unsigned char*)calloc(m->mask_len, sizeof(char));
		/*
		  XISetMask(m->mask, XI_ButtonPress);
		  XISetMask(m->mask, XI_ButtonRelease);
		  XISetMask(m->mask, XI_KeyPress);
		  XISetMask(m->mask, XI_KeyRelease);
		  XISetMask(m->mask, XI_DeviceChanged);
		  XISetMask(m->mask, XI_Enter);
		  XISetMask(m->mask, XI_Leave);
		  XISetMask(m->mask, XI_FocusIn);
		  XISetMask(m->mask, XI_FocusOut);
		  XISetMask(m->mask, XI_TouchBegin);
		  XISetMask(m->mask, XI_TouchUpdate);
		  XISetMask(m->mask, XI_TouchEnd);
		  XISetMask(m->mask, XI_HierarchyChanged);
		  XISetMask(m->mask, XI_PropertyEvent);
		*/
		XISetMask(m->mask, XI_Motion);
		XISetMask(m->mask, XI_RawKeyPress);
		XISetMask(m->mask, XI_RawKeyRelease);
		
		XISetMask(m->mask, XI_RawButtonPress);
		XISetMask(m->mask, XI_RawButtonRelease);
		XISetMask(m->mask, XI_RawMotion);
				  
		XISelectEvents(display, win, m, 1);
	
		XSync(display, False);
		
		std::chrono::steady_clock::time_point lastMouseMotionEvent;
		bool isMouseMoving = false;
		while(true)	{
			XEvent ev;
			XGenericEventCookie *cookie = (XGenericEventCookie*)&ev.xcookie;
			if (XPending(display)) XNextEvent(display, (XEvent*)&ev);

			if (XGetEventData(display, cookie) && cookie->type == GenericEvent) {
				if (cookie->evtype == XI_RawKeyPress) {
					keystrokes++;
					keystrokeLabel.setText(QString("Keystrokes") + QString::number(keystrokes));
				}
				else if (cookie->evtype == XI_RawMotion) {
					lastMouseMotionEvent = std::chrono::steady_clock::now();
					isMouseMoving = true;
				}
				else if (cookie->evtype == XI_RawButtonPress) {
					mouseClicks++;
					keystrokeLabel.setText(QString("Mouse clicks: ") + QString::number(mouseClicks));
				}
			}

			if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastMouseMotionEvent).count() > 100 && isMouseMoving) {
				isMouseMoving = false;
				mouseMovements++;
				mousemovementLabel.setText(QString("Mouse movements: ") + QString::number(mouseMovements));
				std::cout << "mouseMovements: " << mouseMovements << std::endl;
			}

			XFreeEventData(display, cookie);
		}

		XDestroyWindow(display, win);
	}

	void launch() {
		thread = std::thread(&KeyLoggerModule::run, this);
	}

	KeyLoggerModule(QWidget* parent = 0) : keystrokeLabel(parent), mousemovementLabel(parent) {
		test = 0;
		keystrokeLabel.show();
		mousemovementLabel.show();
 	}
};

extern "C" Module* create(QWidget* parent) {return new KeyLoggerModule(parent);}
