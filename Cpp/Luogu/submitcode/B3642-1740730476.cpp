#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
	int l,r; 
}a[1000005];
void preorder(int rt){
	cout<<rt<<" ";
	if(a[rt].l!=0){
		preorder(a[rt].l);
	}
	if(a[rt].r!=0){
		preorder(a[rt].r);
	}
}
void inorder(int rt){
	if(a[rt].l!=0){
		inorder(a[rt].l);
	}
	cout<<rt<<" ";
	if(a[rt].r!=0){
		inorder(a[rt].r);
	}
}
void afterorder(int rt){
	if(a[rt].l!=0){
		afterorder(a[rt].l);
	}
	if(a[rt].r!=0){
		afterorder(a[rt].r);
	}
	cout<<rt<<" ";
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;
	}
	preorder(1);
	cout<<endl;
	inorder(1);
	cout<<endl;
	afterorder(1);
	return 0;
} 