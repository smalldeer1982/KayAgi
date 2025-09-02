#include<bits/stdc++.h>
using namespace std;
int a[105],maxn=0,minn=105;
int cnt[30];
string s;
void prime(){
	for(int i=2;i<=sqrt(100);i++){
		if(a[i]){
			for(int j=i*i;j<=100;j+=i){
				a[j]=0;
			}
		}
	}
}
int main(){
	a[0]=0;
	a[1]=0;
	for(int i=2;i<=100;i++){
		a[i]=1;
	}
	prime();
	cin>>s;
	for(int i=0;i<s.length();i++){
		cnt[s[i]-96]+=1;
	}
	for(int i=1;i<=26;i++){
		maxn=max(maxn,cnt[i]);
		if(cnt[i]>0){
			minn=min(minn,cnt[i]);
		}
	}
	if(minn==105){
		minn=1;
	}
	if(a[maxn-minn]==1){
		cout<<"Lucky Word"<<endl;
		cout<<maxn-minn;
	}
	else{
		cout<<"No Answer"<<endl;
		cout<<0;
	}
	return 0;
}
