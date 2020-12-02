#pragma once
#include <exception>
#include <string>

using namespace std;

class Erreur : public exception 
{
private :
	int m_numero;
	string m_phrase;
	int m_niveau;

public :
	Erreur(int numero = 0, string const& phrase = "", int niveau = 0)
		throw() :m_numero(numero), m_phrase(phrase), m_niveau(niveau) {};
	int getNiveau() const throw() { return m_niveau; };
	virtual const char* what() const throw() { return m_phrase.c_str(); };
	virtual ~Erreur() throw() {};
};