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
	char ch;//�淽��
	int k;//���������ʼλ�ã�
	int i,j;//����
	int ii,jj;//��λ(β)
	int i2,j2;//��λ(ͷ)
	char a[30][30];//��ͼ
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
		a[i][29]='+';//�߿�
	srand(unsigned(time(0)));
	i=rand()%27+1;
	j=rand()%27+1;
	a[i][j]='$';//���ͷ��i,j
	ii=i;i2=i;
	jj=j;j2=j;
	k=rand()%3;//�ڶ�����
	switch(k)
	{
	case 0:jj++;if(a[ii][jj]!=' ')jj-=2;break;
	case 1:jj--;if(a[ii][jj]!=' ')jj+=2;break;
	case 2:ii++;if(a[ii][jj]!=' ')ii-=2;break;
	case 3:ii--;if(a[ii][jj]!=' ')ii+=2;break;
	}
	a[ii][jj]='*';//�ڶ�����β��ii,jj
	ppp=new node;//�ڶ��������������(ѭ������ f l �ƶ�)
	ppp->iii=ii;
	ppp->jjj=jj;
	ppp->next=ppp;
	ppp->front=ppp;
	last=first=ppp;
	int q0=0;//û�г�ʼ�򣨽�����
	while(q0==0)
	{
		i=rand()%27+1;
		j=rand()%27+1;
		if(a[i][j]==' ')
		{
			a[i][j]='?';//��
			q0=1;
		}
	}
	char v;
	int t;
	cout<<"�ٶ�:\n1.��;\n2.��;\n3.��;\n��ѡ��:";
	cin>>v;
	while(v!='1'&&v!='2'&&v!='3')//�а������ƾ���char
	{
		system("cls");
		cout<<"�ٶ�:\n1.��;\n2.��;\n3.��;\n��������!������ѡ��:";
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
	for(i=0;i<30;i++)//show��ʼͼ��
	{
		for(j=0;j<30;j++)
			cout<<a[i][j];
		cout<<endl;
	}
	cout<<"wsad�ƶ���";
	while(((ch=getch())!='w'&&ch!='s'&&ch!='a'&&ch!='d')
		||(a[ii-1][jj]=='$'&&ch=='s')||(a[ii+1][jj]=='$'&&ch=='w')||(a[ii][jj-1]=='$'&&ch=='d')||(a[ii][jj+1]=='$'&&ch=='a'))//�ȴ�������������ֹ��β���˶���
		Sleep(100);
	int score=0;
	int end=0;
	char ch2;//�ݴ水���������޹ؼ�
	char ch1;//�޸���bug �� ��¼�仯ǰ�ķ���
	int cd=0;//�Ե��� ���ӳ���
	while(1)//��Ϸ���� ֱ������
	{
		ch1=ch;
		for(i=0;i<t;i++)
		{
			if(kbhit()&&(((ch2=getch())=='w'&&ch!='s')||(ch2=='s'&&ch!='w')||(ch2=='a'&&ch!='d')||(ch2=='d'&&ch!='a'))&&ch2!=ch)//�����޹ؼ�
			{
				ch=ch2;//¼��ch�����ƶ�
			}
			Sleep(30);//��ֹ��һ��İ�������һ��ͼ�����ʾ (sleep����cin��������Ӧ�ļ�ʱ��)
		}//������bug  ����������
		//���� ��bug
		if(     (ch1=='w'&&ch=='s')  ||  (ch1=='s'&&ch=='w')  ||  (ch1=='a'&&ch=='d')  ||  (ch1=='d'&&ch=='a')     )//���Ƶ�һ��Ҫȫ���޸�
			ch=ch1;
		a[i2][j2]='*';//ͷ��Ϊ��һ
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
			last->iii=i2;//last��ͷ
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
			a[i2][j2]='$';//ͷ���ƶ�
		}
		if(a[i2][j2]!='$')//(����)ͷײ��ǽ���Լ�����i2j2��
		{
			a[i2][j2]='$';//���˵�ͷ
			a[15][13]='E';
			a[15][14]='N';
			a[15][15]='D';
			a[15][16]='!';
			end=1;
		}
		if(cd==1)//����Ե�������
		{
			q0=0;//û�г�ʼ��
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
		system("cls");//����
		for(i=0;i<30;i++)//showͼ��
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