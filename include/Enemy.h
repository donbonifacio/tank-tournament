/***************************************************************************
 *                                                                         *
 *                        Enemy.h
 *  *-- Descricao
 *
 *  Classe base de todos os inimigos, esta classe tem a AI mais fraca
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

#ifndef _TANK_ENEMY_H_
#define _TANK_ENEMY_H_

#include "TankController.h"
#include "Direction.h"
#include "Actor.h"
#include "Arena.h"
#include "Random.h"

namespace Tank {

class Enemy : public TankController {
public:
	void moveTank( TankV* _tank );
	void init( TankV* _tank );
	Direction* getRandomDirection();
};

}

#endif //_TANK_ENEMY_H_

