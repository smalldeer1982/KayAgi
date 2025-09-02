# Balanced Paths

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jag2015spring/tasks/icpc2015spring_a



# 题解

## 作者：lzqy_ (赞：0)

## 题目大意

> 给出一棵 $n$ 个节点的树，每个节点为 `(`  或 `)`求有多少个有序点对 $(u,v)$ 满足路径 $\{u \rightarrow v\}$ 是合法括号序列。
>
> $1 \le n \le 10^5$

## 思路

对于点对计数，考虑点分治。

将路径拆成一条深度递增 $S$ 和一条深度递减的链 $T$。发现两条链可以拼起来的前提是 $S$ 中没有未匹配的 `)`，$T$ 中没有未匹配的 `(`，且 $S$ 中未匹配的 `(` 数量等于 $T$ 中未匹配的 `)` 数量。

所以点分治每一层向下递归的时候，分深度递增和深度递减两种情况（即路径顺序从根出发或到根结束），动态维护未匹配的 `(`，`)` 数量，放到桶里累加答案即可。

注意到点对是有序的，所以需要拿 $S$ 匹配一遍 $T$，再拿 $T$ 匹配一遍 $S$。

时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
using namespace std;
const int maxn=100010;
il int cread(){
	char c=getchar();
	for(;c!='('&&c!=')';c=getchar());
	return c=='(';
}
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x; 
}
struct edge{
	int v,to;
}e[maxn<<1];
int head[maxn],ecnt;
void addedge(int u,int v){
	e[++ecnt].v=v,e[ecnt].to=head[u],head[u]=ecnt;
}
bool vis[maxn];
int a[maxn],n,rt;
int sz[maxn],mp[maxn];
int tap[maxn];
ll ans;
void getrt(int fa,int x,int tot){
	sz[x]=1,mp[x]=0;
	for(int i=head[x];i;i=e[i].to)
		if(!vis[e[i].v]&&e[i].v!=fa){
			getrt(x,e[i].v,tot);
			sz[x]+=sz[e[i].v],mp[x]=max(mp[x],sz[e[i].v]); 
		}mp[x]=max(mp[x],tot-sz[x]);
	if(!rt||mp[x]<mp[rt]) rt=x;
}
void calc1(int fa,int x,bool typ,int f=0,int b=0){
	if(a[x]) f++;
	else f?f--:b++;
//	printf("%d,%d\n",f,b);
	if(!f) typ?ans+=tap[b]:tap[b]++;
	for(int i=head[x];i;i=e[i].to)
		if(!vis[e[i].v]&&e[i].v!=fa) 
			calc1(x,e[i].v,typ,f,b);
}
void calc2(int fa,int x,bool typ,int f=0,int b=0){
	if(a[x]) b?b--:f++;
	else b++;
	if(!b) typ?ans+=tap[f]:tap[f]++;
	for(int i=head[x];i;i=e[i].to)
		if(!vis[e[i].v]&&e[i].v!=fa)
			calc2(x,e[i].v,typ,f,b);
}
void clear1(int fa,int x,int f=0,int b=0){
	if(a[x]) f++;
	else f?f--:b++;
	if(!f) tap[b]--;
	for(int i=head[x];i;i=e[i].to)
		if(!vis[e[i].v]&&e[i].v!=fa) 
			clear1(x,e[i].v,f,b);
}
void clear2(int fa,int x,int f=0,int b=0){
	if(a[x]) b?b--:f++;
	else b++;
	if(!b) tap[f]--;
	for(int i=head[x];i;i=e[i].to)
		if(!vis[e[i].v]&&e[i].v!=fa)
			clear2(x,e[i].v,f,b);
}
void Solve(int x){
//	printf("%d\n",x);
	if(a[x]) tap[1]++;
	for(int i=head[x];i;i=e[i].to)
		if(!vis[e[i].v])
			calc1(x,e[i].v,1),calc2(x,e[i].v,0,a[x],!a[x]);
	for(int i=head[x];i;i=e[i].to) 
		if(!vis[e[i].v]) clear2(x,e[i].v,a[x],!a[x]);
	if(a[x]) tap[1]--;
	////
	if(!a[x]) tap[1]++;
	for(int i=head[x];i;i=e[i].to)
		if(!vis[e[i].v])
			calc2(x,e[i].v,1),calc1(x,e[i].v,0,a[x],!a[x]);
	for(int i=head[x];i;i=e[i].to) 
		if(!vis[e[i].v]) clear1(x,e[i].v,a[x],!a[x]);
	if(!a[x]) tap[1]--;
}
void dfs(int x){
	vis[x]=1,Solve(x);
	for(int i=head[x];i;i=e[i].to)
		if(!vis[e[i].v])
			rt=0,getrt(x,e[i].v,sz[e[i].v]),dfs(rt);
}
int main(){
	int x,y;
	n=read();
	for(int i=1;i<=n;i++) a[i]=cread();
	for(int i=1;i<n;i++){
		x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}getrt(0,1,n),dfs(rt);
	printf("%lld\n",ans);
	return 0;
}
```



---

