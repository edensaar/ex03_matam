
#include "HealthPoints.h"


HealthPoints::HealthPoints(int hp, int maxHP ) {
    if(hp <= 0){
        throw InvalidArgument();
    }
    else{
        this->hp = hp;
        this->maxHP = hp;
    }
}

HealthPoints& HealthPoints::operator+=(const int add) {
    if(this->hp + add > this->maxHP){
        this->hp = this->maxHP;
    }
    else{
        this->hp += add;
    }
    return *this;
}

HealthPoints operator+(const int add, const HealthPoints& obj) {
   HealthPoints result = obj;
   if(result.hp + add > result.maxHP){
       result.hp = result.maxHP;
   }
   else{
       result.hp += add;
   }
   return result;
}

HealthPoints operator+(const HealthPoints& obj, const int add) {
    HealthPoints result = obj;
    if(result.hp + add > result.maxHP){
        result.hp = result.maxHP;
    }
    else{
        result.hp += add;
    }
    return result;
}

HealthPoints& HealthPoints::operator-=(const int subs) {
    if(this->hp - subs < 0){
        this->hp = 0;
    }
    else{
        this->hp -= subs;
    }
    return *this;
}

HealthPoints operator-(const int subs, const HealthPoints& obj) {
    HealthPoints result = obj;
    if(result.hp - subs < 0){
        result.hp = 0;
    }
    else{
        result.hp -= subs;
    }
    return result;
}

HealthPoints operator-(const HealthPoints& obj, const int subs) {
    HealthPoints result = obj;
    if(result.hp - subs < 0){
        result.hp = 0;
    }
    else{
        result.hp -= subs;
    }
    return result;
}


bool operator==(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    if(healthPoints1.hp == healthPoints2.hp){
        return true;
    }
    return false;
}

bool operator<(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    if(healthPoints1.hp < healthPoints2.hp){
            return true;
        }
    return false;
}

bool operator<=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    if(healthPoints1 < healthPoints2 || healthPoints1 == healthPoints2){
        return true;
    }
    return false;
}

bool operator>=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    if(healthPoints1 > healthPoints2 || healthPoints1 == healthPoints2){
        return true;
    }
    return false;
}

bool operator>(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    if(healthPoints1 > healthPoints2){
        return true;
    }
    return false;
}

bool operator!=(const HealthPoints& healthPoints1, const HealthPoints& healthPoints2){
    if(healthPoints1 == healthPoints2){
        return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& healthPoints){
    os << healthPoints.hp << "(" << healthPoints.maxHP << ")";
    return os;
}


int main(){
    HealthPoints healthPoints1; // has 100 points out of 100
    HealthPoints healthPoints2(150); // has 150 points out of 150 //
    healthPoints1 -= 20; // now has 80 points out of 100 //
    healthPoints1 += 100; // now has 100 points out of 100 //
    healthPoints1 -= 150; // now has 0 points out of 100 //
    //healthPoints2 -= 80;
    healthPoints2 = healthPoints2 - 160; // now has 0 points out of 150 //
    healthPoints2 = 160 + healthPoints1; // healthPoints2 now has 100 out of 100,
//healthPoints1 is unchanged //
    std::cout << healthPoints2 <<std::endl;
    std::cout << healthPoints1 << ", " << healthPoints2;

    bool comparisonResult;
    HealthPoints healthPoints3(100);
    HealthPoints healthPoints4 = 100; /* 100 points out of 100 */
    comparisonResult = (healthPoints3 == healthPoints4); /* returns true */
    healthPoints4 = HealthPoints(150); /* has 150 points out of 150 */
    comparisonResult = (healthPoints3 == healthPoints4); /* returns false */
    healthPoints4 -= 50; /* now has 100 points out of 150 */
    comparisonResult = (100 == healthPoints4); /* returns true */
    comparisonResult = (healthPoints3 < healthPoints4); /* returns false */
    healthPoints3 -= 50; /* now has 50 points out of 100 */
    comparisonResult = (healthPoints3 < healthPoints4); /* returns true */
    std::cout << healthPoints3 << ", " << healthPoints4;
    return 0;
}
