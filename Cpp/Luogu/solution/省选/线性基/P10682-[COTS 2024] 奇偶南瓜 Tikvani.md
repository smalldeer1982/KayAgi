# [COTS 2024] 奇偶南瓜 Tikvani

## 题目背景

译自 [Izborne Pripreme 2024 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2024/) D1T3。$\texttt{0.5s,1G}$。

## 题目描述

给定有向图 $G=(V,E)$，其中 $|V|=N,|E|=M$，满足 $\forall (u,v)\in E$，都有 $u\lt v$。

定义边的一种**着色方案**为一种给每条边分配 $0/1$ 权值的方式。记 $(u,v)$ 边权为 $w(u,v)$。

定义节点 $(u,v)$ 的路径为一个序列 $(a_1,a_2,\cdots,a_k)$，满足 $a_1=u,a_k=v$，且 $\forall 1\le i\lt k$，都有 $(a_i,a_{i+1})\in E$。定义路径的权值为其上所有边的权值之和，即 $\displaystyle \sum_{i=1}^{k-1} w(a_{i},a_{i+1})$。

定义一种着色方案是好的，当且仅当对于每一对 $(u,v)$，都有 $(u,v)$ 间的所有路径的权值模 $2$ 后的余数相等。

求出好的着色方案数，对 $(10^9+7)$ 取模。

## 说明/提示


#### 样例解释

样例 $1$ 解释：显然只有 $1,4$ 间有两条路径 $(1,2,3,4),(1,4)$。

当 $w(1,4)=0$ 时，$(1,2,3,4)$ 路径上只能取 $0$ 或 $2$ 条边边权为 $1$，方案数为 $4$；

当 $w(1,4)=1$ 时，$(1,2,3,4)$ 路径上只能取 $1$ 或 $3$ 条边边权为 $1$，方案数为 $4$。

所以答案为 $8$。

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le N\le 400$，$0\le M\le 400$；
- $1\le u\lt v\le n$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $21$  | $N \leq 6$   |
| $2$  | $20$  | $N \leq 13$  |
| $3$  | $37$  | $N, M \leq 50$ |
| $4$  | $22$  | 无额外约束 |



## 样例 #1

### 输入

```
4 4
1 2
2 3
3 4
1 4```

### 输出

```
8```

## 样例 #2

### 输入

```
4 4
1 3
1 4
2 3
2 4```

### 输出

```
16```

# 题解

## 作者：Rainbow_qwq (赞：4)

考虑每条边有一个权值 $a_i$，那么 $a_i$ 之间需要满足若干个方程：对于两条不同的 $u\to v$ 的路径，两条路径上的 $a_i$ 异或和需要 $=0$。

那么就是要求解满足若干个方程的 $a_i$ 的解数。把这些方程插入线性基里，若得到的线性基的大小（秩）为 $k$，则答案为 $2^{m-k}$。

以每个点 $u$ 为根，向外 dfs 得到一棵外向树。对于一条非树边 $x\to y$，就有两条路径 $(u\to x)\to y$ 和 $(u\to y)$。把这两条路径异或起来，得到的方程插入线性基。

对于使用 $\ge 2$ 条非树边的情况，不难发现已经被原有的方程表示了。

这样能得到 $nm$ 条方程，总共 $nm$ 次线性基插入，复杂度为 $O(nm\times \frac{m^2}{w})$，在 $n,m\le 400$ 时可以通过。

<https://qoj.ac/submission/423354>

---

## 作者：oMin0 (赞：1)

## 分析

观察题目条件。发现对任意两条 $i\rightarrow j$ 的路径，都要满足其中所有边的边权和为偶数，而这种要求也是充分的，因此对以上所有边集建出异或方程组跑高斯消元即可得到答案（异或方程组解的数量等于 $2$ 的自由元数量次幂）。

然而方程组数量是指数级的，需要优化。考虑枚举每个 $i$ 为根建出 dfs 树，则只考虑包含恰好一条非树边的限制即可，因为其他限制可以被这样的限制异或得到。那么方程数量降为 $O(nm)$，时间复杂度 $O(\frac{nm^3}{w})$，常数非常小，可以通过。

这种找环基的优化思路在 P4151，P1477，CF1835D，CF1515G 等很多题中都有体现。

## 代码

