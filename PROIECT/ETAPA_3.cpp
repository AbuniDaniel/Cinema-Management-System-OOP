#include <iostream>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unistd.h>

using namespace std;

class Cinema
{
private:
    const char nume_cinema[20] = "City Cinema";
    bool deschis;
    float lei_sapt; // lei incasati intr-o saptamana
    float* lei_zi; // lei incasati in fiecare zi
    char initiala_ceo;
    char prenume_ceo[20];

public:
    const char* getNumeCinema(){return this->nume_cinema;}

    void setDeschis(bool deschis){this->deschis = deschis;}
    bool getDeschis(){return this->deschis;}

    void setLeisapt(float lei_sapt){this->lei_sapt = lei_sapt;}
    float getLeisapt(){return this->lei_sapt;}

    void setLeizi(float* a)
    {
        if(this->lei_zi!=nullptr)
            delete[] this->lei_zi;
        this->lei_zi = new float[7];
        for(int i = 0; i < 7; i++)
            this->lei_zi[i] = a[i];
    }
    float* getLeizi(){return this->lei_zi;}

    void setInitialaCeo(char initiala_ceo){this->initiala_ceo = initiala_ceo;}
    char getInitialaCeo(){return this->initiala_ceo;}

    void setPrenumeCeo(char prenume_ceo[20]){strcpy(this->prenume_ceo,prenume_ceo);}
    char* getPrenumeCeo(){return this->prenume_ceo;}

    // functia de afisare
    void afisare()
    {
        if(deschis == 0)
            cout<<"Bun venit la "<<this->nume_cinema<<", momentan este INCHIS."<< endl;

        else
            cout<<"Bun venit la "<<this->nume_cinema<<", momentan este DESCHIS. Acest cinema este detinut de catre "<<initiala_ceo<<". "<< prenume_ceo<<". Saptamana trecuta s-au incasat: "<<lei_sapt<<"LEI."<<endl;
    }

    // constructor fara parametrii
    Cinema():nume_cinema("City Cinema")
    {
        this->deschis = 0;
        this->lei_sapt = 0;
        this->initiala_ceo = '-';
        strcpy(this->prenume_ceo,"-");
    }

    // constructor cu parametrii
    Cinema(bool deschis, float lei_sapt, char initiala_ceo, char prenume_ceo[]):nume_cinema("City Cinema")
    {
        this->deschis = deschis;
        this->lei_sapt = lei_sapt;
        this->initiala_ceo = initiala_ceo;
        strcpy(this->prenume_ceo,prenume_ceo);
    }

    // constructorul nr 2
    Cinema(bool deschis, float lei_sapt):nume_cinema("City Cinema")
    {
        this->deschis = deschis;
        this->lei_sapt = lei_sapt;
        initiala_ceo = '-';
        strcpy(this->prenume_ceo,"-");
    }

    // copy constructor
    Cinema(const Cinema &ob):nume_cinema("City Cinema")
    {
        this->deschis = ob.deschis;
        this->lei_sapt = ob.lei_sapt;
        this->initiala_ceo = ob.initiala_ceo;
        strcpy(this->prenume_ceo,ob.prenume_ceo);
    }

    // operatorul =
    Cinema &operator=(const Cinema &ob)
    {
        if(this != &ob)
        {

            this->deschis = ob.deschis;
            this->lei_sapt = ob.lei_sapt;
            this->initiala_ceo = ob.initiala_ceo;
            strcpy(this->prenume_ceo,ob.prenume_ceo);
        }
        return *this;
    }
    // operatorul de citire
    friend istream &operator >> (istream &in, Cinema &ob)
    {
        float lei_ramasi;
        cout<<"Scrieti daca este deschis (0 - inchis | 1 - deschis): ";
        in>>ob.deschis;
        if(ob.deschis == 0)
        {
            cout<<"CINEMA-UL ESTE INCHIS!!!";
            exit (0);
        }
        cout<<"Scrieti initiala CEO-ului (ex. 'A'): ";
        in>>ob.initiala_ceo;
        cout<<"Scrieti prenumele CEO-ului (ex. 'Daniel'): ";
        in>>ob.prenume_ceo;
        cout<<"Scrieti cati lei s-au incasat saptamana trecuta: ";
        in>>ob.lei_sapt;
        lei_ramasi = ob.lei_sapt;
        ob.lei_zi = new float[7];
        for(int i = 0; i < 7; i++)
        {
            if(i == 0){cout<<"Au mai ramas de imparit "<<lei_ramasi<<"LEI, cat s-a incasat Luni: "; in>>ob.lei_zi[i]; lei_ramasi-=ob.lei_zi[i];}
            else if(i == 1){cout<<"Au mai ramas de imparit "<<lei_ramasi<<"LEI, cat s-a incasat Marti: "; in>>ob.lei_zi[i]; lei_ramasi-=ob.lei_zi[i];}
            else if(i == 2){cout<<"Au mai ramas de imparit "<<lei_ramasi<<"LEI, cat s-a incasat Miercuri: "; in>>ob.lei_zi[i]; lei_ramasi-=ob.lei_zi[i];}
            else if(i == 3){cout<<"Au mai ramas de imparit "<<lei_ramasi<<"LEI, cat s-a incasat Joi: "; in>>ob.lei_zi[i]; lei_ramasi-=ob.lei_zi[i];}
            else if(i == 4){cout<<"Au mai ramas de imparit "<<lei_ramasi<<"LEI, cat s-a incasat Vineri: "; in>>ob.lei_zi[i]; lei_ramasi-=ob.lei_zi[i];}
            else if(i == 5){cout<<"Au mai ramas de imparit "<<lei_ramasi<<"LEI, cat s-a incasat Sambata: "; in>>ob.lei_zi[i]; lei_ramasi-=ob.lei_zi[i];}
            else{cout<<"Duminica s-au incasat: "<<lei_ramasi<<endl<<endl; ob.lei_zi[i]=lei_ramasi;}
        }
    return in;
    }

    // operatorul de afisare
    friend ostream &operator << (ostream &out, const Cinema &ob)
    {
        float mini = ob.lei_zi[0], maxi = ob.lei_zi[0];
        for(int i = 0; i < 7; i++)
        {
            if(ob.lei_zi[i] < mini)
            mini=ob.lei_zi[i];
            if(ob.lei_zi[i] > maxi)
            maxi=ob.lei_zi[i];
        }
        out<<"Cei mai putini LEI incasati sunt: "<<mini<<"LEI"<<endl;
        out<<"Cei mai mult LEI incasati sunt: "<<maxi<<"LEI"<<endl;
        out<<"In medie s-au incasat zilnic: "<<ob.lei_sapt/7<<"LEI"<<endl;
    return out;
    }

