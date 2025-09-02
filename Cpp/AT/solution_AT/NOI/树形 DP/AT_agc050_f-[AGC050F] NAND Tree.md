# [AGC050F] NAND Tree

## 题目描述

有一棵树，每个顶点上写有 $0$ 或 $1$。这棵树有 $N$ 个顶点，编号为 $1$ 到 $N$。对于每个 $i$，存在一条连接顶点 $a_i$ 和顶点 $b_i$ 的边。顶点 $i$ 上写的数字为 $c_i$。

すぬけ君会对这棵树重复以下操作：

- 选择一条边进行缩约，将被消去的两个顶点上的数字进行 NAND 运算，并将结果写在新顶点上。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc050_f/2832ee2906c66cb526c5b478a4fea0cd9ce9f087.png)

经过 $N-1$ 次操作后，树会只剩下一个顶点。在所有 $(N-1)!$ 种操作顺序中，最后剩下的顶点上写有 $1$ 的方案有多少种？请计算这个答案对 $2$ 取余的结果。

## 说明/提示

### 注释

- NAND 运算的定义如下：$NAND(0, 0) = NAND(0, 1) = NAND(1, 0) = 1,\quad NAND(1, 1) = 0$。
- 当缩约连接顶点 $s$ 和顶点 $t$ 的边时，要同时去除该边并合并这两个顶点。缩约后的树中，如果合并产生的新顶点与顶点 $u$ 之间存在边，当且仅当缩约前的树中 $s$ 与 $u$ 有边或 $t$ 与 $u$ 有边。

### 数据范围

- $2 \leq N \leq 300$
- $1 \leq a_i < b_i \leq N$
- 输入描述的图是一棵树。
- $0 \leq c_i \leq 1$
- 输入中的所有值均为整数。

### 样例解释 1

在 $6$ 种操作顺序中，有 $4$ 种情况下最后剩下的顶点上写有 $1$。因此答案为 $4 \bmod 2 = 0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 2
2 3
2 4
0 1 1 0```

### 输出

```
0```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4
1 1 0 1```

### 输出

```
1```

## 样例 #3

### 输入

```
20
3 15
1 12
10 16
3 19
5 20
1 9
6 13
14 19
2 4
8 11
12 16
6 20
2 17
16 18
17 19
7 10
16 20
2 20
8 20
1 0 0 1 1 0 1 1 1 0 0 1 0 1 0 1 1 1 0 0```

### 输出

```
0```

# 题解

## 作者：jun头吉吉 (赞：8)

## 题意
给定一棵 $N$ 个节点的树，第 $i$ 个点上有数字 $c_i$，每次可以删除一条边 $(x,y)$，合并 $x$ 和 $y$ 两个点，新的数字为 $\mathrm{NAND}(c_x,c_y)$。求在 $(N-1)!$ 种合并方案中有多少种最后剩下 $1$。

**答案对 $2$ 取模。**

$N\le 300$。

> $\mathrm{NAND}(0,0)=\mathrm{NAND}(1,0)=\mathrm{NAND}(0,1)=1,\mathrm{NAND}(1,1)=0$


## 题解
这个膜 $2$ 就很厉害。

当 $n$ 为偶数时，暴力枚举第一次操作。接下来只考虑 $n$ 为奇数，也即是合并次数为偶数的情况。

我们考虑找到最小的 $i$ 使得 $2i-1$ 次和 $2i$ 次相互不影响，交换之后不影响树的样子，那么交换之后和交换之前抵消了，不影响答案。

考虑什么叫做相互影响。首先一定要边有公共点。不妨设为 $(x,y)$ 和 $(y,z)$，那么两种顺序分别是 $\mathrm{NAND}(\mathrm{NAND}(c_x,c_y),c_z)$ 和 $\mathrm{NAND}(\mathrm{NAND}(c_z,c_y),c_x)$。

如果 $c_x=c_z$ 那么得到的树是一样的直接抵消了。否则一定是不一样的。

然后我们就可以换一种合并边的方式：每次选择一条链 $x\leftrightarrow y \leftrightarrow z$，满足 $c_x\ne c_z$，缩成一个点，点权任意。我们把可以自选的点叫做自由点。

考虑如果有自由点参与合并

- 如果 $y$ 是自由点，那么 $y$ 两种选择最后得到了相同的树，然后抵消掉了。

- 如果 $x,z$ 都是自由点，那么选择 $01$ 和 $10$ 也能抵消掉。
- 否则只有 $x$ 是自由点，必须选择和 $z$ 不同的。

也就是说我们禁止自由点作为 $y$，禁止两边都是自由点。

所以发现操作使得自由点的数量是不降的，最后要只剩下一个点，所以除了第一次之后每一次都要把自由点当做链的一端。

因此我们钦定第一次合并时的 $x$，满足 $c_x=1$，那么就是有根树，我们要计算拓扑序 $a_1,\dots,a_n$ 的组数满足：

- $c_{a_3}=0$
- $a_{2i}$ 是 $a_{2i+1}$ 的父亲

但是很妙的一点是这两个条件都可以删去。

先考虑第二点，找到第一个 $a_{2i}$ 不是 $a_{2i+1}$ 的父亲，交换这两个，抵消。

然后考虑第一点，如果 $c_{a_3}=1$，那么所有情况和以 $a_3$ 为根，第三个为 $x$ 的情况抵消。

所以就是拓扑序数量，$n!/\prod sz_i$。

只要求膜 $2$ 的值所以计算每个含有多少个 $2$ 即可。

