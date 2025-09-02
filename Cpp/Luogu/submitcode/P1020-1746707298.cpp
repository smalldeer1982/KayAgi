#include<bits/stdc++.h>
using namespace std;
int sum=0,x,ans=-1,p=-1,k;
int a[50005],f[50005],b[50005];
int main(){
	while(cin>>x){
		sum+=1;
		a[sum]=x;
		p=-1;
		for(int i=1;i<=k;i++){
			if(b[i]>=x){
				p=i;
				break;
			}
		}
		if(p==-1){
			k++;
			b[k]=x;
		}
		else{
			b[p]=x;
		}
	}
	for(int i=1;i<=sum;i++){
		f[i]=1;
		for(int j=1;j<=i-1;j++) {
			if(a[j]>=a[i]){
				f[i]=max(f[i],f[j]+1);
			}
		}
		ans=max(ans,f[i]);
	}
	cout<<ans<<endl;
	cout<<k<<endl;
	return 0;
}