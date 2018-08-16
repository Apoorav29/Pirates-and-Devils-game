#include "boat.h"
#include "main.h"
#include "math.h"

Boat::Boat(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speedz=0.006;
    this->jflag=0;
    this->mcolor=COLOR_BROWN;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data1[] = {
        -0.5f, -1.0f, 0.0f,
        -0.5f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.0f,

        -0.5f, -1.0f, 0.0f,
        0.5f, -1.0f, 0.0f,
        0.5f, 1.0f, 0.0f,

        -0.5f, 1.0f, 0.0f,
        0.0f, 1.5f, 0.0f,
        0.5f, 1.0f, 0.0f,

        -0.5f, -1.0f, 0.0f,
        0.0f, -1.5f, 0.0f,
        0.5f, -1.0f, 0.0f,
    };
    static const GLfloat vertex_buffer_data3[] = {
        
        -0.5f, 1.0f, 0.0f,
        -0.5-0.6*cos(M_PI/3), 1.0f, 0.6*sin(M_PI/3),
        -0.5-0.6*cos(M_PI/3), -1.0f, 0.6*sin(M_PI/3),

        -0.5-0.6*cos(M_PI/3), -1.0f, 0.6*sin(M_PI/3),
        -0.5f, 1.0f, 0.0f,
        -0.5f, -1.0f, 0.0f,

        0.5f, 1.0f, 0.0f,
        0.5+0.6*cos(M_PI/3), 1.0f, 0.6*sin(M_PI/3),    
        0.5+0.6*cos(M_PI/3), -1.0f, 0.6*sin(M_PI/3),    

        0.5+0.6*cos(M_PI/3), -1.0f, 0.6*sin(M_PI/3),    
        0.5f, 1.0f, 0.0f,
        0.5f, -1.0f, 0.0f,
        
    };
    static const GLfloat vertex_buffer_data2[] = {
           0.0f, 1.5f, 0.0f,
        0.0f, 1.5+0.6*cos(M_PI/3), 0.6*sin(M_PI/3),
        0.5+0.6*cos(M_PI/3), 1.0f, 0.6*sin(M_PI/3),

        0.0f, 1.5f, 0.0f,
        0.5+0.6*cos(M_PI/3), 1.0f, 0.6*sin(M_PI/3),
        0.5f, 1.0f, 0.0f,

        -0.5f, 1.0f, 0.0f,
        -0.5-0.6*cos(M_PI/3), 1.0f, 0.6*sin(M_PI/3),
        0.0f, 1.5+0.6*cos(M_PI/3), 0.6*sin(M_PI/3),        

        0.0f, 1.5+0.6*cos(M_PI/3), 0.6*sin(M_PI/3),        
        0.0f, 1.5f, 0.0f,
        -0.5f, 1.0f, 0.0f,

        0.0f, -1.5f, 0.0f,
        0.0f, -1.5-0.6*cos(M_PI/3), 0.6*sin(M_PI/3),
        0.5+0.6*cos(M_PI/3), -1.0f, 0.6*sin(M_PI/3),    

        0.0f, -1.5f, 0.0f,
        0.5+0.6*cos(M_PI/3), -1.0f, 0.6*sin(M_PI/3),    
        0.5f, -1.0f, 0.0f,

        -0.5f, -1.0f, 0.0f,
        -0.5-0.6*cos(M_PI/3), -1.0f, 0.6*sin(M_PI/3),    
        0.0f, -1.5-0.6*cos(M_PI/3), 0.6*sin(M_PI/3),

        0.0f, -1.5-0.6*cos(M_PI/3), 0.6*sin(M_PI/3),
        0.0f, -1.5f, 0.0f,
        -0.5f, -1.0f, 0.0f,
    };
    GLfloat vertex_buffer_data4[100000];
    int idx=0;
        float k=0,n=360;
        for(int j=0;j<n*54;j+=54)
        {
            vertex_buffer_data4[j]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data4[j+1]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data4[j+2]=0.0f;

            vertex_buffer_data4[j+3]=0.1*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data4[j+4]=0.1*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data4[j+5]=0.0f;

            vertex_buffer_data4[j+6]=0.0f;
            vertex_buffer_data4[j+7]=0.0f;
            vertex_buffer_data4[j+8]=0.0f;

            vertex_buffer_data4[j+9]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data4[j+10]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data4[j+11]=2.5f;

            vertex_buffer_data4[j+12]=0.1*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data4[j+13]=0.1*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data4[j+14]=2.5f;

            vertex_buffer_data4[j+15]=0.0f;
            vertex_buffer_data4[j+16]=0.0f;
            vertex_buffer_data4[j+17]=2.5f;
//
            vertex_buffer_data4[j+18]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data4[j+19]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data4[j+20]=0.0f;

            vertex_buffer_data4[j+21]=0.0f;
            vertex_buffer_data4[j+22]=0.0f;
            vertex_buffer_data4[j+23]=0.0f;

            vertex_buffer_data4[j+24]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data4[j+25]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data4[j+26]=2.5f;
////
            vertex_buffer_data4[j+27]=0.0f;
            vertex_buffer_data4[j+28]=0.0f;
            vertex_buffer_data4[j+29]=0.0f;

            vertex_buffer_data4[j+30]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data4[j+31]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data4[j+32]=2.5f;

            vertex_buffer_data4[j+33]=0.0f;
            vertex_buffer_data4[j+34]=0.0f;
            vertex_buffer_data4[j+35]=2.5f;
////
            vertex_buffer_data4[j+36]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data4[j+37]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data4[j+38]=0.0f;

            vertex_buffer_data4[j+39]=0.1*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data4[j+40]=0.1*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data4[j+41]=0.0f;

            vertex_buffer_data4[j+42]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data4[j+43]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data4[j+44]=2.5f;

            vertex_buffer_data4[j+45]=0.1*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data4[j+46]=0.1*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data4[j+47]=0.0f;

            vertex_buffer_data4[j+48]=0.1*(float)cos((k*M_PI)/180);
            vertex_buffer_data4[j+49]=0.1*(float)sin((k*M_PI)/180);
            vertex_buffer_data4[j+50]=2.5f;

            vertex_buffer_data4[j+51]=0.1*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data4[j+52]=0.1*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data4[j+53]=2.5f;            
            k++;
        };
    GLfloat vertex_buffer_data5[]={
        -0.1f, 0.0f, 0.9f,
        -1.0f,0.0f, 0.9f,
        -0.1f, 0.0f, 2.5f,
    };

    this->object1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data1, COLOR_ROSYBROWN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data2, this->mcolor, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data3, COLOR_SIENNA, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 360*18, vertex_buffer_data4, COLOR_ORANGE, GL_FILL);
    // this->object5 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data5, COLOR_ORANGE, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate) ;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object5);
    draw3DObject(this->object4);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object1);
    // draw3DObject(this->object6);

}

void Boat::draw1(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (glm::vec3(this->position.x, this->position.y+3+0.6*cos(M_PI/3),this->position.z+0.15f+ 0.6*sin(M_PI/3)));    // glTranslatef
    // glm::mat4 translate = glm::translate (glm::vec3(this->position.x,this->position.y+3,this->position.z+1));    // glTranslatef 
    glm::mat4 rotate1 = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate2 = glm::rotate((float) ( 90* M_PI / 180.0f), glm::vec3(1, 0, 0));

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate1*rotate2) ;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object6);
}

void Boat::set_position(float x, float y , float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
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
    // this->position.x -= speed;
    // this->position.y -= speed;
}

