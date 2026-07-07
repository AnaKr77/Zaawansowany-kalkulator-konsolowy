#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

double dodawanie(double a, double b)
{
    return a + b;
}

double odejmowanie(double a, double b)
{
    return a - b;
}

double mnozenie(double a, double b)
{
    return a * b;
}

double dzielenie(double a, double b)
{
    if(b == 0)
        throw string("Dzielenie przez 0!");

    return a / b;
}

double potegowanie(double a, double b)
{
    int wynik = 1;

    for(int i = 0; i < b; i++)
        wynik *= a;

    return wynik;
}

int reszta(int a, int b)
{
    if(b == 0)
        throw string("Dzielenie przez 0!");

    return a % b;
}

double wartoscBezwzgledna(double x)
{
    if(x < 0)
        return -x;

    return x;
}

double pierwiastek(double pole)
{
    if(pole < 0)
        throw string("Pierwiastek z liczby ujemnej");

    if(pole == 0)
        return 0;

    double dokladnosc = 0.000001;
    double a = pole / 2;
    double b = pole / a;

    while(wartoscBezwzgledna(b - a) > dokladnosc)
    {
        a = (a + b) / 2;
        b = pole / a;
    }

    return a;
}

bool czyOperator(char znak)
{
    return znak == '+' || znak == '-' || znak == '*' ||
           znak == '/' || znak == '%' || znak == '^';
}

int priorytet(char op)
{
    if(op == '+' || op == '-')
        return 1;

    if(op == '*' || op == '/' || op == '%')
        return 2;

    if(op == '^')
        return 3;

    return 0;
}

double wykonaj(double a, double b, char op)
{
    switch(op)
    {
        case '+': return dodawanie(a, b);
        case '-': return odejmowanie(a, b);
        case '*': return mnozenie(a, b);
        case '/': return dzielenie(a, b);
        case '%': return reszta((int)a, (int)b);
        case '^': return potegowanie((int)a, (int)b);
    }

    return 0;
}

void wykonajOperacje(stack<double>& liczby,
                     stack<char>& operatory)
{
    if(liczby.size() < 2)
        throw string("Za malo liczb");

    if(operatory.empty())
        throw string("Brak operatora");

    double b = liczby.top();
    liczby.pop();

    double a = liczby.top();
    liczby.pop();

    char op = operatory.top();
    operatory.pop();

    liczby.push(wykonaj(a, b, op));
}

