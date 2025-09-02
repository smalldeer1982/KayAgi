# [ABC246G] Game on Tree 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc246/tasks/abc246_g

$ N $ 個の頂点を持ち、頂点 $ 1 $ を根とする根付き木があります。 $ i\ =\ 1,\ 2,\ \ldots,\ N-1 $ について、$ i $ 本目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結びます。 また、根以外の頂点には正の整数が書かれており、具体的には、$ i\ =\ 2,\ 3,\ \ldots,\ N $ について、頂点 $ i $ に正の整数 $ A_i $ が書かれています。 高橋君と青木君はこの根付き木と $ 1 $ 個のコマを使って次の対戦ゲームをします。

はじめ、頂点 $ 1 $ にコマが置かれています。その後、ゲームが終了するまで下記の手順を繰り返します。

1. まず、青木君が根以外の頂点を任意に $ 1 $ 個選び、その頂点に書かれた整数を $ 0 $ に書き換える。
2. 次に、高橋君がコマを、いまコマがある頂点の（直接の）子のいずれかに移動する。
3. その後、コマが葉にある場合はゲームが終了する。そうでない場合であっても、高橋君は望むならゲームを直ちに終了させることができる。

ゲーム終了時点でコマがある頂点に、ゲーム終了時点で書かれている整数が、高橋君の得点となります。 高橋君は自身の得点を出来るだけ大きく、青木君は高橋君の得点を出来るだけ小さくしたいです。 両者がそのために最適な行動を取るときの高橋君の得点を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- 与えられるグラフは木である。
- 入力はすべて整数

### Sample Explanation 1

両者が最適な行動をとる場合のゲームの進行の一例として次のものがあります。 1. はじめ、コマは頂点 $ 1 $ に置かれています。 2. 青木君が頂点 $ 7 $ に書かれた整数を $ 10 $ から $ 0 $ に書き換えます。 3. 高橋君がコマを頂点 $ 1 $ から頂点 $ 2 $ に動かします。 4. 青木君が頂点 $ 4 $ に書かれた整数を $ 6 $ から $ 0 $ に書き換えます。 5. 高橋君がコマを頂点 $ 2 $ から頂点 $ 5 $ に動かします。 6. 高橋君がゲームを終了します。 ゲーム終了時点でコマは頂点 $ 5 $ にあり、頂点 $ 5 $ にはゲーム終了時点で整数 $ 5 $ が書かれているので、高橋君の得点は $ 5 $ です。

## 样例 #1

### 输入

```
7
2 4 6 5 6 10
1 2
1 3
2 4
2 5
5 6
5 7```

### 输出

```
5```

## 样例 #2

### 输入

```
30
29 27 79 27 30 4 93 89 44 88 70 75 96 3 78 39 97 12 53 62 32 38 84 49 93 53 26 13 25
13 15
14 22
17 24
12 3
4 3
5 8
26 15
3 2
2 9
4 25
4 13
2 10
28 15
6 4
2 5
19 9
2 7
2 14
23 30
17 2
7 16
21 13
13 23
13 20
1 2
6 18
27 6
21 29
11 8```

### 输出

```
70```

# 题解

## 作者：Exp10re (赞：6)

## 前言

