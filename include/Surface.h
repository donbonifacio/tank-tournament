#ifndef _SDL_SURFACE_H_
#define _SDL_SURFACE_H_

#include "../include/Safe.h"

#include <string>
#include <list>
#include <SDL/SDL.h>

using std::string;
using std::list;

namespace SDL {

/* declarações */
class SpriteSequence;

//------------------------------------------------------------------------------------------------------------------------

class Surface {

protected:
	SDL_Surface* sdlSurfacePtr;		// SDL_Surface* associada
	SDL_Rect dim;					// dimensão (w,h) e posição actual (x,y) da 'sdlSurfacePtr'
	SDL_Rect blitRect;				// parte da 'sdlSurfacePtr' que será copiada

	/* métodos auxiliares */
	Uint32 getGoodFormatColor( Uint8 _r, Uint8 _g, Uint8 _b );
	SDL_Surface* getDisplayFormat( SDL_Surface* _surface );

public:

	/* ctors - dtors */
	Surface( SDL_Surface* _surface = 0 ) : sdlSurfacePtr(_surface) {}
	Surface( int _w, int _h ) : sdlSurfacePtr(0) { createSurface(_w,_h); }
	Surface( const Surface& _surface ) : sdlSurfacePtr(0) { *this = _surface; }
	Surface( const string& _file ) : sdlSurfacePtr(0) { load( _file.c_str() ); }
	Surface( const char* _file ) : sdlSurfacePtr(0) { load( _file ); }
	virtual ~Surface() { clear(); }

	/* operadores afectação. */
	Surface& operator=( const Surface& _surface );  
	Surface& operator=( SDL_Surface* _sdlSurface );
	Surface& operator=( const string& _file )		{ return load( _file.c_str() ); }
	Surface& operator=( const char* _file )			{ return load(_file); }
	Surface& load( const char* _file );
	Surface& load( const string& _file )			{ return load(_file.c_str()); }

	/* métodos relacionados com os Rect's */
	void setPos( int _x, int _y ) { dim.x = _x; dim.y = _y; }
	void setDim( int _w, int _h ) { dim.w = _w; dim.h = _h; blitRect.w = _w; blitRect.h = _h; }
	void setBlitRect( int _x, int _y, int _w, int _h ) { blitRect.x = _x; blitRect.y = _y; blitRect.w = _w; blitRect.h = _h; dim.w = _w; dim.h = _h; }
	void setBlitRectLocation( int _x, int _y ) { blitRect.x = _x; blitRect.y = _y; }
		
	// altera 'dim' e 'blitRect' com as dimensões de 'sdlSurfacePtr'
	void normalize();

	/* métodos para obter atributos da Surface */
	SDL_Surface* getSdlSurfacePtr() { return sdlSurfacePtr; }
	SDL_Rect*	 getDim() { return &dim; }
	SDL_Rect*	 getBlitRect() { return &blitRect; }
	Uint8		 getAlpha() const { return sdlSurfacePtr->format->alpha; }
	int			 getWidth() const { return dim.w; }
	int			 getHeight() const { return dim.h; }
	bool		 pointIn( int _x, int _y ) const;

	/* operações directas sobre a SDL_Surface */
	void clear();
	void blit( Surface& _surface );
	void blit( int _x, int _y, int size, Surface& _surface );
	void blit( SDL_Surface* _surface, SDL_Rect* _srcRect, SDL_Rect* _dstRect );
	void fill( Uint8 _r, Uint8 _g, Uint8 _b );
	void fill( Uint32 _color );
	void setAlpha( Uint8 _alpha, Uint32 _flags = SDL_SRCALPHA | SDL_RLEACCEL );
	void setNoAlpha() { setAlpha(SDL_ALPHA_OPAQUE,0); }
	void setColorKey( Uint8 _r, Uint8 _g, Uint8 _b );
	void setColorKey( Uint32 _color );
	void setNoColorKey();
	void createSurface(int _w, int _h, int _flags = SDL_SWSURFACE );
	bool lock();
	bool unlock();

	//--------------------------------------------------------------------------------------------
	/* o VC++ só suporta membros de template se eles estiverem definidos no body da class */
	template<typename Container>
	bool splitInSprites( Container& _seq, int _w, int _h, int _columms, int _lines ,int _dx = 0, int _dy = 0 )
	{
		/*
			Divide a Surface em '_columms'*'_lines' sprites cada qual com '_h'*'_w' de dimensão
			'_dx' e '_dy' são a distância em pixel's entre cada sprite
		*/

		// se não há qualquer surface ...
		assert(sdlSurfacePtr);

		// analizar os tamanhos passados com os de *this
		if( (_w + _dx) * _columms > sdlSurfacePtr->w ||
			(_h + _dy) * _lines > sdlSurfacePtr->h   )
			return false;

		// criar uma Surface temporária que irá contendo cada sprite
		Surface temp(_w,_h);

		// blitRect é a parte de 'sdlSurfacePtr' que será pintada, põe-se na primeira posição
		blitRect.x = 0;
		blitRect.y = 0;
		blitRect.w = _w;
		blitRect.h = _h;

		int c = 0, l = 0;
		for( ; l < _lines; ++l ){
			for( ; c < _columms ; ++c ){
				temp.blit(*this);
				_seq.push_back(temp);
				blitRect.x += _w + _dx;
			}
			blitRect.x = 0;
			blitRect.y += _h + _dy;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------
};

//-----------------------------------------------------------------------------------------------------------------------
}// namespace SDL

#endif /* _SDL_SURFACE_H_ */
