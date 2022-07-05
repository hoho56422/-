#include<iostream>
#include<fstream> 
#include<bits/stdc++.h>
#include <windows.h>
#include <cstdio>
#include <cstdlib>

using namespace std;



int tradetime[9]={0,0,0,0,0,0,0,0,0};//每個策略的總交易次數 
struct TX{
	int year,month,day,exdate;
	int price[285][3];//紀錄小時、分鐘、價格 
	 
};
//////1//////
int strategy1(TX* ptx)//每個strategy只計算一天 
{
	
	int r = (ptx->price[284][2]-ptx->price[0][2])*200;
	//cout<<r<<endl;
	tradetime[1]++;
	return r;//r是當天獲利 
} 
//////2////
int strategy2(TX* ptx,double stoploss)
{
	int cost=ptx->price[0][2];//一天的第一個價格是成本 
	int slp = (int)(cost*(1-stoploss)+0.5);//強制四捨五入
	int final_price;
	int n;
	for(n=1;n<285;n++)
	{
		final_price = ptx->price[n][2];
		if(ptx->price[n][2]<=slp)
		{
			tradetime[2]++;
			//cout<<"停損"<<endl;
			break; 
		}
		
	} 

	return(final_price-cost)*200;
}
//////3///////
int strategy3(TX* ptx,double stoploss,double takeprofit)
{
	int cost=ptx->price[0][2];//一天的第一個價格是成本 
	int slp = (int)(cost*(1-stoploss)+0.5);//強制四捨五入
	int tpp = (int)(cost*(1+takeprofit)+0.5);
	int final_price;
	int n;
	for(n=1;n<285;n++)
	{
		final_price = ptx->price[n][2];
		
		if(ptx->price[n][2]<=slp)
		{
			tradetime[3]++;
		//	cout<<"停損"<<endl;
			break; 
		}
		if(ptx->price[n][2]>=tpp)
		{
			tradetime[3]++;
		//	cout<<"停利"<<endl;
			break; 
		}
	} 
	
	return(final_price-cost)*200;
}
/////////4////////
int strategy4(TX* ptx)
{
	double MA5[285]={0};
	double sum;
	int n,i,cost,position=0,r=0;
	for(n=4;n<285;n++)
	{
		sum=0;
		for(i=n-4;i<=n;i++)
			sum+=ptx->price[i][2];
		MA5[n]=sum/5;
	}
	for(n=6;n<285;n++)
	{
		if(ptx->price[n-1][2]<=MA5[n-1]&&ptx->price[n][2]>MA5[n]&&MA5[n-2]>MA5[n-1]&&MA5[n]>MA5[n-1])
		{
			if(position==0)
			{
				position =1;
				cost = ptx->price[n][2];
			}
			else if(position==-1)
			{
				position=0;
				r+=(cost-ptx->price[n][2])*200;
			}
			tradetime[4]++;
		}
		else if(ptx->price[n-1][2]>=MA5[n-1]&&ptx->price[n][2]<MA5[n]&&MA5[n-2]<MA5[n-1]&&MA5[n]<MA5[n-1])
		{
			if(position==1)
			{
				position=0;
				r+=(ptx->price[n][2]-cost)*200;
			}
			else if(position==0)
			{
				position =-1;
				cost = ptx->price[n][2];
			}
			tradetime[4]++;
		}
	}
	if(position==1)
	{
	
		r+=(ptx->price[284][2]-cost)*200;
		tradetime[4]++;
	}
	else if(position==-1)
	{
	
		r+=(cost-ptx->price[284][2])*200;
		tradetime[4]++;
	}
	return r;
}


///5555555555555555555555555555555555555
int k=0;//代表第k天 
int dailymax[245],dailymin[245];
void dailyprice(TX* data, int day_number)	//功能:找出一天中的價格最大最小值 
{
	TX *ptx;
	int day_count;
	ptx = data;
	//find each day 's max min
	for(day_count=0;day_count<day_number;day_count++)
	{
			
	
	int m=0;
	while(ptx->price[m][0]!=13 || ptx->price[m][1]!=29)//不是一天的最後一分鐘->執行 
	{
				
		if(ptx->price[m][2] > dailymax[k]) 	dailymax[k]=ptx->price[m][2];//找出最大值並存入dailymax[]中 
		
		if(dailymin[k] > ptx->price[m][2])    dailymin[k] = ptx->price[m][2];//找出最小值並存入dailymin[]中 
		
		m++;
	}
	
	
	
	k++;
	ptx++;
	}
	}


