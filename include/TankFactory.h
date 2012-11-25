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

class TerrainFactory {

	string key;
	bool evaluate( const string& _key ) { return key == _key; }
	Terrain* getTerrain() const { return new Grass(); }

};
