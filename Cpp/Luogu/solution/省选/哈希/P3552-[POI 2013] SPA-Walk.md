# [POI 2013] SPA-Walk

## 题目描述

The names of towns in Byteotia are unique sequences of exactly $n$ bits.

There are $2^n-k$ towns in Byteotia, and thus,only $k$ sequences of $n$ bits do not correspond to any town.

Some pairs of towns are connected with roads.

Specifically, two towns are directly linked by a road if and only if their names differ in a single bit.

The roads do not cross outside of towns.

Byteasar intends to take a stroll - he intends to walk from the town $x$ to the town $y$, taking the existing roads.

Your task is to write a program that will determine if such a walk is possible.

有2^n个长度为n的01串，两个01串之间有边当且仅当这两个01串只有一位不同，现在从这2n个串中拿掉k个，问指定两个串之间能否到达


## 说明/提示

有2^n个长度为n的01串，两个01串之间有边当且仅当这两个01串只有一位不同，现在从这2n个串中拿掉k个，问指定两个串之间能否到达


## 样例 #1

### 输入

```
4 6
0000 1011
0110
0111
0011
1101
1010
1001
```

### 输出

```
TAK
```

# 题解

## 作者：DYYqwq (赞：5)

这是我的 1000 通过喵！

看 $2^n$，自然联想到 $n$ 维超立方体。

这里偷一张机房同学的图。

