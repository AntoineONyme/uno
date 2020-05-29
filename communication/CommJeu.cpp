#include "CommJeu.h"
#include "../cartes/StaticFunction.h"

void split(std::string const& str, const char delim, vector<int>* out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		string subs = str.substr(start, end - start);
		if (subs.size() > 0)
		{
			out->push_back(std::stoi(subs));
		}
	}
}

bool CommJeu::initialiserTour()
{
	_donneesJoueur.cartesPiochees->clear();
	DonneesCommJeu donneesJoueur;
	_donneesJoueur = donneesJoueur;

	_donneesAdversaires.cartesPiochees->clear();
	DonneesCommJeu donneesAdversaires;
	_donneesAdversaires = donneesAdversaires;

	_finManche = FinManche::manche_en_cours;

	return true;
}

CommJeu::CommJeu(Salon* psalon)
{
	_salon = psalon;
	string nfic = _salon->getNomSalon() + ".jeu.txt";

	_fichier = new Fichier(nfic, REPERTOIRE, false);


	while (true)
	{
		_fichier->synchroniser(REPERTOIRE);

		if (!_fichier->fichierExiste(nfic, REPERTOIRE)) {
			cout << "Ce salon n'existe pas encore...\n";
		}
		else
		{
			break;
		}

	}
}

//	On libère les aggrégations
CommJeu::~CommJeu()
{
	delete _donneesJoueur.cartesPiochees;
	delete _donneesAdversaires.cartesPiochees;
	if (_fichier != nullptr)
		delete _fichier;
}

//	Cette fonction attend que ce soit au joueur actuel de jouer
void CommJeu::attenteTour()
{
	_fichier->synchroniser(REPERTOIRE);

	//	On commence par lire le fichier au cas où on joue tout seul / si la syncronisation a mis bcp de temps
	//	Normalement ce sont les données du joueur actuel qui devraient être visibles la première fois
	while (true)
	{
		cout << "attente...";

		vector<string>* lignes = _fichier->lectureLignes();
		if (lignes->size() > 8) {

			//	On regarde si celui qui a envoyé ça n'est pas le même joueur
			if (lignes->operator[](1) != std::to_string(_salon->getJoueurActuel()))
			{

				string nomJoueur = _salon->getJoueur(lignes->operator[](1));

				//	Carte Jouée
				if (lignes->operator[](2).size() > 0)
				{
					_donneesAdversaires.carteJouee = std::stoi(lignes->operator[](2));
					cout << endl;
				}
				//	Carte déja subie
				if (lignes->operator[](3).size() > 0)
				{
					_donneesAdversaires.carteDejaSubie = true;
					cout << nomJoueur << " n'a pas joue de carte.\n";
				}
				else {
					_donneesAdversaires.carteDejaSubie = false;
					if (_donneesAdversaires.carteJouee >= 0)
					{
						cout << nomJoueur << " vient de jouer la carte ";
						showCardName(_donneesAdversaires.carteJouee);
						cout << "\n";
					}
				}
				//	Uno
				if (lignes->operator[](4).size() > 0)
				{
					cout << nomJoueur << " declare un Uno." << endl;
				}
				//	Contre-Uno
				if (lignes->operator[](5).size() > 0)
				{
					int joueur = std::stoi(lignes->operator[](5));
					cout << nomJoueur << " declare un contre uno contre " << _salon->getJoueur(joueur) << "." << endl;
					if (joueur == _salon->getJoueurActuel())
					{
						_donneesAdversaires.joueurContreUno = 1;
					}
				}
				//	Si c'est la fin de la manche
				if (lignes->operator[](6).size() > 0)
				{
					if (lignes->operator[](6) == "abandon")
					{
						cout << nomJoueur << " a abandonne la partie. Vous avez donc gagne !" << endl;
						_finManche = FinManche::manche_abandonnee;
					}
					else {
						cout << nomJoueur << " vient de jouer sa dernière carte, il remporte donc la manche !" << endl;
						_finManche = FinManche::manche_terminee;
					}
				}
				//	Si pioche
				if (lignes->operator[](7).size() > 0)
				{
					split(lignes->operator[](7), ' ', _donneesAdversaires.cartesPiochees);
					cout << nomJoueur << " vient de piocher " << _donneesAdversaires.cartesPiochees->size() << " carte(s)" << endl;
				}
				//	Si message
				if (lignes->operator[](8).size() > 0)
				{
					cout << "[" << nomJoueur << "] " << lignes->operator[](8) << endl;
				}
			}

			if (_finManche == FinManche::manche_terminee)
			{
				cout << "Tu vois !" << endl;
			}

			//	On regarde si le joueur précédent appelle le joueur actuel à jouer
			if (lignes->operator[](0) == std::to_string(_salon->getJoueurActuel()))
			{
				//	Dans ce cas, attente initiale terminée : c'est au joueur de jouer
				return;
			}

			//	Si fin de la manche, on peut sortir du fichier pour attendre son tour (utile si plus de 2 joueurs)
			if (_finManche == FinManche::manche_terminee)
			{
				return;
			}
		}

		_fichier->detecteChangement();
	}
}

