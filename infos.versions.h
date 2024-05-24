#ifndef INFOS_VERSIONS_H
#define INFOS_VERSIONS_H

/*Création du projet : 
#define	VERSION	"GSM_ACCES_2024.02.XX.V00"
	Création
#define	VERSION	"GSM_ACCES_2024.02.XX.V01"

#define	VERSION	"GSM_ACCES_2024.02.XX.V02"

#define	VERSION	"GSM_ACCES_2024.02.12.V03"

#define	VERSION	"GSM_ACCES_2024.02.12.V04"
	Objectifs :
	Envoi requête API avec num tel appelant 
	Récup réponse
	Réseau GSM OK
	WEB OK
	Récup num appelant OK
	Envoi requête OK
	Réception requête OK
#define	VERSION	"GSM_ACCES_2024.03.04.V05"
	Objectifs :
	Création de la fonction RecoitSMS	OK
	Test d'un envoi et de réception de SMS	OK
#define	VERSION	"GSM_ACCES_2024.03.05.V06"
	Objectifs :
	Intégration de CAcces et de CPeriode
	Mise à jour de CInstant
	Compile mais CAcces incomplète :
	- GetHeureSystem();
	- GetReponseAcces(String reponse_serveur);
	- Controle()
#define	VERSION	"GSM_ACCES_2024.03.18.V07"
	Mise à jour de CAcces (corenthin me la envoyé) mais il manque : 
	- GetReponseAcces(String reponse_serveur);
	- Controle()
	Mais le programme compile et fonctionne en l'état actuel
#define	VERSION	"GSM_ACCES_2024.03.18.V08"
	Mise à jour de CAcces et le programme fonctionne complètement (Corenthin est en train de réaliser le décalage GMT+1 car
	dans ce programme, le serveur nous renvoie l'heure GMT+0 qui ne correspond pas à l'heure française)
#define	VERSION	"GSM_ACCES_2024.03.27.V09"
	Changement de l'API en modèle PHP MVC (Dany et Quentin sont en train de travailler dessus)
	Décalage GMT est fonctionnel (Réalisé par Corenthin)
*/

#define	VERSION	"GSM_ACCES_2024.03.27.V09"
 
#endif
