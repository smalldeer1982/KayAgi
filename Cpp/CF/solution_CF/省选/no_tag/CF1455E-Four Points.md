# Four Points

## 题目描述

You are given four different integer points $ p_1 $ , $ p_2 $ , $ p_3 $ and $ p_4 $ on $ \mathit{XY} $ grid.

In one step you can choose one of the points $ p_i $ and move it in one of four directions by one. In other words, if you have chosen point $ p_i = (x, y) $ you can move it to $ (x, y + 1) $ , $ (x, y - 1) $ , $ (x + 1, y) $ or $ (x - 1, y) $ .

Your goal to move points in such a way that they will form a square with sides parallel to $ \mathit{OX} $ and $ \mathit{OY} $ axes (a square with side $ 0 $ is allowed).

What is the minimum number of steps you need to make such a square?

## 说明/提示

In the first test case, one of the optimal solutions is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1455E/5bb30aae8e24a4fb2bdb37b4e76c6f754c091920.png) Each point was moved two times, so the answer $ 2 + 2 + 2 + 2 = 8 $ .In the second test case, one of the optimal solutions is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1455E/b627822a9e229b004b021331548ea1f11bf28bdc.png) The answer is $ 3 + 1 + 0 + 3 = 7 $ .In the third test case, one of the optimal solutions is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1455E/bc66512f74b52d3a55695e509404022e7c147fd3.png) The answer is $ 1 + 1 + 2 + 1 = 5 $ .

## 样例 #1

### 输入

```
3
0 2
4 2
2 0
2 4
1 0
2 0
4 0
6 0
1 6
2 2
2 5
4 1```

### 输出

```
8
7
5```

# 题解

## 作者：OMG_wc (赞：16)

设移到最终正方形左上角的起始点为 $(x_0,y_0)$，右上角为 $(x_1,y_1)$，左下角为 $(x_2,y_2)$，右下角为 $(x_3,y_3)$。

因为读入的四个点和这四个起点对应关系不明确，但我们可以枚举这 $4!$ 种可能。

现在确定了对应关系后，可以把两个维度单独处理，他们之间唯一的联系是**正方形的边长**。

以横坐标为例，最终正方形的两个横坐标设为 $T_1,T_2$，那么很显然 $T_1$ 在 $x_0$ 和 $x_2$ 之间时移动距离最少，为 $|x_0-x_2|$。

如果不在 $x_0$ 和 $x_2$ 之间，每超过边界 $1$ 个单位距离，就会多移动两步。

同理，$T_2$ 在 $x_1$ 和 $x_3$ 之间是最优的。当同时满足在这两个范围内时，移动总步数为 $|x_0-x_2|+|x_1-x_3|$，此时正方形边长在一个区间 $[l_1,r_1]$ 内，可以算出来 $r_1=\max(x_1, x_3) - \min(x_0, x_2), l_1 = \min(x_1, x_3) - \max(x_0, x_2)$。

同样地考虑纵坐标，可以算出来边长在 $[l_2,r_2]$ 内可以达到最优。

若 $[l_1,r_1]$ 和 $[l_2,r_2]$ 有交集，那么最小步数就为 $|x_0-x_2|+|x_1-x_3|+|y_0-y_1|+|y_2-y_3|$，否则让其中一维迁就另外一维，也就是多出来 $2*(\max(l_1, l_2) - \min(r_1, r_2))$ 的步数。

代码如下：

```c++
int a[4], b[4], c[4];
int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        for (int i = 0; i < 4; i++) {
            scanf("%d%d", &a[i], &b[i]);
            c[i] = i;
        }
        LL ans = 1e18;
        while (1) {
            LL x0 = a[c[0]], y0 = b[c[0]];
            LL x1 = a[c[1]], y1 = b[c[1]];
            LL x2 = a[c[2]], y2 = b[c[2]];
            LL x3 = a[c[3]], y3 = b[c[3]];
            LL now = abs(x0 - x2) + abs(x1 - x3) + abs(y0 - y1) + abs(y2 - y3);
            LL r1 = max(x1, x3) - min(x0, x2), l1 = min(x1, x3) - max(x0, x2);
            LL r2 = max(y0, y1) - min(y2, y3), l2 = min(y0, y1) - max(y2, y3);
            now += 2 * max(0LL, max(l1, l2) - min(r1, r2));
            if (r1 >= 0 && r2 >= 0)
                ans = min(ans, now);
            if (next_permutation(c, c + 4) == 0) break;
        }
        cout << ans << endl;
    }
    return 0;
}
```



