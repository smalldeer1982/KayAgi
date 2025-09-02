# Nene and the Passing Game

## 题目描述

Nene is training her team as a basketball coach. Nene's team consists of $ n $ players, numbered from $ 1 $ to $ n $ . The $ i $ -th player has an arm interval $ [l_i,r_i] $ . Two players $ i $ and $ j $ ( $ i \neq j $ ) can pass the ball to each other if and only if $ |i-j|\in[l_i+l_j,r_i+r_j] $ (here, $ |x| $ denotes the absolute value of $ x $ ).

Nene wants to test the cooperation ability of these players. In order to do this, she will hold several rounds of assessment.

- In each round, Nene will select a sequence of players $ p_1,p_2,\ldots,p_m $ such that players $ p_i $ and $ p_{i+1} $ can pass the ball to each other for all $ 1 \le i < m $ . The length of the sequence $ m $ can be chosen by Nene. Each player can appear in the sequence $ p_1,p_2,\ldots,p_m $ multiple times or not appear in it at all.
- Then, Nene will throw a ball to player $ p_1 $ , player $ p_1 $ will pass the ball to player $ p_2 $ and so on... Player $ p_m $ will throw a ball away from the basketball court so it can no longer be used.

As a coach, Nene wants each of $ n $ players to appear in at least one round of assessment. Since Nene has to go on a date after school, Nene wants you to calculate the minimum number of rounds of assessment needed to complete the task.

## 说明/提示

In the first two test cases, Nene can host two rounds of assessment: one with $ p=[1] $ and one with $ p=[2] $ . It can be shown that hosting one round of assessment is not enough, so the answer is $ 2 $ .

