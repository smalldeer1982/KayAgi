# [ABC270F] Transportation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc270/tasks/abc270_f

AtCoder 国には $ N $ 個の島があり、 最初、どの島にも空港・港はなく、どの島の間にも道路はありません。 王である高橋君はこれらの島の間に交通手段を用意することにしました。 具体的には、高橋君は次の操作のうち $ 1 $ つを選んで行うことを好きなだけ繰り返す事ができます。

- $ 1\leq\ i\leq\ N $ をみたす $ i $ を選び、コスト $ X_i $ を払って、島 $ i $ に空港を建設する。
- $ 1\leq\ i\leq\ N $ をみたす $ i $ を選び、コスト $ Y_i $ を払って、島 $ i $ に港を建設する。
- $ 1\leq\ i\leq\ M $ をみたす $ i $ を選び、コスト $ Z_i $ を払って、島 $ A_i $ と島 $ B_i $ の間を双方向に結ぶ道路を建設する。

高橋君の目標は、任意の相異なる $ 2 $ つの島 $ U $, $ V $ について、 島 $ U $ からはじめて次の行動のうち $ 1 $ つを選んで行うことを好きなだけ繰り返す事で、 島 $ V $ に到達することができるようにする事です。

- 島 $ S,T $ の両方に空港がある時、島 $ S $ から島 $ T $ まで移動する。
- 島 $ S,T $ の両方に港がある時、島 $ S $ から島 $ T $ まで移動する。
- 島 $ S,T $ を結ぶ道路が存在する時、島 $ S $ から島 $ T $ まで移動する。

高橋君が目標を達成するのに必要な最小コストを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ X_i\leq\ 10^9 $
- $ 1\leq\ Y_i\leq\ 10^9 $
- $ 1\leq\ A_i\ <\ B_i\leq\ N $
- $ 1\leq\ Z_i\leq\ 10^9 $
- $ i\neq\ j $ ならば $ (A_i,B_i)\neq\ (A_j,B_j) $
- 入力は全て整数

### Sample Explanation 1

高橋君は次のように交通手段を建設します。 - コスト $ X_1=1 $ を払って、島 $ 1 $ に空港を建設する。 - コスト $ X_3=4 $ を払って、島 $ 3 $ に空港を建設する。 - コスト $ Y_2=2 $ を払って、島 $ 2 $ に港を建設する。 - コスト $ Y_4=3 $ を払って、島 $ 4 $ に港を建設する。 - コスト $ Z_2=6 $ を払って、島 $ 1 $ と島 $ 4 $ の間を結ぶ道路を建設する。 このとき、目標は達成されており、かかったコストは $ 16 $ となります。 コスト $ 15 $ 以下で目標を達成する方法はないため、$ 16 $ を出力します。

### Sample Explanation 2

空港・港・道路のうち、一度も建設されないものがあっても構いません。

## 样例 #1

### 输入

```
4 2
1 20 4 7
20 2 20 3
1 3 5
1 4 6```

### 输出

```
16```

## 样例 #2

### 输入

```
3 1
1 1 1
10 10 10
1 2 100```

### 输出

```
3```

## 样例 #3

### 输入

```
7 8
35 29 36 88 58 15 25
99 7 49 61 67 4 57
2 3 3
2 5 36
2 6 89
1 6 24
5 7 55
1 3 71
3 4 94
5 6 21```

### 输出

```
160```

# 题解

## 作者：CarroT1212 (赞：7)

### 题目大意

有 $N$ 座岛，你可以进行下列操作：

+ 在第 $i\,(1\le i \le N)$ 座岛上花费 $X_i$ 建一座机场；
+ 在第 $i\,(1\le i \le N)$ 座岛上花费 $Y_i$ 建一座海港；
+ 花费 $Z_i\,(1 \le i \le M)$ 建一座连接第 $A_i$ 座岛和第 $B_i$ 座岛的桥。

如果建了机场的岛都可以互相抵达，建了海港的岛也可以互相抵达，有桥连接的两座岛可以互相抵达，问如果要让这 $N$ 座岛都可以互相直接或间接抵达，最少需要多少花费。

数据范围：$2 \le N \le 2\times 10^5$，$1 \le M \le 2\times 10^5$，$1 \le X_i,Y_i,Z_i \le 10^9$。

