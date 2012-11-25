/***************************************************************************
 *                                                                         *
 *                        Screen.h
 *  *-- Descricao
 *
 *	Ecrã de uma aplicação SDL. É um singleton, é a 'Surface' onde devem ser
 *	pintadas as outras surfaces que se pretendem mostrar.
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

#ifndef _SDL_SCREEN_H_
#define _SDL_SCREEN_H_

#include <string>
#include <SDL/SDL.h>

#include "Surface.h"
#include "Ptrsolit.h"
#include "Printable.h"

using std::string;

namespace SDL {

//------------------------------------------------------------------------------------------------------------------------

class Screen : public Surface, public Printable {
	
	static const string FULL_SCREEN_TEXT;
	static const string WINDOW_TEXT;
	const string& getScreenText();
	Util::LogPtr dummy;
	
public:
	
	enum VideoMode {
		WINDOW,
		FULLSCREEN
	};

	Screen();
	~Screen();
	void init( Uint32 _flags = SDL_INIT_VIDEO );
	void setVideoMode( int _w, int _h, VideoMode _videoMode = WINDOW );
	void flip();
	bool isReady() const { return SDL_GetVideoSurface() != 0; }
	void toggleFullScreenMode();
	void setCaption( const string& _caption );
	void setWindowIcon( const string& _file );
	void printOn( ostream& _os ) const;
};

/* declaração do tipo pointer para o objecto solitário */
typedef Util::PtrSolitaireAutoDel<Screen> ScreenPtr;

//------------------------------------------------------------------------------------------------------------------------

}// namespace SDL


// por comodidade...
extern SDL::ScreenPtr screenPtr;
#define SCR (screenPtr)
using SDL::Screen;

#endif /* _SDL_SCREEN_H_ */
