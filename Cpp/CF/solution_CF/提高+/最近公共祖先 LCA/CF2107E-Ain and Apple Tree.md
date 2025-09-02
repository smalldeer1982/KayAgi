# Ain and Apple Tree

## 题目描述

如果我也被从苹果树上掉下的苹果砸中，我能变得像牛顿一样擅长物理吗？

为了更擅长物理，Ain 想建造一棵苹果树，这样她就能被树上的苹果砸中。她的苹果树有 $n$ 个节点，根节点为 $1$。她将苹果树的权重定义为 $\sum \limits_{i=1}^n \sum \limits_{j=i+1}^n \text{dep}(\operatorname{lca}(i,j))$。

这里，$\text{dep}(x)$ 定义为从节点 $1$ 到节点 $x$ 的唯一最短路径上的边数。$\operatorname{lca}(i, j)$ 定义为在路径 $(1, i)$ 和 $(1, j)$ 上同时出现且 $\text{dep}(x)$ 值最大的唯一节点 $x$。

Ain 从一些旧书中得知，牛顿的苹果树的权重大约是 $k$，但具体的值已经丢失了。

作为 Ain 的朋友，你想为她建造一棵有 $n$ 个节点的苹果树，且树的权重与 $k$ 的绝对差不超过 $1$，即 $|\text{权重} - k| \le 1$。如果无法满足这一条件，请报告这一情况。

## 说明/提示

在第一个测试用例中，我们可以验证权重为 $0$。这满足条件，因为 $k = 1$，所以绝对差仅为 $1$。

在第二个测试用例中，不存在解，因为没有 $2$ 个节点的树的权重为 $1$、$2$ 或 $3$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2 1
2 2
4 0
5 7
5 5```

### 输出

```
Yes
1 2
No
Yes
1 2
1 3
1 4
Yes
1 3
3 5
4 5
3 2
Yes
1 2
2 3
2 4
2 5```

# 题解

## 作者：StayAlone (赞：7)

比官方题解更容易的考虑方式（？

容易发现，一棵树的 weight 就是 $\sum\limits_{i\ne 1} \binom{siz_i}{2}$，其中 $siz_i$ 表示 $i$ 号结点子树的大小。这样，每一对结点 $(u, v)$ 在其 $\operatorname{LCA}$ 的每个祖先处（除了根）恰好算了一次，即 $dep_{\operatorname{LCA}}$ 次。

考虑这样一个事实：除非 $k$ 超出最大范围，否则一定存在一个严格递减序列 $a_i$，满足 $a_1<a_0=n$，$|k-\sum\limits_{i\ne 0}{\binom{a_i}{2}}|\leq 1$。构造方式就是贪心地每次找到最大的 $x$ 满足 $\binom{x}{2}\leq k$。更具体地，去掉绝对值该结论仍成立。后附证明。

令 $a_i$ 表示深度为 $i$ 的子树的大小即可。考虑 $siz=1$ 的子树不造成贡献，如下构造即可：

![](https://cdn.luogu.com.cn/upload/image_hosting/z575yi8g.png)

时间复杂度 $\mathcal O(n)$。

```cpp
int n; ll k;
 
il void solve() {
    read(n, k); vector <int> a;
    rep2(i, n - 1, 1) {
        ll p = 1ll * i * (i - 1) / 2;
        if (k >= p) k -= p, a.eb(i);
    }
    if (k > 1) return puts("No"), void();
    int tot = 1, rt = 1, lst = n; puts("Yes");
    for (auto v : a) {
        rep1(_, 1, lst - v) printf("%d %d\n", rt, ++tot);
        lst = v; rt = tot;
    }
}
 
