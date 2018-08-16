#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H


class Monster {
public:
    Monster() {}
    Monster(float x, float y,float z, color_t color);
    glm::vec3 position;
    int health;
    float rotation;
    void draw(glm::mat4 VP);
    void draw1(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speedz;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif 
