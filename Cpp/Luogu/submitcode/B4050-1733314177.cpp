#include<bits/stdc++.h>
using namespace std;
int n,a[100005],sum=1,ans=0,x;
void prime(){
	a[1]=0;
	for(long long i=2;i<=sqrt(100005);i++){
		if(a[i]==0){
			for(long long j=i*i;j<=100005;j+=i){
				a[j]=1;
			}
		}
	}
}
int main(){
	prime();
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		sum=1;
		ans=0;
		while(x>=0){
			if(a[x]==0){
				ans+=1;
				cout<<ans<<endl;
				break;
			}
			else{
				ans+=1;
				x-=sum;
				sum*=2;
			}
		}
		if(x<0){
			cout<<-1<<endl;
		}
	}
	return 0;
}