int main() {
    for (int T = read(); T--; ) solve();
    return 0;
}
```

证明：

- 等价于证明贪心结束时，$k=0$ 或 $k=1$。
- 若 $k=2$，则一定已经选择了 $x=2$（否则选上后 $k=1$）。
- 则选择 $x=2$ 前，$k=3$。同理知一定选择了 $x=3$，以此类推，发现 $k$ 的原值大于最大阈值，矛盾。
- $k>2$ 同理。

---

## 作者：sunkuangzheng (赞：4)

Fun Fact：这道题最开始投的是 2C！

首先分析我们能构造出的最大 weight，不难发现此时树一定时一条链：如果不是链，将分叉处的某一个子树挂在另一个子树下面会让 weight 变大。此时的 weight 是 $m = \dfrac{n(n-1)(n-2)}{6}$，如果 $k > m+1$ 则肯定无解。

考虑从最大的 $m$ 开始往下调整，考虑将链底下的点向上挪 $x$ 步，$m$ 的值会减少 $\dfrac{x(x+1)}{2}$。这个过程可以反复进行，但是要求是后执行上移操作的点的深度不能比之前的更小。

我们每次找到最大合法的 $x$，将链最底下的点上移 $x$ 步，直到 $m \le 1$。注意到令 $f_i = \dfrac{i(i+1)}{2}$，当 $i \ge 2$ 时一定有 $2f_i \le f_{i+1}$，因此 $m - f_x < f_x$ 对所有 $x \ge 2$ 成立，即下一次要提升的高度会严格变小。当 $x=1$ 时 $m \le 2$，此时提升一次后 weight 和 $k$ 的差不会超过 $1$，因此这个构造满足条件。

---

## 作者：SUNCHAOYI (赞：3)

首先考虑无解的情况。

当这棵树为一条链时，答案取到最大值。证明很简单，假设存在一个节点 $u$ 至少有 $2$ 个孩子节点，任取两个 $v_1,v_2$，则 $\text{dep}(\operatorname{LCA}(v_1,v_2)) = \text{dep}(u)$，此时进行调整，将 $v_1$ 与 $v_2$ 改为直接相连，能够增大答案。即断开 $(u,v_2)$，连接 $(v_1,v_2)$，则有 $\text{dep}(\operatorname{LCA}(v_1,v_2)) = \text{dep}(v_1) > \text{dep}(u)$。因此假设不成立，命题得证。

令 $f_i$ 表示 $n = i$ 时的形成链的答案，则有：

$$f_n = \sum _{i = 0}^{n - 1} i \times (n - i - 1) = (n - 1)\sum_{i = 0}^{n - 1}i - \sum_{i = 0}^{n - 1} i^2\\
=\frac{n(n - 1)^2}{2} - \frac{n(n - 1)(2n - 1)}{6} = \frac{n(n - 1)(n - 2)}{6}
$$

因此 $k > ans + 1$ 时无解。

首先构造出 $i$ 与 $i + 1$ 连边所形成的链，之后考虑进行调整。初始时 $l = 1,r = n$，$[l,r]$ 形成主链。每次考虑将 $r - 1$ 与 $r$ 断边并将 $r$ 连至 $l$ 上。分析可知，对答案的**减少量**为 $(f_r - f_{r - 1}) - (f_{l + 1} - f_l) - (l - 1) (r - l - 1)$，化简可得 $\dfrac{(r - 1)(r - 2) - l(l - 1)}{2} - (l - 1)(r - l - 1)$。若可以操作，则完成后 $r \gets r - 1$，否则 $l \gets l + 1$。重复调整操作直至符合条件。

接下去证明该调整操作的可行性。显然，在不断操作后，$l$ 与 $r$ 会不断趋近。当 $r - l = 2$ 时，消去 $r$ 并代入得，该操作对答案的减少量为 $\frac{(l + 1)l - l(l - 1)}{2} - (l - 1)(l + 2 - l - 1) = 1$，而 $r - l = 1$ 时不会改变答案。能够改变答案的减少量为 $1$，因此当有解时，总是存在一种调整方案。

代码如下：

```cpp
#include <bits/stdc++.h>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define pii pair <int,int>
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
inline ll read ();
int t,n;ll k;
int main ()
{
    t = read ();
    while (t--)
    {
        n = read ();k = read ();
        vector <vector <int>> ve (n + 1);
        ll res = 1ll * n * (n - 1) * (n - 2) / 6;
        if (res + 1 < k) {puts ("No");continue;}
        puts ("Yes");
        ll l = 1,r = n;res -= k;
        while (abs (res) > 1) 
        {
            ll del = (1ll * (r - 1) * (r - 2) - 1ll * l * (l - 1)) / 2 -  1ll * (r - l - 1) * (l - 1);
            if (del <= res) res -= del,ve[l].push_back (r--);
            else ++l;
        }
        for (int u = 1;u <= n;++u)
            for (auto v : ve[u]) printf ("%d %d\n",u,v);
        for (int i = 1;i < r;++i) printf ("%d %d\n",i,i + 1);
    }
    return 0;
}
inline ll read ()
{
    ll s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
    {
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

