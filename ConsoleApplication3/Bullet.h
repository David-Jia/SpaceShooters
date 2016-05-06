#ifndef bullet_h
#define bullet_h

class Bullet
{
private:
    static unsigned int numBullets;
    static unsigned int numHits;
    double hitRatio;
    bool isTouchingPlayer;
    bool isTouchingEnemy;
    int speed;
    bool bulletType;//if true: bullet is a player bullet. if false: bullet is an enemy bullet
    

public:
    Bullet();
    bool isTouchingEntity();
    
    //getters
    bool getIsTouchingPlayer();//const {return isTouchingPlayer;}
    bool getIsTouchingEnemy();//const {return isTouchingEnemy;}
    bool getBulletType();//const {return buletType;}
    int getSpeed()const {return speed;}
    
    
    //setters
    void setSpeed(int speed){this->speed = speed;}
    void setIsTouchingPlayer(bool isTouchingPlayer);
    void setBulletType(bool bulletType){this->bulletType=bulletType;}
    
};
#endif /* bullet_h */
