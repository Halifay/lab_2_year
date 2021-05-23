#include <iostream>
#include <vector>
using namespace std;

class origin{
    public:
    virtual void print() = 0;
};

class Composite {
protected:
    vector<origin *> children;
public:
    virtual void add(origin * c){
        children.push_back(c);
    }
};

class Char: public origin
{
    char value = '0';
public:

    Char(char c): value(c){}

    void print()
    {
        cout << value;
    }
};

class String: public origin, public Composite
{
    int index = 0;
public:
    String(int ind): index(ind){}
    void print()
    {
        cout << "string #" << index << ": ";
        for(auto child : children)
            child->print();
    }
};


int main() {

    Char c('c'), h('h'), a('a'), r('r');
    String s(1);
    s.add(&c); s.add(&h); s.add(&a); s.add(&r);
    s.print();
    return 0;
}
