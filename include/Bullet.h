/***************************************************************************
 *                                                                         *
 *                        Bullet.h
 *  *-- Descricao
 *
 *	Classe que representa uma bala
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
 
#ifndef _TANK_BULLET_H_
#define _TANK_BULLET_H_

#include "Movable.h"

namespace Tank {

//--------------------------------------------------------------------------------------------------------
class Bullet : public Movable {
	
public:
	Bullet( const string& _url, Direction* _dir, int _x, int _y, int _w, int _h, int _delay );
	
	void onCollision( Actor* _other );
	void createExplosion();
	void paint( Surface& _surface );
	Point assertPoint() const;

	int getDefaultHealth() const { return 1; }

	virtual int getDamage() const = 0;
	virtual int getOffset() const = 0;
};

//--------------------------------------------------------------------------------------------------------
class SmallFireBullet : public Bullet {
public:	

	enum { 
		SIZE = 6, 
		OFFSET = (TILE_SIZE - SIZE) / 2
	};
	
	SmallFireBullet( Direction* _dir, int _x, int _y  ) 
		: Bullet( "SmallFireBullet",_dir,_x,_y,SIZE,SIZE,50) {}
			
	int getDamage() const 	{ return 10; 		}
	int getSize() const 	{ return SIZE; 		}
	int getOffset() const 	{ return OFFSET; 	}

	void join( Actor* _actor ) {}
};

//--------------------------------------------------------------------------------------------------------
class LargeFireBullet : public Bullet {
	
	enum { 
		SIZE = 9, 
		OFFSET = (TILE_SIZE - SIZE) / 2
	};
	
public:
	LargeFireBullet( Direction* _dir, int _x, int _y ) 
		: Bullet( "LargeFireBullet",_dir,_x,_y,SIZE,SIZE,50) {}
	
	int getDamage() const 	{ return 20; 		}
	int getSize() const 	{ return SIZE; 		}	
	int getOffset() const 	{ return OFFSET; 	}
	
};

//--------------------------------------------------------------------------------------------------------
class CannonBullet : public Bullet {
	
	enum { 
		SIZE = 9, 
		OFFSET = (TILE_SIZE - SIZE)  / 2
	};
	
public:
	CannonBullet( Direction* _dir, int _x, int _y ) 
		: Bullet( "CannonBullet",_dir,_x,_y,SIZE,SIZE,50) {}
	
	int getDamage() const 	{ return 100; 		}
	int getSize() const 	{ return SIZE; 		}	
	int getOffset() const 	{ return OFFSET; 	}
	
};

//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

}

#endif // #ifndef _TANK_BULLET_H_
