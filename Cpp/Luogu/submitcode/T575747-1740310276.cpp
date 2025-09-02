#include<bits/stdc++.h>
using namespace std;
string s;
int k,ans;
int main(){
	cin>>s>>k;
	for(int i=0;i<s.length();i++){
		if((s[i]=='C'&&s[i+k]=='L')||(s[i]=='L'&&s[i+k]=='C')){
			ans+=1;
		}
	}
	cout<<ans;
	return 0;
}
