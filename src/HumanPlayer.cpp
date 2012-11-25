#include "../include/HumanPlayer.h"

using namespace Tank;

//-------------------------------------------------------------------------------------------------------
HumanPlayer::HumanPlayer( const string& _url, Key _up, Key _down, Key _left, Key _rigth, Key _fire )
	: BaseTank(_url, getDefaultHealth()), keyCount(0)
{
	keyMap[_up] = &HumanPlayer::goUp;
	keyMap[_down] = &HumanPlayer::goDown;
	keyMap[_left] = &HumanPlayer::goLeft;
	keyMap[_rigth] = &HumanPlayer::goRigth;
	keyMap[_fire] = &HumanPlayer::fire;
	
	keyMap[SDLK_1] = &HumanPlayer::fireSmall;
	keyMap[SDLK_2] = &HumanPlayer::fireLarge;
	keyMap[SDLK_3] = &HumanPlayer::fireCannon;
	
	ARENA->registerKeyHandler(this);
}

//-------------------------------------------------------------------------------------------------------
bool HumanPlayer::hasKey( const Key _key )
{
	return keyMap.find(_key) != keyMap.end();
}
 
//-------------------------------------------------------------------------------------------------------
void HumanPlayer::keyPressed( Key _key )
{
	KeyMap::iterator iter = keyMap.find(_key);
	if( iter == keyMap.end() )
		return;
	Func func = iter->second;
	(this->*func)();
	++keyCount;
}

//-------------------------------------------------------------------------------------------------------
void HumanPlayer::keyReleased( Key _key )
{
	if( hasKey(_key) ) {
		if( dir != 0 )
			lastDirection = dir;
		if( --keyCount == 0 )
			setDirection(0);
	}
}

//-------------------------------------------------------------------------------------------------------
void HumanPlayer::goUp()		{ setDirection( Direction::up() ); 		}
void HumanPlayer::goDown()		{ setDirection( Direction::down() ); 	}
void HumanPlayer::goLeft()		{ setDirection( Direction::left() ); 	}
void HumanPlayer::goRigth()		{ setDirection( Direction::rigth() ); 	}

//-------------------------------------------------------------------------------------------------------
void HumanPlayer::fireSmall() { currentWeapon = weapons[0]; }
void HumanPlayer::fireLarge() { currentWeapon = weapons[1]; }
void HumanPlayer::fireCannon() { currentWeapon = weapons[2]; }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
