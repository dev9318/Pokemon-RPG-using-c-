#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<ctype.h>
#include<process.h>
#include<graphics.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
#include<fstream.h>

void open();
void save();
int z=8;
int uuu=0;
char NAME[25];
int j1=0,a=100,b1=400;
int posarr[2]={0,0},x,y,cl;
union REGS in,out;
int posx ,posy;
//a class to store the moves of a pokemon
class move
  {
	public:
	char n[20];
	char type;
	int pp,maxpp;
	int a;
  };
//a class to store the pokemon
class pokemon
  {
	public:
	move mv[4];
	char n[20];
	float at,de;
	int speed,ac,lv;
	float hp,maxhp;
	long curexp;
	char type;
  };
//a class to store the player
class player
  {
	public:
	pokemon a[6];
	char NAME[25];
	int pkb, po, cash, curr;
  };
int j;
int cur,cap=1;
player p;
pokemon wild;
//a function to print blackspots
void blackspt(int a,int b,int c,int d)
  {
	setfillstyle(0,SOLID_FILL);
	bar(a,b,c,d);
  }
//a function to display pokeballs
void pk(int curr)
  {
	setfillstyle(SOLID_FILL,RED);
	fillellipse(20,365+curr*15,15,15);
	delay(50);
	setfillstyle(SOLID_FILL,WHITE);
	pieslice(20,365+curr*15,180,360,15);
	delay(50);
	setfillstyle(SOLID_FILL,BLACK);
	fillellipse(20,365+curr*15,5,5);
	delay(50);
	setfillstyle(SOLID_FILL,WHITE);
	pieslice(20,365+15*curr,0,360,3.75);
	fillellipse(20,365+15*curr,3.75,3.75);
	delay(50);
  }
// code for the mouse
int callmouse()
	  {
		 in.x.ax=1;
		 int86(51,&in,&out);
		 return 1;
	  }
void restrictmouseptr(int x1,int y1,int x2,int y2)
	  {
		 in.x.ax=7;
		 in.x.cx=x1;
		 in.x.dx=x2;
		 int86(51,&in,&out);
		 in.x.ax=8;
		 in.x.cx=y1;
		 in.x.dx=y2;
		 int86(51,&in,&out);
	  }
void mouseposi(int x[],int &xpos,int &ypos,int &click)
	   {
		  in.x.ax=3;
		  int86(51,&in,&out);
		  click=out.x.bx;
		  xpos=out.x.cx;
		  ypos=out.x.dx;
		  if(!click)j1=1;
		  if(click&&j1==1)
		  {
		  x[0]=xpos;
		  x[1]=ypos;
		  }
	   }
int mousehide()
	   {
		  in.x.ax=2;
		  int86(51,&in,&out);
		  return 1;
	   }
void setposi(int &xpos,int &ypos)
	  {
		 in.x.ax=4;
		 in.x.cx=xpos;
		 in.x.dx=ypos;
		 int86(51,&in,&out);
	  }
// loading screen
void intro()
	  {
		 setbkcolor(4);
		 for(int a=0;a<getmaxx();a++)
		  {
		       bar(a,getmaxy()/2,a+4,getmaxy());
		       delay(1);
		  }
		 setcolor(8);
		 settextstyle(0,HORIZ_DIR,5);
		 outtextxy(getmaxx()/2-getmaxx()/8-50,getmaxy()/2-getmaxy()/8,"POKEMON");
		 settextstyle(7,HORIZ_DIR,3);
		 outtextxy(getmaxx()/2-getmaxx()/8+26,getmaxy()/2,"LOADING...");
		 rectangle(getmaxx()/2-getmaxx()/8,getmaxy()/2+getmaxy()/8,getmaxx()/2-getmaxx()/8+175,getmaxy()/2+getmaxy()/8+35);
		 setfillstyle(1,4);
		 for(int fg=getmaxx()/2-getmaxx()/8+10;fg<getmaxx()/2-getmaxx()/8+164;fg++)
		     { bar(fg,getmaxy()/2+getmaxy()/8+5,fg+1,getmaxy()/2+getmaxy()/8+30);
		       delay(20);
		     }
	  }
