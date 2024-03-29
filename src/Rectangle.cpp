#include <iostream>
#include "../include/Rectangle.h"

using namespace SDL;
using SDL::Rectangle;
using std::endl;

//---------------------------------------------------------------------------------------------------------------------------------------------------
Rectangle::Rectangle(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {}
//---------------------------------------------------------------------------------------------------------------------------------------------------
Rectangle::Rectangle(const SDL_Rect& _r) : x(_r.x), y(_r.y), w(_r.w), h(_r.h) {}
//---------------------------------------------------------------------------------------------------------------------------------------------------
Rectangle::Rectangle( const Point& _pos, int _size ) : x(_pos.x), y(_pos.y), w(_size), h(_size) {}
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Rectangle::contains(int _x, int _y) const
{
	if( _x > x && _x < (x + w) )
		if( _y > y && _y < (y + h) )
			return true;
	return false;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Rectangle::collide( int _x, int _y ) const
{
	if( _x >= x && _x <= (x + w) )
		if( _y >= y && _y <= (y + h) )
			return true;
	return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Rectangle::contains(int _x, int _y, int _w, int _h) const
{
	// retorna true se todos os pontos estiverem contidos neste rect
	return contains(_x,_y) && contains(_x+_w,_y) &&
				contains(_x,_y+_h) && contains(_x+_w,_y+_h);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Rectangle::contains(const SDL_Rect& _rectangle) const
{
	return contains(_rectangle.x, _rectangle.y, _rectangle.w, _rectangle.h);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Rectangle::contains(const Rectangle& _rectangle) const
{
	return contains(_rectangle.x, _rectangle.y, _rectangle.w, _rectangle.h);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Rectangle::intersects(int _x, int _y, int _w, int _h) const
{
	// retorna true se algum dos pontos estiver contido neste rect
	bool inThis = contains(_x,_y) || contains(_x+_w,_y) ||
				contains(_x,_y+_h) || contains(_x+_w,_y+_h) ||
				contains(_x,_h/2+_y) || contains(_x+_w,_h/2+_y) ||
				contains(_w/2+_x,_y) || contains(_w/2+_x,_y+_h);

	// se poss�vel, n�o fazer o pr�ximo teste

	if( inThis )	
		return true;

	Rectangle other(_x,_y,_w,_h);
	if( other.getArea() <= getArea() )
		return false;

	// pode-se dar o caso do Rect passado ter uma �rea menor que este,
	// nesse caso, para ter a certeza, faz-se a pergunta ao contr�rio
	return other.intersects(*this);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Rectangle::intersects(const SDL_Rect& _rectangle) const
{
	return intersects(_rectangle.x, _rectangle.y, _rectangle.w, _rectangle.h);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Rectangle::intersects(const Rectangle& _rectangle) const
{
	return intersects(_rectangle.x, _rectangle.y, _rectangle.w, _rectangle.h);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Rectangle::collides( const Rectangle& _rectangle ) const
{
	return true;/*collide(_rectangle_x,_y) || collide(_x+_w,_y) ||
				collide(_x,_y+_h) || collide(_x+_w,_y+_h);*/
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
bool Rectangle::isEmpty() const
{
	// o Rectangle est� vazio quando w ou h forem negativos
	// (contudo, a posicao continua a ser valida)
	return w < 0 || h < 0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void Rectangle::setBounds(int _x, int _y, int _width, int _height)
{
	x = _x;
	y = _y;
	w = _width;
	h = _height;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void Rectangle::setBounds(const SDL_Rect& _r)
{
	setBounds(_r.x, _r.y, _r.w, _r.h);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void Rectangle::setDimension(int _w, int _h)
{
	w = _w;
	h = _h;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void Rectangle::setLocation(int _x, int _y)
{
	x = _x;
	y = _y;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void Rectangle::translate(int _x, int _y)
{
	x += _x;
	y += _y;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void Rectangle::printOn(ostream& _os) const
{
	_os	<< endl << "|--Rectangle Test { " << x << ", " << y << ", " 
		<< w << ", " << h << " } ";
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
