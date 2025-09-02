# Soap Time! - 2

## 题目描述

Imagine the Cartesian coordinate system. There are $ k $ different points containing subway stations. One can get from any subway station to any one instantly. That is, the duration of the transfer between any two subway stations can be considered equal to zero. You are allowed to travel only between subway stations, that is, you are not allowed to leave the subway somewhere in the middle of your path, in-between the stations.

There are $ n $ dwarves, they are represented by their coordinates on the plane. The dwarves want to come together and watch a soap opera at some integer point on the plane. For that, they choose the gathering point and start moving towards it simultaneously. In one second a dwarf can move from point $ (x,y) $ to one of the following points: $ (x-1,y) $ , $ (x+1,y) $ , $ (x,y-1) $ , $ (x,y+1) $ . Besides, the dwarves can use the subway as many times as they want (the subway transfers the dwarves instantly). The dwarves do not interfere with each other as they move (that is, the dwarves move simultaneously and independently from each other).

Help the dwarves and find the minimum time they need to gather at one point.

## 样例 #1

### 输入

```
1 0
2 -2
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 2
5 -3
-4 -5
-4 0
-3 -2
```

### 输出

```
6
```

# 题解

## 作者：APJifengc (赞：5)

前言：这个做法是 $O(n \log ^2 n)$ 的，官方题解说有 $O(n \log n)$ 的做法，但是我没看懂他在说啥，贴的代码链接由于过于远古已经失效了，网上也找不到其他关于本题的博客，最后捣鼓半天捣鼓出的这个做法）

# 思路

考虑我们现在找出了一个点，那么答案就是所有点到这个点的时间的最大值，我们要让这个最大值最小，不难想到二分答案。

那么我们首先二分一个答案 $mid$。那么，如果我们把每个点在 $mid$ 时间内能经过的点看作一个集合，那么 $mid$ 合法当且仅当每个点代表的集合的交集不为空。

考虑一个点能够到达的点集是一个菱形。这个菱形很丑，所以我们先考虑将曼哈顿距离转成切比雪夫距离，这样能到达的点集就是一个矩形了。

然后我们现在要考虑的就是这几个集合是否有交。首先每个点可以走以自己为中心的 $mid$ 的一个矩形，而且它可以走到离它最近的一个车站，设这个最短距离为 $dis$，那么这样就相当于又以每个车站为中心的 $mid - dis$ 的一个矩形，某一个点能够到达的点集就是这几个矩形的交。

下面有两种方式能够得出一个结论，第一种比较无脑，如果感觉第一种比较抽象可以看第二种。

我们拿个式子来写一些：设以 $i$ 为中心的矩形为 $A_i$，$i$ 能通过车站到达的矩形的集合的并为 $B_i$，那么我们其实就是要求 $\bigcap (A_i \cup B_i)$。

直接把这个东西拆开。由于我们发现如果 $mid - dis_i \le mid - dis_j$，那么 $B_i \cap B_j = B_j$，那么也就是说其实只有 $mid - dis_j$ 最大的那个 $B_i$ 是有贡献的。那么如果按照 $mid - dis_j$ 从小到大排好序，那么上面那个式子其实等于 $(B_1) \cup (A_1 \cap B_2) \cup (A_1 \cap A_2 \cap B_3) \cup \cdots$。

换一种方式理解，如果某个人决定要到车站，那么如果有的人可以到车站，且他到车站比前面那个人距离还短，那么这个人直接跟着那个人走就可以了，所以只需要考虑到车站且距离最大的那个人即可。

那么问题就变成了要求上面那个式子是否为空集。由于 $A_i$ 是一个矩形，可以 $O(1)$ 计算交集，我们考虑维护 $A_{1\sim i-1}$ 的交集，然后看它与 $B_i$ 是否有交集即可。

那么我们可以用主席树维护出二维平面上某个矩形中是否有车站。如果 $A$ 与某个 $B$ 有交集，那么 $B$ 的中心肯定在 $A$ 往外扩大 $B$ 的边心距的矩形内。这样我们就可以判断了。

