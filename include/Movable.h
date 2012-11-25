/***************************************************************************
 *                                                                         *
 *                        Movable.h
 *  *-- Descricao
 *
 *	Classe base de todos os objectos que se movem
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
 
#ifndef _TANK_MOVABLE_H_
#define _TANK_MOVABLE_H_

#include "Actor.h"
#include "Point.h"
#include "Direction.h"
#include "Task.h"
#include "Global.h"

using SDL::Point;

namespace Tank {

class Movable : public Actor, public Task {

protected:
	
	Direction* dir;
	int atrito;
	Direction* lastDirection;
	
public:
	
	Movable( const SpriteHandlerPointer& _sph, int _health );
	Movable( const SpriteHandlerPointer& _sph, int _health, int _delay );
	
	virtual void move();
	void basicMove( Direction* _onCollision );

	virtual void setDirection( Direction* _dir );

	void advance();
	virtual void join( Actor* _actor );
	virtual Point getNextPos();
	virtual Point assertPoint() const;
	
	bool canStepOver() const { return false; }
	bool isMovable() const { return true; }
	void setAtrito( int _atrito ) { atrito = _atrito; }
	Direction* getDirection() { return dir; }
	Direction* getLastDirection() { if( 0 != dir ) return dir; return lastDirection; }

	// do task
	void action(); 
	void show();
	Actor* getSource() { return &*this; }
	const Rectangle& getRectangle() const { return *this; }
	
};	

	
}	// namespace Tank


#endif // _TANK_MOVABLE_H_
