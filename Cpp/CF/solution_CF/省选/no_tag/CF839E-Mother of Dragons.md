# Mother of Dragons

## 题目描述

There are $ n $ castles in the Lannister's Kingdom and some walls connect two castles, no two castles are connected by more than one wall, no wall connects a castle to itself.

Sir Jaime Lannister has discovered that Daenerys Targaryen is going to attack his kingdom soon. Therefore he wants to defend his kingdom. He has $ k $ liters of a strange liquid. He wants to distribute that liquid among the castles, so each castle may contain some liquid (possibly zero or non-integer number of liters). After that the stability of a wall is defined as follows: if the wall connects two castles $ a $ and $ b $ , and they contain $ x $ and $ y $ liters of that liquid, respectively, then the strength of that wall is $ x·y $ .

Your task is to print the maximum possible sum of stabilities of the walls that Sir Jaime Lannister can achieve.

## 说明/提示

In the first sample, we can assign $ 0.5,0.5,0 $ liters of liquid to castles $ 1,2,3 $ , respectively, to get the maximum sum ( $ 0.25 $ ).

In the second sample, we can assign $ 1.0,1.0,1.0,1.0 $ liters of liquid to castles $ 1,2,3,4 $ , respectively, to get the maximum sum ( $ 4.0 $ )

## 样例 #1

### 输入

```
3 1
0 1 0
1 0 0
0 0 0
```

### 输出

```
0.250000000000
```

## 样例 #2

### 输入

```
4 4
0 1 0 1
1 0 1 0
0 1 0 1
1 0 1 0
```

### 输出

```
4.000000000000
```

# 题解

## 作者：lndjy (赞：3)

最好写好想做法。

题目容易转化为求最大团。

然后假设你和我一样是在模拟赛看到这题的，有一个 $n\le 25$ 的暴力分，你决定先写个 $2^n$ 暴力。

思路就是，设 $f_S$ 表示集合 $S$ 里面的点的最大团，转移枚举 `lowbit`，考虑不选则转移到 `S-lowbit`，否则，和这个 `lowbit` 有边的点都不能选，转移到 `S&e[lowbit]+1`。`e[i]` 表示和 $i$ 有边的集合。

然后你想多骗点分，感觉状态没那么多，决定记忆化一下。

然后你 `AC` 了。

那么这是为什么呢？神说，前面 $n/2$ 层分治树，每种状态只有 $2$ 种决策，总决策数 $2 ^ {n / 2}$。后面 $n/2$ 层分治树，所有状态 $S$ 不含小于 $n/2$ 的点，总共只有 $2 ^ {n / 2}$ 种本质不同状态，被你记忆化掉了。

所以状态数是 $2^{n/2}$ 级别的。

代码超级好写。

```cpp
#include<iostream>
#include<cstdio>
#include<map>
#include<string>
#include<iomanip>
#define int long long
using namespace std;
int e[55],n;
map<int,int> mp,f;
int dfs(int now)
{
	if(now==0) return 0;
	if(mp.find(now)!=mp.end()) return mp[now];
	int lb=(now&(-now));
	return mp[now]=max(dfs(now-lb),dfs(now&e[f[lb]])+1);
}
signed main()
{
	//freopen("cows.in","r",stdin);
	//freopen("cows.out","w",stdout);
    int k;
	cin>>n>>k;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			int x;
            cin>>x;
            if(x==1)
			e[i]|=1ll<<j;
		}
	}
	for(int i=0;i<n;i++)
	f[1ll<<i]=i;
	double ans=dfs((1ll<<n)-1);
    ans=k*k/ans*(ans-1)/2;
    cout<<fixed<<setprecision(10)<<ans;
 	return 0;
}

```


---

## 作者：disangan233 (赞：3)

## 题意简述 

给你一个 $n$ 个节点的无向图 $G=\{V,E\}$的邻接矩阵 $g$ 和每个点的点权为 $s_i$，且 $\sum_{i=1}^n s_i = K$，要你求出 $\mathrm{max} \{ \sum_{u,v \in E} s_u \times s_v\}$