求每个点距离最近的点也可以直接这么二分，方法很多就不说了。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005, M = 200000000;
struct SegmentTree {
    struct Node {
        int lc, rc, sum;
    } t[MAXN * 60];
    int tot;
    void insert(int d, int &p, int l = -M, int r = M) {
        if (!p) p = ++tot, t[p].sum = 1;
        else t[++tot] = t[p], p = tot, t[p].sum++;
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (d <= mid) insert(d, t[p].lc, l, mid);
        else insert(d, t[p].rc, mid + 1, r);
    }
    int query(int a, int b, int p, int l = -M, int r = M) {
        if (!p) return 0;
        if (a <= l && r <= b) return t[p].sum;
        int mid = (l + r) >> 1;
        if (b <= mid) return query(a, b, t[p].lc, l, mid);
        if (a > mid) return query(a, b, t[p].rc, mid + 1, r);
        return query(a, b, t[p].lc, l, mid) + query(a, b, t[p].rc, mid + 1, r);
    }
} st;
int X[MAXN], o;
int root[MAXN];
bool check(int X1, int X2, int Y1, int Y2) {
    int l = lower_bound(X + 1, X + 1 + o, X1) - X, r = upper_bound(X + 1, X + 1 + o, X2) - X - 1;
    return st.query(Y1, Y2, root[r]) - st.query(Y1, Y2, root[l - 1]);
}
int n, k;
int px[MAXN], py[MAXN];
int sx[MAXN], sy[MAXN];
vector<int> s[MAXN];
pair<int, int> a[MAXN];
int main() {
    scanf("%d%d", &n, &k);
    int minX = M, maxX = -M;
    int minY = M, maxY = -M;
    for (int i = 1; i <= n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        px[i] = x + y, py[i] = x - y;
        minX = min(minX, px[i]), minY = min(minY, py[i]);
        maxX = max(maxX, px[i]), maxY = max(maxY, py[i]);
    }
    int ans = (max(maxX - minX, maxY - minY) + 1) / 2;
    for (int i = 1; i <= k; i++) {
        int x, y; scanf("%d%d", &x, &y);
        sx[i] = x + y, sy[i] = x - y;
        X[i] = sx[i];
    }
    sort(X + 1, X + 1 + k);
    o = unique(X + 1, X + 1 + k) - X - 1;
    for (int i = 1; i <= k; i++) {
        int j = lower_bound(X + 1, X + 1 + o, sx[i]) - X;
        s[j].push_back(i);
    }
    for (int i = 1; i <= o; i++) {
        root[i] = root[i - 1];
        for (int j : s[i]) {
            st.insert(sy[j], root[i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        int l = 0, r = M;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (check(px[i] - mid, px[i] + mid, py[i] - mid, py[i] + mid)) r = mid;
            else l = mid + 1;
        }
        a[i] = { l, i };
    }
    sort(a + 1, a + 1 + n, greater<pair<int, int>>());
    int l = 0, r = ans;
    while (l < r) {
        int mid = (l + r) >> 1;
        minX = M, maxX = -M;
        minY = M, maxY = -M;
        bool flag = false;
        for (int i = 1; i <= n; i++) {
            if (mid < a[i].first) {
                minX = min(minX, px[a[i].second] + mid), maxX = max(maxX, px[a[i].second] - mid);
                minY = min(minY, py[a[i].second] + mid), maxY = max(maxY, py[a[i].second] - mid);
                if (maxX > minX || maxY > minY) break;
            } else {
                if (maxX <= minX && maxY <= minY) {
                    int w = mid - a[i].first;
                    if (check(maxX - w, minX + w, maxY - w, minY + w)) {
                        flag = true;
                        break;
                    }
                }
                minX = min(minX, px[a[i].second] + mid), maxX = max(maxX, px[a[i].second] - mid);
                minY = min(minY, py[a[i].second] + mid), maxY = max(maxY, py[a[i].second] - mid);
            }
        }
        if (flag) r = mid;
        else l = mid + 1;
    }
    printf("%d\n", l);
    return 0;
}
```

---

## 作者：ty_mxzhn (赞：1)

二分答案 $x$。

先考虑没有地铁的部分分，每一个矮人可以到达一个菱形区域。判定的时候只需要给这些菱形取交，这是好做的。

现在出现了地铁。每一个矮人可以自由选择自己要直接走还是去地铁站。定义 $d_i$ 表示第 $i$ 个矮人距离最近的地铁站有多近。不难发现，如果一个矮人去了地铁站，那么比他 $d_i$ 更小的都去地铁站。换句话说，去地铁站的矮人是 $d$ 排序后的一个前缀。

考虑不去地铁站的矮人能走到的菱形的交。这个菱形要和至少一个地铁站的菱形有交。

这是容易维护的，定义 $D$ 为这些地铁站的菱形的半径，把这个菱形反过来拓展 $D$ 半径，则问题转化为矩形查询是否有点。用主席树维护可以做到 $O(n\log n\log V)$。

---

