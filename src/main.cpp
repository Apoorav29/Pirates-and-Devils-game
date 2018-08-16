#include "main.h"
#include "bits/stdc++.h"
#include "timer.h"
#include "boat.h"
#include "fireball.h"
#include "sail.h"
#include "barell.h"
#include "gifts.h"
#include "math.h"
#include "water.h"
#include "stone.h"
#include "canon.h"
#include "enemy.h"
#include "monster.h"

using namespace std;
double xpos, ypos, prevx, prevy;
GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
char buff[1024];
int cur,mflag=0;
int health=100;
long long int ticks=0;
int fireflag=0,cflag=0,bcflag=0;
double dirwind;
int killcount=0;
int heli=0, boatview=1, top=0, tower=0, follow=0;
double hangle=0;
double hheight=14;
Boat boat;
Sail sail;
Fireball fireball; 
Canon canon;
Enemy enemy[10];
Monster monster;
Water water1;
Stone stone[10];
Barell barell[10];
Gifts gifts[11];
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glm::vec3 eye;
    // glm::vec3 target;
    // glm::vec3 up;

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 1+100*cos(camera_rotation_angle*M_PI/180.0f), 0, 1+100*sin(camera_rotation_angle*M_PI/180.0f) );
    if (boatview==1)
    {
        // cout<<"boatview"<<endl;
        glm::vec3 eye ((boat.position.x-(0.06*sin(boat.rotation*M_PI/180))),boat.position.y +0.06*cos(boat.rotation*M_PI/180),boat.position.z+1.6f);
        glm::vec3 target ((boat.position.x-10*sin(boat.rotation*M_PI/180)), boat.position.y+10*cos(boat.rotation*M_PI/180),0.05f);
        glm::vec3 up (0, 0, 1);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }
    else if (tower==1)
    {
        // cout<<"tower"<<endl;
        glm::vec3 eye (0,-20, 10);
        glm::vec3 target (boat.position.x, boat.position.y, /*boat.position.y+*/0.05f );
        glm::vec3 up (0, 0, 1);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }
    else if (follow==1)
    {
        // cout<<"follow"<<endl;
        glm::vec3 eye (boat.position.x, boat.position.y-6 , 1.5f/*+0.7f*/ );
        glm::vec3 target (boat.position.x, /*boat.position.y*/ boat.position.y , 0.05f);
        glm::vec3 up (0, 0, 1);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }

    
    else if (top==1)
    {
        // cout<<"top"<<endl;
        glm::vec3 eye (boat.position.x, boat.position.y ,25);
        glm::vec3 target (boat.position.x, boat.position.z, /*boat.position.y+*/0.05f );
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }



    else if(heli==1)
    {
        glm::vec3 eye ((boat.position.x-(5*sin(hangle*M_PI/180))),boat.position.y +5*cos(hangle*M_PI/180),hheight);
        glm::vec3 target (boat.position.x, boat.position.y,0.05f);
        glm::vec3 up (0, 0, 1);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D   
    }
    // glm::vec3 eye ( boat.position.x+7*sin(boat.rotation*M_PI/180), boat.position.y-7*cos(boat.rotation*M_PI/180), 14);
    // // glm::vec3 eye ( 0, -0.5, 0.5f);
    // // glm::vec3 eye ( 0, 0, -1);


    // // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (boat.position.x, boat.position.y, 0);
    // // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (-sin(boat.rotation*M_PI/180), cos(boat.rotation*M_PI/180), 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(-1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for(int i=0;i<10;i++)
        stone[i].draw(VP);
    water1.draw(VP);
    boat.draw(VP);
    sail.draw(VP);
    fireball.draw(VP);
    for(int i=0;i<10;i++)
        enemy[i].draw(VP);
    for(int i=0;i<10;i++)
        barell[i].draw(VP);
    for(int i=0;i<11;i++)
        gifts[i].draw(VP);
    // boat.draw1(VP);
    double x1, y1;
    if(killcount>1 && killcount%3==0 && mflag==0)
    {
        x1 = rand()%21-10;
        y1 = rand()%21+5;
    // monster = Monster(x1, y1, 0, COLOR_RED);
        monster.set_position(x1, y1, 0);
        mflag=1;
    }
    if(mflag)
    {
        monster.draw(VP);
        monster.draw1(VP);
    }
    canon.draw(VP);

}

void drag(GLFWwindow* window, double xpos, double ypos)
{
    double xcurr, ycurr;
    xcurr = xpos;
    ycurr = ypos;
    if(hheight>=0)
        hheight += (ycurr-prevy)/10;
    else
        hheight=0;  
    hangle += (xcurr-prevx)/3;
    prevy = ycurr;
    prevx = xcurr;
}

