/***************************************************************************
 *                                                                         *
 *                        Tank.h
 *  *-- Descricao
 *
 *	Classe que representa um tank
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
 
#ifndef _TANK_TANKV_H_
#define _TANK_TANKV_H_

#include <stack>
#include "Movable.h"
#include "Weapons.h"
#include "Weapon.h"
#include "Lagartas.h"
#include "TankController.h"

using std::stack;

namespace Tank {
	
class TankV : public Movable {

protected:	

	TankController* driver;

	Weapon* weapons[WEAPON_COUNT];
	Weapon* currentWeapon;
	stack<Lagartas*> lagartas;
	
public:

	TankV( TankController* _driver, const string& _url, int _health =100);
	~TankV();

	void setWeapon( int i ) { currentWeapon = weapons[i]; }

	void setDirection( Direction* _dir );
	void onCollision( Actor* _other );
	bool fire();
	void move();

	Point getNextPos();
	void paint( Surface& _surface );
	virtual int getDefaultHealth() const { return 100; }
};
	
}

#endif // #ifndef _TANK_BASETANK_H_
