# [PA 2025] 瞬间传送 / Teleport

## 题目背景

PA 2025 R1A.

## 题目描述

给定一张 $n$ 个节点的简单无向连通图，边权全为 $1$。

在图中加入一条边权为 $0$ 的边，最小化**加边后**这张图的 $\displaystyle \max_{1\le u,v\le n} \{\operatorname{dist}(u,v)\}$。只需要求出 $\displaystyle \max_{1\le u,v\le n} \{\operatorname{dist}(u,v)\}$ 的最小值。

这里，$\operatorname{dist}(u,v)$ 定义为 $u,v$ 间最短路长度。


## 说明/提示

### 样例解释

- 样例 $1$ 解释：给定的图是完全图，无论怎么加边，最长的最短路边权总是 $1$。
- 样例 $2$ 解释：加边 $(1,5)$ 即可。

### 数据范围

- $1\le T\le 21$；
- $1\le n,\sum n\le 400$；
- 给定图是简单无向连通图；
- $s_{i,j}=s_{j,i}$，且 $s_{i,i}=\texttt{0}$。

## 样例 #1

### 输入

```
2
4
0111
1011
1101
1110
5
01000
10100
01010
00101
00010```

### 输出

```
1
2```

# 题解

## 作者：Rainbow_qwq (赞：8)

假设从大到小枚举 $ans$，同时维护当前的每个连 $(u,v)$ 是否可行。

关键观察：对于一个 $i$，连 $(u,v)$  且 $dis(i,u)\le dis(i,v)$ 的话，如果 $dis(i,k)>ans$，从 $i\to k$ 走的方法一定是 $i\to u\to v\to k$。

对于每个 $i$ 分别做以下过程：对于 $dis(i,k) > ans$（即不合法的点），只需要对所有 $v$ 维护 $\max(dis(v,k))$，然后把 $dis(i,u)+\max(dis(v,k))>ans$ 的 $(u,v)$ 弹掉。

时间复杂度 $O(n^3)$。

```cpp
#define maxn 505
#define inf 0x3f3f3f3f

int n,dis[maxn][maxn];
char s[maxn];
int c[maxn][maxn],all;
int mx[maxn][maxn],p[maxn][maxn];

void sub(int u,int v){
	if(u>v)swap(u,v);
	if(c[u][v])c[u][v]=0,--all;
}

int ps[maxn],qs[maxn][maxn];
void work(int up){
//	cout<<"work "<<up<<endl;
	For(i,1,n){
		int *p=::p[i];
		while(dis[i][p[ps[i]]]>up){
			int u=p[ps[i]];
			For(j,1,n)
				mx[i][j]=max(mx[i][j],dis[p[j]][u]);
			--ps[i];
		}
		if(ps[i]==n) continue;
		For(j,1,n){
			int v=p[j];
			while(qs[i][j]>=1){
				int u=p[qs[i][j]];
				if(dis[i][u]+mx[i][j]<=up) break;
		//		cout<<"sub "<<i<<" "<<u<<" "<<v<<endl;
				sub(u,v);
				--qs[i][j];
			}
			// dis(i,u) + mx[v] > up: baodiao u
		}
	}
//	For(i,1,n){
//		For(j,i+1,n) cout<<c[i][j]<<" "; cout<<"\n";
//	}
}

void work()
{
	n=read();
	For(i,1,n){
		scanf("%s",s+1);
		For(j,1,n)dis[i][j]=(s[j]&1)?1:inf;
		dis[i][i]=0;
	}
	For(k,1,n)For(i,1,n)For(j,1,n)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	all=0;
	For(i,1,n)For(j,i+1,n)c[i][j]=n,++all;
	For(i,1,n){
		For(j,1,n)p[i][j]=j;
		sort(p[i]+1,p[i]+n+1,[&](int u,int v){
			return dis[i][u]<dis[i][v];
		});
		ps[i]=n;
		For(j,1,n) qs[i][j]=j-1,mx[i][j]=-inf;
	}
	Rep(i,n-1,1){
		work(i);
		if(!all){
			cout<<i+1<<endl;
			return;
		}
	}
	cout<<1<<endl;
}

signed main()
{
	int T=read();
	while(T--)work();
	return 0;
}
/*
2
4
0111
1011
1101
1110
5
01000
10100
01010
00101
00010
*/
```

---

## 作者：cqbzlym (赞：4)

<https://www.luogu.com.cn/problem/P11915>

需要观察到一个很厉害的贪心策略：如果钦定所有点的距离不大于 $r$，且存在 $d(i,j)>r$。**假设** 一种满足条件的新边是 $(u,v)$（由于两者无序，不妨钦定 $d(i,u)<d(i,v)$），可以进行讨论：

1. $d(j,v)<d(j,u)$：

   此时最优路径为 $i\to u\to v\to j$，判断一下这种方案是否不大于 $r$ 就可以了。
1. $d(j,v)\ge d(j, u)$：

   此时不管是走 $i\to u\to v\to j$ 还是 $i\to v\to u\to j$ 都不如走已经存在的 $i\to u\to j$ 这条路径，也就是说如果要走新边，代价是一定比原距离大，更是比 $r$ 大的；也就是说，$(u,v)$ 不能解决 $(i,j)$ 之间的问题，假设就不成立了。

