#ifndef UI_H
#define UI_H

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 900

typedef struct Panel
{
    Rectangle rectangle;
    Color color;
    const char* header;
} Panel;


void InitPanelElement(Panel* panel, Rectangle rectangle, Color color, const char* header);
void DrawPanelElement(Panel panel);
#endif //UI_H
