#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#define WM_MAX_WINDOWS 100

/// @brief holds window id for window management
/// @param id is used identify window
/// @param handle is used to access window
typedef struct wm_Window_t
{
    unsigned int id;
    void *handle;
} Window;

// window creation
Window *wm_init(int width, int height, const char *title);
void wm_createWindow(int width, int height, const char *title);

// buffer operation
void wm_clearBuffer(float r, float g, float b, float a);
void wm_swapWindowBuffer(Window *window);
void wm_destroyWindow(int index);
Window *wm_getWindowByID(unsigned int id);
void wm_destroyAllWindows();

// event handling
void wm_pollEvents();
void wm_terminate();

// default callback functions

#endif // WINDOW_MANAGER_H