#include<iostream>
#include<fstream>
#include"Formatting file.cpp"
#include"predicted values.cpp"
#include"conversion codes.cpp"
#include<conio.h>
#include<unordered_map>
#include<string>
#include<string.h>
using namespace std;
class Stock_User{ 
    
	private:
	char user_name[50];
	char pass_word[50];

	protected:
	char stocks[10][100];
	int number_of_stocks;

	public:
	static int number_of_users;
	
	void setup_username(const char u[])
	{  
	   strcpy(user_name,u);
	   number_of_users++;
	}
	void setup_password(const char p[])
	{
		strcpy(pass_word,p);
	}
	void set_stocks(char m[][100],int n)
	{
		for(int i=0;i<n;i++)
		{
			strcpy(stocks[i],m[i]);
		}
		number_of_stocks=n;
	
	}
	char* get_user_name()
	{
		return user_name;
		
	}
	char* get_pass_word()
	{
		return pass_word;
	}
	
   void display()
   {
   	cout<<user_name<<" "<<pass_word<<" "<<number_of_stocks<<" ";
   	 
   	for(int i=0;i<number_of_stocks;i++)
   	cout<<strlen(stocks[i])<<endl;
   }
	int get_size()
	{
		return number_of_stocks;
	}
  void update(char u[],char p[],char m[][100],int nos);
  friend void write_into_file(Stock_User su);
  friend bool is_present(char u[],char p[],char m[][100],int &size);
  friend bool new_user(char u[],char p[]);
  
};
int Stock_User::number_of_users=0;
class Stock_Helper :public Stock_User
{   
	
