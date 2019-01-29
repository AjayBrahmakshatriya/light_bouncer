class block
{
	public:
	float x,y;
	block()
	{
		x=0;y=0;
	}
	int checkcoll()
	{
		if(px>x-20 && px<x+20 && py>y-20 && py<y+20)
			return 1;
		return 0;
	}
	void draw()
	{
		glColor3f(0,0,0);
		frectangle(x-20,y-20,x+20,y+20);
	}
};