In the third test case, Nene can host two rounds of assessment: one with $ p=[1,3] $ and one with $ p=[2] $ . Player $ 1 $ can pass the ball to player $ 3 $ as $ |3-1|=2 \in [1+1,3+3] $ . It can be shown that hosting one round of assessment is not enough, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
5
2
1 1
1 1
2
1 1
2 2
3
1 3
1 3
1 3
5
1 1
2 2
1 5
2 2
1 1
6
1 2
5 5
2 3
2 3
2 2
1 2```

### 输出

```
2
2
2
1
3```

# 题解

## 作者：LYH_cpp (赞：9)

# [CF1956F Nene and the Passing Game](https://codeforces.com/contest/1956/problem/F)

> $T$ 组数据，每次有 $n$ 个点，给定每个点的参数 $l_{1\dots n},r_{1\dots n}$。
>
> 对于任意两个点 $i,j$，$i$ 和 $j$ 之间有边当且仅当 $|i-j|\in[l_i+l_j,r_i+r_j]$。
>
> 求连通块个数。
>
> $T\le 2\times 10^5,\sum n\le 2\times 10^6,1\le l_i\le r_i\le n$。

没什么性质，考虑从边权下手。

推一下式子可得：

> $\forall i<j,|i-j|\in[l_i+l_j,r_i+r_j]\Leftrightarrow [i+l_i,i+r_i]\cap[j-r_j,j-l_j]\neq\empty$。

这样就成功把柿子分成 $i,j$ 两部分。

设集合 $L_i=[i-r_i,i-l_i],R_i=[i+l_i,i+r_i]$。

注意到对于两个点 $i\ge j$，必然有 $i+l_i>j-l_j$，即 $R_i\cap L_j=\empty$。

那么两个点 $i,j$ 之间有边 $\Leftrightarrow (R_i\cap L_j)\cup(R_j\cap L_i)\neq \empty$。

---

考虑建虚点，点 $i$ 向虚点集合 $L_i$ 和 虚点集合 $R_i$ 连边。

但是发现如果这样建图，两个点 $i,j$ 仅通过 $L_i\cap L_j$ 或 $R_i\cap R_j$ 也是会被判做连通的。

我们考虑虚点 $x$，若 $\forall i,x\notin L_i$，那么一定不存在点 $i$ 会通过虚点 $x$ 连通，可直接删去虚点 $x$。

$R_i$ 同理。

那么最后留下的虚点满足 $\exist i,x\in L_i$ 且 $\exist j,x\in R_j$。

就不会出现上述的不合法情况。

---

最后考虑优化建图，每次连边都是连接 $x$ 和 $[y,z]$ 中每个点的形式。

直接用线段树优化建图是 $O(n\log_2 n)$ 的，时间较卡。

我们只关心连通性，所以可以先将 $x$ 连向 $y$，再将 $[y,z]$ 中的点连通。

连接 $[y,z]$ 用并查集维护一下即可。

时间复杂度 $O(n)$。

[$\texttt{Submission}$](https://codeforces.com/contest/1956/submission/256737080)

---

## 作者：251Sec (赞：6)

\*3000？\*2000！但是赛时最后 10mins 冲这题没写完赛后光速写完多少有点搞笑。

$|i-j| \in [l_i+l_j,r_i+r_j]$ 显然是二维偏序的形式，即 $i-l_i \ge j+l_j$ 且 $i-r_i \le j+r_j$。我们认为 $j$ 是修改，$i$ 是询问。最终我们要维护出连通块个数。

直接扫描线，扫掉 $i-l_i \ge j+l_j$，用一个 set 维护当前的所有连通块，按照连通块里的最小 $j+r_j$ 排序。每次从 set 取出一段前缀合并成一个连通块丢回 set 里。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T, n, l[2000005], r[2000005];
struct Node {
	int id, x, y;
	bool operator<(const Node &b) const {
		if (x != b.x) return x < b.x;
		return id < b.id;
	}
} g[4000005];
int gC, fa[2000005];
int Find(int u) { return fa[u] == u ? u : fa[u] = Find(fa[u]); }
void Merge(int u, int v) { fa[Find(u)] = Find(v); }
set<pair<int, int>> f;
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n), gC = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", l + i, r + i);
			fa[i] = i;
			g[++gC] = { i, i - l[i], -i + r[i] };
			g[++gC] = { -i, i + l[i], -i - r[i] };
		}
		sort(g + 1, g + gC + 1);
		for (int i = 1; i <= gC; i++) {
			if (g[i].id < 0) f.insert({ g[i].y, -g[i].id });
			else {
				int y = g[i].y;
				auto it = f.begin();
				int minY = 1e9;
				while (it != f.end() && it->first <= y) {
					Merge(g[i].id, it->second);
					minY = min(minY, it->first);
					it++;
				}
				if (it != f.begin()) {
					f.erase(f.begin(), it);
					f.insert({ minY, g[i].id });
				}
			}
		}
		f.clear();
		int ans = 0;
		for (int i = 1; i <= n; i++) ans += (Find(i) == i);
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：6)

## 题目大意

有 $n$ 个人站在一排，第 $i$ 个人的臂长用 $l_i,r_i$ 表示。两个人 $i,j$ 能够互相传球，当且仅当 $|i-j|\in [l_i+l_j,r_i+r_j]$。你可以提取一个序列 $a_1,a_2,...,a_m$，其中 $\forall 1\le i<m$，$a_i$ 与 $a_{i+1}$ 可以互相传球，同一个人在序列中可以多次出现。求最少提取几个序列使得 $n$ 个人都被提取过。

## 题目分析

如果 $i,j$ 可以互相传球，则连无向边 $(i,j)$，则问题相当于求连通块个数。

对于 $i<j$，连边的条件经过移项可以整理为：$i+l_i\le j-l_j$ 且 $j-r_j\le i+r_i$，即区间 $[i+l_i,i+r_i]$ 与区间 $[j-r_j,j-l_j]$ 有交。根据题意，我们称 $[i-r_i,r-l_i]$ 为 $i$ 的左手区间，$[i+l_i,i+r_i]$ 为 $i$ 的右手区间。 

到这一步都还好想，但是很难维护这个连通性的信息。

一个错误的想法是，建立 $n$ 个点表示人，另建 $n$ 个点代表位置。对于每个人 $i$，向位置点区间 $[i-r_i,i-l_i]$ 与 $[i+l_i,i+r_i]$ 连边，以位置为桥梁维护是否可以连通。

问题在于可能存在 $i<j$，$i$ 与 $j$ 两者的左手区间有交，或者两者的右手区间有交，导致 $i,j$ 通过交集连通。然而我们只希望两个人 $i<j$ 通过 $i$ 的右手区间与 $j$ 的左手区间的交连通。

而正解就是处理了这个错误。做了很妙的一步，就是只保留这样的位置点：不仅处在某个人的左手区间，也处在某个人的右手区间。显然这样操作是正确的，因为被删除的点使得不会出现上述的错误，而保留的点满足的能够通过左—右—左或者右—左—右的方式使得所有满足条件的 $(i,j)$ 都能连通。

这样暴力做的复杂度是 $O(n^2)$，注意到 $i$ 向左/右手区间连边，可以修改成 $i$ 向其中一个位置连边，然后位置区间相邻连边，复杂度降为 $O(n)$

懒得写 dfs，写了个路径压缩并查集，带个 $\log$ 也能过。

```
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =2e6+5,M=4e6+5,inf=(1LL<<31)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,a[N],b[N];
int cl[N],cr[N];
inline int getl(int x){
	if(x>n)return n+1;
	return max(x,1LL);
}
inline int getr(int x){
	if(x<1)return 0;
	return min(x,n);
}
int s[N],tp;
inline int findl(int x){//a[ans]>=x
	int l=1,r=tp,ans=tp+1;
	while(l<=r)if(s[mid]>=x)ans=mid,r=mid-1;
	else l=mid+1;
	return ans;
}
inline int findr(int x){//a[ans]<=r
	int l=1,r=tp,ans=0;
	while(l<=r)if(s[mid]<=x)ans=mid,l=mid+1;
	else r=mid-1;
	return ans;
}
bool v[N<<1];
int f[N<<1],c[N];
inline int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
inline void merge(int x,int y){
	f[find(x)]=find(y);
}
inline void Main(){
	n=read();
	repn(i)a[i]=read(),b[i]=read();
	rep(i,1,n+1)cl[i]=cr[i]=0;
	repn(i){
		int l=getl(i-b[i]),r=getr(i-a[i]);
		if(l<=r)cl[l]++,cl[r+1]--;
		l=getl(i+a[i]),r=getr(i+b[i]);
		if(l<=r)cr[l]++,cr[r+1]--;
	}
	tp=0;
	repn(i){
		cl[i]+=cl[i-1],cr[i]+=cr[i-1];
		if(cl[i]&&cr[i])s[++tp]=i;
	}
	rep(i,1,n+tp)f[i]=i;
	rep(i,1,tp)c[i]=0;
	repn(i){
		int l=findl(i-b[i]),r=findr(i-a[i]);
		if(l<=r)c[l]++,c[r]--,merge(i+tp,l);
		l=findl(i+a[i]),r=findr(i+b[i]);
		if(l<=r)c[l]++,c[r]--,merge(i+tp,l);
	}
	rep(i,1,tp){
		c[i]+=c[i-1];
		if(c[i])merge(i,i+1);
	}
	int ans=0;
	repn(i){
		int fa=find(i+tp);
		if(!v[fa])v[fa]=1,ans++;
	}
	cout <<ans<<'\n';
	rep(i,1,n+tp)v[i]=0;
}
signed main(){
	int T=read();
	while(T--)Main(); 
	return 0;
}
```

---

## 作者：Rainsleep (赞：2)

处理很妙的题，部分细节请教了[未来姚班zyl](https://www.luogu.com.cn/user/565742)和[LYH_cpp](https://www.luogu.com.cn/user/686891)，在此鸣谢。

首先考虑把题目给的式子进行转化，设 $i < j$，那么 $i$ 和 $j$ 能传球当且仅当 $l_i + l_j \le j - i \le r_i + r_j$。

移项并拆开得到，$i + l_i \le j - l_i$ 且 $i + r_i \ge j - r_j$，如果画到数轴上的话就能发现这个条件等价于 $i$ 的右半区间和 $j$ 的左半区间相交了。

如果把这种能传球的关系看作是一条边，那么不难发现，一个连通块内的所有点都能在一次计划内完成，那么答案就是连通块的个数。

于是我们有了一个 $O(n^2\alpha(n))$ 的做法，枚举两两点然后连边查答案。

考虑怎么优化，这里用到了处理连通性问题时常用的方法。

我们转换思路，从枚举人连边变成枚举人然后向它的左右区间连边，通过值域上的虚点保证连通性。

注意到这是一个经典的点 $x$ 向区间 $[l, r]$ 连边查连通块个数的做法，可行的做法有 $O(n \log n\alpha(n))$ 的线段树优化建图，以及均摊 $O(n\alpha(n))$ 的并查集做法。

>不过我们忽视了一个问题，如果通过中间点构造联通的话，会出现多个点都通过左区间或者都通过右区间相连的情况。
>
>对于这种情况，我们有这样精妙的处理：
>我们考虑只保留同时被某个点的左区间覆盖并且同时被某个点的右区间覆盖的点。
>
>这样为什么是对的呢？我们分情况来考虑。
>
>如果一个点只被左区间或者只被右区间覆盖到了，显然这个时候没有点能够通过该点进行 ``左-右`` 的联通。
>
>而如果一个点两种区间都有，那么由于题目提到了 **一个人可以在一次训练中重复多次**，那么假设覆盖的左区间分别来自 $L_1, L_2, \cdots, L_n$，右区间至少有一个，设其为 $R$，有方案 $L_1RL_2R\cdots L_nR$ 可以是一种合法的方案，并且完成了所有覆盖该点的任务。

于是我们可以用差分维护值域上的每个点是否同时被左右区间覆盖了，时间复杂度 $O(n\alpha(n))$。

```cpp
// 如果命运对你缄默, 那就活给他看。
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL; 
// #define int LL
const int maxn = 4e6 + 10;
int dl[maxn], dr[maxn], n;
int l[maxn], r[maxn];
int f[maxn];
int pr[maxn], nx[maxn], tot;
int v[maxn];
inline int find(int x) { return f[x] == x ? f[x] : f[x] = find(f[x]); }
inline void clear() {
  tot = 0;
  fill(v + 1, v + 1 + n, 0);
  fill(dl + 1, dl + 1 + n, 0);
  fill(dr + 1, dr + 1 + n, 0);
  fill(f + 1, f + n + n + 1, 0);
  fill(pr + 1, pr + 1 + n, 0);
  fill(nx + 1, nx + 1 + n, 0);
}
inline void mg(int x, int y) {
  x = find(x), y = find(y);
  if(x ^ y) f[y] = x;
}
inline void solve() {
  cin >> n;
  clear();
  for(int i = 1; i <= n; ++ i) {
    f[i] = i;
    cin >> l[i] >> r[i];
    dl[max(1, i - r[i])] ++ ;
    dl[max(1, i - l[i] + 1)] -- ;
    dr[min(n, i + l[i])] ++ ; 
    dr[min(n, i + r[i] + 1)] -- ;
  }
  for(int i = 1; i <= n; ++ i) {
    dl[i] += dl[i - 1];
    dr[i] += dr[i - 1];
    if(dl[i] && dr[i]) {
      pr[i] = nx[i] = ++ tot;
      f[n + tot] = n + tot;
    } else {
      pr[i] = pr[i - 1];
    }
  }
  nx[n + 1] = INT_MAX;
  for(int i = n; i; -- i) {
    if(!nx[i]) {
      nx[i] = nx[i + 1];
    }
  }
  for(int i = 1, ql, qr; i <= n; ++ i) {
    ql = nx[max(1, i - r[i])];
    qr = pr[max(0, i - l[i])];
    if(ql <= qr) {
      v[ql] ++, v[qr] -- ;
      mg(i, qr + n);
    }
    ql = nx[min(n + 1, i + l[i])];
    qr = pr[min(n, i + r[i])];
    if(ql <= qr) {
      v[ql] ++, v[qr] -- ;
      mg(i, qr + n);
    }
  }
  for(int i = 1; i <= tot; ++ i) v[i] += v[i - 1];
  for(int i = 1; i <= tot; ++ i) {
    if(v[i]) {
      mg(i + n, i + 1 + n);
    }
  }
  int ans = 0;
  for(int i = 1; i <= n + tot; ++ i) {
    ans += f[i] == i;
  }
  cout << ans << '\n';
}
signed main() {
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
  ios :: sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while(T -- ) solve();
  return 0;
}
```

---

## 作者：irris (赞：2)

> 图论 / 并查集 / 二维偏序

$*2200$，$6.5$。

傻逼如我，怎么想得到 $\mathcal O(n)$ 做法呢？

首先考虑我们要求的其实就是图的连通块个数。先假设图里没有环，我们统计无向边 $(i, j)$ 的条数。

这要满足

- $1 \leq i < j \leq n\ \  \tt (1)$；
- $l_i + l_j \leq j - i \leq r_i + r_j\ \  \tt (2)$。

这看起来是一个三维偏序，但是由于 $l_i \leq r_i$，你会发现 $\texttt{(2)}$ 中至少有一个不等号是被满足的，因此我们只要用 $j - 1$（满足 $\texttt{(1)}$）减去 $l_i + l_j > j - i$ 的个数再减去 $r_i + r_j < j - i$ 的个数即可。$\mathcal O(n\log n)$。

回到原问题，我们希望求连通块个数，因此我们其实不是统计固定 $j$ 的 $i$ 的个数，而是固定 $j$ 后所有 $i$ 所在不同连通块的个数。

把这个记录到树状数组里就好了，每个连通块记录一个最小的值。合并一堆特定连通块直接暴力删贡献，复杂度是均摊的。

时间复杂度不变，$\mathcal O(n\log n)$。

---

UPD：$i < j$ 是没有必要的，我们可以全部排序了处理。但是这个优化也是没有必要的。

---

## 作者：int08 (赞：0)

## 前言
怎么被卡空了啊。

挺简单的一道题，只要想清楚了，实现也不算很复杂。

# Solution
显然抽象成点之间连边，求连通块个数。

观察 $|i-j|\in [l_i+l_j,r_i+r_j]$，加上这个 $l,r$ 名字的提示，我们将问题放到数轴上研究。

发现，能连接两点的充要条件就是每个点 $x$ 画 $[x+l_i,x+r_i]$ 和 $[x-r_i,x-l_i]$ 两条线段，一个点左侧的线段和另一个点右侧的线段有交。

对于这个问题，我们考虑采用扫描线解决：在数轴上扫一个位置，用两个 `set` 维护包含这个位置的所有左侧线段和右侧线段（所属的点），然后对于每个位置，当两边集合大小都不为 $0$ 时候，就连通两个集合里所有的点。

这样连的边数是 $n^2$ 的，考虑优化。

优化是，每次连通之后，就把两边集合都缩为一个点以及它代表的连通块的 $size$（所以说现在使用 `map` 更好了），换句话说现在 `map` 里只存了每个连通块的根（称 $find(i)=i$ 的为根），然后删除和添加某条线段的时候考虑修改它的根即可。

注意扫描线直接使用 `vector<int>` 数组进行桶排序可能导致 MLE。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 2145141
int fa[N];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
struct node{
	int p,x,ty,tc;
};
bool operator <(const node &x,const node &y)
{
	if(x.p<y.p) return 1;
	if(x.p>y.p) return 0;
	return x.tc<y.tc;
}
node op[N*4];
int cnt;
int n,i,T,l[N],r[N];
map<int,int> m[2];
#define merge(x,y) fa[find(x)]=find(y)
int main()
{
	cin.tie(0)->sync_with_stdio(0);cout.tie(0); 
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(i=1;i<=n;i++)
		{
			cin>>l[i]>>r[i];
			fa[i]=i;
			if(i-l[i]>=2) op[++cnt]={i-l[i],i,1,1},op[++cnt]={max(2,i-r[i]),i,1,0};
			if(i+l[i]<=n-1) op[++cnt]={i+l[i],i,0,0},op[++cnt]={min(n-1,i+r[i]),i,0,1};
		}
		sort(op+1,op+cnt+1);
		int pnt=1;
		for(i=2;i<n;i++)
		{
			while(op[pnt].p==i&&op[pnt].tc==0) m[op[pnt].ty][find(op[pnt].x)]++,pnt++;
			if(m[0].size()&&m[1].size())
			{
				int fat=m[0].begin()->first,si=0;
				for(auto x:m[0]) merge(x.first,fat),si+=x.second;
				m[0].clear();m[0][find(fat)]=si;
				si=0;
				for(auto x:m[1]) merge(x.first,fat),si+=x.second;
				m[1].clear();m[1][find(fat)]=si;
			}
			while(op[pnt].p==i&&op[pnt].tc==1)
			{
				m[op[pnt].ty][find(op[pnt].x)]--;
				if(!m[op[pnt].ty][find(op[pnt].x)]) m[op[pnt].ty].erase(find(op[pnt].x));
				pnt++;
			}
		}
		int ans=0;
		for(i=1;i<=n;i++) if(find(i)==i) ans++;
		cout<<ans<<endl;
		for(i=0;i<=n;i++) fa[i]=l[i]=r[i]=0;
		for(i=1;i<=cnt;i++) op[i]={0,0,0,0};cnt=0;
		m[0].clear();m[1].clear();
	}
	return 0;
}
```
# The End.

