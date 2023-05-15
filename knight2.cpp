#include "knight2.h"
bool trungdoc = 0;
bool omega = 0;
bool hades = 0;
bool untimecia = 0;
bool snt(int n) {
    if (n < 2) return 0;
    else if(n == 2) return 1;
    for(int i = 2; i < n; i++){
        if(n % i == 0) return 0;
    }
    return 1;
}
bool pyt(int n) {
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

/* * * BEGIN implementation of class BaseBag * * */
int BaseBag::count = 0;
bool BaseKnight::insertFirst(BaseItem * item) {
    if(knightType == DRAGON) {
        if (count >14) return 0;
    }
    if(knightType == LANCELOT) {
        if(count > 16) return 0;
    }
    if(knightType == NORMAL) {
        if(count > 19 ) return 0;
    }

    if(head == NULL){
        Node *temp = new Node;
        temp->item = item;
        temp->next = NULL;
        head = temp;
        count++;
    }
    else{
        Node *temp = new Node;
        temp->item = item;
        temp->next = head;
        head = temp;
        count++;
    }
    return 1;
}
BaseItem * BaseBag::get(ItemType itemType){
    Node *temp = head;
    while(temp != NULL) {
        if(temp->item->getType() == itemType) {
            return temp->item;
        }
        temp = temp->next;
    }
    return NULL;
}
BaseItem * BaseKnight::get(ItemType itemType){
    Node *temp = head;
    Node *pre = temp;
    while(temp != NULL) {
        if(temp->item->getType() == itemType) {
            pre->next = temp->next;
            BaseItem * item = temp->item;
            delete temp;
            return item;
        }
        pre = temp;
        temp = temp->next;
    }
    return NULL;
}

string BaseBag::toString() const {
    string s = "";
    Node *temp = head;
    s += "Bag[count=" + to_string(count) ;
    while(temp != NULL) {
        if(temp == head) s += ';';
        else s += ',';

        if(temp->item->getType() == ANTIDOTE) {
            s +="Antidote";
        }
        else if(temp->item->getT() == PHOENIXDOWNII) {
            s += "PhoenixdownII";
        }
        else if(temp->item->getT() == PHOENIXDOWNIII) {
            s += "PhoenixdownIII";
        }
        else {
            s += "PhoenixdownIV";
        }
        temp = temp->next;
    }
    s +=']';
    return s;
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseItem * * */
bool Antidote::canUse(BaseKnight * knight) {
    if (trungdoc = 1) return 1;
    else return 0;
    }
void Antidote::use(BaseKnight * knight) {
    int hp = knight->getHP();
    knight->setHP(hp+10);
    trungdoc = 0;
}

/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + "hp:" + to_string(hp) 
        + "maxhp:" + to_string(maxhp)
        + "level:" + to_string(level)
        + "gil:" + to_string(gil)
        + bag->toString()
        + "knight_type:" + typeString[knightType]
        + "]";
    return s;
}

BaseKnight::BaseKnight(){
    id =0; hp = 0; maxhp = 0;level = 0;gil = 0;
    antidote = 0; bag = NULL;knightType = NORMAL;
}

BaseKnight::~BaseKnight(){
    Node *temp = bag->getHead();
    Node *post = temp;
    while(temp != NULL){
        post = post->next;
        delete temp;
        temp = post;
    }
    bag->getHead();
}

BaseKnight * BaseKnight::create(int id,int maxhp,int level,int gil, int antidote, int phoenixdownI) {
    BaseKnight *a = new BaseKnight;
    a->id = id;
    a->hp = maxhp;
    a->maxhp = maxhp;
    a->level = level;
    a->gil = gil;
    a->antidote = antidote;
    a->bag = NULL;
    //phoenixdownI;
    if(maxhp == 888) a->knightType = LANCELOT;
    else if(pyt(maxhp)) a->knightType = DRAGON;
    else if(snt(maxhp)) a->knightType = PALADIN;
    else a->knightType = NORMAL;
    return a;
}

int BaseKnight::getLevel() { 
    return level;
}

int BaseKnight::getGil() { 
    return gil;
}

void BaseKnight::receiveGil(int &g) {
    gil += g;
    if(gil >999){
        g = gil - 999;
        gil = 999;
    }
    else g = 0;
}

int BaseKnight::getHP() {
    return hp;
}

void BaseKnight::setHP(int hp) {
    this->hp = hp;
}

void BaseKnight::setGil(int g) {
    gil = g;
}

int BaseKnight::getmaxHP() {
    return maxhp;
}

void BaseKnight::setLevel(int cong) {
    level += cong;
    if(level > 10) level = 10;
}

void BaseKnight::setAnti() {
    antidote--;
}

int BaseKnight::getAnti() {
    return antidote;
}
void BaseKnight::drop() {
    if(bag->count <= 3) {
        Node *temp =bag->getHead();
        Node *h = temp;
        while(temp != NULL) {
            h = temp->next;
            delete temp;
            temp = h;
        }
        bag->count = 0;
    }
    else {
        Node *temp =bag->getHead();
        Node *h = temp;
        for(int i = 0; i < 3 ; i++) {
            h = temp->next;
            delete temp;
            temp = h;
        }
        bag->sHead(h);
        bag->count -= 3;
    }
}
/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
int ArmyKnights::count() const {
    return sl;
}
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string('-', 50) << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}
int ArmyKnights::sl = 0;
ArmyKnights::ArmyKnights(const string &file_armyknights) {
    ifstream in;
    in.open(file_armyknights);
    in >> max;
    army = new BaseKnight *[max];
    for(int i = 0; i< max; i++){
        int hp,level,phoenixdownI,gil,antidote;
        in>>hp>>level >> phoenixdownI >>gil >> antidote;
        army[i]= BaseKnight::create(i+1,hp,level,gil,antidote,phoenixdownI);
    }
    sl = max;
    pa=0;gui=0;lan=0;sword = 0;
}
ArmyKnights::~ArmyKnights() {
    for(int i = 0;i < sl; i++){
        delete army[i];
    }
    delete [] army;
}
BaseKnight * ArmyKnights::lastKnight() const {
    if( sl == 1) return *army;
    else {
        return army[sl-1];
    }
}
bool ArmyKnights::hasGuinevereHair() const {
    if(gui) return 1;
    else return 0;
}
bool ArmyKnights::hasLancelotSpear() const {
    if(lan) return 1;
    else return 0;
}
bool ArmyKnights::hasExcaliburSword() const {
    if(sword) return 1;
    else return 0;
}
bool ArmyKnights::hasPaladinShield() const {
    if(pa) return 1;
    else return 0;
}   
int ArmyKnights::getmax() {
    return max;
}
void ArmyKnights::setPa() {
    pa = 1;
}
void ArmyKnights::setGui() {
    gui = 1;
}
void ArmyKnights::setLan() {
    lan = 1;
}
void ArmyKnights::setSword() {
    sword = 1;
}
BaseKnight * ArmyKnights::canReceive() {
    for(int i = sl -1; i >= 0; i--){
        if(army[i]->getGil() < 999) return army[i];
    }
    return NULL;
}

