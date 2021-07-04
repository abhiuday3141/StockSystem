#include<iostream>
#include<time.h>
#include "Color file.cpp"
#include "Size file.cpp"
#include<unordered_map>
#include<string>
#include<string.h>
#include<vector>
using namespace std;
string v[]={"1.Buy a new stock","2.Sell an existing stock","3.Update an existing stock","4.Suggest stocks","5.Show list of stocks","6.Return"};

void shift_down()
{cout<<"\n\n\n";
}

void align_center()
{
		cout<<"\t";
}
void print_list(int idx)
{   
    align_center();
    cout<<Change_color_to("BLUE")<<"Choose from the options below\n\n";
	for(int i=0;i<6;i++)
	{
		align_center();
		if(i!=idx)
		{
			cout<<Change_color_to("BLUE")<<v[i]<<endl;
		}
		else
		{
			cout<<Change_color_to("YELLOW")<<v[i]<<endl;
			
		}
	}
	return;
}
void print_initial(string s)
{   
    if(s=="login")
    {
	shift_down();
	//align_center();
    align_center();
	cout<<Change_color_to("BLUE")<<"Welcome to your personal stock control\n";
	align_center();
	cout<<"\t and inventory system\n";
	align_center();
	cout<<Change_color_to("YELLOW")<<"Login"<<"\t\t\t\t"<<Change_color_to("BLUE")<<"Sign up\n";
	
}
else
{
	shift_down();
	align_center();
//	align_center();
    cout<<Change_color_to("BLUE")<<"Welcome to your personal stock control\n";
	align_center();
	cout<<"\t and inventory system\n";
	align_center(); 
	cout<<Change_color_to("BLUE")<<"Login"<<"\t\t\t\t"<<Change_color_to("YELLOW")<<"Sign up\n";

}
}
void print_loading_bar()
{
	char ch=223;


     cout<<"\t\t\t";    
	 cout<<Change_color_to("BLUE")<<"LOADING.....";
     cout<<endl;
    for(int i=0;i<17;i++)
	cout<<Change_color_to("BLUE")<<ch;
	Sleep(700);
	
	for(int i=0;i<23;i++)
	cout<<Change_color_to("BLUE")<<ch;

	Sleep(700);
	for(int i=0;i<14;i++)
	cout<<Change_color_to("BLUE")<<ch;
//	Sleep(500);
//   for(int i=0;i<51;i++)
//	cout<<Change_color_to("BLUE")<<ch;
	Sleep(350);
}
void getting_stock_input()
{
	cout<<Change_color_to("BLUE");
	cout<<"\n";
    align_center();
	cout<<"Name of Stock\tDay1\tDay2\tDay3\n";

}
void print_return_start(string s)
{   align_center();
	if(s=="return")
    {
    	cout<<Change_color_to("YELLOW")<<"Logout\t\t\t";
    	cout<<Change_color_to("BLUE")<<"Get started\n";
	}
	else
	{
		cout<<Change_color_to("BLUE")<<"Logout\t\t\t";
    	cout<<Change_color_to("YELLOW")<<"Get started\n";
	}
}
void wrong_username()
{
    cout<<"\n";
    cout<<Change_color_to("RED");
	cout<<"\n\n";
    cout<<"     Wrong password or username please try again\n";   
    cout<<"\n";
    cout<<"      PRESS ESCAPE TO RETURN\n";
}
void print_spaces(int l)
{
	for(int i=0;i<14-l;i++)
	cout<<" ";
}