---

## 作者：SamHJD (赞：0)

## Nene and the Passing Game

### Description

$n$ 个位置上每个位置站有一个球员，球员的臂展是 $[l_i,r_i]$。若球员 $i,j$ 满足 $|i-j|\in[l_i+l_j,r_i+r_j]$ 则将他们连边，求最终连通块的个数。

### Solution

将题面中的式子可视化，每个球员的手臂可以在 $[l_i,r_i]$ 范围内活动，那么连边的条件就是两个球员可以碰到，于是先求出每个球员左边和右边的臂展区域线段，称为左区间和右区间。

直接做是 $O(n^2)$ 的，但我们可以将每个线段之下的点互相连边，再给线段新编一个号并连向它覆盖的任意一个点。差分处理哪些点需要连向它的下一个点。显然这样连通性仍然是正确的。

题目限制了只有某一个左区间和某一个右区间相交才能连边，而上面的优化不能保证这一点。

一个巧妙的化解方法是忽略只被左区间或只被右区间覆盖的点，这样就避免了左区间相连或右区间相连的情况。同时不必担心某个点被数个左区间和右区间覆盖而导致错误，因为题目没有限制每个球员出现的次数，于是可以用右区间覆盖这个点的那些球员串起来左区间覆盖这个点的球员。

用并查集或者建边搜索的方法实现即可。

