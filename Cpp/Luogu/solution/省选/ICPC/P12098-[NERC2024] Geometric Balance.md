# [NERC2024] Geometric Balance

## 题目描述

Peter 的弟弟 Ivan 喜欢和一只小乌龟玩耍。这只乌龟是一种特殊的玩具，它生活在平面上，能够执行三种指令：

- 逆时针旋转 $a$ 度；
- 沿当前朝向绘制 $d$ 个单位长度的线段，并留下墨迹。平面上的任意线段最多只会被涂墨一次；
- 沿当前朝向移动 $d$ 个单位长度，但不留下任何痕迹。

Ivan 刚刚学会使用指南针，因此他只会让乌龟朝向八个基本方向或次方向旋转（旋转角度 $a$ 总是 $45$ 的倍数）。此外，他至少会发出一条 $\texttt{draw}$ 指令。

Peter 记录了 Ivan 给乌龟下达的所有指令。他觉得乌龟绘制出的图案非常可爱。现在 Peter 想知道一个最小的正角度 $b$，使得他可以进行如下操作：将乌龟移动到任意位置，将其旋转 $b$ 度，然后按原顺序重新执行全部指令，最终绘制出的图案与原图案完全一致。

你能帮 Peter 找出这个最小的角度 $b$ 吗？

注意，如果两幅图在平面上被墨迹覆盖的点集合相同，则认为它们是**相同**的图案。

## 样例 #1

### 输入

```
1
draw 10```

### 输出

```
180```

## 样例 #2

### 输入

```
7
draw 1
rotate 90
draw 1
rotate 90
draw 1
rotate 90
draw 1```

### 输出

```
90```

## 样例 #3

### 输入

```
3
draw 1
move 1
draw 2```

### 输出

```
360```

# 题解

## 作者：沉石鱼惊旋 (赞：2)

# 前言

- <https://www.luogu.com.cn/problem/P12098>
- <https://codeforces.com/contest/2052/problem/G>

晚自习在机房随机开洛谷最后一页的题，开到了这个题，看了一眼发现会了，结果 CF 评了个 2800 洛谷评紫。为了证明这个题不值 2800，我写了，被创烂了。寄。

# 题意

给定 $n$ 次操作，分别是以下三类：`rotate x`，`draw x`，`move x`。

- `rorate x` 表示把你的朝向逆时针转 $x^\circ$；保证 $45\leq x\leq 360$ 且 $45\mid x$。

- `draw x` 表示从当前位置往前走 $x$ 的单位距离且给路径染色；保证 $1\leq x\leq 10^9$。

- `move x` 表示从当前位置往前走 $x$ 的单位距离；保证 $1\leq x\leq 10^9$。

$n$ 次操作。保证没有一个线段被重复染色。`draw` 操作的个数不多于 $2000$ 个不少于 $1$ 个。

平面上会先进行这 $n$ 此操作，得到一个图形。

找一个最小正整数 $d$ 满足你可以找到一个位置旋转 $d^\circ$ 后开始操作，使得新图形和原图形染色的点集相同（即完美重合）。

# 做法

显然答案只有 $45$ 的倍数，只有 $8$ 个，可以都试一遍。但是官方题解指出尝试 $45^\circ,90^\circ,180^\circ,360^\circ$ 即可。不过无伤大雅，常数的差距而已。

由于 $x$ 很大我们肯定不能把点集直接搞出来。

考虑维护构成图形的线段。

如果给新图形设一个偏移量，满足新图形的每个线段移动这一段偏移量，可以与旧图形的线段一一对应，说明这个新图形可以与旧图形完美重合。

注意这里线段会有端点重合的情况，如果有端点重合，我们需要合并。

具体的，我们可以维护每个端点 $d^\circ$ 方向走到的下一个线段。每次找前驱后继最后拼起来。

 还有个事情是走 $45^\circ$ 的对角线，最后停留的坐标不一定是整数位置，而是 $a+b\sqrt 2$ 的形式。

不妨扩域一下维护 $a,b$。对角线走 $l$ 相当于横着竖着各走 $\frac{l\sqrt 2}{2}$。根据角度分类讨论一下符号问题。

