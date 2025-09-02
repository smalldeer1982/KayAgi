# Doctor's Brown Hypothesis

## 题目描述

The rebels have been crushed in the most recent battle with the imperial forces, but there is a ray of new hope.

Meanwhile, on one of the conquered planets, Luke was getting ready for an illegal street race (which should come as no surprise, given his family history). Luke arrived at the finish line with 88 miles per hour on his speedometer. After getting out of the car, he was greeted by a new reality. It turns out that the battle has not happened yet and will start in exactly $ k $ hours.

The rebels have placed a single battleship on each of the $ n $ planets. $ m $ unidirectional wormholes connect the planets. Traversing each wormhole takes exactly one hour. Generals of the Imperium have planned the battle precisely, but their troops cannot dynamically adapt to changing circumstances. Because of this, it is enough for the rebels to move some ships around before the battle to confuse the enemy, secure victory and change the galaxy's fate.

Owing to numerous strategical considerations, which we now omit, the rebels would like to choose two ships that will switch places so that both of them will be on the move for the whole time (exactly $ k $ hours). In other words, rebels look for two planets, $ x $ and $ y $ , such that paths of length $ k $ exist from $ x $ to $ y $ and from $ y $ to $ x $ .

Because of the limited fuel supply, choosing one ship would also be acceptable. This ship should fly through the wormholes for $ k $ hours and then return to its initial planet.

How many ways are there to choose the ships for completing the mission?

## 说明/提示

In the first sample test, one can choose pairs of ships from the following planets: $ 2 $ and $ 5 $ , $ 3 $ and $ 5 $ , $ 1 $ and $ 4 $ . Individual ships from planets $ 6 $ and $ 7 $ could also be chosen.

In the second sample test, one can choose a pair of ships from the following planets: $ 2 $ and $ 3 $ . Individual ships from planets $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , and $ 5 $ could also be chosen.

In the third sample test, there are no pairs of ships we can choose. Individual ships from planets $ 2 $ and $ 3 $ could also be chosen.

## 样例 #1

### 输入

```
7 8 346
1 2
1 3
2 4
3 4
4 5
5 1
6 7
7 6```

### 输出

```
5```

## 样例 #2

### 输入

```
5 6 128
1 2
1 3
2 4
3 4
4 5
5 1```

### 输出

```
6```

## 样例 #3

### 输入

```
3 3 30
1 2
2 3
3 2```

### 输出

```
2```

# 题解

## 作者：JCY_ (赞：15)

