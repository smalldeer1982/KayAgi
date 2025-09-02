# [USACO21OPEN] Routing Schemes P

## 题目描述

考虑一个由 $N$ 个编号为 $1\dots N$ 的结点组成的网络。每个结点被指定为发送者（sender）、接收者（receiver）或两者均不是。发送者的数量 $S$ 与接收者的数量相等（$S≥1$）。

这一网络中结点间的连接关系可以用一系列形式为 $i→j$
的有向边表示，代表由结点 $i$ 可以路由到结点 $j$。有趣的是，所有的边满足性质 $i<j$，除了 $K$ 条满足 $i>j$（$0≤K≤2$）。网络中没有自环（$i→i$ 形式的边）。

一个「**路由方案**」的描述由 $S$ 条从发送者到接收者的有向路径组成，其中没有两条路径有相同的起止点。也就是说，这些路径将不同的发送者连接到不同的接收者。一条从发送者 $s$ 到接收者 $r$ 的路径可以用一个结点序列
$s=v_0→v_1→v_2→⋯→v_e=r$ 表示，其中对于所有 $0≤i<e$，有向边 $v_i→v_{i+1}$ 均存在。一个结点可能在同一条路径中出现多于一次。

计算使得每条有向边恰好使用一次的路由方案数量。由于答案可能非常大，输出答案对 $10^9+7$ 取模的结果。输入保证存在至少一种路由方案符合条件。

每个输入包含 $T$ 组需要独立求解的测试用例。

## 说明/提示

#### 样例一解释

对于第一个测试用例，网络中的边为 $1→3,2→3,3→4,3→5,4→6,5→6,6→7,6→8$ 。

有四种可能的路由方案：

- $1→3→4→6→7,2→3→5→6→8$
- $1→3→5→6→7,2→3→4→6→8$
- $1→3→4→6→8,2→3→5→6→7$
- $1→3→5→6→8,2→3→4→6→7$

对于第二个测试用例，网络中的边为 $1→4,2→4,3→4,4→5,4→6,4→7,8→10,9→10,10→11,11→12$。

一种可能的路由方案由如下路径组成：

- $1→4→5$
- $2→4→7$
- $3→4→6$
- $8→10→12$
- $9→10→11$

总的来说，发送者 ${1,2,3}$
可以路由到接收者 ${5,6,7}$ 的某个排列，发送者 ${8,9}$ 可以路由到接收者 ${11,12}$ 的某个排列，得出答案为 $6\times 2=12$。 

#### 样例二解释

对于第一个测试用例，网络中的边为 $1→3,1→5,2→3,3→1,3→4$ 。

有三种可能的路由方案：

- $1→3→1→5,2→3→4$
- $1→3→4,2→3→1→5$
- $1→5,2→3→1→3→4$

对于第二个测试用例，网络中的边为 $1→3,2→4,3→2,3→6,4→5,5→3$。

只有一种可能的路由方案：$1→3→2→4→5→3→6$
。 

#### 数据范围和约定

$2\le N\le 100$，$1\le T\le 20$ , $\sum N^2\le 2\times 10^4$。

## 样例 #1

### 输入

```
2

8 0
SS....RR
00100000
00100000
00011000
00000100
00000100
00000011
00000000
00000000

13 0
SSS.RRRSS.RR.
0001000000000
0001000000000
0001000000000
0000111000000
0000000000000
0000000000000
0000000000000
0000000001000
0000000001000
0000000000110
0000000000000
0000000000000
0000000000000```

### 输出

```
4
12```

## 样例 #2

### 输入

```
2

5 1
SS.RR
00101
00100
10010
00000
00000

6 2
S....R
001000
000100
010001
000010
001000
000000```

### 输出

```
3
1```

## 样例 #3

### 输入

```
5

3 2
RS.
010
101
100

4 2
.R.S
0100
0010
1000
0100

4 2
.SR.
0000
0011
0100
0010

5 2
.SSRR
01000
10101
01010
00000
00000

6 2
SS..RR
001010
000010
000010
000010
100101
000000```

### 输出

```
2
1
2
6
24```

# 题解

## 作者：Amidst (赞：9)

## 思路

很容易想到欧拉回路。

我们考虑增加一个超级源点 $C$，将 $C$ 与所有起点之间连一条有向边，再增加一个超级汇点 $D$，将所有终点与 $D$ 之间连一条有向边，$D$ 和 $C$ 之间再连边，就变成了一个有向图欧拉回路计数问题。

于是考虑 BEST 定理。

### BEST 定理

设 $G$ 为有向欧拉图，$k$ 为任意顶点，则 $G$ 的不同欧拉回路个数

$$\operatorname{euc}(G)=t^{\mathrm{in}}(G,k)\prod\limits_{v\in V}(\deg(v)-1)!$$

BEST 定理表明，对于 $\forall k,k'\in V_G$，都有 $t^{\mathrm{in}}(G,k)=t^{\mathrm{in}}(G,k')$。

### 证明

考虑图 $G$ 的任意一棵内向树，对于每个节点 $u$，我们给以 $u$ 为起点的所有**不在**内向树上的 $\deg(u)-1$ 条**出边**一个顺序，称这个根向树及这个出边的排列顺序为一个组合。

于是我们只需要证明组合和欧拉回路一一对应。

考虑从根节点开始，每到达一个节点，若不在内向树上的出边都被走过了，就沿着根向树上的边走向其父亲，否则就按照出边的排列顺序走向下一个节点。

注意到这样只会经过每个节点至多一次，现在证明这样会**经过且仅经过每个节点一次**。

不妨设到达节点 $u$ 后无法移动，考虑分类讨论。

若 $u$ 不是根节点，我们经过 $u$ 时会经过其一条入边和一条出边，而无法移动说明只经过了 $u$ 的一条入边，说明 $\deg^{\mathrm{in}}(u)=\deg^{\mathrm{out}}(u)+1$，与 $G$ 为欧拉图矛盾。

