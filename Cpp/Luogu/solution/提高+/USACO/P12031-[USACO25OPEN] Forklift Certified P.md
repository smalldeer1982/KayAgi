# [USACO25OPEN] Forklift Certified P

## 题目背景

**本翻译使用 AI 生成。**

checker 提供者：kjhhjki


## 题目描述

农夫约翰（Farmer John）正在接受培训，以获得叉车认证！作为培训的一部分，他需要从一个旧仓库中清理 $N$（$1 \le N \le 10^5$）个箱子，这些箱子被方便地标记为 $1$ 到 $N$。

这些箱子可以被建模为二维平面上的轴对齐矩形，其中 $+x$ 方向是东，$+y$ 方向是北。箱子 $i$ 的西南角坐标为 $(x_{i1}, y_{i1})$，东北角坐标为 $(x_{i2}, y_{i2})$。所有坐标都是范围 $[1, 2N]$ 内的整数，并且来自不同矩形的任意两个角都不会共享相同的 $x$ 或 $y$ 坐标。所有箱子都有非零面积，且没有两个箱子相交。

农夫约翰计划每次从仓库的西南入口处移除一个箱子。然而，由于叉车的物理限制，他只有在没有其他箱子的任何部分位于该箱子东北角的南方和西方时，才能移除该箱子。

下面显示了一个 $N = 4$ 的示例。要移除箱子 4，阴影区域内不能有任何其他箱子。箱子 2 和 3 阻止了箱子 4 被移除，但箱子 1 不会。