    // destructor
    ~Cinema()
    {
        if(this->lei_zi != nullptr)
            delete[] this->lei_zi;
        //cout<<"Hatz, am distrus cinema-ul!"<<endl;
    }


};

class Bilete
{
private:
    const int cod_bare;
    char sala;
    int bilete_vandute;
    float lei_incasati;
    bool bilet_disp;
    int nr_bilet_disp;
    char* nume_film;
    float pret_bilet;
    static int sub_16;

public:

    int getCodBare(){return this->cod_bare;}

    void setSala(char sala){this-> sala = sala;}
    char getSala(){return this->sala;}

    void setBileteVandute(int bilete_vandute){this-> bilete_vandute = bilete_vandute;}
    int getBileteVandute(){return this->bilete_vandute;}

    void setLeiIncasati(float lei_incasati){this-> lei_incasati = lei_incasati;}
    float getLeiIncasati(){return this->lei_incasati;}

    void setBiletDisp(bool bilet_disp){this-> bilet_disp = bilet_disp;}
    bool getBileteDisp(){return this->bilet_disp;}

    void setNrBiletDisp(int nr_bilet_disp){this-> nr_bilet_disp = nr_bilet_disp;}
    int getNrBiletDisp(){return this->nr_bilet_disp;}

    void setNumeFilm(char* nume_film)
    {
        if(this->nume_film != nullptr)
            delete[] this->nume_film;
        this->nume_film = new char[strlen(nume_film)+1];
        strcpy(this->nume_film, nume_film);
    }
    char* getNumeFilm(){return this->nume_film;}

    void setPretBilet(float pret_bilet){this-> pret_bilet = pret_bilet;}
    float getPretBilet(){return this->pret_bilet;}

    // functia de afisare
    void afisare()
    {
        if(bilet_disp == 1)
            cout<<"S-au vandut "<<bilete_vandute<<" bilete, s-au incasat "<<lei_incasati<<"lei."<<" Sala: "<<sala<<", mai sunt bilete disponibile bilete, in numar de: "<<nr_bilet_disp<<", nume film: '"<<nume_film<<"', pret bilet: "<<pret_bilet<<"LEI."<<endl;
        else
            cout<<"S-au vandut "<<bilete_vandute<<" bilete, s-au incasat "<<lei_incasati<<"lei."<<" Sala: "<<sala<<", nu mai sunt disponibile bilete, nume film: '"<<nume_film<<"', pret bilet: "<<pret_bilet<<"LEI."<<endl;
    }

    // constructor fara parametrii
    Bilete():cod_bare(0000)
    {
        this->sala = '-';
        this->bilete_vandute = 0;
        this->lei_incasati = 0;
        this->bilet_disp = 0;
        this->nr_bilet_disp = 0;
        this->nume_film = new char[strlen("-") + 1];
        strcpy(this->nume_film,"-");
        this->pret_bilet = 0;
        this->sub_16 = 0;
    }

    // constructor cu parametrii
    Bilete(int id, char sala, int bilete_vandute, float lei_incasati, bool bilet_disp, int nr_bilet_disp, char* nume_film, float pret_bilet):cod_bare(id)
    {
        this->sala = sala;
        this->bilete_vandute = bilete_vandute;
        this->lei_incasati = lei_incasati;
        this->bilet_disp = bilet_disp;
        this->nr_bilet_disp = nr_bilet_disp;
        this->nume_film = new char[strlen(nume_film)+1];
        strcpy(this->nume_film, nume_film);
        this->pret_bilet = pret_bilet;
    }

    // constructorul nr 2
    Bilete(int id, bool bilet_disp, char* nume_film, float pret_bilet):cod_bare(id)
    {
        this->sala = '-';
        bilete_vandute = 0;
        lei_incasati = 0;
        this->bilet_disp = bilet_disp;
        nr_bilet_disp = 0;
        this->nume_film = new char[strlen(nume_film)+1];
        strcpy(this->nume_film, nume_film);
        this->pret_bilet = pret_bilet;
    }

    // copy constructor
    Bilete(const Bilete &ob):cod_bare(ob.cod_bare)
    {
        this->sala = ob.sala;
        this->bilete_vandute = ob.bilete_vandute;
        this->lei_incasati = ob.lei_incasati;
        this->bilet_disp = ob.bilet_disp;
        this->nr_bilet_disp = ob.nr_bilet_disp;
        this->nume_film = new char[strlen(ob.nume_film)+1];
        strcpy(this->nume_film, ob.nume_film);
        this->pret_bilet = ob.pret_bilet;

    }

    // operatorul =
    Bilete &operator=(const Bilete &ob)
    {
        if(this != &ob)
        {
            this->sala = ob.sala;
            this->bilete_vandute = ob.bilete_vandute;
            this->lei_incasati = ob.lei_incasati;
            this->bilet_disp = ob.bilet_disp;
            this->nr_bilet_disp = ob.nr_bilet_disp;
            this->nume_film = new char[strlen(ob.nume_film)+1];
            strcpy(this->nume_film, ob.nume_film);
            this->pret_bilet = ob.pret_bilet;
        }
        return *this;
    }

    // operatorul de citire + try & catch
    friend istream &operator >> (istream &in, Bilete &ob)
    {
        int check = 0;
        while(check == 0)
        {
            char copie[50];
            cout<<"Scrieti numele filmului (CU '_' INTRE CUVINTE): ";
            //in.getline(copie,sizeof(copie));
            in>>copie;
            if(ob.nume_film != nullptr)
                delete[] ob.nume_film;
            ob.nume_film = new char[strlen(copie)+1];
            strcpy(ob.nume_film, copie);
            cout<<"Mai sunt bilete disponibile? (0 - nu | 1 - da): ";
            in>>ob.bilet_disp;
            if(ob.bilet_disp == 1)
                check = 1;
            else
            {
                check = 0;
                cout<<":( Nu mai sunt bilete disponibile pentru filmul: '"<<ob.nume_film<<"' o sa treabuiasca sa alegeti alt film."<<endl;
            }
        }
        cout<<"Sala in care se deruleaza filmul: (ex. 'A', 'a', 'B', 'b' etc.): ";
        in>>ob.sala;
        ob.sala = toupper(ob.sala);
        try
        {
            if (isalpha(ob.sala))
            {
                cout<<"Numar bilete disponibile: ";
                in>>ob.nr_bilet_disp;
                cout<<"Pretul biletului: ";
                in>>ob.pret_bilet;
                cout<<"Numar bilete vandute: ";
                in>>ob.bilete_vandute;
                cout<<"Cate persoane sunt sub 16 ani (acestea primesc o reducere de 15%): ";
                in>>ob.sub_16;
                cout<<endl;
                ob.lei_incasati = ob.pret_bilet * ob.bilete_vandute;
                while(ob.nr_bilet_disp < ob.bilete_vandute)
                {
                    cout<<"EROARE!! Numarul biletelor vandute este mai mare decat numarul biletelor disponibile"<<endl;
                    cout<<"Deci, cate bilete s-au vandut?: "<<endl;
                    in>>ob.bilete_vandute;
                }
            }
            else
            {
                throw ob.sala;
            }
        }
        catch(char a)
        {
            cout<<endl;
            cout<<"EROARE! Sala '"<<a<<"' este invalida.";
            cout<<endl<<endl;
        }

    return in;
    }

