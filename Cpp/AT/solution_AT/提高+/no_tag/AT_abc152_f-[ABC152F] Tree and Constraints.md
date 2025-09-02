# [ABC152F] Tree and Constraints

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc152/tasks/abc152_f

$ 1 $ から $ N $ までの番号がつけられた $ N $ 個の頂点を持つ木があります。 この木の $ i $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結んでいます。  
 この木の各辺に、それぞれ白か黒の色を塗ることを考えます。このような塗り方は $ 2^{N-1} $ 通り考えられますが、そのうち以下の $ M $ 個の制約をすべて満たすものの個数を求めてください。

- $ i(1\ \leq\ i\ \leq\ M) $ 番目の制約は、 $ 2 $ つの整数 $ u_i $ と $ v_i $ によって表される。これは、頂点 $ u_i $ と頂点 $ v_i $ を結ぶパスに含まれる辺のうち、黒く塗られているものが $ 1 $ つ以上存在しなければならないことを意味する。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 50 $
- $ 1\ \leq\ a_i,b_i\ \leq\ N $
- 入力で与えられるグラフは木である。
- $ 1\ \leq\ M\ \leq\ \min(20,\frac{N(N-1)}{2}) $
- $ 1\ \leq\ u_i\ <\ v_i\ \leq\ N $
- $ i\ \not=\ j $ なら $ u_i\ \not=u_j $ または $ v_i\not=v_j $
- 入力はすべて整数である。

### Sample Explanation 1

この入力中の木は以下のようなものです。

