/***************************************************************************
 *                                                                         *
 *                        Arena.h
 *  *-- Descricao
 *
 *	Classe que faz correr o jogo.
 *
 *	*-- Detalhes      
 *                        
 *   begin                : Wed May 28 2003               
 *   copyright            : (C) 2003 by Pedro Santos                  
 *
 *	 author:			  : Pedro Santos <pre@users.sf.net>
 *   homepage             : http://psantos.net						       *
 *   contact              : http://psantos..net/contacto.php	           *
 *   Tank Tournament HP   : http://tank-tournament.sf.net
 *                                                                         *
 * *-- Licence:                                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef _TANK_ARENA_H_
#define _TANK_ARENA_H_

#include "Safe.h"
#include <vector>
#include <list>
#include "Safe.h"
#include <set>
#include "Safe.h"
#include "Map.h"
#include "Screen.h"
#include "Point.h"
#include "Task.h"
#include "KeyHandler.h"

using SDL::Point;
using SDL::KeyHandler;
using SDL::Key;
using Tank::Task;

namespace Tank {

class Movable;

class Arena {
	
	typedef std::vector<Terrain*> ActorVector;
	typedef std::set<Task*> TaskList;
	typedef std::list<Terrain*> TerrainList;
	typedef std::list<KeyHandler*> KeyHandlerList;
	typedef std::list<TaskList::iterator> DeadTasks;
	
	const Map* map;
	const TerrainMatrix& matrix;
	TaskList tasks;
	KeyHandlerList keys;
	
	// retorna os 4 tiles em que o actor está contido
	void getSurrondings( TerrainList& _list, const Point& _point );
	
public:
	
	Arena( const Map* _map );
	
	void run();
	void drawTerrain();
	void drawTasks();

	Actor* getPos( Movable* _source );

	void registerTask( Task* _task );
	void unregisterTask( Task* _task );
	void registerKeyHandler( KeyHandler* _keyH );
	void step();
	void broadCastKey( Key _key, bool _pressed );

	int getTaksNumber() const { return tasks.size(); }
};

} //namespace Tank 

#endif //_TANK_ARENA_H_
