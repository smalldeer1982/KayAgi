# 「GMOI R2-T3」粒子环游

## 题目背景

热爱珂学的小 Z 正在进行一项无聊的实验。

## 题目描述

实验室中有一个由 $n$ 个实验腔连接而成的环形轨道，其中第 $i$ 个实验腔顺时针连向第 $i+1$ 个实验腔（特别的，第 $n$ 个实验腔连向第 $1$ 个实验腔）。同时还有一个标号为 $n+1$ 的新建实验腔要接入这个环形轨道。它可以接在任意两个原本相连的实验腔之间。

第 $i$ 个实验腔可以将带电荷量为 $Q$ 的粒子运输到它的下一个实验腔，这个过程花费的能量为 $\vert Q \vert \times c_i$。除此之外，第 $i$ 个实验腔本身就存储了量为 $e_i$ 的电荷（电荷量有正负）。由于众所周知的电荷守恒定律，第 $n+1$ 个实验腔储存的电荷量与前 $n$ 个实验腔储存的总电荷量的代数和为 $0$。

小 Z 有一个原本不带电的粒子。等到第 $n+1$ 个实验腔接入轨道后，他要任选一个实验腔（包括第 $n+1$ 个）作为出发点，将粒子放入，并使之在实验腔的能量驱动下顺时针环游一周回到出发点。粒子每到达一个实验腔（包括出发点），它所带电荷量就会变成原来所带的电荷量和这个实验腔所储存的电荷量的代数和。

**注意：电荷量会先加上实验腔所含电荷量，再计算能量贡献。**

现在，小 Z 想知道，在所有接入新建实验腔并选定出发点的方案中，粒子环游一周所需的能量最少为多少？

## 说明/提示

样例 $1$ 解释：一种最优方案为将 $4$ 号实验腔接在 $3$ 号实验腔与 $1$ 号实验腔之间，以 $4$ 号实验腔为出发点，花费能量为 $ 1\times 2\ +\ 4\times 1\ + \vert -1 \vert \times 3 \ +\ 0 \times 2 =9$。

**本题采用 Subtask 捆绑测试。**

| Subtask | $n\le$ | $c_i\le$ | $\vert e_i\vert$ | 特殊性质 | 对应测试点 | 总分 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $300$ | $100$ | $100$ | $-$ | $1\sim 5$ | $10$ |
| $1$ | $10^3$ | $10^3$ | $10^3$ | $\bf A$ | $6\sim 7$ | $5$ |
| $2$ | $10^4$ | $10^4$ | $10^4$ | $-$ | $8\sim12$ | $15$ |
| $3$ | $10^5$ | $10^5$ | $10^5$ | $\bf B$ | $13\sim 16$ | $10$ |
| $4$ | $2.5\times 10^5$ | $10^5$ |$10^5$ | $-$ | $17\sim 25$ | $60$ |

特殊性质 $\bf A$：对于所有的 $i\in[1,n+1](i\in \Z)$，满足 $c_i=0$。

特殊性质 $\bf B$：对于所有的 $i\in[1,n+1](i\in \Z)$，满足 $c_i=1$。

对于 $100\%$ 的数据，$1\le n\le 2.5\times 10^5$，$0\le c_i\le 10^5$，$0\le |e_i|\le 10^5$。

保证答案在 long long 范围内。

## 样例 #1

### 输入

```
3
1 3 2 2
3 -5 1```

### 输出

```
9```

## 样例 #2

### 输入

```
12
4 7 7 8 8 4 5 5 9 10 1 1 10 
0 -5 7 8 1 -1 -6 8 2 4 10 8 ```

### 输出

```
509```

# 题解

## 作者：yinhy09 (赞：3)

## 官方题解

我们发现，到底把 $n+1$ 号实验腔插到哪里是一个很难解决的问题，所以我们暴力枚举插入位置。

然后我们可以将 $s$ 数组进行前缀和，因为 $\sum\limits_{i=1}^{n+1} s_i=0$，所以以 $i$ 为起点，走到 $j$ 位置时，粒子的含电荷量为 $s_j-s_{i-1}$。这一步相当于断环成链，但是不倍长。

当我们确定 $n+1$ 插入位置后，只需要找到起点。也就是找到一个整数 $i\in[1,n+1]$ ，使得 $\sum\limits_{j=1}^{n+1}|s_j-s_i|\times c_j$ 最小。因为最终也需要对所有起点进行枚举，所以可以将 $s_{i-1}$ 换成 $s_i$，效果等价。

看到绝对值，我们于是想到把 $s$ 丢到数轴上，本题就化简为了有 $n+1$ 个城市，第 $i$ 个在 $s_i$ 处，有 $c_i$ 个人，希望找一个城市建超市使得所有人到超市的距离总和最小。这就化为了我们熟悉的问题。

