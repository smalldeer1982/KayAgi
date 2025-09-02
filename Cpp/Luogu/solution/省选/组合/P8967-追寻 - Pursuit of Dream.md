# 追寻 | Pursuit of Dream

## 题目背景

“遇到自己喜欢的人或事情的时候，千万不要放弃”

“要一直追寻下去…”

“因为即使成功希望渺茫，也有可能”

有谁和我说过这句话，脑海中忽然闪过一下，被当做无用的激励一同忘却了。现在想要回忆，却总也记不起来。

好不容易来人间一趟，那就别留下遗憾。

房檐落下的雨滴有规律的敲着石砖，那夜的雨声中，却也悄无声息了。

逆着风吹干眼泪，说不出口的痛越藏越多，腐烂在肚子里，却又不知道彼此心知且肚明，所以无法孕育出美好的结局，只会是恋者相残的戏码不停上演。

---

 看见了漫天星野坠落在你的眼底，从此甘愿在那海底般低压的梦境中堕落。

三千尺星空的光辉映照不出那人的身影，璀璨中徒留神明思故人；那人却散入了或许碎散的星辰大海，让神明寻觅了一生。

那些无法兑现的渴望，会日渐荒芜，然后梦境会失去生机，裂缝中会蔓出黑暗，泪无葬身之地。

是神明告诉我的，可是我不信，因为没有时间还等着我空想了。

神明还说，人死了以后，提前离开的亲人都会在另外一个世界等你。

其实，我也会想，这一定就是另外一个世界。

## 题目描述

在 $n$ 维空间中有一个梦想。这梦想坐落在 $(d_1, d_2, \ldots, d_n)$ 的地方。而你从 $(0, 0, \ldots, 0)$ 开始，开启寻梦的旅程。

你的步伐轻缓，每一步只能走一个单位长度。你并不知道你的梦想位于哪里，所以你只能随机选择 $n$ 个正方向中的一个，然后向这个方向走一步。也就是说，在 $[1, n]$ 中均匀随机选择一个正整数 $h$，然后，使你在第 $h$ 维的坐标变成原来的坐标加一。

然而，天有不测风云。在你走每一步的过程中，你会有 $p = \sum_{i = 1}^k p_i$ 的概率散入天际，并开始一段新的旅程。你会在 $k$ 个地点中的一个重新开始这段旅程，其中第 $i$ 个地点的坐标是 $(a_{i,1}, a_{i,2}, \ldots, a_{i,n})$，从这里重新开始的概率为 $p_i$。

那么，期望下，你离到达这个梦想还需要多少步呢？

## 说明/提示

**【样例解释 \#1】**

这是你的一种追寻梦想的方式：

你从 $(0,0)$ 出发，走一步到 $(1,0)$，再走一步到 $(2,0)$，再走一步到 $(3,0)$，但是在路上散入天际，从 $(0,0)$ 重新开始旅程。

然后继续从 $(0,0)$ 出发，走一步到 $(0,1)$，再走一步到 $(1,1)$，但是在路上散入天际，从 $(0,0)$ 重新开始旅程。

接着从 $(0,0)$ 出发，走一步到 $(1,0)$，再走一步到 $(1,1)$，找到了你的梦想。

在这种情况下，你需要 $7$ 步到达这个梦想。发生这种情况的概率是 $4^{-7}$。

---

**【样例解释 \#2】**

答案为 $\frac{505}{24} \approx 21.041667$。  
不难验证 $291154624 \times 24 \equiv 505 \pmod{998244353}$，故应输出 $291154624$。

---

**【样例解释 \#3】**

答案为 $\frac{1399505}{21519} \approx 65.035782$。

---

**【数据范围】**

**本题采用捆绑测试且使用子任务依赖。**

| 子任务编号 | 特殊限制 | 分值 |
| :----------: | :----------: | :----------: |
| 1 | $n=1$，$k=1$ | 11 |
| 2 | $n=1$ | 12 |
| 3 | $k=1$ | 12 |
| 4 | $n=2$，$1 \le d_1 \cdot d_2 \le 200$ | 13 |
| 5 | $k \le 200$ | 22 |
| 6 | 无特殊限制 | 30 |

对于 $100 \%$ 的数据：

- $1 \le n \le 100$，$1 \le k \le 10000$。
- $d_i \ge 0$，$\sum_i d_i \le 10^7$。
- $0 \le a_{i, j} \le {10}^7$。
- $x_i \ge 1$，$\sum_i x_i < {10}^8$。此即保证了 $p_i > 0$ 和 $p < 1$。
- 保证存在一个 $i \in [1, k]$ 使得对于每个 $j \in [1, n]$ 均有 $a_{i,j} \le d_j$。
- 保证每个 $(a_{i, 1}, a_{i, 2}, \ldots, a_{i, n})$ 作为空间中的点互不相同。
- 保证每个 $x_i$ 在所有可能的组合中等概率随机生成。

---

**【提示】**

由于保证了 $x_i$ 是随机生成的，可以说明以接近 $1$ 的概率答案在模意义下存在。事实上，一个当 $x_i$ 尚不确定时以合理地高的概率给出正确答案的算法足以通过本题，考察复杂的模意义下的有理数的处理不是我们的本意。

样例中的 $x_i$ 不是随机生成的，仅为理解题意所用。

## 样例 #1

### 输入

```
2 1
1 1
0 0 50000000
```

### 输出

```
14
```

## 样例 #2

### 输入

```
2 1
1 2
0 0 20000000
```

### 输出

```
291154624
```

## 样例 #3

### 输入

```
3 3
2 3 4
2 1 0 30000000
1 2 3 19000000
2 3 4 1000000
```

### 输出

```
430536142
```

# 题解

## 作者：离散小波变换° (赞：12)

## 题解

考虑设 $f_i$ 表示，从第 $i$ 个地点出发，到达终点的期望步数。特别地，记 $f_0$ 表示从起点 $(0,0,\cdots,0)$ 出发到达终点的期望步数。比较显然的思路是设法算出 $f_i$ 之间的表达式。

从一个点出发，走过了若干步后，总是会到达以下两个情况之一：

- 失足从 $k$ 个起点中的某一个从头来过；
- 顺利到达终点。

前者很不容易计算，因此考虑先算出第二种情况的概率，再回来算出第一种情况。

从 $(a_1,a_2,\cdots,a_n)$ 到达 $(d_1,d_2,\cdots,d_n)$ 的总步数，显然一定是 $s=\sum |d_i-a_i|$。发生的概率是多少呢？需要注意以下两种情况：

- 在前进的时候不慎从头开始了；
- 某一维的值超过了对应的 $d_i$，此时不可能顺利到达终点，只有可能从某个地方从头来过。

前者需要保证在 $s$ 步内都没有失足，后者则可以转化为从 $s$ 个球里取 $d_1-a_1$ 个红球，取 $d_2-a_2$ 个蓝球，……，这样的组合问题。于是得到概率：

