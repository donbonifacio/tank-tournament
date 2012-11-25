#include <cstdlib>
#include "../include/Screen.h"
#include "../include/Exceptions.h"

using namespace SDL;

IMPLEMENT_SOLITAIRE_AUTODEL(Screen)

// Objecto global
ScreenPtr screenPtr;

// constantes da class
const string Screen::FULL_SCREEN_TEXT = " Full Screen";
const string Screen::WINDOW_TEXT = " Window";

//-----------------------------------------------------------------------------------------------------------------------
// MÉTODOS PUBLICOS
//-----------------------------------------------------------------------------------------------------------------------
Screen::Screen() : Surface() 
{ 
	/* Como vai ser um singleton é melhor que o construtor não faça nada */ 
	LOG << "SDL::Screen Singleton created." << endl;
}
//-----------------------------------------------------------------------------------------------------------------------
Screen::~Screen() 
{ 
	/* Nunca se Faz SDL_FreeSurface à Surface do Screen */ 
	LOG << "SDL::Screen Singleton terminated." << endl;
}
//-----------------------------------------------------------------------------------------------------------------------
void Screen::init( Uint32 _flags )
{
	/*
		Inicia a SDL
		SDL_INIT_TIMER	
		SDL_INIT_AUDIO	
		SDL_INIT_VIDEO	
		SDL_INIT_CDROM	
		SDL_INIT_JOYSTICK
		SDL_INIT_EVERYTHING	
		SDL_INIT_NOPARACHUTE
		SDL_INIT_EVENTTHREAD	 
	*/
	LOG << "Initializing SDL { ";

	if( SDL_Init(_flags) == -1 )
		throw Util::GeneralError("Could not initialize SDL: ",SDL_GetError());
	
	Uint32 flags = SDL_WasInit(SDL_INIT_EVERYTHING);
	
	if( (flags & SDL_INIT_TIMER) == SDL_INIT_TIMER ) LOG << "SDL_INIT_TIMER ";
	if( (flags & SDL_INIT_AUDIO) == SDL_INIT_AUDIO ) LOG << "SDL_INIT_AUDIO ";
	if( (flags & SDL_INIT_VIDEO) == SDL_INIT_VIDEO ) LOG << "SDL_INIT_VIDEO ";
	if( (flags & SDL_INIT_CDROM) == SDL_INIT_CDROM ) LOG << "SDL_INIT_CDROM ";
	if( (flags & SDL_INIT_JOYSTICK) == SDL_INIT_JOYSTICK ) LOG << "SDL_INIT_JOYSTICK ";
	if( (flags & SDL_INIT_EVERYTHING) == SDL_INIT_EVERYTHING ) LOG << "SDL_INIT_EVERYTHING ";
	if( (flags & SDL_INIT_NOPARACHUTE) == SDL_INIT_NOPARACHUTE ) LOG << "SDL_INIT_NOPARACHUTE ";
	if( (flags & SDL_INIT_EVENTTHREAD) == SDL_INIT_EVENTTHREAD ) LOG << "SDL_INIT_EVENTTHREAD ";
	LOG	<< "}... ";

	LOG << "OK" << endl;
}
//-----------------------------------------------------------------------------------------------------------------------
void Screen::setVideoMode( int _w, int _h, VideoMode _videoMode )
{
	/*
		Estabelece o Modo Video(with, height, Mode)
	*/

	// ver se o modo video na SDL já foi inicializada ( com o Screen::init() )
	assert( SDL_WasInit(SDL_INIT_VIDEO) );

	// registar...
	char buffer[20];
	LOG << "Setting " << _w << "*" << _h 
		<< ( (_videoMode == FULLSCREEN) ? FULL_SCREEN_TEXT : WINDOW_TEXT )
		<< " Video Mode on '"<< SDL_VideoDriverName(buffer,sizeof(buffer)) << "'... ";

	// criar a janela
	sdlSurfacePtr = SDL_SetVideoMode( 
		_w, 
		_h, 
		0, 
		(_videoMode == WINDOW) ? SDL_HWSURFACE | SDL_DOUBLEBUF : SDL_FULLSCREEN
	);
	
	// na ocorrência de erro...
	if(0 == sdlSurfacePtr)
		throw Util::GeneralError("Error setting Video Mode", SDL_GetError());

	setPos(0,0);
	normalize();

	LOG << "OK" << endl;
}

