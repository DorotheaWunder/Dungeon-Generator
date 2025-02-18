#ifndef UI_H
#define UI_H

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

class Panel
{
public:
    Rectangle rectangle;
    Color color;
    const char* header;

    Panel(Rectangle rectangle, Color color, const char* header)
        : rectangle(rectangle), color(color), header(header) {}

    void Draw() const
    {
        DrawRectangleRec(rectangle, color);
        DrawText(header, rectangle.x + 10, rectangle.y + 10, 45,WHITE);
    }
};

#endif //UI_H
