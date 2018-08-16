#include "main.h"

#ifndef SAIL_H
#define SAIL_H


class Sail {
public:
    Sail() {}
    Sail(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    int jflag;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speedz;
private:
    VAO *object1;

};

#endif 