void prevcoord(GLFWwindow* window, double xpos, double ypos)
{
    prevx=xpos;
    prevy=ypos;
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down  = glfwGetKey(window, GLFW_KEY_DOWN);
    int f = glfwGetKey(window, GLFW_KEY_F);
    int v = glfwGetKey(window, GLFW_KEY_V);
    int z = glfwGetKey(window, GLFW_KEY_Z);
    int x = glfwGetKey(window, GLFW_KEY_X);
    int b = glfwGetKey(window, GLFW_KEY_B);
    int n = glfwGetKey(window, GLFW_KEY_N);
    int m = glfwGetKey(window, GLFW_KEY_M);
    int h = glfwGetKey(window, GLFW_KEY_H);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);    
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    if (left) {
        // camera_rotation_angle+=1;
        boat.rotation+=0.9;
        sail.rotation+=0.9;
        canon.rotation+=0.9;

        // Do something
    }
    else if (right) 
    {
        // camera_rotation_angle-=1;
        boat.rotation-=0.9;
        sail.rotation-=0.9;
        canon.rotation-=0.9;
        // camera_rotation_angle=0;
    }
    else if(up)
    {
        boat.position.y+=0.06*cos(-boat.rotation*M_PI/180.0f);
        boat.position.x+=0.06*sin(-boat.rotation*M_PI/180.0f);

        sail.position.y+=0.06*cos(-boat.rotation*M_PI/180.0f);
        sail.position.x+=0.06*sin(-boat.rotation*M_PI/180.0f);

        canon.position.y+=0.06*cos(-boat.rotation*M_PI/180.0f);
        canon.position.x+=0.06*sin(-boat.rotation*M_PI/180.0f);
    }
    else if(down)
    {
        boat.position.y-=0.06*cos(-boat.rotation*M_PI/180.0f);
        boat.position.x-=0.06*sin(-boat.rotation*M_PI/180.0f);

        sail.position.y-=0.06*cos(-boat.rotation*M_PI/180.0f);
        sail.position.x-=0.06*sin(-boat.rotation*M_PI/180.0f);

        canon.position.y-=0.06*cos(-boat.rotation*M_PI/180.0f);
        canon.position.x-=0.06*sin(-boat.rotation*M_PI/180.0f);
    }
    else if(f && fireflag==0)
    {
        fireball.brotation = boat.rotation;
        fireball.set_position(boat.position.x-(1.5+0.6*cos(M_PI/3)+cos((90+canon.inclination)*M_PI/180))*sin(boat.rotation*M_PI/180.0f), boat.position.y+(1.5+0.6*cos(M_PI/3)+cos((90+canon.inclination)*M_PI/180))*cos(boat.rotation*M_PI/180.0f), boat.position.z+ 0.6*sin(M_PI/3)+sin((90+canon.inclination)*M_PI/180));
        fireflag=1;
    }
    else if(v)
        // cur = (cur+1)%4;
        // if(cur==0)
        // {
        top=1,boatview=0,tower=0,follow=0,heli=0;
    //     }
    //     else if(cur==1)
    //     {
    //         top=0,boatview=1,tower=0,follow=0;
    //     }
    //     else if(cur==2)
    //     {
    //         top=0,boatview=0,tower=1,follow=0;
    //     }
    //     else if(cur==3)
    //     {
    //         top=0,boatview=0,tower=0,follow=1;
    //     }
    // }
    else if(b)
        top=0,boatview=1,tower=0,follow=0,heli=0;

    else if(n)
        top=0,boatview=0,tower=1,follow=0,heli=0;

    else if(m)
        top=0,boatview=0,tower=0,follow=1,heli=0;
    else if(h)
        top=0,boatview=0,tower=0,follow=0,heli=1; 
    // glfwGetCursorPos(window, &xpos, &ypos);
    // if(heli && xpos-prevx>=0)
    //     hangle+=1;
    // else if(heli && xpos-prevx<0)
    //     hangle-=1;
    // if(heli && ypos-prevy>=0)
    //     hheight+=0.7;
    // else if(heli && ypos-prevy<0)
    //     hheight-=0.7;
    // prevx=xpos;
    // prevy=ypos;
    if(heli && w )
        hheight+=0.7;
    if(heli && s && hheight>=4)
        hheight-=0.7;
    if(heli && a)
        hangle-=1;
    if(heli && d)
        hangle+=1;
    if(space && boat.jflag==0)
    {
        boat.jflag=1;
        sail.jflag=1;
        canon.jflag=1;
        boat.speedz=0.13;
        canon.speedz=0.13;
        sail.speedz=0.13;

    }
    if(z && canon.inclination <=0)
        canon.inclination+=2;
    if(x && canon.inclination >=-90)
        canon.inclination-=2;

}
// glm::vec3(boat.position.x-(1.5+0.6*cos(M_PI/3)+cos(M_PI/6))*sin(boat.rotation*M_PI/180.0f),boat.position.y+(1.5+0.6*cos(M_PI/3)+cos(M_PI/6))*cos(boat.rotation*M_PI/180.0f),boat.position.z+ 0.6*sin(M_PI/3)+sin(M_PI/6))
void tick_elements() {

    // ticks++;
    boat.tick();
    sail.tick();
    canon.tick(); 
    monster.tick();
    for(int i=0;i<10;i++)
    {
       enemy[i].tick();
    }
    for(int i=0;i<10;i++)
    {
       barell[i].tick();
    }
    // double ang = atan((monster.position.x-boat.position.x)/(monster.position.y-boat.position.y));
    // monster.position.y-=0.07*cos(ang);
    // monster.position.x+=0.07*sin(ang);
    // if(ticks%120==0)
    //     cout<<ticks<<endl;
    // if(ticks%120==0)
    // {
    //     sail.rotation=rand()%361;
    //     dirwind = sail.rotation;
    // }
    if(fireflag ==1 && fireball.position.z>0)
    {
        fireball.position.x-=0.35*cos((90+canon.inclination)*M_PI/180)*sin(fireball.brotation*M_PI/180);
        fireball.position.y+=0.35*cos((90+canon.inclination)*M_PI/180)*cos(fireball.brotation*M_PI/180);
        fireball.speedz-=0.027;
        fireball.position.z+=fireball.speedz;
    }
    else if(fireball.position.z<=0)
    {
        fireball.set_position(-INT_MAX, INT_MAX, -40);
        fireflag=0;
        cflag=0;
        bcflag=0;
        fireball.speedz=0.4;
    }

    boat.position.y+=0.004*cos(dirwind*M_PI/180.0f);
    boat.position.x-=0.004*sin(dirwind*M_PI/180.0f);
    sail.position.y+=0.004*cos(dirwind*M_PI/180.0f);
    sail.position.x-=0.004*sin(dirwind*M_PI/180.0f);

    canon.position.y+=0.004*cos(dirwind*M_PI/180.0f);
    canon.position.x-=0.004*sin(dirwind*M_PI/180.0f);
    // camera_rotation_angle += 1;
}

