#include<bits/stdc++.h>
using namespace std;
int n,a[15],sum,ans=1;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		int x=a[i],y=ans;
		while((x%y!=0)&&(y%x!=0)){
			if(x>y){
				x-=y;
			}
			else{
				y-=x;
			}
			
		}
		sum=min(x,y);
		ans*=(a[i]/sum);
	}
	cout<<ans;
	return 0;
}