#include "appli.h"

//Constructeur par défaut
CInstant::CInstant() {};
//Constructeur par passage d'argument (instant : secondes depuis le 1/1/2000 à 00:00:00)
CInstant::CInstant(uint32_t instant) 
{ 
	m_instant = instant; 
}

//Get m_instant typé unsigned long 32 bits
uint32_t CInstant::GetInstant()
{
	return m_instant;
}

void CInstant::SetDate(
	uint16_t jour, uint16_t mois, uint16_t an,
	uint16_t heure, uint16_t minute, uint16_t second)
{
	SetDate(jour, mois, an);
	SetHeure(heure,minute,second); 
}

bool CInstant::EstBissextile(uint16_t an)
{
	if (an < 2000) an += 2000;
	return (an % 4 == 0 && an % 100 != 0) || (an % 400 == 0);
}

void CInstant::SetHeure(uint16_t heure, uint16_t minute, uint16_t seconde)
{

    // Calcul du nombre de secondes écoulées depuis le début de la journée
    uint32_t secondes_dans_la_journee = (uint32_t)heure * 3600 + minute * 60 + seconde;

    // Soustraire le nombre de secondes dans la journée actuelle
    m_instant -= (m_instant % 86400);

    // Ajouter le nombre de secondes dans la nouvelle journée
    m_instant += secondes_dans_la_journee;
}

//Mise à jour de m_instant avec une nouvelle date
void CInstant::SetDate(uint16_t jour, uint16_t mois, uint16_t an)
{
	//Contrôle et maj année si an=24 pour 2024 (exemple)
	if (an < 2000) an += 2000;
//Serial.print("jour : ");
//Serial.println(jour);
//Serial.print("mois : ");
//Serial.println(mois);
//Serial.print("an : ");
//Serial.println(an);
	// Calcul du nombre de secondes depuis le début de la journée
	uint32_t secondes_dans_la_journee = (m_instant % 86400);

	// Calcul du nombre de secondes écoulées depuis le 1/1/2000 à 0h0m0s //////////////////////////////////////////////////////
	//Mise à 0 de m_instant
	m_instant = 0;

	//Ajout de 31622400 secondes pour chaque année bissextile
	//Ajout de 31536000 secondes pour chaque année non-bissextile
	//à m_instant
	for (uint16_t i = 2000; i < an; i++)
	{
		if (EstBissextile(i)) // 366 jours
			m_instant += 31622400; 
		else // 365 jours
			m_instant += 31536000; 
	}

	// Mois
	//Ajout de 86400 secondes par le nombre de jours de chaque mois
	//Grâce au tableau suivant
	static const uint16_t jours_mois[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	for (uint16_t m = 1; m < mois; m++)
	{
		m_instant += jours_mois[m] * 86400;
		// Ajoute un jour en février les années bissextiles
		if (m == 2 && EstBissextile(an)) 
			m_instant += 86400; 
	}
	//Ajout de 86400 secondes pour chaque jour du mois en cours
	//(0 seconde pour le 1° du mois et j-1 pour les autres)
	m_instant += (jour - 1) * 86400;

	//Remise à l'heure de m_instant avec les secondes de la journée 
	m_instant += secondes_dans_la_journee;
//Serial.print("m_instant : ");
//Serial.println(m_instant);
}

uint16_t CInstant::GetAn()
{
	CInstant t;
	//Calcul de l'année
	uint16_t an = 1999;
	while (t.m_instant <= m_instant)
		t.SetDate(1, 1, ++an);
	return an - 1;
}

uint16_t CInstant::GetMois()
{
	CInstant t;
	//Calcul de l'année
	uint16_t mois = 0;
	while (t.m_instant <= m_instant)
		t.SetDate(1, ++mois, GetAn());
	return mois - 1;
}

uint16_t CInstant::GetJour()
{
	CInstant t;
	//Calcul de l'année
	uint16_t jour = 0;
	while (t.m_instant <= m_instant)
		t.SetDate(++jour, GetMois(), GetAn());
	return jour - 1;
}

uint16_t CInstant::GetJourSem()
{
	// Calcul du nombre de jours depuis le début de la journée modulo 7 pour le jour semaine
	//+ 6 permet de recaler le 0>dimanche, 1>lundi, 2>mardi, ..., 6>samedi
	return ((m_instant / 86400) + 6) % 7;
}

String CInstant::GetJourSem(uint16_t nb_car)
{
	String jours_sem[7] = { "DIMANCHE", "LUNDI", "MARDI", "MERCREDI", "JEUDI", "VENDREDI", "SAMEDI", };
	return jours_sem[GetJourSem()].substring(0, nb_car);
}

String CInstant::GetMois(uint16_t nb_car)
{
	String tab_mois[12] = { "JANVIER", "FEVRIER", "MARS", "AVRIL", "MAI", "JUIN", "JUILLET", "AOUT", "SEPTEMBRE", "OCTOBRE", "NOVEMBRE", "DECEMBRE"};
	return tab_mois[GetMois()-1].substring(0, nb_car);
}

String CInstant::GetMessage()
{
	String message = GetJourSem(3) + " ";
	message += String(GetJour()) + "/";
	message += GetMois(4) + "/";
	message += String(GetAn()) + " A ";
	message += Get2Digit(GetHeure()+1) + "H";
	message += Get2Digit(GetMinute()) + ":";
	message += Get2Digit(GetSec()) + "\n";
 
	return message;
}

uint16_t CInstant::GetHeure()
{
	return (uint16_t)((m_instant % 86400) / 3600);
}

uint16_t CInstant::GetMinute()
{
	return (uint16_t)((m_instant % 3600) / 60);
}

uint16_t CInstant::GetSec()
{
	return (uint16_t)(m_instant % 60);
}

//Conversion de l’abréviation anglaise du mois en nombre de 1 à 12
int CInstant::Month2Nombre(String abreviation)
{
    static const String tab_abreviation[] = 
	{
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
	// Les mois sont indexés à partir du mois en anglais Janvier <=> 1
    for (int i = 0; i < 12; ++i)
        if (abreviation == tab_abreviation[i])
            return i + 1;  
    return -1;  // Mois non trouvé
}

int CInstant::DernierDimanche(uint16_t mois, uint16_t annee) 
{
    // Détermination du nombre de jours dans le mois
    int joursDansMois;
    if (mois == 2) 
    {
        // Février, gestion de l'année bissextile
        if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0))
            joursDansMois = 29; // Février a 29 jours dans une année bissextile
        else
            joursDansMois = 28;
    } 
    else 
    {
        // Tous les autres mois ont un nombre de jours prédéfini
        static const int joursParMois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        joursDansMois = joursParMois[mois - 1];
    }

    // Parcours du mois depuis la fin jusqu'à trouver un dimanche
    for (int jour = joursDansMois; jour >= (joursDansMois - 6); --jour) 
    {
        SetDate(jour, mois, annee); // Configuration de la date à vérifier
        if (GetJourSem() == 0) 
        {
            // Si c'est un dimanche, retourner le jour
            return jour;
        }
    }
    return -1; // Retourne -1 s'il n'y a pas de dimanche dans le mois
}

