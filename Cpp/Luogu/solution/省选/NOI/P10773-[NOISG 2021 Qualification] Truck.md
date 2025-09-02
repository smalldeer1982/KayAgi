# [NOISG 2021 Qualification] Truck

## 题目描述

有一棵树，每条边有两个权值 $D_i$ 和 $T_i$，给定 $Q$ 次操作。操作分为两种：

`0 x y t`：表示把 $x$ 和 $y$ 之间的一条道路的 $T_i$ 值改为 $t$。

`1 x y`：表示查询 $x$ 到 $y$ 的费用。

定义 $x$ 到 $y$ 的费用为：给定参数 $G$（对每组询问都相同），要求 $x$ 运送一些价值到 $y$，每经过一条权值为 $D_i$ 和 $T_i$ 的边，运送的价值会减少 $T_i$，然后会产生运送的价值的 $D_i$ 倍的费用。在运送到 $y$ 节点时，若运送到的价值刚好为 $G$，产生的费用就为 $x$ 到 $y$ 的费用。

你要对每组询问计算费用。由于费用可能比较大，请输出对 $10^9+7$ 取模的值。

## 说明/提示

#### 数据范围

**本题采用捆绑测试。**

Subtask0 为样例。

Subtask1（5 pts）只有查询操作，每个节点度不超过 $2$，且 $T_i=0$。

Subtask2（9 pts）只有查询操作，且 $T_i = 0$。

Subtask3（12 pts）只有查询操作，$D_i=1$，且所有 $T_i$ 相等。

Subtask4（17 pts）只有查询操作，且每个节点度不超过 $2$。

Subtask5（20 pts）每个节点度不超过 $2$。

Subtask6（18 pts）$N,Q \leq 5000$。

Subtask7（19 pts）无特殊限制。

数据保证 $2 \leq N \leq 10^5$，$1 \leq Q \leq 10^5$，$1 \leq A_i,B_i \leq N$，$1 \leq D_i,G \leq 10^9$，$0 \leq T_i \leq 10^9$。

## 样例 #1

### 输入

```
6 2
1 2 2 1
2 3 1 2
2 4 2 3
4 5 2 2
4 6 1 4
3
1 3 6
0 4 5 5
1 2 5
```

### 输出

```
23
18```

## 样例 #2

### 输入

```
4 3
1 2 3 0
2 3 1 0
3 4 4 0
1
1 1 4```

### 输出

```
24```

# 题解

## 作者：yzljy (赞：4)

UPD：增加和修改了一些内容，辛苦管理员了。

