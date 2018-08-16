#include "gifts.h"
#include "main.h"
#include "math.h"

Gifts::Gifts(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->mflag=0;
    GLfloat vertex_buffer_data1[]={
	    -0.15f,-0.15f,-0.15f, // triangle 1 : begin
        -0.15f,-0.15f, 0.15f,
        -0.15f, 0.15f, 0.15f, // triangle 1 : end
        0.15f, 0.15f,-0.15f, // triangle 2 : begin
        -0.15f,-0.15f,-0.15f,
        -0.15f, 0.15f,-0.15f, // triangle 2 : end
        0.15f,-0.15f, 0.15f,
        -0.15f,-0.15f,-0.15f,
        0.15f,-0.15f,-0.15f,
        0.15f, 0.15f,-0.15f,
        0.15f,-0.15f,-0.15f,
        -0.15f,-0.15f,-0.15f,
        -0.15f,-0.15f,-0.15f,
        -0.15f, 0.15f, 0.15f,
        -0.15f, 0.15f,-0.15f,
        0.15f,-0.15f, 0.15f,
        -0.15f,-0.15f, 0.15f,
        -0.15f,-0.15f,-0.15f,
        -0.15f, 0.15f, 0.15f,
        -0.15f,-0.15f, 0.15f,
        0.15f,-0.15f, 0.15f,
        0.15f, 0.15f, 0.15f,
        0.15f,-0.15f,-0.15f,
        0.15f, 0.15f,-0.15f,
        0.15f,-0.15f,-0.15f,
        0.15f, 0.15f, 0.15f,
        0.15f,-0.15f, 0.15f,
        0.15f, 0.15f, 0.15f,
        0.15f, 0.15f,-0.15f,
        -0.15f, 0.15f,-0.15f,
        0.15f, 0.15f, 0.15f,
        -0.15f, 0.15f,-0.15f,
        -0.15f, 0.15f, 0.15f,
        0.15f, 0.15f, 0.15f,
        -0.15f, 0.15f, 0.15f,
        0.15f,-0.15f, 0.15f	
    };

    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1, COLOR_RED, GL_FILL);

}

void Gifts::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    // glm::mat4 translate = glm::translate (glm::vec3(this->position.x-(1.5+0.6*cos(M_PI/3))*sin(this->rotation*M_PI/180.0f),this->position.y+(1.5+0.6*cos(M_PI/3))*cos(this->rotation*M_PI/180.0f),this->position.z+ 0.6*sin(M_PI/3)));    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate1 = glm::rotate((float) (-90 * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate *rotate *rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}
void Gifts::tick() {
    if(this->speedz>0)
    {
        // this->speedz=-1;
        this->position.z+=this->speedz; 
    }
    else if(this->speedz<0)
        this->position.z += this->speedz;
    if(this->position.z>=0.09){
        this->speedz=-0.004;
    }
    if(this->position.z<=-0.09)
        this->speedz=0.004;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

void Gifts::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}
