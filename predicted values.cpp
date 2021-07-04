#include <stdlib.h> 
#include<iostream>
#include<algorithm>
#include<time.h> 
#include<cmath>
#include<vector>
using namespace std;
int get_mean(vector<int> v)
{
	int s=0;
	for(int i=0;i<v.size();i++)
	s+=v[i];
	return s/v.size();
}
int get_standard_deviation(vector<int> v,int m)
{
	 int s=0;
	for(int i=0;i<v.size();i++)
	{
		s+=(v[i]-m)*(v[i]-m);
	}
	s=s/v.size();
	
	s=sqrt(s);
	return s;

}
vector<int> get_predicted_values(vector<int> v)
{
	int mean=get_mean(v);
	int sd=get_standard_deviation(v,mean);
	int mod=7;
	int arr[7];
	for(int i=0;i<7;i++)
	arr[i]=i;
	srand(time(0));
	vector<int> a;
	while(mod>0)
	{
		int number=rand()%mod;
		number=arr[number];
		int to_push;
		if(number%2==0 && number!=0)
		{
		   	to_push=mean+(sd/number);
		}
		else if(number!=0)
		{
			to_push=mean-(sd/number);
		}
        else
        {
            to_push=sqrt(mean*sd);
        }
		a.push_back(to_push);
		swap(arr[number],arr[mod-1]);
		
		mod--;
	}
	return a;
	
}