//-----------------------------------------------------------------------------------------------------------------------
void Screen::printOn( ostream& _os ) const
{
	assert( isReady() );

	const SDL_VideoInfo* video = SDL_GetVideoInfo();
	assert(video != 0);
	
	_os << "Printing video information:" << endl
		<< "--------------------------------------------------------------------------" << endl
		<< "|\tVideo Information:" << endl
		<< "|\t* Hardware surfaces available? " << video->hw_available << endl
		<< "|\t* Window manager available? " << video->wm_available << endl
		<< "|\t* HW to HW blit's acelarated? " << video->blit_hw << endl
		<< "|\t* HW to HW blit's using color keys acelarated? " << video->blit_hw_CC << endl
		<< "|\t* HW to HW blit's using alpha acelarated? " << video->blit_hw_A << endl
		<< "|\t* SW to HW blit's acelarated? " << video->blit_sw << endl
		<< "|\t* SW to HW blit's using colof keys acelarated? " << video->blit_sw_CC << endl
		<< "|\t* SW to HW blit's using alpha acelarated? " << video->blit_sw_A << endl
		<< "|\t* Color fills acelarated? " << video->blit_fill << endl
		<< "|\t* Video memory? " << video->video_mem << " K" << endl
		<< "|\t* Bits per pixel? " << (int)video->vfmt->BitsPerPixel << endl
		<< "--------------------------------------------------------------------------" << endl;

}

//-----------------------------------------------------------------------------------------------------------------------
void Screen::flip()
{
	/**
	 *	 "Mostrar" o surface currente no ecrã
	 **/
	if( SDL_Flip(sdlSurfacePtr) < 0 )
		throw Util::GeneralError("Error Fliping: ",SDL_GetError());
}
//-----------------------------------------------------------------------------------------------------------------------
void Screen::toggleFullScreenMode()
{
	/**
	 *	Se a aplicação está em window mode passa para fullscreen mode, se estiver em 
	 *	fullscreen mode, passa para window mode
	 **/

	// ver se o modo video na SDL já foi inicializada ( com o Screen::init() )
	assert( SDL_WasInit(SDL_INIT_VIDEO) );

	// ver se já foi criada a Surface do ecrã
	assert( sdlSurfacePtr );

	/**
	 *	Fazer o toggle!
	 *	tentar o toggle pela SDL (poucas probabilidades de funcionar pois está 
	 *	implementado em muito poucos sistemas: Linux e Irix)
	 **/
	
	LOG << "Changing to" << getScreenText() << " mode native way... ";
	
	if( !SDL_WM_ToggleFullScreen(sdlSurfacePtr) ) {
		
		LOG << "FAILED!" << endl
			<< "Changing to" << getScreenText() << " by software... " << endl;

		/* SDL_WM_ToggleFullScreen(_sdlSUrfacePtr) falhou, fazer o toggle à manápula */

		// criar uma Surface Auxiliar vazia
		Surface temp(sdlSurfacePtr->w,sdlSurfacePtr->h);

		// pintar o ecrã nela
		temp.blit(*this);

		// estabelecer o novo modo video(parto do principio que a SDL trata da surface antiga)
		setVideoMode(sdlSurfacePtr->w,sdlSurfacePtr->h,
			(sdlSurfacePtr->flags & SDL_FULLSCREEN) ? WINDOW : FULLSCREEN );

		// pintar o ecrã anterior na nova surface de ecrã
		blit(temp);
	}
	LOG << "Success! Application toggled fullscreen state." << endl;
}
//-----------------------------------------------------------------------------------------------------------------------
void Screen::setCaption( const string& _caption )
{
	/*
		Estabelece a o titulo da janela(visivel somente em WINDOW mode)
	*/
	LOG << "Setting window caption \""<< _caption <<"\"... ";
	SDL_WM_SetCaption(_caption.c_str(),0);
	LOG << "Ok!" << endl;
}

//-----------------------------------------------------------------------------------------------------------------------
void Screen::setWindowIcon( const string& _file )
{
	LOG << "Setting Window icon(" << _file << ")... ";
	SDL_WM_SetIcon(SDL_LoadBMP(_file.c_str()), 0);
	LOG << "Done" << endl;
}

//-----------------------------------------------------------------------------------------------------------------------
const string& Screen::getScreenText()
{
	return ( (sdlSurfacePtr->flags & SDL_FULLSCREEN) != SDL_FULLSCREEN ? FULL_SCREEN_TEXT : WINDOW_TEXT ) ;
}
//-----------------------------------------------------------------------------------------------------------------------
