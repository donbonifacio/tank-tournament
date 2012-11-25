/***************************************************************************
 *                                                                         *
 *                        Printable.h
 *  *-- Descricao
 *
 *	interface correspondente a um objecto que se sabe escrever
 *	num std::ostream
 *
 *	*-- Detalhes      
 *                        
 *   begin                : Wed Aug 6 2003               
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

#ifndef _PRINTABLE_H_
#define _PRINTABLE_H_

#include <iostream>
using std::ostream;
using std::endl;
using std::cout;

struct Printable {
	virtual void printOn( ostream& _os ) const = 0;
	virtual void print() const { printOn(cout); }
	virtual ~Printable() {}
};

#endif // _PRINTABLE_H_

