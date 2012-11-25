/***************************************************************************
 *                                                                         *
 *                        HumanPlayer.h
 *  *-- Descricao
 *
 *	Tank controlado por um Humano
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
 
#ifndef _TANK_HUMAN_PLAER_H_
#define _TANK_HUMAN_PLAER_H_

#include "Safe.h"
#include <map>
#include <SDL/SDL.h>
#include "KeyHandler.h"
#include "BaseTank.h"

using SDL::KeyHandler;
using SDL::Key;

namespace Tank {

class HumanPlayer;
typedef void (HumanPlayer::*Func)();
typedef std::map<Key,Func> KeyMap;

class HumanPlayer : public BaseTank, public KeyHandler {
	
	KeyMap keyMap;
	int keyCount;
	
public:
	
	HumanPlayer( const string& _url, Key _up, Key _down, Key _left, Key _rigth, Key _fire );

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

	int getDefaultHealth() const { return 20; }
	void fire() { BaseTank::fire(); }
};
	
}

#endif //_TANK_HUMAN_PLAER_H_
