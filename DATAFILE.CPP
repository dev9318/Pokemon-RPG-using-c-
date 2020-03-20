#include<string.h>
#include<fstream.h>
class move
  {
	public:
	char n[20];
	char type;
	int pp,maxpp;
	int a;
  };
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
class player
  {
	public:
	pokemon a[6];
	char NAME[25];
	int pkb, po, cash, curr;
  };
struct map{
char cont;
int color;
int bcolor;
};
map check,check1;
void main()
   {
	fstream f("WW2.dat",ios::binary|ios::out|ios::app|ios::in);
	player p;
	int posx=0,posy=0;
	strcpy(p.NAME,"DEV");
	p.pkb=p.po=10;
	p.cash=1000;
	p.curr=0;
	strcpy(p.a[0].mv[0].n,"Scratch");
	p.a[0].mv[0].pp=p.a[0].mv[0].maxpp=30;
	p.a[0].mv[0].type='n';
	p.a[0].mv[0].a=11;
	strcpy(p.a[0].mv[1].n,"Quick Attack");
	p.a[0].mv[1].pp=p.a[0].mv[1].maxpp=30;
	p.a[0].mv[1].type='n';
	p.a[0].mv[1].a=15;
	strcpy(p.a[0].mv[2].n,"Thunder Bolt");
	p.a[0].mv[2].pp=p.a[0].mv[2].maxpp=15;
	p.a[0].mv[2].type='e';
	p.a[0].mv[2].a=25;
	strcpy(p.a[0].mv[3].n,"Bolt Strike");
	p.a[0].mv[3].pp=p.a[0].mv[3].maxpp=5;
	p.a[0].mv[3].type='e';
	p.a[0].mv[3].a=40;
	strcpy(p.a[0].n,"Pikachu");
	p.a[0].hp=p.a[0].maxhp=19;
	p.a[0].curexp=0;
	p.a[0].speed=19;
	p.a[0].lv=5;
	p.a[0].ac=97;
	p.a[0].at=25;
	p.a[0].de=18;
	p.a[0].type='f';
	f.write((char*)&p.a[0],sizeof(pokemon));
       //	f.write((char*)&check,sizeof(map));
	//f.write((char*)&check1,sizeof(map));
	//f<<posx<<'\n';
	//f<<posy;
	f.close();
   }