#include <iostream>
#include <string>
#include <float.h>
#include "TreeMap.h"
//ilosc lisci
#define NRL 4

using namespace std;

/**
 **  Struktura zawierajaca nazwe i numer liscia w tablicy odl
**/
struct lisc
{
    string name;
    int nr;

    lisc(string n, int a): name(n), nr(a) {};
};
/**
 **  Tablica odleglosci - moze byc podawana inaczej ale trzeba zmienic
 **  funkcje init. Do algorytmu wykorzystywany vector d
**/
float t[NRL][NRL]= {{0,3,7,9},
                    {0,0,6,8},
                    {0,0,0,6},
                    {0,0,0,0}
                    };

vector<vector<float> > d;

vector<lisc> name;


//funkcja do zape³niania tablicy odleglosci
void init()
{
    name.push_back(lisc("A",0));
    name.push_back(lisc("B",1));
    name.push_back(lisc("C",2));
    name.push_back(lisc("D",3));
    for(int i=0; i<NRL; ++i)
    {
        d.push_back(vector<float>());
        for(int j=0; j<NRL; ++j)
            d[i].push_back(t[i][j]);
    }
}

void reset()
{
    for(int i=0; i<NRL; ++i)
    {
        d[i].clear();
    }
    d.clear();
    name.clear();
}

//funkcja z tw. (Studier & Keppler).
int r(int a)
{
    float ra=0;
    for(int i=0; i<d.size(); i++)
        ra+=d[a][i];

    return ra/(NRL-2);
}

//aktualizacja tablicy odlelosci
void akt(int i,int j)
{
    d.push_back(vector<float>());
    for(int l=0; l<NRL; l++)
        d[l].push_back((d[i][l] + d[j][l] - d[i][j])/2);
}

int NJ(TreeMap *tree)
{
    int nrl=NRL;
    int k,l;
    float min;
    float djk;
    float dik;

    while(nrl>3)
    {
        min=FLT_MAX;

        //pkt 1
        for(int p=0; p<name.size(); p++)
            for(int j=name[p].nr+1; j<NRL; j++)
            {
                int i=name[p].nr;
                if(t[i][j]-(r(i)+r(j))<min && i!=j)
                {
                    min=(t[i][j]-(r(i)+r(j)));
                    k=i;
                    l=j;
                }
            }
        //pkt 3
        akt(k,l);

        nrl--;

        //pkt 5
        dik =(t[k][l]+ r(k) - r(l))/2;
        djk = t[k][l] - dik;

        //pkt 4
        tree->insert(name[k].name,(d[k][l]+dik-djk)/2,name[l].name,(d[k][l]+djk-dik)/2);

        //pkt 2
        name.push_back(lisc(name[k].name+name[l].name,d.size()-1));
        name.erase(name.begin() + l);
        name.erase(name.begin() + k);
    }

    //obsluz „male drzewo”;
    int a = name[0].nr;
    int b = name[1].nr;
    int c = name[2].nr;

    tree->insert(name[0].name,(d[a][b]+d[a][c]-d[b][c])/2,name[1].name,(d[a][b]+d[b][c]-d[a][c])/2);
    tree->insert(name[0].name+name[1].name,(d[a][c]+d[b][c]-d[a][b])/2,name[2].name,(d[a][c]+d[b][c]-d[a][b])/2);
    tree->laste();
}

int main()
{
    TreeMap *tree1 = new TreeMap();
    TreeMap *tree2 = new TreeMap();
    init();
    NJ(tree1);
    reset();
    init();
    NJ(tree2);
    tree1->show();
    cout<<tree1->equal(*tree2);
    return 0;
}
