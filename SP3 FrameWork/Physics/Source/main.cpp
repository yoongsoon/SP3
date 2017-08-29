#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#include "Application.h"


int main( void )
{
	/*_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(9554);
	_CrtSetBreakAlloc(9553);
	_CrtSetBreakAlloc(9552);*/

	Application &app = Application::GetInstance();
	app.Init();
	app.Run();
	app.Exit();
}