//mainmenu of the program
int mainmenu()
	  {
		 NAME[0]='\0';
		 int k=0;
		 clrscr();
		 int g=DETECT,m;
		 initgraph(&g,&m,"C:\\TurboC3\\BGI");
		 cleardevice();
		 setcolor(WHITE);
		 rectangle(10,10,620,450);
		 rectangle(15,15,615,445);
		 restrictmouseptr(15,15,615,445);
		 setposi(a,b1);
		 callmouse();
		 do
		  {
			settextstyle(0,HORIZ_DIR,3);
			mouseposi(posarr,x,y,cl);
			gotoxy(1,2);
			setcolor(WHITE);
			rectangle(150,150,475,200);
			rectangle(155,155,470,195);
			setcolor(RED);
			outtextxy(225,171,"NEW GAME");
			setcolor(WHITE);
			rectangle(150,250,475,300);
			rectangle(155,255,470,295);
			setcolor(RED);
			outtextxy(215,272,"LOAD GAME");
			setcolor(WHITE);
			rectangle(150,355,475,400);
			rectangle(155,360,470,395);
			setcolor(RED);
			outtextxy(265,370,"QUIT");
			settextstyle(0,HORIZ_DIR,5);
			outtextxy(200,70,"POKEMON");
			settextstyle(0,HORIZ_DIR,3);
			if(posarr[0]>=150&&posarr[0]<=475&&posarr[1]>=350&&posarr[1]<=400)
			  exit(0);
			if(posarr[0]>=150&&posarr[0]<=475&&posarr[1]<=300&&posarr[1]>=250)
			{
			  mousehide();
			  cleardevice();
			  int ch='\0';
			  outtextxy(50,50,"Enter Your Name ");
			  rectangle(130,170,455,220);
			  rectangle(135,175,450,215);
			  for(int ii=0;ii>=0;)
			     {
				 ch=getch();
				 if(ch=='\b')
				  {
				    cleardevice();
				    outtextxy(50,50,"Enter Your Name ");
				    rectangle(130,170,455,220);
				    rectangle(135,175,450,215);
				    NAME[ii-1]='\0';
				    outtextxy(140,190,NAME);
				    if(ii)
				       --ii;
				  }
				 else if(ch==13)
				     break;
				 else
				  {
				    NAME[ii++]=ch;
				    NAME[ii]='\0';
				    outtextxy(140,190,NAME);
				  }
			     }
			     open();
			     closegraph();
			     return 1;
			}
			if(posarr[0]>=150&&posarr[0]<=475&&posarr[1]>=150&&posarr[1]<=200)
			{
			  mousehide();
			  cleardevice();
			  int ch='\0';
			  outtextxy(50,50,"Enter Your Name ");
			  rectangle(130,170,455,220);
			  rectangle(135,175,450,215);
			  for(int ii=0;ii>=0;)
			     {
				 ch=getch();
				 if(ch=='\b')
				  {
				    cleardevice();
				    outtextxy(50,50,"Enter Your Name ");
				    rectangle(130,170,455,220);
				    rectangle(135,175,450,215);
				    NAME[ii-1]='\0';
				    outtextxy(140,190,NAME);
				    if(ii)
				       --ii;
				  }
				 else if(ch==13)
				     break;
				 else
				  {
				    NAME[ii++]=ch;
				    NAME[ii]='\0';
				    outtextxy(140,190,NAME);
				  }
			     }
			  cleardevice();
			  pokemon aaaa[3];
			  fstream fin("starters.dat",ios::in);
			  fin.read((char*)&aaaa[0],sizeof(pokemon));
			  fin.read((char*)&aaaa[1],sizeof(pokemon));
			  fin.read((char*)&aaaa[2],sizeof(pokemon));
			  char c1;
			  int curr;
			  pk(0);
			  settextstyle(0,HORIZ_DIR,1);
			  while(1)
			    {
			     while(!kbhit())
			      {
				 outtextxy(50,365,aaaa[0].n);
				 outtextxy(50,380,aaaa[1].n);
				 outtextxy(50,395,aaaa[2].n);
			      }
			     c1=getch();
			     if(c1=='s'&&curr!=2)
			      {
			       blackspt(0,365+(curr-1)*15,47,370+(curr+1)*15);
			       curr++;
			      }
			     if(c1=='w'&&curr!=0)
			      {
			       curr--;
			       blackspt(0,365+(curr)*15,47,370+(curr+2)*15);
			      }
			     if(c1=='x')
			       break;
			     pk(curr);
			   }
			  p.a[0]=aaaa[curr];
			  p.po=10;
			  p.pkb=10;
			  p.cash=1000;
			  p.curr=0;
			  strcpy(p.NAME,NAME);
			  save();
			  return 1;
			}


		 }while(k==0);
	  }
//to load the introduction
void Intro()
 {
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "");
   errorcode = graphresult();
   if (errorcode != grOk)
      {
	  printf("Graphics error: %s\n", grapherrormsg(errorcode));
	  printf("Press any key to halt:");
	  getch();
	  exit(1); /* terminate with an error
				  code */
   }
	cleardevice();
	setbkcolor(BLACK);
	for(int i=0;i<190;i+=10)
       {

	setfillstyle(SOLID_FILL,RED);
	fillellipse(getmaxx()/2,getmaxy()/2,60+i,60+i);
	setfillstyle(SOLID_FILL,WHITE);
	pieslice(getmaxx()/2,getmaxy()/2,180,360,60+i);
	setfillstyle(SOLID_FILL,BLACK);
	fillellipse(getmaxx()/2,getmaxy()/2,20+i/11,20+i/11);
	setfillstyle(SOLID_FILL,WHITE);
	pieslice(getmaxx()/2,getmaxy()/2,0,360,15+i/11);
	setcolor(BLACK);
	line(getmaxx()/2-80-i,getmaxy()/2,getmaxx()/2-20-i,getmaxy()/2);
	line(getmaxx()/2+20+i,getmaxy()/2,getmaxx()/2+80+i,getmaxy()/2);
	fillellipse(getmaxx()/2,getmaxy()/2,15+i/11,15+i/11);
	delay(69);
	}
	setbkcolor(BLACK);
	delay(100);
	intro();
	mainmenu();
	closegraph();
	}
//to extract the wild pokemon
void wildi(pokemon &b)
	{
	   fstream f;
	   f.open("WW2.dat",ios::in|ios::binary);
	   randomize();
	   int a=random(5);
	   for(int i=0;i<a;i++)
		f.read((char *)&b,sizeof(pokemon));
	   b.maxhp=b.hp;
	}
//the inventory of pokemon user has
void inven(pokemon a[6],pokemon &c,int &usg)
  {
	 cleardevice();
	 char cho;
	 char tx[3];
	 char txt[3];
	 tx[2]='\0';
	 tx[1]='.';
	 txt[2]='\0';
	 cleardevice();
	 for(int j=0;j<6;j++)
	  {
	   tx[0]=(char)(49+j);
	   txt[0]=(char)(48+a[j].lv/10);
	   txt[1]=(char)(48+a[j].lv%10);
	   rectangle(10,70*j+20,202,70*j+80);
	   outtextxy(12,70*j+20,tx);
	   outtextxy(14,70*j+34,a[j].n);
	   outtextxy(14,70*j+44,"lv:");
	   outtextxy(38,70*j+44,txt);
	   outtextxy(14,70*j+54,"Hp bar:");
	   rectangle(14,70*j+64,68,70*j+76);
	   for(int i=66;i>=16;i--)
	    {
	     if((i-16)<=int(50*(a[j].hp/a[j].maxhp)))
		   {
			 setfillstyle(SOLID_FILL,2);
			 bar(16,70*j+66,i,70*j+74);
			 break;
		   }
		  else
		   {
			setfillstyle(SOLID_FILL,5);
			bar(i,70*j+66,66,70*j+74);
		   }

	    }
	 }
	 outtextxy(14,436,"Who do you want to choose?");
	 cho=getch();
	 if(a[int((int)cho-49)].hp<=0)
	  {
	     cleardevice();
	     outtextxy(10,20,"Invalid choice");
	     getch();
	     inven(a,c,usg);
	  }
	else
	  {
	     c=a[int((int)cho-49)];
	     usg=int((int)cho-49);
	  }
   cleardevice();
  }
