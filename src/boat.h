#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z, color_t color);
    glm::vec3 position;
    int jflag;
    float rotation;
    color_t mcolor;
    void draw(glm::mat4 VP);
    void draw1(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    void tick();
    double speed;
    double speedz;
private:
    VAO *object2;
    VAO *object1;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;

};

#endif // BALL_H
