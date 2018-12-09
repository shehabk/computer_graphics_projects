#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>

#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<time.h>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include <unistd.h>
#include "imageloader.h"


using namespace std ;


#define eps 1e-12 

// Variable Declarations

GLfloat pi = 3.1415769 ;
GLfloat degtorad  = 3.1415769/180.0f;
GLfloat width = 600*1.5 , height = 400*1.5  ;                  // width and height of screen 
GLfloat orthox = 150 , orthoy = 100 ;                  // width and height of ortho  
GLfloat mousex = 20 , mousey = 20 ;                    // position of mouse in ortho
GLfloat ballx = 20 , bally = 20 ;                      // present position of the ball
GLfloat inx = 20 , iny = 20    ;                       // initial position of the ball
GLfloat vel =0 , velangle = 0 , velx = 0, vely = 0 ;   // velocity , angle of velocity , velocity along x axis , velocity along y axis ;
GLfloat radi  = 3       ;                              // radious of the ball ;            
bool onball = false  , fired = false ;                 // is the mouse is in ball 
GLfloat stime_g = 0    ;                                 // clock of last update  ;
int ballcnt = 0;
int level = 1 ;
int life_level[] = { 0 , 20 , 15 , 12 , 10 , 8 ,1};
int life = 10 ;
// All basket properties
double basketx[10] ;                                   // x position of basket i
double baskety[10] ;                                   // y position of basket i
double basketvelx[10];                                 // velocity along x axis
double basketvely[10];                                 // velocity along  y axix
bool   basketwithball[10]  ;                           // does the basket has a ball

int bs0_velx_lv[] = {0 ,10 , 15, 14 , 24 , 12};
int bs0_vely_lv[] = {0 , 0 ,  0 ,5 ,  8,  18} ;


int bs1_velx_lv[] = {0 ,- 14 , 12, -24 , 20 , 30};
int bs1_vely_lv[] = {0 ,   0 ,  6, -10 , 6 ,  21} ;


int bs2_velx_lv[] = {0 , 13 , 10, 14 , -28 , 15};
int bs2_vely_lv[] = {0 , 0 ,  0 , 16 ,  10 , 10} ;


double maxy = 0    ;  // maximum height traversed by the ball 


int  score_i = 0 ;
char score_s[100] = "0";
//Variable Declaration ended 

// loading texture started 


GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture

void change(void);
void initRendering() {
	glEnable(GL_DEPTH_TEST);
   // glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

    glShadeModel(GL_FLAT);
    glClearDepth(1.0);
     //glEnable(GL_DEPTH_TEST);
    glDepthFunc( GL_LEQUAL );
	
	change();
}


void Text(GLdouble x, GLdouble y, char *str, void* font=GLUT_BITMAP_8_BY_13)
{ 
   glPushMatrix();
   glRasterPos3d(x, y, 0);
   glScalef(10,10 ,10);
   
   int i;
   for (i=0; str[i]; i++) {
      glutBitmapCharacter(font, str[i]); // GLUT_BITMAP_8_BY_13, GLUT_BITMAP_TIMES_ROMAN_24
   }
   glPopMatrix();
}
float dist ( float x1 , float y1 , float x2 , float y2){
  return sqrt( (x1-x2)*(x1-x2)  + (y1-y2)*(y1-y2) );
}

float cross(float x1 , float y1 , float x2 , float y2){
  return x1*y2 -x2*y1 ;
}

float dot( float x1 , float y1 , float x2 , float y2 ){
 return x1*x2 + y1*y2 ;
}
float ang_with_hori ( float x1 , float y1 , float x2 , float y2){
	
   float cp = cross ( 5 ,0 , x2- -x1 , y2 - y1 );
   float theta = cp /( 5 * dist(x1,y1,x2,y2));
   float ret = dot( 5 ,0 , x2-x1 , y2 - y1);
   //printf(" Dot value = %f \n",ret);
   if(ret<0) return pi - asin(theta);
   return asin(theta);
}