void ArmyKnights::setSL() {
    sl--;
}

void ArmyKnights::remove() {
    for(int i = 0;i < sl; i++){
        delete army[i];
    }
    delete [] army;
}

bool ArmyKnights::fight(BaseOpponent * opponent) {
    if(army[sl]->getHP() <= 0) return 0;
    else return 1;
}

bool ArmyKnights::adventure(Events * events) {
    if(untimecia) return 1;
    else return 0;
}

BaseKnight * ArmyKnights::lKnight(KnightType ktype) const {
    for(int i = count()-1 ;i >= 0; i--) {
        if( army[i]->getType() != ktype) return army[i];
    }
    return NULL;
}
/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class Events * * */
Events::Events(const string & file_events) {
    ifstream in;
    in.open(file_events);
    in >> sl;
    sk = new int [sl];
    for(int i = 0; i < sl; i++){
        int x;
        in >> x;
        sk[i] = x;
    }
}

Events::~Events() { 
    delete [] sk;
}

int Events::count() const {
    return sl;
}

int Events::get(int i) const {
    return sk[i];
}
/* * * END implementation of class Events * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

KnightAdventure::~KnightAdventure() {
    delete armyKnights;
    delete events;
}

void KnightAdventure::loadArmyKnights(const string &file_armyknights) {
    armyKnights = new ArmyKnights (file_armyknights);
}

void KnightAdventure::loadEvents(const string &file_events) {
    events = new Events (file_events);
}

void KnightAdventure::run() {
    int e = events->count();
    for(int i = 0; i < e; i++){
        int a = events->get(i);
        int levelO = (i+a)%10 +1;
        int level = armyKnights->lastKnight()->getLevel();
        int hp = armyKnights->lastKnight()->getHP();
        int maxhp = armyKnights->lastKnight()->getmaxHP();
        BaseOpponent * opponent;
        //1 
        if(a > 0 && a < 6) {
            if(a == 1) opponent = new MadBear;
            else if (a == 2) opponent = new Bandit;
            else if(a == 3 ) opponent = new LordLupin;
            else if(a == 4) opponent = new Elf;
            else opponent = new Troll;

            if(level >= levelO){
                int g = opponent->getGil();
                armyKnights->lastKnight()->receiveGil(g);
            }
            else {
                hp -= opponent->getBaseD() *(levelO - level);
                armyKnights->lastKnight()->setHP(hp);
            }
        }

        //6
        if(a == 6) {
            if(level >= levelO){
                armyKnights->lastKnight()->setLevel(1);
            }
            else {
                trungdoc = 1;
                if (armyKnights->lastKnight()->getAnti() > 0) {
                    armyKnights->lastKnight()->setAnti();
                }
                else {
                    armyKnights->lastKnight()->drop();
                    hp -= 10;
                    armyKnights->lastKnight()->setHP(hp);
                }
            }
        }

        //7
        if(a == 7) {
            if(level > levelO) {
                //codehere
                int g =armyKnights->lastKnight()->getGil();
                armyKnights->lastKnight()->receiveGil(g);
            }
            else {
                int g =armyKnights->lastKnight()->getGil();
                g /= 2;
                armyKnights->lastKnight()->setGil(g);
            }
        }

        //8
        if(a == 8) {
            int g =armyKnights->lastKnight()->getGil();
            if(g >= 50 && hp < maxhp /3) {
                hp += maxhp /5;
                g -= 50;
                armyKnights->lastKnight()->setGil(g);
                armyKnights->lastKnight()->setHP(hp);
            } 
        }
        
        //9
        if(a == 9) {
            armyKnights->lastKnight()->setHP(maxhp);
        }

        //10 
        if(a == 10) {
            if(omega) continue;
            if((level == 10 && hp == maxhp)||(armyKnights->lastKnight()->getType() == DRAGON) ) {
                armyKnights->lastKnight()->setGil(999);
                omega = 1;
            }
            else armyKnights->lastKnight()->setHP(0);
        }

        //11
        if(a == 11) {
            if (hades) continue;
            if (level == 10 || (level >= 8 && armyKnights->lastKnight()->getType() == PALADIN)) {
                hades = 1;
                armyKnights->setPa();
            }
            else armyKnights->lastKnight()->setHP(0);
        }

        //112
        if(a == 112) {
            BaseItem * item = new PhoenixdownII;
            armyKnights->lastKnight()->insertFirst(item);
        }

        //113
        if(a == 113) {
            BaseItem * item = new PhoenixdownIII;
            armyKnights->lastKnight()->insertFirst(item);
        }

        //114
        if(a == 114) {
            BaseItem * item = new PhoenixdownIV;
            armyKnights->lastKnight()->insertFirst(item);
        }

        //95
        if(a == 95) {
            armyKnights->setPa();
        }

        //96
        if(a == 96) {
            armyKnights->setLan();
        }

        //97
        if(a == 97) {
            armyKnights->setGui();
        }

        //98
        if(a == 98) {
            if(armyKnights->hasGuinevereHair() == 1 && armyKnights->hasLancelotSpear() == 1 && armyKnights->hasPaladinShield() == 1 )
            armyKnights->setSword();
        }

        //99
        if(a == 99) {
            if(armyKnights->hasExcaliburSword()) {
                untimecia = 1;
                continue;
            }
            else if(armyKnights->hasGuinevereHair() == 1 && armyKnights->hasLancelotSpear() == 1 && armyKnights->hasPaladinShield() == 1 ) {
                int HPO = 5000;
                while(armyKnights->count() > 0) {
                    //HPO -= armyKnights->lKnight(NORMAL); // code
                    if(HPO <= 0) untimecia = 1;
                }
                
            }
            else {
                armyKnights->remove();
            }
            
        }

        //hp < 0;
        if(hp < 0) {
        //tim do hoi hp
        }
        else if(armyKnights->lastKnight()->getGil() >=100) {
            armyKnights->lastKnight()->setGil(armyKnights->lastKnight()->getGil() -100);
            hp = armyKnights->lastKnight()->getmaxHP() / 2;
            armyKnights->lastKnight()->setHP(hp); 
        }
        else {
            delete armyKnights->lastKnight();
            armyKnights->setSL();
        }
        armyKnights->printInfo();
    }
    armyKnights->printResult(armyKnights->adventure(events));
}
/* * * END implementation of class KnightAdventure * * */