$$q=\dfrac{s!}{(d_1-a_1)!(d_2-a_2)!\cdots (d_n-a_n)!\times n^s}\times (1-p)^s$$

特别地，若存在 $d_i<a_i$，则 $q=0$。

对于 $i=0,1,\cdots,k$ 都可以计算出对应的 $q_i$。接下来考虑失足的情况。

似乎 $f_i$ 的值会与 $f_j\ (j=1,2,\cdots,k)$ 有关。但是我们不希望用 $f_j\ (j=1,2,\cdots,k)$ 写到 $f_i$ 的表达式中，这会变成一个 $k$ 阶的线性方程组，用朴素的高斯消元无法求解。但是注意到从 $f_i$ 失足掉进某一个 $f_j$ 中，这个过程与 $i$ 无关。于是考虑设一个中间变量 $g$ 表示从一个失足过程开始（还没有决定好掉到 $1\sim k$ 中的哪个位置）需要的期望步数。

容易得到 $g$ 的表达式：

$$g=\sum_{i=1}^k \dfrac{p_i}{p}f_i$$

现在继续计算 $f$ 的表达式：

$$f_i=q_is_i+(1-q_i)g+?$$

到这一步，发现很难表示出从起点出发一直到失足前到底走了多少步。考虑使用容斥，假设压根没有终点只是到处乱走，那么在失足前的期望步数显然就是 $\dfrac{1}{p}$。现在加上了终点，那么走到终点之后再失足这一部分的期望步数就消失了。这一部分的期望应该是 $q_i\times \left(\dfrac{1}{p}+s_i\right)$。换言之，问号部分的值应该为：

$$\frac{1}{p}-q_i\times \left(\dfrac{1}{p}+s_i\right)$$

整理一下 $f$：

$$f_i=(1-q_i)\left(g+\frac{1}{p}\right)$$

现在考虑解出 $g$。将 $f_i$ 代入到 $g$ 的表达式里：

$$g=\sum_{i=1}^k \dfrac{p_i}{p}\times(1-q_i)\left(g+\frac{1}{p}\right)$$

将含有 $g$ 的项全部整理到等号的左侧：

$$\left(1+\sum_{i=1}^k \dfrac{p_i}{p}(q_i-1)\right)g=\sum_{i=1}^k\dfrac{p_i}{p}\times \left(\dfrac{1}{p}-\dfrac{q_i}{p}\right)$$