//to decide the outcome of an attack
void att(pokemon &a,pokemon &b,char &c)
  {
	 setfillstyle(SOLID_FILL,0);
	 bar(10,350,getmaxx(),getmaxy());
	 randomize();
	 if(random(100-a.ac)<=random(100))
	{
	  if(a.speed>b.speed)
	   {
		 outtextxy(10,360,a.n);
		 outtextxy(110,360,"used");
		 outtextxy(170,360,a.mv[int((int)c-49)].n);
		 b.hp-= a.at/b.de*a.mv[int((int)c-49)].a;
		 if(b.hp<=0)
		   {
		 outtextxy(10,390,"The opponent has fainted.");
		   }
		 else
		   {
		 int chh=random(2);
		 outtextxy(10,370,"The opponent");
		 outtextxy(110,370,"used");
		 outtextxy(170,370,b.mv[chh].n);
		 a.hp-= b.at/a.de*b.mv[chh].a;
		 if(a.hp<=0)
		  {
		   outtextxy(10,390,a.n);
		   outtextxy(125,390,"has fainted.");
		  }
		   }
	   }
	  else
	   {
		 int chh=random(2);
		 outtextxy(10,370,"The opponent");
		 outtextxy(110,370,"used");
		 outtextxy(170,370,b.mv[chh].n);
		 a.hp-= b.at/a.de*b.mv[chh].a;
		 if(a.hp<=0)
		   {
		 outtextxy(10,390,a.n);
		 outtextxy(125,390,"has fainted.");
		   }
		 else
		   {
		 outtextxy(10,360,a.n);
		 outtextxy(110,360,"used");
		 outtextxy(170,360,a.mv[int((int)c-49)].n);
		 b.hp-= a.at/b.de*a.mv[int((int)c-49)].a;
		 if(b.hp<=0)
		  {
		   outtextxy(10,390,"The opponent has fainted.");
		  }
	   }
	}
	}
  else
	{
	  outtextxy(10,390,a.n);
	  outtextxy(125,390,"has missed.");
	  int chh=random(2);
		 outtextxy(10,370,"The opponent");
		 outtextxy(110,370,"used");
		 outtextxy(170,370,b.mv[chh].n);
	  a.hp-= b.at/a.de*b.mv[chh].a;
	  if(a.hp<=0)
		{
		 outtextxy(10,400,a.n);
		 outtextxy(125,400,"has fainted.");
		}
	}
	   for(int i=80;i>=20;i--)
	   { if((i-20)<=int(60*(b.hp/b.maxhp)))
		   {     setfillstyle(SOLID_FILL,2);
			 bar(20,10,i,25);
			 break;
		   }
		  else
		   {
			setfillstyle(SOLID_FILL,5);
			bar(i,10,80,25);
			delay(50);
		   }

	   }
	rectangle(448,288,512,307);
	for(i=510;i>=450;i--)
	   {     if((i-450)<=int(60*(a.hp/a.maxhp)))
		   { setfillstyle(SOLID_FILL,2);
			 bar(450,290,i,305);
			 break;
		   }
		  else
		   {
			 setfillstyle(SOLID_FILL,5);
			 bar(i,290,510,305);
			 delay(50);
		   }

	   }
	setfillstyle(SOLID_FILL,0);
	bar(10,350,getmaxx(),getmaxy());
  }
