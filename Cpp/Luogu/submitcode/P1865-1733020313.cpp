#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000005],l,r,sum=0;
void prime(){
	for(int i=2;i<=sqrt(1000000);i++){
		if(a[i]){
			for(int j=i*i;j<=1000000;j+=i){
				a[j]=0;
			}
		}
	}
}
int main(){
	for(int i=1;i<=1000000;i++){
		a[i]=1;
	}
	prime();
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>l>>r;
		if(l<1||r>m){
			cout<<"Crossing the line"<<endl;
		}
		else{
			sum=0;
			for(int j=l;j<=r;j++){
				if(a[j]==1){
					sum+=1;
				}
			}
			if(l==1){
				sum-=1;
			}
			cout<<sum<<endl;
		}
	}
	return 0;
}