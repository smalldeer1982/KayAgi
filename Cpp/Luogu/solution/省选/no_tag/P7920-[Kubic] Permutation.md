# [Kubic] Permutation

## 题目背景

建议先看 E 题题目背景。

## 题目描述

对于一个 $1\sim n$ 的排列 $p$，定义 $G_p$ 为使用以下方法构造出来的**无向图**：
- 对于每一个 $i\in (1,n]$，找到最大的 $j\in [1,i)$ 满足 $p_i>p_j$，然后连一条 $i,j$ 之间的边，如果不存在这样的 $j$ 则不连。

给定一棵有 $n$ 个节点的树 $T$。

把 $p$ 称为**好排列**当且仅当 $G_p$ 与 $T$ 同构。

如果存在**好排列**，输出其中**字典序最大**的一个。否则输出 $-1$。

无向图 $G_1,G_2$ 同构当且仅当存在一个 $1\sim n$ 的排列 $q$，满足 $\forall (u,v)\in G_1,(q_u,q_v)\in G_2,\forall (u,v)\notin G_1,(q_u,q_v)\notin G_2$。

## 说明/提示

对于 $100\%$ 的数据，$1\le u,v\le n\le 5\times 10^3$。

||分值|$n$|特殊性质|
|:-:|:-:|:-:|:-:|
|$\operatorname{Subtask}1$|$15$|$\le 8$|无|
|$\operatorname{Subtask}2$|$5$|无特殊限制|树退化为一条链|
|$\operatorname{Subtask}3$|$15$|无特殊限制|度数 $\ge 3$ 的节点个数 $\le 1$|
|$\operatorname{Subtask}4$|$20$|$\le 100$|无|
|$\operatorname{Subtask}5$|$20$|$\le 10^3$|无|
|$\operatorname{Subtask}6$|$25$|无特殊限制|无|

**说明：样例解释中的节点编号是 $p$ 中的下标。**

### 样例解释 1

$G_p$ 的形态如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/yawh0shj.png)

可以证明没有更优的方案。

### 样例解释 2

$G_p$ 的形态如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/o9vgydub.png)

可以证明没有更优的方案。

## 样例 #1

### 输入

```
5
1 2
1 3
2 4
2 5```

### 输出

```
1 5 4 2 3```

## 样例 #2

### 输入

```
9
1 2
2 3
1 4
4 5
5 6
1 7
7 8
8 9```

### 输出

```
1 9 2 6 7 8 3 4 5```

# 题解

## 作者：耶梦加得 (赞：3)

~~不清楚是不是正解反正能过~~

## 分析问题

这个题可能乍一看很高大上~~排列，同构，字典序 blablabla~~

然而我们稍微模拟一下，很容易建立出一个更直观的模型

给这个树的节点填上 $1-n$ 的数字，让它成为一个小根堆，并且把这些数字按照某个 dfs 序排列能够使得字典序最大。

~~我怀疑那个样例故意往图上填下标就是为了不让这个模型太过明显~~

（接下来我们以 $a[x]$ 指代标号为 $x$ 的节点上写的数字）

首先堆顶肯定是 $1$，接下来我们希望第二个遍历到的数字尽可能大，有没有可能第二个数字是 $n$ 呢？~~根据样例显然有可能~~

$n$ 已经是最大的数了，这又是一个小根堆，那么它不能有任何子节点。也就是说我们希望这个根有一个子节点是叶子节点，子树大小为 $1$。

我们进一步推广这个结论，容易发现，假如当前还没写上去的最大的数是 $mx$，当前节点为 $x$ 子树大小为 $sz[x]$，由于我们必须先写上 $sz - 1$ 个数，满足它们比 $a[x]$ 更大，所以 $a[x] \le mx - sz + 1$。

那么对于任何一个局面，$mx$ 固定，根据字典序的比较规则，我们贪心地希望 $a[x]$ 最大，那么就需要 $sz[x]$ 最小。

如果一样呢？

~~那就递归处理（雾）。~~

此时问题变成了两个**固定了根**的子树 ~~（否则就是递归到原问题原地爆炸）~~ ，选一个字典序大的排在前面。我们可以归纳地处理这个问题。

我们比较的不再是 $sz[x]$，而是一个由若干 sz 值构成的序列 $f[x]$。这个序列的构造，使得我们可以通过比较两个子节点的 $f[x]$ 的字典序，判断它们在 dfs 序中的先后。

