
#include<GL/glut.h>
#include<GL/glu.h>
#include<stdio.h>
// #include<GL/GLAUX.h>	
#include<math.h>							
#pragma comment( lib, "glaux.lib" )
#define PI 3.1415926535898


//OpenGL32.lib Glu32.lib Glaux.lib

#include "Vector.h"
#include "TextureLoader.h"



GLfloat	rcube = 0;				// Angle For The Quad
GLuint texture[50];				// Storage For two Texture

double space_rad = 150 ;
double inc = 1.5 ;
double dirinc = 2 ;

double zoom = 0 ;
double zoominc = 1.5 ;

double rotx = 0 ;
double roty = 0 ;


double dirotx = 0 ;
double diroty = 0 ;


double r = 1 ;


Vector eye(0,0,5) ;
Vector dir ;
Vector upv ; 



double eyex = 0, eyey = 0 , eyez = 5.0 , dirx =0 , diry = 0 , dirz = 0 , upx = 0 ,upy = 1 , upz = 0 ;
int viewflag = 0 ;


void LoadGLTextures()									
{
									
	// AUX_RGBImageRec* TextureImage;				
	unsigned char *TextureImage ;
	unsigned int width;
	unsigned height;
	glGenTextures(30, texture);	
	
	TextureImage = loadBMPRaw("images/mud.bmp" , width, height) ;	
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}
	TextureImage = loadBMPRaw("images/grass.bmp" , width, height , false) ;
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}
	TextureImage = loadBMPRaw("images/wall3.bmp" , width, height , false) ;
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}

	TextureImage = loadBMPRaw("images/tin.bmp" , width, height , false) ;
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}

	TextureImage = loadBMPRaw("images/door.bmp" , width, height , false);
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}


	TextureImage = loadBMPRaw("images/wood2.bmp" , width, height , false) ;
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}

	TextureImage = loadBMPRaw("images/marble.bmp" , width, height , false) ;
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}

	TextureImage = loadBMPRaw("images/innerwal.bmp" , width, height , false);
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[7]);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		// glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}
	TextureImage = loadBMPRaw("images/outwin.bmp" , width, height , false);
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[8]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}
	TextureImage = loadBMPRaw("images/inwin.bmp" , width, height , false) ;
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[9]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}


	TextureImage = loadBMPRaw("images/bed-sheet-250x250.172174907_std.bmp" , width, height , false);
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[10]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}

	TextureImage = loadBMPRaw("images/table.bmp" , width, height , false);
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[11]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}
	TextureImage = loadBMPRaw("images/15.bmp" , width, height , false);
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[12]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}
	TextureImage = loadBMPRaw("images/21.bmp" , width, height , false) ;
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[13]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}
	TextureImage = loadBMPRaw("images/Floral_Carpet_Texture_by_stocks_for_you.bmp" , width, height , false);
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[14]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}

	TextureImage = loadBMPRaw("images/paint.bmp" , width, height , false);
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[15]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}

	TextureImage = loadBMPRaw("images/p3.bmp" , width, height , false);
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[16]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}

	TextureImage = loadBMPRaw("images/wood3.bmp" , width, height , false) ;
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[17]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}
	
	TextureImage = loadBMPRaw("images/book1.bmp" , width, height , false) ;
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[18]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}
	TextureImage = loadBMPRaw("images/book2.bmp" , width, height , false) ;
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[19]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}

	TextureImage = loadBMPRaw("images/einstein2.bmp" , width, height , false);
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[20]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}
							
	TextureImage = loadBMPRaw("images/cab.bmp" , width, height , false) ;
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[21]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}

	TextureImage = loadBMPRaw("images/paint_horse.bmp" , width, height , false);
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[22]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}

	TextureImage = loadBMPRaw("images/color1.bmp" , width, height , false);
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[23]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}


	TextureImage = loadBMPRaw("images/p13.bmp" , width, height , false) ;
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[24]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}
	TextureImage = loadBMPRaw("images/ceiling6.bmp" , width, height , false) ;
	if ( TextureImage != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture[25]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, TextureImage);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
}