//to display the health bar and the options
int dsp(pokemon &a, pokemon &b)
	{
	 char c;
	 int curhpa=50;
	 rectangle(18,8,82,27);
	 outtextxy(25,0,"LV:");
	 for(int i=80;i>=20;i--)
	   { if((i-20)<=int(60*(b.hp/b.maxhp)))
		   {     setfillstyle(SOLID_FILL,2);
			 bar(20,10,i,25);
			 break;
		   }
		  else
		   {
			setfillstyle(SOLID_FILL,5);
			bar(i,10,80,25);
			delay(50);
		   }

	   }
	char txt[3];
	txt[0]=(char)(48+a.lv/10);
	txt[1]=(char)(48+a.lv%10);
	txt[2]='\0';
	outtextxy(490,315,txt);
	txt[0]=(char)(48+b.lv/10);
	txt[1]=(char)(48+b.lv%10);
	txt[2]='\0';
	outtextxy(450,315,"LV:");
	outtextxy(65,0,txt);
	outtextxy(20,30,b.n);
	rectangle(448,288,512,307);
	for(i=510;i>=450;i--)
	   {     if((i-450)<=int(60*(a.hp/a.maxhp)))
		   { setfillstyle(SOLID_FILL,2);
			 bar(450,290,i,305);
			 break;
		   }
		  else
		   {
			 setfillstyle(SOLID_FILL,5);
			 bar(i,290,510,305);
			 delay(50);
		   }
		}
	outtextxy(450,275,a.n);

	int curr=0;
	char c1;

	pk(0);
	while(1)
	{
	while(!kbhit())
	{
	  outtextxy(50,350,"WHAT DO YOU WANT TO DO?");
	  outtextxy(50,365,"Attack");
	  outtextxy(50,380,"Use items");
	  outtextxy(50,395,"Switch pokemon");
	  outtextxy(50,410,"Run");
	}
	c1=getch();
	if(c1=='s'&&curr!=3)
	 {	 blackspt(0,360+(curr-1)*15,47,370+(curr+1)*15);
		 curr++;
	 }
	if(c1=='w'&&curr!=0)
	 {	 curr--;
		 blackspt(0,360+(curr)*15,47,370+(curr+2)*15);
	 }
	if(c1=='x')
	  break;
	pk(curr);
	}
	c=char(curr+49);
	setfillstyle(SOLID_FILL,0);
	bar(0,350,getmaxx(),getmaxy());
	if(c=='1')
	   {  char co;
	      pk(0);
	      curr=0;
	while(1)
	{
	while(!kbhit())
	{
		  char pp1[8];
		  pp1[0]='(';
		  pp1[7]='\0';
		  pp1[6]=')';
		  pp1[3]='/';
		  pp1[1]=(char)(48+a.mv[0].pp/10);
		  pp1[2]=(char)(48+a.mv[0].pp%10);
		  pp1[4]=(char)(48+a.mv[0].maxpp/10);
		  pp1[5]=(char)(48+a.mv[0].maxpp%10);
		  outtextxy(50,365,a.mv[0].n);
		  outtextxy(125,365,pp1);
		  pp1[1]=(char)(48+a.mv[1].pp/10);
		  pp1[2]=(char)(48+a.mv[1].pp%10);
		  pp1[4]=(char)(48+a.mv[1].maxpp/10);
		  pp1[5]=(char)(48+a.mv[1].maxpp%10);
		  outtextxy(50,380,a.mv[1].n);
		  outtextxy(125,380,pp1);
		  pp1[1]=(char)(48+a.mv[2].pp/10);
		  pp1[2]=(char)(48+a.mv[2].pp%10);
		  pp1[4]=(char)(48+a.mv[2].maxpp/10);
		  pp1[5]=(char)(48+a.mv[2].maxpp%10);
		  outtextxy(50,395,a.mv[2].n);
		  outtextxy(125,395,pp1);
		  pp1[1]=(char)(48+a.mv[3].pp/10);
		  pp1[2]=(char)(48+a.mv[3].pp%10);
		  pp1[4]=(char)(48+a.mv[3].maxpp/10);
		  pp1[5]=(char)(48+a.mv[3].maxpp%10);
		  outtextxy(50,410,a.mv[3].n);
		  outtextxy(125,410,pp1);
	}
	c1=getch();
	if(c1=='s'&&curr!=3)
	 {	 blackspt(0,360+(curr-1)*15,47,370+(curr+1)*15);
		 curr++;
	 }
	if(c1=='w'&&curr!=0)
	 {	 curr--;
		 blackspt(0,360+(curr)*15,47,370+(curr+2)*15);
	 }
	if(c1=='x'&&a.mv[curr].pp)
	 {
	  --a.mv[curr].pp;
	  break;
	 }
	pk(curr);
	}
		  co=char(curr+49);
		  setfillstyle(SOLID_FILL,0);
		  bar(0,350,getmaxx(),getmaxy());
		  att(a,b,co);
		  if(b.hp<=0)
		   return 1;
		  if(a.hp<=0)
		   return 0;
		  return 2;
	   }
	else if(c=='3')
	  return 0;
	else if(c=='4')
	  return 3;
	else if(c=='2')
	  return 11;
	 return 10;
  }
//to make a pokemon gain experience
void gnexp(pokemon &a,pokemon &b)
	{
	   p.cash+=100;
	   outtextxy(150,100,"You earned 100 Units");
	   a.curexp=a.curexp+b.lv*1000;
	   if(a.curexp>=a.lv*1000&&a.lv!=100)
	    {
		a.curexp-=a.lv*1000;
		a.lv++;
		a.at+=2*(a.lv-5);
		a.de+=2*(a.lv-5);
		a.speed+=1*(a.lv-5);
		a.hp+=1*(a.lv-5);
		a.maxhp+=1*(a.lv-5);
		cleardevice();
		outtextxy(150,200,a.n);
		outtextxy(220,200,"just leveled up");
	    }
	   getch();
	}
//to display the items
void Items(pokemon &b,player &p,int &cap)
	{
	     cleardevice();
	     outtextxy(29,100,"What would you like to do");
	     char nop[3];
	     char nopk[3];
	     char c1;
	     int curr=0;
	     nop[0]=char((p.po/10)+48);
	     nop[1]=char((p.po%10)+48);
	     nop[2]='\0';
	     nopk[0]=char((p.pkb/10)+48);
	     nopk[1]=char((p.pkb%10)+48);
	     nopk[2]='\0';
	     pk(0);
	     while(1)
	      {
		while(!kbhit())
		{
		  outtextxy(50,365,"Pokeballs X");
		  outtextxy(50,380,"Potions X");
		  outtextxy(150,365,nopk);
		  outtextxy(150,380,nop);
		}
		c1=getch();
		if(c1=='s'&&curr!=1)
		{
		 blackspt(0,365+(curr-1)*15,47,370+(curr+1)*15);
		 curr++;
		 }
		if(c1=='w'&&curr!=0)
		 {
		 curr--;
		 blackspt(0,365+(curr)*15,47,370+(curr+2)*15);
		 }
		if(c1=='x')
		  break;
		pk(curr);
		}
		if(curr==0)
		   {
		       cleardevice();
		       if(p.pkb)
			 {
			   if(p.curr==5)
			     { outtextxy(50,75,"You can't catch more than 6 pokemons!");

			     }
			   else
			   {
			   p.pkb--;
			   randomize();
			   if(random(b.maxhp/b.hp+2)-random(4)>0)
				{
				    outtextxy(50,75,"You just captured");
				    outtextxy(250,75,b.n);
				    p.a[++p.curr]=b;
				    cap=0;
				}
			   else
				{
				    outtextxy(50,75,"Failed to capture  ");
				    outtextxy(240,75,b.n);
				}
			 }
			 }
		       getch();
		   }
		else
		   {
		       if(p.po)
			 {
			   p.po--;
			   int cho;
			   pokemon cure;
			   inven(p.a,cure,cho);
			   if(cure.maxhp-cure.hp>=50)
				cure.hp=cure.hp+50;
			   else
				cure.hp=cure.maxhp;
			   p.a[cho]=cure;
			 }
		       else
			 {
			    cleardevice();
			    outtextxy(50,100,"No potion");
			 }
		   }
	  cleardevice();
	}
