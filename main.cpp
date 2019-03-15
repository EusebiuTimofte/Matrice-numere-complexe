
#include <iostream>
#include <cstring>
#include <typeinfo>
using namespace std;

class NrComplex//clasa ce reprezinta  numerele complexe
{
    float re,im;//partea reala si imaginara
public:
    NrComplex(){this->re=0;this->im=0;};
    NrComplex(float re , float im){this->re=re;this->im=im;};
    NrComplex(const NrComplex& c){this->re=c.re;this->im=c.im;}

    friend istream& operator>>(istream& , NrComplex &);//am supraincarcat operatorul de citire
    friend ostream& operator<<(ostream& , NrComplex );//am supraincarcat operatorul de afisare
    friend bool operator==(NrComplex , NrComplex);//operator supraincarcat care verifica daca 2 nr complexe sunt identice
    friend bool operator!=(NrComplex , NrComplex);//operator supraincarcat care verifica daca 2 nr complexe sunt diferite

    NrComplex get(){NrComplex c(this->re,this->im); return c;}//functie ce returneaza un nr complex egal cu cel retinut in obiect
    void set(NrComplex c){this->re=c.re;this->im=c.im;}//functie ce seteaza nr complex retinut in obiect

    int getRe(){return this->re;}//returneaza partea reala
    void setRe(int x){this->re=x;}//seteaza partea reala
    int getIm(){return this->im;}//returneaza partea imaginara
    void setIm(int x){this->im=x;}//seteaza partea imaginara

    friend NrComplex operator+(NrComplex , NrComplex);//operator supraincarcat ce returneaza suma dintre 2 nr complexe
    friend NrComplex operator*(NrComplex , NrComplex);//operator supraincarcat ce returneaza produlul dintre 2 nr complexe

    NrComplex operator=(NrComplex );//operator de atribuire

    friend class Matrice;
};


class Matrice_triunghiulara;//am declarat clasa matrice triunghiulara pentru a putea defini functia matriceTriunghiularaDiagonala


class Matrice//clasa abstracta ce reprezinta multimea tuturor matricelor de numere complexe
{
protected:
    NrComplex **v;//o matrice de numere complexe
public:

    Matrice();
    Matrice(int lin , int col);

    virtual istream& citire(istream&)=0;//functie de citire pur virtuala
    virtual ostream& afisare(ostream&) const=0;//functie de afisare pur virtuala


    friend bool matriceTriunghiularaDiagonala(Matrice_triunghiulara);//verifica daca o matrice triunghiulara este diagonala
};

class Matrice_oarecare: public Matrice//clasa ce reprezinta  matricile oarecare de nr complexe
{
protected:
    int lin,col;//numarul de linii si de coloane
public:
    Matrice_oarecare():Matrice(){this->lin=0;this->col=0;};//constructor de initializare ce apeleaza constr din clasa de baza
    Matrice_oarecare(int l,int c):Matrice(l,c){};//constructor de initializare parametrizat ce apeleaza constr din clasa de baza
    Matrice_oarecare(const Matrice_oarecare&);//constructor de copiere
    ~Matrice_oarecare();//destructor

    istream& citire(istream&);//citeste o matrice oarecare
    ostream& afisare(ostream&) const;//afiseaza o matrice oarecare

    friend istream& operator>>(istream& , Matrice_oarecare&);//am supraincarcat operatorul >> pt a citi o matrice oarecare
    friend ostream& operator<<(ostream& , const Matrice_oarecare);//am supraincarcat operatorul << pt a afisa o matrice oarecare

    Matrice_oarecare operator=(const Matrice_oarecare);//operator de atribuire

    friend bool matriceTriunghiularaDiagonala(Matrice_triunghiulara);//verifica daca o matrice triungiulara este diagonala

};

class Matrice_patratica: public Matrice//clasa ce reprezinta matricile patratice de nr complexe
{
protected:
    int dim;//dimensiunea matricii
public:
    Matrice_patratica():Matrice(){this->dim=0;};//constructor de initializare ce apeleaza constr din clasa de baza
    Matrice_patratica(int d ):Matrice(d,d){cout<<"Clasa baza"<<endl;};//constructor de initializare parametrizat ce apeleaza constr din clasa de baza
    Matrice_patratica(const Matrice_patratica&);//constructor de copiere
    ~Matrice_patratica();//destructor