[题目链接](https://www.luogu.com.cn/problem/P10773)

## 前言

随机跳题跳到的。我并不会题解区另外两篇大佬的做法，我用了一种相对更加复杂的拆式子。似乎这种拆式子的方法更为通用一些？比如 [疯狂动物城](https://www.luogu.com.cn/problem/P7671) 也可以用类似的拆法实现。  
题意题面已经很简洁了，注意一下是**先减少**价值，**再产生**费用就行了。  
到我的博客也许能有更优的阅读体验：[这里](https://yzljyawa.github.io/OI/%E6%B4%9B%E8%B0%B7-P10773-NOISG-2021-Qualification-Truck/)

## 思路

首先我们令 $dis(x,y)$ 表示从 $x$ 到 $y$ 经过的边的 $T_{i}$ 和。$D_{i}$ 在边上不好做，我们使用边权转点权，将一条边的 $D_{i}$ 的值，放到这条边相连的两个点中，深度更深的那个上面。（这个是很常见的边权转点权的方法）  

记 $S(x,y)$ 表示从 $x$ 到 $y$ 的点集。  
根据题意，我们可以写出这样的式子：  

$$
\begin{aligned}
	ans=&\left(\sum_{i\in S(x,\operatorname{LCA}(x,y)),i\not=\operatorname{LCA}(x,y)}D_{i}(dis(fa_{i},y)+G)\right)+\\
	&\left(\sum_{i\in S(\operatorname{LCA}(x,y),y),i\not=\operatorname{LCA}(x,y)}D_{i}(dis(i,y)+G)\right)\\
\end{aligned}
$$

没有看懂式子的话，可以画一下图，模拟一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/fsgh0xda.png)

看着十分吓人，我们可以先将 $G$ 提出来，再将 $dis(x,y)$ 展开成 $dep_{x}+dep_{y}-2dep_{\operatorname{LCA}(x,y)}$。  
（$dep_i$ 也就是从 $1$ 号点到 $i$ 号点的边的 $T$ 和）

 + 对于 $i\in S(x,\operatorname{LCA}(x,y))$，都有 $\operatorname{LCA}(i,y)=\operatorname{LCA}(x,y)$。  
 + 对于 $i\in S(\operatorname{LCA}(x,y),y)$ 都有 $\operatorname{LCA}(i,y)=i$。

那么我们便可以写成这样的式子：

$$
\begin{aligned}
	ans=&\left(G\sum_{i\in S(x,y),i\not=\operatorname{LCA}(x,y)}D_{i}\right)+\\
	&\left(\sum_{i\in S(x,\operatorname{LCA}(x,y)),i\not=\operatorname{LCA}(x,y)}D_{i}(dep_{fa_{i}}+dep_{y}-2dep_{\operatorname{LCA}(x,y)})\right)+\\
	&\left(\sum_{i\in S(\operatorname{LCA}(x,y),y),i\not=\operatorname{LCA}(x,y)}D_{i}(dep_{y}-dep_{i})\right)
\end{aligned}
$$

展开化简一下，得到：

$$
\begin{aligned}
	ans=&\left(\left(G+dep_{y}\right)\sum_{i\in S(x,y),i\not=LCA(x,y)}D_{i}\right)+\\
	&\left(\sum_{i\in S(x,LCA(x,y)),i\not=LCA(x,y)}D_{i}dep_{fa_{i}}\right)-\\
	&\left(2dep_{LCA(x,y)}\sum_{i\in S(x,LCA(x,y)),i\not=LCA(x,y)}D_{i}\right)-\\
	&\left(\sum_{i\in S(LCA(x,y),y),i\not=LCA(x,y)}D_{i}dep_{i}\right)\\
\end{aligned}
$$

我们发现这些都是可以使用线段树来维护的。  
我们需要维护的也就是：  

 + 区间 $D_{i}$ 和  
 + 区间 $dep_{i}$ 和  
 + 区间 $D_{i}dep_{i}$ 和  
 + 区间 $D_{i}dep_{fa_{i}}$ 和  

第一个是不变的，可以用一个前缀和简单实现（写线段树也可以）。  
第二个我们发现和 $T_{i}$ 有关，而修改一条边 $x$ 到 $y$（设 $y$ 点更深）的边权为 $t$ 后，会对 $y$ 及其子树的 $dep_{i}$ 一起增加 $t-T_{i}$（$T_{i}$ 为改之前的边权）。对原树进行树剖重新标号后，这是一个区间加的操作。  
第三个可以看作维护 $kx,x=\sum dep_{i}$，也就是增加倍数的操作。  
第四个和第三个一样，因为我们每次修改的时候，会对一整棵子树进行修改，所以 $dep_{fa_{i}}$ 没变的只有这棵子树的根（也就是第二点中提到的 $y$），特殊处理一下就行了。

那么到这里就结束了，维护起来还是有一点麻烦的。

## 代码

参考一下就好啦。

```cpp
// Problem: P10773 [NOISG 2021 Qualification] Truck
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10773
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+10;
const int mod=1e9+7;
const int inf_int=0x7f7f7f7f;
const long long inf_long=0x7f7f7f7f7f7f7f7f;
const double eps=1e-9;
char Buf[1<<23],*P1=Buf,*P2=Buf;
#define getchar() (P1==P2&&(P2=(P1=Buf)+fread(Buf,1,1<<23,stdin),P1==P2)?EOF:*P1++)
template<typename type>
inline void read(type &x){
	x=0;
	bool f=false;
	char ch=getchar();
	while(ch<'0'||ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	if(f) x=-x;
}
template<typename type,typename... args>
inline void read(type &x,args&... y){
	read(x),read(y...);
}

int n,g,k,q,cnt,head[MAXN],Dep[MAXN],val[MAXN],hson[MAXN]；
int dfsnum[MAXN],dfsnod[MAXN],top[MAXN],fa[MAXN],dep[MAXN],siz[MAXN];
map<pair<int,int>,int> mp;
struct node{
	int to,next,val1,val2;
}edge[MAXN<<1];
struct node2{
	int l,r,val1,val2,val3,val4,lazy;
}tree[MAXN<<2];

void build(int u,int v,int d,int t){
	edge[++k].to=v;
	edge[k].next=head[u];
	edge[k].val1=t;
	edge[k].val2=d;
	head[u]=k;
}

void dfs(int u,int f){
	siz[u]=1;
	int maxsiz=0;
	for(int i=head[u];i;i=edge[i].next){
		int v=edge[i].to;
		if(v==f) continue;
		fa[v]=u;
		dep[v]=(dep[u]+edge[i].val1)%mod;
		Dep[v]=Dep[u]+1;
        //因为T_i可能为0，所以额外记录一下深度。
		val[v]=edge[i].val2;
		dfs(v,u);
		siz[u]+=siz[v];
		if(maxsiz<siz[v]){
			maxsiz=siz[v];
			hson[u]=v;
		}
	}
}

void dfs2(int u,int f){
	top[u]=f;
	dfsnum[u]=++cnt;
	dfsnod[cnt]=u;
	if(hson[u]==0) return;
	dfs2(hson[u],f);
	for(int i=head[u];i;i=edge[i].next){
		int v=edge[i].to;
		if(v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
}

void pushup(int id){
	tree[id].val1=(tree[id*2].val1+tree[id*2+1].val1)%mod;
	tree[id].val2=(tree[id*2].val2+tree[id*2+1].val2)%mod;
	tree[id].val3=(tree[id*2].val3+tree[id*2+1].val3)%mod;
	tree[id].val4=(tree[id*2].val4+tree[id*2+1].val4)%mod;
}

void pushdown(int id){
	if(tree[id].lazy==0) return;
	tree[id*2].val2+=tree[id].lazy;
	tree[id*2].val3+=tree[id*2].val1*(tree[id].lazy%mod)%mod;
	tree[id*2].val4+=tree[id*2].val1*(tree[id].lazy%mod)%mod;
	tree[id*2].lazy+=tree[id].lazy;
	tree[id*2].val2%=mod;
	tree[id*2].val3%=mod;
	tree[id*2].val4%=mod;
	tree[id*2+1].val2+=tree[id].lazy;
	tree[id*2+1].val3+=tree[id*2+1].val1*(tree[id].lazy%mod)%mod;
	tree[id*2+1].val4+=tree[id*2+1].val1*(tree[id].lazy%mod)%mod;
	tree[id*2+1].lazy+=tree[id].lazy;
	tree[id*2+1].val2%=mod;
	tree[id*2+1].val3%=mod;
	tree[id*2+1].val4%=mod;
	tree[id].lazy=0;
}

void build_tree(int id,int l,int r){
	tree[id].l=l;
	tree[id].r=r;
	tree[id].lazy=0;
	tree[id].val1=tree[id].val2=tree[id].val3=tree[id].val4=0;
	if(l==r){
		tree[id].val1=val[dfsnod[l]];
		tree[id].val2=dep[dfsnod[l]];
		tree[id].val3=tree[id].val1*dep[dfsnod[l]]%mod;
		tree[id].val4=tree[id].val1*dep[fa[dfsnod[l]]]%mod;
		return;
	}
	int mid=(l+r)>>1;
	build_tree(id*2,l,mid);
	build_tree(id*2+1,mid+1,r);
	pushup(id);
}

void update(int id,int l,int r,int L,int R,int z,bool kind){
	if(r<L||R<l) return;
	if(L<=l&&r<=R){
		if(kind) tree[id].val2=(tree[id].val2+z)%mod;
		if(kind) tree[id].val3=(tree[id].val3+tree[id].val1*z%mod)%mod;
		tree[id].val4=(tree[id].val4+tree[id].val1*z%mod)%mod;
		if(kind) tree[id].lazy+=z;
		return;
	}
	pushdown(id);
	int mid=(l+r)>>1;
	if(L<=mid) update(id*2,l,mid,L,R,z,kind);
	if(R>mid) update(id*2+1,mid+1,r,L,R,z,kind);
	pushup(id);
}

int query(int id,int l,int r,int L,int R,int type){
	if(r<L||R<l) return 0;
	if(L<=l&&r<=R){
		if(type==1) return tree[id].val1;
		if(type==2) return tree[id].val2;
		if(type==3) return tree[id].val3;
		if(type==4) return tree[id].val4;
	}
	pushdown(id);
	int res=0,mid=(l+r)>>1;
	if(L<=mid){
		int val=query(id*2,l,mid,L,R,type);
		res=(res+val)%mod;
	}
	if(R>mid){
		int val=query(id*2+1,mid+1,r,L,R,type);
		res=(res+val)%mod;
	}
	return res;
}

int ask(int x,int y,int type){
	int res=0;
	while(top[x]!=top[y]){
		if(Dep[top[x]]<Dep[top[y]]) swap(x,y);
		res=(res+query(1,1,cnt,dfsnum[top[x]],dfsnum[x],type))%mod;
		x=fa[top[x]];
	}
	if(Dep[x]<Dep[y]) swap(x,y);
	res=(res+query(1,1,cnt,dfsnum[y],dfsnum[x],type))%mod;
	return res;
}

int lca(int x,int y){
	while(top[x]!=top[y]){
		if(Dep[top[x]]<Dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if(Dep[x]<Dep[y]) swap(x,y);
	return y;
}

int work(int x,int y){
    //照着式子计算即可。
	int res=0,lc=lca(x,y);
	int sum=(g+query(1,1,cnt,dfsnum[y],dfsnum[y],2))%mod;
	int val=(ask(x,y,1)-query(1,1,cnt,dfsnum[lc],dfsnum[lc],1)+mod)%mod;
	res=(res+sum*val%mod)%mod;
	res=(res+ask(x,lc,4)-query(1,1,cnt,dfsnum[lc],dfsnum[lc],4)+mod)%mod;
	res-=2ll*query(1,1,cnt,dfsnum[lc],dfsnum[lc],2)%mod*
    ((ask(x,lc,1)-query(1,1,cnt,dfsnum[lc],dfsnum[lc],1)+mod)%mod)%mod;
	res=(res+mod)%mod;
	res-=(ask(lc,y,3)-query(1,1,cnt,dfsnum[lc],dfsnum[lc],3)+mod)%mod;
	res=(res+mod)%mod;
	return (res+mod)%mod;
}

signed main(){
	read(n,g);
	for(int i=1;i<n;i++){
		int a,b,d,t;
		read(a,b,d,t);
		build(a,b,d,t);
		build(b,a,d,t);
		mp[make_pair(a,b)]=mp[make_pair(b,a)]=t;
	}
	dfs(1,1);
	dfs2(1,1);
	build_tree(1,1,cnt);
	read(q);
	for(int i=1;i<=q;i++){
		int opt,x,y,t;
		read(opt);
		if(opt==0){
			read(x,y,t);
			if(Dep[x]<Dep[y]) swap(x,y);
			int val=t-mp[make_pair(x,y)];
			mp[make_pair(x,y)]=mp[make_pair(y,x)]=t;
			update(1,1,cnt,dfsnum[x],dfsnum[x]+siz[x]-1,val,true);
			update(1,1,cnt,dfsnum[x],dfsnum[x],-val,false);
            //只有x这个点的父亲没有修改，单独处理。
		}
		if(opt==1){
			read(x,y);
			cout<<work(x,y)<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：sintle (赞：2)

## 题目链接

- [洛谷 P10773 [NOISG2021 qualification] Truck](https://www.luogu.com.cn/problem/P10773)

## 解题思路

首先，我们注意到可以把运输的过程反过来，从 $y$ 点开始，运送的价值初始值为 $G$，每走过一条边就产生一次代价，并将运送的价值加上这条边的 $T$。

于是我们得到如下结论：

若有三个点 $x,y,z$ 满足 $y$ 在从 $x$ 到 $z$ 的简单路径上，

令
$val_{a,b}$ 为从点 $a$ 到点 $b$ 的代价，
$sumt_{a,b}$ 为从点 $a$ 到点 $b$ 的边权 $T$ 之和，$sumd_{a,b}$ 为从点 $a$ 到点 $b$ 的边权 $D$ 之和。

则有：

$$
val_{x,z}=val_{x,y}+val_{y,z}+sumt_{x,y} \times sumd_{y,z}
$$

于是我们就可以用树链剖分加线段树维护答案。

## 参考代码（内附注释）

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 200005 , mod = 1000000007;
int n , G , Q;
int son[N] , dep[N] , siz[N] , fa[N] , top[N] , dfn[N] , pos[N] , tot;//树剖要用的数组
int beft[N] , befd[N];//化边为点

struct edge
{
    int to , D , T;//存边
};
vector <edge> g[N];

struct seg
{
    int sumd , sumt , up , down;//sumd和sumt含义如上，up表示在这个区间内从下往上走的代价，down表示在这个区间内从上往下走的代价
};
seg s[N << 1] , null;//null表示一个空点

seg operator +(seg x , seg y)
{
    seg res;
    res.down = (x.down + y.down + (x.sumt * y.sumd) % mod) % mod;
    res.up = (x.up + y.up + (x.sumd * y.sumt) % mod) % mod;
    res.sumd = (x.sumd + y.sumd) % mod;
    res.sumt = (x.sumt + y.sumt) % mod;
    return res;
}//将区间合并重载为加法

void dfs1(int u , int pre)//建树+预处理 
{
    fa[u] = pre;
    if(u == 1)
    {
        fa[u] = u;
    }
    siz[u] = 1;
    dep[u] = dep[pre] + 1;
    for(auto [v , d , t] : g[u])
    {
        if(v == pre)
        {
            continue;
        }
        befd[v] = d;
        beft[v] = t;
        dfs1(v , u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]])
        {
            son[u] = v;
        }
    }
}

void dfs2(int u , int pre)//树剖
{
    dfn[u] = ++tot;
    pos[tot] = u;
    if(!son[u])
    {
        return;
    }
    top[son[u]] = top[u];
    dfs2(son[u] , u);
    for(auto [v , d , t] : g[u])
    {
        if(v == pre || v == son[u])
        {
            continue;
        }
        top[v] = v;
        dfs2(v , u);
    }
}

void build(int num , int l , int r)//建线段树
{
    if(l == r)
    {
        s[num].sumd = befd[pos[l]];
        s[num].sumt = beft[pos[r]];
        return;
    }
    int mid = (l + r) >> 1;
    build(num << 1 , l , mid);
    build(num << 1 | 1 , mid + 1 , r);
    s[num] = s[num << 1] + s[num << 1 | 1];
}

void update(int num , int l , int r , int x , int val)//更新点权
{
    if(l > x || r < x)
    {
        return;
    }
    if(l == x && r == x)
    {
        s[num].sumt = val;
        return;
    }
    int mid = (l + r) >> 1;
    update(num << 1 , l , mid , x , val);
    update(num << 1 | 1 , mid + 1 , r , x , val);
    s[num] = s[num << 1] + s[num << 1 | 1];
}

void change(int x , int y , int t)//更改操作
{
    if(dep[x] > dep[y])
    {
        swap(x , y);
    }
    update(1 , 1 , n , dfn[y] , t);
}

seg get(int num , int l , int r , int x , int y)//线段树上区间查找 
{
    if(l > y || r < x)
    {
        return null;
    }
    if(l >= x && r <= y)
    {
        return s[num];
    }
    int mid = (l + r) >> 1;
    return get(num << 1 , l , mid , x , y) + get(num << 1 | 1 , mid + 1 , r , x , y);
}

int query(int x , int y)//查询操作
{
    int res1 = 0 , nowt = 0 , res2 = 0 , nowd = 0 , totd = 0;
    while(top[x] != top[y])
    {
        if(dep[top[x]] >= dep[top[y]])
        {
            seg awa = get(1 , 1 , n , dfn[top[x]] , dfn[x]);
            totd = (totd + awa.sumd) % mod;
            res1 = (res1 + (nowt * awa.sumd) % mod + awa.up) % mod;
            nowt = (nowt + awa.sumt) % mod;
            x = fa[top[x]];
        }
        else
        {
            seg awa = get(1 , 1 , n , dfn[top[y]] , dfn[y]);
            totd = (totd + awa.sumd) % mod;
            res2 = (res2 + (nowd * awa.sumt) % mod + awa.down) % mod;
            nowd = (nowd + awa.sumd) % mod;
            y = fa[top[y]];
        }
    }
    if(x != y)
    {
        if(dep[x] >= dep[y])
        {
            seg awa = get(1 , 1 , n , dfn[y] + 1 , dfn[x]);
            totd = (totd + awa.sumd) % mod;
            res1 = (res1 + (nowt * awa.sumd) % mod + awa.up) % mod;
            nowt = (nowt + awa.sumt) % mod;
        }
        else
        {
            seg awa = get(1 , 1 , n , dfn[x] + 1 , dfn[y]);
            totd = (totd + awa.sumd) % mod;
            res2 = (res2 + (nowd * awa.sumt) % mod + awa.down) % mod;
            nowd = (nowd + awa.sumd) % mod;
        }
    }
    res1 = (res1 + (nowt * nowd) % mod + res2) % mod;
    return (res1 + (G * totd) % mod) % mod;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    null.down = 0;
    null.sumd = 0;
    null.sumt = 0;
    null.up = 0;//初始化
    cin >> n >> G;
    for(int i = 1 , a , b , D , T ; i < n ; i++)
    {
        cin >> a >> b;
        edge e;
        e.to = b;
        cin >> e.D >> e.T;
        g[a].push_back(e);
        e.to = a;
        g[b].push_back(e);
    }
    dfs1(1 , 0);
    top[1] = 1;
    dfs2(1 , 0);
    build(1 , 1 , n);//预处理
    cin >> Q;
    int op , x , y , t;
    while(Q--)
    {
        cin >> op >> x >> y;
        if(op)
        {
            cout << query(y , x) << endl;//处理询问
        }
        else
        {
            cin >> t;
            change(x , y , t);//处理更改
        }
    }
    return 0;
}
```

## 附：谴责搬题人

充满了血泪的控诉，详情请看[原帖](https://www.luogu.com.cn/discuss/992761)。

---

## 作者：xiangixuan (赞：1)

一道较难的树剖题
~~为什么讨论区建议降蓝~~
### 一、转化问题
> 从 $x$ 节点运送到 $y$ 节点，每经过一条边，价值会减少 $T_i$ ，产生价值的 $D_i$ 倍的费用，且运送到时价值刚好为 $G$ 的费用.

题目中这个条件不好处理，将其转化为：
> 从 $y$ 节点运送到 $x$ 节点，每经过一条边，产生价值的 $D_i$ 倍的费用，价值会增加 $T_i$ ，且初始价值为 $G$ 的费用.

### 二、推式子

从 $x$ 节点运送到 $y$ 节点，且初始价值为 $v$，其产生的费用：
- $cost_v = cost_0 + v \times S_D$

其中 $cost_0$ 表示初始价值为 $0$ 时从 $x$ 节点运送到 $y$ 节点产生的费用，$S_D$ 表示从 $x$ 到 $y$ 的 $D_i$ 之和.

证明：在经过每个节点时，其价值都比初始是 $0$ 的情况下大 $v$ ，因此每个节点产生的费用都增加了 $D_i \times v$.

由此推出从 $x$ 节点经过 $y$ 节点再运送到 $z$ 节点总共产生的费用：

- $cost_{xz} = cost_{xy} + cost_{yz} + S_{T_{xy}} \times S_{D_{yz}}$

其中 $S_{T_{xy}}$ 从 $x$ 到 $y$ 的 $T_i$ 之和，$S_{D_{yz}}$ 表示从 $y$ 到 $z$ 的 $D_i$ 之和.

以上式子线段树加重链剖分可以直接维护.
### 三、实现
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100005
#define P 1000000007
using namespace std;

int n, g, q, D[N], T[N];

struct edge{int to, d, t, nex; } edge[2*N];
int head[N], tot;
void add(int x, int y, int d, int t) {
	edge[++tot]={y, d, t, head[x]};
	head[x]=tot;
}

int siz[N], par[N], dep[N], son[N];
void dfs1(int x, int f) {
	siz[x]=1, par[x]=f, dep[x]=dep[f]+1;
	for(int i=head[x]; i; i=edge[i].nex) {
		int y=edge[i].to, d=edge[i].d, t=edge[i].t;
		if(y==f) continue;
		D[y]=d, T[y]=t;
		dfs1(y, x);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]]) son[x]=y;
	}
}
int dfn[N], top[N], inv[N], tim;
void dfs2(int x, int t) {
	dfn[x]=++tim, top[x]=t, inv[dfn[x]]=x;
	if(!son[x]) return;
	dfs2(son[x], t);
	for(int i=head[x]; i; i=edge[i].nex) {
		int y=edge[i].to;
		if(y==par[x] || y==son[x]) continue;
		dfs2(y, y);
	}
}

