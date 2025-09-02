# Accumulator Apex

## 题目描述

Allyn is playing a new strategy game called "Accumulator Apex". In this game, Allyn is given the initial value of an integer $ x $ , referred to as the accumulator, and $ k $ lists of integers. Allyn can make multiple turns. On each turn, Allyn can withdraw the leftmost element from any non-empty list and add it to the accumulator $ x $ if the resulting $ x $ is non-negative. Allyn can end the game at any moment. The goal of the game is to get the largest possible value of the accumulator $ x $ . Please help Allyn find the largest possible value of the accumulator $ x $ they can get in this game.

## 说明/提示

In the first input, we start with $ x = 1 $ . Then, we can take the first integer from the first list and get $ x = 0 $ — adding the next integer $ 2 $ from the first list we get $ x = 2 $ . After that, we can add the integers from the second list and obtain $ x = 3 $ . Finally, we can add the integers from the third list and obtain $ x = 4 $ .

In the second input, we can add the first integer from the second list and get $ x = 2 $ . Then, by adding the elements from the first list, we get $ x = 4 $ . We cannot add more integers to increase $ x $ .

## 样例 #1

### 输入

```
1 3
2 -1 2
2 -2 3
2 -3 4```

### 输出

```
4```

## 样例 #2

### 输入

```
1 2
3 -1 -1 4
4 1 -3 -4 8```

### 输出

```
4```

# 题解

## 作者：ylch (赞：3)

[Luogu - CF1912A](https://www.luogu.com.cn/problem/CF1912A)
## 思路
考虑贪心，看到这道题的第一反应该是对原始数列进行合并，把相邻的正数合并在一起，把相邻的负数合并在一起。

这样每个数列都变为一正一负、一正一负……的形式。

可能会想到先吃每个数列开头的正数，然后按找负数排序，每次都找绝对值最小的那个负数吃。

但这样是不对的，假设当前 $x=30$，一个数列为 $[-15,45]$，另一个为 $[-3,2]$，按照上面的策略，应该选第二个数列，但显然选第一个数列才是最优的。

还有一种情况，假设 $x=3$，只有一个数列 $[-3,1]$，如果盲目选它的话会导致原来的 $x=3$ 变成 $x=1$，收益不增反降。

正确思路为对每一个数列都求前缀和 $s$，每次取完数字后找到 当前取数位置后第一个前缀和大于 $0$ 的位置（即第一个 $s_i>0$），那个位置就是我们要达到的目标（因为前缀和大于 $0$ 意味着收益为正，我们可以回本）。

根据上面，可以把每一个数列按照前缀和分成若干段，保证每一段的结尾都是前一段结束后的第一个前缀和大于 $0$ 的位置。

由此，对每个数列分成的每一段赋予其一个数对 $(a,b)$，表示可以付出 $a$ 的代价，获得 $b$ 的收益。
 - 代价应该是当前段的**最小**前缀和（因为如果有多个负数的话，只要考虑最小的那一个——也就是影响最大的那一个就行），$b$ 就是第一个大于 $0$ 的前缀和值。

- 注意此时的 $a$ 应该小于等于 $0$（当数列第一个数就为正数时，$a=0$），$b$ 应该大于 $0$，这样才符合代价-贡献的基本要求。如果所有 $b$ 都小于 $0$，说明当前 $x$ 已经为最优，不必继续计算。

根据上面的数对，用优先队列排序后（第一关键字按照 $a$ 的绝对值升序排序，因为代价越小越好；第二关键字按照 $b$ 降序排序，因为贡献越大越好）模拟取数过程：
  1. 找到当前的队头，判断当前的 $x$ 能否获取。
  2. - 如果能，那么更新当前的 $x$，继续计算前缀和，找到第一个大于 $0$ 的前缀和继续放入优先队列。
     - 不能取的话，不做处理。
  3. 弹出当前的队头，因为它已经在步骤 $1$ 中使用过了（因为我们排过序了，此时的队头一定是最优的，无法取出的话直接出队即可）。

设所有列表长度之和为 $n$，则时间复杂度 $O(n\log n)$。

## Code
```cpp
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;

struct P
{
    ll a, b; // 付出a的代价，获得b的收益 a<=0,b>0
    int id; // 表示在a数组中的编号
    friend bool operator < (const P &p1, const P &p2)
    {
        if (abs(p1.a) != abs(p2.a))
            return abs(p1.a) > abs(p2.a); // 默认按照 绝对值 升序排序
        // 原来是abs(p1.a)<abs(p2.a)，但因为优先队列默认大顶堆，所以要反过来
        
        return p1.b < p2.b; // 否则按照收益 降序排序，即收益越大越靠前
        // 原来是p1.b > p2.b，但因为优先队列默认大顶堆，所以要反过来
    }
};

void solve()
{
    int x, k;
    cin >> x >> k;
    vector< vector<int> > a(k + 1); // 存储所有数列
    vector <int> pos(k + 1); // 每个数列的指针，表示当前前缀和统计到哪个位置了
    vector< vector<ll> > s(k + 1); // 前缀和数组

    for (int i = 1, y; i <= k; i ++)
    {
        cin >> y;
        a[i].resize(y + 1), s[i].resize(y + 1);
        for (int j = 1; j <= y; j ++) cin >> a[i][j];
    }

    priority_queue <P> Q; // 存储代价和贡献的队列
    for (int i = 1; i <= k; i ++)
    {
        ll minn = a[i][1]; // 存储过程中的最小前缀和
        for (int j = 1; j < a[i].size(); j ++)
        {
            s[i][j] = s[i][j - 1] + a[i][j];
            minn = min(minn, s[i][j]);
            if (s[i][j] > 0)
            {
                Q.push({minn, s[i][j], i});
                pos[i] = j;
                break;
            }
        }
    }

    ll temp = x; // 替代变量
    while (!Q.empty())
    {
        P it = Q.top(); Q.pop();
        if (temp + it.a >= 0) // 注意a此时应为<=0的数
        {
            temp += it.b; // 直接加上收益即可
            int i = it.id;
            ll minn = s[i][pos[i]];
            for (int j = pos[i] + 1; j < a[i].size(); j ++)
            {
                if (j == pos[i] + 1) s[i][j] = a[i][j]; // 注意要以大于0的前缀和为界分段，所以计算每一段的前缀和是独立的，不能接着s[i][j-1]计算。要单独开一个新前缀和
                else s[i][j] = s[i][j - 1] + a[i][j];
                minn = min(minn, s[i][j]);

                if (s[i][j] > 0)
                {
                    Q.push({minn, s[i][j], i});
                    pos[i] = j;
                    break;
                }
            }
        }
    }
    cout << temp << endl;
}

signed main()
{
    ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}
```

---

