# Continuous City

## 题目描述

Some time ago Homer lived in a beautiful city. There were $ n $ blocks numbered from $ 1 $ to $ n $ and $ m $ directed roads between them. Each road had a positive length, and each road went from the block with the smaller index to the block with the larger index. For every two (different) blocks, there was at most one road between them.

Homer discovered that for some two numbers $ L $ and $ R $ the city was $ (L, R) $ -continuous.

The city is said to be $ (L, R) $ -continuous, if

1. all paths from block $ 1 $ to block $ n $ are of length between $ L $ and $ R $ (inclusive); and
2. for every $ L \leq d \leq R $ , there is exactly one path from block $ 1 $ to block $ n $ whose length is $ d $ .

A path from block $ u $ to block $ v $ is a sequence $ u = x_0 \to x_1 \to x_2 \to \dots \to x_k = v $ , where there is a road from block $ x_{i-1} $ to block $ x_{i} $ for every $ 1 \leq i \leq k $ . The length of a path is the sum of lengths over all roads in the path. Two paths $ x_0 \to x_1 \to \dots \to x_k $ and $ y_0 \to y_1 \to \dots \to y_l $ are different, if $ k \neq l $ or $ x_i \neq y_i $ for some $ 0 \leq i \leq \min\{k, l\} $ .

After moving to another city, Homer only remembers the two special numbers $ L $ and $ R $ but forgets the numbers $ n $ and $ m $ of blocks and roads, respectively, and how blocks are connected by roads. However, he believes the number of blocks should be no larger than $ 32 $ (because the city was small).

As the best friend of Homer, please tell him whether it is possible to find a $ (L, R) $ -continuous city or not.

## 说明/提示

In the first example there is only one path from block $ 1 $ to block $ n = 2 $ , and its length is $ 1 $ .

In the second example there are three paths from block $ 1 $ to block $ n = 5 $ , which are $ 1 \to 2 \to 5 $ of length $ 4 $ , $ 1 \to 3 \to 5 $ of length $ 5 $ and $ 1 \to 4 \to 5 $ of length $ 6 $ .

## 样例 #1

### 输入

```
1 1```

### 输出

```
YES
2 1
1 2 1```

## 样例 #2

### 输入

```
4 6```

### 输出

```
YES
5 6
1 2 3
1 3 4
1 4 5
2 5 1
3 5 1
4 5 1```

# 题解

## 作者：Acfboy (赞：8)

一道有趣的构造题。

原有的题解都只讲了构造方法，没有做其它说明，看上去不明不白的，所以搞懂后自己写一篇。讲得比较详细。

## 情况一

$L = 1,  R = 2^k-1$ 时

因为要构造 $[1, 2^k]$ 每个数字各一个，而数据范围中点数又是 $32$, 启发我们进行二进制拆分。

另第 $i$ 个点表示 $2^i$，$i$ 走到 $i+1$ 就是这一位取上，不走就是不取上，所以从 $i$ 号点对所有大于 $i$ 的点连上一条 $2^i$ 的边，这样所有的走法就对应着每一个二进制位取不取，即 $00...001$ 到 $111...111$， 就是要求的 $[1, 2^k-1]$。如图。

