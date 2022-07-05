#include<vector>
#include<iostream>
#include <stdlib.h> 
#include <time.h>   
using namespace std;
void cmp(vector<int> a,vector<int> b)
{
	for(int i=0;i<a.size();i++) if(a[i]!=b[i]) 
	{
		cout<<"not correct!\n\n";
		return ;
	}
	cout<<"correct!\n\n";
	return ;
}

void InsertionSort(vector<int> &nums1)
{
	
	
	{
		
		int i, key, j;
    	for (i = 1; i < nums1.size(); i++)
    	{
        	key = nums1[i];
        	j = i - 1;
 
 	       while (j >= 0 && nums1[j] > key)
    	    {
       	     nums1[j + 1] = nums1[j];
       	     j--;
       	 	}
       	 	nums1[j + 1] = key;
       	 	if(nums1.size()<=100)
       	 	{
       	 		cout<<i<<" : ";
       	 		for(int i=0;i<nums1.size();i++) cout<<nums1[i]<<",";
       	 		cout<<'\n';
				}
			
    	}
		///
}
}

int partition(vector<int> &nums2, int start, int end)
{
 
    int pivot = nums2[start];
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (nums2[i] <= pivot)
            count++;
    }
 
    int pivotIndex = start + count;
    swap(nums2[pivotIndex], nums2[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (nums2[i] <= pivot) {
            i++;
        }
 
        while (nums2[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(nums2[i++], nums2[j--]);
            
        }
    }

    return pivotIndex;
}
 
void QuickSort(vector<int> &nums2, int start, int end)
{
 
    
    if (start >= end)
        return;
 
    int p = partition(nums2, start, end);
    if(nums2.size()<=100)
    {
    	cout<<start<<"~"<<end<<" :\n";
 		for(int i=0;i<nums2.size();i++) cout<<nums2[i]<<",";
 		cout<<"\n";
    
	}
   
    QuickSort(nums2, start, p - 1);
 	
    QuickSort(nums2, p + 1, end);
 
}
 
int getMax(vector<int> &nums3, int n)
{
    int mx = nums3[0];
    for (int i = 1; i < n; i++)
        if (nums3[i] > mx)
            mx = nums3[i];
    return mx;
}
  
void countSort(vector<int> &nums3, int n, int exp)
{

    int output[n]; 
    int i, count[10] = { 0 };
  
    for (i = 0; i < n; i++)
        count[(nums3[i] / exp) % 10]++;
  
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
  
    for (i = n-1; i >= 0; i--) {
        output[count[(nums3[i] / exp) % 10] - 1] = nums3[i];
        count[(nums3[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        nums3[i] = output[i];
    
    if(n<=100){
	
	for(int t=0;t<=9;t++)
	{
		cout<<t<<" | ";
		for(int k=0;k<n;k++)
		{
			if((nums3[k]/exp)%10==t) cout<<"--> "<<nums3[k];
		}
		cout<<'\n';
	}
	cout<<"result chain : ";
	for(int i=0;i<nums3.size();i++) cout<<nums3[i]<<",";
	cout<<'\n';  
	}
}
  
// Radix Sort
void RadixSort(vector<int> &nums3, int n)
{
    int m = getMax(nums3, n);
  
    for (int exp = 1; m / exp > 0; exp *= 10)
    {
    	if(nums3.size()<=100)
    	{
    		if(exp==1) cout<<"First-pass:\n";
    		else if(exp==10) cout<<"Second-pass:\n";
    		else if(exp==100)cout<<"Third-pass:\n";
		}
    	
    	 countSort(nums3, n, exp);
	}
	cout<<"\n";
	
       
}
//
int main()
{
	cout<<"DS-OO Program3-Demo\n";
	srand(time(NULL));
	vector<int> nums1,nums2,nums3;
	double start,end;
	int num;
	cin>>num;
	if(num<=0)
	{
		int arr[13]={168, 179 ,208 ,306 ,93 ,859, 984, 55 ,9 ,271 ,33};
		for(int i=0;i<11;i++)
		{
			nums1.push_back(arr[i]);
			nums2.push_back(arr[i]);
			nums3.push_back(arr[i]);
		}
	}
	else 
	{
		
		for(int i=0;i<num;i++)
		{
			int x=rand()%999+1;
			nums1.push_back(x);
			nums2.push_back(x);
			nums3.push_back(x);
		}
	}
	
	if(nums1.size()<=100)
	{
		cout<<"Before : ";
	for(int i=0;i<nums1.size();i++) cout<<nums1[i]<<",";
	}
	
	cout<<"\n";
	cout<<"insertion sort:\n";
	start=clock();
	InsertionSort(nums1);
	end=clock();
	cout << "sorting time : " << (end - start) / CLOCKS_PER_SEC << " s\n\n\n";
	cout<<"quick sort:\n";
	if(nums2.size()<=100)
	{
		cout<<"Before : \n";
		for(int i=0;i<nums2.size();i++) cout<<nums2[i]<<",";
		cout<<"\n";
	}
	start=clock();
	QuickSort(nums2,0,nums2.size()-1);
	end=clock();
	cout << "sorting time : " << (end - start) / CLOCKS_PER_SEC << " s\n";
	cmp(nums1,nums2);
	cout<<"\n\nRadix sort:\n";
	start=clock();
	RadixSort(nums3,nums3.size());
	end=clock();
	cout << "sorting time : " << (end - start) / CLOCKS_PER_SEC << " s\n";	
	cmp(nums1,nums3);	
	return 0;
}
