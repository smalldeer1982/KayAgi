#include<bits/stdc++.h>
using namespace std;
int n,q,x,a[100000005],b[6000005],cnt;
void prime2(){
	for(int i=2;i<=n;i++){
		if(a[i]){
			cnt+=1;
			b[cnt]=i;
		}
		for(int j=1;j<=cnt&&i*b[j]<=n;j++){
			a[i*b[j]]=0;
			if(i%b[j]==0){
				break;
			}	
		} 
	}
}
int main(){
	cin>>n>>q;
	memset(a,1,sizeof(a));
	prime2();
	for(int i=1;i<=q;i++){
		scanf("%d",&x);
		cout<<b[x]<<endl;
	}
	return 0;
}