void wykonajSqrt(stack<double>& liczby)
{
    if(liczby.empty())
        throw string("Brak liczby dla sqrt");

    double x = liczby.top();
    liczby.pop();

    liczby.push(pierwiastek(x));
}
void jeden()
{
    cout << "WPISZ WYRAZENIE: ";
   string dzialanie;
   cin.ignore();
    getline(cin, dzialanie);

    stack<double> liczby;
    stack<char> operatory;
    ofstream plik("historia.txt",ios::app);

    bool oczekujeLiczby = true;
    bool bylOperator = false;

    try
    {
        for(int i = 0; i < dzialanie.length(); i++)
        {
            char znak = dzialanie[i];

            if(isspace(znak))
                continue;

            if(isalpha(znak))
            {
                string nazwa = "";

                while(i < (int)dzialanie.length() &&
                      isalpha(dzialanie[i]))
                {
                    nazwa += dzialanie[i];
                    i++;
                }

                i--;

                if(nazwa == "sqrt")
                {
                    operatory.push('s');
                    bylOperator = true;
                }
                else
                {
                    throw string("Nieznana funkcja: " + nazwa);
                }

                oczekujeLiczby = true;
                continue;
            }

            if(isdigit(znak))
            {
                double value = 0;

                while(i < dzialanie.length() &&
                      isdigit(dzialanie[i]))
                {
                    value = value * 10 + (dzialanie[i] - '0');
                    i++;
                }

                i--;

                liczby.push(value);
                oczekujeLiczby = false;
            }
            else if(znak == '-' && oczekujeLiczby)
            {
                double value = 0;
                i++;

                if(i < dzialanie.length() &&
                   isdigit(dzialanie[i]))
                {
                    while(i < dzialanie.length() &&
                          isdigit(dzialanie[i]))
                    {
                        value = value * 10 +
                                (dzialanie[i] - '0');
                        i++;
                    }

                    i--;

                    liczby.push(-value);
                    oczekujeLiczby = false;
                }
                else
                {
                    throw string("Blad: niepoprawna liczba ujemna");
                }
            }
            else if(znak == '('|| znak == '[')
            {
                operatory.push(znak);
                oczekujeLiczby = true;
            }
            else if(znak == ')' || znak == ']')
            {
                char nawiasOtwierajacy = (znak == ']') ? '[' : '(';

                while(!operatory.empty() &&
                operatory.top() != nawiasOtwierajacy)
                {
                    if(operatory.top() == 's')
                    break;

                    wykonajOperacje(liczby, operatory);
                }

                if(operatory.empty())
                    throw string("Blad nawiasow");

                if(operatory.top() == nawiasOtwierajacy)
                    operatory.pop();

                if(!operatory.empty() && operatory.top() == 's')
                {
                    operatory.pop();
                    wykonajSqrt(liczby);
                }

                oczekujeLiczby = false;
            }
            else if(czyOperator(znak))
            {
                while(!operatory.empty() &&
                      operatory.top() != '(' &&
                      operatory.top() != 's' &&
                      priorytet(operatory.top()) >=
                      priorytet(znak))
                {
                    wykonajOperacje(liczby, operatory);
                }

                operatory.push(znak);
                oczekujeLiczby = true;
                bylOperator = true;
            }
            else
            {
                throw string("Niedozwolony znak");
            }
        }

        while(!operatory.empty())
        {
            if(operatory.top() == '(')
                throw string("Brak zamykajacego nawiasu");

            if(operatory.top() == 's')
            {
                operatory.pop();
                wykonajSqrt(liczby);
            }
            else
            {
                wykonajOperacje(liczby, operatory);
            }
        }

        if(liczby.size() != 1 || !bylOperator)
            throw string("Brak operatora w wyrazeniu");

        cout << "Wynik: " << liczby.top() << endl;
        plik << dzialanie << "=" << liczby.top() << endl;
    }
    catch(string blad)
    {
        cout << "Blad: " << blad << endl;
    }
    plik.close();
}
void dwa()
{
    ifstream plik("historia.txt");
    cout<<"HISTORIA OBLICZEN:"<<endl;
    vector<string>dzialania;
    string tekst;
    while(plik>>tekst)
    {
        dzialania.push_back(tekst);
    }
    plik.close();

    for(int i=0;i<dzialania.size();i++)
    {
        cout<<i+1<<". "<<dzialania[i]<<endl;
    }
    cout<<"Wybierz numer, aby wczytac wyrazenie lub 0, aby wrocic: "<<endl;
    int numer;
    cin>>numer;
    if(numer>0)
    {
        cout << "Wybrales wyrazenie: " << dzialania[numer-1] << endl;
        cout << "Edytuj wyrazenie: ";

        ofstream plik2("historia.txt");

        for(int i = 0; i < dzialania.size(); i++)
        {
            if(i != numer - 1)
                plik2 << dzialania[i] << endl;
        }

        plik2.close();
        jeden();
    }



}
int main()
{
    cout << "______________________"<<endl;
    cout << "WITAM W KALKULATORZE\n";
    cout << "______________________"<<endl;
    cout<<"wybierz co dzisiaj robimy: "<<endl;
    cout<<"1.obliczanie nowego wyrazenia."<<endl;
    cout<<"2.wyswietlenie historii obliczen."<<endl;
    cout<<"3.usun historie obliczen."<<endl;
    cout<<"0.koniec na dzis."<<endl;
    int wybor;
    cin>>wybor;
    while(wybor!=0)
    {
       if(wybor==1)
       {
           jeden();
       }
       else if(wybor==2)
       {
           dwa();
       }
       else if(wybor==3)
       {
           ofstream plik("historia.txt");
           plik.close();
           cout<<"HISTORIA ZOSTALA USUNIETA"<<endl;
       }
       cin>>wybor;
    }
    cout<<"DO WIDZENIA! MILEGO DNIA!";




    return 0;
}