    int getDim(){return this->dim;}
    istream& citire(istream&);//citeste o matrice patratica
    ostream& afisare(ostream&) const;//afiseaza o matrice patratica

    friend istream& operator>>(istream& , Matrice_patratica&);//am supraincarcat operatorul >> pt a citi o matrice patratica
    friend ostream& operator<<(ostream& , const Matrice_patratica);//am supraincarcat operatorul << pt a afisa o matrice patratica

    Matrice_patratica operator=(const Matrice_patratica);//operator de atribuire

    NrComplex determinant()const;//returneaza determinantul matricii

    friend bool matriceTriunghiularaDiagonala(Matrice_triunghiulara);//verifica daca o matrice tringhiulara e diagonala
};


///mostenire in diamant

class determinant2:virtual public Matrice_patratica
{
protected:
    NrComplex det;
public:
    determinant2():Matrice_patratica(){ this->det.setRe(0);this->det.setIm(0);}
    determinant2(int d):Matrice_patratica(d){this->det=this->determinant2::determinant();}
    determinant2(const determinant2&);
    ~determinant2()
    {
        for(int i=0;i<this->dim;i++)
            delete[] this->v[i];
        delete [] this->v;
    }
    istream& citire(istream& in)
    {
        Matrice_patratica::citire(in);
        cin>>det;
        return in;
    }
    ostream& afisare(ostream& out) const
    {
        Matrice_patratica::afisare(out);
        cout<<endl<<det<<endl;
        return out;
    }
    friend istream& operator>>(istream& in ,determinant2& D)
    {
        D.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out , const determinant2 D)
    {
        D.afisare(out);
        return out;
    }
};

class suma_diag:virtual public Matrice_patratica
{
protected:
    NrComplex suma;
public:
    suma_diag():Matrice_patratica(){this->suma.setRe(0);this->suma.setIm(0);}
    suma_diag(int d):Matrice_patratica(d)
    {
        this->suma.setRe(0);
        this->suma.setIm(0);
        for(int i=0;i<dim;i++)
        {
            this->suma.setRe(this->suma.getRe()+v[i][i].getRe());
            this->suma.setIm(this->suma.getIm()+v[i][i].getIm());
        }
    }
    suma_diag(const suma_diag&);
    ~suma_diag()
    {
        for(int i=0;i<this->dim;i++)
            delete[] this->v[i];
        delete [] this->v;
    }
    istream& citire(istream& in)
    {
        Matrice_patratica::citire(in);
        cin>>suma;
        return in;
    }
    ostream& afisare(ostream& out) const
    {
        Matrice_patratica::afisare(out);
        cout<<endl<<suma<<endl;
        return out;
    }
    friend istream& operator>>(istream& in ,suma_diag& s)
    {
        s.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out , const suma_diag s)
    {
        s.afisare(out);
        return out;
    }
};

class determinant2_suma_diag:public determinant2,public suma_diag
{
public:
    determinant2_suma_diag():determinant2(){this->suma.setRe(0);this->suma.setIm(0);}
    determinant2_suma_diag(int d):determinant2(d)
    {
        this->suma.setRe(0);
        this->suma.setIm(0);
        for(int i=0;i<dim;i++)
        {
            this->suma.setRe(this->suma.getRe()+v[i][i].getRe());
            this->suma.setIm(this->suma.getIm()+v[i][i].getIm());
        }
    }
    determinant2_suma_diag(const determinant2_suma_diag&);
    ~determinant2_suma_diag()
    {
        for(int i=0;i<this->dim;i++)
            delete[] this->v[i];
        delete [] this->v;
    }
    istream& citire(istream& in)
    {
        determinant2::citire(in);
        cin>>suma;
        return in;
    }
    ostream& afisare(ostream& out) const
    {
        determinant2::afisare(out);
        cout<<endl<<suma<<endl;
        return out;
    }
    friend istream& operator>>(istream& in ,determinant2_suma_diag& ds)
    {
        ds.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out , const determinant2_suma_diag ds)
    {
        ds.afisare(out);
        return out;
    }
};

///mostenire diamant terminata

