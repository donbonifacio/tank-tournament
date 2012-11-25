/***************************************************************************
 *                                                                         *
 *                        Weapon.h
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
 
#ifndef _TANK_WEAPON_H_
#define _TANK_WEAPON_H_

#include <SDL/SDL.h>
#include "Movable.h"
#include "TankPart.h"
#include "Weapons.h"

namespace Tank {
	
//--------------------------------------------------------------------------------------------------------
class Weapon : public TankPart {
	
protected:
	
	int bullets;
	int maxBullets;
	int fireDelay;
	Uint32 ticks;

public:

	Weapon( const string& _tank, const string& _url, int _maxBullets, int _delay );
	
	bool ready() const;
	void addAmmo( int _ammo );
	void fire( Movable* _shooter );
	void cantFire();
	Point getStartPoint( Movable* _shooter );
	void createExplosion( const Point& _point );
	virtual void createBullet( Movable* _shooter ) = 0;
	virtual WeaponIndex getIndex() const = 0;
};

//--------------------------------------------------------------------------------------------------------
class LitleFireWeapon : public Weapon {
	
	static const int MAX_BULLETS;
	static const int FIRE_DELAY;
	
public:
	
	LitleFireWeapon(const string& _tank);
	LitleFireWeapon();
	void createBullet( Movable* _shooter );
	WeaponIndex getIndex() const { return LITLE_FIRE_WEAPON; }
};

//--------------------------------------------------------------------------------------------------------
class LargeFireWeapon : public Weapon {
	
	static const int MAX_BULLETS;
	static const int FIRE_DELAY;
	
public:
	
	LargeFireWeapon(const string& _tank);
	LargeFireWeapon();

	void createBullet( Movable* _shooter );
	WeaponIndex getIndex() const { return LARGE_FIRE_WEAPON; }
};

//--------------------------------------------------------------------------------------------------------
class CannonWeapon : public Weapon {
	
	static const int MAX_BULLETS;
	static const int FIRE_DELAY;
	
public:
	
	CannonWeapon(const string& _tank );
	CannonWeapon( );
	void createBullet( Movable* _shooter );
	WeaponIndex getIndex() const { return CANNON_WEAPON; }
};

//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

}

#endif // #ifndef _TANK_WEAPON_H_
