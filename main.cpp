#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
//it works c++17 do dot try run this code in c++14

class color{
protected:
    int manaCost;
    char colorType;
public:
    color():manaCost(0),colorType('N'){}
    color(int mC,char ty):manaCost(mC),colorType(ty){}
    void setManaWc(int index){
        manaCost = index;
    }
    int getManaWc() const{
        return manaCost;
    }
    char getManaType() const{
        return colorType;
    }
    void setManaValue(int x){
        manaCost= x;
    }
};
color operator+(color c1,color c2){
    color sum;
    sum.setManaWc(c1.getManaWc() + c2.getManaWc());
    return sum;
}
color operator-(color c1,color c2){
    color sum;
    sum.setManaWc(c1.getManaWc() - c2.getManaWc());
    return sum;
}
std::ostream &operator<<(std::ostream &out , color c1){
    out << c1.getManaWc();
    return out;
}
class cards{
protected:
    std::string name;
    std::string colorOfCard ;
    int maxHP;
    int maxAttackPower;
    int baseHP;
    int attackPower;
    bool isItDestroyed ;
    char cardType ;
    bool isFirstStrikes;
    bool isTrample;
    bool isItTapped ;
    bool isDefender = false;
    std::vector<color> colorCost;
    int mana1 ;
    int mana2 ;
    int mana3 ;
    bool isItAttacked = false;
    bool effectedS = false;
    bool effectedUW = false;
    bool effectedR = false;
    bool effectedHL = false;
public:
    friend class effectsOfEnchantment;
    friend class effectsOfSorcery;
    cards(){
        name = "";
        colorOfCard = "";
        baseHP = 0;
        maxHP = baseHP;
        attackPower = 0;
        maxAttackPower = attackPower;
        isItDestroyed = false;
        isItTapped = false;
        isDefender = false;
        isTrample = false;
        isFirstStrikes = false;
        cardType = 'X';
        colorCost.reserve(3);
        mana1 = 0;
        mana2 = 0;
        mana3 = 0;
    }
    bool isEffectedS(){
        return effectedS;
    }
    bool isEffectedUW(){
        return effectedUW;
    }
    bool isEffectedR(){
        return effectedR;
    }
    bool isEffectedHL(){
        return effectedHL;
    }
    bool isAttackAnyCard(){
        return isItAttacked;
    }
    void makeUsed(){
        isItAttacked = true;
    }
    void makeUnUsed(){
        isItAttacked = false;
    }
    std::string getName(){
        return name;
    }
    char getCardType(){
        return cardType;
    }
    int getMana1(){
        return mana1;
    }
    int getMana2(){
        return mana2;
    }
    int getMana3(){
        return mana3;
    }
    virtual int getTotalManaCost(){
        int index=0;
        std::vector<color>::iterator cPtr;
        for (cPtr = colorCost.begin() ; cPtr < colorCost.end() ; cPtr++) {
            index +=cPtr->getManaWc();
        }
        return index;
    }
    bool learnIsDestroyed(){
        return isItDestroyed;
    }
    void makeDestroyed(){
        isItDestroyed = true;
    }
    void makeRevive(){
        isItDestroyed = false;
    }
    char learnManaTypes1(){
        return colorCost.at(0).getManaType();
    }
    char learnManaTypes2(){
        return colorCost.at(1).getManaType();
    }
    virtual int getBaseHP(){
        return baseHP;
    }
    virtual void setBaseHP(int index){
        baseHP = index;
    }
    virtual int getAttackPower(){
        return attackPower;
    }
    virtual void setAttackPower(int index){
        attackPower = index;
    }
    void makeTapped(){
        isItTapped = true;
    }
    void makeUntapped(){
        isItTapped = false;
    }
    bool learnTapped() {
        return isItTapped;
    }
    virtual void makeDefender(){
        makeUntapped();
        isDefender = true;
    }
    virtual void NOTMakeDefender(){
        makeUntapped();
        isDefender = false;
    }
    void makeAttacker(){
        makeTapped();
        isDefender = false;
    }
    bool learnIsItDefender(){
        bool checking = false;
        if(cardType == 'C'){
            if(isDefender){
                checking = true;
            }
        }
        return checking;
    }
    void resetCards() {
        attackPower = maxAttackPower;
        baseHP = maxHP;
    }
    bool isHaveFirstStrike(){
        return isFirstStrikes;
    }
    void setFirstStrike(bool x){
        isFirstStrikes = x;
    }
    bool isHaveTrample(){
        return isTrample;
    }
    void setTrample(bool x){
        isTrample = x;
    }
    std::string getColor(){
        return colorOfCard;
    }
    bool getDefender(){
        return isDefender;
    }
};
class landCards : public cards{
public:
    landCards(std::string Name,std::string CardColor,int m1,int m2,int m3,char t1,char t2){
        name = std::move(Name);
        colorOfCard = std::move(CardColor);
        baseHP = 0;
        maxHP = baseHP;
        attackPower = 0;
        maxAttackPower = attackPower;
        isItDestroyed = false;
        isItTapped = false;
        isDefender = false;
        isTrample = false;
        isFirstStrikes = false;
        cardType = 'L';
        mana1 = m1;
        mana2 = m2;
        mana3 = m3;
        colorCost.reserve(3);
        colorCost.emplace_back(mana1,t1);
        colorCost.emplace_back(mana2,t2);
        colorCost.emplace_back(mana3,'N');
    }
};
class creatureCards : public cards{
public:
    creatureCards(std::string Name,std::string CardColor,int m1,int m2,int m3,char t1,char t2,int bHP,int aP,bool fS,bool tRp){
        name = std::move(Name);
        colorOfCard = std::move(CardColor);
        baseHP = bHP;
        maxHP = baseHP;
        attackPower = aP;
        maxAttackPower = attackPower;
        isItDestroyed = false;
        isItTapped = false;
        isDefender = false;
        isTrample = tRp;
        isFirstStrikes = fS;
        cardType = 'C';
        mana1 = m1;
        mana2 = m2;
        mana3 = m3;
        colorCost.reserve(3);
        colorCost.emplace_back(mana1,t1);
        colorCost.emplace_back(mana2,t2);
        colorCost.emplace_back(mana3,'N');
    }
};

class effects{
protected:
    std::string cardName;
public:
    effects():cardName("non"){}
    effects(std::string cn):cardName(std::move(cn)){
    }
    void setName(std::string Name){
        cardName = std::move(Name);
    }
};
class effectsOfEnchantment : public effects{
public:
    friend class cards;
    effectsOfEnchantment():effects(){}
    effectsOfEnchantment(std::string cn):effects(std::move(cn)){}

public:
    void targetCreatureGainTrample(std::shared_ptr<std::vector<cards>> vec, int position){
        if (vec->at(position).getCardType() == 'C'){
            vec->at(position).setTrample(true);
            std::cout << vec->at(position).getName() << " gain First Strike." << std::endl;
        }
    }
    void targetCreatureLoseFirstStrike(std::shared_ptr<std::vector<cards>> vec, int position){
        if (vec->at(position).getCardType() == 'C'){
            vec->at(position).setFirstStrike(false);
            vec->at(position).effectedS= true;
            std::cout << vec->at(position).getName() << " lose First Strike." << std::endl;

        }
    }
    void allWhiteCreaturesGain11(std::shared_ptr<std::vector<cards>> vec,std::shared_ptr<std::vector<cards>> vec2){
        std::vector<cards>::iterator ptr;
        for(ptr=vec->begin();ptr < vec->end() ; ptr++){
            if ((ptr->getColor() == "White")&&(ptr->getCardType() == 'C')){
                ptr->maxAttackPower += 1 ;
                ptr->setAttackPower(ptr->getAttackPower()+ 1);
                ptr->setBaseHP(ptr->getBaseHP()+1);
                ptr->maxHP += 1;
                std::cout << ptr->getName() << " gain 1 aP 1 HP." << std::endl;
            }
        }
        std::vector<cards>::iterator ptr2;
        for(ptr2 = vec2->begin() ; ptr2 < vec2->end() ; ptr2++){
            if ((ptr2->getColor() == "White")&&(ptr2->getCardType() == 'C')){
                ptr2->setAttackPower(ptr2->getAttackPower()+ 1);
                ptr2->maxAttackPower += 1;
                ptr2->setBaseHP(ptr2->getBaseHP()+1);
                ptr2->maxHP += 1;
                std::cout << ptr2->getName() << " gain 1 aP 1 HP." << std::endl;
            }
        }
    }
    void allBlackCreaturesMinus11(std::shared_ptr<std::vector<cards>> vec,std::shared_ptr<std::vector<cards>> vec2){
        std::vector<cards>::iterator ptr;
        for(ptr=vec->begin();ptr < vec->end();ptr++){
            if ((ptr->getColor() == "Black") && (ptr->getCardType() == 'C')){
                ptr->setAttackPower(ptr->getAttackPower() - 1);
                ptr->maxAttackPower -= 1;
                ptr->setBaseHP(ptr->getBaseHP() - 1);
                ptr->maxHP -= 1;
                ptr->effectedHL = true;
                if(ptr->getBaseHP() <= 0){
                    ptr->makeDestroyed();
                    std::cout << ptr->getName() << " is dead." << std::endl;
                }
            }
        }
        std::vector<cards>::iterator ptr2;
        for(ptr2=vec2->begin();ptr2 < vec2->end();ptr2++){
            if ((ptr2->getColor() == "Black") && (ptr2->getCardType() == 'C')){
                ptr2->setAttackPower(ptr2->getAttackPower() - 1);
                ptr2->maxAttackPower -= 1;
                ptr2->setBaseHP(ptr2->getBaseHP() - 1);
                ptr2->maxHP -= 1;
                if(ptr2->getBaseHP() <= 0){
                    ptr2->makeDestroyed();
                    std::cout << ptr2->getName() << " is dead." << std::endl;
                }
            }
        }
    }
    void allBlackCreaturesGain20(std::shared_ptr<std::vector<cards>> vec,std::shared_ptr<std::vector<cards>> vec2){
        std::vector<cards>::iterator ptr;
        for(ptr=vec->begin();ptr < vec->end();ptr++){
            if ((ptr->getColor() == "Black")&& (ptr->getCardType() == 'C')){
                ptr->setAttackPower(ptr->getAttackPower() + 2);
                ptr->maxAttackPower +=2;
                ptr->effectedUW = true;
                std::cout << ptr->getName() << " gain 2 aP ." << std::endl;

            }
        }
        std::vector<cards>::iterator ptr2;
        for(ptr2=vec2->begin();ptr2 < vec2->end();ptr2++){
            if ((ptr2->getColor() == "Black")&& (ptr2->getCardType() == 'C')){
                ptr2->setAttackPower(ptr2->getAttackPower() + 2);
                ptr2->maxAttackPower += 2;
                ptr2->effectedUW = true;
                std::cout << ptr2->getName() << " gain 2 aP." << std::endl;
            }
        }
    }
    void allGreenCreaturesLoseTrample(std::shared_ptr<std::vector<cards>> vec,std::shared_ptr<std::vector<cards>> vec2){
        std::vector<cards>::iterator ptr;
        for(ptr=vec->begin();ptr < vec->end();ptr++){
            if ((ptr->getColor() == "Green")&&(ptr->getCardType() == 'C')){
                ptr->setTrample(false);
                ptr->effectedR = true;
                std::cout << ptr->getName() << " loses trample skill" << std::endl;
            }
        }
        std::vector<cards>::iterator ptr2;
        for(ptr2=vec->begin();ptr2 < vec->end();ptr2++){
            if ((ptr2->getColor() == "Green")&&(ptr2->getCardType() == 'C')){
                ptr2->setTrample(false);
                ptr2->effectedR = true;
                std::cout << ptr->getName() << " loses trample skill" << std::endl;
            }
        }
    }
};


class enchantmentCards: public cards , public effectsOfEnchantment{
public:
    enchantmentCards(std::string Name,std::string colorCards,int m1,int m2,int m3,char t1,char t2){
        name = std::move(Name);
        colorOfCard = std::move(colorCards);
        baseHP = 0;
        maxHP = baseHP;
        attackPower = 0;
        maxAttackPower = attackPower;
        isItDestroyed = false;
        isItTapped = false;
        isDefender = false;
        isTrample = false;
        isFirstStrikes = false;
        cardType = 'E';
        mana1 = m1;
        mana2 = m2;
        mana3 = m3;
        colorCost.reserve(3);
        colorCost.emplace_back(mana1,t1);
        colorCost.emplace_back(mana2,t2);
        colorCost.emplace_back(mana3,'N');
        cardName = name;
    }
};
class player{// buraya 4 tane vector eklencek daha eklemedim// deste,el,oyundaki kartalr , olu kartlar
protected:
    std::string PlayerName;
    int bHP = 15;
    bool alive;
    std::vector<color> colorCost;
    std::shared_ptr<std::vector<cards>> hand = std::make_shared<std::vector<cards>>();
    std::shared_ptr<std::vector<cards>> discard = std::make_shared<std::vector<cards>>();
    std::shared_ptr<std::vector<cards>> inPlay = std::make_shared<std::vector<cards>>();
    std::shared_ptr<std::vector<cards>> library = std::make_shared<std::vector<cards>>();
public:
    player():alive(true){}
    player(std::string playerName,std::shared_ptr<std::vector<cards>> hand1,std::shared_ptr<std::vector<cards>> discard1
            ,std::shared_ptr<std::vector<cards>> inPlay1,std::shared_ptr<std::vector<cards>> library1):PlayerName(std::move(playerName)){
        alive = true;
        for (int i = 0; i < (int)(hand1->size()); ++i) {
            hand->push_back(hand1->at(i));
        }
        for (int i = 0; i < (int)(library1->size()); ++i) {
            library->push_back(library1->at(i));
        }
        for (int i = 0; i < (int)(discard1->size()); ++i) {
            discard->push_back(discard1->at(i));
        }
        for (int i = 0; i < (int)(inPlay1->size()); ++i) {
            inPlay->push_back(inPlay1->at(i));
        }
        colorCost.reserve(5);
        colorCost.emplace_back(0,'G');
        colorCost.emplace_back(0,'L');
        colorCost.emplace_back(0,'R');
        colorCost.emplace_back(0,'W');
        colorCost.emplace_back(0,'B');
    }
    int getTotalManaP(){
        int index = 0;
        index += colorCost.at(0).getManaWc();
        index += colorCost.at(1).getManaWc();
        index += colorCost.at(2).getManaWc();
        index += colorCost.at(3).getManaWc();
        index += colorCost.at(4).getManaWc();
        return index;
    }
    void printWholeTotalMana(){
        std::cout << "Total mana of " << PlayerName << " : " <<std::endl;
        std::cout << "Green mana : " << getMana1() << std::endl;
        std::cout << "Blue mana : " << getMana2() << std::endl;
        std::cout << "Red mana : " << getMana3() << std::endl;
        std::cout << "White mana : " << getMana4() << std::endl;
        std::cout << "Black mana : " << getMana5() << std::endl;
    }
    int findHighestMana(){
        int index = 0;
        int biggestMana = colorCost.at(0).getManaWc();
        for (int i = 0; i < 5; ++i) {
            if(colorCost.at(i).getManaWc() >= biggestMana){
                biggestMana = colorCost.at(i).getManaWc();
                index = i;
            }
        }
        return index;
    }
    int getHighestMana(){
        return colorCost.at(findHighestMana()).getManaWc();
    }
    bool checkNonColorPayment(int index){
        bool checking = false;
        if(getTotalManaP() >= index){
            if(getHighestMana() - index >= 0){
                checking = true;
            }
            else{
                int manaCO = getHighestMana() - index;
                for (int i = 0; i < 5; ++i) {
                    if (i == findHighestMana()){
                        continue;
                    }
                    else if (colorCost.at(i).getManaWc() + manaCO >= 0){
                        checking = true;
                    }
                    else{
                        manaCO += colorCost.at(i).getManaWc();
                    }
                }
            }
        }
        else {
            checking = false;
        }
        return checking;
    }
    void takeNonColorPayment(int index){
        if(getHighestMana() - index >= 0){
            colorCost.at(findHighestMana()).setManaWc(getHighestMana() - index);
        }
        else{
            colorCost.at(findHighestMana()).setManaWc(getHighestMana() - index);
            int manaCO = colorCost.at(findHighestMana()).getManaWc();
            for (int i = 0; i < 5; ++i) {
                if (i == findHighestMana()){
                    continue;
                }
                else{
                    colorCost.at(i).setManaWc(colorCost.at(i).getManaWc() + manaCO);
                }
            }
        }
    }
    void resetMana(){
        colorCost.at(0).setManaWc(0);
        colorCost.at(1).setManaWc(0);
        colorCost.at(2).setManaWc(0);
        colorCost.at(3).setManaWc(0);
        colorCost.at(4).setManaWc(0);
    }

