#include "main.h"

#ifndef CANON_H
#define CANON_H


class Canon {
public:
    Canon() {}
    Canon(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    float inclination;
    int jflag;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speedz;
private:
    VAO *object1;

};

#endif 