struct node{int lft, rgh, sumd, sumt; };
/*
lft表示从左向右走过区间，初始价值为0的费用
rgh表示从右向左走过区间，初始价值为0的费用
*/
void calc(node x, node y, node &z) {
	z.lft=((x.lft+y.lft)%P+x.sumt*y.sumd%P)%P;
	z.rgh=((x.rgh+y.rgh)%P+x.sumd*y.sumt)%P;
	z.sumd=(x.sumd+y.sumd)%P;
	z.sumt=(x.sumt+y.sumt)%P;
}

class segmentTree{
	private:
		node tr[N<<2];
		#define l(p) tr[p].lft
		#define r(p) tr[p].rgh
		#define d(p) tr[p].sumd
		#define t(p) tr[p].sumt
		#define mid ((s+t)>>1)
		int ls(int p) {return p<<1; }
		int rs(int p) {return p<<1|1; }
		void pushUp(int p) {
			calc(tr[ls(p)], tr[rs(p)], tr[p]);
		}
	public:
		void build(int p, int s, int t) {
			if(s==t) {
				d(p)=D[inv[s]], t(p)=T[inv[s]];
				return;
			}
			build(ls(p), s, mid);
			build(rs(p), mid+1, t);
			pushUp(p);
		}
		void modify(int p, int s, int t, int x, int d) {
			if(s==t) {t(p)=d; return; }
			if(x<=mid) modify(ls(p), s, mid, x, d);
			else modify(rs(p), mid+1, t, x, d);
			pushUp(p);
		}
		node query(int p, int s, int t, int l, int r) {
			if(l>r) return {0, 0, 0, 0};
			if(l<=s && t<=r) return tr[p];
			node x={0, 0, 0, 0}, y={0, 0, 0, 0}, z;
			if(l<=mid) x=query(ls(p), s, mid, l, r);
			if(r>mid) y=query(rs(p), mid+1, t, l, r);
			calc(x, y, z);
			return z;
		}
} seg;

