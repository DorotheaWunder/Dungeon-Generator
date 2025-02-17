#include "raylib.h"
#include "menu.h"
#include "ui.h"

Panel mapPanel((Rectangle)
    {950, 20, 430, 400}, (Color){130, 130, 130, 255}, "MAP");

Panel textPanel((Rectangle)
    {1100, 500, 220, 300}, (Color){130, 130, 130, 255}, "");


void DrawAllPanels()
{
    mapPanel.Draw();
    //textPanel.Draw();
}

void DrawMenu()
{
    DrawAllPanels();
}