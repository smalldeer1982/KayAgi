# Permutation Game

## 题目描述

After a long day, Alice and Bob decided to play a little game. The game board consists of $ n $ cells in a straight line, numbered from $ 1 $ to $ n $ , where each cell contains a number $ a_i $ between $ 1 $ and $ n $ . Furthermore, no two cells contain the same number.

A token is placed in one of the cells. They take alternating turns of moving the token around the board, with Alice moving first. The current player can move from cell $ i $ to cell $ j $ only if the following two conditions are satisfied:

- the number in the new cell $ j $ must be strictly larger than the number in the old cell $ i $ (i.e. $ a_j > a_i $ ), and
- the distance that the token travels during this turn must be a multiple of the number in the old cell (i.e. $ |i-j|\bmod a_i = 0 $ ).

Whoever is unable to make a move, loses. For each possible starting position, determine who wins if they both play optimally. It can be shown that the game is always finite, i.e. there always is a winning strategy for one of the players.

## 说明/提示

In the first sample, if Bob puts the token on the number (not position):

- $ 1 $ : Alice can move to any number. She can win by picking $ 7 $ , from which Bob has no move.
- $ 2 $ : Alice can move to $ 3 $ and $ 5 $ . Upon moving to $ 5 $ , Bob can win by moving to $ 8 $ . If she chooses $ 3 $ instead, she wins, as Bob has only a move to $ 4 $ , from which Alice can move to $ 8 $ .
- $ 3 $ : Alice can only move to $ 4 $ , after which Bob wins by moving to $ 8 $ .
- $ 4 $ , $ 5 $ , or $ 6 $ : Alice wins by moving to $ 8 $ .
- $ 7 $ , $ 8 $ : Alice has no move, and hence she loses immediately.

## 样例 #1

### 输入

```
8
3 6 5 4 2 7 1 8
```

### 输出

```
BAAAABAB
```

## 样例 #2

### 输入

```
15
3 11 2 5 10 9 7 13 15 8 4 12 6 1 14
```

### 输出

```
ABAAAABBBAABAAB
```

# 题解

## 作者：叶ID (赞：8)

