# [ARC121F] Logical Operations on Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc121/tasks/arc121_f

$ 1 $ から $ N $ の番号がついた $ N $ 頂点の木が与えられます。

$ i $ 番目の辺は頂点 $ a_i $ と $ b_i $ をつないでいます。

すぬけ君は頂点には `0` か `1` のラベルを、辺には `AND` か `OR` のラベルをつけることにしました。 頂点と辺へのラベルのつけ方は $ 2^{2N-1} $ 通りあります。それらのうち下記の条件を満たすものの個数を $ 998244353 $ で割ったあまりを求めてください。

条件：*操作* を $ N-1 $ 回行ったのち、残った頂点についているラベルが `1` になるような操作手順が存在する。操作は下記の手順からなる。

- 辺を $ 1 $ 本選んで縮約する(消された $ 2 $ 個の頂点に書かれていたラベルを $ x,y $、消された辺に書かれていたラベルを $ \mathrm{op} $ とする)。
- $ \mathrm{op} $ が `AND` ならば $ \mathrm{AND}(x,y) $ を、`OR` ならば $ \mathrm{OR}(x,y) $ を新たな頂点にラベルとしてつける。

## 说明/提示

### 注記

- 演算 $ \mathrm{AND} $ の定義は次の通りです：$ \mathrm{AND}(0,0)=(0,1)=(1,0)=0,\mathrm{AND}(1,1)=1 $
- 演算 $ \mathrm{OR} $ の定義は次の通りです：$ \mathrm{OR}(1,1)=(0,1)=(1,0)=1,\mathrm{OR}(0,0)=0 $
- 頂点 $ s $ と頂点 $ t $ を結ぶ辺を縮約する際は、その辺を取り除くと同時に $ 2 $ 頂点を併合します。縮約後の木において、併合により生まれた頂点と頂点 $ u $ を結ぶ辺が存在するのは、縮約前の木において $ s $ と $ u $ を結ぶ辺または $ t $ と $ u $ を結ぶ辺が存在するときであり、またそのときに限られます。

### 制約

- 与えられる入力は全て整数
- $ 2\ \leq\ N\ \leq\ 10^{5} $
- $ 1\ \leq\ a_i,\ b_i\ \leq\ N $
- 与えられるグラフは木

### Sample Explanation 2

\- $ 998244353 $ で割ったあまりを出力するのを忘れずに。

## 样例 #1

### 输入

```
2
1 2```

### 输出

```
4```

## 样例 #2

### 输入

```
20
7 3
20 18
16 12
7 2
10 5
18 16
16 3
4 11
7 15
8 1
6 1
12 13
15 5
19 17
7 1
9 8
7 17
16 14
11 7```

### 输出

```
283374562```

# 题解

## 作者：Fido_Puppy (赞：5)

一道比较简单的 ARC F。

## 题目链接

<https://atcoder.jp/contests/arc121/tasks/arc121_f>

## 题解

看到计算合法的方案数，套路地先考虑如何判断一个方案是否合法。

在列举了大量情况后，能够发现先操作所有 $\text{AND}$ 边，后操作所有 $\text{OR}$ 边，一定是不劣的。

形式化地，一个方案合法的条件，当且仅当将所有 $\text{OR}$ 边断开后，形成的若干个连通块中至少有一个联通块的点权是全 $1$ 的。

### 充分性

显然，如果有一个联通块的点权全 $1$，那么将所有联通块缩成一个点后，至少有一个点的点权为 $1$，并且图中只剩下 $\text{OR}$ 边，显然合法。

### 必要性

只需要证明当所有连通块中都至少有一个 $0$ 时，不存在一种边的操作顺序能使得最终剩下的点权为 $1$。

显然地，操作一次 $\text{AND}$ 操作，并不能将一个连通块变成全 $1$ 连通块。

并且，如果操作 $\text{OR}$ 操作将两个联通块合并成一个连通块，则新连通块一定不是全 $1$ 连通块。

**证明**：如果 $\text{OR}$ 边的两个端点都是 $0$，则操作后的新点点权为 $0$；如果至少一个端点为 $1$，因为两个连通块都不是全 $1$ 连通块，所以在其所在的连通块内仍至少存在一个 $0$，新连通块也不是全 $1$ 连通块。

所以不管怎么操作，最终只能得到一个点权为 $0$ 的点。

### 树形 $\text{dp}$

有了上述结论，我们统计方案数，本质上就是枚举 $\text{OR}$ 边，将整棵树断成若干个连通块，然后在连通块内赋上点权，并且保证至少有一个全 $1$ 连通块。