这样我们就证明了这种方案一定会形成一个欧拉回路。

现在我们证明了一个组合对应一个欧拉回路，接下来考虑证明一个欧拉回路对应一个组合。

记 $e_u$ 为 $u$ 最后访问的入边，下面证明所有 $e_u$ 构成一棵内向树。

不妨设 $e_u$ 构成的图中有环，首先根节点必然不会出现在环上。现在环上找出任意一个节点 $u$，容易发现 $u$ 沿着环的方向可以再次回到 $u$。由于原图是欧拉图，$\deg^{\mathrm{in}}(u)=\deg^{\mathrm{out}}(u)$，而 $u$ 在环上回到 $u$ 会导致 $\deg^{\mathrm{in}}(u)=\deg^{\mathrm{out}}(u)+1$，矛盾，故所有 $e_u$ 构成树。

于是一个组合和一个欧拉回路**一一对应**。

----

由上文我们知道

$$\operatorname{euc}(G)=t^{\mathrm{in}}(G,k)\prod\limits_{v\in V}(\deg(v)-1)!$$

在本题中即为

$$\operatorname{euc}(G)=t^{\mathrm{in}}(G,S_b)\deg(S_b)(\deg (S_b)-1)!(\deg(S_e)-1)!\prod\limits_{i=1}^{n}(\deg(i)-1)!$$

其中 $S_b$ 是超级源点，$S_e$ 是超级汇点。

但是仅仅套用 BEST 定理还不够。

而本题中由于我们建立了超级源点和超级汇点，与这两个点相连的边的决策带来的额外方案数不能被算入答案中，由排列的基本知识可以得到这样会令答案额外乘

$$\deg(S_b)!\deg(S_e)!$$

注意 $e=(S_b,S_e)$ 不计入两点度数。

于是有

$$\begin{aligned}ans(G)&=\frac{t^{\mathrm{in}}(G,S_b)\deg(S_b)(\deg (S_b)-1)!(\deg(S_e)-1)!\prod\limits_{i=1}^{n}(\deg(i)-1)!}{\deg(S_b)!\deg(S_e)!}\\&=\frac{t^{\mathrm{in}}(G,S_b)\prod\limits_{i=1}^{n}(\deg(i)-1)!}{\deg(S_e)}\end{aligned}$$

显然，$\deg(S_e)$ 即为给定的字符串中 `S` 的个数。

注意到题目描述中的一句话：**每条边使用恰好一次**，所以要删除孤立点后再计算。

## 代码

```cpp
#include <bits/stdc++.h>
//#include <bits/extc++.h>
#define int long long
#define mod (int)(1e9+7)
#define __MULTITEST__
//#undef __MULTITEST__
using namespace std;
//using namespace __gnu_cxx;
//using namespace __gnu_pbds;
int a[105][105];
string s[105];
int ind[105],oud[105],iid[105];
int cntiid;
int quick_pow(int a,int b,int p)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=ret*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ret;
}
void updeg(int u,int v)
{
	ind[v]++;
	oud[u]++;
}
void upcon(int u,int v)
{
	u=iid[u];
	v=iid[v];
	a[u][v]=(a[u][v]+mod-1)%mod;
	a[v][v]=(a[v][v]+1)%mod;
}
int det(int n)
{
	int ans=1,f=1;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			while(a[i][i])
			{
				int tmp=a[j][i]/a[i][i];
				for(int k=i;k<=n;k++)
					a[j][k]=(a[j][k]-a[i][k]*tmp%mod+mod)%mod;
				for(int k=1;k<=n;k++)
					swap(a[i][k],a[j][k]);
				f=-f;
			}
			for(int k=1;k<=n;k++)
				swap(a[i][k],a[j][k]);
			f=-f; 
		}
	for(int i=1;i<=n;i++)
		if(a[i][i])
			ans=ans*a[i][i]%mod;
	return (ans*f%mod+mod)%mod; 
}
int n,k,ans;
int fac[305];
signed main()
{
	fac[0]=1;
	for(int i=1;i<=300;i++)
		fac[i]=fac[i-1]*i%mod; 
	#ifdef __MULTITEST__
	signed T;
	scanf("%d",&T);
	while(T--)
	{
	#endif
		memset(ind,0,sizeof ind);
		memset(oud,0,sizeof oud);
		memset(iid,0,sizeof iid);
		memset(a,0,sizeof a);
		cntiid=0;
		scanf("%lld%lld",&n,&k);
		string st;
		cin>>st;
		st='#'+st;
		for(int i=1;i<=n;i++)
		{
			if(st[i]=='S')
			{
				updeg(n+1,i);
				updeg(n+2,n+1);
			}
			if(st[i]=='R')
				updeg(i,n+2);
		}
		for(int i=1;i<=n;i++)
		{
			cin>>s[i];
			s[i]='#'+s[i];
			for(int j=1;j<=n;j++)
				if(s[i][j]=='1')
					updeg(i,j);
		}
		for(int i=1;i<=n+2;i++)
			if(ind[i]!=oud[i])
			{
				printf("0\n");
				goto label;
			}
		for(int i=1;i<=n+2;i++)
			if(i!=n+1&&ind[i])
				iid[i]=++cntiid;
		for(int i=1;i<=n;i++)
		{
			if(st[i]=='S')
			{
				upcon(n+1,i);
				upcon(n+2,n+1);
			}
			if(st[i]=='R')
				upcon(i,n+2);
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(s[i][j]=='1')
					upcon(i,j);
		ans=det(cntiid);
		for(int i=1;i<=n;i++)
			if(oud[i])
				ans=(ans*fac[oud[i]-1]%mod+mod)%mod;
		ans=ans*quick_pow(oud[n+1],mod-2,mod)%mod;
		printf("%lld\n",ans);
		label:
			;
	#ifdef __MULTITEST__
	}
	#endif
	return 0;
}
```

