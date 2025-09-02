#include<bits/stdc++.h>
using namespace std;
int n,m,a[10005];
void prime(){
	for(int i=2;i<=sqrt(10000);i++){
		if(a[i]){
			for(int j=i*i;j<=10000;j+=i){
				a[j]=0;
			}
		}
	}
}
int main(){
	for(int i=2;i<=10000;i++){
		a[i]=1;
	}
	prime();
	cin>>n>>m;
	for(int i=n;i<=m;i++){
		if(a[i]==1){
			int x=i;
			bool flag=1;
			while(x/10!=0){
				x/=10;
				if(a[x]==0){
					flag=0;
					break;
				}
			}
			if(a[x]==1&&flag==1){
				cout<<i<<endl;
			}
		}
	}
	return 0;
}
