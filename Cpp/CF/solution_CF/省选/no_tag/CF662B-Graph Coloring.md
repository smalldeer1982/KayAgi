# Graph Coloring

## 题目描述

给出一个$n$个点，$m$条边的无向图，一开始每条边可能是红色或者蓝色，翻转一个点可以使相连的边变成相反的颜色，希望能够把全部边变成红色或者蓝色
问最少需要翻转的点数，并给出具体的方案

---

## 样例 #1

### 输入

```
3 3
1 2 B
3 1 R
3 2 B
```

### 输出

```
1
2 
```

## 样例 #2

### 输入

```
6 5
1 3 R
2 3 R
3 4 B
4 5 R
4 6 R
```

### 输出

```
2
3 4 
```

## 样例 #3

### 输入

```
4 5
1 2 R
1 3 R
2 3 B
3 4 B
1 4 B
```

### 输出

```
-1
```

# 题解

## 作者：Jr_Zlw (赞：9)

# 并查集

提供一种只需使用并查集的好写的方法。

统一蓝和统一红只有一个取反的差别，以下默认全部统一为蓝。

一条蓝边，它的两个端点要么都选，要么都不选。

一条红边，它的两个端点只选择其中之一。

于是对每个点建立两个事件“它选”和“它不选”，可以用诸如  $i,i+n$  的一类方法记录，以下以  $i$  表示选，$i+n$  表示不选。


按照上面的条件，设一条边两个端点为  $(u,v)$。可以发现：

一条蓝边，加入无向边  $(u,v),(u+n,v+n)$。

一条红边，加入无向边  $(u,v+n),(u+n,v)$。


到了这一步，大部分题解使用了  $\rm 2-SAT$  判定。

但其实这些条件都是双向的，并查集就可以实现判断，一个连通块内的事件必须同时发生。

于是贪心地选择一下操作最少连通块就好了，甚至不用建图，也没有啥细节。

代码：

