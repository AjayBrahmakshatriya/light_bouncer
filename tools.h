#define PI 3.1415926535897
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<fstream>
#include<iostream>
using namespace std;
int line(int x1,int y1,int x2,int y2,int z=0)
{
	glBegin(GL_LINES);
	glVertex3i(x1,y1,z);
	glVertex3i(x2,y2,z);
	glEnd();
}
int frectangle(int x1,int y1,int x2,int y2,int z=0)
{
	glBegin(GL_QUADS);
	glVertex3i(x1,y1,z);
	glVertex3i(x1,y2,z);
	glVertex3i(x2,y2,z);
	glVertex3i(x2,y1,z);
	glEnd();
}
int erectangle(int x1,int y1,int x2,int y2,int z=0)
{
	glBegin(GL_LINE_LOOP);
	glVertex3i(x1,y1,z);
	glVertex3i(x1,y2,z);
	glVertex3i(x2,y2,z);
	glVertex3i(x2,y1,z);
	glEnd();
}
float distance(float a,float b,float c,float d)
{
	return sqrt((c-a)*(c-a)+(b-d)*(b-d));
}
void printw (float x, float y, char format[],int size)
{   
	glColor3f(0,0,0);
	glRasterPos2f (x, y);
	int i;
	for(i = 0; format[i] != '\0'; i++)
		if(format[i]!='#')
		{
			if(size==10)
			        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, format[i]);
			if(size==24)
			 	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, format[i]);
		}
		else
		{
			y-=size;
			glRasterPos2f(x,y);
		}
}
void itoa(int v,char s[])
{
	int i=0;
	int t=abs(v);
	if(v==0)
		s[i++]='0';
	while(t)
	{
		s[i]=t%10+'0';
		t/=10;
		i++;
	}
	if(v<0)
		s[i++]='-';
	for(int v=0;v<i/2;v++)
	{
		char temp=s[v];
		s[v]=s[i-v-1];
		s[i-v-1]=temp;
	}
	s[i]='\0';
}
int drawimage(char fname[],int x1, int y1,int type=0)
{
	fstream f1;
	f1.open(fname,ios::in);
	char header[130];
	if(!type)
		f1>>header[0];
	if(type==1)
		for(int i=0;i<118;i++)
			f1>>header[i];
	else if(type==0)
		for(int i=0;i<119;i++)
			f1>>header[i];
	else if(type==2)
		for(int i=0;i<116;i++)
			f1>>header[i];
	int width,height;
	width=*((int*)&(header[17]));
	height=*((int*)&(header[21]));
	if(type==2)
	{
		height=600;
		width=800;
	}
	int padding=0;
	unsigned char R,G,B;
	glPointSize(1);
	if(width%4)
		padding=4-(3*width)%4;
	for(int y=0;y<height;y++)
	{
		for(int x=0;x<width;x++)
		{			
			f1>>B>>G>>R;
			float r=(int)R,g=(int)G,b=(int)B;
			if(r!=0 || g!=0 || b!=255)
			{
				glColor3f(r/255.0,g/255.0,b/255.0);
				glBegin(GL_POINTS);
				glVertex2f(x+x1,y+y1);
				glEnd();
			}
		}
		for(int k=0;k<padding;k++)
			f1>>B;
	}
	f1.close();
	glColor3f(0,0,0);
}
void drawCircle(float cx, float cy, float r, int num_segments=36) 
{ 
	glBegin(GL_LINE_LOOP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
		float x = r * cosf(theta); 
		float y = r * sinf(theta);
		glVertex2f(x + cx, y + cy);

	} 
	glEnd(); 
}
void drawfCircle(float cx, float cy, float r, int num_segments=36) 
{ 
	glBegin(GL_POLYGON); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); 
		float x = r * cosf(theta); 
		float y = r * sinf(theta);
		glVertex2f(x + cx, y + cy);

	} 
	glEnd(); 
}
void drawSpiral(float x,float y,float r,float c=4)
{
	for(float r1=0;r1<360;r1+=60)
	{
		glBegin(GL_LINES);
		for(float t=0;t<r;t++)
		{
			line(x+t*sin((360/c/r*t+r1)/180*PI),y+t*cos((360/c/r*t+r1)/180*PI),x+(t+1)*sin((360/c/r*(t+1)+r1)/180*PI),y+(t	+1)*cos((360/c/r*(t+1)+r1)/180*PI));
		}
		glEnd();
	}
}

