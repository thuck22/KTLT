#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"
class Events;
class BaseItem;
class BaseKnight;
// #define DEBUG

enum ItemType {ANTIDOTE=0,PHOENIXDOWN,PHOENIXDOWNII,PHOENIXDOWNIII,PHOENIXDOWNIV};
struct Node{
    BaseItem *item;
    Node* next;
};
class BaseBag {
protected:
    Node *head;
    static int count;
public:
    BaseBag(){
        head = NULL;
    }
    ~BaseBag(){
        Node *p = head;
        while(p != NULL){
            head = head->next;
            delete p;
            p = head;
        }
    }
    Node * getHead() {return head;}
    void setHead(){head =NULL;}
    void sHead(Node *h) {head = h;}
    virtual bool insertFirst(BaseItem * item) = 0;
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};

class BaseOpponent {
protected:
    int gil;
    int baseD;
public:
    BaseOpponent(){}
    ~BaseOpponent(){}
    virtual int getBaseD() {return baseD;}
    virtual int getGil(){ return gil;}
};
class MadBear : public BaseOpponent {
public:
    MadBear(){}
    ~MadBear() {}
    int getGil(){
        return 100;
    }
    int getbaseDamage(){
        return 10;
    }
};
class Bandit:public BaseOpponent{
public:
    Bandit(){}
    ~Bandit() {}
    int getGil(){
        return 150;
    }
    int getbaseDamage(){
        return 15;
    }
};
class LordLupin:public BaseOpponent{
public:
    LordLupin(){}
    ~LordLupin() {}
    int getGil(){
        return 450;
    }
    int getbaseDamage(){
        return 45;
    }
};
class Elf:public BaseOpponent{
public:
    Elf(){}
    ~Elf() {}
    int getGil(){
        return 750;
    }
    int getbaseDamage(){
        return 75;
    }
};
class Troll:public BaseOpponent{
public:
    Troll(){}
    ~Troll() {}
    int getGil(){
        return 800;
    }
    int getbaseDamage(){
        return 95;
    }
};

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight: public BaseBag {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;
public:
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    int getLevel();
    void setLevel(int cong);
    int getGil();
    void setGil(int g);
    void receiveGil(int &g);
    int getHP();
    int getmaxHP();
    void setHP(int hp);
    int getAnti() ;
    void  setAnti();
    BaseKnight();
    ~BaseKnight();

    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    void drop();
    KnightType getType() {return knightType;}
    virtual double getBaseD() = 0;
};

class PaladinKnight {
private:
public:
    double getBaseD() {
        return 0.06;
    }
};  

class LancelotKnight {
private:
public:
    double getBaseD() {
        return 0.05;
    }
};  

class DragonKnight {
private:
public:
    double getBaseD() {
        return 0.075;
    }
};  

class ArmyKnights {
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();

    void remove();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    int getmax();
    void setSL() ;
    BaseKnight * lastKnight() const;
    BaseKnight * lKnight(KnightType ktype) const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void setPa();
    void setLan();
    void setGui();
    void setSword();

    void printInfo() const;
    void printResult(bool win) const;

    BaseKnight * canReceive();
private:
    int max;
    static int sl;
    BaseKnight **army;
    bool pa,lan,gui,sword;
};

class BaseItem {
private:
    ItemType itemType;
public:
    BaseItem(){itemType = ANTIDOTE;}
    ~BaseItem(){}
    virtual ItemType getT(){}
    virtual ItemType getType(){}
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class Antidote :public BaseItem {
private:
    ItemType type;
public:
    Antidote(){
        type = ANTIDOTE;
    }
    ~Antidote(){}
    ItemType getType() {
        return type;
    }
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};

class PhoenixdownII: public BaseItem {
private:
    ItemType type;
    ItemType t;
public:
    PhoenixdownII(){
        type = PHOENIXDOWN;
        t = PHOENIXDOWNII;
    }
    ~PhoenixdownII(){}
    ItemType getType() {
        return type;
    }
    ItemType getT() {
        return t;
    }
    bool canUse(BaseKnight * knight) {
        int hp = knight->getHP();
        int maxhp = knight->getmaxHP();
        if(hp < maxhp/4) return 1;
        else return 0;
    }
    void use (BaseKnight * knight) {
        int maxhp = knight->getmaxHP();
        knight->setHP(maxhp);
    }
};

class PhoenixdownIII: public BaseItem {
private:
    ItemType type;
    ItemType t;
public:
    PhoenixdownIII(){
        type = PHOENIXDOWN;
        t = PHOENIXDOWNIII;
    }
    ~PhoenixdownIII(){}
    ItemType getType() {
        return type;
    }
    ItemType getT() {
        return t;
    }
    bool canUse(BaseKnight * knight) {
        int hp = knight->getHP();
        int maxhp = knight->getmaxHP();
        if(hp < maxhp/3) return 1;
        else return 0;
    }
    void use (BaseKnight * knight) {
        int hp = knight->getHP();
        int maxhp = knight->getmaxHP();
        if(hp <= 0) knight->setHP(maxhp /3);
        else knight->setHP(hp+maxhp/4);
    }
};

class PhoenixdownIV: public BaseItem {
private:
    ItemType type;
    ItemType t;
public:
    PhoenixdownIV(){
        type = PHOENIXDOWN;
        t = PHOENIXDOWNIV;
    }
    ~PhoenixdownIV(){}
    ItemType getType() {
        return type;
    }
    ItemType getT() {
        return t;
    }
    bool canUse(BaseKnight * knight) {
        int hp = knight->getHP();
        int maxhp = knight->getmaxHP();
        if(hp < maxhp/2) return 1;
        else return 0;
    }
    void use (BaseKnight * knight) {
        int hp = knight->getHP();
        int maxhp = knight->getmaxHP();
        if(hp <= 0) knight->setHP(maxhp /2);
        else knight->setHP(hp+maxhp/5);
    }
};

class Events {
private:
    int *sk;
    int sl;
public:
    Events ( const string & file_events );
    ~Events();
    int count() const;
    int get(int i) const;
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;
public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &file_armyknights);
    void loadEvents(const string &file_events);
    void run();
};

#endif // __KNIGHT2_H__