---

## 作者：Dovish (赞：0)

## 题解

简单转化一下，本题的意思就是按照要求建边后数连通块的数量。

我们不妨令 $j<i$，那么原式化为：
$$
l_i+l_j\le i-j\le r_i+r_j
$$
即：
$$
l_j+j\leqslant i-l_i\\
r_j+j\geqslant i-r_i\\
$$
注意这里如果 $j>i$ 是没有影响的，那我们不妨按 $l_i+i$ 的升序排序，每次往集合中放入权值为 $r_i+i$ 的点 $i$，将 $i-l_i$ 也按升序排序，合并集合中权值 $\geqslant i-r_i$ 的元素。这样，我们使第一维的偏序关系自然满足，就只用考虑第二维。

考虑到我们做的是并查集，那么我们在询问 $i$ 这个点时，集合中那些已经和前边某些节点（我们不妨设其为 $x$）合并过的点再做一次合并显得很浪费。我们其实只需要将当前点和 $x$ 合并即可。当然，这一步的前提是和 $x$ 合并了的节点中的最大的权值 $\geqslant i-r_i$。

所以我们每合并集合中的一个元素就可以将其删去，然后往集合中加入当前这个元素，这样合并次数就是 $O(n)$ 的了。

~~当然你你不怕麻烦也可以选择在 fhq 上打合并的懒标记。~~