```
#include<bits/stdc++.h>
#define rep(a,b,c) for(int c(a);c<=(b);++c)
#define drep(a,b,c) for(int c(a);c>=(b);--c)
using namespace std;
inline int read()
{
	int res=0;char ch=getchar();while(ch<'0'||ch>'9')ch=getchar();
	while(ch<='9'&&ch>='0')res=res*10+(ch^48),ch=getchar();return res;
}
inline bool Get(){char c;do c=getchar();while(c!='R'&&c!='B');return c=='R';}
const int N=1e5+10;int fa[N<<1],U[N],V[N],sz[N<<1];bool W[N],vis[N<<1];int n,m;
inline int fnd(int x){return fa[x]==x?x:fa[x]=fnd(fa[x]);}
inline void merge(int x,int y)
{
	int X=fnd(x),Y=fnd(y);if(X==Y)return;
	fa[X]=Y;sz[Y]+=sz[X];
}
vector<int> a[2];
inline bool work(vector<int> &ans)
{
	memset(vis+1,0,n<<1);
	rep(1,n<<1,i)fa[i]=i,sz[i]=(i<=n);
	rep(1,m,i)
	{
		int u=U[i],v=V[i];
		if(W[i])merge(u,v),merge(u+n,v+n);
		else merge(u+n,v),merge(u,v+n);
	}
	rep(1,n,i)if(fnd(i)==fnd(i+n))return false;
	rep(1,n,i)
	{
		int u=fnd(i),v=fnd(i+n);
		if(!vis[u]&&!vis[v])
		{
			if(sz[u]<sz[v]){ans.push_back(i);vis[v]=true;}
			else vis[u]=true;
		}
		else{if(vis[v])ans.push_back(i);}
	}
	return true;
}
inline void print(vector<int> &a)
{
	printf("%d\n",int(a.size()));
	for(int v:a)printf("%d ",v);puts("");
}
int main()
{
	n=read();m=read();rep(1,m,i){U[i]=read();V[i]=read();W[i]=Get();}
	bool f1=work(a[0]);
	rep(1,m,i)W[i]^=1;
	bool f2=work(a[1]);
	if(!f1&&!f2)return puts("-1"),0;
	if(!f1||!f2){if(f1)print(a[0]);else print(a[1]);return 0;}
	if(a[0].size()>a[1].size())print(a[1]);else print(a[0]);
}
``



---

## 作者：401rk8 (赞：5)

已经有一篇 2-SAT 题解了，但那篇题解没有用到本题的性质，导致代码不那么简洁

---

分别算全变成 `R` 或 `B` 的代价取 $\min$，以变为 `R` 的单个连通块为例：

显然每个点最多翻一次。记 $i$ 为点 $i$ 不翻转，$i+n$ 为点 $i$ 翻转，连边：

- $c_{i}=R$：$(u_{i},v_{i}),(v_{i},u_{i}),(u_{i}+n,v_{i}+n),(v_{i}+n,u_{i}+n)$（要么都翻，要么都不翻）
- $c_{i}=B$：$(u_{i},v_{i}+n),(v_{i}+n,u_{i}),(u_{i}+n,v_{i}),(v_{i},u_{i}+n)$（翻一个）

然后跑 2-SAT，若 $i,i+n$ 在同一 SCC 无解。  
本题的特殊之处在于都是无向边，那么选点 $i$ 就必须选 $i$ 所在的连通块包含的所有点，$i+1$ 同理，且对于 $i,i+n$ 所在的两个连通块，$\forall j\ne i$ 要么不在其中任意一个，要么 $j,j+n$ 分处两个。因此对于 $i,i+n$ 这两个 SCC，只需要贪心的选需要翻转的点数少的即可。

代码几乎都是板子，非常好写。时间复杂度 $O(n)$

[code](https://codeforces.com/contest/662/submission/137589996)

---

## 作者：cmll02 (赞：3)

巨大多细节题。

显然联通块之间互不影响，于是我们每个联通块单独计算答案。

首先全局考虑最后把边染成红色还是~~黑色~~蓝色。

发现如果一个点确定了颜色，那么与这个点直接相连的也确定了颜色，这样下去整个联通块的颜色都确定了。

所以我们每个联通块随便选一个点考虑就行了。

首先假设它不选。然后如果染色成功，注意到把每个点状态反转之后一定还是成功的（相当于异或 $1$ 两次）。

那么看反转是否更优，如果更优就反转。

```cpp
// Problem: CF662B Graph Coloring
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF662B
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <queue>
#define odb(x) printf("%d ",x)
#define odl(x) printf("%d\n",x)
#define rg(x) for(int i=1;i<=(x);i++){
#define fe(u) for(int i=h[u];i;i=e[i].nxt){int v=e[i].v,w=e[i].w;
#define gr }
#define int long long
#define newe(n) struct Edge{int v,w,nxt;}e[n*2+5];\
typedef int arr[n+5];\
arr h;\
int cnt=1;\
inline void addedge(int u,int v,int w){e[cnt]=(Edge){v,w,h[u]};h[u]=cnt++;}
inline int read()
{
	int num=0,f=1;char c=getchar();
	while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
	while(c>47&&c<58)num=num*10+(c^48),c=getchar();
	return num*f;
}
inline int re1d()
{
	char c=getchar();
	while(c<'A'||c>'Z')c=getchar();
	return c=='R';
}
inline int min(int a,int b){return a>b?b:a;}
inline int max(int a,int b){return a<b?b:a;}
newe(200005)
int ans[200005];
class cmll02{
	public:
	int fin=0;
int vis[200005];
int qwq[200005];
int wis[200005],y[200005];
void cpy_main(int u,int fa,int q)
{
	wis[u]=1;
	qwq[u]^=q;
	fe(u)(wis[v]==0)?cpy_main(v,u,q):(void)0;gr
}
int sz,ss;
void cpy_cnt(int u,int fa)
{
	y[u]=1;
	sz++;ss+=qwq[u];
	fe(u)(y[v]==0)?cpy_cnt(v,u):(void)0;gr
}
void cpy(int u,int fa)
{
	sz=ss=0;
	cpy_cnt(u,fa);
	if(ss>sz-ss)cpy_main(u,fa,1);
	else cpy_main(u,fa,0);
}
int dfs(int u,int fa,int c)
{
	qwq[u]=2;vis[u]=1;
	int c1=0,c0=0;
	fe(u)if(vis[v])if(qwq[v]==(c^1^w))c1++;else c0++;gr
	int rs=0;
	if(c1==c0&&c0==0)
	{
		qwq[u]=0;
		fe(u)(vis[v]==0)&&(rs+=dfs(v,u,c));gr
		return rs;
	}
	if(c1&&c0)return 1919810;
	if(c0)qwq[u]=0;else qwq[u]=1,rs=1;
	fe(u)(vis[v]==0)&&(rs+=dfs(v,u,c));gr
	return rs;
}}cmll[2];
inline void solve(int n)
{
	int q0=(cmll[0].dfs(n,0,0)),q1=(cmll[1].dfs(n,0,1));
	cmll[0].cpy(n,0);
	cmll[1].cpy(n,0);
//	odp(q0,q1);
	cmll[0].fin+=q0;
	cmll[1].fin+=q1;
	if(min(q1,q0)>=1919810){puts("-1");exit(0);};
//	if(q0<q1)cmll[0].cpy(n,0);else cmll[1].cpy(n,1);
}
signed main()
{
	int n=read(),m=read();
	rg(m)int u=read(),v=read(),w=re1d();addedge(u,v,w);addedge(v,u,w);gr
	rg(n)if(!cmll[0].vis[i]&&!cmll[1].vis[i])solve(i);gr
	int q0=cmll[0].fin,q1=cmll[1].fin;
	if(min(q0,q1)>=1919810)return puts("-1")&0;
	q0=0,q1=0;
	rg(n)q0+=cmll[0].qwq[i];gr
	rg(n)q1+=cmll[1].qwq[i];gr
	if(cmll[0].fin>=1919810)q0=1919810;
	if(cmll[1].fin>=1919810)q1=1919810;
//	oldp(q0,q1);//
	if(q0<q1)
	{
		odl(q0);
		rg(n)cmll[0].qwq[i]&&odb(i);gr
	}
	else
	{
		odl(q1);
		rg(n)cmll[1].qwq[i]&&odb(i);gr
	}
	return 0;
}
```

---

## 作者：lemondinosaur (赞：3)

[洛谷CF662B](https://www.luogu.org/problemnew/show/CF662B)

---
# 分析
首先翻转奇数次也就是翻转一次，翻转偶数次也就是不翻转，首先我们先枚举要全部变成的颜色，如果这样翻转，会分成几个连通图，对于每个连通图，用深搜的方式，先指定一个点要翻转，然后与它相连的点判断是否需要翻转，如果与它相连的点翻转过而且不合法，那么这种方式也是不合法的，那么应该会分成两个阵营，变色或者不变色，若变色数量超过不变色数量，当然需要把不变色的点变色，变色的点不变色，我的方法就是用一个队列把所有点存下来，当变色数量$tot1$>不变色数量$tot2$,集体翻转

---
# 代码
```cpp
#include <cstdio>
#include <cstring>
#include <cctype>
#include <queue>
#define rr register
using namespace std;
struct node{int y,w,next;}e[200011];
int color1[100001],color[100001]; queue<int>q;
int n,k=1,tot1,tot2,ls[100001],ans=-1,want;
inline signed iut(){
    rr int ans=0; rr char c=getchar();
    while (!isdigit(c)) c=getchar();
    while (isdigit(c)) ans=(ans<<3)+(ans<<1)+(c^48),c=getchar();
    return ans;
}
inline void dfs(int x){
    if (color[x]) ++tot1; else ++tot2; q.push(x);
    for (rr int i=ls[x];i;i=e[i].next){
        rr int j=color[x]^want^e[i].w;
        if (color[e[i].y]<0){
            color[e[i].y]=j;
            dfs(e[i].y);
            if (tot1<0) return;
        }
        else if (color[e[i].y]!=j) {tot1=-1; return;}//怎么可能有解
    }
}
inline void tryto(int temp){
    rr int tans=0; want=temp;
    memset(color,-1,sizeof(color));
    for (rr int i=1;i<=n;++i)
    if (color[i]<0){
    	while (q.size()) q.pop();
        tot1=tot2=0,color[i]=1,dfs(i);
        if (tot1<0) {tans=-1; break;}
        tans+=tot1<tot2?tot1:tot2;
        rr bool t=tot1>tot2;
        while (q.size())
            color[q.front()]^=t,q.pop();
    }
    if ((ans==-1||ans>tans)&&tans!=-1){
        for (rr int i=1;i<=n;++i)
            color1[i]=color[i];
        ans=tans;
    }
}
signed main(){
    n=iut();
    for (rr int m=iut();m;--m){
        rr int x=iut(),y=iut(),q=getchar()=='R';
        e[++k]=(node){y,q,ls[x]}; ls[x]=k;
        e[++k]=(node){x,q,ls[y]}; ls[y]=k;
    }
    tryto(0); tryto(1);
    printf("%d\n",ans);
    if (ans!=-1) for (rr int i=1;i<=n;++i)
    if (color1[i]) printf("%d ",i);
    return 0;
}
```

---

## 作者：A_zjzj (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF662B)

## 题目大意
> 给你一张无向图，图中每条边是蓝色或者红色的，让你每次选一个点，就会把与这个点相连的边的颜色反转（红变蓝，蓝变红），求最少步数的方案使得最后所有边的颜色都一样。

## 思路
好像没有 $2-sat$ 的题解，那我就来一发。

首先分类讨论：要么都变成红色，要么都变成蓝色。

如果一条边的颜色与当前我们期望的颜色相同，那么要么两个点都选，要么都不选，所以如果一个点不选，那么另一个点也不选，一个点选了，另一个点也要选，建图就行了，如下图。

![A_zjzj](https://img-blog.csdnimg.cn/ac4795ef0a764999b81b1fff7615544b.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0Ffemp6ag==,size_16,color_FFFFFF,t_70)

那么同理，如果一条边的颜色与期望的颜色不同，所以，如果一个点选，另一个点就不能选，如果一个点不选，那么另一个点就必须能选，~~图的话，略吧~~。

这样我们就理出来一个 $2-sat$ 的模型。

判断无解的情况，这就是 $2-sat$ 的经典操作，判断 $u,u'$ 是否处于一个强联通分量即可。

对于有解的情况，还要输出解，那么由于这个图是上下对称的，所以也就是说，如果你选了 $i_1,i_2\dots,i_m,j_1',j_2'\dots,j_{m'}'$ 这个强联通分量，那么你也一定可以不选它，选 $i_1',i_2'\dots,i_m',j_1,j_2\dots,j_{m'}$ 这个强联通分量，那么为了让选的个数尽可能的少，所以看看这两个东西中 $u'$ 个数谁多谁少，加到答案里面，然后再把选的这些点放到最后的方案里面就行了。

详见代码。

~~不知道为什么其他题解说这题细节多，可能我的方法没啥细节。~~
## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
void read(){}//学起来吧,可以这么用:read(a,b,c,……,n);
template<typename _Tp,typename... _Tps>
void read(_Tp &x,_Tps &...Ar){
	x=0;char c=getchar();bool flag=0;
	while(c<'0'||c>'9')flag|=(c=='-'),c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if(flag)x=-x;
	read(Ar...);
}
const int N=1e5+10;
int n,m;
struct zj{
	int u,v,w;
}a[N];
struct edges{
	int to,nex;
}edge[N*4];//注意对于每一条边,要建两条双向边,所以大小要开 4 倍
int head[N*2],kk;
void addedge(int u,int v){//链式前向星基本操作,直接建双向边了
	edge[++kk]=(edges){v,head[u]};head[u]=kk;
	edge[++kk]=(edges){u,head[v]};head[v]=kk;
}
int dfn[N*2],low[N*2],s[N*2],top,cnt,scc[N*2],scct;//点数别忘了开 2 倍
void tarjan(int u){//tarjan 缩点模板
	dfn[u]=low[u]=++cnt;s[++top]=u;
	for(int i=head[u];i;i=edge[i].nex){
		int v=edge[i].to;
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(!scc[v])low[u]=min(low[u],low[v]);
	}
	if(dfn[u]==low[u]){
		++scct;
		while(s[top]!=u)scc[s[top--]]=scct;
		scc[s[top--]]=scct;
	}
}
int cnt1,cnt2,k1[N],k2[N],s1[N],s2[N];//记录 dfs 中到达的 u 和 u' 的数量和编号
bool vis[N];
void dfs(int u){
	if(vis[(u-1)%n+1])return;//1,2,……,n 不变, n+1,n+2,……,n+n 变成 1,2,……,n
	vis[(u-1)%n+1]=1;u<=n?(k1[++cnt1]=u):(k2[++cnt2]=u-n);
	for(int i=head[u];i;i=edge[i].nex){
		int v=edge[i].to;
		dfs(v);
	}
}
int get(){
	int i;char c[5];bool flag1,flag2;int ans1=0,ans2=0;
	for(read(n,m),i=1;i<=m;i++)read(a[i].u,a[i].v),scanf("%s",c),a[i].w=(c[0]=='R');//适量压行可以增强代码可读性(
	for(i=1;i<=m;i++)a[i].w?(addedge(a[i].u,a[i].v),addedge(a[i].u+n,a[i].v+n)):(addedge(a[i].u,a[i].v+n),addedge(a[i].u+n,a[i].v));//就是我上面阐述的内容
	for(i=1;i<=n*2;i++)if(!dfn[i])tarjan(i);
	for(flag1=1,i=1;i<=n;i++)if(scc[i]==scc[i+n])flag1=0;
	if(flag1)for(i=1;i<=n;i++){
		if(vis[i])continue;
		cnt1=cnt2=0;
		dfs(i);
		if(cnt1<cnt2){//看看 u,u' 哪个少就选哪个
			ans1+=cnt1;
			while(cnt1)s1[++s1[0]]=k1[cnt1--];
		}
		else{
			ans1+=cnt2;
			while(cnt2)s1[++s1[0]]=k2[cnt2--];
		}
		//此处不能为了节省代码写成这样:
		//if(cnt1>cnt2)swap(k1,k2),swap(cnt1,cnt2);
		//ans1+=cnt1;
		//while(cnt1)s1[++s1[0]]=k1[cnt1--];
		//这样就会导致复杂度变成 O(n^2),直接 T 飞
	}
	//-----------------这些是全部变成蓝色的情况-----------------
	memset(head,0,sizeof(head));kk=0;
	memset(dfn,0,sizeof(dfn));cnt=0;
	memset(low,0,sizeof(low));
	memset(scc,0,sizeof(low));scct=0;
	memset(s,0,sizeof(s));top=0;
	memset(vis,0,sizeof(vis));
	//-----------------一定要注意清空-----------------
	for(i=1;i<=m;i++)a[i].w?(addedge(a[i].u+n,a[i].v),addedge(a[i].u,a[i].v+n)):(addedge(a[i].u,a[i].v),addedge(a[i].u+n,a[i].v+n));
	for(i=1;i<=n*2;i++)if(!dfn[i])tarjan(i);
	for(flag2=1,i=1;i<=n;i++)if(scc[i]==scc[i+n])flag2=0;
	if(flag2)for(i=1;i<=n;i++){
		cnt1=cnt2=0;
		dfs(i);
		if(cnt1<cnt2){
			ans2+=cnt1;
			while(cnt1)s2[++s2[0]]=k1[cnt1--];
		}
		else{
			ans2+=cnt2;
			while(cnt2)s2[++s2[0]]=k2[cnt2--];
		}
	}
	//-----------------这些是全部变成红色的情况-----------------
	if(!flag1&&!flag2)return printf("-1"),0;//两种情况都无解那就无解了
	if(!flag1||(flag2&&s1[0]>s2[0]))swap(s1,s2);//如果第一种情况无解或者第一种情况没有第二种情况优,那就选第二种
	for(printf("%d\n",s1[0]),i=1;i<=s1[0];i++)printf("%d ",s1[i]);
	return 0;//完美撒花
}
int main(){
	return get();//主函数一行,主要可以方便多组测试数据或者开关 freopen,要不然还要把滚轮划上去注释掉，太麻烦了!
}
```
## 温馨提醒
> 如果有什么笔误或不足之类的，评论或私聊我，希望能帮到大家

