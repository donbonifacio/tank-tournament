/***************************************************************************
 *                                                                         *
 *                        Global.h
 *  *-- Descricao
 *
 *	Classe Singleton com várias funções auxiliares
 *
 *	*-- Detalhes      
 *                        
 *   begin                : Wed May 28 2003               
 *   copyright            : (C) 2003 by Pedro Santos                  
 *   homepage             : http://pdpsantos.sf.net                        *
 *   contact              : http://pdpsantos.sf.net/contacto.php           *
 *   Tank Tournament HP   : http://pdpsantos.sf.net/tank/ 	               *
 *                                                                         *
 * *-- Licence:                                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
 
#ifndef _TANK_GLOBAL_H_
#define _TANK_GLOBAL_H_

#include "Safe.h"
#include <map>
#include <string>
#include <ostream>
#include "SharedPointer.h"
#include "Surface.h"
#include "Ptrsolit.h"
#include "TerrainFactory.h"
#include "Log.h"
#include "Arena.h"

using std::map;
using std::ostream;
using std::string;
using Util::SharedPointer;
using SDL::Surface;
using Tank::TerrainFactory;
using Tank::Arena;

namespace Tank {
	
typedef SharedPointer<Surface> SurfacePointer;
typedef map<string,SurfacePointer> SurfaceMap;	
	
typedef map<int,TerrainFactory*> TerrainMap;

class Global {
	
	SurfaceMap surfaceMap;
	Arena* arena;
	TerrainMap terrainMap;
	Util::LogPtr logPtrDummy;
	
public:
	
	static const string IMG_DIR;
	static const string IMG_FORMAT;
	static const string EDITOR_CONFIG_FILE;
	
	Global();
	~Global();
	
	Surface* getSurface(const string& _key);
	void registerSurface( const string& _key, const string& _url );
	void registerSurface( const string& _key, const Surface& _surface );
	void printSurfaceMapOn( ostream& _so );

	TerrainFactory* getTerrainFactory(int _id);
	void registerTerrain(int _id, TerrainFactory* _creator);
	void printTerrainMapOn( ostream& _os );

	void generateEditorConfig() const;

	void setArena( Arena* _arena) { arena = _arena; }
	Arena* getArena();
	
};	

/* declaração do tipo pointer para o objecto solitário */
typedef Util::PtrSolitaireAutoDel<Global> GlobalPtr;

} //namespace Tank 


// por comodidade...
extern Tank::GlobalPtr globalPtr;
#define GLOBAL (globalPtr)
using Tank::Global;

#define ARENA (globalPtr->getArena())

#endif //_TANK_GLOBAL_H_