题目链接：[CF1033C Permutation Game](https://www.luogu.org/problem/CF1033C)

【广告】[在个人博客食用](https://toxic2018.ml/1880/)风味更佳

****

题目大意请见题目链接中的翻译。本题解中的表述将对照这个翻译。

****

先决条件：动态规划板子题（数塔问题） | 有向无环图与拓扑排序

这是一道博弈论（研究游戏必胜策略等问题的学说）问题。

### 游戏状态

显然，游戏局面除了硬币所在的格子之外就没有别的区别了。因此，游戏状态定义为：硬币所在的格子。

### 必胜与必败状态

> It can be shown that the game is always finite, i.e. there always is a winning strategy for one of the players.

题目提到，游戏一定是有限的，即，一定有人有必胜策略。因此，如果以某个状态为 **初始状态** 时，**先手** 玩家是 **有必胜策略** 的，那么称这个状态为 **必胜状态**。否则，因为一定有一个人会有必胜策略，所以这个状态就叫做 **必败状态**。

- 硬币不能移动的状态是 **必败状态**，因为先手立刻就输了。
- 其他情况下：
  - 如果当前状态的下一步 **可以** 是 **必败状态**，那么这个状态是 **必胜状态**，因为，当前状态下，先手有决定权，因此可以将下一个 **必败状态** 留给后手。
  - 否则，即当前状态的下一步 **一定** 是 **必胜状态**，那么这个状态是 **必败状态**，因为，当前状态下，先手无论怎么走，都会将一个 **必胜状态** 留给后手。

### 实现方法 / 复杂度分析

由于硬币只能从数值小的格子移到数值大的格子，因此如果从 **当前状态** 向 **下一步能到达的状态** 连有向边，形成的一定是 **有向无环图**，其中，方格中的数字就是 **拓扑序**。

我们按拓扑序从大到小进行DP。这样，DP进行到数值小的格子时，数值大的格子一定已经完成了DP，当前格子的必胜性就可以确定。

在已知当前格子，枚举当前格子可以到达的状态时，只枚举与当前格子距离为当前格子中数值的格子（这是移动硬币的条件之一）。因为如果枚举$1..n$，时间复杂度会变成$O(n^2)$肯定会TLE

而使用只枚举倍数的方法，复杂度值是：

$\sum\limits_{i=1}^{i \leq n} \lfloor \frac{n}{a_i} \rfloor$

> Furthermore, there are no pair of indices $i \neq j$ such that $a_i = a_j$

题目提到格子中的数范围是$1..n$，且两两不同，因此，复杂度值简化为

$\sum\limits_{i=1}^{i \leq n} \lfloor \frac{n}{i} \rfloor$

如果你数学学得好，你早就知道，这个值大约是$n\cdot ln(n)$。如果你不知道，你可以用下面的程序验证。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    int n = 100000;
    int ans = 0;
    for(int i=1;i<=n;i++) {
        ans += n/i;
    }
    cout<<ans<<endl;
}

```

输出：$1166750$

因此肯定能过。

### 代码

$Talk\ is\ cheap,\ show\ me\ the\ code.$

```cpp
// status: [Accepted]
// oj:     [luogu]

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100001;
// 格子中的值 
int arr[MAXN];
// 值为i的格子编号为pos[i] 
int pos[MAXN];
// 格子是必胜(1)还是必败(0) 
int status[MAXN];

int n;

int main() {
    ios::sync_with_stdio(false);
    
    cin>>n;
    for(int i=1;i<=n;i++) cin>>arr[i];
    
    for(int i=1;i<=n;i++) {
        pos[arr[i]] = i;
    }
    
    for(int i=n;i>=1;i--) {
        int u = pos[i];
        status[u] = 0;
        int v = u;
        // 只枚举距离是倍数的 
        while(v - arr[u] > 0) v-=arr[u];
        for(;v<=n;v+=arr[u]) {
            if(!(arr[u] < arr[v])) continue;
            // 发现能到达必败状态，说明这个状态一定是必胜的。 
            if(status[v] == 0) {
                status[u] = 1; break;
            }
        }
    }
    
    // 输出结果 
    for(int i=1;i<=n;i++) {
        if(status[i]) {
            cout<<'A';
        }
        else {
            cout<<'B';
        }
    }
    cout<<endl;
}

```

评测记录：[R24491666](https://www.luogu.org/record/24491666)


---

## 作者：cosf (赞：1)

## [CF1033C](https://codeforces.com/problemset/problem/1033/C) [排列游戏](https://www.luogu.com.cn/problem/CF1033C)

## 思路

我们可以发现，如果 $i$ 到得了 $j$，那么 $j$ 就一定到不了 $i$（不可能 $a_i \lt a_j \lt a_i$）。也就是说，只要我们把所有可以走的情况各建一条边，得到的会是一个 `DAG`。

我们令 $d(i)$ 表示硬币在第 $i$ 格时先手是否必胜。

容易推导出：如果 $i$ 走不到任何其他点，那么 $d(i) = 0$。若 $i$ 能走到的点 $j$ 都有 $d(j) = 1$，那么 $d(i) = 0$。否则 $d(i) = 1$。

那么我们可以反向建边然后再拓扑一下，就可以得出所有的 $d(i)$ 了。

由于边数不会大于 $\sum\frac{n}{a_i} = \sum_{i=1}^n\frac{n}{i}$，经过计算，它完全是在合理范围内的，复杂度正确。

## 代码

```cpp
vector<int> e[MAXN];

int val[MAXN];
int in[MAXN];
int d[MAXN];

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> val[i];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i - val[i]; j >= 1; j -= val[i])
        {
            if (val[j] > val[i])
            {
                e[j].push_back(i); // 注意是反向建边
                in[i]++;
            }
        }
        for (int j = i + val[i]; j <= n; j += val[i])
        {
            if (val[j] > val[i])
            {
                e[j].push_back(i);
                in[i]++;
            }
        }
    }
    queue<int> q; // 拓扑板子
    for (int i = 1; i <= n; i++)
    {
        if (!in[i])
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int t : e[u])
        {
            d[t] |= (!d[u]); // 但凡有 d[u] = 0, d[t] = 1
            in[t]--;
            if (!in[t])
            {
                q.push(t);
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << "AB"[1 - d[i]];
    }
    cout << endl;
    return 0;
}

```


---

