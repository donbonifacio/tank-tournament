#include "../include/Weapon.h"
#include "../include/Bullet.h"
#include "../include/Explosion.h"

using namespace Tank;

//------------------------------------------------------------------------------------------------------
// Weapon
//------------------------------------------------------------------------------------------------------
Weapon::Weapon( const string& _tank, const string& _url, int _maxBullets, int _delay )
	:	TankPart(_tank,_url), 
		bullets( _maxBullets / 2), maxBullets(_maxBullets), fireDelay(_delay), ticks(SDL_GetTicks()) {}
		
//--------------------------------------------------------------------------------------------------------
bool Weapon::ready() const
{
	return (ticks+fireDelay) <= SDL_GetTicks(); 
}

//--------------------------------------------------------------------------------------------------------
void Weapon::addAmmo( int _ammo )
{
	if( (bullets += _ammo) > maxBullets )
		bullets = maxBullets;
}

//--------------------------------------------------------------------------------------------------------
void Weapon::fire( Movable* _shooter )
{
	if( --bullets <= 0 ) {
		cantFire();
		return;
	}
	ticks = SDL_GetTicks();
	createBullet(_shooter);
}

//--------------------------------------------------------------------------------------------------------
void Weapon::createExplosion( const Point& _point )
{
	new Explosion( Explosion::SMALL, _point.x, _point.y );
}

//--------------------------------------------------------------------------------------------------------
void Weapon::cantFire()
{
	// som?
}

//--------------------------------------------------------------------------------------------------------
Point Weapon::getStartPoint( Movable* _shooter )
{
	Point reference = Point(_shooter->x,_shooter->y) + 16; // centro do tank
	Direction* dir = _shooter->getDirection();
	
	if( 0 == dir ) {
		dir = _shooter->getLastDirection();
	}
	reference += dir->getVector() * 16;
	
	// agora está no meio do lado para onde o Tank está virado
	reference.y -= SmallFireBullet::SIZE;// / 2;
	reference.x -= SmallFireBullet::SIZE;// / 2;
	
	return reference;
}

//--------------------------------------------------------------------------------------------------------
// LitleFireWeapon
//--------------------------------------------------------------------------------------------------------
const int LitleFireWeapon::MAX_BULLETS = 2000;
const int LitleFireWeapon::FIRE_DELAY  = 200;

LitleFireWeapon::LitleFireWeapon()
	: Weapon("prototype","Weapon1",MAX_BULLETS,FIRE_DELAY) {}

LitleFireWeapon::LitleFireWeapon(const string& _tank)
	: Weapon(_tank,"Weapon1",MAX_BULLETS,FIRE_DELAY) {}

//--------------------------------------------------------------------------------------------------------
void LitleFireWeapon::createBullet( Movable* _shooter )
{
	Point reference = getStartPoint(_shooter);
	new SmallFireBullet( _shooter->getLastDirection(), reference.x, reference.y );
	createExplosion(reference);
}

//--------------------------------------------------------------------------------------------------------
// LargeFireWeapon
//--------------------------------------------------------------------------------------------------------
const int LargeFireWeapon::MAX_BULLETS = 100;
const int LargeFireWeapon::FIRE_DELAY  = 200;

LargeFireWeapon::LargeFireWeapon()
	: Weapon("prototype","Weapon2",MAX_BULLETS,FIRE_DELAY) {}

LargeFireWeapon::LargeFireWeapon(const string& _tank)
	: Weapon(_tank,"Weapon2",MAX_BULLETS,FIRE_DELAY) {}

//--------------------------------------------------------------------------------------------------------
void LargeFireWeapon::createBullet( Movable* _shooter )
{
	Point reference = getStartPoint(_shooter);
	new LargeFireBullet( _shooter->getLastDirection(), reference.x, reference.y );
	createExplosion(reference);
}

//--------------------------------------------------------------------------------------------------------
// CannonWeapon
//--------------------------------------------------------------------------------------------------------
const int CannonWeapon::MAX_BULLETS = 20;
const int CannonWeapon::FIRE_DELAY  = 500;

CannonWeapon::CannonWeapon()
	: Weapon("prototype","Weapon3",MAX_BULLETS,FIRE_DELAY) {}

CannonWeapon::CannonWeapon(const string& _tank)
	: Weapon(_tank,"Weapon3",MAX_BULLETS,FIRE_DELAY) {}

//--------------------------------------------------------------------------------------------------------
void CannonWeapon::createBullet( Movable* _shooter )
{
	Point reference = getStartPoint(_shooter);
	new CannonBullet( _shooter->getLastDirection(), reference.x, reference.y );
	createExplosion(reference);
}