显然，超市应该建在最小的 $i$ 使得 $\sum\limits_{j=1}^i c_{pos_j}\ge \sum\limits_{j=i+1}^{n+1} c_{pos_j}$。$pos$ 数组为按照 $s$ 丢到数组上后的顺序。

当我们更改 $n+1$ 的位置时，相当于前缀和数组上单点修改。

我们显然可以二分在 $O(\log{n})$ 的复杂度内找到最优起点，只需要解决移位发生的动态问题。我们可以使用四个树状数组分别维护 $s$ 大于等于起点的 $\sum s\times c$，$\sum c$，$s$ 小于等于起点的 $\sum s\times c$，$\sum c$。利用这四个值和 $s_{start}$ 能计算出给定起点后的距离和。（相当于拆绝对值分类讨论）

离散化是必须的，我们可以将不超过 $2n$ 个可能出现的 $s$ 事先进行离散化。这样就解决了这一题。总体复杂度 $\mathcal O(n\log^2n)$。

PS.也可以使用线段树二分做到 $\mathcal O(n\log n)$。

---

## 作者：_Fatalis_ (赞：2)

**本题解偏向思路的渐进，不喜勿喷**

大前提有 $n$ 种情况，分别是 $n+1$ 加入到环中的 $n$ 种情况。

将环重新编号（$0\sim n$），已知 $c_i$，$e_i$。

设从 $i$ 号开始，计算 $s_{i - 1} = 0, s_j=s_{j - 1} + e_j$ 环状前缀和；

求
$$
\min_i\sum_{j = 0} ^ n c_j \times|s_j|
$$
就是说，$e$ 的前缀和与 $c$ 同位结合，前缀和开始的位置依次向后。

每一次迭代，$s_j \to s_j - s_{i - 1}, s_{i - 2} = s_{\text{all}}$。

也就是说，如果要~~暴力~~直接统计（无论用什么统计方法，由于是计算最大值，最终都需要计算 $n^2$ 种情况）的话，时间复杂度是 $O(n^2)$。

目标：$O(n) \sim O(n \log n)$。

---

## sub1

观察特殊数据，$i \in [1,n+1](i\in Z)$，满足 $c_i=0$。

由于是 $c_i = 0$，式子总为 $0$。答案为 $0$。

---

## sub3

观察特殊数据，$i \in [1,n+1](i\in Z)$，满足 $c_i=1$。

与特殊性质 $A$ 有所区别的，是后面 $c_i$ 的数值。

带入。

即
$$
\min_i\sum_{j = 1} ^ {n + 1} |s_j|
$$
题意变为插入一个下标为 $i$ 位置的 $(e,c)_{i + 1}$ 使得从某一位置开始统计的环形前缀和绝对值总和最小。

要求 $O(n)$ 或 $O(n\log n)$。

$i$ 的取舍并不合适。

可以改变一下前缀和的形式：$s_i' = s_{i - 1}' + e_i$，对应到当 $s_i$ 做开头时的环形前缀和，$s_j = s_j' - s_{i - 1}'$，**这里 $s'$ 表示以 $1$ 作为开头的前缀和**。

事实上，无论 $s'$ 表示从何处开始的前缀和，计算前缀和的方式都是 $s_j = s_j' - s_{i - 1}'$。

证明：当 $j > i$ 时，这条式子是原形式。当 $i > j$ 时，即跨边界进行了前缀和时，$(s_j'-s_{i-1}') \to (-\sum_{q = i} ^ j e_q)$；由于整个环加和为 $0$，那么这一段的相反数正好就是这一段跨边界的前缀和值。

那么就可以将 $s$ 数组适当联想。

由于 $i$ 并不好降低枚举复杂度，所以这一步直接枚举。（修改插入 $c_{n + 1}$ 的位置对前缀和的影响为单点修改，不会影响整体复杂度）

有了上面的提示，那么可以转换为：
$$
\min_i \sum_{j = 1} ^ {n + 1} |s_j' - s_{i - 1}'|
$$
单独抽出来，
$$
\sum_{j = 1} ^ {n + 1} |s_j' - s_i'|\ \ (\text{为方便讨论将}\ (i - 1) \to i)
$$
这条式子不就是所有点到 $i - 1$ 的距离之和吗？

于是把数组 $s$ 抽象到坐标轴上，那么问题转化为在一个点集中选择一个点让使所有点到该点的距离之和**最小**。于是问题就转换为我们熟悉的问题。

结论是：理想到数轴上的中间的位置，即位置 $i$ 满足在中间的位置。

如果是偶数个点，那么左右两边的点都是欧克的。

理由，任意向中间移动距离 $x$，并当前的位置为 $i$，都会增加少 $(i - 1)x$ 的总贡献，且减少 $(n - i + 1)x$，那么相减就是 $(2i-2-n)x$。当 $i = n / 2 + 1$ 即 $2(i - 1) =n $ 时，（就是说有偶数个点并在中心左边）原式 $=0$。即当 由中心偏左位置 向 中心偏右位置 移动时，移动贡献为 $0$。

