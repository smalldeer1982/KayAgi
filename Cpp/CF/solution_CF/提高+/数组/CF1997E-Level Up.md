# Level Up

## 题目描述

Monocarp正在玩一款电脑游戏。他从等级 $ 1 $ 开始。他将依次与 $ n $ 只怪物战斗，这些怪物的等级从 $ 1 $ 到 $ n $ 不等。

对于按顺序给出的每个怪物，Monocarp的遭遇如下：

- 如果Monocarp的等级高于怪物的等级，则怪物会逃跑；
- 否则，Monocarp会与怪物战斗。

在每与第 $ k $ 个怪物战斗（逃跑的怪物不计算在内）后，Monocarp的等级会增加 $ 1 $ 。因此，他在与 $ k $ 个怪物战斗后等级变为 $ 2 $ ，在与 $ 2k $ 个怪物战斗后等级变为 $ 3 $ ，以此类推。

你需要处理 $ q $ 个查询，每个查询的格式如下：

- $ i~x $ ：如果参数 $ k $ 等于 $ x $ ，Monocarp是否会与第 $ i $ 个怪物战斗？

## 样例 #1

### 输入

```
4 16
2 1 2 1
1 1
2 1
3 1
4 1
1 2
2 2
3 2
4 2
1 3
2 3
3 3
4 3
1 4
2 4
3 4
4 4```

### 输出

```
YES
NO
YES
NO
YES
YES
YES
NO
YES
YES
YES
NO
YES
YES
YES
YES```

## 样例 #2

### 输入

```
7 15
1 1 2 1 1 1 1
5 3
2 2
2 2
1 6
5 1
5 5
7 7
3 5
7 4
4 3
2 5
1 2
5 6
4 1
6 1```

### 输出

```
NO
YES
YES
YES
NO
YES
YES
YES
NO
NO
YES
YES
YES
NO
NO```

# 题解

## 作者：Redshift_Shine (赞：51)

## 闲话

大家好，我非常不喜欢暴力数据结构，所以我用树状数组和二分搜索过了这道题。

## 思路

首先，显然 $k$ 越小越容易升级，也就是说 $k$ 越小，逃跑的怪兽就越多。那么对于每一个位置 $i$，我们可以求出一个阈值 $c_i$，保证只要 $k$ 不小于 $c_i$，那么这个怪兽就一定不会逃跑。

## 解法

二分搜索。

使得等级为 $a_i$ 的怪兽 $i$ 在参数 $k$ 下逃跑的充要条件是在 $i$ 之前 Monocarp 的等级超越了 $a_i$，也就是说在 $i$ 之前已经打了至少 $a_ik$ 个怪兽。快速查询一个位置在不同的 $k$ 下有多少个怪物被打可以使用树状数组。

时间复杂度 $O(n\log n\log \max(a)+q)$。

## 代码

```c++
#include <iostream>
#include <tuple>
using namespace std;
const int N = 2e5 + 10;
int a[N], n, q, tr[N], idx = 1, l, r, mid, req[N];
inline void update(int x, int v)
{
    while (x < N)
    {
        tr[x] += v;
        x += (x & -x);
    }
}
inline int query(int x)
{
    int res = 0;
    while (x)
        res += tr[x], x -= (x & -x);
    return res;
}
inline bool check(int x, int v) // xth monster will fl, x=v
{
    return 1ll * a[x] * v <= query(v);
}
int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
    }
    for (int i = 1; i <= n; i++)
    {
        l = 1, r = n;
        while (l < r)
        {
            mid = (l + r) >> 1;
            if (check(i, mid))
                l = mid + 1;
            else
                r = mid;
        }
        update(l, 1);
        req[i] = l;
    }
    for (int i = 1, x, k; i <= q; i++)
    {
        scanf("%d%d", &x, &k);
        puts(k < req[x] ? "NO" : "YES");
    }
}
```

讲个笑话，赛时我把查询排序了导致多用了几十毫秒，虽然还是快的一批。大概四百多毫秒。

但，你不会认为已经结束了吧？

## 优化

### 优化 $1$ - 树状数组内部操作

众所周知，`query` 函数是这么写的：

```c++
inline int query(int x)
{
    int res = 0;
    while (x)
        res += tr[x], x -= (x & -x);
    return res;
}
```

换句话说，`query` 函数干的事就是一个一个削掉 $x$ 的 `lowbit`，顺便加上对应位置上的 $\text{tr}_x$。

也就是说，如果我们给 $x$ 加上一个小于它 `lowbit` 的数 $y$，那么 $\text{query}(x+y)=\text{query}(x)+\text{tr}_{x+y}$。

利用这个性质，我们可以从上向下枚举 $c_i$ 的每个二进制位，若怪兽会应战，就忽略；否则，加上这个二进制位。

```c++
for (int i = 1; i <= n; i++)
{
    l = cur = 0;
    for (int j = 17; ~j; j--)
    {
        if (1ll * a[i] * (l | (1 << j)) <= cur + tr[l | (1 << j)])
            l |= (1 << j), cur += tr[l];
    }
    l++;
    update(l, 1);
    req[i] = l;
}
```

时间复杂度 $O(n\log \max(a))$。

### 优化 $2$ - 输入优化

`scanf` 比 `getchar` 慢是一个老生常谈的道理。

```c++
template <typename _Tp>
inline void read(_Tp &x)
{
    char ch;
    while (ch = getchar(), !isdigit(ch))
        ;
    x = ch - '0';
    while (ch = getchar(), isdigit(ch))
        x = (x << 3) + (x << 1) + (ch ^ '0');
}
template <typename _Tp, typename... _Args>
inline void read(_Tp &x, _Args &...args)
{
    read(x);
    read(args...);
}
```

支持可变参数调用，代码是从之前一次洛谷月赛那里学的，但是忘了是哪一场。

最终时间复杂度 $O(n\log \max(a)+q)$。

### 优化代码

最终运行时间 $187$ 毫秒。评测记录在[这里](https://codeforces.com/contest/1997/submission/273897743)。

```c++
#include <iostream>
#include <tuple>
using namespace std;
const int N = 4e5 + 10;
int a[N], n, q, tr[N], idx = 1, l, r, mid, req[N], cur;
template <typename _Tp>
inline void read(_Tp &x)
{
    char ch;
    while (ch = getchar(), !isdigit(ch))
        ;
    x = ch - '0';
    while (ch = getchar(), isdigit(ch))
        x = (x << 3) + (x << 1) + (ch ^ '0');
}
template <typename _Tp, typename... _Args>
inline void read(_Tp &x, _Args &...args)
{
    read(x);
    read(args...);
}
inline void update(int x, int v)
{
    while (x < N)
    {
        tr[x] += v;
        x += (x & -x);
    }
}
int main()
{
    read(n, q);
    for (int i = 1; i <= n; i++)
    {
        read(a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        l = cur = 0;
        for (int j = 17; ~j; j--)
        {
            if (1ll * a[i] * (l | (1 << j)) <= cur + tr[l | (1 << j)])
                l |= (1 << j), cur += tr[l];
        }
        l++;
        update(l, 1);
        req[i] = l;
    }
    for (int i = 1, x, k; i <= q; i++)
    {
        read(x, k);
        puts(k < req[x] ? "NO" : "YES");
    }
}
```

---

## 作者：Register_int (赞：39)

大家好，我非常喜欢暴力数据结构，所以我用根号分块和根号分治过了这道题。

根分，设阈值为 $B$。当 $k\le B$ 时，我们可以暴力预处理出所有答案。时间复杂度 $O(nB)$。

当 $k>B$ 时，最后升到的级别一定不会超过 $\frac nk+1=O(\frac nB)$。考虑暴力跳，每次对于起点 $i$ 二分找出第一个 $j$，使得 $[i,j]$ 内大于等于级别 $x$ 的个数恰好为 $k$。这部分 $O(\log n)$ 已经很极限了，所以我们需要 $O(1)$ 找区间内大于等于一个数的数的个数。

等级 $\le \frac nk+1$，所以把 $>\frac nk+1$ 的数当成 $\frac nk+1$ 计算贡献即可，值域在 $\frac nB$ 以内。所以你可以直接前缀和处理出每个数的出现次数，做到 $O(\frac{n^2}B)-O(1)$。

时间复杂度 $O(\frac{n^2}B+nB+\frac nB\times q\log n)$，取 $B=\sqrt{n\log n}$ 得到最优复杂度 $O(n\sqrt{n\log n})$，可以通过。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;
const int MAXM = 5e2 + 10;

int B = 3e3, V, a[MAXN], sum[MAXN][MAXM];

inline 
void init(int n) {
	V = n / B + 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= V && j <= a[i]; j++) sum[i][j]++;
		for (int j = 1; j <= V; j++) sum[i][j] += sum[i - 1][j];
	}
}

