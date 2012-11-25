#include "../include/SpriteSequence.h"
#include "../include/Surface.h"
#include "../include/Exceptions.h"

using namespace SDL;

//-----------------------------------------------------------------------------------------------------------------------
// SpriteSequence
//-----------------------------------------------------------------------------------------------------------------------
void SpriteSequence::setDir( Dir _dir )
{ 
	/*
		Altera a direc��o currente para '_dir'
	*/
	currDir = _dir; 

	// currSprite passa a apontar para o 1� elemento da nova direc��o
	currSprite = dirVector[currDir].begin();
} 
//-----------------------------------------------------------------------------------------------------------------------
void SpriteSequence::pushSprite( Surface& _surface )
{
	/*
		Adiciona a sprite '_surface' � Lista da direc��o currente
	*/

	if( currDir == NO_DIR )
		throw Util::GeneralError("Trying to Push a Sprite to a SpriteSequence with NO_DIR.");

	// adicionar
	dirVector[currDir].push_back( _surface );

}
//-----------------------------------------------------------------------------------------------------------------------
Surface& SpriteSequence::getCurrSprite()
{
	/*
		Retorna a sprite currente da direc��o currente
	*/

	// ver se a direc��o currente j� foi inicializada com sprites
	if( dirVector[currDir].empty() )
		throw Util::GeneralError("Trying to get a Sprite form an empty SpriteSequence Direction.");

	// se o 'currSprite' n�o estiver a apontar para lado nenhum...
	if( currSprite == NULL )
		currSprite = dirVector[currDir].begin();

	return *currSprite;
}
//-----------------------------------------------------------------------------------------------------------------------
SpriteSequence& SpriteSequence::operator++()
{
	/*
		Avan�a para a pr�xima Sprite na direc��o currente
	*/

	if( ++currSprite == dirVector[currDir].end() )
		currSprite = dirVector[currDir].begin();

	return *this;
}
//-----------------------------------------------------------------------------------------------------------------------
// SpriteSequenceHandler
//-----------------------------------------------------------------------------------------------------------------------
void SpriteSequenceHandler::setDir( Base::Dir _dir )
{
	/*
		altera a direc��o currente
	*/
	currDir = _dir;

	// actualiza o pointer para a sprite currente
	currSprite = (source->getDirList(_dir)).begin();
}
//-----------------------------------------------------------------------------------------------------------------------
Surface& SpriteSequenceHandler::getCurrSprite()
{
	/*
		Retorna a sprite currente da direc��o currente
	*/

	// ver se a lista currente n�o est� vazia
	if( (source->getDirList(currDir)).empty() )
		throw Util::GeneralError("Trying to get a Sprite form an empty SpriteSequence Direction.");

	// ver se o apontador ainda est� a apontar para NULL, se tiver aponta para a 1� posi��o
	if( currSprite == NULL )
		currSprite = (source->getDirList(currDir)).begin();

	// retorna
	return *currSprite;
}
//-----------------------------------------------------------------------------------------------------------------------
SpriteSequenceHandler& SpriteSequenceHandler::operator ++()
{
	/*
		passa para a pr�xima sprite da direc��o currente
	*/
	if( ++currSprite == (source->getDirList(currDir)).end() )
		currSprite = (source->getDirList(currDir)).begin();

	return *this;
}
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
