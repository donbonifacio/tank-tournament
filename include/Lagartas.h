/***************************************************************************
 *                                                                         *
 *                        TankPart.h
 *  *-- Descricao
 *
 *	Diferentes partes de um tank
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
 
#ifndef _TANK_LAGARTAS_H_
#define _TANK_LAGARTAS_H_

#include "TankPart.h"

namespace Tank {

//----------------------------------------------------------------------------
struct Lagartas : public TankPart {
	Lagartas( const string& _tank, const string& _file) 
		: TankPart(_tank,_file) {}
	virtual void onCollision( Actor* _other ) = 0;
	virtual int getVelocity() const = 0;
};

//----------------------------------------------------------------------------
struct BasicLagartas : public Lagartas {
	enum { VELOCITY = 8 };
	BasicLagartas(const string& _tank) : Lagartas(_tank,"Lagartas-Simples") {}
	void onCollision( Actor* _other ) { /* não faz nada */ }
	int getVelocity() const { return VELOCITY; }
};

//----------------------------------------------------------------------------
struct DamageLagartas : public Lagartas {
	enum { 
		VELOCITY = 10 ,
		DAMAGE = 1
	};
	DamageLagartas(const string& _tank) : Lagartas(_tank,"Lagartas-Damage") {}
	void onCollision( Actor* _other ) { _other->setDamage(DAMAGE); }
	int getVelocity() const { return VELOCITY; }
};


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


}

#endif // _TANK_LAGARTAS_H_
