#include "canon.h"
#include "main.h"
#include "math.h"

Canon::Canon(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speedz=0.006;
    this->jflag=0;
    this->inclination = -60;
    GLfloat vertex_buffer_data6[100000];
        int idx=0;
        float k=0,n=360;
        for(int j=0;j<n*54;j+=54)
        {
            vertex_buffer_data6[j]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data6[j+1]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data6[j+2]=0.0f;

            vertex_buffer_data6[j+3]=0.1*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data6[j+4]=0.1*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data6[j+5]=0.0f;

            vertex_buffer_data6[j+6]=0.0f;
            vertex_buffer_data6[j+7]=0.0f;
            vertex_buffer_data6[j+8]=0.0f;

            vertex_buffer_data6[j+9]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data6[j+10]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data6[j+11]=1;

            vertex_buffer_data6[j+12]=0.1*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data6[j+13]=0.1*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data6[j+14]=1;

            vertex_buffer_data6[j+15]=0.0f;
            vertex_buffer_data6[j+16]=0.0f;
            vertex_buffer_data6[j+17]=1;
//
            vertex_buffer_data6[j+18]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data6[j+19]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data6[j+20]=0.0f;

            vertex_buffer_data6[j+21]=0.0f;
            vertex_buffer_data6[j+22]=0.0f;
            vertex_buffer_data6[j+23]=0.0f;

            vertex_buffer_data6[j+24]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data6[j+25]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data6[j+26]=1;
////
            vertex_buffer_data6[j+27]=0.0f;
            vertex_buffer_data6[j+28]=0.0f;
            vertex_buffer_data6[j+29]=0.0f;

            vertex_buffer_data6[j+30]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data6[j+31]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data6[j+32]=1;

            vertex_buffer_data6[j+33]=0.0f;
            vertex_buffer_data6[j+34]=0.0f;
            vertex_buffer_data6[j+35]=1;
////
            vertex_buffer_data6[j+36]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data6[j+37]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data6[j+38]=0.0f;

            vertex_buffer_data6[j+39]=0.1*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data6[j+40]=0.1*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data6[j+41]=0.0f;

            vertex_buffer_data6[j+42]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data6[j+43]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data6[j+44]=1;

            vertex_buffer_data6[j+45]=0.1*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data6[j+46]=0.1*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data6[j+47]=0.0f;

            vertex_buffer_data6[j+48]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data6[j+49]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data6[j+50]=1;

            vertex_buffer_data6[j+51]=0.1*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data6[j+52]=0.1*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data6[j+53]=1;            
            k++;
        };
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    this->object1 = create3DObject(GL_TRIANGLES, 360*18, vertex_buffer_data6, COLOR_BLACK, GL_FILL);
    // this->object2 = create3DObject(GL_TRIANGLES, 3*360*90, vertex_buffer_data2, COLOR_STONE, GL_FILL);
    // this->object3 = create3DObject(GL_TRIANGLES, 3*360*90, vertex_buffer_data3, COLOR_STONE, GL_FILL);
}

void Canon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (glm::vec3(this->position.x-(1.5+0.6*cos(M_PI/3))*sin(this->rotation*M_PI/180.0f),this->position.y+(1.5+0.6*cos(M_PI/3))*cos(this->rotation*M_PI/180.0f),this->position.z+ 0.6*sin(M_PI/3)));    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate1 = glm::rotate((float) (this->inclination * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate*rotate1) ;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);

}
void Canon::tick() {
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

void Canon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

