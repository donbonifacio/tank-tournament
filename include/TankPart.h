/***************************************************************************
 *                                                                         *
 *                        TankPart.h
 *  *-- Descricao
 *
 *	Diferentes partes de um tank
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
 
#ifndef _TANK_PART_H_
#define _TANK_PART_H_

#include <string>
#include "Actor.h"
#include "Global.h"
#include "Surface.h"
#include "SpriteHandler.h"
#include "SharedPointer.h"

using SDL::Surface;
using SDL::SpriteHandler;
using SDL::FourDimensionsSpriteHandler;
using Util::SharedPointer;
using std::string;

namespace Tank {

class TankPart {
public:
	typedef SharedPointer<SpriteHandler> SpriteHandlerPointer;

protected:	
	SpriteHandlerPointer spriteHandler;

public:

	TankPart( const string& _tank, const string& _file )
		: spriteHandler( new FourDimensionsSpriteHandler(GLOBAL->getSurface("tank/"+_tank+"/"+_file), Actor::TILE_SIZE ) )
	{
		GLOBAL->getSurface("tank/"+_tank+"/"+_file)->setColorKey(0xff,0xff,0xff );
	}

	virtual ~TankPart() {}

	void paintOn( int _x, int _y, Surface& _surf ) {
		spriteHandler->paintOn(_x,_y,_surf);
	}

	void setDirection( Direction* _dir ) {
		spriteHandler->setDirection(_dir);
	}
};

}

#endif // _TANK_PART_H_ FILE

