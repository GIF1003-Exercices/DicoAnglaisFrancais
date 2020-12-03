/*
 * DicoAnglaisFrancaisException.h
 *
 *  Created on: Dec 3, 2020
 *      Author: etudiant
 */

#ifndef DICOANGLAISFRANCAISEXCEPTION_H_
#define DICOANGLAISFRANCAISEXCEPTION_H_

#include <stdexcept>

class DicoAnglaisFrancaisException : public std::runtime_error {
public:
	DicoAnglaisFrancaisException(std::string info) : std::runtime_error(info) {};
};

class MotNonTrouveException : DicoAnglaisFrancaisException {
private:
	std::string m_mot;
public:
	MotNonTrouveException(std::string mot) : DicoAnglaisFrancaisException(mot), m_mot(mot) {};
	std::string reqMot() const {return m_mot;} ;



};

#endif /* DICOANGLAISFRANCAISEXCEPTION_H_ */
