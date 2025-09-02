# [GCJ Farewell Round #4] Genetic Sequences

## 题目描述

Margaret 正在研究基因序列。她正在分析一种新型生命体的两个序列 $\mathbf{A}$ 和 $\mathbf{B}$，这种生命体不使用典型的四字母遗传密码。基因序列的编码方便地使用了 26 个大写英文字母 'A' 到 'Z' 来表示。

Margaret 想要比较序列 $\mathbf{A}$ 和 $\mathbf{B}$。最佳方法是进行一系列序列分析测试。每个测试需要从 $\mathbf{A}$ 中取出一个前缀（称为 $\mathbf{A}$-前缀），包含 $\mathbf{A}$ 的前 $\mathbf{P}$ 个字母；同时从 $\mathbf{B}$ 中取出一个后缀（称为 $\mathbf{B}$-后缀），包含 $\mathbf{B}$ 的最后 $\mathbf{S}$ 个字母。然后 Margaret 需要比较 $\mathbf{A}$-前缀和 $\mathbf{B}$-后缀。子串是指连续的字母子序列。如果 $\mathbf{B}$-后缀以某个 $\mathbf{A}$-前缀的子串开头，即该子串是 $\mathbf{B}$-后缀的前缀，则称该子串与 $\mathbf{B}$-后缀匹配。测试的结果是 $\mathbf{A}$-前缀中能与 $\mathbf{B}$-后缀匹配的最长子串的长度。

Margaret 需要一些软件来确定一批 $\mathbf{Q}$ 个序列分析测试的结果。注意每个测试都是独立的。Margaret 有 $\mathbf{A}$ 和 $\mathbf{B}$ 的多个副本，每个测试都使用新的副本。


## 说明/提示

**样例解释**

在样例 #1 中，有 3 个测试。第一个测试比较 $\mathbf{A}$ 的前缀 $\mathbf{A B C}$ 和 $\mathbf{B}$ 的完整后缀 $\mathbf{C A B A B A}$。答案是 1，因为 $\mathbf{C}$ 是 $\mathbf{A B C}$ 中包含的最长子串，且是 $\mathbf{C A B A B A}$ 的前缀。第二个测试比较 $\mathbf{A B C A B A C}$ 和 $\mathbf{C A B A B A}$，最长匹配是 $\mathbf{C A B A}$。第三个测试比较 $\mathbf{A B C A B A}$ 和 $\mathbf{A B A B A}$，最长匹配是 $\mathbf{A B A}$。

在样例 #2 中，有 2 个测试。第一个测试比较 $\mathbf{B A N A N}$ 和 $\mathbf{B A N A}$，最长匹配是 $\mathbf{B A N A}$。第二个测试比较 $\mathbf{B A N A N}$ 和 $\mathbf{A B A N A}$，最长匹配是 $\mathbf{A}$。

在样例 #3 中，有一个测试。比较 $\mathbf{A B}$ 和 $\mathbf{D}$。由于没有匹配，答案是 0。

**限制**

- $1 \leq \mathbf{T} \leq 100$。
- $1 \leq \mathbf{P}_i \leq \mathbf{A}$ 的长度。
- $1 \leq \mathbf{S}_i \leq \mathbf{B}$ 的长度。

**测试集 1（5 分，可见评测结果）**

- $1 \leq \mathbf{A}$ 的长度 $\leq 3000$。
- $1 \leq \mathbf{B}$ 的长度 $\leq 3000$。
- $1 \leq \mathbf{Q} \leq 3000$。

**测试集 2（17 分，隐藏评测结果）**

- $1 \leq \mathbf{A}$ 的长度 $\leq 10^5$。
- $1 \leq \mathbf{B}$ 的长度 $\leq 10^5$。
- 所有测试用例中 $\mathbf{A}$ 的长度总和 $\leq 5 \times 10^5$。
- 所有测试用例中 $\mathbf{B}$ 的长度总和 $\leq 5 \times 10^5$。
- $1 \leq \mathbf{Q} \leq 10^5$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
ABCABAC CABABA 3
3 6
7 6
6 5
BANANA HABANA 2
5 4
5 5
ABC ABD 1
2 1```

### 输出

```
Case #1: 1 4 3
Case #2: 4 1
Case #3: 0```

# 题解

## 作者：Iniaugoty (赞：2)

后缀自动机力大砖飞。

记 $A$ 串的 $p$ 前缀为 $A'$，$B$ 串的 $s$ 后缀为 $B'$。

多次询问，给定 $s, p$，求 $B'$ 的最长前缀，满足它在 $A'$ 中作为子串出现过。