//to combine all the battle functions into one
void battle(player &p, int &cur, int &cap)
	{
	      cap=1;
	      int gdriver = DETECT, gmode, errorcode;
	      initgraph(&gdriver, &gmode, "");
	      int usg=0;
	      int aaa=0;
	      wildi(wild);
	      pokemon curr=p.a[0];
	      cleardevice();
	      while(1)
		  {
			p.a[usg]=curr;
			if(wild.hp==0)
			 {
			   gnexp(curr,wild);
			   break;
			 }
			if(!cap)
			   break;
			j=dsp(curr,wild);
			if(j==2)
			   continue;
			else if(j==0)
			  {
			   p.a[usg]=curr;
			   for(int loop=0; loop<=p.curr; loop++)
			     {
			      if(p.a[loop].hp<=0)
			       {
				 aaa=1;
			       }
			      else
			       {
				 aaa=0;
				 break;
			       }
			      }
			   if(aaa)
			      break;
			   inven(p.a,curr,usg);
			  }
			else if(j==1)
			  {
			   gnexp(curr,wild);
			   p.a[usg]=curr;
			   break;
			  }
			else if(j==3)
			   break;
			else if(j==11)
			  {
			   Items(wild,p,cap);
			   curr=p.a[usg];
			  }
		  }

	}
//to display the shop
void shop()
     {
	  int gdriver = DETECT, gmode, errorcode;
	  initgraph(&gdriver, &gmode, "");
	  cleardevice();
	  outtextxy(29,100,"What would you like to buy");
	  char c1;
	  int curr=0;
	  char st[3];
	  pk(0);
	  while(1)
	      {
		while(!kbhit())
		 {
		  outtextxy(50,365,"Pokeballs 100 units");
		  outtextxy(50,380,"Potions 200 units");
		 }
		c1=getch();
		if(c1=='s'&&curr!=1)
		 {
		  blackspt(0,365+(curr-1)*15,47,370+(curr+1)*15);
		  curr++;
		 }
		if(c1=='w'&&curr!=0)
		 {
		 curr--;
		 blackspt(0,365+(curr)*15,47,370+(curr+2)*15);
		 }
		if(c1=='x')
		  break;
		pk(curr);
		}
	    if(curr==0)
	       {
		    cleardevice();
		    outtextxy(29,100,"How many would you like to buy(0-99)");
		    st[0]=getch();
		    st[1]='\0';
		    outtextxy(39,185,st);
		    st[1]=getch();
		    st[2]='\0';
		    outtextxy(39,185,st);
		    int num;
		    num=((int)st[0]-48)*10+((int)st[1]-48);
		    if(num*100>p.cash)
			 {
			     cleardevice();
			     outtextxy(220,100,"Not enough money");
			 }
		    else
			 {
			     p.pkb+=num;
			     p.cash-=num*100;
			 }
	       }
	 if(curr==1)
	       {
		    cleardevice();
		    outtextxy(29,100,"How many would you like to buy(0-99)");
		    st[0]=getch();
		    st[1]='\0';
		    outtextxy(39,185,st);
		    st[1]=getch();
		    st[2]='\0';
		    outtextxy(39,185,st);
		    int num;
		    num=((int)st[0]-48)*10+((int)st[1]-48);
		    if(num*200>p.cash)
			 {
			     cleardevice();
			     outtextxy(220,100,"Not enough money");
			 }
		    else
			 {
			     p.po+=num;
			     p.cash-=num*200;
			 }
	       }
	    closegraph();
     }
//to store one unit of the map
struct map
  {
   char cont;
   int color;
   int bcolor;
  };
//to store an npc
struct npc{
int x;
int y;
char t[30];
int ac;};
//to store the doors
struct door{
int x;
int y;
int currentmap;};
int currentmap=0;
//to store the map
class mapr{
public:
map test[40][40];
int xl;
int yl;
door ep;
door xp;
int c;
npc n[5];
};
mapr b[2],c,e;
//cout<<"         ______   ______ \n³\\    ³  ³    \\  ³      \n³ \\   ³  ³     ³ ³______\n³   \\ ³  ³     ³       ³\n³    \\³  ³___ /  ______³\n" ;
//to store the map
class mapf{
public:
map mapa[40][40] ;
int xl;
int yl;
door ep;
door xp;
npc n[5];
void print(int a,int b);
};
mapf map2;
//to print the map
void 	 mapf::print(int a ,int b ){
clrscr();

int i,j,x;
char c;
int l,m,n;
struct text_info ti;
gettextinfo(&ti);
for(i=0;i<11;i++){
for(j=0;j<74;j++){
textbackground(0);
cout<<" "; }
cout<<"\n";
}


for(i=(10+a);i<(17+a);i++){
for(x=0;x<30;x++){
textbackground(0);
cout<<" ";}
for(j=(11+b);j<(27+b);j++){
c=mapa[i][j].cont;
l=mapa[i][j].bcolor;

textcolor(mapa[i][j].color);
//if(c=''){
textbackground(l);
//}
//else

//textbackground(mapa[i][j].bcolor);
cprintf("%c",c);
}
textbackground(0);
cout<<"\n";
}
cout<<"\n";




}//end of function
int cxl,cyl;
//to copy the map
void copy(mapr a){
int i,j,k;
for(i=0;i<18;i++){
for(j=1;j<25;j++){
map2.mapa[i+10][j+10]=a.test[i][j];
}}
map2.xl=a.xl;
map2.yl=a.yl;
cxl=a.xl;
cyl=a.yl;
map2.ep.x=a.ep.x;
map2.ep.y=a.ep.y;
map2.xp.x=a.xp.x;
map2.xp.y=a.xp.y;
map2.ep.currentmap=a.ep.currentmap;
map2.xp.currentmap=a.xp.currentmap;
for(i=0;i<5;i++){
map2.n[i]=a.n[i];}

}
/*
void copy2(mapr a){
int i,j,k;
for(i=0;i<40;i++){
for(j=0;j<40;j++){
b[0].test[i][j]=a.test[i][j];
}}
b[0].xl=a.xl;
b[0].yl=a.yl;
}
*/
//to input the map from the binary file
void input(){
fstream f;
f.open("map.dat",ios::in|ios::out|ios::binary|ios::app);
f.write((char*)&map2,sizeof(map2));

f.close();
}
void read(int c){
fstream f;
f.open("map.dat",ios::in|ios::out|ios::binary|ios::app);
mapf a;
f.seekp(c*(sizeof(a)));
f.read((char*)&a,sizeof(a));
map2=a;
f.close();
}
void replace(){
fstream f,f1;
f.open("map.dat",ios::in|ios::out|ios::binary);
mapf a;
f.seekp(sizeof(a));

f.write((char*)&map2,sizeof(map2));
f.close();



}

