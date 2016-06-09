#include <assert.h>
#include <stdlib.h>
#include <iterator>
#include <vector>
#include <string>

using namespace std;

struct TreeNode;
/**
 **   Krawêdzie drzewa - wskazanie na dany wierzcholek i wartoœæ
 **  tej krawêdzi
**/
struct Vertex
{
    TreeNode *nxt;
    float value;
    Vertex(): nxt(nullptr), value(0.0) {}
};
/**
 **   Wierzcho³ki drzewa
**/
struct TreeNode
{
    Vertex parent;
    Vertex left;
    Vertex right;
    string name;

    TreeNode(string a): name(a) {}
    //dodawanie wierzcho³ków
    //wskazanie na wierzcholek i wartaosc krawedzi
    void addparent(TreeNode* a,float v)
    {
        parent.nxt=a;
        parent.value=v;
    }
    void addleft(TreeNode* a,float v)
    {
        left.nxt=a;
        left.value=v;
    }
    void addright(TreeNode* a,float v)
    {
        right.nxt=a;
        right.value=v;
    }
};

/**
 **  Klasa  Drzewo
**/
class TreeMap
{
private:
    //do przechowywania wierzchołkow
    //ulatwia przechodzenie po wierzcholkach
    //nie potrzeba bawic sie w iteratory
    vector<TreeNode *> t;
public:
    TreeMap()
    {
    }
    ~TreeMap();
    //dodawanie nowych elementow
    //jezeli pierwszy element to dodanie nowego wierzcholka(c) i dolaczenie wierzcholkow a i b
    //jezeli nastepne to potrzebne dodanie jeszcze jednego wierzcholka posredniego
    //nazwy wierzcholkow dodatkowych to suma nazw lisci/wierzcholkow posrednich np.
    //liscie A B C D wierzcholki posrednie t AB i CD po dodaniu jeszcze jednego liscia zrobi sie wierzcholek ABCD
    void insert(string a,float va, string b, float vb)
    {
        TreeNode *aa;
        TreeNode *bb;
        if(find(a)==-1)
        {
            aa = new TreeNode(a);
            t.push_back(aa);
        }
        else aa = t[find(a)];
        if(find(b)==-1)
        {
            bb = new TreeNode(b);
            t.push_back(bb);
        }
        else bb = t[find(b)];
        TreeNode *c = new TreeNode(a+b);
        aa->addparent(c,va);
        bb->addparent(c,vb);
        c->addleft(aa,va);
        c->addright(bb,vb);
        t.push_back(c);
    }

    //jezeli koniec grafu to usuniecie ostatniego wierzcholka i aktualizacja krawedzi
    void laste()
    {
        t[t.size()-1]->right.nxt->addparent(t[t.size()-1]->left.nxt,t[t.size()-1]->left.value);
        t[t.size()-1]->left.nxt->addparent(t[t.size()-1]->right.nxt,t[t.size()-1]->right.value);
        delete t[t.size()-1];
        t.pop_back();
    }

    //prezentacja drzewa
    void show()
    {
        for(int i=0; i<t.size()-1; i++)
        {
            cout<<"Z "<<t[i]->name<<" do "<<t[i]->parent.nxt->name<<" wartosc : "<<t[i]->parent.value<<endl;
        }
    }

    //szukanie danego wierzholka drzewa
    //zwraca iterator albo -1 gdy nie ma tego wierzcholka
    int find(string s)
    {
        for(int i=0; i<t.size(); i++)
        {
            if(t[i]->name==s)return i;
        }
        return -1;
    }

    bool CheckStructEq(TreeNode * T1, TreeNode * T2)
	{
		if(T1 == nullptr || T2 == nullptr)
			return T1 == T2;

		return CheckStructEq(T1->left.nxt, T2->left.nxt) && CheckStructEq(T1->right.nxt, T2->right.nxt);
	}

	TreeNode* last()
	{
	    return t[t.size()-2];
	}

	int size()
	{
	    return t.size();
	}
    //sprawdzanie czy drzewa takie same
	bool equal(TreeMap& another)
	{
	    if(this->size()!=another.size())return false;
		return CheckStructEq(last(), another.last());
	}
};