void modheli(int arg)
{
    if(arg==1)
        hheight+=0.7;       
    else if(arg==2)
        hheight-=0.7;       
    else if(arg==3)
        hangle-=1;
    else if(arg==4)
        hangle-=1;

    return;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    boat = Boat(0, 0, 0, COLOR_RED);
    sail = Sail(0, 0, 0);
    fireball = Fireball(-INT_MAX, INT_MAX, COLOR_RED);
    canon = Canon(0,0,0,COLOR_RED);
    water1 = Water(0, 0, COLOR_WATER);
    double x1;
    double y1;
    for(int i=0;i<10;i++)
    {
        x1 = rand()%21-10;
        y1 = rand()%21+5;
        stone[i] = Stone(x1, y1, COLOR_RED);
    }
    for(int i=0;i<10;i++)
    {
        x1 = rand()%21-10;
        y1 = rand()%21+5;
        enemy[i] = Enemy(x1, y1, 0, COLOR_RED);
    }
    for(int i=0;i<10;i++)
    {
        barell[i] = Barell(-INT_MAX, -INT_MAX, 0, COLOR_RED);
    }
    for(int i=0;i<11;i++)
    {
        gifts[i] = Gifts(-INT_MAX, -INT_MAX, 0, COLOR_RED);
    }
    x1 = rand()%21-10;
    y1 = rand()%21+5;
    monster = Monster(x1, y1, 0, COLOR_RED);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1200;
    int height = 1200;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        // sprintf(buff,"Health :- %d ",health);
        // glfwSetWindowTitle(window, buff);
        if (t60.processTick()) {
            ticks++;
            if(ticks%120 == 0)
            {
                cout<<health<<endl;
                // cout<<boat.mcolor<<endl;
            }

            if(ticks%240 ==0)
            {
                dirwind=rand()%361;
            }
            if(health==0)
                quit(window);
            // 60 fps
            // OpenGL Draw commands
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            if(heli && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) 
                glfwSetCursorPosCallback(window, drag);
            else
                glfwSetCursorPosCallback(window, prevcoord);

            // glfwSetCursorPosCallback(window, drag);
            tick_elements();
            detect_collision();
            tick_input(window);
            draw();
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

int detect_collision() {
    double tempang, ang, dist, tempdist1, tempdist2;
    for(int i=0;i<10;i++)
    {
        // cflag=0;
        tempang= atan((stone[i].position.x-boat.position.x)/(stone[i].position.y-boat.position.y));
        ang = fabs(boat.rotation+tempang*(180/M_PI));
        dist = sqrt(pow((stone[i].position.x-boat.position.x),2)+pow((stone[i].position.y-boat.position.y),2));
        tempdist1 = dist*cos(ang*M_PI/180);
        tempdist2 = dist*sin(ang*M_PI/180);
        if(fabs(tempdist1)<=2.08 && fabs(tempdist2)<=1.08)
        {
            stone[i].set_position(-INT_MAX, -INT_MAX);
            health-=2;
            boat.position.y-=1.2*cos(-boat.rotation*M_PI/180.0f);
            boat.position.x-=1.2*sin(-boat.rotation*M_PI/180.0f);
            sail.position.y-=1.2*cos(-boat.rotation*M_PI/180.0f);
            sail.position.x-=1.2*sin(-boat.rotation*M_PI/180.0f);

            canon.position.y-=1.2*cos(-boat.rotation*M_PI/180.0f);
            canon.position.x-=1.2*sin(-boat.rotation*M_PI/180.0f);
            // cflag=1;
            // cout<<"collided "<<boat.position.x<<" "<<boat.position.y<<endl;
        }
    }
    for(int i=0;i<10;i++)
    {
        // cflag=0;
        tempang= atan((enemy[i].position.x-boat.position.x)/(enemy[i].position.y-boat.position.y));
        ang = fabs(boat.rotation+tempang*(180/M_PI));
        dist = sqrt(pow((enemy[i].position.x-boat.position.x),2)+pow((enemy[i].position.y-boat.position.y),2));
        tempdist1 = dist*cos(ang*M_PI/180);
        tempdist2 = dist*sin(ang*M_PI/180);
        if(fabs(tempdist1)<=2.08 && fabs(tempdist2)<=1.08)
        {
            health-=5;
            boat.position.y-=0.8*cos(-boat.rotation*M_PI/180.0f);
            boat.position.x-=0.8*sin(-boat.rotation*M_PI/180.0f);
            sail.position.y-=0.8*cos(-boat.rotation*M_PI/180.0f);
            sail.position.x-=0.8*sin(-boat.rotation*M_PI/180.0f);

            canon.position.y-=0.8*cos(-boat.rotation*M_PI/180.0f);
            canon.position.x-=0.8*sin(-boat.rotation*M_PI/180.0f);
            // enemy[i].set_position(-INT_MAX, -INT_MAX);
            // cflag=1;
            // cout<<"collided "<<boat.position.x<<" "<<boat.position.y<<endl;
            // boat.position-=
        }
    }
    for(int i=0;i<10;i++)
    {
        // cflag=0;
        tempang= atan((barell[i].position.x-boat.position.x)/(barell[i].position.y-boat.position.y));
        ang = fabs(boat.rotation+tempang*(180/M_PI));
        dist = sqrt(pow((barell[i].position.x-0.5-boat.position.x),2)+pow((barell[i].position.y-boat.position.y),2));
        tempdist1 = dist*cos(ang*M_PI/180);
        tempdist2 = dist*sin(ang*M_PI/180);
        if(fabs(tempdist1)<=1.8 && fabs(tempdist2)<=0.80)
        {
            barell[i].set_position(-INT_MAX, -INT_MAX, 0);
            gifts[barell[i].giftidx].set_position(-INT_MAX, -INT_MAX, 0);
            cout<<gifts[barell[i].giftidx].mflag<<endl;
            int randnum = rand()%3;
            if(gifts[barell[i].giftidx].mflag==1)
            {
                cout<<"YIPEE"<<endl;
                if(randnum==0)
                    boat.mcolor=COLOR_YELLOW;
                else if(randnum==1)
                    boat.mcolor=COLOR_YELLOW;
                else
                    boat.mcolor=COLOR_FIREBRICK;
            }
            barell[i].giftidx=0;
            health=100;
            cout<<"health boost"<<endl;

            // boat.position.y-=0.4*cos(-boat.rotation*M_PI/180.0f);
            // boat.position.x-=0.4*sin(-boat.rotation*M_PI/180.0f);
            // sail.position.y-=0.4*cos(-boat.rotation*M_PI/180.0f);
            // sail.position.x-=0.4*sin(-boat.rotation*M_PI/180.0f);

            // canon.position.y-=0.4*cos(-boat.rotation*M_PI/180.0f);
            // canon.position.x-=0.4*sin(-boat.rotation*M_PI/180.0f);
            // enemy[i].set_position(-INT_MAX, -INT_MAX);
            // cflag=1;
            // cout<<"collided "<<boat.position.x<<" "<<boat.position.y<<endl;
            // boat.position-=
        }
    }
    double disten;
    for(int i=0;i<10;i++)
    {   
        int j;
        disten = sqrt(pow((fireball.position.x-enemy[i].position.x),2)+pow((fireball.position.y-enemy[i].position.y),2));
        if(fireball.position.z<=1 && disten <= 0.35 && cflag==0)
        {

            cflag=1;
            enemy[i].health-=1;
            if(enemy[i].health==0)
            {
                for(j=0;j<10;j++)
                {
                    if(barell[j].position.x==-INT_MAX)
                    {
                        barell[j].set_position(enemy[i].position.x,enemy[i].position.y, enemy[i].position.z );
                        break;
                    }

                }
                for(int z=0;z<10;z++)
                {
                    if(gifts[z].position.x==-INT_MAX)
                    {
                        gifts[z].set_position(enemy[i].position.x-0.5,enemy[i].position.y, enemy[i].position.z + 1);
                        barell[j].giftidx=z;
                        break;
                    }
                    
                }
                killcount++;
                enemy[i].set_position(-INT_MAX, -INT_MAX, 0);
                enemy[i].health=2;
            }
            // cout<<"collided"<<endl;
        }
    }
    ////
    ////
    // int j;
    // disten = sqrt(pow((fireball.position.x-monster.position.x),2)+pow((fireball.position.y-monster.position.y),2));
    // if(fireball.position.z<=1 && disten <= 0.7 && cflag==0)
    // {

    //     cflag=1;
    //     enemy[i].health-=1;
    //     if(enemy[i].health==0)
    //     {
    //         for(j=0;j<10;j++)
    //         {
    //             if(barell[j].position.x==-INT_MAX)
    //             {
    //                 barell[j].set_position(enemy[i].position.x,enemy[i].position.y, enemy[i].position.z );
    //                 break;
    //             }

    //         }
    //         for(int z=0;z<10;z++)
    //         {
    //             if(gifts[z].position.x==-INT_MAX)
    //             {
    //                 gifts[z].set_position(enemy[i].position.x-0.5,enemy[i].position.y, enemy[i].position.z + 1);
    //                 barell[j].giftidx=z;
    //                 break;
    //             }
                
    //         }
    //         killcount++;
    //         enemy[i].set_position(-INT_MAX, -INT_MAX, 0);
    //         enemy[i].health=2;
    //     }
    //     // cout<<"collided"<<endl;
    // }

    disten = sqrt(pow((fireball.position.x-monster.position.x),2)+pow((fireball.position.y-monster.position.y),2));
    if(fireball.position.z<=3 && disten <= 0.7 && bcflag==0)
    {
        int j;
        bcflag=1;
        monster.health-=1;
        if(monster.health==0)
        {
            for(j=0;j<10;j++)
            {
                if(barell[j].position.x==-INT_MAX)
                {
                    barell[j].set_position(monster.position.x,monster.position.y, 0);
                    break;
                }

            }
            for(int z=0;z<10;z++)
            {
                if(gifts[z].position.x==-INT_MAX)
                {
                    gifts[z].set_position(monster.position.x-0.5,monster.position.y, 1);
                    barell[j].giftidx=z;
                    gifts[z].mflag=1;
                    // int randnum=rand()%3;
                    // if(randnum==0)

                    break;
                }
                
            }
            // killcount++;
            monster.set_position(-INT_MAX, -INT_MAX, 0);
            mflag=0;
            monster.health=3;
            killcount=0;
        }
        // cout<<"collided monster"<<endl;
    }
    return 0;
}

void reset_screen() {
    float top    = screen_center_y + 6 / screen_zoom;
    float bottom = screen_center_y - 6 / screen_zoom;
    float left   = screen_center_x - 6 / screen_zoom;
    float right  = screen_center_x + 6 / screen_zoom;
    Matrices.projection = glm::perspective(1.0f, 1.0f, 1.0f, 1200.0f);
}