void cube()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);				//top
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f, 0.0f);		glVertex3f( 1.0f, 1.0f,-1.0f);					
		glTexCoord2f(1.0f, 0.0f);		glVertex3f(-1.0f, 1.0f,-1.0f);				
		glTexCoord2f(1.0f, 1.0f);		glVertex3f(-1.0f, 1.0f, 1.0f);					
		glTexCoord2f(0.0f, 1.0f);		glVertex3f( 1.0f, 1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);				//bottom
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);		glVertex3f( 1.0f,-1.0f, 1.0f);					
		glTexCoord2f(1.0f, 0.0f);		glVertex3f(-1.0f,-1.0f, 1.0f);					
		glTexCoord2f(1.0f, 1.0f);		glVertex3f(-1.0f,-1.0f,-1.0f);					
		glTexCoord2f(0.0f, 1.0f);		glVertex3f( 1.0f,-1.0f,-1.0f);	
		
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0]);				//front
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);		glVertex3f(-1.0f,-1.0f, 1.0f);					
		glTexCoord2f(1.0f, 0.0f);		glVertex3f( 1.0f,-1.0f, 1.0f);					
		glTexCoord2f(1.0f, 1.0f);		glVertex3f( 1.0f, 1.0f, 1.0f);					
		glTexCoord2f(0.0f, 1.0f);		glVertex3f(-1.0f, 1.0f, 1.0f);	
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);				//back
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);		glVertex3f( 1.0f,-1.0f,-1.0f);					
		glTexCoord2f(1.0f, 0.0f);		glVertex3f(-1.0f,-1.0f,-1.0f);				
		glTexCoord2f(1.0f, 1.0f);		glVertex3f(-1.0f, 1.0f,-1.0f);					
		glTexCoord2f(0.0f, 1.0f);		glVertex3f( 1.0f, 1.0f,-1.0f);	
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0]);				//left
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);		glVertex3f(-1.0f, 1.0f, 1.0f);					
		glTexCoord2f(0.0f, 1.0f);		glVertex3f(-1.0f, 1.0f,-1.0f);					
		glTexCoord2f(0.0f, 0.0f);		glVertex3f(-1.0f,-1.0f,-1.0f);					
		glTexCoord2f(1.0f, 0.0f);		glVertex3f(-1.0f,-1.0f, 1.0f);
	glEnd();		

	glBindTexture(GL_TEXTURE_2D, texture[1]);				//right
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);		glVertex3f( 1.0f, 1.0f,-1.0f);					
		glTexCoord2f(0.0f, 1.0f);		glVertex3f( 1.0f, 1.0f, 1.0f);					
		glTexCoord2f(0.0f, 0.0f);		glVertex3f( 1.0f,-1.0f, 1.0f);				
		glTexCoord2f(1.0f, 0.0f);		glVertex3f( 1.0f,-1.0f,-1.0f);	
	glEnd();											
}


void plane(double i , double j){
	
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f*r, 0.0f*r);		glVertex3f(0,0,0);					
		glTexCoord2f(1.0f*r, 0.0f*r);		glVertex3f(i,0,0);					
		glTexCoord2f(1.0f*r, 1.0f*r);		glVertex3f(i,j,0);				
		glTexCoord2f(0.0f*r, 1.0f*r);		glVertex3f(0,j,0);
	glEnd();



}

void front( double i , double j , double k){

    plane(i , j );
}


void back( double i , double j , double k){
 
  glPushMatrix();
  glTranslatef(0,0,-k);
  plane(i,j);
  glPopMatrix();

}

void bottom( double i , double j , double k){

  glPushMatrix();
  glScalef(1,1,1);
  glTranslatef(0,0,0.0f);
  glRotatef(-90 , 1 ,0 ,0);
  plane(i,k);
  glPopMatrix();

}

void up( double i , double j , double k){
  glPushMatrix();
  glScalef(1,1,1);
  glTranslatef(0,j,0.0f);
  glRotatef(-90 , 1 ,0 ,0);
  plane(i,k);
  glPopMatrix();

}
void left( double i , double j , double k){
  
  glPushMatrix();
  glScalef(1,1,1);
  glTranslatef(0,0,0.0f);
  glRotatef(90 , 0 ,1 ,0);
  plane(k,j);
  glPopMatrix();


}
void right( double i , double j , double k){

  glPushMatrix();
  glScalef(1,1,1);
  glTranslatef(i,0,0.0f);
  glRotatef(90 , 0 ,1 ,0);
  plane(k,j);
  glPopMatrix();

}


void cube( double i , double j , double k ){

//	glBindTexture(GL_TEXTURE_2D, texture[0]);
	front(i,j,k);
	back(i,j ,k);
	bottom(i,j,k);
	up(i, j ,k);
	left(i,j,k);
	right(i,j,k);


}

void setcamera(){

	if(viewflag==0){
	 
		eye.x =  0 ; eye.y = 0 ; eye.z = 1;
		eye = rotateVector(eye , I , rotx);
		eye = rotateVector(eye , J , roty);
		eye = eye*space_rad ;

		upv.x = 0 ; upv.y =1 ; upv.z =0 ;
	
		upv = rotateVector(upv , I , rotx);
		upv = rotateVector(upv , J ,  roty);

		dir = Origin - eye ;
		dir.norm() ;

	//	printf("%lf %lf %lf\n",upv.x , upv.y ,upv.z);
		gluLookAt (eye.x + zoom*dir.x, eye.y + zoom*dir.y, eye.z + zoom*dir.z, 0.0, 0.0, 0.0, upv.x, upv.y, upv.z); 

	
	}


	if(viewflag==1){
	  
	     dir.x = 0 ; dir.y = 0 , dir.z = -1 ;
         //Vector dir(0,0,-1);
		 dir = rotateVector(dir ,I , dirotx );
		 dir = rotateVector(dir ,J , diroty );

		 gluLookAt (eye.x + zoom*dir.x, eye.y + zoom*dir.y, eye.z + zoom*dir.z,  eye.x + zoom*dir.x + dir.x , eye.y + zoom*dir.y + dir.y , eye.z + zoom*dir.z + dir.z , 0.0, 1.0, 0.0); 

		 //gluLookAt (eye.x, eye.y, eye.z, eye.x + dir.x , eye.y + dir.y , eye.z + dir.z , 0.0, 1.0, 0.0); 
		//Vector move(dir.x , 0 , dir.z );
		//eye+= dirinc*move ;
      
	
	}

}