void modify(int x, int y, int d) {
	seg.modify(1, 1, n, max(dfn[x], dfn[y]), d);
}

int query(int x, int y) {
	swap(x, y); //转化问题
	
	node ansx={0, 0, 0, 0}, ansy={0, 0, 0, 0};
	bool flag=0;
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]])
			swap(x, y), swap(ansx, ansy), flag^=1;
		calc(seg.query(1, 1, n, dfn[top[x]], dfn[x]), ansx, ansx);
		x=par[top[x]];
	}
	if(dep[x]<dep[y])
		swap(x, y), swap(ansx, ansy), flag^=1;
	
	calc(seg.query(1, 1, n, dfn[y]+1, dfn[x]), ansx, ansx);
	if(flag) swap(x, y), swap(ansx, ansy);
	
	int ans=((((ansx.sumd+ansy.sumd)%P*g%P+ansx.rgh)%P+ansy.lft)%P+ansx.sumt*ansy.sumd%P)%P;
	//从y节点走到x节点，并且初始值为g的花费
	return ans;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> g;
	int x, y, d, t;
	for(int i=1; i<n; ++i) {
		cin >> x >> y >> d >>t;
		add(x, y, d, t);
		add(y, x, d, t);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	seg.build(1, 1, n);
	
	cin >> q;
	int opt;
	while(q--) {
		cin >> opt >> x >> y;
		if(opt) cout << query(x, y) << '\n';
		else {
			cin >> t;
			modify(x, y, t);
		}
	}
	return 0;
}
```
### 四、注意事项
- `query`函数中`calc(seg.query(1, 1, n, dfn[top[x]], dfn[x]), ansx, ansx);` 不要写反成 `calc(ansx, seg.query(1, 1, n, dfn[top[x]], dfn[x]), ansx);`.
- `node`节点记得初始化为`{0, 0, 0, 0}`.

---

## 作者：Wei_Han (赞：0)

考虑在线段树上每个点维护以 $0$ 开始走完当前区间的权值，合并很简单，记 $val$ 为区间内答案，则 $val = val_l + val_r + t_l\times d_r$ 其中 $t_l$ 和 $d_r$ 分别表示两个区间内 $t$ 和 $d$ 的总和。

之后把边权转点权，然后扔到线段树上直接搞就好了，注意由于是路径询问，两段路径的方向不同，所以线段树上需要维护两个不同方向的答案，链查询时注意合并方向，单点修改不影响，复杂度 $O(n \log^2 n)$。

更多细节可以参照代码，对于链合并部分建议手动模拟一下更方便调试。

```cpp
const ll N=1e6+5,M=2e4+5,mod=1e9+7;
ll n,d[N],t[N],G,dep[N],fa[N],son[N],id[N],w[N],siz[N],top[N],cnt;
vector<pii> g[N];
struct SGT{ll l,r,val1,val2,sumd,sumt;}tree[N<<2];
#define rt tree[root]
#define ls tree[root<<1]
#define rs tree[root<<1|1]
inline void ad(ll &x,ll y,ll z=0,ll zz=0,ll zzz=0){x=((y+z+zz+zzz)%mod+mod)%mod;}
inline void merge(SGT &a,SGT b,SGT c)
{
	ad(a.sumd,b.sumd,c.sumd),ad(a.sumt,b.sumt,c.sumt);
	ad(a.val1,b.val1,c.val1,b.sumt*c.sumd);
	ad(a.val2,b.val2,c.val2,b.sumd*c.sumt);
}
inline void pushup(ll root){merge(rt,ls,rs);}
inline void build(ll root,ll l,ll r){rt.l=l,rt.r=r;if(l==r) return rt.sumd=d[w[l]],rt.sumt=t[w[l]],void();ll mid=l+r>>1;build(root<<1,l,mid),build(root<<1|1,mid+1,r);pushup(root);}
inline void upd(ll root,ll x,ll k){ll l=rt.l,r=rt.r;if(l==r) return rt.sumt=k,void();ll mid=l+r>>1;if(x<=mid) upd(root<<1,x,k);else upd(root<<1|1,x,k);pushup(root);}
inline SGT ask(ll root,ll x,ll y){if(y<x) return {0,0,0,0,0,0};ll l=rt.l,r=rt.r;if(x<=l&&y>=r) return rt;ll mid=l+r>>1;if(x>mid) return ask(root<<1|1,x,y);if(y<=mid) return ask(root<<1,x,y);SGT c={0,0,0,0,0,0};return merge(c,ask(root<<1,x,y),ask(root<<1|1,x,y)),c;}
inline void dfs1(ll x,ll fat,ll depth){fa[x]=fat,siz[x]=1,dep[x]=depth;for(pii vv:g[x]){ll y=vv.fi,D=vv.se.fi,T=vv.se.se;if(y==fa[x]) continue;dfs1(y,x,depth+1);siz[x]+=siz[y],d[y]=D,t[y]=T;if(siz[y]>siz[son[x]]) son[x]=y;}}
inline void dfs2(ll x,ll nowtop){top[x]=nowtop,id[x]=++cnt,w[cnt]=x;if(!son[x]) return;dfs2(son[x],nowtop);for(pii vv:g[x]) if(vv.fi!=fa[x]&&vv.fi!=son[x]) dfs2(vv.fi,vv.fi);}
inline ll ask_chain(ll x,ll y)
{
	SGT ans1={0,0,0,0,0,0},ans2={0,0,0,0,0,0};ll fl=0;
	while(top[x]^top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y),swap(ans1,ans2),fl^=1;
		merge(ans1,ask(1,id[top[x]],id[x]),ans1);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y),swap(ans1,ans2),fl^=1;
	merge(ans1,ask(1,id[y]+1,id[x]),ans1);
	if(fl) swap(x,y),swap(ans1,ans2);
	ll ans=0;ad(ans,ans1.val2,ans2.val1,ans1.sumt*ans2.sumd%mod,G*(ans1.sumd+ans2.sumd)%mod);return ans;
}
signed main(){
	read(n);read(G);ll a,b,D,T;fo(1,i,n-1) read(a),read(b),read(D),read(T),g[a].pb({b,{D,T}}),g[b].pb({a,{D,T}});
	dfs1(1,0,1),dfs2(1,1);
	build(1,1,n);
	ll q;read(q);
	fo(1,i,q)
	{
		ll op,x,y,k;
		read(op),read(x),read(y);
		if(!op) read(k),dep[x]<dep[y]?upd(1,id[y],k):upd(1,id[x],k);
		else wr(ask_chain(y,x)),pr;
	}
	return 0;
}
``````