[更好的阅读体验](https://www.cnblogs.com/JCY-std/p/17497579.html)

### 题意简述

给你一张 $n$ 个点 $m$ 条边的有向图，你需要找出有多少个点对 $(u, v), 1 \le u \le v \le n$，满足存在一条从 $u$ 到 $v$ 的长度为 $k$ 的途径，和一条从 $v$ 到 $u$ 的长度为 $k$ 的途径。

$1 \le n \le 10^5$，$0 \le m \le 2 \times 10^5$，$n^3 \le k \le 10^{18}$。

### 题解

本文做法边带权也能做，因此不妨假设边带权。

容易发现只有在同一个强连通分量内的点对 $(u, v)$ 才可能满足条件，因此可以对每个强连通分量分别考虑。我们不妨假设原图强连通。

$k \ge n^3$ 的条件暗示 $k$ 足够大。在强连通图中，这意味着我们可以经过所有节点，并使用图上的每一个环对途径进行增广。记所有环长为 $len_1 \le len_2 \le \dots \le len_m$，不难发现我们增广的长度可以表示为 $len_1x_1 + len_2x_2 + \dots + len_m x_m, \,x_1, x_2, \dots, x_m \ge 0$。记 $d = \gcd_{i = 1}^m len_i$，根据裴蜀定理和同余最短路模型，可以证明对于 $s$ 满足 $d \mid s \land s \ge (len_1 - 1) \times len_m$，我们一定能够增广出长度 $s$。

于是不难想到我们需要求解 $d$。我声称，对于正整数 $p$，$p \mid d$ 的一个充分必要条件是能够找到一组 $\{dis_n\}$，使得原图的所有边 $(u, v, w)$ 有 $dis_v - dis_u \equiv w \,(\bmod \, p)$。

> 充分性：
>
> 对于原图某一个环，记组成它的所有边为 $(u_1, u_2, w_1), (u_2, u_3, w_2), \dots, (u_l, u_1, w_l)$，必有 $\sum_{i = 1}^l w_i \equiv \sum_{i = 1}^{l - 1} (dis_{u_{i + 1}} - dis_{u_i}) + dis_{u_1} - dis_{u_l} \equiv 0 \, (\bmod \, p)$。因此 $p$ 是所有环长的因数，即 $p \mid d$。
>
> 必要性：
>
> 考虑构造证明。由于原图强连通，我们可以找到一棵以 $rt$ 为根的外向生成树。令 $dis_{rt} = 0$，对于外向树上的每一条边 $(u, v, w)$，令 $dis_v = dis_u + w$。
>
> 该构造对于所有树边是合法的。
>
> 考虑一条非树边 $(u, v, w)$。
>
> 由于原图强连通，必然存在一条从 $v$ 到 $rt$ 的途径。该途径与外向树上 $rt$ 到 $v$ 的路径拼成了一条首尾相接的途径，可以分解成若干个环。因此该途径长度模 $p$ 同余 $-dis_v$。
> 
> 因此存在一条 $v$ 到 $u$ 的长度模 $p$ 同余 $dis_u - dis_v$ 的途径。该途径与非树边 $(u, v, w)$ 拼成了一条首尾相接的途径，同样可以分解为若干个环。因此 $w \equiv dis_v - dis_u \, (\bmod \, p)$。

基于上述结论以及必要性的证明过程，任取一棵外向生成树构造出 $\{dis_n\}$，这个构造在模 $p$ 意义下成立是 $p \mid d$ 的充分必要条件。因此对于所有边 $(u, v, w)$，$d$ 即为所有 $dis_v - dis_u - w$ 的 $\gcd$。

求出 $d$ 后，不难发现，$u, v$ 之间的所有途径长度一定在模 $d$ 意义下和 $dis_v - dis_u$ 同余。$u, v$ 之间最短的经过所有节点的途径长度不超过 $(n - 1)^2$，而 $(n - 1)^2 + (len_1 - 1) \times len_m \le (n - 1) \times (2n - 1) \le n^3 \le k$。所以判断点对 $(u, v)$ 是否满足题目条件即判断 $dis_v - dis_u$ 和 $dis_u - dis_v$ 是否在都模 $d$ 意义下同余 $k$。

容易发现要么 $k \equiv 0 \, (\bmod\,d)$，要么 $d$ 是偶数并且 $k \equiv \frac{d}{2} \, (\bmod \, d)$ 才能找到合法点对。如果 $k$ 满足上述两个条件之一，限制就只要求 $dis_v - dis_u \, \equiv k \, (\bmod \, d)$。原题没有边权，因此直接前缀和优化即可。

时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
template <typename T>
void chkmax(T &x, const T &y) {
  if (x < y) x = y;
}
template <typename T>
void chkmin(T &x, const T &y) {
  if (y < x) x = y;
}
constexpr int MAXN = 1e5 + 10;
int n, m, dfn[MAXN], low[MAXN], dfc, stk[MAXN], tp, dep[MAXN];
int cnt[MAXN];
bool ins[MAXN], vis[MAXN];
ll k, ans;
vector<int> g[MAXN];
void tarjan(int u) {
  dfn[u] = low[u] = ++dfc;
  stk[++tp] = u;
  ins[u] = true;
  for (auto v : g[u]) {
    if (!dfn[v]) {
      dep[v] = dep[u] + 1;
      tarjan(v);
      chkmin(low[u], low[v]);
    } else if (ins[v]) {
      chkmin(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    vector<int> buc;
    while (true) {
      int t = stk[tp--];
      ins[t] = false;
      buc.emplace_back(t);
      if (t == u) break;
    }
    for (auto i : buc) vis[i] = true;
    int d = 0;
    for (auto i : buc) {
      for (auto j : g[i])
        if (vis[j]) d = __gcd(d, dep[j] - dep[i] - 1);
    }
    d = abs(d);
    if (d) {
      int mxdep = 0;
      for (auto i : buc) {
        ++cnt[dep[i]];
        chkmax(mxdep, dep[i]);
      }
      if (k % d == 0) {
        for (int i = dep[u]; i <= mxdep; ++i) {
          ans += (ll)(cnt[i] + 1) * cnt[i] / 2;
          if (i - d >= dep[u]) {
            ans += (ll)cnt[i] * cnt[i - d];
            cnt[i] += cnt[i - d];
          }
        }
      } else if (!(d & 1) && k % d == d / 2) {
        for (int i = dep[u]; i <= mxdep; ++i) {
          if (i - d / 2 >= dep[u]) ans += (ll)cnt[i] * cnt[i - d / 2];
          if (i - d >= dep[u]) cnt[i] += cnt[i - d];
        }
      }
      fill(cnt + dep[u], cnt + mxdep + 1, 0);
    }
    for (auto i : buc) vis[i] = false;
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m >> k;
  while (m--) {
    int u, v;
    cin >> u >> v;
    g[u].emplace_back(v);
  }
  for (int i = 1; i <= n; ++i)
    if (!dfn[i]) tarjan(i);
  cout << ans << "\n";
  return 0;
}
```

---

## 作者：do_it_tomorrow (赞：12)

修了一下算 $\gcd$ 的坑。

因为需要分别存在 $x\to y$ 和 $y\to x$ 的路径，所以满足题目要求的 $(x,y)$ 肯定是在一个 SCC 中的。

对于每一个 SCC 分开考虑，最后将结果相加即可，下面讨论的图都是**强连通**的。

假设图中所有的环的长度为 $len_1,len_2,\cdots,len_m$，那么记 $d=\gcd\limits_{i=1}^m len_i$。

下面讨论的图都是在在对 $d$ **取模意义**下的。

在下的 SCC 中有一些性质：

如果存在一条路径 $a\to b$，而且边权为 $w$，那么就可以构造出 $b\to a$ 而且边权为 $-w$ 的路径。

> 证明：
> 
> 因为 $a,b$ 在同一个强连通分量内，所以它们必然在一个环中，假设这个环的边权和为 $s$。那么从 $b$ 出发绕着环走 $t$ 圈，这样的贡献就是 $s\times t$ 也就是 $0$。
> 
> 所以只要在最后一圈的时候直接停在 $a$ 那么就相当于构造出了一条 $b\to a$ 的边权为 $-w$ 的路径。

另外有一个性质，如果强连通分量上有一个环，那么所有的点都可以看作在这个环上。

> 证明：
>
> 假设 $a$ 在长度为 $x$ 的环上，而 $b$ 不在。
> 
> 假设 $a\to b$ 的路径长度为 $w$，那么根据上面的性质，显然 $b\to a$ 的长度就是 $w$。
>
> 那么就可以构造 $b\to a\to  b$ 的路径，在到达 $a$ 之后可以随意的在环上行走，而结束后又可以原路返回。容易理解，这样路径的长度为 $w+x+(-w)=x$。


换而言之：

$x\to y$ 的一条复杂路径可以表示为 $x\to y$ 的简单路径的长度加上 $\sum\limits_{i=1}^m a_i\times len_i$，其中 $\forall a_i\in \mathbb{N}$。

这样就解决有些 $a_i=0$ 但是却经过了一些其他必须要经过 $i$ 的环才能到达的环的问题。


最后还有一个性质，如果有一条 $x\to y$ 的路径长度为 $Len$，那么不管最初的简单路径怎么选择，其长度在模 $d$ 意义下都可以做到为 $Len$。

> 证明：
>
> 由第一个性质可以做出构造，先让长度为 $a$ 的路径走负边权的路原路返回再走一次长度为 $b$ 的路，这样结果就是 $a+(-a)+b=b$ 了。

考虑如何求解一个所有的环长的 $\gcd$。

对于一个 SCC 跑一个叶向生成树，显然环有两种情况：一条非树边和一些树边组成，多条树边和一些树边组成。

因为第二种情况，这些环的长度都可以通过第一种环通过加减得到，所以显然不会对 $\gcd$ 产生影响。

具体的 $\gcd(a,b)=\gcd(a,b,a+b)$，证明如下：

> 设 $\gcd(a,b)=g$，那么 $a=\dfrac{a}{g}\times g$，$b=\dfrac{b}{g}\times g$，所以就有 $a+b=g\times ({\dfrac{a}{g}+\dfrac{b}{g}})$。


于是就遍历这个 dfs 树，如果遇到了返祖边那么就更新 $\gcd$。

假设 $x\to y$ 存在一条非树边，那么计算方法为 $\lvert \text{dep}_{x}-\text{dep}_y+1\rvert$。

显然对于返祖边，这样是正确的，考虑证明对于横叉边的正确性。

> 假设有横叉边 $x\to y$，那么环的长度就应该为 $\text{dis}(rt,x)+\text{dis}(y,rt)+1$。
> 
> 通过上面的性质，因为 $\text{dis}(rt,y)\equiv -\text{dis}(y,rt)\pmod{d}$，所以得到 $\text{dis}(rt,x)+\text{dis}(y,rt)+1\equiv \text{dis}(rt,x)-\text{dis}(rt,y)+1\equiv\text{dep}_x-\text{dep}_y+1\pmod{d}$。

回到这个题目的具体要求，假设 $x\to y$ 的简单路径长度为 $Len$，那么题目的要求就是：

$$Len+\sum\limits_{i=1}^m a_i\times len_i\equiv k \pmod{d}$$

因为 $\forall i\in[1,m]\cap\mathbb{Z}$ 都满足 $d\mid len_i$，所以 $\sum\limits_{i=1}^m a_i\times len_i\equiv 0\bmod{d}$，也就得到了其实题目的要求是 $Len\equiv k$。

因为 $x\to y$ 的长度和 $y\to x$ 的长度需要一样，所以我们先考虑判断 $\text{dis}(x\to y)\equiv \text{dis}(y\to x)\pmod d$。

因为第三个性质，所以不妨我们直接让 $x$ 走到 $rt$ 然后再走到 $y$，反之同理。

因为 $x\to y$ 的边权为 $w$ 那么 $y\to x$ 的边权就为 $-w$，所以就相当于判断：

$$-\text{dis}(rt,x)+\text{dis}(rt,y)\equiv \text{dis}(rt,x)-\text{dis}(rt,y)\pmod d$$

因为 $x$ 和 $y$ 到 $rt$ 的距离就相当于 $\text{dep}$，所以就可以得到：

$$2\times(\text{dep}(x)-\text{dep}(y))\equiv 0\pmod{d}$$

通过瞪眼法可以得到方程的解为 $\text{dep}(x)=\text{dep}(y)$，或者 $2\mid d$ 且 $\text{dep}(x)-\text{dep}(y)\mid \dfrac{d}{2}$。

当然，在最后计算答案的时候需要满足 $\text{dep}(x)\equiv k\pmod d$。

时间复杂度 $O(n)$，做完了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m,dfncnt,Cnt,top,d,k,ans;
int dfn[N],low[N],st[N],scc[N],dep[N],cnt[N];
bitset<N> vis;
vector<int> v[N],g[N];
void tarjan(int x){
    low[x]=dfn[x]=++dfncnt;
    st[++top]=x,vis[x]=1;
    for(int i:v[x]){
        if(!dfn[i]) tarjan(i),low[x]=min(low[x],low[i]);
        else if(vis[i]) low[x]=min(low[x],dfn[i]);
    }
    if(dfn[x]==low[x]){
        Cnt++;
        do{scc[st[top]]=Cnt,vis[st[top]]=0;}while(st[top--]!=x);
    }
}
template<typename _Tp = int>
_Tp gcd(_Tp a,_Tp b){if(!b) return a;return gcd(b,a%b);}
void dfs(int x,int fa){
    dep[x]=dep[fa]+1,vis[x]=1;
    for(int i:g[x]){
        if(!vis[i]) dfs(i,x);
        else d=gcd(d,dep[x]-dep[i]+1);
    }
}
void solve(int x,int p){
    for(int i:v[p]) cnt[dep[i]%d]++;
    if(k%d==0){
        int s=0;
        for(int i:v[p]) s+=cnt[dep[i]%d]-1;
        ans+=v[p].size()+s/2;
    }
    else if(d%2==0&&k%d==d/2){
        int s=0;
        for(int i:v[p]) s+=cnt[(dep[i]+k)%d];
        ans+=s/2;
    }
    for(int i:v[p]) cnt[dep[i]%d]--;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m>>k;
    for(int i=1,x,y;i<=m;i++) cin>>x>>y,v[x].push_back(y);
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    vis.reset();
    for(int i=1;i<=n;i++) for(int x:v[i]) if(scc[x]==scc[i]) g[i].push_back(x);
    for(int i=1;i<=n;i++) v[i].clear();
    for(int i=1;i<=n;i++) v[scc[i]].push_back(i);
    for(int i=1;i<=n;i++,d=0)if(!vis[i]){
        dfs(i,i),d=max(d,-d);
        if(d) solve(i,scc[i]);
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：睿智的憨憨 (赞：3)

首先，$x,y$ 可以互相到达，因此至少它们在一个 SCC 中。

在 SCC 中，一条 $x \rightarrow y$ 的复杂路径可以看成是一条 $x \rightarrow y$ 的简单路径接受了若干环的增广。由于 $k \ge n^3$，因此可以使用任意一个环任意次来增广路径。具体来说，路径长度 $L=simple + \sum a_i \times len_i$，$len_i$ 为 SCC 中的环长，$a_i$ 可以是任意非负整数。

先不考虑简单路径的选取。如何判断一个极大的 $k'=\sum a_i \times len_i$ 是否能作为增广总长度？根据斐蜀定理，设 $g=\gcd(len_1,len_2,\dots,len_s)$，则满足 $g | k'$ 以后，由于 $k'$ 极大，总可以凑出 $k'$，通过数论相关知识可以证明。

接着，如何求一个 SCC 中所有环长的 $\gcd$ 呢？任意选取一个点生成以它为根的生成树，对于每条边，将经过它的环的限制加予 $g$，得到 $g$ 的值。以下同余式均为模 $g$ 意义，具体过程如下：

设 $dis_{x,rt}$ 为任意一条 $x \rightarrow rt$ 的路径的长度，$dep_x$ 为 $x$ 的深度（也可以理解为 $dis_{rt,x}$）。对于一条返祖边 $x \rightarrow y$，有 $dep_x-dep_y+1 \equiv 0$，对于一条横插边 $x \rightarrow y$，有 $dep_x+1+dis_{y,rt} \equiv dep_x+1-dis_{rt,y} \equiv dep_x - dep_y + 1\equiv 0$。可以总结为对于一条非树边 $x \rightarrow y$，$g$ 需要和 $|dep_x-dep_y+1|$ 取 $\gcd$。

得到 $g$ 以后，回顾简单路径的选取，问题似乎已经迎刃而解了。如果有两条起点终点相同，长度分别为 $A,B$ 的简单路径，则 $A \equiv B$，可以通过环的增广来实现微调，因此选哪条简单路径都是一样的，那就干脆选树上路径 $dis_{x,rt}+dis_{rt,y} \equiv dep_y-dep_x$。

于是 $(x,y)$ 合法就必须 $dep_x - dep_y \equiv dep_y-dep_x$，也就是要么 $dep_x \equiv dep_y$，要么 $2 | g$ 且 $dep_x-dep_y \equiv \frac{g}{2}$，用 $cnt_i$ 存余数为 $i$ 的数量即可。

时间复杂度 $O(n)$。

写代码时注意一个孤立点也可以是 SCC，要特判 $g=0$。

[代码](https://codeforces.com/contest/1835/submission/258200337)。

---

## 作者：Leasier (赞：1)

显然 $x, y$ 必须在一个 SCC 内，则我们 SCC 缩点后分开处理，将答案求和即可。

由于 $k \geq n^3$，我们实际上相当于可以在 SCC 内随便绕环。

设 $d$ 为当前 SCC 内所有环长的 $\gcd$，则此时合法的 $x, y$ 需要满足 $depth_x - depth_y \equiv depth_y - depth_x \equiv k \pmod d$，可以发现此时 $k$ 需要满足 $k \bmod d = 0$ 或 $d$ 为偶数且 $k \bmod d = \frac{d}{2}$。

接下来考虑求出 $d$。考虑抓出当前 SCC 的任意一棵生成树，取任意点为根，设有非树边 $u \to v$，则 $d \mid (depth_v - depth_u - 1)$。

可以证明这些东西 $\gcd$ 起来的结果一定为 $d$，此处略去。

进而我们需要求出满足前面条件的 $x, y$ 对数，开个桶统计一下即可。时间复杂度为 $O(n + m)$。

注意特判一个点的 SCC 的情况，此时 $d = 0$ 且不会产生贡献。

代码：
```cpp
#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>

using namespace std;

typedef long long ll;

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt = 0, d;
int head[100007], dfn[100007], low[100007], belong[100007], fa[100007], depth[100007], bucket[100007];
bool vis1[100007], vis2[100007], vis3[100007];
Edge edge[400007];
stack<int> s;
vector<int> v[100007];

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void tarjan(int u, int &id, int &scc_cnt){
	dfn[u] = low[u] = ++id;
	vis1[u] = vis2[u] = true;
	s.push(u);
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (!vis1[x]){
			tarjan(x, id, scc_cnt);
			low[u] = min(low[u], low[x]);
		} else if (vis2[x]){
			low[u] = min(low[u], dfn[x]);
		}
	}
	if (dfn[u] == low[u]){
		int cur;
		scc_cnt++;
		do {
			cur = s.top();
			s.pop();
			vis2[cur] = false;
			belong[cur] = scc_cnt;
			v[scc_cnt].push_back(cur);
		} while (cur != u);
	}
}

int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}

void dfs(int u, int father, int cur){
	vis3[u] = true;
	fa[u] = father;
	depth[u] = depth[father] + 1;
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (belong[x] == cur){
			if (!vis3[x]){
				dfs(x, u, cur);
			} else {
				d = gcd(d, abs(depth[x] - depth[u] - 1));
			}
		}
	}
}

int main(){
	int n, m, id = 0, scc_cnt = 0;
	ll k, ans = 0;
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++){
		int x, y;
		cin >> x >> y;
		add_edge(x, y);
	}
	for (int i = 1; i <= n; i++){
		if (!vis1[i]) tarjan(i, id, scc_cnt);
	}
	for (int i = 1; i <= scc_cnt; i++){
		int size = v[i].size(), max_depth = 0;
		d = 0;
		dfs(v[i][0], 0, i);
		for (int j = 0; j < size; j++){
			bucket[depth[v[i][j]]]++;
			max_depth = max(max_depth, depth[v[i][j]]);
		}
		if (d != 0){
			if (k % d == 0){
				for (int j = 1; j <= max_depth; j++){
					ans += (ll)bucket[j] * (bucket[j] + 1) / 2;
					if (j > d){
						ans += (ll)bucket[j] * bucket[j - d];
						bucket[j] += bucket[j - d];
					}
				}
			} else if (d % 2 == 0 && k % d == d / 2){
				for (int j = d / 2 + 1; j <= max_depth; j++){
					ans += (ll)bucket[j] * bucket[j - d / 2];
					if (j > d) bucket[j] += bucket[j - d];
				}
			}
		}
		for (int j = 1; j <= max_depth; j++){
			bucket[j] = 0;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：UKE_Automation (赞：0)

### CF1835D Doctor's Brown Hypothesis

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1835D)

首先由于 $x,y$ 可以互相到达，所以他们在同一个强连通分量中。所以我们可以对每个 SCC 单独求解。

现在考虑一个 SCC，此时从 $x\to y$ 的路径应该可以写成 $x\to y$ 的一条简单路径和若干个环的长度总和。令所有环分别长为 $l_1,l_2,\cdots$，那么最后的路径长度应该就是 $len+\sum a_il_i(a_i\ge 0)$。先看后面这个部分，根据裴蜀定理可以知道，他可以拼凑出所有长度是 $d=\gcd(l_i)$ 的倍数的路径；并且由于 $k\ge n^3$ 非常大，所以我们是可以随便在 SCC 中绕环的，因此不必考虑无法走出的情况。

求解环长 $\gcd$ 是一个比较经典的问题，具体可以看[这道题](https://codeforces.com/contest/1515/problem/G)。简单来说，我们以任意一个点为根跑一个生成树，对于任意一个非树边 $(u,v)$，我们和 $|dep_u-dep_v+1|$ 取 $\gcd$ 即可得出正确答案。

然后回到原来的部分，由于我们最终要求 $len+\sum a_il_i=k$，而我们又知道 $\sum a_il_i$ 是 $d$ 的倍数，所以实际上我们要求的就是 $len\equiv k\pmod d$。另一方面，我们对于 $x\to y$ 和 $y\to x$ 都有这个性质，所以这两条简单路径也同余于 $d$。

而实际上，这两条路径模 $d$ 的结果可以直接写成 $dep_y-dep_x$ 以及 $dep_x-dep_y$，因为别的路径一定可以用这两个式子加减一些环构成，而环长一定是 $d$ 的倍数。那么此时就有 $dep_y-dep_x\equiv dep_x-dep_y\pmod d$，也就是 $2(dep_x-dep_y)\equiv 0\pmod d$。此时要么 $dep_x=dep_y$，要么 $dep_x-dep_y =\frac{d}{2}$。用一个桶统计一下贡献即可。复杂度 $O(n+m)$。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

typedef long long ll;
const int Maxn = 2e5 + 5;
const int Inf = 2e9;
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int n, m;
ll k;
int head[Maxn], edgenum;
struct node {
	int nxt, to;
}edge[Maxn << 1];

void add(int u, int v) {
	edge[++edgenum] = {head[u], v}; head[u] = edgenum;
}

int dfn[Maxn], low[Maxn], idx, bel[Maxn], stk[Maxn], top, ins[Maxn], scc;
vector <int> V[Maxn];
void tarjan(int x) {
	dfn[x] = low[x] = ++idx;
	stk[++top] = x, ins[x] = 1;
	for(int i = head[x]; i; i = edge[i].nxt) {
		int to = edge[i].to;
		if(!dfn[to]) {
			tarjan(to);
			low[x] = min(low[x], low[to]);
		}
		else if(ins[to])
			low[x] = min(low[x], dfn[to]);
	}
	if(dfn[x] == low[x]) {
		scc++;
		while(1) {
			int v = stk[top--]; ins[v] = 0;
			bel[v] = scc; V[scc].push_back(v);
			if(v == x) break;
		}
	}
}

int vis[Maxn], cnt[Maxn], dep[Maxn], d;
void dfs1(int x, int fth) {
	vis[x] = 1; dep[x] = dep[fth] + 1;
	for(int i = head[x]; i; i = edge[i].nxt) {
		int to = edge[i].to;
		if(bel[to] != bel[x]) continue;
		if(vis[to]) {
			d = __gcd(d, abs(dep[x] - dep[to] + 1));
			continue;
		}
		dfs1(to, x);
	} 
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	read(n), read(m), read(k);
	for(int i = 1, u, v; i <= m; i++) {
		read(u), read(v);
		add(u, v);
	}
	for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i);
	ll ans = 0;
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			d = 0; dfs1(i, 0);
			if(!d) continue;
			for(auto x : V[bel[i]]) cnt[dep[x] % d]++;
			if(k % d == 0) {
				ll sum = 0;
				for(auto x : V[bel[i]]) sum += cnt[dep[x] % d] - 1;
				ans += sum / 2 + V[bel[i]].size();
			}
			else if(d % 2 == 0 && k % d == d / 2) {
				ll sum = 0;
				for(auto x : V[bel[i]]) sum += cnt[(dep[x] + k) % d];
				ans += sum / 2; 
			}
			for(auto x : V[bel[i]]) cnt[dep[x] % d]--;
		}
	}
	write(ans);
    Usd();
	return 0;
}

