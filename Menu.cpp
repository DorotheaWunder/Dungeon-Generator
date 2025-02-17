#include "raylib.h"
#include "ui.h"

Panel mapPanel;
Panel textPanel;

void InitializeMenuPanels()
{
    InitPanelElement(&mapPanel,
        (Rectangle){ 950, 20, 430, 400 },
        (Color){ 130, 130, 130, 255 },
        "MAP");

    InitPanelElement(&textPanel,
        (Rectangle){ 1100, 500, 220, 300 },
        (Color){ 130, 130, 130, 255 },
        "");
}

void DrawAllPanels()
{
    InitializeMenuPanels();

    DrawPanelElement(mapPanel);
    //DrawPanelElement(textPanel);
}

void DrawMenu()
{
    DrawAllPanels();
}