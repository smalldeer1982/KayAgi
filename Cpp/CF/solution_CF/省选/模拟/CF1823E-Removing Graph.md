# Removing Graph

## 题目描述

# 移除图


Alice 和 Bob 在一张图上玩游戏。给定一个无向图，图中的每个顶点的度数都等于 2，不存在自环和重边。该图可能由多个连通分量组成。注意，如果该图有 $ n $ 个顶点，则它一定有 $ n $ 条边。

Alice 和 Bob 轮流进行操作。Alice 先开始。在每一轮中，玩家可以选择一个包含 $ k $ 个顶点的连通子图（$ l \leq k \leq r $，$ l < r $），并将这些顶点及其相邻的边从图中移除。

不能进行操作的玩家失败。

例如，假设他们在给定的图上进行游戏，并且 $ l = 2 $，$ r = 3 $：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1823E/9583c48ed07ed156db67a86c4c0f07d06f492c6b.png)Alice 第一次移除的有效顶点集可以是以下之一：

- $ \{1, 2\} $
- $ \{1, 3\} $
- $ \{2, 3\} $
- $ \{4, 5\} $
- $ \{4, 6\} $
- $ \{5, 6\} $
- $ \{1, 2, 3\} $
- $ \{4, 5, 6\} $

假设 Alice 移除子图 $ \{4, 6\} $，则 Bob 第一次移除的有效顶点集可以是以下之一：

- $ \{1, 2\} $
- $ \{1, 3\} $
- $ \{2, 3\} $
- $ \{1, 2, 3\} $

假设 Bob 移除子图 $ \{1, 2, 3\} $，Alice 无法进行操作，所以 Alice 失败。

给定一个大小为 $ n $ 的图和整数 $ l $ 和 $ r $。如果 Alice 和 Bob 都采取最优策略，谁将获胜。

## 样例 #1

### 输入

```
6 2 3
1 2
2 3
3 1
4 5
5 6
6 4```

### 输出

```
Bob```

## 样例 #2

### 输入

```
6 1 2
1 2
2 3
3 1
4 5
5 6
6 4```

### 输出

```
Bob```

## 样例 #3

### 输入

```
12 1 3
1 2
2 3
3 1
4 5
5 6
6 7
7 4
8 9
9 10
10 11
11 12
12 8```

### 输出

```
Alice```

# 题解

## 作者：Fido_Puppy (赞：10)

## 题目链接

