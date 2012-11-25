/***************************************************************************
 *                                                                         *
 *                        Properties.cpp     
 *                        -------------------                              *
 *   begin                : Thu May 29 2003               
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
#include <fstream>  
#include "../include/Properties.h"
#include "../include/StringTokenizer.h"
#include "../include/Exceptions.h"

using std::endl;
using namespace Util;

const string Properties::tokenDelim = "=";
const string Properties::noKeyFound = "NO_KEY_FOUND";
const char Properties::comment = '#';

//-----------------------------------------------------------------------------------------------------------------------------
bool Properties::getLine( istream& _is, string& _buffer )
{
	char c;
	unsigned originalSize = _buffer.size();

	while( c = _is.get(), c != '\n' ) {
		if( c == -1 ) {
			return false;
		}
		if( c == Properties::comment ) {
			string remaining;
			bool gResult = getLine(_is,remaining);
			if( _buffer.size() == originalSize ) 
				return getLine(_is,_buffer);
			return gResult;
		}
		_buffer.append(&c,1);		
	}
/*	if( _buffer[0] == Properties::comment ) {
		clearString(_buffer);
		return getLine(_is,_buffer);
	}*/
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------
Properties::Properties( const string & _file ) : file(_file.c_str()), fileName(_file)
{
	if( !file )
		throw FileNotFoundException(_file);
}
//-----------------------------------------------------------------------------------------------------------------------------
void Properties::load()
{
	string buffer;
	while( getLine(file,buffer) ) {
		StringTokenizer tokenizer(buffer,tokenDelim);
		if( tokenizer.size() != 2 )
			continue;
		set( tokenizer[0], tokenizer[1] );
		clearString(buffer);
	}	
}
//-----------------------------------------------------------------------------------------------------------------------------
void Properties::save() 
{
	save("");
}
//-----------------------------------------------------------------------------------------------------------------------------
void Properties::save( const string& _header ) 
{
	file.close();
	std::ofstream out(fileName.c_str());;
	if( !_header.empty() )
		out << comment << " " << _header << endl;
	for( const_iterator iter = begin(); iter != end(); ++iter )
		out << iter->first<< tokenDelim << iter->second << endl;
	out.close();
	file.open(_header.c_str());
}
//----------------------------------------------------------------------------------------------------------------------------
void Properties::set( const string& _key, const string& _value )
{
	(*this)[_key] = _value;
}
//-----------------------------------------------------------------------------------------------------------------------------
const string& Properties::get( const string& _key ) const
{
	const_iterator result = find(_key);
	if( result == end() )
		return noKeyFound;
	return result->second;
}
//-----------------------------------------------------------------------------------------------------------------------------
void Properties::printOn( ostream& _os ) const
{	
	_os << endl << "|--Propreties Test" << endl
		<< "   Table" << endl;
	for( const_iterator iter = begin(); iter != end(); ++iter )
		_os << "   : <" << iter->first << ","<< iter->second << ">" << endl;
}
//-----------------------------------------------------------------------------------------------------------------------------
bool Properties::hasKey( const string& _key ) const
{
	return find(_key) != end();
}

//-----------------------------------------------------------------------------------------------------------------------------
void Properties::clearString( string& _str )
{
#ifdef USING_OLD_VC	// o VC++ não tem o string::clear
		_str = "";
#else
		_str.clear();
#endif
}
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
