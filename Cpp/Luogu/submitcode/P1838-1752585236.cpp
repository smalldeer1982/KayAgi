#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[15],b[15];
string s;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(i%2==0){
			a[s[i]-'0']+=1;
			if((a[1]&&a[4]&&a[7])||(a[2]&&a[5]&&a[8])||(a[3]&&a[6]&&a[9])||(a[1]&&a[2]&&a[3])||(a[4]&&a[5]&&a[6])||(a[7]&&a[8]&&a[9])||(a[1]&&a[5]&&a[9])||(a[3]&&a[5]&&a[7])){
				cout<<"xiaoa wins.";
				return 0;
			}
		}
		else{
			b[s[i]-'0']+=1;
			if((b[1]&&b[4]&&b[7])||(b[2]&&b[5]&&b[8])||(b[3]&&b[6]&&b[9])||(b[1]&&b[2]&&b[3])||(b[4]&&b[5]&&b[6])||(b[7]&&b[8]&&b[9])||(b[1]&&b[5]&&b[9])||(b[3]&&b[5]&&b[7])){
				cout<<"uim wins.";
				return 0;
			}
		}
	}
	cout<<"drew.";
	return 0;
}
