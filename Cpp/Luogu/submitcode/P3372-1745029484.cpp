#include<bits/stdc++.h>
using namespace std;
long long n,m,siz,a[500005],s[500005],up[500005];
int main(){
	cin>>n>>m;
	siz=sqrt(n);
	for(int i=0;i<n;i++){
		cin>>a[i];
		s[i/siz]+=a[i];
	}
	for(int i=1;i<=m;i++){
		long long op,x,y,p;
		cin>>op>>x>>y;
		if(op==1){
			x-=1;
			y-=1;
			cin>>p;
			if(x/siz==y/siz){
				for(int i=x;i<=y;i++){
					a[i]+=p;
					s[i/siz]+=p; 
				}
			}
			else{
				for(int i=x;i<(x/siz+1)*siz;i++){
					a[i]+=p;
					s[i/siz]+=p;
				}
				for(int i=y/siz*siz;i<=y;i++){
					a[i]+=p;
					s[i/siz]+=p;
				}
				for(int i=x/siz+1;i<y/siz;i++){
					s[i]+=p*siz;
					up[i]+=p;
				}	
			}	
		}
		else{
			x-=1;
			y-=1;
			long long ans=0;
			if(x/siz==y/siz){
				for(int i=x;i<=y;i++){
					ans+=a[i]+up[i/siz];
				}
			}
			else{
				for(int i=x;i<(x/siz+1)*siz;i++){
					ans+=a[i]+up[i/siz];
				}
				for(int i=y/siz*siz;i<=y;i++){
					ans+=a[i]+up[i/siz];
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