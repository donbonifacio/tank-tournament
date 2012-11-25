#include "../include/Rectangle.h"


Rectangle(int _x=0, int _y=0, int _w=-1, int _h=-1);
Rectangle(const SDL_Rect& _r);

bool contains(int _x, int _y) const;
bool contains(int _x, int _y, int _w, int _h) const;
bool contains(const SDL_Rect& _rectangle) const;

bool intersects(const SDL_Rect& _rectangle) const;
bool isEmpty() const;

void setBounds(int _x, int _y, int _width, int _height);
void setBounds(const SDL_Rect& _r);
void setDimension(int _w, int _h);

void setLocation(int _x, int _y);
void translate(int _x, int _y);

void print(ostream& _os) const;
