#include<bits/stdc++.h>
using namespace std;
int n,l,r,a[55],maxx,miny,sum,x;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	cin>>l>>r;
	for(int i=1;i<=n;i++){
		if(a[i]>r){
			maxx+=a[i]-r;
		}
		else if(a[i]<l){
			miny+=l-a[i];
		}
		
	}
	if(sum<l*n||sum>r*n){
		cout<<-1;
	}
	else{
		x=max(maxx,miny);
		cout<<x;
	}
	return 0;
}