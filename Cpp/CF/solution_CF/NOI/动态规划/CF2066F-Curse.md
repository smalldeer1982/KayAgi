# Curse

## 题目描述

给定两个整数数组 $a_1, a_2, \ldots, a_n$ 和 $b_1, b_2, \ldots, b_m$。

你需要判断是否可以通过若干次（可能为零）如下操作将数组 $a$ 转换为数组 $b$。

- 在所有 $a$ 的非空子数组$^{\text{∗}}$中，选择一个具有最大和的子数组，并将该子数组替换为任意非空整数数组。

如果可能，你需要构造任意可行的操作序列。约束条件：你的答案中，所有操作使用的替换数组的长度之和不得超过 $n + m$。所有数字的绝对值不得超过 $10^9$。

$^{\text{∗}}$ 如果数组 $a$ 可以通过从数组 $b$ 的开头和结尾删除若干（可能为零或全部）元素得到，则称 $a$ 是 $b$ 的子数组。


## 说明/提示

在第一个测试用例中，初始数组按以下方式修改：

$$ [2, -3, 2, 0] \to [2, -3, -3] \to [-3, -3, -3] \to [-3, -7, -3] \to [-3, -7, 0] $$

你可以选择输出空行或不输出。示例中的空行仅为方便阅读添加。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4 3
2 -3 2 0
-3 -7 0
2 1
-2 -2
2
5 4
-5 9 -3 5 -9
-6 6 -1 -9```

### 输出

```
4
3 4 1
-3 

1 1 1
-3 

2 2 1
-7 

3 3 1
0
 
-1

3
2 4 1
-5 

1 1 1
-6 