其中 $q_i,s_i,p_i$ 都很容易计算，那么就可以愉快地解出 $g$ 了。将其代入到 $f$ 的表达式里，即可解出 $f$ 的值。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
const int MOD = 998244353;
int qread(){
    int w=1,c,ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
int qpower(int x, int y){
    int r = 1;
    while(y){
        if(y & 1) r = 1ll * r * x % MOD;
        x = 1ll * x * x % MOD, y >>= 1;
    }
    return r;
}
const int MAXT = 1e7 + 3;
const int MAXN = 1e2 + 3;
const int MAXK = 1e4 + 3;
int o = 1e7, n, k, p, g;
int D[MAXN], S[MAXK], Q[MAXK], P[MAXK], F[MAXK];
int M[MAXT], N[MAXT], X[MAXT], Y[MAXT], A[MAXK][MAXN];
int main(){
    n = qread(), k = qread();
    M[0] = 1, N[0] = 1, X[0] = 1;
    up(1, o, i) M[i] = 1ll * M[i - 1] *   i  % MOD;
    up(1, o, i) X[i] = 1ll * X[i - 1] * M[i] % MOD;
    Y[o] = qpower(X[o], MOD - 2);
    dn(o, 1, i) Y[i - 1] = 1ll * Y[i] * M[i    ] % MOD;
    up(1, o, i) N[i]     = 1ll * Y[i] * X[i - 1] % MOD;
    up(1, n, i) D[i] = qread();
    up(1, k, i){
        up(1, n, j) A[i][j] = qread(); P[i] = qread();
        P[i] = 1ll * P[i] * qpower(1e8, MOD - 2) % MOD;
        p = (p + P[i]) % MOD;
    }
    up(0, k, i){
        bool f = 0;
        up(1, n, j) if(D[j] < A[i][j]) f = true;
        up(1, n, j) S[i] += D[j] - A[i][j];
        if(f == true) Q[i] = 0; else {
            Q[i] = 1ll * M[S[i]]
                * qpower(qpower(n, S[i]), MOD - 2) % MOD 
                * qpower(1 - p + MOD, S[i]) % MOD;
            up(1, n, j) Q[i] = 1ll * Q[i] * N[D[j] - A[i][j]] % MOD;
        }
    }
    int u = 0, v = 1, np = qpower(p, MOD - 2);
    up(1, k, i)
        u = (u + 1ll * P[i] * np % MOD * (np - 1ll * Q[i] * qpower(p, MOD - 2) % MOD + MOD) % MOD) % MOD;
    up(1, k, i)
        v = (v + 1ll * P[i] * np % MOD * (Q[i] - 1 + MOD) % MOD) % MOD;
    g = 1ll * u * qpower(v, MOD - 2) % MOD;
    up(0, k, i)
        F[i] = (1ll * (1 - Q[i] + MOD) * g % MOD + np - 1ll * Q[i] * qpower(p, MOD - 2) % MOD + MOD) % MOD;
    printf("%d\n", F[0]);
    return 0;
}
```

---

## 作者：mc123456 (赞：3)

神仙期望（确信）。

## 分析

对于期望题，通常考虑 dp。这里设 $f_i$ 表示从第 $i$ 个点走到终点的期望步数。那么 $f_i$ 就是两部分的和，一部分是直接走到终点的期望，一部分是散入天际后再走到重点的期望。

### 直接走到终点

对于第一部分，令 $q_i$ 表示从第 $i$ 个点直接走到终点的概率，$P$ 表示 $\sum\limits_{i = 1}^{k}{p_i}$。那么我们可以发现：

+ 若 $\exists j, a_{i, j} > d_j$，那么第 $i$ 个点永远无法直接走到终点，即 $q_i = 0$。

+ 否则 $\forall j, a_{i, j} \leq d$，那么第 $i$ 个点想直接走到终点需要走 $s_i = \sum\limits_{j = 1}^{n}{d_j - a_{i, j}}$ 步。每步不散入天际的概率是 $1 - P$，总的不散入天际的概率是 $(1 - P)^{s_i}$。走 $s_i$ 步一共有 $n^{s_i}$ 种走法，其中只有 $\dfrac{s_i!}{\prod\limits_{j = 1}^{n}{(d_j - a_{i, j})!}}$ 种走法是可以到达终点的。故此时有：

  $$
  q_i = (1 - P)^{s_i} \cdot \dfrac{1}{n^{s_i}} \cdot \dfrac{s_i!}{\prod\limits_{j = 1}^{n}{(d_j - a_{i, j})!}}
  $$

那么这一部分的期望步数就是 $q_i \cdot s_i$。

### 散入天际

这一部分较为复杂。如果直接考虑用 $f_j$ 来表示 $f_i$，则 $f$ 成了一个 $k$ 元线性方程组，那么使用高斯消元将有 $O(k^3)$ 的复杂度，显然无法通过此题。

注意到无论从哪里散入天际，这之后走到终点的期望都是一定的，不妨设这个期望为 $r$。那么我们只需考虑从第 $i$ 个点走，期望散入天际的步数 $g_i$，并将这两个数求和即可。

如此可以轻易得到 $r$ 的表达式：

$$
r = \sum\limits_{i = 1}^{k}{\dfrac{p_i \cdot f_i}{P}}
$$

对于不考虑走到终点停下，期望散入天际的步数，可以得出为 ${g_1}_i = \sum\limits_{j = 1}^{\infty}{j \cdot (1 - P)^{j - 1} \cdot P} = \dfrac{1}{P}$。若走到了终点，那么这一部分期望就为走到终点的期望加上走到终点后的期望，为 ${g_2}_i = q_i \cdot (s_i + \dfrac{1}{P})$。那么总的期望散入天际的步数就是这两个的差，即：

$$
g_i = {g_1}_i - {g_2}_i = \dfrac{1}{P} - q_i \cdot (s_i + \dfrac{1}{P}) = (1 - q_i) \cdot \dfrac{1}{P} - q_i \cdot s_i
$$

### 推式子

综合上述两部分，我们就得到了 $f_i$ 的表达式，即：

$$
f_i = q_i \cdot s_i + (1 - q_i) \cdot r + g_i = (1 - q_i) \cdot (r + \dfrac{1}{P})
$$

再根据 $r = \sum\limits_{i = 1}^{k}{\dfrac{p_i \cdot f_i}{P}}$，将 $f_i$ 代入，得：

$$
r = \sum\limits_{i = 1}^{k}{\dfrac{p_i \cdot (1 - q_i) \cdot (r + \dfrac{1}{P})}{P}}
$$

移向，整理，通分，得：

$$
r = \dfrac{\sum\limits_{i = 1}^{k}{p_i \cdot (1 - q_i)}}{P^2 - P \cdot \sum\limits_{i = 1}^{k}{p_i \cdot (1 - q_i)}}
$$

最后，将 $r$ 代回，得到：

$$
f_0 = (1 - q_0) \cdot (r + \dfrac{1}{P})
$$

$f_0$ 即为答案。

时间复杂度因实现关系可为 $O(kn + (k + n) \log{V} + V)$ 或 $O(kn\log{V} + V)$，均可通过本题（事实上时间复杂度略高的代码以几乎相同的速度和更小的空间通过了本题）。

## 代码

时间复杂度 $O(kn\log{V} + V)$：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 110, K = 10010, M = 1e7 + 10, MOD = 998244353;
const int i1e8 = 205817851;
const int V = 1e7;

int n, k;
int d[N];
int a[K][N], p[K], flg[K], q0, r;
int fac[M];
int sump;

int fpow(int x, int e)
{
    int res = 1;
    while (e)
    {
        if (e & 1)
            res = res * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return res;
}

signed main()
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
    fac[0] = 1;
    for (int i = 1; i <= V; i++)
        fac[i] = fac[i - 1] * i % MOD;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> d[i];
    for (int i = 1; i <= k; i++)
    {
        flg[i] = 1;
        for (int j = 1; j <= n; j++)
            cin >> a[i][j], flg[i] &= (d[j] >= a[i][j]);
        cin >> p[i];
        p[i] = p[i] * i1e8 % MOD;
        sump = (sump + p[i]) % MOD;
    }
    for (int i = 1; i <= k; i++)
        if (flg[i])
        {
            int q = 1, s = 0;
            for (int j = 1; j <= n; j++)
                s += d[j] - a[i][j], q = q * fpow(fac[d[j] - a[i][j]], MOD - 2) % MOD;
            q = q * fpow(((1 - sump) % MOD + MOD) % MOD, s) % MOD * fac[s] % MOD * fpow(fpow(n, s), MOD - 2) % MOD;
            r = (r + p[i] * (((1 - q) % MOD + MOD) % MOD) % MOD) % MOD;
        }
        else
            r = (r + p[i]) % MOD;
    r = r == 0 ? 0 : fpow(((sump * sump % MOD * fpow(r, MOD - 2) % MOD - sump) % MOD + MOD) % MOD, MOD - 2);
    q0 = 1;
    int s = 0;
    for (int i = 1; i <= n; i++)
        s += d[i], q0 = q0 * fpow(fac[d[i]], MOD - 2) % MOD;
    q0 = q0 * fpow(((1 - sump) % MOD + MOD) % MOD, s) % MOD * fac[s] % MOD * fpow(fpow(n, s), MOD - 2) % MOD;
    cout << ((1 - q0) % MOD + MOD) % MOD * (r + fpow(sump, MOD - 2)) % MOD << endl;
}
```

时间复杂度 $O(kn + (k + n) \log{V} + V)$：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 110, K = 10010, M = 1e7 + 10, MOD = 998244353;
const int i1e8 = 205817851;
const int V = 1e7;

int n, k;
int d[N];
int a[K][N], p[K], flg[K], q0, r;
int fac[M], ifac[M], t1[M], t2[M];
int sump;

int fpow(int x, int e)
{
    int res = 1;
    while (e)
    {
        if (e & 1)
            res = res * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return res;
}

signed main()
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
    fac[0] = ifac[0] = t1[0] = 1;
    for (int i = 1; i <= V; i++)
        fac[i] = fac[i - 1] * i % MOD, t1[i] = t1[i - 1] * fac[i] % MOD;
    t2[V] = fpow(t1[V], MOD - 2);
    for (int i = V; i >= 1; i--)
        t2[i - 1] = t2[i] * fac[i] % MOD, ifac[i] = t2[i] * t1[i - 1] % MOD;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> d[i];
    for (int i = 1; i <= k; i++)
    {
        flg[i] = 1;
        for (int j = 1; j <= n; j++)
            cin >> a[i][j], flg[i] &= (d[j] >= a[i][j]);
        cin >> p[i];
        p[i] = p[i] * i1e8 % MOD;
        sump = (sump + p[i]) % MOD;
    }
    for (int i = 1; i <= k; i++)
        if (flg[i])
        {
            int q = 1, s = 0;
            for (int j = 1; j <= n; j++)
                s += d[j] - a[i][j], q = q * ifac[d[j] - a[i][j]] % MOD;
            q = q * fpow(((1 - sump) % MOD + MOD) % MOD, s) % MOD * fac[s] % MOD * fpow(fpow(n, s), MOD - 2) % MOD;
            r = (r + p[i] * (((1 - q) % MOD + MOD) % MOD) % MOD) % MOD;
        }
        else
            r = (r + p[i]) % MOD;
    r = r == 0 ? 0 : fpow(((sump * sump % MOD * fpow(r, MOD - 2) % MOD - sump) % MOD + MOD) % MOD, MOD - 2);
    q0 = 1;
    int s = 0;
    for (int i = 1; i <= n; i++)
        s += d[i], q0 = q0 * ifac[d[i]] % MOD;
    q0 = q0 * fpow(((1 - sump) % MOD + MOD) % MOD, s) % MOD * fac[s] % MOD * fpow(fpow(n, s), MOD - 2) % MOD;
    cout << ((1 - q0) % MOD + MOD) % MOD * (r + fpow(sump, MOD - 2)) % MOD << endl;
}
```

---

## 作者：spdarkle (赞：2)

感谢 E_space 老师的讲解！

### Subtask 1

首先考虑 $n=1,k=1$ 的情况，设 $f$ 表示传送点到终点的期望。

考虑枚举连走 $1\sim d-a$步。
如果是连走 $i$ 步被调回，则期望应该是 $(1-p)^{i-1}p(i+s)$。

所以可以得到方程:

$$f=(1-p)^{d-a}(d-a)+\sum_{k=1}^{d-a}(1-p)^{k-1}p(k+s)$$

然后考虑计算答案：

$$ans=(1-p)^dd+\sum_{k=1}^d(1-p)^{k-1}p(k+s)$$

可以通过消元解决。

### Subtask 3


现在类比Subtask 1，仍然设 $f$ 为传送点到终点的答案。

这时候如果要套用Subtask 1的式子是不现实的，因为我们在Subtask 1中最后直接走 $d-a$ 步的式子要换。(不一定能走到终点)

设 $d=\sum_{k=1}^nd_i-a_i$，也即走 $d$ 步到终点。

但这并不一定到得了终点。想想，在第 $k$ 维，要从 $d$ 步里面选出 $k$ 步，并且要选中第 $k$ 维，这个方案数是 $\frac{A_{k}^d}{n}=\frac{d!}{(d_k-a_k)!n}$，然后我们还要选择其他几维，这等价于从$d$个球里面选出$d_1-a_1,d_2-a_2……$分别染色，等价于一个多项式系数：

$${d\choose {d_1-a_1,d_2-a_2…d_n-a_n} }\frac {1}{n^d}=\frac{d!}{n^d\prod _{i=1}^n(d_i-a_i)!}$$

所以设 $s$ 表示连走 $d$ 步(不被传送)到终点的概率，则:

$$s=\frac{d!}{n^d\prod_{k=1}^n(d_i-a_i)!}$$

但需要注意的是，这样走出去了(没到终点，出界了，概率是 $1-s$ )，还需要花费期望 $\frac{1}{p}$ 步走回传送点。

所以从起点到终点第 $1\sim d$ 步不传送的期望是 $\left(1-p)^d(d+(1-s)\left(\frac{1}{p}+f\right)\right)$。

后半部分照搬（没问题），可以得到：

$$f=(1-p)^d\left(d+\left(1-s\right)\left(\frac{1}{p}+f\right)\right)+\sum_{k=1}^d(1-p)^{k-1}p(k+f)$$

类似地，我们设 $D=\sum_{k=1}^nd_i$，就可以得到：

$$ans=(1-p)^D\left(D+(1-s)\left(\frac{1}{p}+f\right)\right)+\sum_{k=1}^D(1-p)^{k-1}p(k+f)$$

### Subtask 5

Subtask 4就是硬上高斯消元就是

考虑对 Subtask 3 的做法进行扩展。

设 $f_i$ 表示第 $i$ 个传送点到终点的步数期望。$s_i$ 表示第 $i$ 个传送点一直直走到终点的概率。

为了方便处理，我们将起点设为第 $0$ 个传送点，$p_0=0$。

需要分类讨论：设$D_j=\sum_{i=1}^nd_i-a_{j,i}$。

1. $\forall i\in[1,n],a_{j,i}\le d_i$。

>类比Subtask 3 的方法，可以得到：
>
>$$s_j=\frac{D_j!}{n^{D_j}\prod_{i=1}^n(d_i-a_{j,i})!}$$
>
>接着，同样类比计算 $f$，只是每一步需要计算跳到其他传送点的步数，可以得到：
>
>$$f_j=\sum_{i=1}^{D_j}(1-p)^{i-1}\left(\sum_{q=1}^kp_q(i+f_q)\right)+(1-p)^{D_j}\left(D_j+(1-s_j)S\right)$$
>
>$S$ 是指一个直走不可到达终点的点到终点的期望步数，显然 $S=1+(1-p)S+\sum_{i=1}^kp_if_i$。

2. $\exists i\in[1,n],a_{j,i}>d_i$。

>等价于 $S$，也即 $f_j=S$，需要注意 $s_j=0$。


高斯消元即可。
### Subtask 6

上正解！

回忆起式子：

$$D_j=\sum_{i=1}^nd_i-a_{j,i}$$

$$s_j=\frac{D_j!}{n^{D_j}\prod_{i=1}^n(d_i-a_{j,i})!}$$

$$f_j=\sum_{i=1}^{D_j}(1-p)^{i-1}\left(\sum_{q=1}^kp_q(i+f_q)\right)+(1-p)^{D_j}\left(D_j+(1-s_j)S\right)$$

$$S=1+(1-p)S+\sum_{i=1}^kp_if_i\implies S=\frac{1+\sum_{i=1}^kp_if_i}{p}$$

设 $g=\frac{\sum_{i=1}^kp_if_i}{p},S=\frac{1}{p}+g$。

考虑把 $f$ 的计算式拆开：

$$f_j=\sum_{i=1}^{D_j}(1-p)^{i-1}\left(\sum_{q=1}^kp_q(i+f_q)\right)+(1-p)^{D_j}\left(D_j+(1-s_j)S\right)$$

$$=\sum_{i=1}^{D_j}(1-p)^{i-1}p(i+g)+(1-p)^{D_j}\left(D_j+(1-s_j)S\right)$$

前半部分：

$$\sum_{i=1}^{D_j}(1-p)^{i-1}(pi+pg)=pg\sum_{i=0}^{D_j-1}(1-p)^{i}+p\sum_{i=1}^{D_j}i(1-p)^{i-1}$$

运用裂项相消法可以得到其等价于：

$$g(1-(1-p)^{D_j})+\frac{1-(1-p)^{D_j}}{p}-D_j(1-p)^{D_j}$$

然后看后半部分:

拆开式子得到：

$$(1-p)^{D_j}\left(D_j+(1-s_j)S\right)=D_j(1-p)^{D_j}+S(1-p)^{D_j}(1-s_j)$$

合并得到其等价于：

$$f_j=g(1-(1-p)^{D_j})+\frac{1-(1-p)^{D_j}}{p}+S(1-p)^{D_j}(1-s_j)$$

$$=g(1-(1-p)^{D_j})+\frac{1-(1-p)^{D_j}}{p}+(\frac{1}{p}+g)(1-p)^{D_j}(1-s_j)$$

$$=\frac{1-s_j(1-p)^{D_j}}{p}+g(1-s_j(1-p)^{D_j})$$

所以进一步地拆开 $g$ 并带入：

$$g=\frac{\sum_{i=1}^kp_if_i}{p}=\frac{\sum_{i=1}^kp_i\left(\frac{1-s_i(1-p)^{D_i}}{p}+g(1-s_i(1-p)^{D_i})\right)}{p}$$

设 $h_i=s_ip_i(1-p)^{D_i},H=\sum_{i=1}^kh_i$，则可以得到

$$pg=\sum_{i=1}^k\left(\frac{p_i-h_i}{p}+p_ig-gh_i\right)$$

分开求和即得：

$$pg=1-\frac{H}{p}+pg-gH\implies g=\frac{1-\frac{H}{p}}{H}=\frac{1}{H}-\frac{1}{p},S=\frac{1}{H}$$

所以带入 $f_0$：设 $w=1-s_0(1-p)^{D_0}$。

$$f_0=\frac{w}{p}+(\frac{1}{H}-\frac{1}{p})w=\frac{w}{H}$$

一些细节：

1. $\forall i\in[1,k],s_i=[\forall j\in[1,n],a_{i,j}\le d_j]s_i$。
2. $D_i=[D_i>0]$。
3. 记得取模，防爆负数，阶乘逆元用递推搞。

Code:

```cpp
#include<iostream>
#include<cmath>
using namespace std;
#define mod 998244353
#define int long long
int power(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1; 
	}
	return ans;
} 
#define N 150
#define M 10500
int s[M],p[M],mx,P,Inv,D[M],h[M],n,m,H,k,d[M],a[M][N],jc[10000050],inv[10000050];
void init(){
	cin>>n>>k;
	Inv=power(100000000,mod-2);
	for(int i=1;i<=n;i++)cin>>d[i];
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++)cin>>a[i][j];
		int x;cin>>x;p[i]=x*Inv%mod;
		P=(P+p[i])%mod;
	}
	for(int i=0;i<=k;i++){
		for(int j=1;j<=n;j++)D[i]+=d[j]-a[i][j];
		D[i]=max(0ll,D[i]);
		mx=max(mx,D[i]);
	}
	jc[0]=inv[0]=1;
	jc[1]=inv[1]=1;
	for(int i=2;i<=mx;i++) {
		jc[i]=1ll*jc[i-1]*i%mod;
		inv[i]=mod-(1ll*mod/(1ll*i)*1ll*inv[mod%i]%mod)%mod;
	}
	for(int i=2;i<=mx;i++) {
		inv[i]=1ll*inv[i-1]*inv[i]%mod;
	}
	for(int i=0;i<=k;i++){
		s[i]=jc[D[i]];
		s[i]=s[i]*power(power(n,D[i]),mod-2)%mod;
		for(int j=1;j<=n;j++){
			s[i]=s[i]*inv[max(0ll,d[j]-a[i][j])]%mod;
			if(d[j]<a[i][j])s[i]=0;
		}
	}
	for(int i=0;i<=k;i++){
		h[i]=s[i]*p[i]%mod;
		h[i]=h[i]*power(mod+1-P,D[i])%mod;
		H=(H+h[i])%mod;
	}
	int w=1-s[0]*power(mod+1-P,D[0])%mod;
	w=(w%mod+mod)%mod;
	int ans=w*power(H,mod-2)%mod;
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	init();
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

