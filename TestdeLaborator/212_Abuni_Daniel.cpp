/* Abuni Daniel 212
GNU GCC
EDUARD GABRIEL SZMETEANCA */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Vaccin
{
private:
	float pret;
	float temp; //temperatura de depozitare
	vector <string> substante;
	int dim_subst;
public:
	float getPret(){return this->pret;}
	float getTemp(){return this->temp;}
	void afisareSubstante()
	{
		for(int i = 0; i < dim_subst; i++)
        {
            cout<<substante.at(i)<<endl;
        }
	}

	virtual void afisareSchemaVaccinare(){};
	friend istream &operator >> (istream &in, Vaccin &ob)
	{
		string aux;
		cout<<"Pret: ";
		in>>ob.pret;
		cout<<"Temperatura: ";
		in>>ob.temp;
		cout<<"Numarul substantelor: ";
		in>>ob.dim_subst;
		cout<<"Substantele: ";
		for(int i = 0; i < ob.dim_subst; i++)
        {
            cin>>aux;
            ob.substante.push_back(aux);
        }
	return in;
	}

	friend ostream &operator << (ostream &out, const Vaccin &ob)
	{
		out<<"Pretul este: "<<ob.pret<<"LEI temperatura de depozitare este de: "<<ob.temp<<" grade C, iar lista cu substantele care intra in compozitia acestuia sunt: ";
		for(int i = 0; i < ob.dim_subst; i++)
        {
            out<<ob.substante.at(i)<<endl;
        }
	return out;
	}

	~Vaccin(){};
};


class VaccinAntigripal:public Vaccin
{
private:
	string tulpini;
	bool respecta;
public:
	void afisareSchemaVaccinare()
	{
		cout<<"Pretul este: "<<getPret()<<"LEI temperatura de depozitare este de: "<<getTemp()<<" grade C, iar lista cu substantele care intra in compozitia acestuia sunt: ";
		afisareSubstante();
		if(respecta == 1)
			cout<<"Tulpina administrata este "<<tulpini<<" si respecta recomandarile date de Organizatia Mondiala a Sanatatii.";
		else
			cout<<"Tulpina administrata este "<<tulpini<<" si nu respecta recomandarile date de Organizatia Mondiala a Sanatatii.";
	}

	friend istream &operator >> (istream &in, VaccinAntigripal &ob)
	{
		in>>(Vaccin&) ob;
		cout<<"Tulpina administrata: ";
		in>>ob.tulpini;
		cout<<"Respecta recomandarile date de Organizatia Mondiala a Sanatatii (1 - DA || 0 - NU): ";
		in>>ob.respecta;
	return in;
	}

	friend ostream &operator << (ostream &out, const VaccinAntigripal &ob)
	{
		out<<(Vaccin&) ob;
		if(ob.respecta == 1)
			out<<"Tulpina administrata este "<<ob.tulpini<<" si respecta recomandarile date de Organizatia Mondiala a Sanatatii.";
		else
			out<<"Tulpina administrata este "<<ob.tulpini<<" si nu respecta recomandarile date de Organizatia Mondiala a Sanatatii.";
	return out;
	}
	~VaccinAntigripal(){};
};


class VaccinAntihepatic:public Vaccin
{
private:
	char tip_hepa;
	string mod_vac; //modul de vaccinare
public:
	void afisareSchemaVaccinare()
	{
		cout<<"Pretul este: "<<getPret()<<"LEI temperatura de depozitare este de: "<<getTemp()<<" grade C, iar lista cu substantele care intra in compozitia acestuia sunt: ";
		afisareSubstante();
		cout<<"Tipul hepatitei pentru care se administreaza este "<<tip_hepa<<" iar modul de vaccinare este "<<mod_vac;
	}
	friend istream &operator >> (istream &in, VaccinAntihepatic &ob)
	{
		in>>(Vaccin&) ob;
		cout<<"Tip hepatita: ";
		in>>ob.tip_hepa;
		cout<<"Mod vaccinare: ";
		in>> ob.mod_vac;
	return in;
	}

	friend ostream &operator << (ostream &out, const VaccinAntihepatic &ob)
	{
		out<<(Vaccin&) ob;
		out<<"Tipul hepatitei pentru care se administreaza este "<<ob.tip_hepa<<" iar modul de vaccinare este "<<ob.mod_vac;
	return out;
	}
	~VaccinAntihepatic(){};
};


