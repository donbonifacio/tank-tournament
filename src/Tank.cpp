
#include "../include/Tank.h"
#include "../include/Weapons.h"

using namespace Tank;

//--------------------------------------------------------------------------------------------------------
TankV::TankV( TankController* _driver, const string& _url, int _health )
	: Movable( new SDL::FourDimensionsSpriteHandler( GLOBAL->getSurface("tank/"+_url+"/Body"), TILE_SIZE ), _health ),
		driver(_driver)
{
	(GLOBAL->getSurface("tank/"+_url+"/Body"))->setColorKey(0xff,0xff,0xff);
	lagartas.push( new BasicLagartas(_url) );
	for( int i=0; i < WEAPON_COUNT; ++i )
		weapons[i] = 0;
	currentWeapon = *weapons = new LitleFireWeapon(_url);
	weapons[1] = new LargeFireWeapon(_url);
	weapons[2] = new CannonWeapon(_url);
	driver->init(this);
}
	
//--------------------------------------------------------------------------------------------------------
TankV::~TankV()
{
	for( int i = 0; i < WEAPON_COUNT; ++i )
		if( 0 != weapons[i] )
			delete weapons[i];
	
	while( lagartas.size() > 0 ) {
		Lagartas* l = lagartas.top();
		lagartas.pop();
		delete l;
	}

	delete driver;
}

//--------------------------------------------------------------------------------------------------------
void TankV::setDirection( Direction* _dir )
{
	if( 0 != _dir ) {
		spriteHandler->setDirection(_dir);
		lagartas.top()->setDirection(_dir);
		for( int i = 0; i < WEAPON_COUNT; ++i ) {
			if( 0 != weapons[i] ) {
				weapons[i]->setDirection(_dir);
			}
		}
	} else {
		if( 0 != dir )
			lastDirection = dir;
	}
	dir = _dir;
}
//--------------------------------------------------------------------------------------------------------
bool TankV::fire()
{
	if( 0 != currentWeapon && currentWeapon->ready() ) {
		currentWeapon->fire(this);
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------------------------------
void TankV::onCollision( Actor* _other ) 
{ 
	lagartas.top()->onCollision(_other);
}

//---------------------------------------------------------------------------------------------------------
Point TankV::getNextPos()
{	
	int offset = lagartas.top()->getVelocity() - atrito;
	Point next( dir->getVector() * offset );
	next.translate(x,y);
	return next;
}

//--------------------------------------------------------------------------------------------------------------
void TankV::paint( Surface& _surface ) 
{
	spriteHandler->paintOn(x,y,_surface);
	lagartas.top()->paintOn(x,y,_surface);
	currentWeapon->paintOn(x,y,_surface);
}

//--------------------------------------------------------------------------------------------------------
void TankV::move()
{
	driver->moveTank(this);
}

//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