```

---

## 作者：lfxxx (赞：0)

我做法好像有点劣啊。

首先每个 SCC 的问题是独立的，我们下文只考虑一个 SCC。

为什么 $k \geq n^3$，这提示我们存在很充裕的调整空间，首先可以想到假若存在一个长度为 $a$ 与长度为 $b$ 的环，只要不要太长，就基本可以凑出 $\gcd(a,b)$ 倍数的路径。

于是我们猜测答案和所有环长度 $\gcd$ 有关，不妨设其为 $w$，我们发现由于这是一个 SCC，所以对于 $x \to y$ 的所有路径，其加上某条 $y \to x$ 的路径后长度一定是 $w$ 的倍数，故 $x \to y$ 所有路径的长度都模 $w$ 同余，且最短路径不会超过 $n$，只要 $k$ 模 $w$ 和最短路径模 $w$ 同余，根据裴蜀定理，我们总是可以通过往最短路径上挂若干个环并通过不断走这些环将路径长度调整为 $k$。

那怎么确定两个点之间路径长度模 $w$ 的余数呢，不难想到有向图染色，染色后可以直接用颜色编号相对差求解。然后统计合法点对数就是简单的了。

最后一个问题，怎么求解 $w$？受到染色的启发，我们不难发想假若 $d$ 是 $w$ 的因数，那么 SCC 一定存在合法 $d$ 染色，而 $w$ 一定是 SCC 中任意一个环的环长的因数，故先随便找一个环，枚举环长因数再染色 check 即可做到 $O(n \sqrt n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5+114;
vector<int> E[maxn];
int dfn[maxn],low[maxn];
int dfncnt,vis[maxn];
int stk[maxn],tp;
vector<int> col[maxn];
int cl;
int coci[maxn];
void tarjan(int u){
    vis[u]=1;
    stk[++tp]=u;
    dfn[u]=low[u]=++dfncnt;
    for(int v:E[u]){
        if(dfn[v]==0){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(vis[v]==1) low[u]=min(low[u],dfn[v]);
    }
    if(low[u]>=dfn[u]){
        cl++;
        while(stk[tp]!=u){
            col[cl].push_back(stk[tp]);
            coci[stk[tp]]=cl;
            vis[stk[tp]]=0;
            tp--;
        }
        col[cl].push_back(u);
        coci[u]=cl;
        vis[u]=0;
        tp--;
    }
}
vector<int> G[maxn];//临时边集
int huan;
int use[maxn];
int dep[maxn];
int kfa[maxn];
void dfs(int u){
    use[u]=1;
    kfa[u]=1;
    for(int v:G[u]){
        if(kfa[v]==1){
            huan=dep[u]-dep[v]+1;
        }else if(use[v]==0) dep[v]=dep[u]+1,dfs(v);
    }
    kfa[u]=0;
}
int n,m,k;
int color[maxn];
int len;
int cnt[maxn];
bool flag;
void solve(int u){
    use[u]=1;
    for(int v:G[u]){
        if(use[v]==0){
            color[v]=(color[u]+1)%len;
            solve(v);
        }else if(color[v]!=(color[u]+1)%len) flag=false;
    }
}
int ans;
vector<int> d[maxn];
void work(int id){
    if(col[id].size()==1) return ; 
    for(int x:col[id]){
        for(int y:E[x]){
            if(coci[y]==id) G[x].push_back(y);
        }
    }
    huan=0;
    dep[col[id][0]]=1;
    dfs(col[id][0]);
    for(int u:col[id]) dep[u]=0;
    for(int u:col[id]) use[u]=0;
    int mx=1;
    for(int x:d[huan]){
        len=x;
        flag=true;
        solve(col[id][0]);
        if(flag==true) mx=len;
        for(int u:col[id]) color[u]=use[u]=0;
    }
    len=mx;
    solve(col[id][0]);
    for(int u:col[id]) cnt[color[u]]++;
    int K=k%len;
    if(K==0){
        for(int i=0;i<len;i++) ans+=cnt[i]*(cnt[i]-1)/2+cnt[i];
    }else if(K*2==len){
        for(int i=0;i<K;i++){
            ans+=cnt[i]*cnt[i+K];
        }
    }
    for(int u:col[id]) color[u]=use[u]=0,G[u].clear();
    for(int i=0;i<len;i++) cnt[i]=0; 
    return ;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;i*j<=n;j++) d[i*j].push_back(i);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        if(dfn[i]==0) tarjan(i);
    }
    for(int i=1;i<=cl;i++) work(i);
    cout<<ans<<'\n';
    return 0;   
}
```

---

