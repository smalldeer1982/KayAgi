#include<bits/stdc++.h>
using namespace std;
int n,s,l,b,sum=0;
struct apple{
	int x,y;
}a[5005];
bool cmp(apple one,apple two){
	if(one.y<two.y){
		return true;
	}
	return false;
}
int main(){
	cin>>n>>s>>l>>b;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(s<a[i].y){
			break;
		}
		if(a[i].x<=l+b){
			s-=a[i].y;
			sum+=1;
		}
	}
	cout<<sum;
	return 0;
}
