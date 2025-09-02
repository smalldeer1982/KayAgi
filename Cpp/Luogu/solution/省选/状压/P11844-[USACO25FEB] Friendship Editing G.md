# [USACO25FEB] Friendship Editing G

## 题目描述

Farmer John 的 $N$ 头奶牛编号为 $1$ 到 $N$（$2\le N\le 16$）。奶牛之间的朋友关系可以建模为一个有 $M$（$0\le M\le N(N-1)/2$）条边的无向图。两头奶牛为朋友当且仅当图中她们之间存在一条边。

在一次操作中，你可以添加或删除图中的一条边。计算确保以下性质成立所需的最小操作次数：如果奶牛 $a$ 和 $b$ 是朋友，则对于每头其他奶牛 $c$，$a$ 和 $b$ 中至少之一与 $c$ 是朋友。

## 说明/提示

样例 1 解释：

该网络不符合性质。我们可以添加边 $(2,3)$ 或 $(1,3)$，或删除边 $(1,2)$ 进行修复。

样例 2 解释：

不需要进行任何修改。

- 测试点 $4\sim 13$：对于每一个 $N\in [6, 15]$ 依次有一个测试点。
- 测试点 $14\sim 18$：$N=16$。

## 样例 #1

### 输入

```
3 1
1 2```

### 输出

```
1```

## 样例 #2

### 输入

```
3 2
1 2
2 3```

### 输出

```
0```

## 样例 #3

### 输入

```
4 4
1 2
1 3
1 4
2 3```

### 输出

```
1```

# 题解

## 作者：cff_0102 (赞：14)

考虑在满足条件的图上，如果 $a$ 和 $b$ 不是朋友，它们和其它奶牛的关系：
- 如果 $c$ 和 $a$ 是朋友，根据要求 $b$ 要么和 $a$ 是朋友要么和 $c$ 是朋友，而 $a$ 和 $b$ 并不是朋友，所以 $b$ 和 $c$ 必须是朋友。
- 同理，如果 $c$ 和 $a$ 不是朋友，通过反证法可以证明 $b$ 和 $c$ 也不能是朋友。

那么，考虑满足条件的图的补图，不难发现它是由若干个团组成的。

这样，先把刚开始的图变成其补图，原问题就可以转化成：给定一个图，每次可以加边或删边，求将其变为若干个团的并的最少操作次数。

数据范围提示我们状压 DP。首先可以想到一个大致的思路：

设 $f_{S}$ 表示选择 $S$ 中的奶牛，它们内部合法（即形成若干个团）的最少操作次数。为了帮助转移，再设一个 $g_{S}$ 表示选择 $S$ 的奶牛，它们内部要连成一个团的最少操作次数（这个可以 $O(n^22^n)$ 预处理）。那么有：

$$f_{S}=\min\limits_{T\subset S}(f_{T}+g_{S\backslash T})$$

涉及枚举子集，dp 时间复杂度 $O(3^n)$，总时间复杂度 $O(n^22^n+3^n)$。