GLvoid pole_main(GLdouble rad,GLfloat x)
{
		glColor3f(1,1,1);

	GLint points = 100;
	GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
	GLdouble theta = 0.0;
	glPushMatrix();


	glBegin(GL_LINES);
	{
		for( GLint i = 0; i < points; i++, theta += delTheta )
		{
			glVertex3f(rad * cos(theta),x,rad * sin(theta));
			glVertex3f(rad * cos(theta),0,rad * sin(theta));
		}
	}
	glEnd();

	glPopMatrix();

}

void tin(){


	glBindTexture(GL_TEXTURE_2D, texture[3]);


	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f*r, 0.0f*r);		glVertex3f(0,0,0);					
		glTexCoord2f(1.0f*r, 0.0f*r);		glVertex3f(110,0,0);					
		glTexCoord2f(1.0f*r, 1.0f*r);		glVertex3f(64,15,-30);				
		glTexCoord2f(0.0f*r, 1.0f*r);		glVertex3f(46,15,-30);
	glEnd();

	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f*r, 0.0f*r);		glVertex3f(110,0,0);					
		glTexCoord2f(1.0f*r, 0.0f*r);		glVertex3f(110,0,-70);					
		glTexCoord2f(1.0f*r, 1.0f*r);		glVertex3f(64,15,-40);				
		glTexCoord2f(0.0f*r, 1.0f*r);		glVertex3f(64,15,-30);
	glEnd();

	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f*r, 0.0f*r);		glVertex3f(110 ,0,-70);					
		glTexCoord2f(1.0f*r, 0.0f*r);		glVertex3f(0,0,-70);					
		glTexCoord2f(1.0f*r, 1.0f*r);		glVertex3f(46,15,-40);				
		glTexCoord2f(0.0f*r, 1.0f*r);		glVertex3f(64,15,-40);
	glEnd();


	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f*r, 0.0f*r);		glVertex3f(0 ,0,-70);					
		glTexCoord2f(1.0f*r, 0.0f*r);		glVertex3f(0,0,0);					
		glTexCoord2f(1.0f*r, 1.0f*r);		glVertex3f(46,15,-30);				
		glTexCoord2f(0.0f*r, 1.0f*r);		glVertex3f(46,15,-40);
	glEnd();





}

void fence(){

   	glBindTexture(GL_TEXTURE_2D, texture[5]);

    int i , j , k ;
    r = .5 ;
	for(i = 0 ; i<60 ; i+=5){

		glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(i,0,0.0f);
		cube(2,8,1);
        glRotatef(0 , 0 ,0 ,1);
        glPopMatrix();
	
	
	}

	for(i = 90 ; i<=150 ; i+=5){

		glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(i,0,0.0f);
		cube(2,8,1);
        glRotatef(0 , 0 ,0 ,1);
        glPopMatrix();
	
	
	}


	for(i = 0 ; i<=150 ; i+=5){

		glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(i,0,-200);
		cube(2,8,1);
        glRotatef(0 , 0 ,0 ,1);
        glPopMatrix();
	
	
	}


	glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(0,4.5,-200);
		cube(150,1,1);
        glRotatef(0 , 0 ,0 ,1);
    glPopMatrix();


	glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(0,2.5,-200);
		cube(150,1,1);
        glRotatef(0 , 0 ,0 ,1);
    glPopMatrix();



	glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(0,4.5, 0);
		cube(60,1,1);
        glRotatef(0 , 0 ,0 ,1);
    glPopMatrix();

		glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(85,4.5, 0);
		cube(65,1,1);
        glRotatef(0 , 0 ,0 ,1);
    glPopMatrix();


	glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(0,2.5, 0);
		cube(60,1,1);
        glRotatef(0 , 0 ,0 ,1);
    glPopMatrix();

	glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(85,2.5, 0);
		cube(65,1,1);
        glRotatef(0 , 0 ,0 ,1);
    
		
		
	glPopMatrix();

	glPushMatrix();
	    glRotatef(90 , 0 ,1 ,0);
		glTranslatef(0, 0, 1);

	for(i = 0 ; i<=200 ; i+=5){

		glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(i,0,0);
		cube(2,8,1);
        glRotatef(0 , 0 ,0 ,1);
        glPopMatrix();
	
	
	}


	glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(0,2.5,0);
		cube(200,1,1);
        glRotatef(0 , 0 ,0 ,1);
    glPopMatrix();



	glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(0,4.5,0);
		cube(200,1,1);
        glRotatef(0 , 0 ,0 ,1);
    glPopMatrix();

	glTranslatef(0,0,150);


	for(i = 0 ; i<=200 ; i+=5){

		glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(i,0,0);
		cube(2,8,1);
        glRotatef(0 , 0 ,0 ,1);
        glPopMatrix();
	
	
	}


	glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(0,2.5,0);
		cube(200,1,1);
        glRotatef(0 , 0 ,0 ,1);
    glPopMatrix();



	glPushMatrix();
        glScalef(1,1,1);
        glTranslatef(0,4.5,0);
		cube(200,1,1);
        glRotatef(0 , 0 ,0 ,1);
    glPopMatrix();
        ;
        ;
    glPopMatrix();




}

