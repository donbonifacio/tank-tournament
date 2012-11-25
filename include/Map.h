/***************************************************************************
 *                                                                         *
 *                        Map.h
 *  *-- Descricao
 *
 *	Representação física de um Mapa, com todos os dados, 
 *	e que faz o seu load.
 *
 *	*-- Formato dos ficheiros .ttm (Tank Tournament Map)
 
 	Atributo		Tamanho (Bytes)		Descrição
	--------		---------------		---------
	MapNameSize		1					Tamanho da string com o nome do mapa
	MapName			-					Nome do mapa
	AuthorNameSize	1					Tamanho da string com o nome do autor
	AnthorName		-					Nome do Autor
	DescSize		1					Tamanho da string com a descrição do mapa
	Description		-					Descrição do Mapa	
	MapType			1					*** Tipo do mapa.
	MapVersion		1					Versão do Mapa
	EditorVersion	1					Versão do editor que criou o mapa
	DefaultTanks	1					Número de tanks para jogar por defeito
	MapWidth		1					Número de Colunas do mapa
	MapHeight		1					Número de Linhas do mapa
	MapData			MapWidth*MapHeight	Terrenos do mapa
 *
 *	*-- Detalhes      
 *                        
 *   begin                : Wed May 28 2003               
 *   copyright            : (C) 2003 by Pedro Santos                  
 *   homepage             : http://pdpsantos.sf.net                        *
 *   contact              : http://pdpsantos.sf.net/contacto.php           *
 *   Tank Tournament HP   : http://tank-tournament.sf.net                  *
 *                                                                         *
 * *-- Licence:                                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
 
#ifndef _TANK_MAP_H_
#define _TANK_MAP_H_

#include "Safe.h"
#include <vector>
#include "Safe.h"
#include <fstream>
#include <string>
#include "Terrain.h"
#include "Printable.h"

using std::vector;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::vector;

namespace Tank {

typedef SharedPointer<Terrain>	TerrainPtr;
typedef	vector<TerrainPtr>		TerrainVector;
typedef vector<TerrainVector>	TerrainMatrix;

class Map : public Printable {
	
	void resizeMatrix();
	Byte readByte();
	string readString();
	double readDouble();
	
	enum { TYPES = 1 };
	static const string typeDescriptions[TYPES];
	
public:

	enum Type {
		DM = 1
	};

	enum Mask {
		TYPE_MASK			= 0x00000007,
		ID_MASK				= 0x0000007F8,
		WAY_POINT_MASK		= 0x0000F800,
		COMPLETE_ID_MASK	= ID_MASK | TYPE_MASK
	};

	enum MaskShift {
		TYPE_SHIFT			= 0,
		ID_SHIFT			= 3,
		WAY_POINT_SHIFT		= ID_SHIFT + 8,
		COMPLETE_ID_SHIFT	= 8 + 3
	};
	
	string mapName;
	string authorName;
	string description;
	Type mapType;
	double mapVersion;
	double editorVersion;
	int defaultTanks;
	string fileName;
	fstream file;
	TerrainMatrix matrix;
	int mapWidth;
	int mapHeight;

public:
	
	Map( const string& _file ); 
	
	void loadHeader();
	void loadTerrain();
	void load();
		
	Type getType() const { return mapType; }
	int getWidth() const { return mapWidth * Actor::TILE_SIZE; }
	int getHeight() const { return mapHeight * Actor::TILE_SIZE; }

	const string& getTypeDescription(Type _type) const;
	const string& getTypeDescription() const;
	const TerrainMatrix& getTerrain() const { return matrix; }

	void printOn( ostream& _os ) const;

	static void writeSampleMap(const string& _fileName);
};

} // namespace Tank

#endif // END