![](https://cdn.luogu.com.cn/upload/image_hosting/jte8z0w6.png)

帮助农夫约翰决定如何移除所有箱子！您的代码应根据整数标志 $M$ 在两种不同的模式下运行：

*   **模式 1**（$M = 1$）：生成一个 $1, \dots, N$ 的排列，指定一个有效的箱子移除顺序。如果存在多个有效的顺序，则输出任意一个。可以证明这样的顺序总是存在的。
*   **模式 2**（$M = 2$）：对于每个 $k = 1, \dots, N$，如果农夫约翰可以在箱子 $1, \dots, k-1$ 都已被移除的情况下移除箱子 $k$，则输出 1，否则输出 0。

## 说明/提示

### 样例 1 解释

第一个测试用例对应于上面 $N = 4$ 的示例。箱子 1 没有被任何东西阻挡，箱子 3 被箱子 1 阻挡，箱子 2 被箱子 3 阻挡，而箱子 4 被箱子 2 和 3 阻挡。

### 样例 2 解释

第一个测试用例，箱子 2 被箱子 3 阻挡，所以农夫约翰在移除箱子 3 之前无法移除箱子 2。

### 测试点限制

- 测试点 3-5: $M=1$，$N\leq 1000$。
- 测试点 6: $M=2$，$N\leq 1000$。
- 测试点 7-13: $M=1$，无额外限制。
- 测试点 14-16: $M=2$，无额外限制。

## 样例 #1

### 输入

```
2 1
4
1 6 2 8
6 2 7 3
3 1 4 7
5 4 8 5
3
1 5 3 6
4 1 5 2
2 3 6 4```

### 输出

```
1 3 2 4
2 3 1```

## 样例 #2

### 输入

```
2 2
4
1 6 2 8
6 2 7 3
3 1 4 7
5 4 8 5
3
1 5 3 6
4 1 5 2
2 3 6 4```

### 输出

```
1011
011```

# 题解

## 作者：沉石鱼惊旋 (赞：1)

# 做法

一个简单的发现是，我们每个箱子只需要关心『右上角』下方的区域是否包含某个箱子的『左下角』。

$M=2$ 就是 $M=1$ 的 checker。$M=2$ 的情况是好做的。我们把所有箱子的左下角按 $x$ 插入到线段树里，然后查询线段树前缀 $\min$，判断前缀 $\min$ 是否比当前箱子的右上角的 $y$ 小。如果小就是被包含了。

但是删除箱子需要支持删掉某个 $x$ 的某个 $y$ 。而删掉之后新的 $y'$ 可能成为这一行的最小值，我们对线段树的叶子结点开 `std::set` 维护一下。

感谢 @[hard_plan](https://www.luogu.com.cn/user/749406) 指出，这里元素坐标都是不一样的（我一开始没看到这个信息，难过），叶子结点只需要记录对应值就可以了。

$M=1$ 考虑类似拓扑排序的做法。但是按枚举一个点然后枚举出边的做法肯定不行。我们考虑尝试删除 $u$ 的时候，找到一个挡住他的 $v$，尝试递归下去删掉 $v$。如果删掉 $v$ 之后没有障碍了就结束了，否则继续找到下一个 $v_2$ 去删掉，直到 $u$ 可以被删除。重复这个过程。显然每个点只会被删除一次。其实就是一个拓扑排序的 DFS 写法。

注意可能会出自环。先把 $u$ 点删掉就可以了。

# 代码

<https://www.luogu.com.cn/record/212388266>

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
template <class T>
void write(T x)
{
    static int stk[30];
    if (x < 0)
        putchar('-'), x = -x;
    int top = 0;
    do
    {
        stk[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        putchar(stk[--top] + '0');
}
template <class T>
void write(T x, char lastChar) { write(x), putchar(lastChar); }
const int inf = 1e9;
int N, M;
int n;
struct point
{
    int x, y;
};
point a[100020];
point b[100020];
array<int, 2> s[200020];
struct SegTree
{
    struct node
    {
        array<int, 2> mn;
    } t[200020 << 2];
#define ls id << 1
#define rs id << 1 | 1
#define Llen (mid - l + 1)
#define Rlen (r - mid)
    void push_up(int id) { t[id].mn = min(t[ls].mn, t[rs].mn); }
    void build(int id = 1, int l = 1, int r = N)
    {
        if (l == r)
            return t[id].mn = {inf, -1}, void();
        int mid = l + r >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        push_up(id);
    }
    void add(int pos, array<int, 2> v, int k, int id = 1, int l = 1, int r = N)
    {
        if (r < pos || l > pos)
            return;
        if (pos <= l && r <= pos)
        {
            if (k > 0)
                s[pos] = v;
            else
                s[pos] = {0, 0};
            t[id].mn = s[pos] == (array<int, 2>){0, 0} ? (array<int, 2>){inf, -1} : s[pos];
            return;
        }
        int mid = l + r >> 1;
        add(pos, v, k, ls, l, mid);
        add(pos, v, k, rs, mid + 1, r);
        push_up(id);
    }
    array<int, 2> query(int ql, int qr, int id = 1, int l = 1, int r = N)
    {
        if (r < ql || l > qr)
            return {inf, -1};
        if (ql <= l && r <= qr)
            return t[id].mn;
        int mid = l + r >> 1;
        return min(query(ql, qr, ls, l, mid), query(ql, qr, rs, mid + 1, r));
    }
} T;
namespace M1
{
    bool vis[100020];
    bool del[100020];
    void dfs(int u)
    {
        if (del[u])
            return;
        if (!vis[u])
            T.add(a[u].x, {a[u].y, u}, -1), vis[u] = 1;
        auto [w, v] = T.query(1, b[u].x);
        if (w >= b[u].y)
            return del[u] = 1, write(u, ' ');
        dfs(v);
        dfs(u);
    }
    void solve()
    {
        read(n);
        N = n << 1;
        memset(vis, 0, sizeof(bool) * (n + 5));
        memset(del, 0, sizeof(bool) * (n + 5));
        T.build();
        for (int i = 1; i <= n; i++)
            read(a[i].x, a[i].y, b[i].x, b[i].y);
        for (int i = 1; i <= n; i++)
            T.add(a[i].x, {a[i].y, i}, 1);
        for (int i = 1; i <= n; i++)
            dfs(i);
        putchar('\n');
    }
};
namespace M2
{
    void solve()
    {
        read(n);
        N = n << 1;
        T.build();
        for (int i = 1; i <= n; i++)
            read(a[i].x, a[i].y, b[i].x, b[i].y);
        for (int i = 1; i <= n; i++)
            T.add(a[i].x, {a[i].y, i}, 1);
        for (int i = 1; i <= n; i++)
            T.add(a[i].x, {a[i].y, i}, -1), write(T.query(1, b[i].x)[0] >= b[i].y);
        putchar('\n');
    }
}
int main()
{
    int t;
    read(t, M);
    while (t--)
        (M & 1 ? M1::solve() : M2::solve());
    return 0;
}
```

---