首先至少一个全 $1$ 连通块不是很好做，考虑容斥，计算所有连通块都不是全 $1$ 连通块的方案数。

这是一个经典的树形 $\text{dp}$：

设 $f_{u, 0/1}$ 表示在以 $u$ 为根的子树内划分连通块，$u$ 点所在的连通块内，$0$ 表示已经有点权为 $0$ 的点了，$1$ 表示还没有点权为 $0$ 的点。

转移就考虑枚举每一条边 $(u, v)$ 是否断开（$v$ 为 $u$ 的儿子节点）。

$$2 \cdot f_{u, 0} \times f_{v, 0} + f_{u, 1} \times f_{v, 0} + f_{u, 0} \times f_{v, 1} \longrightarrow f_{u, 0}$$

$$f_{u, 1} \times f_{v, 1} + f_{u, 1} \times f_{v, 0} \longrightarrow f_{u, 1}$$

**注意**：当 $v$ 所在联通块还没有点权为 $0$ 的点时，$(u, v)$ 是不能断开的，因为要求没有连通块是全 $1$ 连通块。

最终答案为 $2 ^ {2n - 1} - f_{1, 0}$。

时间复杂度 $\Theta(n)$。

## 代码链接

<https://atcoder.jp/contests/arc121/submissions/43276183>

---

## 作者：hejianxing (赞：4)

