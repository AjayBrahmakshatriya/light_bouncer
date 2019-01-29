class mirror
{
	public:
	float x,y;
	float rot;
	int fix;
	mirror()
	{
		x=0;
		y=0;
		rot=0;
		fix=0;
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
		{
			erectangle(x-50,y-50,x+50,y+50);
			erectangle(x+35,y+35,x+50,y+50);
			glColor3f(1,0,0);
			glLineWidth(2);
			line(x+38,y+38,x+47,y+47);
			line(x+38,y+47,x+47,y+38);
		}
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
