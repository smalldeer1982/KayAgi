#include<bits/stdc++.h>
using namespace std;
int n;
long long a[1000005],sum=1,maxn=0,x=-1;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=n;i++)
    {
        if(a[i]!=x)
        {
            x=a[i];
            maxn=max(maxn,sum);
            sum=1;
        }
        else
        {
            sum+=1;
        }
    }
    cout<<maxn;
    return 0;
} 