void window(){

	int i ; int x= 15 ;

	for(i=0 ; i<2 ; i++ , x+=50)
	{
	
	glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(24.5 , 2.01 , -55.5+.01);
    glRotatef(0 , 0 ,0 ,1);
    
	glTranslatef(x , 5 , 0);
	glBindTexture(GL_TEXTURE_2D, texture[8]);
    front(20,10,.01);

	glPushMatrix();

	glTranslatef(0 , 0 , -5.1);
	glBindTexture(GL_TEXTURE_2D, texture[9]);
    front(20,10,.01);
	
    glTranslatef(0 , 0 , -123.5);
	front(20,10,.01);


	glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[8]);
	glTranslatef(0 , 0 , -130.5);
	front(20,10,.01);


    glPopMatrix();

	}
	

    for(i=0 ,x =15 ; i<3 ; i++ , x+= 35 )
	{
	glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(24.5-.01 , 2.01 , -55.5+.01);
    glRotatef(0 , 0 ,0 ,1);
    glTranslatef(0 , 5 , -x );
	

	glBindTexture(GL_TEXTURE_2D, texture[8]);
    left(.01,10,20);


	glPushMatrix();

	        glTranslatef(1 , 0 , 0);
	        glBindTexture(GL_TEXTURE_2D, texture[9]);
            left(.01,10,20);
	
    glTranslatef(98.5 , 0 , 0);
	 left(.01,10,20);


	glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[8]);
	glTranslatef(101.50 , 0 , 0 );
	left(.01,10,20);


    glPopMatrix();
    }


}


