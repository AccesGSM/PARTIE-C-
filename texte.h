#ifndef TEXTE_H
#define TEXTE_H

#include <Arduino.h>  

/* Carte ARDUINO UNO ou MEGA
Infos :
...
Librairies :
...
Types de cartes utilisées
...
*/

#define VERSION_TEXTE "TEXTE.2023.09.06.V0"
#define DESCRIPTION_TEXTE "Test ...."

/*Pour Visual Studio
#include <iostream>
#include <string>
using namespace std;
#define uint16_t unsigned short
#define uint16_t unsigned short
#define uint32_t unsigned int
//FIN Visual Studio */ 

//Pour ARDUINO
#include <Arduino.h>  
#define	uint32_t	unsigned long
#define	uint16_t	unsigned int
//FIN ARDUINO */ 



//Récupère la valeur d'un paramètre de la réponse serveur par exemple
String GetValeur(String& reponse, String parametre);

#endif
