# [AGC031F] Walk on Graph

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc031/tasks/agc031_f

$ N $ 頂点 $ M $ 辺の連結なグラフが与えられます．各頂点には $ 1,\ 2,...,N $ と番号がついています． $ i(1\ \leq\ i\ \leq\ M) $ 番目の辺は頂点 $ A_i $ と頂点 $ B_i $ を繋ぐ長さ $ C_i $ の無向辺です． また，奇数 $ MOD $ が与えられます．

$ Q $ 個のクエリが与えられるので，処理してください．クエリの形式は以下の通りです．

- $ i $ 番目のクエリでは，$ S_i,T_i,R_i $ が与えられる．頂点 $ S_i $ から頂点 $ T_i $ へ至る経路であって，長さを $ MOD $ で割った余りが $ R_i $ になるようなものが存在する場合は `YES` を，存在しない場合は `NO` を出力する．ただし同じ辺を複数回通っても，来た辺をすぐ戻ってもよい．

ただし，この問題においての経路の長さは辺の長さの単純な和**ではなく**，$ 1 $ 本目に使う辺の長さを $ 1 $ 倍，$ 2 $ 本目に使う辺の長さを $ 2 $ 倍，$ 3 $ 本目に使う辺の長さを $ 4 $ 倍，$ ... $ したものの和とします． (より厳密には，長さ $ L_1,...,L_k $ の辺をこの順に使ったとすると，その経路の長さは $ L_i\ \times\ 2^{i-1} $ の和です．)

## 说明/提示

### 制約

- $ 1\ \leq\ N,M,Q\ \leq\ 50000 $
- $ 3\ \leq\ MOD\ \leq\ 10^{6} $
- $ MOD $ は奇数
- $ 1\ \leq\ A_i,B_i\leq\ N $
- $ 0\ \leq\ C_i\ \leq\ MOD-1 $
- $ 1\ \leq\ S_i,T_i\ \leq\ N $
- $ 0\ \leq\ R_i\ \leq\ MOD-1 $
- 与えられるグラフは連結 (ただし自己辺や多重辺を含むことがある)

### Sample Explanation 1

各クエリに対する答えは以下のようになります． - $ 1 $ 番目のクエリ: 頂点 $ 1,2,3 $ の順に進むと経路の長さは $ 1\ \times\ 2^0\ +\ 2\ \times\ 2^1\ =\ 5 $ となり，長さを $ 2019 $ で割った余りが $ 5 $ になる経路は存在するので，答えは `YES` である． - $ 2 $ 番目のクエリ: どのように頂点 $ 1 $ から頂点 $ 3 $ まで進んでも経路の長さを $ 2019 $ で割った余りが $ 4 $ となることはないので，答えは `NO` である．

## 样例 #1

### 输入

```
3 2 2 2019
1 2 1
2 3 2
1 3 5
1 3 4```

### 输出

```
YES
NO```

## 样例 #2

### 输入

```
6 6 3 2019
1 2 4
2 3 4
3 4 4
4 5 4
5 6 4
6 1 4
2 6 1110
3 1 1111
4 5 1112```

### 输出

```
YES
NO
NO```

## 样例 #3

### 输入

```
1 2 3 25
1 1 1
1 1 2
1 1 13
1 1 6
1 1 14```

### 输出

```
YES
YES
YES```

## 样例 #4

### 输入

```
10 15 10 15
1 2 1
2 3 6
3 4 6
2 5 1
5 6 1
4 7 6
1 8 11
2 9 6
5 10 11
9 10 11
3 6 1
2 5 1
2 7 11
9 10 11
5 6 11
1 3 5
9 8 3
7 7 7
7 10 13
4 1 10
9 3 12
10 10 14
9 2 1
6 6 5
8 8 4```

### 输出

```
YES
NO
NO
NO
NO
NO
NO
YES
YES
NO```

# 题解

## 作者：_ReClouds_ (赞：11)

- 题意

给定一张 $n$ 个点 $m$ 条边的无向连通图，每条边存在边权 $w_i$。

存在 $q$ 组询问，每组询问给定 $s, t, r$，询问图中是否存在一条从 $s$ 到 $t$ 的权值为 $r$ 的路径（可以不是简单路径，即点和边都可以被经过任意多次）。

路径的权值定义为：设路径上依次经过边的边权为 $w_0, w_1, w_2 \cdots w_{k - 1}$，那么该路径的权值为 $\displaystyle (\sum_{i = 0}^{k - 1} w_i \cdot 2^i) \bmod p$。$p$ 给定。

$\mathcal{Data~Range}$：$1 \le n, m, q \le 5 \times 10^4, 1 \le p \le 10^6, p \equiv 1 \pmod{2}$。

------

- 题解

首先考虑如下问题：给定一条路径 $s \to t$，要求计算路径的权值。

这个问题朴素的算法是从 $s$ 开始沿着路径一直走，这样我们不得不时刻维护走过路径的长度，这并不是好的。

由于路径是双向的，我们不妨从 $t$ 开始反着走，这样每走一条边 $w_i$，权值就会由 $x$ 变为 $x \cdot 2 + w_i$，这样我们就不需要维护长度这一维信息了，这是极好的。

------

回到原问题。

我们不妨设一个二维状态 $(u, x)$ 表示走到 $u$ 且当前权值为 $x$，那么询问相当于求解 $(s, 0)$ 是否能够到达 $(t, r)$。

接下来我们深入分析此题的性质。

1. 假设 $(u, x)$ 能够到达 $(v, y)$，那么 $(v, y)$ 也能够到达 $(u, x)$。换言之，状态之间形成的是一个无向图。

证明：

任意找到一条 $u \to v$ 的路径，设路径长度为 $l$，权值为 $w_i$。

若初始状态为 $(u, x)$，那么走一次该路径后到达的状态即为 $(v, x \cdot 2^{l} + w_i)$。

走了 $t$ 次该条路径之后，路径的权值即为 $x \cdot 2^{t\cdot l} + w_i \cdot 2^l\cdot (2^{t} - 1)$。

由于 $p$ 为奇数，那么 $2^{\varphi(p)} \equiv 1 \pmod{p}$。也就是说，当 $t = \varphi(p) \cdot 2$ 时，我们仍然可以走回状态 $(u, x)$。

而 $\varphi(p) \cdot 2 > 1$，也就是说我们可以从状态 $(u, x)$ 走到 $(v, x \cdot 2^{l} + w_i)$，再从 $(v, x \cdot 2^{l} + w_i)$ 走回 $(u, x)$。

得证。 

下文用 $\Leftrightarrow$ 表示这种关系。

2. 假设图中存在两条边，边权分别为 $a, b$，那么 $(u, x) \Leftrightarrow (u, x + (a - b) \cdot 3)$。

证明：

首先，若存在两条边，边权为 $a, b$ 并与点 $u$ 相连，那么 $(u, x \cdot 4 + b \cdot 3) \Leftrightarrow (u, x) \Leftrightarrow(u , x \cdot 4 + a \cdot 3)$。

由于 $4$ 存在乘法逆元，所以我们可以考虑换元，即用 $x$ 代替 $x \cdot 4 + b \cdot 3$，那么可得 $(u, x) \Leftrightarrow (u, x + (a - b) \cdot 3)$。

考虑扩展这个性质。

假设存在两条边，边权为 $a, b$ 并与点 $v$ 相连，那么上述性质同样满足。

类似上文，我们考虑找出一条 $u \to v$ 的路径，长度为 $l$， 权值为 $w_i$，那么走 $t$ 次该路径后权值由 $x$ 变为 $x \cdot 2^{t \cdot l} + w_i \cdot (2^{t\cdot l} - 1)$。

我们接着在 $v$ 上走，令权值变为 $x \cdot 2^{t \cdot l} + w \cdot 2^l \cdot (2^{t } - 1) + (a - b) \cdot 3 \cdot 2^t$。那么当 $t = \varphi(p) \cdot 2$ 时，我们便走到了状态 $(u, x + (a - b) \cdot 3)$。

 接着扩展，我们假设点 $u$ 与点 $v$ 之间存在一条权值为 $b$ 的边，还分别存在一条权值为 $a, c$ 的边与点 $u, v$ 对应相连。

那么 $(u, x) \Leftrightarrow (u, x + (b - a) \cdot 3 + (c - b) \cdot 3)$，也即 $(u, x + (c - a) \cdot 3)$ 。

我们把两次扩展得出的结论相结合，稍加推导便能得出结论。

得证。

------

接下来，我们设 $\displaystyle g' = \gcd_{a, b~\in~\text{E}} (a - b), g = \gcd(g', p)$，那么由裴蜀定理可以得出：$(u, x) \Leftrightarrow (u, x + g \cdot 3)$，也即当 $x \equiv y \pmod{g \cdot 3}$ 时有 $(u, x) \Leftrightarrow (u, y)$。

结合性质 “$x \equiv y \pmod{p}$ 时有 $(u, x) \Leftrightarrow (u, y)$”，我们可以得出：$x \equiv y\pmod{\gcd(g \cdot 3, p)}$ 时有 $(u, x) \Leftrightarrow (u, y)$。

可以发现，我们完全可以用 $\gcd(g\cdot 3, p)$ 代替 $p$，那么下文的 $p$ 皆代表此。

这里有一个细节问题：$g'$ 要怎么计算？实际上，$g'$ 就等于 $\displaystyle \gcd_{i = 1}^m (w_i - w_1)$，证明可以考虑更相减损法，即 $\gcd(a, b) = \gcd(b, a - b)$。

------

考虑到有 $\forall a, b \in \text{E}, g \mid (a - b)$，那么 $a \equiv b \pmod{g}$。也就是说，每条边的边权都可以表示为 $g \cdot k + z$ 形式。

我们不妨把所有边减去 $z$，然后把所有状态的第二维默认加上 $z$。也即：
$$
(u, x)' = (u, x + z) \Leftrightarrow (v, (x + z) \cdot 2 + w_i - z)  = (v, x \cdot 2 + w_i + z) = (v, x \cdot 2 + w_i)'
$$
可以发现，我们只需要把边权进行处理，然后按照其原本的方式操作，是不会造成任何影响的。

------

现在，每一条边的边权都是 $g$ 的倍数了。也就是说，对于状态 $(u, x)'$，它能到达的状态均可以表示为 $(v, x \cdot 2^p + g \cdot q)'$。

显然有 $q \in \{0, 1, 2\}$。 

