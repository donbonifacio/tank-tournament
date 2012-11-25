/***************************************************************************
 *                                                                         *
 *                        Direction.h
 *  *-- Descricao
 *
 *  Classes que representam as diferentes direcções
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
#ifndef _TANK_DIRECTIOM_H_
#define _TANK_DIRECTIOM_H_

#include "Point.h"

using SDL::Point;

namespace Tank {

//--------------------------------------------------------------------------------------------------------	
struct Direction {

	enum {
		STEP = 8,
		ASSERT_POS = 0,
		TILE_SIZE = 32 - ASSERT_POS
	};

	enum Type { RIGTH, LEFT, DOWN, UP };

	static Direction* up();
	static Direction* down();
	static Direction* left();
	static Direction* rigth();
	static Direction* getDirection( Type _type );

	virtual Point transform( int _x, int _y ) const = 0;
	virtual Point transform( const Point& _point ) const { return transform(_point.x,_point.y); }
	virtual Type getType() const = 0;
	virtual Point assertPoint() const = 0;
	virtual Direction* getOpositeDirection() const = 0;
	virtual Direction* getCCWDirection() const = 0;
	virtual Direction* getCWDirection() const = 0;
	virtual const Point& getVector() const = 0;
};

//--------------------------------------------------------------------------------------------------------
struct UpDirection : public Direction {
	
	static const Point dirVector;
	const Point& getVector() const { return dirVector; };
	
	Point transform( int _x, int _y ) const {  return Point( _x, _y - STEP ); }
	Point assertPoint() const { return Point(0,0); }
	Type getType() const { return UP; }
	Direction* getOpositeDirection() const;
	Direction* getCCWDirection() const;
	Direction* getCWDirection() const;
};

//--------------------------------------------------------------------------------------------------------
struct DownDirection : public Direction {
	
	static const Point dirVector;
	const Point& getVector() const { return dirVector; };

	Point transform( int _x, int _y ) const {  return Point( _x, _y + STEP ); }
	Point assertPoint() const { return Point(0,TILE_SIZE); }
	Type getType() const { return DOWN; }
	Direction* getOpositeDirection() const;
	Direction* getCCWDirection() const;
	Direction* getCWDirection() const;
};

//--------------------------------------------------------------------------------------------------------
struct LeftDirection : public Direction {
	
	static const Point dirVector;
	const Point& getVector() const { return dirVector; };
	
	Point transform( int _x, int _y ) const {  return Point( _x - STEP, _y ); }
	Point assertPoint() const { return Point(0,0); }
	Type getType() const { return LEFT; }
	Direction* getOpositeDirection() const;
	Direction* getCCWDirection() const;
	Direction* getCWDirection() const;
};

//--------------------------------------------------------------------------------------------------------
struct RigthDirection : public Direction {
	
	static const Point dirVector;
	const Point& getVector() const { return dirVector; };
	
	Point transform( int _x, int _y ) const {  return Point( _x + STEP, _y ); }
	Point assertPoint() const { return Point(TILE_SIZE,0); }
	Type getType() const { return RIGTH; }
	Direction* getOpositeDirection() const;
	Direction* getCCWDirection() const;
	Direction* getCWDirection() const;
};

//--------------------------------------------------------------------------------------------------------

	
}	// namespace Tank 


#endif // _TANK_DIRECTIOM_H_
