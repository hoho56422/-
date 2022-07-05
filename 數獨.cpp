#include <iostream>
#include <fstream>
using namespace std;

void readFile(char filename[],int Q[][9])
{
	int r,c;
	ifstream f1;
	f1.open(filename);
	for(r=0;r<9;r++)
	{
		for(c=0;c<9;c++)
		{
			f1 >> Q[r][c]; 
		}
	}
	f1.close();
}

void print(int Q[][9])
{
	int r,c;
	for(r=0;r<9;r++)
	{
		for(c=0;c<9;c++)
		{
			if(Q[r][c]==0)
			{
				cout << "  ";
			}
			else
			{
				cout << Q[r][c] << " ";
			}
		} 
		cout << endl;
	}
}
//update
void update(int A[][9][10],int r,int c,int a)
{
	int m,n;
	A[r][c][0] = a;
	for(m=1;m<=9;m++)
		A[r][c][m] = 0;
	for(m=0;m<9;m++)
		A[r][m][a] = 0;
	for(m=0;m<9;m++)	
		A[m][c][a] = 0;
	for(m=r/3*3;m<=r/3*3+2;m++)
	{
		for(n=c/3*3;n<=c/3*3+2;n++)
		{
			A[m][n][a] = 0;
		}
	}
	A[r][c][a] = 1;
}
//CLEAN1:某R、某C、某宮格剩一格能填K 

int  cleanone(int A[][9][10]){
	int flags=0;
	//r//
	for(int i=0;i<9;i++) {
		
		for(int m=1;m<=9;m++){
			int countone=0,s;
			for(int j=0;j<9;j++){
				countone+=A[i][j][m];
				if(A[i][j][m]==1) s=j;
			}
			if(countone==1) {
			update(A,i,s,m);
			flags=1;
	 }
			
		}
	}
	//c//
	for(int j=0;j<9;j++) {
		
		for(int m=1;m<=9;m++){
			int counttwo=0,s=0;
			for(int i=0;i<9;i++){
				counttwo+=A[i][j][m];
				if(A[i][j][m]==1) s=i;
			}
			if(counttwo==1)  {
				
			update(A,s,j,m);
			flags=1;
			
		}
	}
}
	//block//
	for(int i=0;i<=6;i+=3){
		for(int j=0;j<=6;j+=3){
			for(int p=1;p<=9;p++){
				int x,y,z,countthree=0;
				for(int m=i;m<=i+2;m++)
				{
					for(int n=j;n<=j+2;n++)
					{
						countthree+=A[m][n][p];
						if(A[m][n][p]==1) {
							x=m;
							y=n;
							z=p;
						}
					}
					
					}
					if(countthree==1) {
						
					update(A,x,y,z);
					
					flags=1;
					}
			}
		}
	}
	if(flags=1) return 1;
	return 0;
}

