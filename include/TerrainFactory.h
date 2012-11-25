/***************************************************************************
 *                                                                         *
 *                        TerrainFactory.h
 *  *-- Descricao
 *
 *	Conjunto de classes que criam terrenos
 *		Os objectos encontram-se declarados em Terrain.cpp
 *
 *	*-- Detalhes      
 *                        
 *   begin                : Wed May 28 2003               
 *   copyright            : (C) 2003 by Pedro Santos                  
 *   homepage             : http://pdpsantos.sf.net                        *
 *   contact              : http://pdpsantos.sf.net/contacto.php           *
 *   Tank Tournament HP   : http://pdpsantos.sf.net/tank/                  *
 *                                                                         *
 * *-- Licence:                                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _TERRAIN_FACTORY_H_
#define _TERRAIN_FACTORY_H_

#include <istream>
#include "Terrain.h"

using std::istream;

namespace Tank {

//--------------------------------------------------------------------------------------------------------------
class TerrainFactory {
	int id;
public:
	TerrainFactory(int _id);
	virtual bool evaluate( int _id ) const { return _id == id; };
	virtual Terrain* getTerrain() const = 0;
	virtual Terrain* getTerrain( istream& _is ) const = 0;
	virtual const string& getTerrainName() const = 0;
	virtual int getTerrainType() const = 0;
};

//--------------------------------------------------------------------------------------------------------------
struct GrassFactory : public TerrainFactory {
	GrassFactory(int _id) : TerrainFactory(_id) {}
	Terrain* getTerrain() const { return new Grass(); }
	Terrain* getTerrain( istream& _is ) const { return new Grass(); }
	const string& getTerrainName() const { return Grass::NAME; }
	int getTerrainType() const { return Grass::TYPE; }
};


//--------------------------------------------------------------------------------------------------------------
struct ShadowGrassFactory : public TerrainFactory {
	ShadowGrassFactory(int _id) : TerrainFactory(_id) {}
	Terrain* getTerrain() const { return new ShadowGrass(); }
	Terrain* getTerrain( istream& _is ) const { return new ShadowGrass(); }
	const string& getTerrainName() const { return ShadowGrass::NAME; }
	int getTerrainType() const { return ShadowGrass::TYPE; }
};

//--------------------------------------------------------------------------------------------------------------
struct GreenBoxFactory : public TerrainFactory {
	GreenBoxFactory(int _id) : TerrainFactory(_id) {}
	Terrain* getTerrain() const { return new ShadowGrass(); }
	Terrain* getTerrain( istream& _is ) const { return new GreenBox(); }
	const string& getTerrainName() const { return GreenBox::NAME; }
	int getTerrainType() const { return GreenBox::TYPE; }
};

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

}//namespace Tank {

#endif //_TERRAIN_FACTORY_H_