void walls(){

	glPushMatrix();
	glTranslatef(25.0 , 2.01 , -60.);
	glBindTexture(GL_TEXTURE_2D, texture[7]);


	glPushMatrix();
	glTranslatef(0 , 0  , -65.);
	cube(40,20,5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(35.0 , 0  , -80);
	cube(5,20,45);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(60.0 , 0  , 0);
	cube(5,20,30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(60.0 , 0  , -40);
	cube(40,20,5);
	glPopMatrix();


	
	glPushMatrix();
	glTranslatef(60.0 , 0  , -55);
	cube(5,20,30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(60.0 , 0  , -85);
	cube(40,20,5);
	glPopMatrix();




	glPopMatrix();




}


void sofa(){

   
   glBindTexture(GL_TEXTURE_2D, texture[12]);
   glTranslatef(2.0 , 0  , 0);
   r =1 ;
   cube(11 , 2 , 8);
   glTranslatef(-2.0 , 0  , 0);

   //glBindTexture(GL_TEXTURE_2D, texture[12]);
   //up(15,2.01,8);
 

   glBindTexture(GL_TEXTURE_2D, texture[13]);
   cube(2 , 3 ,  8);

   glPushMatrix();
	 glTranslatef(13.0 , 0  , 0);
     cube(2,3,8);
   glPopMatrix();

   glPushMatrix();
	 glTranslatef(0.0 , 0  , -5);
     cube(15,6,2);
   glPopMatrix();


}


void droom(){

	glPushMatrix();
	glTranslatef(25.0 , 2.01 , -60.);

	glTranslatef(2  , 0 , -(65-8));
	sofa();

	glTranslatef(20 , 0 , 0);
	sofa();

	glPopMatrix();

	
	
	
	glPushMatrix();
	glTranslatef(25.0 + 8 , 2.01 , -60.);
    glRotatef(90 , 0 ,1 ,0);
	glTranslatef(6 + 8 , 0  , 0.);
	//glTranslatef(2  , 0 , -(65-8));
	sofa();

	glTranslatef(20 , 0 , 0);
	sofa();



	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.0 + 40  , 2.01 , -68.);
    glRotatef(180 , 0 ,1 ,0);
	//glTranslatef(6 + 8 , 0  , 0.);
	//glTranslatef(2  , 0 , -(65-8));
	sofa();

	glTranslatef(20 , 0 , 0);
	sofa();

	glPopMatrix();

    //------------------ Carpet ----------------

	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, texture[14]);
	glTranslatef(25.0 , 2.5 , -60.);

	glTranslatef(15  , 0 , - 15 );
	r = 1 ;
	bottom(20 , 0 ,35);

	glPopMatrix();


    //-----------------Paintings -------------- 

	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTranslatef(25.0 , 2.5 , -60.);

	glTranslatef(12  , 8 , - 65 + .01 );
	r = 1 ;
	front(16 , 10 , 0);
	glTranslatef(1  , 1 ,  .05 );
	glBindTexture(GL_TEXTURE_2D, texture[15]);
	front(14 , 8  , 0);

	glPopMatrix();

}


void chair(int tx = 5){

glBindTexture(GL_TEXTURE_2D, texture[tx]);

glPushMatrix();
   glScalef(1,1,1);
   glTranslatef(0,0,0.0f);
   glRotatef(0 , 0 ,0 ,1);
   cube(1,3,1);
   glTranslatef(4,0,0.0f);
   cube(1,3,1);
   glTranslatef(0,0,-4.0f);
   cube(1,3,1);
   glTranslatef(-4,0,0.);
   cube(1,3,1);
glPopMatrix();

glPushMatrix();

glTranslatef(0,3,0.0f);
cube(5,.5, 5) ;
glTranslatef(0,.5, -4 );
cube(5, 4 , 1); 
glPopMatrix();


}

void table(int tx=5){


glBindTexture(GL_TEXTURE_2D, texture[tx]);
   

glPushMatrix();
      glScalef(1,1,1);
      glTranslatef(0,5,0.0f);
      glRotatef(0 , 0 ,0 ,1);
	  cube(30 , 1 , 16);
glPopMatrix();

glPushMatrix();
      glScalef(1,1,1);
      glTranslatef(5,0,-4);
      glRotatef(0 , 0 ,0 ,1);
	  cube(8 , 1 , 8);


	  glTranslatef(2,1,-2);
	  cube(4,4,4);
glPopMatrix();


glPushMatrix();
      glScalef(1,1,1);
      glTranslatef(5+8+6,0,-4);
      glRotatef(0 , 0 ,0 ,1);
	  cube(8 , 1 , 8);

	  glTranslatef(2,1,-2);
	  cube(4,4,4);
glPopMatrix();


}


void dine_room(){

      glPushMatrix();
        glScalef(1,1,1);
		glTranslatef(25.0 , 2.01 , -60.);
        glTranslatef(40,0,-90);
            
		    

			glTranslatef(20,0,-9.5);
		
			
			glPushMatrix();
			table();
			glTranslatef( 6 ,0, -16);
			chair();

			glTranslatef( 5+ 8 ,0, 0);
			chair();


			glPopMatrix();

			glPushMatrix();

			glRotatef(90 , 0 ,1 ,0);
			glTranslatef( 5.5 ,0, 0);
			chair();
			glPopMatrix();


			glPushMatrix();
                  glRotatef(180 , 0 ,1 ,0);
		          glTranslatef( -(5+6) ,0, 0);
			      chair();
				  glTranslatef( -8 ,0, 0);
                  chair();
			glPopMatrix();

			glPushMatrix();
                glTranslatef( 30 ,0, -(5+5.5));
				glRotatef(-90 , 0 ,1 ,0);
                chair();
			glPopMatrix();
       glPopMatrix();



	   // ---------------------- paintings -----------------

    glPushMatrix();

	glTranslatef(25.0 , 2.01 , -60.);

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	//glTranslatef(25.0 , 2.5 , -60.);

	glTranslatef( 99.5  , 8 , - (125 - 5 -16));
	r = 1 ;
	left(0 , 10 , 16);
	glTranslatef(-.5  , 1 ,  -1 );
	glBindTexture(GL_TEXTURE_2D, texture[16]);
	left(0 , 8  , 14);

	glPopMatrix();






}


void library(){

  glPushMatrix();
    glScalef(1,1,1);
	glTranslatef(25.0 , 2.01 , -60.);
    glTranslatef(76,0,-55);
	   glScalef(20.0/30,1, 10.0 /16);
	   glRotatef(90 , 0 ,1 ,0);
	   
	   table(17);
	   glRotatef(-90 , 0 ,1 ,0);
	   glScalef(30/20.0,1, 16/10.0);
       glTranslatef(0.5,0,-(7.5+5));
	   glRotatef(-90 , 0 ,1 ,0);
	   chair(17);
  glPopMatrix();


  glPushMatrix();
    glScalef(1,1,1);
	glTranslatef(25.0 , 2.01 , -60.);
	glTranslatef(65.0 ,  0 , -74.);
    glBindTexture(GL_TEXTURE_2D, texture[17]);
	cube(4 , 15 , 9.5 );
	glBindTexture(GL_TEXTURE_2D, texture[18]);
	right(4, 15 , 9.5 );



   
  glPopMatrix();

   glPushMatrix();
    glScalef(1,1,1);
	glTranslatef(25.0 , 2.01 , -60.);
	glTranslatef(95.0 ,  0, -48.);
    glBindTexture(GL_TEXTURE_2D, texture[17]);
	
	cube(4 , 15 , 10 );
	r = 3 ;
	glBindTexture(GL_TEXTURE_2D, texture[19]);
;   left(4 , 15 , 10 );
    


    glBindTexture(GL_TEXTURE_2D, texture[17]);
    glTranslatef( 0 ,  0, -12);

	cube(4 , 15 , 10 );
	r = 3 ;
	glBindTexture(GL_TEXTURE_2D, texture[19]);
;   left(4 , 15 , 10 );

    glBindTexture(GL_TEXTURE_2D, texture[17]);
    glTranslatef( 0 ,  0, -12.);

	cube(4 , 15 , 10 );
	r = 3 ;
	glBindTexture(GL_TEXTURE_2D, texture[19]);
;   left(4 , 15 , 10 );

   
  glPopMatrix();

  //-------------------- pictures ----------------

  glPushMatrix();
    glScalef(1,1,1);
	glTranslatef(25.0 , 2.01 , -60);
	glTranslatef(75.0 ,  8 , -84.9);
	
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    r = 1 ;
	front(16 , 10 , 0);
    	glTranslatef(1.0 ,  1 , 0.5);
	
		glBindTexture(GL_TEXTURE_2D, texture[20]);
	front(14 , 8  , 0);

 

   
  glPopMatrix();
   


}
void bed( double l ,  double b  , double h ,  double fbox , int tx = 10 ){

	 
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	cube(l ,h , b - fbox);

    glPushMatrix();

	r = 1 ;
	glBindTexture(GL_TEXTURE_2D, texture[tx]);
	glTranslatef(0 , h  , 0);
	cube(l,1,b-fbox);
	glPopMatrix();


	r =1 ;
	glBindTexture(GL_TEXTURE_2D, texture[11]);
	glPushMatrix();
	glTranslatef(0 , 0  , -b+fbox);
	cube(l, h+4 , fbox );
	glPopMatrix();
   



}


void masterbed(){

  glPushMatrix();
    glScalef(1,1,1);
	glTranslatef(25.0 , 2.01 , -60.);
    glTranslatef(8.5,0, -(125-22));
	bed(18 ,22 , 2  ,3 );
    glRotatef(0 , 0 ,0 ,1  );
  glPopMatrix();

  glPushMatrix();
    glScalef(1,1,1);

	r = 1 ;
	glBindTexture(GL_TEXTURE_2D, texture[21]);
	glTranslatef(25.0 , 2.01 , -60.);
	glTranslatef(0.0 , 0 , -70.05);

	r = 1  ;
	front(35/3.0 , 12 , 0);
	glTranslatef(0.0 , 12 , 0);
    front(35/3.0 , 4 , 0);

	glTranslatef(35/3.0 , -12 , 0);
  
	r = 1  ;
	front(35/3.0 , 12 , 0);
	glTranslatef(0.0 , 12 , 0);
    front(35/3.0 , 4 , 0);

	
	glTranslatef(35/3.0 , -12 , 0);
  
	r = 1  ;
	front(35/3.0 , 12 , 0);
	glTranslatef(0.0 , 12 , 0);
    front(35/3.0 , 4 , 0);
  glPopMatrix();


  glPushMatrix();
    glScalef(1,1,1);
	glTranslatef(25.0 , 2.01 , -60.);
    glTranslatef(0 ,0, -(125-5));
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	cube(8.5 ,5 ,5);
	glBindTexture(GL_TEXTURE_2D, texture[21]);
	front(8.5,5,5);

	glTranslatef(18+8.5 ,0,0);
		glBindTexture(GL_TEXTURE_2D, texture[5]);
	cube(8.5 ,5 ,5);
	glBindTexture(GL_TEXTURE_2D, texture[21]);
	front(8.5,5,5);



    glRotatef(0 , 0 ,0 ,1  );
  glPopMatrix();

 // ....................... pictures  .......................
   
  glPushMatrix();
    glScalef(1,1,1);
	glTranslatef(25.0 , 2.01 , -60.);
    glTranslatef(34.98, 5, -90);
		glBindTexture(GL_TEXTURE_2D, texture[5]);
	left(0, 12 , 25 );
	    glBindTexture(GL_TEXTURE_2D, texture[22]);
    glTranslatef(-.05, 1 , -1);

	left(0 , 10 , 23);

    glRotatef(0 , 0 ,0 ,1  );
  glPopMatrix();




}

void normalbed(){

  glPushMatrix();
    glScalef(1,1,1);
	glTranslatef(25.0 , 2.01 , -60.);
    glTranslatef(100-22,0, -(8.5 + 18));
    glRotatef(-90 , 0 ,1 ,0  );
	bed(18 ,22 , 2  ,3 ,23);
    glRotatef(0 , 0 ,0 ,1  );
  glPopMatrix();


  glPushMatrix();
    glScalef(1,1,1);
	glTranslatef(25.0 , 2.01 , -60.);
    glTranslatef(100-5,0, 0);
    
		glBindTexture(GL_TEXTURE_2D, texture[5]);
	cube(5 ,5 ,8.5);
        glBindTexture(GL_TEXTURE_2D, texture[21]);
	left(5, 5,8.5);
    glRotatef(0 , 0 ,0 ,1  );
  glPopMatrix();


  // ................pictures ............


  glPushMatrix();
    glScalef(1,1,1);
	glTranslatef(25.0 , 2.01 , -60.);
    glTranslatef(70, 5, -(40 -.05));
    glBindTexture(GL_TEXTURE_2D, texture[5]);
	front(25 , 12 , 0);
    
	glTranslatef( 1 , 1 , 0.5);
    
	glBindTexture(GL_TEXTURE_2D, texture[24]);
	front(23 ,10 , 0 );

	//bed(18 ,22 , 2  ,3 ,23);
    glRotatef(0 , 0 ,0 ,1  );
  glPopMatrix();



}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	setcamera() ;
//	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
	glRotatef(rcube,1.0f,1.0f,1.0f);						// Rotate The Triangle On The Y axis ( NEW )
 //	cube(150,5,150);
	glPushMatrix();
    glTranslatef(-75 , -10 , 100);
     
	//bed(20,25,5,5);
//	sofa();
    //----------------- Basement ----------------
	glPushMatrix();                               
	r=1;
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	cube(150,2,200);                                        
    glPopMatrix();
    

	//----------------- Grass --------------------

    glPushMatrix();
	r = 10 ; ;
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	up(150,2.00 , 200);
    glPopMatrix();
	
	//----------------- Main Box ----------------

    glPushMatrix();
	glTranslatef(24.5 , 2.01 , -55.5);
	r = 5 ; ;
	glBindTexture(GL_TEXTURE_2D, texture[2]);
    cube(101,21 ,130);
    glPopMatrix();

    //---------------- Door ----------------------
    
	glPushMatrix();
	r=1;
	
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTranslatef(24.5 , 2 , -55.5+ 0.01);
	glTranslatef(45.25 , 0 , 0);
	front(10 , 15 , 0);
	glTranslatef(0 , 0 , -4.8);
	front(10 , 15 , 0);
    glPopMatrix();

	//----------------- Window -------------------

	window();

	//-----------------Tin------------------------

	glPushMatrix();
	glTranslatef(19 , 23 , -52);
	r = 4 ; ;
//	glScalef(1.2,1,1.3);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
//	tin();
	cube(114 ,2 ,132);
    glPopMatrix();

	//----------------Fence----------------------
	fence();

	//--------------- Inner Structure  -----------------------
    
	glPushMatrix();
	glTranslatef(25.0 , 2.01 , -60.);
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	r= 5;
    cube(100.,20 ,125);
	

	//----------------------- floor ---------
	r = 10 ; ;
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    cube(100,.02 ,125);

	
	// -----------------------ceil  ------------
	r = 6;
	;glBindTexture(GL_TEXTURE_2D, texture[25]);
	 up(100,19.98 ,125);



    glPopMatrix();

    //============ bed ============================
/*
	glPushMatrix();
	glTranslatef(25.0 , 2.01 , -60.);
    glTranslatef( 10.0 , 0 , -(125 - 25.));

    bed(15,25,3,5);
    //cube(100,.02 ,125);
    glPopMatrix();
*/
	
	masterbed() ;

	normalbed() ;

	//---------------Inside Walls ---------------
    r = 5 ;
	walls() ;

	//---------------------drawing room -----------

	droom();

    //-------------------- dine room ---------------


   	dine_room();
	
	//-------------------- library -----------------

	library();

	glPopMatrix();
	//pole_main(.25 , 1);
 	glutSwapBuffers() ;

}