---

## 作者：Mrkn_chenyx12 (赞：0)

## 解题思路

首先，看到树上路径，第一眼想到树链剖分，本题解默认你已经掌握基于边的树链剖分。

如果我们倒着走，从终点走到起点，不难发现每走一段就是产生 $D_i\cdot G$ 的费用并将 $G$ 增加 $T_i$。假设此后都是倒着走。

由于在走的过程中 $G$ 不断变化，故计算经过若干条边的费用时，需要引入额外费用 $x$ 表示走的过程中由于 $G$ 的变化产生的费用，则走过这些边的总代价为 $D_{sum}\cdot G+x$。可以得知依次走过两条链 $a,b$ 的额外费用为 $x_a+x_b+T_a\cdot D_b$，而走过单段没有额外费用。实现时，由于一条链可以以两种方向走过，额外费用也要计算两份分别对应两种方向。

然后，通过树链剖分实现即可。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll Mod = 1e9 + 7;

map<pair<int, int>, int> rev;
int n, q, logn;
ll g;
int dfn[100024], hson[100024], top[100024], fa[24][100024], dfc;
int ecnt, dep[100024], ev[200024], ex[200024], es[100024], rdfn[100024];
ll et[200024], ed[200024], pt[100024], pd[100024];

// 第一轮 DFS
int dfsr1(int u, int f) {
    int w = 1, hw = -1, tmp;
    for (int i = es[u]; i; i = ex[i]) {
        int v = ev[i];
        if (v == f) continue;
        dep[v] = dep[u] + 1;
        fa[0][v] = u;
        pt[v] = et[i];
        pd[v] = ed[i];
        rev[{u, v}] = rev[{v, u}] = v;
        tmp = dfsr1(v, u);
        w += tmp;
        if (tmp > hw) {
            hw = tmp;
            hson[u] = v;
        }
    }
    return w;
}