但是需要注意实现细节：仔细想想，会发现直接这样转移，不管 $f_S$ 和 $g_S$ 是否需要包括内部的点连到外面的点的状态，总是会有一些边要么被重复算了，要么没有被计算进来。其实这不难解决，因为每条边就算要算，也最多被两个端点各算一次，所以只要保证在计算 $g_S$ 时，把集合内部的点之间的连边也算两次，最后把答案除以二就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=18;
bool a[N][N];
int f[1<<N],g[1<<N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,m;cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=1;
	while(m--){
		int x,y;cin>>x>>y;
		a[x][y]=a[y][x]=0;//补图
	}
	for(int S=0;S<(1<<n);S++){
		for(int i=1;i<=n;i++)if((S>>(i-1))&1){
			for(int j=1;j<=n;j++){
				if(i!=j)g[S]+=(((S>>(j-1))&1)/*是否需要有边*/?(!a[i][j]):a[i][j]);
			}
		}
	}
	for(int S=0;S<(1<<n);S++){
		f[S]=g[S];
		for(int s=S;s;s=S&(s-1)){
			f[S]=min(f[S],f[S^s]+g[s]);
		}
	}
	cout<<f[(1<<n)-1]/2;
	return 0;
}
```

---

## 作者：donaldqian (赞：6)

有一个 key observation：考虑补图，补图一定是若干个完全图的并。考虑反证，若补图中存在 $(a,b),(a,c)$ 的边但不存在 $(b,c)$，由题意知不合法，得证。

然后就很好做了，预处理出 $g_S$ 表示 $S$ 内的点变成一个和外界不交的完全图的代价，$f_S$ 表示考虑完了 $S$ 内的点的最小代价，答案显然是 $f_{2^n-1}$。并且有转移：$f_S=\min\limits_{T\subset S}\{f_T+g_{S-T}\}$，枚举子集即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, f[65536], g[65536];
bool a[16][16];

signed main () {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) a[i][j] = 1;
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v), u--, v--;
		a[u][v] = a[v][u] = 0;
	}
	for (int S = 0; S < (1 << n); S++) {
		for (int i = 0; i < n; i++) if ((S >> i) & 1) {
			for (int j = i + 1; j < n; j++) {
				if (i ^ j) g[S] += ((S >> j) & 1) ? (!a[i][j]) : a[i][j];
			}
		}
	}
	for (int S = 0; S < (1 << n); S++) {
		f[S] = g[S];
		for (int s = S; s; s = S & (s - 1)) {
			f[S] = min (f[S], f[S ^ s] + g[s]);
		}
	}
	return 0;
}
// Is this correct?
```

---

## 作者：Genius_Star (赞：5)

### 思路：

考虑其补图，必为若干个互不相交的团。

故直接状压 $dp_S$ 表示使得 $S$ 的最小操作数，先预处理出 $f_S$ 表示使得 $S$ 为一个团的操作数，有状态转移：

$$dp_S = \min\limits_{T \subset S} dp_T + f_{S - T}$$

