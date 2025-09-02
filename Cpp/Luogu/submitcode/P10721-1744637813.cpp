#include<bits/stdc++.h>
using namespace std;
int n,a[25],m,c[100005],cnt=0;
int dp[100005];
string s;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	cin>>m>>s;
	for(int i=1;i<=n;i++){
        for(int j=i;j<=m;j++){
            dp[j]=max(dp[j],dp[j-i]+a[i]);
        }
    }
	for(int i=0;i<=m-1;i++){
		int num=i,sum=0;
		while(s[num]=='a'&&s[num+1]=='b'&&s[num+2]=='c'){
			sum+=1;
			num+=3;
		}
		i=num;
		if(sum>=1){
			cnt+=1;
			c[cnt]=sum;
		}
	}
	int ans=0;
	for(int i=1;i<=cnt;i++){
		ans+=dp[c[i]];
	}
	cout<<ans;
	return 0;
}