---

## 作者：APJifengc (赞：8)

怎么大量高级做法，我来发个利用 $k \le 2$ 的初等做法。

首先考虑 $k=0$，由于题目保证了有解，那么实际上我们只需要将每个节点的入度与出度配个对就行了，容易发现每一种配对一定都对应着一种解，由于这是个 DAG 所以不可能配出环，所以答案就是每个点的度数的阶乘的乘积（对于起始点与终点其度数为入度出度的最大值）。

考虑 $k=1$，上述算法实际上会多算一些情况，发现这些情况实际上就是出现了环的情况，当一条反边与一条路径匹配成一个环时，这些路径是不会被经过的，所以这种情况是不合法的，我们需要把这些情况去掉。这是很容易的，设反边为 $x \gets y$，我们可以直接 DP 求出 $x \to y$ 的路径数。当然求路径数是不行的，因为实际的贡献不是路径数而是节点的阶乘，于是我们改成每个点的权值为 $\frac{1}{deg_i}$，然后求出 $x \to y$ 所有路径的权值即可。直接 DP 复杂度为 $O(n^2)$。

考虑 $k=2$，实际上也就是多了几种情况而已，设两条边分别为 $p: a \gets b, q : c \gets d$，那么也就是下列几种情况：$p$ 单独成环，$q$ 单独成环，$p,q$ 均单独成环，$p,q$ 在同一个环。前两种情况会把第三种情况计重一次，所以第三种情况需要加上。现在问题在于如何求两条路径的方案数。

乍一看把两条路径的情况乘起来就行了，但是两条路径可能存在交叉的部分，而这些部分的贡献不再是 $\frac{1}{deg_i^2}$ 而是 $\frac{1}{deg_i(deg_i - 1)}$。考虑改成一个二维 DP，求 $f_{i, j}$ 表示当前第一条路径走到 $i$，第二条路径走到 $j$ 的权值数。为了防止同一对路径算重，我们每次让较小的一个点移动。这样的好处还有如果路径上出现了重合点，那么路径中一定存在一个 DP 状态的 $i,j$ 相同，这样我们也容易将重合点的贡献给修正掉了。这样复杂度为 $O(n^3)$，然后就做完了。总复杂度 $O(Tn^3)$。

代码有点长是因为 DP 部分复制了五遍，实际代码极短。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105, P = 1000000007;
int T, n;
char s[MAXN], e[MAXN][MAXN];
int fac[MAXN], inv[MAXN], Inv[MAXN];
int qpow(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % P;
        a = 1ll * a * a % P;
        b >>= 1;
    }
    return ans;
}
void init(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % P;
    inv[n] = qpow(fac[n], P - 2);
    for (int i = n; i >= 1; i--) inv[i - 1] = 1ll * inv[i] * i % P;
    assert(inv[0] == 1);
    for (int i = 1; i <= n; i++) Inv[i] = 1ll * inv[i] * fac[i - 1] % P;
}
int deg[MAXN];
int ans;
int f[MAXN];
void solve1(pair<int, int> p) {
    for (int i = 1; i <= n; i++) f[i] = 0;
    auto [y, x] = p;
    f[x] = Inv[deg[x]];
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) if (e[i][j] == '1') {
            f[j] = (f[j] + 1ll * f[i] * Inv[deg[j]]) % P;
        }
    }
    ans = 1ll * ans * (1 - f[y] + P) % P;
}
int g[MAXN][MAXN];
void solve2(pair<int, int> p, pair<int, int> q) {
    if (p.second > q.second) swap(p, q);
    auto [b, a] = p;
    auto [d, c] = q;
    int tmp = 1;
    {
        for (int i = 1; i <= n; i++) f[i] = 0;
        f[a] = Inv[deg[a]];
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) if (e[i][j] == '1') {
                f[j] = (f[j] + 1ll * f[i] * Inv[deg[j]]) % P;
            }
        }
        tmp = (tmp - f[b] + P) % P;
    }
    {
        for (int i = 1; i <= n; i++) f[i] = 0;
        f[c] = Inv[deg[c]];
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) if (e[i][j] == '1') {
                f[j] = (f[j] + 1ll * f[i] * Inv[deg[j]]) % P;
            }
        }
        tmp = (tmp - f[d] + P) % P;
    }
    {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                g[i][j] = 0;
            }
        }
        g[a][c] = 1ll * Inv[deg[a]] * (a == c ? Inv[deg[a] - 1] : Inv[deg[c]]) % P;
        for (int i = a; i <= b; i++) {
            for (int j = c; j <= d; j++) {
                if (i != b && (j == d || i <= j)) {
                    for (int k = i + 1; k <= b; k++) if (e[i][k] == '1') {
                        g[k][j] = (g[k][j] + 1ll * g[i][j] * (k == j ? Inv[deg[k] - 1] : Inv[deg[k]])) % P;
                    }
                } else {
                    for (int k = j + 1; k <= d; k++) if (e[j][k] == '1') {
                        g[i][k] = (g[i][k] + 1ll * g[i][j] * (k == i ? Inv[deg[k] - 1] : Inv[deg[k]])) % P;
                    }
                }
            }
        }
        tmp = (tmp + g[b][d]) % P;
    }
    {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                g[i][j] = 0;
            }
        }
        g[a][c] = 1ll * Inv[deg[a]] * (a == c ? Inv[deg[a] - 1] : Inv[deg[c]]) % P;
        for (int i = a; i <= d; i++) {
            for (int j = c; j <= b; j++) {
                if (i != d && (j == b || i <= j)) {
                    for (int k = i + 1; k <= d; k++) if (e[i][k] == '1') {
                        g[k][j] = (g[k][j] + 1ll * g[i][j] * (k == j ? Inv[deg[k] - 1] : Inv[deg[k]])) % P;
                    }
                } else {
                    for (int k = j + 1; k <= b; k++) if (e[j][k] == '1') {
                        g[i][k] = (g[i][k] + 1ll * g[i][j] * (k == i ? Inv[deg[k] - 1] : Inv[deg[k]])) % P;
                    }
                }
            }
        }
        tmp = (tmp - g[d][b] + P) % P;
    }
    ans = 1ll * ans * tmp % P;
}
int main() {
    init(101);
    scanf("%d", &T);
    while (T--) {
        scanf("%d%*d%s", &n, s + 1);
        for (int i = 1; i <= n; i++) scanf("%s", e[i] + 1);
        int k = 0;
        pair<int, int> p, q;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < i; j++) if (e[i][j] == '1') {
                if (k == 0) k++, p = { i, j };
                else k++, q = { i, j };
            }
        }
        for (int i = 1; i <= n; i++) deg[i] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) if (e[i][j] == '1') {
                deg[j]++;
            }
        }
        for (int i = 1; i <= n; i++) if (s[i] == 'S') deg[i]++;
        ans = 1;
        for (int i = 1; i <= n; i++) ans = 1ll * ans * fac[deg[i]] % P;
        if (k == 1) solve1(p);
        if (k == 2) solve2(p, q);
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：Time_tears (赞：8)