int day=0;
int times=0,totalrev=0;	

int avg5max[246],avg5min[246];
	
int strategy5(TX *ptx,int gap)	
{

	
	
	for(int i=0;i<285;i++)
	{
	
		avg5max[i+5]=(dailymax[i]+dailymax[i+1]+dailymax[i+2]+dailymax[i+3]+dailymax[i+4])/5;//找出前五天最大價錢的平均值 
		avg5min[i+5]=(dailymin[i]+dailymin[i+1]+dailymin[i+2]+dailymin[i+3]+dailymin[i+4])/5;//找出前五天最小價錢的平均值 
		//cout<<i<<": "<<dailymax[i+5]<<" "<<past3min[i+5]<<'\n';

	}
	int rev=0,cost=0,position=0;

	
	for(int n=5;n<285;n++)
	{
		if(ptx->price[n][2] - avg5max[day]>=0&& ptx->price[n][2] - avg5max[day]>=gap)//當{第n天某一時刻的價錢}減掉{前五天(n-5,n-4,n-3,n-2,n-1)最高價錢的平均}大於特定的數值，則賣出
		{
			if(position==1)
			{
				position=0;
				rev+=(ptx->price[n][2]-cost)*200;
				tradetime[5]++;
			}
			else if(position==0)
			{
				position =-1;
				cost = ptx->price[n][2];
			}
			
			tradetime[5]++;//交易次數加一 
		}
		if( avg5min[day]- ptx->price[n][2] >=gap)//當{前五天(n-5,n-4,n-3,n-2,n-1)最低價錢的平均}減掉{第n天某一時刻的價錢}大於特定數值
		{
			if(position==1)
			{
				position=0;
				rev+=(ptx->price[n][2]-cost)*200;
			}
			else if(position==0)
			{
				position =-1;
				cost = ptx->price[n][2];
			}
			
			tradetime[5]++;//交易次數加一 
			
		}
	}
	//一天的最後一分鐘: 
	if(position==1)
	{
	
		rev+=(ptx->price[284][2]-cost)*200;
		tradetime[5]++;
	}
	else if(position==-1)
	{
	
		rev+=(cost-ptx->price[284][2])*200;
		tradetime[5]++;
	}
	
	
	day++;

	return rev;	
}


/////////////666/////////////////////////

int strategy6(TX *ptx,double rate)
{

	double MA6[285]={0};

	double sum;
	int n,i,cost,position=0,r=0;
	for(n=9;n<285;n++)
	{
		sum=0;
		for(i=n-9;i<=n;i++)
			sum+=ptx->price[i][2];
		MA6[n]=sum/10;//MA6為連續十天的平均價錢 
	}
	for(n=9;n<285;n++)
	{
		if((MA6[n]>=ptx->price[n][2])&&(double)((MA6[n]-ptx->price[n][2])/MA6[n])>rate)
		//視 MA6[n]為成本(平均)，若當時價錢的離均差和成本成一定的比率關係，則進行交易 //
		{
			if(position==0)
			{
				position =1;
				cost = ptx->price[n][2];
			}
			else if(position==-1)
			{
				position=0;
				r+=(cost-ptx->price[n][2])*200;
				tradetime[6]++;
			}
			
		}
		else if((MA6[n]<=ptx->price[n][2])&& (double) ((ptx->price[n][2]-MA6[n])/MA6[n])>rate)
		{
			if(position==1)
			{
				position=0;
				r+=(ptx->price[n][2]-cost)*200;
				tradetime[6]++;
			}
			else if(position==0)
			{
				position =-1;
				cost = ptx->price[n][2];
			}
		}
	}
	if(n==284)//每天的最後一分鐘:
	{
		if(position==1)
		{
		
		r+=(ptx->price[284][2]-cost)*200;
		tradetime[6]++;
		}
		else if(position==-1)
		{
		
		r+=(cost-ptx->price[284][2])*200;
		tradetime[6]++;
		}
	}
	
	//cout<<r<<'\n';	
	return r;
	
	
}