class Matrice_triunghiulara:public Matrice//clasa ce reprezinta matricile triunghiulare de nr complexe
{
    int lin;//numarul de linii
public:
    Matrice_triunghiulara():Matrice(){this->lin=0;};//constructor de initializare ce apeleaza constr din clasa de baza
    Matrice_triunghiulara(int lin);//constructor de initializare parametrizat
    Matrice_triunghiulara(const Matrice_triunghiulara&);//constructor de copiere
    ~Matrice_triunghiulara();//destructor

    istream& citire(istream&);//citeste o matrice triunghiulara
    ostream& afisare(ostream&) const;//afiseaza o matrice triunghiulara

    friend istream& operator>>(istream& , Matrice_triunghiulara&);//am supraincarcat operatorul >> pt a citi o matrice triunghiulara
    friend ostream& operator<<(ostream& , const Matrice_triunghiulara);//am supraincarcat operatorul << pt a afisa o matrice triunghulara

    Matrice_triunghiulara operator=(const Matrice_triunghiulara);//operator de atribuire
    friend bool matriceTriunghiularaDiagonala(Matrice_triunghiulara);//verifica daca o matrice triunghiulara e diagonala
    friend class Matrice;
};


///Definesc metodele clasei NrComplex

istream& operator>>(istream& in, NrComplex & c)//citeste un nr complex
{
    in>>c.re>>c.im;
    return in;
}
ostream& operator<<(ostream& out, NrComplex  c)//afiseaza un nr complex
{
    out<<c.re<<" + "<<c.im<<"i ";
    return out;
}

NrComplex NrComplex::operator=(NrComplex c)//operator atribuire
{
    this->re=c.re;
    this->im=c.im;
    return c;
}

NrComplex operator+(NrComplex c1, NrComplex c2)//operator+ supraincarcat pt a returna suma a 2 nr complexe
{
    NrComplex c;
    c.re=c1.re+c2.re;
    c.im=c1.im+c2.im;
    return c;
}


NrComplex operator*(NrComplex c1, NrComplex c2)//operator* supraincarcat pt a returna produsul a 2 nr complexe
{
    NrComplex c;
    c.re=c1.re*c2.re-c1.im*c2.im;
    c.im=c1.re*c2.im+c1.im*c2.re;
    return c;
}



bool operator==(NrComplex c1, NrComplex c2)//verifica daca 2 nr complexe sunt egale
{
    if(c1.re == c2.re && c1.im==c2.im)
        return 1;
    return 0;
}

bool operator!=(NrComplex c1, NrComplex c2)//verifica daca 2 nr complexe sunt diferite
{
    if(c1.re != c2.re || c1.im!=c2.im)
        return 1;
    return 0;
}

///Definesc metode ale clasei abstracte Matrice

Matrice::Matrice()//constr de initializare
{
    v=NULL;
}

Matrice::Matrice(int lin , int col)//constructor de initializare cu parametri
{
    cout<<"Introduceti elementele matricii patratice de dim "<<lin<<endl;
    v=new NrComplex*[lin];
    for(int i=0;i<lin;i++)//citesc elementele
        {
            v[i]=new NrComplex[col];
            for(int j=0;j<col;j++)
                cin>>this->v[i][j];
        }
}

bool matriceTriunghiularaDiagonala(Matrice_triunghiulara Tr)//verifica daca o matrice triunghiulara este diagonala
{
    NrComplex origin(0,0);
    for(int i=0;i<Tr.lin;i++)//parcurge ce este sub diagonala si daca gaseste un element nenul returneaza 0
        for(int j=0;j<i;j++)
        if(Tr.v[i][j] != origin)
        return 0;
    return 1;//nu a fost gasit nici un element nenul => matricea este diagonala
}


///Definesc metodele clasei Matrice_oarecare
Matrice_oarecare::Matrice_oarecare(const Matrice_oarecare &M)//constructor de copiere
{
    this->lin=M.lin;
    this->col=M.col;
    this->v=new NrComplex*[this->lin];
    for(int i=0;i<this->lin;i++)
        {
            v[i]=new NrComplex[this->col];
            for(int j=0;j<this->col;j++)
                this->v[i][j]=M.v[i][j];
        }

}
Matrice_oarecare::~Matrice_oarecare()//destructor
{
    for(int i=0;i<this->lin;i++)
        delete[] this->v[i];
    delete [] this->v;
}

