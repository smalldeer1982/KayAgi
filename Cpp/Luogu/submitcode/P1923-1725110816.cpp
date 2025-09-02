#include<bits/stdc++.h>
using namespace std;
int n,k,a[5000005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
		cin>>a[i];
	}
    nth_element(a,a+k+1,a+n+1);
    cout<<a[k+1];
}