朴素实现 $\mathcal O(N^3)$，简单换根 $\mathcal O(N^2)$。

## 代码
```cpp
#define nand(a,b) (!(a)||!(b))
#define ctz __builtin_ctz
const int N=3e2+10;
int n,a[N],ans;vector<int>e[N];
int ban,tot,p2,sz[N],kk[N],kkk[N];
void dfs1(int u,int fa){
	sz[u]=1;kk[u]=0;
	for(auto v:e[u])if(v!=fa&&v!=ban)
		dfs1(v,u),sz[u]+=sz[v],kk[u]+=kk[v];
	kk[u]+=ctz(sz[u]);
}
void dfs2(int u,int fa,int up){
	if(a[u]&&up+kk[u]-ctz(sz[u])+ctz(tot)==p2)ans^=1;
	for(auto v:e[u])if(v!=fa&&v!=ban)
		dfs2(v,u,up+kk[u]-kk[v]-ctz(sz[u])+ctz(tot-sz[v]));
}
void calc(){
	dfs1(1,0);dfs2(1,0,0);
}
signed main(){
	read(n);for(int i=1,u,v;i<n;i++)read(u,v),e[u].pb(v),e[v].pb(u);
	for(int i=1;i<=n;i++)read(a[i]);
	tot=n-(n%2==0);for(int i=1;i<=tot;i++)p2+=ctz(i);
	if(n&1)calc();
	else for(int i=1;i<=n;i++){
		vector<int>_=e[i];
		for(auto j:_)if(i<j){
			int _=a[i];
			a[i]=nand(a[i],a[j]);
			for(auto k:e[j])if(k!=i)e[i].pb(k),e[k].pb(i);
			ban=j;calc();
			for(auto k:e[j])if(k!=i)e[i].pop_back(),e[k].pop_back();
			a[i]=_;
		}
	}
	writeln(ans);
}
```

---

## 作者：syzf2222 (赞：5)

这种题我感觉纯纯的人力不可及，不懂怎么才能做出来/ll

考虑一个操作序列，如果相邻两个边没有“交”，那么我们交换它也是等效的。

此处的交指的是在缩完前面的边之后有交。

如果是偶数条边的话，我们可以考虑把边相邻两两配对；否则我们可以枚举第一条选的边然后变成偶数的情况。

总结一下，就是我们每次选出两条边，使得它们在当前的树上相邻。

注意到这里的这个条件其实并不强，这也是我说人力不可及的原因，你需要找到一个弱化的尺度去结合运算的性质，但如果你不弱化成这样你也很难找到你想找的性质。

注意到一次选两条边实际上是要把 $a,b,c$ 三个连通块合并为 $(a\oplus b)\oplus c$。

观察到，如果 $a=c$ 则我们也可以交换这两条边，而当 $a\neq c$ 时上式恒为 $a$！

故我们可以看作这个的运算结果就是 $a$。也就是说我们可以枚举一个点 $p$ 始终作为 $a$。

这时我们考虑加入两条边。若都与 $p$ 无交，则可以交换，反正它们与最终结果无关；若第二条边与 $p$ 有交，则不满足 $p$ 是 $a$ 的性质。所以一定是选一个 $p$ 的儿子和它的一个儿子。

注意到这是一个完美匹配，所以选儿子的方案是固定的，只有顺序关系，于是转化为了树上的拓扑序计数。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int mod=1e9+7;
#define inf 1e9
#define pb push_back
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int N=305;
vector<int>G[N],T[N];
int n,m,c[N],C[N],ans,id[N],tg[N],sz[N],pw[N],S[N];
inline void merge(int x,int y){
	for(int i=1;i<=n+1;i++)id[i]=i-(i>y);id[y]=x;
	for(int i=1;i<=n;i++)T[i].clear();
	for(int i=1;i<=n+1;i++)
		for(auto t:G[i])if(id[i]^id[t])T[id[i]].pb(id[t]);
	for(int i=1;i<=n+1;i++)C[id[i]]=c[i];
	C[x]=!(c[x]&c[y]);
}
inline int dfs(int x,int fa){
	sz[x]=1;
	for(auto t:T[x])if(t^fa){
		int now=dfs(t,x);
		if(now==-1)return -1;
		sz[x]+=sz[t];
		if(now==1){
			if(!tg[x])tg[x]=1;
			else return -1;
		}
	}return 1-tg[x];
}
inline int solve(){
	int res=0;
	for(int i=1;i<=n;i++)if(C[i]){
		memset(tg,0,sizeof(tg));
		if(dfs(i,0)==-1)continue;
		int cnt=S[n/2];
		for(int j=1;j<=n;j++)
			if(tg[j])cnt-=pw[sz[j]/2];
		if(!cnt)res^=1;
	}return res;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)if(i%2==0)pw[i]=1+pw[i/2];
	for(int i=1;i<=n;i++)S[i]=S[i-1]+pw[i];
	for(int i=1,x,y;i<n;i++)
		x=read(),y=read(),G[x].pb(y),G[y].pb(x);
	for(int i=1;i<=n;i++)c[i]=read();
	if(n&1){
		for(int i=1;i<=n;i++)
			for(auto x:G[i])T[i].pb(x);
		for(int i=1;i<=n;i++)C[i]=c[i];
		ans=solve();
	}else{
		--n;
		for(int i=1;i<=n;i++)
			for(auto x:G[i])if(x>i)
				merge(i,x),ans^=solve();
	}printf("%d\n",ans);
	return 0;
}
```

深深地感到自己的弱小。

---