void spinDisplay(void)
{
	rcube = rcube-0.15;
    glutPostRedisplay();
}

void init(void)
{
	LoadGLTextures();
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}


void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 0.1f, 500.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}



void spe_key(int key, int x, int y) 
{
   
	switch (key) {

		case GLUT_KEY_RIGHT:

			if(viewflag==0){
			roty+= inc;
			if(roty>360) roty -= 360 ;
            glutPostRedisplay();
			}

			if(viewflag==1){
			diroty-=inc;
			if(diroty<0) diroty+= 360 ;
			glutPostRedisplay();
			//	printf("%lf %lf %lf %lf\n" , dirotx , diroty , rotx , roty);
			
			}

			break;

		case GLUT_KEY_LEFT:
			
			if(viewflag==0){
			roty-=inc;
			if(roty<0) roty+= 360 ;
			glutPostRedisplay();
			}

		
			if(viewflag==1){
			diroty+= inc;
			if(diroty>360) diroty -= 360 ;
            glutPostRedisplay();
			//	printf("%lf %lf %lf %lf\n" , dirotx , diroty , rotx , roty);
			
			}
			break;

		case GLUT_KEY_DOWN:
		
			if(viewflag==0){
			rotx+=inc;
			if(rotx>360) rotx-= 360 ;
             glutPostRedisplay();
			}

		
			if(viewflag==1){
			dirotx-= inc;
			if(dirotx<0) dirotx+= 360 ;
			glutPostRedisplay();
				//printf("%lf %lf %lf %lf\n" , dirotx , diroty , rotx , roty);
			
			}
			break;

		case GLUT_KEY_UP:
		
			if(viewflag==0){
			rotx-= inc;
			if(rotx<0) rotx+= 360 ;
			glutPostRedisplay();
			}

			
			if(viewflag==1){
			dirotx+=inc;
			if(dirotx>360) dirotx-= 360 ;
            glutPostRedisplay();
		//	printf("%lf %lf %lf %lf\n" , dirotx , diroty , rotx , roty);
			
			}
			break;

	  default:
			break;
	}
}

