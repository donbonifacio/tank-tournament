/***************************************************************************
 *                                                                         *
 *                        Log.h
 *  *-- Descricao
 *
 *	Fácil e simples interacção com um ficheiro de log, usa-se:
 *		LOG << "Log" << endl;
 *	LOG é um ofstream.
 *	A implementação do obejcto global LogPtr logPtr; encontra-se no Safe.cpp
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

#ifndef _LOG_H_
#define _LOG_H_

#include "Safe.h"
#include <fstream>
#include <string>
#include "Ptrsolit.h"
#include "Safe.h"

using std::ofstream;
using std::string;
using std::endl;

//------------------------------------------------------------------------------------------------------------------------
namespace Util {
	
//------------------------------------------------------------------------------------------------------------------------

class LogFile : public ofstream {
public:
	LogFile() : ofstream("Log.txt") 
	{
		*this << "Log System initialized." << std::endl; 
	}

	void init()
	{ 
		*this	<< "--------------------------------------------------------------------------" << endl
				<< "|\tTank Tournament "<< version <<" Log File." << std::endl
				<< "|\tBuilt with " << COMPILER_NAME << COMPILER_VERSION 

				<< " on " << OS_NAME 
#ifdef SDL_COMPILED_VERSION
				<< " with SDL v" << SDL_COMPILED_VERSION
#endif
				<< std::endl
				<< "|\t" << BUILD_MODE << endl
				<< "--------------------------------------------------------------------------" << endl;
	}

	~LogFile() 
	{ 
		*this	<< "Log System shutdown." << std::endl; 
	}
};

// pointer para a única instância de LogFile
typedef Util::PtrSolitaireAutoDel<LogFile> LogPtr;

//------------------------------------------------------------------------------------------------------------------------

} // namespace Util {


// por comodidade. 
#define LOG (*logPtr)
extern Util::LogPtr logPtr;

#endif // _LOG_H_
