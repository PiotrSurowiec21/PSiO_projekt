#ifndef SHOOTINGRANGE_H
#define SHOOTINGRANGE_H
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class obiect: public sf::Sprite{
protected:

public:
    obiect(sf::Vector2f position ){
        setPosition(position);
    }

    ~obiect(){
    }
};

class target: public obiect{
protected:
    double DisplayTime;
    sf::FloatRect bounds;
    sf::Vector2f position;
    float speedPerSec=0;
    int scale;
    bool isShow=true;
public:
    target(sf::Texture & texture, sf::Vector2f position, int Scale, float velocity, float time): obiect(position){
        setTexture(texture);
        scale=Scale;
        DisplayTime=time;
        speedPerSec=velocity;
        switch (Scale) {
        case 1: setScale(1,1);
            break;
        case 2: setScale(2,2);
            break;
        case 3: setScale(3,3);
            break;
        }
        bounds=getGlobalBounds();
    }

    int hit(sf::Vector2f GPPos){
        sf::Vector2f center=sf::Vector2f(bounds.left+(bounds.width/2), bounds.top+(bounds.height/2));
        float r1 = 21*scale, r2 = 10*scale;
        int points=0;
        if(GPPos.x>=bounds.left && GPPos.x<=(bounds.left+bounds.width) &&
                GPPos.y>=bounds.top && GPPos.y<=bounds.top+bounds.height){
            points++;
            isShow=false;
           if(powf(GPPos.x-center.x, 2)<=((r1*r1)-powf(GPPos.y-center.y,2))){
                points++;
                if(powf(GPPos.x-center.x, 2)<=((r2*r2)-powf(GPPos.y-center.y,2))){
                    points++;
                }
            }
        }
        return (points*10)/scale;
    }

    void animate(float fTime){
        if(bounds.left<(150/scale)){
            speedPerSec=fabs(speedPerSec);
        }
        else if (bounds.left+bounds.width>1600-(150/scale)) {
            speedPerSec=-(fabs(speedPerSec));
        }
        move(speedPerSec*fTime, 0);
        bounds=getGlobalBounds();
    }

    bool hide(float time){
        if(isShow==1){
            if(time>DisplayTime){
                isShow=false;
                return true;
            }
            else{return false;}
        }
    }

    bool show(){
        return isShow;
    }

    float getSpeed(){
        return speedPerSec;
    }

    ~target(){}
};

class player: public obiect{
protected:
    int score=0;
    int hp=5;
public:
    player(sf::Texture & texture,sf::Vector2f position, sf::Vector2f scale) : obiect(position){
        setTexture(texture);
        setScale(scale);
        score=0;
        hp=5;
    }

    sf::Vector2f checkIfHit(){
        sf::FloatRect bounds= getGlobalBounds();
        sf::Vector2f centerPos(bounds.left+(bounds.width/2), bounds.top+(bounds.height/2));
        //std::cout<<centerPos.x<<"   "<<centerPos.y<<std::endl;
        return centerPos;
    }

    void move(sf::Vector2f Recoil, sf::RenderWindow & window){
        sf::Vector2f mousePos= window.mapPixelToCoords(sf::Mouse::getPosition(window))+Recoil;
        setPosition(mousePos);
    }

    void modifyStats(int points){
        if(points==0){
            hp--;
        }
        else {
            score+=points;
        }
        std::cout<<"hp:"<<hp<<"      score:"<<score<<std::endl;
    }

    int getHP(){return hp;};

    int getScore(){return score;}

    void defaults(){
        score=0;
        hp=5;
    }

    ~player(){}
};

class bulletMarks: public obiect{
public:
    bulletMarks(sf::Vector2f point, sf::Texture & texture, sf::Vector2f scale):obiect(point){
        setTexture(texture);
        setScale(scale);
    }
    ~bulletMarks() {std::cout<<"USUNIETO OBIEKT PRZESTRZELINA"<<std::endl;}
};



class gameplay{
protected:
    int lvl=1;
    player* Player;
    std::vector<target*> Target;
    std::vector<bulletMarks*> BulletMarks;
    sf::Vector2f recoil;
    std::vector<sf::Sprite> hpSprites;
    sf::Sprite* heart;
    sf::Text counter, gameOver;
    bool roundCreated=false;
    float velocity = 0;
    int x=100;

public:
    gameplay(sf::Texture & texture,sf::Vector2f position1, sf::Vector2f scale, sf::Font& font){
        this->Player=new player (texture, position1, scale);
        counter.setFont(font);
        counter.setPosition(1425, 25);
        counter.setCharacterSize(60);
        counter.setColor(sf::Color::Black);
        gameOver.setFont(font);
        gameOver.setPosition(450, 200);
        gameOver.setCharacterSize(100);
        gameOver.setColor(sf::Color::Red);
        gameOver.setString("GAME OVER");
}

