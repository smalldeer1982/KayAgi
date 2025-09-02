# 「Wdsr-3」蓬莱药局（gene）

## 题目背景

八意永琳是居住在永远亭的医生。她有着精湛的医术以及大量的医学知识，因而可以制造出各种的药物。

尽管如此，八意永琳常常为新的药物进行试验（包括但不限于对铃仙下手）。不过，八意永琳也开始使用被称为「培养基」一类的东西，培养被称为「细菌」的微小妖怪作为实验材料了。

细菌的分裂能力很强。每一次分裂，细菌的数目都能翻倍。更有意思的是，产生的细菌的子代不一定与亲代相同。换言之，子代细菌会发生变异，从而为永琳的药物实验提供了大量的材料。当然了，细菌太多也是一件苦恼的事情；如果培养基里长满了四处活跃的细菌，那么永琳将不得不采取措施，消灭它们。

在执行一次新的培养之前，永琳希望对细菌上的基因进行一些研究；由于永琳忙着去制药，因此这个任务就交给你了。

## 题目描述

为了更方便地描述题意，我们先给出以下定义：

- **子段**：我们定义数组 $B$ 是数组 $A$ 从 $P$ 位置开始的子段，当且仅当 $|A| + P - 1 \le |B|$ 且 $B_1=A_P,B_2=A_{P+1},\dots,B_{|B|}=A_{P+{|B|}-1}$．
- **作为子段的出现次数**：我们定义数组 $B$ 在数组 $A$ 中作为子段的出现次数为：初始设次数为 $0$．枚举每个不同的 $P$，若数组 $B$ 是数组 $A$ 从 $P$ 位置开始的子段，则将次数加一．最后得到的值即为数组 $B$ 在数组 $A$ 中作为子段的出现次数．
- **基因数组**：每个细菌都有一个「基因数组」．它是一个值域为 $[1,k]$ 的整数数组．
- **目标数组**：「目标数组」是一个值域为 $[1,k]$ 的整数数组．在本题中，我们会给定 $m$ 个不同的「目标数组」，第 $i$ 个数组为 $g_i$．
- **目标细菌**：对于一个细菌，记它的「基因数组」为 $X$．我们统计每个「目标数组」$g_1, g_2, \dots, g_m$ 分别在 $X$ 中「作为子段的出现次数」，并将它们求和．若得到的和为 **奇数**，则我们称这个细菌为一个「目标细菌」．
- **基因突变**：「基因突变」是作用于一个细菌的变换．给定一个 $k \times k$ 的突变概率矩阵 $p$．记这个细菌的「基因数组」为 $X$．对于 $x$ 中的每个元素 $X_i$，$X_i$ 会以 $p_{X_i,j}$ 的概率替换为 $j$（$1 \le j \le k$）．根据此定义，显然有 $\forall i \in [1,k], \sum_{i=j}^k p_{i,j}=1$．

一次实验的过程如下：

- 首先在一个空的培养皿中放入一个指定的细菌．
- 在接下来的每分钟，现有的每个细菌会分裂成两个细菌，每个细菌的「基因数组」与原细菌完全相同．分裂之后，每个基因都会进行一次「基因突变」．
- $t$ 分钟后，统计培养皿中「目标细菌」的数量，并结束实验．

现在给定一个长度为 $n$ 的「基因数组」$s$．对于 $s$ 的每个前缀数组 $s[1,1],s[1,2],\dots,s[1,n]$，假设该数组是实验开始时放入的细菌的「基因数组」，请你求出实验结束时得到的「目标细菌」的数量的期望，对 $10^9+7$ 取模．


## 说明/提示

### 样例解释

#### 样例 \#1