2 2 2
6 -1```

# 题解

## 作者：rizynvu (赞：1)

[cnblogs](https://www.cnblogs.com/fiosiate/p/18981002)。

这也太难了，成[官方题解](https://codeforces.com/blog/entry/139415?locale=en)复读机了/ll。

首先考虑一个例子：$a = [-1, -1]$。

那么接下来的操作一定是选择一个 $-1$ 进行替换，接下来分讨替换的数组的最大子段和：

- 若 $> -1$，则接下来只能替换这个数组中的最大子段和的位置。
- 若 $= -1$，则接下来可以替换这个数组中的最大子段和的位置，也可以替换 $-1$。注意这个时候如果一个连续段既包含了左边的一部分又包含了 $-1$ 则其和一定 $< -1$，所以这是不可能的。
- 若 $< -1$，则接下来只能替换右边的 $-1$。

于是能够发现，我们可以增加一个分界符：$[-1, |, -1]$，其中每一步替换一定不会跨过分界符。

那么接下来就是要尝试去划分分界符了。  
首先考虑找到最大子段和的段 $[l_i, r_i](1\le i\le m)$，此时称第 $i$ 段是有用的当且仅当不存在 $1\le j\le m, j\not = i$ 满足 $[l_j, r_j]\subseteq [l_i, r_i]$，然后只保留下这些有用的段，对于中间的一些没有分进段内的元素继续递归下去分段。  

这是因为若 $[l_j, r_j]\subseteq [l_i, r_i]$，那么把 $[l_j, r_j]$ 替换成任意的数组 $a'$ 都可以通过把 $[l_i, r_i]$ 替换成 $[l_i, l_j) + a' + (r_j, r_i]$（这里的 $+$ 指拼接）来实现。

因为有用的段不交，所以这个划分一定可以进行。  
证明：考虑若 $[l_i, r_i]\cap [l_j, r_j]\not = \varnothing$ 且互不包含，不妨令 $l_i < l_j$，那么有 $sum(l_i, r_j) + sum(l_j, r_i) = sum(l_i, r_i) + sum(l_j, r_j)$，所以一定可以尝试替换为更大的 $sum$ 的区间或者替换为长度更长的 $[l_i, r_j]$。

实现时可以直接考虑找出给定范围 $[l, r]$ 中和最大且长度最长的区间， 然后往两侧递归。

于是此时其实就已经知道了所有分界线，也就可以划分出许多个段 $[l_i, r_i](1\le i\le m)$（这里的名字跟上面的重了，但是因为上面的定义都不会用到了就这样吧）。  
这些划分出来的段一定满足，对于这个段内的第一次替换操作一定是把整个段替换段。

紧接着，我们可以说明，进行的替换操作一定形如这样：

- 选择一个值 $x$，也就是主动划分了一个分界线。
- 对于所有 $sum(l_i, r_i) < x$ 的段全部保留。
- 对于 $sum(l_i, r_i)\ge x$ 的段均可以进行替换，但是要保证至多一个段替换后最大子段和 $> x$。

如果合法，那么这个过程是一定可以构造的，考虑先把所有 $sum(l_i, r_i)\ge x$ 的段都直接替换为 $[x]$（即 $x$ 一个元素），然后先处理 $sum(l_i, r_i)\le x$ 的段，最后处理 $sum(l_i, r_i) > x$ 的段。

且这样其实也说明了每一段至多也只会替换一次。

于是可以外层枚举 $x$，内层设计一个 dp。  

设 $f_{i, j, 0 / 1}$ 表示目前在区间顺序（$l_i$ 升序）的第 $i$ 个区间，目前在匹配 $b$ 数组的第 $j$ 个位置，此时是否有选择最大子段和 $> x$ 的段是否可行。

转移考虑进行分讨：

- 若 $sum(l_i, r_i) < x$，则无法匹配，直接枚举每个 $j$ 然后尝试接下来的 $r_i - l_i + 1$ 个元素，复杂度是 $\mathcal{O}(\sum\limits_{i} (r_i - l_i + 1)m) = \mathcal{O}(nm)$ 的。

- 若 $sum(l_i, r_i)\ge x$，则继续分讨接下来是选择替换成什么样的段：

  - 若选择替换成最大子段和 $> x$ 的段，那么这一段可以匹配上 $j$ 为左端点的任意一个区间，即 $f_{i + 1, k + 1, 1}(j\le k\le m)$。
  - 若选择替换成最大子段和 $\le x$ 的段，考虑找到最大的 $k$ 满足 $b$ 中 $[j, k]$ 最大子段和 $\le x$，那么就可以替换为左端点为 $j$ 右端点 $\le k$ 的任意区间，即 $f_{i + 1, h + 1, *}(j\le h\le k)$。

  若直接转移复杂度是 $\mathcal{O}(nm^2)$ 的。

  但是考虑到此时只关心合法性，若一个位置已经为 $1$ 显然不需要重复赋值。  
  所以对于第一类，肯定只需要找到最小的 $j$ 满足 $f_{i, j, 0}$ 合法即可，复杂度为 $\mathcal{O}(nm)$。  
  对于第二类，首先 $k$ 可以通过双指针解决，对于转移可以维护一个指针 $r_{0 / 1}$ 表示 $\le r_{o}$ 的类型为 $o$ 的右端点都不需要考虑了，均摊可以知道复杂度也为 $\mathcal{O}(nm)$。

于是求解合法性的过程都可以在 $\mathcal{O}(nm^2)$ 的复杂度内做完。

对于构造，其实刚刚 dp 的过程就已经给出了对应的步骤，记录下来按照上文所述的构造方法构造即可。

我划分段时写的很暴力，复杂度是 $\mathcal{O}(n^3 + nm^2)$ 的。

代码也基本是参考的 std/ll。

```c++
#include <bits/stdc++.h>

constexpr int inf = 1e9;

constexpr int maxn = 500 + 5;

int n, a[maxn], suma[maxn];
int m, b[maxn], sumb[maxn];

std::vector<std::vector<int>> par;
std::vector<int> parsum;

void split(int l, int r) {
    if (l > r) return ;

    std::array<int, 4> mx = {-inf, 0, 0, 0};
    for (int i = l; i <= r; i++) {
        for (int j = i; j <= r; j++) {
            mx = std::max(mx, {suma[j] - suma[i - 1], j - i + 1, i, j});
        }
    }

    split(l, mx[2] - 1);
    par.push_back({});
    for (int i = mx[2]; i <= mx[3]; i++) {
        par.back().push_back(a[i]);
    }
    parsum.push_back(mx[0]);
    split(mx[3] + 1, r);
}

