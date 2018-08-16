#include "main.h"

#ifndef GIFTS_H
#define GIFTS_H


class Gifts {
public:
    Gifts() {}
    Gifts(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    int health;
    int mflag;
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