中间可能有算重的，但是这是操作次数的最小值，所以不必理会，时间复杂度为 $O(3^n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 17, M = 1 << N;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, m, u, v;
int f[M], g[M];
bool vis[N][N];
bool End;
int main(){
	n = read(), m = read();
	while(m--){
		u = read(), v = read();
		vis[u][v] = 1;
	}
	for(int S = 0; S < (1 << n); ++S)
	  for(int i = 1; i <= n; ++i)
	    if((S >> (i - 1)) & 1)
	      for(int j = i + 1; j <= n; ++j)
	        f[S] += ((S >> (j - 1)) & 1) ? vis[i][j] : (vis[i][j] ^ 1);
	for(int S = 0; S < (1 << n); ++S){
		g[S] = f[S];
		for(int T = S; T; T = (T - 1) & S)
		  g[S] = min(g[S], g[T] + f[S ^ T]);
	}
	write(g[(1 << n) - 1]);
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}


```

---

## 作者：未来姚班zyl (赞：4)

### 题目大意

对于一个 $n$ 个点 $m$ 条边的简单无向图，定义其合法当且仅当：

- 对于任意一条边 $(x,y)$，与不同于 $x,y$ 的点 $z$，$z$ 必须和 $x,y$ 中至少一个点连边。

现在给你一个 $N$ 个点 $M$ 条边的初始图，你可以进行若干次操作，每次形如删除一条边或加入一条边，求使这个图合法的最小操作数，$1\le N\le 16$。

### 题目分析

首先空图是合法的，特判掉，否则所有点在一个连通块内。

这题的关键在于发现性质：对于任意点 $x,y$，其最短路（边数）$\le 2$。

证明很简单，如果最短路边数大于 $2$，设路径为 $x\rightarrow ...\rightarrow z\rightarrow y$，$x$ 和边 $(z,y)$，$x$ 与 $y,z$ 都无边，非法。

于是我们可以找一个点 $x$，并枚举其他点 $y$ 与 $x$ 的最短路，并按照最短路长度将其他点分为集合 $S_1$ 与 $S_2$，则：

- $x$ 到 $S_1$ 中的所有点都应该有边，否则最短路为 $2$。
- $x$ 到 $S_2$ 中的所有点都没有边，否则最短路为 $1$。
- $S_1$ 中的点到 $S_2$ 中的所有点都必须有边，考虑 $y\in S_1,z\in S_2$，由于有边 $(x,y)$，而 $z$ 和 $x$ 没有边，则 $z$ 和 $y$ 必须有边。
- $S_2$ 内部无边，否则 $x$ 与那条边的端点无边。
- $S_1$ 内部成为子问题。

容易发现 $x$ 与 $S_2$ 可以合并，因为他们之间没边，且和 $S_1$ 的点都有边。

设 $dp_S$ 表示点集为 $S$ 的答案（只考虑 $S$ 内部的边），枚举子集转移，我们需要维护：

- 一个集合 $S$ 内部的边数，只需要从 $S$ 中单独取出一个点 $x$，计算 $x$ 到剩下点的边数即可，可以 $O(n2^n)$，使用位运算精细实现可以做到 $O(2^n)$。
- 两个不交集合 $S$ 到 $T$ 的边数，可以用并集的边数减去各自内部的边数。

这样可以 $O(2^n)$ 预处理， $O(3^n)$ 转移，通过此题。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define OK Ll<=l&&r<=Rr
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
const int N=2e1+5,M=1e5+5,inf=(1LL<<29)-1,mod=998244353;
const ll llf=1e18;
int n,m;
int dp[M],ct[M],Ct[M];
inline bool che(int s,int p){
	return (s>>p-1)&1;
}
int Sta[N];
int Id[M];
inline void Main(){
	n=read(),m=read();
	repm(i){
		int x=read(),y=read();
		Sta[x]|=1<<y-1,Sta[y]|=1<<x-1;
	}
	int now=1;
	repn(i)Id[now]=i,now<<=1;
	int S=(1<<n)-1;
	rep(i,1,S)ct[i]=ct[i-(i&-i)]+1;
	rep(s,1,S){
		int t=s-(s&-s);
		Ct[s]=Ct[t]+ct[Sta[Id[s&-s]]&t];
	}
	rep(s,1,S){
		if(ct[s]<=1)continue;
		dp[s]=Ct[s];
		for(int t=s;t;t=(t-1)&s){
			int cst=(ct[t]*ct[s^t])-(Ct[s]-Ct[t]-Ct[s^t]);
			dp[s]=min(dp[s],cst+Ct[t]+dp[s^t]);
		}
	}
	cout <<dp[S];
}
signed main(){
	int T=1;
	while(T--)Main();
	return 0;
}
```

---

## 作者：Monkey_Dog (赞：1)

因为如果奶牛 $a$ 和 $b$ 是朋友，则对于每头其他奶牛 $c$，$a$ 和 $b$ 中至少之一与 $c$ 是朋友，所以假设 $a,b$ 不是朋友，就会有两种情况。（$c$ 为 $a,b$ 外任意一点）

```cpp
1.  a   b   2.  a   b
     \ /
      c           c
```
考虑建[补图](https://oi-wiki.org/graph/concept/#%E8%A1%A5%E5%9B%BE)：
```cpp
1.  a---b   2.  a---b
                 \ /
      c           c
```
将图扩展可以推出，$a,b$ 外任意一个点要么和 $a,b$ 都有连接，要么和 $a,b$ 都没连接。同理，两个点与同一个点都有连接，那这两个点也有连接。

所以只要有 $a,b$ 外的两点 $c,d$ 都跟 $a$ 和 $b$ 有连接，$c,d$ 之间就也会有连接，这时 $a,b,c,d$ 就会形成一个[团](https://oi-wiki.org/graph/concept/#%E5%9B%A2)，所以整个图就是很多团的并集。

所以问题就转换成了求将一个图的补图修改成很多团的并集的最小操作次数。

看到 $N\le 16$ 想到状压。定义 $f_S$ 代表所选点情况为 $S$ 时，所选点构成的图为很多团的并集时，操作次数的最小值。转移：
$$f_S= \min \limits_{i\subseteq S}(f_i+G_{S-i})$$

$G_{S}$ 表示所选点情况为 $S$ 时，所选点构成的图为一个独立的团时，操作次数的最小值。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[20][20],f[(1<<16)+5],g[(1<<16)+5];
signed main(){
	cin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)a[i][j]=1;
    for(int i=1,x,y;i<=m;i++)
        cin>>x>>y,x--,y--,a[x][y]=a[y][x]=0;//补图
    for(int s=0;s<(1<<n);s++)
        for(int i=0;i<n;i++)if(s&(1<<i))
            for(int j=i+1;j<n;j++)//考虑去重，一条边只算一遍
                if(i^j)g[s]+=(s&(1<<j))?(!a[i][j]):a[i][j];

    for(int i=0;i<(1<<n);i++){
        f[i]=g[i];
        for(int j=i;j;j=i&(j-1))
            f[i]=min(f[i],f[i^j]+g[j]);
    }
    cout<<f[(1<<n)-1];
}
//完结撒花\(o w o)/
```

---

## 作者：IGpig (赞：1)

## P11184
## Solution
看到 $n\le 16$ 一眼状压，**我的方法一点都不抽象！！！**。\
先观察题目，为了方便状压，存图的时候选择对于一个点，用二进制的点集来表示其直接连边的点，即 $g_x=1<<y$。

要使整个图满足，我们发现可以把它划分为子点集然后合并，也就是从小到大转移状态。
然后想到 $dp_s$ 表示点集为 $s$ 时的最小答案，那么接下来考虑转移。

我们发现对于一个状态 $s$，要让它合法，它一定是对于另一个点 $z\notin s$，它当中的所有点到这个 $z$ 的最短路都为 $1$ 或 $2$。\
解释一下，因为题目要求确保以下性质成立所需的最小操作次数：如果奶牛 $a$ 和 $b$ 是朋友，则对于每头其他奶牛 $c$，$a$ 和 $b$ 中至少之一与 $c$ 是朋友。\
那么对于 $x\in s,y\in s$，先看最短路为 $1$ 的时候，你会发现很明显 $x$ 与 $z$ 是朋友，那么 $y$ 也必须与 $z$ 是朋友，所以最短路为 $1$。然后 $2$ 的情况就很好理解了，$x$ 和 $y$ 与 $z$ 没有关系。

发现这个性之后就可以动态规划了，我们用 $num_s$ 表示点集 $s$ 中的边数，$dp_s$ 表示要是其合法需要的最小操作次数。\
接下来看看动态规划的过程：
- 枚举从小到大的点集 $s$。
- 枚举 $s$ 的所有子集 $t$。
- $k$ 为 $t$ 的补集。
- 删的边数量是 $t$ 中和 $k$ 中点的数量的积。
- 连的边就是 $num_s-num_t-num_k$。
- 最后不上一个 $num_k$ 因为要把 $t$ 补成 $s$。
- 更新最小值。

### Code
```cpp
#include <bits/stdc++.h>
#define cnt1 __builtin_popcount
using namespace std;
using LL = long long;

LL n, m, mx, dp[1 << 19], U[20], V[20], g[20], num[1 << 19];

int main() {
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        g[x - 1] |= 1 << (y - 1);
        g[y - 1] |= 1 << (x - 1);
    }

    mx = (1 << n) - 1;

  
    for (int s = 0; s <= mx; s++) {
        for (int i = 0; i < n; i++) {
            if (s & (1 << i)) {
                num[s] += cnt1(g[i] & s);
            }
        }
        num[s] /= 2; 
        dp[s] = num[s]; 
    }

    for (int s = 0; s <= mx; s++) {
        for (int t = s; t; t = (t - 1) & s) {
            LL k = s ^ t;
            LL cost = dp[t] + cnt1(t) * cnt1(k) - (num[s] - num[t] - num[k]) + num[k];
            dp[s] = min(dp[s], cost);
        }
    }

    cout << dp[mx] << "\n";
    return 0;
}
```

---

## 作者：dengchengyu (赞：1)

## [P11844 [USACO25FEB] Friendship Editing G](https://www.luogu.com.cn/problem/P11844)

首先特判掉没有边的情况，否则整张图连通。

然后考虑题目要求的限制即任意两个点的最短路小于或等于 $2$。

假设确定一个点 $x$，和与 $x$ 最短路为 $1$ 的点集 $S_1$，与 $x$ 最短路为 $2$ 的点集 $S_2$。

有如下连边规律：

* $S_1$ 中的点与 $x$ 都有边，否则最短路不为 $1$。
* $S_2$ 中的点与 $x$ 都没有边，否则最短路不为 $2$。
* $S_2$ 中的点两两之间都没有边，否则有一条边则 $x$ 与这条边的端点无边，不符合题意。
* $S_2$ 中的点每个点与 $S_1$ 中的每个点都有边，否则对于 $y\in S_1,z\in S_2$，因为 $x,y$ 一定有一条边，如果 $y,z$ 之间无边则不符合题意。
* $S_1$ 中的边成为一个子问题。

如果枚举 $x$，再枚举 $S_2$ 是会算重的，但我们发现 $x$ 与 $S_1$ 的关系、$S_2$ 与 $S_1$ 的关系是相同的，所以可以把 $x$ 并入 $S_2$。

那么就是一个枚举子集的 DP。

现在问题是求边数，求一个点集内部的边 $F_S$ 直接暴力地做即可，复杂度 $O(2^nm)$；求点集 $S$ 与点集 $T$ 之间的边数可以用 $F$ 容斥，即 $F_{S\cup T}-F_S-F_T$。

总复杂度 $O(3^n)$。

代码：

```cpp
int n,m;
const int M=400;
int f[1<<16],s[1<<16];
int edge[1<<16];
int u[M],v[M];
signed main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin>>n>>m;
	fo(i,1,m) {
		cin>>u[i]>>v[i];
		edge[u[i]]|=1<<v[i]-1;
		edge[v[i]]|=1<<u[i]-1;
	}
	fu(i,1,1<<n) {
		int j=__builtin_ctz(i)+1;
		s[i]=s[i^(1<<j-1)]+popc(edge[j]&i);
	}
	fu(i,0,1<<n) {
		f[i]=s[i];
		for(int j=i;j;j=(j-1)&i) {
			f[i]=min(f[i],f[j]+popc(j)*popc(i^j)-(s[i]-s[j]-s[i^j])+s[i^j]);
		}
	}
	cout<<f[(1<<n)-1];
	return 0;
}
```

---

## 作者：Grace2022 (赞：0)

## 题意
给定一个简单无向图，进行一些操作，每一次操作增加或减少一条边，使得图中任意一条边，存在一个端点与除该边之外的每一个点有边相连，输出操作数的最小值。  

## 思路
题目给定的图的性质和完全图（任意两点都有边相连）很像，但不完全一样。考虑其补图是不是完全图，我们发现若其补图存在一条边 $(u,v)$ 使得其中有端点 $v$ 不与点 $c$ 相连（两个端点都不相连是一样的），那么补图的补图即原图就有边 $(u, c)$ 但 $u$ 和 $c$ 都不与 $v$ 相连，与题目要求性质相悖，所以一定补图一定有 $(u, v)$、$(u,c)$、$(v,c)$ 的边，即补图是一个完全图。

问题转化成了怎么增删边使得补图是一个完全图。定义 $f_i$ 表示点集为 $i$ 的满足条件的最小操作数，作为状压 dp 的转移方程应为 $f_S = \min(f_S, f_T + calc(S - T))$，其中 $S - T$ 表示差集运算，即包含于 $S$ 但不包含于 $T$ 的部分，计算函数 $calc$ 表示使得当前点集变成完全图的操作数。  

对于 $calc$ 的运算，我们可以用数组 $s$ 预处理，十分暴力地枚举每一个点集中每两个点需不需要操作即可，如果点 $j$ 在点集里，但同在点集里的点 $k$ 与 $j$ 没有边相连，那么就加边；如果点 $j$ 在点集里，但不在点集里的点 $k$ 却与 $j$ 相连了，那么就删边。把这两种情况的操作数加上就行。

在计算 $s$ 时，因为无向图，如果双层循环都从 $1$ 到 $n$ 遍历会导致重复，你可以选择改变循环端点值使得不重复（代码所示），也可以选择在最后除以二。

时间复杂度 $\mathcal{O}(n^2 2^n + 3^n)$。
## 代码
这里用了快读，略显冗长。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
inline int read(){
	int s = 0, st = 1;
	char c = getchar();
	while(c < '0' || c > '9'){
		(c == '-') && (st = -1);
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		s = (s << 1) + (s << 3) + (c ^ 48);
		c = getchar();
	}
	return s * st;
}
inline void write(int x){
	if(x < 0){
		 x = -x;
		 putchar('-');
	}
	if(x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
const int N = 16, M = 120;
bool e[M + 5][M + 5];
int f[(1 << N) + 5], s[(1 << N) + 5];
/*
s[i]: 点集为i变成团的增加边数
f[i]: 点集为i满足条件的操作次数 
*/
signed main(){
	int n = read(), m = read(), S;
	S = (1 << n) - 1;
	memset(e, 1, sizeof(e));
	for(int i = 1; i <= m; ++i){
		int u = read(), v = read();
		e[u][v] = e[v][u] = 0;
	}
	for(int i = 1; i <= S; ++i){
		for(int j = 1; j <= n; ++j){
			if(((1 << j - 1) & i) == 0) continue;
			for(int k = j + 1; k <= n; ++k){
				if(j == k) continue;
				if(((1 << k - 1) & i) == 0) s[i] += e[j][k];//有边删 
				else s[i] += !e[j][k];//没边添 
			}
		}
	}
	
	for(int i = 0; i <= S; ++i){
		f[i] = s[i];
		for(int j = i; j > 0; j = (j - 1) & i){
			f[i] = min(f[i], f[i ^ j] + s[j]);
		}
	}
	write(f[S]);
	return 0;
}

```

