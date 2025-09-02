#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int data,add=0,mul=1;
	int num=0;
}tree[400005];
int n,m,q,num,a[100005];
void build(int fa,int left,int right){
	if(left==right){
		tree[fa].data=a[left],tree[fa].num=1,num=max(num,fa);return;
	}
	int mid=(left+right)>>1;
	build(fa<<1,left,mid);
	build((fa<<1)+1,mid+1,right);
	tree[fa].data=(tree[fa<<1].data+tree[(fa<<1)+1].data)%q;
	tree[fa].num=tree[fa<<1].num+tree[(fa<<1)+1].num;
}
void push_down(int fa){
	tree[fa<<1].data=(tree[fa<<1].data*tree[fa].mul)%q;
	tree[fa<<1].data=(tree[fa<<1].data+tree[fa].add*tree[fa<<1].num)%q;
	tree[(fa<<1)+1].data=(tree[(fa<<1)+1].data*tree[fa].mul)%q;
	tree[(fa<<1)+1].data=(tree[(fa<<1)+1].data+tree[fa].add*tree[(fa<<1)+1].num)%q;
	tree[fa<<1].add=(tree[fa<<1].add*tree[fa].mul+tree[fa].add)%q;
	tree[fa<<1].mul=tree[fa<<1].mul*tree[fa].mul%q;
	tree[(fa<<1)+1].add=(tree[(fa<<1)+1].add*tree[fa].mul+tree[fa].add)%q;
	tree[(fa<<1)+1].mul=tree[(fa<<1)+1].mul*tree[fa].mul%q;
	tree[fa].mul=1;
	tree[fa].add=0;
}
int query(int fa,int left,int right,int begin,int end){
	int ans=0;
	if(left<=begin&&right>=end){
		return tree[fa].data;
	} 
	push_down(fa);
	int mid=(begin+end)>>1;
	if(left<=mid){
		ans+=query(fa<<1,left,right,begin,mid);
	}
	if(right>mid){
		ans+=query((fa<<1)+1,left,right,mid+1,end);
	}
	return ans%q;
}
void update(int fa,int left,int right,int begin,int end,int k,int type){
	if(left<=begin&&right>=end){
		if(type==0){
			tree[fa].data=(tree[fa].data+k*tree[fa].num)%q;
			tree[fa].add=(tree[fa].add+k)%q;
		}
		else{
			tree[fa].data=(tree[fa].data*k)%q;
			tree[fa].mul=(tree[fa].mul*k)%q;
			tree[fa].add=(tree[fa].add*k)%q;
		}
		return;
	}
	push_down(fa);
	int mid=(begin+end)>>1;
	if(left<=mid){
		update(fa<<1,left,right,begin,mid,k,type);
	}
	if(right>mid){
		update((fa<<1)+1,left,right,mid+1,end,k,type);
	}
	tree[fa].data=(tree[fa<<1].data+tree[(fa<<1)+1].data)%q;
}
signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build(1,1,n);
	int type,left,right,k;
	for(int i=1;i<=m;i++){
		cin>>type;
		if(type==1){
			cin>>left>>right>>k;
			update(1,left,right,1,n,k,1);
		}
		else if(type==2){
			cin>>left>>right>>k;
			update(1,left,right,1,n,k,0);
		}
		else{
			cin>>left>>right;
			cout<<query(1,left,right,1,n)<<'\n';
		}
	}
	return 0;
}