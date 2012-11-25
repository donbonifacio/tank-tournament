#include "../include/Safe.h"
#include "../include/Arena.h"
#include "../include/Task.h"
#include "../include/BaseTank.h"
#include "../include/Tank.h"
#include "../include/Bullet.h"
#include "../include/Movable.h"
#include "../include/Screen.h"
#include "../include/HumanDriver.h"
#include "../include/Enemy.h"

#include <iostream>
using namespace std;

using namespace Tank;

#ifdef USING_OLD_VS
template<typename T>
inline T& min( const T& t1, const T& t2 ) {
	return (t1<t2) ? t1 : t2;
}
#endif

//---------------------------------------------------------------------------------------------------------
Arena::Arena( const Map* _map ) : map(_map), matrix(_map->getTerrain())
{
	assert(map);
	GLOBAL->setArena(this);
	LOG << map->getTypeDescription() << " Arena created." << endl;
}

//---------------------------------------------------------------------------------------------------------
void Arena::run()
{	
/**/	HumanDriver* tankC = new HumanDriver();
	TankV* tank = new TankV(tankC,"prototype");
	tankC->setTank(tank);
	tankC->setKey(UP,SDLK_u);
	tankC->setKey(DOWN,SDLK_j);
	tankC->setKey(LEFT,SDLK_h);
	tankC->setKey(RIGTH,SDLK_k);

	tankC->setKey(FIRE1,SDLK_1);
	tankC->setKey(FIRE2,SDLK_2);
	tankC->setKey(FIRE3,SDLK_3);
	tankC->setKey(FIRE,SDLK_SPACE);

	tank->setLocation(1*32,2*32);

/*	HumanDriver* tankC2 = new HumanDriver();
	TankV* tankv = new TankV(tankC2,"prototype");
	tankv->setLocation(1*32,1*32);*/

/**/TankV* tank2 = new TankV( new Enemy(), "prototype" );
	tank2->setLocation(3*32,2*32);	

	TankV* tank3 = new TankV( new Enemy(), "prototype" );
	tank3->setLocation(3*32,1*32);	

//	new CannonBullet( Direction::rigth(), 37,37 );

	drawTerrain();
	SDL_Event event;
	for(;;){

		while ( SDL_PollEvent(&event) ) {
			switch (event.type) {
				
				case SDL_KEYDOWN:
					if( event.key.keysym.sym == SDLK_ESCAPE )
						return;
					if( event.key.keysym.sym == SDLK_F10 )
						SCR->toggleFullScreenMode();
					broadCastKey(event.key.keysym.sym,true);
			  	break;
				
				case SDL_KEYUP:
					broadCastKey(event.key.keysym.sym,false);
			  	break;
				
				case SDL_MOUSEMOTION:
					
					break;
				case SDL_MOUSEBUTTONDOWN:
					
					break;
				case SDL_QUIT:
					return;
			}
		}
		step();
		
		drawTerrain();
		drawTasks();
	
		SCR->flip();
    }
}

//---------------------------------------------------------------------------------------------------------
void Arena::drawTerrain()
{
	for( TerrainMatrix::const_iterator line = matrix.begin(); line != matrix.end(); ++line ) {
		for( TerrainVector::const_iterator collum = line->begin(); collum != line->end(); ++collum ) {
			(*collum)->paint();
		}
	}
}

//---------------------------------------------------------------------------------------------------------
void Arena::drawTasks()
{
	for( TaskList::const_iterator task = tasks.begin(); task != tasks.end(); ++task ) {
		(*task)->show();
	}
}

//---------------------------------------------------------------------------------------------------------
void Arena::step()
{
	DeadTasks deadTasks;
	for( TaskList::iterator task = tasks.begin(); task != tasks.end(); ++task ) {
		(*task)->step();
		if( (*task)->isDead() )
			deadTasks.push_back(task);
	}

	for( DeadTasks::iterator it = deadTasks.begin(); it != deadTasks.end(); ++it ) {
		tasks.erase(*it);
		delete **it;
	}
}

//---------------------------------------------------------------------------------------------------------
Actor* Arena::getPos( Movable* _source )
{
	// ver os Terrain
	TerrainList terrainSurrondings;
	Point pos = _source->assertPoint() + _source->getNextPos();
	Point matrixPos = pos / Actor::TILE_SIZE;

	// testar se o actor está dentro do mapa
	assert( min<int>(matrixPos.x, matrixPos.y) >= 0 );
//	assert( matrixPos < Point(map->getHeight(),map->getWidth()) );
	
	getSurrondings( terrainSurrondings, matrixPos );

	Rectangle rect( _source->getNextPos(), _source->getSize() );
	
	for( TerrainList::const_iterator iter = terrainSurrondings.begin(); iter != terrainSurrondings.end(); ++ iter ) {
		if( (!(*iter)->canStepOver()) && (*iter)->intersects(rect) ) {
			return *iter;
		}
	}

	// agora ver se choca com um task

	// aumentar o tamanho (porque o Rectangle::contains não
	// tem em conta as margens)
//	rect.setDimension( rect.w + 1, rect.h + 1);
//	rect.setLocation( rect.x - 1, rect.y - 1 );
	Actor* asker = _source;

	for( TaskList::iterator it = tasks.begin(); it != tasks.end(); ++it ) {
		if( asker != (*it)->getSource() && rect.intersects( (*it)->getRectangle() ) ){
			if( (*it)->isAlive() )
				return (*it)->getSource();
		}
	}

	// não choca com nada, retorna o terreno onde está
	TerrainPtr ptr = matrix[matrixPos.y][matrixPos.x];
	Terrain* t = ptr;
	
	return t;
}

//---------------------------------------------------------------------------------------------------------
void Arena::getSurrondings( TerrainList& _list, const Point& _point )
{
	for( int i = 0; i < 2; ++i ) {
		for( int j = 0; j < 2; ++j ) {
			if( (_point.y+i) >= map->mapHeight || (_point.x+j) >= map->mapWidth ) 
				continue;
			TerrainPtr ptr = matrix[_point.y + i][_point.x + j];
			Terrain* t = ptr;
			_list.push_back(t);
		}
	}
}

//---------------------------------------------------------------------------------------------------------
void Arena::registerTask( Task* _task )
{
	tasks.insert(_task);
}

//---------------------------------------------------------------------------------------------------------
void Arena::unregisterTask( Task* _task )
{
	TaskList::iterator it = tasks.find(_task);
	if( it != tasks.end() )
		tasks.erase(_task);
}

//---------------------------------------------------------------------------------------------------------
void Arena::registerKeyHandler( KeyHandler* _keyH )
{
	keys.push_back(_keyH);
}

//---------------------------------------------------------------------------------------------------------
void Arena::broadCastKey( Key _key, bool _pressed )
{
	for( KeyHandlerList::const_iterator iter = keys.begin(); iter != keys.end(); ++iter ) 
		if( _pressed )
			(*iter)->keyPressed(_key);
		else
			(*iter)->keyReleased(_key);
}

//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