int mxb[maxn][maxn];

std::vector<std::tuple<int, int, std::vector<int>>> ans;

bool dp[maxn][maxn][2];
std::array<int, 2> lst[maxn][maxn][2];

inline bool check(int bound) {
    for (int i = 0; i <= par.size(); i++) {
        memset(dp[i], 0, sizeof(dp[i]));
    }
    dp[0][1][0] = true;

    for (int i = 0; i < par.size(); i++) {
        if (par[i] != std::vector<int>{inf}) {
            for (int j = 1; j + par[i].size() - 1 <= m; j++) {
                bool ok = true;
                for (int k = 0; ok && k < par[i].size(); k++) {
                    ok &= par[i][k] == b[j + k];
                }
                
                if (! ok) continue;
                for (int o : {0, 1}) {
                    if (dp[i][j][o]) {
                        dp[i + 1][j + par[i].size()][o] = true;
                        lst[i + 1][j + par[i].size()][o] = {j, o};
                    }
                }
            }
            continue;
        }

        int lstk[2] = {0, 0};
        for (int j = 1, r = 1; j <= m; j++) {
            if (r < j) r++;
            while (r <= m && mxb[j][r] <= bound) r++;
            
            if (! lstk[0] && dp[i][j][0]) {
                for (int k = j; k <= m; k++) {
                    dp[i + 1][k + 1][1] = true;
                    lst[i + 1][k + 1][1] = {j, 0};
                }
            }

            for (int o : {0, 1}) {
                if (dp[i][j][o]) {
                    lstk[o] = std::max(lstk[o], j);
                    while (lstk[o] < r) {
                        dp[i + 1][lstk[o] + 1][o] = true;
                        lst[i + 1][lstk[o] + 1][o] = {j, o};
                        lstk[o]++;
                    }
                }
            }
        }
    }

    if (! dp[par.size()][m + 1][1]) return false;

    int ci = -1, cl = -1, cr = -1;
    for (int i = par.size(), j = m + 1, o = 1; i > 0; i--) {
        auto [lstj, lsto] = lst[i][j][o];
        if (par[i - 1] == std::vector<int>{inf}) {
            if (o == lsto) {
                int id = 0;
                for (int k = 0; k < i - 1; k++) id += par[k].size();
                std::vector<int> now;
                for (int k = lstj; k < j; k++) now.push_back(b[k]);
                ans.emplace_back(id, id + par[i - 1].size() - 1, now);
                par[i - 1] = now;
            } else {
                ci = i - 1, cl = lstj, cr = j - 1;
            }
        }
        j = lstj, o = lsto;
    }

    int id = 0;
    for (int j = 0; j < ci; j++) id += par[j].size();
    std::vector<int> now;
    for (int j = cl; j <= cr; j++) now.push_back(b[j]);
    ans.emplace_back(id, id + par[ci].size() - 1, now);
    par[ci] = now;

    return true;
}

inline void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &b[i]);

    for (int i = 1; i <= n; i++) suma[i] = suma[i - 1] + a[i];
    for (int i = 1; i <= m; i++) sumb[i] = sumb[i - 1] + b[i];

    par.clear(), parsum.clear();
    split(1, n);

    for (int i = 1; i <= m; i++) mxb[i][i] = b[i];
    for (int l = m; l >= 1; l--) {
        for (int r = l + 1; r <= m; r++) {
            mxb[l][r] = std::max({mxb[l + 1][r], mxb[l][r - 1], sumb[r] - sumb[l - 1]});
        }
    }

    std::vector<int> order(par.size());
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int x, int y) {
        return parsum[x] > parsum[y];
    });

    ans.clear();
    for (int p = 0; p < order.size(); p++) {
        const int i = order[p];
        const int bound = parsum[i];
        
        int id = 0;
        for (int j = 0; j < i; j++) id += par[j].size();
        ans.emplace_back(id, id + par[i].size() - 1, std::vector<int>{inf});
        par[i] = {inf};

        if (p + 1 < order.size() && parsum[order[p + 1]] == bound) continue;

        if (check(bound)) {
            printf("%zu\n", ans.size());
            for (auto [l, r, vec] : ans) {
                printf("%d %d %zu\n", l + 1, r + 1, vec.size());
                for (int x : vec) printf("%d ", x == inf ? bound : x);
                puts("");
            }
            return puts(""), void();
        }
    }
    printf("-1\n\n");
}