map check,check1;

void save()
	{
	   int aa=0;
	   int aaaa=0;
	   strcpy(p.NAME,NAME);
	   fstream o("SV.dat",ios::binary|ios::out);
	   fstream f("SV.dat",ios::binary|ios::in);
	   while(!f.eof())
	   {
	     aaaa=f.tellg();
	     f.read((char*)&p,sizeof(player));
	     //f.read((char*)&check,sizeof(map));
	     //f.read((char*)&check1,sizeof(map));
	     //f>>posx;
	     //f>>posy;
	     if(!strcmpi(p.NAME,NAME))
	      {
		o.seekp(aaaa);
		o.write((char*)&p,sizeof(player));
		//f.write((char*)&check,sizeof(map));
		//f.write((char*)&check1,sizeof(map));
		//f<<posx<<'\n';
		//f<<posy;
		aa=1;
		break;
	      }
	   }
	  if(!aa)
	    {
	      o.write((char*)&p,sizeof(player));
	      //f.write((char*)&check,sizeof(map));
	      //f.write((char*)&check1,sizeof(map));
	      //f<<posx<<'\n';
	      //f<<posy;
	    }
	  f.close();
	  o.close();
	}
void open()
	{
	   fstream f("SV.dat",ios::binary|ios::in);
	   while(!f.eof())
	    {
		f.read((char*)&p,sizeof(player));
	       //f.read((char*)&check,sizeof(map));
	       //f.read((char*)&check1,sizeof(map));
	       //f>>posx;
	       //f>>posy;
	       if(!strcmpi(p.NAME,NAME))
		   break;
	    }
	   if(strcmpi(p.NAME,NAME))
	       {
		   cleardevice();
		   outtextxy(50,50,"INVALID USER");
		   getch();
		   Intro();
	       }
	   f.close();
	}

