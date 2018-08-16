#include "main.h"

#ifndef BARELL_H
#define BARELL_H


class Barell {
public:
    Barell() {}
    Barell(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    int giftidx;
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