void drawCircle(GLdouble rad)		//draws circle
{
	GLint points = 50;
	GLdouble delTheta = (2.0 * pi) / (GLdouble)points;
	GLdouble theta = 0.0;
    
	glPushMatrix();
	glColor3f(1,.8,.3);
	glBegin(GL_POLYGON);
	{   
		
		for( GLint i = 0; i <=50; i++, theta += delTheta )
		{
			
			glVertex3f(rad * cos(theta),rad * sin(theta),0);
			glColor3f(1,0,0);
		}
	}
	glEnd();
	glPopMatrix();
	
}

void dirline(){

	glPushMatrix();
    glColor3f(0,0,0);
	glBegin(GL_LINES);
	glVertex3f(ballx ,bally , 0);
    glVertex3f(inx ,iny , 0);
    glEnd();
	glPopMatrix();
}


void angry_bird( bool  bskt = 0 ){

	glPushMatrix();
	if(!bskt)
	glTranslatef(ballx,bally,0.1f);
	glScalef(.7,.7,1);
	
	
	
   float radx  , rady ;
   float theta , dtheta ;
   int pnts  = 100 ;
   int i , j ,k ;

   dtheta = (2*3.1416)/pnts ;
   radx = 6 , rady = 4 ;
   glLineWidth(.5);
   
   // lower half of the bird
   glColor4f(1 ,0,0 ,1);
   glBegin(GL_POLYGON);
   theta = 50*dtheta ;
   for(i=0 ; i<=50 ; i++,theta+=dtheta)
	   glVertex3f(radx*cos(theta) , rady*sin(theta),0);
   glEnd();

   // lower half border
   glColor4f(0,0,0,1);
   glBegin(GL_LINE_STRIP);
   theta = 50*dtheta ;
   for(i=0 ; i<=50 ; i++,theta+=dtheta)
	   glVertex3f(radx*cos(theta) , rady*sin(theta),0);
   glEnd();


   // upper half
   glColor4f(1,0,0,1);
   rady = 6.5;
   glBegin(GL_POLYGON);
   theta = 0 ; ;
   for(i=0 ; i<=50 ; i++,theta+=dtheta)
	   glVertex3f(radx*cos(theta) , rady*sin(theta),0);
   glEnd();

   // upper half border
   //glColor3f(0,0,0);
   glColor4f(0,0,0,1);
   glBegin(GL_LINE_STRIP);
   theta = 0 ; ;
   for(i=0 ; i<=50 ; i++,theta+=dtheta)
	   glVertex3f(radx*cos(theta) , rady*sin(theta),0);
   glEnd();

   // left brow
   glColor4f(0,0,0,1);
   glBegin(GL_POLYGON);
	   glVertex3f( -1 , 2.4 ,0);
	   glVertex3f( -.2, 3.3 ,0);
	   glVertex3f( 2.3, 1.8 ,0);
	   glVertex3f( 2.3 ,1.2 ,0);
	
   glEnd();

   // right brow
    glColor4f(0,0,0,1);
   glBegin(GL_POLYGON);
	   glVertex3f( 2.3, 1.8 ,0);
	   glVertex3f( 4.5, 3.2,0);
	   glVertex3f( 5.1, 2.1,0);
	   glVertex3f( 2.3 ,1.2 ,0);
	
   glEnd();
   
   // left eye
   glColor4f(1,1,1,1);
   glBegin(GL_POLYGON);
	   glVertex3f( 2.3, 1.2 ,0);
	   glVertex3f( 0, 1.9,0);
	   glVertex3f( 0, .3 ,0);
	   glVertex3f( 2.3 ,.5 ,0);
	
   glEnd();

    // right eye
     glBegin(GL_POLYGON);
	   glVertex3f( 2.3, 1.2 ,0);
	   glVertex3f( 4, 1.8,0);
	   glVertex3f( 4.2, .9 ,0);
	   glVertex3f( 2.3 ,.5 ,0);
	
   glEnd();
    // left eye border
   glColor4f(0,0,0,1);
   glBegin(GL_LINE_LOOP);
	   glVertex3f( 2.3, 1.2 ,0);
	   glVertex3f( 0, 2.0,0);
	   glVertex3f( 0, .3 ,0);
	   glVertex3f( 2.3 ,.5 ,0);
	
   glEnd();

    // right eye border 
     glBegin(GL_LINE_LOOP);
	   glVertex3f( 2.3, 1.2 ,0);
	   glVertex3f( 4, 1.8,0);
	   glVertex3f( 4.2, .9 ,0);
	   glVertex3f( 2.3 ,.5 ,0);
	
   glEnd();

   // upper beak
   glColor4f(1,1,0,1);
   glBegin(GL_POLYGON);
	   glVertex3f( 2.3, .5 ,0);
	   glVertex3f( 4.5, -1,0);
	   glVertex3f( 4.7, -1.5 ,0);
	   glVertex3f( 4.7 ,-2.1 ,0);
	   glVertex3f( 4   , -1.7 ,0);
	   glVertex3f( .3 , -1  ,0);
	
   glEnd();

   // upper beak border
     glColor4f(0,0,0,1);
   glBegin(GL_LINE_LOOP);
	   glVertex3f( 2.3, .5 ,0);
	   glVertex3f( 4.5, -1,0);
	   glVertex3f( 4.7, -1.5 ,0);
	   glVertex3f( 4.7 ,-2.1 ,0);
	   glVertex3f( 4   , -1.7 ,0);
	   glVertex3f( .3 , -1  ,0);
	
   glEnd();
   
   // lower beak 

   glColor4f(1,1,0,1);
   glBegin(GL_POLYGON);
	   glVertex3f( .7, -2,0);
	  glVertex3f( 2, -1.4 ,0);
	   glVertex3f( 3.7 ,-1.6 ,0);;
	   glVertex3f( 2 ,  - 3.1 , 0);
	
   glEnd();

   // lower beak border

   glColor4f(0,0,0,1);
   glBegin(GL_LINE_LOOP);
	   
	   glVertex3f( .7, -2,0);
	   glVertex3f( 2, -1.4 ,0);
	   glVertex3f( 3.7 ,-1.6 ,0);
	   glVertex3f( 2 ,  - 3.1 , 0);
	  
   glEnd();

  // left chokher moni

   glColor4f(0,0,0,1);
   glBegin(GL_POLYGON);
   theta = 0 ;
   for(i=0 ; i<=100 ; i++,theta+=dtheta)
	   glVertex3f(1.4 + .2*cos(theta) , 1 + .2*sin(theta),0);
   glEnd();

   // right chokher moni

   glBegin(GL_POLYGON);
   theta = 0 ;
   for(i=0 ; i<=100 ; i++,theta+=dtheta)
	   glVertex3f(3 + .2*cos(theta) , 1 + .2*sin(theta),0);
   glEnd();

   glPopMatrix();

}