![](https://cdn.luogu.com.cn/upload/image_hosting/26t17lps.png)

首先有一个很厉害的定理，原题中给出了，但是你谷没搬过来。

- 对于一个 $n$ 维超立方体的点，将其划分为两个不交集合，则两个集合之间的边数不少于两集合大小的 $\min$。

证明：

首先定义一个东西叫做“特殊路径”，表示什么呢，就是从 $u \rightarrow v$，从前往后依次更改不相同的二进制位置所形成的路径。

比如说 $1001011 \rightarrow 1101100$ 的特殊路径实际上就是 $1001011 \rightarrow 1101011 \rightarrow 1101111 \rightarrow 1101101 \rightarrow 1101100$。

考虑一条 $u \rightarrow v$ 的边，显然经过它的“特殊路径”有 $2^{n-1}$ 条。因为相当于用这条边固定了一个位置，所有只有 $n-1$ 个位置可以随便选。

对于我们分出的两个集合 $S_1,S_2$，我们先不妨设 $|S_2|\ge|S_1|$，那自然集合之间的特殊路径数为两个集合大小乘积，即 $|S_1||S_2|=|S_1|(2^n-|S_1|)$。

然后显然 $|S_1| \leq \frac{2^n}{2}=2^{n-1}$。一条集合之间的路径必然经过集合之间的边（别笑，这是很重要的！），因此边数 $\ge \frac{总特殊路径边数}{2^{n-1}}=\frac{|S_1|(2^{n-1}-|S_1|)}{2^{n-1}}\ge\frac{|S_1|2^{n-1}}{2^{n-1}}=|S_1|$。证毕。

这是第一个定理，但是远远不够！我们还需自己找到一个性质。

- 在 $n$ 维超立方体上删除 $k$ 条边以后，最多只有一个 $n \times k$ 个点以上的连通块。

这个是好证的。

证明：假设存在两个连通块的大小都 $> n \times k$，根据我们最开始的定理，他们之间的边数也必然 $\ge n \times k + 1$。但是你只能删 $n \times k$ 个边啊！这两个连通块之间肯定有边连接的！但是这和我们的假设矛盾了欸，于是就这么水灵灵的证完了！

根据以上两个定理（主要是第二个，第一个是用于证明第二个的），我们就可以从 $S$ 和 $T$ 开始走，如果发现找到了 $> n \times k$ 个节点，那就说明在最大的连通块中。如果双方都是在最大的连通块中，那必然可以到达。如果一个在一个不在，那必然不行。否则的话有可能在同一个小连通块内，但是这种情况必然能直接走到终点。然后就是这样。

我看大家说 `unordered_map` 和 `gp_hash_table` 以及 `cc_hash_table` 都会被卡掉，需要手写哈希表。

但是其实 `unordered_set` 是可以过的。因为 `unordered_map` 是两个键值，而 `unordered_set` 只有一个值，显然更快。

但是我也手写了哈希表。

这是手写哈希表代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf = 1333331;
struct hsb
{
	struct node
	{
		int to , nxt;
	}e[5000010];
	int head[1333341] , tot;
	void add(int v)
	{
		int u = v % inf;
		++ tot;
		e[tot].to = v;
		e[tot].nxt = head[u];
		head[u] = tot;
	}
	bool fnd(int v)
	{
		int u = v % inf;
		for(int i = head[u] ; i != 0 ; i = e[i].nxt)
		{
			int vv = e[i].to;
			if(v == vv) return 1; 
		}
		return 0;
	}
	hsb()
	{
		tot = 0;
		memset(head , 0 , sizeof(head));
	}
}hsh;
int n , k , s , t , a[1000010];
queue<int> q;
int read()
{
	int date = 0 , w = 1;
	char c = 0;
	while(c < '0' || c > '9')
	{
		if(c == '-') w = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		date = ((date << 1) | (c ^ 48));
		c = getchar();
	}
	return date * w;
}
bool bfs(int st , int nd)
{
	if(st == nd)
	{
// 		puts("-1?");
		return 1;
	}
	while(!q.empty()) q.pop();
	hsh = hsb();
	for(int i = 1 ; i <= k ; i ++) hsh.add(a[i]);
	q.push(st) , hsh.add(st);
	int cnt = 1;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = 0 ; i < n ; i ++) // 找到所有连接它的边。由于只有一位有变化，所以只需考虑这一位。
		{
			int v = (u ^ (1ll << i));
			if(v == nd)
			{
				// puts("-1");
				return 1;
			}
			if(hsh.fnd(v)) continue;
			if((++ cnt) > n * k)
			{
				// puts("111");
				return 1;
			}
			q.push(v) , hsh.add(v);
		}
	}
	return 0;
}
signed main()
{
	scanf("%lld%lld" , &n , &k);
	s = read() , t = read();
	for(int i = 1 ; i <= k ; i ++) a[i] = read();
	printf((bfs(s , t) && bfs(t , s)) ? "TAK" : "NIE");
	return 0;
}
```

下面是 `unordered_set` 做法。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf = 1333331;
int n , k , s , t , a[1000010];
int read()
{
	int date = 0 , w = 1;
	char c = 0;
	while(c < '0' || c > '9')
	{
		if(c == '-') w = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		date = ((date << 1) | (c ^ 48));
		c = getchar();
	}
	return date * w;
}
bool bfs(int st , int nd)
{
	if(st == nd) return 1;
	unordered_set<int> s;
	queue<int> q;
	for(int i = 1 ; i <= k ; i ++) s.insert(a[i]);
	q.push(st) , s.insert(st);
	int cnt = 1;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = 0 ; i < n ; i ++)
		{
			int v = (u ^ (1ll << i));
			if(v == nd) return 1;
			if(s.count(v)) continue;
			if((++ cnt) > n * k) return 1;
			q.push(v) , s.insert(v);
		}
	}
	return 0;
}
signed main()
{
	scanf("%lld%lld" , &n , &k);
	s = read() , t = read();
	for(int i = 1 ; i <= k ; i ++) a[i] = read();
	printf((bfs(s , t) && bfs(t , s)) ? "TAK" : "NIE");
	return 0;
}
```

---

## 作者：arundo (赞：4)

P3552 [POI2013]SPA-Walk 题解。

主要是补充一下第一个定理的证明。

还是先简述总流程。

定理 $1$. 对于 $n$ 维超立方体上的点，将其划分为两个不交集合，则两个集合之间的边数不少于两集合大小的 $\min$。

定理 $2$. 在 $n$ 维超立方体上删去 $k$ 个点后最多只有一个点数大于 $n\times k$ 的连通块。