[luogu link](https://www.luogu.com.cn/problem/AT_arc121_f)

[Atcoder link](https://atcoder.jp/contests/arc121/tasks/arc121_f)

# 题意

给定 $n$ 个点的树，每个点填 `0` 或 `1`，每条边填 `And` 或 `Or`，在 $2^{n+n-1}$ 种填法中计数有多少种，存在一种缩边顺序，每次将一条边两点缩成一个点，点权为两点点权与边的运算值，使得最终的点权为 $1$。

# 题解

对于一种填法，显然有贪心缩边策略为优先计算 `And` 的边，从而降低最终结果为 $0$ 的可能性。

那么考虑判断一种填法是否合法。

将 `Or` 边断开，若存在一个连通块的 `And` 值为 $1$，则最终的结果为 $1$，否则一定为 $0$。

至少一个不好计算。转化为所有方案减去全部连通块的 `And` 值为 $0$ 的方案数。

于是考虑树形 dp 计算全部联通块均为 $0$ 的方案数。

设 $f_{i,0/1}$ 为 $i$ 子树中，$i$ 所在的连通块当前的值为 $0/1$ 的方案数。$f$ 是计算了整个 $i$ 的子树，而 $0/1$ 只考虑 $i$ 所在的连通块。

$f_{i,1}$ 存在的意义，是提供一个未完成的连通块（这个连通块的值当前为 $1$），而这个连通块有可能在祖先处加上了若干个 $0$ 的点，从而变成一个合法的连通块。

考虑 $i$ 与儿子 $j$ 这一条边。

- 为 `And`。
	- $f_{i,0}\gets f_{i,0}\cdot f_{j,0}+f_{i,1}\cdot f_{j,0}+f_{i,0}\cdot f_{j, 1}$
	- $f_{i,1}\gets f_{i,1}\cdot f_{j,1}$
- 为 `Or`。注意这里若连通块 $j$ 的值不是 $0$ 则不能断开 $(i,j)$ 这条边，所以没有 $f_{j,1}$ 的贡献。
	- $f_{i,0}\gets f_{i,0}\cdot f_{j,0}$
	- $f_{i,1}\gets f_{i,1}\cdot f_{j,0}$

将两种贡献加起来。最终有：

$$f_{i,0}=2f_{i,0}\cdot f_{j,0}+f_{i,1}\cdot f_{j,0}+f_{i,0}\cdot f_{j,1}\\f_{i,1}=f_{i,1}\cdot f_{j,0}+f_{i,1}\cdot f_{j,1}$$

答案是 $2^{2n-1}-f_{1,0}$。

时间复杂度 $O(n)$。

# 实现

要注意更新 $f_{i,0/1}$ 时的顺序问题，先用临时变量存储再更新。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;
const LL mod = 998244353;
int n, fir[N], nxt[N << 1], to[N << 1], cnt = 0;
LL f[N][2];
void ade(int u, int v) {
	cnt++, nxt[cnt] = fir[u], fir[u] = cnt, to[cnt] = v;
	cnt++, nxt[cnt] = fir[v], fir[v] = cnt, to[cnt] = u;
}
LL qpow(LL x, LL y) {
	LL sum = 1;
	while (y) {
		if (y & 1) sum = sum * x % mod;
		x = x * x % mod, y >>= 1;
	}
	return sum;
}
void dfs(int r, int fr) {
	f[r][0] = f[r][1] = 1;
	for (int i = fir[r]; i; i = nxt[i])
		if (to[i] != fr) {
			dfs(to[i], r);
			LL t1 = (2ll * f[r][0] * f[to[i]][0] % mod + f[r][1] * f[to[i]][0] % mod + f[r][0] * f[to[i]][1] % mod) % mod;
			LL t2 = (f[r][1] * f[to[i]][1] % mod + f[r][1] * f[to[i]][0] % mod) % mod;
			f[r][0] = t1, f[r][1] = t2;
		}
}
int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), ade(u, v);
	dfs(1, 0);
	printf("%lld", (qpow(2, 2 * n - 1) - f[1][0] + mod) % mod);
	return 0;
}
```

# 启示

- 正难则反，简单有效的思维方式。常见于“至少若干个”等，见到此类计数应当迅速反应。由此也可能引出容斥
- 状态设计要考虑全面，不要漏情况
- 树上计数题很大概率是 dp



---

## 作者：ningago (赞：4)

考虑剥叶子。对于一个叶子 $x$，考虑其父边的操作及其自身的权值：

- 如果是 $\mathrm{or}\ 0$ 或 $\mathrm{and}\ 1$ 则对答案没有影响，可以直接剥去这个叶子。
- 如果是 $\mathrm{or}\ 1$，那么胜利了，不用再考虑其他的节点了。
- 如果是 $\mathrm{and}\ 0$，则剥去这个叶子造成的影响是父亲被修改为 $0$。容易发现无论在什么时候剥这个叶子，父亲最后一定会变成 $0$。

所以根据分析可以只考虑子树，令 $dp_{x,0/1/2}$ 表示当前 $x$ 节点的权值为 $0/1$ 或已经胜利了。直接转移即可。

复杂度 $O(n)$。

https://atcoder.jp/contests/arc121/submissions/46985253

---

## 作者：Graphcity (赞：3)

~~第一次见到这么简单的 ARC F~~

首先考虑给定点权和边的运算符时，该怎么样才能够使得最终的答案为 1。

**结论**：先缩 `and` 边，再缩 `or` 边是一种最优方案。这种方案最后答案为 1 当前仅当将所有 `or` 边删掉之后，剩下 `and` 边构成的连通块中有一个答案为 1。

**证明**：首先充分性易证。其次观察必要性，如果每个 `and` 连通块的答案为零，那么用 `or` 操作将两个连通块连接起来的时候，这个新连通块的答案仍然为零。以此类推，最后的答案仍为零。

设 $f_{i,0/1,0/1}$ 表示 $i$ 子树内连通块的答案为 $0/1$，且其它连通块中是否有 1 的方案数，背包即可。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5,Mod=998244353;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,f[Maxn+5][2][2],g[2][2];
vector<int> v[Maxn+5];

inline void add(int &x,int y) {x=(x+y)%Mod;}
inline void dfs(int x,int fa)
{
    f[x][0][0]=f[x][1][0]=1;
    for(auto y:v[x]) if(y!=fa) dfs(y,x);
    for(auto y:v[x]) if(y!=fa)
    {
        memset(g,0,sizeof(g));
        For(a,0,1) For(b,0,1) For(c,0,1) For(d,0,1)
            add(g[a][b|c|d],1ll*f[x][a][b]*f[y][c][d]%Mod);
        For(a,0,1) For(b,0,1) For(c,0,1) For(d,0,1)
            add(g[a&c][b|d],1ll*f[x][a][b]*f[y][c][d]%Mod);
        For(a,0,1) For(b,0,1) f[x][a][b]=g[a][b];
    }
}

int main()
{
    n=read();
    For(i,1,n-1)
    {
        int a=read(),b=read();
        v[a].push_back(b),v[b].push_back(a);
    }
    int ans=0; dfs(1,0);
    For(a,0,1) For(b,0,1) if(a|b) add(ans,f[1][a][b]);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：DengDuck (赞：2)

普遍思路是，先思考方案确定时的策略。

直觉上，我们应该先合并边权为“和”操作的边，为什么呢？我们试着证明。

一种方案有解当且仅当“和”操作边组成的连通块，其中一个所有的点的点权都是 $1$。

必要性：如果所有没有连通块满足“所有的点的点权都是 $1$”，那么你先执行“或”操作只不过是合并两个连通块，之后这个连通块依旧是不满足性质的，最后结果必然为 $0$。

充分性：如果连通块其中一个所有的点的点权都是 $1$，那么考虑先合并所有的“和”操作，那么就是一堆数字和 $1$ 做“或”操作，所以结果是 $1$。

发现证明的同时得到了合法的判断条件，我们考虑以此来做动态规划。

“存在至少一个”这是个抽象的东西，正难则反，考虑求“不存在”的方案数，也就是每个“和”连通块至少一个 $0$。

设 $f_{i,0/1}$ 表示 $i$ 所在连通块是否有 $0$，转移时根据两个条件，分讨四种情况——儿子连通块目前有 $0$ 吗？我和儿子连边吗？

注意儿子当前没有 $0$ 时你必须和儿子连边，不然就有解了。

时间复杂度为 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=3e5+5;
const LL mod=998244353;
LL n,f[N][2];
vector<LL>v[N];
LL ksm(LL x,LL y)
{
	LL ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		x=x*x%mod,y>>=1;
	}
	return ans;
}
void dfs(LL x,LL fa)
{
	f[x][0]=f[x][1]=1;
	for(LL i:v[x])
	{
		if(i==fa)continue;
		dfs(i,x);
		f[x][1]=(f[x][1]*(f[i][0]+2*f[i][1])%mod+f[x][0]*f[i][1]%mod)%mod;
		f[x][0]=(f[x][0]*(f[i][0]+f[i][1]))%mod;	
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n-1;i++)
	{
		LL x,y;
		cin>>x>>y;
		v[x].push_back(y),v[y].push_back(x);
	}
	dfs(1,0);
	LL ans=(ksm(2,2*n-1)-f[1][1]+mod)%mod;
	cout<<ans<<endl;
}
```

