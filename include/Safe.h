/***************************************************************************
 *                                                                         *
 *                        Safe.h
 *  *-- Descricao
 *
 *	V�rias macros especificas para cada sistema operativo/platadorma
 *	tratamento de erros e excep��es
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

#ifndef _TANK_SAFE_H
#define _TANK_SAFE_H

#include <string>
#include <SDL/SDL.h>

/*
	const string's to use
*/
const std::string version("v0.2");
const std::string site("http://tank-tournament.sf.net");

/** defini��o de tipos **/

typedef unsigned char Byte;


/*
	H� casos em que � preciso separar c�digo para VC++ e G++
	Como '_WIN32' � gerado por defeito nos 2 compiladores, e '__GNUG__'
	� gerado no G++ ent�o...
	'linux' � usado nos ambientes linux
*/

// macros relacionadas com o G++
#ifdef __GNUG__	
#	define USING_GCC
#	ifdef __CYGWIN__
#		define COMPILER_NAME	"Cygwin G++ "
#	else
#		define COMPILER_NAME	"GNU G++ "
#	endif
#	define COMPILER_VERSION	(__GNUC__ + __GNUC_MINOR__ * 0.01)
#endif

// macros relacionadas com o Visual C++
#ifdef _MSC_VER	

#	define USING_VC
#	define COMPILER_NAME	"Visual C++ "

#	if _MSC_VER < 1200
#		define COMPILER_VERSION	_MSC_VER
#		define USING_OLD_VC
#	elif _MSC_VER == 1300
#		define COMPILER_VERSION ".NET"
#		define USING_VS_DOT_NET
#	else
#		define COMPILER_VERSION	6
#		define USING_OLD_VC
#	endif

#endif

/*
	Defini��o do modo currente de compila��o
	NOTA: o VC++ gera _DEBUG e _NDEBUG por defeito, mas em rela��o ao G++, parte-se do
	principio que nos parametros de compila��o est� '-D_DEBUG' na flags de debug e
	'-D_NDEBUG' nas flags de release mode
*/
#ifndef USING_VC	// o VC++ define estas macros
#	define _DEBUG	// comentar para sair de debug no gcc
//#	define _NDEBUG
#endif

#ifdef _DEBUG
#	define DEBUG_MODE
#	define BUILD_MODE	"Debug Mode."
#elif defined(_NDEBUG)
#	define RELEASE_MODE
#	define BUILD_MODE	"Release Mode."
#else
#	error S�o precisas as macros _NDEBUG ou _DEBUG nas flags!
#endif

/*
	O seguinte � para se saber em que OS estamos
*/
#ifdef _WIN32
#	ifndef WIN32
#		define WIN32
#	endif
#	define OS_NAME	"Win32"
#elif defined(linux)
#	define LINUX
#	define OS_NAME	"Mandrake 9.1"	// my distro =)
#else
#	define UNKNOWN_OS
#	define OS_NAME	"Unknown OS"
#endif

/*
	Macros relacionadas com a SDL
*/
#define SDL_COMPILED_VERSION	\
	(SDL_MAJOR_VERSION) + (SDL_MINOR_VERSION)*0.1 + (SDL_PATCHLEVEL)*0.01

/*
	Rotinas de debug - controlo de erros
*/

// includes necess�rios
#include <exception>
#include "Log.h"

// 'macro' de assert usada para compatibilidade, deve ser usada a assert();
#include <cassert>
#define ASSERT(cond) assert(cond)

/**
 *	fun���o chamada quando o programa termina por uma excep��o que n�o foi apanhada
 *	tem que se chamar 'auto_catch_all_exceptions()' no in�cio do programa para que funcione
 **/
inline void terminated()
{
	LOG << "Program terminated by an uncaught exception!" << endl;
}

// se estamos a usar o GCC ele j� tem uma fun��o para isso (manda o output para o stderr)
#ifdef USING_GCC
#	define __TERMINATED__ __gnu_cxx::__verbose_terminate_handler
#else
#	define __TERMINATED__ terminated
#endif

inline void auto_catch_all_exceptions() 
{ 

#ifdef USING_OLD_VC
	LOG << "Compiler " << COMPILER_NAME << COMPILER_VERSION << " does not suport std::terminate." << endl; 
#else
	std::set_terminate(__TERMINATED__);
	LOG << "Auto catching all exceptions enabled." << endl;
#endif
}

#endif /* _TANK_SAFE_H */

/* 
	Para o VC++ n�o se chatear com os nomes grandes 
*/
#ifdef USING_OLD_VC
#	pragma warning( disable : 4786 )
#endif