---

## 作者：subcrip (赞：2)

一个不太一样的思路。

设第 $i$ 个点的坐标是 $(x_i,y_i)$。

我们首先尝试将横坐标和纵坐标独立处理。也就是说，在两个维度的每一个上，让这四个点聚成两堆。这样就有一个很显然的做法：不妨设 $x_i\leqslant x_{i+1}$，则当边长在 $[x_2-x_1,x_3-x_0]$ 范围内时，我们可以把 $x_0$ 跟 $x_1$ 放在一堆，而 $x_2$ 和 $x_3$ 放在另一堆。这样只需要代价 $(x_1-x_0)+(x_3-x_2)$。容易证明这样是最优的。对于 $y$ 也是同样的策略。

所以考虑将 $x$ 数组和 $y$ 数组分别排序，然后看区间 $[x_2-x_1,x_3-x_0]$ 与 $[y_2-y_1,y_3-y_0]$ 有没有重合，如果有，就可以取那个公共的边长，然后得到最优解；如果没有，则需要补足这两个区间的距离 $\delta$，可以是最大值较小的那维增加 $2\times\delta$。

但这样有一个问题，就是四个点缩成了对角的两个点。这种情况发生的条件就是有两个点既作为 $x$ 维上最小的两个点，也作为 $y$ 维上最小的两个点，这样它们就会在 $x$ 和 $y$ 方向上都缩成一个点，而另外两个点又缩成第二个点，这样就只剩两个不同的点了，不构成正方形。这种情况下，只要让 $x$ 和 $y$ 中的其中一维（例如 $x$）改为 $x_2$ 和 $x_0$ 凑一堆、$x_1$ 和 $x_3$ 凑一堆即可。

Code:

```cpp
void solve() {
    readvec(pll, a, 4);
    ll res = INFLL;
    for (int i = 0; i < 2; ++i) {
        sort(a.begin(), a.end());
        ll x_min, x_max, y_min, y_max, base;
        if (max(a[0].second, a[1].second) <= min(a[2].second, a[3].second)) {
            x_min = a[2].first - a[1].first, x_max = a[3].first - a[0].first;
            y_min = 0, y_max = max(a[2].second, a[3].second) - min(a[1].second, a[0].second);
            base = a[1].first - a[0].first + a[3].first - a[2].first + a[2].second + a[3].second - a[0].second - a[1].second;
        } else if (min(a[0].second, a[1].second) >= max(a[2].second, a[3].second)) {
            x_min = a[2].first - a[1].first, x_max = a[3].first - a[0].first;
            y_min = 0, y_max = max(a[1].second, a[0].second) - min(a[2].second, a[3].second);
            base = a[1].first - a[0].first + a[3].first - a[2].first - a[2].second - a[3].second + a[0].second + a[1].second;
        } else {
            vector<ll> b(4);
            transform(a.begin(), a.end(), b.begin(), expr(p.second, auto&& p));
            sort(b.begin(), b.end());
            x_min = a[2].first - a[1].first, x_max = a[3].first - a[0].first;
            y_min = b[2] - b[1], y_max = b[3] - b[0];
            base = a[1].first - a[0].first + a[3].first - a[2].first + b[1] - b[0] + b[3] - b[2];
        }
        if (x_min > y_max) {
            chmin(res, base + 2 * (x_min - y_max));
        } else if (y_min > x_max) {
            chmin(res, base + 2 * (y_min - x_max));
        } else {
            chmin(res, base);
        }
        for (int j = 0; j < 4; ++j) {
            swap(a[j].first, a[j].second);
        }
    }
    cout << res << '\n';
}
```

---

## 作者：analysis (赞：1)