注意这里分数分母始终为 $2$，为了避免写分数类或者丢精度（其实这里精度应该很够的？）统一给 $l\gets l\times 2$。

对于这个偏移量，我们不妨就把线段集合内最左上的端点拿出来。

但是你发现找左上会导致计算 $a+b\sqrt 2$ 然后比较大小的问题。直接写这里也没问题，精度足够。但其实我们按 $(a,b)$ 排序然后取最小的一组 $(a,b)$ 也显然正确。

---

可能这些东西都不是很难被想到，但是这个题确实有点难写了，稍微补几个坑点。

一个是读题问题，WA on 6 是

```plain
16
rotate 45
move 3
rotate 270
move 7
rotate 45
move 1
rotate 90
move 1
draw 4
rotate 180
move 5
rotate 180
draw 1
move 5
rotate 180
draw 1
```

这个点挂了。这个点卡的是 `DRAW` 没有移动自己的位置。这个能过样例也是无敌了。

然后是

```plain
2
draw 2
draw 1
```

和

```plain
2
draw 1
draw 2
```

这种，需要注意线段合并的问题。

# 代码

<https://www.luogu.com.cn/record/213013994>

<https://codeforces.com/contest/2052/submission/314897989>

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
struct sqrt2
{
    ll x, y; // x + y * sqrt(2)
    sqrt2(ll a = 0, ll b = 0) { x = a, y = b; }
    ld calc() { return x + y * sqrtl(2); }
};
sqrt2 sq(sqrt2 a) { return {a.x * a.x + a.y * a.y, 2 * a.x * a.y}; }
sqrt2 operator+(sqrt2 a, sqrt2 b) { return {a.x + b.x, a.y + b.y}; }
sqrt2 operator-(sqrt2 a, sqrt2 b) { return {a.x - b.x, a.y - b.y}; }
bool operator<(sqrt2 a, sqrt2 b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
// bool operator<(sqrt2 a, sqrt2 b) { return a.calc() < b.calc(); }
bool operator==(sqrt2 a, sqrt2 b) { return a.x == b.x && a.y == b.y; }
int n;
struct OP
{
    string op;
    int x;
} q[50020];
struct point
{
    sqrt2 x, y;
    point(sqrt2 a = {0, 0}, sqrt2 b = {0, 0}) { x = a, y = b; }
};
point operator-(point a, point b) { return {a.x - b.x, a.y - b.y}; }
bool operator<(point a, point b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
bool operator==(point a, point b) { return a.x == b.x && a.y == b.y; }
struct line
{
    point s, t;
    line(point a = {{0, 0}, {0, 0}}, point b = {{0, 0}, {0, 0}}) { s = a, t = b; }
    sqrt2 calc() { return sq(s.x - t.x) + sq(s.y - t.y); }
};
bool operator==(line a, line b) { return a.s == b.s && a.t == b.t; }
bool operator<(line a, line b) { return a.s == b.s ? a.t < b.t : a.s < b.s; }
// bool operator<(line a, line b) { return a.calc() == b.calc() ? a.s == b.s ? a.t < b.t : a.s < b.s : a.calc() < b.calc(); }
vector<line> s;
vector<line> t;
void print(point p, char c)
{
    printf("(%d + %d sqrt2, %d + %d sqrt2)\n", p.x.x, p.x.y, p.y.x, p.y.y);
    putchar(c);
}
point mv(point p, int deg, int len)
{
    len *= 2;
    if (deg == 0)
        p.y = p.y + (sqrt2){len, 0};
    else if (deg == 45)
        p.x = p.x - (sqrt2){0, len >> 1}, p.y = p.y + (sqrt2){0, len >> 1};
    else if (deg == 90)
        p.x = p.x - (sqrt2){len, 0};
    else if (deg == 135)
        p.x = p.x - (sqrt2){0, len >> 1}, p.y = p.y - (sqrt2){0, len >> 1};
    else if (deg == 180)
        p.y = p.y - (sqrt2){len, 0};
    else if (deg == 225)
        p.x = p.x + (sqrt2){0, len >> 1}, p.y = p.y - (sqrt2){0, len >> 1};
    else if (deg == 270)
        p.x = p.x + (sqrt2){len, 0};
    else if (deg == 315)
        p.x = p.x + (sqrt2){0, len >> 1}, p.y = p.y + (sqrt2){0, len >> 1};
    return p;
}
void solve(vector<line> &s, int deg)
{
    point t = {{0, 0}, {0, 0}};
    for (int i = 1; i <= n; i++)
    {
        if (q[i].op == "rotate")
        {
            (deg += q[i].x) %= 360;
        }
        else if (q[i].op == "draw")
        {
            auto e = mv(t, deg, q[i].x);
            s.push_back({t, e});
            t = e;
        }
        else
        {
            t = mv(t, deg, q[i].x);
        }
    }
}
int getdeg(point a, point b)
{
    if (a.x == b.x && a.y == b.y)
        return 0;
    if (a.x == b.x)
        return a.y < b.y ? 0 : 180;
    if (a.y == b.y)
        return a.x < b.x ? 270 : 90;
    if (a.x < b.x)
        return a.y < b.y ? 315 : 225;
    return a.y < b.y ? 45 : 135;
}
void solve(vector<line> &s)
{
    map<int, map<point, point>> prv;
    map<int, map<point, point>> nxt;
    map<line, bool> del;
    for (auto &[Pa, Pb] : s)
    {
        if (!(Pa < Pb))
            swap(Pa, Pb);
    }
    sort(s.begin(), s.end());
    for (auto [Pa, Pb] : s)
        nxt[getdeg(Pa, Pb)][Pa] = Pb, prv[getdeg(Pb, Pa)][Pb] = Pa;
#ifdef LOCAL_DEBUG
    cout << "solve" << '\n';
    for (auto [Pa, Pb] : s)
    {
        print(Pa, ' ');
        print(Pb, '\n');
        cout << getdeg(Pa, Pb) << ' ' << getdeg(Pb, Pa) << '\n';
    }
#endif

    auto dfs = [&](auto self, point s, map<point, point> &mp) -> point
    {
        if (mp.count(s))
            return self(self, mp[s], mp);
        return s;
    };
    vector<line> t;
    for (auto &[Pa, Pb] : s)
    {
        if (del[{Pa, Pb}])
            continue;
        auto st = dfs(dfs, Pa, prv[getdeg(Pb, Pa)]);
        auto ed = dfs(dfs, Pb, nxt[getdeg(Pa, Pb)]);
#ifdef LOCAL_DEBUG
        cout << "rem: " << '\n';
        print(st, ' ');
        print(ed, '\n');
#endif
        int deg = getdeg(Pa, Pb);
        t.push_back({st, ed});
        while (!(st == ed))
        {
            del[{st, nxt[deg][st]}] = 1;
            st = nxt[deg][st];
        }
    }
    s = t;
    auto p = s[0].s;
    for (auto &[Pa, Pb] : s)
    {
        if (Pa < p)
            p = Pa;
        if (Pb < p)
            p = Pb;
    }
#ifdef LOCAL_DEBUG
    cout << "min" << '\n';
    print(p, '\n');
#endif
    for (auto &[Pa, Pb] : s)
    {
        Pa = Pa - p, Pb = Pb - p;
        if (!(Pa < Pb))
            swap(Pa, Pb);
    }
    sort(s.begin(), s.end());
}
bool same(vector<line> &s, vector<line> &t)
{
    if (s.size() != t.size())
        return 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (!(s[i] == t[i]))
            return 0;
    }
    return 1;
}
int main()
{
#ifndef LOCAL_DEBUG
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#endif
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> q[i].op >> q[i].x;
    solve(s, 0);
    solve(s);
#ifdef LOCAL_DEBUG
    cout << 0 << '\n';
    for (auto [pa, pb] : s)
    {
        print(pa, ' ');
        print(pb, '\n');
    }
#endif
    for (int deg = 45; deg < 360; deg += 45)
    {
        t.clear();
        solve(t, deg);
        solve(t);
#ifdef LOCAL_DEBUG
        cout << deg << '\n';
        for (auto [pa, pb] : t)
        {
            print(pa, ' ');
            print(pb, '\n');
        }
#endif
        if (same(s, t))
            return cout << deg << '\n', 0;
    }
    cout << 360 << '\n';
    return 0;
}
```

---