## code
```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define lb lower_bound
#define ub upper_bound
#define rep(i,a,b) for(register int i=a;i<=b;++i)
#define low(i,a,b) for(register int i=a;i>=b;--i)
#define edge(i,u) for(int i=head[u];i;i=e[i].next)
using namespace std;
const int N=2e6+10,inf=1e9,mod=998244353;
int n,sum,T;
int l[N],r[N];
int f[N];
struct sx
{
	int val,pos;
	bool operator<(const sx&b)const
	{
		if(val!=b.val)
		return val<b.val;
		return pos<b.pos;
	}
}add[N],query[N];
int fa(int x)
{
	if(f[x]==x)return x;
	return f[x]=fa(f[x]);
}
void merge(int u,int v)
{
	int x=fa(u),y=fa(v);
	if(x>y)f[x]=y;
	else f[y]=x;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n;
		rep(i,1,n)
		{
			cin>>l[i]>>r[i];
			f[i]=i;
			add[i].pos=query[i].pos=i;
			add[i].val=l[i]+i;
			query[i].val=i-l[i];
		}
		set<sx>q;
		sort(add+1,add+n+1);
		sort(query+1,query+n+1);
		add[n+1].val=inf;
		int pos=1;
		rep(i,1,n)
		{
			q.insert(sx{add[i].pos+r[add[i].pos],add[i].pos});
			if(add[i+1].val!=add[i].val)//放入一整托再询问 
			{
				while(query[pos].val<add[i].val&&pos<=n)pos++;
				set<sx>ls;
				while(query[pos].val<add[i+1].val&&pos<=n)
				{
					int base=query[pos].pos-r[query[pos].pos];
					auto g=q.lower_bound(sx{base,0});
					if(g!=q.end())ls.insert(sx{g->val,query[pos].pos});
					pos++;
				}
				if(ls.size())
				{
					int p=ls.begin()->pos;
					int base=ls.begin()->val;
					int maxn=q.rbegin()->val;//数据压缩，保留最大值 
					for(auto u=q.rbegin();u!=q.rend();u++)
					{
						if(u->val>=base)
						merge(u->pos,p);
						else break;
					}
					auto v=q.lower_bound(sx{base,0});
					while(v!=q.end())
					{
						auto last=v;
						v++;
						q.erase(last);
					}
					q.insert(sx{maxn,ls.begin()->pos});//替换 
					for(auto u:ls)
					merge(u.pos,p);
				}
			}
		}
		int ans=0;
		rep(i,1,n)if(i==fa(i))ans++;
		cout<<ans<<'\n';
	}
}
```

---

