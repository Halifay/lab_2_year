#include <iostream>
using namespace std;

class Unit{
 public:
    int health, stamina;
 Unit(){
     health = 100;
     stamina = 100;
  cout << "unit" << endl;
 }
  ~Unit(){
    cout << "~unit" << endl;
 }

 virtual void info() {
   cout << "unit info" << endl;
 }
};

class Warrior: virtual public Unit {
 public:
 Warrior(){
  cout << "warrior" << endl;
 }
  ~Warrior(){
    cout << "~warrior" << endl;
 }

 virtual void attack() {
   cout << "\nunit is attacking!" << endl;
 }
   virtual void test() {
   cout << "\nsuper warrior" << endl;
 }

};

class Healer : virtual public Unit{
 public:
 Healer(){
  cout << "healer" << endl;
 }
  ~Healer(){
    cout << "~healer" << endl;
 }

 virtual void heal() {
   cout << "\nunit is healing!" << endl;
 }

  virtual void test() {
   cout << "\nsuper healer" << endl;
 }
};


class Monk: public Warrior, public Healer {
public:
 Monk(){
    cout << "monk" << endl;
 }

 ~Monk(){
    cout << "~monk" << endl;
 }

 void kungfu()
 {
     cout << "unit is showing martial arts!" << endl;
 }
 void go()
 {
     attack();
     heal();
     kungfu();
     Warrior::test();
     Healer::test();
     info();
     cout << endl;
 }
};



int main() {
  Monk a;
  a.go();

}