模拟赛考这个题发现可以很好建图搞欧拉回路。然后就发现不对呀，欧拉回路怎么做计数问题呢？然后就直接弃了，结果真是欧拉回路计数，用 BEST 定理（今天才会）就秒了，还是太年轻了。。。

这篇题解就会讲建图过程及 BEST 定理的简单证明。

我们先不考虑计数，考虑判断是否合法，考虑建一个超级点 $A$ ，从 $A$ 向所有 $S$ 点连边，从所有 $R$ 点向 $A$ 连边。那么只需判断是否有欧拉回路即可，也就是每个点的出度是否等于入度。

因为在欧拉回路中 $A$ 会经过 $|S|+1$ 次（回来算一次），每两次之间其实就对应了一条从 $S$ 到 $R$ 的路径，所以这样我们就只需要做欧拉回路计数即可。考场上我以为这是个不可做问题，直到发现了这个：

## BEST 定理

定理：设一个有向图 $G$ 欧拉回路的个数为 $F(G)$，一个图 $G$ 以 $root$ 为根的生成的内向树数量为 $Tree(G,root)$ 每个点的入度为 $deg_i$，则有：

$$F(G)=Tree(G,root) \prod\limits_{i=1}^{n}(deg_i-1)!$$

考虑证明双射。

1.每一个内向树都能对应 $\prod\limits_{i=1}^{n}(deg_i-1) !$ 条欧拉回路

证明：
考虑让每个内向树上的自己到父亲的边 $(x,fa)$ 作为每个点在欧拉回路上的最后一条出边，那么每个点在经过时前 $deg_i-1$ 条边时有 $(deg_i-1)!$ 种走法，为了确定这个回路，根节点必须要确定第一步走的是什么，不然一条回路会算 $deg_{root}$ 次，所以根节点也是只有 $(deg_i-1)!$ 种走法，所以每一个内向树都能对应 $\prod\limits_{i=1}^{n}(deg_i-1) !$ 条欧拉回路。

2.每一条欧拉回路都恰好被一棵内向树对应

考虑每个点的最后一条出边构成的图，若这个图不连通（即不是内向树），则会在不连通之前结束回路，此时最后一个到达的不是根节点，与欧拉回路的定义矛盾，所以每一条欧拉回路都恰好被一棵内向树对应。

于是我们就证明了 BEST 定理。

至于本题，直接按照上面建出的图跑内向树计数（Matrix-tree 应该都会吧），内向树随便选谁当根答案都一样，然后就乘上 $\prod\limits_{i=1}^{n}(deg_i-1) !$ 就完了，注意一下图上有孤立点，需要去掉这些点之后再跑矩阵树才对，不然答案一定是 $0$。

完结撒花～
```cpp
#include<bits/stdc++.h>
#define N 105
using namespace std;
const int mod=1e9+7;
int T,n,m,num,a[N][N],ans;
int b[N][N],dd[N],fac[N];
char s[N];
inline int Mod(int x) {return x<mod?x:x-mod;}
inline int Ksm(int a,int n,int ans=1) {for(; n; n>>=1,a=1ll*a*a%mod)if(n&1)ans=1ll*ans*a%mod;return ans;}
int Do(int n,int ans=1,int opt=1) {
	for(int i=1,now; i<=n; ++i) {
		now=0;for(int j=i; j<=n&&!now; ++j)if(b[j][i])now=j;
		if(now) {
			if(now!=i)opt=-opt,swap(b[now],b[i]);
			for(int j=i+1,tmp=Ksm(b[i][i],mod-2); j<=n; ++j)
				if(b[j][i])for(int tmpp=1ll*tmp*b[j][i]%mod,k=i; k<=n; ++k)b[j][k]=Mod(b[j][k]-1ll*b[i][k]*tmpp%mod+mod);
		}
	}
	for(int i=1; i<=n; ++i)ans=1ll*ans*b[i][i]%mod;
	return opt==1?ans:mod-ans;
}
int main() {
	scanf("%d",&T);
	for(int i=fac[0]=1; i<=100; ++i)fac[i]=1ll*fac[i-1]*i%mod;
	while(T--) {
		scanf("%d%d%s",&n,&m,s+1);
		for(int i=1; i<=n; ++i)for(int j=1; j<=n; ++j)a[i][j]=0;
		for(int i=1; i<=n; ++i)if(s[i]=='S')++a[i][i];
		for(int i=1; i<=n; ++i) {
			scanf("%s",s+1);
			for(int j=1; j<=n; ++j)if(j!=i&&s[j]=='1')a[i][j]=mod-1,++a[j][j];
		}
		num=0;for(int i=1; i<=n; ++i)if(a[i][i])dd[i]=++num;else dd[i]=0;
		for(int i=1; i<=num; ++i)for(int j=1; j<=num; ++j)b[i][j]=0;
		for(int i=1; i<=n; ++i)for(int j=1; j<=n; ++j)b[dd[i]][dd[j]]=a[i][j];ans=1;
		for(int i=1; i<=num; ++i)ans=1ll*ans*fac[b[i][i]-1]%mod;ans=1ll*ans*Do(num)%mod;cout<<ans<<"\n";
	}
	return 0;
}
```