void gulti(void){

	glPushMatrix();

	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
    
	glVertex3f(15 ,20 , 0);
	glVertex3f(14 ,20 , 0);
    glVertex3f(19 ,14 , 0);
    glVertex3f(21 ,14 , 0);
	
	glEnd();

	glBegin(GL_POLYGON);

	

	glVertex3f(19 ,14 , 0);
	
	glVertex3f(19 , 0 , 0);
	

	
	glVertex3f(21 ,0 , 0);
	glVertex3f(21 ,14 , 0);

	
	
	glEnd();

	glBegin(GL_POLYGON);
    glColor3f(.2,.1,.1);
	glVertex3f(21 ,14 , 0);
    glColor3f(0,0,0);
	glVertex3f(26 ,20 , 0);
	glVertex3f(25 ,20 , 0);
	
	glVertex3f(20 ,15 , 0);
	
	glEnd();

		
	

	glPopMatrix();

}
void basket(int n ){

	int  pnts  = 100 ;
	double radx = 5 , rady = 1.5 ;
    double theta = 0 ;
	double dtheta = (2*pi) /pnts ;
    int i ;
	glPushMatrix();
	glTranslatef( basketx[n] , baskety[n] ,  0 );                  // translates to the position of the basket

     
 
	glColor3ub   (139, 37, 0);  
	glColor3f  (0, 0, 0);  // outer radious of the ellipse
	glBegin(GL_POLYGON);
	  for(  i = 0; i <=100; i++, theta += dtheta )
		{
			glVertex3f(radx* cos(theta),rady * sin(theta),.20);
			
		}
     
	glEnd();
    
	theta = 50*dtheta ;


    
                                            // lower part basket
	theta = 50*dtheta ;
	
	glBegin(GL_POLYGON);
	theta = 100* dtheta;
    glColor3ub   (139, 37, 0);
	for(  i = 50; i <=100; i++, theta -= dtheta )            
		{
			glVertex3f(radx* cos(theta),rady * sin(theta)-4,.4);
			glColor3ub   (205, 102 , 0);
		}
	
    theta = 51* dtheta;
	
	for(  i = 51; i <= 100; i++, theta += dtheta )           
		{
			glVertex3f(radx* cos(theta),rady * sin(theta),.4);
		}
	
	
	glEnd();
   
	
	
	glColor3ub   (139, 37, 0);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	theta = 100* dtheta;

	
	for(  i = 50; i <=100; i++, theta -= dtheta )                         // lower part border
		{
			glVertex3f(radx* cos(theta),rady * sin(theta)-4,.41);
		}
	
    theta = 51* dtheta;
	
	for(  i = 51; i <= 100; i++, theta += dtheta )           
		{
			glVertex3f(radx* cos(theta),rady * sin(theta),.41);
		}
	
	
	glEnd();
	



	glColor3f(0.65f, 0.9f, 1.0f);	
	glColor3ub   (218, 165, 32);      
	glColor3ub   (139, 37, 0); 
	glColor3ub   (205, 102 , 0);                                       //  sky in the middle
	glBegin(GL_POLYGON);
	for(  i = 0; i <=100; i++, theta += dtheta )
		{
			glVertex3f((radx-.5)* cos(theta),(rady-.5) * sin(theta), .25);
		}
	
	glEnd();
	 
	
	if(basketwithball[n])                                              //     ball in the basket
    {
		glTranslatef( 0 , 0 ,  .30 );
		angry_bird(true);
	   // drawCircle(radi);
		glTranslatef( 0 , 0 ,  -.30 );
    }

	
	
	glColor3f(0,0 ,0);
    theta = 100* dtheta;
	for(  i = 50; i <=100; i+=10, theta -= 10*dtheta )                         // lower part border
		{
			glBegin(GL_LINES);
			glVertex3f(radx* cos(theta),rady * sin(theta)-4,.42);
			glVertex3f(radx* cos(theta),rady * sin(theta),.42);
			glEnd();
		}
	glPopMatrix();
	/*
	for( theta = 0 ; theta < = radx ; theta+= radx/4){
	
		glBegin(GL_LINES);
	       glVertex3f(theta ,0 , 0);
	       glVertex3f(theta ,-rady, 0);
	    glEnd();
	}

	glPopMatrix();
*/
}