### 解法分析

赛时没去动，赛后听学长讲评后发现似乎不难。

这个题看着就很最小生成树，但它好像也不是那么的最小生成树。

其实很简单，以 Kruskal 为例，我们建两个超级源 $N+1,N+2$，分别和所有岛连边，把 $M$ 座可建的桥也当做边，再跑 Kruskal，最终选出来的边中，与 $N+1$ 相连的代表建了机场，与 $N+2$ 相连的代表建了海港。

但是这个方法并不完全对，因为有可能会有这种情况：本来只建机场就能在花费最小的情况下使所有岛连通，这时程序一看，诶，这个 $N+2$ 为啥不连通啊？赶紧找条边给它连上！然后就莫名其妙多了一条边。如果你坚持在只跑一遍 Kruskal 的情况下调掉这一个 bug 的话，你就会发现特别麻烦，所以，我们跑四遍 Kruskal 就好了……

+ 机场、海港都不建；
+ 建机场；
+ 建海港；
+ 机场、海港都建。

这四种情况的实现就是加哪个超级源的区别了，跑完四种情况取个最小值就完事了。

------------

### 代码

只放 Kruskal 版本。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const ll N=2e5+7,M=1e6+7;
struct node { ll from,to,dis; };
ll n,m,x[N],y[N],a[N],b[N],z[N],f[N],ans=1e18,sum;
vector <node> v;
bool cmp(const node i,const node j) { return i.dis<j.dis; }
ll find(ll x) { return f[x]==x?x:f[x]=find(f[x]); }
int main() {
	scanf("%lld%lld",&n,&m);
	for (ll i=1;i<=n+2;i++) f[i]=i;
	for (ll i=1;i<=n;i++) scanf("%lld",&x[i]);
	for (ll i=1;i<=n;i++) scanf("%lld",&y[i]);
	for (ll i=1;i<=m;i++) scanf("%lld%lld%lld",&a[i],&b[i],&z[i]);
	for (ll i=1;i<=m;i++) v.pb({a[i],b[i],z[i]}); // 都不建
	sort(v.begin(),v.end(),cmp);
	for (ll i=1;i<=n+2;i++) f[i]=i;
	for (node i:v) {
		ll r1=find(i.from),r2=find(i.to);
		if (r1!=r2) f[r1]=r2,sum+=i.dis;
	}
	bool flg=1;
	for (ll i=1;i<=n;i++) if (find(i)!=find(1)) {
		flg=0;
		break;
	}
	if (flg) ans=min(ans,sum);sum=0;
	for (ll i=1;i<=n;i++) v.pb({i,n+1,x[i]}); // 只建机场
	sort(v.begin(),v.end(),cmp);
	for (ll i=1;i<=n+2;i++) f[i]=i;
	for (node i:v) {
		ll r1=find(i.from),r2=find(i.to);
		if (r1!=r2) f[r1]=r2,sum+=i.dis;
	}
	flg=1;
	for (ll i=1;i<=n;i++) if (find(i)!=find(1)) {
		flg=0;
		break;
	}
	if (flg) ans=min(ans,sum);sum=0;
	for (ll i=1;i<=n;i++) v.pb({i,n+2,y[i]}); // 机场、海港都建
	sort(v.begin(),v.end(),cmp);
	for (ll i=1;i<=n+2;i++) f[i]=i;
	for (node i:v) {
		ll r1=find(i.from),r2=find(i.to);
		if (r1!=r2) f[r1]=r2,sum+=i.dis;
	}
	flg=1;
	for (ll i=1;i<=n;i++) if (find(i)!=find(1)) {
		flg=0;
		break;
	}
	if (flg) ans=min(ans,sum);sum=0;
	v.clear();
	for (ll i=1;i<=m;i++) v.pb({a[i],b[i],z[i]});
	for (ll i=1;i<=n;i++) v.pb({i,n+2,y[i]}); // 只建海港
	sort(v.begin(),v.end(),cmp);
	for (ll i=1;i<=n+2;i++) f[i]=i;
	for (node i:v) {
		ll r1=find(i.from),r2=find(i.to);
		if (r1!=r2) f[r1]=r2,sum+=i.dis;
	}
	flg=1;
	for (ll i=1;i<=n;i++) if (find(i)!=find(1)) {
		flg=0;
		break;
	}
	if (flg) ans=min(ans,sum);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Register_int (赞：6)

如果不考虑机场与港口，那么就是一个最小生成树问题。  
对机场和港口分别创立一个虚点，建立机场/港口表示为与虚点连接，表示所有建立机场/港口后小岛的连通性，跑最小生成树就能够得到答案。  
最后是坑点：可以不建机场或港口，所以要枚举 $4$ 种虚点的选择情况，分别跑最小生成树取最小值输出。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;
const int MAXM = 6e5 + 10;
const ll inf = ~0ull >> 1;

struct node {
	int u, v;
	ll w;
	bool operator < (const node &rhs) const { return w < rhs.w; }
} e[MAXM];

int fa[MAXN], tot;

int find(int k) {
	return k == fa[k] ? k : fa[k] = find(fa[k]);
}

inline 
bool merge(int x, int y) {
	return (x = find(x)) ^ (y = find(y)) ? fa[x] = y : 0;
}

int n, m, s1, s2;

inline 
ll kruskal(bool x, bool y) {
	ll res = 0, cnt = 0;
	for (int i = 1; i <= n + 2; i++) fa[i] = i;
	for (int i = 1; i <= tot; i++) {
		if (x && (e[i].u == s1 || e[i].v == s1)) continue;
		if (y && (e[i].u == s2 || e[i].v == s2)) continue;
		if (merge(e[i].u, e[i].v)) res += e[i].w, cnt++;
	}
	return cnt == n + 1 - x - y ? res : inf;
}

int main() {
	scanf("%d%d", &n, &m), s1 = n + 1, s2 = n + 2;
	for (int i = 1, x; i <= n; i++) scanf("%d", &x), e[++tot] = { s1, i, x };
	for (int i = 1, x; i <= n; i++) scanf("%d", &x), e[++tot] = { s2, i, x };
	for (int i = 1, u, v, w; i <= m; i++) scanf("%d%d%d", &u, &v, &w), e[++tot] = { u, v, w };
	sort(e + 1, e + tot + 1);
	printf("%lld", min({ kruskal(0, 0), kruskal(1, 0), kruskal(0, 1), kruskal(1, 1) }));
}
```

---

## 作者：DengDuck (赞：2)

让所有点联通，很像最小生成树，考虑如何处理机场和港口。

可以建两个超级源点，一个负责机场，一个负责港口，建立机场或港口相当于往超级源点上连边。

这样就可以解决了，不过机场和港口不一定要建，而直接当成点又会被强制相连，所以要讨论建还是不建。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
    long long s,t,w;
};
long long n,m,a[200005],b[200005],fa[200005],x,y,z;
vector<node>r,v;
bool cmp(node x,node y)
{
    return x.w<y.w;
}
long long find(long long x)
{
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
long long work(int flg1,int flg2)
{
   // cout<<flg1<<' '<<flg2<<endl;
    long long t=n-1;
    v.clear();
    for(auto i:r)
    {
        v.push_back(i);
    }
    if(flg1)
    {
        t++;
        for(int i=1;i<=n;i++)
        {
            v.push_back({n+1,i,a[i]});
        }   
    }
    if(flg2)
    {
        t++;
        for(int i=1;i<=n;i++)
        {
            v.push_back({n+2,i,b[i]});
        }   
    }
    for(int i=1;i<=n+2;i++)
    {
        fa[i]=i;
    }
    sort(v.begin(),v.end(),cmp);
    long long sum=0;
    for(auto i:v)
    {
        if(t==0)break;
        if(find(i.s)==find(i.t))continue;
      //  cout<<i.s<<' '<<i.t<<' '<<i.w<<endl;
        fa[find(i.s)]=find(i.t);
        sum+=i.w;
        t--;
    }
    if(t!=0)return 1e18;
    return sum;
}
int main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&b[i]);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%lld%lld%lld",&x,&y,&z);
        r.push_back({x,y,z});
    }
    printf("%lld",min(work(1,1),min(work(1,0),min(work(0,1),work(0,0)))));
}

```

---

## 作者：NobodyThere (赞：1)

[Link](https://www.luogu.com.cn/problem/AT_abc270_f)

### Idea

观察三种修建方式。容易发现若只有第三种修建方式，那么要在最小花费的情况下，使所有点连通，一定是找一棵最小生成树。

而第一、二种修建方式呢？无非就是把所有修建了机场和修建了港口的点分别全部连接起来。

当然，两两之间建边的话，复杂度是 $\mathcal O(n^2)$ 的，效率太低了。

事实上，我们不需要建这么多边，我们只需要新建一个虚拟结点，并将所有点连向这个虚拟结点，边权为建造机场/港口的花费。

有一种更形象的理解方式：

- 在某个点建机场就是建一条从这个点到天空的边。

- 在某个点建港口就是建一条从这个点到水域的边。

于是问题就很简单了。枚举点集是否包含两个名为“天空”“水域”的结点，分别跑最小生成树即可。

### Code

```cpp
#include <cstdio>
#include <algorithm>
typedef long long ll;
const int NMAX = 2e5, MMAX = 6e5;
const ll INF = 1ll << 60;
int N, M, A[NMAX + 7], B[NMAX + 7]; ll Z[NMAX + 7], X[NMAX + 7], Y[NMAX + 7];
int n, m;
struct edge {
	int a, b; ll w;
	bool operator <(edge ed) {return w < ed.w;}
}l[MMAX + 7];
int fa[NMAX + 7], siz[NMAX + 7];
int anc(int i) {return i == fa[i] ? i : fa[i] = anc(fa[i]);}
ll solve() { // MST，记得判无解
	ll res = 0; int cnt = 0;
	std::sort(l + 1, l + m + 1);
	for(int i = 1; i <= n; i++)
		fa[i] = i, siz[i] = 1;
	for(int i = 1; i <= m; i++) {
		int a = l[i].a, b = l[i].b; ll w = l[i].w;
		if((a = anc(a)) == (b = anc(b))) continue;
		if(siz[a] > siz[b]) std::swap(a, b);
		res += w, fa[a] = b, siz[b] += siz[a];
		if(++cnt >= n - 1) break;
	}
	res = cnt < n - 1 ? INF : res;
	return res;
}
ll ans;
int main() {
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= N; i++)
		scanf("%lld", &X[i]);
	for(int i = 1; i <= N; i++)
		scanf("%lld", &Y[i]);
	for(int i = 1; i <= M; i++)
		scanf("%d %d %lld", &A[i], &B[i], &Z[i]);
	for(int i = 1; i <= M; i++) // 只有道路
		l[i] = (edge){A[i], B[i], Z[i]};
	n = N, m = M;
	ans = solve();
	++n, m += N;
	for(int i = 1; i <= M; i++) // 有海港
		l[i] = (edge){A[i], B[i], Z[i]};
	for(int i = 1; i <= N; i++)
		l[M + i] = (edge){i, n, Y[i]};
	ans = std::min(ans, solve());
	for(int i = 1; i <= M; i++) // 有机场
		l[i] = (edge){A[i], B[i], Z[i]};
	for(int i = 1; i <= N; i++)
		l[M + i] = (edge){i, n, X[i]};
	ans = std::min(ans, solve());
	for(int i = 1; i <= M; i++) // 都有
		l[i] = (edge){A[i], B[i], Z[i]};
	for(int i = 1; i <= N; i++)
		l[M + i] = (edge){i, n, X[i]};
	for(int i = 1; i <= N; i++)
		l[m + i] = (edge){i, n + 1, Y[i]};
	++n, m += N;
	ans = std::min(ans, solve());
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：wnsyou (赞：1)

# [Transportation](https://www.luogu.com.cn/problem/AT_abc270_f)

## 题意

有 $n$ 个城市，你可以执行以下操作若干次：

- 选择一个没有建机场的城市 $i$，花费 $x_i$ 建一个机场。
- 选择一个没有建港口的城市 $i$，花费 $y_i$ 建一个港口。

还有 $m$ 条没有修建的道路，第 $i$ 条道路双向连接 $a_i$ 和 $b_i$，修建这条道路需要花费 $z_i$。

两个城市 $u$ 和 $v$ 直接可达当且仅当：

- $u$ 和 $v$ 都有机场。
- $u$ 和 $v$ 都有港口。
- $u$ 和 $v$ 直接有一条道路。

求最小花费，使得从任意一个城市 $u$ 可以在经过若干城市后抵达任意一个城市 $v$。

## 思路

这题只考建图和最小生成树。

### 初步考虑

首先，不看机场和港口，那么就变成了一个最小生成树问题。

### 特殊情况

那么有机场呢？画张草图看看吧。

![](https://cdn.luogu.com.cn/upload/image_hosting/ufr9aisv.png)

上面那种建图方式，就是在两个有机场的城市间建边，不仅难以维护花费，你也不知道有多少个城市建了机场，建图方式不够优秀。

### 优化建图

这种建图方式值得思考。

根据题意，两个有机场的城市可以互相抵达，**相当于有一个机场聚集地**，设立机场的城市可以来到这个聚集地，并从这里走向另外一个设立机场的城市。

那么维护起来就很方便了，假定机场聚集地在 $n+1$，那么就可以把 $i = 1,2\cdots n$ 中的每个 $i$ 都向 $n + 1$ 建立一条候选边，边权为 $x_i$。

上图就会变成： 

![](https://cdn.luogu.com.cn/upload/image_hosting/ibcmcc94.png)

港口同理，将聚集地设置为与机场聚集地不同的一个即可(也不能和任何一座城市下标相同)，建议设为 $n+2$。

### 最后思考

可我并不知道是否要通过建立机场来互相抵达啊？

这个也不难，枚举是否建立机场和是否建立港口，跑一遍克鲁斯卡尔，求出 $4$ 种情况中花费最小值即可。

## 复杂度

- 时间：$O((n+m) \log (n+m))$。
- 空间：$O(n+m)$。

## Code

```cpp
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

const int N = 2e5 + 10, E = 6e5 + 10;

struct Edge {
  int x, y, z;
  bool operator < (const Edge &i) const {
    return z < i.z;
  }
} e[N], a[E];

int n, m, x[N], y[N], fa[N], ae;
ll ans = 1e18;

int Find (int x) {
  return (fa[x] ? fa[x] = Find(fa[x]) : x);
}

ll kruskal (bool f1, bool f2) { // 克鲁斯卡尔算法
  ll sum = 0;
  int num = 0;
  sort(a + 1, a + ae + 1);
  for (int i = 1; i <= ae; i++) { // 这些不用说了吧
    int l = Find(a[i].x), r = Find(a[i].y);
    if (l != r) {
      sum += a[i].z, num++, fa[l] = r;
    }
  }
  if (num == n + f1 + f2 - 1) { // 注意！题目并不保证在只走普通道路的情况下一定合法，需判断
    return sum;
  }
  return 1e18;
}

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> x[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> y[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> e[i].x >> e[i].y >> e[i].z;
  }
  for (int i = 0; i < 2; i++) { // 是否建立机场
    for (int j = 0; j < 2; j++) { // 是否建立港口
      for (int k = 1; k <= n + 2; k++) {
        fa[k] = 0; // 先清空
      }
      ae = 0;
      for (int k = 1; k <= m; k++) { // m 条道路
        a[++ae] = e[k];
      }
      if (i) { // 走机场
        for (int k = 1; k <= n; k++) {
          a[++ae] = {k, n + 1, x[k]};
        }
      }
      if (j) { // 走港口
        for (int k = 1; k <= n; k++) {
          a[++ae] = {k, n + 2, y[k]};
        }
      }
      ans = min(ans, kruskal(i, j));
    }
  }
  cout << ans;
  return 0;
}
```



---

## 作者：mz2022 (赞：0)

题目大意
--------
给你 $n$ 个点求最小生成树，有以下三个操作。

$1$：建一条 $u$ 到 $v$ 的边边权为 $w$。

$2$：在 $i$ 点建一个机场，代价为 ${x_i}$。

$3$：在 $i$ 点建一个海港，代价为 ${y_i}$。

对于点 $u$ 和点 $v$ 满足以下任意一个条件，则点 $u$ 和点 $v$ 连通。

$1$：$u$ 到 $v$ 有边。

$2$：$u$ 和 $v$ 都有机场。

$3$：$u$ 和 $v$ 都有海港。

思路：
--------
建立两个超级源点 $i + 1$ 和 $i + 2$，把点权转化为边权，然后讨论以下四种情况取最小值：

$1$：只建机场。

$2$：只建海港。

$3$：机场和海港都建。

$4$：机场和海港都不建。

Code：
--------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m, tot = 0, last_tot = 0, x[200005], y[200005], fa[200005];
struct no {
	int a, b, w;
} ed[200005];
bool cmp (no a, no b) {
	return a.w < b.w;
}
void init () {
	for (int i = 1; i <= n + 2; i++)fa[i] = i;
}
int find (int x) {
	if (fa[x] == x) return x;
	return fa[x] = find (fa[x]);
}
int kruscal () {
	sort (ed + 1, ed + 1 + tot, cmp);
	init ();
	int res = 0, cnt = 0;
	for (int i = 1; i <= tot; i++) {
		int a = ed[i].a, b = ed[i].b, w = ed[i].w;
		a = find (a), b = find (b);
		if (a != b) {
			fa[a] = b;
			res += w;
			cnt ++;
		}
	}
	if (cnt < n - 1)return LLONG_MAX;
	else return res;
}
int kruscall() {
	sort (ed + 1, ed + 1 + last_tot, cmp);
	init ();
	int res = 0, cnt = 0;
	for (int i = 1; i <= last_tot; i++) {
		int a = ed[i].a, b = ed[i].b, w = ed[i].w;
		a = find (a), b = find (b);
		if (a != b) {
			fa[a] = b;
			res += w;
			cnt ++;
		}
	}
	if (cnt < n - 1)return LLONG_MAX;
	else return res;
}
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> y[i];
	}
	for (int x, y, v, i = 1; i <= m; i++) {
		cin >> x >> y >> v;
		ed[++tot] = {x, y, v};
		ed[++tot] = {y, x, v};
	}
	int ans1 = kruscal()//机场和海港都不建。 
	int last_tot = tot;
	for (int i = 1; i <= n; i++) {
		ed[++tot] = {i, n + 1, x[i]};//化点权为边权。
		ed[++tot] = {n + 1, i, x[i]};
	}
	int ans2 = kruscal();//只建机场。 
	for (int i = 1; i <= n; i++) {
		ed[++tot] = {i, n + 2, y[i]};
		ed[++tot] = {n + 2, i, y[i]};
	}
	int ans3 = kruscal();//机场和海港都建。
	for (int i = 1; i <= n; i++) {
		ed[++last_tot] = {i, n + 1, y[i]};
		ed[++last_tot] = {n + 1, i, y[i]};
	}
	int ans4 = kruscall();//只建海港。 
	cout << min(min(ans1, ans2), min(ans3, ans4));
	return 0;
}
```

---

## 作者：Mingrui_Yang (赞：0)

[luogu 传送门](https://www.luogu.com.cn/problem/AT_abc270_f)

## 思路

本题的科技是 **最小生成树**。

如果只建桥，那就是一道非常明显的最小生成树。   
所以我们考虑该如何处理建港口、建机场的情况。

建两个超级源点 $s1, s2$。   
将建港口的点与 $s1$ 连接，边的权值为建港口的代价，这样所有建港口的点就连起来了。   
将建机场的点与 $s2$ 连接，边的权值为建机场的代价，这样所有建机场的点就连起来了。   

这样就可以开始跑最小生成树了。   
考虑是稀疏图，所以使用 kruskal 算法。   
需要跑 $4$ 次。
* 建机场 & 建港口
* 只建机场
* 只建港口
* 都不建（只有桥）

## CODE

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 6e5 + 10;
int n, m;
int s1, s2;
struct Edge {
	int u, v, w;
	bool operator < (const Edge &W) const {return w < W.w; }
} edges[N];
int fa[N];
int find(int x) {
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
int kruskal(int x, int y) {
	int res = 0, cnt = 0;
	for (int i = 1; i <= n + 2; i ++ ) fa[i] = i;
	for (int i = 1; i <= 2 * n + m; i ++ ) {
		if (x && edges[i].v == s1) continue;
		if (y && edges[i].v == s2) continue;
		int a = find(edges[i].u), b = find(edges[i].v);
		if (a != b) {
			fa[a] = b;
			res += edges[i].w;
			cnt ++ ;
		}
	}
	if (cnt < n + 2 - x - y - 1) return 0x3f3f3f3f3f3f3f3f;
	return res;
}
signed main() {
	int a, b, c;
	cin >> n >> m;
	s1 = n + 1, s2 = n + 2;
	for (int i = 1; i <= n; i ++ ) cin >> c, edges[i] = {i, s1, c};
	for (int i = 1; i <= n; i ++ ) cin >> c, edges[i + n] = {i, s2, c};
	for (int i = 1; i <= m; i ++ ) cin >> a >> b >> c, edges[i + 2 * n] = {a, b, c};
	sort(edges + 1, edges + 2 * n + m + 1);
	cout << min({kruskal(0, 0), kruskal(1, 0), kruskal(0, 1), kruskal(1, 1)}) << endl;
	return 0;
}
```

---

## 作者：541forever (赞：0)

ABC270F

题目大意

有 $n$ 个点，有 $m$ 条可供选择的无向边，边有边权，同时，你还可以在城市 $i$ 建上航空港或码头，建航空港的代价为 $x_i$，建码头的代价为 $y_i$，拥有航空港的的城市可以互相到达，同理，拥有码头的城市也可以互相到达，求使该图联通的最小代价。

考虑建 $2$ 个虚点，分别将这两个虚点连向所有点，边权分别为 $x_i$ 和 $y_i$，但这样直接跑最小生成树会存在一个问题，就是这两个虚点一定都被选到了，即一定会建造航空港和码头，然而这样并不一定会更优，因此进一步进行分类讨论，即是否使用这两个虚点，每次都直接跑 Kruskal，最后再将所有答案取个最小值即可。

---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$
要求使所有岛屿联通的最小代价，不难想到最小生成树，而这里我们发现有三种不同的边，所以我们分情况讨论。

首先，先看第 $3$ 类连边方式，建一座桥既有起点终点，也有边权，所以我们直接将其建在图上，因为无论其他两种边如何建，都不会因为建桥的这一类边而使得结果的改变。

然后，再看 $1$ 与 $2$ 这两类的建图，我们可以分别建一个超级远点，所有建了机场或港口的点都连向这个岛屿，边权为建机场或港口的费用。

接着，再来研究如何解决其他两种方式对答案的影响，大致能分为以下四种情况：

1. 只建桥；
2. 只不建港口；
3. 只不建机场；
4. 都建；

最后，每种情况分别跑一遍最小生成树，判断是否能使岛屿联通，能使岛屿联通的情况中取最小答案输出就行了。

```cpp

/*
	Luogu name: Symbolize
	Luogu uid: 672793
*/
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(register auto i:x)
#define debug() puts("----------")
const int N=1e6+10;
const int inf=0x3f3f3f3f3f3f3f3f;
const double pi=acos(-1);
using namespace std;
typedef complex<double> cp;
int n,m,fa[N],x[N],y[N],a[N],b[N],z[N],sum,ans=inf;
bool res;
struct node
{
	int u,v;
	int dist;
};
vector<node> v;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
bool cmp(node x,node y){return x.dist<y.dist;}
int find(int x)
{
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
signed main()
{
//	#ifndef ONLINE_JUDGE
//		freopen(".in","r",stdin);
//		freopen(".out","w",stdout);
//	#endif
	n=read();
	m=read();
	//n+1机场超级远点，n+2港口超级远点 
	rep1(i,1,n) x[i]=read();//机场 
	rep1(i,1,n) y[i]=read();//港口 
	rep1(i,1,m)//桥梁 
	{
		a[i]=read();
		b[i]=read();
		z[i]=read();
	}
	//--------------------情况1 
	res=1;
	sum=0;
	rep1(i,1,n+2) fa[i]=i;
	rep1(i,1,m) v.push_back({a[i],b[i],z[i]});
	//Kruskal求最小生成树 
	sort(v.begin(),v.end(),cmp);
	rep4(i,v)
	{
		int X=find(i.u),Y=find(i.v);
		if(X!=Y)
		{
			fa[X]=Y;
			sum+=i.dist;
		}
	}
	rep1(i,1,n)
	{
		if(find(i)!=find(1))
		{
			res=0;
			break;
		}
	}
	if(res) ans=min(ans,sum);//满足条件取最小值 
	//--------------------情况2 
	res=1;
	sum=0;
	rep1(i,1,n+2) fa[i]=i;
	rep1(i,1,n) v.push_back({i,n+1,x[i]});
	//Kruskal求最小生成树 
	sort(v.begin(),v.end(),cmp);
	rep4(i,v)
	{
		int X=find(i.u),Y=find(i.v);
		if(X!=Y)
		{
			fa[X]=Y;
			sum+=i.dist;
		}
	}
	rep1(i,1,n)
	{
		if(find(i)!=find(1))
		{
			res=0;
			break;
		}
	}
	if(res) ans=min(ans,sum);//满足条件取最小值 
	//--------------------情况3 
	res=1;
	sum=0;
	rep1(i,1,n+2) fa[i]=i;
	rep1(i,1,n) v.push_back({i,n+2,y[i]});
	//Kruskal求最小生成树 
	sort(v.begin(),v.end(),cmp);
	rep4(i,v)
	{
		int X=find(i.u),Y=find(i.v);
		if(X!=Y)
		{
			fa[X]=Y;
			sum+=i.dist;
		}
	}
	rep1(i,1,n)
	{
		if(find(i)!=find(1))
		{
			res=0;
			break;
		}
	}
	if(res) ans=min(ans,sum);//满足条件取最小值 
	//--------------------情况4 
	res=1;
	sum=0;
	rep1(i,1,n+2) fa[i]=i;
	v.clear();
	rep1(i,1,m) v.push_back({a[i],b[i],z[i]});
	rep1(i,1,n) v.push_back({i,n+2,y[i]});
	//Kruskal求最小生成树 
	sort(v.begin(),v.end(),cmp);
	rep4(i,v)
	{
		int X=find(i.u),Y=find(i.v);
		if(X!=Y)
		{
			fa[X]=Y;
			sum+=i.dist;
		}
	}
	rep1(i,1,n)
	{
		if(find(i)!=find(1))
		{
			res=0;
			break;
		}
	}
	if(res) ans=min(ans,sum);//满足条件取最小值 
	//--------------------
	cout<<ans<<endl;//输出 
	return 0;
}
```

---

## 作者：high_sky (赞：0)

### 思路
如果要让价值最小，那肯定是用 `最小生成树` 啦~

只需要建立两个超级源点，做四次最小生成树，分别为：道路、机场、海港、都有（可以不建机场和海港）。

最后取这四者的最小值，就是本题的答案了。

### Code
代码贴上，注释在上：
```cpp
#include <bits/stdc++.h>//万能头
#define LL long long// 简写 long long
using namespace std;
const int N = 2e5 + 5;// 最大数组
const LL inf = 0x3f3f3f3f3f3f3f7f;//最大值
struct edge {// 结构体
    int x, y, z;//从x到y需要花费z
    bool friend operator<(edge x, edge y) { return x.z < y.z; }//自动排序
} e[N << 2];
int n, m, idx, a[N], b[N], u[N], v[N], w[N], fa[N];//定义数组
LL ans = inf;
inline int Get(int x) { return fa[x] == x ? x : fa[x] = Get(fa[x]); }//并查集
inline LL Kruskal(int n) {
    for (int i = 1; i <= n; i++) fa[i] = i;//初始化
    sort(e + 1, e + 1 + idx);//排序——贪心策略
    LL res = 0, cnt = 0;//以下的是模板
    for (int i = 1, fx, fy; i <= idx && cnt < n - 1; i++) {
        fx = Get(e[i].x);
        fy = Get(e[i].y);
        if (fx ^ fy)// 可以写成 if(fx!=fy)
            fa[fx] = fy, ++cnt, res += e[i].z;
    }
    return cnt == n - 1 ? res : inf;//返回值
}
int main() {
    //输入
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= m; i++) cin >> u[i] >> v[i] >> w[i];
    //四次最小生成树
    for (int k = 0, node; k < 4; k++) {
        node = n, idx = 0;
        if (k & 1) {
            ++node;
            for (int i = 1; i <= n; i++) e[++idx] = (edge){ i, node, a[i] };
        }
        if (k & 2) {
            ++node;
            for (int i = 1; i <= n; i++) e[++idx] = (edge){ i, node, b[i] };
        }
        for (int i = 1; i <= m; i++) e[++idx] = (edge){ u[i], v[i], w[i] };
        ans = min(ans, Kruskal(node));//取最小值
    }
    cout << ans << endl;//输出
    return 0;
}
```

---