bool CInstant::EstEnHeureDete() 
{
		// Récupérer la date actuelle
		uint16_t jour = GetJour();
		uint16_t mois = GetMois();
		uint16_t an = GetAn();
		
		// Mois et jour du dernier dimanche de mars
		int dernierDimancheMars = DernierDimanche(3, an);
		 while (true) {
			SetDate(dernierDimancheMars, 3, an, GetHeure(), GetMinute(), GetSec());
			if (GetJourSem() == 0) // Si c'est un dimanche
				break;
			dernierDimancheMars--;
		}

		int dernierDimancheOctobre = DernierDimanche(10, an);
		 while (true) {
			SetDate(dernierDimancheOctobre, 10, an, GetHeure(), GetMinute(), GetSec());
			if (GetJourSem() == 0) // Si c'est un dimanche
				break;
			dernierDimancheOctobre--;
		}
		// Vérifier si nous sommes en heure d'été (dernier dimanche de mars à 2h)




        if ((mois >= 4 && mois <= 9) || (mois == 3 && (jour > dernierDimancheMars || (jour == dernierDimancheMars && GetHeure() >= 2))) ||(mois == 10 && (jour < dernierDimancheOctobre || (jour == dernierDimancheOctobre && GetHeure() < 3)))) 
	
	{ // Pour octobre
        return true;
    } 
	else 
	{
        return false;
    }
	
}

void CInstant::DecaleGMT()
{
    // Déterminer si nous sommes en heure d'été ou d'hiver
    bool estEnHeureDete = EstEnHeureDete();
	if (estEnHeureDete == 1)
		m_instant += 3600;
	else
		m_instant += 0;
	
}

void CInstant::Add(uint32_t secondes)
{
	m_instant += secondes;
}

void CInstant::SetInstant(CInstant instant)
{
	m_instant = instant.m_instant;
}

bool CInstant::SuperieurA(CInstant instant)
{
	return m_instant > instant.m_instant;
}

void CInstant::SetInstant(uint32_t instant)
{
	m_instant = instant;
}

String CInstant::Get2Digit(int nombre)
{
  String val = String(nombre);
	if (nombre < 10)
		val = "0"+val;
	 return val;
		
}
