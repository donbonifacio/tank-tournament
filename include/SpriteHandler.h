/***************************************************************************
 *                                                                         *
 *                        SpriteHandler.h
 *  *-- Descricao
 *
 *	*) SpriteHandler:
 *		Classe base para gestão de sprites contidas numa só SDL::Surface
 *	*) OneDimensionSpriteHandler:
 *		Só suporta sprites numa só imagem (na horizontal), numa direcção
 *	*) FourDimensionSpriteHandler:
 *		Suporta as quatro direcções
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
 
#ifndef _SPRITE_HANDLER_H_
#define _SPRITE_HANDLER_H_

#include "Surface.h"
#include "Exceptions.h"
#include "Direction.h"

#include <iostream>
using namespace std;

using Tank::Direction;

namespace SDL {

// macro que deve estar a um caso se queria actualizar
// o blitrect da surface a ser usada a cada paint	
#define UPDATE_SIZE_EVERY_PAINT 0
	
class SpriteHandler {

protected:
	
	Surface* source;
	int tileWidth;
	int tileHeight;
	int currentX;
	int currentY;

public:
	
	SpriteHandler( Surface* _source, int _tileWidth, int _tileHeight );
	SpriteHandler( Surface* _source, int _tileSize );

	int getWidth() { return source->getSdlSurfacePtr()->w; }
	int getheigth() { return source->getSdlSurfacePtr()->h; }

	virtual	void step() {
		if( (currentX += tileWidth) >= getWidth() )
			currentX = 0;
	}

	void paintOn( int _actorLocationX, int _actorLocationY, Surface& _destination );
	void partialPaintOn( int _offset, int _size, int _actorLocationX, int _actorLocationY, Surface& _destination );

	virtual void setDirection( Direction* _dir ) = 0;
	virtual void nextDirection() = 0;
};

//--------------------------------------------------------------------------------------------------------------

class OneDimensionSpriteHandler : public SpriteHandler {
	
public:
	
	OneDimensionSpriteHandler( Surface* _source, int _tileWidth, int _tileHeight ) 
		: SpriteHandler(_source,_tileWidth,_tileHeight) {}
			
	OneDimensionSpriteHandler( Surface* _source, int _tileSize )
		: SpriteHandler(_source,_tileSize) {}

	void setDirection( Direction* _dir ) {
		throw Util::GeneralException("OneDimensionSpriteHandler::setDirection called!");
	}

	void nextDirection() {
		throw Util::GeneralException("OneDimensionSpriteHandler::nextDirection called!");
	}

};


//--------------------------------------------------------------------------------------------------------------

class FourDimensionsSpriteHandler : public SpriteHandler {
	
public:
	
	FourDimensionsSpriteHandler( Surface* _source, int _tileWidth, int _tileHeight ) 
		: SpriteHandler(_source,_tileWidth,_tileHeight) {}
			
	FourDimensionsSpriteHandler( Surface* _source, int _tileSize )
		: SpriteHandler(_source,_tileSize) {}

	void setDirection( Direction* _dir ) {
		Direction::Type type = _dir->getType();
		currentY = (int)type * tileHeight;
		if( currentY >= getheigth() )
			currentY = 0;
	}

	void nextDirection() {
		currentY *= tileHeight;
		if( currentY >= getheigth() )
			currentY = 0;
	}
};

//--------------------------------------------------------------------------------------------------------------


} // namespace SDL


#endif //_SPRITE_HANDLER_H_
