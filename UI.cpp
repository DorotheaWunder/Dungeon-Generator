#include "raylib.h"
#include "ui.h"



void InitPanelElement(Panel* panel, Rectangle rectangle, Color color, const char* header)
{
    panel->rectangle = rectangle;
    panel->color = color;
    panel->header = header;
}

void DrawPanelElement(Panel panel)
{
    DrawRectangleRec(panel.rectangle, panel.color);
    DrawText(panel.header, panel.rectangle.x + 10, panel.rectangle.y + 10, 45, WHITE);
}