很难不想到对 $A$ 和 $B$ 的反串建立广义 SAM。

容易找到 $B'$ 对应的结点，设其为 $u$。那么在 parent tree 上，$u$ 及其全部祖先恰好对应了所有 $B'$ 的前缀。我们在这条到根的链上求一些什么 $\max$。

考虑这条链上的某个点 $v$。设 $v$ 在 $A$ 串中第一次出现的位置为 $f _ v$（即 $\operatorname {endpos}$ 集合中的 $\min$，这是容易预处理的），设 $v$ 表示的所有串中最长的长度为 $g _ v$（即 $\operatorname {maxlen}$），那么 $v$ 对于答案的贡献就是 $\min(p - f _ v + 1, g _ v)$，前者保证了这个东西是 $A'$ 的子串，后者保证了这个东西是 $B'$ 的前缀。

要求 $\min(p - f _ v + 1, g _ v)$ 的 $\max$。注意到，随着深度的增加，$f _ v$ 是不减的（孩子的 $\operatorname {endpos}$ 集合被父亲包含），$g _ v$ 是增加的（parent tree 基本的性质）。于是这个形如一个上升函数和一个下降函数的 $\min$。那么它将在中间相交的位置取到 $\max$。

我们做一个倍增找到这个位置。具体地，跳到最浅的 $w$ 满足 $p - f _ w + 1 \le g _ w$，则答案一定在 $w$ 或 $w$ 的父亲上取到。

设 $\vert A \vert + \vert B \vert = n$，时间复杂度为 $O(n \Sigma + (n + q) \log n)$。

讲个笑话，一开始笔者用线段树合并求 $\operatorname {endpos}$ 集合的 $\min$，写题解的时候才发现有点奇怪。

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, LL> pii;
const int N = 2e6 + 5;

int n, m, q; char a[N], b[N];

int cnt, las, fa[N], len[N], c[N][26];
int buc[N], id[N], ida[N], idb[N], f[N][21], val[N];
void Insert(char s) {
  int it = s - 'A', p = las, w = c[p][it];
  if (w && len[p] + 1 == len[w]) return las = w, void();
  int u = ++cnt; len[las = u] = len[p] + 1;
  while (p && !c[p][it]) c[p][it] = u, p = fa[p];
  if (!p) return fa[u] = 1, las = u, void();
  int q = c[p][it];
  if (len[p] + 1 == len[q]) return fa[u] = q, void();
  int v = (w ? u : ++cnt); F(i, 0, 25) c[v][i] = c[q][i];
  len[v] = len[p] + 1, fa[v] = fa[q], fa[q] = v; if (!w) fa[u] = v;
  while (c[p][it] == q) c[p][it] = v, p = fa[p];
}

void mian() {
  cin >> (a + 1) >> (b + 1)>> q, cnt = 1;
  n = strlen(a + 1), m = strlen(b + 1);
  las = 1; dF(i, n, 1) Insert(a[i]), ida[i] = las;
  las = 1; dF(i, m, 1) Insert(b[i]), idb[i] = las;
  F(i, 1, cnt) ++buc[len[i]];
  F(i, 1, max(n, m)) buc[i] += buc[i - 1];
  dF(i, cnt, 1) id[buc[len[i]]--] = i;
  F(i, 2, cnt) {
    int u = id[i]; f[u][0] = fa[u];
    F(j, 1, 20) f[u][j] = f[f[u][j - 1]][j - 1];
  }
  F(i, 1, cnt) val[i] = N;
  F(i, 1, n) val[ida[i]] = i;
  dF(i, cnt, 2) {
    int u = id[i], f = fa[u];
    val[f] = min(val[f], val[u]);
  }
  while (q--) {
    int p, s; cin >> p >> s;
    int u = idb[m - s + 1], ans = 0;
    dF(i, 20, 0)
      if (f[u][i] && p - val[f[u][i]] + 1 <= len[f[u][i]])
        u = f[u][i];
    ans = max(ans, min(p - val[u] + 1, len[u]));
    if (fa[u]) ans = max(ans, min(p - val[fa[u]] + 1, len[fa[u]]));
    cout << ans << " ";
  }
  F(i, 1, max(n, m)) buc[i] = 0;
  F(i, 1, cnt) {
    fa[i] = len[i] = 0;
    F(j, 0, 20) f[i][j] = 0;
    F(j, 0, 25) c[i][j] = 0;
  }
}

int main() {
  // freopen("zyq.in", "r", stdin);
  // freopen("zyq.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int _; cin >> _;
  F(i, 1, _)
    cout << "Case #" << i << ": ",
    mian(), cout << "\n";
  return 0;
}
```

---

