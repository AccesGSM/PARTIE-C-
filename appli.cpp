#include "appli.h"

void CAppli::Init()
{
	//Initialisation de la LED (port 13) embarquée
	pinMode(13, OUTPUT);
	//Initialisation du port série
	Serial.begin(115200);
	while(!Serial);
	//Affichage VERSION
	Serial.println("\n");
	Serial.println(VERSION);
	
	//Initialisation du SuperGSM
	m_gsm.Init(PT_ACCES_WEB);
	//Initialisation de la partie http gsm
	m_http_gsm.Init(SERVEUR_WEB, PORT_SERVEUR);
	delay(1000);
	String reponse_serveur = "date: Thu, 31 Aug 2023 10:47:23 GMT";
	//Test envoi requête API sans numéro pour récupérer l'heure et date
	if (m_http_gsm.EnvoiRequete(API, "" ))
	{	
		//Récupération de la réponse http dans un String reponse
		reponse_serveur = m_http_gsm.GetReponseClient(10000);
		Serial.println(reponse_serveur);
		//Mise à l'heure de l’accès depuis le serveur
		m_acces.SetHeureSystem(reponse_serveur);
		//Affichage heure accès
		Serial.println(m_acces.GetHeureSystem().GetMessage());
	}
}

void CAppli::Run(unsigned long intervalle)
{
	//Temporisation KO/////////////////
	if (millis()  < m_top_run) return;
	m_top_run = millis() + intervalle;
	//Temporisation OK/////////////////
		
	String reponse_serveur = "";
	//Déclaration objet période
	
	//Vérification appel entrant par CtrlAppels()
	if (m_gsm.CtrlAppels()==RECEIVINGCALL)
	{
		//Récupération numéro appel entrant
		
		//Envoi requête serveur demande période réservation supprime le préfixe international et rajoute 0
		m_http_gsm.EnvoiRequete(API, "0" + m_gsm.GetNumAppel().substring(3));
		//Récupération réponse client
		reponse_serveur = m_http_gsm.GetReponseClient(10000);
		Serial.println(reponse_serveur);
		//Serial.println(m_instant_reseau.GetMessage());
		m_gsm.EnvoiSMS(m_acces.GetReponseAcces(reponse_serveur));
		//m_gsm.EnvoiSMS("bonjour");
	}
	//Mise à jour horloge 
	
	//Affiche l'heure toutes les 30 secondes
	
	//Vérification SMS entrant
	String sms;
	if(m_gsm.RecoitSMS(sms))
	{
		//m_acces.ConfigParSms(sms);
		m_gsm.EnvoiSMS(sms);
	}
	
	//Affiche état accès
	m_acces.Controle();
}

void CAppli::Run()
{
}

/*
String CAppli::GetInfoRecup(String& reponse_serveur)
{
	String infos 	= "Bonjour ";
	infos 			+= GetValeur(reponse_serveur, "prenom:");
	infos 			+= " ";
	infos 			+= GetValeur(reponse_serveur, "usager:");
	infos 			+= "\nVotre acces : ";
	infos 			+= GetValeur(reponse_serveur, "designation:");
	infos 			+= "\n";
	return infos;
} 
*/