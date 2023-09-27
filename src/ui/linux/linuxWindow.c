#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
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

void WindowCreate()
{
    // set window attributes
    XSetWindowAttributes windowAttributes;
    windowAttributes.backing_store = Always;

    // create window
    Window window = XCreateWindow(wm_display, wm_root, 0, 0, 200, 200, 1, CopyFromParent, InputOutput, CopyFromParent, 0, NULL);

    // apply window attributes
    XChangeWindowAttributes(wm_display, window, CWBackingStore, &windowAttributes);

    // select events to listen to
    XSelectInput(wm_display, window, ExposureMask | KeyPressMask);


    // create graphics context
    GC gc = XCreateGC(wm_display, window, 0, NULL);
    
    // draw a blue rectangle
    XSetForeground(wm_display, gc, 0x00ff0000);
    XFillRectangle(wm_display, window, gc, 20, 20, 10, 10);

    XMapWindow(wm_display, window);
    
    // swap buffers
    XFlush(wm_display);

    // get events
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

    // clean up
    XFreeGC(wm_display, gc);

    XUnmapWindow(wm_display, window);
    XDestroyWindow(wm_display, window);
    XCloseDisplay(wm_display);

    return;
}