---

## 作者：Elma_ (赞：2)

不妨钦定 $1$ 为根。考虑一个特殊的局部：如果在操作过程中，出现了某个叶子的值为 $1$ 且连接它的边为 $\text{OR}$，那么只需要将其放在最后操作，就一定能够得到 $1$。我们用有序对 $(1, \text{OR})$ 来描述这个叶子的状态。

接着我们考虑出现的叶子的其他状态：

- $(1,\text{AND})$ 和 $(0,\text{OR})$ ：显然这个叶子对答案没有影响，因此原树合法的充要条件是上面的部分合法。

- $(0,\text{AND})$：由于操作之后其父亲的权会变为 $0$，我们不妨在这样的叶子出现时就立刻对其进行操作，这样能够减小它对答案的负面影响。因此原树合法的充要条件还是上面的部分合法。

也就是说，如果不存在某种操作方式使得能够出现 $(1, \text{OR})$ 这样的叶子，那么依次删掉叶子一定不劣。此时合法的充要条件是：根节点权为 $1$，且其儿子形成的叶子的状态都是 $(1,\text{AND})$ 或 $(0,\text{OR})$。这是相对容易计数的。

考虑容斥，改为计算不合法的方案数。如果我们能求出不存在 $(1,\text{OR})$ 的方案数 $f$ 和其中合法的方案数 $g$，那么 $f-g$ 就是不合法的方案数。考虑树形 DP，设 $f_u$ 表示 $u$ 的子树中不存在 $(1,\text{OR})$ 的方案数，$g_u$ 表示 $u$ 的子树中不存在 $(1,\text{OR})$ 且合法的方案数。根据上面的分析，初始时 $f_u = 2,g_u = 1$。

对于 $f$，有转移 $f_u \gets f_u \times \prod \limits_{v \in \text{son}_u} (2 \times f_v - g_v )$。其中 $2 \times f_v$ 是因为 $(u,v)$ 可以是 $\text{OR}$ 或 $\text{AND}$，减去 $g_v$ 是为了排除 $v$ 子树合法且 $(u,v)$ 为 $\text{OR}$，即出现 $(1,\text{OR})$ 的情况。

对于 $g$，有转移 $g_u \gets g_u \times \prod \limits_{v \in \text{son}_u} f_v$。注意无论 $v$ 子树是否合法，由于其成为叶子时状态只能是 $(1, \text{AND})$ 或 $(0,\text{OR})$，因此 $(u,v)$ 实际上是确定的，因此 $f_v$ 的系数为 $1$。

