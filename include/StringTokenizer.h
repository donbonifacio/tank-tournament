/***************************************************************************
 *                                                                         *
 *                        StringTokenizer.h
 *  *-- Descricao
 *
 *  Separa uma string em substrings, sendo esta string separada
 *  por varios tokens.
 *	Faz logo o parse e divide a string no construtor.
 *	Suporta iteradores e indexacao sobre os tokens
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

#ifndef _STRING_TOKENIZER_H_
#define _STRING_TOKENIZER_H_

#include "Safe.h"
#include <vector>
#include <string>
#include "Printable.h"

using std::string;
using std::vector;

namespace Util {

class StringTokenizer : public Printable {

	/** definio de tipos **/
	typedef vector<string> StringVector;

	/** constantes estaticas **/
	static const string defaultDelim;

	/**	 atributos gerais **/
	string raw;
	string delim;
	StringVector results;	

public:

	typedef StringVector::iterator iterator;
	typedef StringVector::const_iterator const_iterator;

	/*** Construtores ***/
	StringTokenizer() : delim(defaultDelim) {}
	StringTokenizer( const string& _raw, const string& _delim = defaultDelim );
	virtual ~StringTokenizer(){}
	
	/** metodos gerais **/

	void parse();
	void parse( const string& _raw );

	void setString(const string& _raw) { raw = _raw; }
	void setDelim( const string& _delim ) { delim = _delim; }

	const string& getString() const { return raw; }
	const string& getDelim() const { return delim; }
	const string& getDefaultDelim() const { return defaultDelim; }
	int size() const { return results.size(); }

	iterator begin() { return results.begin(); }
	const_iterator begin() const { return results.begin(); }
	iterator end() { return results.end(); }
	const_iterator end() const { return results.end(); }

	const string& operator[](int index) const { return results[index]; }

	void printOn( ostream& _os ) const;
};

} // namespace Util 

#endif /* _STRING_TOKENIZER_H_ */