---

## 作者：7KByte (赞：6)

给定一张有向图，和若干个起点和终点，求这用若干条起点到终点的路径将图中每个点不重不漏覆盖的方案数。起点和终点可以任意匹配。图是在$\rm DAG$ 的基础上增加最多 $k\le 2$ 条任意边。

首先这个模型看起来非常的网络流。

如果只是判断是否有解，可以建立超级源点和超级汇点，然后源点和起点连边，终点和汇点连边，跑最大流即可。

还有一个特殊的条件是每条边要恰好被覆盖一次，也就是说如果再从汇点流到源点，则一条起点到终点的路径将是一条回路，而这些回路将每条边都恰好覆盖一次，而又在源点和汇点处相交。

所以这些回路合并起来一定是原图的欧拉回路！

然后欧拉回路计数有一个神奇的定理 $\rm BEST$ 定理，OI wiki 上有介绍，所以这就转换为生成树计数，直接矩阵树定理即可。

这个$k\le 2$非常的迷惑，貌似是有奇奇怪怪的$\rm DP$做法。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 155
#define P 1000000007
#define int long long 
using namespace std;
int n,k,a[N][N],b[N][N],fac[N],v[N];char s[N];
void add(int x,int y){
	a[x][y]--;a[y][y]++;
}
int calc(){
	int ans=1;
	rep(i,1,n)rep(j,i+1,n)while(a[j][i]){
		int cur = a[i][i] / a[j][i];
		rep(k,i,n)(a[i][k] -= 1LL * cur * a[j][k] % P) %= P,swap(a[i][k],a[j][k]);
		ans*=-1;
	}
	rep(i,1,n)ans=1LL*ans*a[i][i]%P;
	//cout<<"ss "<<ans<<endl;
	return (ans+P)%P;
}
void solve(){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(v,0,sizeof(v));
	scanf("%lld%lld",&n,&k);
	scanf("%s",s+1);
	rep(i,1,n)if(s[i]=='S')add(n+1,i),v[n+1]=v[i]=1;else if(s[i]=='R')add(i,n+1),v[i]=v[n+1]=1;
	rep(i,1,n){
		scanf("%s",s+1);
		rep(j,1,n)if(s[j]=='1')add(i,j),v[i]=v[j]=1;
	}
	int cur = 1 , T = 0;
	rep(i,1,n)if(a[i][i])cur=1LL*cur*fac[a[i][i]-1]%P;
	rep(i,1,n)if(v[i]){
		++T;int res=0;
		rep(j,1,n)if(v[j]) b[T][++res]= a[i][j];
	}
	n=T;rep(i,1,n)rep(j,1,n)a[i][j]=b[i][j];
	//cout<<cur<<" "<<calc()<<endl;
	printf("%lld\n",1LL*cur*calc()%P);
}
signed main(){
	//freopen("6.in","r",stdin);
	fac[0]=1;rep(i,1,N-5)fac[i]=1LL*i*fac[i-1]%P;
	int T;scanf("%lld",&T);
	while(T--)solve();
	return 0;
} 
```

---

## 作者：_lbw_ (赞：5)

# 前言 

（可能是）全网首发 DP 做法！

不会 BEST 定理？用 BEST 定理但觉得这题没有挑战性？来看这篇题解！

# 做法

建立超级源汇，源 $\to S$，$R \to$ 汇，并称 $s>t$ 的边为回边。

### $K=0$

容易发现每个点入度等于出度，于是答案就是 $\prod du_i!$ 

### $K=1$

我们考虑枚举走回边的点 $x$，设回边为 $s\to t$，容易发现 $x$ 最后走到 $t$ 并且 $x$ 走到 $s$ 经过的点度数都要减 $1$。

于是设计 DP，$f_i$ 表示从 $i\to x$，$\prod du_i!$ 的和是多少。

转移乘上 $\dfrac{f_u}{du_v}\to f_v$。

时间复杂度：$\mathcal{O}(n^3)$

### $K=2$

困难的。

考虑枚举走回边的点 $x,y$，设回边为 $s_0\to t_0,s_1\to t_1$，我们发现最大的困难在于会有点被走两遍。

于是设计 DP，$f_{i,j}$ 含义类似上面，转移时分为两种情况：

- $i\not = j$，我们走 $i,j$ 中标号小的点，若走到 $j$ 则 $\dfrac{f_{i,j}}{du_j-1}\to f_{j,j}$，否则 $\dfrac{f_{i,j}}{du_v}\to f_{v,j}$。

- $i=j$，用上面的做法会出现走到同一条边的可能，于是我们同时枚举两条边。

当 $x=y$ 时可以看作从 $x,t_0$ 开始到 $s_0,s_1$。

但这样时间复杂度来到了 $n^6$，不过我们又发现这个其实是线性变换，于是所有 $x,y$ 的 $f$ 加在一起转移，时间复杂度 $\mathcal{O}(n^4)$，常数**极**小。

```
const int MAX = 2e2;
const int maxn = 2e2+5;
ll n,fac[maxn],ifac[maxn];
IV cadd(ll&x,ll val){x=(x+val)%cht;}
namespace Subtask0{
    const int maxn = 2e2+5;ll special_edge_u,special_edge_v;
    ll dp[maxn],lu[maxn],cu[maxn],ans;vector<ll>g[maxn];char s[maxn];