## 做法

设两个不相邻的点$u$，$v$的点权为$s_u$和$s_v$，令$a_u = \sum_{g[u][i]=1}  s_i, a_v=\sum_{g[v][i]=1} s_i$，此时这对点$(u,v)$的贡献为$a_us_u+a_vs_v$。

- 不妨设$a_u\geq a_v$，若$s_u=s_u+s_v,s_v=0$，$ans$并不会变小。

所以最优解一定包含选取一个团(完全图)。对于一个 $n$ 个点的完全图，这个完全图的答案为 $(\frac {K}{n})^2 \times \frac {n(n-1)}{2}$，所以本题的答案为 $(\frac {K}{tot})^2 \times \frac {tot(tot-1)}{2}$，其中 $tot$为最大团的大小。

我们采用 $Bron-Kerbosch$ 算法来求最大团，采用dfs剪枝的方法，时间复杂度 $O\left( 3^{\frac n3} \right)$。

------

当然此题模拟退火也可以过，维护一个序列 ${c_n}$，$s_i=\frac {c_i}{\sum_j c_j}$。对于序列进行随机的 $\bmod $ 固定值(如 $100$ )意义下的加减，如果更优则转移。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define ll long long
#define ak *
#define in inline
#define db double
in char getch()
{
	static char buf[1<<12],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<12,stdin),p1==p2)?EOF:*p1++;
}
char qwq;
#define gc() getchar()
in int read()
{
	re cz=0,ioi=1;qwq=gc();
	while(qwq<'0'||qwq>'9') ioi=qwq=='-'?~ioi+1:1,qwq=gc();
	while(qwq>='0'&&qwq<='9') cz=(cz<<3)+(cz<<1)+(qwq^48),qwq=gc();
	return cz ak ioi;
}
const int N=45;
int n,k,g[N][N],ans,cnt[N],ch[N];
bool dfs(re u,re nw)
{
	ch[nw]=u;
	if(nw>ans) return ans=nw,true;
	for(re i,v=u+1;v<=n;v++)
	{
		if(!g[u][v]||nw+cnt[v]<=ans) continue;
		for(i=1;i<=nw;i++)
		if(!g[ch[i]][v]) break;
		if(i>nw&&dfs(v,nw+1)) return true; 
	}
	return false;
}
in int bron_kerbosch()
{
	for(re i=n;i;i--) dfs(i,1),cnt[i]=ans;
	return ans;
}
int main()
{
	n=read();k=read();
	for(re i=1;i<=n;i++) 
	for(re j=1;j<=n;j++)
	g[i][j]=read();
	re cnt=bron_kerbosch();
	if(!cnt) return puts("0"),0;
	db per=1.0*k/cnt,tot=cnt*(cnt-1)/2.0;
	printf("%.8lf",tot*pow(per,2));
	return 0;
}
```



---

## 作者：RainFestival (赞：2)

首先，我们可以贪心地发现，我们需要找一个最大的完全子图，然后给每一个点平均分配点权就可以了。

如果不是完全子图，每次删除那个度数最小的点，结果一定不会变差。

因此我们现在要求出一个图中最大的完全子图大小。

暴力是 $\mathcal{O(2^n\times n)}$，过不了。

一种解决方式是 Bron-Kerbosch，可惜我没有听说过，现学了一下。

后来别人和我提起这个题的时候，想到了一个 meet-in-middle 的做法，大概是枚举前面 $\frac{n}{2}$ 个点和后面 $\frac{n}{2}$ 个点的情况，然后考虑把它们拼起来。

事实证明，比赛中通过这个题的人大多是用后一种方法，~~可见 Bron-Kerbosch 真的不普及~~。

代码如下(Bron-Kerbosch)，口胡的状态压缩没写过：

```cpp
#include<cstdio>
#include<algorithm>
int n,k,f[45][45],ans=0,tt,t[45];
int popcount(long long x)
{
	int ans=0;
	for (int i=1;i<=n;i++) if (x&(1ll<<(i-1))) ++ans;
	return ans;
}
void solve(long long r,long long p,long long x)
{
	if (!p&&!x) return ans=std::max(ans,popcount(r)),void();
	int k;
	for (int i=1;i<=n;i++) if ((p&(1ll<<(i-1)))||x&(1ll<<(i-1))) k=i;
	for (int i=1;i<=n;i++)
	{
		int v=i;
		if (f[k][v]) continue;
		if (!(p&(1ll<<(v-1)))) continue;
		long long rr=0,pp=0,xx=0;
		rr=r+(1ll<<(v-1));
		for (int k=1;k<=n;k++) if ((p&(1ll<<(k-1)))&&f[v][k]) pp=pp+(1ll<<(k-1));
		for (int k=1;k<=n;k++) if ((x&(1ll<<(k-1)))&&f[v][k]) xx=xx+(1ll<<(k-1));
		solve(rr,pp,xx);
		p=p-(1ll<<(v-1));x=x+(1ll<<(v-1));
	}
}
void bron_kerbosch()
{
	long long r,p,x;
	p=(1ll<<n)-1;
	solve(r,p,x);
}
int main()
{
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++)
	    for (int j=1;j<=n;j++)
	        scanf("%d",&f[i][j]);
	bron_kerbosch();
	double x=k/(double)ans;
	printf("%.12lf\n",x*x*ans*(ans-1)/2);
	return 0;
}
```

---

## 作者：masonpop (赞：1)

妙妙题。

首先可以证明，有权值的点的导出子图为完全图。证明可以考虑调整法，假设没边的 $x,y$ 被同时选出，则其贡献独立。不妨设边集为 $E$，且$\sum\limits_{(x,v)\in E}\ge \sum\limits_{(y,v)\in E}$。那么把 $y$ 的权值全给 $x$ 一定更优。证毕。

枚举点数 $t$，那么就转化为这样一个问题：有一个序列 $a_1,a_2,\cdots,a_t$ 满足 $\sum\limits_{i=1}^ta_i=S$，最大化 $\sum\limits_{i=1}^t\sum\limits_{j=i+1}^t a_ia_j$。由基本不等式很容易推出所有数全相等时取到 $W_{\max}=\dfrac{t(t-1)}{2}(\dfrac{S}{t})^2$。

这个式子关于 $t$ 单调递增，于是问题转化为求 $t$ 的最大值，即图中的最大团。

到这里就很神秘了，我并不会其它题解提到的 Bron–Kerbosch 算法，于是开始乱搞。直接状压，设 $f_{S}$ 表示当选取的点集是 $S$ 的子集时的最大团。转移枚举 $\text{lowbit}$ 并枚举选不选，如果选，后面选的点必须和他有连边。

然后我认为这是 $O(2^n)$ 的过不了，但是状态看上去好像不都能取到，于是加了个记忆化，结果跑的飞快直接过了。

其实这东西复杂度 $O(2^{n/2})$。证明大概是，前 $n/2$ 个点最多只有这么多状态，而后面的状态不含前面的点，也只有这么多。加起来就是 $O(2^{n/2})$ 的了。[代码](https://www.luogu.com.cn/record/139479484)。

~~这个故事告诉我们，要勇于乱搞，万一过了呢。~~



---

## 作者：望月Asta (赞：1)

## 题意

给定一个 $n$ 个点的无向图 $G(V,E)$ 和一个值 $k$，为每个点分 $i$ 配一个**非负**点权 $s_i$ 使得 $\sum_{i = 1}^{n} s_i = k$。

记一个分配点权方案的价值为 $\sum_{(u,v) \in E} s_u \times s_v$，最大化价值。

其中 $n \le 40$。

## 解法

首先分配的点权非负，导致不能玩一些两个负极大值放一起乘出一个正极大值这样的花活。

然后有一个结论，分配了正点权的点集的导出子图是原图的一个**完全子图**。

考虑对于不相邻两点 $u,v$，其贡献是独立的，那么如果 $\sum_{(u,t) \in E} s_t \ge \sum_{(v,t) \in E} s_t$，将权值重新分配为 $s_u' \leftarrow s_u + s_v,s_v' \leftarrow 0$ 是不劣的。

于是可以得到，最后分配到正点权的点集的导出子图是完全子图，此时如果导出子图节点个数为 $p$ 则价值为 $\left( \dfrac{k}{p} \right)^2 \times \dfrac{p(p - 1)}{2}$，可以发现完全子图大小越大价值越大，问题转化为求原图的一个最大完全子图（或者叫做**最大团**）。

求无向图的最大团是一个 NPC 问题，直接枚举每个点是否在最大团内再验证的复杂度为 $\mathcal{O} (n2^n)$，会超时，我并不会 Bron–Kerbosch 算法这样的科技，考虑折半状压。

令 $f_S$ 表示前一半点可选集合为 $S$ 时的最大团，则有：

$$

f_S = \left\{

\begin{matrix}

&|S| \ (S {\text{是一个完全子图}}) \\

&\max{f_T,T \subseteq S} \ (\text{otherwise.})

\end{matrix}\right.

$$

这个转移可以暴力枚举得到，复杂度 $\mathcal{O} (\dfrac{n}{2}2^{\frac{n}{2}})$。

然后用同样的方式枚举另一半点，记枚举的集合为 $S$，同时处理出和 $S$ 里每个点都相邻的前一半点的集合记为 $T$，则最大团大小为 $\max {|S| + f_T}$

整体的复杂度降低到 $\mathcal{O} (\dfrac{n}{2}2^{\frac{n}{2}})$。

（正确的时间复杂度表述里不应该出现 $2$ 这样的常数，上面的写法其实是不够严谨的，但是也不知道该怎么表述比较好）

## 代码

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>

using i64 = long long;
using f64 = double;

constexpr int N = 40;
constexpr int M = 1 << 20 | 5;

int f[M];
i64 e[N + 5];

#define popcnt(x) (__builtin_popcount(x))

int main() {
	int n,k;
	scanf("%d %d",&n,&k);
	for(int i = 0;i < n;++i)
		for(int j = 0;j < n;++j) {
			int t;
			scanf("%d",&t);
			e[i] |= (1ll << j) * t;
			e[j] |= (1ll << i) * t;
		}
	int p1 = n >> 1,p2 = n - p1,mx = 0;
	for(int i = 1;i < (1 << p1);++i) {
		bool flag = 1;
		for(int j = 0;j < p1;++j) if(i & (1 << j))
			if(((i ^ (1 << j)) & e[j]) != (i ^ (1 << j))) {
				flag = 0;
				break;
			}
		if(flag) f[i] = popcnt(i);
	}
	for(int i = 1;i < (1 << p1);++i)
		for(int j = 0;j < p1;++j) if(i & (1 << j))
			f[i] = std::max(f[i],f[i ^ (1 << j)]);
	for(int i = 0;i < (1 << p2);++i) {
		i64 S = (1ll << n) - 1;
		bool flag = 1;
		for(int j = 0;j < p2;++j) if(i & (1 << j)) {
			if(((i ^ (1 << j)) & (e[j + p1] >> p1)) != (i ^ (1 << j))) {
				flag = 0;
				break;
			}
			S &= e[j + p1];
		}
		S &= (1 << p1) - 1;
		if(flag)
			mx = std::max(mx,f[S] + popcnt(i));
	}
	f64 t = (f64)k / mx;
	f64 ans = t * t * (mx * (mx - 1) >> 1);
	printf("%.12lf",ans);
	return 0;
}

#undef popcnt
```

---