模拟赛题，场切了，来记录一下。

### 思路：

点的空间太大，不好考虑，考虑设 $dp_i$ 表示从第 $i$ 个地点目标点的期望步数；特别的，我们令起点 $(0, 0, \cdots, 0)$ 为第 $0$ 个地点。

那么从第 $i$ 个地点出发的过程中，有两种可能：

- 直接走到目标点。

- 中途运气不好，传送到了其它点。

第一种情况是好算的，设第 $i$ 个地点为 $(a_{i, 1}, \cdots, a_{i, n})$，若存在 $j$ 使得 $a_{i, j} > d_j$ 则不可能走到目标点；否则走的总步数显然是 $all_i = \sum\limits_{j = 1}^n d_j - a_{i, j}$。

那么相当于将 $all$ 个点的排列，划分为 $n$ 组（组内本质相同），第 $j$ 组大小为 $d_j - a_{i, j}$ 方案数，显然是：

$$\frac{all_i!}{\prod\limits_{j = 1}^n (d_j - a_{i, j})!}$$

注意要乘上概率 $n^{-all_i}$，同时由于中途都没有进行传送，若 $p = \sum\limits_{i = 1}^k p_i$，则发生的概率为 $(1 - p)^{all_i}$。

故第一种情况的概率：

$$q_i = (1 - p)^{all_i} \frac{all_i!}{n^{all_i} \prod\limits_{j = 1}^n (d_j - a_{i, j})!}$$

