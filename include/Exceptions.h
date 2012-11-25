/***************************************************************************
 *                                                                         *
 *                        Exceptions.h
 *  *-- Descricao
 *
 *	Algumas exepções a serem usadas. Compatíveis com o standard
 *
 *	*-- Detalhes      
 *                        
 *   begin                : Wed May 28 2003               
 *   copyright            : (C) 2003 by Pedro Santos                  
 *   homepage             : http://pdpsantos.sf.net                        *
 *   contact              : http://pdpsantos.sf.net/contacto.php           *
 *   Tank Tournament HP   : http://pdpsantos.sf.net/tank/                  *
 *                                                                         *
 * *-- Licence :                                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include "Safe.h"
#include <exception>
#include <string>
#include <stdexcept>

using std::string;

//------------------------------------------------------------------------------------------------------------------------
namespace Util {
	
//------------------------------------------------------------------------------------------------------------------------

struct BasicException : public std::exception {

	virtual const string getError() const = 0;
    virtual ~BasicException() throw() {}
	
	// compatibilidade com o standard		
	virtual const char* what() const throw() { return getError().c_str(); }
};

typedef BasicException Exception;

//-----------------------------------------------------------------------------------------------------------------------------

/* Para erros relacionados com ficheiros */
class FileNotFoundException : public BasicException {
	string file;
	const char* error;
public:
	explicit FileNotFoundException( const string& _file, const char* _error = 0 ) : file(_file), error(_error) {}
	const string getError() const { 
		string temp = "File not found: " + file + ". ";
		if(error)
			temp += error;
		return temp;
	}
	virtual ~FileNotFoundException() throw() {}
};

typedef FileNotFoundException FileLoadingError;
//-----------------------------------------------------------------------------------------------------------------------------

/* Excepções gerais */
class GeneralError : public BasicException {
	string msg;
	const char* error;
public:
	explicit GeneralError( const string& _msg, const char* _error = 0 ) : msg(_msg), error(_error) {}
	const string getError() const { 
		string temp = "* Fatal Exception: " + msg;
		if(error)
			temp += string("(") + error + ")";
		return  temp;
	}
	virtual ~GeneralError() throw() {}
};

typedef GeneralError GeneralException;

//-----------------------------------------------------------------------------------------------------------------------------

} // namespace Util 

#endif // _EXCEPTIONS_H_
