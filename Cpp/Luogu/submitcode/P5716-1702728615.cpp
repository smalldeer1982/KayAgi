#include <iostream>
using namespace std;
int main()
{
    int n,m;
	cin>>n>>m;
	if (m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12) 
    {
        cout<<31;
        return 0;
    }
	if (m==4 || m==6 || m==9 || m==11) 
    {   
        cout<<30;
        return 0;
    }   
	if ((n%400==0 || (n%4==0 && n%100!=0)) && m==2)
	{
		cout<<29;
	}
	else 
    {    
        cout<<28;
	    return 0;
    }
}