    // operatorul de afisare
    friend ostream &operator << (ostream &out, const Bilete &ob)
    {
        if(isalpha(ob.sala))
        {
            out<<"Pentru filmul '"<<ob.nume_film<<"' care se deruleaza in sala "<<ob.sala<<" s-au vandut "<<ob.bilete_vandute<<" de bilete, mai sunt disponibile "<<ob.nr_bilet_disp - ob.bilete_vandute<<" de bilete la pretul de "<<ob.pret_bilet<<"LEI. "<<endl;
            if(ob.sub_16 > 0)
                out<<"Din nefericire au venit "<<ob.sub_16<<" persoane sub 16 ani (care au 15% reducere), deci Cinema-ul a iesit in 'pierdere' cu "<<ob.sub_16 * (ob.pret_bilet * 15/100)<<"LEI din cauza acestei promotii."<<endl;
            else
                out<<"Deoarece nu a venit nici o persoana sub 16 ani, Cinema-ul nu a fost nevoit sa ofere nici o reducere :D. S-au incasat "<<ob.lei_incasati<<"LEI."<<endl;
        }
        else
        {
            cout<<"Nu am nimic de afisat deoarece sala '"<<ob.sala<<"' este invalida.";
        }
    return out;
    }

    // citirea din fisier
    friend ifstream &operator >> (ifstream &in, Bilete &ob)
    {
        in>>ob.bilete_vandute;
        in>>ob.lei_incasati;
        in>>ob.sala;
        in>>ob.bilet_disp;
        in>>ob.nr_bilet_disp;
        char copie[50];
        in>>copie;
        if(ob.nume_film != nullptr)
            delete[] ob.nume_film;
        ob.nume_film = new char[strlen(copie)+1];
        strcpy(ob.nume_film, copie);
        in>>ob.pret_bilet;
    return in;
    }

    // afisarea in fisier
    friend ofstream &operator << (ofstream &out, const Bilete &ob)
    {
        if(ob.bilet_disp == 1)
            out<<"S-au vandut "<<ob.bilete_vandute<<" bilete, s-au incasat "<<ob.lei_incasati<<"lei."<<" Sala: "<<ob.sala<<", mai sunt bilete disponibile bilete, in numar de: "<<ob.nr_bilet_disp<<", nume film: '"<<ob.nume_film<<"', pret bilet: "<<ob.pret_bilet<<"LEI."<<endl;
        else
            out<<"S-au vandut "<<ob.bilete_vandute<<" bilete, s-au incasat "<<ob.lei_incasati<<"lei."<<" Sala: "<<ob.sala<<", nu mai sunt disponibile bilete, nume film: '"<<ob.nume_film<<"', pret bilet: "<<ob.pret_bilet<<"LEI."<<endl;
    return out;
    }

    // functia de citire (pentru meniu)
    void citire_meniu()
    {
       cout<<"Sala (ex. 'A', 'a', 'B', 'b' etc.): ";
       cin>>sala;
       sala = toupper(sala);
       cout<<"Numele film (CU '_' INTRE CUVINTE): ";
       cin>>nume_film;
       cout<<"Bilete vandute: ";
       cin>>bilete_vandute;
       cout<<"Pret bilet: ";
       cin>>pret_bilet;
    }
    // functia de afisare (pentru meniu)
    void afisare_meniu()
    {

        cout<<"In sala "<<sala<<" se deruleaza filmul "<<nume_film<<". S-au vandut "<<bilete_vandute<<" de bilete la pretul de "<<pret_bilet<<"LEI."<<endl;
    }
    // operatorul de indexare
    char operator [](int i)
    {
        if ((i < strlen(nume_film)) && i > 0)
            return this->nume_film[i];
        else
        {
            cout << "index invalid.";
            return -1;
        }
    }

    // operatorul ++ pre
    const Bilete operator++()
    {
        this->lei_incasati++;
        return *this;
    }

    // operatorul ++ post
    const Bilete operator++(int)
    {
        this->lei_incasati++;
        return *this;
    }

    // operatorul +
    Bilete operator+(int a)
    {
        this->lei_incasati += a;
        return *this;
    }

    // operatorul *
    Bilete operator*(int a)
    {
        this->lei_incasati *= a;
        return *this;
    }

    // operatorul cast explicit
    explicit operator int()
    {
        return (int)this->lei_incasati;
    }

    // operatorul conditional <
    bool operator<(Bilete &ob)
    {
        return this->lei_incasati < ob.lei_incasati;
    }

    // operatorul conditional ==
    bool operator==(Bilete &ob)
    {
        return this->lei_incasati == ob.lei_incasati;
    }

    // destructor
    ~Bilete()
    {
        if(this->nume_film != nullptr)
            delete[] this->nume_film;
        //cout<<"Am distrus biletele"<<endl;
    }

};
int Bilete::sub_16 = 0;

class Bar
{
private:
    const int cod_bare_bar;
    int suc_vandut;
    int pop_vandut;
    char* nume_suc;
    bool stoc;
    float lei_incasati_bar;
    int meniu_vandut_s;
    int meniu_vandut_l;
    float pret_suc;
    float pret_pop;

public:
    virtual float pretMarfaActuala(){};

    const int getCodBareBar(){return this->cod_bare_bar;}

    void setSucVandut(int suc_vandut){this-> suc_vandut = suc_vandut;}
    int getSucVandut(){return this->suc_vandut;}

    void setPopVandut(int pop_vandut){this-> pop_vandut = pop_vandut;}
    int getPopVandut(){return this->pop_vandut;}

    void setNumeSuc(char* nume_suc)
    {
        if(this->nume_suc != nullptr)
            delete[] this->nume_suc;
        this->nume_suc = new char[strlen(nume_suc)+1];
        strcpy(this->nume_suc, nume_suc);
    }
    char* getNumeSuc(){return this->nume_suc;}

    void setStoc(bool stoc){this-> stoc = stoc;}
    bool getStoc(){return this->stoc;}

    void setLeiIncasatiBar(float lei_incasati_bar){this-> lei_incasati_bar = lei_incasati_bar;}
    float getLeiIncasatiBar(){return this->lei_incasati_bar;}