综上，只需要判断 $i\to u\to v\to j\le r$ 是否成立，就可以判断 $(u,v)$ 是否合法。从大到小枚举 $r$，同时维护当前依然合法的 $(u,v)$（显然是有单调性的），对于不合法的 $(i,j)$，枚举每个 $i$，维护 $\max\{d(v,j)\}$，精细实现（主要是利用各种均摊）一下就能 $O(n^3)$。

这里具体提一下需要摊的几个点：

1. 枚举到 $r$ 的时候用所有 $d(i,j)=r+1$ 把 $v$ 在 $i$ 处的最大 $d(v,j)$ 更新，方便后面 $O(n)$ 地 check。摊出来是 $O(n^3)$ 的。
1. 枚举仍然处在合法队列里的 $(u,v)$，如果 check 合法，就说明对于当前 $r$ 至少存在一个合法解，就可以 `break` 了；否则，把 $(u,v)$ 弹出，继续 check 下一条边。这样每条边只会被弹出一次，而未弹出边的 check 次数最多是 $O(n)$；加上 $O(n)$ 的 check，摊出来是 $O(n^3)$ 的。

```cpp
#include <bits/stdc++.h>
const int inf = 0x3f3f3f3f;
int main() {
#ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
#else
    std::freopen(".in", "r", stdin);
    std::freopen(".out", "w", stdout);
#endif
    int T;
    for (std::cin >> T; T--; ) {
        int n;
        std::cin >> n;
        std::vector<std::vector<int> > g(n + 1, std::vector<int> (n + 1, inf));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) {
                char t;
                std::cin >> t;
                if (t == '1' || i == j)
                    g[i][j] = t - '0';
            }
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                if (i != k)
                    for (int j = 1; j <= n; ++j)
                        if (j != i && j != k)
                            g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]);
        std::queue<std::pair<int, int> > q;
        std::vector<std::vector<std::pair<int, int> > > p(n + 1);
        std::vector<std::vector<int> > mx(n + 1, std::vector<int> (n + 1));
        for (int i = 1; i < n; ++i)
            for (int j = i + 1; j <= n; ++j) {
                q.emplace(i, j);
                p[g[i][j] - 1].emplace_back(i, j);
            }
        auto check = [&](int u, int v, int r) {
            for (int i = 1; i <= n; ++i) {
                if (g[u][i] > g[v][i])
                    std::swap(u, v);
                if (g[u][i] + mx[v][i] > r)
                    return false;
            }
            return true;
        };
        for (int r = n; r >= -1; --r) {
            for (auto [i, j] : p[r])
                for (int v = 1; v <= n; ++v) {
                    mx[v][i] = std::max(mx[v][i], g[v][j]);
                    mx[v][j] = std::max(mx[v][j], g[v][i]);
                }
            for (; !q.empty(); ) {
                auto [u, v] = q.front();
                if (!check(u, v, r))
                    q.pop();
                else
                    break;
            }
            if (q.empty()) {
                std::cout << r + 1 << '\n';
                break;
            }
        }
    }
    return 0;
}
```

---

## 作者：Starrykiller (赞：4)

$\mathcal{O}(n^4\log n/w)$ 做法。但是常数非常小，实际表现很好。

考虑二分答案 $l$，枚举加入的边 $(u,v)$。

如果不合法，那么必然存在一对 $s,t$，使得 $\operatorname{dist}'(s,t)\ge l+1$。

预处理出原图的 $\operatorname{dist}$，枚举 $s$。如果 $t$ 不合法，那么必须满足：

- $\operatorname{dist}(s,t)\ge l+1$；
- $\operatorname{dist}(s,u)+\operatorname{dist}(v,t)\ge l+1\implies \operatorname{dist}(v,t)\ge l-\operatorname{dist}(s,u)+1$；
- $\operatorname{dist}(s,v)+\operatorname{dist}(u,t)\ge l+1\implies \operatorname{dist}(u,t)\ge l-\operatorname{dist}(s,v)+1$。

我们枚举了 $u,v,s$。我们可以预处理 $f(u,i)=\{v:\operatorname{dist}(u,v)\ge i\}$，这样判定的时候只需要判定三个集合交集是否非空。

使用 $\texttt{bitset}$ 维护集合，时间复杂度即为 $\mathcal{O}(n^3\cdot n/w \cdot \log n)=\mathcal{O}(n^4 \log n / w)$。

有一个显然的剪枝：如果 $(u,v)$ 已经合法，直接返回 `true` 即可。这样在官方数据下跑得飞快。（如果不加这个剪枝，在洛谷上依然可以通过。）

赛时担心被卡加了随机化打乱点权，在洛谷上运行时间为 $\text{311 ms}$。

如果有人能够提供在随机化下能够几乎一定将本做法卡到复杂度上界的数据，欢迎联系我。


