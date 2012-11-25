#include "../include/Surface.h"
#include "../include/SpriteSequence.h"
#include "../include/Exceptions.h"
#include "../include/Log.h"

using namespace SDL;
using std::endl;

//-----------------------------------------------------------------------------------------------------------------------
// MÉTODOS PUBLICOS
//-----------------------------------------------------------------------------------------------------------------------
Surface& Surface::operator=( const Surface& _surface )
{
	/*
		Coloca *this exactamente igual a '_surface', copiando a 'sdlSurfacePtr' associada
	*/

	// ver se 'sdlSurfacePtr' está a apontar para algum lado, se estiver, deixa de estar
	clear();

	// agora passa-se à cópia da SDL_Surface:	
	sdlSurfacePtr = getDisplayFormat( _surface.sdlSurfacePtr );

	// actualizar os valores de 'dim'
	setPos( _surface.dim.x, _surface.dim.y );
	setDim( _surface.dim.w, _surface.dim.h );

	// actualizar o 'blitRect'
	setBlitRect( 
		_surface.blitRect.x,
		_surface.blitRect.y,
		_surface.blitRect.w,
		_surface.blitRect.h
	);

	return *this;
}
//-----------------------------------------------------------------------------------------------------------------------
Surface& Surface::operator=( SDL_Surface* _sdlSurface )
{
	/*
		Coloca *this exactamente igual a '_sdlSurface', copiando a '_sdlSurface'
	*/

	// ver se 'sdlSurfacePtr' está a apontar para algum lado, se estiver, deixa de estar
	clear();

	// agora passa-se à cópia da SDL_Surface:
	sdlSurfacePtr = getDisplayFormat( _sdlSurface );

	// Como uma SDL_Surface não tem os atributos da SDL::Surface estes serão normalizados
	normalize();

	// e por fim por a posição a (0,0) - a única coisa que o normalize() não faz
	setPos(0,0);

	return *this;
}
//-----------------------------------------------------------------------------------------------------------------------
Surface& Surface::load( const char* _file )
{
	/*
		Lê para uma Surface o conteúdo do ficheiro passado (BMP)
	*/

	// ver se foi mesmo passada uma string
	assert(_file);
	
	LOG << "Loading " << _file << "... ";
	
	clear();

	// tenta ler
	SDL_Surface* image = SDL_LoadBMP( _file );

	// se ocorrer algum erro throw
	if( 0 == image )
        throw Util::FileNotFoundException(string(_file),SDL_GetError());
	
	// criar a surface no mesmo formato da surface de ecrã
	sdlSurfacePtr = getDisplayFormat(image);
	SDL_FreeSurface(image);
	
	// por os Rect's como deve ser
	normalize();

	// po-lo no sitio certo
	setPos(0,0);

	LOG << "OK" << endl;

	return *this;
}
//-----------------------------------------------------------------------------------------------------------------------
void Surface::normalize()
{
	/* 
		Este método altera os atributos de 'dim' e 'blitRect' passando estes a fica com as dimensões da 'sdlSurfacePtr'
	*/

	// verificar se existe alguma surface
	assert(sdlSurfacePtr);

	// alterar a dimensão do SDL_Rect principal
	setDim( sdlSurfacePtr->w, sdlSurfacePtr->h );

	// alterar o blitRect para que contenha toda a Surface
	setBlitRect( 0, 0, sdlSurfacePtr->w, sdlSurfacePtr->h );
}
//-----------------------------------------------------------------------------------------------------------------------
void Surface::clear()
{
	/*
		Desaloja a 'sdlSurfacePtr'
	*/

	if(sdlSurfacePtr)
		SDL_FreeSurface(sdlSurfacePtr);
	
	sdlSurfacePtr = 0;
}
//-----------------------------------------------------------------------------------------------------------------------
bool Surface::pointIn( int _x, int _y ) const
{
	/*
		Indica se um ponto está ou não dentro desta surface
	*/
	if( _x >= dim.x && _x <= dim.x + dim.w )
		if( _y >= dim.y && _y <= dim.y + dim.h )
			return true;
	return false;
}
//-----------------------------------------------------------------------------------------------------------------------
void Surface::blit( Surface& _surface )
{
	/*
		Pinta nesta Surface a '_surface' passada como parametro
	*/

	// verificar se existe alguma surface
	assert(sdlSurfacePtr);
	assert(_surface.sdlSurfacePtr);
	
	blit( _surface.sdlSurfacePtr, &_surface.blitRect, &_surface.dim );
}
//-----------------------------------------------------------------------------------------------------------------------
void Surface::blit( SDL_Surface* _surface, SDL_Rect* _srcRect, SDL_Rect* _dstRect )
{
	/*
		Pinta a SDL_Surface* '_surface' em 'sdlSurfacePtr'
	*/
	SDL_BlitSurface(_surface, _srcRect, sdlSurfacePtr, _dstRect);
}
//-----------------------------------------------------------------------------------------------------------------------
void Surface::fill( Uint8 _r, Uint8 _g, Uint8 _b )
{
	/*
		Preenche o correspondente a 'blitRect' na 'sdlSurfacePtr' de uma só cor: (_r,_g,_b)
	*/

	// verificar se existe alguma surface
	assert(sdlSurfacePtr);

	SDL_FillRect( sdlSurfacePtr, &blitRect, getGoodFormatColor(_r,_g,_b) );
}
//-----------------------------------------------------------------------------------------------------------------------
void Surface::fill( Uint32 _color )
{
	/*
		Preenche o correspondente a 'blitRect' na 'sdlSurfacePtr' de uma só cor: 'color'
		Usa void Surface::fill( Uint8 _r, Uint8 _g, Uint8 _b );
	*/
	fill( 
		(_color & 0xFF0000) >> sdlSurfacePtr->format->Rshift,	// colocar red no sitio certo
		(_color & 0x00FF00) >> sdlSurfacePtr->format->Gshift,	// colocar green no sitio certo
		(_color & 0x0000FF) >> sdlSurfacePtr->format->Bshift	// colocar blue no sitio certo
	);
}
//-----------------------------------------------------------------------------------------------------------------------
void Surface::setAlpha( Uint8 _alpha, Uint32 _flags )
{
	/*
		Faz com que a Surface utilize o alpha channel
	*/

	// verificar se existe alguma surface
	assert(sdlSurfacePtr);

	SDL_SetAlpha(sdlSurfacePtr, _flags, _alpha);
}
//-----------------------------------------------------------------------------------------------------------------------
void Surface::setColorKey( Uint8 _r, Uint8 _g, Uint8 _b )
{
	/*
		Fixa uma cor como transparente
	*/

	// verificar se existe alguma surface
	assert(sdlSurfacePtr);

	SDL_SetColorKey(sdlSurfacePtr, SDL_SRCCOLORKEY | SDL_RLEACCEL, getGoodFormatColor(_r,_g,_b) );
}