```cpp
/*
  author: honglan0301
  Sexy_goodier _ xiaoqing
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <bitset>
#include <assert.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define int long long
#define mod 1000000007
#define G 3
#define Gi 332748118
mt19937 rnd(time(0));
mt19937_64 rndl(time(0));

int ksm(int x,int k) {int na=1; for(int i=1;i<=k;i<<=1) {if(i&k) na=na*x%mod; x=x*x%mod;} return na;}

int n,m,u,v,vis[405];
vector <pair<int,int>> e[405];
bitset <405> nr[405],cf[405];
bitset <405> p[405];
int ok[405];

void ins(bitset <405> nr)
{
	for(int i=m;i>=1;i--)
	{
		if(nr[i]&&!ok[i]) {ok[i]=1; p[i]=nr; return;}
		else if(nr[i]&&ok[i]) nr^=p[i];
	}
}
void dfs(int x)
{
	vis[x]=1;
	for(auto i:e[x])
	{
		if(!vis[i.fi]) nr[i.fi]=nr[x],nr[i.fi][i.se]=1,dfs(i.fi);
		else ins(nr[x]^nr[i.fi]^cf[i.se]);
	}
}

signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>u>>v,e[u].pb(mp(v,i)),cf[i][i]=1;
	for(int i=1;i<=n;i++) nr[i].reset(),memset(vis,0,sizeof(vis)),dfs(i);
	int tot=m; 
	for(int i=1;i<=m;i++) tot-=ok[i];
	cout<<ksm(2,tot)<<endl;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

下文认为 $n,m$ 同阶。

填 $0/1$ 的合法方案计数，限制可以表达为一个异或方程组。

不难想到答案就是 $2$ 的这个异或方程组的自由元数量次方（这是因为消元后填数时只有自由元怎么填都可以并且一定存在一组形如全 $0$ 的解）。

但是问题是方程太多了，我们需要考虑减少方程数量。

这个问题看似不好处理，我们考虑一下，假若是在无向图上怎么解决这个问题？

无向图上这是个经典问题，考虑建立一颗 dfs 生成树后，任意一个复杂环都可以通过若干条只经过一条非树边的简单环异或得到，把问题放回到有向图上，不妨以每个点为根都建立一棵外向 dfs 生成树并对于每个生成树考察所有只经过一条非树边的限制，这样做考察了所有只有终点一个交点的两条路径，显然所有相同终点路径对都可以通过若干个这样的路径对组合起来，因此将这些路径对的限制方程做高斯消元（实际上可以用类似线性基插入的办法实现）即可，使用 bitset 优化可以做到 $O(\frac{n^4}{w})$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 414;
int n,m;
int head[maxn],nxt[maxn],to[maxn];
int tot;
void add(int u,int v){
    tot++;
    to[tot]=v;
    nxt[tot]=head[u];
    head[u]=tot;
}
bitset<maxn> d[maxn];
int fa[maxn];
int x[maxn],y[maxn];
void dfs(int u){
    for(int now=head[u];now;now=nxt[now]){
        int v=to[now];
        if(fa[v]==0){
            fa[v]=now;
            dfs(v);
        }
    }
}
int diam;
void ins(bitset<maxn> bit){
    for(int i=m;i>=1;i--){
        if(bit[i]==1){
            if(d[i].count()==0){
                d[i]=bit;
                diam++;
                return ;
            }else bit^=d[i];
        }
    }
}
const int mod = 1e9+7;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        x[i]=u,y[i]=v;
        add(u,v);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) fa[j]=0;
        dfs(i);
        for(int j=1;j<=m;j++){
            int u=x[j],v=y[j];
            if((fa[u]==0&&u!=i)||(fa[v]==0&&v!=i)) continue;
            bitset<maxn> bit;
            bit[j]=1;
            while(u!=i) bit[fa[u]]=bit[fa[u]]^1,u=x[fa[u]];
            while(v!=i) bit[fa[v]]=bit[fa[v]]^1,v=x[fa[v]];
            ins(bit);
        }
    }
    int ans=1;
    for(int i=1;i<=m-diam;i++) ans=1ll*ans*2%mod;
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

考虑所有路径对 $(S,T)$ ，满足起点和终点相同。那么他们就会形成一个异或方程组对边权进行限制。路径的个数是有限的，方程的个数也是有限的。

考虑优化方程的个数。容易发现，对于一组相交路径，我们只用在它第一个交点处的情况即可，剩下的部分可以换个起点继续考虑。

因此我们的思路很简单：选定一个起点，DFS。如果到了一个访问过的点（这一轮中，每次更改起点都要清空标记）就将一组路径组放进线性基里，最后求 $2^{m-\dim B}$ 即可。

每一轮一条边最多对应一个“方程”，所以一共有 $O(nm)$ 个方程，在线性基里面插入一个元素复杂度为 $O(\dfrac{m^2}{w})$，总复杂度为 $O(\dfrac{nm^3}{w})$，足以通过本题。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=400+10,MOD=1e9+7;
int n,m,vis[MAXN];
vector<pair<int,int>> G[MAXN];
bitset<MAXN> bt[MAXN],bs[MAXN];
void insert(bitset<MAXN> bt) {
	ffor(i,1,m) if(bt[i]) {
		if(bs[i][i]) bt^=bs[i];
		else return bs[i]=bt,void();
	}
	return ;
}
void dfs(int u,bitset<MAXN> b) {
	if(vis[u]) return insert(bt[u]^b),void();
	vis[u]=1,bt[u]=b;
	for(auto pr:G[u]) {
		int v=pr.first,id=pr.second;
		bitset<MAXN> nw=b;
		nw[id]=1;
		dfs(v,nw);	
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,m) {int u,v;cin>>u>>v,G[u].push_back({v,i});}
	ffor(i,1,n) {
		memset(vis,0,sizeof(vis));
		ffor(j,1,n) bt[j]=0;
		bitset<MAXN> tmp=0;
		dfs(i,tmp);	
	}
	int cnt=m;
	ffor(i,1,m) if(bs[i][i]) cnt--;
	int ans=1;
	ffor(i,1,cnt) ans=ans*2%MOD;
	cout<<ans;
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/P10682)

**题目大意**

> 给定 $n$ 个点 $m$ 条边的 DAG，求有多少种给每条边赋 $0/1$ 权值的方式使得任意两条起终点相同的路径权值和 $\bmod 2$ 都同余。
>
> 数据范围：$n,m\le 400$。

**思路分析**

很显然题目的要求就是对于任意两条 $u\to v$ 的路径，路径上所有边权异或和为 $0$，可以用高斯消元求解。

由于本题全填 $0$ 肯定是一组解，因此可以直接维护，不需要特判一些 Corner Case。

那么我们只要优化限制组数即可。

对每个起点 $u$ 分别考虑，根据经典结论，先求出一棵以 $u$ 为根的外向 dfs 树，设树上 $u\to v$ 的路径为 $T_u$，那么只要考虑恰经过一条非树边的环。

即对于一条非树边 $x\to y$，我们只要求 $T_x\oplus T_y\oplus w(x\to y)=0$，并且不难证明这是充分的。

对于任意一条路径，找到其中的第一条非树边 $x\to y$，根据限制，可以把到 $y$ 的路径等效成 $T_y$，递归进行此过程即可证明该路径合法。

那么此时总共只有 $\mathcal O(nm)$ 条限制，暴力插入并用  `bitset` 优化高斯消元维护。

时间复杂度 $\mathcal O\left(\dfrac{nm^3}\omega\right)$

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=405,MOD=1e9+7;
int n,m;
struct Edge { int v,id; };
vector <Edge> G[MAXN];
bool vis[MAXN];
bitset <MAXN> w,d[MAXN],x[MAXN];
void ins() {
	for(int i=1;i<=m;++i) if(w[i]) {
		if(!x[i].any()) return x[i]=w,void();
		else w^=x[i];
	}
}
void dfs(int u) {
	vis[u]=true;
	for(auto e:G[u]) {
		if(!vis[e.v]) d[e.v]=d[u],d[e.v].set(e.id),dfs(e.v);
		else w=d[u],w^=d[e.v],w.flip(e.id),ins();
	}
}
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;++i) scanf("%d%d",&u,&v),G[u].push_back({v,i});
	for(int i=1;i<=n;++i) {
		for(int u=1;u<=n;++u) d[u].reset(),vis[u]=false;
		dfs(i);
	}
	int ans=1;
	for(int i=1;i<=m;++i) if(!x[i].any()) ans=ans*2%MOD;
	printf("%d\n",ans);
	return 0;
}
```

---

