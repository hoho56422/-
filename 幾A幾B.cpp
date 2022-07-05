#include <bits/stdc++.h>
using namespace std;

void match(int G[], int A[], int AB[]);
  
int Separate(int num, int D[]);
void initT(int T[]);
int computerGuess(int T[]);
void updateT(int T[],int G[],int AB[]);
int sep(int num,int n[]);
int main()
{
	srand( time(NULL) );

  
    int tp,x=rand()/10000;
	int uA[4],uG[4],cA[4],cG[4],uAB[2],cAB[2],T[10000];
	int tmp,count=0,cou=0;
	//
	 cout<<"Please input your guess: ";
	    cin>>tmp;
	    while(sep(tmp,uA)==0){
	    cout<<"請輸入合法數值(4位不重複的數)"<<endl;	
		cout<<"Please input your guess: ";
		cin>>tmp;
		}//input防呆 
	do{
		x= rand()%10000;
		
	}while(sep(x,cA)==0);
	if(x<1000)  cout<<"computer's answer is "<<"0"<<x<<endl;
	cout<<"computer's answer is "<<x<<endl;
	
	initT(T);
	
	
	do{
		
		///com//
		count++;
		Separate(computerGuess(T),cG);
		match(cG,uA,cAB);
		cout << "computer's guess" <<count << ":" << cG[0] << cG[1] << cG[2] << cG[3];
		cout << "(" << cAB[0] << "A" << cAB[1] << "B)"<<endl;
		updateT(T,cG,cAB);
		////user/////
	    cou++;
	    cout<<"Please input your guess: ";
	    cin>>tp;
	    while(sep(tp,uG)==0){
	    cout<<"請輸入合法數值(4位不重複的數)"<<endl;	
		cout<<"Please input your guess: ";
		cin>>tp;
		}
	    match(uG,cA,uAB);
	    cout <<"your guess"<< count << ":" << uG[0] << uG[1] << uG[2] << uG[3];
		cout << "(" << uAB[0] << "A" << uAB[1] << "B)"<<endl;
	  
	}while(cAB[0]!=4&&uAB[0]!=4);
	if(uAB[0]==4&&cAB[0]!=4) cout<<"the winner is user"<<endl;
	if(cAB[0]==4&&uAB[0]!=4) cout<<"the winner is computer"<<endl;
	if(uAB[0]==4&&cAB[0]==4) cout<<"draw"<<endl;
	
	return 0;
}

void match(int G[], int A[], int AB[])
{
	int i,j;
	AB[0]=0;
	AB[1]=0;
	for(i=0;i<4;i++)
	{
		if(G[i]==A[i])
			AB[0]++;
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(i==j)
				continue;
			if(G[i]==A[j])
			{
				AB[1]++;
			}
		} 
	}
}

int Separate(int num, int D[])
{
	if(num>9999||num<0)
		return 0;
	D[0] = num / 1000;
	D[1] = num%1000/100;
	D[2] = num%100/10;
	D[3] = num%10;
	if(D[0]==D[1]||D[0]==D[2]||D[0]==D[3]||D[1]==D[2]||D[1]==D[3]||D[2]==D[3])
		return 0;
	else
		return 1;
}
int sep(int num,int D[]){
	if(num>9999||num<0)
		return 0;
	D[0] = num / 1000;
	D[1] = num%1000/100;
	D[2] = num%100/10;
	D[3] = num%10;
	if(D[0]==D[1]||D[0]==D[2]||D[0]==D[3]||D[1]==D[2]||D[1]==D[3]||D[2]==D[3])
		return 0;
	else
		return 1;
}
void initT(int T[])
{
	int i;
	int D[4];
	for(i=0;i<10000;i++)
	{
		if(Separate(i,D)==1)
			T[i]=1;
		else
			T[i]=0;
	}
}

int computerGuess(int T[])
{
	int i;
	for(i=0;i<10000;i++)
	{
		if(T[i]==1)
			return i;
	}
}
 
void updateT(int T[],int G[],int AB[])//確認表裡面還有那些數字符合x a y b 
{  
	int i,tA[4],tAB[2];
	for(i=0;i<10000;i++)
	{
		if(T[i]==1)
		{
			Separate(i,tA);
			match(G,tA,tAB);
			if(tAB[0]!=AB[0]||tAB[1]!=AB[1])
				T[i]=0;
		}
	}
}

