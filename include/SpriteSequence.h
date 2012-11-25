#ifndef _SDL_SPRITE_SEQUENCE_H_
#define _SDL_SPRITE_SEQUENCE_H_
#include "../include/Safe.h"

#include <string>
#include <list>
#include <vector>

#include "../include/Surface.h"

using std::string;
using std::list;
using std::vector;

namespace SDL {

//------------------------------------------------------------------------------------------------------------------------

#define NUM_OF_DIRECTIONS 4

class SpriteSequence {
public:
	/* typedef's */
	typedef list<Surface>			SurfaceList;
	typedef vector<SurfaceList>		DirVector;
	typedef SurfaceList::iterator	iterator;

	/* enum para as direc��es */
	enum Dir {
		DOWN,
		UP,
		LEFT,
		RIGHT,
		NO_DIR	// s� para ajuda em termos l�gicos, n�o conta em NUM_OF_DIRECTIOS
	};

private:
	/* atributos */
	SurfaceList::iterator currSprite;
	DirVector dirVector;
	Dir currDir;
	

public:
	SpriteSequence() : currSprite(NULL), dirVector(NUM_OF_DIRECTIONS), currDir(NO_DIR) {}

	void setDir( Dir _dir );
	void pushSprite( Surface& _surface );
	// para compatibilidade com os contentores standard
	void push_back( Surface& _surface ) {pushSprite(_surface);}
	Surface& getCurrSprite();
	Dir geCurrDir() const { return currDir; }

	SpriteSequence& operator++();

	/* m�todos usados para a SpriteSequenceHandler */
	SurfaceList& getDirList( Dir _dir ) { return dirVector[_dir]; }
};

#undef NUM_OF_DIRECTIONS

//------------------------------------------------------------------------------------------------------------------------

/*
	Caso uma SpriteSequence tenha que ser partilhada por v�rios objectos, deve usar-se esta
	SpriteSequenceHandler que funciona como um apontador para a SpriteSequence mas com todos
	os seus atributos replicados.
*/

class SpriteSequenceHandler {

	typedef SpriteSequence Base;
	/* atributos */
	Base* source;
	Base::Dir currDir;
	Base::iterator currSprite;

public:
	/* construtor */
	SpriteSequenceHandler( SpriteSequence* _source ) : 
	  source(_source), currDir(Base::NO_DIR), currSprite(NULL) {}

	/* m�todos */
	void setDir( Base::Dir _dir );
	Surface& getCurrSprite();
	Base::Dir geCurrDir() const { return currDir; }

	SpriteSequenceHandler& operator++();
};

//------------------------------------------------------------------------------------------------------------------------

}// namespace SDL

#endif /* _SDL_SPRITE_SEQUENCE_H_ */
