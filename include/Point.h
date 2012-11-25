/***************************************************************************
 *                                                                         *
 *                        Point.h
 *  *-- Descricao
 *
 *	Representação gráfica de um ponto
 *
 *	*-- Detalhes      
 *                        
 *   begin                : Wed May 28 2003               
 *   copyright            : (C) 2003 by Pedro Santos                  
 *   homepage             : http://pdpsantos.sf.net                        *
 *   contact              : http://pdpsantos.sf.net/contacto.php           *
 *   Tank Tournament HP   : http://pdpsantos.sf.net/tank/                  *
 *                                                                         *
 * *-- Licence:                                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *****************'**********************************************************/
#ifndef _SDL_POINT_H_
#define _SDL_POINT_H_

//#include <cmath>
#include "Printable.h"

inline int _abs(int _n) {
	return (_n>0) ? _n : -_n;
}

namespace SDL {
	
struct Point : public Printable {
	int x, y;
	
	Point( int _x = 0, int _y = 0 ) : x(_x), y(_y) {}
	Point( const Point& _p ) : x(_p.x), y(_p.y) {}
		
	const int getX() const { return x; }
	const int getY() const { return y; }

	void setLocation( int _x, int _y ) { x = _x, y = _y; } 
	void setLocation( const Point& _p ) { x = _p.x; y = _p.y; } 

	void translate( int _dx, int _dy ) { x += _dx; y += _dy; }
		
	Point& operator=( const Point& _p ) { setLocation(_p); return *this; }
	bool operator==( const Point& _p ) { return _p.x == x && _p.y == y; }
	bool operator!=( const Point& _p ) { return !(*this==_p); }

	Point operator/( int _divisor ) const { return Point(x/_divisor,y/_divisor); }
	Point operator/( const Point& _p ) const { return Point(x/_p.x,y/_p.y); }
	Point& operator/=( int _divisor ) { x/=_divisor; y/=_divisor; return *this; }
	Point& operator/=( const Point& _p ) { x/=_p.x; y/=_p.y; return *this; }

	Point operator*( int _divisor ) const { return Point(x*_divisor,y*_divisor); }
	Point& operator*=( int _divisor ) { x*=_divisor; y*=_divisor; return *this; }
	Point operator*( const Point& _p ) const { return Point(x*_p.x,y*_p.y); }
	Point& operator*=( const Point& _p ) { x*=_p.x; y*=_p.y; return *this; }

	Point operator+( const Point& _p ) const { return Point(x+_p.x,y+_p.y); }
	Point operator+( int _somador ) const { return Point(x+_somador,y+_somador); }
	Point& operator+=( const Point& _p ) { x+=_p.x; y+=_p.y; return *this; }
	Point& operator+=( int _somador ) { x+=_somador; y+=_somador; return *this; }

	Point operator-( const Point& _p ) const { return Point(x-_p.x,y-_p.y); }
	Point operator-( int _somador ) const { return Point(x-_somador,y-_somador); }
	Point& operator-=( const Point& _p ) { x-=_p.x; y-=_p.y; return *this; }
	Point& operator-=( int _somador ) { x-=_somador; y-=_somador; return *this; }

	int operator%( int _divisor ) const { return x % _divisor + y % _divisor; }

	void abs() { x=_abs(x); y=_abs(y); }

	void printOn( ostream& _os ) const {
		_os << "Point(" << x << "," << y << ")";
	}

};
	
}	// namespace SDL


#endif // _SDL_POINT_H_