    void setMeniuVandutS(int meniu_vandut_s){this-> meniu_vandut_s = meniu_vandut_s;}
    int getMeniuVandutS(){return this->meniu_vandut_s;}

    void setMeniuVandutL(int meniu_vandut_l){this-> meniu_vandut_l = meniu_vandut_l;}
    int getMeniuVandutL(){return this->meniu_vandut_l;}

    void setPretSuc(float pret_suc){this-> pret_suc = pret_suc;}
    float getPretSuc(){return this->pret_suc;}

    void setPretPop(float pret_pop){this-> pret_pop = pret_pop;}
    float getPretPop(){return this->pret_pop;}

    // functia de afisare
    void afisare()
    {
        if(stoc == 1)
            cout<<"Sucul: "<<nume_suc<<" este in stoc. Suc vandut: "<<suc_vandut<<", pret suc: "<<pret_suc<<", popcorn vandut: "<<pop_vandut<<", pret popcorn: "<<pret_pop<<", lei incasati: "<<(pret_pop * pop_vandut) + (pret_suc * suc_vandut)<<"LEI."<<endl;
        else
            cout<<"Sucul: "<<nume_suc<<" nu mai este in stoc. Suc vandut: "<<suc_vandut<<", pret suc: "<<pret_suc<<", popcorn vandut: "<<pop_vandut<<", pret popcorn: "<<pret_pop<<", lei incasati: "<<(pret_pop * pop_vandut) + (pret_suc * suc_vandut)<<"LEI."<<endl;
    }

    // constructor fara parametrii
    Bar():cod_bare_bar(0000)
    {
        this->suc_vandut = 0;
        this->pop_vandut = 0;
        this->nume_suc = new char[strlen("-") + 1];
        strcpy(this->nume_suc,"-");
        this->stoc = 0;
        this->pret_suc = 0;
        this->pret_pop = 0;
    }

    // constructorul cu parametrii
    Bar(int id, int suc_vandut, int pop_vandut, char* nume_suc, bool stoc, float pret_suc, float pret_pop):cod_bare_bar(id)
    {
        this-> suc_vandut = suc_vandut;
        this-> pop_vandut = pop_vandut;
        this->nume_suc = new char[strlen(nume_suc)+1];
        strcpy(this->nume_suc, nume_suc);
        this->stoc = stoc;
        this->pret_suc = pret_suc;
        this->pret_pop = pret_pop;
    }

    // constructorul nr 2
    Bar(int id, int suc_vandut, char* nume_suc, float pret_suc):cod_bare_bar(id)
    {
        this->suc_vandut = suc_vandut;
        pop_vandut = 0;
        this->nume_suc = new char[strlen(nume_suc)+1];
        strcpy(this->nume_suc, nume_suc);
        stoc = 0;
        this->pret_suc = pret_suc;
        pret_pop = 0;
    }

    // copy constructor
    Bar(const Bar &ob):cod_bare_bar(ob.cod_bare_bar)
    {
        this->suc_vandut = ob.suc_vandut;
        this->pop_vandut = ob.pop_vandut;
        this->nume_suc = new char[strlen(ob.nume_suc)+1];
        strcpy(this->nume_suc, ob.nume_suc);
        this->stoc = ob.stoc;
        this->pret_suc = ob.pret_suc;
        this->pret_pop = ob.pret_pop;
    }

    // operatorul =
    Bar &operator=(const Bar &ob)
    {
        if(this != &ob)
        {
            this->suc_vandut = ob.suc_vandut;
            this->pop_vandut = ob.pop_vandut;
            this->nume_suc = new char[strlen(ob.nume_suc)+1];
            strcpy(this->nume_suc, ob.nume_suc);
            this->stoc = ob.stoc;
            this->pret_suc = ob.pret_suc;
            this->pret_pop = ob.pret_pop;
        }
        return *this;
    }

    // operatorul de citire
    friend istream &operator >> (istream &in, Bar &ob)
    {
        int check = 0;
        while(check == 0)
        {
            char copie[50];
            cout<<"Scrieti numele sucului (ex. 'Fanta', 'Sprite'): ";
            in>>copie;
            if(ob.nume_suc != nullptr)
                delete[] ob.nume_suc;
            ob.nume_suc = new char[strlen(copie)+1];
            strcpy(ob.nume_suc, copie);
            cout<<"Mai este in stoc? (0 - nu | 1 - da): ";
            in>>ob.stoc;
            if(ob.stoc == 1)
                check = 1;
            else
            {
                check = 0;
                cout<<":( Sucul '"<<ob.nume_suc<<"' nu mai este in stoc, va trebui sa alegeti alt suc."<<endl;
            }
        }
        cout<<"Pretul sucului '"<<ob.nume_suc<<"': ";
        in>>ob.pret_suc;
        cout<<"Numar suc '"<<ob.nume_suc<<"' vandut: ";
        in>>ob.suc_vandut;

        cout<<"Pretul popcornului: ";
        in>>ob.pret_pop;
        cout<<"Numar popcorn vandut: ";
        in>>ob.pop_vandut;

        cout<<"Acestea sunt promotiie ('S' - 1 popcorn + 1 suc => 15% reducere || 'L' - 2 popcorn + 2 suc => 1 popcorn gratis) "<<endl;
        cout<<"Cate meniuri de tipul 'S' s-au vandut: ";
        in>>ob.meniu_vandut_s;
        cout<<"Cate meniuri de tipul 'L' s-au vandut: ";
        in>>ob.meniu_vandut_l;
        cout<<endl;

        ob.lei_incasati_bar = (ob.pret_suc * ob.suc_vandut) + (ob.pret_pop * ob.pop_vandut);

    return in;
    }

    // operatorul de afisare
    friend ostream &operator << (ostream &out, const Bar &ob)
    {
        float dupa_promotie = ob.lei_incasati_bar - ((ob.pret_pop + ob.pret_suc) * ob.meniu_vandut_s) * 15/100;
        out<<"S-au vandut "<<ob.suc_vandut<<" de sucuri '"<<ob.nume_suc<<"'."<<endl;
        out<<"S-au vandut "<<ob.pop_vandut<<" pungi de popcorn."<<endl;
        out<<"S-au incasat "<<ob.lei_incasati_bar<<"LEI (fara calculul promotiilor)"<<endl;
        out<<"Dar din cauza meniului 'S' s-au incasat "<<dupa_promotie<<"LEI. (cu "<<ob.lei_incasati_bar - dupa_promotie<<"LEI mai putin)"<<endl;
        out<<"Iar din cauza meniului 'L' s-au oferit gratis "<<ob.meniu_vandut_l<<" pungi de popcorn, echivalentul a "<<ob.pret_pop * ob.meniu_vandut_l<<"LEI."<<endl;

    return out;
    }

