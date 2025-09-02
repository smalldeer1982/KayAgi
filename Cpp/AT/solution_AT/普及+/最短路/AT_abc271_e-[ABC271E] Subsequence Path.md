# [ABC271E] Subsequence Path

## 题目描述

某地区有 $N$ 个城镇，编号为 1 到 $N$ ，并且由 $M$ 条公路连接，编号 1 到 $M$ 。

每条公路都是有向的；而且编号为 $i(1 \le i \le M)$ 的道路将带领你从编号 $A_i$ 的城镇到编号为 $B_i$ 的城镇去,它的长度为 $C_i$。

现在给你一个长度为 $K$ 的正整数序列 $E=(E_1,E_2,...,E_K)$ 且 $\forall i \in [1,K],E_i \in [1,M]$ 。我们说一条由一些连通的公路组成的路径为“**好路**”，当且仅当满足以下条件：

+ 这条路径的起点为 1 ，终点为 $N$ 。
+ 按经过顺序组成这条路径的公路的编号组成的序列是 $E$ 的子序列。

**注意**，若序列 $S$ 是长度为 $L$ 的数列 $T$ 的**子序列**，则 $S$ 是数列 $T$ 删除任意 $i\ (i\in [0,L])$ 个元素得到的。

现在你要找到最短的“**好路**”。如果没有，输出 ```-1``` 。

## 说明/提示

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M,\ K\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N,\ A_i\ \neq\ B_i\ \,\ (1\ \leq\ i\ \leq\ M) $
- $ 1\ \leq\ C_i\ \leq\ 10^9\ \,\ (1\ \leq\ i\ \leq\ M) $
- $ 1\ \leq\ E_i\ \leq\ M\ \,\ (1\ \leq\ i\ \leq\ K) $
+ 所有输入都是整数

#### 样例解释

对于**样例1**，有两条好路：

+ 选择编号为 $4$ 的公路。在这种情况下，“**好路**”的长度是 $5$ 。
+ 依次选择编号为 $1$ 和 $2$ 的公路。在这种情况下，“**好路**”的长度就变为了 $2+2=4$ 。

因此，输出的期望值为 $4$ 。

对于**样例2**，没有“**好路**”，输出 ``` -1 ``` 。

## 样例 #1

### 输入

```
3 4 4
1 2 2
2 3 2
1 3 3
1 3 5
4 2 1 2```

### 输出

```
4```

## 样例 #2

### 输入

```
3 2 3
1 2 1
2 3 1
2 1 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 4 5
3 2 2
1 3 5
2 4 7
3 4 10
2 4 1 4 3```

### 输出

```
14```

# 题解

## 作者：2020luke (赞：6)

# [[ABC271E] Subsequence Path](https://www.luogu.com.cn/problem/AT_abc271_e) 题解

## 思路解析

很好的一道题，很有迷惑性，表面上是一道图论实际上是 dp，定义 $f_{i}$ 为从 $1$ 到  $i$ 的最短 “好路”。先把每条边对应的起点，终点和边权记录下来，然后输入每个 $e$，由于是子序列顺序不会改变，因此可以顺序进行操作。对于每一个 $e$，都有选和不选两种情况，若选，则相当于最短路算法中的松弛操作，转移 $f_{a_{e}}\gets\min(f_{a_{e}},f_{b_{e}}+c_{e})$（$a_{i},b_{i},c_{i}$ 分别代表第 $i$ 条边的起点，终点和边权）。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5 + 10;
ll n, m, k;
ll a[N], b[N], c[N];
ll e;
ll f[N];
int main() {
	cin >> n >> m >> k;
	for(int i = 1; i <= m; i++) {
		cin >> a[i] >> b[i] >> c[i];
	}
	memset(f, 0x3f, sizeof(f));
	f[1] = 0;
	for(int i = 1; i <= k; i++) {
		cin >> e;
		f[b[e]] = min(f[b[e]], f[a[e]] + c[e]);
	}
	if(f[n] < 1e18) {
		cout << f[n];
	}
	else {
		cout << -1;
	}
	return 0;
}
```

---

## 作者：_GW_ (赞：2)

## 思路
看到题目的第一眼是一脸懵逼的。

实际上，我们直接从 $E$ 序列本身出发求最短距离即可。

我们用 $f_i$ 表示从点 $1$ 到点 $i$ 的最短距离。

首先，先把 $f$ 数组初始化成极大值。

然后，用一个自定义结构存图。

最后，输入 $E$ 数列的同时用计算一下从旁边的点出发是否更近即可。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=114514*3;
int u,f[N],val;
int n,m,k;
struct node
{
    int x,y,z;
}a[N];
signed main()
{
    cin>>n>>m>>k;
    for(int i=2;i<=n;i++) f[i]=0x3f3f3f3f3f3f3f3f;
    for(int i=1;i<=m;i++)
    {
        cin>>a[i].x>>a[i].y>>a[i].z;
    }
    for(int i=1;i<=k;i++)
    {
        cin>>u;
        f[a[u].y]=min(f[a[u].y],f[a[u].x]+a[u].z);
    }
    if(f[n]==4557430888798830399) cout<<-1<<endl;
    else cout<<f[n]<<endl;
    return 0;
} 
```

