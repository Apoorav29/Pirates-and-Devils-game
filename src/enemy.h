#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    int health;
    int xflag;
    int yflag;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speedz;
private:
    VAO *object1;
    VAO *object2;

};

#endif 
