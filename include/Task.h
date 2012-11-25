/***************************************************************************
 *                                                                         *
 *                        Task.h
 *  *-- Descricao
 *
 *  Classes que se movem têm que derivar desta 
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
 
#ifndef _TANK_TASK_H_
#define _TANK_TASK_H_

#include <SDL/SDL.h>
#include <iostream>
using namespace std;

namespace Tank {

struct Actor;
	
class Task {
	
	bool dead;
	Uint32 ticks;
	int delay;
	// definido no movsble.cpp
	enum { DELAY = 100 };
	
public:
	Task( int _delay = DELAY ); // definido no Movable.cpp 
	virtual ~Task();
	
	void step() { 
		if( isTime() ) { 
			action(); 
			ticks = getTicks();
		} 
	}

	bool isTime() {
		return (ticks+delay) <= getTicks(); 
	}

	void die() { dead = true; }
	bool isDead() const { return dead; }
	bool isAlive() const { return !isDead(); }

	Uint32 getTicks() const { return SDL_GetTicks(); }

	virtual void action() = 0;
	virtual void show() = 0;
	virtual const Rectangle& getRectangle() const = 0;
	virtual Actor* getSource() = 0;
	
};

} // namespace Tank

#endif // _TANK_TASK_H_
