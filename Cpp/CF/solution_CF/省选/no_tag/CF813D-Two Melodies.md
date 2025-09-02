# Two Melodies

## 题目描述

Alice is a beginner composer and now she is ready to create another masterpiece. And not even the single one but two at the same time!

Alice has a sheet with $ n $ notes written on it. She wants to take two such non-empty non-intersecting subsequences that both of them form a melody and sum of their lengths is maximal.

Subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

Subsequence forms a melody when each two adjacent notes either differs by 1 or are congruent modulo 7.

You should write a program which will calculate maximum sum of lengths of such two non-empty non-intersecting subsequences that both of them form a melody.

## 说明/提示

In the first example subsequences $ [1,2] $ and $ [4,5] $ give length 4 in total.

In the second example subsequences $ [62,48,49] $ and $ [60,61] $ give length 5 in total. If you choose subsequence $ [62,61] $ in the first place then the second melody will have maximum length 2, that gives the result of 4, which is not maximal.

## 样例 #1

### 输入

```
4
1 2 4 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6
62 22 60 61 48 49
```

### 输出

```
5
```

# 题解

## 作者：Tarsal (赞：10)

## 1. [CF813D](https://www.luogu.com.cn/problem/CF813D)

### 题意：

给一个长度为$n$的序列,求两个不相交的子集长度之和最大是多少，能放入同一子集的条件是首先顺序不能变，然后每一个相邻的要么相差$1$或者相差$7$的倍数。 $n < 5000$

### 题解：

$f[i][j]$ 表示第一序列到了第 $i$ 位,第二个序列到了第 $j$ 位,符合条件的长度之和最大.

那么显然可以退出 $O(n^3)$ 方程：

```
i : 1 ~ n
j : i + 1 ~ n
k : 分两段。
第一段：1 ~ i，此时判一下a[k]有没有被j选中，如果没有在考虑转移i
第二段：j ~ n，此时就分别转移i,j就行了
```

那么这肯定是过不了的，所以还需要优化。

就是开一个桶记录相差 $1$ 的 $max$

再开一个桶记录 $\%7$ 同余