void my_keyboard(unsigned char key, int x, int y) 
{
   
	switch (key) {


		case 'w':
			if(viewflag==1){
			dir.x = 0 ; dir.y = 0 , dir.z = -1 ;
            dir = rotateVector(dir ,I , dirotx );
		    dir = rotateVector(dir ,J , diroty );
			Vector move(dir.x , 0 , dir.z );
		    eye=  eye + dirinc*move ;
			glutPostRedisplay();
			}
			break;

		case 's':
            if(viewflag==1){
			dir.x = 0 ; dir.y = 0 , dir.z = -1 ;
            dir = rotateVector(dir ,I , dirotx );
		    dir = rotateVector(dir ,J , diroty );
			Vector move(dir.x , 0 , dir.z );
		    eye=  eye - dirinc*move ;
			glutPostRedisplay();
			}
	
			break;

		case 'a':
		//	spinDisplay_left();

			if(viewflag==1){
			dir.x = 0 ; dir.y = 0 , dir.z = -1 ;
            dir = rotateVector(dir ,I , dirotx );
		    dir = rotateVector(dir ,J , diroty );
			Vector move(dir.x , 0 , dir.z );
			move = rotateVector(move , J , 90);
		    eye=  eye + dirinc*move ;
			glutPostRedisplay();
			}
			break;

		case 'd':
		//	spinDisplay_right();

			if(viewflag==1){
			dir.x = 0 ; dir.y = 0 , dir.z = -1 ;
            dir = rotateVector(dir ,I , dirotx );
		    dir = rotateVector(dir ,J , diroty );
			Vector move(dir.x , 0 , dir.z );
			move = rotateVector(move , J , 90);
		    eye=  eye - dirinc*move ;
			glutPostRedisplay();
			}
			break;

		case 'i':

			if(viewflag==0){ zoom+= zoominc ;
			glutPostRedisplay();
			}

			if(viewflag==1){ zoom+= zoominc ;
			glutPostRedisplay();
			}
			break ;
		case 'o':
			if(viewflag==0){
			zoom-= zoominc ;
			glutPostRedisplay();
			}

			if(viewflag==1){
			zoom-= zoominc ;
			glutPostRedisplay();
			}
			break ;

		case '1':
			viewflag = 0 ;
			rotx =0 ; roty = 0;
			rcube=0 ;
			zoom = 0 ;
            glutPostRedisplay();
			break;

		case '2':
			viewflag = 1 ;
			eye.x = 0 ; eye.y = 5 ; eye.z = space_rad ;
			upv.x = 0 ; upv.y = 1 ; upv.z = 0 ;
			rcube=0;
			dirotx = 0 ; diroty =0 ;
			zoom = 0;
            glutPostRedisplay();
			break;

	  default:
			break;
	}
}


void mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay);
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
      default:
         break;
   }
}

int  main( int argc, char *argv[] )
{
  

   glutInit( & argc, argv );
   printf("\n\t\tPress mouse left button to rotate and right button to stop.\n");
   printf("\n\t Press 1 for Satellite View\n");
   printf("\n\t Press 2 for Walking View\n")  ;
   printf("\n\t Use Arrow Keys To Change the Eye Position in mode 1\n")  ;
   printf("\n\t Use Arrow Keys To Change the looking direction in mode 2\n")  ;
   printf("\n\t Use w.s.a.d Keys To Change the looking direction in mode 2\n")  ;
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (850, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("lab_10");
   init ();

   glutKeyboardFunc(my_keyboard);
   glutSpecialFunc(spe_key);
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);

   glutMainLoop();
   return 0;
}