## 谢谢--zhengjun

---

## 作者：Mihari (赞：2)

# 题目

[传送门](http://codeforces.com/problemset/problem/662/B)

# 题解

首先，意识到每一个连通块都是独立的，那么我们可以分每个联通块进行考虑.

对于每一个连通块，如果我们需要确定这个块的反转情况，我们只需要知道两个条件：

1. 某一个点的反转情况；
2. 所有边最终会被翻成什么颜色；

因为这两个情况的组合至多有 $2\times 2=4$ 种情况，而每个连通块，如果我们要确定其颜色，只需要 $dfs$ 一遍，复杂度 $\mathcal O(n)$，那么总共的复杂度为 $\mathcal O(4n)$，是可过的

所以，我们只需要对于每一个连通块，假定其中任意一点的反转情况，再枚举所有边染成的颜色，然后 $dfs$ 检查是否可行，选择最小的反转方法即可

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13387963.html
```


---

## 作者：Jerrywang09 (赞：0)

很有趣的题目。

考虑从最终状态出发。最后只可能全红色或者全蓝色，那么就枚举最终状态。

假设现在要求最后每条边都是蓝色，那么每个点只有翻转或者不翻转两种选择。一条边是否改变了颜色，决定了其两端的点的翻转情况是否相同。这是个非常经典的问题，可以使用 2-Sat、并查集、二分图染色等方法给出一种翻转方案。我的代码采用了二分图染色的方法，点会被分成两侧，其中点数较小的一侧翻转。

这题还有一些细节。图可以不连通，而且无解等情况判得要很仔细。

```cpp
// Title:  Graph Coloring
// Source: CF662B
// Author: Jerrywang
#include <cstdio>
#include <iostream>
#include <vector>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=100010, inf=0x3f3f3f3f;
using namespace std;

int n, m, c[N]; bool ok;
struct edge {int u, v, c;} e[N];
vector<pair<int, int>> g[N];
vector<int> vec[3], res[2];
void dfs(int u, int col)
{
    c[u]=col; vec[col].push_back(u);
    for(auto [v,w]:g[u])
    {
        if(w==1)
        {
            if(!c[v]) dfs(v, 3-col);
            else if(c[v]!=3-col) ok=0;
        }
        else
        {
            if(!c[v]) dfs(v, col);
            else if(c[v]!=col) ok=0;
        }
    }
}

void solve(int x)
{
    rep(i, 1, n) g[i].clear();
    rep(i, 1, m)
    {
        auto [u,v,c]=e[i];
        c=(c!=x);
        g[u].push_back({v, c}), g[v].push_back({u, c});;
    }
    ok=1; rep(i, 1, n) c[i]=0;
    rep(i, 1, n) if(!c[i])
    {
        vec[1].clear(), vec[2].clear();
        dfs(i, 1);
        if(vec[1].size()<vec[2].size())
        {
            for(int u:vec[1]) res[x].push_back(u);
        }
        else
        {
            for(int u:vec[2]) res[x].push_back(u);
        }
    }
    if(!ok)
    {
        rep(i, 1, n+1) res[x].push_back(i);
    }
}

int main()
{
#ifdef Jerrywang
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d%d", &n, &m);
    rep(i, 1, m)
    {
        int u, v; char c[2]; scanf("%d%d%s", &u, &v, c);
        e[i]={u, v, c[0]=='B'};
    }
    solve(0), solve(1);
    if(res[0].size()>n && res[1].size()>n)
        return puts("-1"), 0;
    if(res[0].size()<res[1].size())
    {
        printf("%d\n", res[0].size());
        for(int u:res[0]) printf("%d ", u);
    }
    else
    {
        printf("%d\n", res[1].size());
        for(int u:res[1]) printf("%d ", u);
    }

    return 0;
}
```

---

## 作者：Graphcity (赞：0)

首先整张图可以被划分为若干个连通块，且每个连通块之间是相互独立的。考虑钦定每条边最终的颜色。

对于每个连通块，找到它的任意一棵生成树，可以发现如果固定了钦定的颜色，以及根结点是否翻转，要满足生成树里面边的条件，那其它点的翻转状态也就唯一确定了。

对于生成树外的边，由于已经确定了每个结点是否翻转，直接进行判断即可。时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

struct Node{int frm,to,nxt,w;} Edge[Maxn*2+5];
int tot=1,Head[Maxn+5];
inline void Add(int x,int y,int z)
{
    Edge[++tot]=(Node){x,y,Head[x],z};
    Head[x]=tot;
}

int n,m,s,col[Maxn+5],ind[Maxn+5];
int rt[Maxn+5],vis[Maxn+5];
vector<int> v[Maxn+5],w[Maxn+5];
vector<int> chk[Maxn+5],ans[2];
vector<int> tmp[Maxn+5][2],cur[Maxn+5][2][2];

inline void Addedge(int p)
{
    int x=Edge[p].frm,y=Edge[p].to;
    v[x].push_back(p),v[y].push_back(p);
    ind[x]++,ind[y]++;
}
inline void dfs(int x)
{
    w[s].push_back(x);
    for(int i=Head[x];i;i=Edge[i].nxt)
    {
        int y=Edge[i].to;
        if(!col[y]) col[y]=s,Addedge(i),dfs(y);
    }
}
inline void Build()
{
    For(i,1,s) rt[i]=*w[i].begin();
    for(int i=2;i<=tot;i+=2) chk[col[Edge[i].to]].push_back(i);
}
inline int dfs2(int x,int f,int c,int typ,int id,int rev)
{
    int res=0;
    if(x!=rt[id] && c^vis[f]^typ)
    {
        vis[x]=1,res++;
        cur[id][typ][rev].push_back(x);
    }
    for(auto i:v[x])
    {
        int y=Edge[i].frm+Edge[i].to-x;
        if(y==f) continue;
        res+=dfs2(y,x,Edge[i].w,typ,id,rev);
    }
    return res;
}
inline int Count(int x,int typ,int rev)
{
    for(auto i:w[x]) vis[i]=0;
    int res=rev; vis[rt[x]]=rev;
    if(rev) cur[x][typ][rev].push_back(rt[x]);
    res+=dfs2(rt[x],0,0,typ,x,rev);
    for(auto i:chk[x]) if(Edge[i].w^typ^vis[Edge[i].frm]^vis[Edge[i].to]) return -1;
    return res;
}
inline int Solve(int x,int typ)
{
    int s1=Count(x,typ,0),s2=Count(x,typ,1);
    if(s1==-1 && s2==-1) return -1;
    if(s1==-1) return tmp[x][typ]=cur[x][typ][1],s2;
    if(s2==-1) return tmp[x][typ]=cur[x][typ][0],s1;
    if(s1<s2) return tmp[x][typ]=cur[x][typ][0],s1;
    else return tmp[x][typ]=cur[x][typ][1],s2;
}
inline int Find(int typ)
{
    int all=0;
    For(i,1,s)
    {
        int res=Solve(i,typ);
        if(res==-1) return -1;
        all+=res;
    }
    return all;
}
inline void Print(int typ)
{
    For(i,1,s) for(auto j:tmp[i][typ]) ans[typ].push_back(j);
    printf("%u\n",ans[typ].size());
    for(auto i:ans[typ]) printf("%d ",i);
    printf("\n");
}

int main()
{
    n=read(),m=read();
    For(i,1,m)
    {
        int a=read(),b=read(); char c; cin>>c;
        Add(a,b,c=='R'?0:1),Add(b,a,c=='R'?0:1);
    }
    For(i,1,n) if(!col[i]) col[i]=++s,dfs(i);
    Build();
    int flag0=Find(0),flag1=Find(1);
    if(flag0==-1 && flag1==-1) {printf("-1\n"); return 0;}
    if(flag0!=-1 && (flag1==-1 || flag0<flag1)) Print(0);
    else Print(1);
    return 0;
}
```

---

