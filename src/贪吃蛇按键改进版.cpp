#include<iostream>
#include<time.h>
#include<conio.h>
#include<Windows.h>
using namespace std;
#include<fstream>
struct node
{
	int iii;
	int jjj;
	struct node *next;
	struct node *front;
}*first,*last,*ppp;
int main()
{
	char ch;//存方向
	int k;//随机数（起始位置）
	int i,j;//计数
	int ii,jj;//方位(尾)
	int i2,j2;//方位(头)
	char a[30][30];//地图
	for(i=0;i<30;i++)
		for(j=0;j<30;j++)
			a[i][j]=' ';
	for(j=0;j<30;j++)
		a[0][j]='+';
	for(j=0;j<30;j++)
		a[29][j]='+';
	for(i=1;i<29;i++)
		a[i][0]='+';
	for(i=1;i<29;i++)
		a[i][29]='+';//边框
	srand(unsigned(time(0)));
	i=rand()%27+1;
	j=rand()%27+1;
	a[i][j]='$';//起点头子i,j
	ii=i;i2=i;
	jj=j;j2=j;
	k=rand()%3;//第二个点
	switch(k)
	{
	case 0:jj++;if(a[ii][jj]!=' ')jj-=2;break;
	case 1:jj--;if(a[ii][jj]!=' ')jj+=2;break;
	case 2:ii++;if(a[ii][jj]!=' ')ii-=2;break;
	case 3:ii--;if(a[ii][jj]!=' ')ii+=2;break;
	}
	a[ii][jj]='*';//第二个点尾子ii,jj
	ppp=new node;//第二个点存在链表中(循环链表 f l 移动)
	ppp->iii=ii;
	ppp->jjj=jj;
	ppp->next=ppp;
	ppp->front=ppp;
	last=first=ppp;
	int q0=0;//没有初始球（建立）
	while(q0==0)
	{
		i=rand()%27+1;
		j=rand()%27+1;
		if(a[i][j]==' ')
		{
			a[i][j]='?';//球
			q0=1;
		}
	}
	char v;
	int t;
	cout<<"速度:\n1.慢;\n2.中;\n3.快;\n请选择:";
	cin>>v;
	while(v!='1'&&v!='2'&&v!='3')//有按键控制就用char
	{
		system("cls");
		cout<<"速度:\n1.慢;\n2.中;\n3.快;\n输入有误!请重新选择:";
		cin>>v;
	}
	if(v=='1')
		t=20;
	else
		if(v=='2')
			t=5;
		else
			t=1;
	system("cls");
	for(i=0;i<30;i++)//show初始图像
	{
		for(j=0;j<30;j++)
			cout<<a[i][j];
		cout<<endl;
	}
	cout<<"wsad移动！";
	while(((ch=getch())!='w'&&ch!='s'&&ch!='a'&&ch!='d')
		||(a[ii-1][jj]=='$'&&ch=='s')||(a[ii+1][jj]=='$'&&ch=='w')||(a[ii][jj-1]=='$'&&ch=='d')||(a[ii][jj+1]=='$'&&ch=='a'))//等待按键出发（防止向尾部运动）
		Sleep(100);
	int score=0;
	int end=0;
	char ch2;//暂存按键，屏蔽无关键
	char ch1;//修复新bug 用 记录变化前的方向
	int cd=0;//吃到球 增加长度
	while(1)//游戏进行 直到结束
	{
		ch1=ch;
		for(i=0;i<t;i++)
		{
			if(kbhit()&&(((ch2=getch())=='w'&&ch!='s')||(ch2=='s'&&ch!='w')||(ch2=='a'&&ch!='d')||(ch2=='d'&&ch!='a'))&&ch2!=ch)//屏蔽无关键
			{
				ch=ch2;//录入ch常规移动
			}
			Sleep(30);//防止这一秒的按键在下一次图像才显示 (sleep融入cin，按键响应的及时性)
		}//产生新bug  连续按出错
		//纠正 新bug
		if(     (ch1=='w'&&ch=='s')  ||  (ch1=='s'&&ch=='w')  ||  (ch1=='a'&&ch=='d')  ||  (ch1=='d'&&ch=='a')     )//复制的一定要全面修改
			ch=ch1;
		a[i2][j2]='*';//头变为身一
		if(cd==1)
		{
			ppp=new node;
			ppp->iii=i2;
			ppp->jjj=j2;
			ppp->front=last;
			ppp->next=first;
			first->front=ppp;
			last->next=ppp;
			first=ppp;
		}
		else
		{
			a[last->iii][last->jjj]=' ';
			last->iii=i2;//last放头
			last->jjj=j2;
			first=last;
			last=last->front;
		}
		if(ch=='a')
			j2--;
		if(ch=='d')
			j2++;
		if(ch=='w')
			i2--;
		if(ch=='s')
			i2++;
		cd=0;
		if(a[i2][j2]==' '||a[i2][j2]=='?')
		{
			if(a[i2][j2]=='?')
			{
				score++;
				cd=1;
			}
			a[i2][j2]='$';//头的移动
		}
		if(a[i2][j2]!='$')//(检验)头撞（墙或自己）（i2j2）
		{
			a[i2][j2]='$';//死了的头
			a[15][13]='E';
			a[15][14]='N';
			a[15][15]='D';
			a[15][16]='!';
			end=1;
		}
		if(cd==1)//如果吃掉再生成
		{
			q0=0;//没有初始球
			while(q0==0)
			{
				i=rand()%27+1;
				j=rand()%27+1;
				if(a[i][j]==' ')
				{
					a[i][j]='?';
					q0=1;
				}
			}
		}
		system("cls");//清屏
		for(i=0;i<30;i++)//show图像
		{
			for(j=0;j<30;j++)
				cout<<a[i][j];
			cout<<endl;
		}
		cout<<score<<endl;
		if(end==1)
			break;
	}
	system("pause");
	return 0;
}