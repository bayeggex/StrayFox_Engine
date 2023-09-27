#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>

#include "linuxWindow.h"

static Display *wm_display;
static int wm_screen;
static Window wm_root;

typedef struct LinuxWindow_t
{
    Window windowPointer;
} LinuxWindow;

void WindowManagerInit()
{
    // get display, screen and root window
    wm_display = XOpenDisplay(NULL);
    wm_screen = DefaultScreen(wm_display);
    wm_root = RootWindow(wm_display, wm_screen);
}

void WindowCreate(Window *window)
{
    // create window
    window = XCreateSimpleWindow(wm_display, wm_root, 0, 0, 200, 200, 1, BlackPixel(wm_display, wm_screen), WhitePixel(wm_display, wm_screen));

    // select input events
    XSelectInput(wm_display, window, ExposureMask | KeyPressMask);

    XMapWindow(wm_display, window);
    XFlush(wm_display);

    XEvent event;
    while (1)
    {
        XNextEvent(wm_display, &event);

        // print button names
        if (event.type == KeyPress)
        {
            if (event.xkey.keycode == XKeysymToKeycode(wm_display, XK_Escape))
            {
                break;
            }
        }
    }

    XUnmapWindow(wm_display, window);
    XDestroyWindow(wm_display, window);
    XCloseDisplay(wm_display);

    return;
}