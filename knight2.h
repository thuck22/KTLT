#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
bool trungdoc = 0;
bool snt(int n){
    if (n < 2) return 0;
    else if(n == 2) return 1;
    for(int i = 2; i < n; i++){
        if(n % i == 0) return 0;
    }
    return 1;
}
bool pyt(int n){
    int a = n /100;
    n = n % 100;
    int b = n / 10;
    int c = n % 10;
    if( a == 0 || b == 0 || c == 0) return 0;
    if((a * a + b * b) == (c * c)) return 1;
    if((b * b + c * c) == ( a * a)) return 1;
    if((a* a + c * c) == ( b * b)) return 1;
    return 0;
}



enum ItemType {ANTIDOTE = 0 , PHOENIXDOWNI , PHOENIXDOWNII , PHOENIXDOWNIII , PHOENIXDOWNIV };
struct Bag{
        Bag *head = NULL;
        Bag *tail = NULL;
        BaseItem *data = NULL;
        static int count ;
};
class BaseBag:public BaseItem {
protected:
    Bag b;
public:
    BaseBag(){
        b.count = 0;
        b.data = NULL;
        b.head = NULL;
        b.tail = NULL;
    }
    virtual bool insertFirst(BaseItem * item){
        Bag *pNew = new Bag;
        pNew -> data = item;
        pNew ->count = b.count +1;
        pNew -> tail = b.head;
        b.head = pNew -> head;
    }
    virtual BaseItem * get(ItemType itemType){
        BaseItem *p = NULL;
        //codehere
    }
    virtual string toString() const;
    ~BaseBag(){
        Bag *p = new Bag;
        p = b.head;
        while(p != NULL){
            bag.head = p ->tail;
            delete p;
            p = bag.head;
        }
    }
};





class BaseOpponent{
    virtual int getGil() = 0;
    virtual int getbaseDamage() = 0;
};
class MadBear:public BaseOpponent{
private:
    int gil;
    int baseDamage;
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
private:
    int gil;
    int baseDamage;
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
private:
    int gil;
    int baseDamage;
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
private:
    int gil;
    int baseDamage;
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
private:
    int gil;
    int baseDamage;
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
class BaseKnight:public BaseBag {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    BaseBag * bag;
    KnightType knightType;

public:
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        BaseKnight *a;
        a -> id = id;
        a -> hp = maxhp;
        a -> maxhp = maxhp;
        a -> gil = gil;
        a -> antidote = antidote;
        a -> phoenixdownI = phoenixdownI;
        a -> level = level;
        a -> bag = NULL;
        return a;
    }
    string toString() const;
    void setAntidote(int antidote){
        this -> antidote = antidote;
    }
    int getAntidote() {
        return antidote;
    }
    int getHp(){
        return hp;
    }
    void setHp(int hp){
        this -> hp = hp;
    }
    int getMaxhp() {
        return maxhp;
    }
    int setKnightType(int maxhp,KnightType &knightType){
        if(snt(maxhp)) knightType = PALADIN;
        else if(maxhp == 888) knightType = LANCELOT;
        else if(pyt(maxhp)) knightType = DRAGON;
        else knightType = NORMAL;
    }
    BaseKnight(){id = 0; hp = 0; maxhp = 0; level = 0; gil = 0; antidote = 0;phoenixdownI = 0; knightType = NORMAL; bag = NULL;}
    ~BaseKnight(){
        delete bag;
    }
};

class PaladinKnight: public BaseKnight{


};
class LancelotKnight: public BaseKnight{

};
class DragonKnight: public BaseKnight{

};
class NormalKnight: public BaseKnight{

};




class ArmyKnights: protected BaseKnight,protected Events {
private:
    BaseKnight **army;
protected:
    static int n ;
public:
    ArmyKnights (const string & file_armyknights){
        ifstream in(file_armyknights);
        in >> n;
        string s;
        army = new BaseKnight * [n+1];
        for(int i = 0; i < n; i++){
            in >> maxhp >> level >> phoenixdownI >> gil >> antidote;
            army[i] = create(i+1,maxhp,level,gil,antidote,phoenixdownI);
        }
    }
    ~ArmyKnights(){
        for(int i = 0; i < n; i++){
            delete [] army[i];
        }
        delete [] army;
    }
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};





class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;

};
class Antidote: public BaseItem
{
private:
    bool canuse = 0;
public:
    Antidote(){}
    bool canUse (BaseKnight * knight){
        if(trungdoc) {
            return 1;
            canuse = 1;
        }
        else return 0;
    }
    void use(BaseKnight * knight){
        int a = knight -> getAntidote();
        if (canuse &&(a > 0)){ 
            knight -> setAntidote(a -1);
            trungdoc = 0;
        }
    }
    ~Antidote(){}
};
class PhoenixDownI: public BaseItem{
private:
    bool canuse = 0;
public:
    PhoenixDownI() {}
    bool canUse(BaseKnight * knight){
        if(knight -> getHp() <= 0) {
            return 1;
            canuse = 1;
        }
        else return 0;
    }
    void use(BaseKnight * knight){
        int a = knight -> getMaxhp();
        if(canuse) knight ->setHp(a);
    }
    ~PhoenixDownI() {}
};
class PhoenixDownII: public BaseItem{
private:
    bool canuse = 0;
public:
    PhoenixDownII() {}
    bool canUse(BaseKnight * knight){
        int a = knight -> getMaxhp();
        if(knight -> getHp() < a/4) {
            return 1;
            canuse = 1;
        }
        else return 0;
    }
    void use(BaseKnight * knight){
        int a = knight -> getMaxhp();
        if(canuse) knight ->setHp(a);
    }
    ~PhoenixDownII() {}
};
class PhoenixDownIII: public BaseItem{
private:
    bool canuse = 0;
public:
    PhoenixDownIII() {}
    bool canUse(BaseKnight * knight){
        int a = knight -> getMaxhp();
        if(knight -> getHp() < a/3) {
            return 1;
            canuse = 1;
        }
        else return 0;
    }
    void use(BaseKnight * knight){
        int a = knight -> getMaxhp();
        if(canuse && (knight ->getHp() <= 0)) knight ->setHp(a/3);
        else knight -> setHp(knight -> getHp() + a/4);
    }
    ~PhoenixDownIII() {}
};
class PhoenixDownIV: public BaseItem{
private:
    bool canuse = 0;
public:
    PhoenixDownIV() {}
    bool canUse(BaseKnight * knight){
        int a = knight -> getMaxhp();
        if(knight -> getHp() < a/2) {
            return 1;
            canuse = 1;
        }
        else return 0;
    }
    void use(BaseKnight * knight){
        int a = knight -> getMaxhp();
        if(canuse && (knight ->getHp() < 0)) knight ->setHp(a/2);
        else knight -> setHp(knight -> getHp() + a/5);
    }
    ~PhoenixDownIV() {}
};





class Events {
    int *sk;
    string s;
    int a;
public:
    int count() const;
    int get(int i) const;
    void event() const;
    Events (const string &file_events)
    {
        ifstream file;
        file.open(file_events);
        file >> a;
        sk = new int [a];
        getline(file,s);
        for(int i = 0; i < count(); i ++)
        {
            file >> sk[i];
        }
    }
    ~Events(){delete sk;}
};
int Events::count() const
{
    return a;
}
int Events::get(int i) const
{
    return sk[i-1];
}

//end class events






class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;
public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &){
        //todo
    }
    void loadEvents(const string &);
    void run();
};
#endif // __KNIGHT2_H__