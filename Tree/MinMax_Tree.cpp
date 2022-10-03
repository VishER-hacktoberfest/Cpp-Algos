#include<iostream>   
#include<algorithm>   
using namespace std;   
int main()   
{   
pair<int, int> mnmx;   
mnmx = minmax(53, 23);   

cout << "The minimum value obtained is : ";   
cout << mnmx.first;   
cout << "\nThe maximum value obtained is : ";   
cout << mnmx.second ;   
        
mnmx = minmax({2, 5, 1, 6, 3});   
          
cout << "\n\nThe minimum value obtained is : ";   
cout << mnmx.first;   
cout << "\nThe maximum value obtained is : ";   
cout << mnmx.second;   
return 0;        
}  