[CF1823E Removing Graph](https://codeforces.com/contest/1823/problem/E)

## 题解

看到博弈论后先想一下 $\text{SG}$ 函数。

由于图中每一个点的度数有恰好为 $2$，所以整张图一定是若干个环拼成的。

然后这题有两种局面，一种是一个环，一种是一条链（将环断开后形成的）。

我们先考虑一条链的 $\text{SG}$ 函数，设长度为 $i$ 的链的 $\text{SG}$ 函数为 $f_i$。

$$f_i = 0 \qquad (\forall i < l)$$

显然如果长度 $< l$ 了就不能取了。

$$f_i = \operatorname{mex}_{j \in [l, r], k \in [0, i - j]} \left( f_k \oplus f_{i - j - k} \right) \qquad (\forall i \ge l)$$

意义就是一条长度为 $i$ 的链可以从中间取一段长度为 $j$ 的链，将其断成长度分别为 $k$ 和 $i - j - k$ 的链，两条链的局面就是两个 $\text{SG}$ 函数异或起来。

于是链的 $\text{SG}$ 函数就可以确定了。

然后考虑环的 $\text{SG}$ 函数，设大小为 $i$ 的环的 $\text{SG}$ 函数为 $g_i$。

$$g_i = \operatorname{mex}_{j \in [l, r]} f_{i - j}$$

就是一个大小为 $i$ 的环，取了 $j$ 个点后，就变成了一条长度为 $i - j$ 的链。

最终整张图的 $\text{SG}$ 函数就是将每个环的 $\text{SG}$ 函数异或起来，如果是 $0$ 则后手必胜，否则先手必胜。

然后就可以直接爆算 $\text{SG}$ 函数了，但是时间复杂度炸了，无法通过。

然后发现不会更加牛的算法，所以考虑打表。

## 打表程序

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, l, r, sg[200005], sg2[200005];
int f[200005], siz[200005];
int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}
void merge(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) {
		f[fx] = fy;
		siz[fy] += siz[fx], siz[fx] = 0;
	}
}
int main() {
	ios :: sync_with_stdio(0), cin.tie(0);
	cin >> n >> l >> r;
	for (int i = 0; i < l; ++i) {
		sg[i] = 0;
	}
	auto mex = [&] (vector <int> &V) -> int {
		sort(V.begin(), V.end());
		int p = 0;
		for (int i = 0; i < V.size(); ++i) {
			if (V[i] == p) ++p;
			else if (V[i] > p) return p;
		}
		return p;
	};
	for (int i = l; i <= n; ++i) {
		vector <int> V;
		for (int j = l; j <= r; ++j) {
			for (int k = 0; k + j <= i; ++k) {
				V.push_back(sg[k] ^ sg[ i - j - k ]);
			}
		}
		sg[i] = mex(V);
	}
	for (int i = 1; i <= n; ++i) {
		vector <int> V;
		for (int j = l; j <= r; ++j) {
			if (i >= j) V.push_back(sg[ i - j ]);
		}
		sg2[i] = mex(V);
	}
	iota(f + 1, f + n + 1, 1);
	fill(siz + 1, siz + n + 1, 1);
	for (int i = 1; i <= n; ++i) {
		int u, v; cin >> u >> v;
		merge(u, v);
	}
	int Z = 0;
	for (int i = 1; i <= n; ++i) {
		Z ^= sg2[ siz[i] ];
	}
	if (Z) cout << "Alice\n";
	else cout << "Bob\n";
	return 0;
}
```

考场上实现的一个打表程序，实现比较烂。

然后打出表后发现链的 $\text{SG}$ 函数至少我没有找出规律，但是环的 $\text{SG}$ 函数规律非常明显。

具体地，就是：

$$\begin{cases} g_i = \lfloor \dfrac{i}{l} \rfloor \qquad (i < l + r) \\ g_i = 0 \qquad (i \ge l + r)\end{cases}$$

然后就可以直接算 $\text{SG}$ 函数了，时间复杂度 $\Theta(n)$，题解中的实现复杂度瓶颈在于并查集。

## 代码链接

<https://codeforces.com/contest/1823/submission/203762498>

---

## 作者：honglan0301 (赞：6)

## 题目分析

[题目传送门](https://www.luogu.com.cn/problem/CF1823E)。我看现在题解里还没有对结论的证明，来补充一下。

首先发现不同环之间互不影响，且一个环的状态只取决于它的大小。于是显然要根据大小快速算 $\text{sg}$ 函数。

那么因为环会断成链，链会断成两条链，所以设 $h_i$ 表示大小为 $i$ 的环的 $\text{sg}$ 函数值，$g_i$ 表示长为 $i$ 的链的 $\text{sg}$ 函数值。朴素的转移有 $h_i=\mathop{\text{mex}}\limits_{j=i-r}^{i-l} g_i,\ g_i=\mathop{\text{mex}}\limits_{j=i-r,k\leq j}^{i-l} \{g_k\bigoplus g_{j-k}\}$，其中初值是对于 $\forall i< l$ 有 $g_{i}=0$。经过打表之后容易发现结论是：

$$ h_i=\left\{
\begin{aligned}
& \lfloor \frac{i}{l}\rfloor\ \ \ (i< l+r)\\
& 0\ \ \ (i\geq l+r)\\
\end{aligned}
\right.
$$

下面我们尝试进行证明。先看链的部分：

1. 考虑归纳证明当 $i<l+r$ 时 $g_i=\lfloor \frac{i}{l}\rfloor$。假设 其对 $i\leq p-1$ 时成立，然后 $p$ 时的证明可以分如下的两步。

	先发现 $g_k\bigoplus g_{j-k}\leq g_k+g_{j-k}=\lfloor \frac{k}{l}\rfloor+\lfloor \frac{j-k}{l}\rfloor\leq \lfloor \frac{j}{l}\rfloor$，故 $g_{p}=\mathop{\text{mex}}\limits_{j=p-r,k\leq j}^{p-l} \{g_k\bigoplus g_{j-k}\}\leq \lfloor \frac{p-l}{l}\rfloor+1=\lfloor \frac{p}{l}\rfloor$。
    
   再发现 $k=0$ 时 $g_{j-k}$ 能够取到 $[g_{p-r},g_{p-l}]$ 中的每个数，故 $g_p\geq \mathop{\text{mex}}\limits_{j=p-r}^{p-l} g_j+1=\lfloor \frac{p}{l}\rfloor$。
   
   于是有 $g_p=\lfloor \frac{p}{l}\rfloor$ 成立，得证。
   
2. 考虑证明当 $i\geq l$ 时有 $g_i>0$。这是简单的，因为 $l\neq r$，故不管 $i$ 的奇偶性总能找到一个 $j$ 满足 $i-r\leq j\leq i-l,\ j\equiv 0\pmod 2$。此时令 $k=\frac{j}{2}$，有 $g_k \bigoplus g_{j-k}=g_k \bigoplus g_{k}=0$，故 $g_i=\text{mex}>0$。

再看环的部分：

1. 考虑 $i\geq l+r$ 时，显然根据上面的结论 $\forall j∈[i-r,i-l]$ 都有 $g_j>0$，故此时 $h_i=\text{mex}=0$。

2. $i<l+r$ 时，此时上面证过对于 $\forall i∈[i-r,r-l]$ 有 $g_i=\lfloor \frac{i}{l}\rfloor$。故放在 $\text{mex}$ 中的 $g_j$ 形成了一个区间 $[0,g_{i-l}]$，故此时 $h_i=\text{mex}=g_{i-l}+1=\lfloor \frac{i-l}{l}\rfloor+1=\lfloor \frac{i}{l}\rfloor$。

于是结论得证。只需找出每个简单环，时间复杂度 $O(n)$，结论题不放代码了。

---

## 作者：tybbs (赞：3)

本题另外一篇有证明的题解证明有些问题。

博弈论问题，考虑 SG 函数。记 $f_i$ 为长为 $i$ 的链的 SG 值，$g_i$ 为长为 $i$ 的环的 SG 值。

得到转移：
1. $f_i=mex \left\{ f_a\oplus f_b \right\}$，其中 $i-r\le a+b \le i-l$。表示把长为 $i$ 的链切为长为 $a$ 和 $b$ 的链。
2. $g_i=mex\left\{ f_j \right\}$，其中 $i-r\le j\le i-l$。表示把长为 $i$ 的环切为一条长为 $j$ 的链。

打表得到 $g_i=\begin{cases} \lfloor \frac{i}{l} \rfloor & i<l+r \\ 0 & i\ge l+r\end{cases}$

证明： 先证明当 $\forall i<l+r$，$f_i=\lfloor \frac{i}{l}\rfloor$。归纳证明，$i=0$ 显然成立，假设其对 $j<i$ 成立。

1. $f_i\le \lfloor \frac{i}{l}\rfloor$。因为 $f_a\oplus f_b \le f_a+f_b=\lfloor \frac{a}{l}\rfloor+\lfloor\frac{b}{l}\rfloor\le \lfloor\frac{a+b}{l}\rfloor\le\lfloor\frac{i}{l}\rfloor-1$，所以 $f_i\le \max \left\{ f_a\oplus f_b \right\}+1\le \lfloor \frac{i}{l}\rfloor$。
2. $f_i \ge \lfloor \frac{i}{l}\rfloor$。当 $a<l$，$f_a=0$。此时 $b$ 取遍 $\max\left\{ 0,i-l-r \right\}$ 到 $i-l$。故 $f_a\oplus f_b$ 可以取遍 $f_{\max\left\{ 0,i-l-r \right\}}$ 到 $f_{i-l}$。由于 $i<l+r$，其可以取遍 $0$ 至 $\lfloor \frac{i-l}{l} \rfloor$，所以 $f_i\ge \lfloor\frac{i-l}{l}\rfloor+1=\lfloor \frac{i}{l}\rfloor$。

故 $f_i=\lfloor \frac{i}{l} \rfloor$。  
再证明当 $i>l$，$f_i>0$。由于 $l>r$，$i-r$ 到 $i-l$ 之间必有一个偶数，可取 $a=b$。 

根据上述结论，当 $i<l+r$，$mex$ 中的 $f_i$ 可以取遍 $[0,\lfloor \frac{i-l}{l} \rfloor]$，所以 $g_i=\lfloor \frac{i-l}{l} \rfloor+1=\lfloor \frac{i}{l} \rfloor$。
当 $i>l+r$，$mex$ 中的 $f_i$ 无法取到 $0$，故 $g_i=0$。

最会求出所有 $g_i$ 的异或和即可判断胜负。代码略。

---

## 作者：ifffer_2137 (赞：2)

吐了，第一眼看的是基环森林。
### 题意
若干个环，两人轮流每次选一个大小在 $[l,r]$ 内的连通块删去，不能操作者负，判断赢家。
### 分析
首先 dsu 把环的大小全求出来存好。

看着就是 Nim 博弈，所以上 SG 函数，容易发现一个环删过一次就变成链，而链只会变成更多的链，所以先暴力枚举删的位置和长度，打一下链的 SG 函数表：
```cpp
for(int i=0;i<=n;i++){
    memset(vis,0,sizeof(vis));
    for(int j=L;j<=R&&j<=i;j++) for(int k=0;k<=i-j;k++) vis[sgl[k]^sgl[i-j-k]]=1;
    for(sgl[i]=0;vis[sgl[i]];sgl[i]++);
}
```
很遗憾并没有发现什么规律。但没有关系我们要的是环，所以再暴力打一下环的表：

```cpp
for(int i=0;i<=n;i++){
    memset(vis,0,sizeof(vis));
    for(int j=L;j<=R&&j<=i;j++) vis[sgl[i-j]]=1;
    for(sgr[i]=0;vis[sgr[i]];sgr[i]++);
}
```
发现后面一车 $0$，这不 win 了。

多换几个 $l,r$ 试一下就会发现只有 $x<l+r$ 的时候才有可能非 $0$，并且 SG 函数值为 $\lfloor \frac{x}{l} \rfloor$，全部 xor 起来就搞定了。

时间复杂度 $O(n\log n)$，瓶颈是并查集。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
#define arr(x) array<int,x>
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
	return w==1?x:-x;
}
inline bool getmn(auto &x,auto y){if(y<x)return x=y,1;return 0;}
inline bool getmx(auto &x,auto y){if(y>x)return x=y,1;return 0;}
mt19937 rnd(time(NULL));
constexpr int maxn=2e5+5;
constexpr int mod=998244353;
class DSU{
private:
	int fa[maxn],siz[maxn];
public:
	void init(int n){for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;}
	int fd(int x){return fa[x]==x?x:fa[x]=fd(fa[x]);}
	int get(int x){return siz[x];}
	bool merge(int x,int y){
		x=fd(x),y=fd(y);if(x==y)return 0;
		fa[x]=y,siz[y]+=siz[x];return 1;
	}
}dsu;
int n,m,L,R,ans;
int a[maxn];
signed main(){
	#ifdef LOCAL
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read(),L=read(),R=read();
	dsu.init(n);
	for(int i=1;i<=n;i++){
		int u=read(),v=read();
		dsu.merge(u,v);
	}
	for(int i=1;i<=n;i++) if(dsu.fd(i)==i) a[++m]=dsu.get(i);
	for(int i=1;i<=m;i++){
		int sg=(a[i]<L+R?a[i]/L:0);
		ans^=sg;
	}
	puts(ans?"Alice":"Bob");
	//cerr<<1.0*clock()/CLOCKS_PER_SEC<<'\n';
	return 0;
}
```

---