---

## 作者：DengStar (赞：0)

> 代码见于 [博客园](https://www.cnblogs.com/dengstar/p/18738170)

称满足题目给出性质的图是“好的“图。首先肯定要找到一种简洁的方式来刻画”好的“图，~~但我第一步就输了~~

如果直接想比较困难，不妨考虑**补图**。事实上一个好的图必定满足：其补图的每个连通块都是完全图。

证明：在原图中，$(a, b)$ 有边 $\Longrightarrow$ 对任意其它点 $c$，$(a, c)$ 有边或 $(b, c)$ 有边。因此，在反图中，$(a, b)$ 没有边 $\Longrightarrow$ 对任意其它点，$(a, c)$ 没有边或 $(b, c)$ 没有边。考虑**逆否命题**，在补图中，$(a, c)$ 有边**且** $(b, c)$ 有边 $\Longrightarrow$ $(a, b)$ 有边。所以对于补图中的一个连通图，不断应用这个结论就可以得出：每个连通分量都必须是完全图时，原图才是好的。

下面默认在补图中考虑。

有了这个结论之后就可以直接 dp 了。具体而言，设 $f(S)$ 表示使得点集 $S$ 的导出子图成为若干个完全图的并的最小代价，$g(S)$ 代表点集 $S$ 的导出子图中的边数，$cross(S, T)$ 表示两个点集 $S$ 和 $T$ 之间的边数。

由于我们要让补图变成若干个（两两之间无边的）完全图的并，所以转移时枚举当前点集 $S$ 的一个子集 $T$ 作为新加入的完全图。我们还要要求 $T$ 和 $S$ 的剩余部分 $S \setminus T$ 之间没有边，所以需要删除原有的这些边，代价为 $cross(T, S \setminus T)$。综上所述，转移方程如下：
$$
\boxed{f(S) = \min_{T \subseteq S} \{g(T) + f(S \setminus T) + cross(T, S \setminus T)\}}
$$
（注意一个同方案可能被转移了多次，但这是最优化问题而不是计数题，所以对同一个状态的多次转移不影响答案）

$g(S)$ 可以在 $O(2^{n}n^{2})$ 的时间内平凡地暴力求出，$cross(S, T)$ 可以通过容斥求出（两个点集之间的边数等于点集之并的边数减去两个点集内部的边数之和）。转移时枚举子集的时间复杂度为 $O(3^{n})$，因此总时间复杂度为 $O(2^{n}n^{2} + 3^{n})$。

**总结**：对于这类要求结构满足某种性质的题，要先找到这种性质的更为简洁的等价刻画方式，才能入手解决问题。对于本题，考虑图上的问题时，如果不容易在原图上之间考虑，可以考虑补图。推出性质之后的状压 dp 是比较平凡的。

---

