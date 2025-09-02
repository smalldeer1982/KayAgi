#include<bits/stdc++.h>
using namespace std; 
const int N=200005;
int n,m,a[N],maxn=-1;
bool check(int x){  
    int now=1,num=1;
    for(int i=2;i<=n;i++){
        if(a[i]-a[now]>=x){
            now=i;
            num++;
        }
    }
    return num>=m;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	int left=1,right=1e9,mid;
	while(left<=right){
		mid=(left+right)/2;
		if(check(mid)){
			left=mid+1;
			maxn=max(maxn,mid);
		}
		else{
			right=mid-1;
		}
	}
	cout<<maxn;
	return 0;
}