istream& Matrice_oarecare::citire(istream& in)//citeste o matrice oarecare
{
    if(this->v != NULL)//daca este nenula o sterge
        {
            for(int i=0;i<this->lin;i++)
                delete[] this->v[i];
            delete [] this->v;
        }
    cout<<"Nr linii si coloane:"<<endl;
    in>>this->lin>>this->col;
    cout<<endl<<"Introduceti de la tastatura numerele complexe din matrice ( partea reala , enter,partea imaginara)"<<endl;

    v=new NrComplex*[this->lin];
    for(int i=0;i<this->lin;i++)//aloca memorie
        v[i]=new NrComplex[this->col];

    for(int i=0;i<this->lin;i++)//citeste
        for(int j=0;j<this->col;j++)
        in>>this->v[i][j];
    return in;
}

ostream& Matrice_oarecare::afisare(ostream& out) const//afiseaza o matrice oarecare
{
    if(this->lin == 0)
        {
            out<<"Matrice nula"<<endl;
            return out;
        }
    for(int i=0;i<this->lin;i++)//daca nu este nula , o afiseaza
    {
        for(int j=0;j<this->col;j++)
            out<<this->v[i][j]<<' ';
        out<<endl;
    }
    return out;
}

Matrice_oarecare Matrice_oarecare::operator=(const Matrice_oarecare M)//operator atribuire
{
        if(this != NULL)//daca este nenula o sterge
        {
            for(int i=0;i<this->lin;i++)
                delete[] this->v[i];
            delete [] this->v;
        }
        this->lin=M.lin;
        this->col=M.col;
        this->v=new NrComplex*[this->lin];
        for(int i=0;i<this->lin;i++)
        {
            this->v[i]=new NrComplex[this->col];
        }
        for(int i=0;i<this->lin;i++)
            for(int j=0;j<this->col;j++)
            this->v[i][j]=M.v[i][j];
    return M;
}

istream& operator>>(istream& in, Matrice_oarecare& M)//citeste o matrice oarecare
{
    return M.citire(in);//apeleaza functia de citire
}
ostream& operator<<(ostream& out, const Matrice_oarecare M)//afiseaza o matrice oarecare
{
    return M.afisare(out);//apeleaza functia de afisare
}


///Definesc metodele clasei Matrice_patratica
Matrice_patratica::Matrice_patratica(const Matrice_patratica& M)//constructor de copiere
{
    this->dim=M.dim;
    this->v=new NrComplex*[this->dim];
    for(int i=0;i<this->dim;i++)
        {
            v[i]=new NrComplex[this->dim];
            for(int j=0;j<this->dim;j++)
                this->v[i][j]=M.v[i][j];
        }

}
Matrice_patratica::~Matrice_patratica()//destructor
{
    for(int i=0;i<this->dim;i++)
        delete[] this->v[i];
    delete [] this->v;
}


istream& Matrice_patratica::citire(istream& in)//citeste o matrice patratica
{
    if(this->v != NULL)//stergea matricea daca este nenula
        {
            for(int i=0;i<this->dim;i++)
                delete[] this->v[i];
            delete [] this->v;
        }
    cout<<"Dimensiune:"<<endl;
    in>>this->dim;
    cout<<endl<<"Introduceti de la tastatura numerele complexe din matrice ( partea reala , enter,partea imaginara)"<<endl;

    v=new NrComplex*[this->dim];
    for(int i=0;i<this->dim;i++)
        v[i]=new NrComplex[this->dim];

    for(int i=0;i<this->dim;i++)
        for(int j=0;j<this->dim;j++)
        in>>this->v[i][j];
    return in;
}

ostream& Matrice_patratica::afisare(ostream& out) const//afiseaza matricea
{
    if(this->dim == 0)
        {
            out<<"Matrice nula"<<endl;
            return out;
        }
    for(int i=0;i<this->dim;i++)//daca e nenula, parcurge matricea si o afiseaza
    {
        for(int j=0;j<this->dim;j++)
            out<<this->v[i][j]<<' ';
        out<<endl;
    }
    out<<"det: "<<determinant()<<endl;
    return out;
}

