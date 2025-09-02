# 题目信息

# Game with Marbles (Hard Version)

## 题目描述

The easy and hard versions of this problem differ only in the constraints on the number of test cases and $ n $ . In the hard version, the number of test cases does not exceed $ 10^4 $ , and the sum of values of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . Furthermore, there are no additional constraints on $ n $ in a single test case.

Recently, Alice and Bob were given marbles of $ n $ different colors by their parents. Alice has received $ a_1 $ marbles of color $ 1 $ , $ a_2 $ marbles of color $ 2 $ ,..., $ a_n $ marbles of color $ n $ . Bob has received $ b_1 $ marbles of color $ 1 $ , $ b_2 $ marbles of color $ 2 $ , ..., $ b_n $ marbles of color $ n $ . All $ a_i $ and $ b_i $ are between $ 1 $ and $ 10^9 $ .

After some discussion, Alice and Bob came up with the following game: players take turns, starting with Alice. On their turn, a player chooses a color $ i $ such that both players have at least one marble of that color. The player then discards one marble of color $ i $ , and their opponent discards all marbles of color $ i $ . The game ends when there is no color $ i $ such that both players have at least one marble of that color.

The score in the game is the difference between the number of remaining marbles that Alice has and the number of remaining marbles that Bob has at the end of the game. In other words, the score in the game is equal to $ (A-B) $ , where $ A $ is the number of marbles Alice has and $ B $ is the number of marbles Bob has at the end of the game. Alice wants to maximize the score, while Bob wants to minimize it.

Calculate the score at the end of the game if both players play optimally.

## 说明/提示

In the first example, one way to achieve a score of $ 1 $ is as follows:

1. Alice chooses color $ 1 $ , discards $ 1 $ marble. Bob also discards $ 1 $ marble;
2. Bob chooses color $ 3 $ , discards $ 1 $ marble. Alice also discards $ 1 $ marble;
3. Alice chooses color $ 2 $ , discards $ 1 $ marble, and Bob discards $ 2 $ marble.

As a result, Alice has $ a = [3, 1, 0] $ remaining, and Bob has $ b = [0, 0, 3] $ remaining. The score is $ 3 + 1 - 3 = 1 $ .

It can be shown that neither Alice nor Bob can achieve a better score if both play optimally.

In the second example, Alice can first choose color $ 1 $ , then Bob will choose color $ 4 $ , after which Alice will choose color $ 2 $ , and Bob will choose color $ 3 $ . It can be shown that this is the optimal game.

## 样例 #1

### 输入

```
5
3
4 2 1
1 2 4
4
1 20 1 20
100 15 10 20
5
1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1
3
5 6 5
2 1 7
6
3 2 4 2 5 5
9 4 7 9 2 5```

### 输出

```
1
-9
2999999997
8
-6```

# AI分析结果

### 题目内容重写（中文）

# 弹珠游戏（困难版）

## 题目描述

这个问题的简单版和困难版仅在测试用例的数量和 $n$ 的约束上有所不同。在困难版中，测试用例的数量不超过 $10^4$，且所有测试用例的 $n$ 值之和不超过 $2 \cdot 10^5$。此外，单个测试用例中的 $n$ 没有额外限制。

最近，Alice 和 Bob 从他们的父母那里得到了 $n$ 种不同颜色的弹珠。Alice 收到了 $a_1$ 个颜色为 $1$ 的弹珠，$a_2$ 个颜色为 $2$ 的弹珠，……，$a_n$ 个颜色为 $n$ 的弹珠。Bob 收到了 $b_1$ 个颜色为 $1$ 的弹珠，$b_2$ 个颜色为 $2$ 的弹珠，……，$b_n$ 个颜色为 $n$ 的弹珠。所有的 $a_i$ 和 $b_i$ 都在 $1$ 到 $10^9$ 之间。

经过一番讨论，Alice 和 Bob 提出了以下游戏：玩家轮流进行，Alice 先开始。轮到某个玩家时，他选择一个颜色 $i$，使得双方都至少有一个该颜色的弹珠。然后该玩家丢弃一个颜色为 $i$ 的弹珠，而对方则丢弃所有颜色为 $i$ 的弹珠。当没有颜色 $i$ 使得双方都至少有一颗该颜色的弹珠时，游戏结束。

游戏的得分是游戏结束时 Alice 剩余的弹珠数与 Bob 剩余的弹珠数之差。换句话说，游戏的得分等于 $(A-B)$，其中 $A$ 是 Alice 拥有的弹珠数，$B$ 是游戏结束时 Bob 拥有的弹珠数。Alice 希望得分最大化，而 Bob 希望得分最小化。