- 赛时沿用了 [P4654 [CEOI2017] Mousetrap](https://www.luogu.com.cn/problem/P4654) 的思路，成功导致想出了二分答案没想出 DP。
- 教练的思路很通俗易懂。
- 赛后讲题我自己的思路我自己都没懂，寄。

## 解题思路

本题解参照题目翻译，认为移动的一方为 B，另一方为 A。

容易发现答案具有单调性，考虑二分答案。

定义 $target$ 为 B 的目标（二分的答案），并且认为当 B 经过若干次行动后能到达满足 $val_i \geq target$ 的点 $i$ 时 $target$ 为一个满足条件的解，于是我们考虑如何判断 $target$ 是否为解。

为了方便，我们对点进行染色：在 $target$ 已经确定的情况下，定义一个点为黑点当且仅当 $val_i \geq target$，否则为白点。

定义 $f_i$ 表示当 B 移动到点 $i$ **之前**，如果 B 下一步就要移动到点 $i$，那么 A 至少需要进行多少次操作才能保证 B 在以 $i$ 为根的子树内一定无法到达任何黑点。

通俗易懂的解释是：如果 B 开局的时候下一步就要到达 $i$，那么 A 至少要~~作弊~~额外修改多少个节点的颜色才能使得 B 即使走到根为 $i$ 的子树也走不到任何黑点。

其实不是很直观，如果感觉难以理解建议手玩一下，很好懂的。

接下来考虑转移方程：

$$f_i=\max(\sum f_j-1,0)+[val_i \geq target]$$

其中 $\sum f_j$ 为点 $i$ 的所有孩子的 $f$ 值之和。

为什么是对的呢？

当 B 从点 $i$ 开始进行移动，并且点 $i$ 还有子节点 $j$ 能使得 B 走到 $j$ 之后能到达黑点，那么 B 就一定会走这个点。为了避免这种情况，A 必须保证在到达 $i$ 之前至少使用了 $\sum f_j-1$ 次操作以保证 B 走到 $i$ 之后无论选择哪个子树都不能到达黑点（此处要 $-1$ 是因为 B 走到点 $i$ 的回合 A 还能进行一次操作）。

而 $[val_i \geq target]$ 就是判断点 $i$ 是否为黑点，如果是，那么还要在到达 $i$ 之前匀出一次操作来把 $i$ 变为白点。

因为 B 开局就在点 $1$ 上，所以判断对于一个既定的 $target$ 是否有解，只需要进行一次 DP 之后判断 $f_1$ 是否等于 $0$ 即可。

总时间复杂度 $O(n\log{a_{max}})$，能过。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=200100;
long long val[MAXN],n,cpy[MAXN],dp[MAXN];
vector<long long> e[MAXN];
void check(long long x,long long tag,long long fat)
{
	long long i,mp=e[x].size()-1,v,sum=0;
	for(i=0;i<=mp;i++)
	{
		v=e[x][i];
		if(v==fat)
		{
			continue;
		}
		else
		{
			check(v,tag,x);
			sum+=dp[v];//求子节点的和 
		}
	}
	sum=max(sum-1,0ll);//为了避免减到 0 以下 
	dp[x]=sum+(val[x]>=tag);//判断是否为黑点 
	return;
}
int main()
{
	long long i,j,ta,tb,l,r,mid,maxn=0,ans=0;
	scanf("%lld",&n);
	for(i=2;i<=n;i++)
	{
		scanf("%lld",&val[i]);
		cpy[i]=val[i];
		maxn=max(maxn,val[i]);
	}
	for(i=1;i<n;i++)
	{
		scanf("%lld%lld",&ta,&tb);
		e[ta].push_back(tb);
		e[tb].push_back(ta);
	}
	sort(cpy+1,cpy+1+n);
	l=1;
	r=n;
	while(l<=r)//二分答案 
	{
		mid=(l+r)/2;
		check(1,cpy[mid],0);
		if(dp[1]>=1)
		{
			ans=mid;
			l=mid+1;
		}
		else
		{
			r=mid-1;
		}
	}
	printf("%lld",cpy[ans]);
	return 0;
}
```

---

## 作者：MyDearJellyfish (赞：4)

这题我给出了一个 $O(n \alpha (n))$ 的做法，应该是爆标了。目前 Atcoder 上速度第一，并且比第二优解快了一倍。

提交链接：[Submission #45442447 - AtCoder Beginner Contest 246](https://atcoder.jp/contests/abc246/submissions/45442447)

经过实测，可以在 $2$ 秒内通过 $n = 10^7$，且将近有一半时间在于找到 $fa_u$ 的 bfs 部分。也就是说输入 $fa_u$ 的话甚至能跑更快。

为了方便说明，我们将这棵树看作以 $1$ 为根节点的有根树。定义 $fa_u$ 表示节点 $u$ 的父亲，定义 $son_u$ 表示节点 $u$ 的儿子集合。

这个题最简单的做法就是二分，二分答案是否至少是 $x$。我们模拟 Aoki 的策略，记录 $dp_u$ 表示如果当前在 $u$，并且希望能让最终答案至少是 $x$ 的前提下，至少要在到达 $x$ 前在以 $u$ 为根的子树内将多少个数变为 $0$。显然有如下转移方程：

 $dp_u = \max(\sum_{v \in son_u} dp_v - 1, 0) + [a_u \geq x]$ 

$[dp_1 > 0]$ 决定了答案是否至少是 $x$。二分显然没前途，只能做到 $O(n \log a)$。

我们考虑维护 $f_{u, x}$ 表示当二分值为 $x$ 时，$dp_u$ 的取值，转移似乎没什么不同：

 $f_{u, x} = \max(\sum_{v \in son_u} f_{v, x} - 1, 0) + [a_u \geq x]$ 

考虑对 $f_{u, x}$ 做差分，令 $g_{u, x} = f_{u, x} - f_{u, x + 1}$，你会发现由于 $\max$ 的存在，$g$ 的转移并不容易刻画，但我们发现对于所有 $u$，$f_u$ 单调，因此 $g$ 非负，我们做类似 slope trick 的操作，对于点 $u$，录一个可重集 $S_u$，假设 $x$ 在 $S_u$ 中出现了 $c$ 次，就表示 $g_{u, x} = c$。

记录 $\text{merge}(S_1, S_2, \dots, S_m)$ 表示将 $S_1, S_2, \dots, S_m$ 内所有元素合并得到的新集合。我们考虑如何刻画 $S_u$。

1. 由于数组相加等于差分数组相加。我们令 $S_u = \text{merge}_{v \in son_u}(S_v)$

2. 如果 $f$ 不是全为 $0$，差分唯一变动的点 $x$ 满足，$f_{u, x} > 0, f_{u, x + 1} = 0$。显然对应了最大的 $x$ 满足 $g_{u, x} > 0$。如果 $S_u$ 不为空，删去最大的元素。
3. 对于所有 $x \leq a_u$ 的 $f_{u, x}$ 加 $1$，即是将 $g_{u, a_u}$ 加 $1$。我们将 $a_u$ 加入 $S_u$。

不难发现 $S_1$ 的最大值就是答案。利用可并堆可以做到 $O(n \log n)$，比原来复杂度略优，但这显然不够。

依然不好直接优化，我们考虑维护数组 $z$，$z_u$ 表示在点 $u$ 上，我们从 $S_u$ 中删除的元素是多少，如果在 $u$ 没有删除元素，$z_u = -1$。

不失一般性的，我们假设所有 $a$ 互不相同，以方便后续的说明细节。

我们将所有点 $u$ 按照 $a_u$ 排序，此处我们利用基数排序，复杂度 $O(n)$，我们假设 $a$ 第 $i$ 大的点为 $p_i$。

我们从 $n$ 到 $1$ 枚举 $i$，然后考虑是否有这样一个位置 $u$，满足 $z_u = a_{p_i}$。但是 $u$ 咋找呢？

我们记录 $vis$ 数组，一开始全为 $0$。为了方便起见，我们令 $fa_1 = 0$。我们从 $n$ 到 $1$ 枚举 $i$，每次重复如下过程：

- 一开始 $u = fa_{p_i}$，如果 $vis_u=1$，则 $u \leftarrow fa_u$，重复该过程直到 $vis_u = 0$ 或 $u=0$。
- 如果 $u=0$ 说明 $a_{p_i}$ 就是答案，直接输出，否则令 $vis_u = 1$，且说明 $z_u=a_{p_i}$。

这个为啥对呢？你考虑我们进行 $\text{merge}$ 操作的时候，$a_{u}$ 只会出现在 $u$ 即其祖先的 $S$ 之中，只可能在这些位置被删除，且由于我们按 $a$ 排过序，一旦找到一个地方还没确定删除的值，它就必定在这个位置被删除。否则说明有更大的值在这里已经替代它被删除，我们就继续向上寻找可能能删除它的位置。而如果发现整个过程中都没有被删除，说明其存在于 $S_1$ 内。也就是我们要找的答案。

直接暴力是 $O(n^2)$ 的，但不难发现我们可以用并查集代替维护这个过程。

我们用如下维护方式：一开始所有点自成一个连通块，每次我们找到 $z_u = a_{p_i}$ 的点 $u$，将 $u$ 和 $fa_u$ 所在的连通块合并。对于一个连通块，记录 $r$ 表示该连通块深度最浅的点，那么我们不难发现 $fa_{p_i}$ 所在的连通块的 $r$ 就是我们需要找到的点 $u$。

并查集同时进行路径压缩，和按照连通块大小合并，就可以做到 $O(n \alpha(n))$。



---

## 作者：封禁用户 (赞：4)

## 分析

考虑树形 DP。

因为我们要求小 B 能够得到的最大分数的最小值，所以可以二分答案。对于每一次二分的答案 $x$，定义 $f_{i}$ 表示在以 $i$ 为根的（子）树中（从节点 $i$ 开始走），按照双方最优策略小 B 能够达到的权值不小于 $x$ 的数量。如果 $f_{1}$（小 B 从 $1$ 开始的）大于 $0$，则表示在最优情况下，小 B 是一定能得到至少 $x$ 分的。对于小 A 的最优策略，那就一定是在小 B 每次行动前将一个以小 B 所在节点为根的（子）树中一个权值不小于 $x$ 的点的权值变成 $0$，那状态转移方程就相当于：$f_i=\max(f_{i}'-1,0)+(val_{i} ≥ x)$（$f_{i}'$ 是不计小 A 在这次移动前的操作时，能得到的值）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int n,a[N];
int ne[N],e[N],h[N],idx;
void add(int a,int b){
	ne[idx]=h[a],e[idx]=b,h[a]=idx++;
}
int f[N];//f[i]:从i开始，B能到达点权>=x的点的数量
void dfs(int now,int fa,int x){
	for(int i=h[now];~i;i=ne[i]){
		int j=e[i];
		if(j==fa) continue;
		dfs(j,now,x);
		f[now]+=f[j];
	}
	f[now]--;//在B走向子节点之前，A可以将now的子树中一个权值>=x的点改成0
	if(f[now]<0){
		f[now]=0;
	}
	if(a[now]>=x){
		f[now]++;
	}
}
int ans;
signed main(){
	memset(h,-1,sizeof(h));
	cin>>n;
	for(int i=2;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		add(u,v),add(v,u);
	}
	int l=0,r=1145141919810;
	while(l<=r){
		int mid=l+r>>1;
		memset(f,0,sizeof(f));
		dfs(1,-1,mid);
		if(f[1]>=1){//可以
			ans=mid,l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
	return cout<<ans,0;
}
```


---

## 作者：菲斯斯夫斯基 (赞：2)

## AT_abc246_g [ABC246G] Game on Tree 3 题解

**这是一篇启发式合并的题解。**

### 前言

教练把这题放在了模拟赛第一题，难得场切。一看题解区都是二分和 dp，所以来写一篇题解开拓新思路。

### 思路

首先思考一手弱智问题：只有一个节点，答案显然为 $0$，因为没有节点可以继续行走。

扩展一下情况，考虑深度为 $2$ 的树（也就是只有 $1$ 个非叶子节点）。答案就应该是所有叶子节点的权值的次大值。

为什么呢？因为 A 有一次归 $0$ 的机会，将最大值归 $0$ 是最优的。

继续扩展情况，考虑下面这棵树：

![](https://cdn.luogu.com.cn/upload/image_hosting/ziqkx5jm.png)

相当于在刚刚的根节点上多加了一个父亲，但是又多了一个权值和一次删除的机会。

如果 $x$ 节点的权值最大或次大，那么优先归零 $x$。否则直接归零次大和最大的点就好了。

不难发现深度加一就可以多归零一个点。不妨将一个子树看作为一个集合，只有一个节点时为空集。每次把所有子树的集合合并在一起，接着把儿子的权值也给加到集合里面去，**然后把权值最大的节点删除**。最后 $1$ 节点集合的最大值即为答案。

为什么这样做是正确的呢？可以发现，一个子树的集合实际上表示的就是 B 能到达的点的权值。现在要把多个子树通过 $x$ 这个节点合并到一起，那么就都能够到达，但是因为深度又增加了 $1$，所以可以将一个节点归零，贪心地想显然是归零最大值。

### 代码实现

于是这题就结束了。直接做是 $\mathcal O(n^2)$，用启发式合并可以优化到 $\mathcal O(n\log^2 n)$。

因为只用求最大值，所以用 `priority_queue` 和 `multiset` 维护都可以。

注意如果树是一条链的话最后会变成空集，答案为 $0$。

~~赛时打的代码，有点丑陋。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n;
int siz[N],c[N],son[N],f[N];
vector<int>v[N];
multiset<int>s[N];
void dfs1(int x,int fa)
{
	siz[x]=1;
	int ma=0;
	for(int i:v[x])
	{
		if(i==fa)continue;
		dfs1(i,x);
		if(siz[i]>ma)ma=siz[i],son[x]=i;
		siz[x]+=siz[i];
	}
}
void dfs2(int x,int fa)
{
	if(son[x])dfs2(son[x],x),f[x]=f[son[x]],s[f[x]].insert(c[son[x]]);
	for(int i:v[x])
	{
		if(i==fa||i==son[x])continue;
		dfs2(i,x);
		for(int j:s[f[i]])
			s[f[x]].insert(j);
		s[f[x]].insert(c[i]);
		s[f[i]].clear();
	}
	if(!s[f[x]].empty())s[f[x]].erase(--s[f[x]].end());
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		f[i]=i;
	for(int i=2;i<=n;i++)
		scanf("%d",&c[i]);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs1(1,0);
	dfs2(1,0);
	if(s[f[1]].empty())cout<<0;
	else cout<<*(--s[f[1]].end());
	return 0;
}
```

---

## 作者：gdf_yhm (赞：1)

[abc246g](https://www.luogu.com.cn/problem/AT_abc246_g)

### 思路

最少拿分，考虑二分答案。

B 最少拿 $mid$ 分，则 A 需要在 B 之前改变所有 $a_u\geq mid$ 的点。

显然 B 不会走回头路。

设 $f_u$ 表示：B 在 $u$ 点并向其儿子之一 $v$ 移动前，A 需要对 $u$ 的子树操作几次使 B 无法成功。如果 $f_u\geq 1$，就意味着当 A 在到达 $u$ 之前就要提前在 $u$ 的子树内做准备。如果 $f_u\leq 0$，说明 $u$ 的子树内 A 必胜，但 $f_u$ 不能向上转移负数，所以 $f_u=\max(f_u,0)$。否则 B 必胜。

B 可以去任意的 $v$ 且无法预测，所以 $f_u=\sum f_v$ 。又因为 A 先手，A 在 B 移动前可以操作一次,$f_u$ 加 $1$，但如果 $a_u\geq mid$，$f_u$ 减 $1$。

$$f_u=\max(\sum f_v-1,0)+(a_u\geq mid))$$

从 $1$ 开始 dfs 搜索。如果 $f_1\geq 1$，说明此时 B 必胜。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn],f[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot].nxt=head[u];
	e[tot].to=v;
	head[u]=tot;
}
int l,r,mid,ans,mx;

void dfs(int u,int fa,int x){
	int sum=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			dfs(v,u,x);
			sum+=f[v];
		}
	}
	if(sum)--sum;
	f[u]=sum+(a[u]>=x);
}
bool check(int x){
	dfs(1,0,x);
	return f[1]!=0; 
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	n=read();
	for(int i=2;i<=n;i++){
		a[i]=read();
		if(mx<a[i])mx=a[i];
	}
	for(int i=1;i<n;i++){
		int u,v;u=read();v=read();
		add(u,v);add(v,u);
	}
	int l=1,r=mx;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)){
			l=mid+1;
			ans=mid;
		}
		else r=mid-1;
	}
	printf("%lld\n",ans);
}
```


---

## 作者：一个程序员 (赞：1)

截止至 2023 年 10 月 7 日，本题解在洛谷所有提交中为最优解。

---

### 题目大意

给定一棵树根为 $1$ 的有根树，树上除了根以外的点均有点权 $a_i$。一枚棋子一开始放在根处。现在 A 和 B 在树上进行如下博弈：

- A 选择一个点，将其点权变为 $0$。

- B 选择将棋子移向它所在节点的某个子节点上。

如此不断进行下去。B 可以在任何时刻结束游戏，此时 B 的得分为结束游戏时棋子所在的位置。现在 A 希望最小化得分，而 B 希望最大化得分。求两人均采取最优策略时 B 的得分。

---

### 思路

这里提供一种新的思路。

记 $dp[u]$ 表示在以 $u$ 为根的子树内 B 的得分。它有两种可能的取值：

- 若 B 在当前节点停下，则 $dp[u]=a_u$。

- 若 B 选择走到某个子节点，则 $dp[u]$ 的值为某个 $dp[v]$，其中 $v$ 是 $u$ 的子节点。

但是第二种情况下 A 有一次操作的机会。此时贪心地考虑，A 必然会操作使 $dp[v]$ 最大的那个子树 $v$ 内的点。如果不这样操作，B 便能走到子树 $v$ 内，此时答案便为 $dp[v]$。而如果标记上这个点，则答案必定比 $dp[v]$ 小。因此 A 必然会把 $v$ 内等于 $dp[v]$ 的那个点标记上。

现在考虑计算 $dp[u]$。此时 $dp[u]$ 应为子树内所有点（包括 $u$）的所有未被标记过的点的最大值。然而答案有可能来自被删掉了最大值的子树 $v$，因为 $v$ 内的次大值有可能成为答案。因此我们发现，不能只记录最大值。

考虑把子树 $v$ 内所有可能成为答案的数记下来。此时我们需要维护几种操作：

- 求可能成为答案的数的最大值。

- 删去这个最大值（对应了标记这个点）。

- 将 $u$ 内的子树 $v$ 的答案合并到 $u$。

容易发现我们可以使用左偏树解决这个问题。

---

### Solution

对每个节点维护一棵左偏树，表示以这个节点为根的子树内可能成为答案的数的集合。初始时第 $i$ 个节点的左偏树内只有一个点 $a_i$。特殊地，根节点的左偏树为空。

在树上自底向上地计算。遍历到节点 $u$ 时，先计算好 $u$ 的所有子节点 $v$ 的答案。

接下来寻找 $u$ 的所有子树的左偏树中的最大值。由贪心，A 必然不会让 B 取到这个值，因此在左偏树中将这个值删除。然后所有 $v$ 的左偏树全都合并到 $u$ 的左偏树即可。答案即为根节点 $1$ 的左偏树内的最大值。

---

### Code

```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;

struct edge
{
    int v, next;
}e[maxn << 1];
int head[maxn], tot;

inline void addedge(int u, int v)
{
    e[++tot] = (edge){v, head[u]};
    head[u] = tot;
}

struct node
{
    int lch, rch;
    int val, dis;
}t[maxn]; //左偏树
int rt[maxn]; //节点i对应的左偏树的树根

int merge(int a, int b) //合并
{
    if (!a || !b) return a + b;
    if (t[a].val < t[b].val) swap(a, b); //大根堆
    t[a].rch = merge(t[a].rch, b);
    if (t[t[a].rch].dis > t[t[a].lch].dis) swap(t[a].rch, t[a].lch);
    t[a].dis = t[t[a].rch].dis + 1;
    return a;
}

void dfs(int u, int fu)
{
    int mx = 0;
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if (v == fu) continue;
        dfs(v, u);
        if (!rt[v]) continue;
        mx = max(mx, t[rt[v]].val); //查找子树内最大值
    }
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if (v == fu) continue;
        if (!rt[v]) continue; //如果子树为空，则不用删除
        if (mx == t[rt[v]].val)
        {
            rt[v] = merge(t[rt[v]].lch, t[rt[v]].rch);
            mx = 0; //确保只删除一遍
        }
        rt[u] = merge(rt[u], rt[v]);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        rt[i] = i;
        scanf("%d", &t[i].val);
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    dfs(1, 0);
    printf("%d", t[rt[1]].val);
    return 0;
}
```

---

## 作者：wbwone1 (赞：1)

# Game on Tree 3 题解

## 题目大意

Alice 和 Bob 玩游戏。有一个有根树（根为 $1$），有一个球在 $1$ 上。每轮开始，Bob 可以选择一个节点，将点权变为 $0$，Alice 在**此操作后**，可以将球移动到它的儿子节点。在每轮结束时，Alice 也可以选择结束游戏，如果移动到了叶子节点，游戏结束。最终的得分为结束时球所在的点的权值，Alice 想让得分最大，而 Bob 想让得分最小，问你最大得分。

## 思路

观察，发现只要能得到 $\geq x$ 分，那么 $<x$ 的分数就不用算了，答案具有单调性，于是可以二分答案。

假设现在我们要判断得分 $\geq x$ 是否可行，Bob 显然只用考虑对那些分数 $\geq x$ 的点操作，把这样的点对 Bob 操作次数的贡献设为 $1$，其他点设为 $0$。

假设现在在点 $u$，设 $f[u]$ 为 Alice 操作前，Bob 使 $u$ 的子树中的点都变成 $0$ **至少**要操作多少次。

由于这里是至少，所以我们要假设 Bob 无法猜测 Alice 的移动，所作的移动纯粹是在 Alice 移动之前的决策。

所以需要把所有 Alice 可能走的地方都变成 $0$，即 $\sum_{v\in son_u}f[v]$。

但是，Bob 总是在 Alice 之前做决策，所以可以在 $u$ 这里进行一次操作，原先所需的操作次数减 $1$，还要考虑到当 $u$ 的贡献为 $1$ 时，Bob 也需要把这个点变成 $0$，增加 $1$ 的代价，于是得到状态转移方程：

$f[u] = \max(\sum_{v\in son_u}f[v]-1,0)+(v[u] = 1)$

Bob 必胜，当且仅当 $f[1] = 0$。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
int n,a[N],head[N],tot,b[N],f[N];
struct e{
	int next,to;
} edge[N*2];
void add(int x,int y){
	edge[++tot].to = y;
	edge[tot].next = head[x];
	head[x] = tot;
}
void dfs(int u,int fa){
	int v,sum = 0;
	f[u] = 0;
	for (int i=head[u];i;i = edge[i].next){
		v = edge[i].to;
		if (v == fa) continue;
		dfs(v,u);
		sum+=f[v];
	}
	sum = max(sum-1,0);
	f[u] = sum+b[u];
}
bool chk(int x){
	for (int i=1;i<=n;i++) b[i] = (a[i]>=x);
	dfs(1,0);
	return f[1]!=0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	int l = 0,r = 0,mid,ans = 0;
	for (int i=2;i<=n;i++){
		cin>>a[i];
		r = max(r,a[i]);
	}
	int x,y;
	for (int i=1;i<n;i++){
		cin>>x>>y;
		add(x,y),add(y,x);
	}
	while (l<=r){
		mid = (l+r)>>1;
		if (chk(mid)){
			ans = mid;
			l = mid+1;
		}
		else r = mid-1;
	}
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：zero_range (赞：0)

特长生考试考的题目。当时很快想出这个做法，赛后却发现没一个人这么写。遂验证。暂时没发现错误的地方。

此做法复杂度极优。使用基数排序可做到 $O(n\alpha(n))$，且代码很短。

考虑先计算删点人的策略：给每一个节点 $x$ 选定一个需要删除的子树中的节点 $p_x$，当对手走到这个节点上便删除它。

若删点人不想让对手获得某个点 $x$ 的权值，则需要在这个点到根的路径上（不含这个点）有一个点 $y$ 使得 $p_y=x$。

简单的贪心可以知道，我们可以优先从权值较大的节点考虑，同时优先选择最深的节点 $y$，以给之后的节点留出更多空间。当一个节点找不到一个合法的点 $y$ 时，它就是答案。

使用并查集维护。首先将权值从大到小排序。对于每一个点，若已经被选中，则在并查集上将其并入其父节点所在集合（即把它删除）。这样每个点所在集合的根节点就是这个点上方第一个未被占用的节点。每次寻找点 $y$ 时寻找 $x$ 所在集合的根节点即可。

代码：
```cpp
#include<stdio.h>
#include<vector>
#include<algorithm>
#define M 200005
using namespace std;
int n,a[M],b[M],f[M],fa[M];
vector<int> G[M];
int find(int x){return x!=f[x]?(f[x]=find(f[x])):x;}
void dfs(int x,int fa){
	::fa[x]=fa;
	for(int p:G[x]) if(p!=fa)
		dfs(p,x);
}
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;++i) scanf("%d",a+i),b[i]=i;
	for(int i=1,u,v;i<n;++i) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	sort(b+2,b+n+1,[](int x,int y){return a[x]>a[y];}),dfs(1,0);
	for(int i=1;i<=n;++i) f[i]=i;
	for(int i=2;i<=n;++i){
		int x=b[i],y=find(fa[x]);
		if(!y) return printf("%d\n",a[x]),0;
		f[y]=find(fa[y]);
	}
	puts("0");
}
```

---

## 作者：Tsawke (赞：0)

# [ABC246G Game on Tree 3](https://www.luogu.com.cn/problem/AT_abc246_g) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=ABC246G)

## 题面

类似于 [LG-P3554 [POI2013]LUK-Triumphal arch](https://www.luogu.com.cn/problem/P3554)，给定一棵树，有点权，B 初始在 $ 1 $，每轮 A 选择一个点将权值变为 $ 0 $，然后 B 移动一次，B 可在任意时刻停止游戏然后获得所在点上的权值的得分，两人均采取最优策略那么最终 B 最少会拿到多少的得分。

## Solution

与 [LG-P3554 [POI2013]LUK-Triumphal arch](https://www.luogu.com.cn/problem/P3554) 基本相同，对于本题依然考虑二分答案，对于当前的答案 $ k $，认为树上点权大于 $ k $ 的贡献为 $ 1 $，小于等于的为 $ 0 $，于是显然可以树形 DP，令 $ dp(i) $ 表示 A 在 $ i $ 节点上时需要额外多少次的变为 $ 0 $ 的操作，显然有转移 $ dp(i) = \max(\sum_{j \in son(i)} dp(j) - 1, 0) + \left[ v(i) \gt k \right] $，最后判断一下根节点 $ 1 $ 为 $ 0 $ 则合法，反之不合法。

对于二分的当然可以直接二分值域，不过这里可以考虑一个小剪枝，上界显然为点权的最小值，若根节点有多个子树，那么下界显然为根节点连接的节点的点权的最小值。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/extc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;
using namespace __gnu_pbds;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template<typename T = int>
inline T read(void);

int N;
struct Edge{
    Edge* nxt;
    int to;
    OPNEW;
}ed[410000];
ROPNEW(ed);
Edge* head[210000];

int val[210000];
int mnval(INT_MAX), mxval(-1);
int f[210000];

void dfs(int k, int p = 1, int fa = 0){
    for(auto i = head[p]; i; i = i->nxt){
        if(SON == fa)continue;
        dfs(k, SON, p);
        f[p] += f[SON];
    }
    f[p] -= 1;
    f[p] = max(0, f[p]);
    f[p] += val[p] > k ? 1 : 0;
}
bool Check(int K){
    memset(f, 0, sizeof(f));
    dfs(K);
    return f[1] == 0;
}
int main(){
    N = read();
    for(int i = 2; i <= N; ++i)val[i] = read(), mxval = max(mxval, val[i]);
    for(int i = 1; i <= N - 1; ++i){
        int s = read(), t = read();
        head[s] = new Edge{head[s], t};
        head[t] = new Edge{head[t], s};
        if(s == 1)mnval = min(mnval, val[t]);
        if(t == 1)mnval = min(mnval, val[s]);
    }if(!head[1]->nxt)mnval = 0;
    int l = mnval, r = mxval;
    int ans(-1);
    while(l <= r){
        int mid = (l + r) >> 1;
        Check(mid) ? ans = mid, r = mid - 1 : l = mid + 1;
    }printf("%d\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template<typename T>
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_10_21 初稿

---

