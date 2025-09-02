#include<bits/stdc++.h>
using namespace std;
int n,sum1,sum2;
string s,t;
int main(){
	cin>>n;
	cin>>s>>t;
	for(int i=0;i<n;i++){
		if(s[i]=='R'&&t[i]=='S'||s[i]=='S'&&t[i]=='P'||s[i]=='P'&&t[i]=='R'){
			sum1+=1;
		}
		else if(t[i]=='R'&&s[i]=='S'||t[i]=='S'&&s[i]=='P'||t[i]=='P'&&s[i]=='R'){
			sum2+=1;
		}
	}
	cout<<sum1<<" "<<sum2;
	return 0;
}