////7////
int strategy7(TX *ptx,int gap)
{
	int position=0,cost=0,r=0;
	for(int i=1;i<285;i++)
	{
		if(ptx->price[i-1][2]-ptx->price[i][2]>=gap)//當第i-1分鐘的價格和第i分鐘(此時時間)的價格為差距大於gap 進行交易 
		{
			if(position==1)
			{
				position=0;
				r+=(ptx->price[i][2]-cost)*200;
				tradetime[7]++;
			}
			else if(position==0)
			{
				position =-1;
				cost = ptx->price[i][2];
			}
		}
		else if(ptx->price[i][2]-ptx->price[i-1][2]>=gap)
		{
			if(position==0)
			{
				position =1;
				cost = ptx->price[i][2];
			}
			else if(position==-1)
			{
				position=0;
				r+=(cost-ptx->price[i][2])*200;
				tradetime[7]++;
			}
		}
		if(i==284)//每日的最後一分鐘 
		{
			if(position==1)
			{
		
				r+=(ptx->price[284][2]-cost)*200;
				tradetime[7]++;
			}
			else if(position==-1)	
			{
					
			r+=(cost-ptx->price[284][2])*200;
			tradetime[7]++;
			}
		}
	}
	return r;
}

int day8=0;
int past3max[246],past3min[246];
int strategy8(TX *ptx)
{
	for(int i=0;i<=242;i++)
	{
	
	if(dailymax[i]>=dailymax[i+1] && dailymax[i]>=dailymax[i+2]) past3max[i+3]=dailymax[i];
		else if(dailymax[i+1]>=dailymax[i] && dailymax[i+1]>=dailymax[i+2]) past3max[i+3]=dailymax[i+1];
		else past3max[i+3]=dailymax[i+2];//past3max[i]:過去三天(i-3~i-1)中最大最小值 
		
	if(dailymin[i]<=dailymin[i+1] && dailymin[i]<=dailymin[i+2]) past3min[i+3]=dailymin[i];
		else if  (dailymin[i+1]<=dailymin[i] && dailymin[i+1]<=dailymin[i+2]) past3min[i+3]=dailymin[i+1];
		else past3min[i+3]=dailymin[i+2];
	}
	int r=0,flag=0,final=0,premax=0,prepremax=0;	
	if(day8<=2) day8++;//前三天為觀察期，不交易 
	else if(day8<245)
	{
		for(int i=0;i<285;i++)
		{
			if(ptx->price[i][2]>past3max[day])
			{
				final=ptx->price[i][2];//第n天某個時刻(i)的價錢(final)大於前三天的最高價錢則賣出 
				flag=-1;
				if(i>260) break;
				//flag++;
				for(int j=i+1;j<285<final;j++)//繼續找出一個小於final的價錢(premax)
				{
					if(ptx->price[j][2]<final)
					{
						premax=(ptx->price[j][2]);
						for(int k=j+1;k<285;k++)//找出一個小於premax的價錢(prepremax)並買入
						{
							if(ptx->price[k][2]<premax)
							{
								prepremax=ptx->price[k][2];
								
								tradetime[8]++;
								break;
							}
						}
						break;
					}
				}
				break;
			}
	}

	if(final-prepremax>10000) r=0;//因為prepremax為0，所以不交易 
	else r=final-prepremax;//當日最終獲利 
	//cout<<day8<<": "<<final<<"premax"<<premax<<" "<<prepremax<<"r  "<<r<<'\n';
	day8++;
	}	
		
return r*200;
}
/////trade/////
int  maxp[10],minp[10];
int trading(TX* data, int day_number, int strategy_no)
{

	TX *ptx;
	int day_count;
	int R = 0;//R=獲利
	ptx = data;//從第0天開始
	for(int i=0;i<10;i++) {
		maxp[i]=0;
		minp[i]=100000;
	}
	for(day_count=0;day_count<day_number;day_count++)
	{
			
		switch(strategy_no)
		{
			case 1:
				if(maxp[1]<strategy1(ptx)) maxp[1]=strategy1(ptx);//maxp功能:找出單日交易最大值 
				if(minp[1]>strategy1(ptx)) minp[1]=strategy1(ptx);//minp功能:找出單日交易最小值 
				R+=strategy1(ptx);
				break;
			case 2:
				if(maxp[2]<strategy2(ptx,0.01)) maxp[2]=strategy2(ptx,0.01);
				if(minp[2]>strategy2(ptx,0.01)) minp[2]=strategy2(ptx,0.01);
				R+=strategy2(ptx,0.01);
				break;
			case 3:
				if(maxp[3]<strategy3(ptx,0.01,0.02)) maxp[3]=strategy3(ptx,0.01,0.02);
				if(minp[3]>strategy3(ptx,0.01,0.02)) minp[3]=strategy3(ptx,0.01,0.02);
				R+=strategy3(ptx,0.01,0.02);
				break;
			case 4:
				if(maxp[4]<strategy4(ptx)) maxp[4]=strategy4(ptx);
				if(minp[4]>strategy4(ptx)) minp[4]=strategy4(ptx);
				R+=strategy4(ptx);
				break;
			case 5:
			
				if(maxp[5]<strategy5(ptx,10)) maxp[5]=strategy5(ptx,10);
				if(minp[5]>strategy5(ptx,10)) minp[5]=strategy5(ptx,10);
				R+=strategy5(ptx,10);
				break;
			case 6:
				if(maxp[6]<strategy6(ptx,0.0001)) maxp[6]=strategy6(ptx,0.0001);
				if(minp[6]>strategy6(ptx,0.0001)) minp[6]=strategy6(ptx,0.0001);
				R+=strategy6(ptx,0.0001);
				break;	
			case 7:
				if(maxp[7]<strategy7(ptx,10)) maxp[7]=strategy7(ptx,10);
				if(minp[7]>strategy7(ptx,10)) minp[7]=strategy7(ptx,10);
				R+=strategy7(ptx,10);
				break;	
			case 8:
				if(maxp[8]<strategy8(ptx)) maxp[8]=strategy8(ptx);
				if(minp[8]>strategy8(ptx)) minp[8]=strategy8(ptx);
				R+=strategy8(ptx);
				break;		
		}
		ptx++;
	} 
	return R;
	 
}