## 练习
[P1552](https://www.luogu.com.cn/problem/P1522)


---

## 作者：littlebug (赞：1)

## Solution

因为 $e_i$ 可能重复，所以不能跑最短路。

但是这是教练放在 dp 入门题单里的题，所以考虑 dp。

然后就简单了。设 $f_i$ 为 $1 \leadsto i$ 的合法最短路，于是在顺序遍历 $e_i$ 的过程中，有转移 $f_{v_{e_i}} = \min(f_{v_{e_i}},f_{u_{e_i}}+w_{e_i})$。

## Code

代码中的 $a_i$ 指题面中的 $e_i$。

```cpp
int n,m,k,a[MAXN],f[MAXN];
struct edge{int u,v,w;} e[MAXN];

signed main()
{
	read(n,m,k); rep(i,1,m) read(e[i].u,e[i].v,e[i].w); _::r(a,k);
	
	memset(f,0x3f,sizeof(f));
	f[1]=0;
	rep(i,1,k) f[e[a[i]].v]=min(f[e[a[i]].v],f[e[a[i]].u]+e[a[i]].w);
	write(f[n]==inf ? -1ll : f[n]);
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：__HHX__ (赞：1)

# 思路
可以使用01背包的思想。

因为序列可以转换成每个边**选或不选**，选择顺序强制遵照**序列的顺序**

所以我们很容易知道拓扑序为：$1$ 到 $n$，这里枚举的是序列 $E$ 的编号。

状态便是：$(x, len)$，$x$ 为当前位置，$len$ 为已行走长度。

我们来考虑两种转移：

若选：$(A_i, len)\rightarrow(B_i, len + C_i)$。

若不选：不变即可。

代码如下：
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e5 + 3;

long long dp[N], a[N], b[N], c[N], e[N];

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 1; i <= m; i++) {
    cin >> a[i] >> b[i] >> c[i];
  }
  for (int i = 1; i <= k; i++) {
    cin >> e[i];
  }
  for (int i = 1; i <= n; i++) {
    dp[i] = 1ll * 2e14 + 3;
  }
  dp[1] = 0;
  for (int i = 1; i <= k; i++) {
    dp[b[e[i]]] = min(dp[b[e[i]]], dp[a[e[i]]] + c[e[i]]);
  }
  cout << (dp[n] == 1ll * 2e14 + 3 ? -1 : dp[n]);
  return 0;
}

```

---

## 作者：CQ_Bab (赞：1)

# 前言
第一眼看到这道题的时候以为是个图论，可是发现老师放在 Dp 题单中的，便立即转变思路，然后一下就出来了。
# 思路
我们可以定义 $f_i$ 为从 $1$ 号点走到 $i$ 号点是否可以，那么我们的转移只需要将互相能到达的两个点的路径相互转移一下即可，这里的转移方程为 $f_i=f_j+z$ 这里的 $j$ 为 $i$ 能到达的点，$z$ 为边权。
# 代码
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
il int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=(res*a);
		a=a*a;
		b>>=1;
	}
	return res;
}
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
const int N=2e5+10;
struct node{
	int x,y,z;
}edg[N];
int n,m,k,dis[N];
fire main() {
	cin>>n>>m>>k;
	rep(i,1,m) {
		int a,b,c;
		cin>>a>>b>>c;
		edg[i]={a,b,c};
	}
	rep(i,2,n) dis[i]=0x3f3f3f3f3f3f3f3f;
	rep(i,1,k) {
		int u;
		cin>>u;
		dis[edg[u].y]=min(dis[edg[u].y],dis[edg[u].x]+edg[u].z);
	}
	if(dis[n]>=0x3f3f3f3f3f3f3f3f) puts("-1");
	else cout<<dis[n]<<endl;
	return false;
}

