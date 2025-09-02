#include <iostream>
using namespace std;
int main()
{
	int k,n,a;
	double sn;
	cin>>k;
	a=1;
	n=0;
	sn=0;
	while (sn<=k)
	{
		sn+=1.00/a;
		a+=1;
		n+=1;
	}
	cout<<n;	
    return 0;	
}