//MUSIC

const int C = 1109,  G = 1661, A = 1865;
/////////do///////// la///////si//////
const int T = 50;////時間間隔80頻 

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	
	
	
	HANDLE hConsole;//顏色控制台 
	int day_number,count=0,m,a=0;//m是當天第幾分鐘 
	 
	char c,str[101];
	int year,month,day,hour,minute,exdate,price;
	TX *data, *ptx;
	ifstream fin;
	fin.open("TXF_minute_2021_285.csv");
	fin.getline(str,100);//讀掉第一行 
	while(fin>>year)
	{
		a++;
		fin>>c;//讀斜線
		fin>>month>>c; 
		fin>>day>>c;
		fin>>hour>>c;
		fin>>minute>>c;
		fin>>exdate>>c;
		fin>>price;
		if(hour==13&&minute==29)
		{
			//cout<<year<<"/"<<month<<"/"<<day<<endl;
			count++;
		}
	}//直到讀不到int 
	fin.close();
	day_number=count;//有幾天 
	//cout<<day_number<<endl;
	data=new TX[day_number];//動態
	ptx = data;//ptx會指向當時要處理的那個TX，這裡先設在第0天 
	fin.open("TXF_minute_2021_285.csv");
	fin.getline(str,100);//讀掉第一行 
	m=0; 
	while(fin>>year)
	{
		fin>>c;//讀斜線
		fin>>month>>c; 
		fin>>day>>c;
		fin>>hour>>c;
		fin>>minute>>c;
		fin>>exdate>>c;
		fin>>price;
		if(m==0)//讀到第一分鐘的資料 
		{
			ptx->year=year;
			ptx->month=month;
			ptx->day=day;
			ptx->exdate=exdate;
		}
		ptx->price[m][0]=hour;
		ptx->price[m][1]=minute;
		ptx->price[m][2]=price;
		m++;
		if(hour==13&&minute==29)
		{
			m=0;
			ptx++;
		}
	}
	fin.close();
	

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//顏色控制 
	
	
	
	SetConsoleTextAttribute(hConsole,95);//改顏色 
   
    
	cout<<"策略一(buy and hold)-- "<< endl;
	cout<<"可獲利:"<<trading(data,day_number,1)<<endl; 
	cout<<"單日最大獲利: "<<maxp[1]<<endl;
	cout<<"單日最大虧損: "<<minp[1]<<endl;
	cout<<"交易次數"<<tradetime[1]<<endl;
	
	SetConsoleTextAttribute(hConsole,112 );//改顏色 
	
	cout<<"策略二(B&H+停損)-- "<<endl;
	cout<<"可獲利: "<<trading(data,day_number,2)<<endl; 
	cout<<"單日最大獲利: "<<maxp[2]<<endl;
	cout<<"單日最大虧損: "<<minp[2]<<endl;
	cout<<"交易次數"<<tradetime[2]<<endl;
	
	SetConsoleTextAttribute(hConsole,224 );//改顏色 
	
	cout<<"策略三(B&H+停損停利)--"<<endl;
	cout<<"可獲利: "<<trading(data,day_number,3)<<endl;
	cout<<"策略三單日最大獲利"<<maxp[3]<<endl;
	cout<<"策略三單日最大虧損"<<minp[3]<<endl;
	cout<<"交易次數"<<tradetime[3]<<endl;
	
	SetConsoleTextAttribute(hConsole,249 );	//改顏色 
	cout<<"策略四(簡化版葛蘭碧交易法則)--"<<endl;
	cout<<"可獲利: "<<trading(data,day_number,4)<<endl; 
	cout<<"單日最大獲利: "<<maxp[4]<<endl;
	cout<<"單日最大虧損: "<<minp[4]<<endl;
	cout<<"交易次數"<<tradetime[4]<<endl;
	
	SetConsoleTextAttribute(hConsole,46 );//改顏色 
	
	
	 dailyprice(data,day_number);
	cout<<"策略五(最大最小平均值)--"<<endl;	
	cout<<"可獲利: "<<trading(data,day_number,5)<<endl;
	cout<<"策略單日最大獲利"<<maxp[5]<<endl;
	cout<<"策略5單日最大虧損"<<minp[5]<<endl;
	cout<<"交易次數"<<tradetime[5]<<endl;

	SetConsoleTextAttribute(hConsole,188 );//改顏色 
	cout<<"策略六(離均差)--"<<endl;
	cout<<"可獲利: "<<trading(data,day_number,6)<<endl;
	cout<<"策略六單日最大獲利"<<maxp[6]<<endl;
	cout<<"策略六單日最大虧損"<<minp[6]<<endl;
	cout<<"交易次數"<<tradetime[6]<<endl;
	
	SetConsoleTextAttribute(hConsole,206);//改顏色 
	cout<<"策略七(GAP)--"<<endl;
	cout<<"可獲利: "<<trading(data,day_number,7)<<endl;
	cout<<"策略七單日最大獲利"<<maxp[7]<<endl;
	cout<<"策略七單日最大虧損"<<minp[7]<<endl;
	cout<<"交易次數"<<tradetime[7]<<endl;
	
	SetConsoleTextAttribute(hConsole,226);//改顏色 
	cout<<"策略八(最大值)--"<<endl;
	cout<<"可獲利: "<<trading(data,day_number,8)<<endl;
	cout<<"策略八單日最大獲利"<<maxp[8]<<endl;
	cout<<"策略八單日最大虧損"<<minp[8]<<endl;
	cout<<"交易次數"<<tradetime[8]<<endl;
	//MUSIC//LITTLE STAR
	
	Beep( C, T  );//響一聲do,再空200頻的時間 
    Beep( G, T  *4/3);
    Beep( A, T *4/3);
    Beep( G, T  *4/3);
    Beep( A, T  *4/3); 
	SetConsoleTextAttribute(hConsole,7 );
	return 0;
	
}