本题解中的坐标系是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/sf8ro05f.png)

---

显然，我们可以通过枚举的方式确定四个点的顺序。

假设四点从左上角开始按顺时针方向排序分别为 $P_0$、$P_1$、$P_3$、$P_2$。

确定了四个点的顺序，我们还需要**左上角点的坐标**和**正方形边长**才能确定一个正方形。

显然，我们需要对上述两个条件进行合理的确定以求出最优解。

直接对于四个点两个维度讨论是麻烦的，我们可以分别讨论每个维度。

- 讨论 $y$

假设左上角的横坐标为 $y$，边长为 $w$，则移动距离即为：

$$
|y_0 - y| + |y_2 - y| + |y_1 - (y+w)| + |y_3-(y+w)|
$$

显然，若要令上述值最小，$y$ 应在 $y_0$ 与 $y_2$ 间，$y+w$ 应在 $y_1$ 与 $y_3$ 间。

此时步数为 $|y_0 - y_2| + |y_1 - y_3|$。

- 讨论 $x$

同理，若要令上述值最小，$x$ 应在 $x_0$ 与 $x_1$ 间，$x+w$ 应在 $x_2$ 与 $x_3$ 间。

此时步数为 $|x_0 - x_1| + |x_2 - x_3|$。

显然我们要把上述两个讨论和在一起。我们可以任意设置 $x$、$y$、$w$ 的值，很轻松地可以满足其中三个条件：

1.$y$ 应在 $y_0$ 与 $y_2$ 间

2.$x$ 应在 $x_0$ 与 $x_1$ 间

3.$y+w$ 应在 $y_1$ 与 $y_3$ 间

如果此时恰好满足了 $x+w$ 应在 $x_2$ 与 $x_3$ 间的限制那自然是极好的，但如果没有完成呢？

应该移动 $x_2$ 与 $x_3$，让他去适应我们的决策，移动距离应为 $\min(x_2-(x+w),x_3-(x+w))$。

可以发现，这是最优的解法，因为任意条件不满足都需要移动两个点，是等价的。

此时，基础贡献（即把对应的点放到同一条线上的最小代价）为：

$$
|y_0 - y_2| + |y_1 - y_3| + |x_0 - x_1| + |x_2 - x_3|
$$

于是，通过 $y$ 计算出 $w$ 的取值范围，进而计算出合法 $x + w$ 的取值范围，然后计算额外贡献即可。

具体解释可以看代码。

时间复杂度瓶颈在于枚举四个点的顺序，共为 $O(Ta!)$，$a=4$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int x[4],y[4];
bool ch[4];
int xx[4],yy[4];
int ans;
void state(int pos)
{
    if(pos == 4)
    {
        int wmx = max(yy[1],yy[3]) - min(yy[0],yy[2]),wmn = min(yy[1],yy[3]) - max(yy[0],yy[2]);
        //w的取值范围
        int xmx = max(xx[0],xx[1]),xmn = min(xx[0],xx[1]);
        xmx = xmx + wmx,xmn = xmn + wmn;
        //x+w的取值范围
        int res = abs(yy[1] - yy[3]) + abs(yy[0] - yy[2]) + abs(xx[2] - xx[3]) + abs(xx[0] - xx[1]);
        //基础贡献
        int nmx = max(xx[2],xx[3]),nmn = min(xx[2],xx[3]);
        if(nmn > xmx || nmx < xmn)
        {
            if(nmn > xmx)res += 2 * (nmn - xmx);
            else res += 2 * (xmn - nmx);
        }
        //额外贡献，每次移动两个点，所以要乘2
        ans = min(ans,res);
        return;
    }
    for(int i=0;i<4;i++)
    {
        if(!ch[i])
        {
            xx[pos] = x[i];
            yy[pos] = y[i];
            ch[i] = 1;
            state(pos+1);
            ch[i] = 0;
        }
    }
}
void sol()
{
    ans = 1e18;
    for(int i=0;i<4;i++)cin >> x[i] >> y[i],ch[i] = 0;
    state(0);
    cout<<ans<<'\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--)sol();
    return 0;
}
```

---