void main()
{
//to run the into
Intro();
//to extract the previous save to te user
XX:{
     clrscr();
     open();
   }
int scrollx=0,scrolly=0,j;
int i;

int count=0;
char l,k,poschar,poscolor;
map temp;


for(i=0;i<30;i++){
for(j=0;j<30;j++){
b[0].test[i][j].cont='Û';
b[0].test[i][j].color=2;
b[0].test[i][j].bcolor=2;
}}
for(i=0;i<=40;i++){
for(j=0;j<40;j++){
map2.mapa[i][j].cont='Û';
map2.mapa[i][j].color=2;
map2.mapa[i][j].bcolor=2;
}}

for(i=0;i<2;i++){
for(j=1;j<11;j++){
b[0].test[i][j].cont=5;
b[0].test[i][j].color=10;
b[0].test[i][j].bcolor=2;
}}
for(i=0;i<5;i++){
b[0].n[i].ac=0;}

b[0].xp.currentmap=1;
c.xp.currentmap=2;
for(i=0;i<5;i++){
for(j=11;j<13;j++){
b[0].test[i][j].cont=5;
b[0].test[i][j].color=10;
b[0].test[i][j].bcolor=2;
}}
b[0].n[0].x=14;
b[0].n[0].y=14;
strcpy(b[0].n[0].t,"hello traveller, enjoy!");
b[0].n[0].ac=1;



b[0].xl=35;
b[0].yl=28;
b[0].ep.x=12;
b[0].ep.y=12;
b[0].xp.x=34;
b[0].xp.y=14;
c.ep.x=12;
c.ep.y=12;
c.xp.x=34;
c.xp.y=14;
e.xl=35;
e.yl=28;
e.ep.x=12;
e.ep.y=12;
e.xp.x=34;
e.xp.y=14;
for(i=0;i<5;i++){
e.n[i].ac=0;}

for(i=0;i<20;i++){
for(j=0;j<25;j++){
e.test[i][j].cont='';
e.test[i][j].color=7;
e.test[i][j].bcolor=2;
}}
e.xp.currentmap=4;
e.ep.currentmap=2;
//b[1].ep.currentmap=0;

//f.ep.currentmap=1;

for(i=0;i<6;i++){
for(j=1;j<30;j++){
e.test[i][j].cont='°';
e.test[i][j].color=9;
e.test[i][j].bcolor=2;
}}

for(i=17;i<28;i++){
for(j=1;j<30;j++){
e.test[i][j].cont='°';
e.test[i][j].color=9;
e.test[i][j].bcolor=2;
}}

/*
for(i=0;i<20;i++){
for(j=0;j<25;j++){
f.test[i][j].cont='Û';
f.test[i][j].color=2;
f.test[i][j].bcolor=3;
}}

for(i=3;i<16;i++){
for(j=2;j<20;j++){
f.test[i][j].cont='Û';
f.test[i][j].color=7;
f.test[i][j].bcolor=7;
}}
for(i=5;i<7;i++){
for(j=4;j<12;j=j+5){
f.test[i][j].cont='³';
f.test[i][j].color=0;
f.test[i][j].bcolor=7;
}}
for(i=4;i<8;i=i+3){
for(j=5;j<9;j++){
f.test[i][j].cont='Í';
f.test[i][j].color=0;
f.test[i][j].bcolor=7;
}}
f.test[4][4].cont='Õ';
f.test[4][4].color=0;
f.test[4][4].bcolor=7;
f.test[7][4].cont='Ô';
f.test[7][4].color=0;
f.test[7][4].bcolor=7;
f.test[4][9].cont='¸';
f.test[4][9].color=0;
f.test[4][9].bcolor=7;
f.test[7][9].cont='Ù';
f.test[7][9].color=0;
f.test[7][9].bcolor=7;

f.test[5][5].cont='s';
f.test[5][6].cont='h';
f.test[5][7].cont='o';
f.test[5][8].cont='p';
for(j=5;j<9;j++){
f.test[5][j].color=0;
f.test[5][j].bcolor=7;  }



for(i=3;i<4;i++){
for(j=2;j<20;j++){
f.test[i][j].cont='Í';
f.test[i][j].color=0;
f.test[i][j].bcolor=7;
}}

for(i=16;i<17;i++){
for(j=2;j<20;j++){
f.test[i][j].cont='Í';
f.test[i][j].color=0;
f.test[i][j].bcolor=7;
}}

for(i=4;i<16;i++){
for(j=2;j<3;j++){
f.test[i][j].cont='³';
f.test[i][j].color=0;
f.test[i][j].bcolor=7;
}}

for(i=4;i<16;i++){
for(j=20;j<21;j++){
f.test[i][j].cont='³';
f.test[i][j].color=0;
f.test[i][j].bcolor=7;
}}
f.test[3][2].cont='Õ';
f.test[3][2].color=0;
f.test[3][2].bcolor=7;

f.test[16][20].cont='Ù';
f.test[16][20].color=0;
f.test[16][20].bcolor=7;

f.test[16][2].cont='Ô';
f.test[16][2].color=0;
f.test[16][2].bcolor=7;

f.test[3][20].cont='¸';
f.test[3][20].color=0;
f.test[3][20].bcolor=7;










for(i=8;i<9;i++){
for(j=5;j<19;j++){
f.test[i][j].cont='Í';
f.test[i][j].color=0;
f.test[i][j].bcolor=7;
}}

for(i=12;i<13;i++){
for(j=5;j<19;j++){
f.test[i][j].cont='Í';
f.test[i][j].color=0;
f.test[i][j].bcolor=7;
}}

for(i=8;i<12;i++){
for(j=4;j<5;j++){
f.test[i][j].cont='³';
f.test[i][j].color=0;
f.test[i][j].bcolor=7;
}}

for(i=8;i<12;i++){
for(j=19;j<20;j++){
f.test[i][j].cont='³';
f.test[i][j].color=0;
f.test[i][j].bcolor=7;
}}
f.test[8][4].cont='Õ';
f.test[8][4].color=0;
f.test[8][4].bcolor=7;

f.test[12][19].cont='Ù';
f.test[12][19].color=0;
f.test[12][19].bcolor=7;

f.test[12][4].cont='Ô';
f.test[12][4].color=0;
f.test[12][4].bcolor=7;

f.test[8][19].cont='¸';
f.test[8][19].color=0;
f.test[8][19].bcolor=7;


f.test[9][10].cont='p';
f.test[9][11].cont='o';
f.test[9][12].cont='k';
f.test[9][13].cont='e';
f.test[10][9].cont='c';
f.test[10][10].cont='e';
f.test[10][11].cont='n';
f.test[10][12].cont='t';
f.test[10][13].cont='r';
f.test[10][14].cont='e';
for(int z=10;z<14;z++)
{
f.test[9][z].color=0;
f.test[9][z].bcolor=7;
}
for( z=9;z<15;z++)
{
f.test[10][z].color=0;
f.test[10][z].bcolor=7;
}
f.xl=35;
f.yl=28;
f.ep.x=12;
f.ep.y=12;
f.xp.x=34;
f.xp.y=14;
f.xp.currentmap=3;
f.ep.currentmap=1;
for(i=0;i<5;i++){
f.n[i].ac=0;}
*/

for(i=2;i<3;i++){
for(j=1;j<10;j++){
b[0].test[i][j].cont='Û';
b[0].test[i][j].color=7;
b[0].test[i][j].bcolor=7;
}}
for(i=2;i<5;i++){
for(j=10;j<11;j++){
b[0].test[i][j].cont='Û';
b[0].test[i][j].color=7;
b[0].test[i][j].bcolor=7;
}}

c.xl=35;
c.yl=28;
//b.test[2][2].cont='';
//b.test[2][2].color=4;
//b.test[2][2].bcolor=2;


b[0].test[b[0].n[0].y-10][b[0].n[0].x-10].cont='!';
b[0].test[b[0].n[0].y-10][b[0].n[0].x-10].color=4;
b[0].test[b[0].n[0].y-10][b[0].n[0].x-10].bcolor=2;






for(i=0;i<40;i++){
for(j=0;j<40;j++){
c.test[i][j].cont='Û';
c.test[i][j].color=2;
c.test[i][j].bcolor=2;
}}
for(i=2;i<3;i++){
for(j=1;j<10;j++){
c.test[i][j].cont='Û';
c.test[i][j].color=7;
c.test[i][j].bcolor=7;
}}
for(i=2;i<5;i++){
for(j=10;j<11;j++){
c.test[i][j].cont='Û';
c.test[i][j].color=7;
c.test[i][j].bcolor=7;
}}
b[1]=c;
b[1].xp.currentmap=2;
b[1].ep.currentmap=0;
//copy(e);






check=map2.mapa[12][12];

map2.mapa[map2.ep.y][map2.ep.x].cont='';
map2.mapa[map2.ep.y][map2.ep.x].color=4;
map2.mapa[map2.ep.y][map2.ep.x].bcolor=2;
map2.mapa[map2.xp.y][map2.xp.x].cont='Û';
map2.mapa[map2.xp.y][map2.xp.x].color=0;
map2.mapa[map2.xp.y][map2.xp.x].bcolor=2;
/*map2.mapa[14][12].cont='|';
map2.mapa[14][12].color=4;
map2.mapa[14][12]. bcolor=2;
map2.mapa[13][13].cont='_';
map2.mapa[13][13].color=4;
map2.mapa[13][13].bcolor=2;
map2.mapa[13][11].cont='_';
map2.mapa[13][11].color=4;
map2.mapa[13][11].bcolor=2;

*/
//copy(b[map2.xp.currentmap]);



scrollx=0;
scrolly=0;

//input();
read(0);
check=map2.mapa[15][15];
mapmove:
count++;
l=getch();
//to move the player model
switch(l){
case 'd':

for(i=10;i<map2.yl;i++){
for(j=11;j<map2.xl-1;j++){
if(map2.mapa[i][j].cont==''){
if(j<11){
scrollx=j-16;}
else if(j>22){
scrollx=j-25;}

map2.mapa[i][j].bcolor=map2.mapa[i][j+1].bcolor;
check1=map2.mapa[i][j+1];
map2.mapa[i][j+1]=map2.mapa[i][j];
map2.mapa[i][j]=check;
check=check1;



posx=j+1;
posy=i;

map2.print(scrolly,scrollx);
cout<<posy<<" "<<posx;
//cout<<cyl/2<<" "<<cxl;
goto mapmove1;
}}}

break;
case 'a':
for(i=10;i<map2.yl;i++){
for(j=12;j<map2.xl;j++){
if(map2.mapa[i][j].cont==''){


if(j<11){
scrollx=j-11;}
else if(j>22){
scrollx=j-23;}


map2.mapa[i][j].bcolor=map2.mapa[i][j-1].bcolor;
check1=map2.mapa[i][j-1];
map2.mapa[i][j-1]=map2.mapa[i][j];
map2.mapa[i][j]=check;
check=check1;

map2.print(scrolly,scrollx);
posx=j-1;
posy=i;
cout<<posy<<" "<<posx;
goto mapmove1;
}}}
break;
case 's':
for(i=10;i<map2.yl-1;i++){
for(j=11;j<map2.xl;j++){
if(map2.mapa[i][j].cont==''){

if(i<10){
scrolly=i-10;}
else if(i>14){
scrolly=i-14;}

map2.mapa[i][j].bcolor=map2.mapa[i+1][j].bcolor;
check1=map2.mapa[i+1][j];
map2.mapa[i+1][j]=map2.mapa[i][j];
map2.mapa[i][j]=check;
check=check1;



map2.print(scrolly,scrollx);
posx=j;
posy=i+1;
cout<<posy<<" "<<posx;
goto mapmove1;
}}}
break;

case 'w':
for(i=11;i<map2.yl;i++){
for(j=11;j<map2.xl;j++){
if(map2.mapa[i][j].cont==''){

if(i<10){
scrolly=i-10;}
else if(i>14){
scrolly=i-15;}
map2.mapa[i][j].bcolor=map2.mapa[i-1][j].bcolor;
check1=map2.mapa[i-1][j];
map2.mapa[i-1][j]=map2.mapa[i][j];
map2.mapa[i][j]=check;
check=check1;



map2.print(scrolly,scrollx);
posx=j;
posy=i-1;
//cout<<posy<<" "<<posx;
goto mapmove1;
}}}
break;
//to save
   case 'p':
	     save();
	     cout<<" Saved!";
	     goto mapmove1;
	     break;
//to exit
case 'q':exit(1);
break;

}
mapmove1:
for(int h=0;h<5;h++){
if(posx==map2.n[h].x&&posy==map2.n[h].y&&map2.n[h].ac==1){
puts(map2.n[h].t);
}
}
//b[1]=c;
//to go into battle
if(check.cont=='h')
    {
	shop();
    }
/*
if(check.cont=='t')
    {
	cout<<" Welcome to the pokecenter"<<"\nyour pokemon are getting healed.....";
	for(int ck=0;ck<=p.curr;ck++)
	   {
	       p.a[ck].hp=p.a[ck].maxhp;
	       for(int ck1=0; ck1<4; ck1++)
		    p.a[ck].mv[ck1].pp=p.a[ck].mv[ck1].maxpp;
	   }
	cout<<"\nThanks for coming";
    }
*/
if (check.cont=='Û'){
int aaa=0;
randomize();
if(uuu==10)
  {
     battle(p, cur, cap);
     closegraph();
     clrscr();
     for(int ck=0;ck<=p.curr;ck++)
       {
	 if(p.a[ck].hp<=0)
	   {
	     aaa=1;
	   }
	 else
	   {
	     aaa=0;
	     break;
	   }
       }
     uuu=0;
     if(aaa)
      {
	cout<<" You are being taken to your previous save";
	getch();
	goto XX;
      }
     }
   else
     ++uuu;
   goto mapmove;
}

if(posx==map2.xp.x&&posy==map2.xp.y){

//copy2(c);

read(map2.xp.currentmap);
check=map2.mapa[map2.ep.y-1][map2.ep.x-1];
map2.mapa[map2.ep.y][map2.ep.x].cont='';
map2.mapa[map2.ep.y][map2.ep.x].color=4;
map2.mapa[map2.ep.y][map2.ep.x].bcolor=2;
map2.mapa[map2.xp.y][map2.xp.x].cont='Û';
map2.mapa[map2.xp.y][map2.xp.x].color=0;
map2.mapa[map2.xp.y][map2.xp.x].bcolor=2;

scrollx=0;
scrolly=0;
map2.print(scrolly,scrollx);


}
//to back to the map after the player has been moved
goto mapmove;



if(posx<11){
scrollx=posx-11;}
else if(posx>22){
scrollx=posx-22;}
if(posy<10){
scrolly=posy-10;}
else if(posy>14){
scrolly=posy-14;}
map2.print(scrolly,scrollx);
//to back to the map after the player has been moved
goto mapmove;

getch();




}