```

---

## 作者：Expert_Dream (赞：1)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

可以用 DP 来解决。$dp_{i,j}$ 代表着第 $i$ 条边，点 $1$ 到 $j$ 最短距离。考虑转移方式：如果需要这个边 $(u,v,w)$ 那么，$dp_{i,j} = dp_{i-1,u} + w$。不需要这个边：$dp_{i,j}=dp_{i-1,j}$。$j$ 其实就是 $v_i$。

空间的限制，所以我们没法开二维数组来存储。发现 $i$ 从 $i-1$ 转移来，所以说，我们可以压维。因此就得到了正解。

[link](https://atcoder.jp/contests/abc271/submissions/49003802)。

---

## 作者：wusixuan (赞：0)

# 思路

我们发现这样的问题是没法用最短路跑的，因为这样还要记录在 $E$ 中那些位置出现了，以及路径边集与 $E$ 已经匹配到了哪个位置，比较麻烦，所以我们这道题不采用最短路的方法。

那么我们该怎么做呢？DP！

我们回归某些最短路算法的本质，虽然可以不采用最短路算法，但是我们可以借鉴它的思想。因为绝大多数的最短路算法，本质上都是 dp 发展过来的。

因为要按顺序的匹配，所以我们考虑按顺序的转移。我们思考 Bellman_Ford 算法的本质，发现它就是枚举已经走的步数，对于每条边执行松弛操作，也就是枚举每条边，然后看边的起点能否更新终点的最短路长度值。

于是我们考虑仿照这种做法，对于每条在 $E$ 中的边执行松弛操作，于是这道题就被做完了，可以感性理解一下，这种方法一定是正确的。

梳理一下，我们用 $dp[i]$ 表示从 $1$ 走到 $i$ 的满足要求的最短路径，则可以得出转移方程：对于 $E$ 中的每条边 $e$，$dp[e_v]=\min(dp[e_v],dp[e_u]+e_w)$，其中 $e_u$ 表示 $e$ 的起点，$e_v$ 表示终点，$e_w$ 表示边权。

实现及其简单，代码就不放了。

---

## 作者：Empty_Dream (赞：0)

## 题意

给你 $n$ 个点，$m$ 条路从 $a_i$ 到 $b_i$ 长度为 $c_i$，一段长为 $k$ 的序列 $e$。求从 $1$ 号点到 $n$ 号点最短的**好路**长度。

对于**好路**，如果经过的边序号（输入时的顺序）是 $e$ 的子序列，那么称作一条好路。

## 分析

看起来是一道图论，但是发现题目说**子序列**，可以想到用 dp 去求。

**状态表示**：子序列我们可以选或不选，对应到上面的边就是加不加这条边的权值。这样一来我们就不需要去记录边而是记录到这一点权值的最小值。综上，$dp_i$ 表示到第 $i$ 个点好路的权值最小值。

**状态计算**：根据状态表示的思想，子序列上 dp 我们不需要考虑前面选了哪几条边，我们只关心这个点经过这次操作后权值的最小，所以得到方程 $dp_{b_i}=\min(dp_{b_i},dp_{a_i}+c_i)$。

**basecase**：显然一号点最小权值为 $0$，$dp_1=0$。

**ans**：最终只要判断 $dp_n$ 是否能到达（是否为极大值），能则输出 $dp_n$，否则输出 $-1$。

不开 `long long` 见祖宗？

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m, k;
int a[200005], b[200005], c[200005], e[200005], dp[200005];

signed main(){
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) cin >> a[i] >> b[i] >> c[i];
	for (int i = 1; i <= k; i++) cin >> e[i];
	memset(dp, 0x3f, sizeof(dp));
	dp[1] = 0;
	for (int i = 1; i <= k; i++){
		dp[b[e[i]]] = min(dp[b[e[i]]], dp[a[e[i]]] + c[e[i]]);
	}
	if (dp[n] == 0x3f3f3f3f3f3f3f3f) cout << "-1";
	else cout << dp[n];
	return 0;
}
```

---

## 作者：haokee (赞：0)

## 题目大意

有 $N$ 个点 $M$ 条边，每一条边都是双向边，第 $i$ 条道路连接着 $A_i$ 和 $B_i$，长度为 $C_i$。现在有一个长度为 $K$ 的序列，第 $i$ 个数为 $E_i$ $(1\le E_i\le M)$。接下来你需要在这个序列当中选择若干个数，使得这些数对应的边连接起一条 $1$ 到 $N$ 的路径，问你这一条路径的最小长度。如果没有，输出 $-1$。

