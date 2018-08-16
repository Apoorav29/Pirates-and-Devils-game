#include "enemy.h"
#include "main.h"
#include "math.h"

Enemy::Enemy(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speedz=0.006;
    this->xflag=rand()%2;
    this->yflag=rand()%2;
    this->health=2;
    GLfloat vertex_buffer_data1[100000];
        int idx=0;
        float k=0,n=360;
        for(int j=0;j<n*54;j+=54)
        {
            vertex_buffer_data1[j]=0.25*(float)cos((k*M_PI)/180);
            vertex_buffer_data1[j+1]=0.25*(float)sin((k*M_PI)/180);
            vertex_buffer_data1[j+2]=0.0f;

            vertex_buffer_data1[j+3]=0.25*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data1[j+4]=0.25*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data1[j+5]=0.0f;

            vertex_buffer_data1[j+6]=0.0f;
            vertex_buffer_data1[j+7]=0.0f;
            vertex_buffer_data1[j+8]=0.0f;

            vertex_buffer_data1[j+9]=0.25*(float)cos((k*M_PI)/180);
            vertex_buffer_data1[j+10]=0.25*(float)sin((k*M_PI)/180);
            vertex_buffer_data1[j+11]=1;

            vertex_buffer_data1[j+12]=0.25*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data1[j+13]=0.25*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data1[j+14]=1;

            vertex_buffer_data1[j+15]=0.0f;
            vertex_buffer_data1[j+16]=0.0f;
            vertex_buffer_data1[j+17]=1;
//
            vertex_buffer_data1[j+18]=0.25*(float)cos((k*M_PI)/180);
            vertex_buffer_data1[j+19]=0.25*(float)sin((k*M_PI)/180);
            vertex_buffer_data1[j+20]=0.0f;

            vertex_buffer_data1[j+21]=0.0f;
            vertex_buffer_data1[j+22]=0.0f;
            vertex_buffer_data1[j+23]=0.0f;

            vertex_buffer_data1[j+24]=0.25*(float)cos((k*M_PI)/180);
            vertex_buffer_data1[j+25]=0.25*(float)sin((k*M_PI)/180);
            vertex_buffer_data1[j+26]=1;
////
            vertex_buffer_data1[j+27]=0.0f;
            vertex_buffer_data1[j+28]=0.0f;
            vertex_buffer_data1[j+29]=0.0f;

            vertex_buffer_data1[j+30]=0.25*(float)cos((k*M_PI)/180);
            vertex_buffer_data1[j+31]=0.25*(float)sin((k*M_PI)/180);
            vertex_buffer_data1[j+32]=1;

            vertex_buffer_data1[j+33]=0.0f;
            vertex_buffer_data1[j+34]=0.0f;
            vertex_buffer_data1[j+35]=1;
////
            vertex_buffer_data1[j+36]=0.25*(float)cos((k*M_PI)/180);
            vertex_buffer_data1[j+37]=0.25*(float)sin((k*M_PI)/180);
            vertex_buffer_data1[j+38]=0.0f;

            vertex_buffer_data1[j+39]=0.25*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data1[j+40]=0.25*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data1[j+41]=0.0f;

            vertex_buffer_data1[j+42]=0.25*(float)cos((k*M_PI)/180);
            vertex_buffer_data1[j+43]=0.25*(float)sin((k*M_PI)/180);
            vertex_buffer_data1[j+44]=1;

            vertex_buffer_data1[j+45]=0.25*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data1[j+46]=0.25*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data1[j+47]=0.0f;

            vertex_buffer_data1[j+48]=0.25*(float)cos((k*M_PI)/180);
            vertex_buffer_data1[j+49]=0.25*(float)sin((k*M_PI)/180);
            vertex_buffer_data1[j+50]=1;

            vertex_buffer_data1[j+51]=0.25*(float)cos(((k+1)*M_PI)/180);
            vertex_buffer_data1[j+52]=0.25*(float)sin(((k+1)*M_PI)/180);
            vertex_buffer_data1[j+53]=1;            
            k++;
        };
        //
    GLfloat vertex_buffer_data2[]={
        -0.4,-0.4,1.01,
        0.4,-0.4,1.01,
        0.4, 0.4,1.01,

        -0.4,-0.4,1.01,
        0.4, 0.4,1.01,
        -0.4, 0.4,1.01,

    };  
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    this->object1 = create3DObject(GL_TRIANGLES, 360*18, vertex_buffer_data1, COLOR_YELLOW, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, COLOR_RED, GL_FILL);
    // this->object2 = create3DObject(GL_TRIANGLES, 3*360*90, vertex_buffer_data2, COLOR_STONE, GL_FILL);
    // this->object3 = create3DObject(GL_TRIANGLES, 3*360*90, vertex_buffer_data3, COLOR_STONE, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    // glm::mat4 translate = glm::translate (glm::vec3(this->position.x-(1.5+0.6*cos(M_PI/3))*sin(this->rotation*M_PI/180.0f),this->position.y+(1.5+0.6*cos(M_PI/3))*cos(this->rotation*M_PI/180.0f),this->position.z+ 0.6*sin(M_PI/3)));    // glTranslatef
    // glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // glm::mat4 rotate1 = glm::rotate((float) (-60 * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= translate ;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}
void Enemy::tick() {
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
    // int num = rand()%2;
    if(this->xflag==1)
        this->position.x+=0.006;
    else 
        this->position.x-=0.006;
    // num = rand()%2;
    if(this->yflag==1)
        this->position.y+=0.006;
    else 
        this->position.y-=0.006;
    if(this->position.x > 15 || this->position.x < -15 )
        this->xflag=1-this->xflag;
    if(this->position.y > 15 || this->position.y < -15 )
        this->yflag=1-this->yflag;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

void Enemy::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