又由于 $(u, x)' \Leftrightarrow (u, x \cdot 4 + w_i \cdot 3)'\Leftrightarrow (u, x \cdot 4)' = (u, x\cdot 2^2)'$，那么状态就只和 $p$ 的奇偶性有关了，也即 $p \in \{0, 1\}$。

这样，对于每个点而言，本质不同的状态只剩下 $6$ 种，这是十分好的优化。

我们如何维护这些状态的连通性呢？枚举每一条边，把两个端点对应的状态用并查集合并即可。

------

回到问题上来，现在我们需要判断 $(s, z)$ 是否能够到达 $(t, r + z)$。

那么我们需要找到 $p, q$ 满足：

1. $(s, 0)'$ 需要能够到达 $(t, 2^p + g \cdot q)'$。

2. 存在 $k_1, k_2$，满足 $z \cdot 2^{k_1 \cdot 2 + p} + g \cdot (q + k_2 \cdot 3) \equiv r + z \pmod{p}$。

对于第一个条件，我们可以用并查集判断。

对于第二个条件，我们可以将式子转化为 $r + z - g \cdot q \equiv z \cdot 2^{k_1 \cdot 2 + p}\pmod{p}$，然后提前预处理后面一部分即可。

------

代码实现：

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>

using namespace std;

namespace IO
{
    int f, c;

    template<typename T> inline void _Read(T &k)
    {
        k = 0, f = 1, c = getchar();
        while(!isdigit(c))
        {
            if(c == '-') f = -1;
            c = getchar();
        }
        while(isdigit(c))
        {
            k = (k << 3) + (k << 1) + c - '0';
            c = getchar();
        }
        return k *= f, void();
    }

    template<typename T> inline void _Write(T k)
    {
        if(k < 0) putchar('-'), k = -k;
        if(k > 9) _Write(k / 10);
        return putchar(k % 10 + '0'), void();
    }

    inline int Read32() { int k; _Read(k); return k; }
    inline void Write32(int k, char ed = '\n') { return _Write(k), putchar(ed), void(); }
}

using IO :: Read32;
using IO :: Write32;

namespace Program
{
    const int MAXN = 2000005;

    int n, m, q, mod, g, z, ed[MAXN][3];
    bool f[2][MAXN];

    inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

    namespace Disjoint_Set
    {
        int fa[MAXN], si[MAXN];

        inline void Init()
        {
            for(register int i = 1; i <= n * 6; i++) fa[i] = i, si[i] = 1;
            return;
        }

        inline int Id(int u, int p, int q) { return (u - 1) * 6 + p * 3 + q + 1; }

        inline int Find(int u) { return fa[u] = (u == fa[u] ? u : Find(fa[u])); }

        inline void Merge(int u, int v)
        {
            int fu = Find(u), fv = Find(v);
            if(fu == fv) return;
            if(si[fu] < si[fv]) swap(fu, fv);
            return fa[fv] = fu, si[fu] += si[fv], void();
        }
    }

    using namespace Disjoint_Set;

    inline bool Check(int s, int t, int r)
    {
        for(register int p = 0; p < 2; p++) for(register int q = 0; q < 3; q++) if(Find(Id(t, 0, 0)) == Find(Id(s, p, q)) && f[p][(r + z + g * (3 - q)) % mod]) return true;
        return false;
    }

    inline int Run()
    {
        n = Read32(), m = Read32(), q = Read32(), g = mod = Read32(); 
        for(register int i = 1; i <= m; i++)
        {
            ed[i][0] = Read32(), ed[i][1] = Read32(), ed[i][2] = Read32();
            g = gcd(g, abs(ed[i][2] - ed[1][2]));
        }
        mod = gcd(g * 3, mod), z = ed[1][2] % g, Init();
        for(register int i = 1; i <= m; i++)
        {
            int u = ed[i][0], v = ed[i][1], w = (ed[i][2] - z) / g; 
            for(register int p = 0; p < 2; p++) for(register int q = 0; q < 3; q++)
            {
                Merge(Id(u, p, q), Id(v, p ^ 1, ((q << 1) + w) % 3));
                Merge(Id(v, p, q), Id(u, p ^ 1, ((q << 1) + w) % 3));
            }
        }
        for(register int i = 0, now = z; i < (mod << 1); i++)
        {
            f[i & 1][now] = true;
            now = (now << 1) % mod;
        }
        while(q--)
        {
            int s = Read32(), t = Read32(), r = Read32();
            if(Check(s, t, r)) puts("YES"); else puts("NO");
        }
        return 0;
    }
}

int main() { return Program :: Run(); }
```

------

**完结撒花！**

---

## 作者：关怀他人 (赞：4)

首先转化一下问题，倒着来做，一开始有一个数 $0$ , 每次走过一条边该数变为乘以 $2$ 再加上这条边的边权。用 $(u,x)$ 代表一个状态，表示当前在点 $u$ ，权值在模 $p$ 下为 $x$ 。

有一条边 $(u,v,c)$ ，那么可以走到的状态是
$$
(u,x)\to (v,2x+c)\to (u,4x+3c)\cdots
$$
由于 $p$ 是奇数，所以存在 $k>1$ 使得 $2^k\equiv 1 \mod p$，所以状态是循环的，由 $(u,x)$ 出发最终还会走回 $(u,x)$ ，所以可以认为递推关系是双向的，即 $(u,x)\Leftrightarrow (v,2x+c)$ 。

接下来考虑如果连接点$u$的两条边边权分别为 $a,b$ ，则
$$
(u,v)\Leftrightarrow (u,4x+3a)
$$
$$
(u,v)\Leftrightarrow (u,4x+3b)
$$
于是我们可以选择这样一条路
$$
(u,4x+3a)\Leftrightarrow (u,x)\Leftrightarrow (v,4x+3b)
$$
事实上，因为存在 $4$ 的逆元，那么 $4x$ 可以表示任何数，那么就相当于
$$
(u,v)\Leftrightarrow (u,x+3k(a-b)),k\in \mathbb{Z}
$$
接着考虑不同的点，$(u,x)\Leftrightarrow(v,2x+w)$ , 设  $u$ 循环节长度为 $t_u $，那么 $v$ 的循环节长度为 $2t_u$ ，和其本身的取 $\gcd$ 得$\gcd(t_u,2t_v)=\gcd(t_u,t_v)$ ( $2$ 可以去掉是因为 $2$ 与 $3g_u$ 互质因而与 $t_u$ 互质)。由于整个图是联通的，这可以扩展到所有点，也就是对于所有 $(u,x)$ 有  $(u,x)\Leftrightarrow(u,x+T)$ ，令

$$
t=\gcd_{u=1}^nt_u=\gcd(3\gcd_{i=1}^m(w_i-w_1),p)
$$
$$
g=\gcd_{i=1}^m(w_1-w_1)
$$
显然有 $t=g$ 或 $t=3g$ 。整理一下，同一点所有模 $t$ 同余的状态是一样的，而所有边权是模 $g$ 同余的，且 $t=g$ 或 $t=3g$ 。

这样，我们可以把题目中的 $p$ 直接改成 $t$ , 不会对答案有任何影响，那么现在所有边权在模$g$意义下都相等，设为 $z$ ，于是可以吧所有状态的 $x$ 加 $z$ ，所有边权减 $z$ ，则之前所有性质仍成立，因为
$$
(u,x)\Leftrightarrow (v,2(x-z)+(c+z)+z)=(v,2x+c)
$$
这样的话边权都是 $g$ 的倍数了，而因为 $(u,x)\Leftrightarrow(u,4x+3c)$ ，而 $c$ 又是 $g$ 的倍数，那么可以认为 $(u,x)\Leftrightarrow(u,4x)$ ，于是有
$$
(u,x)\Leftrightarrow (u,x2^p+qg),\ (0\leq p\leq 1,0\leq q\leq 2)
$$
也就是说，对于每个点，我们只有 $6$ 种状态有用。可以用并查集把所有在同一个连通块里的点缩起来，对于询问，只需要判断 $(t,z)$ 和 $(s,z+r)$ 是否连通，可以得到
$$
z2^p+qg=r+z
$$
对于每个 $p$ 预处理一下 $z2^p$ 的奇偶性即可。

时间复杂度 $O((n+m+q)\alpha (n)+p)$ 。
#### Code
```cpp
int n,m,Q,MOD,g,z;
int u[MAXN],v[MAXN],f[MAXN],c[MAXN];
bool flag[2][MAXM];

int GetId(int u,int p,int q){
    return (u - 1) * 6 + p * 3 + q + 1;
}

int gcd(int a,int b){
    if(b == 0) return a;
    return gcd(b,a % b);
}

int Find(int x){
    if(x == f[x]) return x;
    return f[x] = Find(f[x]);
}

void Merge(int u,int v){
    u = Find(u); v = Find(v);
    if(u != v) f[u] = v;
}

