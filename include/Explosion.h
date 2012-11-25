/***************************************************************************
 *                                                                         *
 *                        Explosion.h
 *  *-- Descricao
 *
 *	Classe usada pelos Tanks para disparar
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
 
#ifndef _TANK_EXPLOSION_H_
#define _TANK_EXPLOSION_H_

#include "Actor.h"

namespace Tank {
	
//--------------------------------------------------------------------------------------------------------
class Explosion : public Actor, public Task {
	
public:
	
	enum Intensity {
		SMALL = 9,
		MEDIUM,
		LARGE,
		VERY_LARGE
	};

	Intensity intensity;
	int duration;
	int count;

	Explosion( Intensity _intensity, int _x, int _y )
		: Actor( new SDL::FourDimensionsSpriteHandler( GLOBAL->getSurface("Explosion"), TILE_SIZE ), 
			getDefaultHealth()), Task(100), intensity(_intensity), count(0)	
	{
		setLocation(_x,_y);
		(GLOBAL->getSurface("Explosion"))->setColorKey(0,0,0); 
		switch(intensity){
			case SMALL: duration = 1; break;
			case MEDIUM: duration = 2; break;
			case LARGE: duration = 3; break;
			case VERY_LARGE: duration = 4; break;
		}
	}
	
	int getDefaultHealth() const { return 4000; }
	void show() { paint(*SCR); }
	bool canStepOver() const { return true; }
	void onCollision( Actor * _other ) {}
	bool isMovable() const { return false; }

	void action() { 
		spriteHandler->step(); 
		spriteHandler->nextDirection();
		if( ++count == duration ) 
			die(); 
	}

	void paint( Surface& _surface ){
		spriteHandler->partialPaintOn( intensity ,(TILE_SIZE - intensity) / 2,x,y,_surface);
	}

	const Rectangle& getRectangle() const { return *this; }
	Actor* getSource() { return this; }
};

}

#endif // #ifndef _TANK_EXPLOSION_H_