	friend void array_to_map(char s[10][100],int size,unordered_map<string,vector<int>> &m);
	friend int map_to_array(unordered_map<string,vector<int>> m,char s[][100]);
	
};
void write_into_file(char u[],char p[],char m[][100],int nos)
{ 
    Stock_User su;
    su.setup_password(p);
    su.setup_username(u);
    su.set_stocks(m,nos);
	fstream fout("stocks.dat",ios::binary | ios::out | ios::app);
	fout.write((char*)&su,sizeof(su));
	fout.close();
}
void Stock_User::update(char u[],char p[],char m[][100],int nos)
{ 
    
    int pos, flag = 0; 

    fstream fs; 
    fs.open("stocks.dat", ios::in | ios::binary | ios::out); 
  
    while (!fs.eof()) { 
        
        pos = fs.tellg(); 
  
        fs.read((char*)this, sizeof(Stock_User)); 
        if (fs) { 
   
   
    
            if (strcmp(u,user_name)==0) { 
                flag = 1; 
             
                setup_username(u);
                setup_password(p);
                set_stocks(m,nos);
                fs.seekp(pos); 
  
                fs.write((char*)this, sizeof(Stock_User)); 
                
                break; 
            } 
        } 
    } 
    
    fs.close(); 
  
} 
bool is_present(char u[],char p[],char m[][100],int &size)
{
	Stock_User su;
	fstream fin("stocks.dat",ios::binary | ios::in);
	while(fin.read((char*)&su,sizeof(su)))
		{
  		   if(strcmp(u,su.user_name)==0 && strcmp(p,su.pass_word)==0)
  		   {
  		   	
  		   	for(int i=0;i<su.number_of_stocks;i++)
  		   	{   
  		   		strcpy(m[i],su.stocks[i]);
  		   		
  		   		
		   }
		    size=su.get_size();
  		   	return true;
			 }
		}
		return false;
}
bool new_user(char u[],char p[])
{
	Stock_User su;
	fstream fin("stocks.dat",ios::binary | ios::in);
	while(fin.read((char*)&su,sizeof(su)))
		{
  		   if(strcmpi(u,su.user_name)==0)
  		   {
  		   	return false;
			 }
		}
		return true;
	
}
int Maximize_profit(vector<int> v)
{
    int step=1;
    int profit=0;
    vector<int> predicted_values=get_predicted_values(v);
    int n=predicted_values.size();
    for(int i=0;i<n-1;) {
 
       
        while ((i < n - 1) && (predicted_values[i + 1] <= predicted_values[i]))
            i++;
 
        
        if (i == n - 1)
            break;
 
        int buy_day = i++;
 
      
        while ((i < n) && (predicted_values[i] >= predicted_values[i - 1]))
            i++;
 
        int sell_day = i - 1;
        
        
        cout<<Change_color_to("BLUE");
        cout<<"    ";
        cout<<"Step "<<step<<": ";
        cout <<"Buy on day " << buy_day+1
             << " and then Sell on day " << sell_day+1 << endl;
             step++;
             profit+=predicted_values[sell_day]-predicted_values[buy_day];
    }
    return profit;
}
string print_stocks(unordered_map<string,vector<int>> v,int idx)
{
int i=0;
 string s;
 shift_down();
 align_center();

 cout<<Change_color_to("BLUE")<<"  Choose the stock you want to update:\n\n";
 align_center();
 getting_stock_input();
 cout<<"\n";
	for(auto x:v)
	{
		align_center();
		if(i==idx)
		{
			cout<<Change_color_to("YELLOW");
			cout<<i+1<<"."<<x.first;
			print_spaces(x.first.length());
			for(auto y:x.second)
			cout<<y<<"\t";
			s=x.first;
		}
		else
		{
			cout<<Change_color_to("BLUE");
			cout<<i+1<<"."<<x.first;
			print_spaces(x.first.length());
			for(auto y:x.second)
			cout<<y<<"\t";
		}
		cout<<endl;
		i++;
	}
	return s;
}
string print_stocks_suggestion(unordered_map<string,vector<int>> v,int idx)
{
int i=0;
 string s;
 shift_down();

 cout<<Change_color_to("BLUE")<<"  Choose the stock you want the smart suggestion for:\n\n";
 align_center();
 getting_stock_input();
 cout<<"\n";
	for(auto x:v)
	{
		align_center();
		if(i==idx)
		{
			cout<<Change_color_to("YELLOW");
			cout<<i+1<<"."<<x.first;
			print_spaces(x.first.length());
			for(auto y:x.second)
			cout<<y<<"\t";
			s=x.first;
		}
		else
		{
			cout<<Change_color_to("BLUE");
			cout<<i+1<<"."<<x.first;
			print_spaces(x.first.length());
			for(auto y:x.second)
			cout<<y<<"\t";
		}
		cout<<endl;
		i++;
	}
	return s;
}
string print_stocks_selling(unordered_map<string,vector<int>> v,int idx)
{
int i=0;
 string s;
 shift_down();
 align_center();

 cout<<Change_color_to("BLUE")<<"  Choose the stock you want to sell:\n\n";
 align_center();
 getting_stock_input();
 cout<<"\n";
	for(auto x:v)
	{
		align_center();
		if(i==idx)
		{
			cout<<Change_color_to("YELLOW");
			cout<<i+1<<"."<<x.first;
			print_spaces(x.first.length());
			for(auto y:x.second)
			cout<<y<<"\t";
			s=x.first;
		}
		else
		{
			cout<<Change_color_to("BLUE");
			cout<<i+1<<"."<<x.first;
			print_spaces(x.first.length());
			for(auto y:x.second)
			cout<<y<<"\t";
		}
		cout<<endl;
		i++;
	}
	return s;
}