    void plusSetColorManaWithChar(int mana, char index){
        if(index == 'G'){
            colorCost.at(0).setManaWc((getMana1() + mana));
        }
        else if (index == 'L'){
            colorCost.at(1).setManaWc(getMana2()+  mana);
        }
        else if (index == 'R'){
            colorCost.at(2).setManaWc(getMana3() + mana);
        }
        else if (index == 'W'){
            colorCost.at(3).setManaWc(getMana4() + mana);
        }
        else if (index == 'B'){
            colorCost.at(4).setManaWc(getMana5() + mana);
        }
    }
    void minusSetColorManaWithChar(int mana, char index){
        if(index == 'G'){
            colorCost.at(0).setManaValue(getMana1() - mana);
        }
        else if (index == 'L'){
            colorCost.at(1).setManaValue(getMana2() -  mana);
        }
        else if (index == 'R'){
            colorCost.at(2).setManaValue(getMana3() - mana);
        }
        else if (index == 'W'){
            colorCost.at(3).setManaValue(getMana4() - mana);
        }
        else if (index == 'B'){
            colorCost.at(4).setManaValue(getMana5() - mana);
        }
    }
    void refreshWholeCards(std::shared_ptr<std::vector<cards>> hand1,std::shared_ptr<std::vector<cards>> discard1
            ,std::shared_ptr<std::vector<cards>> inPlay1,std::shared_ptr<std::vector<cards>> library1){
        hand->clear();
        library->clear();
        discard->clear();
        inPlay->clear();
        for (int i = 0; i < (int)(hand1->size()); ++i) {
            hand->push_back(hand1->at(i));
        }
        for (int i = 0; i < (int)(library1->size()); ++i) {
            library->push_back(library1->at(i));
        }
        for (int i = 0; i < (int)(discard1->size()); ++i) {
            discard->push_back(discard1->at(i));
        }
        for (int i = 0; i < (int)(inPlay1->size()); ++i) {
            inPlay->push_back(inPlay1->at(i));
        }
    }
    void setPlayerHP(int x){
        bHP = x;
    }
    int getPlayerHp(){
        return bHP;
    }
    void makeLoser(){
        alive = false;
    }
    void printHand(){
        std::cout << "Cards that are in the hand : " << std::endl;
        for (int i = 0; i < (int)(hand->size()); i++) {
            if(hand->at(i).getCardType() == 'C'){
                std::cout << "Creature Card:" << std::endl;
                std::cout << "Name : "<< i << " "  << hand->at(i).getName() << " Color : " << hand->at(i).getColor() << " AttackPower / Hp : " << hand->at(i).getAttackPower()<< "/" << hand->at(i).getBaseHP() ;
                std::cout<< " /Mana Cost : ";
                if(hand->at(i).getMana3() > 0){
                    std::cout<< hand->at(i).getMana3() ;
                }
                if(hand->at(i).getMana1() > 0){
                    for (int j = 0; j < hand->at(i).getMana1(); j++) {
                        std::cout<< hand->at(i).learnManaTypes1() ;
                    }
                }
                if(hand->at(i).getMana2() > 0){
                    for (int j = 0; j < hand->at(i).getMana2(); j++) {
                        std::cout<< hand->at(i).learnManaTypes2() ;
                    }
                }
                std::cout<< std::endl;
            }
            else if(hand->at(i).getCardType() == 'L'){
                std::cout << "Land Card:" << std::endl;
                std::cout << "Name : "<< i << " "  << hand->at(i).getName() << "  Color  " << hand->at(i).getColor() << "  / Given Mana Color: " << hand->at(i).learnManaTypes1()<< " Given Mana " << hand->at(i).getTotalManaCost() << std::endl;
            }
            else if(hand->at(i).getCardType() == 'S'){
                std::cout << "Sorcery Card:" << std::endl;
                std::cout << "Name : "<< i << " " << hand->at(i).getName() << "  Color  " << hand->at(i).getColor() ;
                std::cout<< " /Mana Cost : ";
                if(hand->at(i).getMana3() > 0){
                    std::cout<< hand->at(i).getMana3() ;
                }
                if(hand->at(i).getMana1() > 0){
                    for (int j = 0; j < hand->at(i).getMana1(); j++) {
                        std::cout<< hand->at(i).learnManaTypes1() ;
                    }
                }
                if(hand->at(i).getMana2() > 0){
                    for (int j = 0; j < hand->at(i).getMana2(); j++) {
                        std::cout<< hand->at(i).learnManaTypes2() ;
                    }
                }
                std::cout<< std::endl;
            }
            else if(hand->at(i).getCardType() == 'E'){
                std::cout << "Enchantment Card:" << std::endl;
                std::cout << "Name : "<< i << " " << hand->at(i).getName() << "  Color  " << hand->at(i).getColor() ;
                std::cout<< " /Mana Cost : ";
                if(hand->at(i).getMana3() > 0){
                    std::cout<< hand->at(i).getMana3() ;
                }
                if(hand->at(i).getMana1() > 0){
                    for (int j = 0; j < hand->at(i).getMana1(); j++) {
                        std::cout<< hand->at(i).learnManaTypes1() ;
                    }
                }
                if(hand->at(i).getMana2() > 0){
                    for (int j = 0; j < hand->at(i).getMana2(); j++) {
                        std::cout<< hand->at(i).learnManaTypes2() ;
                    }
                }
                std::cout<< std::endl;
            }
        }
    }
    void printInPlay(){
        std::cout << "Cards that are in the inPlay : " << std::endl;
        for (int i = 0; i < (int)(inPlay->size()); i++) {
            if(inPlay->at(i).getCardType() == 'C'){
                std::cout << "Creature Card:" << std::endl;
                std::cout << "Name : " << i << " " << inPlay->at(i).getName() << "  /Color  " << inPlay->at(i).getColor() << " A/Hp : " << inPlay->at(i).getAttackPower() << "/" << inPlay->at(i).getBaseHP() ;
                std::cout<< " /Mana Cost : ";
                if(inPlay->at(i).getMana3() > 0){
                    std::cout << inPlay->at(i).getMana3() ;
                }
                if(inPlay->at(i).getMana1() > 0){
                    for (int j = 0; j < inPlay->at(i).getMana1(); j++) {
                        std::cout << inPlay->at(i).learnManaTypes1() ;
                    }
                }
                if(inPlay->at(i).getMana2() > 0){
                    for (int j = 0; j < inPlay->at(i).getMana2(); j++) {
                        std::cout << inPlay->at(i).learnManaTypes2() ;
                    }
                }
                std::cout<< std::endl;
            }
            else if(inPlay->at(i).getCardType() == 'L'){
                std::cout << "Land Card:" << std::endl;
                std::cout << "Name : " << i << " " << inPlay->at(i).getName() << "  Color  " << inPlay->at(i).getColor() << "  /Given Mana Color: " << inPlay->at(i).learnManaTypes1() << " Given Mana " << inPlay->at(i).getTotalManaCost() << std::endl;
            }
            else if(inPlay->at(i).getCardType() == 'S'){
                std::cout << "Sorcery Card:" << std::endl;
                std::cout << "Name : " << i << " " << inPlay->at(i).getName() << "  Color  " << inPlay->at(i).getColor() ;
                std::cout<< " /Mana Cost : ";
                if(inPlay->at(i).getMana3() > 0){
                    std::cout << inPlay->at(i).getMana3() ;
                }
                if(inPlay->at(i).getMana1() > 0){
                    for (int j = 0; j < inPlay->at(i).getMana1(); j++) {
                        std::cout << inPlay->at(i).learnManaTypes1() ;
                    }
                }
                if(inPlay->at(i).getMana2() > 0){
                    for (int j = 0; j < inPlay->at(i).getMana2(); j++) {
                        std::cout << inPlay->at(i).learnManaTypes2() ;
                    }
                }
                std::cout<< std::endl;
            }
            else if(inPlay->at(i).getCardType() == 'E'){
                std::cout << "Enchantment Card:" << std::endl;
                std::cout << "Name : " << i << " " << inPlay->at(i).getName() << "  Color  " << inPlay->at(i).getColor() ;
                std::cout<< " /Mana Cost : ";
                if(inPlay->at(i).getMana3() > 0){
                    std::cout << inPlay->at(i).getMana3() ;
                }
                if(inPlay->at(i).getMana1() > 0){
                    for (int j = 0; j < inPlay->at(i).getMana1(); j++) {
                        std::cout << inPlay->at(i).learnManaTypes1() ;
                    }
                }
                if(inPlay->at(i).getMana2() > 0){
                    for (int j = 0; j < inPlay->at(i).getMana2(); j++) {
                        std::cout << inPlay->at(i).learnManaTypes2() ;
                    }
                }
                std::cout<< std::endl;
            }
        }
    }
    void printDiscard(){
        std::cout << "Cards that are in the discard : " << std::endl;
        for (int i = 0; i < (int)(discard->size()); i++) {
            if(discard->at(i).getCardType() == 'C'){
                std::cout << "Creature Card:" << std::endl;
                std::cout << "Name : " << i << " " << discard->at(i).getName() << "  /Color  " << discard->at(i).getColor() << " A/Hp : " << discard->at(i).getAttackPower() << "/" << discard->at(i).getBaseHP() ;
                std::cout<< " /Mana Cost : ";
                if(discard->at(i).getMana3() > 0){
                    std::cout << discard->at(i).getMana3() ;
                }
                if(discard->at(i).getMana1() > 0){
                    for (int j = 0; j < discard->at(i).getMana1(); j++) {
                        std::cout << discard->at(i).learnManaTypes1() ;
                    }
                }
                if(discard->at(i).getMana2() > 0){
                    for (int j = 0; j < discard->at(i).getMana2(); j++) {
                        std::cout << discard->at(i).learnManaTypes2() ;
                    }
                }
                std::cout<< std::endl;
            }
            else if(discard->at(i).getCardType() == 'L'){
                std::cout << "Land Card:" << std::endl;
                std::cout << "Name : " << i << " " << discard->at(i).getName() << "  Color  " << discard->at(i).getColor() << "  /Given Mana Color: " << discard->at(i).learnManaTypes1() << " Given Mana " << discard->at(i).getTotalManaCost() << std::endl;
            }
            else if(discard->at(i).getCardType() == 'S'){
                std::cout << "Sorcery Card:" << std::endl;
                std::cout << "Name : " << i << " " << discard->at(i).getName() << "  Color  " << discard->at(i).getColor() ;
                std::cout<< " /Mana Cost : ";
                if(discard->at(i).getMana3() > 0){
                    std::cout << discard->at(i).getMana3() ;
                }
                if(discard->at(i).getMana1() > 0){
                    for (int j = 0; j < discard->at(i).getMana1(); j++) {
                        std::cout << discard->at(i).learnManaTypes1() ;
                    }
                }
                if(discard->at(i).getMana2() > 0){
                    for (int j = 0; j < discard->at(i).getMana2(); j++) {
                        std::cout << discard->at(i).learnManaTypes2() ;
                    }
                }
                std::cout<< std::endl;
            }
            else if(discard->at(i).getCardType() == 'E'){
                std::cout << "Enchantment Card:" << std::endl;
                std::cout << "Name : " << i << " " << discard->at(i).getName() << "  Color  " << discard->at(i).getColor() ;
                std::cout<< " /Mana Cost : ";
                if(discard->at(i).getMana3() > 0){
                    std::cout << discard->at(i).getMana3() ;
                }
                if(discard->at(i).getMana1() > 0){
                    for (int j = 0; j < discard->at(i).getMana1(); j++) {
                        std::cout << discard->at(i).learnManaTypes1() ;
                    }
                }
                if(discard->at(i).getMana2() > 0){
                    for (int j = 0; j < discard->at(i).getMana2(); j++) {
                        std::cout << discard->at(i).learnManaTypes2() ;
                    }
                }
                std::cout<< std::endl;
            }
        }
    }
    std::string getPlayerName(){
        return PlayerName;
    }
    bool isAlive(){
        return alive;
    }
    int getMana1(){
        return colorCost.at(0).getManaWc();
    }
    int getMana2(){
        return colorCost.at(1).getManaWc();
    }
    int getMana3(){
        return colorCost.at(2).getManaWc();
    }
    int getMana4(){
        return colorCost.at(3).getManaWc();
    }
    int getMana5(){
        return colorCost.at(4).getManaWc();
    }

};
class effectsOfSorcery : public effects{
public:
    friend class cards;
    effectsOfSorcery():effects(){}
    effectsOfSorcery(std::string cardNAME):effects(std::move(cardNAME)){}
public:
    void DisenchantEffect(std::shared_ptr<std::vector<cards>> vecL , std::shared_ptr<std::vector<cards>> vecD, int position){
        if (vecL->at(position).getCardType() == 'E'){
            vecL->at(position).makeDestroyed();
            std::cout << vecL->at(position).getName() << " is dead." << std::endl;
            if(vecL->at(position).getName() == "Unholy War"){
                for (int i = 0; i < (int)(vecL->size()); ++i) {
                    if(vecL->at(i).isEffectedUW()){
                        vecL->at(i).setAttackPower(vecL->at(i).getAttackPower() - 2);
                        vecL->at(i).maxAttackPower -= 2;
                        vecL->at(i).effectedUW = false;
                    }
                }
                for (int i = 0; i < (int)(vecD->size()); ++i) {
                    if(vecD->at(i).isEffectedUW()){
                        vecD->at(i).setAttackPower(vecD->at(i).getAttackPower() - 2);
                        vecD->at(i).maxAttackPower -=2;
                        vecD->at(i).effectedUW = false;
                    }
                }
            }
            if(vecL->at(position).getName() == "Restrain"){
                for (int i = 0; i < (int)(vecL->size()); ++i) {
                    if(vecL->at(i).isEffectedR()){
                        vecL->at(i).setTrample(true);
                        vecL->at(i).effectedR = false;
                    }
                }
                for (int i = 0; i < (int)(vecD->size()); ++i) {
                    if(vecD->at(i).isEffectedR()){
                        vecD->at(i).setTrample(true);
                        vecD->at(i).effectedR = false;
                    }
                }
            }
            if(vecL->at(position).getName() == "Slow"){
                for (int i = 0; i < (int)(vecD->size()); ++i) {
                    if(vecD->at(i).isEffectedS()){
                        vecD->at(i).setFirstStrike(true);
                        vecD->at(i).effectedS = false;
                    }
                }
                for (int i = 0; i < (int)(vecL->size()); ++i) {
                    if(vecL->at(i).isEffectedS()){
                        vecL->at(i).setFirstStrike(true);
                        vecL->at(i).effectedS = false;
                    }
                }
            }
        }
        else{
            std::cout << "Invalid Index !!!" << std::endl;
        }
    }
    void terrorEffect(std::shared_ptr<std::vector<cards>> vec, int position){
        if (vec->at(position).getCardType() == 'C'){
            vec->at(position).makeDestroyed();
            std::cout << vec->at(position).getName() << " is dead." << std::endl;
        }
        else{
            std::cout << "Invalid Index !!!" << std::endl;
        }
    }
    void floodEffect(std::shared_ptr<std::vector<cards>> vec, int position){
        if (vec->at(position).getCardType() == 'L'){
            vec->at(position).makeDestroyed();
            std::cout << vec->at(position).getName() << " is dead." << std::endl;
        }
        else{
            std::cout << "Invalid Index !!!" << std::endl;
        }
    }
    void LightningBoltEffect(std::shared_ptr<std::vector<cards>> vec, int position){
        if (vec->at(position).getCardType() == 'C'){
            vec->at(position).setBaseHP(vec->at(position).getBaseHP() - 2);
            if(vec->at(position).getBaseHP() <= 0){
                vec->at(position).makeDestroyed();
                std::cout << vec->at(position).getName() << " is dead." << std::endl;
            }
        }
        else{
            std::cout << "Invalid Index !!!" << std::endl;
        }
    }
    void LightningBoltEffect(std::shared_ptr<player> player){
        player->setPlayerHP(player->getPlayerHp() - 2);
        if (player->getPlayerHp() <= 0){
            player->makeLoser();
        }
    }
    void PlagueEffect(std::shared_ptr<std::vector<cards>> vec){
        std::vector<cards>::iterator ptr;
        for(ptr=vec->begin();ptr < vec->end();ptr++){
            if (ptr->getCardType() == 'C'){
                ptr->setBaseHP(ptr->getBaseHP() - 1);
                if(ptr->getBaseHP() <= 0){
                    ptr->makeDestroyed();
                    std::cout << ptr->getName() << " is dead." << std::endl;
                }
            }
        }
    }
    void ReanimateCardEffect(std::shared_ptr<std::vector<cards>> discard,std::shared_ptr<std::vector<cards>> hand,int index){
        if((0 <= index) && (index < discard->size())){
            discard->at(index).makeRevive();
            std::cout << "You Revived " << discard->at(index).getName()<< std::endl;
            for (int i = 0; i < (int)(discard->size()); ++i) {
                if(discard->at(i).isEffectedUW()){
                    discard->at(i).setAttackPower(discard->at(i).getAttackPower() - 2);
                    discard->at(i).maxAttackPower -=2;
                    discard->at(i).effectedUW = false;
                }
                if(discard->at(i).isEffectedR()){
                    discard->at(i).setTrample(true);
                    discard->at(i).effectedR = false;
                }
                if(discard->at(i).isEffectedS()){
                    discard->at(i).setFirstStrike(true);
                    discard->at(i).effectedS = false;
                }
                if(discard->at(i).isEffectedHL()){
                    discard->at(i).setAttackPower(discard->at(i).getAttackPower() + 1);
                    discard->at(i).maxAttackPower +=1;
                    discard->at(i).setBaseHP(discard->at(i).getBaseHP() + 1);
                    discard->at(i).maxHP +=1;
                    discard->at(i).effectedHL = false;
                }
            }
            discard->at(index).makeUnUsed();
            discard->at(index).resetCards();
            discard->at(index).makeUntapped();
            discard->at(index).NOTMakeDefender();
            hand->emplace_back(discard->at(index));
            auto ptr = discard->begin() + index;
            discard->erase(ptr);
        }
        else{
            std::cout << "Invalid Index !!!" << std::endl;
        }
    }
};
class sorceryCards : public cards , public effectsOfSorcery{
public:
    sorceryCards(std::string Name, std::string colorCards, int m1, int m2, int m3, char t1, char t2){
        name = std::move(Name);
        colorOfCard = std::move(colorCards);
        baseHP = 0;
        maxHP = baseHP;
        attackPower = 0;
        maxAttackPower = attackPower;
        isItDestroyed = false;
        isItTapped = false;
        isDefender = false;
        isTrample = false;
        isFirstStrikes = false;
        cardType = 'S';
        mana1 = m1;
        mana2 = m2;
        mana3 = m3;
        colorCost.reserve(3);
        colorCost.emplace_back(mana1,t1);
        colorCost.emplace_back(mana2,t2);
        colorCost.emplace_back(mana3,'N');
        cardName = name;
    }
};