对于第二种情况，容易发现传送到哪里和 $i$ 所处的位置是**完全无关**的。

故我们可以设一个辅助变量 $start$，表示若当前开始传送，到达目标点的期望步数（注意传送不算步数），那么有：

$$start = \sum_{i = 1}^k \frac{p_i}{p} dp_i$$

知道了 $start$，想要推 $dp_i$ 的表达式还是有些困难，因为是求期望步数，而我们根本不知道走多少步后会进行传送：

$$dp_i = all_i q_i + \sum_{point} (start + g_{point}) f_{point}$$

其中 $f_{point}, g_{point}$ 分别表示走到 $point$ 这个点还未发生传送的概率与到这个点的步数（注意 $point$ 不能是终点）。

显然 $\sum\limits_{point} f_{point} = 1 - q_i$，故原式可以化为：

$$dp_i = all_i q_i + (1 - q_i)start + \sum_{point} g_{point} f_{point}$$

后面这串考虑容斥一下，我们需要求在到目标点过程中传送的期望步数，相当于用**从这个点到处乱走而发生传送的期望**减去**从这个点走到终点后再到处乱走而发生传送的期望**。

显然第一种情况的期望步数是：

$$\sum_{i = 1}^{+\inf} i (1 - p)^{i - 1} p = \frac{1}{p}$$

第二种情况，首先先走到终点的期望步数是 $all_i q_i$，之后就是第一种情况 $\frac{q_i}{p}$。

故在走到终点过程中进行传送的期望步数是 $\frac{1}{p} - all_i q_i - \frac{q_i}{p} = \frac{1 - q_i}{p} - all_i q_i$。

故有 $dp_i$ 的转移方程：

$$dp_i = all_iq_i + (1 - q_i) start + \frac{1 - q_i}{p} - all_i q_i$$

化简一下得到：