时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, mod = 998244353;
int n, f[N], g[N];
vector <int> e[N];
int ksm(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1LL * ret * a % mod;
        a = 1LL * a * a % mod, b >>= 1;
    }
    return ret;
}
void dfs(int u, int ff) {
    f[u] = 2, g[u] = 1;
    for (auto v : e[u]) {
        if (v == ff) {
            continue;
        }
        dfs(v, u);
        f[u] = 1LL * f[u] * (1LL * f[v] * 2 % mod + mod - g[v]) % mod;
        g[u] = 1LL * g[u] * f[v] % mod;
    }
}
int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, x, y; i < n; i++) {
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs(1, 0);
    int ans = (1LL * ksm(2, 2 * n - 1) + mod - f[1] + g[1]) % mod;
    cout << ans << "\n";
    return 0;
}
```


---

## 作者：tribool4_in (赞：1)

非常好水 arc F。

首先考虑如何判定方案是否合法。注意到如果 $n=3$ 且两条边分别为 $\text{AND}$ 和 $\text{OR}$ 时，先做 $\text{AND}$ 后做 $\text{OR}$ 一定最优。于是猜一个结论，先做所有 $\text{AND}$ 再做所有 $\text{OR}$，也就是考虑断开所有 $\text{OR}$ 边后形成的若干个连通块必须存在一个全 $1$ 的。

不太严谨的证明，大概考虑相邻的两条边操作符不同，分类讨论一下三个点各自连通块的最优情况，然后发现先做 $\text{AND}$ 更优（跟 $n=3$ 类似）。

于是就很好做了。考虑大力 dp，设 $dp_{u,0/1,0/1,0/1}$ 表示 $u$ 子树内是否已经有全 $1$ 的连通块（不包括当前）、当前连通块是否全 $1$、当前点填的是 $0/1$ 时的方案数。转移直接枚举 $2^6$ 种情况即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, mod = 998244353;
int n;
vector<int> G[N];
int dp[N][2][2][2], f[2][2][2];
void dfs(int u, int fa) {
    dp[u][0][0][0] = dp[u][0][1][1] = 1;
    for (auto v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
        memcpy(f, dp[u], sizeof(f));
        memset(dp[u], 0, sizeof(dp[u]));
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    for (int ii = 0; ii < 2; ii++) {
                        for (int jj = 0; jj < 2; jj++) {
                            for (int kk = 0; kk < 2; kk++) {
                                (dp[u][i | ii][j & jj][k] += 1ll * f[i][j][k] * dp[v][ii][jj][kk] % mod) %= mod;
                                (dp[u][i | ii | jj][j][k] += 1ll * f[i][j][k] * dp[v][ii][jj][kk] % mod) %= mod;
                            }
                        }
                    }
                }
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs(1, 0);
    cout << (1ll * dp[1][1][0][0] + dp[1][1][0][1] + dp[1][1][1][0] + dp[1][1][1][1] + dp[1][0][1][0] + dp[1][0][1][1]) % mod << '\n';
    return 0;
}
```

---

## 作者：teylnol_evteyl (赞：1)

这道题可以猜想，最优策略是先执行所有填 AND 的边，再执行所有填 OR 的边。也就是说，可以使最终点权为 $1$，当且仅当由填 AND 的边组成的图中，存在一个点权全部为 $1$ 的连通块。下面证明这个结论的正确性：

- 充分性：按照刚才的策略，执行所有填 AND 的边之后，至少有一个点的点权为 $1$，所以执行填 OR 的边之后剩下的点点权为 $1$。
- 必要性：可以归纳证明如果由填 AND 的边组成的图中，不存在一个点权全部为 $1$ 的连通块，则最终点的点权必定为 $0$：
  - 若只有一个点，则这个点点权为 $0$。
  - 若有超过一个点，执行填 AND 的边，当这条边连接的点点权有 $0$，则执行后由填 AND 的边组成的图中所在连通块内仍然有 $0$；当这条边连接的点点权都为 $1$，由于由填 AND 的边组成的图中所在连通块内点的点权不全是 $1$，则仍然有点权为 $0$ 的点。综上，执行操作后的图点数减 $1$ 而仍满足此性质。
  - 若有超过一个点，执行填 OR 的边，当这条边连接的点点权都是 $0$，则执行后由填 OR 的边组成的图中所在连通块内仍然有 $0$；当这条边连接的点点权都有 $1$，则其中一个点权为 $1$ 的连通块内有 $0$，执行这条边后两个连通块合并为一个连通块且有点点权为 $0$。综上，执行操作后的图点数减 $1$ 而仍满足此性质。
  