void attackPlayer(std::shared_ptr<player> Player, int damage){
    Player->setPlayerHP(Player->getPlayerHp() - damage);
}
void attackWithCreature(std::shared_ptr<std::vector<cards>> inPLayAttacker,int attackerLoc,std::shared_ptr<std::vector<cards>> inPLayDefender
        ,int defenderLoc,std::shared_ptr<player> playerDefender,std::shared_ptr<player> playerAttacker){
    std::vector<cards>::iterator attacker;
    attacker = inPLayAttacker->begin() + attackerLoc;
    std::vector<cards>::iterator defender;
    defender = inPLayDefender->begin() + defenderLoc;
    if (attacker->isHaveFirstStrike() && !defender->isHaveFirstStrike()){
        std::cout << attacker->getName() << " attacked to " << defender->getName() << "." << std::endl;
        defender->setBaseHP(defender->getBaseHP() - attacker->getAttackPower());
        if (defender->getBaseHP() < 0){
            std::cout << defender->getName() <<" has died." << std::endl;
            std::cout << attacker->getName() <<" has " << attacker->getBaseHP() << " HP." << std::endl;
            defender->makeDestroyed();
            if (attacker->isHaveTrample()){
                std::cout << attacker->getName() <<" attacked to the " << playerDefender->getPlayerName() << "." << std::endl;
                playerDefender->setPlayerHP(playerDefender->getPlayerHp() + defender->getBaseHP());
                if (playerDefender->getPlayerHp() > 0){
                    std::cout << playerDefender->getPlayerName() <<" has " << playerDefender->getPlayerHp() << " HP." << std::endl;
                }
                else {
                    std::cout << playerDefender->getPlayerName() <<" has died. " << playerAttacker->getPlayerName() <<" won the game with " << playerAttacker->getPlayerHp() << " HP." << std::endl;
                    playerDefender->makeLoser();
                }
            }
        }
        else if (defender->getBaseHP() == 0){
            std::cout << defender->getName() <<" has died." << std::endl;
            std::cout << attacker->getName() << " has " << attacker->getBaseHP() << " HP." << std::endl;
            defender->makeDestroyed();
        }
        else {
            std::cout << defender->getName() << " has " << defender->getBaseHP() << " HP." << std::endl;
            std::cout << defender->getName() << " attacked to "<< attacker->getName() << "." << std::endl;
            attacker->setBaseHP(attacker->getBaseHP() - defender->getAttackPower());// def attack to def
            if (attacker->getBaseHP() > 0){
                std::cout << attacker->getName() << " has " << attacker->getBaseHP() << " HP." << std::endl;
            }
            else{
                std::cout << attacker->getName() <<" has died." << std::endl;
                attacker->makeDestroyed();
            }
        }
    }
    else if (!attacker->isHaveFirstStrike() && defender->isHaveFirstStrike()){
        std::cout << defender->getName() << " attacked to " << attacker->getName() << "." << std::endl;
        attacker->setBaseHP(attacker->getBaseHP() - defender->getAttackPower());// def attack to def
        if (attacker->getBaseHP() > 0){
            std::cout << attacker->getName() <<" has " << attacker->getBaseHP() << " HP." << std::endl;
            std::cout << attacker->getName() <<" attacked to "<< defender->getName() << "." << std::endl;
            defender->setBaseHP(defender->getBaseHP() - attacker->getAttackPower());// att attack to def
            if (defender->getBaseHP() < 0){
                std::cout << defender->getName() << " has died." << std::endl;
                defender->makeDestroyed();
                if (attacker->isHaveTrample()){
                    std::cout << attacker->getName() <<" attacked to the " << playerDefender->getPlayerName() << "." << std::endl;
                    playerDefender->setPlayerHP(playerDefender->getPlayerHp() + defender->getBaseHP());
                    if (playerDefender->getPlayerHp() > 0){
                        std::cout << playerDefender->getPlayerName() <<" has " << playerDefender->getPlayerHp() << " HP." << std::endl;
                    }
                    else{
                        std::cout << playerDefender->getPlayerName() <<" has died. "<< playerAttacker->getPlayerName() << " won the game with " << playerAttacker->getPlayerHp() << " HP." << std::endl;
                        playerDefender->makeLoser();
                    }
                }
            }
            else if (defender->getBaseHP() == 0){
                std::cout << defender->getName() <<" has died." << std::endl;
                defender->makeDestroyed();
            }
            else{
                std::cout << defender->getName() << " has " << defender->getBaseHP() << " HP." << std::endl;
            }
        }
        else{
            std::cout << attacker->getName() << " has died." << std::endl;
            std::cout << defender->getName() <<" has " << defender->getBaseHP() << " HP." << std::endl;
            attacker->makeDestroyed();
        }
    }
    else {
        std::cout << attacker->getName() << " and "<< defender->getName() <<" attacked each other." << std::endl;
        attacker->setBaseHP(attacker->getBaseHP() - defender->getAttackPower());// def attack to def
        defender->setBaseHP(defender->getBaseHP() - attacker->getAttackPower());
        if (defender->getBaseHP() < 0){
            std::cout << defender->getName() <<" has died." << std::endl;
            defender->makeDestroyed();
            if (attacker->getBaseHP() > 0){
                std::cout << attacker->getName() <<" has " << attacker->getBaseHP() << " HP." << std::endl;
                if (attacker->isHaveTrample()){
                    std::cout << attacker->getName() <<" attacked to the "<< playerDefender->getPlayerName() <<"."<< std::endl;
                    playerDefender->setPlayerHP(playerDefender->getPlayerHp() + defender->getBaseHP());
                    if (playerDefender->getPlayerHp() > 0){
                        std::cout << playerDefender->getPlayerName() <<" has " << playerDefender->getPlayerHp() << " HP." << std::endl;
                    }
                    else{
                        std::cout << playerDefender->getPlayerName() <<" has died. "<< playerAttacker->getPlayerName() << " won the game with " << playerAttacker->getPlayerHp() << " HP." << std::endl;
                        playerDefender->makeLoser();
                    }
                }
            }
            else {
                std::cout << attacker->getName() <<" has died." << std::endl;
                attacker->makeDestroyed();
                if (attacker->isHaveTrample()){
                    std::cout << attacker->getName() <<" attacked to the "<< playerDefender->getPlayerName() <<" before its dies." << std::endl;
                    playerDefender->setPlayerHP(playerDefender->getPlayerHp() + defender->getBaseHP());
                    if (playerDefender->getPlayerHp() > 0){
                        std::cout << playerDefender->getPlayerName() <<" has " << playerDefender->getPlayerHp() << " HP." << std::endl;
                    }
                    else{
                        std::cout << playerDefender->getPlayerName() <<" has died. "<< playerAttacker->getPlayerName() << " won the game with " << playerAttacker->getPlayerHp() << " HP." << std::endl;
                        playerDefender->makeLoser();
                    }
                }
            }
        }
        else if (defender->getBaseHP() == 0){
            std::cout <<defender->getName() <<" has died." << std::endl;
            defender->makeDestroyed();
            if (attacker->getBaseHP() > 0) {
                std::cout << attacker->getName() <<" has " << attacker->getBaseHP() << " HP." << std::endl;
            }
            else{
                std::cout << attacker->getName()  <<" has died." << std::endl;
                attacker->makeDestroyed();
            }
        }
        else{
            std::cout << defender->getName() <<" has " << defender->getBaseHP() << " HP." << std::endl;
            if (attacker->getBaseHP() > 0){
                std::cout << attacker->getName() <<" has " << attacker->getBaseHP() << " HP." << std::endl;
            }
            else{
                std::cout << attacker->getName() <<" has died." << std::endl;
                attacker->makeDestroyed();
            }
        }
    }
}

void makeWholeUntapped(std::shared_ptr<std::vector<cards>> hand1,std::shared_ptr<std::vector<cards>> discard1
        ,std::shared_ptr<std::vector<cards>> inPlay1,std::shared_ptr<std::vector<cards>> library1){
    for (int i = 0; i < (int)(hand1->size()); ++i) {
        hand1->at(i).makeUntapped();
        hand1->at(i).NOTMakeDefender();
        hand1->at(i).makeUnUsed();
    }
    for (int i = 0; i < (int)(discard1->size()); ++i) {
        discard1->at(i).makeUntapped();
        discard1->at(i).NOTMakeDefender();
        discard1->at(i).makeUnUsed();
    }
    for (int i = 0; i < (int)(inPlay1->size()); ++i) {
        inPlay1->at(i).makeUntapped();
        inPlay1->at(i).NOTMakeDefender();
        inPlay1->at(i).makeUnUsed();
    }
    for (int i = 0; i < (int)(library1->size()); ++i) {
        library1->at(i).makeUntapped();
        library1->at(i).NOTMakeDefender();
        library1->at(i).makeUnUsed();
    }
}
void resetAttacker(std::shared_ptr<std::vector<cards>> inPlay1){
    for (int i = 0; i < (int)(inPlay1->size()); ++i) {
        inPlay1->at(i).makeUnUsed();
    }
}
bool checkAreThereAnyDefender(std::shared_ptr<std::vector<cards>> vec){
    bool checking = false;
    for (int i = 0; i < (int)(vec->size()); ++i) {
        if (vec->at(i).learnIsItDefender()){
            checking = true;
        }
    }
    return checking;
}
void goToDiscard(std::shared_ptr<std::vector<cards>> inPlayy,std::shared_ptr<std::vector<cards>> discardd){
    for (int i = 0; i < (int)(inPlayy->size()); ++i) {
        if(inPlayy->at(i).learnIsDestroyed()){
            discardd->push_back(inPlayy->at(i));
            auto ptrX = inPlayy->begin() + i;
            inPlayy->erase(ptrX);
        }
    }
}