int main(){
    scanf("%d%d%d%d",&n,&m,&Q,&MOD);
    g = MOD;
    for(int i = 1;i <= m;i++){
        scanf("%d%d%d",&u[i],&v[i],&c[i]);
        g = gcd(g,abs(c[i] - c[1]));
    }
    MOD = gcd(3 * g,MOD);
    z = c[1] % g;
    for(int i = 1;i <= n * 6;i++) f[i] = i;
    for(int i = 1;i <= m;i++){
        int w = (c[i] / g) % 3;
        for(int p = 0;p < 2;p++){
            for(int q = 0;q < 3;q++){
                Merge(GetId(u[i],p,q),GetId(v[i],p ^ 1,(q * 2 + w) % 3));
                Merge(GetId(v[i],p,q),GetId(u[i],p ^ 1,(q * 2 + w) % 3));
            }
        }
    }
    for(int i = 0,t = z;i < MOD;i++){
        flag[i & 1][t] = 1;
        t = t * 2 % MOD;
    }
    while(Q--){
        int s,t,r;
        scanf("%d%d%d",&s,&t,&r);
        for(int p = 0;p < 2;p++){
            for(int q = 0;q < 3;q++){
                if(Find(GetId(t,0,0)) == Find(GetId(s,p,q)) && flag[p][(r + z + (3 - q)* g) % MOD]){
                    puts("YES");
                    goto NEXT;
                }
            }
        }
        puts("NO");
        NEXT: continue;
    }
    return 0;
}
```

---

## 作者：_fairytale_ (赞：3)

>如果只转身后退就能回到那个夏天
>
>把颜色逐一背下就能复现当时画面
>
>无意回眸撞入你镜头前
>
>恼笑着排列语言
>
>于是一切定格包括光线

出这题的和自己做出来这题的都不是人啊！！！！！

记 $p=MOD$。

我们发现可以把路径反过来，这样经过一条边的时候，只需把当前距离乘 $2$ 再加上边权即可。于是我们建一张图，图中的点 $(u,x)$ 表示走到 $u$，当前距离为 $x$，根据原图中的边在新图上连一些边，这样只需判断 $(t,0)$ 是否能到达 $(s,r)$。

接下来就需要一些性质了。猜猜 $p$ 为啥是奇数？

我们先忽略起点，设 $(u,x)$ 表示走到 $u$，当前距离为 $x$ 的状态。考虑一条边 $(u,v,w)$，我们可以在这条边来回走，假如我们走了 $i$ 次，那么当前的距离应该变为 $2^ix+(2^i-1)w$。

因为 $p$ 是奇数，我们可以求出模 $p$ 意义下 $2$ 的阶 $q$，那么当 $i=2q$ 时，当前的状态会回到 $(u,x)$。因此对于两个状态 $(u,x),(v,y)$，如果 $(u,x)$ 能转移到 $(v,y)$，那么 $(v,y)$ 也能转移到 $(u,x)$。

接下来考虑这样一个结构：存在两条边 $E_1=(u,v_1,w_1)$ 和 $E_2=(u,v_2,w_2)$，当前状态是 $(u,x)$。如果我们在 $E_1$ 上走一个来回，当前状态会变为 $(u,4x+3w_1)$；同理，在 $E_2$ 上走一个来回，当前状态会变为 $(u,4x+3w_2)$。

所以 $(u,x),(u,4x+3w_1),(u,4x+3w_2)$ 三个状态是连通的。诶！还记得刚刚的结论嘛！换个元，令 $y=4x+3w_1$，则 $(u,y)$ 可以到达 $(u,y-3(w_1-w_2))$！

我们断言，$(u,x)$ 可以到达 $(u,x+3kg),k\in \mathbb{Z}$，其中 $g$ 表示图中所有边两两边权差的 $\gcd$。

这是因为，考虑现在我们需要某一个点 $v$ 连边中的某一个边权差 $W$，可以先从 $(u,x)$ 走 $k$ 步到 $(v,x2^k+\sum_{i=1}^kw_k)$，然后在这个地方刷到 $(v,x2^k+\sum_{i=1}^kw_k+3W2^k)$，再回退回去即可。假如 $u$ 有一条相邻边，边权为 $a$，$v$ 有一条相邻边，边权为 $b$，它们有一条公共边，边权为 $c$，那么可以从 $(u,x)$ 变成 $(u,x+3(a-b)+3(b-c))=(u,x+3(a-c))$，因为这个图是连通图，因此可以推广到图中任意边权差。

又因为我们在模 $p$ 意义下，自然 $x$ 可以变成 $x+kp$，所以 $(u,x)$ 可以到达 $(u,x+k\gcd(3g,p))$。

因为 $\gcd(a,b)=\gcd(a,b-a)$，所以 $\gcd(w_1-w_i,w_1-w_j)=\gcd(w_1-w_i,w_i-w_j)$，所以 $g=\gcd_{i\in[2,n]}|w_i-w_1|$。

顶级性质：$a\equiv b \pmod {a-b}$，因此所有边模 $g$ 同余，设余数为 $z$，我们接下来尝试把所有边权变成 $g$ 的倍数。

令 $w'=w-z$。对应地，定义新状态 $(u,x)'=(u,x-z)$，在这个状态上，我们使用 $w'$ 作为边权。尝试从 $(u,x)'$ 经过一条长为 $w$ 的边到达 $v$。有 $(u,x)'\iff(v,2x+w')'\iff(v,2x+w-z)'\iff(v,2x+w-2z)\iff (u,x-z)$。所以这样变换之后对原来的性质没有影响，而且所有边权都变成了 $g$ 的倍数。

我们再断言，所有新状态都可以写成 $(u,z2^a+bg)',a\in\{0,1\},b\in\{0,1,2\}$ 的形式，因为初始在 $(u,z)'$，而所有边权都是 $g$ 的倍数，所以状态一定是 $(u,2^a+bg) $ 的形式。又因为 $(u,x)'\iff(v,2x+w)'\iff(u,4x+3w)'\iff(u,2^2x)'$，所以 $a$ 可以对 $2$ 取模；因为模数是 $3g$ 的约数，所以 $b$ 会对 $3$ 取模。

询问相当于问是否有 $(t,z)'\iff(s,r+z)'$。

因为 $z=z2^0+0g$，所以只需枚举 $(c,d)$，首先满足 $(t,z)'\iff(s,z2^c+dg)'$，然后还要满足 $\exist k\in \mathbb{Z},z2^{c+2k}+dg=r+z\pmod p$，对每个 $c$ 预处理所有可能的 $z2^{c+2k}$ 即可。

```cpp
#include<bits/stdc++.h>
bool Mst;
#define YoN(x) (x?cout<<"YES\n":cout<<"NO\n")
#define rep(x,qwq,qaq) for(int x=(qwq);x<=(qaq);++x)
#define per(x,qwq,qaq) for(int x=(qwq);x>=(qaq);--x)
using namespace std;
template<class _T>
void ckmax(_T &x,_T y) {
	x=max(x,y);
}
template<class _T>
void ckmin(_T &x,_T y) {
	x=min(x,y);
}
#define maxn 51000
int n,m,q,p;
struct Edge {
	int u,v,w;
} E[maxn];
//(1,0)->(2,x)->(3->)
struct node {
	int u,a,b;
	bool operator ==(const node&bb)const {
		return u==bb.u&&a==bb.a&&b==bb.b;
	}
};
ostream&operator<<(ostream&os,const node&bb) {
	return os<<"("<<bb.u<<","<<bb.a<<","<<bb.b<<")",os;
}
node fa[maxn][2][3];
//x*2^a
node fd(node x) {
	int u=x.u,a=x.a,b=x.b;
	return fa[u][a][b]==x?x:fa[u][a][b]=fd(fa[u][a][b]);
}
void mrg(node x,node y) {
	node s=fd(x),t=fd(y);
	if(s==t)return;
	fa[s.u][s.a][s.b]=t;
}
bitset<1001000>ok[2];
bool Med;
signed main() {
	cerr<<(&Mst-&Med)/1024.0/1024.0<<" MB\n";
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>q>>p;
	int g=p;
	for(int i=1,u,v,w,W1; i<=m; ++i) {
		cin>>u>>v>>w;
		E[i]= {u,v,w};
		if(i==1)W1=w;
		else g=__gcd(g,abs(w-W1));
	}
	int z=E[1].w%g;
	rep(i,2,m)assert(E[i].w%g==z);
	rep(i,1,m)E[i].w=(E[i].w-z)/g;
	p=__gcd(p,3*g);
	rep(i,1,n)rep(a,0,1)rep(b,0,2)fa[i][a][b]= {i,a,b};
	rep(i,1,m) {
		int u=E[i].u,v=E[i].v,w=E[i].w;
		rep(a,0,1) {
			rep(b,0,2) {
				mrg({u,a,b}, {v,a^1,(b*2+w)%3});
				mrg({v,a,b}, {u,a^1,(b*2+w)%3});
			}
		}
	}
	rep(c,0,1) {
		int pw=z*(c?2:1)%p;
		for(int k1=0;;++k1) {
			if(ok[c][pw]==1)break;
			ok[c][pw]=1;
			pw=pw*4%p;
		}
	}
	for(int i=1,s,t,r; i<=q; ++i) {
		cin>>s>>t>>r;
		swap(s,t);
		rep(c,0,1)rep(d,0,2)if(fd({s,0,0})==fd({t,c,d})){
			int f=((z+r-g*d)%p+p)%p;
		    if(!ok[c][f])continue;
			YoN(1);
			goto IE;
		}
		YoN(0);
IE:
		;
		/*
		(s,z)' <-> (t,z+r)'
		a=0,b=0
		for(c,d)
		    (s,z)' <-> (t,z2^c+dg)
		    exist k1\in Z s.t.
		    z2^{c+2k1}=z+r-gd mod p

		*/
	}
	return 0;
}
/*
input:

output:

*/



```

---

## 作者：Leasier (赞：3)

是我最喜欢的纯数论题！

做这道题，你所需要的几乎只有足够的脑容量。~~但是我的好像不太够 /kk~~

------------

直接考虑正路径的话会发现加点后权值改变量与路径长度有关，不妨转化为反路径。

设 $(u, x)$ 表示到达 $u$ 时距离为 $x$。

具体地，设经过 $u \to^w v$ 前为 $(u, x)$，则经过后距离为 $(v, 2x + w)$。

考虑在这条边上反复横跳，则正反加起来经过 $i$ 次后为 $(u/v, 2^i x + (2^i - 1)w)$。

注意到题给条件：$mod$ 为**奇数**。

于是一定存在一个 $i > 0$ 使得 $2^i \equiv 1 \pmod p$，此时 $\varphi(p) \mid i$。也即，在一条边上反复横跳若干次后一定可以走回起点，且经过距离不变。同理，我们可以得到路线 $(u, 4x + 3c) \to (u, x)$ 存在。

考虑到路线 $(u, 4x + 3c_1) \to (u, x) \to (u, 4x + 3c_2)$（$w_1 \neq c_2$），则 $(u, x) \to (u, y)$ 的充要条件为：

- 设 $d = \displaystyle\gcd_{c_1 \neq c_2} |c_1 - c_2|, d' = \gcd(3d, mod)$，则 $d' \mid |x - y|$。
- 这里出现了一个小问题：$d$ 如何计算？根据更损相减法，我们其实只需要计算 $\displaystyle\gcd_{i = 2}^m |c_i - c_1|$。

于是下面我们可以考虑把 $(u, x)$ 中的 $x$ 放在 $\bmod \ d'$ 意义下讨论。

人类智慧地，注意到可以把所有 $c_i$ 表示为 $d c'_i + t$ 的形式，我们尝试用 $c'_i$ 代替 $c_i$。

代入前面的计算，可知 $(u, (x - t) + t) \to (u, 4(x - t) + 3dc'_i + t)$，于是我们再用 $x - t$ 代替 $x$ 即可在形式上满足原来的性质。

记 $(u, x)' = (u, x + t)$，则原问题转化为求 $(v, t)', (u, r + t)'$ 是否连通。

考虑把 $(u, x_0)'$ 中的 $x_0$ 表示为 $2^P x + Q d'$ 的形式，则一条边的转移相当于：

- $(u, 2^P x + Qd')' \to (v, 2^{P + 1} x + (2Q + c')d)'$。

一个直接的想法是记录 $(u, P, Q)$ 三元组，预处理时并查集合并，查询时枚举 $P, Q$ 看一下连通性和数值关系是否都满足，但这样时间复杂度会爆炸……

注意到 $d' \leq 3d$，则可以限制 $0 \leq Q \leq 2$；又注意到 $(u, x)' \to (u, 4x + 3dc'_i)' \to (u, 4x)$，则当 $P$ 奇偶性相同的时候连通性关系不变，于是可以限制 $P = 0/1$。于是现在并查集点数降到 $O(n)$，可以接受。

时间复杂度为 $O(n + mod + (m + q) \log n)$。

代码：
```cpp
#include <stdio.h>
#include <stdlib.h>