$$dp_i = (1 - q_i)(start + \frac{1}{p})$$

这是方程组的形式，但是这些方程形式基本相同，可以更容易的求出解。

将 $dp_i$ 代入 $start$：

$$\begin{aligned} start &= \sum_{i = 1}^k \frac{p_i}{p} dp_i \\ &= \sum_{i = 1}^k \frac{p_i}{p} (1 - q_i)(start + \frac{1}{p}) \\ &= start \sum_{i = 1}^k \frac{p_i}{p}(1 - q_i) + \sum_{i = 1}^k \frac{p_i}{p^2}(1 - q_i)\end{aligned}$$

那么我们有：

$$\left(1 - \sum_{i = 1}^k \frac{p_i}{p}(1 - q_i)\right) start = \sum_{i = 1}^k \frac{p_i}{p^2}(1 - q_i)$$

故解得：

$$start = \frac{\sum\limits_{i = 1}^k \frac{p_i}{p^2}(1 - q_i)}{1 - \sum\limits_{i = 1}^k \frac{p_i}{p}(1 - q_i)}$$

然后通过 $start$ 去计算 $dp_0$ 即可。

时间复杂度未 $O(nk)$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define ctz(x) __builtin_ctz(x)
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 1e4 + 10, M = 105, W = 1e7 + 10, mod = 998244353;
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
int T, n, k, inv_start, start, P;
int d[M], p[N], q[N], all[N], inv[W], fac[W];
int a[N][M];
inline int qpow(int a, int b){
	int ans = 1;
	while(b){
		if(b & 1)
		  ans = 1ll * ans * a % mod;
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return ans;
}
inline void init(){
	inv_start = qpow(1e8, mod - 2);
	fac[0] = fac[1] = 1;
	for(int i = 2; i < W; ++i)
	  fac[i] = 1ll * i * fac[i - 1] % mod;
	inv[W - 1] = qpow(fac[W - 1], mod - 2);
	for(int i = W - 2; i >= 0; --i)
	  inv[i] = 1ll * (i + 1) * inv[i + 1] % mod;
}
inline void solve(){
	P = 0;
	n = read(), k = read();
	for(int i = 1; i <= n; ++i)
	  d[i] = read();
	for(int i = 0; i <= k; ++i){
		all[i] = 0;
	    for(int j = 1; j <= n; ++j){
	    	if(i)
			  a[i][j] = read();
	    	if(a[i][j] > d[j])
	    	  q[i] = -1;
	    	all[i] += d[j] - a[i][j];
		}
		if(i)
	      p[i] = 1ll * read() * inv_start % mod;
		P = (P + p[i]) % mod;
	}
	int invn = qpow(n, mod - 2), rP = (1 - P + mod) % mod;
	for(int i = 0; i <= k; ++i){
		if(q[i] == -1){
			q[i] = 0;
			continue;
		}
		q[i] = 1ll * qpow(1ll * invn * rP % mod, all[i]) * fac[all[i]] % mod;
		for(int j = 1; j <= n; ++j)
		  q[i] = 1ll * q[i] * inv[d[j] - a[i][j]] % mod;
	}
	// (1 - sum) x = sum / p
	int invP = qpow(P, mod - 2), sum = 0;
	for(int i = 0; i <= k; ++i)
	  sum = (sum + 1ll * (1 - q[i] + mod) % mod * invP % mod * p[i] % mod) % mod;
	start = 1ll * sum * invP % mod * qpow((1 - sum + mod) % mod, mod - 2) % mod;
	write(1ll * (1 - q[0] + mod) % mod * (start + invP) % mod);
	putchar('\n');
}
bool End;
int main(){
//	open("rwec.in", "rwec.out");
	init();
	T = 1; 
	while(T--)
	  solve();
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：LEWISAK (赞：1)

[传送门](https://www.luogu.com.cn/problem/P8967)

[我的不乐观](https://www.cnblogs.com/lewisak/p/18759115)

# 题解

> 为便于表述，下文称第 $i$ 个可以散入天际到的点为第 $i$ 天际点，特别的，起点为第 $0$ 天际点，$P=\sum p_i$

看到恐怖的 $\sum d_i \le 10^7$ 就知道不能所有点都讨论了。考虑设 $dp_i$ 表示第 $i$ 天际点到终点的期望步数，我们把贡献拆开，先只计算天际点到终点不经过散入天际的期望步数。

### 不散入天际的期望

假设现在在算第 $i$ 天际点的期望步数，首先注意到步数一定是：

$$\sum_{j=1}^{n} d_{j}-a_{i,j}$$

所以只用算出概率然后乘起来算贡献即可，我们令 $s_i$ 等于到终点的步数。

那么可以转化问题为有 $s_i$ 个球，把它们放入 $n$ 个盒子中（每一步都有 $n$ 种选择），求第 $j$ 个盒子刚好有 $d_j-a_{i,j}$ 个球的概率，于是这就是 lmx 小学二年级就会的概率期望入门了，答案显然就是（$(1-P)^{s_i}$ 表示 $s_i$ 步不散入天际的概率）：

$$
\frac{s_i!}{\prod_{j=1}^{n}(d_j-a_{i,j})!\times n^{s_i}} \times (1-P)^{s_i}
$$

然后我们把这个答案用 $q$ 数组存起来，特别的，当有任意 $d_j < a_{i,j}$ 时，$q_i=0$。

### 引入散入天际

为避免 $dp_i$ 的转移式中出现其他 dp 值，考虑设 $g$ 表示散入天际后的期望步数，那么显然：

$$
g=\sum_{i=1}^{k}\frac{p_i}{P}dp_i
$$

然后第 $i$ 天际点乱走直到散入天际的期望就是 $\frac{1}{P}$。但有可能走到一半走到终点了，应该减掉，走到终点的期望步数为 $q_is_i$，而走到终点后散入天际的期望为 $q_i\frac{1}{P}$，于是最后从第 $i$ 天际点出发直到散入天际的期望就是：

$$
\frac{1}{P}-q_i\times\left(\frac{1}{P}+s_i\right)
$$

于是有

$$
dp_i=q_is_i+\left(1-q_i\right)g+\frac{1}{P}-q_i\times\left(\frac{1}{P}+s_i\right)
$$

然后来解 $g$，代入有：

$$
g=\sum_{i=1}^{k}\frac{p_i}{P}\times\left (q_is_i+\left (1-q_i\right )g+\frac{1}{P}-q_i\times\left (\frac{1}{P}+s_i\right )\right )
$$

移项整理得：

$$
P\left (1+\sum_{i=1}^k\frac{p_i}{P}\left (q_i-1\right )\right )g=\sum_{i=1}^k\frac{p_i}{P}\left (1-q_i\right )
$$

也就是：


$$
g=\frac{\sum_{i=1}^k\frac{p_i}{P}\left (1-q_i\right )}{P\left (1+\sum_{i=1}^k\frac{p_i}{P}\left (q_i-1\right )\right )}
$$

然后答案（$dp_0$）就是：
$$
q_0 s_0+\left(1-q_0\right)g+\frac{1}{P}-q_0\times\left(\frac{1}{P}+s_0\right)
$$

实际代码中不需要 $dp$ 数组。

# code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,k,d[10010],a[10010][110],x[10010],fac[10010000],p[10010],q[10010],s[10010],fl[10010],P,g;
int qpow(int x,int y){
	int aaa=1;
	while(y){
		if(y&1){
			aaa=aaa*x%mod;
		}
		x=x*x%mod;
		y>>=1;
	}
	return aaa;
}
signed main(){
	fac[0]=1;
	for(int i=1;i<=10000000;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>d[i];
		s[0]=(s[0]+d[i])%mod;
	}
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
			if(a[i][j]>d[j]){
				fl[i]=1;
			}
			s[i]=(s[i]+d[j]-a[i][j])%mod;
		}
		cin>>p[i];
		p[i]=p[i]*qpow(1e8,mod-2)%mod;
		P=(P+p[i])%mod;
	}
	for(int i=0;i<=k;i++){
		if(fl[i]){
			q[i]=0;
			continue;
		}
		int su=1;
		for(int j=1;j<=n;j++){
			su=su*fac[((d[j]-a[i][j])%mod+mod)%mod]%mod;
		}
		q[i]=fac[s[i]]*qpow(su*qpow(n,s[i])%mod,mod-2)%mod*qpow((1-P+mod)%mod,s[i])%mod;
	}
	int zuo=1,you=0;
	for(int i=1;i<=k;i++){
		zuo=(zuo+p[i]*qpow(P,mod-2)%mod*(q[i]-1)%mod)%mod;
		you=(you+p[i]*qpow(P,mod-2)%mod*(((qpow(P,mod-2)-qpow(P,mod-2)*q[i]%mod+mod)%mod)%mod)%mod)%mod;
	}
	g=you*qpow(zuo,mod-2)%mod;
	cout<<(((1-q[0])%mod+mod)%mod*((g+qpow(P,mod-2))%mod)%mod+mod)%mod;
	return 0;
}
```

---

## 作者：Laoshan_PLUS (赞：0)

# [P8967 追寻 | Pursuit of Dream](https://www.luogu.com.cn/problem/P8967)

很久没做过这种酸爽的推式子题了。

首先可以确定的是，看似每个点的坐标的每个维度都是 $10^7$ 级别的，实际上有用的点只有 $k$ 个，剩下点之间的期望都是相同并且可计算的。

对于期望 DP，一般是逆推的方法。考虑设一个 $f_i$ 表示从第 $i$ 个点出发到达终点的期望步数，其中特殊地定义 $f_0$ 表示 $(0,0,\dots,0)$ 这个点。由期望的线性性，这个期望分为三部分：直接到终点的期望、中间发生散入天际的期望。这两部分加和就是当前点的答案。最后的答案显然为 $f_0$。

## 直接到达终点

显然前者较为好算，我们先来计算前者，也就是直接到达终点的期望。

对于一个点 $(a_1,a_2,\dots,a_n)$，它到终点 $(d_1,d_2,\dots,d_n)$ 显然需要 $\sum_{j=1}^n(d_j-a_j)$ 步，把这个值记作 $s_i$。注意到这样计算有意义当且仅当 $\forall d_j\ge a_j$ 时，因为我们只能往前走，于是但凡 $\exists d_j<a_j$，这个点直接到达终点的期望就是 $0$。

还有一点需要注意，我们要保证这 $s_i$ 步都不会散入天际，这个概率是 $(1-p)^{s_i}$。

想要走完这 $s_i$ 步显然有 $n^{s_i}$ 种走法，因为每一步都可以走在任意一个维度上。我们接下来需要求出合法的走法数量。注意到这个问题可以转化为**多重集的排列数问题**，即我们有一个集合 $S$，其中包含 $d_1-a_1$ 个 $x_1$、$d_2-a_2$ 个 $x_2$、……、$d_n-a_n$ 个 $x_n$，求 $S$ 的全排列数。由公式可得，这个全排列数为 $\dfrac{s_i!}{\prod_{j=1}^n(d_j-a_j)!}$。也就是一共有这么多种合法的走法。最后我们得到直接到达终点的**概率**为
$$
q_i=\cfrac{\cfrac{s_i!}{\prod_{j=1}^n(d_j-a_j)!}}{n^{s_i}}\times(1-p)^{s_i}
$$
于是这部分的期望步数就是 $q_is_i$。

## 出现散入天际

首先可以确定的是，不能使 $f_i$ 的式子里面出现 $f_j$ 之类的东西，那样的话就需要高斯消元，但复杂度我们显然无法承受。

但是注意到，不管从哪里散入天际，这个期望都是恒定的。也就是说，“散入天际之后到达终点” 这一部分的期望和 $i$ 无关。于是考虑求出这一部分不变量，记作 $g$。容易得到
$$
g=\sum_{i=1}^k\frac{p_i}pf_i
$$
到这一步，$f_i$ 的表达式还缺一部分，就是从 $i$ 出发到达散入天际那个点的期望步数。直接求是不好求的，因为我们根本不知道走多少步会散入天际。考虑**容斥**，分别计算从当前点出发到处乱走然后遇到散入天际的期望，以及从当前点出发先走到终点再到处乱走然后散入天际的期望，二者相减就是答案。

前者的计算是一个很典的结论，如下：
$$
\sum_{i=1}^\infty(1-p)^{i-1}\times i\times p=\frac1p
$$
用求导可证明。后一部分的计算参考我们上文计算的结果，走到终点的期望步数是 $q_is_i$，之后的期望步数是 $q_i\times\dfrac1p=\dfrac{q_i}p$。所以从点 $i$ 出发到达散入天际那个点的期望步数就是
$$
\frac1p-q_is_i-\frac{q_i}p
$$
于是我们得到了 $f_i$ 的最终表达式：
$$
\begin{aligned}f_i&=q_is_i+(1-q_i)g+\frac1p-q_is_i-\frac{q_i}p\\&=(1-q_i)g+(1-q_i)\times\frac1p\\&=(1-q_i)\bigg(g+\frac1p\bigg)\end{aligned}
$$

## 酸爽推式子

发现 $f_i$ 的这个式子中，$q_i$ 和 $p$ 都是好求的，考虑解出 $g$。

把 $f_i$ 代入 $g=\sum\limits_{i=1}^k\dfrac{p_i}pf_i$ 中得到：
$$
\begin{aligned}
g&=\sum_{i=1}^k\frac{p_i}p(1-q_i)\bigg(g+\frac1p\bigg)\\
&=g\Bigg(\sum_{i=1}^k\frac{p_i}p(1-q_i)\Bigg)+\frac1p\Bigg(\sum_{i=1}^k\frac{p_i}p(1-q_i)\Bigg)
\end{aligned}
$$
再整理得：
$$
\Bigg(1-\sum_{i=1}^k\frac{p_i}p(1-q_i)\Bigg)g=\frac1p\Bigg(\sum_{i=1}^k\frac{p_i}p(1-q_i)\Bigg)
$$
于是我们只需知道 $p_i,p,q_i$ 这三个量就可以解出 $g$，而这三个量都是好求的，于是解出 $g$ 之后代入 $f$ 的式子中，输出 $f_0$ 即可。

```cpp
#include<bits/stdc++.h>
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
#define inv(x) power(x,MOD-2)
using namespace std;

char buf[1<<20],*p1=buf,*p2=buf;
int read(){
	int x=0;
	char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x;
}
using ll=long long;
constexpr int MAXN=105,MAXK=10005,MAXV=1e7+5;
constexpr ll MOD=998244353,inv8=205817851;
int n,k;
ll d[MAXN],a[MAXK][MAXN],p[MAXK],P,invP,s[MAXK],q[MAXK];
ll fac[MAXV];

ll power(ll a,ll b){
	ll res=1;
	for(;b;a=a*a%MOD,b>>=1)if(b&1)res=res*a%MOD;
	return res;
}
void init(){
	fac[0]=1;
	for(int i=1;i<MAXV;i++) fac[i]=fac[i-1]*i%MOD;
}
void add(ll&x,ll y){
	x=(x+y>=MOD?x+y-MOD:x+y);
}

int main(){
	init();
	n=read(),k=read();
	for(int i=1;i<=n;i++) d[i]=read(),s[0]+=d[i];
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=read();
			if(d[j]<a[i][j]) s[i]=-1;
			else if(~s[i]) s[i]+=d[j]-a[i][j];
		}
		p[i]=inv8*read()%MOD;
		add(P,p[i]);
	}
	invP=inv(P);
	ll res1,res2=0,g;
	for(int i=0;i<=k;i++){
		if(~s[i]){
			q[i]=fac[s[i]]*power((1-P+MOD)%MOD,s[i])%MOD*inv(power(n,s[i]))%MOD;
			for(int j=1;j<=n;j++) q[i]=q[i]*inv(fac[d[j]-a[i][j]])%MOD;
		}
		add(res2,p[i]*invP%MOD*((1-q[i]+MOD)%MOD)%MOD);
	}
	res1=(1-res2+MOD)%MOD;
	res2=res2*invP%MOD;
	g=res2*inv(res1)%MOD;
	printf("%lld\n",(1-q[0]+MOD)%MOD*((g+invP)%MOD)%MOD);
	return 0;
}
```

---

## 作者：Corzica (赞：0)

非常好题目，使我大脑旋转。

注意到一条合法的路径一定是从一个天际点（我们规定 $(0,0)$ 也是一个天际点）开始到达终点，令此距离为 $dis_i$。而此前的运动轨迹也一定是从一天际点开始，运动若干步后散入天际。

基于此，我们可以求出从一个天际点开始的期望答案 $ans_i= f_i  \times k + g_i $。其中，$k$ 是掉入天际后从新开始的期望答案，$k$ 可以表示为 $ i=\sum_{i = 1}^nx_i/sum  \times ans_i $，而 $sum$ 代表着掉入天际的概率。

我们考虑求解 $f,g$ 数组，求出两数组后，便可回代入 $k$ 的表达式中，进而求出最终的答案。

我们将调入天际的期望步数记为 $op$，$op$ 有两种计算方式，分别为 $op=\sum_{i = 1}^\infty q^i  \times i $ 与 $op=\sum_{i = 0}^\infty (1-q)^i $，$q$ 为单次调入天际的概率。我们使用第二个式子和等比数列求和公式求出 $op$。

现在，我们来求解 $f,g$ 数组，$f$ 数组的求解是简易的，我们先正着求能到达天际点的概率（即为 $(1-q)^{dis}$）乘上 $dis$ 步内的行走方案到达终点的概率)，再用 $1$ 去作差即可。我们用上面的第一个式子求解 $g$，注意到减去能到达的概率会让 $i$ 在大于等于 $dis$ 的时候全部乘上 $1-f_i$，再加上能到达一部分的权值后，发现 $g_i=op-(1-f_i) \times op$，便可以此求解出 $g$ 数组。

代码如下（主要变量名与上述相同，部分过程中变量未定义）。
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 998244353;
int n, m, d[105], a[10005][105], flg[10005];
ll f[10005], x[10005], dis[10005], jie[10000007], inv[10000007], sum, op, g[10005];
// 第i个点的期望步数为 f[i]*点开始期望步数 + g[i]
ll ksm(ll p, ll q = mod - 2) {
	ll base = 1;
	while (q) {
		if (q & 1) base = base * p % mod;
		q >>= 1;
		p = p * p % mod;
	}
	return base;
}
inline ll C(int p, int q) {
	if (p < q) return 0;
	return jie[p] * inv[q] % mod * inv[p - q] % mod;
}
const ll ei = ksm(100000000);
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> d[i];
	}
	jie[0] = 1;
	for (int i = 1; i <= 10000000; i++) {
		jie[i] = jie[i - 1] * i % mod;
	}
	inv[10000000] = ksm(jie[10000000]);
	for (int i = 10000000 - 1; i >= 0; i--) {
		inv[i] = (inv[i + 1] * (i + 1)) % mod;
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			if (a[i][j] > d[j]) flg[i] |= 1;
			dis[i] += d[j] - a[i][j];
		}
		cin >> x[i];
		sum = (sum + x[i]) % mod;
	}
	m++;
	for (int j = 1; j <= n; j++) {
		dis[m] += d[j];
	}
	op = 100000000 * ksm(sum) % mod;
	ll ccnt;
	for (int i = 1; i <= m; i++) {
		if (flg[i]) {
			f[i] = 1;
			g[i] = op;
			continue;
		}
		f[i] = 1;
		ll cnt = dis[i];
		for (int j = 1; j <= n; j++) {
			f[i] = f[i] * C(cnt, d[j] - a[i][j]) % mod;
			cnt -= d[j] - a[i][j];
		}
		f[i] = f[i] * ksm(ksm(n, dis[i])) % mod;
		f[i] = f[i] * ksm((100000000 - sum) * ei % mod, dis[i]) % mod;
		g[i] = op;
		g[i] = (g[i] + mod - f[i] * op % mod) % mod;
		f[i] = (1 - f[i] + mod) % mod;
	}
	ll p = 1, q = 0;
	sum = ksm(sum);
	for (int i = 1; i <= m; i++) {
		p = (p - sum * x[i] % mod * f[i] % mod + mod) % mod;
		q = (q + sum * x[i] % mod * g[i] % mod) % mod;
	}
	q = q * ksm(p) % mod;
	cout << (f[m]*q % mod + g[m]) % mod;
	return 0;
}
```

---

