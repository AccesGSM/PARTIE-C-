//Tous les fichiers ".h" reprennent les mêmes
//directives de préprocesseur de manière à ne compiler qu'une seule fois 
//les ".h" et ".cpp" correspondants
//Par convention la directive porte le nom des fichiers en majuscule suivi de "_H"
#ifndef PERIODE_H
#define PERIODE_H
#include "instant.h"
/*Matériel :
ARDUINO UNO
ou
ARDUINO MEGA
*/

//Infos et versions réalisées
#include "infos.versions.h"
 
/*extraction heure, minute, seconde, jour, mois, annees de reponse serveur
 void SetdateServeur(String reponse_serveur);
*/
//Librairie Arduino
#include <Arduino.h>

//Librairies pour les classes du projet
//Pour la classe CNvClasse

//Paramètres divers :

//Déclaration de la classe

class CPeriode : public CInstant 
{

private:
    float m_duree_heure;
    int m_index;
    unsigned int m_cycle;
	
public:
    // Constructeurs
    CPeriode();
    ~CPeriode();
    //CPeriode(String& reponse_serveur);
    CPeriode(float duree, int index, unsigned int cycle);
    CPeriode(uint32_t instant, float duree, int index, unsigned int cycle);
    CPeriode(unsigned int jour, unsigned int mois, unsigned int an, unsigned int cycle, unsigned int jour_fin, unsigned int mois_fin, unsigned int an_fin);

    // Autres méthodes
    uint32_t MinutesRestantes(CInstant instant);
    bool Coincide(CPeriode periode);
    float GetDuree();
    uint32_t GetDebut(int index);
    uint32_t GetFin(int index);
    CPeriode GetPeriode(int index);
    CInstant GetFin();
    String GetMessage();

    // Setters
    void SetFin(unsigned int jour, unsigned int mois, unsigned int an);
    void SetDuree(float duree);
    void SetCycle(unsigned int cycle);
    void SetIndex(int index);
    void SetIndex(unsigned int jour, unsigned int mois, unsigned int an, unsigned int cycle, unsigned int jour_fin, unsigned int mois_fin, unsigned int an_fin);
    void SetPeriodeServeur(String reponse_serveur);
};
#endif