然后可以根据这个结论设计 DP 方程，设 $f_{u,0/1/2}$ 表示对于 $u$ 的子树由填 AND 的边组成的图中，没有点权全为 $1$ 的连通块、$u$ 所在连通块点权全为 $1$ 且其它连通块不是、存在连通块点权全为 $1$ 且不包含点 $u$ 的方案数。初值 $f_{u,0}=f_{u,1}=1,f_{u,2}=0$，对于子树 $u$ 加入一个子树 $v$。容易推出转移方程，具体见代码。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 1e5 + 5, P = 998244353;

int n;
int la[N], ne[N * 2], en[N * 2], idx;
LL f[N][3], g[3];

void add(int a, int b)
{
	ne[ ++ idx] = la[a];
	la[a] = idx;
	en[idx] = b;
}
void dfs(int u, int fa)
{
	f[u][1] = f[u][2] = 1;
	for(int i = la[u]; i; i = ne[i])
	{
		int v = en[i];
		if(v != fa)
		{
			dfs(v, u);
			g[0] = g[1] = g[2] = 0;
			g[0] = (g[0] + f[u][0] * f[v][0]) % P;
			g[0] = (g[0] + f[u][0] * f[v][0]) % P;
			g[0] = (g[0] + f[u][0] * f[v][1]) % P;
			g[0] = (g[0] + f[u][0] * f[v][1]) % P;
			g[0] = (g[0] + f[u][0] * f[v][2]) % P;
			g[0] = (g[0] + f[u][0] * f[v][2]) % P;
			g[0] = (g[0] + f[u][1] * f[v][0]) % P;
			g[0] = (g[0] + f[u][1] * f[v][0]) % P;
			g[0] = (g[0] + f[u][1] * f[v][1]) % P;
			g[1] = (g[1] + f[u][1] * f[v][1]) % P;
			g[1] = (g[1] + f[u][1] * f[v][2]) % P;
			g[2] = (g[2] + f[u][1] * f[v][2]) % P;
			g[0] = (g[0] + f[u][2] * f[v][0]) % P;
			g[0] = (g[0] + f[u][2] * f[v][0]) % P;
			g[0] = (g[0] + f[u][2] * f[v][1]) % P;
			g[2] = (g[2] + f[u][2] * f[v][1]) % P;
			g[2] = (g[2] + f[u][2] * f[v][2]) % P;
			g[2] = (g[2] + f[u][2] * f[v][2]) % P;
			f[u][0] = g[0], f[u][1] = g[1], f[u][2] = g[2];
		}
	}
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; i ++ )
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b), add(b, a);
	}
	dfs(1, 0);
	printf("%lld\n", (f[1][0] + f[1][1]) % P);
	return 0;
}
```


---

## 作者：翼德天尊 (赞：1)

首先显然一眼树形 dp。

这种复杂些的树形计数 dp 可以考虑先思考下合法方案的性质。

考虑对于一种方案，按照什么顺序缩边才能使其尽可能满足最终点权为 $1$ 呢？

可以发现，对于 `&1` 的节点和 `|0` 的节点，是毫无用处的；对于 `&0` 的节点，我们应该尽可能将其往前放；对于 `|1` 的节点，我们应该尽可能将其往后放。

所以就有如下贪心方式：先将所有 `&` 边形成的连通块缩边，此时剩下的所有边皆为 `|`，然后判断是否有某一个连通块值为 $1$ 即可。

所以使用树形 dp 计数的时候也可以使用类似的方式进行计数。显然，我们会注意两点：当前 `&` 连通块的值，以及子树内是否有值为 `1` 的连通块。

于是不妨设 $dp_{u,0/1,0/1}$ 表示这个，然后跑树形背包进行转移即可。总时间复杂度 $O(n)$。

转移方程很长，有些细节，如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/x32tjjg4.png)

---

## 作者：demonlover923 (赞：1)

特判 $n=1$ .

考虑确定权值之后怎么判定是否合法.

考虑一个度为 $1$ 的点, 对其分类讨论:

$1 \lor$ , 显然只要最后选这条边即可.

$1 \land$ 或 $0 \lor$ , 显然这种边没意义, 可以直接选.

$0 \land$ , 将最终结果变成 $0$ , 显然不如直接将初始值变为 $0$ , 所以也可以直接选.

综上, 有以下策略, 若存在 $1 \lor$ 的边一定合法, 否则不断选度数为 $1$ 的边即可.

然后就可以 $dp$ 了, 令 $f_{x,0/1/2}$ 表示以 $x$ 为根的子树中, 最终的权值为 $0/1$ , 且为出现 $1 \lor$ 的方案数, 和出现 $1 \lor$ 的方案数.
$$
\begin{cases}
f_{x,0} = f_{x,0}(2f_{son,0}+f_{son,1})+f_{x,1}f_{son,0} \\
f_{x,1} = f_{x,1}(f_{son,0}+f_{son,1}) \\
f_{x,2} = (f_{x,0}+f_{x,1})(f_{son,1}+2f_{son,2})+2f_{x,2}(f_{son,0}+f_{son,1}+f_{son,2})
\end{cases}
$$
初始状态为 $f_{x,0} = f_{x,1} = 1$ .

```cpp
/************************************************
*Author        :  demonlover
*Created Time  :  2022.01.15.15:58
*Problem       :  ARC121F
************************************************/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
typedef pair <int,int> pii;
#define DEBUG(x) cout << #x << " = " << x << "\n"
template <typename T>
inline bool read(T &x) {
	int f = 1,c = getchar();x = 0;
	while (!isdigit(c)) {if (c == 45)f = -1;c = getchar();}
	while (isdigit(c))x = (x<<3)+(x<<1)+(c^48),c = getchar();
	return x *= f,true;
}
template <typename T,typename... Args>
inline bool read(T &x,Args &...args) {
	return read(x) && read(args...);
}