//CLEAN2:某R、某C、某宮格中有二格剩兩個數字能填，且這兩個數字一樣 
//sametwo :find那些格剩二個可能數// 
/*oid lasttwo(int test[9][9][1],int A[][9][10]){
	
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			int countaa=0;
			for(int m=1;m<=9;m++){
				countaa+=A[i][j][m];
				test[i][j][0]=0;
			}
			if(countaa==2) test[i][j][0]=1;
			
		}
	}
	
}
//store (i,j) 的唯二數字 
void compare(int same[9][9][2],int A[][9][10],int test[9][9][1]){
	
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			int count=0;
			if(test[i][j][0]==1){
				for(int m=1;m<=9;m++){
					same[i][j][0]=0;
					same[i][j][1]=0;
					if(A[i][j][m]==1){
						same[i][j][count]=m;
						count++;
					}
				}
			}
		}
	}
	
	
}*/
//cleantwo//
int cleantwo(int A[][9][10]){
	int same[9][9][2],test[9][9][1];
	int flag=0;
	//
		for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			int countaa=0;
			for(int m=1;m<=9;m++){
				countaa+=A[i][j][m];
				test[i][j][0]=0;
			}
			if(countaa==2) test[i][j][0]=1;
			
		}
	}
	///
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			int countbb=0;
			if(test[i][j][0]==1){
				for(int m=1;m<=9;m++){
					same[i][j][0]=0;
					same[i][j][1]=0;
					if(A[i][j][m]==1){
						same[i][j][countbb]=m;
						countbb++;
					}
				}
			}
		}
	}
	//r
	for(int i=0;i<9;i++){
		int countcc=0,x1,x2;
		for(int j=0;j<9;j++){
			if(same[i][j][0]!=0){
				countcc++;
				x1=j;
				x2+=j;
			
			if(countcc==2) {
				x2=x2-x1;
				if(same[i][x1][0]==same[i][x2][0]&&same[i][x1][1]==same[i][x2][1]) {
					int a=same[i][x1][0],b=same[i][x2][1];
					for(int k=0;k<9;k++){
						if(k==x1||k==x2) continue;
						else {
						A[i][k][a]=0;
						A[i][k][b]=0;
						flag=1;
					}
					}
				}
			}
			}
		}
	}

	//c
	for(int j=0;j<9;j++){
		int countdd=0,x1,x2;
		for(int i=0;i<9;i++){
			if(same[i][j][0]!=0){
				countdd++;
				x1=i;
				x2+=i;
			
			if(countdd==2) {
				x2=x2-x1;
				if(same[x1][j][0]==same[x2][j][0]&&same[x1][j][1]==same[x2][j][1]) {
					int a=same[x1][j][0],b=same[x2][j][1];
					for(int k=0;k<9;k++){
						if(k==x1||k==x2) continue;
						else {
						A[k][j][a]=0;
						A[k][j][b]=0;
						flag=1;
					}
					}
				}
			}
			}
		}
	}
	//block//
	for(int i=0;i<=6;i+=3){
		for(int j=0;j<=6;j+=3){
			int countee=0,x1,x2,y1,y2;
			for(int h=i;h<=i+2;h++){
				for(int g=j;g<=j+2;g++){
					if(same[h][g][0]!=0){
						countee++;
						x1=h;
						y1=g;
						x2+=h;
						y2+=g;
					}
					
				}
			}
			if(countee==2){
				if(same[x1][y1][0]==same[x2][y2][0]&&same[x1][y1][1]==same[x2][y2][1]){
				int a=same[x1][y1][0],b=same[x1][y1][1];
				for(int h=i;h<=i+2;h++){
				for(int g=j;g<=j+2;g++){
					if((h==x1&&g==y1)||(h==x2&&g==y2)) continue;
					else {
						A[h][g][a]=0;
						A[h][g][b]=0;
					}
					flag=1;
				}
				}
				}
			}
		}
	}
	
	
	
	return flag;	
 } 

//onlyyou//
int onlyyou(int A[][9][10],int r,int c)
{
	int count = 0, a, i;
	for(i=1;i<=9;i++)
	{
		if(A[r][c][i]>0)
		{
			count++;
			a = i;
		}
	}
	if(count==1)
		return a;
	else
		return 0;
}

//init
void init(int Q[][9],int A[][9][10])
{
	int r,c,i;
	for(r=0;r<9;r++)
	{
		for(c=0;c<9;c++)
		{
			A[r][c][0] = 0;
			for(i=1;i<=9;i++)
				A[r][c][i] = 1;
		}
	}
	for(r=0;r<9;r++)
	{
		for(c=0;c<9;c++)
		{
			if(Q[r][c]>0)
			{
				update(A,r,c,Q[r][c]);
			}
		}
	}
}
//main//
int main()
{
	int Q[9][9];
	int A[9][9][10];
	int test[9][9][1],same[9][9][2];
	int ANS[9][9];
	readFile("Q3.txt",Q);
	print(Q);
	init(Q,A);
	int r,c,a,flag = 0;
	do{
		flag = 0;//on off
		for(r=0;r<9;r++)
		{
			for(c=0;c<9;c++)
			{
			
				if(A[r][c][0]==0)
				{
					a = onlyyou(A,r,c);
					
					if(a>0)
					{
						update(A,r,c,a);
						flag = 1;
					} 
				}
			}
		}
		
		
	}while(flag==1);
	int n=100;
	while(n--){
		int flag=0;
		
		flag+=cleanone(A);
		if(flag==0) flag+=cleantwo(A);
		
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				
				int a = onlyyou(A,r,c);
					
					if(a>0)
					{
						update(A,r,c,a);
						flag = 1;
			}
		}}
	
	}
		
	
		
	cout<<"///////////////////////////"<<endl;
	for(r=0;r<9;r++)
	{
		for(c=0;c<9;c++)
		{
			ANS[r][c] = A[r][c][0];
		}
	}
	print(ANS);
	return 0;
}

