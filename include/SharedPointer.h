/***************************************************************************
 *                                                                         *
 *                        SharedPointer.h
 *  *-- Descricao
 *
 *	Clone das referências em Java. Um objecto pode ser partilhado por diversos
 *	SharedPointer's, e só será destruido quando já não restarem referências
 *	para ele.
 *	
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
 
#ifndef _SHARED_POJNTER_H_
#define _SHARED_POJNTER_H_

#include "Printable.h"

namespace Util {

template<class T>
class SharedPointer : public Printable {
	
	struct Link {
		T* data;
		int count;
		Link(const T* _object) : data(_object), count(1) {}
		Link(T* _object) : data(_object), count(1) {}
		void incRef() { ++count; }
		void decRef() { if( --count == 0 ) delete this; }
	};

	Link* link;

public:
	
	SharedPointer() : link(0) {}
	SharedPointer(T& _object) : link( new Link(&_object) ) 	{ link->incRef(); }
	SharedPointer(T* _object) : link( new Link(_object) ) 	{ link->incRef(); }
	SharedPointer( const SharedPointer& sh ) : link(sh.link) 	{ link->incRef(); }
	virtual ~SharedPointer() { link->decRef(); }

	operator T *()				{ return link->data; }
	T &operator*()	{ return *(link->data); }
	const T &operator*() const	{ return *(link->data); }
	T *operator->()	{ return link->data; }
	T *operator->()	const { return link->data; }

	SharedPointer& operator=( const SharedPointer& sh ) {
		link->decRef();
		link = sh.link;
		link->incRef();
		return *this;
	}

	SharedPointer& operator=( T* tp ) {
		if(0 != link)
			link->decRef();
		link = new Link(tp);
		return *this;
	}

	bool operator==( const SharedPointer& sh ) const { return sh.link == link; }
	bool operator!=( const SharedPointer& sh ) const { return !(*this == sh); }

	void printOn( ostream& _os ) const { 
		_os << "|--SharedPointer" << endl 
			<< "   Pointer = " << &(link->data) << endl
			<< "   Count = " << link->count <<endl; 
	}
};

} // namespace Util 

#endif /* _SHARED_POJNTER_H_ */
