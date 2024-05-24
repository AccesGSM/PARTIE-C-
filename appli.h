#ifndef APPLI_H
#define APPLI_H

//Infos diagrammes de classes
#include "infos.versions.h"
#include <Arduino.h>  
//Librairies configurées pour les classes du projet
//Pour la classe CSuperGSM
#include "supergsm.h"
//Pour la classe CPeriode
#include "periode.h"
//Pour la classe CInstant
#include "instant.h"
//Pour la classe CHttpGsm
#include "httpgsm.h"
//Pour la classe CAcces
#include "acces.h"
//Pour la classe CTexte
#include "texte.h"

//Paramètres :
#define PT_ACCES_WEB "coriolis"
#define PT_ACCES_WEB "Free"
//#define SERVEUR_WEB "10.0.255.200"
#define SERVEUR_WEB "http://185.182.169.30"
#define PORT_SERVEUR 64120
#define SERVEUR_WEB "185.182.169.30"
#define PORT_SERVEUR 83
#define SERVEUR_WEB "sn2hasp.free.beeceptor.com"

//Api monsieur Irazoqui :

/*#define SERVEUR_WEB "185.182.169.30"
#define PORT_SERVEUR 1024
#define API    		"/api/verifierReservationApi?telephone="*/

//Api monsieur Pons :

#define SERVEUR_WEB "acces-gsm.alwaysdata.net"
#define PORT_SERVEUR 80
#define API    		"/api/verifierReservationApi.php?telephone="
/*#define API    		"/recup.reservation.2.0.php?telephone="*/

//Api Dany Sevrin (Ne fonctionne pas encore le 02/04/2024)

/*#define SERVEUR_WEB "10.0.2.16"
#define PORT_SERVEUR 1024
#define API    		"/api/verifierReservationApi.php?telephone=0646811496"*/


class CAppli
{
	private:
		unsigned long	m_top_run = 0;
		CSuperGSM		m_gsm;
		CHttpGsm		m_http_gsm;
		CInstant 		m_instant_reseau;
		CAcces			m_acces;

	public:
		CAppli(){};
		~CAppli(){};

		void Init();
		void Run(unsigned long intervalle);
		void Run();
		
		String GetInfoRecup(String& reponse_serveur);


};

#endif