    IV solve(){
        scanf("%s",s+1);mem(lu,0);mem(cu,0);
        F(i,1,n)if(s[i]=='S')lu[i]++;else if(s[i]=='R')cu[i]++;
        F(i,1,n)F(j,1,n){
            ll x;scanf("%1lld",&x);
            if(x){
                lu[j]++;cu[i]++;if(i<j)g[i].push_back(j);
                else special_edge_u=i,special_edge_v=j;
            }
    
    
        }
        F(i,1,n)assert(lu[i]==cu[i]);
        ll origin_mul=1;


        F(i,1,n)origin_mul=origin_mul*fac[cu[i]]%cht;
        printf("%lld\n",origin_mul);
    }
} // namespace Subtask0
namespace Subtask1{
    const int maxn = 2e2+5;ll special_edge_u,special_edge_v;
    ll dp[maxn],lu[maxn],cu[maxn],ans;vector<ll>g[maxn];char s[maxn];
    IV solve(){
        scanf("%s",s+1);mem(lu,0);mem(cu,0);ans=0;
        F(i,1,n)if(s[i]=='S')lu[i]++;else if(s[i]=='R')cu[i]++;
        F(i,1,n){
            g[i].clear();
            F(j,1,n){
                ll x;scanf("%1lld",&x);
                if(x){
                    lu[j]++;cu[i]++;if(i<j)g[i].push_back(j);
                    else special_edge_u=i,special_edge_v=j;
                }
            }
        }
        F(i,1,n)assert(lu[i]==cu[i]);ll origin_mul=1;
        F(i,1,n)origin_mul=origin_mul*fac[cu[i]]%cht;mem(dp,0);
        F(x,1,n)if(s[x]=='S')dp[x]=origin_mul*ifac[cu[x]]%cht*fac[cu[x]-1]%cht;
        F(u,1,n)for(ll v:g[u])cadd(dp[v],dp[u]*ifac[cu[v]]%cht*fac[cu[v]-1]%cht);
        cadd(ans,dp[special_edge_u]);
        printf("%lld\n",ans);
    }
} // namespace Subtask1

