#include<bits/stdc++.h>
using namespace std;
int m,n,a[100005],b[100005],ans=0;
int find(int x){
	int mid,l=0,r=m-1;
	while(true)
	{
		mid=(l+r)/2;
		if(a[mid]==x){
			return 0;
		}
		else if(a[mid]<x&&a[mid+1]>=x){
			return min(x-a[mid],a[mid+1]-x);
		}
		else if(a[mid]<x){
			l=mid+1;
		}
		else{
			r=mid;
		}
	}
}
int main(){
	cin>>m>>n;
	for(int i=0;i<m;i++){
		cin>>a[i];
	}
	for(int i=0;i<n;i++)
	{
		cin>>b[i];
	}
	sort(a,a+m);
	for(int i=0;i<n;i++){
		if(a[0]>=b[i]){
			ans+=a[0]-b[i];
		}
		else if(a[m-1]<=b[i]){
			ans+=b[i]-a[m-1];
		}
		else
		{
			ans+=find(b[i]);
		}
	}
	cout<<ans;
	return 0;
}