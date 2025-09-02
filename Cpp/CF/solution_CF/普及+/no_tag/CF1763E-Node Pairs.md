# Node Pairs

## 题目描述

Let's call an ordered pair of nodes $ (u, v) $ in a directed graph unidirectional if $ u \neq v $ , there exists a path from $ u $ to $ v $ , and there are no paths from $ v $ to $ u $ .

A directed graph is called  $ p $ -reachable if it contains exactly $ p $ ordered pairs of nodes $ (u, v) $ such that $ u < v $ and $ u $ and $ v $ are reachable from each other. Find the minimum number of nodes required to create a $ p $ -reachable directed graph.

Also, among all such $ p $ -reachable directed graphs with the minimum number of nodes, let $ G $ denote a graph which maximizes the number of unidirectional pairs of nodes. Find this number.

## 说明/提示

In the first test case, the minimum number of nodes required to create a $ 3 $ -reachable directed graph is $ 3 $ . Among all $ 3 $ -reachable directed graphs with $ 3 $ nodes, the following graph $ G $ is one of the graphs with the maximum number of unidirectional pairs of nodes, which is $ 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1763E/056ef4fb4b6b27a5f901099fab6d214793a2d54c.png)

## 样例 #1

### 输入

```
3```

### 输出

```
3 0```

## 样例 #2

### 输入

```
4```

### 输出

```
5 6```

## 样例 #3

### 输入

```
0```

### 输出

```
0 0```

# 题解

## 作者：nullqtr_pwp (赞：2)

