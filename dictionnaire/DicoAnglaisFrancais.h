/*
 * DicoAnglaisFrancais.h
 *
 *  Created on: Dec 2, 2020
 *      Author: etudiant
 */

#ifndef DICOANGLAISFRANCAIS_H_
#define DICOANGLAISFRANCAIS_H_

#include <iostream>
#include <map>
#include <set>
#include <string>
#include "DicoAnglaisFrancaisException.h"


class DicoAnglaisFrancais {
public:

	// Types membres

	typedef std::pair<const std::string, std::string> Entree;

	// Fonctions de validation

	bool static valider(std::pair<const std::string, std::string> p);
	bool valider() const;

	// Constructeur par défaut: dico vide

	DicoAnglaisFrancais();

	// Ajouter une définition

	void ajouter(const Entree&);
	void ajouter(const std::string& mot, const std::string& traduction);

	// Consulter les définitions d'un mot

	std::set<std::string> consulter(const std::string& mot) const;

	// Affichage à la console

	std::string repr() const;
	friend std::ostream& operator << (std::ostream&, const DicoAnglaisFrancais&);

	// Sauvegarde

	void sauvegarder(std::ostream&) const;
	void recuperer(std::istream&);

	// Destructeur

	virtual ~DicoAnglaisFrancais();

private:
	std::multimap<std::string, std::string> dictionnaire;
	void verifieInvariant() const;
};

#endif /* DICOANGLAISFRANCAIS_H_ */