- 当前缀长度为 $1$ 时，初始细菌的「基因数组」为 $\{1\}$．分裂一次后变为 $\{1\}$ 和 $\{2\}$ 的概率均为 $\frac 1 2$．若变为 $\{1\}$，则是「目标细菌」；若变为 $\{2\}$，则不是「目标细菌」．分裂一次后培养皿中有 $2$ 个细菌，故「目标细菌」总数的期望为 $\frac 1 2\times 2=1$．  
![](https://cdn.luogu.com.cn/upload/image_hosting/ytz7qxkl.png)
- 当前缀长度为 $2$ 时，初始细菌的「基因数组」为 $\{1, 1\}$．分裂一次后的细菌变为 $\{1, 1\}, \{1, 2\}, \{2, 1\}, \{2, 2\}$ 的概率都为 $\frac 1 4$．其中 $\{2, 2\},\{1,2\},\{2,1\}$ 均为「目标细菌」，$\{1,1\}$ 不是「目标细菌」（因为出现了两次子串 $\{1\}$）．即分裂后的「目标细菌」的总数的期望为 $\frac 3 4$．分裂一次后培养皿中有 $2$ 个细菌．即最后「目标细菌」数量之和的期望为 $\frac 3 4\times 2=\frac 3 2$．  
![](https://cdn.luogu.com.cn/upload/image_hosting/cjx85fuk.png)

### 数据范围

**本题采用捆绑测试，且不存在一个 Subtask 包含其他所有 Subtask 的数据范围和限制．**

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|c|c|c|} \hline
\textbf{Subtask} & \textbf{分值} &\bm{n\le} & \bm{m\le} &\bm{k\le}&\bm{t\le} & \bm {|g_i|\le} &  \textbf{特殊性质} \cr \hline
1 & 1 & 10^5 & 10^5 & 100 & 0 & 10^5 \cr \hline
2 & 14 & 5 & 5 & 5 & 1 & 5 \cr \hline
3 & 15 & 10^3 & 1 & 10^3 & 1 & 100 & \text{A} \cr \hline
4 & 30 & 5\times 10^4 & 5 & 10 & 1 & 50 & \text{B} \cr \hline
5 & 20 & 5\times 10^4 & 5 & 10 & 10^3 & 50 \cr \hline
6 & 20 & 10^3 & 10^4 & 10 & 10^3 &  10^4 & \text{C}\cr \hline
\end{array}
$$

- **特殊性质** $\textbf{A}$：对于 $i=1,2,\dots,m$，保证 $g_{i}$ 中所有整数均为 $1$
- **特殊性质** $\textbf{B}$：对于 $i=1,2,\dots, k$，$j=1,2,\dots,k$，保证 $p'_{i,j}=1$ 
- **特殊性质** $\textbf{C}$：保证 $\sum_{i=1}^m |g_i|\le 10^4$

对于所有数据，保证 $1\le n,m,\sum|g_i| \le 10^5$．$0\le t\le 10^3$，$0\le p'_{i,j} \le 10^9$．且 $p'$ 矩阵不会出现某一行的和在模 $10^9+7$ 意义下为 $0$．


## 样例 #1

### 输入

```
2 2 2 1
1 1
1 1
2 2 2
1 1
1 1```

### 输出

```
1
500000005```

## 样例 #2

### 输入

```
5 5 5 1
1 4 2 3 3
3 1 1 4
3 5 1 4
4 1 4 1 4
2 5 3
1 5
9 9 8 2 4
4 3 5 3 2
1 4 7 4 8
3 6 4 7 1
1 4 5 1 4```

### 输出

```
250000002
273809526
931547626
97163867
377852186```

# 题解

## 作者：老莽莽穿一切 (赞：3)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16517906.html)

---

[**你谷 link**](https://www.luogu.com.cn/problem/P8011)

综合性比较强的 AC 自动机题目，我们可以对这道题逐步分解求解。

#### $\rm subtask\ 1$

没有变换，问题转化成多模式串单文本串，求文本串的每个前缀的模式串出现次数，AC 自动机模板题，也可以用后缀数据结构解决，这里不多做解释，可以出门左转你谷模板区自行学习（AC 自动机模板都不会就来刷字符串黑题？），时间复杂度就是 AC 自动机模板的时间复杂度 $\mathcal O\left(n+k\sum|g_i|\right)$。

#### $\rm subtask\ 2$

直接暴力，对正解没什么启示，这里直接 skip。

#### $\rm subtask\ 3$

这档部分分的特点是只经过一个时刻，只有一个模式串，且串里只有 $1$，那么我们可以运用 dp 求解，设 $f_{i,j}$ 表示文本串长度为 $i$ 的前缀后缀 $1$ 长度为 $j$ 的概率，$g_{i,j}$ 表示文本串长度为 $i$ 的前缀是目标细菌的概率。

关于 $g_{i,j}$ 为什么是概率而不是期望，我们发现 $t$ 个时刻过后一共会有 $2^t$ 个细菌，而这 $2^t$ 个细菌互相独立，所以我们只要先算出是目标细菌的概率，然后乘上总数就可以即可得到答案。

那么我们考虑动态转移方程，$f$ 的转移方程是非常浅显的，设第文本串第 $i$ 位变为 $1$ 的概率为 $x_i$，则：

$$
f_{i,j}=\begin{cases}
(1-x_i)\sum_{j=0}^{i-1}f_{i-1,j}&,\ i=0\\
x_if_{i-1,j-1}                  &,\ \texttt{otherwise}
\end{cases}
$$

意思非常显然，即讨论最后一个数字是不是 $1$，初始化 $f_{0,0}=1$。设 $\mathrm{length}$ 表示给定模式串的长度，同理我们可以得到 $g$ 的转移：

$$
g_{i,j}=\begin{cases}
(1-x_i)\sum_{j=0}^{i-1}g_{i-1,j}&,\ i=0\\
f_{i,j}-x_ig_{i-1,j-1}          &,\ i\ge\mathrm{length}\\
x_ig_{i-1,j-1}                  &,\ \texttt{otherwise}
\end{cases}
$$

和 $f$ 的转移长得很像，一样的部分我不多做赘述，我们发现中间有所不同，当 $i\ge\mathrm{length}$ 时的转移是特别的，从意思上也不难理解，即出现模式串的数量又增加了，那么概率自然要取反，至于为什么用是 $f_{i,j}$ 去操作，从集合的角度，即全集减去子集得到补集，根据上面的定义，我们将 $f_{i,j}$ 视为“长度为 $i$ 的前缀后缀 $1$ 长度为 $j$ ”的全集，则 $g_{i,j}$ 是其中一个子集，那么转移方程也就理所当然了。

每次的答案就是当前所有 $g$ 的和，再乘上细胞数量，即 $\mathrm{ans}_i=2\sum_{j=0}^ig_{i,j}$，时间复杂度 $\mathcal O\left(n^2\right)$。

#### $\rm subtask\ 4$

题目给的性质 $\mathbf B$ 反倒意义不大，这个包的重点是仍旧满足 $t=1$，我们可以考虑将刚刚 $\rm subtask\ 3$ 的单模式串问题扩展到多模式串上。

首先考虑将 $\rm subtask\ 3$ 的情况再普遍化一点，如果这个串不只有 $1$，我们怎么做，思考一番后发现我们可以使用 KMP 来解决这个问题，设 $f_{i,j}$ 表示文本串长度为 $i$ 的前缀长度为 $j$ 的后缀匹配模式串长度为 $j$ 的前缀的概率，$g$ 定义同理，利用 KMP 的 $\mathrm{next}$ 数组辅助转移即可，至于上面的概率取反操作，就是当到达字符串结尾的时候要做的。

那么用 KMP 解决单模式串问题启示我们使用 AC 自动机解决多模式串问题，那么剩下的就顺其自然了，首先将所有串插入 AC 自动机，设 $\mathrm{tag}_p$ 表示在节点 $p$ 所代表的串的后缀中模板串的数量的奇偶性，然后在算 $\mathrm{fail}$ 的同时把所有节点的 $\mathrm{tag}$ 也一起算出来，运用 $tag$ 来支持我们的 dp，转移方程由于 AC 自动机认子不认父的结构，写成枚举起点转移别人的方式会更加简单，直接根据 AC 自动机的 trie 图转移就好了，等所有都转移好了再将满足 $\mathrm{tag}_p=1$ 的 $p$ 对应的 $g$ 全部取反，实现难度不大，时间复杂度 $\mathcal O\left(nk\sum|g_i|\right)$。

#### $\rm subtask\ 5,6$

到这里就是正解了，我们发现我们现在唯一的障碍就是 $t>1$，但是我们在前面讲 $\rm subtask\ 3$ 的时候讲到我们分裂得到的每个细胞是互相独立的，那么 $t$ 影响的实际上就是数列中每个数变成别的数的概率，我们只要知道 **$t$ 个时刻后每个数变成另一个数的概率**直接套用 $\rm subtask\ 4$ 的做法就好了，我们发现可以对给定的 $P$ 矩阵做矩阵快速幂，$P$ 矩阵的 $t$ 次方即我们所求，这样就做完了，时间复杂度 $\mathcal O\left(k^3\log t+nk\sum|g_i|\right)$。

具体代码实现方面，整份代码本来是数据点分治，$\rm subtask\ 1$ 部分 $n$ 与 $\sum|g_i|$ 较大，直接用后面的做法会 TLE，要特殊处理，而后面 $\rm subtask\ 3$ 的 $k$ 较大，在矩阵快速幂过程中 $k^3$ 与单位矩阵相乘一次会直接 TLE，但是这些都可以解决，我们一定要建出 AC 自动机，且与后面的 AC 自动机一致，所以 $\rm subtask\ 1$ 可以在建出 AC 自动机后几行解决，$\rm subtask\ 3$ 实际我们在转移过程中有用的可以压缩成 $1/2$，将所有不是 $1$ 的转移压缩到 $2$ 上，矩阵压缩成 $k\times 2$ 的，虽然不能矩阵幂，但是矩阵乘一次是可以接受的，就可以减少很大一部分特判，剩下的部分直接和正解部分合并就好了，代码并不麻烦。

[c++ 代码](https://www.cnblogs.com/LaoMang-no-blog/p/16517906.html)

---

## 作者：yzy1 (赞：3)

这里是出题人官方题解。

## subtask 1

这不就 AC 自动机板子吗？

## subtask 2

爆搜，枚举所有可能的 $S$，算概率相加即可。

```cpp
void Dfs(int x, int mx) {
  if (x == mx + 1) {
    int cnt = 0;
    re (i, m) {
      re (l, mx) {
        int r = l + b[i].size() - 1;
        if (r > mx) break;
        bool fl = 1;
        rep (j, 0, b[i].size() - 1)
          if (b[i][j] != now[l + j]) {
            fl = 0;
            break;
          }
        if (fl) ++cnt;
      }
    }
    int gl = 1;
    re (i, mx)
      gl = 1ll * gl * p[a[i]][now[i]] % mo;
    if (cnt & 1) ans[mx] += gl, umod(ans[mx]);
    return;
  }
  re (i, K)
    now[x] = i, Dfs(x + 1, mx);
}
```

## subtask 3

设 $f(i,j)$ 为当前 dp 到第 $i$ 位，串的末尾有 $j$ 个 $1$ 的概率，$g(i,j)$ 为当前 dp 到第 $i$ 位，串的末尾有 $j$ 个 $1$ 时期望的致病性细菌个数。枚举 $i,j$ 转移即可。

```cpp
void Solve() {
  re (i, K) {
    in(p[i], K);
    re (j, K)
      sump[i] += p[i][j], umod(sump[i]);
    int ny = Pow(sump[i], mo - 2, mo);
    re (j, K)
      p[i][j] = 1ll * p[i][j] * ny % mo;
    sump[i] = 0;
    re (j, K)
      sump[i] += p[i][j], umod(sump[i]);
  }
  f[0][0] = 1;
  re (i, n) {
    rep (j, 0, i) {
      f[i][0] += 1ll * f[i - 1][j] * ((mo + sump[a[i]] - p[a[i]][1]) % mo) % mo, umod(f[i][0]);
      g[i][0] += 1ll * g[i - 1][j] * ((mo + sump[a[i]] - p[a[i]][1]) % mo) % mo, umod(g[i][0]);
    }
    re (j, i) {
      f[i][j] = 1ll * f[i - 1][j - 1] * p[a[i]][1] % mo, umod(f[i][j]);
      g[i][j] = 1ll * g[i - 1][j - 1] * p[a[i]][1] % mo, umod(g[i][j]);
    }
    rep (j, 0, i) {
      if (j >= (int)b[1].size()) g[i][j] = (0ll + mo + f[i][j] - g[i][j]) % mo;
      ans[i] += 1ll * g[i][j] % mo, umod(ans[i]);
    }
  }
}
```

## subtask 4

将所有 $g_i$ 建出 AC 自动机。设 $f(i,j)$ 表示当前是 $S$ 的第 $i$ 个字符，且当前正好走到 AC 自动机的第 $j$ 个节点的概率。$g(i,j)$ 表示当前是 $S$ 的第 $i$ 个字符，在自动机的 $j$ 号节点时出现的致病细菌的期望个数，转移即可。注意要用滚动数组压一下内存。

注意需要提前用拓朴排序预处理一遍来保证复杂度。具体方式类似 [AC 自动机（二次加强版）](https://www.luogu.com.cn/problem/P5357)。

时间复杂度 $O(n\sum|g_i|)$。

```cpp
struct Trie {
  int e[N][109], ed[N], fal[N], tot = 1;
  void Ins(const vector<int> &v) {
    int x = 1;
    each (c, v)
      x = e[x][c] = (e[x][c] ?: ++tot);
    ++ed[x];
  }
  void AC() {
    re (i, K)
      e[0][i] = 1;
    queue<int> q{{1}};
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      re (c, K) {
        if (e[x][c])
          fal[e[x][c]] = e[fal[x]][c], q.push(e[x][c]);
        else
          e[x][c] = e[fal[x]][c];
      }
    }
  }
} tr;

struct G {
  int tot, h[N];
  struct E {
    int t, n;
  } e[N];
  inline void Add(int f, int t) { e[++tot] = {t, h[f]}, h[f] = tot; }
} falg;

int f[2][N], g[2][N], ans[N], p[1009][1009], sump[1009], n, a[N], m, T, sumed[N], rd[N];
vector<int> b[N];

void Topo() {
  re (i, tr.tot)
    if (tr.fal[i]) falg.Add(tr.fal[i], i), ++rd[i], sumed[i] += tr.ed[i];
  queue<int> q;
  re (i, tr.tot)
    if (rd[i] == 0) q.push(i);
  while (!q.empty()) {
    int qf = q.front();
    q.pop();
    nxt (i, qf, falg) {
      auto t = falg.e[i].t;
      sumed[t] += sumed[qf];
      if (--rd[t] == 0) q.push(t);
    }
  }
}

void DP() {
  f[0][1] = 1;
  rep (i, 0, n) {
    int ii = i & 1;
    re (j, tr.tot) {
      g[ii][j] = 1ll * Pow(f[ii][j], mo - 2, mo) * g[ii][j] % mo;
      if (sumed[j] & 1) g[ii][j] = (1ll + mo - g[ii][j]) % mo;
      ans[i] += 1ll * f[ii][j] * g[ii][j] % mo, umod(ans[i]);
      re (c, K) {
        int t = tr.e[j][c];
        ll gx = 1ll * f[ii][j] * p[a[i + 1]][c] % mo;
        f[ii ^ 1][t] += gx, umod(f[ii ^ 1][t]);
        g[ii ^ 1][t] += gx * g[ii][j] % mo, umod(g[ii ^ 1][t]);
      }
    }
    rep (j, 0, tr.tot)
      f[ii][j] = 0, g[ii][j] = 0;
  }
}

```

## subtask 5~6

我们发现 $P$ 矩阵可以矩乘。快速幂预处理后按照 sub4 的方法做即可。

时间复杂度 $O(n\sum|g_i|+k^3 \log t)$。

---

## 作者：囧仙 (赞：2)

[$\textsf{yzy}$ 给出的题解](https://www.luogu.com.cn/paste/pfzcbo23)。

## $\small \textbf{Subtask 1}$

问题等价于，每次向字符串加入一个字符，询问其中 $g_i$ 的子串的总数是否有奇数个。那么这就是 $\text{AC}$ 自动机的模板：根据 $g_i$ 建出 $\textrm{AC}$ 自动机，每个位置维护下以它作为右端点可以匹配上的 $g_i$ 的个数。最后遍历一遍 $S$，指针在 $\text{AC}$ 自动机上走动的时候就能同时计算出此时可以匹配上的 $g_i$ 的个数。

时间复杂度是 $\mathcal O(n+\sum |g_i|)$。因为非常板子，因此只有 $1$ 分。

## $\small \textbf{Subtask 2}$

根据题意，枚举一下可能出现的所有细菌并且统计一下概率，暴力算下是否是目标细菌，最后相加即可。

## $\small \textbf{Subtask 4,5,6}$

观察到这样一件事情：最终分裂出来的 $2^t$ 个细胞，应该是完全等价的。因此只需要计算出一个细胞突变 $t$ 次后的期望，再乘上 $2^t$ 即可。再观察一下 $P$ 矩阵，容易发现这是一个传递闭包一类的东西。换言之，一个字符突变 $t$ 次后变成其他各种字符的概率，对应于 $P^t$ 当中这一行的数值。因此只需要将矩阵乘上 $t$ 次即可。

- 由于 $\textsf{yzy}$ 是毒瘤，因此对于 $t=0$，$P^t$ 是单位矩阵 $E$（也就是有且仅有对角线上有值，并且值为 $1$）。这是需要特判的。  
- 由于 $\textsf{yzy}$ 是毒瘤，因此对于 $t=1$，$P^t$ 就是给出的矩阵 $P$。但如果你使用 $k^3$ 的矩阵乘法对着单位矩阵乘了一遍，那恭喜你会挂掉 $k\le 10^3$ 的那个 $\textrm{Subtask}$。  
- 由于 $\textsf{yzy}$ 大发慈悲，因此你甚至不需要写快速幂，对于 $t\ge 2$ 的情况直接对 $P$ 乘上 $t-1$ 次就行了。

那么 $t>1$ 的情况可以都归纳到 $t=1$ 的情况。这就是我们的重点。

---

考虑按照 $\textrm{Subtask 1}$ 的思路，直接建出 $g_i$ 的 $\text{AC}$ 自动机。那么可以得出这样一种动态规划的做法：

记 $\mathit{dp}_{i,0/1}$ 表示「当前走到了 $\text{AC}$ 自动机的 $i$ 号节点，当前所匹配的 $g_i$ 的总数为偶数还是奇数」的数学期望。初始时的空字符串对应着 $dp_{0,0}=1$。在不断向字符串内加入新字符 $w$ 的同时，使用递推，枚举每一个节点 $u$，再枚举下一个走的边 $c$，更新 $dp$ 值。假设下个到达的状态是 $v$，以 $v$ 作为右端点的 $g_i$ 的个数的奇偶性为 $f(v)$，容易得出这样的递推方程：

$$
\begin{aligned}
dp'_{v,f(v)}&\gets dp'_{v,f(v)}+dp_{u,0}\cdot p(w,c) \cr
dp'_{v,\neg f(v)}&\gets dp'_{v,\neg f(v)}+dp_{u,1}\cdot p(w,c) \cr
\end{aligned}$$

其中 $p(w,c)$ 表示，字符 $w$ 在经过了 $t$ 次变换后变成 $c$ 的概率，这是可以通过上文提到的矩阵乘法求解的。这样暴力做一遍就能得到复杂度为 $\mathcal O(n\cdot |\sum g_i|\cdot k+t\cdot k^3)$ 的做法。

建议预处理出 $d$ 数组，其中 $d_{u,c}$ 表示 $\text{AC}$ 自动机上的节点 $u$ 通过字符 $c$ 会转移到哪里。这样可以省去每次遍历自动机时重复计算带来的时间开销。同时可能需要在一些地方加上取模优化来防止卡常。

因为 $\textsf{yzy}$ 是毒瘤，因此他出了一大堆乱七八糟的 $\textrm{Subtask}$。所以对于不同 $\textrm{Subtask}$ 可能存在一些小坑。由于这些细枝末节的地方没有太大难度，这里不再赘述。

## $\small\textbf{Subtask 3}$

这个 $\textrm{Subtask}$ 的特殊性质是，$m=1$ 且 $g_i$ 所有元素都是 $1$。那么建出来的 $\text{AC}$ 自动机肯定是一条边全部都是 $1$ 的链。那么对于自动机上的节点，只要转移时的边不是 $1$，那都会转移到根节点去，因此可以在这里下文章，对于任意的 $i$ 预处理出 $T_i=\sum_{j=2}^k p(i,j)$，那么在枚举 $c$ 的时候就可以剪掉一大堆情况。

同样是这个 $\textrm{Subtask}$，注意不要算了个 $\mathcal O(k^3)$ 复杂度的矩阵乘法导致超时。此外，由于 $k$ 比较大，在 $\textrm{AC}$ 自动机进行预处理的时候可能有些需要特判的地方，诸如可能要使用 $\text{map}$ 来维护字典树上一个节点向儿子的边。

时间复杂度为 $\mathcal O(n\cdot |\sum g_i|)$。

## 参考代码

这个是小波的：

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int MOD =1000000007;
const int MAXN=1e5+3,MAXM=1e3+3,MAXK=10+3;
int n,m,k,h,s,g,w,S[MAXN],P[MAXN],F[MAXN],T[MAXM]; bool N[MAXN];
int X[MAXM][MAXM],Y[MAXM][MAXM],Z[MAXM][MAXM];
int A[MAXN][2],B[MAXN][2],D[MAXN][MAXK]; map<int,int> C[MAXN];
void ins(int *U){
	int p=0; for(int i=1;U[i];p=C[p][U[i++]]){
		if(!C[p].count(U[i])) C[p][U[i]]=++s;}
	N[p]^=1;
}
void bld(){
	queue <int> Q; Q.push(0); while(!Q.empty()){
		int u=Q.front(); Q.pop(); for(auto &v:C[u]){
			int x=v.first,y=v.second,t=F[u]; Q.push(y);
			while(t!=0&&!C[t].count(x)) t=F[t];
			if(C[t].count(x)&&C[t][x]!=y) t=C[t][x];
			F[y]=t,N[y]^=N[t];
		}
		if(k<=10) up(1,k,j)
			D[u][j]=C[u].count(j)?C[u][j]:D[F[u]][j];
	}
}
void slv(){
	if(h==0){
		int p=0,u,t; bool f=false; up(1,n,i) if(t=S[i]){
			u=p; while(!C[u].count(t)&&u!=0) u=F[u];
			if(C[u].count(t)) u=C[u][t]; f^=N[u]; p=u,printf("%d\n",f);
		}
		return;
	}
	up(1,k,i) up(2,k,j) T[i]=(T[i]+X[i][j])%MOD;
	A[0][0]=1; up(1,n,i){
		bool f; int ans=0,u; up(0,s,j) up(1,k,t){
			if(w&&t!=1){
				B[0][0]=(1ll*A[j][0]*T[S[i]]%MOD+B[0][0])%MOD;
				B[0][1]=(1ll*A[j][1]*T[S[i]]%MOD+B[0][1])%MOD;
				break;
			}
			if(k<=10) u=D[j][t],f=N[u]; else {
				u=j; while(!C[u].count(t)&&u!=0) u=F[u];
				u=C[u][t]; f=N[u];
			}
			B[u][0]+=1ll*A[j][ f]*X[S[i]][t]%MOD,B[u][0]>=MOD&&(B[u][0]-=MOD);
			B[u][1]+=1ll*A[j][!f]*X[S[i]][t]%MOD,B[u][1]>=MOD&&(B[u][1]-=MOD);
		}
		up(0,s,j) ans=(ans+B[j][1])%MOD,
			A[j][0]=B[j][0],B[j][0]=0,
			A[j][1]=B[j][1],B[j][1]=0;
		printf("%lld\n",1ll*ans*g%MOD);
	}
}
int qrd(){
	int w=1,c,ret;
	while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
	while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
	return ret*w;
}
int pwr(int x,int y){
	int r=1; while(y){
		if(y&1) r=1ll*r*x%MOD; x=1ll*x*x%MOD,y>>=1; }
	return r;
}
int inv(int x){return pwr(x,MOD-2);}
int main(){
	n=qrd(),m=qrd(),k=qrd(),h=qrd(),w=0; up(1,n,i) S[i]=qrd();
	up(1,m,i){
		int p=qrd(); up(1,p,i) P[i]=qrd(),w|=P[i]; P[p+1]=0,ins(P);
	}
	w=w==1,bld();
	up(1,k,i){
		int s=0; up(1,k,j) Y[i][j]=qrd(),s=(s+Y[i][j])%MOD;
		s=inv(s);up(1,k,j) Y[i][j]=1ll*Y[i][j]*s%MOD;
	}
	up(1,k,i) X[i][i]=1;
	if(h!=0){
		up(1,k,i) up(1,k,j) X[i][j]=Y[i][j];
		up(2,h,o){
			up(1,k,i) up(1,k,j) up(1,k,l)
				Z[i][j]=(1ll*X[i][l]*Y[l][j]%MOD+Z[i][j])%MOD;
			up(1,k,i) up(1,k,j) X[i][j]=Z[i][j],Z[i][j]=0;
		}
	}
	g=pwr(2,h),slv(); return 0;
}
```

这个是 $\textsf{yzy}$ 的（去掉了部分缺省源以防止占用大量篇幅，但不影响阅读）：

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lf;

#define rep(i, f, t) for (int i = (f), ed##i = (t); i <= ed##i; ++i)
#define re(i, t) rep (i, 1, t)
#define per(i, t, f) for (int i = (t), ed##i = (f); i >= ed##i; --i)
#define ste(i, f, t, s) for (int i = (f), ed##i = (t); i <= ed##i; i += s)
#define each(i, x) for (auto &&i : (x))
#define nxt(i, f, g) for (int i = g.h[f]; i; i = g.e[i].n)
#define dbg(x) (cerr << "(dbg) " << #x " = " << (x) << '\n')
#define umod(x) ((x) >= mo && ((x) -= mo))
#define dmod(x) ((x) < 0 && ((x) += mo))
#define up(x, y) (((x) < (y)) && ((x) = (y)))
#define down(x, y) (((x) > (y)) && ((x) = (y)))

const int N = 1e5 + 9;
const int mo = 1000000007;

int K;

struct Trie {
  int e[N][109], ed[N], fal[N], tot = 1;
  void Ins(const vector<int> &v) {
    int x = 1;
    each (c, v)
      x = e[x][c] = (e[x][c] ?: ++tot);
    ++ed[x];
  }
  void AC() {
    re (i, K)
      e[0][i] = 1;
    queue<int> q{{1}};
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      re (c, K) {
        if (e[x][c])
          fal[e[x][c]] = e[fal[x]][c], q.push(e[x][c]);
        else
          e[x][c] = e[fal[x]][c];
      }
    }
  }
} tr;

struct G {
  int tot, h[N];
  struct E {
    int t, n;
  } e[N];
  inline void Add(int f, int t) { e[++tot] = {t, h[f]}, h[f] = tot; }
} falg;

int n, a[N], m, T, sumed[N], rd[N];
vector<int> b[N];

void Topo() {
  // re (i, tr.tot) {
  //   for (int j = i; j; j = tr.fal[j]) sumed[i] += tr.ed[j], umod(sumed[i]);
  //   // dbg(sumed[i]);
  // }
  re (i, tr.tot)
    if (tr.fal[i]) falg.Add(tr.fal[i], i), ++rd[i], sumed[i] += tr.ed[i];
  queue<int> q;
  re (i, tr.tot)
    if (rd[i] == 0) q.push(i);
  while (!q.empty()) {
    int qf = q.front();
    q.pop();
    nxt (i, qf, falg) {
      auto t = falg.e[i].t;
      sumed[t] += sumed[qf];
      if (--rd[t] == 0) q.push(t);
    }
  }
}

namespace st4 {
int f[2][N], g[2][N], ans[N], sump[N];

struct Mat {
  ll m[12][12];
} bas, p;

void DP() {
  f[0][1] = 1;
  // re (i, tr.tot) {
  //   for (int j = i; j; j = tr.fal[j]) sumed[i] += tr.ed[j], umod(sumed[i]);
  //   // dbg(sumed[i]);
  // }
  rep (i, 0, n) {
    // if (i % 1000 == 0) dbg(i);
    int ii = i & 1;
    re (j, tr.tot) {
      // g[ii][j] = 1ll * Pow(f[ii][j], mo - 2, mo) * g[ii][j] % mo;
      if (sumed[j] & 1) g[ii][j] = (0ll + mo + f[ii][j] - g[ii][j]) % mo;
      // cerr << i << ' ' << j << ' ' << g[ii][j] << '\n';
      ans[i] += g[ii][j], umod(ans[i]);
      re (c, K) {
        int t = tr.e[j][c];
        f[ii ^ 1][t] += 1ll * f[ii][j] * p.m[a[i + 1]][c] % mo, umod(f[ii ^ 1][t]);
        g[ii ^ 1][t] += 1ll * p.m[a[i + 1]][c] * g[ii][j] % mo, umod(g[ii ^ 1][t]);
      }
    }
    rep (j, 0, tr.tot)
      f[ii][j] = 0, g[ii][j] = 0;
  }
}

Mat operator*(Mat a, Mat b) {
  Mat res;
  memset(res.m, 0, sizeof res.m);
  re (i, K)
    re (j, K)
      re (k, K)
        res.m[i][j] += 1ll * a.m[i][k] * b.m[k][j] % mo, umod(res.m[i][j]);
  return res;
}

void Mpow(int k) {
  while (k) {
    if (k & 1) p = p * bas;
    bas = bas * bas;
    k >>= 1;
  }
}

void Main() {
  re (i, m) {
    int sz = in();
    re (j, sz)
      b[i].emplace_back(in());
    tr.Ins(b[i]);
  }
  tr.AC();
  Topo();
  re (i, K) {
    in(p.m[i], K);
    re (j, K)
      sump[i] += p.m[i][j], umod(sump[i]);
    int ny = Pow(sump[i], mo - 2, mo);
    re (j, K)
      bas.m[i][j] = p.m[i][j] = 1ll * p.m[i][j] * ny % mo;
  }
  Mpow(T - 1);
  DP();
  re (i, n)
    out(1ll * ans[i] * Pow(2, T, mo) % mo)('\n');
}
}  // namespace st4

namespace st1 {
void Main() {
  re (i, m) {
    int sz = in();
    re (j, sz)
      b[i].emplace_back(in());
    tr.Ins(b[i]);
  }
  tr.AC();
  Topo();
  int x = 1;
  int res = 0;
  re (i, n) {
    x = tr.e[x][a[i]];
    res += sumed[x];
    if (res & 1)
      out(1)('\n');
    else
      out(0)('\n');
  }
}
}  // namespace st1

namespace st3 {
const int N = 1e3 + 9;
int sump[N], p[N][N], f[N][N], g[N][N], ans[N];

void Main() {
  re (i, m) {
    int sz = in();
    re (j, sz)
      b[i].emplace_back(in());
  }
  re (i, K) {
    in(p[i], K);
    re (j, K)
      sump[i] += p[i][j], umod(sump[i]);
    int ny = Pow(sump[i], mo - 2, mo);
    re (j, K)
      p[i][j] = 1ll * p[i][j] * ny % mo;
    sump[i] = 0;
    re (j, K)
      sump[i] += p[i][j], umod(sump[i]);
  }
  f[0][0] = 1;
  re (i, n) {
    rep (j, 0, i) {
      f[i][0] += 1ll * f[i - 1][j] * ((mo + sump[a[i]] - p[a[i]][1]) % mo) % mo, umod(f[i][0]);
      g[i][0] += 1ll * g[i - 1][j] * ((mo + sump[a[i]] - p[a[i]][1]) % mo) % mo, umod(g[i][0]);
    }
    re (j, i) {
      f[i][j] = 1ll * f[i - 1][j - 1] * p[a[i]][1] % mo, umod(f[i][j]);
      g[i][j] = 1ll * g[i - 1][j - 1] * p[a[i]][1] % mo, umod(g[i][j]);
    }
    rep (j, 0, i) {
      if (j >= (int)b[1].size()) g[i][j] = (0ll + mo + f[i][j] - g[i][j]) % mo;
      ans[i] += 1ll * g[i][j] % mo, umod(ans[i]);
    }
  }
  re (i, n)
    out(1ll * ans[i] * 2 % mo)('\n');
}
}  // namespace st3

signed main() {
  in(n)(m)(K)(T)(a, n);
  if (T == 0) st1::Main(), exit(0);
  if (m == 1 && K > 10) st3::Main(), exit(0);
  st4::Main();
  return 0;
}

---

