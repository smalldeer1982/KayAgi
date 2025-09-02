#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;
int n,q;
int ch[maxn][27];
int idx=1,y[maxn],z[maxn];
string s;
void insert(string x){
	int p=1;
	for(int i=0;i<x.size();i++){
		int j=x[i]-'a';
		if(!ch[p][j]){
			ch[p][j]=++idx;
		}
		p=ch[p][j];
	}
	y[p]=1;
}
int query(string x){
	int p=1;
	for(int i=0;i<x.size();i++){
		int j=x[i]-'a';
		if(!ch[p][j]){
			return 0;
		}
		p=ch[p][j];
	}
	if(y[p]){
		if(z[p]){
			return 2;
		}
		else{
			z[p]=1;
			return 1;
		}
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(false); // 加速输入输出
    cin.tie(nullptr);

    // 初始化数组
    memset(ch, 0, sizeof(ch));
    memset(y, 0, sizeof(y));
    memset(z, 0, sizeof(z));
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		insert(s);
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>s;
		int num=query(s);
		if(num==0){
			cout<<"WRONG"<<endl;
		}
		else if(num==1){
			cout<<"OK"<<endl;
		}
		else{
			cout<<"REPEAT"<<endl;
		}
	}
	return 0;
}