~~算了太绕了我们直接举例子吧~~

~~手写丑图预警，轻喷~~

![样例，但改了改](https://cdn.luogu.com.cn/upload/image_hosting/bc974nzm.png)

圆圈内是我们填上的数（而非标号），这个图最终得到的序列是 1 9 2 6 8 7 3 4 5

~~大概能懂这个 $f$ 序列是什么意思了吧~~

由于我们优先考虑 $sz[x]$，因此 $f[x]$ 的首项就是 $sz[x]$，接下来是按 dfs 序的 $sz[v]$ （$v$ 为 $x$ 后代），具体实现时我们可以直接把它的儿子的 $f[x]$ 按照 dfs 序拼接起来（容易证明二者等价）。

~~算法本身正确性由字典序的贪心性可以感性理解一下。~~

## 定根时的 DP 解法

```cpp
vector<int> g[5007], f[5007];
int fa[5007];
inline bool cmp(int x, int y) {
    bool flag = true;
    if(f[x].size() > f[y].size()) {swap(x, y); flag = false;}
    for(int i = 0; i < f[x].size(); ++i) {
        if(f[x][i] < f[y][i]) return flag;
        if(f[x][i] > f[y][i]) return !flag;
    }
    if(f[x].size() < f[y].size()) return flag;
    return !flag;
}
int sz[5007];
int n;
void dfs1(int x) {
    sz[x] = 1; f[x].clear();
    for(int i = 0; i < g[x].size(); ++i) {
        if(g[x][i] != fa[x]) {
            fa[g[x][i]] = x;
            dfs1(g[x][i]);
            sz[x] += sz[g[x][i]];
        }
    }
    f[x].push_back(sz[x]);
    sort(g[x].begin(), g[x].end(), cmp);
    for(int i = 0; i < g[x].size(); ++i) {
        int k = g[x][i]; if(k == fa[x]) continue;
        for(int j = 0; j < f[k].size(); ++j) {
            f[x].push_back(f[k][j]);
        }
    }
}
```
由于 $|f[x]| = sz[x]$，易证所有 $f[x]$ 的总长度小于 $n^2$，那么瓶颈在于 sort 这一行上。

对于一个点 $u$ 和它的所有儿子 $v$，令 $u$ 有 $w$ 个儿子，那么比较次数是 $O(w \log w)$ 的。而单次比较的操作次数最多为两者 $f[x]$ 长度（亦即  $sz[x]$）的较小值。不严谨地说，我们总的操作次数应该不会超过（且实际上远小于）：

$\sum\overline{sz[v]}wlogw \approx \sum sz[x] logn = \sum n^2logn$

（欢迎各位大佬在评论区留言给出更严谨的说明 ~~wtcl~~）

好了细心的同学可能已经发现了，我们写的是 dfs1 

~~那势必有 dfs2~~

## 开始换根

~~不难发现如果我们对每个节点都作为根跑一次 dfs1 势必会 T~~

换根的思维难度不高，~~然而我自己的实现丑的要死~~

假设此时我们处理好了 $fa[x]$ 为根时的信息，那么我们把 $x$ 换成根，我们就要把 $fa[x]$ 旋下来，重新更新一遍信息。

暴力地遍历 $fa[x]$ 的儿子（我们已经排好序了），遇到不是 $x$ 的就合并。

但是停一下！在此之前，要二分地查找 $fa[fa[x]]$ 作为 $fa[x]$ 的儿子该塞在哪个位置，然后才能开始合并。

（由于我们似乎不能破坏已经排序好的数组，所以~~我~~只能用这种方式粗暴地解决问题）

然后我们故技重施，暴力查找 $fa[x]$ 应该扔在哪里，然后遍历 $x$ 的儿子，合并。

~~由于前面 cmp 函数写丑了所以这里会有一些 n + 2, n + 3 之类的数，本身并没有特别的意义。~~

```
int ansi;
vector<int> F[5007];
void dfs2(int x) {
    F[fa[x]].clear(); F[fa[x]].push_back(n - sz[x]);
    f[n + 3] = F[fa[fa[x]]];
    int pos = lower_bound(g[fa[x]].begin(), g[fa[x]].end(), n + 3, cmp) - g[fa[x]].begin();
    for(int i = 0; i < pos; ++i) {
        if(g[fa[x]][i] == x || g[fa[x]][i] == fa[fa[x]])continue;
        for(int j = 0; j < f[g[fa[x]][i]].size(); ++j) {
            F[fa[x]].push_back(f[g[fa[x]][i]][j]);
        }
    }
    for(int j = 0; j < F[fa[fa[x]]].size(); ++j) {
        F[fa[x]].push_back(F[fa[fa[x]]][j]);
    }
    for(int i = pos; i < g[fa[x]].size(); ++i) {
        if(g[fa[x]][i] == x || g[fa[x]][i] == fa[fa[x]])continue;
        for(int j = 0; j < f[g[fa[x]][i]].size(); ++j) {
            F[fa[x]].push_back(f[g[fa[x]][i]][j]);
        }
    }
    f[n + 3] = F[fa[x]]; f[n + 2].clear(); f[n + 2].push_back(n);
    pos = lower_bound(g[x].begin(), g[x].end(), n + 3, cmp) - g[x].begin();
    for(int i = 0; i < pos; ++i) {
        if(g[x][i] == fa[x])continue;
        for(int j = 0; j < f[g[x][i]].size(); ++j) {
            f[n + 2].push_back(f[g[x][i]][j]);
        }
    }
    for(int j = 0; j < F[fa[x]].size(); ++j) {
        f[n + 2].push_back(F[fa[x]][j]);
    }
    for(int i = pos; i < g[x].size(); ++i) {
        if(g[x][i] == fa[x])continue;
        for(int j = 0; j < f[g[x][i]].size(); ++j) {
            f[n + 2].push_back(f[g[x][i]][j]);
        }
    }
    if(cmp(n + 2, n + 1)) {
        ansi = x; f[n + 1] = f[n + 2];
    }
    for(int i = 0; i < g[x].size(); ++i) {
        if(g[x][i] != fa[x]) dfs2(g[x][i]);
    }
}
```
完结撒花！

~~gg，我们还没有输出~~

```cpp
int ans[5007];
void dfs(int x) {
    static int cnt = 0;
    ans[x] = ++cnt;
    for(int i = g[x].size() - 1; i >= 0; --i) {
        if(g[x][i] == fa[x]) continue;
        dfs(g[x][i]);
    }
}
void sfd(int x) {
    printf("%d ", ans[x]);
    for(int i = 0; i < g[x].size(); ++i) {
        if(g[x][i] == fa[x]) continue;
        sfd(g[x][i]);
    }
}
signed main() {
    scanf("%d", &n);
    for(int i = 1; i < n; ++i) {
        int a, b; scanf("%d %d", &a, &b);
        g[a].push_back(b); g[b].push_back(a);
    }
    dfs1(1); ansi = 1;
    f[n + 1] = f[1];
    for(int i = 0; i < g[1].size(); ++i) dfs2(g[1][i]);
    fa[ansi] = 0; dfs1(ansi);
    dfs(ansi); sfd(ansi);
    return 0;
}
```
 ~~（两个 dfs 用来输出看上去不太优雅，但是它能解决这道题）~~
 

---

## 作者：€€£ (赞：0)

乱搞选手前来报到

稍微讲一下乱搞思路把（$\color{white}{\text{剑指CSP T1三分}}$

首先考虑转化题意，在选定了根后，一个点一定要比他的所有儿子小；而为了题目中尽可能大，所以一定是尽可能地取大；

不妨先选定一个根，然后我们**由深到浅**地对于每个节点 $x$ 以及他的子树做如下处理，并记录以每个节点为根的子树的答案序列 $p$；

考虑以 $x$ 为根的子树单独拉出来如何考虑，我们将其子树 **按 size 为第一关键字（从小到大），以 p 为第二关键字（从大到小）** 排序，容易发现我们按这个顺序递归，最后的结果序列一定是以这个节点为根中最大的；

所以，我们可以一开始根据一个点的以他为根的各个儿子的大小进行排序（先比较大小为 $1$ 的儿子个数，再比较大小为 $2$……）；显然，只有一模一样且等于排序后第一名的点可能是答案，所以我们只考虑这些点；然后我们对于这些点求答案，最后比较一下他们得到的答案序列，就是最终答案。

我的实现的时间复杂度是 $O(n^2 - n^3)$，实现得好一点可能可以做到 $O(n\log n-n^2\log n)$

---

