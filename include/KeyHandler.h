/***************************************************************************
 *                                                                         *
 *                        KeyHandler.h
 *  *-- Descricao
 *
 *	Interface relacionada com as teclas
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
 
#ifndef _UTIL_KEY_HANDLER_H_
#define _UTIL_KEY_HANDLER_H_

#include <SDL/SDL.h>

namespace SDL {

typedef SDLKey Key;
	
struct KeyHandler {
	virtual bool hasKey( Key _key ) = 0;
	virtual void keyPressed( Key _key ) = 0;
	virtual void keyReleased( Key _key ) = 0;	
	virtual ~KeyHandler() {}
};
	
}

#endif // _UTIL_KEY_HANDLER_H_
