
#if __APPLE__
#include<OpenGL/gl.h>
#include<OpenGL/glu.h>
#include<GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/gluh.h>
#include <GL/glut.h>
#endif
//This is just a extra tool made for easy making of levels, hence it is not formatted. The code written for this is very crude made just for serving the purpose.
#include"tools.h"
#include<stdlib.h>
int manstate=0;
int px1,py1;
float px=80,py=300,pa=0;
int drag=0;
int game=0;
int *selection=NULL;
int seltype=0;
//mirror=0;
//block=1;
//wormhole1=2;
//wormhole2=3;
class wormhole{
	public:
		float x1,y1,x2,y2;
		wormhole()
		{
			x1=150;y1=300;x2=250;y2=300;
		}
		void draw()
		{
			glLineWidth(2);
			glColor3f(0.5,0.5,0.5);
			line(x1,y1,x2,y2);
			drawfCircle(x1,y1,40);
			drawfCircle(x2,y2,40);
			glColor3f(0,0,0);
			drawCircle(x1,y1,40);
			drawCircle(x2,y2,40);
			drawSpiral(x1,y1,40);
			drawSpiral(x2,y2,40);
			glColor3f(0,1,0);
			glLineWidth(1);
			if(selection==(int*)this && seltype==2)
				erectangle(x1-50,y1-50,x1+50,y1+50);
			if(selection==(int*)this && seltype==3)
				erectangle(x2-50,y2-50,x2+50,y2+50);
		}
		int checkcoll1()
		{
			if(distance(px,py,x1,y1)<=40)
				return 1;
			return 0;
		}
		int checkcoll2()
		{
			if(distance(px,py,x2,y2)<=40)
				return 1;
			return 0;
		}
};
int wcount=0;
wormhole *wormholes[5];
class block{
	public:
		float x,y;
		block(){
			x=255;y=155;
		}
		int checkcoll()
		{
			if(px>x-20 && px<x+20 && py>y-20 && py<y+20)
				return 1;
			return 0;
		}
		void draw()
		{
			glColor3f(0,1,0);
			if((block*)selection==this)
				erectangle(x-50,y-50,x+50,y+50);
			glColor3f(0,0,0);
			frectangle(x-20,y-20,x+20,y+20);
		}
};
block *blocks[100];
int bcount=0;
class mirror{
	public:
		float x,y;
		float rot;
		mirror(){
			x=0;
			y=0;
			rot=0;
		}
		int checkcoll()
		{
			if(distance(x,y,px,py)<40)
				for(float r=-40;r<=40;r+=1)
					if(distance(px,py,x-r*sin(rot/180*PI),y+r*cos(rot/180*PI))<=2)
						return 1;
			return 0;
		}
		void draw()
		{
			if(x<=55)
				x=55;
			if(y<=155)
				y=155;
			if(x>745)
				x=745;
			if(y>545)
				y=545;
			while(rot>180)
				rot-=360;
			while(rot<=-180)
				rot+=360;
			glColor3f(0,1,0);
			if((mirror*)selection==this)
				erectangle(x-50,y-50,x+50,y+50);
			glColor3f(0,0,0);
			glLineWidth(2);
			line(x-40*sin(rot/180*PI),y+40*cos(rot/180*PI),x+40*sin(rot/180*PI),y-40*cos(rot/180*PI));
			float x1=x-10*cos(rot/180*PI);
			float y1=y-10*sin(rot/180*PI);
			for(int k=-35;k<=35;k+=10)
				line(x-k*sin(rot/180*PI),y+k*cos(rot/180*PI),x1-(k+5)*sin(rot/180*PI),y1+(k+5)*cos(rot/180*PI));
			glLineWidth(1);
			char r[5];
			itoa(rot,r);
			printw(x+30,y-30,r,10);
		}
};
mirror *mirrors[20];
int mcount=0;
void drawstage()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(0.9,0.9,0.9);
	frectangle(5,5,795,595);
	glColor3f(0.8,0.8,0.8);
	for(int x=5;x<=795;x+=10)
		line(x,105,x,595);
	for(int y=105;y<=595;y+=10)
		line(5,y,795,y);
	glColor3f(0,0,0);
	glLineWidth(2);
	erectangle(5,5,795,595);
	erectangle(5,5,105,105);
	erectangle(105,105,205,5);
	erectangle(205,105,305,5);
	erectangle(305,105,405,5);
	erectangle(405,105,505,5);
	erectangle(505,105,605,5);
	printw(120,55,"RESET",24);
	printw(220,55,"BLOCK",24);
	printw(320,55,"WORM",24);
	printw(420,55,"SAVE",24);
	printw(520,55,"LOAD",24);
	line(5,105,795,105);
	glLineWidth(1);
	for(int k=0;k<bcount;k++)
		blocks[k]->draw();
	for(int k=0;k<mcount;k++)
		mirrors[k]->draw();
	for(int k=0;k<wcount;k++)
		wormholes[k]->draw();
	glLineWidth(2);
	glColor3f(0,0,0);
	erectangle(5,290,35,310);
	line(35,300,80,300);
	glPointSize(7);
	glBegin(GL_POINTS);
	glVertex2f(80,300);
	glEnd();
	int h=10;
	for(int x=40;x<80;x+=10,h-=2)
		line(x,300-h,x,300+h);
	glColor3f(0,0,0);
	glLineWidth(2);
	line(55-40*sin(-45.0/180*PI),55+40*cos(-45.0/180*PI),55+40*sin(-45.0/180*PI),55-40*cos(-45.0/180*PI));
	float x1=55-10*cos(-45.0/180*PI);
	float y1=55-10*sin(-45.0/180*PI);
	for(int k=-35;k<=35;k+=10)
		line(55-k*sin(-45.0/180*PI),55+k*cos(-45.0/180*PI),x1-(k+5)*sin(-45.0/180*PI),y1+(k+5)*cos(-45.0/180*PI));
	if(manstate==0)
		drawimage("images/man0.bmp",735,300-55);
	else if(manstate==1)
		drawimage("images/man1.bmp",737,302-55);
	else if(manstate==2)
		drawimage("images/man2.bmp",736,297-55);
	else if(manstate==3)
		drawimage("images/man3.bmp",650,297-55);
}
void draw(void)
{
	if(!game)
	{
		drawstage();
	}
	else
	{
		px+=0.2*cos(pa/180*PI);
		py+=0.2*sin(pa/180*PI);
		glLineWidth(2);
		glColor3f(1,0,0);
		line(px1,py1,px,py);
		glLineWidth(1);
		px1=px;
		py1=py;
		if(px<5 || px>795 || py<105 || py>595)
		{
			manstate=1;

			game=0;
		}
		if(distance(px,py,765,327)<=28 || px>=755 && px<=775 && py>=248 && py<=300)
		{

			manstate=3;
			game=0;
		}
		if(distance(px,py,765,365)<=10)
		{

			manstate=2;
			game=0;
		}

		for(int k=0;k<bcount;k++)
			if(blocks[k]->checkcoll())
			{
				manstate=1;

				game=0;
				break;
			}
		for(int k=0;k<wcount;k++)
		{
			if(wormholes[k]->checkcoll1())
			{

				px=wormholes[k]->x2+wormholes[k]->x1-px;
				py=wormholes[k]->y2+wormholes[k]->y1-py;

				px1=px;
				py1=py;
				px+=0.2*cos(pa/180*PI);
				py+=0.2*sin(pa/180*PI);
			}
			else if(wormholes[k]->checkcoll2())
			{

				px=wormholes[k]->x1+wormholes[k]->x2-px;
				py=wormholes[k]->y1+wormholes[k]->y2-py;

				px1=px;
				py1=py;
				px+=0.2*cos(pa/180*PI);
				py+=0.2*sin(pa/180*PI);
			}
		}
		for(int k=0;k<mcount;k++)
		{
			if(mirrors[k]->checkcoll() && game)
			{
				if(abs(pa-mirrors[k]->rot)<=90)
				{

					game=0;

					manstate=1;
				}
				else
				{

					float r=mirrors[k]->rot;
					pa=180+pa;
					while(pa>180)
						pa=pa-360;
					while(pa<-180)
						pa+=360;
					pa=r+r-pa;
					while(pa>180)
						pa=pa-360;
					while(pa<-180)
						pa+=360;
					px+=5*cos(pa/180*PI);
					py+=5*sin(pa/180*PI);
					glLineWidth(2);
					glColor3f(1,0,0);
					line(px1,py1,px,py);
					glLineWidth(1);
					px1=px;
					py1=py;
				}
			}
		}
	}
	glFlush();
	glutPostRedisplay();
}
void spkeyhandler(int key,int x,int y)
{
	if(key==GLUT_KEY_LEFT && selection!=NULL)
		if(seltype=0)
			((mirror*)selection)->x-=1;
		else if(seltype=1)
			((block*)selection)->x-=1;
		else if(seltype=2)
			((wormhole*)selection)->x1-=1;
		else if(seltype=3)
			((wormhole*)selection)->x2-=1;

	if(key==GLUT_KEY_RIGHT && selection!=NULL)
		if(seltype=0)
			((mirror*)selection)->x+=1;
		else if(seltype=1)
			((block*)selection)->x+=1;
		else if(seltype=2)
			((wormhole*)selection)->x1+=1;
		else if(seltype=3)
			((wormhole*)selection)->x2+=1;

	if(key==GLUT_KEY_UP && selection!=NULL)
		if(seltype=0)
			((mirror*)selection)->y+=1;
		else if(seltype=1)
			((block*)selection)->y+=1;
		else if(seltype=2)
			((wormhole*)selection)->y1+=1;
		else if(seltype=3)
			((wormhole*)selection)->y2+=1;
	if(key==GLUT_KEY_DOWN && selection!=NULL)
		if(seltype=0)
			((mirror*)selection)->y-=1;
		else if(seltype=1)
			((block*)selection)->y-=1;
		else if(seltype=2)
			((wormhole*)selection)->y1-=1;
		else if(seltype=3)
			((wormhole*)selection)->y2-=1;
}
void dragger(int x,int y)
{
	if(drag && selection!=NULL)
	{
		if(seltype==0)
		{
			((mirror*)selection)->x=x;
			((mirror*)selection)->y=600-y;
		}
		else if(seltype==1)
		{
			((block*)selection)->x=x;
			((block*)selection)->y=600-y;
		}
		else if(seltype==2)
		{
			((wormhole*)selection)->x1=x;
			((wormhole*)selection)->y1=600-y;
		}
		else if(seltype==3)
		{
			((wormhole*)selection)->x2=x;
			((wormhole*)selection)->y2=600-y;
		}
	}
}
void keyhandler(unsigned char key,int x,int y)
{

	if(key==27)
		exit(0);
	if(key==' ')
		game=0;
	if(key==127 && selection!=NULL)
	{
		for(int k=0;k<mcount;k++)
			if(mirrors[k]==(mirror*)selection)
			{
				delete(mirrors[k]);
				for(int j=k;j<mcount-1;j++)
					mirrors[j]=mirrors[j+1];
				mcount--;
				break;
			}
		for(int k=0;k<bcount;k++)
			if(blocks[k]==(block*)selection)
			{
				delete(blocks[k]);
				for(int j=k;j<bcount-1;j++)
					blocks[j]=blocks[j+1];
				bcount--;
				break;
			}
		for(int k=0;k<wcount;k++)
			if(wormholes[k]==(wormhole*)selection)
			{
				delete(wormholes[k]);
				for(int j=k;j<wcount-1;j++)
					wormholes[j]=wormholes[j+1];
				wcount--;
				break;
			}
	}
	if(key==13)
	{
		manstate=0;
		selection=NULL;
		drawstage();
		pa=0;
		px=80;
		py=300;
		game=1;
		px1=px;py1=py;

	}
}
void mousehandler(int button,int state,int x,int y){
	y=600-y;
	if(button==3 && selection!=NULL && seltype==0)
		((mirror*)selection)->rot+=2.5;
	if(button==4 && selection!=NULL && seltype==0)
		((mirror*)selection)->rot-=2.5;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && x>=0 && y>=0 && x<=800 && y<=600)
	{
		manstate=0;
		if(x>=505 && x<=605 && y>=5 && y<=105)
		{

			int t=mcount;
			for(int k=0;k<t;k++)
			{
				delete(mirrors[k]);
				mcount--;
			}
			t=bcount;
			for(int k=0;k<t;k++)
			{
				delete(blocks[k]);
				bcount--;
			}
			t=wcount;
			for(int k=0;k<t;k++)
			{
				delete(wormholes[k]);
				wcount--;
			}

			cout<<"Please enter a file name of the format lx";
			char fname[20];
			cin>>fname;
			fstream f1;
			f1.open(fname,ios::in);
			f1>>mcount;
			for(int k=0;k<mcount;k++)
			{
				mirrors[k]= new mirror();
				f1>>mirrors[k]->x>>mirrors[k]->y>>mirrors[k]->rot;
			}
			f1>>bcount;
			for(int k=0;k<bcount;k++)
			{
				blocks[k]=new block();
				f1>>blocks[k]->x>>blocks[k]->y;
			}
			f1>>wcount;
			for(int k=0;k<wcount;k++)
			{
				wormholes[k]=new wormhole();
				f1>>wormholes[k]->x1>>wormholes[k]->y1>>wormholes[k]->x2>>wormholes[k]->y2;
			}
			f1.close();
		}
		if(x>=405 && x<=505 && y>=5 && y<=105)
		{
			cout<<"Please enter number of free mirrors";
			int nb;
			cin>>nb;
			cout<<"Please enter a file name of the format lx";
			char fname[20];
			cin>>fname;
			fstream f;
			f.open(fname,ios::out);
			f<<mcount<<"\n";
			for(int k=0;k<mcount;k++)
				f<<mirrors[k]->x<<" "<<mirrors[k]->y<<" "<<mirrors[k]->rot<<"\n";
			f<<bcount<<"\n";
			for(int k=0;k<bcount;k++)
				f<<blocks[k]->x<<" "<<blocks[k]->y<<"\n";
			f<<wcount<<"\n";
			for(int k=0;k<wcount;k++)
				f<<wormholes[k]->x1<<" "<<wormholes[k]->y1<<" "<<wormholes[k]->x2<<" "<<wormholes[k]->y2<<"\n";
			f<<nb;
			f.close();
		}

		if(x>=105 && x<=205 && y>=5 && y<=105)
		{
			int t=mcount;
			for(int k=0;k<t;k++)
			{
				delete(mirrors[k]);
				mcount--;
			}
			t=bcount;
			for(int k=0;k<t;k++)
			{
				delete(blocks[k]);
				bcount--;
			}
			t=wcount;
			for(int k=0;k<t;k++)
			{
				delete(wormholes[k]);
				wcount--;
			}
		}
		if(x>=5 && y>=5 && y<=105 && x<=105)
		{
			mirror *temp;
			temp=new mirror();
			mirrors[mcount]=temp;
			mcount++;
			selection=(int*)temp;
			seltype=0;
			drag=1;
			return;
		}
		if(x>=205 && y>=5 && y<=105 && x<=305)
		{
			block *temp;
			temp=new block();
			blocks[bcount]=temp;
			bcount++;
			selection=(int*)temp;
			seltype=1;
			drag=1;
			return;
		}
		if(x>=305 && y>=5 && y<=105 && x<=405)
		{
			wormhole *temp;
			temp=new wormhole();
			wormholes[wcount]=temp;
			selection=NULL;
			wcount++;
			return;
		}
		int flag=1;
		for(int k=0;k<mcount;k++)
			if(!game && x>=mirrors[k]->x-40 &&x<=mirrors[k]->x+40 && y>=mirrors[k]->y-40 &&y<=mirrors[k]->y+40)
			{ flag=0;
				seltype=0;
				selection=(int*)mirrors[k];drag=1;break;}
		for(int k=0;k<bcount;k++)
			if(!game && x>=blocks[k]->x-20 &&x<=blocks[k]->x+20 && y>=blocks[k]->y-20 &&y<=blocks[k]->y+20)
			{ flag=0;
				seltype=1;
				selection=(int*)blocks[k];drag=1;break;}
		for(int k=0;k<wcount;k++)
		{
			if(!game && distance(x,y,wormholes[k]->x1,wormholes[k]->y1)<40)
			{ flag=0;
				seltype=2;
				selection=(int*)wormholes[k];drag=1;break;}
			if(!game && distance(x,y,wormholes[k]->x2,wormholes[k]->y2)<40)
			{ flag=0;
				seltype=3;
				selection=(int*)wormholes[k];drag=1;break;}
		}
		if(flag)
		{
			selection=NULL;
			drag=0;
		}
	}
}
int init()
{
	glClearColor(1,1,1,0);
	glColor3f(0,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,800,0,600);
}
int main(int argc, char ** argv)
{

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutCreateWindow("Level builder");
	glutDisplayFunc(draw);
	glutMouseFunc(mousehandler);
	glutKeyboardFunc(keyhandler);
	glutSpecialFunc(spkeyhandler);
	glutMotionFunc(dragger);
	init();
	glutMainLoop();
}
