#include<bits/stdc++.h>
using namespace std;
int n,b[1005],sum;
struct game{
	int x,f;
}a[1005];
bool cmp(game y,game z){
	if(y.f>z.f){
		return true;
	}
	else if(y.f==z.f&&y.x<z.x){
		return true;
	}
	return false;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i].f;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		int j=a[i].x;
		while(j>0){
			if(b[j]==0){
				b[j]=a[i].f;
				break;
			}
			else{
				j-=1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		sum+=b[i];
	}
	cout<<sum;
	return 0;
}