    ~Bar()
    {
        if(this->nume_suc != nullptr)
            delete[] this->nume_suc;
        //cout<<"S-a dus barul"<<endl;
    }

};

class Angajati
{
private:
    char* nume;
    char prenume[30];
    char genul;
    const int CNP;
    int varsta;
    float salariu;
    bool lucreaza;
    int* ore_lucrate;
    static int nr_angajati;

public:
    void setNume(char* nume)
    {
        if(this->nume != nullptr)
            delete[] this->nume;
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume, nume);
    }
    char* getNume(){return this->nume;}

    void setPrenume(char prenume[30]){strcpy(this->prenume,prenume);}
    char* getPrenume(){return this->prenume;}

    void setGenul(char genul){this->genul = genul;}
    char getGenul(){return this->genul;}

    const int getCnp(){return this->CNP;}

    void setVarsta(int varsta){this->varsta = varsta;}
    int getVarsta(){return this->varsta;}

    void setSalariu(float salariu){this->salariu = salariu;}
    float getSalariu(){return this->salariu;}

    void setDeschis(bool lucreaza){this->lucreaza = lucreaza;}
    bool getDeschis(){return this->lucreaza;}

    void setOreLucrate(int* a)
    {
        if(this->ore_lucrate!=nullptr)
            delete[] this->ore_lucrate;
        this->ore_lucrate = new int[4];
        for(int i = 0; i < 4; i++)
            this->ore_lucrate[i]=a[i];
    }
    int* getOreLucrate(){return this->ore_lucrate;}

    // functia de afisare
    void afisare()
    {
        int ore = 0;
        for(int i = 0; i < 4; i++)
            ore += this->ore_lucrate[i];
        genul = toupper(genul);
        if(lucreaza == 0)
            cout<<"Angajatul "<<nume<<" "<<prenume<<" nu lucreaza in acest moment si are: varsta de "<<varsta<<" ani, genul "<<genul<<", salariu de "<<salariu<<"LEI pe luna, ore lucare "<<ore<<" in ultima luna."<<endl;
        else
            cout<<"Angajatul "<<nume<<" "<<prenume<<" lucreaza in acest moment si are: varsta de "<<varsta<<" ani, genul "<<genul<<", salariu de "<<salariu<<"LEI pe luna, ore lucare "<<ore<<" in ultima luna."<<endl;
    }

    // funtia de citire (am facut asta deoarece in operatiorul de citire citesc o gramada de chestii pt functionalitate)
    void citire()
    {
        char copie[30];
        cout<<"Numele angajatului: ";
        cin>>copie;
        if(nume != nullptr)
                delete[] nume;
        nume = new char[strlen(copie)+1];
        strcpy(nume, copie);
        cout<<"Prenumele angajatului: ";
        cin>>prenume;
        cout<<"Varsta angajatului: ";
        cin>>varsta;
        cout<<"Salariul angajatului: ";
        cin>>salariu;
        cout<<endl;
    }

    // constructor fara parametrii
    Angajati():CNP(0000000000000)
    {
        this->nume = new char[strlen("-") + 1];
        strcpy(this->nume, "-");
        strcpy(this->prenume, "-");
        this->genul = '-';
        this->varsta = 0;
        this->salariu = 0;
        this->lucreaza = 0;
        this->ore_lucrate = new int[4];
        for (int i = 0; i < 4; i++)
            this->ore_lucrate[i] = 0;
        this->nr_angajati = 0;
    }

    // constructor cu parametrii
    Angajati(char* nume, char prenume[30], char genul, int varsta, float salariu, bool lucreaza, int* ore_lucrate):CNP(1931225421271)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        strcpy(this->prenume, prenume);
        this->genul = genul;
        this->varsta = varsta;
        this->salariu = salariu;
        this->lucreaza = lucreaza;
        this->ore_lucrate = new int[4];
        for (int i = 0; i < 4; i++)
            this->ore_lucrate[i] = ore_lucrate[i];
        this->nr_angajati = nr_angajati;
    }

    // constructorul nr 2
    Angajati(char* nume, char prenume[30], char genul, int varsta, bool lucreaza):CNP(1931225421271)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        strcpy(this->prenume, prenume);
        this->genul = genul;
        this->varsta = varsta;
        this->salariu = 0;
        this->lucreaza = lucreaza;
        this->ore_lucrate = new int[4];
        for (int i = 0; i < 4; i++)
            this->ore_lucrate[i] = 0;
        this->nr_angajati = 0;
    }

    // copy constructor
    Angajati(const Angajati &ob):CNP(ob.CNP)
    {
        this->nume = new char[strlen(ob.nume) + 1];
        strcpy(this->nume, ob.nume);
        strcpy(this->prenume, ob.prenume);
        this->genul = ob.genul;
        this->varsta = ob.varsta;
        this->salariu = ob.salariu;
        this->lucreaza = ob.lucreaza;
        this->ore_lucrate = new int[4];
        for (int i = 0; i < 4; i++)
            this->ore_lucrate[i] = ob.ore_lucrate[i];
        this->nr_angajati = ob.nr_angajati;
    }

    // operatorul =
    Angajati &operator=(const Angajati &ob)
    {
        if(this != &ob)
        {
            this->nume = new char[strlen(ob.nume) + 1];
            strcpy(this->nume, ob.nume);
            strcpy(this->prenume, ob.prenume);
            this->genul = ob.genul;
            this->varsta = ob.varsta;
            this->salariu = ob.salariu;
            this->lucreaza = ob.lucreaza;
            this->ore_lucrate = new int[4];
            for (int i = 0; i < 4; i++)
                this->ore_lucrate[i] = ob.ore_lucrate[i];
            this->nr_angajati = ob.nr_angajati;
        }
        return *this;
    }

    // operatorul de citire + try & catch
    friend istream &operator >> (istream &in, Angajati &ob)
    {
        char copie[30];
        cout<<"Numele angajatului: ";
        in>>copie;
        if(ob.nume != nullptr)
                delete[] ob.nume;
        ob.nume = new char[strlen(copie)+1];
        strcpy(ob.nume, copie);
        cout<<"Prenumele angajatului: ";
        in>>ob.prenume;
        cout<<"Varsta angajatului: ";
        in>>ob.varsta;
        try
        {
            if(ob.varsta > 0)
            {
                cout<<"Lucreaza acum angajatul (0 - NU || 1 - DA): ";
                in>>ob.lucreaza;
                cout<<"Genul angajatului ('M' || 'F'): ";
                in>>ob.genul;
                ob.genul = toupper(ob.genul);
                while(ob.genul != 'M' && ob.genul != 'F')
                {
                    cout<<"Ati scris gresit. Rescrieti genul angajatului ('M' || 'F'): ";
                    in>>ob.genul;
                    ob.genul = toupper(ob.genul);
                }
                cout<<"Salariul angajatului: ";
                in>>ob.salariu;
                ob.ore_lucrate = new int[4];
                cout<<"\n !!! Urmeaza sa scrieti cate ore a avut lucrate in ultmele 4 sapt. Va rog sa scrieti numere a caror suma este aprox 160 (pt functionalitate), deaorece 160 de ore inseamna programul basic de lucru (5 zile pe sapt, 8 ore pe zi) !!!\n"<<endl;
                for(int i = 0; i < 4; i++)
                {
                    cout<<"Cate ore a avut lucrate in saptamana "<<i + 1<<" (~40): ";
                    in>>ob.ore_lucrate[i];
                }
                cout<<endl<<endl;
            }
            else
            {
                throw ob.varsta;
            }
        }
        catch(int a)
        {
            cout<<"EROARE! Varsta '"<<a<<"' pe care ati scris-o nu poate fi < 0.";
            cout<<endl<<endl;
        }
    return in;
    }

    // operatorul de afisare
    friend ostream &operator << (ostream &out, const Angajati &ob)
    {
        if(ob.varsta > 0)
        {
            int ore = 0, diferenta;
            for(int i = 0; i < 4; i++)
                ore += ob.ore_lucrate[i];
            int salariu_ora = ob.salariu / 160;
            diferenta = ore - 160;
            if(ob.lucreaza == 0)
                cout<<"Angajatul "<<ob.nume<<" "<<ob.prenume<<", care nu lucreza in acest moment, are: varsta de "<<ob.varsta<<" ani, genul "<<ob.genul<<", salariu de "<<ob.salariu<<"LEI pe luna."<<endl<<endl;
            else
                cout<<"Angajatul "<<ob.nume<<" "<<ob.prenume<<", care lucreza in acest moment, are: varsta de "<<ob.varsta<<" ani, genul "<<ob.genul<<", salariu de "<<ob.salariu<<"LEI pe luna."<<endl<<endl;
            if(diferenta == 0)
                cout<<"Deoarece nu are nicio ora suplimentara si nici una in minus, salariul ramane "<<ob.salariu;
            else if(diferenta < 0)
            {
                float salariu_diferenta = (-1) * diferenta * salariu_ora;
                cout<<"Deoarece are in minus "<<(-1) * diferenta<<" ore salariul lui devine: "<<ob.salariu - salariu_diferenta<<"LEI dar dupa scaderea orelor in minus, se va mai aplica si o mica sanctiune, deci salariul devine:  "<<ob.salariu - salariu_diferenta - ((salariu_diferenta)*40/100)<<"LEI (pentru fiecare ora in minus i se scade 40% din salariu pentru acea ora)"<<endl;
            }
            else if(diferenta > 0)
            {
                float salariu_diferenta = diferenta * salariu_ora;
                cout<<"Deoarece are in plus "<<diferenta<<" ore salariul lui devine: "<<ob.salariu + salariu_diferenta<<"LEI dar dupa adunearea orelor in plus, se va mai aplica si un mic bonus, deci salariul devine: "<<ob.salariu + salariu_diferenta + ((salariu_diferenta)*30/100)<<"LEI (pentru fiecare ora in plus primeste 30% bonus din salariu pentru acea ora)"<<endl;
            }
        }
        else
        {
            cout<<"Nu am nimic de afisat deoarece varsta e < 0.";
        }
    return out;
    }

    // operatorul de indexare
    char operator [](int i)
    {
        if ((i < strlen(prenume)) && i > 0)
            return this->prenume[i];
        else
        {
            cout << "index invalid.";
            return -1;
        }
    }

    // operatorul ++ pre
    const Angajati operator++()
    {
        this->varsta++;
        return *this;
    }

    // operatorul ++ post
    const Angajati operator++(int)
    {
        this->varsta++;
        return *this;
    }

    // operatorul +
    Angajati operator+(int a)
    {
        this->varsta += a;
        return *this;
    }

    // operatorul *
    Angajati operator*(int a)
    {
        this->varsta *= a;
        return *this;
    }

    // operatorul cast explicit
    explicit operator int()
    {
        return (int)this->salariu;
    }

    // operatorul conditional <
    bool operator<(Angajati &ob)
    {
        return this->varsta < ob.varsta;
    }

    // operatorul conditional ==
    bool operator==(Angajati &ob)
    {
        return this->varsta == ob.varsta;
    }

    ~Angajati()
    {
        if(this->nume != nullptr)
            delete[] this->nume;
        if(this->ore_lucrate != nullptr)
            delete[] this->ore_lucrate;
        //cout<<"I-am concediat pe toti!"<<endl;
    }
};