void CommJeu::declareCartesPiochees(vector<int>* cartesPiochees)
{
	if (cartesPiochees != nullptr)
	{
		for (int i = 0; i < cartesPiochees->size(); i++)
		{
			_donneesJoueur.cartesPiochees->push_back(cartesPiochees->operator[](i));
		}
		delete cartesPiochees;
	}

}

bool CommJeu::declarerUno() {
	if (_donneesJoueur.declareUno)
	{
		return false;
	}
	_donneesJoueur.declareUno = true;
	return true;
}

bool CommJeu::declareContreUno(int idJoueur) {
	if (_donneesJoueur.joueurContreUno != -1)
	{
		return false;
	}
	_donneesJoueur.joueurContreUno = idJoueur;
	return true;
}

//	Permet d'envoyer les actions du tour, puis attente de son tour
bool CommJeu::finTourAtt(FinManche finManche) {
	//On écrit les données
	if (!finTour(finManche))
		return false;

	//On réinitialiser les attribus de jeu
	initialiserTour();

	//On va maintenant attendre que ce soit notre tour avant de débloquer, sauf si abandon
	if (finManche == FinManche::manche_en_cours)
	{
		attenteTour();
	}

	return true;
}

CommJeu::FinManche CommJeu::getStatusManche()
{
	return _finManche;
}

bool CommJeu::finTour(FinManche finManche)
{
	vector<string> lignes;

	//Ligne 1 : on donne l'id du joueur suivant
	lignes.push_back(std::to_string(_salon->idNextPlayer()));

	//Ligne 2 : on donne l'id du joueur actuel
	lignes.push_back(std::to_string(_salon->getJoueurActuel()));

	//Ligne 3 : id carte jouée, vide si passé son tour (+ pioche dans ce cas)
	if (_donneesJoueur.carteJouee != -1)
		lignes.push_back(std::to_string(_donneesJoueur.carteJouee));
	else
		lignes.push_back("");

	//Ligne 4 : si les effets de la carte ont déja été subits
	if (_donneesJoueur.carteDejaSubie)
		lignes.push_back("Deja subi");
	else
		lignes.push_back("");

	//Ligne 5 : si un uno est déclaré
	if (_donneesJoueur.declareUno)
		lignes.push_back("Uno");
	else
		lignes.push_back("");

	//Ligne 6 : si un contre-uno est déclaré
	if (_donneesJoueur.joueurContreUno != -1)
		lignes.push_back(std::to_string(_donneesJoueur.joueurContreUno));
	else
		lignes.push_back("");

	//Ligne 7 : si fin tour ou abandon
	if (finManche == FinManche::manche_terminee)
		lignes.push_back("fin");
	else if (finManche == FinManche::manche_abandonnee)
		lignes.push_back("abandon");
	else
		lignes.push_back("");

	//Ligne 8 :
	string cartesTirees = "";
	for (int i = 0; i < _donneesJoueur.cartesPiochees->size(); i++)
	{
		cartesTirees += std::to_string(_donneesJoueur.cartesPiochees->operator[](i)) + " ";
	}
	lignes.push_back(cartesTirees);

	//Ligne 9 : si message à transmettre
	lignes.push_back(_donneesJoueur.message);

	//	On essaye d'écrire les lignes et on teste si il y a une erreur
	if (!_fichier->ecritureLignes(lignes)) {
		cout << "Erreur de transmission :(\n";
		return false;
	}
	cout << "Informations transmises !" << endl;

	return true;
}

bool CommJeu::declarerCarteJouee(int idCarte, bool carteDejaSubie)
{
	if (_donneesJoueur.carteJouee != -1)
	{
		return false;
	}
	_donneesJoueur.carteJouee = idCarte;
	_donneesJoueur.carteDejaSubie = carteDejaSubie;		//On stocke cet id sous forme de string car c'est plus pratique
	return true;
}
