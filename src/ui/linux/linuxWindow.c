#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>

#include "linuxWindow.h"

void LinuxWindowCreate()
{
    // get display, screen and root window
    Display *display = XOpenDisplay(NULL);
    int screen = DefaultScreen(display);
    Window root = RootWindow(display, screen);

    // create window
    Window window = XCreateSimpleWindow(display, root, 0, 0, 200, 200, 1, BlackPixel(display, screen), WhitePixel(display, screen));

    // select input events
    XSelectInput(display, window, ExposureMask | KeyPressMask);

    XMapWindow(display, window);
    XFlush(display);

    XEvent event;
    while (1)
    {
        XNextEvent(display, &event);

        // print button names
        if (event.type == KeyPress)
        {
            if (event.xkey.keycode == XKeysymToKeycode(display, XK_Escape))
            {
                break;
            }
        }
    }

    XUnmapWindow(display, window);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return;
}