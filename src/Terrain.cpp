
#include "../include/Terrain.h"
#include "../include/TerrainFactory.h"
#include "../include/Global.h"
#include "../include/Movable.h"

using namespace Tank;

/*** Terrain Factory's ***/
GrassFactory 		___grass___(Grass::ID);
ShadowGrassFactory	___shadowGrass___(ShadowGrass::ID);

GreenBoxFactory		___greenBox__(GreenBox::ID);

//--------------------------------------------------------------------------------------------------------------	
//	TerrainFactory
//--------------------------------------------------------------------------------------------------------------	
TerrainFactory::TerrainFactory(int _id) : id(_id)
{ 
	GLOBAL->registerTerrain(id,this); 
}

//--------------------------------------------------------------------------------------------------------------	
//	Terrain
//--------------------------------------------------------------------------------------------------------------	
Terrain::Terrain( const SpriteHandlerPointer& _sph, int _health )
	: Actor(_sph, _health) {}

//--------------------------------------------------------------------------------------------------------------	
Terrain::Terrain( const SpriteHandlerPointer& _sph, int _x, int _y, int _health )
	: Actor( _sph,  _x, _y, _health) {}
		
//--------------------------------------------------------------------------------------------------------------	
bool Terrain::canStepOver() const
{
	return getType() == MEDIUM_LEVEL;
}

//--------------------------------------------------------------------------------------------------------------	
void Terrain::onCollision( Actor* _other )
{
	assert( _other->isMovable() );
	reinterpret_cast<Movable*>(_other)->setAtrito( getAtrito() );
}

//--------------------------------------------------------------------------------------------------------------	
//	Grass
//--------------------------------------------------------------------------------------------------------------	
const string Grass::NAME("Grass");

const string ShadowGrass::NAME("ShadowGrass");

Grass::Grass() 
	: Terrain( new OneDimensionSpriteHandler( GLOBAL->getSurface(NAME), TILE_SIZE), getDefaultHealth()) {}

//--------------------------------------------------------------------------------------------------------------	
Grass::Grass( const string& _key  )
	: Terrain( new OneDimensionSpriteHandler(GLOBAL->getSurface(_key), TILE_SIZE, getDefaultHealth()), getDefaultHealth() ) {}


//--------------------------------------------------------------------------------------------------------------	
//	GreenBox
//--------------------------------------------------------------------------------------------------------------	
const string GreenBox::NAME("GreenBox");	
	
GreenBox::GreenBox() 
	: Terrain( new OneDimensionSpriteHandler( GLOBAL->getSurface(NAME), TILE_SIZE), getDefaultHealth()) {}

//--------------------------------------------------------------------------------------------------------------	
GreenBox::GreenBox( const string& _key )
	: Terrain( new OneDimensionSpriteHandler(GLOBAL->getSurface(_key), TILE_SIZE), getDefaultHealth() ) {}

//--------------------------------------------------------------------------------------------------------------
