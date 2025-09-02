#include <iostream>
using namespace std;
int main()
{
	int n,k;
	double sum=0,sum1=0,a=0,b=0;
	cin >> n>>k;
	for (int i=1;i<=n;i++)
	{
		if(i%k==0)
		{
			a+=i;
			sum+=1;
		}
		else 
		{
			b+=i;
			sum1+=1;
		}
	}
	printf("%.1f",a/sum);
	cout<<" ";
	printf("%.1f",b/sum1);		
	return 0;
}
