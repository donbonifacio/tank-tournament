#include "../include/HumanDriver.h"
#include "../include/Arena.h"

using namespace Tank;

//------------------------------------------------------------------------------------
const HumanAction HumanDriver::actions[NACTIONS] = {
	&HumanDriver::goUp,
	&HumanDriver::goDown,
	&HumanDriver::goLeft,
	&HumanDriver::goRigth,
	&HumanDriver::fireSmall,
	&HumanDriver::fireLarge,
	&HumanDriver::fireCannon,
	&HumanDriver::fire
};

HumanDriver::HumanDriver() : keyCount(0)
{
	ARENA->registerKeyHandler(this);
}

//-------------------------------------------------------------------------------------------------------
void HumanDriver::setKey( KeyAction _action, Key _key )
{
	keyMap[_key] = actions[_action];
}

//-------------------------------------------------------------------------------------------------------
bool HumanDriver::hasKey( const Key _key )
{
	return keyMap.find(_key) != keyMap.end();
}
 
//-------------------------------------------------------------------------------------------------------
void HumanDriver::keyPressed( Key _key )
{
	KeyMap::iterator iter = keyMap.find(_key);
	if( iter == keyMap.end() )
		return;
	HumanAction func = iter->second;
	(this->*func)();
	++keyCount;
}

//-------------------------------------------------------------------------------------------------------
void HumanDriver::keyReleased( Key _key )
{
	if( hasKey(_key) ) {
		/*if( dir != 0 )
			lastDirection = dir;*/
		if( --keyCount == 0 )
			tank->setDirection(0);
	}
}

//-------------------------------------------------------------------------------------------------------
void HumanDriver::goUp()		{ tank->setDirection( Direction::up() ); 		}
void HumanDriver::goDown()		{ tank->setDirection( Direction::down() ); 	}
void HumanDriver::goLeft()		{ tank->setDirection( Direction::left() ); 	}
void HumanDriver::goRigth()		{ tank->setDirection( Direction::rigth() ); 	}

//-------------------------------------------------------------------------------------------------------
void HumanDriver::fireSmall() { tank->setWeapon(0); }
void HumanDriver::fireLarge() {tank->setWeapon(1); }
void HumanDriver::fireCannon() { tank->setWeapon(2); }

void HumanDriver::fire() { tank->fire(); }

//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
