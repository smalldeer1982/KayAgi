#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
string s,p;
int ne[maxn];
int main(){
	cin>>s>>p;
	int slen=s.size();
	int plen=p.size();
	s=" "+s;
	p=" "+p;
	for(int i=2,j=0;i<=plen;i++){
		while(j&&p[j+1]!=p[i]){
			j=ne[j];
		}
		if(p[j+1]==p[i]){
			j++;
		}
		ne[i]=j;
	}
	for(int i=1,j=0;i<=slen;i++){
		while(j&&p[j+1]!=s[i]){
			j=ne[j];
		}
		if(p[j+1]==s[i]){
			j++;
		}
		if(j==plen){
			cout<<i-plen+1<<endl;
		}
	}
	for(int i=1;i<=plen;i++){
		cout<<ne[i]<<" ";
	}
	return 0;
}