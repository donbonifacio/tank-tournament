/***************************************************************************
 *                                                                         *
 *                        HumanDriver.h
 *  *-- Descricao
 *
 *	Interface que permite ao jogador controlar o Tank
 *
 *	*-- Detalhes      
 *                        
 *   begin                : Wed May 28 2003               
 *   copyright            : (C) 2003 by Pedro Santos                  
 *
 *	 author:			  : Pedro Santos <pre@users.sf.net>
 *   homepage             : http://psantos.net						       *
 *   contact              : http://psantos..net/contacto.php	           *
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

#ifndef _TANK_HUMAN_DRIVER_H_
#define _TANK_HUMAN_DRIVER_H_

#include <map>
#include "TankController.h"
#include "Tank.h"
#include "KeyHandler.h" // definição da Key
#include "Weapons.h"

using std::map;
using Tank::TankV;

namespace Tank {

class HumanDriver;
typedef void (HumanDriver::*HumanAction)();
typedef map<Key,HumanAction> KeyMap;

enum KeyAction {
	UP,
	DOWN,
	LEFT,
	RIGTH,

	FIRE1,
	FIRE2,
	FIRE3,

	FIRE,

	NACTIONS
};

class HumanDriver : public TankController, public KeyHandler {

	static const HumanAction actions[NACTIONS];
	KeyMap keyMap;
	int keyCount;
	TankV* tank;

public:
	HumanDriver();

	void setTank( TankV* _tank ) { tank=_tank; }
	void moveTank( TankV* _tank ) { _tank->basicMove(0); }
	void init(TankV* _tank) {}

	void setKey( KeyAction _action, Key _key );

	bool hasKey( Key _key );
	void keyPressed( Key _key );
	void keyReleased( Key _key );
	
	void goUp();
	void goDown();
	void goLeft();
	void goRigth();

	void fireSmall();
	void fireLarge();
	void fireCannon();

	void fire();
	
};

inline TankV* newHumanDriver(const string& _name) {
	HumanDriver* tankC = new HumanDriver();
	TankV* tank = new TankV(tankC,_name);
	tankC->setTank(tank);
	return tank;
}

}

#endif // _TANK_HUMAN_DRIVER_H_