namespace run {
	const int maxn = 1e5+10;
	const int mod = 998244353;
	struct Edge {int nxt,to;}edge[maxn<<1];
	int begn[maxn],e;
	inline void add(int x,int y) {
		edge[++e] = (Edge){begn[x],y};begn[x] = e;
		return;
	}
	int f[maxn][3],g[maxn];
	inline void dfs(int x,int fa) {
		f[x][0] = f[x][1] = 1;
		for (int i = begn[x];i;i = edge[i].nxt) {
			int y = edge[i].to;
			if (y ^ fa) {
				dfs(y,x);
				memcpy(g,f[x],sizeof(g));
				f[x][0] = (1ll*g[0]*((2ll*f[y][0]%mod+f[y][1])%mod)%mod+1ll*g[1]*f[y][0]%mod)%mod;
				f[x][1] = 1ll*g[1]*((f[y][0]+f[y][1])%mod)%mod;
				f[x][2] = (1ll*(g[0]+g[1])%mod*((f[y][1]+2ll*f[y][2]%mod)%mod)%mod+2ll*g[2]*(((f[y][0]+f[y][1])%mod+f[y][2])%mod)%mod)%mod;
			}
		}
		return;
	}
	int n;
	inline bool main() {
		read(n);
		for (int i = 1,x,y;i < n;++i)read(x,y),add(x,y),add(y,x);
		dfs(1,0);
		printf("%d\n",(f[1][1]+f[1][2])%mod);
		return 0;
	}
}

int main() {
#ifdef demonlover
	freopen("ARC121F.in","r",stdin);
	freopen("ARC121F.out","w",stdout);
#endif
	return run :: main();
}
```

---

## 作者：TLEWA (赞：0)

and 操作和 or 操作混杂的情况似乎很不好计数。怎么办？

注意到我们的操作序列取一段连续 and 后面一段连续 or 的操作方法显然是最优的，这启示我们将两个操作分开考虑，我们不妨先将 or 边断开，此时树变为森林，对于每一个联通块，赋点权后操作的值都是唯一确定的。由或运算的性质我们知道仅当至少一个连通块的值为 1 时，最终操作结果为一，此时问题转化为：

选择任意条边将一棵树断为若干连通块，给每个节点填上 $0$ 或 $1$，对至少一个连通块点权全为 $1$ 的填法计数。

这个东西很不好计算，考虑反向。计算所有连通块取值均为 $0$ 的个数，这个就很好算了。设 $dp_{i,0/1}$ 表示以 $i$ 的子树中除 $i$ 所在联通块以外取值均为 $0$ 的方案数，而且 $i$ 所在连通块取值目前为 $0/1$，分别讨论当前节点到子树的边为 and，or 的情况的贡献，最终转移为：

$$$dp_{u,0} = 2dp_{u,0} \times dp_{v,0} + dp_{u,0} \times dp_{v,1} + dp_{u,1} \times dp_{v,0}$$$

$$$dp_{u,1} = dp_{u,1} \times dp_{v,0} + dp_{u,1} \times dp_{v,1}$$$

转移即可，最终答案即为 $2^{2n-1}-dp_{1,0}$。

## AC 代码


```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N=100005,mod=998244353;

