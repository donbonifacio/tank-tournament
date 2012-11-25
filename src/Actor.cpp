#include "../include/Actor.h"

using namespace Tank;

//--------------------------------------------------------------------------------------------------------------
Actor::Actor( const SpriteHandlerPointer& _sph, int _health ) 
	: Rectangle(0, 0, TILE_SIZE, TILE_SIZE), spriteHandler(_sph), health(_health) {}
	
//--------------------------------------------------------------------------------------------------------------
Actor::Actor( const SpriteHandlerPointer& _sph, int _x, int _y, int _health ) 
	:  Rectangle(_x, _y, TILE_SIZE, TILE_SIZE), spriteHandler(_sph), health(_health) {}		
		
//--------------------------------------------------------------------------------------------------------------
void Actor::paint() 
{
	paint(*SCR);
}
//--------------------------------------------------------------------------------------------------------------
void Actor::paint( Surface& _surface ) 
{
	spriteHandler->paintOn(x,y,_surface);
}
//--------------------------------------------------------------------------------------------------------------
void Actor::hide() const
{
	// fazer depois
}
		
//--------------------------------------------------------------------------------------------------------------
bool Actor::isAlive() const
{
	return health <= 0;
}

//--------------------------------------------------------------------------------------------------------------
bool Actor::setDamage(int _damage) 
{
	health -= _damage;
	return isAlive();
}


