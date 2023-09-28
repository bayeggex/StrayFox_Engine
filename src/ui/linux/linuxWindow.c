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

    // new window
    Window window = XCreateWindow(wm_display, wm_root, 0, 0, 200, 200, 1, CopyFromParent, InputOutput, CopyFromParent, 0, NULL);

    // set WM_PROTOCOLS atom
    Atom wm_protocols = XInternAtom(wm_display, "WM_PROTOCOLS", False);
    Atom wm_delete_window = XInternAtom(wm_display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(wm_display, window, &wm_delete_window, 1);

    // apply window attributes
    XChangeWindowAttributes(wm_display, window, CWBackingStore, &windowAttributes);

    // select events to listen to
    XSelectInput(wm_display, window, ExposureMask | KeyPressMask);

    // create double buffer
    Pixmap buffer = XCreatePixmap(wm_display, window, 200, 200, DefaultDepth(wm_display, DefaultScreen(wm_display)));

    // new graphics context
    GC gc = XCreateGC(wm_display, window, 0, NULL);

    // clear window
    XClearWindow(wm_display, window);

    // draw a red circle
    XSetForeground(wm_display, gc, 0x00ff0000);
    XFillArc(wm_display, buffer, gc, 20, 20, 50, 50, 0, 360 * 64);

    // copy double buffer to window
    XCopyArea(wm_display, buffer, window, DefaultGC(wm_display, DefaultScreen(wm_display)), 0, 0, 200, 200, 0, 0);

    // map window
    XMapWindow(wm_display, window);

    // swap buffers
    XFlush(wm_display);

    // get events
    XEvent event;
    while (1)
    {
        XNextEvent(wm_display, &event);

        // handle events
        switch (event.type)
        {
        case Expose:
            // redraw window
            XCopyArea(wm_display, buffer, window, DefaultGC(wm_display, DefaultScreen(wm_display)), 0, 0, 200, 200, 0, 0);
            break;

        case KeyPress:
            if (event.xkey.keycode == XKeysymToKeycode(wm_display, XK_Escape))
                goto cleanup;
            break;

        case ClientMessage:
            if (event.xclient.message_type == wm_protocols && event.xclient.data.l[0] == (long)wm_delete_window)
                goto cleanup;
            break;
        }
    }

cleanup:
    // clean up
    XFreeGC(wm_display, gc);

    XUnmapWindow(wm_display, window);
    XDestroyWindow(wm_display, window);
    XCloseDisplay(wm_display);

    return;
}