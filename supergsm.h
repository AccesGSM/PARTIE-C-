//Tous les fichiers ".h" reprennent les mêmes
//directives de préprocesseur de manière à ne compiler qu'une seule fois 
//les ".h" et ".cpp" correspondants
//Par convention la directive porte le nom des fichiers en majuscule suivi de "_H"
#ifndef SUPERGSM_H
#define SUPERGSM_H

/*Matériel :
Circuit:
* Carte MKR GSM 1400 ou carte GSM ARDUINO SHIELD2
Pour la carte MKR GSM 1400 :
* Antenne
* Carte SIM IOT
Pour la carte GSM ARDUINO SHIELD2
* Carte SIM grand format 
*/

//Infos :
//http://www.arduino.cc/en/Tutorial/GSMExamplesReceiveSMS
//http://www.arduino.cc/en/Guide/ArduinoGSMShield#toc11
//http://www.arduino.cc/en/Tutorial/GSMExamplesReceiveVoiceCall
//https://fr.wikipedia.org/wiki/Access_Point_Name
//https://github.com/arduino-libraries/MKRGSM/blob/master/src/GSM_SMS.h

//Librairies :
//https://github.com/arduino-libraries/MKRGSM/tree/master 
//https://docs.arduino.cc/retired/archived-libraries/GSM

#include <GSM.h>		//Pour la carte GSM ARDUINO SHIELD2
//#include <MKRGSM.h> 	//Pour la carte GSM MKR1400

//Type de carte utilisée
#define	SHIELD2			'S'
#define	MKR1400			'M'
#define	CODE_PIN_FREE	"0000"
#define	CODE_PIN_NEUF	"1234"
#define	CODE_PIN		CODE_PIN_FREE

class CSuperGSM
{
	private:
		GSM m_reseau_gsm;
		GSMVoiceCall m_appel;
		GSM_SMS m_sms;
		GPRS m_conx_web_operateur;
		char m_type_carte = SHIELD2;
		String m_code_pin = CODE_PIN;
		String m_num_appel;
		
	public:
		CSuperGSM();
		~CSuperGSM();
		
		void Init(String id_pt_acces_web);
		short CtrlAppels();
		void EnvoiSMS(String message);
		bool RecoitSMS(String& message);
		String GetNumAppel();
};
//Fin des directives de préprocesseur 
#endif