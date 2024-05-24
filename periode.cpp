#include "appli.h"
// Constructeurs
CPeriode::CPeriode()
{
	// Initialisation des variables membres par défaut
	m_duree_heure = 0.0f;
	m_index = 0;
	m_cycle = 0;
}

CPeriode::~CPeriode()
{
	// Destructeur par défaut
}


CPeriode::CPeriode(float duree, int index, unsigned int cycle) 
{
    m_duree_heure = duree;
    m_index = index;
    m_cycle = cycle;
}

CPeriode::CPeriode(uint32_t instant, float duree, int index, unsigned int cycle) 
{
    m_duree_heure = duree;
    m_index = index;
    m_cycle = cycle;
}


// Setters
void CPeriode::SetFin(uint16_t jour, uint16_t mois, uint16_t an) 
{
	CInstant fin;
	fin.SetDate(jour, mois, an);
	fin.SetHeure(GetHeure(), GetMinute(), GetSec());
	if (fin.GetInstant() < GetInstant()) m_index = 0;
	else m_index = (fin.GetInstant() - GetInstant())/(m_cycle*86400);
}

void CPeriode::SetDuree(float duree) 
{
	m_duree_heure = duree;
}

void CPeriode::SetCycle(unsigned int cycle) 
{
	m_cycle = cycle;
}

void CPeriode::SetIndex(int index) 
{
	m_index = index;
}

void CPeriode::SetIndex(unsigned int jour, unsigned int mois, unsigned int an, unsigned int cycle, unsigned int jour_fin, unsigned int mois_fin, unsigned int an_fin) 
{
	// Met à jour la date de début en utilisant le constructeur de CInstant
	CInstant::SetDate(jour, mois, an);

	// Met à jour la date de fin en utilisant le constructeur de CInstant
	CInstant::SetDate(jour_fin, mois_fin, an_fin);

	// Met à jour le cycle et l'index
	m_cycle = cycle;
}


void CPeriode::SetPeriodeServeur(String reponse_serveur) 
{
    // Trouver les positions des éléments nécessaires
    size_t pos_day = reponse_serveur.indexOf(" ") + 1;
    size_t pos_month = reponse_serveur.indexOf(" ", pos_day + 1) + 1;
    size_t pos_year = reponse_serveur.indexOf(" ", pos_month + 1) + 1;
    size_t pos_hour = reponse_serveur.indexOf(" ", pos_year + 1) + 1;
    size_t pos_minute = reponse_serveur.indexOf(":", pos_hour + 1);
    size_t pos_second = reponse_serveur.indexOf(":", pos_minute + 1);

    // Extraire les parties de la date et de l'heure
    unsigned int day = reponse_serveur.substring(pos_day, pos_day + 2).toInt();
    unsigned int month = Month2Nombre(reponse_serveur.substring(pos_month, pos_month + 3));
    unsigned int year = reponse_serveur.substring(pos_year, pos_year + 4).toInt();
    unsigned int hour = reponse_serveur.substring(pos_hour, pos_hour + 2).toInt();
    unsigned int minute = reponse_serveur.substring(pos_minute + 1, pos_minute + 3).toInt();
    unsigned int second = reponse_serveur.substring(pos_second + 1, pos_second + 3).toInt();

    // Mettre à jour l'instant de la période en utilisant les informations extraites
    SetDate(day, month, year, hour, minute, second);
}

// Autres méthodes
uint32_t CPeriode::MinutesRestantes(CInstant instant) 
{
	
    for (int i = 0; i <= m_index; i++) 
    {
        if (instant.GetInstant() >= GetDebut(i) && instant.GetInstant() < GetFin(i)) 
        {
			return (GetFin(i) - instant.GetInstant()) / 60;
        }
    }
	
    return 0; // Aucune période correspondante trouvée
}

bool CPeriode::Coincide(CPeriode periode) 
{
	// Obtenez les instants de début et de fin de la période en cours
	uint32_t debut_periode_actuelle = GetInstant();
	uint32_t fin_periode_actuelle = GetFin().GetInstant();

	// Obtenez les instants de début et de fin de la période donnée
	uint32_t debut_periode_donnee = periode.GetInstant();
	uint32_t fin_periode_donnee = periode.GetFin().GetInstant();

	// Vérifiez si les périodes se chevauchent ou si l'une commence juste après la fin de l'autre
	if ((debut_periode_actuelle <= fin_periode_donnee && fin_periode_actuelle >= debut_periode_donnee) ||
		(debut_periode_donnee <= fin_periode_actuelle && fin_periode_donnee >= debut_periode_actuelle)) {
		return true; // Les périodes coïncident
	} else {
		return false; // Les périodes ne coïncident pas
	}
}

float CPeriode::GetDuree() 
{
	return m_duree_heure;
}

uint32_t CPeriode::GetDebut(int index) 
{
	//if (index >= 0 && index < m_index) 
		return (CInstant::m_instant + m_cycle * 86400 *index) ; 
	//Index non valide
	return 0;
}


uint32_t CPeriode::GetFin(int index) 
{
	return (m_instant + m_duree_heure*3600+ index *m_cycle*86400); 
}

CInstant CPeriode::GetFin() 
{
	return GetFin(m_index); 
}

CPeriode CPeriode::GetPeriode(int index) 
{	
	CPeriode periode = CPeriode (m_instant + (this->m_cycle * 86400* m_index), this->m_duree_heure, this->m_index, this->m_cycle);
	return periode;
}

String CPeriode::GetMessage() 
{
	String message = "\nPériode du ";
	message += CInstant::GetMessage();

	message += "AU " + Get2Digit(GetFin().GetJour()) + "/" + Get2Digit(GetFin().GetMois()) + "/" + Get2Digit(GetFin().GetAn());
	message += ". Durée : " + String(m_duree_heure) + " heure(s).";
	return message;
}
