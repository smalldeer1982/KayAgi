#include<bits/stdc++.h>
using namespace std; 
const int N=50005;
int a[N];
int n,m,l;
bool check(int mid){
	int c=0;
	int p=0;
	for(int i=1;i<=n;i++){
		if(a[i]-p<mid){
			c++;
		}
		else{
			p=a[i];
		}
	}
	if(l-p<mid){
		c++;
	}
	return c<=m;
}
int main(){
	cin>>l>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int left=1,right=l,mid;
	while(left<=right){
		mid=(left+right)/2;
		if(check(mid)){
			left=mid+1;
		}
		else{
			right=mid-1;
		}
	}
	cout<<left-1;
	return 0;
}