#include<bits/stdc++.h>
using namespace std;
int n,k,a[25],b[25],cnt,t,ans,sum=0;
bool flag=1;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<(1<<n);i++){
		int x=i;
		cnt=0,t=1;
		while(x>0){
			if(x%2){
				b[t]=1;
				cnt+=1; 
			}
			else{
				b[t]=0;
			}
			t+=1;
			x/=2;
		}
		if(cnt==k){
			ans=0;
			for(int j=1;j<=n;j++){
				if(b[j]==1){
					ans+=a[j];
				}
			}
			flag=1;
			for(int j=2;j<=sqrt(ans);j++){
				if(ans%j==0){
					flag=0;
					break;
				}
			}
			if(flag==1){
				sum+=1;
			}
		}
	}
	cout<<sum;
	return 0;
}