Matrice_patratica Matrice_patratica::operator=(const Matrice_patratica M)//operator atribuire
{
        if(this != NULL)//daca este nenula, dezaloca memoria
        {
            for(int i=0;i<this->dim;i++)
                delete[] this->v[i];
            delete [] this->v;
        }
        this->dim=M.dim;
        this->v=new NrComplex*[this->dim];
        for(int i=0;i<this->dim;i++)//realoca memoria
        {
            v[i]=new NrComplex[this->dim];
        }
        for(int i=0;i<this->dim;i++)
            for(int j=0;j<this->dim;j++)
            this->v[i][j]=M.v[i][j];
    return M;
}

istream& operator>>(istream& in, Matrice_patratica& M)//citeste o matrice patratica
{
    return M.citire(in);//apelaza functia de citire
}
ostream& operator<<(ostream& out, const Matrice_patratica M)//afiseaza o matrice patratica
{

    return M.afisare(out);//apeleaza functia de afisare
}


void getCofactor(NrComplex **mat, NrComplex **temp, int p, int q, int n)//memoreaza in temp matricea mat din care au fost scoase linia p si coloana q
{
    int i = 0, j = 0;

    for (int row = 0; row < n; row++)//parcurge matricea
    {
        for (int col = 0; col < n; col++)//copiaza intr-o matrice temporara elementele care nu se afla pe linia p si coloana q
        {
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];

                if (j == n - 1)//capat de rand , creste linia si se reseteaza coloana
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}


NrComplex determinantMatrice(NrComplex **mat, int n)//returneaza determinantul matricii mat
{
    NrComplex D(0,0);//initializare rezultat

    if (n == 1)//daca matricea contine un singur element
        return mat[0][0];

    NrComplex **temp=new NrComplex*[n];//matricea temp retine cofactorii
    for(int i=0;i<n;i++)
        temp[i]=new NrComplex[n];

    NrComplex sign(1,0);//semnul cu care fiecare cofactor se inmulteste cand un determinant se descompune

    for (int f = 0; f < n; f++)//parcurge prima linie
    {
        getCofactor(mat, temp, 0, f, n);//matricea temp devine cofactorul determinat de prima linie si coloana f+1
        D =D + sign * mat[0][f] * determinantMatrice(temp, n - 1);

        sign.setRe(-sign.getRe());//se schimba semnul cu care sunt inmultiti cofactorii
    }
    for(int i=0;i<n;i++)
        delete [] temp[i];
    delete [] temp;
    return D;
}

NrComplex Matrice_patratica::determinant()const//returneaza determinantul matricei
{
    Matrice_patratica Mp(*this);//obiect nou ce ia valoarea matricii retinute in clasa
    return determinantMatrice(Mp.v,Mp.dim);//returneaza determinantul obiectului nou
}



///Definesc metodele clasei Matrice_triunghiulara


Matrice_triunghiulara::Matrice_triunghiulara(int lin)//constructor parametrizat
{
    this->lin=lin;
    this->v=new NrComplex*[this->lin];//aloca memorie
    for(int i=0;i<this->lin;i++)//citeste elementele
    {
        this->v[i]=new NrComplex[i+1];//aloca memorie pt fiecare rand
        for(int j=0;j<i+1;j++)
            cin>>this->v[i][j];
    }
}

Matrice_triunghiulara::Matrice_triunghiulara(const Matrice_triunghiulara& M)//constructor de copiere
{
    this->lin=M.lin;
    this->v=new NrComplex*[this->lin];
    for(int i=0;i<this->lin;i++)
        {
            this->v[i]=new NrComplex[i+1];
            for(int j=0;j<i+1;j++)
                this->v[i][j]=M.v[i][j];
        }

}
Matrice_triunghiulara::~Matrice_triunghiulara()//destructor
{
    for(int i=0;i<this->lin;i++)
        delete[] this->v[i];
    delete [] this->v;
}

istream& Matrice_triunghiulara::citire(istream& in)//citeste o matrice triunghiulara
{
    if(this->v != NULL)//daca e nenula , dezaloca memoria
        {
            for(int i=0;i<this->lin;i++)
                delete[] this->v[i];
            delete [] this->v;
        }

    cout<<"Nr linii:"<<endl;
    in>>this->lin;
    cout<<endl<<"Introduceti de la tastatura numerele complexe din matrice ( partea reala , enter,partea imaginara)"<<endl;

    v=new NrComplex*[this->lin];
    for(int i=0;i<this->lin;i++)//aloca memorie
        this->v[i]=new NrComplex[i+1];

    for(int i=0;i<this->lin;i++)//citeste
        for(int j=0;j<i+1;j++)
        in>>this->v[i][j];
    return in;
}

ostream& Matrice_triunghiulara::afisare(ostream& out) const//afiseaza o matrice triunghiulara
{
    if(this->lin == 0)
        {
            out<<"Matrice nula"<<endl;
            return out;
        }
    for(int i=0;i<this->lin;i++)//daca este nenula , o afiseaza
    {
        for(int j=0;j<i+1;j++)
            out<<this->v[i][j]<<' ';
        out<<endl;
    }
    return out;
}

Matrice_triunghiulara Matrice_triunghiulara::operator=(const Matrice_triunghiulara M)//operator atribuire
{
        if(this->v != NULL)//daca e nenula, o dezaloca
        {
            for(int i=0;i<this->lin;i++)
                delete[] this->v[i];
            delete [] this->v;
        }
        this->lin=M.lin;
        this->v=new NrComplex*[this->lin];
        for(int i=0;i<this->lin;i++)//aloca memorie
        {
            this->v[i]=new NrComplex[i+1];
        }
        for(int i=0;i<this->lin;i++)
            for(int j=0;j<this->lin;j++)
            this->v[i][j]=M.v[i][j];
    return M;
}

istream& operator>>(istream& in, Matrice_triunghiulara& M)//citeste o matrice triunghiulara
{
    return M.citire(in);//apeleaza functia de citire
}
ostream& operator<<(ostream& out, const Matrice_triunghiulara M)
{//afiseaza o triunghiulara
    return M.afisare(out);//apeleaza functia de afisare
}


int main()
{
    ///citesc n obiecte amestecate de orice tip implementat,sa se stocheze si sa se afiseze grupate dupa tip
    ///,iar cele din clasa initiala sa fie sortate dupa un criteriu la alegere (le am sortat pe cele din clasa derivata Matrice_patratica
    /// dupa dimensiuen , deoarece clasa de baza este abstracta);
    /// upcast , rtti
    cout<<"Nr matrici care sa fie citite si afisate:";
    int nr;
    cin>>nr;
    cout<<endl;

    Matrice **pm=new Matrice*[nr];

    char opt;
    for(int i=0;i<nr;i++)
        {
            cout<<"Ce tip are matricea cu numarul "<<i+1<<" ? ( O - oarecare ; P - patratica ; T - triunghiulara)"<<endl;
            cin>>opt;
            cout<<endl;
            switch (opt)
            {
            case 'O':
                {
                    pm[i]=new Matrice_oarecare;
                    cin>>*(dynamic_cast<Matrice_oarecare*>(pm[i]));
                    break;
                }
            case 'P':
                {
                    pm[i]=new Matrice_patratica;
                    cin>>*(dynamic_cast<Matrice_patratica*>(pm[i]));
                    break;
                }
            case 'T':
                {
                    pm[i]=new Matrice_triunghiulara;
                    cin>>*(dynamic_cast<Matrice_triunghiulara*>(pm[i]));
                    break;
                }
            }
        }

    cout<<"Matricile oarecare:"<<endl;
    for(int i=0;i<nr;i++)
        {
            if(strstr(typeid(*pm[i]).name(),"Matrice_oarecare"))
                cout<<*(dynamic_cast<Matrice_oarecare*>(pm[i]));
            cout<<endl;
        }
    cout<<endl<<"Matricile patratice:"<<endl;
    for(int i=0;i<nr;i++)
        {
            if(strstr(typeid(*pm[i]).name(),"Matrice_patratica"))
                cout<<*(dynamic_cast<Matrice_patratica*>(pm[i]));
            cout<<endl;
        }
    cout<<endl<<"Matricile triunghiulare:"<<endl;
    for(int i=0;i<nr;i++)
        {
            if(strstr(typeid(*pm[i]).name(),"Matrice_triunghiulara"))
                cout<<*(dynamic_cast<Matrice_triunghiulara*>(pm[i]));
            cout<<endl;
        }

    int j=0;
    Matrice** pm2=new Matrice*[nr];
    for(int i=0;i<nr;i++)
        {
            if(strstr(typeid(*pm[i]).name(),"Matrice_patratica"))
                {
                    pm2[j]=dynamic_cast<Matrice_patratica*>(pm[i]);
                    j++;
                }

        }

    Matrice_patratica aux;
    for(int i=0;i<j-1;i++)
        for(int k=i+1;k<j;k++)
        if(dynamic_cast<Matrice_patratica*>(pm2[i])->getDim() < dynamic_cast< Matrice_patratica*>(pm2[k])->getDim())
    {
        aux=*dynamic_cast<Matrice_patratica*>(pm2[i]);
        *dynamic_cast<Matrice_patratica*>(pm2[i])=*dynamic_cast<Matrice_patratica*>(pm2[k]);
        *dynamic_cast<Matrice_patratica*>(pm2[k])=aux;
    }

    cout<<"Matricile patratice ordonate dupa dimensiune:"<<endl;
    for(int i=0;i<j;i++)
    {
        cout<<*(dynamic_cast<Matrice_patratica*>(pm2[i]));
        cout<<endl;
    }


    ///end


    ///transmiterea parametrilor catre constructorii din clasa de baza/clasele de baza
    /// (va afisa Clasa baza pt ca apeleaza constructorul din Matrice_patratica)
    //determinant2 D2(2);
    ///end

    ///Downcast
    /*Matrice_patratica baza(2);
    Matrice_patratica *pb=new Matrice_patratica;
    *pb=baza;
    determinant2 *pderivata=new determinant2;
    *(dynamic_cast<Matrice_patratica*>(pderivata))=baza;
    pderivata->afisare(cout);*/
    ///end

    ///supraincarcare operatori pentru fiecare clasa
    /*NrComplex c1(2,4),c2,c3,c4;
    cin>>c3;
    c4=c3;
    NrComplex c5=c1;
    NrComplex c6=c1+c1;
    NrComplex c7=c1*c2;
    cout<<c1<<endl<<c2<<endl<<c3<<endl<<c4<<endl<<c5<<endl<<c1+c3<<endl<<c1*c1<<endl<<c6<<c7<<endl;

    NrComplex c8,c9,c10(5,7);
    c8=c9=c10;
    cout<<c8<<c9<<c10;*/


    /*Matrice_oarecare Mo1,Mo2;
    cin>>Mo1;
    Matrice_oarecare Mo3(Mo1);

    Matrice_oarecare Mo4,Mo5;
    Mo4=Mo5=Mo1;

    cout<<Mo1<<endl<<Mo2<<endl<<Mo3<<endl<<Mo4<<endl<<Mo5;*/

    /*Matrice_patratica Mp1,Mp2;
    cin>>Mp1;
    Matrice_patratica Mp3(Mp1);
    Matrice_patratica Mp4,Mp5;
    Mp4=Mp5=Mp1;

    cout<<Mp1<<Mp2<<Mp3<<Mp4<<Mp5<<endl;*/


   /* Matrice_patratica *p=new Matrice_patratica;
    cin>>(*p);
    cout<<(*p);

    Matrice *pb=p;
    cin>>(*dynamic_cast<Matrice_patratica*>(pb));
    cout<<(*dynamic_cast<Matrice_patratica*>(pb));*/


    /*Matrice_triunghiulara Mt1,Mt2;
    cin>>Mt1;
    Matrice_triunghiulara Mt3(Mt1);
    Matrice_triunghiulara Mt4,Mt5;
    Mt4=Mt5=Mt1;
    cout<<Mt1<<Mt2<<Mt3<<Mt4<<Mt5;

    cin>>Mt3;
    if(matriceTriunghiularaDiagonala(Mt1))
        cout<<"Mt1 este";
    else
        cout<<"Mt1 nu este";
    cout<<endl;
    if(matriceTriunghiularaDiagonala(Mt3))
        cout<<"Mt3 este";
    else
        cout<<"Mt3 nu este";*/
    ///end



    return 0;
}