void updateball(float tm){

	 //printf("%f %f %f \n" , vely  ,bally , time );
	
	/*
     ballx =  inx  + velx*time ;
     bally =  iny +  vely*time - .5*50.0*time*time ;
	 */

	 //float tm = (time -stime )*.002 ;
	 //stime = time;

	 ballx = ballx + velx*tm ;                                      // update ball position x
	 bally = bally + vely*tm ;                                      // update ball position y
	 vely = vely - tm * 50 ;                                        // gravity effect ..... update velocity along y axis
	 maxy = max( maxy , (double)bally );
	
    // printf("tm %.14f %f %f \n" , tm , vely  ,bally  );
	
	 
	 if(bally < radi && vely < 0 && vely > - 2  )                    // no bounce if less velocity  
	 {
		 // printf(" first %f %f %f \n" , vely  ,bally , time );
	      ballx = inx ;
          bally = iny ;
          velx = 0 ;
          vely = 0 ;
		  maxy = 0 ;
		  fired = false ;
	 }

	 else if (bally < radi && vely < 0)                              // bouncing effect
			vely = -vely /3.5  ;
		
}



void update_score(){

	char text[100] = "Score : " ;
	char lev[100];
	char buff[100];

	strcat(text , score_s );
	Text(2 , 86 , text ,GLUT_BITMAP_TIMES_ROMAN_24);
	strcpy(text, "Level : ");
    sprintf(buff , "%d", level );
	strcat(text , buff);
	Text(2 , 82 , text ,GLUT_BITMAP_TIMES_ROMAN_24);

}
void drawlife(void)
{
   int x = radi  , y = orthoy - 2*radi ;
   int i ;

   for(i= 1 ; i<= life ; i++){
	glPushMatrix();
    
    //glTranslatef(-ballx + 2* i*radi ,-bally + y,0.0f);
	glTranslatef( 1.5* i*radi , y,0.0f);
	glScalef(.6,.6,1);
	angry_bird(1);
    glRotatef(0 , 0 ,0 ,1);

	glPopMatrix();
   
   
   }


}

