#include <iostream>  
#include <Windows.h>  
using namespace std;  
HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);  
void fontsize(int fsa, int fsb)
{  
  PCONSOLE_FONT_INFOEX lpConsoleCurrentFontE = new CONSOLE_FONT_INFOEX();  
  lpConsoleCurrentFontE->cbSize = sizeof(CONSOLE_FONT_INFOEX);  
  GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontE);  
  lpConsoleCurrentFontE->dwFontSize.X = fsa;  
  lpConsoleCurrentFontE->dwFontSize.Y = fsb;  
  SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontE); 
 }  

