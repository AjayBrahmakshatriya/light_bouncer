class wormhole
{
	public:
	float x1,y1,x2,y2;
	wormhole()
	{
		x1=y1=x2=y2=0;
	}
	void draw()
	{
		glColor3f(0.5,0.5,0.5);
		drawfCircle(x1,y1,40);
		drawfCircle(x2,y2,40);
		glColor3f(0,0,0);
		glLineWidth(2);
		drawCircle(x1,y1,40);
		drawCircle(x2,y2,40);
		drawSpiral(x1,y1,40);
		drawSpiral(x2,y2,40);
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
;

