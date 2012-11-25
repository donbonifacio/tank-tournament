
#include <sstream>
#include <iostream>
#include "../include/Map.h"
#include "../include/Global.h"
#include "../include/Safe.h"
#include "../include/Exceptions.h"
#include "../include/TerrainFactory.h"

using namespace Tank;
using namespace std;
using std::stringstream;

const string Map::typeDescriptions[TYPES] = { "Death Match" };

//-------------------------------------------------------------------------------------------------------------
Map::Map( const string& _file )
	: fileName(_file), file(_file.c_str(), std::ios::in | std::ios::binary), matrix(0), mapWidth(-1), mapHeight(-1) 
{
	if( !file )
		throw Util::FileNotFoundException(fileName);
}
	
//-------------------------------------------------------------------------------------------------------------
void Map::loadHeader()
{
	LOG << "Loading " << fileName << " Header... [";
	LOG.flush();
	mapName = readString();				LOG << "=";
	authorName  = readString();			LOG << "=";
	description = readString();			LOG << "=";
	mapType = (Type)readByte();			LOG << "=";
	mapVersion = readDouble();;			LOG << "=";
	editorVersion = readDouble();		LOG << "=";
	defaultTanks = readByte();			LOG << "=";
	mapWidth = readByte();				LOG << "=";
	mapHeight = readByte();				LOG << "=";	LOG << "=";
	LOG << "] Complete!" << endl;
}
		
//-------------------------------------------------------------------------------------------------------------
void Map::loadTerrain()
{
	resizeMatrix();
	const int TILE_SIZE = Actor::TILE_SIZE;
	int x = 0, y = 0;
	
	LOG << "Loadding " << fileName << " Terrain... ";
	for( TerrainMatrix::iterator line = matrix.begin(); line != matrix.end(); ++line, ++y ) {
		for( TerrainVector::iterator collum = line->begin(); collum != line->end(); ++collum, ++x ) {
			TerrainId id;
			file.read( (char*)&id, sizeof(TerrainId) );

			id &= COMPLETE_ID_MASK;
	
			TerrainFactory* terrainFactory = GLOBAL->getTerrainFactory(id);
			if( 0 == terrainFactory ) {
				stringstream sstr;
				sstr << "Terrain ID: " << (int)id << "("<< getRawId(id) <<"'"<< getIdType(id) << ") not registred!";
				throw Util::GeneralException(sstr.str());
			}
	
			Terrain* terrain = terrainFactory->getTerrain(file);
			*collum = terrain;
			terrain->setLocation( x * TILE_SIZE, y * TILE_SIZE );
		}
		x = 0;
	}

	LOG << "Done" << endl;	
}

//-------------------------------------------------------------------------------------------------------------
void Map::load()
{
	loadHeader();
	loadTerrain();
}

//-------------------------------------------------------------------------------------------------------------
void Map::resizeMatrix()
{
	LOG << "Resizing Terrain Matrix... "; LOG.flush();
	matrix.clear();
	matrix.reserve(mapHeight);
	matrix.resize(mapHeight);
	/*for( TerrainMatrix::iterator iter = matrix.begin(); iter != matrix.end(); ++iter ) {
		cout << "BUU 3" << endl;
		iter->clear();
		cout << "BUU 4" << endl;
		iter->reserve(mapWidth);
		cout << "BUU 5" << endl;
		iter->resize(mapWidth);
		cout << "BUU 5" << endl;
	}*/
	for(unsigned i = 0; i < matrix.size(); ++i ) {
		for( int j = 0; j < mapWidth; ++j )
			matrix[i].push_back(0);
		/*cout << "BUU 3 " << endl;
		matrix[i].clear();
		cout << "BUU 4 " << endl;
		matrix[i].reserve(mapWidth +8);
		cout << "BUU 5 " << endl;
		matrix[i].resize(mapWidth);*/
		
	}
	LOG << "Done" << endl;
}

//-------------------------------------------------------------------------------------------------------------	
Byte Map::readByte()
{
	char byte;
	file.read(&byte,sizeof(char));
	assert(file.good());
	return byte;
}

//-------------------------------------------------------------------------------------------------------------
string Map::readString()
{
	static char buffer[200];
	Byte size = readByte();
	file.read( buffer, size );
	assert(file.good());
	return string(buffer);
}

