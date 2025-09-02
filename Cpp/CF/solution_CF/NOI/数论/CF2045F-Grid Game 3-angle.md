# Grid Game 3-angle

## 题目描述

Anda 和 Kamu 决定玩一个叫作「网格游戏」的游戏，并请你来做裁判。作为裁判，你需要设置一个大小为 $N$ 的三角形网格。这个网格共有 $N$ 行（从 $1$ 到 $N$ 编号）。第 $r$ 行有 $r$ 个格子，第 $r$ 行的第 $c$ 个格子记作 $(r, c)$。

![示例图1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045F/d40475d9abd66fd4b8b1753d7ed7b9ab45f87e16.png)

在开始游戏前，有 $M$ 个不同的格子被选中（编号从 $1$ 到 $M$），并在格子 $(R_i, C_i)$ 上放置 $A_i$ 颗石子。随后，你给 Anda 和 Kamu 一个整数 $K$，游戏随即开始。

玩家 Anda 和 Kamu 轮流进行游戏，由 Anda 先手。每个玩家在他的回合中必须：

- 选择一个至少包含一颗石子的格子 $(r, c)$；
- 从该格子中移除至少一颗但不超过 $K$ 颗石子；
- 对于每个满足 $r + 1 \leq x \leq \min(N, r + K)$ 且 $c \leq y \leq c + x - r$ 的格子 $(x, y)$，可以向其中添加零颗或多颗，但不超过 $K$ 颗的石子。

下图显示了当 $K = 3$ 时，可以添加石子的所有可能格子。左图选择了 $(2, 1)$，右图选择了 $(4, 3)$。

![示例图2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2045F/b2d9c6a56735a1903fa39837671da9d8b4751eac.png)

无法进行有效回合（即因为没有足够的石子）的一方将输掉比赛，而对方将获胜。请判断，如果双方都采取最佳策略，谁将赢得比赛。

## 样例 #1

### 输入

```
3
2 2 4
1 1 3
2 1 2
100 2 1
4 1 10
4 4 10
10 5 2
1 1 4
3 1 2
4 2 5
2 2 1
5 3 4```

### 输出

```
Anda
Kamu
Anda```

# 题解

## 作者：YipChip (赞：3)

题链：[CF2045F - Grid Game 3-angle](https://codeforces.com/contest/2045/problem/F "F. Grid Game 3-angle")

*3000？可能没这么难，不过不妨碍他是一个神仙题，巴什博奕变种。

题目描述的已经很清楚了，就不复述一次了。

---

令 $a_i$ 表示所有 $(x, y)$ 满足 $x \equiv i \pmod {k + 1}$ 的位置上石头数量模 $k + 1$ 的异或和。

对同层考虑 $SG$ 定理，单个格子考虑巴什博奕模型。

> 定理：如果所有 $a_i$ 不全为 $0$，先手必胜，否则后手必胜。

我们尝试证明上述定理。

> 引理：如果所有 $a_i$ 均为 $0$，操作一次之后一定存在 $a_j$ 变得不为 $0$。

容易发现，对某个 $x \equiv i$ 操作后，$a_i$ 会变得非 $0$，因为操作的石子数是 $[1, k]$，模 $k + 1$ 定然会变，所以 $a_i$ 变得非 $0$ 了。我们可以给 $(x + j, y)$ 加 $[0, k]$ 个石子，其中 $j \in [1, k]$，容易发现，无法使得 $a_i$ 恢复非 $0$。

后手必然可以操作一次使得所有 $a_i$ 变回非 $0$，这是很容易看出的。

因为 $a_i$ 非 $0$，所以 $a_i$ 必定有值，后手对 $a_i$ 操作后 $a_i$ 可以归零，对于所有 $a_{(i+j) \bmod {k + 1}}(1 \le j \le k)$，如果先手给一个位置添加了 $t$，后手在相同位置添加 $k + 1 - t$ 即可。

综上，按照第一种定义，存在必胜和必败态转换，此题可以解决。

时间复杂度 $O(M \log M)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k, k = k + 1;
    map<int, int> mp;
    for (int i = 1; i <= m; i ++ )
    {
        int r, c, a;
        cin >> r >> c >> a, a %= k, r %= k;
        if (mp.count(r)) mp[r] = mp[r] ^ a;
        else mp[r] = a;
    }
    int ans = 0;
    for (auto it : mp) ans |= it.second;
    if (ans) cout << "Anda\n";
    else cout << "Kamu\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T -- ) solve();
    return 0;
}
```

---

