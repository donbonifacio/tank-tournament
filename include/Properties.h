/***************************************************************************
 *                                                                         *
 *                        Properties.h     
 *	*-- Descricao
 *
 *   Clone do Properties do Java, dada uma stream com linhas com a sintaxe:
 *		NOME_DO_JOGADOR=Jose anibal
 *		ArmaFavorita=Shock
 *	Separa as strings em map<string,string> em que a chave e o primeiro
 *	e o valor e todo o que esta a seguir ao igual
 *	NOTA: 
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

#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_

#include "Safe.h"
#include <map>
#include <string>
#include <fstream>
#include <istream>
#include "Printable.h"

using std::istream;
using std::string;
using std::map;
using std::fstream;

//------------------------------------------------------------------------------------------------------------------------
namespace Util {

//------------------------------------------------------------------------------------------------------------------------
	
typedef map<string,string> PropertiesMap;

class Properties : public PropertiesMap, public Printable {
	
	fstream file;
	string fileName;

	static const string tokenDelim;
	static const string noKeyFound;
	static const char comment;
	
	static bool getLine( istream& _is, string& _buffer );
	static void clearString( string& _str );
	
public:

	Properties( const string& _file );
	virtual ~Properties() {}

	void load();
	void save();
	void save( const string& _header );

	void set( const string& _key, const string& _value );
	const string& get( const string& _key ) const;
	bool hasKey( const string& _key ) const;

	void printOn( ostream& _os ) const;
};

} //namespace Util 

//------------------------------------------------------------------------------------------------------------------------

#endif  /* _PROPERTIES_H_ */