int main() {
    int round = 1;
    effectsOfEnchantment enchantmentEffects;
    effectsOfSorcery sorceryEffects;
    std::shared_ptr<std::vector<cards>> libraryDark = std::make_shared<std::vector<cards>>();
    std::shared_ptr<std::vector<cards>> handDark = std::make_shared<std::vector<cards>>();
    handDark->reserve(7);
    std::shared_ptr<std::vector<cards>> inPLayDark = std::make_shared<std::vector<cards>>();
    std::shared_ptr<std::vector<cards>> discardDark = std::make_shared<std::vector<cards>>();

    std::shared_ptr<std::vector<cards>> libraryLight = std::make_shared<std::vector<cards>>();
    std::shared_ptr<std::vector<cards>> handLight = std::make_shared<std::vector<cards>>();
    handLight->reserve(7);
    std::shared_ptr<std::vector<cards>> inPLayLight = std::make_shared<std::vector<cards>>();
    std::shared_ptr<std::vector<cards>> discardLight = std::make_shared<std::vector<cards>>();
    //=========== kart atama===================
    int indexSlowEFFECTED;
    libraryLight->push_back(landCards("Plains","Colorless",1,0,0,'W','X'));
    libraryLight->push_back(landCards("Plains","Colorless",1,0,0,'W','X'));
    libraryLight->push_back(landCards("Plains","Colorless",1,0,0,'W','X'));
    libraryLight->push_back(landCards("Plains","Colorless",1,0,0,'W','X'));
    libraryLight->push_back(landCards("Plains","Colorless",1,0,0,'W','X'));
    libraryLight->push_back(landCards("Forest","Colorless",1,0,0,'G','X'));
    libraryLight->push_back(landCards("Forest","Colorless",1,0,0,'G','X'));
    libraryLight->push_back(landCards("Forest","Colorless",1,0,0,'G','X'));
    libraryLight->push_back(landCards("Island","Colorless",1,0,0,'L','X'));
    libraryLight->push_back(creatureCards("Soldier","White",1,0,0,'W','X',1,1, false, false));
    libraryLight->push_back(creatureCards("Soldier","White",1,0,0,'W','X',1,1, false, false));
    libraryLight->push_back(creatureCards("Soldier","White",1,0,0,'W','X',1,1, false, false));
    libraryLight->push_back(creatureCards("Armored Pegasus","White",1,0,1,'W','X',2,1, false, false));
    libraryLight->push_back(creatureCards("Armored Pegasus","White",1,0,1,'W','X',2,1, false, false));
    libraryLight->push_back(creatureCards("White Night","White",2,0,0,'W','X',2,2, true,false));
    libraryLight->push_back(creatureCards("White Night","White",2,0,0,'W','X',2,2, true,false));
    libraryLight->push_back(creatureCards("Angry Bear","Green",1,0,2,'G','X',2,3,false, true));
    libraryLight->push_back(creatureCards("Guard","White",2,0,2,'W','X',5,2, false, false));
    libraryLight->push_back(creatureCards("Werewolf","Green",1,1,2,'G','W',6,4,false, true));
    libraryLight->push_back(sorceryCards("Disenchant", "White", 1, 0, 1, 'W', 'X'));
    libraryLight->push_back(sorceryCards("Lightning Bolt", "Green", 1, 0, 1, 'G', 'X'));
    libraryLight->push_back(sorceryCards("Flood", "Green", 1, 1, 1, 'G', 'W'));
    libraryLight->push_back(sorceryCards("Flood", "Green", 1, 1, 1, 'G', 'W'));
    libraryLight->push_back(enchantmentCards("Rage","Green",1,0,0,'G','X'));
    libraryLight->push_back(enchantmentCards("Holy War","White",1,0,1,'W','X'));
    libraryLight->push_back(enchantmentCards("Holy Light","White",1,0,1,'W','X'));

    unsigned seed = std::chrono::system_clock::now()
            .time_since_epoch()
            .count();
    shuffle (libraryLight->begin(), libraryLight->end(), std::default_random_engine(seed));
    std::vector<cards>:: iterator randPtr;
    for (int i = (int)(libraryLight->size())-5; i < (int)(libraryLight->size()); i++) {
        handLight->push_back(libraryLight->at(i));
    }
    for (randPtr = libraryLight->end()-5; randPtr < libraryLight->end();randPtr++) {
        libraryLight->erase(randPtr);
    }
    std::shared_ptr<player> lightSide = std::make_shared<player>("jedi",handLight,discardLight,inPLayLight,libraryLight);

    libraryDark->push_back(landCards("Swamp","Colorless",1,0,0,'B','X'));
    libraryDark->push_back(landCards("Swamp","Colorless",1,0,0,'B','X'));
    libraryDark->push_back(landCards("Swamp","Colorless",1,0,0,'B','X'));
    libraryDark->push_back(landCards("Swamp","Colorless",1,0,0,'B','X'));
    libraryDark->push_back(landCards("Swamp","Colorless",1,0,0,'B','X'));
    libraryDark->push_back(landCards("Mountain","Colorless",1,0,0,'R','X'));
    libraryDark->push_back(landCards("Mountain","Colorless",1,0,0,'R','X'));
    libraryDark->push_back(landCards("Mountain","Colorless",1,0,0,'R','X'));
    libraryDark->push_back(landCards("Island","Colorless",1,0,0,'L','X'));
    libraryDark->push_back(creatureCards("Skeleton","Black",1,0,0,'B','X',1,1, false, false));
    libraryDark->push_back(creatureCards("Skeleton","Black",1,0,0,'B','X',1,1, false, false));
    libraryDark->push_back(creatureCards("Skeleton","Black",1,0,0,'B','X',1,1, false, false));
    libraryDark->push_back(creatureCards("Ghost","Black",1,0,1,'B','X',1,2, false, false));
    libraryDark->push_back(creatureCards("Ghost","Black",1,0,1,'B','X',1,2, false, false));
    libraryDark->push_back(creatureCards("Black Knight","Black",2,0,0,'B','X',2,2, true, false));
    libraryDark->push_back(creatureCards("Black Knight","Black",2,0,0,'B','X',2,2, true, false));
    libraryDark->push_back(creatureCards("Orc Maniac","Red",2,0,1,'R','X',1,4, false, false));
    libraryDark->push_back(creatureCards("Hobgoblin","Red",1,1,1,'R','B',3,3, false, false));
    libraryDark->push_back(creatureCards("Vampire","Black",1,0,3,'B','X',3,6, false, false));
    libraryDark->push_back(sorceryCards("Reanimate", "Black", 1, 0, 0, 'B', 'X'));
    libraryDark->push_back(sorceryCards("Plague", "Black", 1, 0, 2, 'B', 'X'));
    libraryDark->push_back(sorceryCards("Terror", "Black", 1, 0, 1, 'B', 'X'));
    libraryDark->push_back(sorceryCards("Terror", "Black", 1, 0, 1, 'B', 'X'));
    libraryDark->push_back(enchantmentCards("Unholy War","Black",1,0,1,'B','X'));
    libraryDark->push_back(enchantmentCards("Restrain","Red",1,0,2,'R','X'));
    libraryDark->push_back(enchantmentCards("Slow","Black",1,0,0,'B','X'));

    shuffle (libraryDark->begin(), libraryDark->end(), std::default_random_engine(seed));
    std::vector<cards>:: iterator randPtrDark;
    for (int i = (int)(libraryDark->size())-5; i < (int)(libraryDark->size()); i++) {
        handDark->push_back(libraryDark->at(i));
    }
    for (randPtrDark = libraryDark->end()-5; randPtrDark < libraryDark->end();randPtrDark++) {
        libraryDark->erase(randPtrDark);
    }
    std::shared_ptr<player> darkSide = std::make_shared<player>("sith",handDark,discardDark,inPLayDark,libraryDark);

    int numOfLandCardLR = 0;
    int numOfLandCardDA = 0;

    std::cout << "############################ GAME STARTED ################################" << std::endl;
    while(lightSide->isAlive() && darkSide->isAlive()){
        std::cout << "############################ "<< round << "." << "STARTED ################################" << std::endl;
        if(round == 1){
            std::cout << "Welcome to the mgtA" << std::endl;
        }
        else if(libraryLight->size() != 0){
            if((int)(handLight->size()) < 7){
                int indexL = (int)(libraryLight->size()-1);
                handLight->push_back(libraryLight->at(indexL));
                auto ptrL = libraryLight->begin() + indexL;
                libraryLight->erase(ptrL);
            }
            else{
                std::cout << "Elin dolu kart cekemedin" << std::endl;
            }
        }
        else{
            std::cout << "You do not have any in library, you have Lost the game." << std::endl;
            lightSide->makeLoser();
            std::cout << darkSide->getPlayerName() << " has WON with " << darkSide->getPlayerHp() << " hp." << std::endl;
            return 0;
            break;
        }
        makeWholeUntapped(handLight,discardLight,inPLayLight,libraryLight);
        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);

        bool isLandCardsPlayedR = false;
        lightSide->printHand();
        std::cout << "Do you want to play land card? If you do, Enter 1. If you do not, Enter 0." << std::endl;
        int landPlayCheckR;
        std::cin >> landPlayCheckR;
        if(landPlayCheckR == 1){
            std::cout << "Please Enter index of land card." << std::endl;
            int landIndex;
            std::cin >> landIndex;
            if(handLight->at(landIndex).getCardType() == 'L'){
                inPLayLight->push_back(handLight->at(landIndex));
                std::cout << "You have played " << handLight->at(landIndex).getName() << std::endl;
                auto ptr = handLight->begin() + landIndex;
                handLight->erase(ptr);
                isLandCardsPlayedR = true;
                numOfLandCardLR++;
                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
            }
            else{
                std::cout << "hata land bolmu " << std::endl;
            }
        }
        if(numOfLandCardLR > 0){
            std::cout << "Do you want to make your land card tapped? If you do, Enter 1. If you do not, Enter 0." << std::endl;
            int landTapped;
            std::cin >> landTapped;
            if(landTapped == 1){
                lightSide->printInPlay();
                std::cout << "Land kart indexi cikmak icin -3" << std::endl;
                int landIndex;
                std::cin >> landIndex;
                while(landIndex != -3){
                    if(inPLayLight->at(landIndex).getCardType() == 'L' && !inPLayLight->at(landIndex).learnTapped()){
                        inPLayLight->at(landIndex).makeTapped();
                        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                        lightSide->plusSetColorManaWithChar(inPLayLight->at(landIndex).getMana1(),inPLayLight->at(landIndex).learnManaTypes1());
                        std::cout <<  "You have earned " << inPLayLight->at(landIndex).getMana1() << " " << inPLayLight->at(landIndex).learnManaTypes1() << std::endl;
                        std::cout << "Your Total Mana : ";
                        lightSide->printWholeTotalMana();
                        if(numOfLandCardLR > 1){
                            std::cout << "Do you want to make your another land card tapped? If you do, Enter index. If you do not, Enter -3." << std::endl;
                            std::cin >> landIndex;
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        std::cout << "hata land bolmu " << std::endl;
                        std::cout << "Do you want to make your another land card tapped? If you do, Enter index. If you do not, Enter -3." << std::endl;
                        std::cin >> landIndex;
                    }
                }
            }
        }
        lightSide->printHand();
        std::cout << "Do you want to play another card? If you do, Enter 1. If you do not, Enter 0." << std::endl;
        int checkOtherR;
        std::cin >> checkOtherR;
        if(checkOtherR == 1){
            std::cout << "Please Enter index of your card that you want to play. If you do not want to play, Enter -3." << std::endl;
            int indexCardWP;
            std::cin >> indexCardWP;
            while(indexCardWP != -3){
                int checkPayment = 0;
                if(handLight->at(indexCardWP).getCardType() == 'C'){
                    if(handLight->at(indexCardWP).getMana1() >= 0){
                        if(handLight->at(indexCardWP).learnManaTypes1() == 'G'){
                            if(lightSide->getMana1() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'L'){
                            if(lightSide->getMana2() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'R'){
                            if(lightSide->getMana3() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'W'){
                            if(lightSide->getMana4() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'B'){
                            if(lightSide->getMana5() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                    }
                    if (handLight->at(indexCardWP).getMana2() >= 0){
                        if(handLight->at(indexCardWP).learnManaTypes2() == 'G'){
                            if(lightSide->getMana1() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'L'){
                            if(lightSide->getMana2() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'R'){
                            if(lightSide->getMana3() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'W'){
                            if(lightSide->getMana4() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'B'){
                            if(lightSide->getMana5() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if(handLight->at(indexCardWP).learnManaTypes2() == 'X'){
                            checkPayment++;
                        }
                    }
                    if(handLight->at(indexCardWP).getMana3() >= 0){
                        if(lightSide->checkNonColorPayment(handLight->at(indexCardWP).getMana3())){
                            checkPayment++;
                        }
                    }
                    // uygulama yeri
                    if(checkPayment == 3){
                        lightSide->minusSetColorManaWithChar(handLight->at(indexCardWP).getMana1(),handLight->at(indexCardWP).learnManaTypes1());
                        lightSide->minusSetColorManaWithChar(handLight->at(indexCardWP).getMana2(),handLight->at(indexCardWP).learnManaTypes2());
                        if(lightSide->checkNonColorPayment(handLight->at(indexCardWP).getMana3())){
                            lightSide->takeNonColorPayment(handLight->at(indexCardWP).getMana3());
                            inPLayLight->push_back(handLight->at(indexCardWP));
                            std::cout << "You have played " << handLight->at(indexCardWP).getName() << std::endl;
                            std::cout << "Your Total Mana : ";
                            lightSide->printWholeTotalMana();
                            auto ptr = handLight->begin() + indexCardWP;
                            handLight->erase(ptr);
                            lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                            darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                        }
                        else{
                            lightSide->plusSetColorManaWithChar(handLight->at(indexCardWP).getMana1(),handLight->at(indexCardWP).learnManaTypes1());
                            lightSide->plusSetColorManaWithChar(handLight->at(indexCardWP).getMana2(),handLight->at(indexCardWP).learnManaTypes2());
                            std::cout << "You do not have enought MANA :( " << std::endl;

                        }
                    }
                    else{
                        std::cout << "You do not have enough MANA :( " << std::endl;
                    }
                }
                else if(handLight->at(indexCardWP).getCardType() == 'E'){
                    if(handLight->at(indexCardWP).getMana1() >= 0){
                        if(handLight->at(indexCardWP).learnManaTypes1() == 'G'){
                            if(lightSide->getMana1() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'L'){
                            if(lightSide->getMana2() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'R'){
                            if(lightSide->getMana3() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'W'){
                            if(lightSide->getMana4() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'B'){
                            if(lightSide->getMana5() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                    }
                    if (handLight->at(indexCardWP).getMana2() >= 0){
                        if(handLight->at(indexCardWP).learnManaTypes2() == 'G'){
                            if(lightSide->getMana1() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'L'){
                            if(lightSide->getMana2() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'R'){
                            if(lightSide->getMana3() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'W'){
                            if(lightSide->getMana4() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'B'){
                            if(lightSide->getMana5() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if(handLight->at(indexCardWP).learnManaTypes2() == 'X'){
                            checkPayment++;
                        }
                    }
                    if(handLight->at(indexCardWP).getMana3() >= 0){
                        if(lightSide->checkNonColorPayment(handLight->at(indexCardWP).getMana3())){
                            checkPayment++;
                        }
                    }
                    // uygulama yeri
                    if(checkPayment == 3){
                        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);

                        lightSide->minusSetColorManaWithChar(handLight->at(indexCardWP).getMana1(),handLight->at(indexCardWP).learnManaTypes1());
                        lightSide->minusSetColorManaWithChar(handLight->at(indexCardWP).getMana2(),handLight->at(indexCardWP).learnManaTypes2());

                        if(lightSide->checkNonColorPayment(handLight->at(indexCardWP).getMana3())){
                            lightSide->takeNonColorPayment(handLight->at(indexCardWP).getMana3());
                            inPLayLight->push_back(handLight->at(indexCardWP));
                            std::cout << "You have played " << handLight->at(indexCardWP).getName() << std::endl;
                            if(handLight->at(indexCardWP).getName() == "Holy War"){
                                enchantmentEffects.allWhiteCreaturesGain11(inPLayLight,inPLayDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                            }
                            else if(handLight->at(indexCardWP).getName() == "Holy Light"){
                                enchantmentEffects.allBlackCreaturesMinus11(inPLayLight,inPLayDark);
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        goToDiscard(inPLayLight,discardLight);
                                    }
                                }
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        goToDiscard(inPLayDark,discardDark);
                                    }
                                }
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                            }
                            else if(handLight->at(indexCardWP).getName() == "Unholy War"){
                                enchantmentEffects.allBlackCreaturesGain20(inPLayLight,inPLayDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);

                            }
                            else if(handLight->at(indexCardWP).getName() == "Restrain"){
                                enchantmentEffects.allGreenCreaturesLoseTrample(inPLayLight,inPLayDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                            }
                            else if(handLight->at(indexCardWP).getName() == "Rage"){
                                std::cout<< "Which creature card, do you want to give trample? " << std::endl;
                                int indexLOLO;
                                lightSide->printInPlay();
                                std::cin >> indexLOLO;
                                enchantmentEffects.targetCreatureGainTrample(inPLayLight,indexLOLO);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                            }
                            else if(handLight->at(indexCardWP).getName() == "Slow"){
                                std::cout<< "Which enemy creature card, do you want to take it's First Strike? " << std::endl;
                                int indexLOLO;
                                darkSide->printInPlay();
                                std::cin >> indexLOLO;
                                enchantmentEffects.targetCreatureLoseFirstStrike(inPLayDark,indexLOLO);

                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                            }
                            std::cout << "The enchantment card that you have already played is, activated its effect. " << std::endl;
                            std::cout << "Your Total Mana : ";
                            lightSide->printWholeTotalMana();
                            auto ptr = handLight->begin() + indexCardWP;
                            handLight->erase(ptr);
                            lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                        }
                        else{
                            lightSide->plusSetColorManaWithChar(handLight->at(indexCardWP).getMana1(),handLight->at(indexCardWP).learnManaTypes1());
                            lightSide->plusSetColorManaWithChar(handLight->at(indexCardWP).getMana2(),handLight->at(indexCardWP).learnManaTypes2());
                            std::cout << "You do not have enough MANA :(" << std::endl;
                        }
                    }
                    else{
                        std::cout << "You do not have enough MANA :( " << std::endl;
                    }
                }
                else if(handLight->at(indexCardWP).getCardType() == 'S'){
                    if(handLight->at(indexCardWP).getMana1() >= 0){
                        if(handLight->at(indexCardWP).learnManaTypes1() == 'G'){
                            if(lightSide->getMana1() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'L'){
                            if(lightSide->getMana2() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'R'){
                            if(lightSide->getMana3() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'W'){
                            if(lightSide->getMana4() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'B'){
                            if(lightSide->getMana5() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                    }
                    if (handLight->at(indexCardWP).getMana2() >= 0){
                        if(handLight->at(indexCardWP).learnManaTypes2() == 'G'){
                            if(lightSide->getMana1() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'L'){
                            if(lightSide->getMana2() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'R'){
                            if(lightSide->getMana3() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'W'){
                            if(lightSide->getMana4() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'B'){
                            if(lightSide->getMana5() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if(handLight->at(indexCardWP).learnManaTypes2() == 'X'){
                            checkPayment++;
                        }
                    }
                    if(handLight->at(indexCardWP).getMana3() >= 0){
                        if(lightSide->checkNonColorPayment(handLight->at(indexCardWP).getMana3())){
                            checkPayment++;
                        }
                    }
                    // uygulama yeri
                    if(checkPayment == 3){
                        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);

                        lightSide->minusSetColorManaWithChar(handLight->at(indexCardWP).getMana1(),handLight->at(indexCardWP).learnManaTypes1());
                        lightSide->minusSetColorManaWithChar(handLight->at(indexCardWP).getMana2(),handLight->at(indexCardWP).learnManaTypes2());

                        if(lightSide->checkNonColorPayment(handLight->at(indexCardWP).getMana3())){
                            lightSide->takeNonColorPayment(handLight->at(indexCardWP).getMana3());
                            discardLight->push_back(handLight->at(indexCardWP));

                            std::cout << "You have played " << handLight->at(indexCardWP).getName() << std::endl;

                            if(handLight->at(indexCardWP).getName() == "Disenchant"){
                                int indexSOSO;
                                darkSide->printInPlay();
                                std::cout<< "Which Enchantment card, do you want to destroy? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.DisenchantEffect(inPLayDark,inPLayLight,indexSOSO);
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        goToDiscard(inPLayDark,discardDark);
                                    }
                                }
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                            }
                            else if(handLight->at(indexCardWP).getName() == "Lightning Bolt"){
                                std::cout<< "Do you want to attack (2dmg) to enemy or enemy's card, If your decision is enemy, Enter 0. If your decision is enemy creature, Enter 1." << std::endl;
                                int indexControl;
                                std::cin >> indexControl;
                                if(indexControl == 0){
                                    sorceryEffects.LightningBoltEffect(darkSide);
                                    if(darkSide->getPlayerHp() <= 0){
                                        std::cout << darkSide->getPlayerName() <<" has died." << std::endl;
                                        std::cout << lightSide->getPlayerName() <<" has WON the game with " << lightSide->getPlayerHp()<<" HP." << std::endl;
                                        return 0;
                                        break;
                                    }
                                    else{
                                        std::cout << darkSide->getPlayerName() <<" has not died YET." << std::endl;
                                        std::cout << darkSide->getPlayerName() <<" has " << darkSide->getPlayerHp() << " HP" << std::endl;
                                    }
                                }
                                else if(indexControl == 1){
                                    int index123;
                                    darkSide->printInPlay();
                                    std::cout<< "Which creature card, do you want to give 2 dmg ? " << std::endl;
                                    std::cin >> index123;
                                    sorceryEffects.LightningBoltEffect(inPLayDark,index123);
                                    if(inPLayDark->at(index123).getBaseHP() <= 0){
                                        std::cout << inPLayDark->at(index123).getName()<<" has died." << std::endl;
                                        inPLayDark->at(index123).makeDestroyed();
                                        discardDark->push_back(inPLayDark->at(index123));
                                        auto ptr = inPLayDark->begin() + index123;
                                        inPLayDark->erase(ptr);
                                        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                        for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                            if (inPLayLight->at(j).getBaseHP() <= 0){
                                                inPLayLight->at(j).makeDestroyed();
                                                goToDiscard(inPLayLight,discardLight);
                                            }
                                        }
                                        for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                            if (inPLayDark->at(j).getBaseHP() <= 0){
                                                inPLayLight->at(j).makeDestroyed();
                                                goToDiscard(inPLayDark,discardDark);
                                            }
                                        }
                                        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                    }
                                    else{
                                        std::cout << inPLayDark->at(index123).getName()<<" has not died YET." << std::endl;
                                        std::cout << inPLayDark->at(index123).getName()<<" has " << inPLayDark->at(index123).getBaseHP() << " HP" << std::endl;
                                        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                    }
                                }
                                else{
                                    std::cout << "Invalid Number !!" << std::endl;
                                }
                            }
                            else if(handLight->at(indexCardWP).getName() == "Flood"){
                                int indexSOSO;
                                darkSide->printInPlay();
                                std::cout<< "Which Land card, do you want to destroy? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.floodEffect(inPLayDark,indexSOSO);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        goToDiscard(inPLayLight,discardLight);
                                    }
                                }
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        goToDiscard(inPLayDark,discardDark);
                                    }
                                }
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                            }
                            else if(handLight->at(indexCardWP).getName() == "Reanimate"){
                                int indexSOSO;
                                lightSide->printDiscard();
                                std::cout<< "Which card, do you want to revive? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.ReanimateCardEffect(discardLight,handLight,indexSOSO);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                            }
                            else if(handLight->at(indexCardWP).getName() == "Plague"){
                                sorceryEffects.PlagueEffect(inPLayDark);
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        goToDiscard(inPLayLight,discardLight);
                                    }
                                }
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        std::cout << inPLayDark->at(j).getName()<<" has died." << std::endl;
                                        goToDiscard(inPLayDark,discardDark);
                                    }
                                }
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);

                                darkSide->printInPlay();
                            }
                            else if(handLight->at(indexCardWP).getName() == "Terror"){
                                int indexSOSO;
                                darkSide->printInPlay();
                                std::cout<< "Which Creature card, do you want to destroy? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.terrorEffect(inPLayDark,indexSOSO);

                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        goToDiscard(inPLayDark,discardDark);
                                    }
                                }
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                            }
                            std::cout << "The sorcery card that you have already played is, activated its effect. " << std::endl;
                            std::cout << "Your Total Mana : ";
                            lightSide->printWholeTotalMana();
                            auto ptr = handLight->begin() + indexCardWP;
                            handLight->erase(ptr);
                            lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                            darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                        }
                        else{
                            lightSide->plusSetColorManaWithChar(handLight->at(indexCardWP).getMana1(),handLight->at(indexCardWP).learnManaTypes1());
                            lightSide->plusSetColorManaWithChar(handLight->at(indexCardWP).getMana2(),handLight->at(indexCardWP).learnManaTypes2());
                            std::cout << "You do not have enough MANA :(" << std::endl;
                        }
                    }
                    else{
                        std::cout << "You do not have enough MANA :( " << std::endl;
                    }
                }
                std::cout << "Do you want to play another card? If you do, Enter index. If you do not, Enter -3." << std::endl;
                std::cin>>indexCardWP;
            }
        }
        std::cout << "Do you want to make your creature card defender? If you do, Enter 1." << std::endl;
        lightSide->printInPlay();
        int indexDoYouWannaMakeDEFR;
        std::cin >> indexDoYouWannaMakeDEFR;
        if(indexDoYouWannaMakeDEFR == 1){
            std::cout << "Please Enter index of your creature card that you want to make defender. If you do not, Enter -3." << std::endl;
            int control;
            std::cin >> control;
            while(control != -3){
                if (!inPLayLight->at(control).learnTapped()){
                    inPLayLight->at(control).makeDefender();
                    std::cout << inPLayLight->at(control).getName() << " is defender now." <<std::endl;
                    lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                    std::cout << "Do you want to make your another creature card defender? If you do, Enter index. If you do not, Enter -3." << std::endl;
                    std::cin >> control;
                }
                else{
                    std::cout << inPLayLight->at(control).getName() << " This card is already tapped. Enter another index. If you do not want to make defender Enter -3." <<std::endl;
                    std::cin >> control;
                }
            }
        }
        std::cout << "Do you want to attack? If you do, Enter 1. If you do not, Enter 0." << std::endl;
        int indexDoYOUWANNAttackR;
        std::cin >> indexDoYOUWANNAttackR;
        if(indexDoYOUWANNAttackR == 1){
            lightSide->printInPlay();
            std::cout << "Chose, which card do you want to use it in attack." <<std::endl;
            int indexAttacker;
            std::cin >> indexAttacker;
            if((0 <= indexAttacker) && (indexAttacker < (int)(inPLayLight->size()))){
                while(indexAttacker != -3 && !inPLayLight->at(indexAttacker).isAttackAnyCard()){
                    if(inPLayLight->at(indexAttacker).getCardType() == 'C'){
                        inPLayLight->at(indexAttacker).makeAttacker();
                        if(checkAreThereAnyDefender(inPLayDark)){
                            for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                if(inPLayDark->at(j).learnIsItDefender()){
                                    attackWithCreature(inPLayLight,indexAttacker,inPLayDark,j,lightSide,darkSide);
                                    darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                    lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                    for (int k = 0; k < (int)(inPLayLight->size()); ++k) {
                                        if (inPLayLight->at(k).getBaseHP() <= 0){
                                            inPLayLight->at(k).makeDestroyed();
                                            inPLayLight->at(k).resetCards();
                                            goToDiscard(inPLayLight,discardLight);
                                        }
                                    }
                                    for (int k = 0; k < (int)(inPLayDark->size()); ++k) {
                                        if (inPLayDark->at(k).getBaseHP() <= 0){
                                            inPLayLight->at(k).makeDestroyed();
                                            inPLayLight->at(k).resetCards();
                                            goToDiscard(inPLayDark,discardDark);
                                        }
                                    }
                                    darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                    lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                    if(darkSide->getPlayerHp() <= 0){
                                        return 0;
                                        break;
                                    }
                                }
                            }
                        }
                        else{
                            attackPlayer(darkSide,inPLayLight->at(indexAttacker).getAttackPower());
                            inPLayLight->at(indexAttacker).makeUsed();
                            if(darkSide->getPlayerHp() <= 0){
                                return 0;
                                break;
                            }
                            lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                            darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                        }
                    }
                    else{
                        std::cout << "You can only Attack with creature card!!!"<< std::endl;
                    }
                    std::cout << "bastan saldircan mi yoksa -3" << std::endl;
                    std::cin >> indexAttacker;
                    if(inPLayLight->at(indexAttacker).isAttackAnyCard()){
                        std::cout << "You cannot attack again with same card. If you want to attack, Enter another valid index. If you do not, Enter -3." << std::endl;
                    }
                    if(0 > indexAttacker || indexAttacker >= (int) (inPLayLight->size())){
                        std::cout << "hatali bastan g'r cikicaksan -3!!!" << std::endl;
                        std::cin >> indexAttacker;
                    }
                }
            }
            else{
                std::cout << "Invalid Number !!!" << std::endl;
            }

        }
        // play 2
        lightSide->printHand();
        if(!isLandCardsPlayedR){
            std::cout << "Do you want to play land card? If you do, Enter 1. If you do not, Enter 0." << std::endl;
            int landPlayCheck1;
            std::cin >> landPlayCheck1;
            if(landPlayCheck1 == 1){
                std::cout << "Please enter index of land card." << std::endl;
                int landIndex2;
                std::cin >> landIndex2;
                if(handLight->at(landIndex2).getCardType() == 'L'){
                    inPLayLight->push_back(handLight->at(landIndex2));
                    std::cout << "You have played " << handLight->at(landIndex2).getName() << std::endl;
                    auto ptr = handLight->begin() + landIndex2;
                    handLight->erase(ptr);
                    isLandCardsPlayedR = true;
                    numOfLandCardLR++;
                    lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                    darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                }
                else{
                    std::cout << "hata land bolmu " << std::endl;
                }
            }
        }
        if(numOfLandCardLR > 0){
            std::cout << "Do you want to make your land card tapped? If you do, Enter 1. If you do not, Enter 0." << std::endl;
            int landTapped;
            std::cin >> landTapped;
            if(landTapped == 1){
                lightSide->printInPlay();
                std::cout << "Land kart indexi cikmak icin -3" << std::endl;
                int landIndex;
                std::cin >> landIndex;
                while(landIndex != -3){
                    if(inPLayLight->at(landIndex).getCardType() == 'L' && !inPLayLight->at(landIndex).learnTapped()){
                        inPLayLight->at(landIndex).makeTapped();
                        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                        lightSide->plusSetColorManaWithChar(inPLayLight->at(landIndex).getMana1(),inPLayLight->at(landIndex).learnManaTypes1());
                        std::cout << "You have earned " << inPLayLight->at(landIndex).getMana1() << " " << inPLayLight->at(landIndex).learnManaTypes1() << std::endl;
                        std::cout << "Your Total Mana : ";
                        lightSide->printWholeTotalMana();
                        if(numOfLandCardLR > 1){
                            std::cout << "Do you want to make tapped another land card? If you do, Enter index. If you do not, Enter -3." << std::endl;
                            std::cin >> landIndex;
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        std::cout << "hata land bolmu " << std::endl;
                        std::cout << "Do you want to make tapped another land card? If you do, Enter index. If you do not, Enter -3." << std::endl;
                        std::cin >> landIndex;
                    }
                }
            }
        }
        std::cout << "Do you want to play another card? If you do, Enter 1. If you do not, Enter 0." << std::endl;
        int checkOther1R;
        std::cin >> checkOther1R;
        if(checkOther1R == 1){
            lightSide->printInPlay();
            std::cout << "Please Enter index of card that you want to play. If you do not want to play Enter -3." << std::endl;
            int indexCardWP;
            std::cin >> indexCardWP;
            while(indexCardWP != -3){
                int checkPayment = 0;
                if(handLight->at(indexCardWP).getCardType() == 'C'){
                    if(handLight->at(indexCardWP).getMana1() >= 0){
                        if(handLight->at(indexCardWP).learnManaTypes1() == 'G'){
                            if(lightSide->getMana1() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'L'){
                            if(lightSide->getMana2() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'R'){
                            if(lightSide->getMana3() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'W'){
                            if(lightSide->getMana4() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'B'){
                            if(lightSide->getMana5() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                    }
                    if (handLight->at(indexCardWP).getMana2() >= 0){
                        if(handLight->at(indexCardWP).learnManaTypes2() == 'G'){
                            if(lightSide->getMana1() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'L'){
                            if(lightSide->getMana2() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'R'){
                            if(lightSide->getMana3() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'W'){
                            if(lightSide->getMana4() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'B'){
                            if(lightSide->getMana5() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if(handLight->at(indexCardWP).learnManaTypes2() == 'X'){
                            checkPayment++;
                        }
                    }
                    if(handLight->at(indexCardWP).getMana3() >= 0){
                        if(lightSide->checkNonColorPayment(handLight->at(indexCardWP).getMana3())){
                            checkPayment++;
                        }
                    }
                    // uygulama yeri
                    if(checkPayment == 3){
                        lightSide->minusSetColorManaWithChar(handLight->at(indexCardWP).getMana1(),handLight->at(indexCardWP).learnManaTypes1());
                        lightSide->minusSetColorManaWithChar(handLight->at(indexCardWP).getMana2(),handLight->at(indexCardWP).learnManaTypes2());
                        if(lightSide->checkNonColorPayment(handLight->at(indexCardWP).getMana3())){
                            lightSide->takeNonColorPayment(handLight->at(indexCardWP).getMana3());
                            inPLayLight->push_back(handLight->at(indexCardWP));
                            std::cout << "You have played " << handLight->at(indexCardWP).getName() << std::endl;
                            std::cout << "Your Total Mana : ";
                            lightSide->printWholeTotalMana();
                            auto ptr = handLight->begin() + indexCardWP;
                            handLight->erase(ptr);
                            lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                            darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                        }
                        else{
                            lightSide->plusSetColorManaWithChar(handLight->at(indexCardWP).getMana1(),handLight->at(indexCardWP).learnManaTypes1());
                            lightSide->plusSetColorManaWithChar(handLight->at(indexCardWP).getMana2(),handLight->at(indexCardWP).learnManaTypes2());
                            std::cout << "You do not have enough MANA :( " << std::endl;

                        }
                    }
                    else{
                        std::cout << "You do not have enough MANA :( " << std::endl;
                    }
                }
                else if(handLight->at(indexCardWP).getCardType() == 'E'){
                    if(handLight->at(indexCardWP).getMana1() >= 0){
                        if(handLight->at(indexCardWP).learnManaTypes1() == 'G'){
                            if(lightSide->getMana1() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'L'){
                            if(lightSide->getMana2() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'R'){
                            if(lightSide->getMana3() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'W'){
                            if(lightSide->getMana4() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'B'){
                            if(lightSide->getMana5() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                    }
                    if (handLight->at(indexCardWP).getMana2() >= 0){
                        if(handLight->at(indexCardWP).learnManaTypes2() == 'G'){
                            if(lightSide->getMana1() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'L'){
                            if(lightSide->getMana2() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'R'){
                            if(lightSide->getMana3() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'W'){
                            if(lightSide->getMana4() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'B'){
                            if(lightSide->getMana5() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if(handLight->at(indexCardWP).learnManaTypes2() == 'X'){
                            checkPayment++;
                        }
                    }
                    if(handLight->at(indexCardWP).getMana3() >= 0){
                        if(lightSide->checkNonColorPayment(handLight->at(indexCardWP).getMana3())){
                            checkPayment++;
                        }
                    }
                    // uygulama yeri
                    if(checkPayment == 3){
                        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);

                        lightSide->minusSetColorManaWithChar(handLight->at(indexCardWP).getMana1(),handLight->at(indexCardWP).learnManaTypes1());
                        lightSide->minusSetColorManaWithChar(handLight->at(indexCardWP).getMana2(),handLight->at(indexCardWP).learnManaTypes2());

                        if(lightSide->checkNonColorPayment(handLight->at(indexCardWP).getMana3())){
                            lightSide->takeNonColorPayment(handLight->at(indexCardWP).getMana3());
                            inPLayLight->push_back(handLight->at(indexCardWP));
                            std::cout << "You have played " << handLight->at(indexCardWP).getName() << std::endl;
                            if(handLight->at(indexCardWP).getName() == "Holy War"){
                                enchantmentEffects.allWhiteCreaturesGain11(inPLayLight,inPLayDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                            }
                            else if(handLight->at(indexCardWP).getName() == "Holy Light"){
                                enchantmentEffects.allBlackCreaturesMinus11(inPLayLight,inPLayDark);
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        goToDiscard(inPLayLight,discardLight);
                                    }
                                }
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        goToDiscard(inPLayDark,discardDark);
                                    }
                                }
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                            }
                            else if(handLight->at(indexCardWP).getName() == "Unholy War"){
                                enchantmentEffects.allBlackCreaturesGain20(inPLayLight,inPLayDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);

                            }
                            else if(handLight->at(indexCardWP).getName() == "Restrain"){
                                enchantmentEffects.allGreenCreaturesLoseTrample(inPLayLight,inPLayDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                            }
                            else if(handLight->at(indexCardWP).getName() == "Rage"){
                                std::cout<< "Which creature card, do you want to give trample? " << std::endl;
                                int indexLOLO;
                                lightSide->printInPlay();
                                std::cin >> indexLOLO;
                                enchantmentEffects.targetCreatureGainTrample(inPLayLight,indexLOLO);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                            }
                            else if(handLight->at(indexCardWP).getName() == "Slow"){
                                std::cout<< "Which enemy creature card, do you want to take it's First Strike? " << std::endl;
                                int indexLOLO;
                                darkSide->printInPlay();
                                std::cin >> indexLOLO;
                                enchantmentEffects.targetCreatureLoseFirstStrike(inPLayDark,indexLOLO);

                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                            }
                            std::cout << "The enchantment card that you have already played is, activated its effect. " << std::endl;
                            std::cout << "Your Total Mana : ";
                            lightSide->printWholeTotalMana();
                            auto ptr = handLight->begin() + indexCardWP;
                            handLight->erase(ptr);
                            lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                        }
                        else{
                            lightSide->plusSetColorManaWithChar(handLight->at(indexCardWP).getMana1(),handLight->at(indexCardWP).learnManaTypes1());
                            lightSide->plusSetColorManaWithChar(handLight->at(indexCardWP).getMana2(),handLight->at(indexCardWP).learnManaTypes2());
                            std::cout << "You do not have enough MANA :(" << std::endl;
                        }
                    }
                    else{
                        std::cout << "You do not have enough MANA :( " << std::endl;
                    }
                }
                else if(handLight->at(indexCardWP).getCardType() == 'S'){
                    if(handLight->at(indexCardWP).getMana1() >= 0){
                        if(handLight->at(indexCardWP).learnManaTypes1() == 'G'){
                            if(lightSide->getMana1() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'L'){
                            if(lightSide->getMana2() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'R'){
                            if(lightSide->getMana3() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'W'){
                            if(lightSide->getMana4() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes1() == 'B'){
                            if(lightSide->getMana5() - handLight->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                    }
                    if (handLight->at(indexCardWP).getMana2() >= 0){
                        if(handLight->at(indexCardWP).learnManaTypes2() == 'G'){
                            if(lightSide->getMana1() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'L'){
                            if(lightSide->getMana2() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'R'){
                            if(lightSide->getMana3() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'W'){
                            if(lightSide->getMana4() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handLight->at(indexCardWP).learnManaTypes2() == 'B'){
                            if(lightSide->getMana5() - handLight->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if(handLight->at(indexCardWP).learnManaTypes2() == 'X'){
                            checkPayment++;
                        }
                    }
                    if(handLight->at(indexCardWP).getMana3() >= 0){
                        if(lightSide->checkNonColorPayment(handLight->at(indexCardWP).getMana3())){
                            checkPayment++;
                        }
                    }
                    // uygulama yeri
                    if(checkPayment == 3){
                        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);

                        lightSide->minusSetColorManaWithChar(handLight->at(indexCardWP).getMana1(),handLight->at(indexCardWP).learnManaTypes1());
                        lightSide->minusSetColorManaWithChar(handLight->at(indexCardWP).getMana2(),handLight->at(indexCardWP).learnManaTypes2());

                        if(lightSide->checkNonColorPayment(handLight->at(indexCardWP).getMana3())){
                            lightSide->takeNonColorPayment(handLight->at(indexCardWP).getMana3());
                            discardLight->push_back(handLight->at(indexCardWP));

                            std::cout << "You have played " << handLight->at(indexCardWP).getName() << std::endl;

                            if(handLight->at(indexCardWP).getName() == "Disenchant"){
                                int indexSOSO;
                                darkSide->printInPlay();
                                std::cout<< "Which Enchantment card, do you want to destroy? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.DisenchantEffect(inPLayDark,inPLayLight,indexSOSO);
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        goToDiscard(inPLayDark,discardDark);
                                    }
                                }
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                            }
                            else if(handLight->at(indexCardWP).getName() == "Lightning Bolt"){
                                std::cout<< "Do you want to attack (2dmg) to enemy or enemy's card, If your decision is enemy, Enter 0. If your decision is enemy creature, Enter 1." << std::endl;
                                int indexControl;
                                std::cin >> indexControl;
                                if(indexControl == 0){
                                    sorceryEffects.LightningBoltEffect(darkSide);
                                    if(darkSide->getPlayerHp() <= 0){
                                        std::cout << darkSide->getPlayerName() <<" has died." << std::endl;
                                        std::cout << lightSide->getPlayerName() <<" has WON the game with " << lightSide->getPlayerHp()<<" HP." << std::endl;
                                        return 0;
                                        break;
                                    }
                                    else{
                                        std::cout << darkSide->getPlayerName() <<" has not died YET." << std::endl;
                                        std::cout << darkSide->getPlayerName() <<" has " << darkSide->getPlayerHp() << " HP" << std::endl;
                                    }
                                }
                                else if(indexControl == 1){
                                    int index123;
                                    darkSide->printInPlay();
                                    std::cout<< "Which creature card, do you want to give 2 dmg ? " << std::endl;
                                    std::cin >> index123;
                                    sorceryEffects.LightningBoltEffect(inPLayDark,index123);
                                    if(inPLayDark->at(index123).getBaseHP() <= 0){
                                        std::cout << inPLayDark->at(index123).getName()<<" has died." << std::endl;
                                        inPLayDark->at(index123).makeDestroyed();
                                        discardDark->push_back(inPLayDark->at(index123));
                                        auto ptr = inPLayDark->begin() + index123;
                                        inPLayDark->erase(ptr);
                                        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                        for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                            if (inPLayLight->at(j).getBaseHP() <= 0){
                                                inPLayLight->at(j).makeDestroyed();
                                                goToDiscard(inPLayLight,discardLight);
                                            }
                                        }
                                        for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                            if (inPLayDark->at(j).getBaseHP() <= 0){
                                                inPLayLight->at(j).makeDestroyed();
                                                goToDiscard(inPLayDark,discardDark);
                                            }
                                        }
                                        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                    }
                                    else{
                                        std::cout << inPLayDark->at(index123).getName()<<" has not died YET." << std::endl;
                                        std::cout << inPLayDark->at(index123).getName()<<" has " << inPLayDark->at(index123).getBaseHP() << " HP" << std::endl;
                                        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                    }
                                }
                                else{
                                    std::cout << "Invalid Number !!" << std::endl;
                                }
                            }
                            else if(handLight->at(indexCardWP).getName() == "Flood"){
                                int indexSOSO;
                                darkSide->printInPlay();
                                std::cout<< "Which Land card, do you want to destroy? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.floodEffect(inPLayDark,indexSOSO);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        goToDiscard(inPLayLight,discardLight);
                                    }
                                }
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        goToDiscard(inPLayDark,discardDark);
                                    }
                                }
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                            }
                            else if(handLight->at(indexCardWP).getName() == "Reanimate"){
                                int indexSOSO;
                                lightSide->printDiscard();
                                std::cout<< "Which card, do you want to revive? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.ReanimateCardEffect(discardLight,handLight,indexSOSO);
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                            }
                            else if(handLight->at(indexCardWP).getName() == "Plague"){
                                sorceryEffects.PlagueEffect(inPLayDark);
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        goToDiscard(inPLayLight,discardLight);
                                    }
                                }
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        std::cout << inPLayDark->at(j).getName()<<" has died." << std::endl;
                                        goToDiscard(inPLayDark,discardDark);
                                    }
                                }
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);

                                darkSide->printInPlay();
                            }
                            else if(handLight->at(indexCardWP).getName() == "Terror"){
                                int indexSOSO;
                                darkSide->printInPlay();
                                std::cout<< "Which Creature card, do you want to destroy? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.terrorEffect(inPLayDark,indexSOSO);

                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayLight->at(j).makeDestroyed();
                                        goToDiscard(inPLayDark,discardDark);
                                    }
                                }
                                darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                                lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                            }
                            std::cout << "The sorcery card that you have already played is, activated its effect. " << std::endl;
                            std::cout << "Your Total Mana : ";
                            lightSide->printWholeTotalMana();
                            auto ptr = handLight->begin() + indexCardWP;
                            handLight->erase(ptr);
                            lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
                            darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
                        }
                        else{
                            lightSide->plusSetColorManaWithChar(handLight->at(indexCardWP).getMana1(),handLight->at(indexCardWP).learnManaTypes1());
                            lightSide->plusSetColorManaWithChar(handLight->at(indexCardWP).getMana2(),handLight->at(indexCardWP).learnManaTypes2());
                            std::cout << "You do not have enough MANA :(" << std::endl;
                        }
                    }
                    else{
                        std::cout << "You do not have enough MANA :( " << std::endl;
                    }
                }
                std::cout << "Do you want to play another card? If you do, Enter index. If you do not, Enter -3." << std::endl;
                std::cin>>indexCardWP;
            }
        }

        lightSide->resetMana();

        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);
        std::cout << "JEDI's turn has ended. " << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Its SITH's turn now." << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        if(round == 1){
            std::cout << "Welcome to mghtA darkboyyyy" << std::endl;
        }
        else if(libraryDark->size() != 0){
            if((int)(handDark->size()) < 7){
                int indexL = (int)(libraryDark->size()) - 1;
                handDark->push_back(libraryDark->at(indexL));
                auto ptrL = libraryDark->begin() + indexL;
                libraryDark->erase(ptrL);
            }
            else{
                std::cout << "Elin dolu oyun bitti bb" << std::endl;
                darkSide->makeLoser();
                std::cout << lightSide->getPlayerName() << " has WON with " << lightSide->getPlayerHp() << " hp" << std::endl;
                return 0;
                break;
            }
        }
        else{
            std::cout << "You do not have any card in library. You have Lost the game. " << std::endl;
            darkSide->makeLoser();
            std::cout << lightSide->getPlayerName() << " has WON with " << lightSide->getPlayerHp() << " hp" << std::endl;
            return 0;
            break;
        }
        makeWholeUntapped(handDark,discardDark,inPLayDark,libraryDark);
        darkSide->refreshWholeCards(handDark,discardDark,inPLayDark,libraryDark);
        lightSide->refreshWholeCards(handLight,discardLight,inPLayLight,libraryLight);

        bool isLandCardPlayedDR = false;
        darkSide->printHand();
        std::cout << "Do you want to play land card? If you do, Enter 1. If you do not, Enter 0." << std::endl;
        int landCardPlayedDAR;
        std::cin >> landCardPlayedDAR;
        if(landCardPlayedDAR == 1){
            std::cout << "Please Enter index of land card." << std::endl;
            int landIndex;
            std::cin >> landIndex;
            if(handDark->at(landIndex).getCardType() == 'L'){
                inPLayDark->push_back(handDark->at(landIndex));
                std::cout << "You have played " << handDark->at(landIndex).getName() << std::endl;
                auto ptr = handDark->begin() + landIndex;
                handDark->erase(ptr);
                isLandCardPlayedDR = true;
                numOfLandCardDA++;
                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
            }
            else{
                std::cout << "land kart degil  " << std::endl;
            }
        }
        if(numOfLandCardDA > 0){
            std::cout << "Do you want to make your land card tapped? If you do, Enter 1. If you do not, Enter 0." << std::endl;
            int landTapped;
            std::cin >> landTapped;
            if(landTapped == 1){
                darkSide->printInPlay();
                std::cout << "Land kart indexi cikmak icin -3" << std::endl;
                int landIndex;
                std::cin >> landIndex;
                while(landIndex != -3){
                    if(inPLayDark->at(landIndex).getCardType() == 'L' && !inPLayDark->at(landIndex).learnTapped()){
                        inPLayDark->at(landIndex).makeTapped();
                        darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                        lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                        darkSide->plusSetColorManaWithChar(inPLayDark->at(landIndex).getMana1(), inPLayDark->at(landIndex).learnManaTypes1());
                        std::cout << "You have earned " << inPLayDark->at(landIndex).getMana1() << " " << inPLayDark->at(landIndex).learnManaTypes1() << std::endl;
                        std::cout << "Your Total Mana : ";
                        darkSide->printWholeTotalMana();
                        if(numOfLandCardDA > 1){
                            std::cout << "Do you want to make another land card tapped? If you do, Enter index. If you do not, Enter -3." << std::endl;
                            std::cin >> landIndex;
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        std::cout << "index land kart indexi degil " << std::endl;
                        std::cout << "Do you want to make another land card tapped? If you do, Enter index. If you do not, Enter -3." << std::endl;
                        std::cin >> landIndex;
                    }
                }
            }
        }
        darkSide->printHand();
        std::cout << "Do you want to play another card? If you do, Enter 1. If you do not, Enter 0." << std::endl;
        int checkOtherDAAR;
        std::cin >> checkOtherDAAR;
        if(checkOtherDAAR == 1){
            std::cout << "Please Enter index of your card that you want to play. If you do not want to play, Enter -3." << std::endl;
            int indexCardWP;
            std::cin >> indexCardWP;
            while(indexCardWP != -3){
                int checkPayment = 0;
                if(handDark->at(indexCardWP).getCardType() == 'C'){
                    if(handDark->at(indexCardWP).getMana1() >= 0){
                        if(handDark->at(indexCardWP).learnManaTypes1() == 'G'){
                            if(darkSide->getMana1() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'L'){
                            if(darkSide->getMana2() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'R'){
                            if(darkSide->getMana3() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'W'){
                            if(darkSide->getMana4() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'B'){
                            if(darkSide->getMana5() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                    }
                    if (handDark->at(indexCardWP).getMana2() >= 0){
                        if(handDark->at(indexCardWP).learnManaTypes2() == 'G'){
                            if(darkSide->getMana1() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'L'){
                            if(darkSide->getMana2() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'R'){
                            if(darkSide->getMana3() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'W'){
                            if(darkSide->getMana4() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'B'){
                            if(darkSide->getMana5() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if(handDark->at(indexCardWP).learnManaTypes2() == 'X'){
                            checkPayment++;
                        }
                    }
                    if(handDark->at(indexCardWP).getMana3() >= 0){
                        if(darkSide->checkNonColorPayment(handDark->at(indexCardWP).getMana3())){
                            checkPayment++;
                        }
                    }
                    // uygulama yeri
                    if(checkPayment == 3){
                        darkSide->minusSetColorManaWithChar(handDark->at(indexCardWP).getMana1(), handDark->at(indexCardWP).learnManaTypes1());
                        darkSide->minusSetColorManaWithChar(handDark->at(indexCardWP).getMana2(), handDark->at(indexCardWP).learnManaTypes2());
                        if(darkSide->checkNonColorPayment(handDark->at(indexCardWP).getMana3())){
                            darkSide->takeNonColorPayment(handDark->at(indexCardWP).getMana3());
                            inPLayDark->push_back(handDark->at(indexCardWP));
                            std::cout << "You have played " << handDark->at(indexCardWP).getName() << std::endl;
                            std::cout << "Your Total Mana : ";
                            darkSide->printWholeTotalMana();
                            auto ptr = handDark->begin() + indexCardWP;
                            handDark->erase(ptr);
                            darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                            lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                        }
                        else{
                            darkSide->plusSetColorManaWithChar(handDark->at(indexCardWP).getMana1(), handDark->at(indexCardWP).learnManaTypes1());
                            darkSide->plusSetColorManaWithChar(handDark->at(indexCardWP).getMana2(), handDark->at(indexCardWP).learnManaTypes2());
                            std::cout << "You do not have enough MANA :( " << std::endl;

                        }
                    }
                    else{
                        std::cout << "You do not have enough MANA :( " << std::endl;
                    }
                }
                else if(handDark->at(indexCardWP).getCardType() == 'E'){
                    if(handDark->at(indexCardWP).getMana1() >= 0){
                        if(handDark->at(indexCardWP).learnManaTypes1() == 'G'){
                            if(darkSide->getMana1() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'L'){
                            if(darkSide->getMana2() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'R'){
                            if(darkSide->getMana3() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'W'){
                            if(darkSide->getMana4() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'B'){
                            if(darkSide->getMana5() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                    }
                    if (handDark->at(indexCardWP).getMana2() >= 0){
                        if(handDark->at(indexCardWP).learnManaTypes2() == 'G'){
                            if(darkSide->getMana1() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'L'){
                            if(darkSide->getMana2() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'R'){
                            if(darkSide->getMana3() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'W'){
                            if(darkSide->getMana4() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'B'){
                            if(darkSide->getMana5() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if(handDark->at(indexCardWP).learnManaTypes2() == 'X'){
                            checkPayment++;
                        }
                    }
                    if(handDark->at(indexCardWP).getMana3() >= 0){
                        if(darkSide->checkNonColorPayment(handDark->at(indexCardWP).getMana3())){
                            checkPayment++;
                        }
                    }
                    // uygulama yeri
                    if(checkPayment == 3){
                        lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                        darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);

                        darkSide->minusSetColorManaWithChar(handDark->at(indexCardWP).getMana1(), handDark->at(indexCardWP).learnManaTypes1());
                        darkSide->minusSetColorManaWithChar(handDark->at(indexCardWP).getMana2(), handDark->at(indexCardWP).learnManaTypes2());

                        if(darkSide->checkNonColorPayment(handDark->at(indexCardWP).getMana3())){
                            darkSide->takeNonColorPayment(handDark->at(indexCardWP).getMana3());
                            inPLayDark->push_back(handDark->at(indexCardWP));
                            std::cout << "You have played " << handDark->at(indexCardWP).getName() << std::endl;
                            if(handDark->at(indexCardWP).getName() == "Holy War"){
                                enchantmentEffects.allWhiteCreaturesGain11(inPLayDark, inPLayLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                            }
                            else if(handDark->at(indexCardWP).getName() == "Holy Light"){
                                enchantmentEffects.allBlackCreaturesMinus11(inPLayDark, inPLayLight);
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        goToDiscard(inPLayDark, discardDark);
                                    }
                                }
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        goToDiscard(inPLayLight, discardLight);
                                    }
                                }
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                            }
                            else if(handDark->at(indexCardWP).getName() == "Unholy War"){
                                enchantmentEffects.allBlackCreaturesGain20(inPLayDark, inPLayLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);

                            }
                            else if(handDark->at(indexCardWP).getName() == "Restrain"){
                                enchantmentEffects.allGreenCreaturesLoseTrample(inPLayDark, inPLayLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                            }
                            else if(handDark->at(indexCardWP).getName() == "Rage"){
                                std::cout<< "Which creature card, do you want to give trample? " << std::endl;
                                int indexLOLO;
                                darkSide->printInPlay();
                                std::cin >> indexLOLO;
                                enchantmentEffects.targetCreatureGainTrample(inPLayDark, indexLOLO);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                            }
                            else if(handDark->at(indexCardWP).getName() == "Slow"){
                                std::cout<< "Which enemy creature card, do you want to take it's First Strike? " << std::endl;
                                int indexLOLO;
                                lightSide->printInPlay();
                                std::cin >> indexLOLO;
                                enchantmentEffects.targetCreatureLoseFirstStrike(inPLayLight, indexLOLO);

                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                            }
                            std::cout << "The enchantment card that you have already played is, activated its effect. " << std::endl;
                            std::cout << "Your Total Mana : ";
                            darkSide->printWholeTotalMana();
                            auto ptr = handDark->begin() + indexCardWP;
                            handDark->erase(ptr);
                            darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                        }
                        else{
                            darkSide->plusSetColorManaWithChar(handDark->at(indexCardWP).getMana1(), handDark->at(indexCardWP).learnManaTypes1());
                            darkSide->plusSetColorManaWithChar(handDark->at(indexCardWP).getMana2(), handDark->at(indexCardWP).learnManaTypes2());
                            std::cout << "You do not have enough MANA :(" << std::endl;
                        }
                    }
                    else{
                        std::cout << "You do not have enough MANA :( " << std::endl;
                    }
                }
                else if(handDark->at(indexCardWP).getCardType() == 'S'){
                    if(handDark->at(indexCardWP).getMana1() >= 0){
                        if(handDark->at(indexCardWP).learnManaTypes1() == 'G'){
                            if(darkSide->getMana1() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'L'){
                            if(darkSide->getMana2() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'R'){
                            if(darkSide->getMana3() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'W'){
                            if(darkSide->getMana4() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'B'){
                            if(darkSide->getMana5() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                    }
                    if (handDark->at(indexCardWP).getMana2() >= 0){
                        if(handDark->at(indexCardWP).learnManaTypes2() == 'G'){
                            if(darkSide->getMana1() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'L'){
                            if(darkSide->getMana2() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'R'){
                            if(darkSide->getMana3() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'W'){
                            if(darkSide->getMana4() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'B'){
                            if(darkSide->getMana5() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if(handDark->at(indexCardWP).learnManaTypes2() == 'X'){
                            checkPayment++;
                        }
                    }
                    if(handDark->at(indexCardWP).getMana3() >= 0){
                        if(darkSide->checkNonColorPayment(handDark->at(indexCardWP).getMana3())){
                            checkPayment++;
                        }
                    }
                    // uygulama yeri
                    if(checkPayment == 3){
                        lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                        darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);

                        darkSide->minusSetColorManaWithChar(handDark->at(indexCardWP).getMana1(), handDark->at(indexCardWP).learnManaTypes1());
                        darkSide->minusSetColorManaWithChar(handDark->at(indexCardWP).getMana2(), handDark->at(indexCardWP).learnManaTypes2());

                        if(darkSide->checkNonColorPayment(handDark->at(indexCardWP).getMana3())){
                            darkSide->takeNonColorPayment(handDark->at(indexCardWP).getMana3());
                            discardDark->push_back(handDark->at(indexCardWP));

                            std::cout << "You have played " << handDark->at(indexCardWP).getName() << std::endl;

                            if(handDark->at(indexCardWP).getName() == "Disenchant"){
                                int indexSOSO;
                                lightSide->printInPlay();
                                std::cout<< "Which Enchantment card, do you want to destroy? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.DisenchantEffect(inPLayLight,inPLayDark,indexSOSO);
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        goToDiscard(inPLayLight, discardLight);
                                    }
                                }
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                            }
                            else if(handDark->at(indexCardWP).getName() == "Lightning Bolt"){
                                std::cout<< "Do you want to attack (2dmg) to enemy or enemy's card? If your decision is enemy, Enter 0. If your decision is enemy creature, Enter 1" << std::endl;
                                int indexControl;
                                std::cin >> indexControl;
                                if(indexControl == 0){
                                    sorceryEffects.LightningBoltEffect(lightSide);
                                    if(lightSide->getPlayerHp() <= 0){
                                        std::cout << lightSide->getPlayerName() << " has died." << std::endl;
                                        std::cout << darkSide->getPlayerName() << " has WON the game with " << darkSide->getPlayerHp() << " HP." << std::endl;
                                        return 0;
                                        break;
                                    }
                                    else{
                                        std::cout << lightSide->getPlayerName() << " has not died YET." << std::endl;
                                        std::cout << lightSide->getPlayerName() << " has " << lightSide->getPlayerHp() << " HP" << std::endl;
                                    }
                                }
                                else if(indexControl == 1){
                                    int index123;
                                    lightSide->printInPlay();
                                    std::cout<< "Which creature card, do you want to give 2 dmg ? " << std::endl;
                                    std::cin >> index123;
                                    sorceryEffects.LightningBoltEffect(inPLayLight, index123);
                                    if(inPLayLight->at(index123).getBaseHP() <= 0){
                                        std::cout << inPLayLight->at(index123).getName() << " has died." << std::endl;
                                        inPLayLight->at(index123).makeDestroyed();
                                        discardLight->push_back(inPLayLight->at(index123));
                                        auto ptr = inPLayLight->begin() + index123;
                                        inPLayLight->erase(ptr);
                                        lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                        darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                        for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                            if (inPLayDark->at(j).getBaseHP() <= 0){
                                                inPLayDark->at(j).makeDestroyed();
                                                goToDiscard(inPLayDark, discardDark);
                                            }
                                        }
                                        for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                            if (inPLayLight->at(j).getBaseHP() <= 0){
                                                inPLayDark->at(j).makeDestroyed();
                                                goToDiscard(inPLayLight, discardLight);
                                            }
                                        }
                                        lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                        darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                    }
                                    else{
                                        std::cout << inPLayLight->at(index123).getName() << " has not died YET." << std::endl;
                                        std::cout << inPLayLight->at(index123).getName() << " has " << inPLayLight->at(index123).getBaseHP() << " HP" << std::endl;
                                        lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                        darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                    }
                                }
                                else{
                                    std::cout << "Invalid Number !!" << std::endl;
                                }
                            }
                            else if(handDark->at(indexCardWP).getName() == "Flood"){
                                int indexSOSO;
                                lightSide->printInPlay();
                                std::cout<< "Which Land card, do you want to destroy? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.floodEffect(inPLayLight, indexSOSO);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        goToDiscard(inPLayDark, discardDark);
                                    }
                                }
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        goToDiscard(inPLayLight, discardLight);
                                    }
                                }
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                            }
                            else if(handDark->at(indexCardWP).getName() == "Reanimate"){
                                int indexSOSO;
                                darkSide->printDiscard();
                                std::cout<< "Which card, do you want to revive? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.ReanimateCardEffect(discardDark, handDark, indexSOSO);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                            }
                            else if(handDark->at(indexCardWP).getName() == "Plague"){
                                sorceryEffects.PlagueEffect(inPLayLight);
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        goToDiscard(inPLayDark, discardDark);
                                    }
                                }
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        std::cout << inPLayLight->at(j).getName() << " has died." << std::endl;
                                        goToDiscard(inPLayLight, discardLight);
                                    }
                                }
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);

                                lightSide->printInPlay();
                            }
                            else if(handDark->at(indexCardWP).getName() == "Terror"){
                                int indexSOSO;
                                lightSide->printInPlay();
                                std::cout<< "Which Creature card, do you want to destroy? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.terrorEffect(inPLayLight, indexSOSO);

                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        goToDiscard(inPLayLight, discardLight);
                                    }
                                }
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                            }
                            std::cout << "The sorcery card that you have already played is, activated its effect. " << std::endl;
                            std::cout << "Your Total Mana : ";
                            darkSide->printWholeTotalMana();
                            auto ptr = handDark->begin() + indexCardWP;
                            handDark->erase(ptr);
                            darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                            lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                        }
                        else{
                            darkSide->plusSetColorManaWithChar(handDark->at(indexCardWP).getMana1(), handDark->at(indexCardWP).learnManaTypes1());
                            darkSide->plusSetColorManaWithChar(handDark->at(indexCardWP).getMana2(), handDark->at(indexCardWP).learnManaTypes2());
                            std::cout << "You do not have enough MANA :(" << std::endl;
                        }
                    }
                    else{
                        std::cout << "You do not have enough MANA :( " << std::endl;
                    }
                }
                std::cout << "Do you want to play another card? If you do, Enter index. If you do not, Enter -3." << std::endl;
                std::cin>>indexCardWP;
            }
        }
        std::cout << "Do you want make your creature card defender? If you do, Enter 1" << std::endl;
        darkSide->printInPlay();
        int indexDoYouWannaMakeDAR;
        std::cin >> indexDoYouWannaMakeDAR;
        if(indexDoYouWannaMakeDAR == 1){
            std::cout << "Please Enter index of card that you want to make defender. If you do not want, Enter -3" << std::endl;
            int control;
            std::cin >> control;
            while(control != -3){
                if (!inPLayDark->at(control).learnTapped()){
                    inPLayDark->at(control).makeDefender();
                    std::cout << inPLayDark->at(control).getName() << " is defender now" << std::endl;
                    darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                    std::cout << "Do you want to make another creature card defender? If you do, Enter index. If you do not, Enter -3." << std::endl;
                    std::cin >> control;
                }
                else{
                    std::cout << inPLayDark->at(control).getName() << "This card is already tapped. Enter another valid index. If you do not want to make tapped Enter -3." << std::endl;
                    std::cin >> control;
                }
            }
        }
        std::cout << "Do you want to attack? If you do, Enter 1. If you do not, Enter 0." << std::endl;
        int indexDoYOUWANNAttackDAR;
        std::cin >> indexDoYOUWANNAttackDAR;
        if(indexDoYOUWANNAttackDAR == 1){
            darkSide->printInPlay();
            std::cout << "Chose, which card do you want to use it in attack?" <<std::endl;
            int indexAttacker;
            std::cin >> indexAttacker;
            if((0 <= indexAttacker) && (indexAttacker < (int)(inPLayDark->size()))){
                while(indexAttacker != -3 && !inPLayDark->at(indexAttacker).isAttackAnyCard() && !inPLayDark->at(indexAttacker).learnIsItDefender()) {
                    if(inPLayDark->at(indexAttacker).getCardType() == 'C'){
                        inPLayDark->at(indexAttacker).makeAttacker();
                        if(checkAreThereAnyDefender(inPLayLight)){
                            for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                if(inPLayLight->at(j).learnIsItDefender()){
                                    attackWithCreature(inPLayDark, indexAttacker, inPLayLight, j, darkSide, lightSide);
                                    lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                    darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                    for (int k = 0; k < (int)(inPLayDark->size()); ++k) {
                                        if (inPLayDark->at(k).getBaseHP() <= 0){
                                            inPLayDark->at(k).makeDestroyed();
                                            inPLayDark->at(k).resetCards();
                                            goToDiscard(inPLayDark, discardDark);
                                        }
                                    }
                                    for (int k = 0; k < (int)(inPLayLight->size()); ++k) {
                                        if (inPLayLight->at(k).getBaseHP() <= 0){
                                            inPLayDark->at(k).makeDestroyed();
                                            inPLayDark->at(k).resetCards();
                                            goToDiscard(inPLayLight, discardLight);
                                        }
                                    }
                                    lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                    darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                    if(lightSide->getPlayerHp() <= 0){
                                        return 0;
                                        break;
                                    }
                                }
                            }
                        }
                        else{
                            attackPlayer(lightSide, inPLayDark->at(indexAttacker).getAttackPower());
                            inPLayDark->at(indexAttacker).makeUsed();
                            if(lightSide->getPlayerHp() <= 0){
                                return 0;
                                break;
                            }
                            darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                            lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                        }
                    }
                    else{
                        std::cout << "You can only Attack with creature card!!!"<< std::endl;
                    }
                    std::cout << "Do you want to attack again? If you do, Enter index. If you do not, Enter -3." << std::endl;
                    std::cin >> indexAttacker;
                    if(indexAttacker == -3){
                        break;
                    }
                    if(inPLayDark->at(indexAttacker).isAttackAnyCard()){
                        std::cout << "You cannot attack again with same card. If you want to attack, Enter valid index. If you do not want to attack, Enter -3." << std::endl;
                    }
                    if(inPLayDark->at(indexAttacker).learnIsItDefender()){
                        std::cout << "You cannot attack with defender creature card. If you want to attack, Enter valid index. If you do not want to attack, Enter -3." << std::endl;
                    }
                    if(0 > indexAttacker || indexAttacker >= (int) (inPLayDark->size())){
                        std::cout << "hatali bastan g'r cikicaksan -3!!!" << std::endl;
                        std::cin >> indexAttacker;
                        if(indexAttacker == -3){
                            break;
                        }
                    }
                }

            }
            else{
                std::cout << "Invalid Number !!!" << std::endl;
            }

        }
        // play 2
        darkSide->printHand();
        if(!isLandCardPlayedDR){
            std::cout << "Do you want to play land card? If you do, Enter 1, If you do not, Enter 0." << std::endl;
            int landPlayCheck1;
            std::cin >> landPlayCheck1;
            if(landPlayCheck1 == 1){
                std::cout << "Please Enter index of land card." << std::endl;
                int landIndex2;
                std::cin >> landIndex2;
                if(handDark->at(landIndex2).getCardType() == 'L'){
                    inPLayDark->push_back(handDark->at(landIndex2));
                    std::cout << "You have played " << handDark->at(landIndex2).getName() << std::endl;
                    auto ptr = handDark->begin() + landIndex2;
                    handDark->erase(ptr);
                    isLandCardPlayedDR = true;
                    numOfLandCardDA++;
                    darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                    lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                }
                else{
                    std::cout << "hata land bolmu " << std::endl;
                }
            }
        }
        if(numOfLandCardDA > 0){
            std::cout << "Do you want to make your land card tapped? If you do, Enter 1, If you do not, Enter 0." << std::endl;
            int landTapped;
            std::cin >> landTapped;
            if(landTapped == 1){
                darkSide->printInPlay();
                std::cout << "Land kart indexi cikmak icin -3" << std::endl;
                int landIndex;
                std::cin >> landIndex;
                while(landIndex != -3){
                    if(inPLayDark->at(landIndex).getCardType() == 'L' && !inPLayDark->at(landIndex).learnTapped()){
                        inPLayDark->at(landIndex).makeTapped();
                        darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                        lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                        darkSide->plusSetColorManaWithChar(inPLayDark->at(landIndex).getMana1(), inPLayDark->at(landIndex).learnManaTypes1());
                        std::cout << "You have earned " << inPLayDark->at(landIndex).getMana1() << " " << inPLayDark->at(landIndex).learnManaTypes1() << std::endl;
                        std::cout << "Your Total Mana : ";
                        darkSide->printWholeTotalMana();
                        if(numOfLandCardDA > 1){
                            std::cout << "Do you want to make tapped another land card? If you do, Enter index, If you do not, Enter -3." << std::endl;
                            std::cin >> landIndex;
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        std::cout << "land degil veya tapped yapilmis kart " << std::endl;
                        std::cout << "Do you want to make tapped another land card? If you do, Enter index, If you do not, Enter -3." << std::endl;
                        std::cin >> landIndex;
                    }
                }
            }
        }
        std::cout << "Do you want to play another card? If you do, Enter 1, If you do not, Enter 0." << std::endl;
        int checkOtherD1R;
        std::cin >> checkOtherD1R;
        if(checkOtherD1R == 1){
            darkSide->printInPlay();
            std::cout << "Please enter index of card that you want to play. If you do not want to play Enter -3." << std::endl;
            int indexCardWP;
            std::cin >> indexCardWP;
            while(indexCardWP != -3){
                int checkPayment = 0;
                if(handDark->at(indexCardWP).getCardType() == 'C'){
                    if(handDark->at(indexCardWP).getMana1() >= 0){
                        if(handDark->at(indexCardWP).learnManaTypes1() == 'G'){
                            if(darkSide->getMana1() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'L'){
                            if(darkSide->getMana2() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'R'){
                            if(darkSide->getMana3() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'W'){
                            if(darkSide->getMana4() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'B'){
                            if(darkSide->getMana5() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                    }
                    if (handDark->at(indexCardWP).getMana2() >= 0){
                        if(handDark->at(indexCardWP).learnManaTypes2() == 'G'){
                            if(darkSide->getMana1() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'L'){
                            if(darkSide->getMana2() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'R'){
                            if(darkSide->getMana3() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'W'){
                            if(darkSide->getMana4() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'B'){
                            if(darkSide->getMana5() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if(handDark->at(indexCardWP).learnManaTypes2() == 'X'){
                            checkPayment++;
                        }
                    }
                    if(handDark->at(indexCardWP).getMana3() >= 0){
                        if(darkSide->checkNonColorPayment(handDark->at(indexCardWP).getMana3())){
                            checkPayment++;
                        }
                    }
                    // uygulama yeri
                    if(checkPayment == 3){
                        darkSide->minusSetColorManaWithChar(handDark->at(indexCardWP).getMana1(), handDark->at(indexCardWP).learnManaTypes1());
                        darkSide->minusSetColorManaWithChar(handDark->at(indexCardWP).getMana2(), handDark->at(indexCardWP).learnManaTypes2());
                        if(darkSide->checkNonColorPayment(handDark->at(indexCardWP).getMana3())){
                            darkSide->takeNonColorPayment(handDark->at(indexCardWP).getMana3());
                            inPLayDark->push_back(handDark->at(indexCardWP));
                            std::cout << "You have played " << handDark->at(indexCardWP).getName() << std::endl;
                            std::cout << "Your Total Mana : ";
                            darkSide->printWholeTotalMana();
                            auto ptr = handDark->begin() + indexCardWP;
                            handDark->erase(ptr);
                            darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                            lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                        }
                        else{
                            darkSide->plusSetColorManaWithChar(handDark->at(indexCardWP).getMana1(), handDark->at(indexCardWP).learnManaTypes1());
                            darkSide->plusSetColorManaWithChar(handDark->at(indexCardWP).getMana2(), handDark->at(indexCardWP).learnManaTypes2());
                            std::cout << "You do not have enough MANA :( " << std::endl;

                        }
                    }
                    else{
                        std::cout << "You do not have enough MANA :( " << std::endl;
                    }
                }
                else if(handDark->at(indexCardWP).getCardType() == 'E'){
                    if(handDark->at(indexCardWP).getMana1() >= 0){
                        if(handDark->at(indexCardWP).learnManaTypes1() == 'G'){
                            if(darkSide->getMana1() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'L'){
                            if(darkSide->getMana2() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'R'){
                            if(darkSide->getMana3() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'W'){
                            if(darkSide->getMana4() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'B'){
                            if(darkSide->getMana5() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                    }
                    if (handDark->at(indexCardWP).getMana2() >= 0){
                        if(handDark->at(indexCardWP).learnManaTypes2() == 'G'){
                            if(darkSide->getMana1() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'L'){
                            if(darkSide->getMana2() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'R'){
                            if(darkSide->getMana3() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'W'){
                            if(darkSide->getMana4() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'B'){
                            if(darkSide->getMana5() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if(handDark->at(indexCardWP).learnManaTypes2() == 'X'){
                            checkPayment++;
                        }
                    }
                    if(handDark->at(indexCardWP).getMana3() >= 0){
                        if(darkSide->checkNonColorPayment(handDark->at(indexCardWP).getMana3())){
                            checkPayment++;
                        }
                    }
                    // uygulama yeri
                    if(checkPayment == 3){
                        lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                        darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);

                        darkSide->minusSetColorManaWithChar(handDark->at(indexCardWP).getMana1(), handDark->at(indexCardWP).learnManaTypes1());
                        darkSide->minusSetColorManaWithChar(handDark->at(indexCardWP).getMana2(), handDark->at(indexCardWP).learnManaTypes2());

                        if(darkSide->checkNonColorPayment(handDark->at(indexCardWP).getMana3())){
                            darkSide->takeNonColorPayment(handDark->at(indexCardWP).getMana3());
                            inPLayDark->push_back(handDark->at(indexCardWP));
                            std::cout << "You have played " << handDark->at(indexCardWP).getName() << std::endl;
                            if(handDark->at(indexCardWP).getName() == "Holy War"){
                                enchantmentEffects.allWhiteCreaturesGain11(inPLayDark, inPLayLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                            }
                            else if(handDark->at(indexCardWP).getName() == "Holy Light"){
                                enchantmentEffects.allBlackCreaturesMinus11(inPLayDark, inPLayLight);
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        goToDiscard(inPLayDark, discardDark);
                                    }
                                }
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        goToDiscard(inPLayLight, discardLight);
                                    }
                                }
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                            }
                            else if(handDark->at(indexCardWP).getName() == "Unholy War"){
                                enchantmentEffects.allBlackCreaturesGain20(inPLayDark, inPLayLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);

                            }
                            else if(handDark->at(indexCardWP).getName() == "Restrain"){
                                enchantmentEffects.allGreenCreaturesLoseTrample(inPLayDark, inPLayLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                            }
                            else if(handDark->at(indexCardWP).getName() == "Rage"){
                                std::cout<< "Which creature card, do you want to give trample? " << std::endl;
                                int indexLOLO;
                                darkSide->printInPlay();
                                std::cin >> indexLOLO;
                                enchantmentEffects.targetCreatureGainTrample(inPLayDark, indexLOLO);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                            }
                            else if(handDark->at(indexCardWP).getName() == "Slow"){
                                std::cout<< "Which enemy creature card, do you want to take it's First Strike? " << std::endl;
                                int indexLOLO;
                                lightSide->printInPlay();
                                std::cin >> indexLOLO;
                                enchantmentEffects.targetCreatureLoseFirstStrike(inPLayLight, indexLOLO);

                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                            }
                            std::cout << "The enchantment card that you have already played is, activated its effect. " << std::endl;
                            std::cout << "Your Total Mana : ";
                            darkSide->printWholeTotalMana();
                            auto ptr = handDark->begin() + indexCardWP;
                            handDark->erase(ptr);
                            darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                        }
                        else{
                            darkSide->plusSetColorManaWithChar(handDark->at(indexCardWP).getMana1(), handDark->at(indexCardWP).learnManaTypes1());
                            darkSide->plusSetColorManaWithChar(handDark->at(indexCardWP).getMana2(), handDark->at(indexCardWP).learnManaTypes2());
                            std::cout << "You do not have enough MANA :(" << std::endl;
                        }
                    }
                    else{
                        std::cout << "You do not have enough MANA :( " << std::endl;
                    }
                }
                else if(handDark->at(indexCardWP).getCardType() == 'S'){
                    if(handDark->at(indexCardWP).getMana1() >= 0){
                        if(handDark->at(indexCardWP).learnManaTypes1() == 'G'){
                            if(darkSide->getMana1() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'L'){
                            if(darkSide->getMana2() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'R'){
                            if(darkSide->getMana3() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'W'){
                            if(darkSide->getMana4() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes1() == 'B'){
                            if(darkSide->getMana5() - handDark->at(indexCardWP).getMana1() >= 0){
                                checkPayment++;
                            }
                        }
                    }
                    if (handDark->at(indexCardWP).getMana2() >= 0){
                        if(handDark->at(indexCardWP).learnManaTypes2() == 'G'){
                            if(darkSide->getMana1() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'L'){
                            if(darkSide->getMana2() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'R'){
                            if(darkSide->getMana3() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'W'){
                            if(darkSide->getMana4() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if (handDark->at(indexCardWP).learnManaTypes2() == 'B'){
                            if(darkSide->getMana5() - handDark->at(indexCardWP).getMana2() >= 0){
                                checkPayment++;
                            }
                        }
                        else if(handDark->at(indexCardWP).learnManaTypes2() == 'X'){
                            checkPayment++;
                        }
                    }
                    if(handDark->at(indexCardWP).getMana3() >= 0){
                        if(darkSide->checkNonColorPayment(handDark->at(indexCardWP).getMana3())){
                            checkPayment++;
                        }
                    }
                    // uygulama yeri
                    if(checkPayment == 3){
                        lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                        darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);

                        darkSide->minusSetColorManaWithChar(handDark->at(indexCardWP).getMana1(), handDark->at(indexCardWP).learnManaTypes1());
                        darkSide->minusSetColorManaWithChar(handDark->at(indexCardWP).getMana2(), handDark->at(indexCardWP).learnManaTypes2());

                        if(darkSide->checkNonColorPayment(handDark->at(indexCardWP).getMana3())){
                            darkSide->takeNonColorPayment(handDark->at(indexCardWP).getMana3());
                            discardDark->push_back(handDark->at(indexCardWP));

                            std::cout << "You have played " << handDark->at(indexCardWP).getName() << std::endl;

                            if(handDark->at(indexCardWP).getName() == "Disenchant"){
                                int indexSOSO;
                                lightSide->printInPlay();
                                std::cout<< "Which Enchantment card, do you want to destroy? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.DisenchantEffect(inPLayLight,inPLayDark,indexSOSO);
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        goToDiscard(inPLayLight, discardLight);
                                    }
                                }
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                            }
                            else if(handDark->at(indexCardWP).getName() == "Lightning Bolt"){
                                std::cout<< "Do you want to attack (2dmg) to enemy or enemy's card, If your decision is enemy, Enter 0. If your decision is enemy, creature Enter 1." << std::endl;
                                int indexControl;
                                std::cin >> indexControl;
                                if(indexControl == 0){
                                    sorceryEffects.LightningBoltEffect(lightSide);
                                    if(lightSide->getPlayerHp() <= 0){
                                        std::cout << lightSide->getPlayerName() << " has died." << std::endl;
                                        std::cout << darkSide->getPlayerName() << " has WON the game with " << darkSide->getPlayerHp() << " HP." << std::endl;
                                        return 0;
                                        break;
                                    }
                                    else{
                                        std::cout << lightSide->getPlayerName() << " has not died YET." << std::endl;
                                        std::cout << lightSide->getPlayerName() << " has " << lightSide->getPlayerHp() << " HP" << std::endl;
                                    }
                                }
                                else if(indexControl == 1){
                                    int index123;
                                    lightSide->printInPlay();
                                    std::cout<< "Which creature card, do you want to give 2 dmg ? " << std::endl;
                                    std::cin >> index123;
                                    sorceryEffects.LightningBoltEffect(inPLayLight, index123);
                                    if(inPLayLight->at(index123).getBaseHP() <= 0){
                                        std::cout << inPLayLight->at(index123).getName() << " has died." << std::endl;
                                        inPLayLight->at(index123).makeDestroyed();
                                        discardLight->push_back(inPLayLight->at(index123));
                                        auto ptr = inPLayLight->begin() + index123;
                                        inPLayLight->erase(ptr);
                                        lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                        darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                        for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                            if (inPLayDark->at(j).getBaseHP() <= 0){
                                                inPLayDark->at(j).makeDestroyed();
                                                goToDiscard(inPLayDark, discardDark);
                                            }
                                        }
                                        for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                            if (inPLayLight->at(j).getBaseHP() <= 0){
                                                inPLayDark->at(j).makeDestroyed();
                                                goToDiscard(inPLayLight, discardLight);
                                            }
                                        }
                                        lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                        darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                    }
                                    else{
                                        std::cout << inPLayLight->at(index123).getName() << " has not died YET." << std::endl;
                                        std::cout << inPLayLight->at(index123).getName() << " has " << inPLayLight->at(index123).getBaseHP() << " HP" << std::endl;
                                        lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                        darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                    }
                                }
                                else{
                                    std::cout << "Invalid Number !!" << std::endl;
                                }
                            }
                            else if(handDark->at(indexCardWP).getName() == "Flood"){
                                int indexSOSO;
                                lightSide->printInPlay();
                                std::cout<< "Which Land card, do you want to destroy? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.floodEffect(inPLayLight, indexSOSO);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        goToDiscard(inPLayDark, discardDark);
                                    }
                                }
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        goToDiscard(inPLayLight, discardLight);
                                    }
                                }
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                            }
                            else if(handDark->at(indexCardWP).getName() == "Reanimate"){
                                int indexSOSO;
                                darkSide->printDiscard();
                                std::cout<< "Which card, do you want to revive? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.ReanimateCardEffect(discardDark, handDark, indexSOSO);
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                            }
                            else if(handDark->at(indexCardWP).getName() == "Plague"){
                                sorceryEffects.PlagueEffect(inPLayLight);
                                for (int j = 0; j < (int)(inPLayDark->size()); ++j) {
                                    if (inPLayDark->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        goToDiscard(inPLayDark, discardDark);
                                    }
                                }
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        std::cout << inPLayLight->at(j).getName() << " has died." << std::endl;
                                        goToDiscard(inPLayLight, discardLight);
                                    }
                                }
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);

                                lightSide->printInPlay();
                            }
                            else if(handDark->at(indexCardWP).getName() == "Terror"){
                                int indexSOSO;
                                lightSide->printInPlay();
                                std::cout<< "Which Creature card, do you want to destroy? " << std::endl;
                                std::cin >> indexSOSO;
                                sorceryEffects.terrorEffect(inPLayLight, indexSOSO);

                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                                for (int j = 0; j < (int)(inPLayLight->size()); ++j) {
                                    if (inPLayLight->at(j).getBaseHP() <= 0){
                                        inPLayDark->at(j).makeDestroyed();
                                        goToDiscard(inPLayLight, discardLight);
                                    }
                                }
                                lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                                darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                            }
                            std::cout << "The sorcery card that you have already played is, activated its effect. " << std::endl;
                            std::cout << "Your Total Mana : ";
                            darkSide->printWholeTotalMana();
                            auto ptr = handDark->begin() + indexCardWP;
                            handDark->erase(ptr);
                            darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
                            lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
                        }
                        else{
                            darkSide->plusSetColorManaWithChar(handDark->at(indexCardWP).getMana1(), handDark->at(indexCardWP).learnManaTypes1());
                            darkSide->plusSetColorManaWithChar(handDark->at(indexCardWP).getMana2(), handDark->at(indexCardWP).learnManaTypes2());
                            std::cout << "You do not have enough MANA :(" << std::endl;
                        }
                    }
                    else{
                        std::cout << "You do not have enough MANA :( " << std::endl;
                    }
                }
                std::cout << "Do you want to play another card? If you do, Enter index, If you do not, Enter -3." << std::endl;
                std::cin>>indexCardWP;
            }
        }

        lightSide->refreshWholeCards(handLight, discardLight, inPLayLight, libraryLight);
        darkSide->refreshWholeCards(handDark, discardDark, inPLayDark, libraryDark);
        std::cout << "SITH's turn has ended. " << std::endl;
        darkSide->resetMana();
        isLandCardsPlayedR = false;
        isLandCardPlayedDR = false;
        std::cout << "End of The "<< round <<" Round." << std::endl;
        round++;
        if(lightSide->getPlayerHp() <= 0 || !lightSide->isAlive()){
            std::cout << "oldun cik" << std::endl;
            lightSide->makeLoser();
            std::cout << darkSide->getPlayerName() << " is won with " << darkSide->getPlayerHp() << " hp" << std::endl;
            return 0;
            break;

        }
        if(darkSide->getPlayerHp() <= 0 || !darkSide->isAlive()){
            std::cout << "Elin dolu oyun bitti bb" << std::endl;
            darkSide->makeLoser();
            std::cout << lightSide->getPlayerName() << " is won with " << lightSide->getPlayerHp() << " hp" << std::endl;
            return 0;
            break;
        }

    }
    return 0;
}