根据以上两个定理，尝试从 $S$ 和 $T$ 分别出发 dfs，如果找到 $n\times k+1$ 个点，说明其在大连通块内，退出。否则说明在小连通块内，看找到 $T$ 没有即可。如果两边都没找到退出，那么若 $S$ 和 $T$ 都找到至少 $n\times k+1$ 个点则均在唯一大连通块内，否则不在同一连通块。

---

最后证明两个定理。

证明 $1$. 对于两个超立方体上的点，定义其之间的特殊路径为将其二进制表示后，从前往后依次更改不相同的维度所形成的路径。  
例如 $\text{SP}(1001\to 0100) = 1001\to 0001\to 0101\to 0100$。

对于任意一条边 $x\to y$，经过其的特殊路径数为 $2^{n-1}$。因为边只改了一个维度，且起点在该维度及其后与 $x$ 相同，终点在该维度及其后与 $y$ 相同，所以有 $n-1$ 个位置可以自由选择。

对于两个不交集合 $S$、$T$，不妨设 $|S|\le |T|$，则集合间的特殊路径数为 $|S||T|=|S|(2^n-|S|)$ 且 $|S|\le {2^n\over 2}$，每条特殊路径至少经过一条集合之间的边，所以边数 $\ge {|S|(2^n-|S|)\over 2^{n-1}}\ge {|S|2^{n-1}\over 2^{n-1}}=|S|$。

证明 $2$. 考虑反证法。设存在两集合都大于 $n\times k$ 个点，根据前述结论它们之间至少有 $n\times k+1
 $ 条边，而删 $k$ 个点最多删去 $n\times k$ 条边，矛盾。

---

## 作者：YLWang (赞：4)

Lemma 1：对于一个 $n$ 维超立方体，将其分为两个点集，点集之间的边个数必不少于较小点集的大小。

证明：不会。

Lemma 2：对于一个 $n$ 维超立方体，去掉 $k$ 个点后最多形成一个大小大于 $nk$ 的连通块。

证明：

设有两个集合 $S_1, S_2$ 的大小均大于 $nk$。

设 $S$ 为所有点构成的集合，则$S_2\subset S-S_1$

根据 Lemma1, 容易知道 $S_1, S-S_1$ 之间边数大于等于二者较小者大小，即 $nk+1$。

然后我们惊奇的发现我们只删了 $k$ 个节点，总共删了 $nk$ 条边，并无法将这两个连通块断开。

故得证。

故爆搜即可。注意常数。

Q：我也不知道 Lemma 1 我怎么会做呢？

A：原题题面中给了 Lemma 1。但是这儿没有。

---

## 作者：出言不逊王子 (赞：1)

先不管那个 $k$ 的限制。

假设 $n$ 等于 $1$，则现在有一条线，线上有两个点。

假设 $n$ 等于 $2$，则他在 $n=1$ 的基础上把每个点往外延伸了一遍。

$n=3$ 同理，在 $n=2$ 的基础上把每个点向外（在空间坐标里就是向上）延伸了一遍。

以此类推，我们可以发现题目中的那张图是在 $n-1$ 维的基础上往外扩张了一维得来的。

观察每个 $01$ 串，我们会发现 $n=2$ 时的 `10` 等价于 $n=3$ 时的 `010`。

所以我们可以假定从左往右数第 $1$ 位是 $0$ 的是在构造第 $n-1$ 维时本来就有的，而如果是 $1$，则他们是在此基础上扩张一维的产物，对应点就是第一位是 $0$，后面 $n-1$ 位和它相同的那个点。

所以题目的这张图就可以被看成一个 $n$ 维超立方体。

然后我们可以开始做题了。

观察原题的一个结论：

> 对于一个 $n$ 维超立方体，把它分成两个点集后它们之间的边数大于等于两个点集点数的最小值。

通过这个结论，我们考虑另一个结论：

> 对于一个 $n$ 维超立方体，删掉 $k$ 个点后最多只有一个点数大于 $nk$ 的连通块。

