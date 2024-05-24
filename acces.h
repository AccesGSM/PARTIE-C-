//Tous les fichiers ".h" reprennent les mêmes
//directives de préprocesseur de manière à ne compiler qu'une seule fois 
//les ".h" et ".cpp" correspondants
//Par convention la directive porte le nom des fichiers en majuscule suivi de "_H"
#ifndef ACCES_H
#define ACCES_H


//Déclaration de la classe
class CAcces 
{
	private:
		
		String m_nom_acces;
		int m_portA;
		String m_nom_portA; 
		int m_portB;
		String m_nom_portB;
		int m_sec_gache;
		bool m_hs;
		CInstant m_instant_ferme;
		CInstant m_horloge = 0;
		uint32_t m_millis_start;
		
	public:
	    CAcces();
		void Ouvre(int minutes);
		int CtrlTempsRestant(CPeriode reservation);
		void Controle();
		String GetReponseAcces(String reponse_serveur);
		void SetHeureSystem(String& reponse_serveur);
		CInstant GetHeureSystem();
		CPeriode GetPeriodeServeur(String& reponse_serveur);

	
};
//Fin des directives de préprocesseur 
#endif