## 思路

看到在 $K$ 个数当中选择若干个数，我们果断选择 dp。我们设 $dp_{(i,j)}$ 表示为选择了前 $i$ 个数对应的边，$1$ 到 $j$ 的最小距离。那么对于第 $i$ 条边，我们可以选择选与不选，因为对后面的决策毫无影响，在其中取最小值就行了：
$$
dp_{(i,B_{(E_i)})}=\min(dp_{(i-1,B_{(E_i)})},dp_{(i-1,a_{(A_i)})}+C_{(E_{i})})
$$
接着，我们发现了 $dp$ 数组内存占用过大，而且每一次转移时，首先就需要将上一层的状态全部拷贝下来，而根本就没有用到本层状态，因此我们可以压数组，把 $i$ 这个维度给压掉，这样子就可以愉快地通过此题了。时间复杂度：$\mathcal O(\max(M,K))$，空间复杂度 $\mathcal O(N)$。

## 代码

```cpp
#include <iostream>

using namespace std;
using ll = long long;      // 10^9 累加会爆 int

const ll kMaxN = 2e5 + 5;  // 最大边数和点数

ll a[kMaxN], b[kMaxN], c[kMaxN], e[kMaxN], dp[kMaxN], n, m, k;

int main() {
  cin >> n >> m >> k;
  for (ll i = 1; i <= m; i++) {
    cin >> a[i] >> b[i] >> c[i];
  }
  for (ll i = 1; i <= k; i++) {
    cin >> e[i];
  }
  fill(dp + 2, dp + n + 1, 1e18);                           // 初始化 dp 数组，注意不初始化 dp[1]，dp[1] 仍为 0
  for (ll i = 1; i <= k; i++) {                             // 枚举第 i 个数
    dp[b[e[i]]] = min(dp[b[e[i]]], dp[a[e[i]]] + c[e[i]]);  // 不选和选取最小值
  }
  cout << (dp[n] == 1e18 ? -1 : dp[n]) << '\n';  // 判断是否能够到达并输出
  return 0;
}
```





---

## 作者：Zhao_daodao (赞：0)

# problem
给你一个有向图，一共 $n$ 个点，$m$ 条边。

其中有一个由边构成的序列 $E=(E_1,E_2,\dots,E_k)$。

一个路径是好的，当且仅当：
1. 起点是 $1$，终点是 $n$。
1. **按经过顺序**组成这条路径的边的编号所组成的序列是 $E$ 的子序列。

输出最短的好的路径的长度。

如果没有好的路径，输出 `-1`。
# solution
**如果没有长度及顺序的限制：**

直接用并查集维护即可。

**如果没有长度的限制：**

对于每一个点，记录 $vis$ 数组。

只有点 $1$ 的值是 $1$，其余的初始值是 $0$。

按边在 $E$ 中的顺序，依次枚举每一条边，对于第 $i$ 条边：

如果 $vis[A_i]=1$，将 $vis[B_i]$ 也赋值为 $1$。

最后判断 $vis[n]$ 即可。

正确性证明：

如果 $A_i$ 的 $vis$ 值是 $1$，$1$ 到 $A_i$ 的序列必然是 $E$ 的子序列。

将这个子序列设为 $P$。

此时 $A_i$ 到 $B_i$ 的边 $E_i$ 是 $E$ 中的一条边，而且因为枚举顺序，此时 $E_i$ 比 $P$ 的最后一条边还要大，所以此时构成的边序列 $P'\in E$。

**如果有长度的限制：**

只需要一个 $dep$ 数组，记录 $1$ 到 $i$ 的最短长度。

$dep_1=0$，其余都是 $\infty$。

对于每一条 $E$ 中的边，进行松弛操作：

$dep[B_i]=\min(dep[A_i]+\langle A_i,B_i \rangle)$，

其中 $\langle A_i,B_i \rangle$ 表示这一条边的权值。

因为上面的证明，所以这样做的正确性有保障。

