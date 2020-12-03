/*
 * \file testeurdictionnaire.cpp
 *
 * \version 0.1
 * \author Pascal Charpentier
 */

#include "gtest/gtest.h"
#include "DicoAnglaisFrancais.h"
#include "DicoAnglaisFrancaisException.h"
#include "ContratException.h"
#include <fstream>

/** Méthode testée: constructeur
 *
 * Cas testé: Par défaut
 *
 * Comportement attendu: créée un objet vide
 *
 */
TEST(DicoAnglaisFrancais, constructeur)
{
	DicoAnglaisFrancais d;
	EXPECT_EQ(d.repr(), "");
}

/**
 * Méthode testée: ajouter
 *
 * Cas testé: mot ou définition vide (cas non-valide)
 *
 * Comportement attendu: lance PreconditionException
 */

TEST(DicoAnglaisFrancais, ajouterPaireInvalide)
{
	DicoAnglaisFrancais d;
	EXPECT_THROW(d.ajouter(DicoAnglaisFrancais::Entree("", "non vide")), PreconditionException);
	EXPECT_THROW(d.ajouter(DicoAnglaisFrancais::Entree("non vide", "")), PreconditionException);
}

/**
 * Méthode testée: ajouter(pair)
 *
 * Cas testé: valide
 *
 * Comportement attendu: la paire est ajoutée au dictionnaire
 */
TEST(DicoAnglaisFrancais, ajouterPaireValide)
{
	DicoAnglaisFrancais d;
	EXPECT_NO_THROW(d.ajouter(DicoAnglaisFrancais::Entree("soleil", "sun")));
    EXPECT_EQ("soleil: sun\n", d.repr());
}

/**
 * Méthode testée: ajouter(string, string)
 *
 * Cas testé: valide
 *
 * Comportement attendu: la paire est ajoutée au dictionnaire
 */

TEST(DicoAnglaisFrancais, ajouterPaireValide2)
{
	DicoAnglaisFrancais d;
	EXPECT_NO_THROW(d.ajouter("soleil", "sun"));
	EXPECT_EQ("soleil: sun\n", d.repr());
}

/**
 * Dispositif de test, comprend un objet dictionnaire vide dans lequel on rajoute 6
 * paires mot-définition.  Deux de ces paires sont pour le même mot
 *
 */

class TestDicoAnglaisFrancais : public::testing::Test
{
public:

	TestDicoAnglaisFrancais() : dTest()
	{
	    dTest.ajouter("soleil", "sun");
	    dTest.ajouter("sourire", "smile");
	    dTest.ajouter("sourcil", "eyebrow");
	    dTest.ajouter("riz", "rice");
	    dTest.ajouter("est", "east");
	    dTest.ajouter("est", "is");
	}

	DicoAnglaisFrancais dTest;
};

/**
 * Méthode testée repr
 *
 * Cas testé: dispositif de test
 *
 * Comportement attendu: génère une chaîne de caractères affichable
 */
TEST_F(TestDicoAnglaisFrancais, affichage)
{
	EXPECT_EQ(dTest.repr(), "est: east\nest: is\nriz: rice\nsoleil: sun\nsourcil: eyebrow\nsourire: smile\n");
}

/**
 * Méthode testée: consulter
 *
 * Cas testé: dispositif de test, mot présent
 *
 * Comportement attendu: retourne un set contenant la ou les définitions du mot
 */

TEST_F(TestDicoAnglaisFrancais, consulterPresent)
{
	std::set<std::string>v1{"sun"};
	std::set<std::string>v2{"east", "is"};

	EXPECT_EQ(dTest.consulter("soleil"), v1);
	EXPECT_EQ(dTest.consulter("est"), v2);
}

/**
 * Méthode testée: consulter
 *
 * Cas testé: dispositif de test, mot absent du dictionnaire
 *
 * Comportement attendu: lance une exception MotNonTrouveException qui contient le mot manquant
 */
TEST_F(TestDicoAnglaisFrancais, consulterAbsent)
{
	EXPECT_THROW(dTest.consulter("papillon"), MotNonTrouveException);
}

/**
 * Méthode testée: sauvegarder et récupérer
 *
 * Cas testé: dispositif de test
 *
 * Comportement attendu: sauvegarde les données du dispositif dans un fichier.  Récupère ces données dans un autre objet.  Cet
 * autre objet est identique au premier.
 */

TEST_F(TestDicoAnglaisFrancais, sauvegarderEtRecuperer)
{
	std::ofstream fichier("sauvegarde.txt", std::ofstream::out);
	if (!fichier.is_open())
	{
		std::cerr << "Erreur à l'ouverture du fichier sauvegarde." << std::endl;
	}
	dTest.sauvegarder(fichier);
	fichier.close();
	std::ifstream fichier2("sauvegarde.txt", std::ifstream::in);
	if (!fichier2.is_open())
	{
		std::cerr << "Erreur à l'ouverture du fichier sauvegarde." << std::endl;
	}
	DicoAnglaisFrancais dictionnaireLu;
	dictionnaireLu.recuperer(fichier2);

	EXPECT_EQ(dTest.repr(), dictionnaireLu.repr());
}




