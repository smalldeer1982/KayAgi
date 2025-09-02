#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4+5;
int a[maxn],b[maxn],c[maxn],d[1005][1005],pre[405][maxn];
int n,k,m,x;
int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++){
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b,b+n);
	int cnt=unique(b,b+n)-b;
	for(int i=0;i<n;i++){
		a[i]=lower_bound(b,b+cnt,a[i])-b;
	}
	k=int(sqrt(n));
	for(int i=0;i<(n-1)/k+1;i++){
		memset(c,0,sizeof(c));
		int num=0,dan=0;
		for(int j=i*k;j<n;j++){
			c[a[j]]++;
			if(c[a[j]]>num||(c[a[j]]==num&&a[j]<dan)){
				num=c[a[j]];
				dan=a[j];
			}
			if((j+1)%k==0||j+1==n){
				d[i][j/k]=dan;
			}
		}	
	}
	memset(c,0,sizeof(c));
	for(int i=0;i<n;i++){
		for(int j=i/k;j<(n-1)/k+1;j++){
			pre[j][a[i]]++;
		}
	}
	for(int I=0;I<m;I++){
		int l,r,l0,r0;
		cin>>l0>>r0;
		l=(l0+x-1)%n+1;
		r=(r0+x-1)%n+1;
		if(l>r){
			swap(l,r);
		} 
		l--;
		r--;
		int dan=0,num=0;
		if(l/k==r/k){
			for(int i=l;i<=r;i++){
				c[a[i]]++;
				if(c[a[i]]>num||(c[a[i]]==num&&a[i]<dan)){
					num=c[a[i]];
					dan=a[i];
				}
			}
			for(int i=l;i<=r;i++){
				c[a[i]]--;
			}
		}
		else{
			for(int i=l;i<(l/k+1)*k;i++){
				c[a[i]]++;
				int U=pre[r/k-1][a[i]]-pre[l/k][a[i]]+c[a[i]];
				if(U>num||(U==num&&a[i]<dan)){
					num=U;
					dan=a[i];
				}
			}
			for(int i=r/k*k;i<=r;i++){
				c[a[i]]++;
				int U=pre[r/k-1][a[i]]-pre[l/k][a[i]]+c[a[i]];
				if(U>num||(U==num&&a[i]<dan)){
					num=U;
					dan=a[i];
				}
			}
			if(r/k-l/k>1){
				int f=d[l/k+1][r/k-1];
				int U=pre[r/k-1][f]-pre[l/k][f];
				if(U>num||(U==num&&f<dan)){
					num=U;
					dan=f;
				}	
			}
			for(int i=l;i<(l/k+1)*k;i++){
				c[a[i]]--;
			}
			for(int i=r/k*k;i<=r;i++){
				c[a[i]]--;
			}	
		}
		x=b[dan];
		cout<<b[dan]<<endl;
	}
	return 0;
} 