利用这个线性的性质，可以 $O(1)$ 计算出最优的**开始位置** $b$。

解决开始问题后，就剩下统计最终的答案。

那么如何 $O(\log n) \text{ or } O(1)$ 求
$$
\sum_{j = 1} ^ {n + 1} |s_b' - s_j'|
$$
其中 $b$ 为选定的开始，并且在 $s'$ 有单点修改（插入的位置）的情况呢？（此处为本题难点）

对 $s'$ 排序，得到 $t$。拆开这条式子，可以得到
$$
\sum_{j = 1} ^ {b'} (s_b' - s_j') \cdot c_j + \sum_{j = b' + 1} ^ {n + 1}(s_j' - s_b')\cdot c_j
$$
所以最后答案是
$$
\sum_{j = b' + 1} ^ {n + 1}s_j'\cdot c_j -\sum_{j = 1} ^ {b'} s_j' \cdot c_j + s_b'\cdot \left(\sum_{j = 1} ^ {b'} c_j- \sum_{j = b' + 1} ^ {n + 1}c_j\right)
$$
于是我们发现需要维护的是区间的 $\sum s_j'\cdot c_j$ 和 $\sum c_j$。

考虑到每次改变某一个前缀和位置的时候要求 $\log n$ 做，修改的内容是什么？

修改的就是 $s_j'$，和对应 $c_j$ 的位置。（由于是有序的，所以得保证 $s_j'$ 和 $c_j$ 位置是对应的，否则统计不了）

如果每一次修改 $s_j'$ 都移动整个数列来让整个线段树变得有序，那么就不是 $O(\log n)$ 的了。

可以考虑用空间换时间，由于每次修改的内容是确定的，并且每一个位置对应的修改的最终值是确定唯一的，那么可以想到开到两倍的线段树，初始将所有的 $s_j'$ 和 $s_j' - (e_j + e_{n + 1})$（这里的式子原因在后面）都预加入，一起排序，得到的预排序结果就包含了增加修改的部分。

解决了有序的问题之后，考虑解决前缀和改变后，整个前缀和数组的改变。

这是样例前缀和数组改变的规律：

```
3 -5 1 1  3 -2 -1 0
          1 3  2  2
3 -5 1 1  3 -2 -1 0
          1 3  2  2
3 1 -5 1  3 4 -1 0
          1 2 3  2
1 3 -5 1  1 4 -1 0
          2 1 3  2
```

可以通过观察数据得到以下规律，

由于一开始 $e_{n + 1}$ 已经预加入到 $s'$ 中，那么设当前移动后来到了 $i$ 的位置，那么就要修改 $s_i \to s_i - (e_i + e_{n + 1})$。

维护的方法，每次移动的时候，先删除当前的 $s'$，再加入 $s_i - (e_i + e_{n + 1})$ 就好聊。别忘了移动 $c_i$。

---

解决了性质 B，其实在性质 B 之后可以直接做正解了。只是需要多维护个 $c$ 就可以了。每次只需要移动一次 $c_{i}$ 和 $c_{i + 1}$，同时维护一下两个 $\Sigma$ 就口以了。

在前文中已经暗示了含 $c_i$ 的做法，所以不多讲解；我的 Code：

```cpp
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

template<typename T>
void read(T &r) { r = 0; static char ch, last; ch = getchar(), last = 'z'; while (ch < '0' || ch > '9') last = ch, ch = getchar(); while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar(); r = (last == '-') ? -r : r; }
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { read(arg); read(arg_left...); }

template<typename T>
void write(T x) { if (x < 0) putchar('-'), x = -x; int len = 0; static char ch[100]; while (x) ch[++len] = x % 10 + '0', x /= 10; if (!len) ch[++len] = '0'; while (len) putchar(ch[len--]); }
template<typename T, typename...Ts>
void write(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); }
template<typename T>
void writeln(T x) { write(x); putchar('\n'); }
template<typename T, typename...Ts>
void writeln(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); putchar('\n'); }

#define int long long
const int maxn = (int)(2e5 + 100) << 2;
const int inf = 0x3f3f3f3f3f3f3f3fll;
int n;
int c[maxn], e[maxn];
int s[maxn], t[maxn], tot = 0;

struct Tree {
    struct Node {
        int l, r, lc, rc;
        int c, x; // x mean s * c
    } nds[maxn << 2];

    int cnt = 0;
    int init(int l, int r) {
        int id = ++cnt;
        nds[id] = {l, r, -1, -1, 0, 0};
        if (l == r) return id;
        int mid = (l + r) >> 1;
        nds[id].lc = init(l, mid);
        nds[id].rc = init(mid + 1, r);
        return id;
    }

    void add(int u, int pt, int s, int c, int pos) {
        nds[u].c += c * pos; nds[u].x += c * s * pos;
        if (nds[u].l == nds[u].r) return;
        int mid = (nds[u].l + nds[u].r) >> 1;
        if (pt <= mid) add(nds[u].lc, pt, s, c, pos);
        else add(nds[u].rc, pt, s, c, pos);
    }

    int queryc(int u, int l, int r) {
        if (u == -1) return 0;
        if (l == nds[u].l && nds[u].r == r) return nds[u].c;
        int mid = (nds[u].l + nds[u].r) >> 1;
        if (r <= mid) return queryc(nds[u].lc, l, r);
        else if (l > mid) return queryc(nds[u].rc, l, r);
        else return queryc(nds[u].lc, l, mid) + queryc(nds[u].rc, mid + 1, r);
    }
    int queryx(int u, int l, int r) {
        if (u == -1) return 0;
        if (l == nds[u].l && nds[u].r == r) return nds[u].x;
        int mid = (nds[u].l + nds[u].r) >> 1;
        if (r <= mid) return queryx(nds[u].lc, l, r);
        else if (l > mid) return queryx(nds[u].rc, l, r);
        else return queryx(nds[u].lc, l, mid) + queryx(nds[u].rc, mid + 1, r);
    }

    int find() {
        int u = 1, c = 0, cpos = nds[1].c / 2;
        while (nds[u].l != nds[u].r) {
            if (c + nds[nds[u].lc].c <= cpos) {
                c += nds[nds[u].lc].c;
                u = nds[u].rc;
            } else {
                u = nds[u].lc;
            }
        }
        return nds[u].l;
    }

    int query() {
        int b = find(), qs;
        int lc = queryc(1, 1, b), rc = queryc(1, b + 1, tot);
        int lx = queryx(1, 1, b), rx = queryx(1, b + 1, tot);
        if (lc - rc != 0) qs = queryx(1, b, b) / queryc(1, b, b);
        else qs = 0;
        return (lc - rc) * qs - (lx - rx);
    }
} tr;



signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    read(n);
    for (int i = 1; i <= n + 1; ++i) read(c[i]);
    for (int i = 1; i <= n; ++i) read(e[i]), t[++tot] = s[i] = s[i - 1] + e[i];
    e[n + 1] = -s[n]; t[++tot] = s[n + 1] = s[n] + e[n + 1];
    for (int i = 1; i <= n; i++) {
        t[++tot] = s[i] - (e[i] - e[n + 1]);
    }
    std::sort(t + 1, t + tot + 1);

    tr.init(1, tot);
    for (int i = 1; i <= n + 1; i++) { // 为什么是 n + 1
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, s[i], c[i], 1);
    }
    int ans = inf;
    for (int i = n; i >= 1; i--) {
        ans = std::min(ans, tr.query());
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, s[i], c[i], -1);
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i + 1]) - t, s[i + 1], c[i + 1], -1); // 为什么要更新这里？
        // writeln(std::lower_bound(t + 1, t + tot + 1, s[i]) - t, tr.queryc(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, std::lower_bound(t + 1, t + tot + 1, s[i]) - t));
        s[i] -= (e[i] - e[n + 1]); std::swap(c[i], c[i + 1]);
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i]) - t, s[i], c[i], 1);
        tr.add(1, std::lower_bound(t + 1, t + tot + 1, s[i + 1]) - t, s[i + 1], c[i + 1], 1);
    }
    writeln(ans);
    return 0;
}

```


---

## 作者：Aiopr_2378 (赞：1)

Solution of P9200 「GMOI R2-T3」粒子环游

## 解题思路

难得质量不错的题！在 @JLGxy 神仙的帮助下想出了这道题的 key observation！

因为第 $n+1$ 个点插入的位置和开始位置两个变量都在变化，考虑固定枚举一个，另一个使用数据结构优化。

发现固定开始节点，$n+1$ 节点上变化的信息很多，所以考虑：固定枚举 $n+1$ 号节点，尝试使用数学推导或数据结构求得最优的开始位置。

下面是一些约定。

令 $sum_i$ 表示从起点走到节点 $i$ 一路上的电荷量代数和，即 $\sum\limits_{j=s}^i e_i$。不难发现，最后求得的答案就是：

$$
\sum\limits_{i=1}^{n+1} |sum_i|\times c_i
$$

令 $s_i$ 表示从**节点 $1$** 开始，一路走到 $i$ 的电荷量代数和。特别地，因为题目保证 $\sum e_i=0$，设起点为 $p$ 节点，当 $i\le p$ 时，$s_i$ 表示为从点 $i$ 走到 $p$ 的电荷量代数和的相反数。显然这样定义之后**数值上等价**。事实上，这里的正负是无关紧要的，详见下面解释。

我们可以将答案转化为：

$$
\sum\limits_{i=1}^{n+1} |s_i-s_p|\times c_i
$$

发现式子中的绝对值符号很难代数处理，考虑进行转换为**几何意义**。

不难发现，上述式子的几何意义就是：在数轴上，有 $n+1$ 个点，每个点有点权 $c_i$。我们要选择一个点为中心点，使得**所有点到这个中心点的加权距离和最小**。进而，我们可以将点权转化成 $c_i$ 个重复的点，使得每个点的点权都为 $1$，这样，就可以以 $\sum c_i$ 个点的代价换取考虑点权的代价。

通过上述方法消去点权，问题就变成了：在数轴上，有 $\sum c_i$ 个点，我们要选择一个中心点，使得**所有点到这个点的距离和最小**。发现这是一个初中数学问题，中心点的最优选取已经是**选位于中心的点**，即大小排序后第 $\lceil\dfrac{\sum c_i}{2}\rceil$ 个点。

考虑每次枚举 $n+1$ 点位置，我们都可以求出上面这个代数和。我们把比“中心点大的点”（称为“大点”）和“比中心点小的点”（称为“小点”）分开考虑。具体地，在考虑大点时，我们设 $sz$ 为大于中心点的点数， $idsum$ 为他们到中心点距离之和，$sum$ 表示他们在数轴上表示的数的和，$mid$ 为中心点在数轴上代表的数，这些大点的贡献为：

$$
idsum=sum-sz\times mid
$$

比中心点小的点同理统计，有

$$
idsum=sz\times mid-sum
$$

我们使用线段树维护每个位置上的点个数 $sz$ 和这些点各自下标（几何意义：数轴上表示的点）的和 $sum$。具体地，我们开值域线段树（值域后面有说明，动态开点），每个区间 $[l,r]$ 表示在数轴上区间 $[l,r]$ 内的点的信息。

我们可以先在线段树上找到大小正好在正中间的点，之后执行询问操作即可。

注意 $\sum c_i$ 的值域是 $[-2.5\times 10^{10},2.5\times 10^{10}]$，需使用动态开点线段树。

现在考虑在更改 $n+1$ 点位置时，线段树和 $s$ 数组怎样变化。当我们把 $i$ 位置上的 $n+1$ 号点和在 $i-1$ 位置上的点互换位置时，不难发现，变化的只有 $s_{i-1},s_i$ 两个数据。具体地，令 $s'$ 表示变动后的 $s$ 数组，$e'$ 表示变动后的 $e$ 数组，有

$$
\begin{cases}
s_{i-1}=s_{i-2}+e_{i-1}\\
s_i=s_{i-1}+e_i\\
s'_{i-1}=s_{i-2}+e'_{i-1}\\
s'_i=s'_{i-1}+e'_i
\end{cases}
$$

直接更改一下，记得在改之前先把线段树上的值减去，之后再加上改的值就好啦~

这样，枚举 $n+1$ 号点的位置复杂度为 $O(n)$，线段树维护信息复杂度为 $O(\log \omega)$，其中 $\omega=5\times 10^{10}$ 为值域，总时间复杂度为 $O(n\log\omega)$，空间复杂度为 $O(n\log \omega)$，带多倍常数。开 -O2 优化大约需要 850ms。

呜呜呜。可能并没有讲得很明白，可以参考一下代码和注释喵！

## 参考代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define MAXN 250005
#define Max 25000000000
#define ls tree[p].lson
#define rs tree[p].rson
typedef long long ll;
typedef pair<ll,ll> pll;
int n,root;
ll c[MAXN],e[MAXN],s[MAXN],sumc,ans=__INT64_MAX__;
pll operator+(pll x,pll y){
    return {x.first+y.first,x.second+y.second};
}
namespace sgt{
    struct node{
        int lson,rson;
        ll sz,sum;
    }tree[MAXN*50];//空间记得开大，动态开点
    int tot=0;
    void update(int p){//上传信息
        tree[p].sz=tree[p].sum=0;
        if(ls){
            tree[p].sz+=tree[ls].sz;
            tree[p].sum+=tree[ls].sum;
        }
        if(rs){
            tree[p].sz+=tree[rs].sz;
            tree[p].sum+=tree[rs].sum;
        }
    }
    void modify(int &p,ll l,ll r,ll goal,ll k){//修改操作，在 goal 位置加上 k 个点
        if(!p) p=++tot;
        if(l==r){
            tree[p].sz+=k;
            tree[p].sum+=1ll*k*l;
            return;
        }
        ll mid=(l+r)>>1;
        if(goal<=mid) modify(ls,l,mid,goal,k);
        else modify(rs,mid+1,r,goal,k);
        update(p);
    }
    pll query(int p,ll l,ll r,ll ql,ll qr){//询问操作，pair 中第一项为 sz，第二项为 sum
        if(!p) return {0,0};
        if(ql<=l&&qr>=r) return {tree[p].sz,tree[p].sum};
        ll mid=(l+r)>>1;
        pll ans={0,0};
        if(ql<=mid) ans=ans+query(ls,l,mid,ql,qr);
        if(qr>mid) ans=ans+query(rs,mid+1,r,ql,qr);
        return ans;
    }
    ll findmid(int p,ll l,ll r,ll k){//找第 k 小
        if(!p) return 0;
        if(l==r) return l;
        ll mid=(l+r)>>1;
        if(tree[ls].sz>=k) return findmid(ls,l,mid,k);
        return findmid(rs,mid+1,r,k-tree[ls].sz);
    }
}
inline int read(){
    int w=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        w=w*10+ch-'0';
        ch=getchar();
    }
    return w*f;
}
int main(){
    n=read();
    for(int i=1;i<=n+1;i++){
        c[i]=read();
        sumc+=c[i];
    }
    for(int i=1;i<=n;i++){
        e[i]=read();
        e[n+1]-=e[i];
    }
    for(int i=1;i<=n+1;i++) s[i]=s[i-1]+e[i];//计算 s 数组
    for(int i=1;i<=n+1;i++){
        sgt::modify(root,-Max,Max,s[i],c[i]);//预处理，先把信息放进去
    }
    for(int i=n+1;i;i--){
        ll l=sgt::findmid(root,-Max,Max,(sumc+1)/2);//找到中心点所表示的数
        pll ar=sgt::query(root,-Max,Max,l+1,Max);//找到在中心点左侧的信息
        pll al=sgt::query(root,-Max,Max,-Max,l-1);//右侧
        ll cnt=ar.second-ar.first*l+al.first*l-al.second;//计算当前位置的答案
        ans=min(ans,cnt);//答案取最小值
        if(i>1){//更改 n+1 号点的位置
            sgt::modify(root,-Max,Max,s[i],-c[i]);//先撤销原信息
            sgt::modify(root,-Max,Max,s[i-1],-c[i-1]);
            swap(e[i],e[i-1]);//交换和更改信息
            swap(c[i],c[i-1]);
            s[i-1]=s[i-2]+e[i-1];
            s[i]=s[i-1]+e[i];
            sgt::modify(root,-Max,Max,s[i],c[i]);//加上更改后的信息
            sgt::modify(root,-Max,Max,s[i-1],c[i-1]);
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：sqrtqwq (赞：0)

考虑暴力枚举 $n + 1$ 在哪一个位置后面，然后每一次考虑维护答案。

此时我们记 $sum_i = \sum^i_{j = 1} e_j$。那么对于从一个起点 $i$ 移动到终点 $j$ 的电荷量就是 $sum_j - sum_{i - 1}$。

那么我们要求的答案就是 $\sum^{n + 1}_{j = 1} |sum_j - sum_{i - 1}| \times c_j$。其中 $i$ 为粒子环游的开始节点。由于 $sum_{n + 1} = sum_{0} = 0$，所以这个式子就等价于 $\sum^{n + 1}_{j = 1} |sum_j - sum_i| \times c_j$。那么现在我们考虑这个式子在什么时候取到最最小值。

但是我们发现直接处理绝对值是一件很难的事情，所以我们考虑用几何意义吧绝对值拆开来。那么上面那个式子的几何意义就是在数轴上有 $n + 1$ 个点，点有点权，现在需要选取一个点，使得所有点到这个中心点的加权距离和最小。但是我们发现带权也不好做，所以考虑把一个点拆成 $c_i$ 个点，那么总点数就变为了 $\sum c_i$，并且不带权。

那么我们只需要选出来这 $\sum c_i$ 个点的中心点就行了。即点按照坐标大小排序后的第 $\lceil \dfrac{\sum c_i}{2} \rceil$ 个数，然后这个东西用权值线段树维护即可。

---

## 作者：nullqtr_pwp (赞：0)

主动弱化限制条件。直接上手做不了一点。

考虑确定下来 $n+1$ 插入到哪里怎么做，显然有 $n$ 种选择（插入到 $i=1,2,\cdots,n$ 的后面）

记录此时的长度为 $n+1$ 的数列 $e_i$ 的前缀和为 $pre_i$。

对于一个起点 $i$，移动到 $j$ 的电荷量，考虑断环成链，将数列 $e_i$ 复制一份到后面，如果有 $i\le j$，那么有到达 $j$ 的电荷量为 $pre_j-pre_{i-1}$，意义是求出区间和。否则，对于 $i>j$ 的情况，有到达 $j$ 的电荷量为 $pre_{j+n+1}-pre_{i-1}$，也就是环上的区间和。

注意到 $\sum e_i=0$，即 $pre_{n+1}$ 恒等于 $0$，显然有 $pre_{j+n+1}=pre_{j}$，那么到达 $j$ 的电荷量就等于 $pre_{j}-pre_{i-1}$，与 $i\leq j$ 没有任何区别，因此可以不考虑位置关系。

考虑记 $f(x,i)=\sum_{j=1}^{n+1}|pre_j-pre_{i-1}|\times c_j$。$x$ 是枚举 $n+1$ 的插入的位置是 $(x,x+1)$ 之间（对于 $x=n$ 是 $(n,1)$ 之间），$i$ 是枚举粒子环游的起点，有 $1\leq x\leq n,1\leq i\leq n+1$。$x$ 是我们最开始就在枚举的东西，考虑从 $i$ 入手做。

因为 $pre_{n+1}=pre_0=0$，所以，对全体的 $i\in [0,n]$ 扫一遍取 $\min$ 就等价于对 $i\in[1,n+1]$ 扫一遍。式子可以改写为 $f(x,i)=\sum_{j=1}^{n+1}|pre_j-pre_i|\times c_i$。

考虑 $i$ 取在什么时可以取到 $\min$。这显然是一个带权中位数的形式。就是考虑，有一个 $\sum c_i$ 个数的序列，对于每个 $j$，在这个序列中有 $c_j$ 个 $pre_j$。对这个排序之后，中位数的值就是我们想要的 $i$。证明的话，调整法或者交换法随便证下就好了。

注意到这个形式不要求对 $(pre_i,c_i)$ 具体的下标做出要求，考虑以 $pre_i$ 为值域的下标进行维护。

注意到 $\sum c_i$ 是定值，那么找出来的中位数 $x$ 就是满足，下标 $\leq x$（也就是所有 $pre_j\leq x$ 的 $j$），对于 $c_i$ 前缀和第一个 $\ge \lceil \dfrac{\sum_{i=1}^{n+1} c_i}{2}\rceil$ 的 $x$。因为前缀和会变，考虑用权值线段树维护，下标为 $pre_{i}$，存的值为 $c_i$，直接在线段树二分就可以处理。

现在考虑移动 $n+1$ 插入的位置。
考虑操作的序列，现在 $n+1$ 在整个序列第 $i$ 个，移动到第 $i-1$ 个。

注意到每次只会影响前一个位置的前缀和值，直接模拟即可。具体的，考虑初始状态是放在 $n$ 之后，也就是 
$\lbrace1,2,\cdots,n,n+1\rbrace$，然后把 $n+1$ 逐个往前移动。

每次移动形如将： 

$\lbrace1,2,\cdots,i-2,i-1,n+1,i,i+1,\cdots,n\rbrace$

更改为：

$\lbrace1,2,\cdots,i-2,n+1,i-1,i,i+1,\cdots,n\rbrace$

直接对这两个位置进行修改即可。

因为直接在数据结构上二分，所以时间复杂度 $O(n\log n)$。都放双 $\log$ 过去了，为什么不开大空间到 $512\text{ MB}$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define pb push_back
#define fi first
#define se second
#define inf 1e9
#define pii pair<int,int>
#define F(i,a,b) for(int i=a;i<=(b);i++)
#define dF(i,a,b) for(int i=a;i>=(b);i--)
#define wh(lzm) while(lzm--)
#define lowbit(x) (x&(-x))
#define HH printf("\n")
#define eb emplace_back
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
const int maxn=500005;
int n,a[maxn],b[maxn];
ll pre[maxn],ans=1e18;
const int D=2.5e9;
void chkmin(ll &x,ll y){ x=min(x,y); }
void chkmax(ll &x,ll y){ x=max(x,y); }
namespace seg{
	ll t[maxn<<5],sz[maxn<<5];
	signed ls[maxn<<5],rs[maxn<<5],cnt,R=0;
	void update(signed &o,int l,int r,int pos,int val){
		if(!o) o=++cnt;
		sz[o]+=val,t[o]+=1ll*pos*val;
		if(l==r) return;
		int mid=(l+r)>>1;
		(pos<=mid)?update(ls[o],l,mid,pos,val):update(rs[o],mid+1,r,pos,val);
	}
	int query(signed o,int l,int r,int ql,int qr){
		if(!o) return 0;
		if(ql<=l&&qr>=r)return sz[o];
		int mid=(l+r)>>1,rt=0;
		if(ql<=mid) rt=query(ls[o],l,mid,ql,qr);
		if(qr>mid) rt+=query(rs[o],mid+1,r,ql,qr);
		return rt;
	}
	int Query(signed o,int l,int r,int ql,int qr){
		if(!o) return 0;
		if(ql<=l&&qr>=r)return t[o];
		int mid=(l+r)>>1,rt=0;
		if(ql<=mid) rt=Query(ls[o],l,mid,ql,qr);
		if(qr>mid) rt+=Query(rs[o],mid+1,r,ql,qr);
		return rt;
	}
	int find(signed o,int l,int r,int k){
		if(!o) return 0;
		if(l==r) return l;
		int mid=(l+r)>>1;
		return (sz[ls[o]]>=k)?find(ls[o],l,mid,k):find(rs[o],mid+1,r,k-sz[ls[o]]);
	}
}
using namespace seg;
signed main(){
	n=read();
	int sum=0;
	F(i,1,n+1) a[i]=read(),sum+=a[i];
	sum=(sum+1)>>1;
	F(i,1,n) b[i]=read(),pre[i]=pre[i-1]+b[i];
	b[n+1]=-pre[n];
	F(i,1,n+1) update(R,-D,D,pre[i],a[i]);
	dF(i,n+1,1){
		int pos=find(R,-D,D,sum);
		int lcnt=query(R,-D,D,-D,pos-1),rcnt=query(R,-D,D,pos+1,D);
		int lsum=Query(R,-D,D,-D,pos-1),rsum=Query(R,-D,D,pos+1,D);
		chkmin(ans,rsum-lsum-rcnt*pos+lcnt*pos);
		if(i==1) break;
		update(R,-D,D,pre[i],a[i-1]-a[n+1]);
		update(R,-D,D,pre[i-1],-a[i-1]);
		pre[i-1]+=b[n+1]-b[i-1];
		update(R,-D,D,pre[i-1],a[n+1]);
	}
	cout<<ans;
}
```

---

## 作者：MuelsyseU (赞：0)

我先考虑枚举插入在哪里，因为看起来这个要推结论过于复杂。

那考虑再枚举起点，尝试去维护答案。随便取个起点维护前缀和，显然起点移动一位，相当于全局加上 / 减去一个数，然后交换一下相邻的 $c$，然后求绝对值乘上 $c_i$ 的和。随便上个数据结构加上懒标记差不多就可以了。

考虑正解，注意到一圈的和为 $0$，所以无论在起点 $p$ 之前还是之后的位置 $i$，其电荷量都可以表示为 $s_i-s_{p-1}$。

然后先前那部分有点像加权中位数啊，是不是做完了。

就是先求 $c$ 之和，然后考虑第一个达到 $\dfrac{c}{2}$ 的数，随便线段树二分维护。

```cpp
#include <bits/stdc++.h>
#define mid (l + r) / 2
using namespace std;

const int maxn = 300005;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int n, num, rt;
ll ans = inf, b[maxn], c[maxn], e[maxn], s[maxn];
struct Seg {
	int l, r;
	ll x, c, s;
} t[maxn * 8];
int tot;
Seg merge(Seg p, Seg q) {
	return {0, 0, p.x + q.x, p.c + q.c, p.s + q.s};
}
void insert(int &p, int l, int r, int i, int x, ll c) {
	// s = b[i]
	if (!p) p = ++tot;
	t[p].x += x, t[p].c += c * x, t[p].s += c * b[i] * x;
	if (l == r) return;
	if (i <= mid) insert(t[p].l, l, mid, i, x, c);
	else insert(t[p].r, mid + 1, r, i, x, c);
}
// 大于 k 的第一个数
int find(int p, int l, int r, ll x) {
	if (l == r) return l;
	if (t[t[p].l].c > x) return find(t[p].l, l, mid, x);
	return find(t[p].r, mid + 1, r, x - t[t[p].l].c);
}
// 然后查询一个区间和。
Seg query(int p, int l, int r, int ql, int qr) {
//	cout << l << " " << r << " " << ql << " " <<qr << endl;
	if (r < ql || l > qr) return {0, 0, 0, 0};
	if (ql <= l && r <= qr) return t[p];
	return merge(query(t[p].l, l, mid, ql, qr), query(t[p].r, mid + 1, r, ql, qr));
}
ll get(int x) {
	if (x == -1) return inf;
	Seg tl = query(rt, 1, num, 1, x), tr = query(rt, 1, num, x + 1, num);
	return tl.c * b[x] - tl.s + tr.s - tr.c * b[x];
}
signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n + 1; ++i) scanf("%lld", c + i);
	for (int i = 1; i <= n; ++i) scanf("%lld", e + i), b[++num] = s[i] = s[i - 1] + e[i];
	e[n + 1] = -s[n];
	for (int i = n + 1; i >= 1; --i) b[++num] = s[i] + e[n + 1];
	sort(b + 1, b + 1 + num);
	num = unique(b + 1, b + 1 + num) - b - 1;
	for (int i = 1; i <= n + 1; ++i)
		insert(rt, 1, num, lower_bound(b + 1, b + 1 + num, s[i]) - b, 1, c[i]);
	for (int i = n; i >= 1; --i) {
		ans = min(ans, get(find(rt, 1, num, t[rt].c / 2)));
		insert(rt, 1, num, lower_bound(b + 1, b + 1 + num, s[i]) - b, -1, c[i]);
		insert(rt, 1, num, lower_bound(b + 1, b + 1 + num, s[i + 1]) - b, -1, c[i + 1]);
		s[i] = s[i - 1] + e[n + 1], swap(c[i], c[i + 1]);
		insert(rt, 1, num, lower_bound(b + 1, b + 1 + num, s[i]) - b, 1, c[i]);
		insert(rt, 1, num, lower_bound(b + 1, b + 1 + num, s[i + 1]) - b, 1, c[i + 1]);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

