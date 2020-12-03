/*
 * DicoAnglaisFrancais.cpp
 *
 *  Created on: Dec 2, 2020
 *      Author: etudiant
 */

#include "DicoAnglaisFrancais.h"
#include "ContratException.h"
#include <sstream>

///////////////////////////////////////////////////////////////////////////////////
// SECTION VALIDATION INTERNE ET CONTRAT
//

// Valider une entrée: les deux mots doivent être non-vides

bool DicoAnglaisFrancais::valider(std::pair<const std::string, std::string> p){
	return !(p.first.empty() or p.second.empty());
}

// Valider le dictionnaire: toutes les clés et définitions sont non-vides

bool DicoAnglaisFrancais::valider() const {
	//std::multimap<std::string, std::string>::const_iterator iter;

	bool valide = true;
	for (std::multimap<std::string, std::string>::const_iterator iter = dictionnaire.begin(); valide and iter != dictionnaire.end(); iter++){
		if (! valider(*iter) ){
			valide = false;
		}
	}
    return valide;
}

// Vérifie la validité interne de la classe avec les macros de ContratException

void DicoAnglaisFrancais::verifieInvariant() const
{
	INVARIANT(valider());
}

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTEUR
//

// Par défaut, on construit un dictionnaire vide

DicoAnglaisFrancais::DicoAnglaisFrancais() : dictionnaire() {}

////////////////////////////////////////////////////////////////////////////////
// MÉTHODES
//

// Ajouter une définition

void DicoAnglaisFrancais::ajouter(const Entree& paire){
	PRECONDITION(valider(paire));
	dictionnaire.insert(paire);
	INVARIANTS();
}

void DicoAnglaisFrancais::ajouter(const std::string& mot, const std::string& traduction)
{
	Entree paire(mot, traduction);
	ajouter(paire);

}

// Consulter les définitions d'un mot

std::set<std::string> DicoAnglaisFrancais::consulter(const std::string& mot) const{

	bool valide = true;
    std::set<std::string> definitions;

	auto resultat = dictionnaire.equal_range(mot);

	if (resultat.first == resultat.second) throw MotNonTrouveException(mot);

	for (auto iter = resultat.first; valide and iter != resultat.second; ++iter)
	{
		valide = (definitions.insert(iter->second)).second;
	}

	POSTCONDITION(valide);
	return definitions;
}

// Affichage à la console

std::string DicoAnglaisFrancais::repr() const
{
	std::stringstream ss;

	for (auto iter = dictionnaire.begin(); iter != dictionnaire.end(); ++iter)
		ss << (*iter).first << ": " << (*iter).second << '\n';
	return ss.str();
}

std::ostream& operator << (std::ostream& os, const DicoAnglaisFrancais& dict){
	os << dict.repr();
	return os;
}

// Sauvegarde sur fichier

void DicoAnglaisFrancais::sauvegarder(std::ostream& os) const
{
	for (auto iter = dictionnaire.begin(); iter != dictionnaire.end(); iter++)
	{
		os << iter->first << '$' << iter->second << '\n';
	}
}

void DicoAnglaisFrancais::recuperer(std::istream& is)
{
	static std::size_t MAX_CHAR = 256;
	char tampon[MAX_CHAR];

	while (is.getline(tampon, MAX_CHAR, '$'))
	{
		std::string mot(tampon);
		is.getline(tampon, MAX_CHAR);
		std::string definition(tampon);
		ajouter(mot, definition);
	}
}

// Destructeur

DicoAnglaisFrancais::~DicoAnglaisFrancais(){}



