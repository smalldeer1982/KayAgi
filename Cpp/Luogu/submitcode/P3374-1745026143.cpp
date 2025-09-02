#include<bits/stdc++.h>
using namespace std;
int n,m,siz,a[500005],s[10005];
int main(){
	cin>>n>>m;
	siz=sqrt(n);
	for(int i=0;i<n;i++){
		cin>>a[i];
		s[i/siz]+=a[i];
	}
	for(int i=1;i<=m;i++){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1){
			x-=1;
			a[x]+=y;
			s[x/siz]+=y;
		}
		else{
			x-=1;
			y-=1;
			int ans=0;
			if(x/siz==y/siz){
				for(int i=x;i<=y;i++){
					ans+=a[i];
				}
			}
			else{
				for(int i=x;i<x/siz*siz+siz;i++){
					ans+=a[i];
				}
				for(int i=y/siz*siz;i<=y;i++){
					ans+=a[i];
				}
				for(int i=x/siz+1;i<y/siz;i++){
					ans+=s[i];
				}	
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}