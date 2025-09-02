#include<bits/stdc++.h>
using namespace std;
int n,a[100005],mark;
struct node{
	int num,s;
}t[100005];
void insert(int k){
	int find=0,flag=0,tnum=100005;
	for(int i=0;i<mark;i++){
		if(t[i].s==k-1){
			if(t[i].num<tnum){
				flag=i;
				find=1;
				tnum=t[i].num;
			}
		}
	}
	if(find==1){
		t[flag].s=k;
		t[flag].num+=1;
	}
	else{
		t[mark].s=k;
		t[mark].num=1;
		mark+=1;
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		insert(a[i]);
	}
	int ans=t[0].num;
	for(int i=1;i<mark;i++){
		ans=min(ans,t[i].num);
	}
	cout<<ans;
	return 0;
}
