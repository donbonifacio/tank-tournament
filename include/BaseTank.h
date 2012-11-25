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
 
#ifndef _TANK_BASETANK_H_
#define _TANK_BASETANK_H_

#include "Movable.h"
#include "Weapons.h"
#include "Weapon.h"

namespace Tank {
	
class BaseTank : public Movable {
protected:	
	Weapon* weapons[WEAPON_COUNT];
	Weapon* currentWeapon;
	
public:
	BaseTank( const string& _url, int _health );
	
	void setDirection( Direction* _dir );
	bool fire();
	void onCollision( Actor* _other ) { /* não faz nada! */ }
};
	
}

#endif // #ifndef _TANK_BASETANK_H_
