#include <iostream>
using namespace std;
int main()
{
    int a[15],n,sum=0;
    for (int i=1;i<=10;i++)
    {
		cin>>a[i];
	}
	cin>>n;
	for (int i=1;i<=10;i++)
	{
		if ((n+30)>=a[i])
		{
			sum+=1;
		}
	}
	cout<<sum;
    return 0;	
}