#include<iostream>
#include<unordered_map>
#include<string>
#include<string.h>
#include<vector>
using namespace std;
void array_to_map(char s[10][100],int size,unordered_map<string,vector<int>> &m)
{
	string s1,s2;
	for(int i=0;i<size;i++)
	{
      char *t= strtok(s[i], "\t"); 
    int n=strlen(t);
    
    if(s1.length()!=0)
    s1.erase();

if(s2.length()!=0)
s2.erase();
    for(int i=0;i<n;i++)
    s1+=t[i];

    while (t!= NULL) 
    {  
        t = strtok(NULL, "\t"); 
      if(t!=NULL)
      {

        n=strlen(t);
      for(int i=0;i<n;i++)
    s2+=t[i];
    int val=stoi(s2);
    m[s1].push_back(val);
    s2.erase();
      }
       
    }
}


}
int map_to_array(unordered_map<string,vector<int>> m,char s[][100])
{
	int i=0;
	for(auto x:m)
	{
		strcpy(s[i],x.first.c_str());
		strcat(s[i],"\t");
		for(int j=0;j<x.second.size();j++)
		{
			string q=to_string(x.second[j]);
			strcat(s[i],q.c_str());
			strcat(s[i],"\t");
		}
		i++;
	}
	return m.size();
}

	


