#include "colormap.h"
#include "../math/math.h"
#include <malloc.h>
#include <memory.h>
#include <stdio.h>

ColorMap* ColorMapCreate(const int width, const int height)
{
    ColorMap* _map = malloc(sizeof(ColorMap));
    _map->width = width;
    _map->height = height;
    _map->linearSize = width * height;
    Color* _clr = malloc(_map->linearSize * sizeof(Color));
    for (int x = 0; x < _map->linearSize; x++)
    {
        _clr[x] = ColorCreate(255, 255, 255);
    }
    _map->colors = _clr;
    _map->ratio = (float)width / (float)height;
    return _map;
}

void ColorMapDestroy(const ColorMap* colorMap)
{
    free(colorMap->colors);
    free(colorMap);
}

void ColorMapResize(ColorMap* colorMap, const int newWidth, const int newHeight)
{
    int _nW;
    int _nH;
    if (newWidth < colorMap->width)
        _nW = newWidth;
    else
        _nW = colorMap->width;
    if (newHeight < colorMap->height)
        _nH = newHeight;
    else
        _nH = colorMap->height;
    int newLinearSize = newWidth * newHeight;
    Color* _clr = malloc(newLinearSize * sizeof(Color));
    for (int y = 0; y < _nH; y++)
    {
        for (int x = 0; x < _nW; x++)
        {
            _clr[y * newWidth + x] = ColorMapGetPixelA(colorMap, x, y);
        }
    }
    Color* __ = colorMap->colors;
    colorMap->width = newWidth;
    colorMap->height = newHeight;
    colorMap->colors = _clr;
    colorMap->ratio = (float)newWidth / (float)newHeight;
    colorMap->linearSize = newLinearSize;
    free(__);
}

void ColorMapSetPixel(const register ColorMap* colorMap, const register Point2D position, const register Color color)
{
    if ((position.x | position.y) >= 0 && position.x < colorMap->width && position.y < colorMap->height)
        ColorMapPixel(colorMap, position.x, position.y) = color;
}

void ColorMapSetPixelA(const register ColorMap* colorMap, const register int x, const register int y, const register Color color)
{
    if ((x | y) >= 0 && x < colorMap->width && y < colorMap->height)
        ColorMapPixel(colorMap, x, y) = color;
}

Color ColorMapGetPixel(const ColorMap* colorMap, const Point2D position)
{
    if ((position.x | position.y) >= 0 && position.x < colorMap->width && position.y < colorMap->height)
        return ColorMapPixel(colorMap, position.x, position.y);
    return ColorCreate(255, 255, 255);
}

Color ColorMapGetPixelA(const ColorMap* colorMap, const int x, const int y)
{
    if ((x | y) >= 0 && x < colorMap->width && y < colorMap->height)
        return ColorMapPixel(colorMap, x, y);
    return ColorCreate(255, 255, 255);
}

void ColorMapDrawLine(const ColorMap* colorMap, Point2D start, Point2D end, const Color color)
{
    int _a = end.x - start.x;
    int _b = end.y - start.y;
    const int _w = colorMap->width;
    const int _h = colorMap->height;
    int sX;
    int eX;
    const char _check = AbsInt(_b) > AbsInt(_a);
    if (_check)
    {
        register int _s = start.x;
        start.x = start.y;
        start.y = _s;
        _s = end.x;
        end.x = end.y;
        end.y = _s;
        _s = _a;
        _a = _b;
        _b = _s;
    }
    if (start.x < end.x)
    {
        sX = start.x;
        eX = end.x;
    }
    else
    {
        sX = end.x;
        eX = start.x;
    }
    const register float n = (float)_b / (float)_a;
    const register float m = start.y - start.x * n;
    if (_check)
    {
        for (; sX < eX; sX++)
        {
            ColorMapSetPixelA(colorMap, RoundInt(sX * n + m), sX, color);
        }
        return;
    }
    for (; sX < eX; sX++)
    {
        ColorMapSetPixelA(colorMap, sX, RoundInt(sX * n + m), color);
    }
}

void ColorMapSave(const ColorMap* colorMap, const char* location)
{
    FILE* _f;
    
    int _size = colorMap->linearSize * 13 + 20;
    int _nSize = 0;
    int _s = 0;
    
    char* _txt = malloc(_size);
    char* _txtA = _txt;
    char _nTxt[100];
    
    Color color;
    
    sprintf(_nTxt, "P3 %i %i 255\n\0", colorMap->width, colorMap->height);
        
    for (; _nTxt[_s]; _s++)
    {
    }
        
    sprintf(_txtA, "%s", _nTxt);
    _txtA += _s;
    _nSize += _s;

    for (int x = 0; x < colorMap->linearSize; x++)
    {
        
        color = ColorMapPixelA(colorMap, x);
        
        sprintf(_nTxt, "%i %i %i\n\0", color.r, color.g, color.b);
        
        for (_s = 0; _nTxt[_s]; _s++)
        {
        }
        
        sprintf(_txtA, "%s", _nTxt);
        _txtA += _s;
        _nSize += _s;
    }
    _txtA[1] = '\0';

    _f = fopen(location, "w");
    
    fwrite(_txt, 1, _nSize, _f);
    
    fclose(_f);
    
    free(_txt);
}

void ColorMapClear(const ColorMap* colorMap)
{
    for (int x = 0; x < colorMap->width; x++)
    {
        for (int y = 0; y < colorMap->height; y++)
        {
            ColorMapPixel(colorMap, x, y) = ColorCreate(255, 255, 255);
        }
    }
}