inline 
int ask(int ql, int qr, int x) {
	return sum[qr][x] - sum[ql - 1][x];
}

int n, m; bitset<MAXN> vis[3010];

inline 
bool solve(int p, int x) {
	for (int i = 1, j = 1; i <= n; i++, j++) {
		int l = i, r = n, mid;
		for (; l < r; ask(i, mid = l + r >> 1, j) < x ? l = mid + 1 : r = mid);
		if (i <= p && p <= l) return a[p] >= j; i = l;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	init(n);
	for (int j = 1, k, x; j <= B; j++) {
		k = 1, x = 0;
		for (int i = 1; i <= n; i++) {
			if (a[i] < k) continue; vis[j][i] = 1;
			if (++x == j) ++k, x = 0;
		}
	}
	for (int p, x; m--;) {
		scanf("%d%d", &p, &x);
		if (x <= B) puts(vis[x][p] ? "YES" : "NO");
		else puts(solve(p, x) ? "YES" : "NO");
	}
}
```

---

## 作者：沉石鱼惊旋 (赞：31)

# 题目翻译

打怪操作是指，顺次对于 $[1,n]$ 的每个怪，每个怪有 $a_i$ 的等级，如果你的等级 $lv$ **严格**大于怪的等级 $a_i$，它就会逃跑。反之你会和它战斗。

你每与 $k$ 个怪战斗就会升一级，即 $lv\gets lv+1$。

现在有若干组查询，每次查询 $i,x$ 表示询问 $k=x$ 时，你是否会和第 $i$ 个怪战斗。

$1\leq n,q\leq 2\times 10^5$，$1\leq a_i\leq 2\times 10^5$，$1\leq i,x\leq n$

# 题目思路

首先考虑一个 $\log^3$ 的最暴力做法，然后在这上面优化。

由于每打 $k$ 个怪就会升级，所以你最多会升 $\lfloor\frac{n}{k}\rfloor$ 次。而 $\sum\limits_{k=1}^{n} \frac nk \approx n \log n$。也就是对于所有的 $k=x$ 我们只会有 $\mathcal O(n \log n )$ 次升级。

对于每一组 $k=x$，我们可以找到若干升级段，也就是 $[l,r]$ 满足击杀了第 $l$ 到第 $r$ 只怪会正好升级。

因为最多升级 $\mathcal O(n\log n)$ 次，因此每次升级二分右端点，接下来处理怎么判定 $[l,r]$ 是可以恰好升级的段。我们需要判断 $[l,r]$ 是否满足 $\sum\limits_{i=l}^r [a_i\geq lv] \geq k$，其中的 $[]$ 为艾弗森括号，取值为 $[x]=\begin{cases}1&x\ \text{is True}\\0& \text{Otherwise}\end{cases}$。

那么我们可以使用主席树等数据结构求解。详见 [牛客小白月赛 9 E. 换个角度思考](https://ac.nowcoder.com/acm/contest/275/E) 或 [HDU 4417 Super Mario](https://acm.hdu.edu.cn/showproblem.php?pid=4417)。

这样就得到了一个没有什么思维含量的 $\mathcal O(n\log^3 n)$ 的做法。

调和级数一共 $\mathcal O(n\log n)$ 种区间，二分一只 $\log$，这两个都无法优化了，我们尝试在计算 $\sum\limits_{i=l}^r [a_i\geq lv] \geq k$ 上做文章。

由于随着 $k$ 的上升，那么相对升级就会变慢，**等级高的怪我们不需要考虑**。准确的说只有 $a_i\leq \frac n k$ 的怪才有可能给我们升级带来影响。

然而如果我们 $a_i$ 都很小的话，我们可以通过预处理前缀和计算 $\sum\limits_{i=l}^r [a_i\geq lv] \geq k$。我们设 $sum_{i,j}$ 表示前 $i$ 个数中，怪物等级 $\leq j$ 的怪物个数。那么 $\sum\limits_{i=l}^r [a_i\geq lv]$ 就等价于 $(r-l+1)-(sum_{r,lv-1}-sum_{l-1,lv-1})$。这样就可以把这个一个 $\log$ 优化掉。

这个预处理是 $\mathcal O(\frac{n^2}{B})$ 的。这样我们就处理了 $k\gt B$ 的情况。

如果 $k\leq B$，那么我们直接做 $\mathcal O(Bn)$ 的暴力就行。

把两个做法结合一下，取 $B=\sqrt n$，那么两种算法的复杂度分别是：

- $k\leq B$

  暴力 $\mathcal O(n\sqrt n)$。

- $k\gt B$

  预处理 $\mathcal O(n\sqrt n)$。

  做查询 $\mathcal O(n\log^2 n)$。

这样我们就在 $\mathcal O(n\sqrt n+n\log^2 n)$ 的时间中做完了这个问题。

因此，简单说一下过程，就是预处理 $sum_{i,j}$ 表示前 $i$ 个等级 $\leq j$ 的怪兽个数，离线询问，对于 $k\leq B$ 的暴力扫一遍序列模拟，对于 $k\gt B$ 的二分区间端点，通过预处理的 $sum$ 数组判断是否合法。

# 完整代码

[CF submission 273823527](https://codeforces.com/contest/1997/submission/273823527)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
const int B = 448;
int n, Q;
int a[200020];
vector<array<int, 2>> q[200020];
bool ans[200020];
int sum[450][200020];
bool skip[200020];
int level[200020];
int main()
{
    read(n, Q);
    for (int i = 1; i <= n; i++)
    {
        read(a[i]);
        if (a[i] <= B)
            sum[a[i]][i]++;
    }
    for (int j = 1; j <= B; j++)
    {
        for (int i = 1; i <= n; i++)
            sum[j][i] += sum[j - 1][i] + sum[j][i - 1] - sum[j - 1][i - 1];
    }
    for (int i = 1; i <= Q; i++)
    {
        int p, k;
        read(p, k);
        q[k].push_back({p, i});
    }
    for (int k = 1; k <= n; k++)
    {
        if (q[k].empty())
            continue;
        if (k <= B)
        {
            int lvl = 1;
            int cnt = 0;
            for (int i = 1; i <= n; i++)
            {
                skip[i] = 0;
                if (a[i] < lvl)
                {
                    skip[i] = 1;
                    continue;
                }
                cnt++;
                if (cnt == k)
                    cnt = 0, lvl++;
            }
            for (auto [p, i] : q[k])
            {
                if (!skip[p])
                    ans[i] = 1;
            }
        }
        else
        {
            sort(q[k].begin(), q[k].end());
            int l = 1, r = 0, lvl = 1;
            int j = 0;
            auto check = [&](int r)
            { return (r - l + 1) - (sum[lvl - 1][r] - sum[lvl - 1][l - 1]) >= k; };
            while (l <= n)
            {
                int L = l, R = n, r = n;
                while (L <= R)
                {
                    int mid = L + R >> 1;
                    if (check(mid))
                        R = (r = mid) - 1;
                    else
                        L = mid + 1;
                }
                while (j < q[k].size() && l <= q[k][j][0] && q[k][j][0] <= r)
                    level[q[k][j][0]] = lvl, j++;
                l = r + 1;
                lvl++;
            }
            for (auto [p, i] : q[k])
            {
                if (level[p] <= a[p])
                    ans[i] = 1;
            }
        }
    }
    for (int i = 1; i <= Q; i++)
        puts(ans[i] ? "YES" : "NO");
    return 0;
}
```

---

## 作者：Lavaloon (赞：17)

**这里是单 $\log$ 做法，并且不需要任何高级数据结构。**

## $\text{Analysis}$

从感性理解出发来感受本题可能具有的性质：

- 每打 $k$ 个怪升一级，那这可能说明：$k$ 越大，升级越难。

用数学语言来表述并推广这个结论：

- **对于固定的一个怪物 $i$，玩家遇到它的时候，玩家的等级一定随着 $k$ 的增大而单调不增。**

- 又因为这个怪的等级是恒定的，那么这就说明一种单调性：随着 $k$ 的减小，”这个怪物是否应战“是单调的——只会从应战到不应战。这是因为在 $k$ 比较小的时候，此时玩家可能已经具有高于这个怪的等级，这个怪此时会选择逃跑。

上面加粗的结论终究是感性理解的产物，接下来给出严谨证明：

- 我们定义“**所需经验值**”是玩家升到下一级，还需击败的怪物的数量。

- 假设 $k_1<k_2$，考虑两个玩家，第一个玩家 $k=k_1$，第二个玩家 $k=k_2$。
- 采用数学归纳法，我们归纳证明一个结论：**要么**第一个玩家的等级高于第二个玩家，**要么**第一个玩家的等级等于第二个玩家，且第一个玩家的“所需经验值”少于第二个玩家的“所需经验值”：
  - 一开始两人等级相等，$k=k_1$ 时玩家的“所需经验值”少于 $k=k_2$ 时玩家的“所需经验值”。**这是归纳的前提。**
  - **假设归纳的结论对一段前缀的怪都成立**，对于下一个与第二个玩家战斗的怪：
    - 假如第一个玩家与之战斗，分为两种情况：若**刚刚打完**这个怪后两人等级相等（当然这说明第一个玩家此时没有升级），那么无论第二个玩家是否升级，第一个玩家的“所需经验值”少于第二个玩家的“所需经验值”仍然是正确的；否则，第一个玩家的等级**高于**第二个玩家的等级。
    - 假如面对第一个玩家时怪物逃离，那这说明：在**将要**打这个怪物时，第一个玩家的等级**高于**第二个时玩家的等级。即使在**刚刚打完**这个怪物之后第二个玩家获得升级，第二个玩家的“所需经验值”也要**大于**第一个玩家的“所需经验值”，因为第二个玩家的“所需经验值”现在又是 $k_2$ 了。
  - 证毕。

**因此，随着 $k$ 的减小，”一个固定的怪物是否应战“是单调的——只会从应战到不应战。**

一些读者此时可能已经有解决这道题的思路了。

## $\text{Solution}$

有了上面的单调性，我们可以对于每个怪物，求出来**最小**的那个 $k$，使得在“每打 $k$ 个怪升一级”的情况下，这个怪物会和玩家对战。这样即可对于每一组询问 $\mathcal{O}(1)$ 回答。

**对于固定的一个怪物**，如何求出这个 $k$ 呢？单调性启示我们使用**二分答案**。这样，求解的复杂度是 $\mathcal{O}(n\log n)$ 的。

问题是我们要对于所有怪物求解这个玩意，这启示我们使用**整体二分**。

整体二分的过程中，我们考虑**答案 $k\in[L,R]$ 的所有怪物**，二分一个 $\mathrm{mid}$，对这些怪物怪物决策它是否在此情况下应战。

假如它应战，那么这个怪物对应的 $k\le \mathrm{mid}$ ；否则 $k>\mathrm{mid}$。

我们想要求的是 $k=\mathrm{mid}$ 时，**这个怪物前面**已经有多少个怪物选择应战了。

为了保证复杂度**只与当前参与二分的怪物集合的大小有关**，我们对于每一个怪物，记录**答案 $k<L$，且在这个怪物前面**的怪物数量——这些怪物在此时二分的 $\mathrm{mid}$ 时一定应战。这样只剩下了 **$L\le k\le \mathrm{mid}$，且在这个怪物前面**的情况。

在此情况下，**可能应战的怪物一定存在于当前参与二分的怪物集合里面**——这是我们复杂度的保障。

在这个集合里面，**我们按下标递增的顺序**，一个个处理该怪物是否应战。因为下标是递增的，我们直接使用一个计数器 $cnt$ 表示**这个集合里面且在这个位置前面**已经选择应战的怪物数量即可。**不需要任何高级数据结构**。

综上，总复杂度 $\mathcal{O}(n\log n+q)$。

对于不熟练整体二分的读者，代码附带的注释或许会对您有帮助。

## $\text{Code}$

附有部分注释，这样良心的题解哪里找！

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<unordered_map>
#include<vector>
#include<bitset>
#include<queue>
#include<set>
#include<map>
#include<ctime>
#include<random>
#include<numeric>
#include<assert.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define lc (x<<1)
#define rc (x<<1|1)
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
const int Mx=300005,p=998244353;
int read(){
	char ch=getchar();
	int Alice=0,Aya=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-') Aya=-Aya;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		Alice=(Alice<<3)+(Alice<<1)+(ch^48),ch=getchar();
	return (Aya==1?Alice:-Alice);
}
int n,m;
int a[Mx];
int inter[Mx];
struct Info{
	int id,pre;
	//id: 怪物编号
	//pre: 答案 k<L ，且在这个怪物前面的怪物数量，——这些怪物在此时二分的 mid 时一定应战 
};
void Solve(int L,int R,vector<Info>vec){//答案 k\in[L,R] 的所有怪物
	if(vec.empty()) return;
	if(L==R){
		for(Info _:vec) inter[_.id]=L;
		return;
	}
	int mid=((L+R)>>1);
	vector<Info>acc,ref;//应战；不应战 
	for(Info &_:vec){
		int i=_.id;
		int lv=1+(_.pre+acc.size())/mid;//题解中的 cnt 就是应战的怪物数量，就是 acc.size()  
		if(lv>a[i]) _.pre+=acc.size(),ref.push_back(_);//注意更新 pre  
		else acc.push_back(_);
	}
	Solve(L,mid,acc);
	Solve(mid+1,R,ref);
}
signed main(){
	n=read(),m=read();
	vector<Info>vec(n);
	for(int i=1;i<=n;i++) a[i]=read(),vec[i-1]={i,0};
	Solve(1,n,vec);
	for(int i=1,id,k;i<=m;i++){
		id=read(),k=read();
		printf((inter[id]>k?"NO\n":"YES\n"));
	}
	return 0;
}
```

---

## 作者：Z1qqurat (赞：17)

树状数组是 $\mathcal{O}(1)$ 的，望周知。

1. Observation: 假如给出一组询问，问阈值为 $k$ 的时候 $x$ 有没有被打。观察发现肯定会将所有怪物划分为若干不交连续段 $[l_1,r_1],[l_2,r_2],\dots,[l_m,r_m]$，而他们当时的上界就是 $1,2,\dots,m$，也就是说 $[l_i,r_i]$ 间的怪如果权值 $\ge i$ 就会被打。容易发现 $r_i-l_i+1\ge k$，也就是说对于每个 $k$，它的连续段数量 $m\le \lfloor\frac{n}{k}\rfloor$。

2. Analysis: $\sum\limits_{k=1}^n \lfloor\frac{n}{k}\rfloor=\mathcal{O}(n\ln n)$。这时候容易想到离线处理所有询问，先考虑对于每个 $k$ 维护它的连续段，询问怎么做先不管。

   枚举 $k\in [1,n]$，然后枚举段数 $i$，现在在找阈值为 $k$ 时第 $i$ 个连续段的位置 $[l_i,r_i]$。首先有 $l_i=r_{i-1}+1$，那么就只要考虑求 $r_i$。容易发现 $r_i$ 就是满足 $[l_i,rt]$ 中 $\ge i$ 的数个数至少为 $k$ 的最小的 $r$，这时候想到二分，那么 check 一个区间内会被打的怪的个数就是一个二维数点问题，二分一个 $\log$，二维数点两个 $\log$，然后还有一个 $\mathcal{O}(n\ln n)$，这要寄了。考虑用树套树做二维数点，那么可以线段树二分（？），变成大常数 $\mathcal{O}(n\ln n \log^2 n)$。这个做法难写也时空常数大，不具有建设性价值。

   考虑一些轻量级做法，建一棵以原数组下标为 $x$ 轴的树状数组，枚举每个 $i$ 的时候保证树状数组内只保留了 $a_j\ge i$ 的所有 $j$（可以一开始把所有数插进去，然后枚举到 $i$ 的时候删掉所有 $a_j=i-1$ 的数），但是这样枚举的 $j$ 的个数对于每个 $k$ 都可能是 $\mathcal{O}(n)$ 的，这样就平方了，做不了。但是如果不考虑树状数组的部分，这个做法是小常数 $\mathcal{O}(n\ln n \log^2 n)$ 的，有前途。

3. Optimization: 虽然上面那个树状数组做法是 $\mathcal{O}(n^2)$ 的，但是它很具有建设性。灵光一闪，你发现复杂度瓶颈在于树状数组的维护，考虑减少树状数组删除节点的次数。再次观察对于每个 $k$ 的所有连续段之间的性质，其实两个连续段之间是相对独立的，因为它们的上界不同。想到这样一种像“交换求和顺序”一样神奇的转化，不再是外层枚举 $k$，而是外层枚举上界（段数）$i$，考虑对于每个 $k$，统一维护它们的第 $i$ 段。这时候所有存在第 $i$ 段的 $k$，它们的 $[l_{i-1},r_{i-1}]$ 是已知的，那么只需要一个二分就可以求出 $r_i$，而这时候树状数组的更新是放在外层的，所以树状数组的维护只带来了 $\mathcal{O}(n\log n)$ 的时间开销，处理每个 $k$ 的所有连续段的时间仍然是   $\mathcal{O}(n\ln n \log^2 n)$，这回它是瓶颈。

   需要注意一个细节，枚举 $i$ 之后，可能存在第 $i$ 段的 $k$ 不是得满足 $ik\le n$，而是 $(i-1)k\le n$ 就够了，画个图发现这是因为 $k$ 的最后一段不一定是满的。

4. Analysis: 最后考虑询问怎么维护。把询问挂到 $k$ 上面，然后对于每个 $k$ 内部将询问按照 $x$ 排序，然后每次求出一个 $[l_i,r_i]$ 的时候将 $x\in [l_i,r_i]$ 的询问给维护了，具体为了保证复杂度可以在每个 $k$ 的询问集合里面弄一个指针。

5. Optimization: 发现二分 + 树状数组 check 的那个东西可以使用树状数组倍增弄过去，这样二分连续段右端点就从 $\log^2 n$ 变成 $\log n$ 了。虽然说树状数组倍增的边界问题不好处理，也就是到底取 $\ge$ 还是 $>$，但是这题没关系，因为如果一个位置 $j$ 在第 $i$ 个连续段里用不上，它在第 $i+1$ 个连续段更用不上（因为 $a_j<i\to a_j<i+1$），所以为 $0$ 的点就算被取了也不影响，连续段的右端点不一定是唯一的。

朴素写法：总复杂度 $\mathcal{O}(n\ln n \log^2 n)$，但是 827ms 过了。

```cpp
#include <bits/stdc++.h>

#define FOR(i, l, r) for (int i = l; i <= (r); ++i)
#define ROF(i, l, r) for (int i = (r); i >= l; --i)
#define rep(n) FOR(i, 1, n)
#define each(i, x) for (auto &i : x)

using ll = long long;
using db = double;
using str = std::string;

using std::cin;
using std::cout;

using pi = std::pair<int, int>;
#define mr std::make_pair
#define fi first
#define se second

#define ttt template <typename T
ttt > using V = std::vector<T>;
ttt, size_t n > using A = std::array<T, n>;

#define sz(x) int((x).size())
#define rsz resize
#define ALL(v) begin(v), end(v)
#define All(v, l, r) &v[l], &v[(r) + 1]
#define pb push_back
#define eb emplace_back

#define il inline
ttt > il bool ckmin(T &x, const T &y) { return y < x ? x = y, true : false; }
ttt > il bool ckmax(T &x, const T &y) { return y > x ? x = y, true : false; }

constexpr int N = 2e5 + 5;
int n, q;
A<V<pi>, N> qr;
A<int, N> a, ans, rt, lst;
A<V<int>, N> p;

namespace fwk {
   A<int, N> t;

   int ask(int x) {
      int r = 0;
      for (int i = x; i; i -= i & (-i)) r += t[i];
      return r;
   }
   void upd(int x, int v) {
      for (int i = x; i <= n + 1; i += i & (-i)) t[i] += v;
      return ;
   }
}

int binary(int x, int k) {
   int w = fwk::ask(x);
   int l = x, r = n + 1;
   while (l + 1 < r) {
      int mid = l + r >> 1;
      if (fwk::ask(mid) - w >= k) r = mid;
      else l = mid;
   }
   return r;
}

int main() {
   std::ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

   cin >> n >> q;
   FOR (i, 1, n) cin >> a[i], p[a[i]].eb(i), fwk::upd(i, 1);
   FOR (i, 1, q) {
      int x, k; cin >> x >> k, qr[k].eb(x, i);
   }
   FOR (i, 1, n) std::sort(ALL(qr[i]));

   FOR (w, 1, n) { //level
      each (i, p[w - 1]) fwk::upd(i, -1);
      int lim = w == 1 ? n : n / (w - 1);
      FOR (k, 1, lim) { //parameter
         if (rt[k] >= n) break;
         if (!sz(qr[k])) continue;
         rt[k] = binary(rt[k], k);
         while (lst[k] < sz(qr[k]) && qr[k][lst[k]].fi <= rt[k])
            ans[qr[k][lst[k]].se] = (a[qr[k][lst[k]].fi] >= w), ++lst[k];
      }
   }
   FOR (i, 1, q) cout << (ans[i] ? "YES\n" : "NO\n");
   return 0;
}
```

with 树状数组倍增：$\mathcal{O}(n\ln n\log n)$，感谢 @[夜明](https://www.luogu.com.cn/user/305891) 的提出。这样只要 515ms。

```cpp
#include <bits/stdc++.h>

#define FOR(i, l, r) for (int i = l; i <= (r); ++i)
#define ROF(i, l, r) for (int i = (r); i >= l; --i)
#define rep(n) FOR(i, 1, n)
#define each(i, x) for (auto &i : x)

using ll = long long;
using db = double;
using str = std::string;

using std::cin;
using std::cout;

using pi = std::pair<int, int>;
#define mr std::make_pair
#define fi first
#define se second

#define ttt template <typename T
ttt > using V = std::vector<T>;
ttt, size_t n > using A = std::array<T, n>;

#define sz(x) int((x).size())
#define rsz resize
#define ALL(v) begin(v), end(v)
#define All(v, l, r) &v[l], &v[(r) + 1]
#define pb push_back
#define eb emplace_back

#define il inline
ttt > il bool ckmin(T &x, const T &y) { return y < x ? x = y, true : false; }
ttt > il bool ckmax(T &x, const T &y) { return y > x ? x = y, true : false; }

constexpr int N = 2e5 + 5;
int n, q;
A<V<pi>, N> qr;
A<int, N> a, ans, rt, lst;
A<V<int>, N> p;

namespace fwk {
   A<int, N> t;

   int ask(int x) {
      int r = 0;
      for (int i = x; i; i -= i & (-i)) r += t[i];
      return r;
   }
   int binary(int x, int k) {
   	int w = fwk::ask(x) + k, r = 0, sum = 0;
   	ROF (i, 0, 17) {
   		if (sum >= w) break;
   		int _r = r + (1 << i);
   		if (_r > n) continue;
   		if (sum + t[_r] <= w) r = _r, sum += t[r]; 
		}
   	return r;
	}
   void upd(int x, int v) {
      for (int i = x; i <= n + 1; i += i & (-i)) t[i] += v;
      return ;
   }
}

int main() {
   std::ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

   cin >> n >> q;
   FOR (i, 1, n) cin >> a[i], p[a[i]].eb(i), fwk::upd(i, 1);
   FOR (i, 1, q) {
      int x, k; cin >> x >> k, qr[k].eb(x, i);
   }
   FOR (i, 1, n) std::sort(ALL(qr[i]));

   FOR (w, 1, n) { //level
      each (i, p[w - 1]) fwk::upd(i, -1);
      int lim = w == 1 ? n : n / (w - 1);
      FOR (k, 1, lim) { //parameter
         if (rt[k] >= n) break;
         if (!sz(qr[k])) continue;
         rt[k] = fwk::binary(rt[k], k);
         while (lst[k] < sz(qr[k]) && qr[k][lst[k]].fi <= rt[k])
            ans[qr[k][lst[k]].se] = (a[qr[k][lst[k]].fi] >= w), ++lst[k];
      }
   }
   FOR (i, 1, q) cout << (ans[i] ? "YES\n" : "NO\n");
   return 0;
}
```



后期了解到还有别的做法，基本上都跑得没这个 $\mathcal{O}(n\ln n\log^2 n)$ 快。

1. （**从怪物入手而不是从阈值 $k$ 入手**）观察到单调性，做 dp：发现如果这样分连续段，那么对于同一个怪物 $i$，$k$ 越大它被分到的连续段越靠前，下界 $w$ 会越小。也就是说 $k$ 越大 $i$ 越容易被打，所以如果阈值为 $k$ 时怪物 $i$ 没有被打，那么阈值为 $k-1$ 时 $i$ 也一定不会被打；如果 $k$ 时被打，那么 $k+1$ 时一定被打。这就存在了一种单调性，考虑记 $f_i$ 表示对于怪物 $i$，$k\ge f_i$ 时怪物 $i$ 会被打，那么 $f_i$ 的求解只需要一个二分：如果当前 $k$ 满足 $1\sim i-1$ 中在 $k$ 时会被打的怪物数量 $cnt$，有 $a_i> \lfloor\frac{cnt}{k}\rfloor$，也就是说如果 $i$ 放进去那么它就在第 $\lfloor\frac{cnt}{k}\rfloor+1$ 个连续段里面，这时候的 $k$ 就是合法的。求 $cnt$ 可以利用 $f_{1\sim i-1}$，结合树状数组做到总复杂度 $\mathcal{O}(n\log^2 n)$，太天才了。

   ```cpp
   #include <bits/stdc++.h>
   
   #define FOR(i, l, r) for (int i = l; i <= (r); ++i)
   #define ROF(i, l, r) for (int i = (r); i >= l; --i)
   #define rep(n) FOR(i, 1, n)
   #define each(i, x) for (auto &i : x)
   
   using ll = long long;
   using db = double;
   using str = std::string;
   
   using std::cin;
   using std::cout;
   
   using pi = std::pair<int, int>;
   #define mr std::make_pair
   #define fi first
   #define se second
   
   #define ttt template <typename T
   ttt > using V = std::vector<T>;
   ttt, size_t n > using A = std::array<T, n>;
   
   #define sz(x) int((x).size())
   #define rsz resize
   #define ALL(v) begin(v), end(v)
   #define All(v, l, r) &v[l], &v[(r) + 1]
   #define pb push_back
   #define eb emplace_back
   
   #define il inline
   ttt > il bool ckmin(T &x, const T &y) { return y < x ? x = y, true : false; }
   ttt > il bool ckmax(T &x, const T &y) { return y > x ? x = y, true : false; }
   
   constexpr int N = 2e5 + 5;
   
   int n, q;
   A<int, N> a, f;
   
   namespace fwk {
      A<int, N> t;
   
      int ask(int x) {
         int r = 0;
         for (int i = x; i; i -= i & (-i)) r += t[i];
         return r;
      }
      void upd(int x, int v) {
         for (int i = x; i <= n + 1; i += i & (-i)) t[i] += v;
         return ;
      }
   }
   
   int main() {
      std::ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
   
      cin >> n >> q;
      FOR (i, 1, n) {
         cin >> a[i];
         int l = 0, r = n + 1;
         while (l + 1 < r) {
            int mid = l + r >> 1;
            if (fwk::ask(mid) < (ll)a[i] * mid) r = mid;
            else l = mid;
         }
         f[i] = r, fwk::upd(f[i], 1);
      }
      FOR (i, 1, q) {
         int x, k; cin >> x >> k;
         cout << (k >= f[x] ? "YES\n" : "NO\n");
      }
      return 0;
   }
   ```

2. 跳连续段的时候发现这东西可能可以根号分治：

   * 对于比较小的 $k\le B$，如果直接暴力枚举 $i\in[1,n]$，check 它是否满足当前下界，是 $\mathcal{O}(nB)$ 的。
   * 对于比较大的 $k>B$，考虑延续第一个做法的二分，但这时候至多存在 $\frac{n}{B}$ 段，下界分别是 $1,2,\dots,\frac{n}{B}$，如果记录前缀和 $sum_{i,j}$ 表示对于 $i\in[1,n],j\in[1,\frac{n}{B}]$，前缀 $i$ 内 $a_k\ge j$ 的 $k$ 个数，那么空间开销是 $\mathcal{O}(n \frac{n}{B})$ 的；二分每一段的右端点，二分时候用 $sum$ 辅助可以 $\mathcal{O}(1)$ check，所以是 $\mathcal{O}(n\frac{n}{B}\log n)$ 的时间。

   平衡一下，取 $B=\sqrt{n\log n}=1900$，但是经过一系列尝试发现块长不太好取，并不是恰好 $1900$ 最优。

   * 如果取 $1900$ 会在 $n=q=200000$，$a_i=1$ 的时候寄掉。
   * 如果取 $1000$ 之类的会在 $n=q=200000$，$a_i=200000$ 寄掉。

   平衡一下取了 $B=3000$，然后用了 bitset 优化。发现如果开 $B$ 个长度为 $n$ 的 bitset 比 $n$ 个长度为 $B$ 的 bitset 快很多，前者能过，后者在 Test $7$ 就挂了，个人猜测是内存连续访问之类的（？不知道为啥感觉这个取块长毫无科学可言啊。。。

   卡常的时候发现 [cfhj](https://codeforces.com/contest/1997/submission/273560132) 的做法是取的块长 $B=1000$，但是他过了，hack 无果。发现他把 $>B$ 的二分改成了倍增，但是他的倍增也不是普通的 $0\sim \log n$ 的倍增，他是这么写的：

   ```cpp
   for(int j=10;j>=0;--j){
      while(nxt+(1<<j)<=n&&cnt[nxt+(1<<j)][now]-cnt[pos][now]<y)nxt+=(1<<j);
   }
   ```

   你发现这在段长比较小的时候可以省掉一些 $j$ 过大的枚举，因为 $k>B$ 的时候，数的下界相对小，段长比较小的概率大一些。这很天才啊。

   给出我写的 $B=3000$。

   ```cpp
   #include <bits/stdc++.h>
   
   #define FOR(i, l, r) for (int i = l; i <= (r); ++i)
   #define ROF(i, l, r) for (int i = (r); i >= l; --i)
   #define rep(n) FOR(i, 1, n)
   #define each(i, x) for (auto &i : x)
   
   using ll = long long;
   using db = double;
   using str = std::string;
   
   using std::cin;
   using std::cout;
   
   using pi = std::pair<int, int>;
   #define mr std::make_pair
   #define fi first
   #define se second
   
   #define ttt template <typename T
   ttt > using V = std::vector<T>;
   ttt, size_t n > using A = std::array<T, n>;
   
   #define sz(x) int((x).size())
   #define rsz resize
   #define ALL(v) begin(v), end(v)
   #define All(v, l, r) &v[l], &v[(r) + 1]
   #define pb push_back
   #define eb emplace_back
   
   #define il inline
   ttt > il bool ckmin(T &x, const T &y) { return y < x ? x = y, true : false; }
   ttt > il bool ckmax(T &x, const T &y) { return y > x ? x = y, true : false; }
   
   constexpr int N = 2e5 + 5, B = 3000, K = N / B + 1;
   int n, q;
   A<int, N> a;
   A<A<int, K + 2>, N> sum;
   A<std::bitset<N>, B + 2> b;
   
   void init() {
      FOR (k, 1, B) {
         int cnt = 0, lvl = 1;
         FOR (i, 1, n) {
            if (a[i] >= lvl) ++cnt, b[k][i] = 1;
            if (cnt == k) ++lvl, cnt = 0;
         }
      }
      FOR (i, 1, n) {
         if (i) std::copy_n(&sum[i - 1][1], K, &sum[i][1]);
         FOR (j, 1, std::min(a[i], K)) ++sum[i][j];
      }
      return ;
   }
   
   int binary(int x, int w, int k) {
      int l = x, r = n + 1;
      while (l + 1 < r) {
         int mid = l + r >> 1;
         if (sum[mid][w] - sum[x][w] >= k) r = mid;
         else l = mid;
      }
      return r;
   }
   
   int main() {
      std::ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
   
      cin >> n >> q;
      FOR (i, 1, n) cin >> a[i];
      init();
      rep (q) {
         int x, k; cin >> x >> k;
         if (k <= B) cout << (b[k][x] ? "YES\n" : "NO\n");
         else {
            int r = 0, lvl = 1;
            bool tag = 0;
            while (r < n) {
               r = binary(r, lvl, k);
               if (x <= r) { tag = a[x] >= lvl; break; }
               ++lvl;
            }
            cout << (tag ? "YES\n" : "NO\n");
         }
      }
      return 0;
   }
   ```

3. 还可以暴力主席树上二分，本质思路和 dp 有点像，但是 no heavy data structure please，不推荐也不讲解。

---

## 作者：Aurora5090 (赞：6)

[CF 传送门](https://codeforces.com/contest/1997/problem/E)

提供一个 $O(q + n \sqrt n)$ 时间，$O(n)$ 空间的解法。

容易想到根号分治，我们先离线询问，按询问的 $k$ 排序。

根据套路，枚举 $k \lt \sqrt n$ 的部分，每次扫一遍序列，  
预处理出每个 $a_i$ 是否被使用，暴力回答对应的询问。  
这部分时间是 $O(n \sqrt n)$，离线后空间可以做到 $O(n)$。

随后解决 $k \ge \sqrt n$ 的部分：  
在这部分，我们的等级最多只有 $\sqrt n$，所以可以找出每个等级区间的范围,  
第一直觉的做法可能是会带个  $\log$ 的，我们每次从序列的最左边开始二分，  
可以找到等级 $1$ 的右端点，以此类推，重复 $\sqrt n$ 次就可以找到所有的端点，  
然后回答询问，如果这个端点在等级 $L$ 的区间里，答案即为 $[a_i \ge L]$。  
这样的话是 $O(n \sqrt n \log n)$，但是有洁癖？！

其实稍微改一下就可以做到严格 $O(n \sqrt n)$。  
依赖一个观察：随着我们 $k$ 的不断增大，每个等级区间的端点只会单调右移。  
证明比较简单，考虑等级 $1$ 的区间不会左移，那么等级 $2$ 的区间也不会左移......  
实际上就是 $O(\sqrt n)$ 个区间指针在不断右移，直到满足 $k$ 的限制，  
在移动过程中，暴力维护 $a_i$ 有没有被使用，被谁使用，每个等级区间使用了多少个 $a$。  

每次可以 $O(1)$ 回答，就做到 $O(q + n \sqrt n)$ 时间，$O(n)$ 空间了。

挪指针的时候访存比较垃圾，好像 $B = 1000$ 跑的比较快，这样最多有 $200$ 个指针，421 ms。

代码
```cpp
#include <bits/stdc++.h>
using namespace std;

struct node
{
    int pos, k, id;
    inline bool operator<(const node &n) const
    {
        return k < n.k;
    }
};

const int maxn = 2e5 + 5, B = 1000;
int n, q;
int a[maxn], ans[maxn];
node ask[maxn];
int col[maxn];
int ptr[205], val[205], bel[maxn];

void build(int qk)
{
    int level = 1, cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        cnt += (a[i] >= level);
        col[i] = (a[i] >= level);
        if (cnt >= qk)
            level++, cnt = 0;
    }
}

