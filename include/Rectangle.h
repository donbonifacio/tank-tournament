/***************************************************************************
 *                                                                         *
 *                        Rectangle.h
 *  *-- Descricao
 *
 *  Classe auxiliar rectangulo 
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
 ***************************************************************************/
 
#ifndef _SDL_RECTANGLE_H_
#define _SDL_RECTANGLE_H_
 
#include <SDL/SDL.h>
#include "Point.h"
#include "Printable.h" 

namespace SDL {
	 
struct Rectangle : public Printable /*, public SDL_Rect*/ {	 
	int x,y,w,h;

	Rectangle(int _x=0, int _y=0, int _w=-1, int _h=-1);
	Rectangle(const SDL_Rect& _r);
	Rectangle( const Point& _pos, int _size );
	
	// o contains não conta com as margens, o colide sim.
	bool collide( int _x, int _y ) const;
	bool contains(int _x, int _y) const;
	bool contains( const Point& _p ) const { return contains(_p.x,_p.y); }
	bool contains(int _x, int _y, int _w, int _h) const;
	bool contains(const SDL_Rect& _rectangle) const;
	bool contains(const Rectangle& _rectangle) const;

	bool intersects(const SDL_Rect& _rectangle) const;
	bool intersects(const Rectangle& _rectangle) const;
	bool intersects(int _x, int _y, int _w, int _h) const;
	bool collides( const Rectangle& _rectangle ) const;

	bool isEmpty() const;

	void setBounds(int _x, int _y, int _width, int _height);
	void setBounds(const SDL_Rect& _r);
	void setDimension(int _w, int _h);

	void setLocation(int _x, int _y);
	void setLocation(const Point& _p) { setLocation(_p.x, _p.y); }
	void translate(int _x, int _y);
	void translate( const Point& _p ) { translate(_p.x,_p.y); }

	Point getLocation() const { return Point(x,y); }

	const int getArea() const { return h*w; }

	void printOn(ostream& _os) const;
};	

} // namespace SDL {
 
 
#endif //_SDL_RECTANGLE_H_

