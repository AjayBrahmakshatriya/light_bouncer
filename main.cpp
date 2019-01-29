
#if __APPLE__
#include<OpenGL/gl.h>
#include<OpenGL/glu.h>
#include<GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/gluh.h>
#include <GL/glut.h>
#endif

#include<stdlib.h>
#include"tools.h"
#include"declarations.h"
#include"wormhole.h"
#include"block.h"
#include"mirror.h"
bool hasDrawn = false;


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
	erectangle(695,5,795,105);
	frectangle(725,30,765,60);
	glColor3f(0.9,0.9,0.9);
	frectangle(740,30,750,45);
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	glVertex2f(780,60);
	glVertex2f(745,90);
	glVertex2f(710,60);
	glVertex2f(725,60);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(240,35);
	glVertex2f(240,75);
	glVertex2f(280,55);
	glEnd();
	line(5,105,795,105);
	printw(125,50,"Reset",24);
	glLineWidth(1);
	for(int k=0;k<bcount;k++)
		blocks[k]->draw();
	for(int k=0;k<mcount;k++)
		mirrors[k]->draw();
	for(int k=0;k<wcount;k++)
		wormholes[k]->draw();
	char r[5];
	itoa(mleft,r);
	printw(70,15,r,24);
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
	char t[40];
	strcpy(t,"Light_bouncer() { Level_");
	char b[5];
	itoa(lnum,b);
	strcat(t,b);
	strcat(t," };");
	glutSetWindowTitle(t);
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
	glColor3f(0,0,0);
	printw(310,75,quote,24);
}
void windraw()
{
	drawimage("images/win.bmp",200,100,1);
	glColor3f(0.8,0.8,0.8);
	frectangle(200,50,690,100);
	glLineWidth(2);
	glColor3f(0,0,0);
	erectangle(450,50,585,100);
	erectangle(305,50,440,100);
	printw(350,73,"Retry",24);
	printw(460,73,"Main menu",24);
	glFlush();
}
void winmouse(int button,int state,int x,int y)
{
	y=600-y;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		if(x>=450 && x<=585 && y>=50 && y<=100)
		{
			selection=NULL;
			for(int k=0;k<mcount;k++)
				delete(mirrors[k]);
			for(int k=0;k<wcount;k++)
				delete(wormholes[k]);
			for(int k=0;k<bcount;k++)
				delete(blocks[k]);
			mcount=wcount=bcount=0;
			glutDisplayFunc(drawmenu);
			glutMouseFunc(mousehandlermenu);
			glutPostRedisplay();
			trailcount=0;
			manstate=0;
			trailcolor=0;
		}
		if(x>=305 && x<=440 && y>=50 && y<=400)
		{
			glutDisplayFunc(draw);
			glutMouseFunc(mousehandler);
			glutPostRedisplay();
		}
	}
}
void draw(void)
{
	if(!game || game==2)
	{		
		drawstage();
		if(!trailcolor)
			glColor3f(0,0,0);
		else
			glColor3f(0,1,0);
		glLineWidth(2);
		for(int k=0;k<trailcount;k++)
			if(trailtrue[k])
				line(trailx[k],traily[k],trailx[k+1],traily[k+1]);
		glLineWidth(1);
		if(game==2)
		{
			game=0;	
			glutMouseFunc(winmouse);
			glutDisplayFunc(windraw);
		}
	}
	else if(game==1)
	{
		px+=1*cos(pa/180*PI);
		py+=1*sin(pa/180*PI);
		glLineWidth(2);
		glColor3f(1,0,0);
		line(px1,py1,px,py);
		glLineWidth(1);
		px1=px;
		py1=py;
		if(px<5 || px>795 || py<105 || py>595)
		{
			manstate=1;
			trailcount++;
			trailtrue[trailcount]=1;
			trailx[trailcount]=px;
			traily[trailcount]=py;
			trailcolor=0;
			game=0;
		}
		if(distance(px,py,765,327)<=28 || px>=755 && px<=775 && py>=248 && py<=300)
		{
			trailcount++;
			trailtrue[trailcount]=1;
			trailx[trailcount]=px;
			traily[trailcount]=py;
			trailcolor=0;
			manstate=3;
			game=0;
		}
		if(distance(px,py,765,365)<=10)
		{
			trailcount++;
			trailtrue[trailcount]=1;
			trailx[trailcount]=px;
			traily[trailcount]=py;
			trailcolor=1;
			manstate=2;
			game=2;
		}
		for(int k=0;k<bcount;k++)
			if(blocks[k]->checkcoll())
			{
				manstate=1;
				trailcount++;
				trailtrue[trailcount]=1;
				trailx[trailcount]=px;
				traily[trailcount]=py;
				trailcolor=0;
				game=0;
				break;
			}
		for(int k=0;k<wcount;k++)
		{
			if(wormholes[k]->checkcoll1())
			{
				trailcount++;
				trailtrue[trailcount]=0;
				trailx[trailcount]=px;
				traily[trailcount]=py;
				px=wormholes[k]->x2+wormholes[k]->x1-px;
				py=wormholes[k]->y2+wormholes[k]->y1-py;
				trailcount++;
				trailtrue[trailcount]=1;
				trailx[trailcount]=px;
				traily[trailcount]=py;		
				px1=px;
				py1=py;
				px+=1*cos(pa/180*PI);
				py+=1*sin(pa/180*PI);
			}
			else if(wormholes[k]->checkcoll2())
			{
				trailcount++;
				trailtrue[trailcount]=0;
				trailx[trailcount]=px;
				traily[trailcount]=py;
				px=wormholes[k]->x1+wormholes[k]->x2-px;
				py=wormholes[k]->y1+wormholes[k]->y2-py;
				trailcount++;
				trailtrue[trailcount]=1;
				trailx[trailcount]=px;
				traily[trailcount]=py;
				px1=px;
				py1=py;
				px+=1*cos(pa/180*PI);
				py+=1*sin(pa/180*PI);
			}
		}
		for(int k=0;k<mcount;k++)
		{
			if(mirrors[k]->checkcoll() && game)
			{
				if(abs(pa-mirrors[k]->rot)<=90)
				{
					trailcount++;
					trailtrue[trailcount]=1;
					trailx[trailcount]=px;
					traily[trailcount]=py;
					game=0;
					trailcolor=0;
					manstate=1;
				}
				else
				{
					trailcount++;
					trailtrue[trailcount]=1;
					trailx[trailcount]=px;
					traily[trailcount]=py;
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
		((mirror*)selection)->x-=5;
	if(key==GLUT_KEY_RIGHT && selection!=NULL)
		((mirror*)selection)->x+=5;
	if(key==GLUT_KEY_UP && selection!=NULL)
		((mirror*)selection)->y+=5;
	if(key==GLUT_KEY_DOWN && selection!=NULL)
		((mirror*)selection)->y-=5;
}
void dragger(int x,int y)
{
	if(drag && selection!=NULL)
	{
		((mirror*)selection)->x=x;
		((mirror*)selection)->y=600-y;
	}
}
void keyhandler(unsigned char key,int x,int y)
{
	if(key=='z' && selection!=NULL)
		((mirror*)selection)->rot+=5;
	if(key=='x' && selection!=NULL)
		((mirror*)selection)->rot-=5;
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
			mleft++;
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
		trailx[0]=80;
		traily[0]=300;
		trailcount=0;
		trailtrue[0]=1;
	}
}
void mousehandler(int button,int state,int x,int y)
{
	y=600-y;
	if(button==3 && selection!=NULL)
		((mirror*)selection)->rot+=2.5;
	if(button==4 && selection!=NULL)
		((mirror*)selection)->rot-=2.5;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && x>=0 && y>=0 && x<=800 && y<=600)
	{
		manstate=0;trailx[0]=5;traily[0]=300;trailcount=0;
		if(x>=695 && x<=795 && y>=5 && y<=105)
		{
			selection=NULL;
			for(int k=0;k<mcount;k++)
				delete(mirrors[k]);
			for(int k=0;k<wcount;k++)
				delete(wormholes[k]);
			for(int k=0;k<bcount;k++)
				delete(blocks[k]);
			mcount=wcount=bcount=0;
			glutDisplayFunc(drawmenu);
			glutMouseFunc(mousehandlermenu);
			glutPostRedisplay();
			trailcount=0;
			manstate=0;
			trailcolor=0;
		}
		if(x>=105 && x<=205 && y>=5 && y<=105)
		{
			trailcount=0;
			trailx[0]=80;
			traily[0]=300;
			int t=mcount;
			for(int k=0;k<t;k++)
			{
				if(mirrors[k]->fix==0)
				{
					delete(mirrors[k]);
					mcount--;
					mleft++;
				}
			}
		}
		if(x>=5 && y>=5 && y<=105 && x<=105 && mleft!=0)
		{
			mirror *temp;
			temp=new mirror();
			mirrors[mcount]=temp;
			mcount++;
			temp->fix=0;
			selection=(int*)temp;
			drag=1;
			mleft--;
			return;
		}
		if(x>=205 && x<305 && y>=5 && y<=105)
		{
			manstate=0;
			selection=NULL;
			drawstage();
			pa=0;
			px=80;
			py=300;
			game=1;
			px1=px;py1=py;
			trailx[0]=80;
			traily[0]=300;
			trailcount=0;
			trailtrue[0]=1;
			return;
		}
		int flag=1;
		for(int k=0;k<mcount;k++)
		{
			if(!game && (int*)mirrors[k]==selection && x>=mirrors[k]->x+35 && x<=mirrors[k]->x+50 && y>=mirrors[k]->y+35 && y<=mirrors[k]->y+50)
			{
				delete(mirrors[k]);
				for(int j=k;j<mcount-1;j++)
					mirrors[j]=mirrors[j+1];
				mcount--;
				mleft++;
				break;
			}
		}
		for(int k=0;k<mcount;k++)
			if(!game && x>=mirrors[k]->x-40 &&x<=mirrors[k]->x+40 && y>=mirrors[k]->y-40 &&y<=mirrors[k]->y+40 && mirrors[k]->fix!=1)
			{ 
				flag=0;
				selection=(int*)mirrors[k];drag=1;break;
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
void mousehandlermenu(int button,int state,int x,int y)
{
	y=600-y;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
		if(instruction)
			drawmenu();
		else 
		{
			if(distance(736,542,x,y)<30)
			{
				instruction=1;
				glColor3f(1,1,1);
				frectangle(200,100,600,500);
				glColor3f(0,0,0);				
				glLineWidth(2);
				drawimage("images/instructions.bmp",0,0,2);
				glFlush();
			}
			for(int i=1;i<=totallevels;i++)
				if(x>=100+120*((i-1)%5) && x<=200+120*((i-1)%5) && y>=350-((i-1)/5)*120 && y<=450-((i-1)/5)*120)
				{
					char a[20];
					strcpy(a,"levels/l");
					char b[5];
					itoa(i,b);
					strcat(a,b);
					fstream f;
					f.open(a,ios::in);
					int fm;
					f>>fm;
					for(int j=0;j<fm;j++)
					{
						mirror *temp;
						temp=new mirror();
						f>>temp->x>>temp->y>>temp->rot;
						temp->fix=1;
						mirrors[mcount]=temp;
						mcount++;
					}
					int fb;
					f>>fb;
					for(int j=0;j<fb;j++)
					{
						block *temp;
						temp=new block();
						f>>temp->x>>temp->y;
						blocks[bcount]=temp;
						bcount++;
					}
					int fw;
					f>>fw;
					for(int j=0;j<fw;j++)
					{
						wormhole *temp;
						temp=new wormhole();
						f>>temp->x1>>temp->y1>>temp->x2>>temp->y2;
						wormholes[wcount]=temp;
						wcount++;
					}
					f>>mleft;
					f.close();
					game=0;
					lnum=i;
					glutDisplayFunc(draw);
					glutMouseFunc(mousehandler);
					glutPostRedisplay();
					fstream quotes;
					quotes.open("resources/quotes.txt",ios::in);
					int noq;
					string quotel;
					quotes>>noq;
					srand(time(0));
					int q=rand()%noq+1;
					for(int j=0;j<=q;j++)
						getline(quotes,quotel);
					int N=quotel.size();
					for (int a=0;a<=N;a++)
						quote[a]=quotel[a];
					return;
				}
		}
}
void drawmenu()
{
	if(!hasDrawn){
		glutPostRedisplay();
		hasDrawn = true;
	}
	instruction=0;
	glColor3f(01,01,01);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glutSetWindowTitle("Light_bouncer();");
	glColor3f(0.9,0.9,0.9);
	frectangle(5,5,795,595);
	glColor3f(0.8,0.8,0.8);
	for(int x=5;x<=795;x+=10)
		line(x,5,x,595);
	for(int y=5;y<=595;y+=10)
		line(5,y,795,y);
	drawimage("images/main.bmp",0,0,2);
	glColor3f(0,0,0);
	glLineWidth(2);
	erectangle(5,5,795,595);
	for(int i=1;i<=totallevels;i++)
	{
		char a[20];
		strcpy(a,"Level ");
		char b[5];
		itoa(i,b);
		strcat(a,b);
		printw(110+120*((i-1)%5),390-((i-1)/5)*120,a,24);
		erectangle(100+120*((i-1)%5),450-((i-1)/5)*120,200+120*((i-1)%5),350-((i-1)/5)*120);
	}
	glFlush();
}
int main(int argc, char ** argv)
{
	int j=1;
	fstream f;
	f.open("levels/l1",ios::in);
	while(f!=NULL)
	{
		j++;
		char a[20];
		strcpy(a,"levels/l");
		char b[3];
		itoa(j,b);
		strcat(a,b);
		f.close();
		f.open(a,ios::in);
	}
	f.close();
	totallevels=j-1;
	trailx[0]=80;
	traily[0]=300;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutCreateWindow("Light_bouncer();");
	glutDisplayFunc(drawmenu);
	glutMouseFunc(mousehandlermenu);
	glutKeyboardFunc(keyhandler);
	glutSpecialFunc(spkeyhandler);
	glutMotionFunc(dragger);
	init();
	glutMainLoop();
}
