#include<bits/stdc++.h>
using namespace std;
long long a,b,c,cnt[25][25][25];
long long solve(long long a,long long b,long long c){
	if(a<=0||b<=0||c<=0){
		return 1;
	}
	if(a>20||b>20||c>20){
		return solve(20,20,20);
	}
	if(a<b&&b<c){
		if(cnt[a][b][c-1]==0){
			cnt[a][b][c-1]=solve(a,b,c-1);
		}
		if(cnt[a][b-1][c-1]==0){
			cnt[a][b-1][c-1]=solve(a,b-1,c-1);
		}
		if(cnt[a][b-1][c]==0){
			cnt[a][b-1][c]=solve(a,b-1,c);
		}
		cnt[a][b][c]=cnt[a][b][c-1]+cnt[a][b-1][c-1]-cnt[a][b-1][c];
	}
	else{
		if(cnt[a-1][b][c]==0){
			cnt[a-1][b][c]=solve(a-1,b,c);
		}
		if(cnt[a-1][b-1][c]==0){
			cnt[a-1][b-1][c]=solve(a-1,b-1,c);
		}
		if(cnt[a-1][b][c-1]==0){
			cnt[a-1][b][c-1]=solve(a-1,b,c-1);
		}
		if(cnt[a-1][b-1][c-1]==0){
			cnt[a-1][b-1][c-1]=solve(a-1,b-1,c-1);
		}
		cnt[a][b][c]=cnt[a-1][b][c]+cnt[a-1][b][c-1]+cnt[a-1][b-1][c]-cnt[a-1][b-1][c-1];
	}
	return cnt[a][b][c];
}
int main(){
	while(true){
		cin>>a>>b>>c;
		if(a==-1&&b==-1&&c==-1){
			return 0;
		}
		cout<<"w("<<a<<", "<<b<<", "<<c<<") = ";
		cout<<solve(a,b,c)<<endl;
	}
	return 0;
}