namespace Subtask2{
    const int maxn = 2e2+5;ll special_edge_u[2],special_edge_v[2],tot;
    ll dp[maxn][maxn],lu[maxn],cu[maxn],ans,calc[maxn];vector<ll>g[maxn];char s[maxn];
    IV givet(ll x,ll y,ll v,bool cx,bool cy){
        assert(cx||cy);
        if(x==y){
            if(cx&&cy)
                 cadd(dp[x][y],v*ifac[cu[x]  ]%cht*(cu[x]>=2?fac[cu[x]-2]:0));
            else cadd(dp[x][y],v*ifac[cu[x]-1]%cht*(cu[x]>=2?fac[cu[x]-2]:0));
        }
        else{
            if(cx)v=v*ifac[cu[x]]%cht*fac[cu[x]-1]%cht;
            if(cy)v=v*ifac[cu[y]]%cht*fac[cu[y]-1]%cht;
            cadd(dp[x][y],v);
        }
    }
    IV solve(){
        scanf("%s",s+1);mem(lu,0);mem(cu,0);ans=0;tot=0;
        F(i,1,n)if(s[i]=='S')lu[i]++;else if(s[i]=='R')cu[i]++;
        F(i,1,n){
            g[i].clear();
            F(j,1,n){
                ll x;scanf("%1lld",&x);
                if(x){
                    lu[j]++;cu[i]++;if(i<j)g[i].push_back(j);
                    else special_edge_u[tot]=i,special_edge_v[tot++]=j;
                }
            }
        }
        F(i,1,n)assert(lu[i]==cu[i]);ll origin_mul=1;
        F(i,1,n)origin_mul=origin_mul*fac[cu[i]]%cht;
        F(k,0,1){
            mem(dp,0);
            F(x,1,n)if(s[x]=='S')givet(x,special_edge_v[k],origin_mul,1,1);
            F(u1,1,n)F(u2,1,n)if(dp[u1][u2]){
                if(u1<u2||u2==special_edge_u[!k])for(ll v1:g[u1])givet(v1,u2,dp[u1][u2],1,0);
                if(u1>u2||u1==special_edge_u[ k])for(ll v2:g[u2])givet(u1,v2,dp[u1][u2],0,1);
                if(u1==u2)for(ll v1:g[u1])for(ll v2:g[u2])if(v1^v2)givet(v1,v2,dp[u1][u2],1,1);
            }
            cadd(ans,dp[special_edge_u[k]][special_edge_u[!k]]);
        }
        mem(dp,0);
        F(x,1,n)F(y,1,n)if(s[x]=='S'&&s[y]=='S'&&x!=y)givet(x,y,origin_mul,1,1);
        F(u1,1,n)F(u2,1,n){
            if(u1==u2)for(ll v1:g[u1])for(ll v2:g[u2])if(v1^v2)givet(v1,v2,dp[u1][u2],1,1);
            if(u1>u2||u1==special_edge_u[0])for(ll v2:g[u2])givet(u1,v2,dp[u1][u2],0,1);
            if(u1<u2||u2==special_edge_u[1])for(ll v1:g[u1])givet(v1,u2,dp[u1][u2],1,0);
        }
        cadd(ans,dp[special_edge_u[0]][special_edge_u[1]]);
        printf("%lld\n",ans);
    }
} // namespace Subtask2
IV solve(){//
    n=read();ll k=read();
    if(k==0)return Subtask0::solve();
    if(k==1)return Subtask1::solve();
    if(k==2)return Subtask2::solve();
}  
I qpow(ll n,ll base=cht-2){
    ll ans=1;
    while(base){
        if(base&1)ans=ans*n%cht;
        n=n*n%cht;base>>=1;
    }
    return ans;
}
IV init(){
    fac[0]=1;F(i,1,MAX)fac[i]=fac[i-1]*i%cht;
    ifac[MAX]=qpow(fac[MAX]);D(i,MAX-1,0)ifac[i]=ifac[i+1]*(i+1)%cht;
}
int main(){
    // freopen("1.in","r",stdin);
    // freopen("1.out","w",stdout);
    init();
    ll T=read();while(T--)solve();return 0;
}
```













---

## 作者：tzc_wk (赞：4)

~~就这？也能放到 USACO Pt T2？~~

首先考虑怎样判断有无解，这显然是个网络流问题，对于每个 Sender 连一条源点到该点，容量为 1 的边，对于每个 Receiver 连一条该点到汇点，容量为 1 的边，对于原图中每条边连上下界均为 1 的边，然后跑网络流即可。

不过我们细想其实不需要网络流，注意到题目中有一个条件叫“每条边经过恰好一次”，看到这个条件我们很自然地想到欧拉回路，而又由于每个 Sender 都要发出消息，因此所有源点连出的、与汇点相连的边都要被经过恰好一次，但显然这个图不存在欧拉回路，因为源点的入度为 $0$，因此考虑再从汇点向源点连 $s$ 条边，然后判断是否存在欧拉回路即可，其中 $s$ 为 Sender 的个数，正确性显然。

接下来考虑怎样统计方案数，这显然可以转化为一个欧拉回路计数问题，考虑 BEST 定理（如果不知道什么是 BEST 定理可以点[这儿](https://www.cnblogs.com/ET2006/p/matrix-tree-best-theroem.html)），我们定根为源点 $S$ 用矩阵树定理求出根向生成树的个数 $C$，那么整张图欧拉回路的个数就是 $deg_S\times C\times\prod(deg_i-1)!$，但显然这并不是合法的方案数个数，因为所有与 $S$ 相连的边的访问顺序是不重要的，所有与 $T$ 相连的边的访问顺序也是不重要的，因此需除以 $(s!)^2$，而 $deg_S=deg_T=s$，$S$ 的贡献为 $(s-1)!\times s=s!$，$T$ 的贡献为 $(s-1)!$，除掉两个 $s!$ 就等价于将 $S,T$ 的贡献都抵消掉再除以 $s$。

因此方案数就是 $C\times\dfrac{1}{s}\prod\limits_{i=1}^n(deg_i-1)!$

时间复杂度 $Tn^3$

注意特判孤立点！

~~所以这个 $k\le 2$ 是来干嘛的……~~

```cpp
const int MAXN=100;
const int MOD=1e9+7;
int qpow(int x,int e){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;
	return ret;
}
int n,AAA,a[MAXN+5][MAXN+5],fac[MAXN+5];
char buf[MAXN+5],s[MAXN+5][MAXN+5];
int in[MAXN+5],out[MAXN+5],id[MAXN+5],idn;
void add1(int u,int v){in[v]++;out[u]++;}
void add2(int u,int v){
	u=id[u];v=id[v];
	a[u][v]=(a[u][v]+MOD-1)%MOD;
	a[u][u]=(a[u][u]+1)%MOD;
}
void clear(){
	memset(a,0,sizeof(a));
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(out));
	memset(id,0,sizeof(id));
	idn=0;
}
void solve(){
	scanf("%d%d%s",&n,&AAA,buf+1);clear();int cnt=0;
	for(int i=1;i<=n;i++){
		if(buf[i]=='S') add1(n+1,i),add1(n+2,n+1),cnt++;
		if(buf[i]=='R') add1(i,n+2);
	}
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=n;j++) if(s[i][j]=='1')
			add1(i,j);
	}
	for(int i=1;i<=n+2;i++) if(in[i]^out[i])
		return printf("0\n"),void();
	for(int i=1;i<=n+2;i++){
		if(i==n+1) continue;
		if(!in[i]) continue;
		id[i]=++idn;
	}
	for(int i=1;i<=n;i++){
		if(buf[i]=='S') add2(n+1,i),add2(n+2,n+1);
		if(buf[i]=='R') add2(i,n+2);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) if(s[i][j]=='1')
			add2(i,j);
	} int sgn=1;
	for(int i=1;i<=idn;i++){
		int t=i;
		for(int j=i+1;j<=idn;j++) if(a[j][i]) t=j;
		if(t^i) sgn=-sgn;
		for(int j=i;j<=idn;j++) swap(a[i][j],a[t][j]);
		int iv=qpow(a[i][i],MOD-2);
		for(int j=i+1;j<=idn;j++){
			int mul=1ll*(MOD-a[j][i])*iv%MOD;
			for(int k=i;k<=idn;k++) a[j][k]=(a[j][k]+1ll*a[i][k]*mul)%MOD;
		}
	} int res=(sgn+MOD)%MOD;
	for(int i=1;i<=idn;i++) res=1ll*res*a[i][i]%MOD;//printf("%d\n",res);
	for(int i=1;i<=n;i++) if(out[i]) res=1ll*res*fac[out[i]-1]%MOD;
	res=1ll*res*qpow(cnt,MOD-2)%MOD;printf("%d\n",res);
}
int main(){
	fac[0]=1;for(int i=1;i<=MAXN;i++) fac[i]=1ll*fac[i-1]*i%MOD;
	int qu;scanf("%d",&qu);while(qu--) solve();
	return 0;
}
```

---

## 作者：Anonymely (赞：2)

谔谔，为什么没有想到。

首先每条路径都要走一步，想到欧拉回路，再看到计数，想到 BEST 定理。

然后就做完了？需要将许多路径连通起来，开一个超级源点向 S 连边，T 向超级源点连边，然后是 BEST 定理板子，最后要除一个阶乘，因为第一步随便选本质相同。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define QwQ01AwA return 0
#define ll long long
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> void ckmax(T &x, T y) {x = max(x, y);}
template <typename T> void ckmin(T &x, T y) {x = min(x, y);}

const int N = 105;
const int mod = 1e9 + 7;
int n, w[N][N], in[N], out[N], fac[3200000], opt[N];
bool vis[N];
vector <int> e[N];
int cnt = 0;
void dfs(int u) {
    vis[u] = 1;
    for (auto v : e[u]) {
        cnt++;
        if (!vis[v]) dfs(v);
    }
}
int Gauss() {
    int ans = 1, op = 0;
    for (int i = 1; i < n; i++) {
        if (!vis[i]) continue;
        for (int j = i + 1; j < n; j++) {
            if (!vis[j]) continue;
            while (w[j][i]) {
                int xs = w[i][i] / w[j][i];
                for (int k = 1; k <= n; k++) {
                    w[i][k] = (w[i][k] - 1ll * xs * w[j][k] % mod + mod) % mod;
                    swap(w[j][k], w[i][k]);
                }
                op ^= 1;
            }
        }
        ans = 1ll * ans * w[i][i] % mod;
    }
    return op ? (mod - ans) % mod : ans;
}

void solve() {
	int sp;
    cin >> n >> sp;
    for (int i = 1; i <= n + 1; i++) {
        vis[i] = 0, out[i] = in[i] = opt[i] = 0;
        e[i].clear();
        for (int j = 1; j <= n + 1; j++) w[i][j] = 0;
    }
	string s; cin >> s; s = " " + s;
	for (int i = 1; i <= n; i++) {
		if (s[i] == 'S') opt[i] = 1;
		if (s[i] == 'R') opt[i] = -1;
	}
	auto add = [&](int u, int v) -> void {
		in[v]++, out[u]++, w[u][v] = (w[u][v] - 1 + mod) % mod, e[u].push_back(v);
	};
    int m = 0, mx = 0;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s; s = " " + s;
        for (int j = 1; j <= n; j++) {
			if (s[j] == '0') continue;
            add(i, j);
        }
    }
	for (int i = 1; i <= n; i++) {
		if (opt[i] == 1) add(n + 1, i);
		if (opt[i] == -1) add(i, n + 1);
	}
	n++;
	for (int i = 1; i <= n; i++) {
		w[i][i] = (w[i][i] + out[i]) % mod;
		ckmax(mx, out[i]);
        m += out[i];
	}
    for (int i = 1; i <= n; i++) {
        if (in[i] != out[i]) {
            cout << 0 << '\n';
            return ;
        }
    }
    cnt = 0;
    dfs(n);
    if (cnt != m) {
        cout << 0 << '\n';
        return ;
    }
    fac[0] = 1;
    for (int i = 1; i <= mx; i++) fac[i] = 1ll * fac[i - 1] * (i % mod) % mod;
    int ans = Gauss();
    for (int i = 1; i < n; i++) {
        if (!vis[i]) continue;
        ans = 1ll * ans * fac[out[i] - 1] % mod;
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
    QwQ01AwA;
}
```

