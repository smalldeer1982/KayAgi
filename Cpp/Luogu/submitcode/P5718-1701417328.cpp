#include <bits/stdc++.h>
using namespace std;
int a[1000000];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	cout<<a[1];
	return 0;
}