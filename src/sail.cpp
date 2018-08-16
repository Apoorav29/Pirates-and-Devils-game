#include "sail.h"
#include "main.h"
#include "math.h"

Sail::Sail(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speedz=0.006;
    this->jflag=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data1[]={
        this->position.x+1, this->position.y, this->position.z+0.9,
        this->position.x-1, this->position.y, this->position.z+0.9,
        this->position.x, this->position.y, this->position.z+2.5,

    };

    this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_ORANGE, GL_FILL);
}

void Sail::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);

}

void Sail::tick() {
    if(this->jflag==0)
    {
        // if(this->speedz>0)
        // {
            // this->speedz=-1;
        this->position.z+=this->speedz; 
        // }
        // else if(this->speedz<0)
            // this->position.z += this->speedz;
        if(this->position.z>=0.09){
            this->speedz=-0.004;
        }
        if(this->position.z<=-0.09)
            this->speedz=0.004;
    }
    else
    {
        this->position.z+=this->speedz;
        this->speedz-=0.01;
    }
    if(this->position.z<=0 && this->jflag==1)
    {

        this->position.z=0.004;
        this->jflag=0;
    }
}
void Sail::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

