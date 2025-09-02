#include <iostream>
using namespace std;
int main()
{
    int a,b,c;
    c=0;
    cin>>a;
    for (int i=1;i<=a/2;i++)
    {
        if (a%i==0)
        {
        	b=a/i;
        	if (i<=b)
        	{
				c+=1;	
			}
            
        }
        
    }
    cout<<c;
    return 0;	
}