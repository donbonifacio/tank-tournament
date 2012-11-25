#include <sstream>
#include "../include/Global.h"
#include "../include/Map.h"
#include <iostream>
using namespace std;
using namespace Tank;

IMPLEMENT_SOLITAIRE_AUTODEL(Global)

// Objecto global
Tank::GlobalPtr globalPtr;

const string Global::IMG_DIR("img/");
const string Global::IMG_FORMAT(".bmp");
const string Global::EDITOR_CONFIG_FILE("Editor.ini");

//-------------------------------------------------------------------------------------------------------------
Global::Global()
{
	LOG << "Tank::Global Singleton Created." << endl;
}
//-------------------------------------------------------------------------------------------------------------
Global::~Global()
{
	LOG << "Tank::Global Singleton Terminated" << endl;
}

//-------------------------------------------------------------------------------------------------------------
Surface* Global::getSurface(const string& _key)
{
	SurfaceMap::iterator iter = surfaceMap.find(_key);
	
	if( iter == surfaceMap.end() ) {
		registerSurface(_key, IMG_DIR + _key + IMG_FORMAT);
		return getSurface(_key);
	}

	return (iter->second);
}
	
//-------------------------------------------------------------------------------------------------------------
void Global::registerSurface( const string& _key, const string& _url )
{
	surfaceMap.insert( SurfaceMap::value_type(_key,SurfacePointer(new Surface(_url))) );
}

//-------------------------------------------------------------------------------------------------------------
void Global::registerSurface( const string& _key, const Surface& _surface )
{
	surfaceMap.insert(SurfaceMap::value_type(_key, SurfacePointer(new Surface(_surface)) ));
}

//-------------------------------------------------------------------------------------------------------------
void Global::printSurfaceMapOn( ostream& _os )
{
	_os << "|--SurfaceMap" << endl;
	for( SurfaceMap::iterator iter = surfaceMap.begin(); iter != surfaceMap.end(); ++ iter )
		_os << "  * " << iter->first << " <- " << iter->second << endl;
}

//-------------------------------------------------------------------------------------------------------------
TerrainFactory* Global::getTerrainFactory( int _id )
{
	TerrainMap::iterator iter = terrainMap.find(_id);
	if( iter == terrainMap.end() )
		return 0;
	return (iter->second);
}

//-------------------------------------------------------------------------------------------------------------
void Global::registerTerrain(int _id, TerrainFactory* _creator)
{
	assert( terrainMap.find(_id) == terrainMap.end() );
	terrainMap[_id] = _creator;
}

//-------------------------------------------------------------------------------------------------------------
void Global::printTerrainMapOn( ostream& _os )
{
	_os << "|--TerrainMap" << endl;
	for( TerrainMap::iterator iter = terrainMap.begin(); iter != terrainMap.end(); ++iter )
		_os << "  * " << iter->first << " <- " << iter->second << endl;
}

//-------------------------------------------------------------------------------------------------------------
Arena* Global::getArena()
{
	assert(arena);
	return arena;
}

//-------------------------------------------------------------------------------------------------------------
void Global::generateEditorConfig() const
{
	ofstream file(EDITOR_CONFIG_FILE.c_str());
	
	file << "# Tank Tournament "<< version << " Editor init File" << endl
		 << "ImageDir=" << IMG_DIR << endl
		 << "ImageFormat=" << IMG_FORMAT << endl
		 << "TerrainCount=" << terrainMap.size() << endl <<endl

		 << "# ID Masks and Shifts" << endl 
		 << "TypeMask=" << Map::TYPE_MASK << endl
		 << "TypeShift=" << Map::TYPE_SHIFT << endl
		 << "IdMask=" << Map::ID_MASK << endl
		 << "IdShift=" << Map::ID_SHIFT << endl
		 << "CompleteIdMask=" << Map::COMPLETE_ID_MASK << endl
		 << "CompleteIdShift=" << Map::COMPLETE_ID_SHIFT << endl
		 << "WayPointMask=" << Map::WAY_POINT_MASK << endl
		 << "WayPointShift=" << Map::WAY_POINT_SHIFT << endl << endl
		

		 << "# Table Format: <id>\t<name>\t<type>" << endl
		 << "# File = ImageDir + name + ImageFormat" << endl
		 << "# Type = { LOW_LEVEL, MEDIUM_LEVEL, HIGH_LEVEL }" << endl << endl;
	
	for( TerrainMap::const_iterator iter = terrainMap.begin(); iter != terrainMap.end(); ++iter ) {
		file << iter->first << "\t";
		file << iter->second->getTerrainName() << endl;
	}
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