int main() {
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}
```

---

## 作者：3a51_ (赞：1)

出题人不想要自己的妈妈了，于是给这道题增加了需要输出方案。

---

定义 $\text{m}(a)$ 表示 $a$ 的最大子数组和，$\text{s}(a)$ 表示 $a$ 的和。

原题要替换的一定是 $\text{s}(k)=\text{m}(a)$ 的一个子数组 $k$。同时也有一个很简单的观察：$\forall k_1\subset k_2$，替换 $k_2$ 一定比替换 $k_1$ 更优。所以不妨每次都对这种**不存在任何一个 $k'$ 满足 $\text{s}(k')=\text{m}(a)$ 且 $k\subset k'$ 的 $k$**（下文简记为最优子数组）进行替换。

不难发现最优子数组一定不相交，于是一个很自然的想法就是把整个数组递归地分为若干个块：

- 选择一个最优子数组，将该最优子数组分为一个块，递归处理左边和右边。

然后手搓几次操作，就会得到一个很强的性质：

**如果 $a_i$ 和 $a_j$ 不属于同一个块，那么永远无法同时替换 $a_i$ 和 $a_j$**。换句话说，块的边界永远不会被打破。

证明是简单的，设 $i<j$。假设一次操作同时替换了 $a_i$ 和 $a_j$，即操作区间 $[l,r]$ 满足 $l\leq i$ 且 $j\leq r$，则 $[l,r]$ 一定不是最优子数组。而我们已规定只能在最优子数组上进行操作。

考虑 $a$ 最终可以变为哪些数组。令 $x$ 表示所有被替换了的最优子数组里面 $\text{m}$ 的最大值，那么最终通过 $a$ 得到的数组一定具有以下特征：

- 先将所有满足 $\text{m}(k)\geq x$ 的最优子数组**恰好替换一次**，且替换后的数组 $k'$ 满足 $\text{m}(k')\leq x$；
- 随后再将任意一个 $\text{m}(k)=x$ 的最优子数组替换为**任意数组**并结束操作。

称最后一次替换为特殊替换。为了使被特殊替换的数组 $k_0$ 满足 $\text{m}(k_0)=x$，不妨在进行非特殊替换的时候将被特殊替换的数组先替换为 $k_0=\{x\}$。由于非特殊替换的替换数组 $k'$ 都满足 $\text{m}(k')\leq x$，所以特殊替换一定能够替换 $k_0$。 

然后就可以 dp 了。枚举 $x$，设 $f(i,j,0/1)$ 表示 $a$ 中的前 $i$ 块在没使用/使用了特殊替换的情况下能否与 $b$ 的前 $j$ 个数匹配。转移时双指针维护前 $i-1$ 块替换了的元素个数最大值 $t$ 即可，注意需要记录路径。

输出方案的时候给所有记录的操作按照（是否为特殊操作，被替换数组的和的大小）进行双关键字排序，为了输出在原数组中的下标可以使用树状数组。实现起来细节比较多。

时间复杂度：直接做是 $O(n^2m^2)$ 的，容易超时，可以在转移的时候加一些小优化：

- 对于不使用特殊替换的转移，记录上一次的最优决策点，然后下一次枚举直接从最优决策点的下一个位置开始枚举；
- 由于 dp 记录的是可行性，所以转移成功了就可以 `break` 了。

优化后总时间复杂度 $O(n^2m)$。

[Submission（估计放了也没人看）](https://codeforces.com/contest/2066/submission/321854475)。

---

