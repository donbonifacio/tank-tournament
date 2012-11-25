#include "../include/SpriteHandler.h"

using namespace SDL;

//---------------------------------------------------------------------------------------------------------------------------------------------------
SpriteHandler::SpriteHandler( Surface* _source, int _tileWidth, int _tileHeight ) 
	: source(_source), tileWidth(_tileWidth), tileHeight(_tileHeight), currentX(0), currentY(0) 
{
	assert(source);
	source->setBlitRect( 0, 0, tileWidth, tileHeight );
}
		
//---------------------------------------------------------------------------------------------------------------------------------------------------
SpriteHandler::SpriteHandler( Surface* _source, int _tileSize ) 
	: source(_source), tileWidth(_tileSize), tileHeight(_tileSize), currentX(0), currentY(0)
{
	assert(source);
	source->setBlitRect( 0, 0, tileWidth, tileHeight );
}
		
//---------------------------------------------------------------------------------------------------------------------------------------------------
void SpriteHandler::paintOn( int _actorLocationX, int _actorLocationY, Surface& _destination )
{	
	// actualizar as coordenadas / o tamanho
	// (esta surface pode ser partilhada por muitos SpriteHandler's)
#if UPDATE_SIZE_EVERY_PAINT
	source->setBlitRect( currentX, currentY, tileWidth, tileHeight );
#else
	source->setBlitRectLocation( currentX, currentY );
#endif
	
	source->setPos(_actorLocationX, _actorLocationY );
	_destination.blit(*source);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
void SpriteHandler::partialPaintOn( int _offset, int _size, int _actorLocationX, int _actorLocationY, Surface& _destination )
{
	//paintOn(_actorLocationX, _actorLocationY, _destination );
	source->setBlitRect( currentX + _offset, currentY + _offset, _size, _size );
	source->setPos( _actorLocationX, _actorLocationY );
	_destination.blit(*source);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