int a[50007], b[50007], c[50007], id[50007][7][7], root[300007];
bool vis[7][1000007];

inline void init(int n){
	for (int i = 1; i <= n; i++){
		root[i] = i;
	}
}

int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}

int get_root(int x){
	if (root[x] == x) return x;
	return root[x] = get_root(root[x]);
}

inline void merge(int x, int y){
	int x_root = get_root(x), y_root = get_root(y);
	if (x_root != y_root) root[x_root] = y_root;
}

int main(){
	int n, m, q, mod, d, rem, cnt = 0;
	scanf("%d %d %d %d", &n, &m, &q, &mod);
	d = mod;
	for (int i = 1; i <= m; i++){
		scanf("%d %d %d", &a[i], &b[i], &c[i]);
	}
	for (int i = 2; i <= m; i++){
		d = gcd(d, abs(c[i] - c[1]));
	}
	rem = c[1] % d;
	mod = gcd(d * 3, mod);
	for (int i = 1; i <= m; i++){
		c[i] = (c[i] - rem) / d % 3;
	}
	for (int i = 1; i <= n; i++){
		for (int j = 0; j <= 1; j++){
			for (int k = 0; k <= 2; k++){
				id[i][j][k] = ++cnt;
			}
		}
	}
	init(cnt);
	for (int i = 1; i <= m; i++){
		for (int j = 0; j <= 1; j++){
			for (int k = 0; k <= 2; k++){
				merge(id[a[i]][j][k], id[b[i]][j ^ 1][(k * 2 + c[i]) % 3]);
				merge(id[b[i]][j][k], id[a[i]][j ^ 1][(k * 2 + c[i]) % 3]);
			}
		}
	}
	for (int i = 0, j = rem; i < mod; i++, j = j * 2 % mod){
		vis[i & 1][j] = true;
	}
	for (int i = 1; i <= q; i++){
		int s, t, r;
		bool ans = false;
		scanf("%d %d %d", &s, &t, &r);
		for (int j = 0; j <= 1 && !ans; j++){
			for (int k = 0; k <= 2; k++){
				if (get_root(id[t][0][0]) == get_root(id[s][j][k]) && vis[j][((r + rem - k * d % mod) % mod + mod) % mod]){
					ans = true;
					break;
				}
			}
		}
		if (ans){
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}
```

---

## 作者：laihaochen (赞：3)

神仙数论题。

首先，如果正着做，我们需要记录**走过了几条边**以及**当前路径的长度**，这不方便我们挖掘性质，所以我们考虑倒着做，每次把当前路径的长度乘二再加上当前边权。

我们把状态定义为 $(u, x)$ 其中 $u$ 是当前节点，$x$ 是当前路径长度（这里的 $x$ 是在模 $Mod$ 意义下的）。

假设我们经过一条边 $(u, v, w)$ 可以把状态 $(u, x)$ 转移成 $(v, 2x +w)$ ，我们不妨把这两个状态连有向边。

那么我们总共有 $nMod$ 个状态，我们需要找到状态 $(T, 0)$ 是否能到达 $(S, R)$ 。

### 性质一

我们发现题目提到了 $Mod$ 为奇数，那么 $\gcd(2, Mod) = 1$ ，所以由欧拉定理，存在 $x = \varphi(Mod)$ 使得 $2^x \equiv 1 \pmod {Mod}$ 。

考虑状态 $(u, x)$ 反复走 $(u, v, w)$ 这条边，即：

$(u, x) \rightarrow (v, 2x + w) \rightarrow (u, 4x + 3w) \rightarrow \cdots$

走到第 $i$ 次的权值为 $2^ix+(2^i - 1)w$ ，当 $i = \varphi(Mod)$ 时，权值就恰好等于 $x$ ，如果当前在节点 $u$， 我们就回到了 $(u, x)$ ，如果当前在节点 $v$ ， 我们再走 $i$ 步就能回到 $(u, x)$ 。

综上，我们反复走 $(u, v, w)$ 所达到的状态形成了一个环，所以我们**状态之间可以连无向边**。

那么我们如果根据这个性质枚举 $nMod$ 个状态然后用并查集建边，可以得到一个 $O(nMod^2\alpha(nMod))$ 的算法。

---

### 性质二

我们考虑一个节点 $u$ 如果连了两条权值分别为 $a, b$ 的边，那么 $(u, x)$ 可以到达 $(u, 4x+3a)$ 与 $(u, 4x+3b)$ 所以 $(u, x)$ 可以到达 $(u, x + 3(a-b))$ ，同样地，$(u, x + 3(a-b))$ 也能到达 $(u, x)$。

即：$(u, x) \Leftrightarrow (u, x + 3(a-b))$

根据这个性质，我们考虑把与节点 $u$ 相连的所有边的边权求 $\gcd$ ，由于图是联通的，所以这个 $\gcd$ 也就是任意两条边的 $\gcd$ 。

设这个 $\gcd = g'$ ，

令$g=\gcd(g',Mod)$

根据剩余系的知识，可以得到：

$\forall u \in V, (u, x) \Leftrightarrow (u, x+3g)$

也就是说当 $x \equiv y \pmod{3g}$ 时 $(u,x) \Leftrightarrow (u,y)$

---

### 性质三

$\because x \equiv y \pmod{Mod}$ 时 $(u,x) \Leftrightarrow (u,y)$

$\therefore$ 当 $x \equiv y \pmod{\gcd(3g,Mod)}$ 时， $(u,x) \Leftrightarrow (u,y)$

所以我们发现令 $Mod = \gcd (3g,Mod)$ 能替代原问题。

（下面的 $Mod$ 均代表 $\gcd (3g,Mod)$）

$\because \forall a,b \in E,g | (a-b)$

$\therefore a \equiv b \pmod g$

$\therefore \forall a \in E,a = kg + z$ ，其中 $z$ 是常数。

边权如果用 $kg + z$ 表示会比较复杂，所以我们考虑把所有边权减去 $z$ 。

为了与原来的转换保持不变，我们要把所有状态中的路径长度加上 $z$ ：

$(u,x)' = (u,x+z) \Leftrightarrow (v,2(x+z)+w-z) \Leftrightarrow (v,2x+w+z) =(v,2x+w)'$

$\therefore \forall u \in V, (u, x)$ 能到达的状态均可以表示成 $(v, 2^px+qg)$

由性质二，$q \equiv q' \pmod 3$ 时，$(v, 2^px+q'g)  \Leftrightarrow (v, 2^px+qg)$

所以只需取 $q = \{0, 1, 2\}$ 即可。

$\because (u,2^{p}x) \Leftrightarrow (v,2^px + qg) \Leftrightarrow (u,2^{p+1}x+3qg) \Leftrightarrow (u,2^{p+2}x)$

所以只需取 $p = \{0,1\}$ 即可。

所以状态只有 $6n$ 种了，用并查集维护这 $6n$ 个状态的联通情况。

---

考虑把 $(T,z)$ 能否到达 $(S,R+z)$ 转换成表达式

$(T,z)$ 能到达 $(S,R+z)$ 

$\Leftrightarrow \exists p, q$ 同时满足

1. $(T,z)$ 与 $(S,2^p+qg)$ 联通
2. $\exists k_1, k_2 \in \mathbb{Z}$ 使得 $2^{2k_1+p}z+(q+3k_2)g \equiv R+z\pmod{Mod}$

但因为 $Mod | 3k_2g$

所以只需满足 $\exists k \in \mathbb{Z}$ 使得 $R+z-qg \equiv 2^{2k+p}z\pmod{Mod}$

我们可以预处理出 $[0,Mod)$ 中所有可以表示为 $2^{2k+p}z$ 的值，然后就能 $O(\alpha(m))$ 处理询问了。

总时间复杂度 $O(Mod + n + m\alpha(m))$ 预处理 $O(\alpha(m))$ 查询。

代码：

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 5e4 + 5, maxn = 1e6 + 5;
int n, m, Q, mod, u[N], v[N], w[N];
bool pre[5][maxn];
int gcd (int a, int b) {
	if (b == 0) {
		return a;
	}
	return gcd (b, a % b);
}
int S[N << 3];
int getf (int x) {
	if (x == S[x]) {
		return x;
	}
	return S[x] = getf(S[x]);
}
void merge (int x, int y) {
	int u = getf(x), v = getf(y);
	if (u != v) {
		S[u] = v;
	}
}
inline int get_id (int u, int p, int q) {
	return (u - 1) * 6 + p * 3 + q + 1;
}
int main() {
	scanf ("%d%d%d%d", &n, &m, &Q, &mod);
	for (int i = 1; i <= m; i++) {
		scanf ("%d%d%d", &u[i], &v[i], &w[i]);
	}
	int g = mod;
	for (int i = 2; i <= m; i++) {
		g = gcd (g, abs(w[i] - w[1]));
	}
	mod = gcd (mod, 3 * g);
	int z = w[1] % g;
	for (int i = 1; i <= n * 6; i++) {
		S[i] = i;
	}
	for (int i = 1; i <= m; i++) {
		w[i] = (w[i] - z) / g;
		for (int p = 0; p <= 1; p++) {
			for (int q = 0; q <= 2; q++) {
				merge (get_id (u[i], p, q), get_id (v[i], p ^ 1, (q * 2 + w[i]) % 3));
				merge (get_id (v[i], p, q), get_id (u[i], p ^ 1, (q * 2 + w[i]) % 3));
			}
		}
	}
	for (int i = 0, x = z; i < (mod << 1); i++) {//phi(mod) < mod
		pre[i & 1][x] = 1;
		x = (x << 1) % mod; 
	}
	for (int i = 1, s, t, r; i <= Q; i++) {
		bool ans = 0;
		scanf ("%d%d%d", &s, &t, &r);
		for (int p = 0; p <= 1; p++) {	
			for (int q = 0; q <= 2; q++) {
				if (getf(get_id(t, 0, 0)) == getf(get_id(s, p, q))) {
					ans |= pre[p][(r + z + (3 - q) * g) % mod];	//保证为正数 
				}
			}
		}
		if (ans) {
			printf ("YES\n");
		} else {
			printf ("NO\n");
		}
	}
	return 0;
}
```

---

## 作者：Tony2 (赞：2)

upd: 稍微有一些小问题，审核看到了直接过就好了（

我尽量用简短的语言代替长长的数学公式，因为这很容易让人看不下去。

正着跑需要记录当前跑了几条边，考虑从 $t$ 走到 $s$，一开始有一个 $x$，假设每次在 $u$ 时数字为 $x$，则通过一条权值为 $w$ 的 $u\leftrightarrow v$ 的边时到达 $v$ 把权值变成 $(2x+w)\bmod p$。状态的第二维的大小为模数 $p$。

于是我们有了最初的想法，设计状态 $(u,x)_0$ 表示走到了 $u$ 且手上的数为 $x$ 的状态。每次询问相当于问能否从 $(t,0)_0$ 走到 $(s,r)_0$。

此时我们的状态转移是有向的，但其实如果我们能实现 $(u,x)_0\to(v,2x+w)_0$，我们同样也能实现 $(v,2x+w)_0\to(u,x)_0$。考虑在 $u$ 和 $v$ 之间反复横跳 $\varphi(p)$ 次即可，$\varphi(p)$ 一定是偶数，一开始状态为 $(u,x)_0$，第一次会变成 $(v,2x+w)_0$，最后会变成 $(u,2^{\varphi(p)}x+(2^{\varphi(p)}-1)w)_0$ 即初始状态。

简单地说状态之间的连边都是无向边，状态形成的图是无向图，这样暴力可以用并查集做。

继续研究反复横跳的过程，如果 $u$ 在一条边（边权为 $w$）上走过去又走回来，那么状态会 $(u,x)_0\to(u,4x+3w)_0$。

如果 $u$ 有两条出边，边权分别是 $a$ 和 $b$，初始状态 $(u,x)_0$ 可以分别变成 $(u,4x+3a)_0$ 和 $(u,4x+3b)_0$。如果我们定义 $x'=4x+3a$，那么就有 $(u,x')_0\leftrightarrow(u,x'+3(b-a))_0$。如果定义 $g=\gcd_{a,b}(b-a)$，这会使得由 $(u,x)$ 组成的集合被分为 $\gcd(3g,p)$ 个环。实际上可以简单的写成 $g=\gcd_{i=2}^d(w_1-w_i)$，其中 $d$ 是点 $u$ 的度数。

因为图是联通的，所以我们可以简单地把所有的 $g$ 一起取 $\gcd$。下文 $g$ 全部代指 $\gcd_{i=2}^m(w_1-w_i)$。

图上任意两条边的差都是 $g$ 的倍数，所以有 $w_1\equiv w_2\pmod g$，所以所有的边权都能被表示为 $kg+z$。

因为一个 $u$ 对应的有效的 $x$ 的数量为 $\gcd(3g,p)$，不妨令 $p'=\gcd(3g,p)$，设计状态 $(u,x)_1$，其中第二维的值域为 $p'$。如果原来的状态是 $(u,x)_0$，那么它将对应到 $(u,(x+z)\bmod p')_1$。这里我们将所有的边权统一减去 $z$，这样不仅能让所有的边权都变成 $g$ 的倍数，还能让原来的转移继续成立。

考虑 $u\to v\to u$ 的过程，有 $(u,x)_1\leftrightarrow(u,4x+3w)_1$，因为 $p'|3w$，所以 $(u,x)_1\leftrightarrow(u,4x)_1$。因为我们的起点一定是 $(s,z)_1$，第二维一定是固定的 $z$，我们唯一的变换是 $(u,x)_1\leftrightarrow(v,2x+w)_1$，并且 $p'|3g|3w$，所以我们路上经过的一切状态都能表达为 $(u,2^iz+jg)_1$，而其中的所有**等价状态**有 $i\in\{0,1\}$，如果 $p'|g$ 则 $j=0$，否则 $j\in\{0,1,2\}$。

进一步压缩状态为 $(u,i,j)_2$，对于每条边连边即可。注意可能有多种状态 $2$ 对应着同一个状态 $1$，将状态 $1$ 对应到状态 $2$ 需要枚举所有可能的 $2^tz$ 和 $j$。

```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N = 5e4 + 5, NN = 3e5 + 5, M = 1e6 + 5;
int n, m, q, g, p, z;
int U[N], V[N], W[N];
bool vis[M][6];
int fa[NN]; int getfa(int x){return x == fa[x] ? x : fa[x] = getfa(fa[x]);}
int getid1(int i, int j){
	return (i - 1) * 2 + j + 1;
}
int getid2(int i, int j){
	return (i - 1) * 6 + j + 1;
}
void upd(int i, int x){
	vis[i][x] = 1;
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	cin >> n >> m >> q >> p;
	for (int i = 1; i <= m; i++)
		cin >> U[i] >> V[i] >> W[i];
	for (int i = 2; i <= m; i++)
		g = __gcd(abs(W[1] - W[i]), g);
	int g2 = __gcd(g, p);
	p = __gcd(g * 3, p);
	g = g2;
	z = W[1] % g;
	for (int i = 1; i <= m; i++)
		W[i] -= z;
	if (g == p){
		for (int i = 1; i <= n * 2; i++) fa[i] = i;
		for (int i = 0, cur = z * 2 % p; ; i++, cur = cur * 4 % p){
			upd(cur, 1);
			if (cur * 4 % p == z * 2 % p) break;
		}
		for (int i = 0, cur = z; ; i++, cur = cur * 4 % p){
			upd(cur, 0);
			if (cur * 4 % p == z) break;
		}
		for (int i = 1; i <= m; i++)
			for (int j = 0; j < 2; j++){
				int u = getid1(U[i], j), v = getid1(V[i], j ^ 1);
				fa[getfa(u)] = getfa(v);
			}
		while (q--){
			int s, t, r;
			cin >> t >> s >> r;
			bool ans = 0;
			for (int i = 0; i < 2; i++)
				if (vis[(z + r) % p][i])
					ans |= getfa(getid1(s, 0)) == getfa(getid1(t, i));
			puts(ans ? "YES" : "NO");
		}
	}else{
		for (int i = 1; i <= n * 6; i++) fa[i] = i;
		for (int i = 1; i <= m; i++)
			W[i] /= g;
		for (int i = 0, cur = z * 2 % p; ; i++, cur = cur * 4 % p){
			upd((cur + g * 2) % p, 5);
			upd((cur + g) % p, 3);
			upd(cur, 1);
			if (cur * 4 % p == z * 2 % p) break;
		}
		for (int i = 0, cur = z; ; i++, cur = cur * 4 % p){
			upd((cur + g * 2) % p, 4);
			upd((cur + g) % p, 2);
			upd(cur, 0);
			if (cur * 4 % p == z) break;
		}
		for (int i = 1; i <= m; i++)
			for (int j = 0; j < 6; j++){
				int u = getid2(U[i], j), v = getid2(V[i], ((j & 1) ^ 1) | ((((j >> 1) * 2 + W[i]) % 3) << 1));
				fa[getfa(u)] = getfa(v);
			}
		while (q--){
			int s, t, r;
			cin >> t >> s >> r;
			bool ans = 0;
			for (int i = 0; i < 6; i++)
				if (vis[(z + r) % p][i])
					ans |= getfa(getid2(s, 0)) == getfa(getid2(t, i));
			puts(ans ? "YES" : "NO");
		}
	}
	return 0;
}
```

---

## 作者：enucai (赞：1)

## [[AGC031F] Walk on Graph](https://www.luogu.com.cn/problem/AT_agc031_f)

> 有一张 $n$ 个点 $m$ 条边的无向连通图 $G$，每条边有长度 $L_i$，有一个人在上面游走。
>
> 有 $q$ 组询问，每组询问给出 $s_i,t_i,r_i$，询问是否存在一条从 $s_i$ 出发到 $t_i$ 结束且长度为 $r_i$ 的路径。其中路径长度的定义为：假设走过了的边长度为 $L_1,L_2,\cdots, L_k$，则这条路径的长度为 $(\sum_{i=1}^kL_i\times 2^{i-1}) \bmod mod$。
>
> $1\leq n,m,q\leq 50000$，$mod\leq 10^6$，$mod\equiv 1\pmod 2$。

首先先把路径反转，变成每次走一条长度为 $w$ 的边，路径长度由 $x$ 变为 $(2x+w)\bmod mod$。

令状态 $(u,x)$ 表示在点 $u$ 时路径长度 $=x$。称 $(u,x)\to(v,y)$ 表示如果 $(u,x)$ 状态能到达，那么 $(v,y)$ 状态可以到达。有结论：$(u,x)\to(v,y)\iff (v,y)\to(u,x)$。证明考虑只要证明相邻的任意 $u,v$ 通过任意一条连接他们的边 $w$ 满足即可，其他可以通过路径上推过去。

对于一对点 $u,v$ 之间边权为 $w$ 的边，有 $(u,x)\to (v,(2x+w)\bmod mod)$，来回走 $t$ 次后的路径长度会变成 $2^tx+(2^t-1)w$，令 $t=2\varphi(mod)$ 时，由于 $2^{\varphi(mod)}\equiv 1\pmod{mod}$，路径长度会变成 $x+0\cdot w=x$。也就是说从 $(v,(2x+w)\bmod mod)$ 状态沿着这条边走 $2\varphi(mod)-1$ 次后，就会回到 $(u,x)$ 状态。原命题得证。

接下来考虑对于任意一个点的两条出边 $(u,v_1,w_1)$ 与 $(u,v_2,w_2)$，如果第一条边来回一次，会得到 $(u,x)\to (u,4x+3w_1)$，第二条边来回会得到 $(u,x)\to (u,4x+3w_2)$，结合上一条结论，可以得到 $(u,x),(u,4x+3w_1),(u,4x+3w_2)$ 三个状态是等价的，因此 $(u,4x+3w_1)\iff (u,4x+3w_2)$，考虑设 $y=4x+3w_1$，则有 $x=\frac{y-3w_1}{4}$（可以这么设元因为题目中保证了 $mod$ 是奇数，所以在 $\bmod mod$ 意义下 $4$ 一定存在逆元），因此 $4x+3w_2=y+3(w_2-w_1)$，不难发现对于连接同一个点的任意两条边，对于满足 $3(w_1-w_2)\mid\vert x-y\vert$ 的 $x,y$，$(u,x)$ 与 $(u,y)$ 状态等价。

考虑对于另一个点 $u'$ 周围的两条边的权值差 $d$ 能否同样应用在 $u$ 上（形式化的说，考虑有 $(u',v_1,w_1)$ 与 $(v',v_2,w_2)$，能否得出 $(u,x)\iff (u,x+3(w_1-w_2))$），答案是可以的。令 $d=w_1-w_2$，考虑将 $(u,x)$ 与 $(u,x+3d)$ 同时沿着 $u\to u'$ 的路径上一直使用第一个结论推，推到 $u'$ 时形式会变成 $(u',c_1x+c_3)$ 与 $(u',c_1x+3c_2d+c_3)$，在 $u'$ 处应用同端点两条边的结论可以推到得到 $(u',c_1x+c_3)\iff (u',c_1x+3c_2d+c_3)$，因此得到 $(u,x)\iff (u,x+3d)$。这样任意两条相邻边的差都可以应用在图上的任意定点上，根据裴蜀定理，直接将所有边的差取 $\gcd$ 即可，设这个 $\gcd$ 为 $g$，那么对于任意 $3g\mid \vert x-y\vert$，都有 $(u,x)\iff(u,y)$。

此时所有边的边权 $\bmod g$ 的值全部相等，设为 $z$，我们尝试将所有边的值 $-z$，新的状态 $(u,x)'=(u,x-z)$，$(u,x)'$ 在经过新边权为 $w'$ 的边时变成 $2(x-z)+w+z=2x+w-z$，所以 $(u,x)'$ 的下一个状态变为 $(v,2x+w')'$，形式与之前相同，询问判定的问题变成了 $(t,z)'$ 能否到达 $(s,z+r)'$。好处是所有边的边权全部变成了 $g$ 的倍数。

仍然考虑一个点出去再回来，此时新状态的变化是 $(u,x)'\to (u,4x+3w')'$，由于 $g\mid w'$，所以 $3g\mid 3w'$，在 $\bmod 3g$ 意义下，有 $(u,4x+3w')'\iff (u,4x)'$，所以 $(u,x)'\iff (u,4x)'$。

考虑需要判定的是从 $(s,z)'$ 出发，因此可能到达的状态可以被表示为 $(u,2^tz+kg)'$（由于每条边的边权都是 $g$ 的倍数）。由于第二维已经是在 $\bmod 3g$ 意义下的了，所以有 $0\le k<2$。

由于 $(u,x)'\iff (u,4x)'$，所以 $(u,2^tz+kg)'\iff (u,2^{t+2}z+4kg)'\iff (u,2^{t+2}z+kg)$，所以在 $k$ 相同时，$t$ 奇偶性相同的状态也是等价的，因此只有 $t=0/1$ 的点是有用的，这样状态数就被压缩至了 $6n$ 个。

直接对每个这样的状态开一个节点，能到达的之间连边，使用并查集维护即可。最后判断时枚举 $t,k$，需要判断是否存在一个 $w\equiv t\pmod{\gcd(mod, 3g)}$，使 $(2^wz+kg)\equiv r+z\pmod{\gcd(mod,3g)}$，可以 $O(mod)$ 预处理。复杂度 $O(n\log n+mod)$。

---

## 作者：Shunpower (赞：0)

## **Intro**

本题网上能找到的题解普遍存在证明不全的问题。这篇题解尽可能地补全了证明过程。

**为了避免变量名冲突，在本题解中，我们令 $p$ 表示 $MOD$，令 $w_i$ 表示边权 $L_i$。**

## **Solution**

长度长成这个形式，还要先取模，肯定不能架算法乱搞。容易想到思路的起点应该是考虑走过一条边之后对长度的影响，然后可以发现我们的长度长成一个升幂形式不好计算，所以应该把 $s\to t$ 转成 $t\to s$ 搞成降幂形式，这样可以直接累过去，走一条边权为 $w$ 的边直接 $d\gets 2d+w$ 即可。

然后考虑在无向图上一个最自然的想法，就是在一条边上反复横跳。我们考虑一个状态 $(u,d)$ 表示到达 $u$，路径长度为 $d$，那么我们总是可以通过在一条边上反复横跳得到：

$$
(u,d)\to (v,2d+w)\to (u,4d+3w)\to\cdots \to (u/v,2^id+(2^i-1)w)
$$

其中显然 $i$ 为奇数时在 $v$，偶数时在 $u$。

考虑因为 $p$ 是奇数，所以 $\gcd(2,p)=1$，于是总是可以找到一个偶数 $i=2\varphi(p)$ 使得 $2^i\equiv 1\pmod p$。所以一定存在 $(u,d)\to (u,d)$ 的状态变化路径，从而这条路上遇到的所有状态都是和 $(u,d)$ 可以互相到达的。不妨提取 $(u,4d+3w)$，考虑 $(u,d)$ 和 $(u,4d+3w)$ 这两个状态总是可以互相到达的。

我们用 $(u,4d)$ 串起所有这个点上的边。我们可以换元，令 $x\gets 4d+3w_1$，那么可以发现状态 $(u,x),(u,x+3w_2-3w_1)$ 是可以互相到达的。考虑我们的记号 $d$，事实上因为 $4$ 一定存在模 $p$ 的逆元，所以 $4d+3w_1$ 其实表示了整个模 $p$ 剩余系。$x$ 也是同理的。

于是整理一下字母和编号，于是我们有状态 $(u,x)$ 与状态 $(u,x+3w_1-3w_2)$ 是可以互相到达的。嵌套下去，假设我们令 $w'\gets 3w$，那么我们可以模意义下推出 $(w'_i-w'_j)$ 的全部加减组合。也就是形如 $\sum x_k(w'_i-w'_j), x_k\in\Z$ 的形式。这显然应当应用（扩展？）裴蜀定理：我们可以用这种方式得到所有 $\gcd(|w'_i-w'_j|)$ 的整数倍数。

进一步，根据 $w'\gets 3w$ 的转化可以提取一个 $3$。

此时我们的结论变成：$(u,x)$ 与状态 $(u+3k\gcd(|w_i-w_j|)),k\in \Z$ 是可以互相到达的。其中 $w$ 是所有和 $u$ 相连的边的边权。

我们尝试进一步扩展结论，考虑是否状态 $(u,x)$ 与状态 $(u,x+3w_1-3w_2)$ 是可以互相到达的，而无需保证 $w_1,w_2$ 是和 $u$ 相连的边。这样我们可以把上面的结论一般性地扩展给所有点（因为统一了 $\gcd$）。

事实上是可以的。

> 证明：
> 
> 我们先考虑证明能不能把 $w_1,w_2$ 换成另外一个点相连的两条边。显然我们可以先证明可以换相邻点，从而由于图连通，可以归纳下去证明可以换所有点。
> 
> 考虑我们先一步走到 $v$ 得到 $(v,2d+w)$，再到达 $(v,2d+w+3k(w_1-w_2))$，然后从这个状态开始在 $(u,v)$ 之间反复横跳。从而我们可以到达所有的 $(u,2^id+(2^i-1)w+2^{i-1}\cdot 3k(w_1-w_2))$，其中 $i$ 是一个偶数。我们不妨考虑 $i=2\varphi(p)$，此时可以发现由于前面我们所有的状态转移都是可以互相到达的，所以 $(u,d)$ 与 $(u,d+2^{-1}\cdot 3k(w_1-w_2))$ 也是可以互相到达的。
> 
> 显然 $2^{-1}$ 并没有什么用，$k\gets 2k$ 即可。统一一下字母，$x\gets d$，得出 $(u,x)$ 和 $(u,x+3k(w_1-w_2))$ 是可以互相到达的。

所以现在 $w_1,w_2$ 可以取与任何一个点相连的两条边。我们进一步证明这两条边也可以不点相邻。

> 证明：
> 
> 继续使用归纳证明，我们只需证明可以把其中一条边换到相邻点的一条边也有正确性。这样一直换下去由于图连通，可以覆盖任取两条边的情况。
> 
> 考虑 $u,v$ 之间的边为 $a$，$u$ 上的另一边为 $b$，$v$ 上的另一边为 $c$。我们直接有 $(u,x)$ 与 $(u,x+3k(a-b))$ 互相可达，由刚刚证明的结论有 $(u,x)$ 与 $(u,x+3k(a-c))$ 互相可达。令第二个结论中 $x\gets x+3k(a-b)$，那么有 $(u,x)$ 与 $(u,x+3k_1(b-a)+3k_2(a-c))$ 互相可达。考虑 $k_1=k_2$，有 $(u,x)$ 与 $(u,x+3k(b-c))$ 互相可达。
> 
> 归纳地，下一步只需令 $x\gets x+3k(b-c)$，然后继续向相邻点换边，把 $c$ 抵消掉即可。由于图连通，显然可以覆盖任取两条边的全部情况。

于是我们证明了 $w_1,w_2$ 可以是任意两条边的边权。所以与之前同理，这次我们往 $\gcd$ 里塞所有边的边权差的 $\gcd$。这是经典的好求的东西，可以用辗转相除法转化为所有边权和 $w_1$ 的边权差的 $\gcd$。

所以不妨记 $G$ 表示这个 $\gcd$，那么所有状态 $(u,x)$ 与状态 $(u,x+3kG)$ 都互相可以到达。于是我们直接把这样的状态划分成等价类，整个问题可以在 $\bmod 3G$ 剩余系下考虑。

目前我们知道 $x\equiv y\pmod{3G}$ 和 $x\equiv y\pmod p$ 的状态 $(u,x)$ 和 $(u,y)$ 是可以互相到达的。直接合并方程，这等价于 $x\equiv y\pmod{\gcd(3G,p)}$。为了防止有奶龙像我一样不会合并同余方程，我把做法写在这里：

> 考虑 $\begin{cases}x=3Gm_1+r\\y=3Gm_2+r\end{cases},\begin{cases}x=pm_3+r'\\y=pm_4+r'\end{cases}$。两者对 $\gcd(3G,p)$ 取模后前面的项都会消掉，于是正推是正确的。反推是显然的，因为 $\gcd(3G,p)\le\min(3G,p)$。所以两者等价。

于是直接令 $p\gets \gcd(3G,p)$，继续考虑。

人类智慧地，我们发现所有边的边权都满足 $w_1-w_2\equiv 0\pmod{G}\Rightarrow w_1\equiv w_2\pmod{G}$，所以不妨表示 $w_i=m_iG+k$。考虑这个 $k$ 在这里很烦人，我们考虑给所有边权全部减去 $k$，状态里面 $x\gets x+k$，可以发现这样做我们对状态转移的刻画是等价的：

> $(u,x)$ 事实上是 $(u,x-k)$，向 $v$ 走一步变成 $2(x-k)+w+k=2x+w-k$，再填一个 $k$ 回去变成 $(v,2x+w)$。形式没有变化。

这样做的好处是所有边权全都是 $G$ 的倍数。那么状态 $(u,x)$ 走到任何一个点 $v$，$x$ 的变化都形如 $(v,2^ix+jG)$，显然由于整个东西在 $\bmod p$ 剩余系下考虑，而 $p$ 里面有 $3G$ 的因子，所以 $0\le j\le 2$。

同样地我们去考虑 $i$ 的缩减。还记得 $(u,x)$ 和 $(u,4x+3w)$ 互相可达的结论吗？显然在这里因为和上面一样的原因 $3w$ 等价于 $0w$ 就可以抹掉，所以 $(u,x)$ 和 $(u,4x)$ 互相可达。

利用这个结论，考虑 $(v,2^ix+jG)$ 和 $(v,2^{i+2}x+4jG)$ 互相可达。$4jG$ 仍然因为和上面一样的原因等价于 $jG$，从而 $(v,2^ix+jG)$ 和 $(v,2^{i+2}x+jG)$ 互相可达。

所以在 $j$ 确定的时候，$i$ 只有 $0,1$ 是有用的。

所以在对于确定的 $x$，每个节点上只有 $6$ 个状态是有用的。

回到问题本身，我们的问题变成 $(t,k)$ 能否到达 $(s,r+k)$（注意倒过来做）。事实上根据我们一开始反复横跳一定可以跳回本身的结论扩展下去，任意两个可达的状态也一定是互相可达的。

> 证明：
>
> 假设 $(u,x)$ 可达 $(v,2^ix+jG)$。那么我们考虑证明后者也可达前者。
>
> 不妨进行反复横跳，假设来回横跳一次产生的边权贡献是 $lG$，那么来回横跳 $i$ 次后会得到 $(u,2^{2i}x+\frac{4^i-1}{3}lG)$（后半部分是 $\sum\limits_{j=0}^{i-1} 4^j lG$ 的通项）。考虑 $i=\varphi(p)$，此时得到 $(u,x)$。

这样做的好处是可达性转成了连通性，好做了很多。

处理询问时，我们考虑 $(t,k)$ 事实上是 $(t,2^0k+0G)$，也就是我们确定 $x=k$ 了。所以我们先找出若干对 $(i,j)$ 使得其满足数值关系上允许成立（也就是存在一对 $o_1,o_2$，使得 $2^{2o_1+i}k+(j+3o_2)G\equiv r+k\pmod p$，这里 $o_1,o_2$ 的意义就是补齐被模掉的部分），然后判定 $(t,0,0)$ 是否与 $(s,i,j)$ 连通即可。

前者显然等价于判断存在一个 $o_1$ 使得 $2^{2o_1+i}k\equiv r+k-jG\pmod p$，注意到 $2o_1$ 的循环节是 $\mathcal O(\varphi(p))$ 的，暴力预处理即可。后者则是使用并查集可以轻易实现。

注意需要特判一下边权全部相等的情况。此时 $G=0$ 可以看作是 $G=p$ 处理，方便我们进行除法和取模。其实在除法和取模处特判也行，只要保证在各处满足 $G=0$ 时的性质就可以了。

$n,m,q$ 同阶，时间复杂度为 $\mathcal O(n\alpha (n)+p)$。

简短的代码，使用 ACL 库的 `atcoder::dsu` 实现：

```cpp
using namespace atcoder;
dsu d(N*6);
int n,m,q,p;
struct Edge{
    int u,v,w;
} E[N];
int G,k;
int st(int u,int i,int j){
    return (i*3+j)*n+u;
}
bool exist[2][N*20];
int main(){
#ifdef Shun
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    ios::sync_with_stdio(false);
    cin>>n>>m>>q>>p;
    fr1(i,1,m){
        cin>>E[i].u>>E[i].v>>E[i].w;
        G=__gcd(G,abs(E[i].w-E[1].w)); 
    }
    p=__gcd(3*G,p);
    if(G) k=E[1].w%G;
    else k=E[1].w;
    fr1(i,1,m) E[i].w=E[i].w-k;
    fr1(_,1,m){
        int u=E[_].u,v=E[_].v,w=E[_].w;
        fr1(i,0,1){
            fr1(j,0,2){
                d.merge(st(u,i,j),st(v,i^1,((j<<1)+(G?w/G:0))%3));
                d.merge(st(v,i,j),st(u,i^1,((j<<1)+(G?w/G:0))%3));
            }
        }
    }
    fr1(i,0,1){
        int o1=k;
        do{
            exist[i][i?(o1<<1)%p:o1]=1;
            (o1<<=2)%=p;
        }while(o1!=k);
    }
    while(q--){
        int s,t,r;
        cin>>s>>t>>r;
        bool ans=0;
        fr1(i,0,1)
            fr1(j,0,2)
                if(exist[i][((r+k-j*G)%p+p)%p]&&d.same(st(t,0,0),st(s,i,j))) ans=1;
        cout<<(ans?"YES":"NO")<<'\n';
    }
    ET;
}
//ALL FOR Zhang Junhao.
```

---

## 作者：Sky_Maths (赞：0)

## 说明
设 $(u, x)$ 表示当前在 $u$，权值为 $x$，若无特殊说明 $u, v$ 为任意相连两点，边权为 $w$。

## 性质
### 性质1
$$(u, x)\leftrightarrow (v, 2x + w)$$

考虑从 $(u, x)$ 走 $1$ 步到 $(v, 2x + w)$，来回走 $2\varphi(p)$ 步从 $(u, x)$ 走回 $(u ,x)$。

### 性质2
$$(u, x)\leftrightarrow (u, 4x + 3w)$$

即走过去再走回来。

### 推论1
$$(u, x)\leftrightarrow (u, x + 3(w_1 - w_2))$$

因为 $(u, 4x + 3w_1)\leftrightarrow(u, x)\leftrightarrow(u, 4x + 3w_2)$，而 $4$ 在 $\bmod mod$ 下是有逆元的，所以可以用 $x$ 换元 $4x$。

### 推论2
$(u, x)\leftrightarrow(u, y)$ 当 $d_u'|x - y$，其中 $d_u' = (3\gcd{w_{u1} - w_{u2}}, mod)$。即 $(u, x)$ 中的 $x$ 处于 $\bmod d_u'$ 意义下。

由推论 1 可得。

### 推论3
因为有 $(u, x)\leftrightarrow (v, 2x + w)$，可以进一步令 $d_u' = \gcd(d_u', 2d_v')= \gcd(d_u', d_v')$ （因为 $\gcd(2, mod) = 1$） 所以所有的 $d_u'$ 都是相同的等于 $\gcd(3d, mod), d = 3\gcd\{w_i - w_j\}$。

## 思路
于是只用考虑 $(s_i, 0)$ 与 $(t_i, r_i)$ 在 $\bmod d'$ 意义下是否联通即可（并查集）。

发现不太好做，状态太多。

因为 $(u, x)\leftrightarrow (u, 4x + 3w_i), w_i = w_i'd + t$，即 $(u, x)\leftrightarrow (u, 4x + 3(w_i'd + t))$，即 $(u, (x + t) - t)\leftrightarrow (u, 4(x + t) + 3w_i'd - t)$，即$(u, x - t)\leftrightarrow (u, 4x + 3w_i'd - t)\leftrightarrow (u, 4x - t)$。