---

## 作者：win114514 (赞：0)

best 定理居然还有运用范围。

### 思路

考虑如何来判断是否有解。

由于每一条边都需要用到。

但是它是使用很多条路径进行覆盖。

我们考虑一个很巧妙的转化。

建立一个超级源点，源点向每一条路径的开头连一条边。每一条路径的结尾向源点连一条边，这样一条路径就变成了一个回路。

把所有回路连起来，就是一条欧拉回路。

问题转化成了欧拉回路计数。

对于欧拉回路计数，我们有经典的 best 定理。

它描述的是这样一个东西。

$$
ans=内向树个数\times \prod (deg_i-1)!
$$

内向树个数容易使用矩阵树定理求出。

考虑这个题实际求的是匹配路径方案数。

所以要把源点的 $(deg_i-1)!$ 除掉。

时间复杂度：$O(Tn^3)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int n, k, ru[110], cu[110];
int f[110];
int a[110][110];

inline int power(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) res = 1ll * res * x % mod;
    x = 1ll * x * x % mod, y >>= 1;
  }
  return res;
}
inline int gauss() {
  int res = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (a[i][j] < 0) a[i][j] += mod;
  for (int i = 1; i <= n; i++) {
    if (ru[i] == 0 && cu[i] == 0) continue;
    int id = i;
    for (int j = i; j <= n; j++) if (a[j][i]) id = j;
    if (id != i) {
      swap(a[i], a[id]), res = mod - res;
    }
    int p = power(a[i][i], mod - 2);
    for (int j = i + 1; j <= n; j++) {
      int c = 1ll * a[j][i] * p % mod;
      for (int k = i; k <= n; k++) {
        a[j][k] = (a[j][k] - 1ll * a[i][k] * c) % mod;
        if (a[j][k] < 0) a[j][k] += mod;
      }
    }
  }
  for (int i = 1; i <= n; i++)
    if (ru[i] || cu[i]) res = 1ll * res * a[i][i] % mod;
  return res;
}
inline void solve() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    char c;
    cin >> c;
    if (c == 'S') a[0][i]--, a[0][0]++, cu[0]++, ru[i]++;
    if (c == 'R') a[i][0]--, a[i][i]++, cu[i]++, ru[0]++;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      char c;
      cin >> c;
      if (c == '1') {
        a[i][j]--;
        a[i][i]++;
        cu[i]++, ru[j]++;
      }
    }
  }
  bool flag = 0;
  for (int i = 0; i <= n; i++)
    if (ru[i] != cu[i]) flag = 1;
  if (flag == 0) {
    int ns = gauss();
    for (int i = 1; i <= n; i++)
      if (cu[i]) ns = 1ll * ns * f[cu[i] - 1] % mod;
    cout << ns << "\n";
  } else {
    cout << 0 << "\n";
  }
  memset(a, 0, sizeof a);
  memset(ru, 0, sizeof ru);
  memset(cu, 0, sizeof cu);
}

int main() {
  int t;
  cin >> t;
  f[0] = 1;
  for (int i = 1; i <= 100; i++) f[i] = 1ll * f[i - 1] * i % mod;
  while (t--) solve();
}
```

---