计算双方都采取最优策略时，游戏结束时的得分。

## 说明/提示

在第一个示例中，得分为 $1$ 的一种可能方式如下：

1. Alice 选择颜色 $1$，丢弃 $1$ 个弹珠。Bob 也丢弃 $1$ 个弹珠；
2. Bob 选择颜色 $3$，丢弃 $1$ 个弹珠。Alice 也丢弃 $1$ 个弹珠；
3. Alice 选择颜色 $2$，丢弃 $1$ 个弹珠，Bob 丢弃 $2$ 个弹珠。

最终，Alice 剩余的弹珠为 $a = [3, 1, 0]$，Bob 剩余的弹珠为 $b = [0, 0, 3]$。得分为 $3 + 1 - 3 = 1$。

可以证明，如果双方都采取最优策略，Alice 和 Bob 都无法获得更好的得分。

在第二个示例中，Alice 可以先选择颜色 $1$，然后 Bob 选择颜色 $4$，接着 Alice 选择颜色 $2$，Bob 选择颜色 $3$。可以证明这是最优的游戏策略。

## 样例 #1

### 输入

```
5
3
4 2 1
1 2 4
4
1 20 1 20
100 15 10 20
5
1000000000 1000000000 1000000000 1000000000 1000000000
1 1 1 1 1
3
5 6 5
2 1 7
6
3 2 4 2 5 5
9 4 7 9 2 5```

### 输出

```
1
-9
2999999997
8
-6```

### 题解分析与结论

本题的核心在于理解双方的最优策略，即每次选择对双方影响最大的颜色进行操作。通过贪心算法，按照 $a_i + b_i$ 的值从大到小排序，模拟双方的轮流操作，最终计算得分。

### 精选题解

#### 1. 作者：abensyl (赞：2)
- **星级**: 4
- **关键亮点**: 使用优先队列（大根堆）进行贪心排序，时间复杂度为 $O(n\log n)$，思路清晰，代码简洁。
- **代码核心思想**: 将 $a_i + b_i$ 压入优先队列，每次取出堆顶元素，根据回合的奇偶性更新得分。

```cpp
priority_queue<pii> pq;
rep(i,1,n) pq.push({a[i]+b[i],i});
rep(i,1,n) {
    if(i%2) sc+=a[pq.top().second]-1;
    else sc-=b[pq.top().second]-1;
    pq.pop();
}
```

#### 2. 作者：Erica_N_Contina (赞：1)
- **星级**: 4
- **关键亮点**: 明确解释了双方的最优策略，通过结构体存储 $a_i$ 和 $b_i$，并按 $a_i + b_i$ 排序，模拟双方操作。
- **代码核心思想**: 使用结构体存储 $a_i$ 和 $b_i$，排序后根据回合的奇偶性更新得分。

```cpp
struct node{ int a,b,c; }t[N];
bool cmp(node x,node y){return x.c>y.c;}
for(int i=1;i<=n;i++){
    if(i&1) ans+=t[i].a-1;
    else ans-=t[i].b-1;
}
```

#### 3. 作者：ThySecret (赞：0)
- **星级**: 4
- **关键亮点**: 通过结构体存储 $a_i$ 和 $b_i$，并排序后模拟双方操作，思路清晰，代码可读性强。
- **代码核心思想**: 使用结构体存储 $a_i$ 和 $b_i$，排序后根据回合的奇偶性更新得分。

```cpp
struct Node{ int a,b,idx; };
bool operator < (const Node &u) const { return a + b > u.a + u.b; }
for(int i=1;i<=n;i++){
    if(i&1) a[f[i].idx]--, b[f[i].idx]=0;
    else a[f[i].idx]=0, b[f[i].idx]--;
}
```

### 最优关键思路与技巧

1. **贪心策略**: 每次选择 $a_i + b_i$ 最大的颜色进行操作，确保双方的最优策略。
2. **数据结构**: 使用优先队列或结构体存储 $a_i$ 和 $b_i$，方便排序和操作。
3. **模拟过程**: 通过奇偶性判断当前回合是 Alice 还是 Bob 操作，更新得分。

### 可拓展之处

- **类似题目**: 可以扩展到其他双人博弈问题，如石子游戏、硬币游戏等，通常需要分析双方的最优策略。
- **算法套路**: 贪心算法在博弈问题中的应用，通常需要找到影响最大的操作进行优先处理。

### 推荐题目

1. [P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005)
2. [P1048 石子合并](https://www.luogu.com.cn/problem/P1048)
3. [P1052 过河](https://www.luogu.com.cn/problem/P1052)

---
处理用时：52.06秒