void back(void){

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
   GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
   GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
   glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
   glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);


  glPushMatrix();
  glScalef(1,1,1);
  glTranslatef(0,0,-4);
  glRotatef(0 , 0 ,0 ,1);
  glColor3f(1,1,1);

  glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0  , 0 );
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f( orthox ,  0 , 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(orthox , orthoy , 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( 0 ,orthoy  , 0);
    glEnd();
  
	
 glPopMatrix();

 glDisable(GL_TEXTURE_2D);
}



void updatebasket(float tm){
 int i ;


 for( i=0 ; i<3 ;i++) basket(i);                                    // draws the baskets 

 for( i = 0 ; i<3 ; i++){                                           // updates the position of the basket
   
	basketx[i] = basketx[i]+ basketvelx[i]*tm ;
	baskety[i] = baskety[i]+ basketvely[i]*tm ;
	
	if(basketx[i] > orthox -radi){
		basketvelx[i]*=-1;
	    basketx[i] = orthox -radi ;
	}

	if( basketx[i]< 0 + radi + 50 ){
		basketvelx[i]*=-1;
	    basketx[i] = 0 + radi + 50 ;
	}

	if( baskety[i]< 5  ){
		basketvely[i]*=-1;
	    baskety[i] = 5 ;
	}

	if( baskety[i]> 90 ){
		basketvely[i]*=-1;
	    baskety[i] = 90 ;
	}
	
 }



 for(i=0 ; i<3 ; i++){                                             // checks if the ball is in the basket
   if(!basketwithball[i] && 
	   dist(ballx , bally , basketx[i] ,baskety[i]) < 2*radi &&    // is the ball close ?
	   maxy > baskety[i] + radi &&                                 // has it traversed sufficient height
	   vely < 0                                                    // is its motion downward  
	   )
   {
          basketwithball[i] = true ;
	      ballx = inx ;
          bally = iny ;
          velx = 0 ;
          vely = 0 ;
		  maxy = 0 ;
		  fired = false ;
		  ballcnt++ ;
		  score_i+=    (20 - life_level[level] + life ) * level * 10 + level*10 +  ballx*4 + maxy*4  ;
		  sprintf(score_s , "%d", score_i );
        //   itoa(score_i , score_s , 10 );
		  printf("%d %s\n",score_i,score_s);
   
   
   
   }
 }


 if(ballcnt == 3){
	 
		 
	

    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );
	
	

    back() ;
	gulti() ;
	if(onball) dirline();
    angry_bird();
	for( i=0 ; i<3 ;i++) basket(i);   
	drawlife();
	if(fired) updateball(tm);
    update_score();

    glutSwapBuffers();
    sleep(2000);

	for(i=0 ; i<3 ;i++)  basketwithball[i] = false ;
	 
	ballcnt = 0 ;
	level++ ;
	life = life_level[level];
	change();
 
 }
 
}
void display( void ){

	

	float time = clock();
	float tm = (time -stime_g )*.00001 ;                           // time passed since last update
	stime_g = time;

    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );
	
	

    back() ;
   

	if(level != 0 && level!=6)
	{
	 gulti() ;
	if(onball) dirline();
    angry_bird();
	updatebasket(tm);
	drawlife();

	if( life == 0 && velx ==0 && vely ==0 ){
	level = 0 ;
	change();
	}
    if(fired) updateball(tm);
    update_score();
	}
	usleep(5);
	glutSwapBuffers();
	glutPostRedisplay();
}






void mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
		  if (state == GLUT_DOWN){
		  mousex =  x* ( orthox / width);
		  mousey = (height - y + 1 )*( orthoy / height );


		  
		  float ds = dist( mousex , mousey , inx , iny );

		  //printf( " mouse ( %f , %f ) , ball ( %f, %f) with distance %f\n", mousex , mousey , ballx ,bally ,ds );
		  if(ds<radi){ 
			  onball = true ;
			  ballx  = mousex ;
			  bally  = mousey ;
		  }
		  
		  }
		  else if( state = GLUT_UP && onball ){
		  
		  mousex =  x* ( orthox / width);
		  mousey = (height - y + 1 )*( orthoy / height );
			 
		  vel = dist( mousex , mousey , inx , iny );
		  velangle = ang_with_hori(mousex , mousey , inx , iny );

		 // printf(" Released at mouse (%f,%f ) dist = %f , angle = %f\n" ,mousex , mousey , vel , velangle /degtorad);
		  velx = vel*cos(velangle)*5;
		  vely = vel*sin(velangle)*7;

		  stime_g = clock();
		  onball = false ;
		  fired  = true ;
		  life -- ;
		  
		  }
         break;
      case GLUT_MIDDLE_BUTTON:
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN);
         break;
      default:
         break;
   }
}


void mousemotion( int x , int y ){

	if(onball){
	
	      ballx =  mousex =  x* ( orthox / width);
		  bally =  mousey = (height - y + 1 )*( orthoy / height );
	
	}



}



void reshape (int w, int h)
{
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	width = w ; height = h ;
}

void init (void) 
{  
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glMatrixMode(GL_MODELVIEW);
   glClearColor(0, 1, 1 , 1);	
   glOrtho(0, orthox, 0, orthoy  , -5, 5);





   initRendering();

   /*
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
   GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
   GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
   glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
   glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
   
   */
/*
   life = life_level[level];
   int i ;
   for( i = 0 ; i<3 ; i++)
	   basketx[i] = 100 ;
   
   baskety[0] = 35  ;
   for( i=1 ; i<3 ; i++)
	   baskety[i] = baskety[i-1]+ 15;

   basketvelx[0] =   14 ;
   basketvelx[1] =  -28;
   basketvelx[2] =   12.5 ;

   basketvely[0] =   6 ;
   basketvely[1] =   2 ;
   basketvely[2] =   -3 ;
*/
}


void change(void){

	Image* image;
	image = loadBMP("images/angrybirdsbg.bmp");
    
	if(level == 0)
	{
	
	image = loadBMP("images/game_over.bmp");
	}
	
	if(level == 1)
	{
	//image = loadBMP("angrybirdsbg.bmp");
	
	 image = loadBMP("images/SunsetBird.bmp");
	}
	
    else if( level == 2)
	{
	image = loadBMP("images/house.bmp");
	
	}

	else if( level == 3)
	{
	image = loadBMP("images/angrybirdsbg.bmp");
	
	}

	else if( level == 4)
	{
	image = loadBMP("images/Nature2.bmp");
	
	}

	else if( level == 5){
	image = loadBMP("images/_vector-dandelion-vector-preview-by-dragonart.bmp");
	}

	else if(level == 6)
	{
	image = loadBMP("images/winner-win.bmp");
	}
	


	
	
	_textureId = loadTexture(image);
	delete image;



   life = life_level[level];
   int i ;
   for( i = 0 ; i<3 ; i++)
	   basketx[i] = 100 ;
   
   baskety[0] = 35  ;
   for( i=1 ; i<3 ; i++)
	   baskety[i] = baskety[i-1]+ 15;

   basketvelx[0] =   bs0_velx_lv[level] ;
   basketvelx[1] =   bs1_velx_lv[level] ;
   basketvelx[2] =   bs2_velx_lv[level] ;
   basketvely[0] =   bs0_vely_lv[level] ;
   basketvely[1] =   bs1_vely_lv[level] ;
   basketvely[2] =   bs2_vely_lv[level] ;

 
	//
	/*
	glDisable(GL_BLEND);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
   GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
   GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
   glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
   glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
*/

}
int  main( int argc, char *argv[] )
{
  

   glutInit( & argc, argv );
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (800, 600);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("2d Project BASKET THE BIRD");
   
   
  
   init ();
   

   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);
   glutMotionFunc(mousemotion);
   glutMainLoop();

   return 0;
}
