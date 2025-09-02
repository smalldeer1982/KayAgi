# [USACO16JAN] Mowing the Field P

## 题目描述

Farmer John 在管理农场的各个方面都相当可靠，除了一件事：他非常不擅长及时修剪草地。事实上，他每天只能移动一次割草机。在第 1 天，他从位置 $(x_1, y_1)$ 开始，在第 $d$ 天，他沿着一条直线段移动到位置 $(x_d, y_d)$，在农场的二维地图上，他要么水平移动，要么垂直移动；也就是说，要么 $x_d = x_{d-1}$，要么 $y_d = y_{d-1}$。FJ 在连续的日子里交替进行水平和垂直移动。

FJ 的进展非常缓慢，以至于在他完成所有修剪之前，一些被他修剪过的草可能会重新长出来。任何在第 $d$ 天被修剪的草会在第 $d + T$ 天重新长出来，因此如果 FJ 的修剪路径与至少 $T$ 天前修剪过的路径交叉，他将再次在同一位置修剪草地。为了尝试改进他糟糕的修剪策略，FJ 想要计算这种情况发生的次数。

请计算 FJ 的修剪路径与之前已经重新长草的路径交叉的次数。你只需计算“垂直”交叉，定义为水平线段和垂直线段之间的共同点，且该点不是任何线段的端点。

## 说明/提示

在这里，FJ 在第 7 天与他在第 2 天修剪的草地路径交叉，这算作一次。其他交叉点不算。

注意：本题有扩展的限制：每个测试用例 5 秒（Python 和 Java 为 10 秒），内存限制为 512 MB。

## 样例 #1

### 输入

```
7 4
0 10
10 10
10 5
3 5
3 12
6 12
6 3```

### 输出

```
1```

# 题解

## 作者：zhzh2001 (赞：5)

# 本文约定


$\left\vert S\right\vert$:集合$S$的元素数量


$$\{x\vert p(x)\}$$:符合$p(x)$的元素组成的集合


$\land$:逻辑与


$\lor$:逻辑或


# 思路


首先根据题意(以及官方题解)，一个交点应该只会出现一次，所以只要考虑时间在范围外的交点数即可。也就是说，与第$i$条竖直线段相交的线段


$$c_i=\left\vert\{j\vert x_j^l<x_i<x_j^r\land y_i^l<y_j<y_i^r\land\left\vert t_i-t_j\right\vert\ge T\}\right\vert$$


当然，这个可以$O(N^2)$枚举。如果把绝对值拆开，就变成$t_j+T\le t_i\le t_j+T$，这时就变成经典的三维偏序问题了，可以在$O(N\log^2N)$内解决。


我们可以把竖直线段作为查询操作。按照x坐标排序，用扫描线维护水平线段$i$，保存点$(t_i,y_i)$。对于竖直线段$i$，查询$$\left\vert\{(t_j,y_j)\vert(t_j\le t_i-T\lor t_j\ge t_i+T)\land(y_i^l<y_j<y_i^r)\}\right\vert$$即为答案。注意，线段端点相交不计入答案，在处理x坐标时也要注意。


至于数据结构，我用了官方的树状数组套线段树。


# 代码


```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100005, LOGN = 32;
struct node
{
    int sum, ls, rs;
} tree[N * LOGN * 4];
int cc;
//线段树
void modify(int &id, int l, int r, int x, int val)
{
    if (!id)
        id = ++cc;
    if (l == r)
        tree[id].sum += val;
    else
    {
        int mid = (l + r) / 2;
        if (x <= mid)
            modify(tree[id].ls, l, mid, x, val);
        else
            modify(tree[id].rs, mid + 1, r, x, val);
        tree[id].sum = tree[tree[id].ls].sum + tree[tree[id].rs].sum;
    }
}
int query(int id, int l, int r, int L, int R)
{
    if (!id)
        return 0;
    if (L <= l && R >= r)
        return tree[id].sum;
    int mid = (l + r) / 2;
    if (R <= mid)
        return query(tree[id].ls, l, mid, L, R);
    if (L > mid)
        return query(tree[id].rs, mid + 1, r, L, R);
    return query(tree[id].ls, l, mid, L, R) + query(tree[id].rs, mid + 1, r, L, R);
}
int n, t;
//树状数组
struct BIT
{
    int root[N];
    void modify(int t, int x, int val)
    {
        for (; t <= n; t += t & -t)
            ::modify(root[t], 0, 1e9, x, val);
        //  ^  全局名称空间
    }
    int query(int t, int l, int r)
    {
        int ans = 0;
        for (; t; t -= t & -t)
            ans += ::query(root[t], 0, 1e9, l, r);
        return ans;
    }
} T;
struct event
{
    int x, y, t, val;
    event() {}
    event(int x, int y, int t, int val) : x(x), y(y), t(t), val(val) {}
    bool operator<(const event &rhs) const
    {
        return x < rhs.x;
    }
} E[N * 2];
struct query_t
{
    int x, yl, yr, t;
    query_t() {}
    query_t(int x, int yl, int yr, int t) : x(x), yl(yl), yr(yr), t(t) {}
    bool operator<(const query_t &rhs) const
    {
        return x < rhs.x;
    }
} Q[N];
int main()
{
    ios::sync_with_stdio(false);
    int px, py;
    cin >> n >> t >> px >> py;
    int en = 0, qn = 0;
    for (int i = 2; i <= n; i++)
    {
        int x, y;
        cin >> x >> y;
        if (y == py)
        {
            E[++en] = event(min(px, x) + 1, y, i, 1);
            E[++en] = event(max(px, x), y, i, -1);
            //本来应该为[l,r+1]，去除端点为[l+1,r]
        }
        else
            Q[++qn] = query_t(x, min(py, y) + 1, max(py, y) - 1, i);
        px = x;
        py = y;
    }
    sort(E + 1, E + en + 1);
    sort(Q + 1, Q + qn + 1);
    long long ans = 0;
    for (int i = 1, j = 1; i <= qn; i++)
    {
        for (; j <= en && E[j].x <= Q[i].x; j++)
            T.modify(E[j].t, E[j].y, E[j].val);
        if (Q[i].t - t > 0)
            ans += T.query(Q[i].t - t, Q[i].yl, Q[i].yr);
        if (Q[i].t + t <= n)
            ans += T.query(n, Q[i].yl, Q[i].yr) - T.query(Q[i].t + t - 1, Q[i].yl, Q[i].yr);
    }
    cout << ans << endl;
    return 0;
}
```

---