// 第二轮 DFS
void dfsr2(int u, int f) {
    rdfn[dfc] = u;
    dfn[u] = dfc++;
    if (!hson[u]) return;
    top[hson[u]] = top[u];
    dfsr2(hson[u], u);
    for (int i = es[u]; i; i = ex[i]) {
        int v = ev[i];
        if (v == f || v == hson[u]) continue;
        top[v] = v;
        dfsr2(v, u);
    }
}


// 加边
inline void add(int u, int v, int d, int t) {
    ev[++ecnt] = v;
    ex[ecnt] = es[u];
    et[ecnt] = t;
    ed[ecnt] = d;
    es[u] = ecnt;
    ev[++ecnt] = u;
    ex[ecnt] = es[v];
    et[ecnt] = t;
    ed[ecnt] = d;
    es[v] = ecnt;
}

struct Node {
    ll t, d, px, nx;
} seg[400024];

// 合并答案
inline Node pushup(const Node l, const Node r) {
    return {(l.t + r.t) % Mod, (l.d + r.d) % Mod, (l.px + r.px + l.t * r.d) % Mod, (l.nx + r.nx + l.d * r.t) % Mod};
}

// 单点修改
void modify(int id, int l, int r, int u, ll v) {
    if (l == r) {
        seg[id].t = v;
        return;
    }
    int mid = l + r >> 1;
    if (u <= mid) modify(id << 1, l, mid, u, v);
    else modify(id << 1 | 1, mid + 1, r, u, v);
    seg[id] = pushup(seg[id << 1], seg[id << 1 | 1]);
}