代码：
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#define N 5200
#define M 100010
#define ls x << 1
#define rs x << 1 | 1
#define inf 10000000000
#define inc(i) (++ (i))
#define dec(i) (-- (i))
// #define mid ((l + r) >> 1)
#define int long long
#define XRZ 212370440130137957
#define debug() puts("XRZ TXDY");
#define mem(i, x) memset(i, x, sizeof(i));
#define Next(i, u) for(register int i = head[u]; i ; i = e[i].nxt)
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout);
#define Rep(i, a, b) for(register int i = (a) , i##Limit = (b) ; i <= i##Limit ; inc(i))
#define Dep(i, a, b) for(register int i = (a) , i##Limit = (b) ; i >= i##Limit ; dec(i))
int dx[10] = {1, -1, 0, 0};
int dy[10] = {0, 0, 1, -1};
using namespace std;
// const int base = 30;
// const int prime = 19260817;
inline int read() {
    register int x = 0, f = 1; register char c = getchar();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
int pre[M], num[10], n, ans, a[N], f[N][N];
void clean() { mem(num, 0) mem(pre, 0)}
signed main() { n = read();
    Rep(i, 1, n) a[i] = read();
    Rep(i, 0, n) { clean();
        Rep(j, 1, i - 1) pre[a[j]] = max(pre[a[j]], f[i][j]), num[a[j] % 7] = max(num[a[j] % 7], f[i][j]);
        Rep(j, i + 1, n) { f[i][j] = f[i][0] + 1;
            f[i][j] = max(f[i][j], max(pre[a[j] + 1] + 1, max(pre[a[j] - 1] + 1, num[a[j] % 7] + 1))); f[j][i] = f[i][j];
            pre[a[j]] = max(pre[a[j]], f[i][j]), num[a[j] % 7] = max(num[a[j] % 7], f[i][j]); ans = max(ans, f[i][j]);
        }
    }
    printf("%lld", ans);
	return 0;//int zmy = 666666, zzz = 233333;
}
```

---

## 作者：LinkyChristian (赞：6)

审核求过

在[我的博客](https://lookcatbox.github.io/post/ti-jie-cf818g-four-melodies/)食用更佳

~~这是在咕了一周的每日总结以及一次每周总结的情况下写的题解~~

其实蛮简单的....就是没有有图的题解。

考虑每个 $a_i$ 只能选一次的限制，这个太典了，直接拆点 $in_i,out_i$，连一条容量 $1$，费用 $1$ 的边，走了这条边意味着选了 $a_i$， 并且产生 $1$ 的贡献。

然后思考两个限制，相邻元素绝对值差为 $1$，或模 $7$ 同余。

显然有这么一种思路，从 $out_i$ 向之后所有的与它差为 $1$ 或模 $7$ 同余的点的 $in_i$ 连边，但这样边数是 $O(n^2)$ 的，显然过不了。

考虑从 $a_i$ 到 $a_j$，如果中间有一个一样可以到达 $a_i$，$a_j$ 的点 $a_k$，那么从 $a_i$ 到 $a_k$，再从 $a_k$ 到 $a_j$ 是完全可以替代 $a_i,a_j$ 的。   

因此继续拆点，将 $a_i$ 再拆成 $sub_i,mod_i$，用于与绝对值差为 $1$，以及膜 $7$ 同余的 **最近点** 连边。

具体连边像这样（容量、费用）

![](https://cdn.luogu.com.cn/upload/image_hosting/i4rq50jd.png)

然后在相邻的模 $7$ 同余的点的 $mod_i$ 之间连 $(INF,0)$ 的边（不选），在相邻的 $a_i$ 相同的点的 $sub_i$ 之间连 $(INF,0)$ 的边（这些是表示不用选自己就可以选到自己后面的）。从每个点的 $out_i$ 向之后最近的 $a_i-a_j==1$ 的点和 $a_j-a_i==1$ 的点的 $sub_i$ 连 $(INF,0)$ 的边，向之后最近的模 $7$ 同余的节点的 $mod_i$ 连 $(INF,0)$ 的边。（表示选了自己后能选后面的）

然后从源点向每个点的 $in_i$ 连 $(INF，0)$ 的边，从每个点的 $out_i$ 向汇点连 $(INF,0)$。

最后有一个子序列数量的限制，我们建一个超级源点，向源点连容量为需要的子序列数，费用为 $0$ 的边。（所以其实 k-Melodies 都是能做的）

附上样例二的建图

![](https://cdn.luogu.com.cn/upload/image_hosting/t4b9w0zl.png)

~~很丑陋吧?画图画的~~

附上代码

```cpp
// Problem: CF818G Four Melodies
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF818G
// Memory Limit: 1000 MB
// Time Limit: 5000 ms
#include<bits/stdc++.h>
#define N 20010
#define M 1000010
using namespace std;
namespace MCMF{
	int cnt=1,head[N],to[M],nxt[M],val[M],flow[M];
	const int INF=0x3f3f3f3f;
	void insert(int u,int v,int f,int w){
		cnt++;
		to[cnt]=v;
		val[cnt]=w;
		flow[cnt]=f;
		nxt[cnt]=head[u];
		head[u]=cnt;
	}
	void ins(int u,int v,int f,int w) {
		insert(u,v,f,w);
		insert(v,u,0,-w);
	}
	int wat[N],dis[N],vis[N],fr[N];
	int SPFA(int ss,int tt) {
		memset(dis,-1,sizeof(dis));
		queue<int> q;
		q.push(ss),dis[ss]=0,wat[ss]=INF,vis[ss]=1;
		while(!q.empty()) {
		    int now=q.front();q.pop();
		    vis[now]=0;
		    for(int i=head[now]; i; i=nxt[i]) 
		        if(flow[i]&&dis[to[i]]<dis[now]+val[i]) {
		        	dis[to[i]]=dis[now]+val[i];
		        	fr[to[i]]=i;
		        	wat[to[i]]=min(wat[now],flow[i]);
		        	if(!vis[to[i]]) q.push(to[i]),vis[to[i]]=1;
		        }
		}
		return dis[tt]!=-1;
	}
	pair<int,int> Dinic(int ss,int tt) {
		int rf=0,rv=0;
		while(SPFA(ss,tt)) {
			rf+=wat[tt],rv+=wat[tt]*dis[tt];
			int now=tt;
			while(now!=ss) {
				flow[fr[now]]-=wat[tt];
				flow[fr[now]^1]+=wat[tt];
				now=to[fr[now]^1];
			}
		}
		return make_pair(rf,rv);
	}
}
using namespace MCMF;
int read() {
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)) f=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch)) res=res*10+ch-'0',ch=getchar();
	return f*res;
}
int S,s,T,n,num[N];
int main()
{
	n=read();s=4*n+1,T=4*n+2;
    for(int i=1; i<=n; i++) num[i]=read();
    ins(S,s,4,0);
    for(int i=1; i<=n; i++) {
    	ins(s,2*n+i,INF,0),ins(i,2*n+i,INF,0),ins(n+i,2*n+i,INF,0);
    	ins(2*n+i,3*n+i,1,1),ins(3*n+i,T,INF,0);
    	for(int j=i+1;j<=n;j++)if(num[i]-num[j]==1){ins(n*3+i,n+j,INF,0);break;}
		for(int j=i+1;j<=n;j++)if(num[j]-num[i]==1){ins(n*3+i,n+j,INF,0);break;}
		for(int j=i+1;j<=n;j++)if(num[i]%7==num[j]%7){ins(n*3+i,j,INF,0),ins(i,j,INF,0);break;}
		for(int j=i+1;j<=n;j++)if(num[i]==num[j]){ins(n+i,n+j,INF,0);break;}
    }
    cout<<Dinic(S,T).second;
    return 0;
}
```


---

## 作者：UperFicial (赞：1)

好难，下面是我的全部思考过程，不会直接说结论。

考虑费用流，流量处理数的出现次数，费用处理最长长度。

每个数不能同时存在于两个子序列，那么可以对每个点拆点，流量为 $1$，费用为 $1$，表示一个数只能选一次，以及选了之后答案长度会贡献 $1$。

每个点都可以作为序列的开头，所以令源 $s$ 联向每个点的入点，流量为 $1$，费用为 $0$。同理，每个点都可作为序列的结尾，则令每个点的出点连向汇 $t$，流量为 $1$，费用为 $0$。

最多只有两个子序列，也就是说 $s$ 出发的流量最多为 $2$，则可以建立超级源 $s'$ 连向 $s$，流量为 $1$，费用为 $0$。

下面考虑相邻两项的限制，我一开始直接暴力 $n^2$ 建图，全部用 short 类型，最多只能冲到第 12 个点，需要找性质来优化。

考虑模 $7$ 同余这个条件，它是有传递性的。所以只需将 $a_i$ 与最近模 $7$ 同余的 $a_j(j>i)$ 连边。第一种方法是不选 $j$，$out_i$ 向 $out_j$ 连一条容量为 $\infty$，费用为 $0$ 的边，第二种方法是选，$out_i$ 连向 $in_j$。

之后是相差不超过 $1$ 的条件，我觉得这个是本题最难的地方，因为它不具有传递性。

如果按照模 $7$ 同余的方法建图，那么对于 $|a_i-a_j|=1$ 的两个点 $i,j(i<j)$，第一种方法不选 $a_j$，将 $out_i$ 连向 $out_j$，第二种方法选 $a_j$，$out_i$ 连向 $in_j$。

但是这样会出现什么问题，比如 $1,2,3$，如果 $2$ 不选，$1,3$ 还是会有流量的。

我们之所以会出现这种错误，是因为 $2$ 的出点连向 $3$ 的入点时，由于到 $3$ 的流量是从 $2$ 的**出点**进来的，出点就意味着 $2$ 是选的，而我们本身可能并没有选 $2$。

那么我们不妨就可以找到 $2$ 的等价形式，也就是找到之后另一个 $2$，我们把第一个 $2$ 的 $in$ 连向第二个 $2$ 的 $in$，表示如果你第一个 $2$ 不选，那么你其实可以去尝试一下第二个 $2$。

但是这个你会发现模 $7$ 同余与相差为 $1$ 会混，因为一个入点和出点只能表示一个意思。

所以你可以对每个点再拆出来两个点，分别表示模 $7$ 的点和相差为 $1$ 的点，两个点都向 $in$ 连容量为 $\infty$，费用为 $0$ 的边。

注意这里容量是 $\infty$，因为你可能是两个子序列，一个子序列选了 $i$，直接经过 $in$ 到 $out$ 的边，另一个子序列则是可能直接去找了 $a_i$ 的等价形式。

---

## 作者：xzggzh1 (赞：1)

题意：

给一个长度为 $n$ 的序列,求两个不相交的子集长度之和最大是多少，能放入同一子集的条件是首先顺序不能变，然后每一个相邻的要么相差 $1$ 或者相差 $7$ 的倍数。 $n < 5000 $ 。

---

当我看到[CF818G](https://www.luogu.com.cn/problem/CF818G)时，我发现这题不止 $\rm DP$ 一种解法。甚至 $\rm DP$ 的解法只能算是暴力。


[CF818G](https://www.luogu.com.cn/problem/CF818G) 算的是**四个**不相交的子序列，而这题只要求两个，若用费用流的做法，那么只要改一下关键边的流量即可（当然，这题数据范围稍大）。

大致思路：

把一个点拆成两个点来限制每个点最多用一遍。

把模 $7$ 相同的最近的数连边表示相差 $7$ 的倍数的点有边。

把相同权的点搞在一起，然后差一的数连最近的，表示差 $1$ 的点有边。

其中取一个数获得的贡献可以用边权表示，取的限制可以用流量表示。

这样最后边数大概是 $O(n)$ 级别的（上面的连边中的细节略去，若细节不懂说明网络流的题刷的太少）。

最后跑费用流输出答案即可。

这个费用流写的好速度升值可以吊打 $\rm DP$ 。并且更加普适，求多少个序列改变只需改变流量。

----

代码虽丑还是放一个吧：

```cpp
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<bool> VB;
typedef vector<unsigned long long> VULL;
typedef vector<vector<int>> VVI;
typedef queue<int> QI;
int gcd(int x, int y)
{
	return y ? gcd(y, x % y) : abs(x);
}
template<class T> T sqr(T x)
{
	return x * x;
}
const int INF = 1000 * 1000 * 1000;
struct rib {
	int b, u, c, f;
	size_t back;
};
vector < vector<rib> > g(4 * 5030);
void add_rib(int a, int b, int u, int c) {
	rib r1 = { b, u, c, 0, g[b].size() };
	rib r2 = { a, 0, -c, 0, g[a].size() };
	g[a].push_back(r1);
	g[b].push_back(r2);
}
int a[5030];
int lastnum[101010];
int lastmod[7];
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	REP(i, n)cin >> a[i + 1];
	int N = 4 * n + 2;
	REP(i, 101010)lastnum[i] = -1;
	REP(i, 7)lastmod[i] = -1;
	REP(i, n)
	{
		add_rib(0, 4 * i + 3, 1, 0);
		add_rib(4 * i + 1, 4 * i + 3, 1, 0);
		add_rib(4 * i + 2, 4 * i + 3, 1, 0);
		add_rib(4 * i + 3, 4 * i + 4, 1, -1);
		add_rib(4 * i + 4, 4 * n + 1, 1, 0);
		if(lastnum[a[n - i] - 1] != -1)add_rib(4 * (n - i - 1) + 4, 4 * (lastnum[a[n - i] - 1] - 1) + 1, 1, 0);
		if (lastnum[a[n - i] + 1] != -1)add_rib(4 * (n - i - 1) + 4, 4 * (lastnum[a[n - i] + 1] - 1) + 1, 1, 0);
		if (lastmod[a[n - i] % 7] != -1)add_rib(4 * (n - i - 1) + 4, 4 * (lastmod[a[n - i] % 7] - 1) + 2, 1, 0);
		if (lastnum[a[n - i]] != -1)add_rib(4 * (n - i - 1) + 1, 4 * (lastnum[a[n - i]] - 1) + 1, 2, 0);
		if (lastmod[a[n - i] % 7] != -1)add_rib(4 * (n - i - 1) + 2, 4 * (lastmod[a[n - i] % 7] - 1) + 2, 2, 0);
		lastnum[a[n - i]] = n - i;
		lastmod[a[n - i] % 7] = n - i;
	}
	int s = 0, t = 4 * n + 1;
	int flow = 0, cost = 0;
	const int INF = 1000000000;
	while (flow < 2) {
		vector<int> id(N, 0);
		vector<int> d(N, INF);
		vector<int> q(N);
		vector<int> p(N);
		vector<size_t> p_rib(N);
		int qh = 0, qt = 0;
		q[qt++] = s;
		d[s] = 0;
		while (qh != qt) {
			int v = q[qh++];
			id[v] = 2;
			if (qh == N)  qh = 0;
			for (size_t i = 0; i<g[v].size(); ++i) {
				rib & r = g[v][i];
				if (r.f < r.u && d[v] + r.c < d[r.b]) {
					d[r.b] = d[v] + r.c;
					if (id[r.b] == 0) {
						q[qt++] = r.b;
						if (qt == N)  qt = 0;
					}
					else if (id[r.b] == 2) {
						if (--qh == -1)  qh = N - 1;
						q[qh] = r.b;
					}
					id[r.b] = 1;
					p[r.b] = v;
					p_rib[r.b] = i;
				}
			}
		}
		if (d[t] == INF)  break;
		int addflow = 4 - flow;
		for (int v = t; v != s; v = p[v]) {
			int pv = p[v];  size_t pr = p_rib[v];
			addflow = min(addflow, g[pv][pr].u - g[pv][pr].f);
		}
		for (int v = t; v != s; v = p[v]) {
			int pv = p[v];  size_t pr = p_rib[v], r = g[pv][pr].back;
			g[pv][pr].f += addflow;
			g[v][r].f -= addflow;
			cost += g[pv][pr].c * addflow;
		}
		flow += addflow;
	}
	cout << -cost << endl;
}
```

---

## 作者：Unnamed114514 (赞：0)

dp 状态显然，定义 $f_{i,j}$ 表示钦定第 $i$ 个选了，第 $j$ 个选在另一个里面，保证 $j<i$，且在 $(j,i)$ 的都不会出现在另一个里面。

考虑枚举 $i$ 上一个合法的转移点 $k$，容易得到 $O(n^3)$ 的 dp，即 $f_{i,j}\gets \max\limits_{|a_i-a_k|\le 1\cup a_i\equiv a_k\pmod 7}\{f_{k,j}/f_{j,k}\}$（方程中是啥要根据大小来定）

然后考虑快速转移，注意到 $j$ 这一维一直是不变的，容易想到定义 $g_{k,j}$ 表示 $a_i\bmod 7=k$ 中 $f_{i,j}$ 的最大值，同理定义 $h_{k,j}$ 表示 $|a_i-k|\le 1$ 中 $f_{i,j}$ 的最大值，这个直接存存不下，离散化一下即可。

然后我们的转移就是 $f_{i,j}\gets\max\{f_{j,0},g_{a_i\bmod 7}{j},h_{a_i,j}\}$，时间复杂度就是 $O(n^2)$ 了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int n,a[N],f[N][N],g[7][N],h[N][N],ans=1,lsh[N],m;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i],lsh[i]=a[i];
	sort(lsh+1,lsh+n+1);
	m=unique(lsh+1,lsh+n+1)-lsh-1;
	for(int i=1;i<=n;++i) a[i]=lower_bound(lsh+1,lsh+m+1,a[i])-lsh;
	for(int i=1;i<=n;++i){
 		for(int j=0;j<i;++j){
			f[i][j]=max({f[j][0]+1,g[lsh[a[i]]%7][j]+1,h[a[i]][j]+1});
			ans=max(ans,f[i][j]);
			g[lsh[a[i]]%7][j]=max(g[lsh[a[i]]%7][j],f[i][j]);
			g[lsh[a[j]]%7][i]=max(g[lsh[a[j]]%7][i],f[i][j]);
			if(lsh[a[i]-1]==lsh[a[i]]-1) h[a[i]-1][j]=max(h[a[i]-1][j],f[i][j]);
			h[a[i]][j]=max(h[a[i]][j],f[i][j]);
			if(lsh[a[i]+1]==lsh[a[i]]+1) h[a[i]+1][j]=max(h[a[i]+1][j],f[i][j]);
			if(lsh[a[j]-1]==lsh[a[j]]-1) h[a[j]-1][i]=max(h[a[j]-1][i],f[i][j]);
			h[a[j]][i]=max(h[a[j]][i],f[i][j]);
			if(lsh[a[j]+1]==lsh[a[j]]+1) h[a[j]+1][i]=max(h[a[j]+1][i],f[i][j]);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