    void generateObiects(sf::Texture & texture, sf::Clock& clock, sf::Texture& texture2){
        float dt;
        if(roundCreated==0){
            std::vector<sf::FloatRect> bounds;
            if(lvl<4){
                dt=7;
                for(int i = 0; i<lvl; i++){
                    dt*=0.8;
                    Target.emplace_back(new target(texture, sf::Vector2f(rand()%1300+150, 300), 3, 0, dt));
                    sf::FloatRect aRec=Target[i]->getGlobalBounds();
                    if(lvl!=1){
                        for(int j=0;j<bounds.size();j++){
                            if((bounds[j].left>=aRec.left+aRec.width <= bounds[j].left+bounds[j].width) ||
                                    (bounds[j].left>=aRec.left <= bounds[j].left+bounds[j].width)){
                                std::cout<<"warunek spelnony"<<std::endl;
                                if(Target[i]->getPosition().x<=550){Target[i]->move(150,0);}
                                else{Target[i]->move(-150,0);}
                                aRec=Target[i]->getGlobalBounds();
                            }
                        }
                    }
                    bounds.emplace_back(aRec);
                }
            }
            else if(lvl>=4 && lvl<=6){
                dt=5;
                for(int i = 0; i<3; i++){
                    dt*=0.8;
                    Target.emplace_back(new target(texture, sf::Vector2f(rand()%1300+150, 300), (rand()%3)+1, 0, dt));
                    sf::FloatRect aRec=Target[i]->getGlobalBounds();

                    for(int j=0;j<bounds.size();j++){
                        if(bounds[j].left>=aRec.left+aRec.width <= bounds[j].left+bounds[j].width ||
                                bounds[j].left>=aRec.left <= bounds[j].left+bounds[j].width){
                            std::cout<<"warunek spelnony"<<std::endl;
                            if(Target[i]->getPosition().x<=550){Target[i]->move(150,0);}
                            else{Target[i]->move(-150,0);}
                            aRec=Target[i]->getGlobalBounds();
                        }
                    }
                    bounds.emplace_back(aRec);
                }
            }
            else if(lvl>=7){
                dt=5;
                for(int i = 0; i<3; i++){
                    dt=dt*0.8;
                    velocity = (rand()%25)+x;
                    x+=10;
                    if((rand()%2)+1==1){velocity*=-1;}
                    Target.emplace_back(new target(texture, sf::Vector2f(rand()%1300+150, 300), (rand()%3)+1, velocity, dt));
                    sf::FloatRect aRec=Target[i]->getGlobalBounds();
                    for(int j=0;j<bounds.size();j++){
                        if(bounds[j].left>=aRec.left+aRec.width <= bounds[j].left+bounds[j].width ||
                                bounds[j].left>=aRec.left <= bounds[j].left+bounds[j].width){
                            std::cout<<"warunek spelnony"<<std::endl;
                            if(Target[i]->getPosition().x<=550){Target[i]->move(150,0);}
                            else{Target[i]->move(-150,0);}
                            aRec=Target[i]->getGlobalBounds();

                        }
                    }
                    bounds.emplace_back(aRec);
                }
            }
           if(lvl==1){
               for(int i=0; i<=Player->getHP(); i++){
                   sf::Sprite x;
                   x.setTexture(texture2);
                   x.setScale(0.05, 0.05);
                   x.setPosition(25+i*70, 25);
                   hpSprites.emplace_back(x);
               }
           }
           clock.restart();
           roundCreated=true;

       }
}

    void drawAll(sf::RenderWindow& window){
        if(Player->getHP()<=0){
            window.draw(gameOver);
        }
        else{
            for(auto& BM: BulletMarks){
                window.draw(*BM);
            }
            for(auto &a : Target){
                if(a->show()){
                    window.draw(*a);
                }
            }
            for(auto& HP: hpSprites){
                window.draw(HP);
            }
            window.draw(*Player);

            window.draw(counter);
        }
        window.draw(counter);
    }

    void onEvent(sf::Event& event, sf::Texture& BulletMarkTex){
        if (event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Left) {
                recoil=sf::Vector2f((std::rand()%20)-20,(std::rand()%20)-10);
                int isHit=0;
                for(auto i=0; i<Target.size(); i++){
                    isHit+=Target[i]->hit(Player->checkIfHit());
                    BulletMarks.emplace_back(new bulletMarks(Player->checkIfHit()-sf::Vector2f(12,12), BulletMarkTex, sf::Vector2f(0.1, 0.1)));
                }
                Player->modifyStats(isHit);
            }
        }
        if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space ){
                defaultValues();
        }
    }

    void updateAll(sf::RenderWindow& window, float tAnim, float tFrame){
        Player->move(recoil, window);
        for(auto &a : Target){
            bool b=a->hide(tAnim);
            if(b){

            }
        }
        for(auto &a : Target){
            a->animate(tFrame);
        }
        if(hpSprites.size()>Player->getHP()){
            hpSprites.pop_back();
        }
        counter.setString(std::to_string(Player->getScore()));
    }

    void nextRound(){
        if(roundCreated==true){
            int howManyIsShow=0;
            for(auto &a : Target){
                if(!a->show()){howManyIsShow++;}
            }
            if(howManyIsShow==Target.size()){
                Target.clear();
                //BulletMarks.clear();
                lvl++;
                roundCreated=false;
            }
        }
    }


    void defaultValues(){
        lvl=1;
        roundCreated=false;
        velocity = 0;
        x=100;
        Target.clear();
        BulletMarks.clear();
        Player->defaults();
    }
};

#endif // SHOOTINGRANGE_H