![図](https://img.atcoder.jp/ghi/5b0208ab1e3bb39a5d4fb7bafbfc448e.png) 

辺 $ 1 $ と辺 $ 2 $ をそれぞれ (白,黒), (黒,白), (黒,黒) で塗った場合に、$ M $ 個の制約をすべて満たすことができます。 したがって答えは $ 3 $ です。

### Sample Explanation 2

この入力中の木は以下のようなものです。

![図](https://img.atcoder.jp/ghi/d08b3f53dfa4857fe9ffe13fa5d7ae69.png)   
辺 $ 1 $ を黒く塗った場合のみ、 $ M $ 個の制約をすべて満たすことができます。 したがって答えは $ 1 $ です。

### Sample Explanation 3

この入力中の木は以下のようなものです。

![図](https://img.atcoder.jp/ghi/386502bb3c85e0bb5aee64e4e7c087a1.png)

### Sample Explanation 4

この入力中の木は以下のようなものです。

![図](https://img.atcoder.jp/ghi/955fa8fd8af658abb24ff2f68b9997be.png)

## 样例 #1

### 输入

```
3
1 2
2 3
1
1 3```

### 输出

```
3```

## 样例 #2

### 输入

```
2
1 2
1
1 2```

### 输出

```
1```

## 样例 #3

### 输入

```
5
1 2
3 2
3 4
5 3
3
1 3
2 4
2 5```

### 输出

```
9```

## 样例 #4

### 输入

```
8
1 2
2 3
4 3
2 5
6 3
6 7
8 6
5
2 7
3 5
1 6
2 8
7 8```

### 输出

```
62```

# 题解

## 作者：ix35 (赞：8)

怎么没人做这题...

很典型的容斥，令 $f(S)$ 表示 $S$ 中所有路径上的所有边均为白色的方案数，令输入的路径集合为 $P$，那么：

$$Ans=\sum\limits_{S\in P} (-1)^{|S|}f(S)$$

然后枚举子集，计算 $f(S)$ 即可，设 $S$ 中所有路径的并所占边数为 $x$，则 $f(S)=2^{n-1-x}$，即除了这 $x$ 条边以外都是任意染色的。

于是计算路径并的边数 $x$ 即可，每个子集都暴力做太慢了，总复杂度是 $O(2^m\times nm)$，可以采用递推的思想，考虑一个 $p\in S$，$S$ 的 $x$ 值可以由 $S/\{p\}$ 的 $x$ 值并上 $p$ 的边得到，这样可以 $O(2^m\times n)$。

最后，还可以再用 bitset 优化一下常数。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=60;
int n,m,x,y,eg,u[MAXN],v[MAXN],hd[MAXN],ver[2*MAXN],nx[2*MAXN],f[MAXN];
bitset <51> q[21],t[1<<20];
ll ans;
ll qpow (ll a,ll b) {
	ll res=1;
	while (b) {
		if (b&1) {res*=a;}
		a*=a,b>>=1;
	}
	return res;
}
void add_edge (int x,int y) {
	ver[++eg]=y;
	nx[eg]=hd[x];
	hd[x]=eg;
	return;
}
void dfs (int x,int fa) {
	f[x]=fa;
	for (int i=hd[x];i;i=nx[i]) {
		if (ver[i]==fa) {continue;}
		dfs(ver[i],x);
	}
	return;
}
void mk (int x,int y,int p) {
	for (int i=x;i!=1;i=f[i]) {q[p].set(i,1);}
	int cur=y;
	for (;cur!=1&&!q[p][cur];cur=f[cur]) {q[p].set(cur,1);}
	for (;cur!=1;cur=f[cur]) {q[p].set(cur,0);}
	return;
}
int main () {
	eg=1;
	scanf("%d",&n);
	for (int i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		add_edge(x,y),add_edge(y,x);
	}
	dfs(1,0);
	scanf("%d",&m);
	for (int i=1;i<=m;i++) {
		scanf("%d%d",&u[i],&v[i]);
		mk(u[i],v[i],i);
	}
	for (int i=0;i<(1<<m);i++) {
		int cnt=0,cur=0;
		for (int j=0;j<m;j++) {
			if (i&(1<<j)) {cnt++,cur=j+1;}
		}
		if (cnt) {t[i]=t[i^(1<<(cur-1))]|q[cur];}
		if (cnt&1) {
			ans-=qpow(2,n-1-t[i].count());
		} else {
			ans+=qpow(2,n-1-t[i].count());
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：NATO (赞：5)

状压好题。

经过思考我们并没有一个多项式复杂度的解法，但我们发现本题 $n,m$ 都非常的小，可以考虑非多项式复杂度。但是 $n$ 的范围又不能支持一个非多项式复杂度的做法，即我们不能直接枚举每条边来寻找答案，又由于 $m\le 20$，再加上每种限制只有满足和不满足两种情况，容易想到使用状态压缩来表示 $m$ 种限制的满足或不满足，那么我们求的就是这 $n-1$ 条边凑出 $2^m-1$ 的情况数。

然后我们考虑如何处理每一条边选择后的影响。

容易想到可以对于每一组 $u,v$，我们从 $u$ 点出发，暴力遍历整棵树，并记录每个点是通过哪条边遍历的，扫到 $v$ 点时就按照记录往 $u$ 回溯，并标记回溯时经过的边（即那些选择后满足 $u,v$ 限制的边），这样我们就可以预处理出每一条边选择后会满足哪些限制。

最后，我们将这 $n-1$ 条边看作是 $n-1$ 个最多选一次的物品，在状态压缩意义下跑一遍 $01$ 背包即可。

时间复杂度：$O(n 2^m)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007ll
#define MAXN 1000000000ll
using namespace std;
ll n,m;
ll head[55],cnt;
ll dp[(1ll<<20)+5];
ll uid[55];
ll to,bh;
struct ed
{
	ll v,next,uid;
}edge[105];
void add(ll u,ll v,ll uid)
{
	edge[++cnt].v=v;edge[cnt].next=head[u];head[u]=cnt;edge[cnt].uid=uid;
	edge[++cnt].v=u;edge[cnt].next=head[v];head[v]=cnt;edge[cnt].uid=uid;
}
bool dfs(ll id,ll fa)
{
	if(id==to)return 1;
	for(ll i=head[id];i;i=edge[i].next)
	{
		ll v=edge[i].v;
		if(v==fa)continue;
		bool f=dfs(v,id);
		if(f)
		{
			uid[edge[i].uid]|=(1<<(bh-1));return 1;
		}
	}
	return 0;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	ll u,v;
	for(ll i=1;i<n;++i)
	cin>>u>>v,add(u,v,i);
	dp[0]=1;
	cin>>m;
	for(ll i=1;i<=m;++i)
	{
		bh=i;cin>>u>>v;to=v;
		bool ls=dfs(u,0);
	}//预处理每一条边选择后满足的性质
	dp[0]=1;
	for(ll i=1;i<n;++i)
	{
		for(ll j=(1<<(m))-1;j>-1;--j)
		dp[j|uid[i]]+=dp[j];
	}//01背包
	cout<<dp[(1<<(m))-1];
}
```

总结一下，对于这种数据范围小、情况只有选或者不选、无多项式复杂度的题目，一般都考虑状压，而解决状压的重点在于将题目中的选择通过适当的转化转化为类似于背包的形态，将板子扔上去即可。

---

## 作者：Louis_lxy (赞：4)

what? 为啥题解区都是容斥啊？？？

人性化题意：给定 $n$ 个点的树，根为 $1$，你现在要将每条边边权设为为 $0/1$，需要满足对于 $m$ 条约束，$u\to v$ 的唯一路径边权和大于等于 $1$。

我们先将边权下放到点权，然后预处理出路径上会经过的点（注意去除 lca），就变成了给定 $m$ 个不重集合，第 $i$ 个集合记为 $a_i$，让你选择一个不重集合 $S$，满足 $\forall i\in[1,m]$，有 $a_i\cap S\ne\varnothing$。

然后考虑如何做，观察一下发现，如果选择节点确定，那么影响的集合也确定了，于是可以状压 $a_i$ 有没有一个数在 $S$ 中出现。考虑如此状压的原因是：由于选择顺序不影响，于是 dp 的时候对答案造成影响的只有第 $i$ 个点被不被标记，以及前 $i-1$ 个点影响到了的集合，满足无后效性。

以下记 $k_i$ 表示选择第 $i$ 个点影响到的集合（状压后的）。

然后就很简单了，记 $f_{i,j}$ 表示考虑到第 $i$ 个点，选择满足条件 $j$（即 $\forall i$ 满足 $2^i\wedge j=1$，$a_{i+1}$ 存在一个数在 $S$ 中出现），然后我们考虑刷表，不选第 $i+1$ 个点的方案数 $f_{i+1,j}\gets f_{i+1,j}+f_{i,j}$，选第 $i+1$ 个点的方案数 $f_{i+1,j\cup k_{i+1}}\gets f_{i+1,j\cup k_{i+1}}+f_{i,j}$。

答案就很显然了，就是第 $n$ 个点满足所有集合的答案。

upd：看到了一个跟我思路一样的金钩大佬的题解。

---

## 作者：Miraik (赞：4)

为啥题解区都是容斥啊qwq

看到 $m\le20$，考虑直接状压。

预处理一个状态数组 $sta$ 表示对于一条边，将其染为黑色能满足条件的限制状态。对于第 $i$ 个限制 $(u,v)$，我们直接把路径上所有边拉出来，并把 $i$ 并给这些边的状态。

然后你发现这个问题已经和树的形态无关了，直接设 $f_s$ 表示处理到当前边，已经满足的限制状态为 $s$ 的方案数。对于当前边 $i$ 而言，转移就是：

$f_{s \space \cup \space sta_i} = f_{s \space \cup \space sta_i}+ f_s$

直接转移即可，时间复杂度 $O(n \times 2^m)$。

```cpp
inline void dfs3(int u){
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa[u]) continue;
        dfs3(v);
        for(int j=(1<<m)-1;~j;j--)
            f[sta[v]|j]+=f[j];
    }
}
int main(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v); add(v,u);
    }
    dfs1(1); dfs2(1,1);
    m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),g=lca(u,v);
        while(u!=g) sta[u]|=1<<i-1,u=fa[u];
        while(v!=g) sta[v]|=1<<i-1,v=fa[v];
    }
    f[0]=1; dfs3(1); printf("%lld\n",f[(1<<m)-1]);
    return 0;
}
```


---

## 作者：Magic_World (赞：3)

# ABC-F - Tree and Constraints

## Description

对于一棵 $n$ 个节点的树，每个边染成黑色或白色。给出 $m$ 条限制；每个限制 $(u,v)$ 要求从 $u$ 到 $v$ 的路径至少有一条黑边，求同时满足所有限制的染色总方案数。

## Solution

设第 $i$ 个限制为 $A_i$，则答案为：
$$
\Big|\bigcap_{i=1}^nA_i\Big|
$$
这并不好求，但都能转化到这个形式了，丰富的经验告诉我们这是一道容斥题。

转化：
$$
U-\Big|\bigcup_{i=1}^n \overline{A_i}\Big|
$$
后半段式子根据容斥公式转化为：
$$
\Big|\bigcup_{i=1}^n \overline{A_i}\Big|=\sum\limits_{T\subset U}(-1)^{|T|+1}\Big|\bigcap_{j=1}^{|T|}\overline{A_{T_j}}\Big|
$$
为了使问题更直观，将限制条件状态压缩，若第 $i$ 个不满足，则 $S_i=1$，否则为 $0$。

设 $f(S)$ 为状态 $S$ 的方案数，则：
$$
\Big|\bigcup_{i=1}^n \overline{A_i}\Big|=\sum\limits_{T\subset U}(-1)^{|T|+1}f(T)
$$
于是我们求出所有 $f(S)$ 的值套入这个公式即可。

现在思考如何求每个 $f(S)$。

发现 $f(S)$ 代表属于 $S$ 的限制条件的路径上，边的颜色全为白色，其它边放飞自我的方案数。

则我们只需要直到多少边必须是白色即可，这相当于求出这些路径的并集有多少边。

发现 $N\le50$，所以所有的边我们同样可以状压起来。

设 $path_x$ 表示从根节点到 $x$ 经过的边的状压数值；

设 $info_{x,y}$ 表示 $x$ 和 $y$ 的路径上的边的状压数值。

则根据经典的树上异或性质： $info_{x,y}=path_x \oplus path_y$。

求出 $S$ 的所有限制条件的 $info$ 的并集，即为 $S$ 已经确定的白边个数；

设这个数为 $cnt$，则 $f(S)=2^{n-1-cnt}$。

最终答案为 $2^{n-1}-\sum\limits_{S=1}^{2^m-1} f(S)$。

**注意细节！！！**

- 64位使用 `__builtin_popcountll`。
- 枚举状压时，$S\in[1,2^m-1]$，之所以不从 $0$ 开始，是因为 $0$ 的状态是全集，而我们枚举时要算的是非法答案。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define int long long
using namespace std;
const int N = 51,M = 21;
int n,m,path[N],info[M];
struct EDGE{int to,nxt;}e[N<<1];
int h[N],qcnt;
void adedge(int x,int y){e[++qcnt] = (EDGE){y,h[x]},h[x]=qcnt;}
void dfs(int x,int fa)
{
	for(int i=h[x];i;i=e[i].nxt)
	{
		int v = e[i].to;
		if(v==fa) continue;
		path[v] = path[x] | (1ll<<v);
		dfs(v,x);
	}
}
// 64 位使用 __builtin_popcountll() !!! 
int f(int S)
{
	int edge=0ll,num = __builtin_popcountll(S);
	rep(i,0,m-1) if(S&(1ll<<i)) 
	    edge |= info[i+1];
	return (1ll<<(n - 1 - __builtin_popcountll(edge)))*(num&1 ? 1ll : -1ll);
} 
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	rep(i,1,n-1) {
		int x,y; cin>>x>>y;
		adedge(x,y),adedge(y,x);
	}
	dfs(1,0);
	cin>>m;
	int U = (1ll<<m)-1;
	rep(i,1,m) 
	{
		int x,y; cin>>x>>y;
		info[i] = path[x]^path[y];
	}
	int ans=0ll;
	rep(S,1,U) // S = 0 的情况就是全集本身 
	{
		ans += f(S);
	}
	int uans = (1ll<<(n-1));
	cout<<uans-ans;
	return 0;
}
```

---

## 作者：KokiNiwa (赞：2)

# ABC 152 F

容斥经典题。[题目链接](https://atcoder.jp/contests/abc152/tasks/abc152_f)。

## 题目叙述

给你一颗树，你要给树黑白染色，并给你$m$个限制，每个限制给一条路径$(u,v)$，限制是这条路径上至少有一个黑色边，问有多少个符合条件的染色方法。

## 题解

+ 考虑容斥。考虑计算$f(s)$为$s$（一个选不选某个限制的状压）满足这个集合里的所有限制都不满足的染色方法数。
+ 然后容斥即可。$\text{所有不满足的}=-\sum_{i=1}^{2^n-1}(-1)^{|s|}f(i)$。那么只需要计算不满足某些限制的一共有多少种即可。
+ 可以发现，不被这些不满足的路径覆盖的边可以任意选，其他的边必须为白色。
+ 如何计算某些路径的并？可以通过状压$dp$搞，用$\operatorname{lowbit}$转移。

## 知识点

+ 正难则反（暂时没找到容斥题的类型特征？计数题就先想想容斥吧
+ 容斥

## 代码

注意：

+ 注意`1ll<<a`！有些地方不能写`1<<a`！
+ 欸，注意`count`（数位`1`的位数）的函数要写一个对于`long long`的和一个对于`int`的

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxNode = 55, maxLim = 25;
template<const int nbNode, const int nbEdge> struct Graph {
	int tot, head[nbNode], to[nbEdge << 1], next[nbEdge << 1];
	Graph() { memset(head, -1, sizeof(head)); }
	void AddEdge(int u, int v) {
		to[++tot] = v;
		next[tot] = head[u];
		head[u] = tot;
	}
};
Graph<maxNode, maxNode> Tree;
int nbNode, limNum, fa[maxNode], dep[maxNode];
ll setCover[1 << 20];
void dfs(int now, int from) {
	dep[now] = dep[from] + 1;
	fa[now] = from;
	for (int pt = Tree.head[now]; ~pt; pt = Tree.next[pt])
		if (Tree.to[pt] != from)
			dfs(Tree.to[pt], now);
}
int count1_(int num) {
	int ret = 0;
	for (int wei = 0; wei < limNum; ++wei)
		if ((1 << wei) & num)
			++ret;
	return ret;
}
int count2_(ll num) {
	int ret = 0;
	for (int wei = 0; wei < nbNode - 1; ++wei)
		if ((1ll << wei) & num)
			++ret;
	return ret;
}
signed main() {
	scanf("%d", &nbNode);
	for (int i = 1; i < nbNode; ++i) {
		int uNode, vNode;
		scanf("%d%d", &uNode, &vNode);
		Tree.AddEdge(uNode, vNode);
		Tree.AddEdge(vNode, uNode);
	}
	scanf("%d", &limNum);
	dfs(1, 0);
	for (int i = 1; i <= limNum; ++i) {
		int uNode, vNode;
		scanf("%d%d", &uNode, &vNode);
		if (dep[uNode] < dep[vNode])
			swap(uNode, vNode);
		while (dep[uNode] > dep[vNode]) {
			setCover[1 << (i - 1)] |= 1ll << (uNode - 2);
			uNode = fa[uNode];
		}
		while (uNode != vNode) {
			setCover[1 << (i - 1)] |= 1ll << (uNode - 2);
			setCover[1 << (i - 1)] |= 1ll << (vNode - 2);
			uNode = fa[uNode];
			vNode = fa[vNode];
		}
	}
	//边的编号，定义为这个边深度较低的点的编号 - 2 
	setCover[0] = 0;
	for (int state = 1; state < (1 << limNum); ++state) {
		int last = state & (-state);
		if (last == state) continue ;
		setCover[state] = setCover[state ^ last] | setCover[last];
	}
	ll ans = 0;
	for (int state = 1; state < (1 << limNum); ++state) {
		int notCover = nbNode - count2_(setCover[state]) - 1;
		ll fu = ((count1_(state)) & 1) ? 1 : -1;
		ans += fu * (1ll << notCover);
	}
	printf("%lld\n", (1ll << (nbNode - 1)) - ans);
	return 0;
}
```



---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

考虑容斥：假设 $f(i)$ 是不符合至少i条规定的方案数；从容斥原理可以推到答案式子：
$$\sum^m_{i=0}(-1)^if(i)$$
应为不知道 $f(i)$ 的一个具体式子，用一个集合$S\subseteq[1,n]$表示不符合什么条件：如果第 $i$ 位是1，那么肯定不符合第 $i$ 条件。  
发现如果必须不符合一个条件 $(u,v)$ 的话，等价于把 $u$ 和 $v$ 的路径上边全染白色，没有然的边可以任意染色。所以，如果一个集合让 $i$ 个边必染白色，那么这个集合的染色方案数为 $2^{n-1-i}$.  
来优化，可以把每一个条件表示为一个集合，如果不符合条件 $j$ 的时候第 $i$ 边必染白色，那么 $i$ 就在 $T_j$ 集合里。  
一个集合 $S$ 的可以任意染边为 

$$n-1-|\bigcup_{j\in S} T_j|$$

所以，答案为

$$\sum_{s\in \mathbb{P}([1,n])}[(-1)^{|s|}2^{n-1-|\bigcup_{j\in S} T_j|}]$$

采用二进制数表达集合会大大提升程序运行时间。

**必须开LL**

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair

using ll=long long;
using pii=pair<int, int>;
#define int ll
const int MOD = 1000000007;

vector<int> elist[55];
int fa[55][8], dep[55];

void dfs(int node, int par) {
	int v = 0;
	fa[node][v] = par;
	while(fa[node][v] != -1) {
		fa[node][v+1] = fa[fa[node][v]][v];
		v++;
	}
	while(v != 8) fa[node][v++] = -1;
	if(par == -1) dep[node] = 0;
	else dep[node] = dep[par]+1;
	for(int i:elist[node]) if(i != par) dfs(i, node);
}

int lca(int a, int b) {
	if(dep[a] < dep[b]) swap(a, b);
	for(int i=7; i>=0; i--)
		if(fa[a][i] != -1 && dep[a] - (1<<i) >= dep[b]) a = fa[a][i];
	for(int i=7; i>=0; i--)
		if(fa[a][i] != -1 && fa[b][i] != -1 && fa[a][i] != fa[b][i]) {
			a = fa[a][i];
			b = fa[b][i];
		}
	if(a != b) return fa[a][0];
	return a;
}

uint64_t mask[25];

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	rep(i, n-1) {
		int u, v; cin >> u >> v;
		elist[u].pb(v);
		elist[v].pb(u);
	}
	dfs(1, -1);
	int m; cin >> m;
	rep(i, m) {
		int a, b; cin >> a >> b;
		int lc = lca(a, b);
		while(b != lc) {
			mask[i] |= (1ull<<b);
			b = fa[b][0];
		}
		while(a != lc) {
			mask[i] |= (1ull<<a);
			a = fa[a][0];
		}
	}
	uint64_t ans = 0;
	rep(bm, 1ull<<m) {
		uint64_t tree = 0;
		int cnt = 0, free = 0;
		rep(i, m) {
			if(bm & (1ull<<i)) {
				tree |= mask[i];
				cnt++;
			}
		}
		iter(i, 2, n+1) if(!(tree & (1ull<<i))) free++;
		if(cnt%2) ans -= (1ull<<free);
		else ans += (1ull<<free);
	}
	cout << ans << endl;
}
```

---

## 作者：StevenLiTheOIer (赞：1)

## 思路：
经典的状压容斥。直接考虑有多少满足条件的太困难了，正难则反，考虑对于每一种情况，有多少不满足条件，最后用全集 $2^{n-1}$ 减去容斥后的结果。

令 $f(S)$ 表示不满足集合 $S$ 内所有条件的方案数，因为有一条黑边就满足条件，所以 $S$ 中所有条件所占边的并都要涂白。设需要涂白的边数为 $C$，则剩余 $n-1-C$ 条边染色情况任意，故 $f(S) = 2^{n-1-C}$。

设输入的条件集合为 $T$，根据容斥原理，最终答案 $ans = \sum_{S\in T}(-1)^{|S|}f(S)$。

时间复杂度 $O(n+m\times 2^m)$。
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m, son[56], status[26];
vector <int> e[106];
void dfs(int now, int fa)
{
	for (int i = 0; i < e[now].size(); i++)
	{
		int to = e[now][i];
		if (to == fa) continue;
		son[to] = son[now] | (1ll << (to - 1));
		dfs(to, now);
	}
}
long long f(long long S)
{
	long long cur = 0, cnt = __builtin_popcountll(S);
	for (int i = 1; i <= m; i++)
		if (S & (1ll << (i - 1)))
			cur |= status[i];
	long long res = 1ll << (n - 1 - __builtin_popcountll(cur));
	if (cnt % 2 == 0) res = res * -1ll; //容斥 
	return res;
}
int main()
{
	cin >> n;
	for (int i = 1; i <= n - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		status[i] = son[u] ^ son[v]; //异或，求出两点间的路径 
	}
	long long ans = 0;
	for (int S = 1; S <= (1 << m) - 1; S++)
		ans += f(S); //状压容斥 
	cout << ((1ll << (n - 1)) - ans) << endl; //用全集减去答案 
	return 0;
}
```

---

## 作者：Lagerent (赞：1)

正难则反，我们考虑容斥原理。

设所有给定要求的路径集合为 $P$，最后的答案即为 $P$ 中所有路径随便染的情况减去所有边纯白的情况。

定义 $f(S)$ 为路径集合 $S$ 染成纯白的方案数，设 $E \in P$ 且 $|E| = 1$，当 $S = \varnothing$ 时，就是所有点随便选的情况。那么

$ans = f(\varnothing) - f(E_1) - f(E_2) - f(E_3) - ... + f(E_1 \cap E_2) + f(E_2 \cap E_3) - f(E_1 \cap E_2 \cap E_3) - ...$

整理一下，得到

$$ans = \sum_{S \in P}(-1)^{|S|}f(S)$$

拓展到每一组限制，那么当限制的个数为偶数的时候加，当限制个数为奇数的时候减。

如何求 $f(S)$ 呢？考虑已经确定有 $|S|$ 条边一定要染成白色，其余边任选染成黑，白两种情况，那么 $f(S) = 2^{n - 1 - |S|}$。

用 bitset 维护一下边集，枚举一下所有的 $2^m$ 中情况即可。

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#define rep(a, b, c) for(int (a) = (b); (a) <= (c); ++ (a))
#define per(a, b, c) for(int (a) = (b); (a) >= (c); -- (a))
#define Rep(a, b, c) for(int (a) = (b); (a) < (c); ++ (a))
#define Per(a, b, c) for(int (a) = (b); (a) > (c); -- (a))
#define il inline
#define inf 0x3f3f3f3f
using namespace std;

il int read() {
   int x = 0, f = 1; char ch = getchar();
   while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
   while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48),  ch = getchar();
   return x * f;
}

typedef long long LL;
const int N = 55;

int n, m;
int hd[N], to[N << 1], nt[N << 1], idx;
int fa[N][7], dep[N];
int q[N];
LL ans;
bitset<51> bits[N], t[1 << N];

il void add(int u, int v) {
	to[ ++ idx] = v, nt[idx] = hd[u], hd[u] = idx;
}

il void bfs(int root) {
	memset(dep, inf, sizeof dep);
	dep[0] = 0, dep[root] = 1;
	fa[root][0] = 0;
	int hh = 0, tt = 0;
	q[tt ++ ] = root;
	while(hh != tt) {
		int u = q[hh ++ ];
		for(int i = hd[u]; i; i = nt[i]) {
			int v = to[i];
			if(dep[v] > dep[u] + 1) {
				dep[v] = dep[u] + 1;
				fa[v][0] = u;
				q[tt ++ ] = v;
				rep(j, 1, 6) fa[v][j] = fa[fa[v][j - 1]][j - 1];
			}
		}
	}
}

int lca(int a, int b) {
	if(dep[a] < dep[b]) swap(a, b);
	per(k, 6, 0) {
		if(dep[fa[a][k]] >= dep[b]) a = fa[a][k];
	} 
	if(a == b) return a;
	per(k, 6, 0) {
		if(fa[a][k] != fa[b][k]) a = fa[a][k], b = fa[b][k];
	}
	return fa[a][0];
}

LL qpow(LL a, int b) {
	LL res = 1;
	for( ; b; b >>= 1) {
		if(b & 1) res = (LL)res * a;
		a *= a;
	}
	return res;
}

int main() {
	n = read();
	rep(i, 1, n - 1) {
		int u = read(), v = read();
		add(u, v), add(v, u);
	}
	bfs(1);
	m = read();
	rep(i, 1, m) {
		int u = read(), v = read();
		int LCA = lca(u, v);
		while(u != LCA) {
			bits[i].set(u, 1);
			u = fa[u][0];
		}
		while(v != LCA) {
			bits[i].set(v, 1);
			v = fa[v][0];
		}
	}
	rep(i, 0, (1 << m) - 1) {
		int cnt = 0, cur = 0;
		rep(j, 0, m - 1) {
			if(i >> j & 1) {
				++ cnt, cur = j + 1;
			}
		} //  cur 表示包含的最后一组路径 
		if(cnt) t[i] = t[i ^ (1 << (cur - 1))] | bits[cur];
		if(cnt & 1) ans -= qpow(2ll, n - 1 - t[i].count());
		else ans += qpow(2ll, n - 1 - t[i].count());
	}
	printf("%lld\n", ans);
	return 0;
}

```

---

## 作者：TernaryTree (赞：0)

经典容斥题，一看到 $m\le 20$ 就会容斥了。

首先 $f_i$ 表示**至少不满足** $i$ 个限制条件的方案数。

则有

$$f_i=\sum_{T\in S,|T|=i}\ \prod_{\text{没被}T\text{中任意路径覆盖的边数}}2$$

可以 $\Theta((n+m)2^m)$ 树上差分解决。之所以没有 lca 的 $\log $ 是因为我 $n^3$ 预处理了所有 lca/oh

然后根据容斥原理

$$ans=\sum_{i=0}^m(-1)^if_i$$

总复杂度 $\Theta(n^3+(n+m)2^m)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second

using namespace std;

const int maxn = 1e2 + 10;
const int maxm = 23;
typedef pair<int, int> pii;

int n, m, ans;
int a[maxn];
vector<int> g[maxn];
pii b[maxm];
int f[maxm];
int lca[maxn][maxn];
int dep[maxn];

void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	for (int v : g[u]) if (v != fa) dfs(v, u), a[u] += a[v];
}

int popcount(int x) {
	int y = 0;
	while (x) x &= x - 1, ++y;
	return y;
}

signed main() {
	cin >> n;
	for (int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int u = 1; u <= n; u++) {
		for (int v = 1; v <= n; v++) {
			for (int i = 1; i <= n; i++) a[i] = 0;
			a[u]++, a[v]++;
			dfs(1, 0);
			int res = 0;
			for (int i = 1; i <= n; i++) if (a[i] == 2 && dep[i] > dep[res]) res = i;
			lca[u][v] = res;
		}
	}
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> b[i].fs >> b[i].sc;
	for (int s = 0; s < (1 << m); s++) {
		for (int i = 1; i <= n; i++) a[i] = 0;
		for (int i = 1; i <= m; i++) {
			if (s >> i - 1 & 1) {
				a[b[i].fs]++, a[b[i].sc]++;
				a[lca[b[i].fs][b[i].sc]] -= 2;
			}
		}
		dfs(1, 0);
		int cnt = 1;
		for (int i = 2; i <= n; i++) if (!a[i]) cnt <<= 1;
		f[popcount(s)] += cnt;
	}
	for (int i = 0; i <= m; i++) {
		if (i & 1) ans -= f[i];
		else ans += f[i];
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：M1saka16I72 (赞：0)

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-abc152-f.html)

## 思路

不太一样的做法。

直接爆搜每条边的颜色复杂度是 $2^n$，我们可以尝试折半搜索然后合并答案。

具体地，把 $n-1$ 条边分成两半，分别搜索每条边染黑还是白，搜索结果是一个二进制数，第 $i$ 位是否为 $1$ 代表是否满足第 $i$ 个条件的限制。$\mathcal{O}(1)$ 检查是否满足条件可以先预处理每个条件所包含的边集 $E_i$，然后再把搜索出来的边集 $S$ 与 $E_i$ 做按位与即可，这部分预处理时间复杂度为 $\mathcal{O(nm)}$，搜索时间复杂度为 $\mathcal{O}(2^{\frac{n}{2}}m)$。

搜索完之后我们得到了两个二进制数组成的集合，分别代表前 $\frac{n-1}{2}$ 条边染色后满足条件的情况和后 $\frac{n-1}{2}$ 条边的情况。可以考虑对于第一个集合里的每个元素分别计算可以和多少个第二个集合里的元素配对。两个状态 $a,b$ 可以配对当且仅当 $a\operatorname{or} b=2^m-1$，此处 $\operatorname{or}$ 代表按位或。容易发现这个条件可以转换为 $b$ 按位取反后是 $a$ 的子集，把第二个集合中的元素全部按位取反后的集合叫作 $S$，此时问题就变成了多次询问集合 $S$ 中有多少个元素是 $x$ 的子集，可以用高维前缀和 $\mathcal{O}(2^mm)$ 解决。

总时间复杂度 $\mathcal{O}((2^\frac{n}{2}+2^m)m)$，可以通过。

## 代码

[link](https://atcoder.jp/contests/abc152/submissions/56740222)

---

