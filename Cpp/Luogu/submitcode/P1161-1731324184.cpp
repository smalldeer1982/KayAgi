#include<bits/stdc++.h>
using namespace std;
int n,a[2000005],y;
double x,t;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>t;
		for(double j=1;j<=t;j++){
			if(a[int(x*j)]==1){
				a[int(x*j)]=0;
			}
			else{
				a[int(x*j)]=1;
			}
		}
	}
	for(int i=1;;i++){
		if(a[i]==1){
			cout<<i;
			break;
		}
	}
	return 0;
}