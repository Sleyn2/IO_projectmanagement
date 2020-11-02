#include <vector>
#include "klasy.h"

QStringList Fun_projekty::pobierz_liste_projektow()
{
	Pobieranie_bazy pobierz;
	vector<Projekt>projekty;
	QStringList lista;
	// instancja jest nullptr i nie wiem czemu :(
	//string id = Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika();
	string id = "1";
	projekty = pobierz.pobierz_projekt("select * from projekt where Id_projektu in ( select Id_projektu from Przypisanie_do_projektow where Id_pracownika= "+ id +")");

	for (auto i = projekty.begin(); i != projekty.end(); ++i)
	{
		lista.append(QString::fromStdString(i->pobierz_nazwa()));
	}
	return lista;
}