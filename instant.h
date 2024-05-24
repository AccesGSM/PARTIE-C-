#ifndef INSTANT_H
#define INSTANT_H


/* Carte ARDUINO UNO ou MEGA


Infos :
...
Librairies :
...
Types de cartes utilisées
...

*/
#define VERSION_INSTANT "CINSTANT.2023.09.06.V0"
#define DESCRIPTION_INSTANT "Test ...."

/*Pour Visual Studio
#include <iostream>
#include <string>
using namespace std;
#define uint16_t unsigned short
#define uint16_t unsigned short
#define uint32_t unsigned int
//FIN Visual Studio */ 

//Pour ARDUINO
//Pour manipuler les chaînes
//#include "texte.h"
#define	uint32_t	unsigned long
#define	uint16_t	unsigned int

//FIN ARDUINO */ 

class CInstant 
{
protected:
    uint32_t m_instant = 0;
    bool EstBissextile(uint16_t an);

public:
    CInstant();
	CInstant(uint32_t instant);

    // Calcul du nombre de secondes depuis le 1/1/2000 à 0h0m0
	void SetDate(uint16_t jour, uint16_t mois, uint16_t an, uint16_t hour, uint16_t minute, uint16_t seconde);
	void SetHeure(uint16_t heure, uint16_t minute, uint16_t seconde);
	void SetDate(uint16_t jour, uint16_t mois, uint16_t an);
	uint32_t GetInstant();
	uint16_t GetAn();
	uint16_t GetJour();
	uint16_t GetMois();
	String GetMois(uint16_t nb_car);
	uint16_t GetJourSem();
	String GetJourSem(uint16_t nb_car);
	uint16_t GetHeure();
	uint16_t GetMinute();
	uint16_t GetSec();
	int Month2Nombre(String abreviation);
	int DernierDimanche(uint16_t mois, uint16_t annee);
	void DecaleGMT();
    bool EstEnHeureDete();
	String GetMessage();
	void Add(uint32_t secondes);
	void SetInstant(CInstant instant);
	void SetInstant(uint32_t instant);
	bool SuperieurA(CInstant instant);
	String Get2Digit(int nombre);
};


#endif
