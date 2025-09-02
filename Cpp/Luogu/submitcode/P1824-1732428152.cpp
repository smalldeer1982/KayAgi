#include<bits/stdc++.h>
using namespace std; 
int n,m,a[200005],ans;
bool check(int x){  
    int now=1,num=1;
    for(int i=2;i<=n;i++){
        if(a[i]-a[now]>=x){
            now=i;
            num++;
        }
    }
    if(num<m){
    	return true;
	}
    return false;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	int l=1,r=1e9,mid;
	while(l<r){
		mid=(l+r+1)/2;
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