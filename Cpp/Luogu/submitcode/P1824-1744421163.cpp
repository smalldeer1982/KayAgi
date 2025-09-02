#include<bits/stdc++.h>
using namespace std;
int n,c,a[200005];
bool check(int x){
	int pre=a[1],num=1;
	for(int i=2;i<=n;i++){
		if(a[i]-pre>=x){
			pre=a[i];
			num+=1;
		}
	}
	return num<c;
} 
int main(){
	cin>>n>>c;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	int l=1,r=1e9+5;
	while(l<r){
		int mid=(l+r+1)/2;
		if(check(mid)){
			r=mid-1;
		}
		else{
			l=mid;
		}
	}
	cout<<l;
	return 0;
}