# code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5;
const int inf=1e18;
int n,m,k;
struct node{
    int u,v,w;
}a[MAXN];
int dis[MAXN];
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)
        cin>>a[i].u>>a[i].v>>a[i].w;
    for(int i=1;i<=n;i++)dis[i]=inf;
    dis[1]=0;
    for(int i=1;i<=k;i++){
        int t;cin>>t;
        int u=a[t].u,v=a[t].v,w=a[t].w;
        dis[v]=min(dis[v],dis[u]+w);
    }
    if(dis[n]==inf)cout<<"-1";
    else cout<<dis[n]<<"\n";
}
```

---

## 作者：wnsyou (赞：0)

# [Subsequence Path](https://www.luogu.com.cn/problem/AT_abc271_e)

[前排兜售我的博客园。](https://www.cnblogs.com/lw0-blog/p/17420295.html)

## 题意
有 $n$ 个城市和 $m$ 条有向道路，编号从 $1$ 开始，第 $i$ 条道路从 $a_i$ 到 $b_i$，长度为 $c_i$。

给定一个长度为 $k$ 的序列 $e$，我们定义从 $1$ 到 $n$ 的一条路径是优秀的当且仅当：

- 经过的边的编号按顺序构成 $e$ 的一个子序列。

求从 $1$ 到 $n$ 的优秀路径长度最小值，如果不存在，输出 `-1`。
## 思路
看起来是一道图论题，但实际上是**动态规划！**

因为题目要求是 $e$ 序列的一个子序列，那就可以变成一个类子序列 `dp`。

- 状态：$dp_i$ 表示走到城市 $i$ 的最短距离。
- 转移：对于 $1 \leqslant i \leqslant k$，$dp_{b_{e_i}} = \min({dp_{a_{e_i}} + c_{e_i}, dp_{b_{e_i}}})$。
- 初始状态：$dp_1=0$。
- 目标状态：$dp_n$。

**不开 `long long` 见祖宗！**
### 复杂度
- 时间：$O(n + m + k)$。
- 空间：$O(n + m)$。
## Code

```cpp
#include <iostream>

using namespace std;
using ll = long long; // 前排提示：不开 long long 见祖宗！

const int N = 2e5 + 10;

int n, m, k, e, a[N], b[N], c[N];
ll dp[N];

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> k;
  for (int i = 2; i <= n; i++) {
    dp[i] = 1e18; // 赋值最大值
  }
  for (int i = 1; i <= m; i++) {
    cin >> a[i] >> b[i] >> c[i]; // 记录每条边
  }
  for (int i = 1; i <= k; i++) {
    cin >> e;
    dp[b[e]] = min(dp[b[e]], dp[a[e]] + c[e]); // 转移
  }
  cout << (dp[n] < 1e18 ? dp[n] : -1);
  return 0;
}
```

---

## 作者：Tsawke (赞：0)

#  [[ABC271E] Subsequence Path](https://www.luogu.com.cn/problem/AT_abc271_e) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC271E)

## 题面

给定 $ n $ 个点 $ m $ 条边有边权无自环的无向图，给定边集序列 $ E_k $，求边集序列的子序列路径使得能按序从 $ 1 $ 到 $ n $ 且路径长度最小，输出最小值，无解输出 `-1`。

## Solution

最开始的思路是把边集下放然后每个点挂多个 `pair < ll, int >` 表示到这个点的所有可能的权值与其对应的最小的序列终止位置，然后用类似二维偏序的思路转移，但是不确定这个思路假没假以及复杂度是否正确，不过细想一下就会发现这题实际上特别水。

不难发现我们要找的是边的子序列，也就是其是有顺序的，那么我们直接按照边序列顺序跑的话显然是无后效性的，所以我们可以按照最短路的思想，考虑记录到每个点的 $ dis $，然后按序列顺序遍历边，用其起始点的 $ dis $ 加上边权去更新该点的 $ dis $，注意到这里我们可以这么做的原因是如果要求前面的边，一定不会在其之前先走后面的边，这也就是我们刚才提到的无后效性，这样最后 $ dis_n $ 就是答案了。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}
#define ROPNEW_NODE void* Node::operator new(size_t){static Node* P = nd; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define INFLL (0x3f3f3f3f3f3f3f3fll)

template < typename T = int >
inline T read(void);

int N, M, K;
struct{int s, t, v;}edg[210000];
ll dis[210000];

int main(){
    memset(dis, 0x3f, sizeof dis);
    N = read(), M = read(), K = read();
    for(int i = 1; i <= M; ++i)edg[i].s = read(), edg[i].t = read(), edg[i].v = read();
    dis[1] = 0;
    for(int i = 1; i <= K; ++i){
        int idx = read();
        dis[edg[idx].t] = min(dis[edg[idx].t], dis[edg[idx].s] + edg[idx].v);
    }printf("%lld\n", dis[N] == INFLL ? -1ll : dis[N]);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
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

update-2023_02_09 初稿

---

