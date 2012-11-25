#include "../include/Bullet.h"
#include "../include/Explosion.h"

using namespace Tank;

//--------------------------------------------------------------------------------------------------------
//	Bullet
//--------------------------------------------------------------------------------------------------------
Bullet::Bullet( const string& _url, Direction* _dir, int _x, int _y, int _w, int _h, int _delay )
	: Movable( new SDL::FourDimensionsSpriteHandler( GLOBAL->getSurface(_url), TILE_SIZE ), getDefaultHealth(), _delay )
{
	(GLOBAL->getSurface(_url))->setColorKey(0,0,0);
	setBounds(_x,_y,_w,_h);
	setDirection(_dir);
}
	
//--------------------------------------------------------------------------------------------------------
void Bullet::onCollision( Actor* _other )
{
	if( _other->canStepOver() )
		return;
	_other->setDamage( getDamage() );
	createExplosion();
	die();
}

//--------------------------------------------------------------------------------------------------------
void Bullet::createExplosion()
{
	new Explosion( Explosion::VERY_LARGE, x, y );
}

//--------------------------------------------------------------------------------------------------------
Point Bullet::assertPoint() const
{
	Point point = dir->assertPoint();
	point /= Direction::TILE_SIZE;
	return point *= getSize();
}

//--------------------------------------------------------------------------------------------------------
void Bullet::paint( Surface& _surface )
{
	spriteHandler->partialPaintOn( getOffset() ,getSize(),x,y,_surface);
}

//--------------------------------------------------------------------------------------------------------
// SmallFireBullet

//--------------------------------------------------------------------------------------------------------
// LargeFireBullet 

//--------------------------------------------------------------------------------------------------------
// CannonBullet

//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
