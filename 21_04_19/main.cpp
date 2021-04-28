#include <iostream>
#include <vector>

using namespace std;

class Unit {
public:
    virtual void description() = 0;
    virtual ~Unit() {}
    // we can rewrite this methods in derived classes or even make these virtual,
    // but this is enough for current task.
    void attack()
    {
        description();
        cout << " attacks" << endl;
    }
    void move()
    {
        description();
        cout << " moves" << endl;
    }
};

//Human
class Archer : public Unit {
    void description() override {
        cout << "Archer";
    }
};

class Footman : public Unit {
    void description() override {
        cout << "Footman";
    }
};
class Knight : public Unit {
    void description() override {
        cout << "Knight";
    }
};

//Ork
class Spearman : public Unit {
    void description() override {
        cout << "Spearman";
    }
};

class Grunt : public Unit {
    void description() override {
        cout << "Grunt";
    }
};
class Wolfrider : public Unit {
    void description() override {
        cout << "Wolfrider";
    }
};

class Factory {
public:
    virtual Unit* createMelee() = 0;
    virtual Unit* createRanged() = 0;
    virtual Unit* createMounted() = 0;
    virtual ~Factory() {}
};

class Barracks : public Factory {
public:
    virtual Unit* createMelee(){
        return new Footman();
    }
    virtual Unit* createRanged(){
        return new Archer();
    }
    virtual Unit* createMounted() {
        return new Knight();
    }
};

class Lair : public Factory {
public:
    virtual Unit* createMelee(){
        return new Grunt();
    }
    virtual Unit* createRanged(){
        return new Spearman();
    }
    virtual Unit* createMounted() {
        return new Wolfrider();
    }
};

template<class T>
class Squad
{
    vector<Unit*> units;
    // assemble squad
public:
    // Squad(Factory *factory, int number=10)
    Squad(int number=4)
    {
        Factory *factory = new T();
        for(int i = 0; i < number; i++)
        {
            int r = rand() % 3;
            switch (r)
            {
                case 0: units.push_back(factory->createMelee()); break;
                case 1: units.push_back(factory->createRanged()); break;
                case 2: units.push_back(factory->createMounted()); break;
                default: cout << "Unmatched case during squad assembly!" << endl; break;
            }
        }
        delete factory;
    }

    // void print_units()
    // {
    //     for(auto current_unit : units)
    //     {
    //         if(current_unit == units.back())
    //             cout << " and ";
    //         else if(current_unit != units.front())
    //             cout << ", ";
    //         current_unit->description();
    //     }
    // }
    // void move()
    // {
    //     print_units();
    //     cout << " move to the target." << endl;
    // }

    // void attack()
    // {
    //     print_units();
    //     cout << " attack the target." << endl;

    // }

    void move()
    {
        for(auto unit : units)
            unit->move();
        cout << endl;
    }

    void attack()
    {
        for(auto unit : units)
            unit->attack();
        cout << endl;
    }

    void disband_squad()
    {
        for(auto current_unit: units)
            delete current_unit;
    }

    ~Squad()
    {
        disband_squad();
    }
};

int main() {
    // Factory* f = new Barracks();

    // vector<Unit*> army;
    // army.push_back(f->createMelee());
    // army.push_back(f->createMelee());
    // army.push_back(f->createRanged());
    // army.push_back(f->createRanged());
    // army.push_back(f->createMounted());

    // for(auto unit : army)
    //     unit->description();
    // for(auto unit : army)
    //     delete unit;
    // army.clear();

    // delete f;

    cout << "first squad test" << endl;
    auto first_squad = new Squad<Barracks>();
    first_squad->move();
    first_squad->attack();
    cout << endl;
    delete first_squad;

    cout << "second squad test" << endl;
    auto second_squad = new Squad<Lair>();
    second_squad->move();
    second_squad->attack();
    delete second_squad;
}
