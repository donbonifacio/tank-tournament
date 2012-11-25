/***************************************************************************
 *                                                                         *
 *                        Terrain.h
 *  *-- Descricao
 *
 *	Classe base de todos os terreno do mapa e os tipos de terreno
 *
 *	*-- Criar novos terrenos
 *		1) Criar a classe derivada de Terrain (com um ID que não exista)
 *		2) Criar a classe derivada de TerrainFactory
 *		3) Criar no ficheiro Terrain.cpp uma instância desse objecto Factory
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
 
#ifndef _TANK_TERRAIN_H_
#define _TANK_TERRAIN_H_

#include "Actor.h" 

typedef Uint32 TerrainId;

/*
	funções para tratamentos dos id's
*/

// macros para as construçoes dos ID's
// três primeiros bits para o tipo:
// - LOW_LEVEL:		000
// - MEDIUM_LEVEL:	001
// - HIGH_LEVEL:	010
#define LOW_LEVEL_ID(id)	((TerrainId(id) << 3) | 0)
#define MEDIUM_LEVEL_ID(id)	((id << 3) | 1)
#define HIGH_LEVEL_ID(id)	((id << 3) | 2)

inline int getRawId( int _id )  { return _id >> 3; }
inline int getIdType( int _id ) { return TerrainId(0) & 7; }

namespace Tank {

//--------------------------------------------------------------------------------------------------------------	
class Terrain : public Actor {
	
public:
	
	enum Type {
		LOW_LEVEL,
		MEDIUM_LEVEL,
		HIGH_LEVEL
	};

	enum { ATRITO_INFINITO = -1 };

	Terrain( const SpriteHandlerPointer& _sph, int _health );
	Terrain( const SpriteHandlerPointer& _sph, int _x, int _y, int _health );

	bool canStepOver() const;
	bool isMovable() const { return false; }
	void onCollision( Actor* _other );

	virtual int getType() const = 0;
	virtual int getAtrito() const = 0;
	virtual const string& getName() const = 0;
};

//--------------------------------------------------------------------------------------------------------------	
struct Grass : public Terrain {
	
	static const string NAME;

	enum { 
		TYPE = MEDIUM_LEVEL,
		ID = MEDIUM_LEVEL_ID(1)
	};

	Grass();
	Grass( const string& _key );

	int getType() const			{ return TYPE;				}
	int getAtrito() const			{ return 0;					}
	int getDefaultHealth() const 	{ return NO_HEALTH; 		}
	bool setDamage( int _damage ) 	{ return isAlive(); 		}
	const string& getName() const 	{ return NAME;				}

};
//--------------------------------------------------------------------------------------------------------------	
struct ShadowGrass : public Grass {
	static const string NAME;
	enum { 
		TYPE = MEDIUM_LEVEL,
		ID = MEDIUM_LEVEL_ID(2)
	};
	ShadowGrass() : Grass(NAME) {}
	const string& getName() const 	{ return NAME;				}
};

//--------------------------------------------------------------------------------------------------------------	
struct GreenBox : public Terrain {
	
	static const string NAME;

	enum { 
		TYPE = HIGH_LEVEL,
		ID = HIGH_LEVEL_ID(1)
	};
	
	GreenBox();
	GreenBox( const string& _key );

	int getType() const				{ return TYPE;				}
	int getAtrito() const			{ return ATRITO_INFINITO;	}
	int getDefaultHealth() const 	{ return 100; 				}
	const string& getName() const 	{ return NAME;				}

};

//--------------------------------------------------------------------------------------------------------------	
//--------------------------------------------------------------------------------------------------------------	
//--------------------------------------------------------------------------------------------------------------	
//--------------------------------------------------------------------------------------------------------------	
//--------------------------------------------------------------------------------------------------------------	
//--------------------------------------------------------------------------------------------------------------	
//--------------------------------------------------------------------------------------------------------------	
//--------------------------------------------------------------------------------------------------------------	
} // namespace Tank
 
 
#endif //  _TANK_TERRAIN_H_