//-----------------------------------------------------------------------------------------------------------------------
void Surface::setNoColorKey()
{
	/*
		Elimina a colorkey currente
	*/

	// verificar se existe alguma surface
	assert(sdlSurfacePtr);

	SDL_SetColorKey(sdlSurfacePtr, 0, 0);
}
//-----------------------------------------------------------------------------------------------------------------------
void Surface::createSurface(int _w, int _h, int _flags )
{
	/*
		Cria uma nova 'sdlSurfacePtr' com '_w' * '_h' de dimensão
		compatível com a surface de display
	*/

	// apaga a surface currente
	clear();


	SDL_PixelFormat* format = SDL_GetVideoSurface()->format;
    sdlSurfacePtr = SDL_CreateRGBSurface(_flags, _w, _h, format->BitsPerPixel,
                                   format->Rmask, format->Gmask, format->Bmask, format->Amask);
    if(0 == sdlSurfacePtr)
		throw Util::GeneralError("Error creating SDL_Surface*: ", SDL_GetError());

	setPos(0,0);
	normalize();
}

//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//	MÉTODOS PRIVADOS
//-----------------------------------------------------------------------------------------------------------------------
Uint32 Surface::getGoodFormatColor( Uint8 _r, Uint8 _g, Uint8 _b )
{
	/*
		Retorna a cor passada no formato da SDL_Surface* 'sdlSurfacePtr'
	*/

	// verificar se existe alguma surface
	assert(sdlSurfacePtr);

	return SDL_MapRGB (sdlSurfacePtr->format, _r, _g, _b );	

}
//-----------------------------------------------------------------------------------------------------------------------
SDL_Surface* Surface::getDisplayFormat( SDL_Surface* _surface )
{
	/*
		Retorna uma nova SDL_Surface* criada através da SDL_Surface* '_surface'
	*/

	// verificar se existe alguma surface
	assert(_surface);
	
	SDL_Surface* a = SDL_DisplayFormat( _surface );
	if( 0 == a )
        throw Util::GeneralException("Erro no SDL_DisplayFormat",SDL_GetError());
	return a;

}
//-----------------------------------------------------------------------------------------------------------------------
bool Surface::lock()
{
	if( SDL_MUSTLOCK(sdlSurfacePtr) ) {
		if( SDL_LockSurface(sdlSurfacePtr) == 0 )
			return true;
		return false;
	}
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------
bool Surface::unlock()
{
	if( SDL_MUSTLOCK(sdlSurfacePtr) ) 
		SDL_UnlockSurface(sdlSurfacePtr);
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------