//-------------------------------------------------------------------------------------------------------------
double Map::readDouble()
{
	double dummy;
	file.read( (char*)&dummy, sizeof(double) );
	assert(file.good());
	return dummy;
}
//-------------------------------------------------------------------------------------------------------------
void Map::writeSampleMap(const string& _fileName)
{
	ofstream ofs(_fileName.c_str(), std::ios::out | std::ios::binary);

	string mName = "DM-Teste.ttm";
	string author = "Pedro Santos";
	string description = "Mapa de teste!";
	Type type = DM;
	double mVersion = 0.6;
	double eVersion = 0.0;
	Byte dTanks = 2;
	const Byte w = 8;
	const Byte h = 7;

	LOG << "Generating " << mName << "... ";
	
	Byte buu = mName.size();
	ofs.write( (char*)&buu, sizeof(Byte) );
	ofs.write( mName.c_str(), mName.size() );
	
	buu = author.size();
	ofs.write( (char*)&buu, sizeof(Byte));
	ofs.write( author.c_str(), author.size() );
	
	buu = description.size();
	ofs.write( (char*)&buu, sizeof(Byte));
	ofs.write( description.c_str(), description.size() );
	

	ofs.write( (char*)&type, sizeof(Byte));
	
	ofs.write( (char*)&mVersion, sizeof(double) );
	ofs.write( (char*)&eVersion, sizeof(double) );
	
	ofs.write( (char*)&dTanks, sizeof(Byte) );
	
	ofs.write( (char*)&w, sizeof(Byte) );
	ofs.write( (char*)&h, sizeof(Byte) );
	
	TerrainId terrain[w*h] = {
		HIGH_LEVEL_ID(1), 	HIGH_LEVEL_ID(1), 	HIGH_LEVEL_ID(1), 	HIGH_LEVEL_ID(1), 	HIGH_LEVEL_ID(1), 	HIGH_LEVEL_ID(1),	HIGH_LEVEL_ID(1),	HIGH_LEVEL_ID(1),	
HIGH_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(2), 	MEDIUM_LEVEL_ID(2), 	MEDIUM_LEVEL_ID(2), 	MEDIUM_LEVEL_ID(2),		HIGH_LEVEL_ID(1), MEDIUM_LEVEL_ID(2), 	HIGH_LEVEL_ID(1),
HIGH_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(2), 	MEDIUM_LEVEL_ID(1),	HIGH_LEVEL_ID(1),
HIGH_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(1), 	HIGH_LEVEL_ID(1),  	MEDIUM_LEVEL_ID(1), 	HIGH_LEVEL_ID(1), 	HIGH_LEVEL_ID(1), 	HIGH_LEVEL_ID(1), 	HIGH_LEVEL_ID(1), 
HIGH_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(2), 	MEDIUM_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(2), 	MEDIUM_LEVEL_ID(2), 	MEDIUM_LEVEL_ID(2),	HIGH_LEVEL_ID(1),
HIGH_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(1), 	HIGH_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(1), 	MEDIUM_LEVEL_ID(1),	HIGH_LEVEL_ID(1),
HIGH_LEVEL_ID(1), 	HIGH_LEVEL_ID(1), 	HIGH_LEVEL_ID(1), 	HIGH_LEVEL_ID(1), 	HIGH_LEVEL_ID(1),	HIGH_LEVEL_ID(1),	HIGH_LEVEL_ID(1),	HIGH_LEVEL_ID(1)
	};
	ofs.write( (char*)terrain, sizeof(TerrainId) * w * h );

	LOG << "Done" << endl;
}

//-------------------------------------------------------------------------------------------------------------
void Map::printOn( ostream& _os ) const
{	
	_os << "|--Map " << mapName << endl
		<< "   Anthor: " << authorName << endl
		<< "   Description: " << description << endl
		<< "   Map Type: " << mapType << endl
		<< "   Map Version: " << mapVersion << endl
		<< "   Editor Version: " << editorVersion << endl
		<< "   Default Tanks: " << defaultTanks << endl
		<< "   Map Size: " << mapWidth << "*" << mapHeight << " - " << matrix.size() << "*"<< matrix[0].size()<< endl;
	
	_os << "   Data:" << endl;
	for( TerrainMatrix::const_iterator line = matrix.begin(); line != matrix.end(); ++line ) {
		for( TerrainVector::const_iterator collum = line->begin(); collum != line->end(); ++collum ) {
			_os << &(*collum) << '\t';
		}
		_os << endl;
	}
}

//-------------------------------------------------------------------------------------------------------------
const string& Map::getTypeDescription(Type _type) const
{
	int type = (int)_type - 1;
	assert( (type >= 0) && (type < TYPES) );
	return typeDescriptions[type];
}

//-------------------------------------------------------------------------------------------------------------
const string& Map::getTypeDescription() const
{
	return getTypeDescription(mapType);
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
