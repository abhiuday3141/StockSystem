#include <iostream> 
#include<string>
#include <windows.h> 
#include<conio.h>
using namespace std;
string color_array[]={"BLACK","BLUE","GREEN","LIGHT BLUE","RED","PURPLE","YELLOW","WHITE","GREY","NAVY BLUE","GREEN","TURQUOISE","PINK","PURPLE","PEACH"};
int return_color_idx(string s)
{
	for(int i=0;i<15;i++)
	{
		if(s==color_array[i])
		{
		return i;
	}
	}
	return 7;
	
}
class Change_color_to{ 
private: 
         int color; 
         HANDLE consoleHandle;
         
  public: 
         Change_color_to(string requiredcolor){ 
             consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); 
             color = return_color_idx(requiredcolor); 
         } 
 
         friend ostream& operator<<(ostream& ss, Change_color_to obj){ 
             SetConsoleTextAttribute(obj.consoleHandle, obj.color); 
             return ss; 
         } 
  
}; 
