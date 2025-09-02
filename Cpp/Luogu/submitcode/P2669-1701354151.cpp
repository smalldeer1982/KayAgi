#include <iostream>
using namespace std;
int main()
{
    int k,n,sum=0,a=0;
    n=0;
    cin>>k;
    for (int i=1;i<=k;i+=n)
    { 
		n+=1;
		if (k-(i-1)<n)
		{
			a=(k-(i-1))*n;
			n-=1;
			break;
		}
	}
	while (n>0)
	{
		sum+=n*n;
		n-=1;
	}
	sum+=a;
	cout<<sum;   
    return 0;	
}