/***************************************************************************
 *                                                                         *
 *                        Actor.h
 *  *-- Descricao
 *
 *	Classe base de todos os objectos do jogo
 *
 *	*-- Detalhes      
 *                        
 *   begin                : Wed May 28 2003               
 *   copyright            : (C) 2003 by Pedro Santos                  
 *
 *	 author:			  : Pedro Santos <pre@users.sf.net>
 *   homepage             : http://psantos.net						       *
 *   contact              : http://psantos..net/contacto.php	
 *
 *   Tank Tournament HP   : http://tank-tournament.sf.net
 *                                                                         *
 * *-- Licence:                                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _TANK_ACTOR_H_
#define _TANK_ACTOR_H_

#include "Surface.h"
#include "Rectangle.h"
#include "Screen.h"
#include "SpriteHandler.h"
#include "SharedPointer.h"

using SDL::Surface;
using SDL::Rectangle;
using SDL::SpriteHandler;
using SDL::OneDimensionSpriteHandler;
using Util::SharedPointer;

namespace Tank {
	
struct Actor : public Rectangle {
	
	typedef SharedPointer<SpriteHandler> SpriteHandlerPointer;
	
protected:

	enum { NO_HEALTH = -4000 };

	SpriteHandlerPointer spriteHandler;
	int health;
	
public:
	
	// constantes gerais
	enum { TILE_SIZE = 32 };

	Actor( const SpriteHandlerPointer& _sph, int _health );
	Actor( const SpriteHandlerPointer& _sph, int _x, int _y, int _health );
	virtual ~Actor() {}

	void hide() const;
	void paint();
	virtual void paint( Surface& _surface );
		
	virtual bool isAlive() const;
	virtual bool canStepOver() const = 0;
	bool isObstacle() const { return !canStepOver(); }
	virtual void onCollision( Actor* _other ) = 0;
	virtual bool setDamage( int _damage );
	virtual int getDefaultHealth() const = 0;
	virtual bool isMovable() const = 0;
	virtual int getSize() const { return TILE_SIZE; }

};
	
} //namespace Tank 

#endif // _TANK_ACTOR_H_
