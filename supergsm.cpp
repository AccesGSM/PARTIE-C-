#include "appli.h"

CSuperGSM::CSuperGSM(){}

CSuperGSM::~CSuperGSM(){}

void CSuperGSM::Init(String id_pt_acces_web)
{
	//Initialisation du GSM
	Serial.println("Initialisation du SuperGSM");
	//Mode Carte SHIELD2
	if(m_type_carte == SHIELD2)
		Serial.println("Mode réception d'appels : SHIELD2");
	else
		Serial.println("Mode réception SMS : MKR1400");
	
	//Connexion au réseau GSM	
	Serial.print("Attente connexion au réseau GSM avec le code PIN : ");
	Serial.println(m_code_pin);
	while (m_reseau_gsm.begin(m_code_pin.c_str()) != GSM_READY)
	{
		Serial.print(".");
		delay(1000);
	}
	Serial.println("\nConnexion GSM!");
			
	//Assure que le combiné est raccroché
	m_appel.hangCall();
	Serial.println("Attente d'appels OK");
		
	//Connexion au WEB de l'opérateur
	Serial.print("Attente WEB via l'APN opérateur : ");
	Serial.print(id_pt_acces_web);
	while (m_conx_web_operateur.attachGPRS(	id_pt_acces_web.c_str(),"","")!= GPRS_READY)
	{
		Serial.print(" .");
		delay(1000);
	}
	Serial.println("\nConnecté au WEB!");
}

String 	CSuperGSM::GetNumAppel()
{
	return m_num_appel;
}


short CSuperGSM::CtrlAppels() 
{
	//Récupération du statut de l'appel
	short statut = m_appel.getvoiceCallStatus();
	switch (statut) 
	{
		//IDLE_CALL = appel en attente
		case IDLE_CALL: 	//Rien ne se passe
			break;
		case RECEIVINGCALL: //Réception d'appel
			Serial.println("Réception d'appel");
			//Récupération du numéro d'appel
			char numtel[20];
			m_appel.retrieveCallingNumber(numtel, 20);
			m_num_appel = String(numtel);
			Serial.print("Numéro :");
			Serial.println(m_num_appel);
			//On décroche
			m_appel.answerCall();
			delay(200);
			//On raccroche
			m_appel.hangCall();
			Serial.println("Raccroché");
			delay(200);
			break;
/*		case TALKING:  		//Appel établi
			Serial.println("On laisse causer, on peut raccrocher avec la touche entrée");
			while (Serial.read() != '\n') delay(100);
			//On raccroche
			m_appel.hangCall();
			Serial.println("Attente nouvel appel.");
			return statut;
			break;
*/
	}
	return statut;
}

void CSuperGSM::EnvoiSMS(String message) 
{
	//envoi du message d'accès suite à l'appel
	Serial.println("Message Envoyé :");
	Serial.println(message);
	m_sms.beginSMS(m_num_appel.c_str());
	m_sms.print(message.c_str());
	m_sms.endSMS();
}

bool CSuperGSM::RecoitSMS(String& message)
{
	message = "";
	char c;
	char NumTel[20];
	// S'il y a des SMS disponibles()
	if (m_sms.available()) 
	{
		Serial.println("\nMessage recu du :");

		// Obtenir le numéro de téléphone à distance
		m_sms.remoteNumber(NumTel, 20);
		m_num_appel = String(NumTel);
		Serial.println(m_num_appel);
	
		// Lire les octets du message et les imprimer
		while (c = m_sms.read()) 
		{
			message += c;
			Serial.print(c);
		}
	
		Serial.println("\nFIN DU MESSAGE");
	
		// Effacer le message de la mémoire du modem
		m_sms.flush();
		Serial.println("MESSAGE SUPPRIMÉ");
		
  }
	return (message.length()>0);
}