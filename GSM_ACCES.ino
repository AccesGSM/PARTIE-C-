#include "appli.h"

CAppli appli;

void setup()
{
	appli.Init();
}

void loop()
{
	//Chaque n ms
	appli.Run(2000);
	//Fonction rapide
	appli.Run();	//vide
	
}