[![6f4gUK.png](https://s4.ax1x.com/2021/03/20/6f4gUK.png)](https://imgtu.com/i/6f4gUK)

注意题目中要求点是从 $1$ 开始的。

## 情况二

$L=1,R = 2^k+t$

那么如果不是恰好的 $2^k-1$ 怎么办呢? 考虑新开一个节点。

我们原来的图显然有这样一个性质，那就是从开始的节点到每一个节点 $i$ 满足有长度为 $[1,2^i-1]$ 恰好一条，所以对于 $R$ 的二进制，从某一位开始截断向后的 $00...000$ 到 $11..111$ 都是有的，举个例子，如果 $R$ 的二进制是 $101000$, 那么路径就必然包含长度 $[100000, 100111]$ 的，而我们的 $2$ 号节点恰好是满足起始点到它的路径 $[001, 111]$ 的，所以对于 $[100001, 100111]$， 只需要连一条 $2$ 号点到新来的那个点，长度为 $100000$ 的就可以了。

那问题来了，这样一来我们就没有长度为 $100000$ 和 $101000$ 的这样两条路径了啊！原因是我们第一步中做的 $[1, 2^k-1]$ 的做法没有包含左($0$)右($2^k$)端点，我们需要让其包含一个端点以覆盖所有情况。

改为 $[1,2^k]$ 可以采用这样一个方法：把所有节点向后移一个编号，从新的起始点向所有的节点连一条长度为 $1$ 边。

但对于最大的一位，前面没有东西了，这样一连有一条长度为 $0$ 的边，但长度不能为 $0$, 为了解决这个问题，可以把 $R$ 减去 $1$ 的加边法做出来，再给每一个边加上一个 $1$。

对于上面那副图，若我们的输入是 $10$(即 $(1010)_2$), 那么就是这样子的了（经过加边和上述的修正后，并将节点从 $1$ 开始编号）

(省略了 $1$ 开始的边，不然图太糊了)

[![6fIOXj.png](https://s4.ax1x.com/2021/03/20/6fIOXj.png)](https://imgtu.com/i/6fIOXj)

## 情况三

用情况二构造一个 $L = 1, R' = R-L+1$ 的图，再开一个新节点，加一条原来最后一个节点到他的，长度为 $L-1$ 的边就可以了。

## 代码

需要处理一些节点编号与幂之间关系的细节。

```cpp
#include <cstdio>
#include <vector>
int L, R;
struct twt { int u, v, c; };
std::vector<twt> edge;
void add(int u, int v, int c) {	edge.push_back((twt){u, v, c}); }
int solve(int L, int R) {
	if(L > 1) { // 情况三
		int n = solve(1, R-L+1);
		add(n, n+1, L-1);
		return n+1;
	}
	if((R & -R) == R) { // ex情况一
		int k = 0, R_ = R;
		while(R_) R_ /= 2, k++;
		k--;
		add(1, 2, 1);
		for(int i = 3; i <= k+2; i++) {
			add(1, i, 1);
			for(int j = 2; j < i; j++) add(j, i, (1 << (j-2)));
		}
		return k+2;
	}
	int n = 0; // 情况二
	while(1 << (n+1) <= R-1) n++;
	solve(1, 1 << n);
	add(1, n+3, 1);
	for(int i = 0; i <= n; i++)
		if((R-1) >> i & 1) 
			add(i+2, n+3, 1 + ((R - 1) >> (i + 1) << (i + 1)));
	return n+3;
}
int main() {
	scanf("%d%d", &L, &R);
	puts("YES");
	int n = solve(L, R);
	printf("%d %d\n", n, (signed)edge.size());
	for(int i = 0; i < (signed)edge.size(); i++) printf("%d %d %d\n", edge[i].u, edge[i].v, edge[i].c);
} 
```

---

## 作者：Lynkcat (赞：8)

经典套路，考虑二进制。

先考虑构造 $1$ 到 $2^{k-1}$ 的答案。

我们考虑设走到第 $i$ 个点上表示下一位二进制要选 $2^{i-2}$ 。第一个点用来选最小的那一位二进制，最后一个点结束。那么连边方案就非常简单了。每一位往后面的位连长度位 $2^{i-2}$ 的边。然后再从第一个点连向所有点就得到了 $1$ ~ $2^k$ 的答案。

再考虑再开一个点。我们发现其一定是 $1001……100100$ 的形式，我们想象一下对每个 $1$ 分层，那么显然我们从高位往低位做，把每一层的答案加上比它还低的层的总和连向最后一个点。

然后再开一个点，用来加上 $L-1$ 就行。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
#define int ll
//#define N
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int L,R,l,r,t,sum,ans,ans1;
vector<pa>G[100005];
signed main()
{
	L=read(),R=read();
	l=1,r=R-L+1;
	t=log2(r)+2;
	for (int i=2;i<=t;i++) G[1].push_back({i,1}),ans++;
	for (int i=2;i<=t;i++)
		for (int j=i+1;j<=t;j++)
			G[i].push_back({j,(1ll<<(i-2))}),ans++;
	sum=0;
	r--;
	G[1].push_back({t+1,1}),ans++;
	for (int i=t-1;i>=1;i--)
	{
		sum+=(1ll<<(i))*(((1ll<<i)&r)>0);
		if ((1ll<<(i-1))&r) 
		{
			G[i+1].push_back({t+1,sum+1}),ans++,ans1++;
		}
	}
	if (L!=1)
	{
		puts("YES");
		writesp(t+2);writeln(ans+1);
		for (int i=1;i<=t+1;i++)
		{
			for (auto u:G[i])
				writesp(i),writesp(u.first),writeln(u.second);
		}
		writesp(t+1),writesp(t+2),writeln(L-1);
	} else
	{		
		puts("YES");
		writesp(t+1);writeln(ans);
		for (int i=1;i<=t+1;i++)
		{
			for (auto u:G[i])
				writesp(i),writesp(u.first),writeln(u.second);
		}
	}
}
/*

*/



---

## 作者：清烛 (赞：3)

来一发讲得更清楚些的题解。

题意翻译成人话就是 $1\to n$ 的路径需要恰好有 $R - L + 1$ 条并且权值刚好覆盖了 $[L,R]$ 的区间。

注意到 $n\le 32$ 有点二进制的意思？说明我们是不是可以往用二进制位来拼凑整数的方向去想？

考虑构造 $[1, 2^{k}]$ 的答案，令经过 $i$ 号点表示选上 $2^{i-2}$，将 $i$ 号点向后面所有边连上权为 $2^{i-2}$ 的边，再从 $1$ 向后面所有点连权为 $1$ 的边，那么从 $1$ 到 $k+2$ 的所有路径就都对应了 $[1,2^k]$ 里面的每一个数。点的标号平移两位是因为 $1$ 要做起点。

对于 $R\ne 2^k$ 的情况，令其为 $2^k + t$，其中 $2^{k+1}>R$。刚才的图中有一个性质，就是对于 $i$ 号点（$i>1$），$1\to i$ 的所有路径里面是恰好覆盖了 $[1, 2^{i-2}]$ 的。并且若我们令 $R$ 的二进制表示为 $(R_kR_{k-1}\cdots R_1R_0)_2$，则对于 $R_j=1$，将该位设为 $0$ 的话低位就可以任意覆盖的。

就例如 $R = (111010)_2$，关注 $R_3 = 1$，发现 $[(110000)_2, (110111)_2]$ 都是可以取到的（第 $0$ 到 $2$ 位任意取），这启发我们从 $j+2$ 号点连边向一个新点 $k+3$，边权为更高位上的值之类的想法。但是这样会出现一些细节上的遗漏，因为形如 $(110000)_2$ 就是没能覆盖到的，因为 $j+2$ 号点覆盖的是 $[1, 2^{j}]$，有一个 $0$ 的下界没被覆盖，而 $2^{j}$ 的上界又恰好多覆盖了一位。

这启发我们 $R\leftarrow R - 1$，这样子就刚好把上述问题全部修复了，$1\to k+3$ 的所有路径就能覆盖整个区间了，形式化地我们连边 $(j+2,k+3,1+\sum\limits_{n\ge j}R_n2^n)$。

最后对于 $L\ne 1$，直接先建出 $[1,R - L + 1]$ 的图，新开一个节点再接上一条 $L - 1$ 的边即可。

```cpp
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 1e6 + 5;
vector<tuple<int, int, int>> ans;
int l, r, n;

int main() {
    cin >> l >> r;
    r = r - l + 1;
    int k = 31 - __builtin_clz(r); // 最高位
    n = k + 2;
    FOR(i, 0, k) FOR(j, i + 1, k) ans.emplace_back(i + 2, j + 2, 1 << i);
    FOR(i, 0, k) ans.emplace_back(1, i + 2, 1);
    if (__builtin_popcount(r) > 1) {
        --r, ans.emplace_back(1, ++n, 1);
        FOR(i, 0, k) if ((1 << i) & r) {
            int tmp = 0;
            FOR(j, i + 1, k) tmp |= ((1 << j) & r);
            ans.emplace_back(i + 2, n, 1 + tmp);
        }
    }
    if (l != 1) ans.emplace_back(n, n + 1, l - 1), ++n;
    cout << "YES\n" << n << ' ' << ans.size() << endl;
    for (auto &x : ans) {
        int i, j, k; tie(i, j, k) = x;
        cout << i << ' ' << j << ' ' << k << endl;
    }
    return 0;
}
```

---

## 作者：lightup37 (赞：2)

### CF1480E

### 题意

  给定 $L, R$. 构造一个有向带权图, 其中点数不大于 32, 且所有边都是从较小的点指向较大的点. 假设这个有向图有 $n$ 个点, 你需要保证从 $1$ 到 $n$ 的所有路径的权值都在 $[L, R]$ 内且不存在 $x\in [L, R]$, 使得不存在或存在多于一条从 $1$ 到 $n$ 的路径权值为 $x$, 或者断言这是不可能的.

### 输入格式

  仅一行两个正整数 $L, R$.

### 输出

  第一行一个字符串为 "YES" (存在一个符合要求的图) 或者 "NO".

  第二行两个正整数 $n, m$, 表示你构造的图的点数和边数.

  接下来 $m$ 行, 每一行包括三个正整数 $u_i, v_i, t_i$, 表示第 $i$ 条边的起点, 终点和边权.

### 题解

  考虑先解决 $L=1, R=2^k$ 时的问题. 我们建立点 $2, 3, \cdots k+2$, 对于 $2\leq i < j \leq k+2$, 我们连边 $(i, j, 2^{i-2})$. 然后连边 $(1, i, 1)$ 对所有 $i\in [2, k+2]$. 容易发现这样就是一个对于 $L=1, R=2^k$ 的合法的图.
  对于 $L=1, R=2^k+t(2^{k+1}>R, 0\leq t)$ 的情况, 我们新增一个点 $k+3$, 不妨设 $R-1 = \sum\limits_{i=0}^{+\infty} 2^iR_i$ 且 $R_i \in {0, 1}$. 然后对于 $i\in [1, k+1]$, 如果 $R_{i-1}=1$, 连边 $(i+1, k+3, 1+\sum\limits_{j=i}^{+\infty} R_j2^j)$. 注意到连上这些边后, 我们就构造了一个对于这样的 $L, R$ 的合法的图.

  接下来, 我们考虑 $L, R$ 都任取的情况: 我们只需要构造一个 $L=1, R=R-L+1$ 的图, 然后在它的最后一个点后增加一个新点, 在他们间连一条边权为 $L-1$ 的边.

### 代码

```cpp
#include<bits/stdc++.h>
#define f(i,x,y) for(int i=x, i##end=y; i<=i##end; ++i)
#define d(i,x,y) for(int i=y, i##end=x; i>=i##end; --i)
#define int long long
#define ll long long
char ch;
int rd() {
  int f=1, x=0; ch=getchar();
  while(!isdigit(ch)) { f=((ch=='-')?-1:f); ch=getchar(); }
  while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
  return x*f;
}
void rd(int& x) { x=rd(); }
using namespace std;
#define _ 100005
int s=1, t, val[32], tot=1;
struct edges {
	int u, v, w;
} E[_]; int totE;
void add(int u, int v, int w) {
	E[++totE].u=u; E[totE].v=v; E[totE].w=w;
}
void solve(int r) { // solve({1..r}), where r = 2^k
	int tmp=1, k=0; while(tmp!=r) { tmp=tmp*2; ++k; }
	add(s, ++tot, 1);
	f(i,3,k+2) {
		add(s, ++tot, 1);
		f(j,2,i-1) add(j, i, 1<<(j-2));
	}
}
void solvesolve(int r) {
	int tmp=1, k=0; while(tmp*2<=r) { tmp=tmp*2; ++k; }
	solve(tmp); if(tmp==r) return; add(1, ++tot, 1); f(i,1,k+1) if((r-1)&(1<<(i-1))) add(i+1, tot, 1+((r-1)>>i<<i));
}
void solve(int l, int r) {
	if(l==1) solvesolve(r);
	else {
		solvesolve(r-l+1); add(tot, tot+1, l-1); ++tot;
	}
}
void print() {
	printf("%lld %lld\n", tot, totE);
	f(i,1,totE) printf("%lld %lld %lld\n", E[i].u, E[i].v, E[i].w);
}
int l, r;
signed main() {
  rd(l); rd(r); puts("YES"); solve(l, r); print();
  return 0;
}
```

---