否则假设有两个块，它们之间的边数至少是 $nk+1$ 条，这意味着在删边时被删掉了至少 $nk+1$ 条边。

但是删一个点最多只会删掉 $n$ 条边（每一位变化一下就是一条边，一共 $n$ 位），所以我们最多删掉了 $nk$ 条边，铁寄。

---

现在我们对起点 $S$ 开始搜索，如果搜到了 $nk+1$ 个点，就说明 $S$ 在大连通块内，否则搜到的点还没这么多，就说明 $S$ 在一个小连通块内，可以直接搜到终点 $T$；

如果 $S$ 在大连通块内，说明 $T$ 也在大连通块内，开始搜 $T$，如果 $T$ 也搜到了 $nk+1$ 个点，说明它们一定在同一连通块内。

否则它们就不在一个连通块内。

但是数据很大，连 `unordered_map` 都过不去，得手写哈希。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
#define mid (l+r>>1)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const ll N=5000001,inf=1000003ll,M=1000001;//别太大 
inline ll read(){
	ll date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=(date<<1|(c^48));c=getchar();}
	return date*w;
}
struct hsht{
	struct edge{int nx;ll v;}e[N];
	int hd[inf+10];ll totm;
	void add(ll v){
		ll u=v%inf;e[++totm].v=v;
		e[totm].nx=hd[u];hd[u]=totm;
	}
	bool find(ll v){
		ll u=v%inf;
		for(int i=hd[u];i;i=e[i].nx) if(e[i].v==v) return 1;
		return 0;
	}
	hsht(){totm=0;ms(hd,0);}
}x;
ll n,k;
ll num[M],s,t;
queue<ll> q;
bool bfs(ll sp,ll ep){
	ll cnt=0;//sp在的连通块里有几个 
	if(sp==ep) return 1;
	x=hsht();
//	unordered_map<ll,bool> x;//x表示这个点有没有炸 
	fs(i,1,k,1) x.add(num[i]);
	while(!q.empty()) q.pop();
	q.push(sp);cnt++;x.add(sp);
	while(!q.empty()){
		ll u=q.front();q.pop();
		fs(i,0,n-1,1){
			ll v=(u^(1ll<<i));
			if(v==ep) return 1;
			if(x.find(v)) continue;
			cnt++;if(cnt>n*k) return 1;
			q.push(v);x.add(v);
		}
	}
	return 0; 
}
int main(){
	scanf("%lld%lld",&n,&k);
	s=read(),t=read();fs(i,1,k,1) num[i]=read();
	bool res=bfs(s,t);if(!res) return puts("NIE"),0;
	res&=bfs(t,s);if(!res) return puts("NIE"),0;
	puts("TAK");return 0;
}
//从原点开始BFS
//只要两个人的连通块都大于nk，那么就说明他们在一起
//因为n维超立方体断掉k个点最多只能形成一个> nk的连通块
//否则的话，假如有两个，则他们的边\ge nk+1 
```

---

## 作者：Tsawke (赞：1)

# LG-P3552 [POI2013]SPA-Walk Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=LG-P3552-Solution)

（建议您从上方链接进入我的个人网站查看此 Blog，在 Luogu 中图片会被墙掉，部分 Markdown 也会失效）

## 题面

存在 $ 2^n $ 个长度为 $ n $ 的 $ 01 $ 串，两个 $ 01 $ 串之间有边当且仅当两者之间仅有一位不同，或者说 $ x, y $ 之间有边当且仅当 $ x \oplus y = 2^t $。我们称这样的一个图为 $ n $ 维超立方体（n-dimensional hipercube）。现在从这其中去掉 $ k $ 个串 $ s_1, s_2, \cdots, s_k $，给定两个串 $ S, T $，求两者之间是否能够到达。

能到达输出 `TAK`，反之输出 `NIE`。

$ 1 \le n \le 60, 0 \le k \le \min(10^6, 2^n - 1), n \times k \le 5 \times 10^6 $。

## 输入格式

> n k
>
> S T
>
> $ s_1 $
>
> $ s_2 $
>
> $ \cdots $
>
> $ s_k $

（偷个懒就不写文字叙述了。。。）

## Solution

这道题我本来还以为是和 [LG-P7966 [COCI2021-2022#2] Hiperkocka](https://www.luogu.com.cn/problem/P7966) 差不多的题，[该题题解](http://blog.monkey-hyx.tech?t=COCI-2021-2022-Contest2)，按照那道题的思路想了一下然后假了，改了一下之后 T 掉了，寄，和之前的题关系不是很大，只是定义一样。

Lemma 1：对于一个 $ n $ 维超立方体，令点集为 $ S $，将其所有的点分为两个点集 $ S_1, S_2 $，$ S_1 \cup S_2 = S, S_1 \cap S2 = \phi $，则两点集之间的边集的大小一定不小于两点集之间较小者的大小，也就是 $ \left\vert \{ (u, v) \vert u \in S_1, v \in S_2, u \oplus v = 2^t \} \right\vert = \min(\left\vert S_1 \right\vert, \left\vert S_2 \right\vert) $。

证明：~~A proof is left to the reader~~.

证明：这东西大多数地方都没有人证明，甚至官方题解，感觉可以当成一个已知结论记住，关于严谨证明网上也找到了个大佬的证明（看不懂），[戳此进入](https://www.cnblogs.com/LinZhengyu/p/15518777.html)。

Lemma 2：对于一个 $ n $ 维超立方体，将其删去 $ k $ 个点后，最多仅能够形成 $ 1 $ 个点集大小大于 $ n \times k $ 的连通块。

证明：假设我们现在有两个连通块，其点集分别为 $ S_1, S_2 $，显然 $ S_1 \cap S_2 = \phi $，我们设 $ \left\vert S_1 \right\vert, \left\vert S_2 \right\vert \ge n \times k $，令点的全集为 $ S $，则显然 $ S_2 \subset S \cap \overline{S_1} $。我们又可以通过 Lemma 1 知道 $ S_1 $ 和  $ S_2 \subset S \cap \overline{S_1} $ 之间的边集大小不小于 $ \min(\left\vert S_1 \right\vert, \left\vert S \cap \overline{S_1} \right\vert) $，也就是其边集 $ E $ 满足 $ E \ge n \times k + 1 $，也就是说如果我们想要形成这两个连通块就必须要断开至少 $ n \times k + 1 $ 条边，而我们去掉 $ k $ 个点只能断开 $ n \times k $ 条边，无法形成这两个连通块，$ \square $。

于是只要有了 Lemma 2，我们就可以很容易想到，令出发点和终点分别为 $ S, T $，如果两者可以互通，那么他们要么都在唯一的大于 $ n \times k $ 的连通块内，要么在某一个小于等于 $ n \times k $ 的连通块内，所以我们只需要搜至多 $ n \times k $ 的点数，如果两者都不在小于 $ n \times k $ 的连通块中，那么一定同在唯一的大连通块中，反之如果在同一个连通块内那么一定可以被搜到。

于是我们分别从 $ S, T $ 进行爆搜，各自维护一个 `unordered_set` 记录其所在连通块有哪些点，如果从搜索过程中遇到另一个点了，则两者同在一个小连通块中，直接输出连通然后 `exit`，如果连通块大小超过 $ n \times k $ 了那么直接标记一下然后 `return`。两者都搜完后如果两个连通块都超过 $ n \times k $ 了那么一定同在一个大块，反之则一定不在同一个块，不连通。

另外个人建议把二进制转成 `long long` 再存，否则还会存在一个 hash 的复杂度，虽然我感觉好像嗯搞也能过？？？

然后写位移的时候记得写成 `1ll`。

这个的复杂度大概是 $ O(n^2k) $ 级别的，但是常数可能会很大，然后我不太确定这玩意能不能被卡成类似 $ O(2^n) $ 级别的，但是因为有 $ n \times k $ 这个限制感觉似乎是可以被严谨证明的，~~我不会~~。

A proof is left to the reader.

然后。。。[Luogu 评测记录](https://www.luogu.com.cn/record/87670127)

`unordered_set` 寄了，`cc_hash_table` 寄的更多，经典被卡常，调了亿会怎么 Luogu 上都是两个点 TLE，一个点 MLE，于是开始手搓 hash 挂链，队列之类的，最终终于在 Luogu 上把这破题给卡过去了。。。

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

/******************************
abbr
uex => unexist
******************************/

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

ll str2ll(char* s, int n){
    ll ret(0), base(0);
    for(int i = n - 1; i >= 0; --i)
        ret += (1ll << (base++)) * (s[i] == '0' ? 0 : 1);
    return ret;
}
#define MOD 2737321
struct Edge{
    Edge* nxt;
    ll val;
    OPNEW;
}eData[4145149];
ROPNEW(eData);
Edge* head[2737330];
void clear(void){memset(head, 0, sizeof(head));}
void Add(ll val){
    int idx = val % MOD;
    head[idx] = new Edge{head[idx], val};
}
bool Check(ll val){
    int idx = val % MOD;
    for(auto i = head[idx]; i; i = i->nxt)
        if(i->val == val)return true;
    return false;
}

ll S, T;
int N, K;
ll cur[5100000];
int fnt(0), til(0);
void bfs(ll S, ll T){
    fnt = til = 0;
    cur[til++] = S;
    Add(S);
    while(fnt < til){
        ll tp = cur[fnt++];
        for(int base = 0; base <= N - 1; ++base){
            ll val = tp ^ (1ll << base);
            if(val == T)printf("TAK\n"), exit(0);
            if(Check(val))continue;
            else{
                Add(val);
                cur[til++] = val;
            }
        }
        if(til > N * K)return;
    }
    printf("NIE\n"); exit(0);
}
char c[65];
vector < ll > values;
int main(){
    // freopen("in.txt", "r", stdin);
    N = read(), K = read();
    scanf("%s", c); S = str2ll(c, N);
    scanf("%s", c); T = str2ll(c, N);
    if(S == T)printf("TAK\n"), exit(0);
    for(int i = 1; i <= K; ++i){
        scanf("%s", c); ll tmpp = str2ll(c, N);
        values.push_back(tmpp);
    }
    for(auto i : values)Add(i);
    bfs(S, T);
    clear();
    for(auto i : values)Add(i);
    bfs(T, S);
    printf("TAK\n");
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

update-2022_09_27 初稿

---

## 作者：ELECTRON_wa (赞：0)

## P3552 [POI2013] SPA-Walk
[P3552](https://www.luogu.com.cn/problem/P3552 "P3552")
现在只考虑 $n$，在 $n$ 等于 $1$ 时是一条线，$n$ 变成 $2$，向外拓展一维，$n$ 每增加一维，就在当前基础上向外拓展一维（拓展前增加的位上的数字是 $0$，拓展出来增加位为一的所有数并且向原来的数连边，整体构造方法：拓展、平移、连边），所以我们可以把每一个数当作一个点，向它所能直接到达的点（只有一位不同的数）连边，得到了一个**超立方体**，下面是 $n$ 等于 $4$ 的示意图：

![](https://cdn.luogu.com.cn/upload/image_hosting/26t17lps.png)

现在描述几个性质：
1. 将 $n$ 维超立方体分成两部分，则连接两部分的边数不少于最少的那部分的点数。$\left\vert E_{middle}\right\vert \geqslant \min(\left\vert v_1\right\vert,\left\vert v_2\right\vert)$。
1. 去掉$n$维超立方体中任意$k$个点，剩下的点最多形成一个点数大于$nk+1$的连通块。$\sum_{V_i\in V-V_k}[\left\vert V_i\right\vert>nk]\leqslant 1$。

现在证明上述的性质：
1. 对于第一个性质，设一条边连接点 $x$ 和点 $y$，经过这条边只改变了一位，对于这一位，由 $x$ 拓展的部分和 $x$ 相同，由 $y$ 拓展的部分和 $y$ 相同，剩余的位可以自由组合，所以经过这条边二进制从前向后更改一共有 $2^{n-1}$ 种数，设两个不交集合为 $S,T$ 两个集合的点能互相到达的路径条数为 $\left\vert S\right\vert(2^n-\left\vert S\right\vert)$，$\left\vert S\right\vert\leqslant 2^{n-1}$，所以两个集合中间连接的边数 $\leqslant\frac{\left\vert S\right\vert(2^n-\left\vert S\right\vert)}{2^{n-1}}\leqslant\frac{\left\vert S\right\vert2^{n-1}}{2^{n-1}}=\left\vert S\right\vert$。
1. 对于第二个性质，可以假设有两个部分点数大于 $nk$，把大于 $nk$ 的部分拿出来，则连接两部分的边至少有 $nk+1$ 条，删除 $k$ 个点只能删除 $nk$ 条边，无法把两部分分开，所以不会出现大于一个的连通块点数大于 $nk+1$。

利用这两个性质就可以进行 $bfs$ 搜索，分别从给定两个点出发，向外搜索$nk+1$个点，如果给定两点在同一个小连通块中，可以直接搜索到，如果搜索完任意给定点所在的连通块找不到另一个给定点，则不能到达，否则给定两个点都在大连通块中，可以到达。（由于这道题的数据实在太大gp_hash_table寄了，需要手写哈希表）。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,k,s,t;
const int maxn=1e6+10;
ll a[maxn];
queue<ll> q;
char tmp[70];
ll trans(char *str)
{
    ll res=0;
    int len=strlen(str);
	ll k=1;
    for(int i=len-1;i>=0;i--)
    {
        if(str[i]=='1')res+=k;
        k<<=1;
    }
    return res;
}
const int mod=1234577,maxk=5e6+10;
#define LL ll
struct Hash_Map
{
    int nxt[maxk],cnt[maxk],head[mod+100],tot;
    ll val[maxk];
    void clear()
    {
    	memset(head,0,sizeof(head));
    	memset(cnt,0,sizeof(cnt));
    	memset(nxt,0,sizeof(nxt));
    	memset(val,0,sizeof(val));tot=0;
	}
    void add(int u,LL v)
    {
        tot++;
        val[tot]=v,nxt[tot]=head[u];cnt[tot]=1;
        head[u]=tot;
    }
    int Hash(LL x)
    {
        return x%mod;
    }
    void ins(LL x)
    {
        int u=Hash(x);
        for(int i=head[u];i;i=nxt[i])
        {
            if(val[i]==x)
            {
                cnt[i]++;
                return;
            }
        }
        add(u,x);
    }
    bool find(LL x)
    {
        int u=Hash(x);
        for(int i=head[u];i;i=nxt[i])
        {
            if(val[i]==x)return true;
        }
        return false;
    }
};	
Hash_Map hh;
int bfs(ll x,ll y)
{
	int cnt=0;
	if(x==y) return 1;
	hh.clear();
	for(int i=1;i<=k;i++)
	{
		hh.ins(a[i]);
	}
	while(!q.empty()) q.pop();
	q.push(x);cnt++;
	hh.ins(x);
	while(!q.empty())
	{
		ll u=q.front(); q.pop();
		for(int i=0;i<n;i++)
		{
			ll v=(u^(1ll<<i));
			if(v==y)return 1;
			if(hh.find(v))continue;
			cnt++;
			if(cnt>1ll*n*k) return 1;
			q.push(v);
			hh.ins(v);
		}
	}
	return 0;
}
int main()
{
	scanf("%lld%lld",&n,&k);
	scanf("%s",tmp);s=trans(tmp);
	scanf("%s",tmp);t=trans(tmp);
	for(int i=1;i<=k;i++)
	{
		scanf("%s",tmp); a[i]=trans(tmp);
	}
	int res=bfs(s,t);
	if(!res) {cout<<"NIE";return 0;}
	res&=bfs(t,s);
	if(!res) {cout<<"NIE";return 0;}
	cout<<"TAK";
}
```


---

