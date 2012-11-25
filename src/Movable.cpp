#include "../include/Movable.h"
#include <iostream>
using namespace std;

using namespace Tank;

//--------------------------------------------------------------------------------------------------------
Task::Task(int _delay) : dead(false), ticks(getTicks()), delay(_delay) { ARENA->registerTask(this); }
Task::~Task() {}

//---------------------------------------------------------------------------------------------------------
Movable::Movable( const SpriteHandlerPointer& _sph, int _health ) 
	: Actor(_sph,_health), dir(0), atrito(0), lastDirection(Direction::up()) {}

//---------------------------------------------------------------------------------------------------------
Movable::Movable( const SpriteHandlerPointer& _sph, int _health, int _delay ) 
	: Actor(_sph,_health), Task(_delay), dir(0), atrito(0), lastDirection(Direction::up()) {}
		
//---------------------------------------------------------------------------------------------------------
void Movable::move()
{
	basicMove(dir);
}

void Movable::basicMove( Direction* _onCollision )
{
	if( 0 == dir )
		return;
	
	Actor* actor = ARENA->getPos(this);
	actor->onCollision(this);
	onCollision(actor);
	
	if( actor->canStepOver() ) {
		advance();
	} else {
		join(actor);	// coloca este encostado ao actor
		setDirection(_onCollision);
	}
}

//---------------------------------------------------------------------------------------------------------
void Movable::join( Actor* _actor )
{
	Direction* opositeDir = dir->getOpositeDirection();
	Point offset = _actor->getLocation() + opositeDir->assertPoint();
	offset -= getLocation() + assertPoint();
	Point vector = opositeDir->getVector();
	vector.abs();
	offset *= vector;
	translate(offset);
}

//---------------------------------------------------------------------------------------------------------
void Movable::advance()
{
	setLocation(getNextPos());
}

//---------------------------------------------------------------------------------------------------------
Point Movable::assertPoint() const
{
	return dir->assertPoint();
}

//---------------------------------------------------------------------------------------------------------
Point Movable::getNextPos()
{	
	return dir->transform(x,y);
}

//---------------------------------------------------------------------------------------------------------
void Movable::action()
{
	move(); 
	if( 0 != dir )
		spriteHandler->step();  
}
	
//---------------------------------------------------------------------------------------------------------
void Movable::show() 
{ 
	paint(); 
}

//---------------------------------------------------------------------------------------------------------
void Movable::setDirection( Direction* _dir ) 
{  
	if( 0 != _dir ) {
		lastDirection = _dir;
		spriteHandler->setDirection(_dir);
	}
	dir = _dir; 
}

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
