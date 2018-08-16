#include "stone.h"
#include "main.h"
#include "math.h"

Stone::Stone(float x, float y, color_t color) {
    this->position = glm::vec3(x, y,0);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data1[300000];
    int idx=0,r=1;
    for(int i=1;i<=90;i+=3)
    {
        float k=0,n=360;
        for(int j=0;j<n*9;j+=9)
        {
            vertex_buffer_data1[idx+j]=0.5*(float)sin((float)i*M_PI/180)*(float)cos((k*M_PI)/180);
            vertex_buffer_data1[idx+j+1]=0.5*(float)sin((float)i*M_PI/180)*(float)sin((k*M_PI)/180);
            vertex_buffer_data1[idx+j+2]=0.5*(float)cos((float)i*M_PI/180);

            vertex_buffer_data1[idx+j+3]=0.5*(float)sin((float)i*M_PI/180)*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data1[idx+j+4]=0.5*(float)sin((float)i*M_PI/180)*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data1[idx+j+5]=0.5*(float)cos((float)i*M_PI/180);

            vertex_buffer_data1[idx+j+6]=0.0f;
            vertex_buffer_data1[idx+j+7]=0.0f;
            vertex_buffer_data1[idx+j+8]=0.5*(float)cos((float)i*M_PI/180);
            k++;
        }
        idx=360*9*r;
        r++;
    }
    GLfloat vertex_buffer_data2[300000];
    int idx1=0;
    r=1;
    for(int i=1;i<=90;i+=3)
    {
        float k=0,n=360;
        for(int j=0;j<n*9;j+=9)
        {
            vertex_buffer_data2[idx1+j]=0.5*(float)sin((float)i*M_PI/180)*(float)cos((k*M_PI)/180);
            vertex_buffer_data2[idx1+j+1]=0.5*(float)cos((float)i*M_PI/180);
            vertex_buffer_data2[idx1+j+2]=0.5*(float)sin((float)i*M_PI/180)*(float)sin((k*M_PI)/180);

            vertex_buffer_data2[idx1+j+3]=0.5*(float)sin((float)i*M_PI/180)*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data2[idx1+j+4]=0.5*(float)cos((float)i*M_PI/180);
            vertex_buffer_data2[idx1+j+5]=0.5*(float)sin((float)i*M_PI/180)*(float)sin(((k+1)*M_PI)/180);

            vertex_buffer_data2[idx1+j+6]=0.0f;
            vertex_buffer_data2[idx1+j+7]=0.5*(float)cos((float)i*M_PI/180);
            vertex_buffer_data2[idx1+j+8]=0.0f;
            k++;
        }
        idx1=360*9*r;
        r++;
    }
    GLfloat vertex_buffer_data3[300000];
    int idx2=0;
    r=1;
    for(int i=1;i<=90;i+=3)
    {
        float k=0,n=360;
        for(int j=0;j<n*9;j+=9)
        {
            vertex_buffer_data3[idx2+j]=0.5*(float)cos((float)i*M_PI/180);
            vertex_buffer_data3[idx2+j+1]=0.5*(float)sin((float)i*M_PI/180)*(float)sin((k*M_PI)/180);
            vertex_buffer_data3[idx2+j+2]=0.5*(float)sin((float)i*M_PI/180)*(float)cos((k*M_PI)/180);

            vertex_buffer_data3[idx2+j+3]=0.5*(float)cos((float)i*M_PI/180);
            vertex_buffer_data3[idx2+j+4]=0.5*(float)sin((float)i*M_PI/180)*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data3[idx2+j+5]=0.5*(float)sin((float)i*M_PI/180)*(float)cos(((k+1)*M_PI)/180);

            vertex_buffer_data3[idx2+j+6]=0.5*(float)cos((float)i*M_PI/180);
            vertex_buffer_data3[idx2+j+7]=0.0f;
            vertex_buffer_data3[idx2+j+8]=0.0f;
            k++;
        }
        idx2=360*9*r;
        r++;
    }
    
    this->object1 = create3DObject(GL_TRIANGLES, 3*360*30, vertex_buffer_data1, COLOR_STONE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*360*30, vertex_buffer_data2, COLOR_STONE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3*360*30, vertex_buffer_data3, COLOR_STONE, GL_FILL);
}

void Stone::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate ;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);

}

void Stone::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

