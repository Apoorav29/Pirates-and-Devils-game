#include "main.h"

#ifndef STONE_H
#define STONE_H


class Stone {
public:
    Stone() {}
    Stone(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;

};

#endif 
