#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long n,x=0,sum=0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
        string str;
		cin >> str;
		sum=0;
		for (int j = str.length() - 1; j >= 0; j--) 
		{
            if ((str.length() - j) % 2 == 1)   // 奇数位
			{
				x=(int)str[j]-48;
				x*=7;
				while(x>9)
				{
					x=(x/10%10)+(x%10);
				}	
				sum+=x;
			}
			else
			{
				x=(int)str[j]-48;
				sum+=x;
			}
		}
		if(sum%8==0)
		{
			cout<<"T"<<endl;
		}
		else
		{
			cout<<"F"<<endl;
		}
	}
	return 0;
}