int Angajati::nr_angajati = 0;


//-----------------------ETAPA A 2-A-----------------------
// interfata
class Taxe
{
public:
    virtual float impozit() = 0;
};

// clasa cu 1 IS A si 1 HAS A
class Manager:public Angajati, public Taxe
{
private:
    int nr_ang_mng;     // nr angajati subordonati managerului
    vector <Angajati> vector;
public:
    void setNrAngMng(int nr_ang_mng){this->nr_ang_mng = nr_ang_mng;}
    void setAngajati()
    {
        for(int i = 0; i < nr_ang_mng; i++)
        {
            Angajati x;
            x.citire();
            vector.push_back(x);
        }
    }
    void afisareManager()
    {
        cout<<"Managerul '"<<getNume()<<" "<<getPrenume()<<"' are urmatorii angajati pe care ii manageriaza: "<<endl;
    }

    void afisareNumeAng(int i)
    {
        cout<<vector.at(i).getNume()<<" "<<vector.at(i).getPrenume();
    }
    float impozit()
    {
        return (getSalariu() - (10 * getSalariu()) / 100);
    }
};

// clasa abstracta ester Bar + 1 IS A
class Depozit:public Bar
{
private:
    int marfa_suc_totala;
    int marfa_pop_totala;
public:
    void citesteMarfaTotala()
    {
        cout<<"Marfa totala suc: ";
        cin>>marfa_suc_totala;
        cout<<"Marfa totala popcorn: ";
        cin>>marfa_pop_totala;
    }

    void citesteMarfaVanduta()
    {
        int x, y;
        cout<<"Cat suc s-a vandut: ";
        cin>>x;
        setSucVandut(x);
        cout<<"Cat popcorn s-a vandut: ";
        cin>>y;
        setPopVandut(y);
    }

    void citestePret()
    {
        float x, y;
        cout<<"Pretul sucului: ";
        cin>>x;
        setPretSuc(x);
        cout<<"Pretul popcornului: ";
        cin>>y;
        setPretPop(y);
    }