void init()
{
    int level = 1, cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        int v = a[i] >= level;
        cnt += v;
        val[level] += v;
        col[i] = v;
        bel[i] = level;
        if (cnt >= B)
            ptr[level] = i, level++, cnt = 0;
    }
    ptr[level] = n;
}

void solve(int qk)
{
    for (int id = 1; id <= 200; id++)
    {
        if (ptr[id] == 0 || ptr[id] >= n)
            break;
        if (ptr[id] < ptr[id - 1])
            ptr[id] = ptr[id - 1], val[id] = 0;
        while (val[id] < qk && ptr[id] < n)
        {
            int i = ++ptr[id];
            if (a[i] >= id)
            {
                val[id]++;
                if (col[i] == 1)
                    val[bel[i]]--;
                bel[i] = id;
                col[i] = 1;
            }
            else
            {
                bel[i] = 0;
                col[i] = 0;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= q; i++)
    {
        cin >> ask[i].pos >> ask[i].k;
        ask[i].id = i;
    }

    sort(ask + 1, ask + 1 + q);

    int pre = 0;
    int flag = true;
    for (int i = 1; i <= q; i++)
    {
        auto [qpos, qk, qid] = ask[i];

        if (qk <= B)
        {
            if (pre != qk)
                build(qk);
        }
        else
        {
            if (flag == true)
                init(), flag = false;
            if (pre != qk)
                solve(qk);
        }
        ans[qid] = col[qpos];
        pre = qk;
    }

    for (int i = 1; i <= q; i++)
        cout << (ans[i] == 0 ? "NO\n" : "YES\n");

    // cout.flush();
    // system("Pause");
    return 0;
}
```

---

## 作者：Muse_Dash (赞：5)

根号做法，感觉这道题比较难。

考虑根号分治，设一个阈值 $V$，对 $x$ 的大小进行讨论：

- $x\leq V$，考虑暴力求出 $k=x$ 时每个怪物是否战斗的状况。这个可以预处理出来，查询直接输出预处理的答案，`bitset` 优化一点空间。预处理复杂度 $\Theta(Vn)$。
- $x>V$，假设 Monocarp 最终有 $lv$ 等级，那么 $lv\leq\frac{n}{x}$，故 $lv$ 不会超过 $\frac{n}{V}$ 级别。可以考虑二分每个等级到达下一个等级需要最终击杀第几个怪物，这个可以对每个等级用前缀和预处理。预处理前缀和复杂度是 $\Theta(\frac{n^2}{V})$，二分查询一次答案约是 $\Theta(\frac{n}{V}\log n)$。

总体复杂度约为 $\Theta(Vn+\frac{n^2}{V}+\frac{nq}{V}\log n)$，取 $V=\sqrt{n\log n}$ 达到最优复杂度 $\Theta(n\sqrt{n\log n})$。

```cpp
void init_ans(int x){
	int lv=1,cnt=0;
	for (int i=1;i<=n;i++){
		if (a[i]>=lv) {cnt++,ans[x][i]=1;if (cnt==x) {lv++,cnt=0;}}
		else ans[x][i]=0;
	}
}
void init_pre(int x){
	for (int i=1;i<=n;i++)
		pre[x][i]=pre[x][i-1]+(a[i]>=x);
}
bool search(int i,int x){
	int lv=1,now=0;
	while (pre[lv][i-1]-pre[lv][now]>=x){
		int l=now,r=i-1;
		while (l<r){
			int mid=(l+r)>>1;
			if (pre[lv][mid]-pre[lv][now]<=x) l=mid+1;
			else r=mid;
		}
		while (pre[lv][l]-pre[lv][now]>x) l--;
		now=l,lv++;
	}
	return a[i]>=lv;
}
```

---

## 作者：BYR_KKK (赞：3)

## CF1997E

> 一个怪物能被击败当且仅当他的等级不小于主人公的等级，主人公每击败 $k$ 个怪物就会升一级，初始为 $1$ 级，从左往右攻击怪物。多组询问当 $k=x$ 时，怪物 $i$ 是否能被击败。

题面给出了 $2k$，$3k$ 这种表示，很容易让人联想到调和级数。因此将询问离线下来，对每组 $x$ 进行处理。对于某个 $x$，我们每一轮暴力往后跳到下一等级从哪开始（一轮最少要跳 $x$ 步）。于是我们只需要对于 $l$，$p$，找到 $l\sim n$ 中第 $k$ 个权值 $\ge p$ 的点在哪。可以主席树上二分。但是我们观察到时限较长，因此果断选择分块，块内进行排序。当查询时对于散块暴力查，对于整块进行二分，容易找到答案。复杂度上限为 $O(n\log^2n\times\sqrt{n})$，但达不到这个上限。我设的块长为 $\sqrt{n}$，卡卡常就能跑进 $2$ 秒。

[代码](https://codeforces.com/contest/1997/submission/273649199)

---

## 作者：wmrqwq (赞：1)

upd：原来代码 fst 了，现已修改了代码和思路。

# 题目链接

[CF1997E Level Up (codeforces)](https://codeforces.com/problemset/problem/1997/E)

[CF1997E Level Up (luogu)](https://www.luogu.com.cn/problem/CF1997E)

# 解题思路

根号分治。

设阙值为 $B$，我们可以将所有小于等于 $B$ 的 $k$ 的全部答案都预处理出来，这个部分可以使用 bitset 来进行维护从而降低空间复杂度，反之可以通过预处理 $sum_{i,j}$ 表示前 $i$ 个人战斗力大于等于 $j$ 的人的个数，然后就可以进行二分答案了。

这里第一个预处理 $B$ 取 $1200$，第二个预处理 $B$ 取 $560$ 可以通过此题。

时间复杂度 $O(n \sqrt{n} \log n)$。

# 参考代码

```cpp
// LUOGU_RID: 170011394
#include<bits/stdc++.h>
using namespace std;//
//#define map unordered_map
#define re register
#define ll int
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);init();
//#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
namespace Fread
{
	const int SIZE = 1 << 16;
	char buf[SIZE], *S, *T;
	inline char getchar() { if (S == T) { T = (S = buf) + fread(buf, 1, SIZE, stdin); if (S == T) return '\n'; } return *S++; }
}
using namespace Fread;
namespace Fwrite
{
	const int SIZE = 1 << 16;
	char buf[SIZE], *S = buf, *T = buf + SIZE;
	inline void flush() { fwrite(buf, 1, S - buf, stdout); S = buf; }
	inline void putchar(char c) { *S++ = c; if (S == T) flush(); }
	struct NTR { ~NTR() { flush(); } } ztr;
}
using namespace Fwrite;
#define getchar Fread::getchar
#define putchar Fwrite::putchar
namespace Fastio
{
	struct Reader
	{
		template <typename T> Reader& operator >> (T &x)
		{
			x = 0;
			short f = 1;
			char c = getchar();
			while (c < '0' || c > '9') { if (c == '-') f *= -1; c = getchar(); }
			while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
			x *= f;
			return *this;
		}
		Reader& operator >> (double &x)
		{
			x = 0;
			double t = 0;
			short f = 1, s = 0;
			char c = getchar();
			while ((c < '0' || c > '9') && c != '.') { if (c == '-') f *= -1; c = getchar(); }
			while (c >= '0' && c <= '9' && c != '.') x = x * 10 + (c ^ 48), c = getchar();
			if (c == '.') c = getchar();
			else { x *= f; return *this; }
			while (c >= '0' && c <= '9') t = t * 10 + (c ^ 48), s++, c = getchar();
			while (s--) t /= 10.0;
			x = (x + t) * f;
			return *this;
		}
		Reader& operator >> (long double &x)
		{
			x = 0;
			long double t = 0;
			short f = 1, s = 0;
			char c = getchar();
			while ((c < '0' || c > '9') && c != '.') { if (c == '-') f *= -1; c = getchar(); }
			while (c >= '0' && c <= '9' && c != '.') x = x * 10 + (c ^ 48), c = getchar();
			if (c == '.') c = getchar();
			else { x *= f; return *this; }
			while (c >= '0' && c <= '9') t = t * 10 + (c ^ 48), s++, c = getchar();
			while (s--) t /= 10.0;
			x = (x + t) * f;
			return *this;
		}
		Reader& operator >> (__float128 &x)
		{
			x = 0;
			__float128 t = 0;
			short f = 1, s = 0;
			char c = getchar();
			while ((c < '0' || c > '9') && c != '.') { if (c == '-') f *= -1; c = getchar(); }
			while (c >= '0' && c <= '9' && c != '.') x = x * 10 + (c ^ 48), c = getchar();
			if (c == '.') c = getchar();
			else { x *= f; return *this; }
			while (c >= '0' && c <= '9') t = t * 10 + (c ^ 48), s++, c = getchar();
			while (s--) t /= 10.0;
			x = (x + t) * f;
			return *this;
		}
		Reader& operator >> (char &c)
		{
			c = getchar();
			while (c == ' ' || c == '\n' || c == '\r') c = getchar();
			return *this;
		}
		Reader& operator >> (char *str)
		{
			int len = 0;
			char c = getchar();
			while (c == ' ' || c == '\n' || c == '\r') c = getchar();
			while (c != ' ' && c != '\n' && c != '\r') str[len++] = c, c = getchar();
			str[len] = '\0';
			return *this;
		}
		Reader& operator >> (string &str)
		{
			str.clear();
			char c = getchar();
			while (c == ' ' || c == '\n' || c == '\r') c = getchar();
			while (c != ' ' && c != '\n' && c != '\r') str.push_back(c), c = getchar();
			return *this;
		}
		Reader() {}
	} cin;
	const char endl = '\n';
	struct Writer
	{
		const int Setprecision = 6;
		typedef int mxdouble;
		template <typename T> Writer& operator << (T x)
		{
			if (x == 0) { putchar('0'); return *this; }
			if (x < 0) putchar('-'), x = -x;
			static short sta[40];
			short top = 0;
			while (x > 0) sta[++top] = x % 10, x /= 10;
			while (top > 0) putchar(sta[top] + '0'), top--;
			return *this;
		}
		Writer& operator << (double x)
		{
			if (x < 0) putchar('-'), x = -x;
			mxdouble _ = x;
			x -= (double)_;
			static short sta[40];
			short top = 0;
			while (_ > 0) sta[++top] = _ % 10, _ /= 10;
			if (top == 0) putchar('0');
			while (top > 0) putchar(sta[top] + '0'), top--;
			putchar('.');
			for (int i = 0; i < Setprecision; i++) x *= 10;
			_ = x;
			while (_ > 0) sta[++top] = _ % 10, _ /= 10;
			for (int i = 0; i < Setprecision - top; i++) putchar('0');
			while (top > 0) putchar(sta[top] + '0'), top--;
			return *this;
		}
		Writer& operator << (long double x)
		{
			if (x < 0) putchar('-'), x = -x;
			mxdouble _ = x;
			x -= (long double)_;
			static short sta[40];
			short top = 0;
			while (_ > 0) sta[++top] = _ % 10, _ /= 10;
			if (top == 0) putchar('0');
			while (top > 0) putchar(sta[top] + '0'), top--;
			putchar('.');
			for (int i = 0; i < Setprecision; i++) x *= 10;
			_ = x;
			while (_ > 0) sta[++top] = _ % 10, _ /= 10;
			for (int i = 0; i < Setprecision - top; i++) putchar('0');
			while (top > 0) putchar(sta[top] + '0'), top--;
			return *this;
		}
		Writer& operator << (__float128 x)
		{
			if (x < 0) putchar('-'), x = -x;
			mxdouble _ = x;
			x -= (__float128)_;
			static short sta[40];
			short top = 0;
			while (_ > 0) sta[++top] = _ % 10, _ /= 10;
			if (top == 0) putchar('0');
			while (top > 0) putchar(sta[top] + '0'), top--;
			putchar('.');
			for (int i = 0; i < Setprecision; i++) x *= 10;
			_ = x;
			while (_ > 0) sta[++top] = _ % 10, _ /= 10;
			for (int i = 0; i < Setprecision - top; i++) putchar('0');
			while (top > 0) putchar(sta[top] + '0'), top--;
			return *this;
		}
		Writer& operator << (char c) { putchar(c); return *this; }
		Writer& operator << (char *str)
		{
			int cur = 0;
			while (str[cur]) putchar(str[cur++]);
			return *this;
		}
		Writer& operator << (const char *str)
		{
			int cur = 0;
			while (str[cur]) putchar(str[cur++]);
			return *this;
		}
		Writer& operator << (string str)
		{
			int st = 0, ed = str.size();
			while (st < ed) putchar(str[st++]);
			return *this;
		}
		Writer() {}
	} cout;
}
using namespace Fastio;
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll _t_;
void _clear(){}
ll n,q,sq,sq2;
ll a[200010];
//ll vis[200010][320];
bitset<1210>vis[200010];
ll sum[200010][560];
ll maxn[200010],minn[200010],Sum[200010];
ll times;
map<ll,map<ll,ll>>mp;
ll get(ll l,ll r,ll x)
{
	ll su=0;
	forl(i,l,r)
		su+=a[i]>=x,times++;
	return su;
}
ll lst;
ll x,y;
void solve()
{
	_clear();
	cin>>n>>q;
	sq=558,sq2=1200;
//	sq=sqrt(n);
	forl(i,1,n)
	{
		maxn[i]=1e18;
		cin>>a[i];
		forl(j,0,sq+1)
		{
			sum[i][j]=sum[i-1][j];
			if(a[i]>=j)
				sum[i][j]++;
			times++;
		}
	}
	forl(i,1,n)
		Sum[i]=Sum[i-1]+(a[i]==200000);
	forl(i,1,sq2)
	{
		ll sum=1,sum2=0;
		forl(j,1,n)
		{
			times++;
			if(sum>a[j])
				continue;
			vis[j][i]=1;
			sum2++;
			if(sum2==i)
			{
				sum2=0;
				sum++;
			}
		}
	}
	while(q--)
	{
		cin>>x>>y;
		if(a[x]==2e5)
		{
			cfy;
			continue;
		}
		if(a[x]==1 && Sum[x]>y)
		{
			cfn;
			continue;
		}
		if(maxn[x]<=y)
		{
			cfy;
			continue;
		}
		if(minn[x]>=y)
		{
			cfn;
			continue;
		}
		if(a[x]>=(x+y-1)/y)
		{
			cfy;
			lst=1;
			continue;
		}
		if(mp[x][y])
		{
			if(mp[x][y]==1){
				cfy;
			}
			else
				cfn;
			continue;
		}
		if(y<=1200)
		{
			printcf(vis[x][y]);
			continue;
		}
		ll now=1,sum2=1;
		forl(i,1,n)
		{
			ll L=now+y-1,R=n,fl=1;
			while(L<R)
			{
				ll Mid=(L+R)/2;
				if(sum[Mid][sum2]-sum[now-1][sum2]<y)
					L=Mid+1;
				else
					R=Mid;
				if(L>=x)
				{
					if(a[x]>=sum2)
						mp[x][y]=1,Min(maxn[x],y);
					else
						mp[x][y]=-1,Max(minn[x],y);
					printcf(a[x]>=sum2);
					fl=0;
					break;
				}
			}
			if(!fl)
				break;
			sum2++;
			now=L+1;
			if(L>=x)
			{
				if(a[x]>=sum2-1)
					mp[x][y]=1,Min(maxn[x],y);
				else
					mp[x][y]=-1,Max(minn[x],y);
				printcf(a[x]>=sum2-1);
				break;
			}
		}
	}
}
void init(){}
int main()
{
//	IOS;
	_t_=1;
 //	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：MarSer020 (赞：1)

你说的对，但是这个傻逼赛时 -3，居然是因为离线之后没有给询问排序/cf

$\Large\text{Solution}$

考虑若当前等级为 $i$，升到 $i+1$ 级只需要向后找到第 $k$ 个 $\ge i$ 的数即可。于是我们建主席树，第 $i$ 个根表示 $\ge i$ 的数组成的线段树，查询时直接在主席树上二分即可。

考虑将询问离线下来，对每种 $k$ 分开考虑，这样就只有 $O(n\ln n)$ 次询问了。总时间复杂度 $O(n\ln n\log n)$。

$\Large\text{Code}$

upd on 2024.8.1：被 hack 了，原因是 $a_i$ 可以大于 $n$。已修改代码。

```cpp
// LUOGU_RID: 169632761
#include<bits/stdc++.h>
#define ls t[cur].lc
#define rs t[cur].rc
#define mid ((l+r)>>1)
using namespace std;
int n,m,a[200005],top,rt[200005],p,x,ans[200005],ret;
vector<pair<int,int>>v[200005];
pair<int,int>b[200005];
struct node{
	int val,lc,rc;
}t[40000005];
int clone(int cur){
	top++,t[top]=t[cur];
	return top;
}
int build(int cur,int l,int r){
	cur=++top;
	if(l==r){
		t[cur].val=0;
		return cur;
	}
	ls=build(ls,l,mid),rs=build(rs,mid+1,r),t[cur].val=t[ls].val+t[rs].val;
	return cur;
}
int update(int cur,int l,int r,int p){
	cur=clone(cur);
    if(l==r){
		t[cur].val=1;
		return cur;
	}
    if(p<=mid)
		ls=update(ls,l,mid,p);
	else
		rs=update(rs,mid+1,r,p);
	t[cur].val=t[ls].val+t[rs].val;
	return cur;
}
int find(int cur,int l,int r,int val){
	if(l==r)
		return l;
	if(val<=t[ls].val)
		return find(ls,l,mid,val);
	else
		return find(rs,mid+1,r,val-t[ls].val);
}
void query(int cur,int l,int r,int x,int y,int&val){
	if(!val||x>y)
		return;
	if(x<=l&&r<=y){
		if(val<=t[cur].val)
			ret=find(cur,l,r,val),val=0;
		else
			val-=t[cur].val;
		return;
	}
	if(x<=mid)
		query(ls,l,mid,x,y,val);
	if(y>mid)
		query(rs,mid+1,r,x,y,val);
}
void solve(){
    cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i],a[i]=min(a[i],n);
	rt[n+1]=build(0,1,n);
	for(int i=1;i<=n;i++)
		b[i]={a[i],i};
	sort(b+1,b+n+1,greater<>());
	for(int i=n,p=1;i>=1;i--){
		rt[i]=rt[i+1];
		while(p<=n&&b[p].first==i)
			rt[i]=update(rt[i],1,n,b[p].second),p++;
	}
	assert(top<=40000000);
	for(int i=1;i<=m;i++)
		cin>>p>>x,v[x].emplace_back(p,i);
	for(int k=1,p,i,tmp;k<=n;k++){
		sort(v[k].begin(),v[k].end());
		auto it=v[k].begin();
		for(p=0,i=1;;i++){
			tmp=k,ret=0,query(rt[i],1,n,p+1,n,tmp);
			if(tmp||it==v[k].end())
				break;
			p=ret;
			while(it!=v[k].end()&&it->first<=p)
				ans[it->second]=(a[it->first]>=i),it++;
		}
		while(it!=v[k].end())
			ans[it->second]=(a[it->first]>=i),it++;
	}
	for(int i=1;i<=m;i++)
		cout<<(ans[i]?"YES\n":"NO\n");
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),solve();
	return 0;
}
```

---

