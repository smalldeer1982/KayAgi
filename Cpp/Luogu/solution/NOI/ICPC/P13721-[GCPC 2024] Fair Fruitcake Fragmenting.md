# [GCPC 2024] Fair Fruitcake Fragmenting

## 题目描述

Frida 的生日快到了，作为她最好的朋友，你当然为她烤了一个蛋糕。
你知道 Frida 喜欢旋转对称，所以你打算烤一个从上方看起来在旋转 $180^\circ$ 后依然相同的蛋糕。
当然，你本可以简单地烤一个普通的圆形蛋糕，但没有一个完美的圆形蛋糕模具，这听起来比做起来要容易。
因此，你决定烤一个可以用直线段描述形状的蛋糕。

![](https://cdn.luogu.com.cn/upload/image_hosting/j4oo5c4y.png)

:::align{center}

图 F.1：样例输入 2 的可视化。像 S 形的蛋糕可以用一刀分成红色和蓝色两部分。

:::

然而，在你完成蛋糕后，你发现你还想把蛋糕切成两等份，一份给 Frida，一份给你自己。
更准确地说，你想知道是否可以沿着一条无限长的直线将蛋糕精确地分成两部分，每部分的重量相等。
你可以假设蛋糕的密度和高度都是均匀的。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
0 0
2 0
2 2
0 2```

### 输出

```
1 1 1337/42 3141/1000```

## 样例 #2

### 输入

```
20
7 1
8 2
8 5
7 6
4 6
4 4
3 4
3 7
6 7
7 8
2 8
1 7
1 4
2 3
5 3
5 5
6 5
6 2
3 2
2 1```

### 输出

```
11 13 -2 -4```

## 样例 #3

### 输入

```
10
11 5
10 2
12 6
2 2
7 3
1 1
2 4
0 0
10 4
5 3```

### 输出

```
impossible```

# 题解

## 作者：cosf (赞：0)

分享一篇复杂度正确，但是常数爆炸的做法。~~很遗憾没有通过原时间限制 `3s`，本地跑最慢的只有 `4222ms`。怎么我的电脑比 qoj 还快。~~

现在卡常卡过了。

### 题目分析

下文令 $n \gets \frac{n}{2}$。

首先根据题目限制，切的那一条边必然经过中心对称点。中心对称点是好求的，把 $v_1$ 和 $v_{1 + n}$ 取中点即可。下文假设中心对称点为 $0, 0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/scjmak3k.png)

由样例图可知，这样的一条线一定将所有点分成编号连续（环上连续）的两部分，因此考虑双指针，维护两个集合 `set_point, set_angle`，其中 `set_point` 维护 $[i - n + 1, i]$ 的所有点，`set_angle` 维护相邻的夹角。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/e5b90fp7.png)

显然，如果存在某个 `set_angle` 中的角 $\gt \pi$，则存在一个答案，即将最后一个点做对称点后，再做一个平行四边形。这样横纵坐标都是 $O(V)$ 量级的，远远小于题目要求的 $10^9$。

![](https://cdn.luogu.com.cn/upload/image_hosting/dmmectx2.png)

然后就是棘手的地方了。有时候，我们可能不会出现 $\gt \pi$ 的角，但仍有答案。这个时候角度为 $\pi$。例如下图，

![](https://cdn.luogu.com.cn/upload/image_hosting/u0k2vfzp.png)

这条线经过了 $4$ 个点，$B, G, P, K$，但是它并没有将图形分成 $4$ 部分。然而，这并不代表所有最大角 $=\pi$ 的都可行，比如（抱歉画歪了），直线经过 $B, E, L, I$，但确实划分成了四个部分。

![](https://cdn.luogu.com.cn/upload/image_hosting/n6webhjc.png)


事实上我们要做的是这么一个事情：对于每一个点，当中点向它连线时，会不会因它而划分成多块。称不会分成多块的点为安全的。

![](https://cdn.luogu.com.cn/upload/image_hosting/05i8xcgu.png)

如上图，当直线将该点的上一个、下一个点分开时，这个点是安全的。而当上下点都处于一侧（包括线上）时，如下图，我们还需要判断这个多边形处于哪一侧。如果处于绿色一侧，则这个点是安全的，如果处于橙色，则这个点不安全。

假设我们知道了每个点是否安全，那怎么知道经过一些点的直线是否会划分出多部分？显然，如果它经过了不安全的点，它就会划分成不同的部分，但是，点数可能会很大，我们不可能遍历这些点。

这里可以这么做：对于辐角相同的点，在处理 `set_points` 中的顺序时，把不安全的点放在前面，则这样一条从中心出发的射线上是否安全可以快速算出。例如，设 $\pi$ 角两边同辐角的点分别是 $[1, \dots, 1, 0, \dots, 0], [1, \dots, 1, 0, \dots, 0]$，其中 $1$ 代表不安全，则 $\pi$ 角是由左侧第一个数与右侧第一个数构成的。因而我们可以快速判断左侧是否存在不安全的点。

那对于右边呢？显然我们只需要将不安全的点放在后面再算一次即可。在代码中称为第一部分和第二部分。

复杂度 $O(n\log n)$。总体的实现细节非常多。代码经过轻微卡常。

### 实现细节

在 `<cmath>` 头文件中，有一个函数叫做 `atan2l(y, x)`，可以返回一个 $(-\pi, \pi]$ 之间的角度。使用该函数就可以实现 `set_point` 的排序。然而，该函数常数较大，并且 `set_point` 最多只会出现 $2n$ 个点，所以应该预处理所有点的角度，这样就可以真正的 $O(1)$ 比较。

对于 `set_angle`，我们无法预处理所有的角度，但是我们只关心是否有角度 $\ge \pi$。事实上，由于 `set_angle` 里的角度和 $=2\pi$，所以至多一个角度 $\ge \pi$（请想一想为什么不会出现两个角都 $=\pi$ 的情况），而 $\ge \pi$ 的角度相当于在一个坐标 $(x, y)$ 中有 $y \le 0$，所以这个排序只需要类似 `pair<ll, ll>` 的默认排序即可。

```cpp line-numbers
// 英文注释是写题时留下的，中文注释是写题解时添加的

#include <iostream>
#include <numeric>
#include <cassert>
#include <iomanip>
#include <cmath>
#include <tuple>
#include <ctime>
#include <set>
using namespace std;

#define MAXN 100005
#define eps (1e-10l)

using ll = long long;
using ld = long double;

// 快读

char buf[1 << 22], *p1 = buf, *p2 = buf;

inline char gc()
{
    if (p1 == p2)
    {
        p2 = buf + fread(p1 = buf, 1, sizeof(buf), stdin);
    }
    return *p1++;
}

inline int read()
{
    int x = 0;
    static char ch = gc();
    while (ch < '0' || ch > '9')
    {
        ch = gc();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + (ch ^ '0');
        ch = gc();
    }
    return x;
}

ld pi = acosl(-1);

int n;

// sf 表示一个点是否安全；re 表示 [i - n + 1, i] 是否可能成为备选答案（即在第一部分中符合条件）
// rev 表示是否是第二部分
bool sf[MAXN], re[MAXN], rev = false;

struct LLPoint // 存储在 set_angle
{
    ll x, y;

    bool operator<(const LLPoint b) const
    {
        if (y == b.y)
        {
            return x < b.x;
        }
        return y < b.y;
    }
};

ld at2[MAXN]; // 预处理角度

struct IntPoint
{
    int x, y;
    int id;

    inline bool operator<(const IntPoint b) const
    {
        if (x == b.x && y == b.y)
        {
            if (sf[id] == sf[b.id]) // 注意相同角的排序方式
            {
                return id > b.id;
            }
            else if (rev)
            {
                return sf[id] < sf[b.id];
            }
            else
            {
                return sf[id] > sf[b.id];
            }
        }
        else
        {
            return at2[id] < at2[b.id];
        }
    }

    inline LLPoint ang(const IntPoint b) const // 用于计算 *this 逆时针转到 b 的角度
    {
        LLPoint res = {ll(x) * b.x + ll(y) * b.y, ll(x) * b.y - ll(b.x) * y};
        ll g = gcd(res.x, res.y);
        res.x /= g, res.y /= g;
        return res;
    }

    inline ll gy(const IntPoint b) const // 上一个函数返回的 y 值。由于较多情况下只会判断 y，所以创建这个函数卡常
    // 其实就是向量叉积
    {
        return ll(x) * b.y - ll(b.x) * y;
    }
} v[MAXN], C;

using spi = set<IntPoint>::iterator;
using tpi = tuple<LLPoint, int, int>;

set<IntPoint> sp; // set_point
set<tpi> sa; // set_angle，我们同时要维护这个角是哪两个点中间的，以便判断是否安全

inline spi safeprev(spi it) // 环上的 prev
{
    if (it == sp.begin())
    {
        return prev(sp.end());
    }
    return prev(it);
}

inline spi safenext(spi it)
{
    if (it == prev(sp.end()))
    {
        return sp.begin();
    }
    return next(it);
}

int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        v[i].x = read() << 1;
        v[i].y = read() << 1;
        v[i].id = i;
    }
    n >>= 1;
    C.x = (v[1].x + v[n + 1].x) >> 1;
    C.y = (v[1].y + v[n + 1].y) >> 1; // C 是中心对称点
    for (int i = 1; i <= 2 * n; i++)
    {
        v[i].x -= C.x;
        v[i].y -= C.y;
        at2[i] = atan2l(v[i].y, v[i].x);
    }
    for (int i = 1; i <= 2 * n; i++)
    {
        IntPoint pre = v[(i + 2 * n - 2) % (2 * n) + 1], nxt = v[i % (2 * n) + 1];
        ll bk = v[i].gy(pre), ed = v[i].gy(nxt);
        if (bk > 0 && ed < 0) // if they aren't on the same side, then i must be safe
        {
            sf[i] = true;
        }
        else if (bk < 0 && ed > 0)
        {
            sf[i] = true;
        } // bk.y and ed.y won't be zero at the same time.
        else if (IntPoint{pre.x - v[i].x, pre.y - v[i].y}.gy(IntPoint{nxt.x - v[i].x, nxt.y - v[i].y}) < 0)
        {
            sf[i] = true;
        }
    }
    for (int i = 1; i <= 2 * n; i++)
    {
        ll g = gcd(v[i].x, v[i].y);
        v[i].x /= g;
        v[i].y /= g;
    }

    int res = 0;

    // the first part
    sp.insert(v[1]);
    sa.insert({v[1].ang(v[1]), 1, 1});
    for (int i = 2; i < n; i++)
    {
        auto it = sp.insert(v[i]).first, pre = safeprev(it), nxt = safenext(it);
        sa.erase({pre->ang(*nxt), pre->id, nxt->id});
        sa.insert({pre->ang(v[i]), pre->id, i});
        sa.insert({v[i].ang(*nxt), i, nxt->id});
    }
    for (int i = n; i < 2 * n; i++)
    {
        auto it = sp.insert(v[i]).first, pre = safeprev(it), nxt = safenext(it);
        sa.erase({pre->ang(*nxt), pre->id, nxt->id});
        sa.insert({pre->ang(v[i]), pre->id, i});
        sa.insert({v[i].ang(*nxt), i, nxt->id});
        auto &[ang, s, e] = *sa.begin();
        if (ang.y < 0) // found, and this must be an answer
        {
            res = i;
            goto Output;
        }
        if (ang.y == 0 && ang.x < 0) // 刚好为 -\pi
        {
            re[i] = sf[e];
        }
        it = sp.find(v[i - n + 1]), pre = safeprev(it), nxt = safenext(it);
        sa.erase({pre->ang(v[i - n + 1]), pre->id, i - n + 1});
        sa.erase({v[i - n + 1].ang(*nxt), i - n + 1, nxt->id});
        sa.insert({pre->ang(*nxt), pre->id, nxt->id});
        sp.erase(it);
    }

    // the second part
    rev = true;
    sp.clear();
    sa.clear();
    sp.insert(v[1]);
    sa.insert({v[1].ang(v[1]), 1, 1});
    for (int i = 2; i < n; i++)
    {
        auto it = sp.insert(v[i]).first, pre = safeprev(it), nxt = safenext(it);
        sa.erase({pre->ang(*nxt), pre->id, nxt->id});
        sa.insert({pre->ang(v[i]), pre->id, i});
        sa.insert({v[i].ang(*nxt), i, nxt->id});
    }
    for (int i = n; i < 2 * n; i++)
    {
        auto it = sp.insert(v[i]).first, pre = safeprev(it), nxt = safenext(it);
        sa.erase({pre->ang(*nxt), pre->id, nxt->id});
        sa.insert({pre->ang(v[i]), pre->id, i});
        sa.insert({v[i].ang(*nxt), i, nxt->id});
        auto &[ang, s, e] = *sa.begin();
        if (ang.y == 0 && ang.x < 0 && re[i] && sf[s]) // -\pi 且两边都安全
        {
            res = i;
            break;
        }
        it = sp.find(v[i - n + 1]), pre = safeprev(it), nxt = safenext(it);
        sa.erase({pre->ang(v[i - n + 1]), pre->id, i - n + 1});
        sa.erase({v[i - n + 1].ang(*nxt), i - n + 1, nxt->id});
        sa.insert({pre->ang(*nxt), pre->id, nxt->id});
        sp.erase(it);
    }

    if (!res)
    {
        puts("impossible");
        return 0;
    }
    Output:
    /** [res - n + 1, res] are on the same side
     *  we need to find the line that can partition the 2n points into the desired partition
     */
    auto &[_, s, e] = *sa.begin();
    auto &[lx, ly,  __] = v[s];
    auto &[rx, ry, ___] = v[e];
    printf("%d/2 %d/2 %d/2 %d/2\n", C.x, C.y, C.x + rx - lx, C.y + ry - ly); // 平行四边形
    return 0;
}

```

附带一些文件。

[官网链接](https://2024.gcpc.nwerc.eu/)

[数据连接](https://2024.gcpc.nwerc.eu/problems.zip)（注意这个文件有 `246M`）

---