class VaccinAntiSarsCov2:public Vaccin
{
private:
	vector <string> reactii_adv;
	float rata_efic;
	vector <string> medicamente;
public:
	void afisareSchemaVaccinare()
	{
		cout<<"Pretul este: "<<getPret()<<"LEI temperatura de depozitare este de: "<<getTemp()<<" grade C, iar lista cu substantele care intra in compozitia acestuia sunt: ";
		afisareSubstante();
		cout<<"Reactiile advesre sunt: ";
		for(int i = 0; i < reactii_adv.size(); i++)
        {
            cout<<reactii_adv.at(i)<<endl;
        }
        cout<<"Rata de eficienta este de "<<rata_efic<<"%. Medicamentele contraindicate folosirii pe o perioada de 6 luni sunt: ";
        for(int i = 0; i < medicamente.size(); i++)
        {
            cout<<medicamente.at(i)<<endl;
        }
	}
	friend istream &operator >> (istream &in, VaccinAntiSarsCov2 &ob)
	{
		in>>(Vaccin&) ob;
		string aux;
		int nr;
		cout<<"Numar reactii adverse: ";
		in>>nr;
		cout<<"Reactiile adverse (cu _ intre cuvinte): ";
		for(int i = 0; i < nr; i++)
        {
            cin>>aux;
            ob.reactii_adv.push_back(aux);
        }
        cout<<"Rata de eficienta: ";
        in>>ob.rata_efic;
        cout<<"Numar medicamente: ";
        in>>nr;
        cout<<"Medicamente (cu _ intre cuvinte): ";
        for(int i = 0; i < nr; i++)
        {
            cin>>aux;
            ob.medicamente.push_back(aux);
        }
	return in;
	}

	friend ostream &operator << (ostream &out, const VaccinAntiSarsCov2 &ob)
	{
		out<<(Vaccin&) ob;
		out<<"Reactiile advesre sunt: ";
		for(int i = 0; i < ob.reactii_adv.size(); i++)
        {
            out<<ob.reactii_adv.at(i)<<endl;
        }
        out<<"Rata de eficienta este de "<<ob.rata_efic<<"%. Medicamentele contraindicate folosirii pe o perioada de 6 luni sunt: ";
        for(int i = 0; i < ob.medicamente.size(); i++)
        {
            out<<ob.medicamente.at(i)<<endl;
        }
	return out;
	}
	~VaccinAntiSarsCov2(){};
};


class Comanda
{
private:
	int id;
	string dataa;
	string nume_client;
	string nume_vaccin;
	int cantitate;
public:
    string getDataa(){return this->dataa;}
	string getNumeClient(){return this->nume_client;}
	string getNumeVaccin(){return this->nume_vaccin;}
	int getCantitate(){return this->cantitate;}
	Comanda(string dataa, string nume_client, string nume_vaccin, int cantitate)
	{
		this->dataa = dataa;
		this->nume_client = nume_client;
		this->nume_vaccin = nume_vaccin;
		this->cantitate = cantitate;
	}
	~Comanda(){};
};

class ListaComenzi:public Comanda
{
private:
    vector <Comanda> vector_comenzi;
private:
	friend ostream &operator << (ostream &out, const ListaComenzi &ob)
	{
		out<<"Pe data de "<<ob.getDataa()<<" spitalul "<<ob.getNumeClient()<<" a primit "<<ob.getNumeVaccin()<<" in cantitate de "<<ob.getCantitate();
	return out;
	}

    ~ListaComenzi(){};
};
int main()
{
/*
    VaccinAntigripal a;
	VaccinAntihepatic b;
	VaccinAntiSarsCov2 c;
	//cin>>a;
	//cout<<a;
	//cin>>b;
	//cout<<b;
	//cin>>c;
	//cout<<c;
*/
/*
	Vaccin* lista[3];
	lista[0]=new VaccinAntigripal();
	cin>>(VaccinAntigripal&) *lista[0];
	lista[1]=new VaccinAntihepatic ();
	cin>>(VaccinAntihepatic&) *lista[1];
	lista[2]=new VaccinAntiSarsCov2();
	cin>>(VaccinAntiSarsCov2&) *lista[2];
	for(int i=0; i<3; i++)
        lista[i]->afisareSchemaVaccinare();
*/
/*
    Comanda com1("20-12-2020", "SpitalX", "AntiSarsCov2", 20);
    ListaComenzi listaa;
    cout<<listaa;
*/
	return 0;
}