令 $(u, x)\leftrightarrow (u, x + t)'$（是 + 而非 - ），即有 $(u, 2^0x)'\leftrightarrow (u, 2^2x)'$。

于是只需考虑 $(s_i, 0 + t)'$ 是否与 $(t_i, r_i + t)'$ 联通即可。

若将 $(u, x)'$ 表示为 $(u, 2^Px' + Qd)'\leftrightarrow (u, P, Q)$，则$P$ 只有奇偶性有意义，且 $d'|3d$，那么 $Q\in \{0, 1, 2\}$。

状态数就是 $O(n)$ 的。

## 实现
对于每条边，$(u, P, Q)\leftrightarrow (v, P + 1, 2Q + w')$。

还需要判断当经过边的奇偶性确定的情况下这种路径长度是否可以走出来（和 $w_i$ 有关的由 $Q$ 统计），即 `exist` 数组。

关于为什么要用 `exist` 数组，也许是因为并不是所有的 $P, Q$ 都符合要求（只确定了 $(s, P, Q)$ 与 $(t, 0, 0)$ 的关系，没有确定 $(s, 0)$ 和 $(s, P, Q)$ 的关系？），欢迎讨论。

## 代码
```cpp
int main() {
	read(n, m, q, mod);
	rep (i, 1, 6 * n) pa[i] = i;
	rep (i, 1, m) {
		read(u[i], v[i], w[i]);
	}
	d = mod;
	rep (i, 2, m) {
		d = gcd(d, abs(w[i] - w[1]));
	}// 统计 d
	rem = w[1] % d;
	mod = gcd(d * 3, mod); // 这里用 mod 代替 d'
	rep (i, 1, m) {
		w[i] = (w[i] - rem) / d % 3;
	}// 预处理 wi（也可以不用预处理）
	rep (i, 1, m) {// 连边，维护并查集
		rep (P, 0, 1) {
			rep (Q, 0, 2) {
				merge(id(u[i], P, Q), id(v[i], 1 - P, Q * 2 + w[i]));
				merge(id(v[i], P, Q), id(u[i], 1 - P, Q * 2 + w[i]));
			}
		}
	}
	for (int i = 0, j = rem; i < (mod << 1); ++i, j = j * 2 % mod) {//phi(mod) < mod
		exist[i & 1][j] = 1;
	}
	rep (i, 1, q) {
		int s, t, r;
		read(s, t, r);
		int ans(0);
		rep (P, 0, 1) {
			rep (Q, 0, 2) {
				if (find(id(t, 0, 0)) == find(id(s, P, Q))) {
					ans |= exist[P & 1][(r + rem - Q * d % mod + mod) % mod];
				}
			}
		}
		if (ans) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：xht (赞：0)

## [Walk on Graph](https://atcoder.jp/contests/agc031/tasks/agc031_f)

### 题意

- 给定一张 $n$ 个点 $m$ 条边的连通无向图，边有长度。
- 定义一条路径的长度为，设这条路径经过的边的长度依次为 $l_{1\dots k}$，则路径长度为 $\sum_{i=1}^{k} l_i2^{i-1}$。
- 有 $q$ 次询问，每次给定 $s,t,r$，求是否存在一条 $s \to t$ 的路径，满足其长度模 $P$ 的值为 $r$。
- $n,m,q \le 5 \times 10^4$，$P \le 10^6$ 且为奇数。

### 题解

倒过来考虑这个问题，走一条边 $c$ 就是 $x\to 2x+c$，因为 $P$ 是奇数，所以 $2$ 有逆元，即这是一个双射，所以一定能回到自己。

注意到一个点走两次一条边会回到自己，$x\to 4x+3c$，那么如果有另一条边 $c^\prime$，则我们能凑出 $3(c-c^\prime)$。记 $g$ 是所有边权之差以及 $P$ 的 $\gcd$，那么我们只需要在模 $\gcd(3g, P)$ 意义下考虑这个问题即可（此时模数要么是 $g$ 要么是 $3g$）。

假设所有边模 $g$ 都为 $z$，那么令 $x^\prime=x+z$，将边权减去 $z$，走一步后新的 $x^\prime$ 会变成 $2(x^\prime-z) + (c+z) + z = 2x^\prime + c$，和原来的规则一样，所以我们可以认为在新的图中，每条边都是 $g$ 的倍数。

对于 $(1,x)$，其能到的状态可以写成 $(v, 2^px+qg)(0\le q<3)$ 的形式，由之前的变换 $x\to 4x+3c$，且 $c$ 是 $g$ 的倍数，得 $x$ 和 $4x$ 是等价状态，故 $0\le p<2$。这样新的图中点数就只有 $\mathcal O(n)$ 个了，用并查集连一下就好了。

### 代码

```cpp
const int N = 5e4 + 7, M = 1e6 + 7;
int n, m, q, P, a[N], b[N], c[N], f[N*6+1], g, z;
bool v[2][M];

inline int get(int x) {
	return x == f[x] ? x : f[x] = get(f[x]);
}

inline void merge(int x, int y) {
	f[get(x)] = get(y);
}

inline int id(int x, int y, int z) {
	return (x - 1) * 6 + y * 3 + z;
}

int main() {
	rd(n, m, q), rd(P);
	for (int i = 1; i <= m; i++)
		rd(a[i], b[i], c[i]), g = __gcd(g, abs(c[i] - c[1]));
	g = g ? g : P, P = __gcd(P, 3 * g), z = c[1] % g;
	for (int i = 1; i <= 6 * n; i++) f[i] = i;
	for (int i = 1; i <= m; i++) {
		int w = (c[i] - z) / g;
		for (int p = 0; p < 2; p++)
			for (int q = 0; q < 3; q++)
				merge(id(a[i], p, q), id(b[i], 1 - p, (2 * q + w) % 3)),
				merge(id(b[i], p, q), id(a[i], 1 - p, (2 * q + w) % 3));
	}
	for (int i = 0, j = z; i < P << 1; i++, (j <<= 1) %= P) v[i&1][j] = 1;
	for (int i = 1, s, t, r; i <= q; i++) {
		rd(s, t, r);
		bool ans = 0;
		for (int p = 0; p < 2; p++)
			for (int q = 0; q < 3; q++)
				if (get(id(t, 0, 0)) == get(id(s, p, q)))
					ans |= v[p][(r+z+(3-q)*g)%P];
		prints(ans ? "YES" : "NO");
	}
	return 0;
}
```

---

## 作者：Rorschachindark (赞：0)

[我的cnblogs博客](https://www.cnblogs.com/Dark-Romance/p/16811247.html)

[link](https://www.luogu.com.cn/problem/AT_agc031_f)
# Solution
非常厉害的题捏，可惜我什么都想不到/kk

我们首先转化一下，我们对于 $s\to t$ 计算这个长度变为 $t\to s$ 每次加入一个 $w$，当前权值 $x$ 就变为 $2x+w$。这样就不需要在乎长度了。

所以我们可以考虑暴力设计状态 $(u,x)$ 表示到了点 $u$ 当前长度为 $x$，那么我们的暴力的做法就是对于这个状态暴力并查集，最后对于 $s\to t$ 要求长度为 $r$ 的判断判断就是是否 $(t,0)$ 与 $(s,r)$ 连通即可。显然无法通过，我们考虑仔细观察性质。

---


1.如果 $(u,x)\to (v,y)$，那么我们同样存在 $(v,y)\to (u,x)$。

假设我们是 $u\to v$ 间存在一个真实长度为 $l$，值为 $w$ 的边，那么我们存在 $y=x2^l+w$，那么我们考虑来回走这条路径 $t$ 次，那么值即是 $x2^{tl}+w(\frac{2^{tl}-1}{2^l-1})$，这样的话因为模数不是质数似乎没法考虑，但是考虑到我们的路径都是长度为 $1$ 的边构成的，所以我们不妨考虑 $l=1$，可以发现 $t=2\varphi(p)$ 的时候我们是满足条件的，所以我们可以证明该性质。

为了方便，我们下面用 $(u,x)\leftrightarrow (v,y)$ 来表示这种关系。

---

2.如果图中存在两条边权值分别为 $a,b$，那么存在 $(u,x)\leftrightarrow (u,x+(a-b)\times 3)$。

首先我们先考虑 $u$ 连出两条权值为 $a,b$ 的情况，我们可以发现如下关系式：

$$(u,4x+3a)\leftrightarrow (u,x)\leftrightarrow (u,4x+3b)$$

因为 $4$ 在 $\mod p$ 的情况下是存在逆元的，所以 $4x$ 其实在模 $p$ 条件下可以表达任意值，所以我们可以推出：$(u,x)\leftrightarrow (u,(a-b)\times 3)$。

我们考虑 $u$ 与 $v$ 存在连边的情况，假设 $u,v$ 连边权值为 $w$，那么我们走 $t$ 次的话就存在：$(u,x)\leftrightarrow (v,x2^t+w(2^t-1))$ ，取 $t=\varphi(p)$，可以发现 $(u,x)\leftrightarrow (v,x)$。

有了以上两个条件，我们发现我们不断拓展就可以得到该性质。

---

有了上面的两个性质以及裴蜀定理，我们其实可以发现（$w_i$ 是第 $i$ 条边的边权（长度）），如果设 $g=\gcd(w_i-w_j),i\not= j$，那么 $(u,x) \leftrightarrow (u,y)$ 当且仅当 $x\equiv y\pmod {\gcd(3g,p)}$，所以我们完全可以把 $p\to \gcd(3g,p)$。那么可以发现每一个 $w_i$ 都可以表示为 $tg+z,t\in \mathbb{Z}$ 的形式。

我们发现，如果把 $w_i$ 都减去 $z$，那么可以满足都是 $g$ 的倍数，同时如果我们设 $(u,x+z)^{'}=(u,x)$，那么对于一条边 $w$，我们可以发现：$(u,x+z)^{'}\leftrightarrow (v,2(x+z)+w-z)^{'}=(v,2x+w+z)^{'}$，所以就跟原来的转移相同了。

同时我们观察最后的查询形式，发现现在就是查询 $(t,z)^{'}$ 与 $(s,r+z)^{'}$ 是否连通了。我们观察我们的转移，发现是 $x\to 2x+w$ 的形式，而我们现在 $w$ 都是 $g$ 的倍数，而我们的 $p$ 至多是 $3g$，所以我们可以发现我们所有需要的 $x$ 都可以表示为 $z2^{2r+i}+jg,i\in \mathbb{Z},j\in \{0,1,2\}$。而我们对于 $u\to v$ 的权值为 $w$ 的边，我们可以发现：$(u,x)\leftrightarrow (u,4x+3w)\leftrightarrow (u,4x)$，也就是 $2$ 的指数奇偶性相同时是可达的。所以其实我们只需要记录 $z2^i+jg$ 这种形式。所以只有 $\Theta(6n)$ 个状态。所以这个时候我们就可以暴力跑并查集了，然后判一下就好了。

---

复杂度 $\Theta(n\log n)$，瓶颈在于并查集。
# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define MAXN 1000005

template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}
template <typename T> inline void chkmax (T &a,T b){a = max (a,b);}
template <typename T> inline void chkmin (T &a,T b){a = min (a,b);}

int n,m,T,mod,tot,fa[MAXN * 6],ind[MAXN][2][3],vis[2][MAXN];//ind[u][0/1][0/1/2]表示u点2^{0/1}*x+g*(0/1/2)
int findSet (int x){return fa[x] == x ? x : fa[x] = findSet (fa[x]);}
void unionSet (int u,int v){fa[findSet (u)] = findSet (v);}
bool checkit (int u,int v){return findSet (u) == findSet (v);}

struct edge{
	int u,v,w;
	bool operator < (const edge &p)const{return w < p.w;}
}seq[MAXN];

signed main(){
	read (n,m,T,mod);
	for (Int u = 1;u <= n;++ u)
		for (Int p = 0;p < 2;++ p)
			for (Int q = 0;q < 3;++ q) ind[u][p][q] = ++ tot;
	for (Int u = 1;u <= tot;++ u) fa[u] = u;
	for (Int i = 1;i <= m;++ i) read (seq[i].u,seq[i].v,seq[i].w);
	sort (seq + 1,seq + m + 1);int g = mod,z;
	for (Int i = 2;i <= m;++ i) g = __gcd (g,seq[i].w - seq[i - 1].w);
	z = seq[1].w % g;for (Int i = 1;i <= m;++ i) seq[i].w = (seq[i].w - z) / g,seq[i].w %= 3;
	mod = __gcd (3 * g,mod);
	for (Int i = 1;i <= m;++ i){
		int u = seq[i].u,v = seq[i].v,w = seq[i].w;
		for (Int p = 0;p < 2;++ p)
			for (Int q = 0;q < 3;++ q){
				unionSet (ind[u][p][q],ind[v][p ^ 1][(q * 2 + w) % 3]);
				unionSet (ind[v][p][q],ind[u][p ^ 1][(q * 2 + w) % 3]);
			}
	}
	for (Int i = 0,now = z;i < mod;++ i,now = now * 2 % mod) vis[i & 1][now] = 1;
	for (Int i = 1;i <= T;++ i){
		int u,v,r;read (u,v,r);swap (u,v);
		for (Int p = 0;p < 2;++ p)
			for (Int q = 0;q < 3;++ q) if (checkit (ind[u][0][0],ind[v][p][q]) && vis[p][(r + z - g * q % mod + mod) % mod]){
				puts ("YES");
				goto there;
			}
		puts ("NO");
		there:;
	}
	return 0;
}
```

---

