/***************************************************************************
 *                                                                         *
 *                        Random.h
 *  *-- Descricao
 *
 *	Classe útil para gerar números aleatórios
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

#ifndef _UTIL_RANDOM_H_
#define _UTIL_RANDOM_H_

#include <cstdlib>
#include <ctime>
#include "Ptrsolit.h"

namespace Util {

struct Random {
	Random() { srand( time(0) ); }
	int get( int _number ) const { return rand()%_number; }
	int get( int _min, int _max ) const { return get(_max-_min)+_min; }
};

/* declaração do tipo pointer para o objecto solitário */
typedef Util::PtrSolitaireAutoDel<Random> RandomPtr;

}// namespace Util

// por comodidade...
extern Util::RandomPtr randomPtr;
#define RND (randomPtr)
using Util::Random;

#endif // _UTIL_RANDOM_H_

