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
 
#ifndef _TANK_WEAPONS_H_
#define _TANK_WEAPONS_H_

namespace Tank {
	
enum WeaponIndex {
	LITLE_FIRE_WEAPON,
	LARGE_FIRE_WEAPON,
	CANNON_WEAPON,
	WEAPON_COUNT		// tem que ser sempre o último Item!!!
};

}

#endif // #ifndef _TANK_WEAPONS_H_