int main()
{
    
    fontsize(50,50);
    
    bool counter_login=1;
  
    bool counter_start=0;
	print_initial("login");
	bool logged_out=0;
	int c;
while(1)
{
	
	c=getch();
    if(c==224)
    {
    	int k;
    	k=getch();
    	if(k==75)//left arrow
    	{
    		counter_login=1;
    		system("CLS");
    		print_initial("login");
		}
		else if(k==77)//right arrow
		{
		   counter_login=0;
			system("CLS");
    		print_initial("sign up");
		}
    	
	}
	else if(c==13)
	{
		if(counter_login==1)//existing user and search the file
		{
			   char u[50];
	          char p[50];
	         char stocks[10][100];
	         
	        int nos=0;
		  system("CLS");
		    cout<<Change_color_to("BLUE");
		    shift_down();
		    align_center();
		    //align_center();
		    int counter_options=0;
		    cout<<"     PLEASE LOGIN USING CREDENTIALS\n\n";
		    align_center();
			cout<<"Username:";
			cout<<Change_color_to("TURQUOISE");
			cin>>u;
			int i=0;
			char q=9;
			align_center();
			cout<<Change_color_to("BLUE");
			cout<<"Password:";
			cout<<Change_color_to("TURQUOISE");
			while(q!=13)
			{
				q=getch();
				if(isalpha(q) || isdigit(q))
				{ p[i]=q;
				i++;
				cout<<"*";
			    }
			    
		}
		p[i]='\0';
	cout<<"\n";
		print_loading_bar();
		system("CLS");
	      cout<<Change_color_to("BLUE");
			if(is_present(u,p,stocks,nos))//existing user
			{   
			    shift_down();
			    align_center();
				cout<<"You are logged in\n";
				system("CLS");
				shift_down();
				int counter_options=0;
				print_list(counter_options);
				unordered_map<string,vector<int>> stk;
				stk.clear();
				array_to_map(stocks,nos,stk);
		
				//options array is printed;
				while(1)
				{
					string stock_name;
					stock_name.erase();
							
			c=getch();
	     	if(c==224)
	     	{
	     		int k=getch();
	     		if(k==72)
	     		{
	     			 if(counter_options!=0)
	     			 counter_options--;
	     			 else
	     			 counter_options=5;
	     			 
	     			 system("CLS");
	     			 shift_down();
	     			 print_list(counter_options);
				 }
				 else if(k==80)
				 {
				 	 counter_options=(counter_options+1)%6;
				 	 system("CLS");
	     			 shift_down();
	     			 print_list(counter_options);
	     				
				 }
			 }
			 else if(c==13)//option is selected
			 {
			 	
				 if(counter_options==0)//add a new stock
			 	{     
				    string s;
			        system("CLS");
			 		shift_down();
			 		align_center();
			 		getting_stock_input();
			 		char a=9;
			 		s.erase();
			 		while(1)
				       	{
				       		a=getch();
				       		if(a==32)
				       		break;
				       		s+=a;
				       		cout<<"\r";
				       		align_center();
				       		cout<<s;
				       	
				       		
						}
						cout<<"\t\t";
						int val;
						for(int i=0;i<3;i++)
						{
							scanf("%d",&val);
							stk[s].push_back(val);
							cout<<"\t\t";
						}
						
						Stock_User s_u;
						s_u.setup_password(p);
					    s_u.setup_username(u);
					    char map[50][100];
					   int size_of_array=map_to_array(stk,map);
					   s_u.set_stocks(map,size_of_array);
					 	s_u.update(u,p,map,size_of_array);
					 	cout<<"\n";
					 	align_center();
					 	cout<<"Stock bought successfully!\n";
					 	int qwe=getch();
					 	
					 	while(1)
					 	{
					 	system("CLS");
	                    shift_down();
	     			 print_list(counter_options);
					 	break;
					 }
			 		
				 }
				 else if(counter_options==1)//selling a stock
				 {
				 	int idx=0;
				 	system("CLS");
				 	stock_name.erase();
				 	stock_name=print_stocks_selling(stk,0);
				 	int w;
				 	while(1)
				 	{
					 w=getch();
				 	if(w==224)
				 	{
				 		int f=getch();
				 		if(f==72)//up arrow
				 		{
				 			if(idx>0)
				 			{
				 				idx--;
							 }
							 else 
						idx=stk.size()-1;
						
					     system("CLS");
						 stock_name=print_stocks_selling(stk,idx);
						}
						else if(f==80)//down arrow
						{
							idx=(idx+1)%stk.size();
							system("CLS");
						  stock_name=print_stocks_selling(stk,idx);
						}
					 }
					 else if(w==13 && stk.size()>0)//stock is selected and needs to sold
					 {
					 	system("CLS");
					 	shift_down();
					 	int money_gained=stk[stock_name][2];
					 	align_center();
					 	cout<<Change_color_to("PURPLE");
					 	cout<<"Your selected stock has been sold and Rs "<<money_gained;
					 	cout<<"\n";
					 	align_center();
					 	cout<<"have been transferred to your account";
					 	stk.erase(stock_name); 	
					 	Stock_User s_u;
					 	char map[50][100];
					   int size_of_array=map_to_array(stk,map);
					 	s_u.setup_username(u);
					 	s_u.setup_password(p);
					 	s_u.set_stocks(map,size_of_array);
					 	s_u.update(u,p,map,size_of_array);
					 	
					 	int t=getch();
					 	break;
					 	
					 }
					 else if(w==27)
					 {
					 		system("CLS");
	                    shift_down();
	     			 print_list(counter_options);
					 	break;
					 }
				 		
					 }
				 	
				 }
				 else if(counter_options==2)//updating stock
				 {
				 	int idx=0;
				 	system("CLS");
				 	stock_name.erase();
				 	stock_name=print_stocks(stk,0);
				 	int w;
				 	while(1)
				 	{
					 w=getch();
				 	if(w==224)
				 	{
				 		int f=getch();
				 		if(f==72)//up arrow
				 		{
				 			if(idx>0)
				 			{
				 				idx--;
							 }
							 else 
						idx=stk.size()-1;
						
					     system("CLS");
						 stock_name=print_stocks(stk,idx);
						}
						else if(f==80)//down arrow
						{
							idx=(idx+1)%stk.size();
							system("CLS");
						  stock_name=print_stocks(stk,idx);
						}
					 }
					 else if(w==13 && stk.size()>0)//stock is selected and needs to be updated
					 {
					 	system("CLS");
					 	shift_down();
					 	align_center();
					 	int val;
					 	cout<<Change_color_to("BLUE")<<"Enter the latest value for the stock "<<stock_name<<":";
					 	cin>>val;
					 	stk[stock_name][0]=stk[stock_name][1];
					 	stk[stock_name][1]=stk[stock_name][2];
					 	stk[stock_name][2]=val;
					 	Stock_User s_u;
					 	char map[50][100];
					   int size_of_array=map_to_array(stk,map);
					 	s_u.setup_username(u);
					 	s_u.setup_password(p);
					 	s_u.set_stocks(map,size_of_array);
					 	s_u.update(u,p,map,size_of_array);
					 	cout<<"\n";
					 	align_center();
					 	cout<<"Stock updated successfully!\n";
					 	int qwe=getch();
					 	
					 	system("CLS");
	                    shift_down();
	     			 print_list(counter_options);
					 	break;
					 }
					 else if(w==27)
					 {
					 		system("CLS");
	                    shift_down();
	     			 print_list(counter_options);
					 	break;
					 }
				 		
					 }
		
				 	
				 }
				 else if(counter_options==3)//suggest a stock
				 {
		            int idx=0;
				 	system("CLS");
				 	stock_name.erase();
				 	string stock_name=print_stocks_suggestion(stk,idx);
				 	
				 	int w;
				 	while(1)
				 	{
					 w=getch();
				 	if(w==224)
				 	{
				 		int f=getch();
				 		if(f==72)//up arrow
				 		{
				 			if(idx!=0)
				 			idx--;
				 			else
				 			idx=stk.size()-1;
				 			
				 			system("CLS");
				 		stock_name=print_stocks_suggestion(stk,idx);
						    
						}
						else if(f==80)//down arrow
						{
							idx=(idx+1)%stk.size();
								system("CLS");
				 		stock_name=print_stocks_suggestion(stk,idx);
							
						}
					 }
					 else if(w==13 && stk.size()>0)//stock selected and enter is pressed
					 {
					 	system("CLS");
					
					 	cout<<Change_color_to("BLUE");
					 	align_center();
					 	cout<<"Start the Day count after the current day\n\n";
                        
					 	cout<<"  Smart suggestion for this stock is shown below\n\n";
					 	
					   int max_profit=Maximize_profit(stk[stock_name]);
					   cout<<"\n  ";
					   
					   cout<<"Rs "<<max_profit<<" can be earned when above steps are followed\n\n";
					   
					
				      cout<<"(Our system predicts the stock values on the following\n";
					  cout<<"6 days and then determines a strategy to maximize \n";   
					  cout<<"the profit)";
					 
					 int qwe=getch();
					 	system("CLS");
	                    shift_down();
	     			 print_list(counter_options);
					 	break;
					 
					 	
					 }
					 else if(w==27)
					 {
					 		system("CLS");
	                    shift_down();
	     			 print_list(counter_options);
					 	break;
					 }
				 		
					 }
				 	
				 	
				 }
				 else if(counter_options==4)//show all stocks
				 {
				 	system("CLS");
				 	cout<<"\n";
				 	align_center();
				 	getting_stock_input();
				 	for(auto x:stk)
				 	{   
				 	align_center();
				 		cout<<x.first<<"\t\t";
				 		
				 		for(auto y:x.second)
				 		{
				 			cout<<y<<"\t";
						 }
						 cout<<"\n";
		
					 }
					 cout<<"\n\n";
					 align_center();
					 cout<<"PRESS ANY KEY TO RETURN......";
					 int qwe=getch();
					while(1)
					{
					 	system("CLS");
	                    shift_down();
	     			 print_list(counter_options);
					 	break;
					 }
				 	
				 }
				 else//customer logout to home out
				 {
				 	counter_login=1;
    		system("CLS");
    		print_initial("login");
    		break;
			 	
				 }
			 }
			 else if(c==27)
			 {
			 	counter_login=1;
    		system("CLS");
    		print_initial("login");
    		break;
			 }
				}
				
			}
			else//user does not exist please register
			{   
			    system("CLS");
				wrong_username();
				
				cout<<"\n";
				align_center();
				cout<<"Press any key to return....";
				int t;
				t=getch();
			    system("CLS");
			    	print_initial("login");
			    	counter_login=1;
				
			}
			
			
			
		}
	
	
	
	
	
	
	
	
	
		
		
		///****///sign up page
		else//new user and wants to sign up
		{
			
			char u[50];
			char p[50];
			char stocks[10][100];
			system("CLS");
          cout<<Change_color_to("BLUE");
			  char rp[50];
		 shift_down();
         align_center();
        cout<<Change_color_to("BLUE")<<"Register and get started!\n\n";
         align_center();
		cout<<"Set Username:";
		cout<<Change_color_to("TURQUOISE");
		cin>>u;
		align_center();
		cout<<Change_color_to("BLUE");
		cout<<"Set Password:";
		int i=0;
		char ch=9;
		cout<<Change_color_to("TURQUOISE");
		while(ch!=13)
		{
			ch=getch();
			if(isalpha(ch) || isdigit(ch))
			{
			p[i]=ch;
			i++;
			cout<<"*";	
		   }
	    }

		p[i]='\0';
		cout<<"\n";
		align_center();
		cout<<Change_color_to("BLUE");
		cout<<"Re-enter Password:";
		cout<<Change_color_to("TURQUOISE");
		cin>>rp;
		cout<<Change_color_to("BLUE");
		if(new_user(u,p) && strcmp(rp,p)==0)
		{
          	cout<<"\n";
			align_center();	
			cout<<"Registration Successfull! You are logged in\n\n";
			print_return_start("return");
			unordered_map<string,vector<int>> stk;
			while(1)
			{
				c=getch();
				if(c==224)
				{
					int k=getch();
					if(k==75)
					{
						system("CLS");
						shift_down();
						align_center();
					  cout<<Change_color_to("BLUE")<<"Register and get started!\n\n";
                 align_center();
		        cout<<"Set Username:"<<Change_color_to("TURQUOISE")<<u<<"\n";
		        align_center();
		        cout<<Change_color_to("BLUE");
		        cout<<"Set Password:";
		        cout<<Change_color_to("TURQUOISE");
		        for(int p=0;p<i;p++)
		        cout<<"*";
		        cout<<"\n";
		align_center();
		cout<<Change_color_to("BLUE");
		cout<<"Re-enter Password:";
		 cout<<Change_color_to("TURQUOISE");
		cout<<rp;
		cout<<Change_color_to("BLUE");
		        cout<<"\n\n";
			align_center();	
			cout<<"Registration Successfull! You are logged in\n\n";
			print_return_start("return");
					counter_start=0;
					}
					else if(k==77)
					{
				    	system("CLS");
				    	shift_down();
						align_center();
				   cout<<Change_color_to("BLUE")<<"Register and get started!\n\n";
                 align_center();
		        cout<<"Set Username:"<<Change_color_to("TURQUOISE")<<u<<"\n";
		        align_center();
		        cout<<Change_color_to("BLUE");
		        cout<<"Set Password:";
		        cout<<Change_color_to("TURQUOISE");
		        for(int p=0;p<i;p++)
		        cout<<"*";
		           cout<<"\n";
		align_center();
		cout<<Change_color_to("BLUE");
		cout<<"Re-enter Password:";
		cout<<Change_color_to("TURQUOISE");
		cout<<rp;
		       cout<<"\n\n";
			align_center();	
		
			cout<<Change_color_to("BLUE")<<"Registration Successfull! You are logged in\n\n";
						print_return_start("start");
						counter_start=1;
					}
					
				}
				else if(c==13)//user pressed enter
				{
					
					if(counter_start==1)
					{  
					system("CLS");
					cout<<Change_color_to("BLUE");
					int nos;
					shift_down();
					align_center();
					   cout<<"Enter number of stocks you want to enter:";
					   cin>>nos;
					   system("CLS");
					   shift_down();
					   align_center();
				       getting_stock_input();
				       char a=9;
				       int val;
				       string s;
				       for(int i=1;i<=nos;i++)
				       {
				       	align_center();
				       	while(1)
				       	{
				       		a=getch();
				       		if(a==32)
				       		break;
				       		s+=a;
				       		cout<<"\r";
				       		align_center();
				       		cout<<s;
				       	
				       		
						}
						cout<<"\t\t";
						for(int i=0;i<3;i++)
						{
							scanf("%d",&val);
							stk[s].push_back(val);
							cout<<"\t\t";
						}
						 
						   s.erase();
				       	
					   }
				      Stock_User su;
				      su.setup_password(p);
				      su.setup_username(u);
					char stok_map[10][100];
				  int size=map_to_array(stk,stok_map);
				   su.set_stocks(stok_map,size);
				   write_into_file(u,p,stok_map,size);
	
	     system("CLS");
	     shift_down();
	      int counter_options=0;
	     print_list(counter_options);
	     //options array is printed
	     while(1)
	     {
	     	c=getch();
	     	if(c==224)
	     	{
	     		int k=getch();
	     		if(k==72)
	     		{
	     			 if(counter_options!=0)
	     			 counter_options--;
	     			 else
	     			 counter_options=5;
	     			 system("CLS");
	     			 shift_down();
	     			 print_list(counter_options);
				 }
				 else if(k==80)
				 {
				 	
				 	counter_options=(counter_options+1)%6;
				 	 system("CLS");
	     			 shift_down();
	     			 print_list(counter_options);
	     			
				 	
				 }
			 }
			 else if(c==13)//option is selected
			 {
			 	
				 if(counter_options==0)//buy a stock
			 	{  
				    system("CLS");
			 		shift_down();
			 		align_center();
			 		getting_stock_input();
			 		s.erase();
			 		while(1)
				       	{
				       		a=getch();
				       		if(a==32)
				       		break;
				       		s+=a;
				       		cout<<"\r";
				       		align_center();
				       		cout<<s;
				       	
				       		
						}
						cout<<"\t\t";
						for(int i=0;i<3;i++)
						{
							scanf("%d",&val);
							stk[s].push_back(val);
							cout<<"\t\t";
						}
					Stock_User s_u;
					 	char map[10][100];
					   int size_of_array=map_to_array(stk,map);
					 	s_u.setup_password(p);
					 	s_u.setup_username(u);
					 	s_u.set_stocks(map,size_of_array);
					 	s_u.update(u,p,map,size_of_array);
					 	cout<<"\n";
					 	align_center();
					 	cout<<"Stock bought successfully!\n";
					 	while(1)
					 	{
					 	int qwe=getch();
					 	system("CLS");
	                    shift_down();
	     			 print_list(counter_options);
					 	break;
					 }
			 		
				 }
				 else if(counter_options==1)
				 {
				 	   int idx=0;
				 	system("CLS");
				 	string stock_name;
				 	stock_name=print_stocks_selling(stk,0);
				 	int w;
				 	while(1)
				 	{
					 w=getch();
				 	if(w==224)
				 	{
				 		int f=getch();
				 		if(f==72)//up arrow
				 		{
				 			if(idx>0)
				 			{
				 				idx--;
							 }
							 else 
						idx=stk.size()-1;
						
					     system("CLS");
						 stock_name=print_stocks_selling(stk,idx);
						}
						else if(f==80)//down arrow
						{
							idx=(idx+1)%stk.size();
							system("CLS");
						  stock_name=print_stocks_selling(stk,idx);
						}
					 }
					 else if(w==13 && stk.size()>0)//stock is selected and needs to sold
					 {
					 	system("CLS");
					 	shift_down();
					 	int money_gained=stk[stock_name][2];
					 	align_center();
					 	cout<<Change_color_to("PURPLE");
					 	cout<<"Your selected stock has been sold and Rs "<<money_gained;
					 	cout<<"\n";
					 	align_center();
					 	cout<<"have been transferred to your account";
					 	stk.erase(stock_name); 	
					 	Stock_User s_u;
					 	char map[50][100];
					   int size_of_array=map_to_array(stk,map);
					 	s_u.setup_username(u);
					 	s_u.setup_password(p);
					 	s_u.set_stocks(map,size_of_array);
					 	s_u.update(u,p,map,size_of_array);
					 	
					 	int t=getch();
					 	break;
					 	
					 }
					 else if(w==27)
					 {
					 		system("CLS");
	                    shift_down();
	     			 print_list(counter_options);
					 	break;
					 }
				 		
					 }
				 }
				 else if(counter_options==2)//updating stock
				 {
				 	int idx=0;
				 	system("CLS");
				 	string stock_name;
				 	stock_name=print_stocks(stk,0);
				 	int w;
				 	while(1)
				 	{
					 w=getch();
				 	if(w==224)
				 	{
				 		int f=getch();
				 		if(f==72)//up arrow
				 		{
				 			if(idx>0)
				 			{
				 				idx--;
							 }
							 else 
						idx=stk.size()-1;
						
					     system("CLS");
						 stock_name=print_stocks(stk,idx);
						}
						else if(f==80)//down arrow
						{
							idx=(idx+1)%stk.size();
							system("CLS");
						  stock_name=print_stocks(stk,idx);
						}
					 }
					 else if(w==13 && stk.size()>0)//stock selected and enter is pressed
					 {
					 	system("CLS");
					 	shift_down();
					 	align_center();
					 	cout<<Change_color_to("BLUE")<<"Enter the latest value for the stock "<<stock_name<<":";
					 	cin>>val;
					 	stk[stock_name][0]=stk[stock_name][1];
					 	stk[stock_name][1]=stk[stock_name][2];
					 	stk[stock_name][2]=val;
					 	Stock_User s_u;
					 	char map[10][100];
					   int size_of_array=map_to_array(stk,map);
					 	s_u.setup_password(p);
					 	s_u.setup_password(u);
					 	s_u.set_stocks(map,size_of_array);
					 	s_u.update(u,p,map,size_of_array);
					 	cout<<"\n";
					 	align_center();
					 	cout<<"Stock updated successfully!\n";
					 	int qwe=getch();
					 	
					 	system("CLS");
	                    shift_down();
	     			 print_list(counter_options);
					 	break;
					 }
					 else if(w==27)
					 {
					 	system("CLS");
	                    shift_down();
	     			 print_list(counter_options);
					 	break;
					 }
				 		
					 }
		
				 	
				 }
				 else if(counter_options==3)//suggest a stock
				 {
		            int idx=0;
				 	system("CLS");
				 	string stock_name=print_stocks_suggestion(stk,idx);
				 	
				 	int w;
				 	while(1)
				 	{
					 w=getch();
				 	if(w==224)
				 	{
				 		int f=getch();
				 		if(f==72)//up arrow
				 		{
				 			if(idx!=0)
				 			idx--;
				 			else
				 			idx=stk.size()-1;
				 			
				 			system("CLS");
				 		stock_name=print_stocks_suggestion(stk,idx);
						    
						}
						else if(f==80)//down arrow
						{
							idx=(idx+1)%stk.size();
								system("CLS");
				 		stock_name=print_stocks_suggestion(stk,idx);
							
						}
					 }
					 else if(w==13 && stk.size()>0)//stock selected and enter is pressed
					 {
					 	system("CLS");
					
					 	cout<<Change_color_to("BLUE");
					 	align_center();
					 	cout<<"Start the Day count after the current day\n\n";
                        
					 	cout<<"  Smart suggestion for this stock is shown below\n\n";
					 	
					   int max_profit=Maximize_profit(stk[stock_name]);
					   cout<<"\n  ";
					   
					   cout<<"Rs "<<max_profit<<" can be earned when above steps are followed\n\n";
					   
					
				      cout<<"(Our system predicts the stock values on the following\n";
					  cout<<"6 days and then determines a strategy to maximize \n";   
					  cout<<"the profit)";
					 
					 int qwe=getch();
	
					 	system("CLS");
	                    shift_down();
	     			 print_list(counter_options);
					 	break;
					 
					 	
					 }
					 else if(w==27)
					 {
					 	system("CLS");
	                    shift_down();
	     			 print_list(counter_options);
					 	break;
					 }
				 		
					 }
				 	
				 	
				 }
				 else if(counter_options==4)//show all stocks
				 {
				 	system("CLS");
				 	cout<<"\n";
				 	align_center();
				 	getting_stock_input();
				 	for(auto x:stk)
				 	{   
				 	align_center();
				 		cout<<x.first<<"\t\t";
				 		
				 		for(auto y:x.second)
				 		{
				 			cout<<y<<"\t";
						 }
						 cout<<"\n";
		
					 }
					 cout<<"\n\n";
					 align_center();
					 cout<<"PRESS ANY KEY TO RETURN......";
					 int qwe=getch();
					while(1)
					{
					 	system("CLS");
	                    shift_down();
	     			 print_list(counter_options);
					 	break;
					 }
				 	
				 }
				 else//customer pressed return
				 {
				
					 system("CLS");
						shift_down();
						align_center();
					  cout<<Change_color_to("BLUE")<<"Register and get started!\n\n";
                 align_center();
		        cout<<"Set Username:"<<Change_color_to("TURQUOISE")<<u<<"\n";
		        align_center();
		        cout<<Change_color_to("BLUE");
		        cout<<"Set Password:";
		       cout<<Change_color_to("TURQUOISE");
		        for(int p=0;p<i;p++)
		        cout<<"*";
		        cout<<"\n";
			align_center();	
			cout<<Change_color_to("BLUE");
			cout<<"Re-enter Password:";
			cout<<Change_color_to("TURQUOISE")<<rp;
		cout<<Change_color_to("BLUE")<<"\n\n";
		align_center();
			cout<<"Registration Successfull! You are logged in\n\n";
			print_return_start("return");
					counter_start=0;
			 	break;
	     	 
				 
				 	
				 }
			 }
			 else if(c==27)
			 {   system("CLS");
			 		counter_start=0;
	print_initial("login");
			 	break;
			 }
		//////	 
		 }		
				}
					else//user exits and returns
					{
					system("CLS");
					print_initial("login");
			    	counter_login=1;
					break;
						
					}
					
				}
				else if(c==27)
				{
					system("CLS");
					print_initial("login");
			    	counter_login=1;
					break;
					
				}
			}
		}
			
		else
		{   cout<<"\n";
			cout<<Change_color_to("RED")<<"   Username already exists or password doesn't match!\n\n";
			align_center();
			cout<<"PRESS ESCAPE TO RETURN...";
			int x;
			x=getch();
			system("CLS");
				print_initial("login");
			    	counter_login=1;
		}
         
      	
		}
		
	}
	else if(c==27)
	{
		system("CLS");
		break;
		
	}
   
}  
   shift_down();
   align_center();
    cout<<Change_color_to("PURPLE")<<"Thank you for using our stock system";
    return 0;
}
