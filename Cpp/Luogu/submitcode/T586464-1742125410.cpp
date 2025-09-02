#include<bits/stdc++.h>
using namespace std;
int n,sum1,sum2;
string s;
int main(){
	cin>>n>>s;
	for(int i=0;i<n;i++){
		if(i%2==0&&s[i]=='W'){
			sum1+=1;
		}
		if(i%2==1&&s[i]=='B'){
			sum1+=1;
		}
	}
	for(int i=0;i<n;i++){
		if(i%2==0&&s[i]=='B'){
			sum2+=1;
		}
		if(i%2==1&&s[i]=='W'){
			sum2+=1;
		}
	}
	cout<<min(sum1,sum2);
	return 0;
}