[题目链接](https://codeforces.com/contest/1763/problem/E)

感觉很诈骗啊。看到连通性去想想缩点之类的也没啥坏处。

先求解第 $1$ 问。

$u,v$ 互相可达不就是 $u,v$ 在同一个强连通分量中吗。有 $p$ 个点的极大强连通分量，由其性质，可以产生 $\dfrac{p(p-1)}{2}$ 对互相到达点对。而对答案的贡献是 $p$，因此可以考虑 $dp_i$ 表示产生 $i$ 对互相可达点对至少需要 $dp_i$ 个点。下记 $num_i=\dfrac{i(i-1)}{2}$。

转移显然长成 $dp_i=\min\lbrace dp_{i-num_j}+j\rbrace$，理由是枚举 $i$ 所在强连通分量大小，可以覆盖最优情况。由于 $j$ 的上限需要满足 $num_j\leq i$，所以 $j$ 是 $O(\sqrt n)$ 级别的，因此复杂度为 $O(n\sqrt n)$。

考虑求解第 $2$ 问。

记 $n=|G|$，即节点最少的 $ p $ 可达图的节点数，也就是 $dp_p$。

我们定义**广义联通**点对 $(u,v)$ 满足 $u<v$ 且至少单向联通。

**广义联通**点对分为且仅分为两种：双向联通和单向联通。设广义联通点对数量为 $A_p$，单向联通点对数量为 $B_p$，双向联通点对数量为 $C_p$。有 $A_p=B_p+C_p$。

根据的题目的条件，双向联通点对数量就是 $p$，则 $B_p=p$。

那么单向联通的点对 $C_p=A_p-B_p=A_p-p$，题目等价于去最大化广义联通的数量 $A_p$。

而 $A_p=\dfrac{n(n-1)}{2}$，理由是在强连通分量与另一个强连通分量间连无向边，使得缩点之后是一张 DAG 或者树，就能满足。因为这样可以让任意点对 $(u,v)$ 广义联通，而且不破坏这两个点对是否双向联通，也就是在同一个强连通分量之中。

因此答案 $C_p$ 就是 $\dfrac{n(n-1)}{2}-p$。

```cpp
int f[maxn];
signed main(){
	int n=read();
	memset(f,0x3f,sizeof f);
	f[0]=0,f[1]=2;
	F(i,2,n) F(j,2,i){
		int cur=j*(j-1)/2;
		if(i<cur) break;
		f[i]=min(f[i-cur]+j,f[i]);
	}
	printf("%d ",f[n]);
	ll ans=1ll*f[n]*(f[n]-1);
	ans>>=1;
	printf("%lld\n",ans-n);
}
```


---

## 作者：stntn (赞：2)

## 题意

构造一张有向图，满足其中有恰好 $p$ 对有序点对 $(u,v)$ 满足 $u<v$ 且 $u,v$ 可相互到达。

求出构造满足条件的图的最少点数和在点数最少的情况下单向点对最多的数量。

单相点对：$(u,v)$ 满足 $u$ 可以到达 $v$，但 $v$ 不能到达 $u$。

------------

由于第二问依赖于第一问，所以我们先考虑第一问。

首先贪心地想，怎么用最少的点数构造出尽可能多的可互相到达的点。

显然，一个大小为 $n$ 的强连通图的可互相到达点对最多，为 $\dfrac{n(n-1)}{2}$。

由于两个强连通分量之间一定不会有点对可以相互到达，所以最终答案图一定是由若干个强连通分量构成的，且 $p$ 等于各个强连通分量贡献的点对数之和。

所以我们要求的是：从各种大小强连通图中选若干种，满足它们的点对数之和为 $p$，且节点数最少，每种大小可以选任意多次。

这显然是一个完全背包，可以发现单个强连通图的大小不超过 $633$ 左右，所以背包复杂度为 $O(|G|p)$，其中 $|G|$ 为单个强连通图的最大值，可以接受。

然后考虑第二问就简单了，显然强连通分量内部不会对该问做贡献，而两个大小为 $a,b$ 的强连通分量的贡献为 $ab$。直接算即可。

## CODE

```cpp
#include<bits/stdc++.h>
#define N 110
#define LL long long
#define ULL unsigned long long
#define DB double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define INF 0x3f3f3f3f
#define mod 1000000007
#define pir pair<int,int>
#define mp(i,j) make_pair(i,j)
#define fi first
#define se second
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
int n,sum,ans,f[200010],fr[200010];
vector<int> b;
inline int calc(int x){return (x*(x-1))>>1;}
signed main()
{
	read(n);
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	rep(i,2,633)
	{
		int w=calc(i);
		rep(j,w,n) if(f[j-w]+i<f[j]) f[j]=f[j-w]+i,fr[j]=i;
	}
	for(int i=n;i;i-=calc(fr[i])) b.push_back(fr[i]);
	for(int x:b)
	{
		ans+=sum*x;sum+=x;
	}
	printf("%d %d\n",f[n],ans);
	return 0;
}
```

---

## 作者：Polaris_Australis_ (赞：2)

考虑对于一个有向图，只有每个强连通分量内的点才能两两到达，所以直接利用背包，$dp_{i}=\min(dp_{i-\frac{s\times (s-1)}{2}}+s)$，就能解决第一问。

第二问，可以发现，把所有强连通分量排列成链，并按照拓扑序给点进行编号，可以让所有强连通分量之间的点对都产生贡献，所以答案是 $\binom{dp_p}{2}-p$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

namespace Wilson_Inversion{

void main();

}

int main(){
	Wilson_Inversion::main();
	return 0;
}

namespace Wilson_Inversion{

int n,dp[200010];

void main(){
	scanf("%d",&n);
	for(int i(1);i<=n;++i){
		dp[i]=0x3f3f3f3f;
		for(int j(2);j*(j-1)/2<=i;++j){
			dp[i]=min(dp[i],dp[i-j*(j-1)/2]+j);
		}
	}
	printf("%d %lld\n",dp[n],1ll*dp[n]*(dp[n]-1)/2-n);
}

}
```


---

## 作者：wind_seeker (赞：1)

~~虽然做法很烂。~~

## 正文

### 转化

先把题目转化一下，两个点两两互达证明其必在同一强连通块分量中。

所以变成了:

$$
\begin{aligned}
 \min&\sum_{i=1}^nk_i\\
 \text{s.t.}&\sum_{i=1}^n\binom{k_i}2=p
\end{aligned}
$$

$k$ 最大取值为 $\sqrt{2n}$ ，所以完全背包即可:

$$dp_j=\min(dp_j,dp_{j-i \times (i-1)}+i)$$

在转移时，记录转移过来的 $i$ ，最后算出单向节点对数。

不过，楼上[Wilson_Inversion](https://www.luogu.com.cn/user/576737)的做法更好，拿所有点对数减去 $p$ ，即可。

### code
```cpp
/* let life be like summer flowers	*/
/* by wind_seeker					*/
/* 2023-01-15 08:59					*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+1e3;

inline int read(){
	int res=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) res=(res<<3)+(res<<1)+(c^48);
	return res*f;
}

int n,dp[N],from[N],a[N],cnt;

void solve(){
	int Max=(sqrt(n)+1)*2;
	for(int i=1;i<=n;i++) dp[i]=N;dp[0]=0;
	for(int i=2;i<=Max;i++)
		for(int j=i*(i-1)/2;j<=n;j++){
			if(dp[j-(i*(i-1)/2)]+i<dp[j]){
				from[j]=i;
				dp[j]=dp[j-(i*(i-1))/2]+i;
			}
		}
	printf("%lld ",dp[n]);
	int p=n;
	while(p){
		a[++cnt]=from[p];
		p-=from[p]*(from[p]-1)/2;
	}
	int res=0,ans=0;
	for(int i=cnt;i>=1;i--){
		res+=a[i];
		ans+=a[i]*(dp[n]-res);
	}
	printf("%lld\n",ans);
}

signed main(){
	n=read();
	solve();
	return 0;
}

```

---

## 作者：ZLCT (赞：0)

# CF1763E Node Pairs
## 题目翻译
定义一个有向图的一个单向点对为点对 $(u,v)$ 满足 $u$ 可达 $v$ 且 $v$ 不可达 $u$，定义一个有向图的双向点对 $(u,v)$ 满足 $u,v$ 互相可达，问最少多少点可以组成一个双向点对恰好为 $p$ 的有向图，并求出此时单向点对数量的最大值。
## solution
### Q1
首先我们来看第一小问，至少多少点可以恰好满足 $p$ 对点对。\
我们知道相互可达就意味着 $u,v$ 在同一个强连通分量里，所以我们从强连通分量入手。\
首先这个题全题维护的信息只有“可达”二字，所以如果我们其实可以把一个连通分量进行缩点，换言之，我们对于一个强连通分量我们不关心它内部形态，只关系它的大小。\
又因为在两个强连通分量之间无论如何连边都不会产生新的双向点对（如果出现就违背了强连通分量的极大性），所以我们可以认为最终图的双向点对是由若干个强连通分量构成的。\
我们考虑一个大小为 $s$ 的强连通分量会产生多少对双向点对，由于强连通分量点之间两两可达，所以一共会产生 $\displaystyle\binom{s}{2}$ 个双向点对。\
我们注意到这是个平方级别的数，所以最大的强连通分量的大小也就是 $\sqrt{p}$ 级别的，所以我们可以枚举强连通分量的大小。\
那么这个题就转化为了你有大约 $\sqrt{p}$ 个物品，第 $i$ 个物品都有代价 $i$ 和价值 $\displaystyle\binom{i}{2}$，数量无限，求选若干物品使价值为 $p$ 且代价最小。\
这是一个典型的完全背包问题，我们可以完全背包解决，复杂度 $O(n\sqrt{n})$。
### Q2
这个题第二问有三种做法，其中前两种比较容易证明，第三种的想法比较自然，我们一一介绍。
### 法1
假设我们现在求出有 $m$ 个连通分量，每个连通分量的大小为 $a_1,a_2…a_m$，则有第一问的答案 $ans1=\sum_{i=1}^{m}a_i$。\
我们考虑一共有多少点对，显然任意两个点之间就有点对，所以一共 $\displaystyle\binom{ans1}{2}$ 个点对。根据题目要求我们其中有 $p$ 个是双向点对，那么我们现在的答案上限就是 $\displaystyle\binom{ans1}{2}-p$。\
但是很碰巧的是我们可以构造出 $\displaystyle\binom{ans1}{2}-p$ 对有向点对。\
我们考虑一对不是双向点对的点对，根据我们第一问的解法，这就说明这两个点不在同一个连通块内，那么此时我们就把两点之间连一条有向边。\
但是这样有个问题，万一和原来的边组成一个环导致双向点对的数量增加怎么办？\
那么我们可以假设随便给 $m$ 个连通分量进行编号，每次连边的时候由于不在一个连通分量里，所以 $u,v$ 所在连通分量的编号一定不同，那我们只需要连边方向为从大到小或从小到大就可以保证不会出现环。\
那么根据上面我们对于答案上界的证明，我们构造出的 $\displaystyle\binom{ans1}{2}-p$ 对有向点对一定是最优解。
### 法2
其实根据法1的结论我们就可以发现只要确定了第一问的答案那么无论如何构造答案都唯一。\
但是我们正常发现不了这个结论怎么办？\
我们考虑构造出的若干强连通分量，我们发现如果我们假定了只能从编号小的往编号大的连边，那么我们对于每个连通分量加入的时候就已经能算出它以及它之前的所有连通分量连完的边了，而在我们背包的时候由于要记录 $f_i$ 表示目前价值为 $i$ 最少需要多少点。\
所以对于后续的用到 $i$ 的转移来说，所添加的点都是 $i\times a_j$（其中 $a_j$ 表示该连通分量的大小），所以这满足了无后效性。\
那么我们当然是希望在 $f_i$ 尽可能小的时候已经连的边尽可能多了。\
所以我们 $f_i$ 维护一个 `pair` 表示目前价值为 $i$ 最少需要多少点且满足需要这些点的基础上能连最多多少边。转移就和最短路计数的转移一样了。
### 法3
这个做法就属于先贪再证的做法了。\
我们这个做法相当于考虑凑数，那我们考虑花钱时如果要尽可能用少的张数那肯定是从大到小依次去取，那对于这个我们也用类似的想法去取的话，那么最终取出来的方案就是唯一的了，于是我们可以记录每次更新 $f_i$ 的最新连通块的大小，然后就得出来所有连通块的大小，按照任意顺序把每一个连通块的所有点向还没连过的所有点都连一条边就是答案。\
注意这里有个误区，我们不一定要从小到大或从大到小，因为如果把单向边看做双向边，那么我们每个点都与其他连通块里的点连了一条边，所以最终答案是一样的。\
证明：\
在证明前我以为这个题就是个普通的背包，证明后我才发现这个题最巧妙的地方。\
我们考虑一个连通块大小为 $x$，那么它的价值和代价分别是 $\displaystyle\binom{x}{2}$ 和 $x$，我们先忽略常数 $2$，那么假设我们把这个连通块用其余小连通块替代（注意由于我们的贪心是能选大的就选大的，所以不存在用大的替代的情况），那么假设你换成了 $x-y$，那你省下了 $y$ 的代价但同样损失了 $x\times(x-1)-(x-y)\times(x-y-1)=x^2-x-x^2+2xy+x-y^2+y=2xy-y^2+y$ 的价值，可能不好理解，换到图上就是下图红色部分的价值。\
![](https://cdn.luogu.com.cn/upload/image_hosting/s9ahfmui.png)\
由于你只会把这部分补到一个最终长小于 $x$ 宽小于 $x-1$ 的矩形中，类比正方形感性理解一下你会发现你一定会需要更多的代价来补上这一些，这就违背了需要点最少的要求。\
因此得证。
## 法1 code by `tourist`
```cpp

/**
 *    author:  tourist
 *    created: 19.12.2022 18:40:09       
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int p;
  cin >> p;
  const int inf = (int) 1e9;
  vector<int> dp(p + 1, inf);
  dp[0] = 0;
  for (int v = 2; v * (v - 1) / 2 <= p; v++) {
    int u = v * (v - 1) / 2;
    for (int i = 0; i <= p - u; i++) {
      dp[i + u] = min(dp[i + u], dp[i] + v);
    }
  }
  long long ans = dp[p];
  long long ans2 = ans * (ans - 1) / 2 - p;
  cout << ans << " " << ans2 << '\n';
  return 0;
}
```
## 法2 code by `Um_nik`
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <array>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) {fprintf(stderr, __VA_ARGS__);fflush(stderr);}
#else
	#define eprintf(...) 42
#endif

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {
	return (ull)rng() % B;
}

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second

clock_t startTime;
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

const int INF = (int)1e9;
const int N = 200200;
pii dp[N];

int main()
{
	startTime = clock();
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	for (int i = 0; i < N; i++)
		dp[i] = mp(INF, INF);
	dp[0] = mp(0, 0);
	for (int x = 0; x < N; x++)
		for (int y = 1;; y++) {
			//if (y == 2) continue;
			int z = x + y * (y - 1) / 2;
			if (z >= N) break;
			pii cur = dp[x];
			cur.second -= cur.first * y;
			cur.first += y;
			dp[z] = min(dp[z], cur);
		}

	int n;
	scanf("%d", &n);
	printf("%d %d\n", dp[n].first, -dp[n].second);

	return 0;
}
```
## 法3 code by me
```cpp
#include<bits/stdc++.h>
using namespace std;
int p,w[1145],v[1145],cnt=1,f[214514],lst[214514];
signed main(){
    memset(f,0x3f,sizeof(f));
    cin>>p;
    w[1]=1;
    for(int i=2;(i-1)*i/2<=p;++i){
        w[i]=i;
        v[i]=(i-1)*i/2;
        cnt++;
    }
    f[0]=0;
    for(int i=2;i<=cnt;++i){
        for(int j=v[i];j<=p;++j){
            if(f[j-v[i]]+w[i]<f[j]){
                f[j]=f[j-v[i]]+w[i];
                lst[j]=i;
            }
        }
    }
    cout<<f[p]<<' ';
    int lstsum=f[p];
    multiset<int,greater<> >s;
    s.insert(lst[p]);
    p-=v[lst[p]];
    do{
        s.insert(lst[p]);
        p=p-v[lst[p]];
    }while(p);
    int ans=0;
    while(!s.empty()){
        lstsum-=*s.begin();
        ans+=*s.begin()*lstsum;
        s.erase(s.begin());
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：02Ljh (赞：0)

## [CF1763E](https://codeforces.com/contest/1763/problem/E) //2200

好题。

考虑可达图本质，就是强连通分量森林，每个强连通分量贡献为（点数为 $n$） $\dfrac{n\times(n-1)}{2}$。考虑抽象成背包，其价值是节点个数，体积则是上面那一大坨东西。我们的目标是让背包价值最小，跑背包即可。

看第二问，设森林共有 $k$ 颗分量，那么让这 $k$ 棵分别往其他分量上连边即可，注意不能连回去已经对他连边的分量。这样每连一个边，贡献就加上该分量的点数 $\times$ 他连边的分量点数和，我们可以在背包过程中逆推这东西。具体来说设 $cnt_{i}$ 为体积为 $i$ 时的总贡献，$dp_i$ 为普通背包（点数和），那么原来每个分量都会向他连一条边，新增贡献为 $w_i\times dp_{i-v_{i}}$，$w_i$ 物品价值，$v_i$ 物品体积。

## [code](https://codeforces.com/contest/1763/submission/226470169)

---

## 作者：jasonliujiahua (赞：0)

# CF1763E

[题目传送门](https://www.luogu.com.cn/problem/CF1763E)
## 题意简述：

在一个有向图中，一个节点对 $ ( u , v ) $ 如果满足 $ u \ne v $，$ u $ 能到达 $ v $ 且 $ v $ 不能到达 $ u $，则称其为单向节点对。

如果一个有向图刚好存在 $ p $ 对节点 $ ( u , v) $（$ u < v $ 且二者能互相到达），则称这是一个 $ p $ 可达图，求节点最少的 $ p $ 可达图的节点数。

同时，定义图 $ G $ 为在所有节点数最少的 $ p $ 可达图中，单向节点对数量最多的图，求出图 $ G $ 中单向节点对的个数。

## 题目分析：
可以发现，若使总结点数最少，则该图必定形如：**若干完全图中间被有向边连起来组成的图形**。因此第一问就可以直接 dp 了。具体地，设 $f_i$ 表示满足 $i$ 对节点相互到达的最少的节点数，显然有转移方程：
$$f_i=\min_{\frac{j(j-1)}{2}\le i} f_{i-\frac{j(j-1)}{2}}+j$$

接下来考虑第二问。显然这些完全图之间构成一条链的时候单向节点对数量最多，因此，根据乘法原理，有转移方程：
$$g_i=\max_{\frac{j(j-1)}{2}\le i} g_{i-\frac{j(j-1)}{2}}+f_{i-\frac{j(j-1)}{2}}\times j$$
注意 $f$ 相等时也要更新 $g$。
## 参考代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int n,f[maxn],g[maxn];
void DP()
{
    f[0]=0,g[0]=0;
    for(int i=1;i<=n;i++)
    {
        f[i]=1e18;
        for(int j=2;j*(j-1)/2<=i;j++)
        {
            if(f[i]>f[i-j*(j-1)/2]+j)
            {
                f[i]=f[i-j*(j-1)/2]+j;
                g[i]=g[i-j*(j-1)/2]+f[i-j*(j-1)/2]*j;
            }
            else if(f[i]==f[i-j*(j-1)/2]+j)
            {
                g[i]=max(g[i],g[i-j*(j-1)/2]+f[i-j*(j-1)/2]*j);
            }
        }
    }
}
signed main()
{
    cin>>n;
    DP();
    cout<<f[n]<<" "<<g[n];
    return 0;
}
```

---