int n;

vector<int> vec[N];

int qmod(int n,int k) {
	if(k==0) return bool(n);
	if(k==1) return n;
	if(k&1) return n*qmod(n*n%mod,k/2)%mod;
	else return qmod(n*n%mod,k/2);
}

int dp[N][2];

void dfs(int u,int fa) {
	dp[u][0]=dp[u][1]=1;
	for(auto v:vec[u]) {
		if(v==fa) continue;
		dfs(v,u);
		int a=(2*dp[u][0]*dp[v][0]+dp[u][1]*dp[v][0]+dp[u][0]*dp[v][1])%mod;
		int b=(dp[u][1]*dp[v][0]+dp[u][1]*dp[v][1])%mod;
		dp[u][0]=a,dp[u][1]=b;
	}
}

signed main() {
	cin >> n;
	
	int u,v;
	for(int i=1;i<n;++i) {
		cin >> u >> v;
		vec[u].push_back(v);
		vec[v].push_back(u); 
	}
	
	dfs(1,0);
	
	cout << (qmod(2,2*n-1)-dp[1][0]+mod)%mod;
	
	return 0;
}

```

---

## 作者：Natori (赞：0)

>[ARC121F Logical Operations on Tree](https://www.luogu.com.cn/problem/AT_arc121_f)

很好的思维题哇！

------------

>要学会计数，先要学会判断是否合法。

直觉上，比较好的策略应该是先缩所有的 AND 边，再缩 OR 边。感性证明一下：如果先缩了一些 OR 边，那么得到的一些 $1$ 点可能会被 AND 边“覆盖”成 $0$，所以先缩 AND 边是更优的。

进一步地，我们考虑存在合法方案的充要条件。不妨将所有 AND 边当成真实存在的边，OR 边直接忽略，那么这棵树就变成了一个森林，森林中的每棵树由 AND 边相连。每棵树缩出来的权值为 $1$，当且仅当树中所有点的权值都为 $1$。而全局缩出来的权值为 $1$，当且仅当存在一个连通块，使得其中所有点的权值都为 $1$。

注意到存在合法方案需要“存在”一个连通块满足某种限制，这样是不好做的。于是正难反易，考虑求出没有连通块满足限制的方案数。相当于所有连通块中都至少存在一个 $0$。

考虑 DP，设 $dp_{u,0/1}$ 表示在原树上 $u$ 的子树中划分连通块，$u$ 所在连通块为 $0/1$ 的方案数。枚举子节点 $v$ 表示考虑边 $(u,v)$ 是否断开。

具体地：

- 若当前边为 AND：

$dp_{u,0}\leftarrow dp_{u,0}\times dp_{v,0}+dp_{u,1}\times dp_{v,0}+dp_{u,0}\times dp_{v,1}$

$dp_{u,1}\leftarrow dp_{u,1}\times dp_{v,1}$

- 若当前边为 OR，那么必须连边（即 $dp_{v,1}$ 没有贡献），否则会存在合法方案：

$dp_{u,0}\leftarrow dp_{u,0}\times dp_{v,0}$

$dp_{u,1}\leftarrow dp_{u,1}\times dp_{v,0}$

转移方程合并即可得到最终方程。这个转移相当于背包合并，所以要用临时变量存计算出来的值。时间复杂度 $\mathcal{O}(n)$。

关于卡常：转移时如果全部先取模再相加是比较慢的，可以开 ```long long``` 然后全部加在一起再取模。~~这样居然卡到了最优解前五。~~

---

## 作者：Unnamed114514 (赞：0)

首先相同运算之间是无序的。

显然先算 `AND`，然后再算 `OR`，因为你 `AND` 会消耗 $1$ 而 `OR` 不会，`OR` 合并完之后 `AND` 消耗的 $1$ 会更多。

其实你举个例子这就很清楚了：`1 OR 0 AND 0`，先 `OR` 是 $0$，先 `AND` 是 $1$。

所以把 `AND` 缩成若干个块，只要有一个块为 $1$ 就行了。

这样不是很好算，考虑算 `AND` 块全 $0$ 的情况。

因为只有一个连通块要向上合并，所以其它连通块要求都是 $0$，故只需要记录子树的根所在的连通块当前的值就行了。

因此定义 $f_{u,0/1}$ 表示 $u$ 为根的子树，$u$ 所在连通块当前值为 $0/1$ 的方案数。

儿子 $v$ 转移到 $u$ 的时候只需要讨论它是否被 `AND` 连着即可。

---