// 区间查询
Node query(int id, int l, int r, int L, int R) {
    if (l > R || r < L) return {0, 0, 0, 0};
    if (L <= l && r <= R) return seg[id];
    int mid = l + r >> 1;
    return pushup(query(id << 1, l, mid, L, R), query(id << 1 | 1, mid + 1, r, L, R));
}

// 建树
void build(int id, int l, int r) {
    if (l == r) {
        seg[id] = {pt[rdfn[l]], pd[rdfn[l]], 0, 0};
        return;
    }
    int mid = l + r >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    seg[id] = pushup(seg[id << 1], seg[id << 1 | 1]);
}

// 查询 LCA 下面的点
pair<int, int> sublca(int a, int b) {
    if (dep[a] > dep[b]) {
        for (int i = logn; i >= 0 && dep[a] > dep[b]; i--) {
            if (dep[a] - dep[b] > (1 << i)) a = fa[i][a];
        }
        if (fa[0][a] == b) {
            return {a, -1};
        }
        a = fa[0][a];
    }
    else if (dep[a] < dep[b]) {
        for (int i = logn; i >= 0 && dep[a] < dep[b]; i--) {
            if (dep[b] - dep[a] > (1 << i)) b = fa[i][b];
        }
        if (fa[0][b] == a) {
            return {-1, b};
        }
        b = fa[0][b];
    }
    if (a == b) return {-1, -1};
    for (int i = logn; i >= 0; i--) if (fa[i][a] != fa[i][b]) {
        a = fa[i][a];
        b = fa[i][b];
    }
    return {a, b};
}

