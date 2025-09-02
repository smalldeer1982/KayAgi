#include<bits/stdc++.h>
using namespace std;
#define int long long
char f;
string x="12345678",mb="";
map<string,string>mp;
string now;
queue<string>q;
void A(string x){
	now=x;
	x[0]=now[7],x[1]=now[6],x[2]=now[5],x[3]=now[4];
	x[7]=now[0],x[6]=now[1],x[5]=now[2],x[4]=now[3];
	if(mp.count(x)==0){
		q.push(x);
		mp[x]=mp[now]+'A';
	}
}
void B(string x){
	now=x;
	x[0]=now[3],x[1]=now[0],x[2]=now[1],x[3]=now[2];
	x[7]=now[4],x[6]=now[7],x[5]=now[6],x[4]=now[5];
	if(mp.count(x)==0){
		q.push(x);
		mp[x]=mp[now]+'B';
	}
}
void C(string x){
	now=x;
	x[1]=now[6],x[2]=now[1];
	x[6]=now[5],x[5]=now[2];
	if(mp.count(x)==0){
		q.push(x);
		mp[x]=mp[now]+'C';
	}
}
void bfs(){
	q.push("12345678");
	mp["12345678"]="";
	while(!q.empty()){
		A(q.front());
		B(q.front());
		C(q.front());
		if(mp.count(mb)!=0){
			cout<<mp[mb].size()<<endl;
			cout<<mp[mb]<<endl;
			return;
		}
		q.pop();
	}
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(int i=1;i<=8;i++){
		cin>>f;
		mb+=f;
	}
	bfs();
	return 0;
}