```cpp
auto check=[&](int L) {
    for (int u=0; u<n; ++u)
        for (int v=u+1; v<n; ++v) {
            bool flag=true;
            for (int s=0; s<n; ++s) {
                // dis[s][t]>=L+1
                // dis[v][t]>=L+1-dis[s][u]
                // dis[u][t]>=L+1-dis[s][v]
                int a=max(0,L+1-dis[s][u]), b=max(0,L+1-dis[s][v]);
                if ((f[s][L+1]&f[v][a]&f[u][b]).any()) {
                    flag=false; break;
                }
            }
            if (flag) return true;
        }
    return false;
};

int l=0, r=(n+1)/2;
while (l<r) {
    int mid=(l+r)>>1;
    if (check(mid)) r=mid;
    else l=mid+1;
}
cout<<l<<'\n';
```

---

## 作者：lalaouye (赞：2)

这题有一车 $\mathcal{O}(n^4)$ 做法，但是很难优化到 $\mathcal{O}(n^3)$，因为我们有 $n^2$ 个限制点对和 $n^2$ 个加边选择。要想优化必须考虑某些东西一起处理。

考虑答案从大到小的性质，发现可行的加边选择只会存在于一段后缀，于是考虑答案从大到小去 check 是否可行，于是我们要动态去删除不能坚持下去的加边选择，并且动态加入关键限制点对，就是说原图中距离已经大于当前大于 $ans$ 的点对。

考虑分析一些性质，即如何去考虑限制，如果点对 $(x,y)$ 原图中距离已经大于 $ans$，那么对于新加的边 $(i,j)$，此时若 $dis(x,i)\le dis(y,i)$，那么如果 $x\rightarrow i\rightarrow j\rightarrow y$ 的距离大于 $ans$ 就能够把 $(i,j)$ 扔掉了。

证明手玩一下即可，$i$ 走更远的点不会变得合法。

有了这个规则之后我们就可以将一些性质一起处理，比如说我们对于点对 $(i,j)$，考虑枚举 $x$ 去扔掉它。那么如果对于 $x$，如果 $dis(x,i)+\max(dis(j,y))>ans$ 则可以扔掉 $(i,j)$。

具体实现考虑先枚举 $x$，我们对于每个 $x$ 维护出一个编号数组，他是按照 $x$ 到他们的距离排序的。那么在 $x$ 的数组中，被淘汰的 $(p_i,p_j)$ 对于 $j$ 来说这样的 $i$ 只存在与一个末尾为 $j$ 的后缀。

这样均摊即可做到 $\mathcal{O}(n^3)$。

代码：


```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i (l); i <= (r); ++ i)
#define rrp(i, l, r) for (int i (r); i >= (l); -- i)
#define eb emplace_back
using namespace std;
#define pii pair <int, int>
#define inf 1000000000
#define ls (p << 1)
#define rs (ls | 1)
constexpr int N = 400 + 5, M = 1e5, P = 998244353, B = 400;
typedef long long ll;
typedef unsigned long long ull;
inline int rd () {
  int x = 0, f = 1;
  char ch = getchar ();
  while (! isdigit (ch)) {
    if (ch == '-') f = -1;
    ch = getchar ();
  }
  while (isdigit (ch)) {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar ();
  }
  return x * f;
}
int n;
int dis[N][N];
char s[N][N];
int ps[N][N], p[N][N], mx[N][N];
bool ext[N][N];
int cnt;
void D (int u, int v) {
  if (u > v) swap (u, v);
  if (! ext[u][v]) ++ cnt;
  ext[u][v] = 1;
}
void solve () {
  memset (ext, 0, sizeof ext); cnt = 0;
  n = rd ();
  rep (i, 1, n) scanf ("%s", s[i] + 1);
  rep (i, 1, n) {
    rep (j, 1, n) {
      if (s[i][j] == '0') dis[i][j] = 1e9; else dis[i][j] = 1;
    } dis[i][i] = 0;
  }
  rep (k, 1, n) {
    rep (i, 1, n) {
      rep (j, 1, n) {
        dis[i][j] = min (dis[i][j], dis[i][k] + dis[k][j]);
      }
    }
  }
  rep (i, 1, n) {
    rep (j, 1, n) p[i][j] = j, ps[i][j] = j - 1, mx[i][j] = -1e9;
    sort (p[i] + 1, p[i] + n + 1, [&] (int x, int y) { return dis[i][x] < dis[i][y]; });
  }
  rrp (t, 1, n) {
    rep (i, 1, n) {
      rep (j, 1, n) {
        if (dis[i][j] == t + 1) {
          rep (v, 1, n) {
            mx[i][v] = max (mx[i][v], dis[v][j]);
          }
        }
      }
    }
    rep (i, 1, n) {
      rep (j, 1, n) {
        while (ps[i][j] && dis[i][p[i][ps[i][j]]] + mx[i][p[i][j]] > t) {
          D (p[i][ps[i][j]], p[i][j]); -- ps[i][j];
        }
      }
    }
    if (cnt == n * (n - 1) / 2) {
      cout << t + 1 << endl; return ;
    }
  } puts ("1");
}
int32_t main () {
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  for (int T (rd ()); T; -- T) solve ();
  
}
```

---

