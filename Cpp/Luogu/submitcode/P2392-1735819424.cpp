#include<bits/stdc++.h>
using namespace std;
int n,s[5],a[25],b[5],sum=0,ans=INT_MAX;
void dfs(int x,int num){
    for(int i=1;i<=2;i++){
        if(b[i]>=ans){
            return;
        }
    }
    if(x==s[num]+1){
        int t=0;
        for(int i=1;i<=2;i++){
            t=max(t,b[i]);
        }
        ans=min(ans,t);
    }
    else{
        for(int i=1;i<=2;i++){
            b[i]+=a[x];
            dfs(x+1,num);
            b[i]-=a[x];
        }
    }
}
int main(){
    for(int i=1;i<=4;i++){
        cin>>s[i];
    }
    for(int i=1;i<=4;i++){
    	ans=INT_MAX;
		for(int j=1;j<=s[i];j++){
			cin>>a[j];
		}
		dfs(1,i);
		sum+=ans;
	}
    cout<<sum;
    return 0;
}