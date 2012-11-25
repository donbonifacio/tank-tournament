/***************************************************************************
 *                                                                         *
 *                        Menu.h
 *  *-- Descricao
 *
 *	Simulação de Menu com vários botões e Imagens
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

#ifndef _SDL_BUTTON_H_
#define _SDL_BUTTON_H_

#include <SDL/SDL.h>
#include "Surface.h"
#include "Exceptions.h"

namespace SDL {

template<class T>
class Menu {

public:	
	/* Para os botões */
	class Button {
		Surface onMouseOverSurf;
		Surface baseSurf;
	public:
		Button() {}
		Button( const string& _onMouseOver, const string& _base )
			: onMouseOverSurf(_onMouseOver), baseSurf(_base) {}

		Button( const Surface& _onMouseOverSurf, const Surface& _baseSurf )
			: onMouseOverSurf(_onMouseOverSurf), baseSurf(_baseSurf) {}

		Surface& getOnMouseOverSurface() { return onMouseOverSurf; }
		Surface& getBaseSurface() { return baseSurf; }

		bool pointIn( int _x, int _y) const { return baseSurf.pointIn(_x,_y); }

	};

	/* typedefs */
	typedef void (T::*BaseEvent)();
	typedef std::pair<BaseEvent,Button> Pair;

	typedef list<Pair> ButtonList;

protected:
	/* atributos */
	ButtonList buttons; 
	ScreenPtr scr;

	/* métodos privados */
	Pair* mousePosInButton( int _x, int _y );

public:
	
	void add( const Button& _button, BaseEvent _event );
	BaseEvent run();

};

//-----------------------------------------------------------------------------------------------------------------------
// Definição
//-----------------------------------------------------------------------------------------------------------------------
template<class T>
void Menu<T>::add( const Button& _button, BaseEvent _event )
{
	buttons.push_back(std::make_pair(_event,button));
}
//-----------------------------------------------------------------------------------------------------------------------
template<class T>
Menu<T>::BaseEvent Menu<T>::run()
{
	/* ver se a SDL já foi inicializada */
	ASSERT(scr->isReady());
	
	/* ver se há botoes... se não houver retorna logo 0 */
	if( buttons.empty() )
		return 0;

	bool isOnMouseOver(false);
	SDL_Event event;
	
	for(;;){ 
		while ( SDL_PollEvent(&event) ){ 

			/* ver se houve quit */
			if ( event.type == SDL_QUIT )
			   return 0;				

			/* ver se houve escape */
			if ( event.type == SDL_KEYDOWN )
			   if ( event.key.keysym.sym == SDLK_ESCAPE ) 
				  return 0;

			/* ver se houve mouse over nalgum botão */
			if( event.type == SDL_MOUSEMOTION ){
				Pair* result = mousePosInButton(event.motion.x,event.motion.y);
				if(result && !isOnMouseOver){
					isOnMouseOver = true;
					scr->blit( (result->second).getOnMouseOverSurface() );
				} else {
					if(!result) isOnMouseOver = false;
				}	
			}

			/* ver se houve click nalgum botão */
			if( event.type == SDL_MOUSEBUTTONDOWN ){
				Pair* result = mousePosInButton(event.button.x,event.button.y);
				if(result)
					return result->first;
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------
template<class T>
Menu<T>::Pair* Menu<T>::mousePosInButton( int _x, int _y )
{
	for( ButtonList::iterator it = buttons.begin(); it != buttons.end(); ++it )
		if( (it->second).pointIn(_x,_y) )
			return &(*it);

	return 0;
}
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------

} // namespace SDL


#endif /* _SDL_BUTTON_H_ */
