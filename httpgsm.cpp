#include "appli.h"

//Constructeur
CHttpGsm::CHttpGsm(){}

void CHttpGsm::Init(String serveur, int port)
{
	m_port = port;
	m_serveur = serveur;
	//Affichage du port dans le moniteur série
	Serial.print("Port: ");
	Serial.println(m_port);
	//Affichage du serveur dans le moniteur série
	Serial.print("Host: ");
	Serial.println(m_serveur);
}

int CHttpGsm::EnvoiRequete(String api, String param)
{
	Serial.print("Envoi requête : ");
	Serial.println( api + param);

	//Test connexion serveur
	if (connect(m_serveur.c_str(), m_port)) 
	{
		Serial.println("Connecté -> Envoi");
		//Requête HTTP:
		print("GET ");
		print((api+param).c_str());
		println(" HTTP/1.1");
		print("Host: ");
		println(m_serveur.c_str());
		println("Connection: close");
		println();
		return 1;
	} 
	else Serial.println("Échec");
	return 0;
	
}

String CHttpGsm::GetReponseClient(int delai)
{
	String reponse = "";
	Serial.println("Attente réponse client");
	unsigned long	attendu = millis()+delai;
	
	//Attente limitée par le délai
	while (millis() < attendu) 
	{
		if ((millis()%1000)==0)
		{
			delay(10); 
			Serial.println(reponse.length());
		};
		//Octets du serveur lus et stockés
		if (available()) reponse += (char)read();

		//Le serveur est déconnecté on stoppe l'attente client
		if (!available() && !connected()) 
		{
			Serial.println("Déconnecté.");
			stop();
			break;
		}
	}
	Serial.println("Fin d'attente.");
	return reponse; 
}