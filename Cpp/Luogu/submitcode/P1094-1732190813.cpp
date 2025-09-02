#include<bits/stdc++.h>
using namespace std;
int w,n,a[30005],sum;
int main(){
	cin>>w>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	sort(a+1,a+n+1);
	int l=1,r=n;
	while(l<=r){
		if(a[l]+a[r]<=w){
			l+=1;
			r-=1;
			sum+=1;
		}
		else{
			r-=1;
			sum+=1;
		}
	}
	cout<<sum;
	return 0;
}