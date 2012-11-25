/***************************************************************************
 *                                                                         *
 *                        Ptrsolit.h
 *  *-- Descricao
 *
 *	Implementação da design pattern Solitaire (singleton)
 *	Feita pelos engenheiros do CC (http://cc.isel.ipl.pt) 
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

#ifndef PTRSOLITAIRE_H
#define PTRSOLITAIRE_H

namespace Util {

template <class T>
class PtrSolitaire{
protected:
	void *operator new(size_t)    { return 0; }
  void operator delete(void *)  {  }

  static T *instance;
  void begin()                         { if(!instance) instance = new T;}
public:
  void end()                           { delete instance; instance = 0; }
  PtrSolitaire()                       { begin(); }
  operator T *()                       { return instance; }
  T &operator*()                       { return *instance; }
  T *operator->()                      { return instance; }
};

template <class T>
class PtrSolitaireAutoDel: public PtrSolitaire<T> {
protected:
  PtrSolitaire<T>::end;
  static int count;
public:
  ~PtrSolitaireAutoDel()    { if (!--count) end(); }
  PtrSolitaireAutoDel(const PtrSolitaireAutoDel &pi) { ++count; }
  PtrSolitaireAutoDel()     { ++count;  }
};

// MACRO to declare "instance" and "counter"
// for each instance of PtrSolitaire in global scope
#define IMPLEMENT_SOLITAIRE(T) \
T * Util::PtrSolitaire<T>::instance = NULL;

#define IMPLEMENT_SOLITAIRE_AUTODEL(T) \
IMPLEMENT_SOLITAIRE(T) \
int Util::PtrSolitaireAutoDel<T>::count = 0;

} // namespace Util 

#endif
