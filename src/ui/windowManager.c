#include "windowManager.h"

#include <stdio.h>

Window wm_windows[WM_MAX_WINDOWS];
static unsigned int wm_windowCount = 0;

Window *wm_init(int width, int height, const char *title)
{
    // init functions
    
    // create first window
    wm_createWindow(width, height, title);
    
    // give user full acces to all windows
    return &wm_windows[0];
}

void wm_createWindow(int width, int height, const char *title)
{
    // check window count
    if (wm_windowCount >= WM_MAX_WINDOWS)
    {
        printf("error: cannot create window, window count exceeded\n");
        return;
    }

    // easier access to the window
    Window *window = &wm_windows[wm_windowCount];

    // set early attributes

    // create handle

    // check handle
    if (window->handle == NULL)
    {
        printf("error: cannot create window\n");
        return;
    }

    // set late attributes

    // assign id
    static unsigned int LastId = 0;
    window->id = LastId++;
    
    // increase window count
    wm_windowCount++;

    return;
}

Window *wm_getWindowByID(unsigned int id)
{
    for (int i = 0; i < wm_windowCount; i++)
        if (wm_windows[i].id == id)
            return &wm_windows[i];
    return NULL;
}

void wm_destroyWindow(int index)
{
    // destroy handle
    glfwDestroyWindow(wm_windows[index].handle);
    // move the last window to the index of the destroyed window
    // to not leave a gap in the array
    wm_windows[index] = wm_windows[wm_windowCount - 1];
    wm_windowCount--;
}

void wm_destroyAllWindows()
{
    for (int i = 0; i < wm_windowCount; i++)
        wm_destroyWindow(i);
}

void wm_pollEvents()
{
    // poll events
    glfwPollEvents();
    // if any window should close, destroy it
    for (int i = 0; i < wm_windowCount; i++)
    {
        if (glfwWindowShouldClose(wm_windows[i].handle))
        {
            // destroy window and re-check the current index
            wm_destroyWindow(i--);
        }
    }
}

void wm_measureFPS()
{
    static int fps = 0;
    static double lastMeasure = 0;
    double currentTime = glfwGetTime();
    if (currentTime - lastMeasure >= 1.0)
    {
        printf("fps: %d\n", fps);
        fps = 0;
        lastMeasure = currentTime;
    }
    fps++;
}

void wm_terminate()
{
    wm_destroyAllWindows();
    glfwTerminate();
}