// 查询链
Node qchain(int u, int d) {
    Node res = {0, 0, 0, 0};
    while (dep[top[d]] > dep[u]) {
        res = pushup(query(1, 1, n - 1, dfn[top[d]], dfn[d]), res);
        d = fa[0][top[d]];
    }
    res = pushup(query(1, 1, n - 1, dfn[u], dfn[d]), res);
    return res;
}

// 查询完整答案
ll qlca(int a, int b) {
    auto[x, y] = sublca(a, b);
    if (~x) {
        if (~y) {
            auto le = qchain(x, a), ri = qchain(y, b);
            return (ri.d * g + le.d * (g + ri.t) + ri.nx + le.px) % Mod;
        }
        else {
            auto le = qchain(x, a);
            return (le.d * g + le.px) % Mod;
        }
    }
    else {
        if (~y) {
            auto ri = qchain(y, b);
            return (ri.d * g + ri.nx) % Mod;
        }
        else return 0;
    }
}

int main() {
    scanf("%d %lld", &n, &g);
    int u, v, w;
    ll d, t;
    for (int i = 1; i < n; i++) {
        scanf("%d %d %lld %lld", &u, &v, &d, &t);
        add(u, v, d, t);
    }
    fa[0][1] = 1;
    top[1] = 1;
    dfsr1(1, -1);
    dfsr2(1, -1);
    build(1, 1, n - 1);
    logn = log2(n);
    for (int i = 1; i <= logn; i++) for (int j = 1; j <= n; j++) {
        fa[i][j] = fa[i - 1][fa[i - 1][j]];
    }
    scanf("%d", &q);
    while (q--) {
        scanf("%d %d %d", &u, &v, &w);
        if (u) {
            printf("%lld\n", qlca(v, w));
        }
        else {
            scanf("%lld", &t);
            int e = rev[{v, w}];
            modify(1, 1, n - 1, dfn[e], t);
        }
    }
    return 0;
}
```

---

