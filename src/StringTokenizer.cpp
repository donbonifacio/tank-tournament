/***************************************************************************
 *                                                                         *
 *                        StringTokenizer.cpp    
 *                        -------------------                              *
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
 
#include "../include/StringTokenizer.h"

using std::endl;
using namespace Util;

const string StringTokenizer::defaultDelim = " .,!?:;";

//-----------------------------------------------------------------------------------------------------------------------------
StringTokenizer::StringTokenizer( const string& _raw, const string& _delim ) : raw(_raw), delim(_delim)
{
	parse();
}
//-----------------------------------------------------------------------------------------------------------------------------
void StringTokenizer::parse()
{
	// size_type string::find_first_not_of( const basic_string &str, size_type index );
	// basic_string string::substr( size_type index, size_type num );

	unsigned index = 0, lastIndex = 0;
	results.clear();

	for(;index != raw.size();){
		index = raw.find_first_of( delim , lastIndex );
		if( index < 0 )
			index = raw.size();
		results.push_back( raw.substr( lastIndex, index - lastIndex ) );
		lastIndex = raw.find_first_not_of( delim, index );
	} 
}
//-----------------------------------------------------------------------------------------------------------------------------
void StringTokenizer::parse( const string& _raw )
{
	raw = _raw;
	parse();
}

//-----------------------------------------------------------------------------------------------------------------------------
void StringTokenizer::printOn( ostream& _os ) const
{
	_os << endl << "|--StringTokenizer Test" << endl
		<< "   Raw string: \"" << raw << "\"" << endl
		<< "   Tokens" << endl;
	for( StringVector::const_iterator iter = results.begin(); iter != results.end(); ++iter )
		_os << "   : " << *iter << endl;
}
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------
