//Tous les fichiers ".h" reprennent les mêmes
//directives de préprocesseur de manière à ne compiler qu'une seule fois 
//les ".h" et ".cpp" correspondants
//Par convention la directive porte le nom des fichiers en majuscule suivi de "_H"
#ifndef HTTPGSM_H
#define HTTPGSM_H

#include <GSM.h>		//Pour la carte GSM ARDUINO SHIELD2
//#include <MKRGSM.h> 	//Pour la carte GSM MKR1400


class CHttpGsm : public GSMClient
{
	private:
		String m_serveur;
		int m_port;
		//String m_chemin;
		
	public:
		CHttpGsm();
		
		void Init(String serveur, int port);
		int EnvoiRequete(String api, String param);
		String GetReponseClient(int delai);
};
//Fin des directives de préprocesseur
#endif