    float pretMarfaActuala()
    {
        return (getPretSuc() * (marfa_suc_totala - getSucVandut()) + getPretPop() * (marfa_pop_totala - getPopVandut()));
    }
};

int main()
{
    //            TESTELE PENTRU CLASA: CINEMA
    // ------------------------------------------------------------
    /*
    cout<<"Constructor fara parametrii: "<<endl;
    Cinema test;
    test.afisare();
    cout<<"\nConstructor cu parametrii: "<<endl;
    Cinema test2(1, 63464.34, 'A', "Daniel");
    test2.afisare();
    cout<<"\nConstructor nr2 cu parametrii: "<<endl;
    Cinema test3(1, 53456.7);
    test3.afisare();
    cout<<"\nCopy constructor: "<<endl;
    Cinema test4(test2);
    test4.afisare();
    cout<<"\nOperatorul egal: "<<endl;
    Cinema test5;
    test5 = test2;
    test5.afisare();
    */
    // Urmeaza functionalitatea la clasa Cinema (cel mai bine o rulezi separat de codul de sus):
    /*
    Cinema funct;
    cin>>funct;
    cout<<funct;
    */

    //            TESTELE PENTRU CLASA: Bilete
    // ------------------------------------------------------------
    /*
    cout<<"Constructor fara parametrii: "<<endl;
    Bilete test;
    test.afisare();
    cout<<"\nConstructor cu parametrii: "<<endl;
    Bilete test2(5234, 'A', 25, 462.5, 1, 72, "GREENLAND: CURSA PENTRU SUPRAVIETUIRE", 18.5);
    test2.afisare();
    cout<<"\nConstructor nr2 cu parametrii: "<<endl;
    Bilete test3(5234, 0, "GREENLAND: CURSA PENTRU SUPRAVIETUIRE", 18.5);
    test3.afisare();
    cout<<"\nCopy constructor: "<<endl;
    Bilete test4(test2);
    test4.afisare();
    cout<<"\nOperatorul egal: "<<endl;
    Bilete test5;
    test5 = test2;
    test5.afisare();
    cout<<"\nOperatorul de indexare: "<<endl;
    cout<<test2[2]<<endl;
    cout<<"\nOperatorul ++ pre: "<<endl;
    ++test2;
    test2.afisare();
    cout<<"\nOperatorul ++ post: "<<endl;
    test2++;
    test2.afisare();
    cout<<"\nOperatorul +: "<<endl;
    test2 + 5;
    test2.afisare();
    cout<<"\nOperatorul *: "<<endl;
    test2 * 3;
    test2.afisare();
    cout<<"\nOperatorul cast explicit: "<<endl;
    cout<<(int)test2<<endl;
    cout<<"\nOperatorul <: "<<endl;
    if (test3 < test2) cout<<"da"<<endl; else cout<<"nu"<<endl;
    cout<<"\nOperatorul ==: "<<endl;
    if (test3 == test2) cout<<"da"<<endl; else cout<<"nu"<<endl;
    */
    // Urmeaza functionalitatea la clasa Bilete:
    /*
    Bilete funct;
    cin>>funct;
    cout<<funct;
    */

    //            TESTELE PENTRU CLASA: Bar
    // ------------------------------------------------------------
    /*
    cout<<"Constructor fara parametrii: "<<endl;
    Bar test;
    test.afisare();
    cout<<"\nConstructor cu parametrii: "<<endl;
    Bar test2(4234, 26, 34, "Fanta", 1, 9.3, 14.7);
    test2.afisare();
    cout<<"\nConstructor nr2 cu parametrii: "<<endl;
    Bar test3(8453, 12, "Sprite", 42);
    test3.afisare();
    cout<<"\nCopy constructor: "<<endl;
    Bar test4(test2);
    test4.afisare();
    cout<<"\nOperatorul egal: "<<endl;
    Bar test5;
    test5 = test2;
    test5.afisare();
    */
    // Urmeaza functionalitatea la clasa Bar:
    /*
    Bar funct;
    cin>>funct;
    cout<<funct;
    */

    //            TESTELE PENTRU CLASA: Angajati
    // ------------------------------------------------------------
    /*
    cout<<"Constructor fara parametrii: "<<endl;
    Angajati test;
    test.afisare();
    cout<<"\nConstructor cu parametrii: "<<endl;
    int orelucrate[] = {41, 42, 38, 40};
    Angajati test2("Abuni", "Daniel", 'M', 20, 4353.5, 1, orelucrate);
    test2.afisare();
    cout<<"\nConstructor nr2 cu parametrii: "<<endl;
    Angajati test3("Dorian", "Popa", 'M', 32, 0);
    test3.afisare();
    cout<<"\nCopy constructor: "<<endl;
    Angajati test4(test2);
    test4.afisare();
    cout<<"\nOperatorul egal: "<<endl;
    Angajati test5;
    test5 = test2;
    test5.afisare();
    cout<<"\nOperatorul de indexare: "<<endl;
    cout<<test2[2]<<endl;
    cout<<"\nOperatorul ++ pre: "<<endl;
    ++test2;
    test2.afisare();
    cout<<"\nOperatorul ++ post: "<<endl;
    test2++;
    test2.afisare();
    cout<<"\nOperatorul +: "<<endl;
    test2 + 3;
    test2.afisare();
    cout<<"\nOperatorul *: "<<endl;
    test2 * 2;
    test2.afisare();
    cout<<"\nOperatorul cast explicit: "<<endl;
    cout<<(int)test2<<endl;
    cout<<"\nOperatorul <: "<<endl;
    if (test3 < test2) cout<<"da"<<endl; else cout<<"nu"<<endl;
    cout<<"\nOperatorul ==: "<<endl;
    if (test3 == test2) cout<<"da"<<endl; else cout<<"nu"<<endl;
    */
    // Urmeaza functionalitatea la clasa Angajati:
    /*
    Angajati funct;
    cin>>funct;
    cout<<funct;
    */

    //-----------------------ETAPA A 2-A-----------------------
    // majoritatea chestiilor din etapa 2
    /*
    cout<<"Urmeaza datele managerului"<<endl;
    Manager manager;
    manager.citire();
    int j;
    cout<<"Cati angajati manageriaza (maxim 3): ";
    cin>>j;
    while(j > 3)
    {
        cout<<"EROARE! Introduceti un numar mai mic sau egal cu 3: ";
        cin>>j;
    }
    cout<<endl;
    manager.setNrAngMng(j);
    manager.setAngajati();
    manager.afisareManager();
    for(int i = 0; i < j; i++)
    {
        cout<<"Angajatul numarul "<<(i+1)<<": ";
        manager.afisareNumeAng(i);
        cout<<endl;
    }
    cout<<endl;
    cout<<"Dupa calcularea impozitului de 10%"<<" pe venit, salariul managerului devine: "<<manager.impozit()<<" LEI";
    */

    //teste pt cu clasa abstracta
    /*
    Depozit a;
    a.citesteMarfaTotala();
    cout<<endl;
    a.citesteMarfaVanduta();
    cout<<endl;
    a.citestePret();
    cout<<endl;
    cout<<"Valoarea sucului si a popcornului din depozit in momentul acesta este de: "<<a.pretMarfaActuala()<<"LEI.";
    */

    //-----------------------TEST PENTRU CITIRE + AFISARE DIN FISIER-----------------------
    /*
    ifstream fin("Bilete.in");
    ofstream fout("Bilete.out");
    Bilete y;
    fin>>y;
    fout<<y;
    */
    int alege, alege2, alege3, alege4, alege5;
    list <Bilete> lista;

    cout<<"------ BUN VENIT LA CITYCINEMA ------"<<endl<<endl;
    do
    {
        cout<<"-- MENIUL PRINCIPAL --"<<endl;
        cout<<"1) Cinema"<<endl;
        cout<<"2) Bilete"<<endl;
        cout<<"3) Bar"<<endl;
        cout<<"4) Angajati"<<endl;
        cout<<"0) EXIT"<<endl;
        cout<<"Alege una din optiunile de mai sus: ";
        cin>>alege;
        system("cls");
        switch(alege)
        {
            case 1: // Cinema
            {
                do
                {
                cout<<"---- CLASA CINEMA ----"<<endl<<endl;
                cout<<"1) Funtionalitatea pentru clasa Cinema"<<endl;
                cout<<"2) Inapoi"<<endl;
                cout<<"Alege una din optiunile de mai sus: ";
                cin>>alege2;
                switch(alege2)
                {
                    case 1:
                    {
                        int inapoi = 0;
                        system("cls");
                        Cinema funct;
                        cin>>funct;
                        cout<<funct;
                        cout<<endl;
                        while(inapoi != 1)
                        {
                            cout<<"Pentru a reveni la meniul anterior, apasati tasta 1: ";
                            cin>>inapoi;
                        }
                        system("cls");
                        break;
                    }
                }
                }while(alege2 != 2);
                system("cls");
                break;
            }
            case 2: // Bilete
            {
                do
                {
                cout<<"---- CLASA BILETE ----"<<endl<<endl;
                cout<<"1) Funtionalitatea pentru clasa Bilete"<<endl;
                cout<<"2) Adaugati bilete"<<endl;
                cout<<"3) Stergeti bilete"<<endl;
                cout<<"4) Afisati toate biletele"<<endl;
                cout<<"5) Citire + scriere in fisier (nu are legatura cu cele de sus)"<<endl;
                cout<<"6) Inapoi"<<endl;
                cout<<"Alege una din optiunile de mai sus: ";
                cin>>alege3;
                system("cls");
                switch(alege3)
                {
                    case 1: // functionalitate
                    {
                        int inapoi = 0;
                        Bilete funct;
                        cin>>funct;
                        cout<<funct;
                        cout<<endl;
                        while(inapoi != 1)
                        {
                            cout<<"Pentru a reveni la meniul anterior, apasati tasta 1: ";
                            cin>>inapoi;
                        }
                        system("cls");
                        break;
                    }
                    case 2: // adaugare bilete
                    {
                        Bilete a;
                        a.citire_meniu();
                        lista.push_back(a);
                        system("cls");
                        cout<<"Biletul a fost adaugat cu succes!";
                        sleep(2);
                        system("cls");
                        break;
                    }
                    case 3: // stergere bilete
                    {

                        int c = 1,del = 0;
                        for(auto i = lista.begin(); i != lista.end(); i++)
                        {
                            cout<<"("<<c<<") ";
                            (*i).afisare_meniu();
                            c++;
                            cout<<endl;
                        }
                        cout<<endl;
                        cout<<"Alegeti un numar de la 1 la "<<c-1<<" pentru a sterge biletul respectiv: ";
                        cin>>del;
                        list<Bilete>::iterator itr = lista.begin();
                        advance(itr,del-1);
                        lista.erase(itr);
                        system("cls");
                        cout<<"Biletul a fost sters cu succes!";
                        sleep(2);
                        system("cls");
                        break;

                    }
                    case 4: // afisare bilete
                    {
                        int inapoi = 0;
                        for(auto i = lista.begin(); i != lista.end(); i++)
                        {
                            (*i).afisare_meniu();
                            cout<<endl;
                        }
                        while(inapoi != 1)
                        {
                            cout<<"Pentru a reveni la meniul anterior, apasati tasta 1: ";
                            cin>>inapoi;
                        }
                        system("cls");
                        break;
                    }
                    case 5: // citire + scriere in fisier
                    {
                        ifstream fin("Bilete.in");
                        ofstream fout("Bilete.out");
                        Bilete y;
                        fin>>y;
                        fout<<y;
                        cout<<"A fost citit si scris cu succes in fisier!";
                        sleep(3);
                        system("cls");
                        break;
                    }
                }
                }while(alege3 != 6);
                system("cls");
                break;
            }
            case 3: // Bar
            {
                do
                {
                cout<<"---- CLASA BAR ----"<<endl<<endl;
                cout<<"1) Funtionalitatea pentru clasa Bar"<<endl;
                cout<<"2) Inapoi"<<endl;
                cout<<"Alege una din optiunile de mai sus: ";
                cin>>alege4;
                switch(alege4)
                {
                    case 1:
                    {
                        int inapoi = 0;
                        system("cls");
                        Bar funct;
                        cin>>funct;
                        cout<<funct;
                        cout<<endl;
                        while(inapoi != 1)
                        {
                            cout<<"Pentru a reveni la meniul anterior, apasati tasta 1: ";
                            cin>>inapoi;
                        }
                        system("cls");
                        break;
                    }
                }
                }while(alege4 != 2);
                system("cls");
                break;
            }
            case 4: // Angajati
            {
                do
                {
                cout<<"---- CLASA ANGAJATI ----"<<endl<<endl;
                cout<<"1) Funtionalitatea pentru clasa Angajati"<<endl;
                cout<<"2) Inapoi"<<endl;
                cout<<"Alege una din optiunile de mai sus: ";
                cin>>alege5;
                switch(alege5)
                {
                    case 1:
                    {
                        int inapoi = 0;
                        system("cls");
                        Angajati funct;
                        cin>>funct;
                        cout<<funct;
                        cout<<endl;
                        while(inapoi != 1)
                        {
                            cout<<"Pentru a reveni la meniul anterior, apasati tasta 1: ";
                            cin>>inapoi;
                        }
                        system("cls");
                        break;
                    }
                }
                }while(alege5 != 2);
                system("cls");
                break;
            }
        }
    }while(alege);

    return 0;
}
