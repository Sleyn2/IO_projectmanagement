#include "klasy.h"
#include <fstream>

string Dane_polaczenia::dbname;
string Dane_polaczenia::user;
string Dane_polaczenia::password;
string Dane_polaczenia::hostaddr;
string Dane_polaczenia::port;


bool Dane_polaczenia::init()
{
	fstream file("database.conf");
	if (file.is_open()) {
		string buff;
		while (file >> buff) {
			if (buff == "dbname") {
				file >> buff;
				if (buff == "=") {
					file >> buff;
					dbname = buff;
				}
				else {
					return false;
				}
			}
			else if (buff == "user") {
				file >> buff;
				if (buff == "=") {
					file >> buff;
					user = buff;
				}
				else {
					return false;
				}
			}
			else if (buff == "password") {
				file >> buff;
				if (buff == "=") {
					file >> buff;
					password = buff;
				}
				else {
					return false;
				}
			}
			else if (buff == "hostaddr") {
				file >> buff;
				if (buff == "=") {
					file >> buff;
					hostaddr = buff;
				}
				else {
					return false;
				}
			}
			else if (buff == "port") {
				file >> buff;
				if (buff == "=") {
					file >> buff;
					port = buff;
				}
				else {
					return false;
				}
			}
		}
		file.close();
		// sprawdzenie czy wszystko jest wype³nione 
		if (dbname.empty())
			return false;
		if (user.empty())
			return false;
		if (password.empty())
			return false;
		if (hostaddr.empty())
			return false;
		if (port.empty())
			return false;

		return true;
	}
	else {
		// blad bazy cos sie moze stac :OOOO
		return false;
	}
}
string Dane_polaczenia::Conncet()
{
	return "dbname = " + dbname + " user = " + user + " password = " + password + " hostaddr = " + hostaddr + " port = " + port;
}


