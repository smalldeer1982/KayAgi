# 题目信息

# Game with Marbles (Easy Version)

## 题目描述

The easy and hard versions of this problem differ only in the constraints on the number of test cases and $ n $ . In the easy version, the number of test cases does not exceed $ 10^3 $ , and $ n $ does not exceed $ 6 $ .

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

### 题目内容重写

#### 弹珠游戏（简易版）

**题目描述**

本题的简易版和困难版仅在测试用例数量和 $n$ 的约束上有所不同。在简易版中，测试用例的数量不超过 $10^3$，且 $n$ 不超过 $6$。

最近，Alice 和 Bob 从他们的父母那里得到了 $n$ 种不同颜色的弹珠。Alice 收到了 $a_1$ 个颜色为 $1$ 的弹珠，$a_2$ 个颜色为 $2$ 的弹珠，……，$a_n$ 个颜色为 $n$ 的弹珠。Bob 收到了 $b_1$ 个颜色为 $1$ 的弹珠，$b_2$ 个颜色为 $2$ 的弹珠，……，$b_n$ 个颜色为 $n$ 的弹珠。所有的 $a_i$ 和 $b_i$ 都在 $1$ 到 $10^9$ 之间。

经过一番讨论，Alice 和 Bob 提出了以下游戏规则：玩家轮流进行操作，Alice 先开始。轮到某个玩家时，他选择一种颜色 $i$，使得双方都至少有一个该颜色的弹珠。然后该玩家丢弃一个颜色为 $i$ 的弹珠，而对手则丢弃所有颜色为 $i$ 的弹珠。当没有颜色 $i$ 使得双方都至少有一个该颜色的弹珠时，游戏结束。

游戏的得分是游戏结束时 Alice 剩余的弹珠数与 Bob 剩余的弹珠数之差。换句话说，游戏的得分等于 $(A-B)$，其中 $A$ 是 Alice 拥有的弹珠数，$B$ 是 Bob 拥有的弹珠数。Alice 希望最大化得分，而 Bob 希望最小化得分。

计算双方都采取最优策略时游戏结束时的得分。

**说明/提示**

在第一个样例中，一种得分为 $1$ 的策略如下：

1. Alice 选择颜色 $1$，丢弃 $1$ 个弹珠。Bob 也丢弃 $1$ 个弹珠；
2. Bob 选择颜色 $3$，丢弃 $1$ 个弹珠。Alice 也丢弃 $1$ 个弹珠；
3. Alice 选择颜色 $2$，丢弃 $1$ 个弹珠，Bob 丢弃 $2$ 个弹珠。

最终，Alice 剩余的弹珠为 $a = [3, 1, 0]$，Bob 剩余的弹珠为 $b = [0, 0, 3]$。得分为 $3 + 1 - 3 = 1$。

可以证明，如果双方都采取最优策略，Alice 和 Bob 都无法获得更好的得分。

在第二个样例中，Alice 可以先选择颜色 $1$，然后 Bob 选择颜色 $4$，接着 Alice 选择颜色 $2$，Bob 选择颜色 $3$。可以证明这是最优的游戏策略。

### 题解分析与结论

#### 综合分析

本题的核心在于模拟 Alice 和 Bob 在游戏中的最优策略。由于 $n$ 的限制较小（$n \leq 6$），可以直接使用搜索或贪心策略来解决问题。大多数题解采用了贪心策略，通过计算每种颜色的 $a_i + b_i$ 并排序，模拟双方的轮流选择过程。

#### 最优关键思路

1. **贪心策略**：每次选择 $a_i + b_i$ 最大的颜色进行操作，因为这种颜色对双方的影响最大。Alice 和 Bob 都会优先选择这种颜色来最大化或最小化得分。
2. **模拟过程**：按照排序后的顺序，轮流让 Alice 和 Bob 选择颜色，并根据回合的奇偶性更新得分。

#### 推荐题解

1. **作者：Elhaithan (赞：2)**
   - **星级**：4
   - **关键亮点**：使用结构体存储 $a$ 和 $b$，并计算 $sum = a_i + b_i$，排序后模拟游戏过程。代码简洁清晰，易于理解。
   - **代码核心**：
     ```cpp
     for(int i=1; i<=n; i++){
         if(i&1) res += num[i].a - 1; // Alice的回合
         else res -= num[i].b - 1;    // Bob的回合
     }
     ```

2. **作者：Erica_N_Contina (赞：2)**
   - **星级**：4
   - **关键亮点**：详细解释了贪心策略的合理性，并通过排序和模拟实现。代码结构清晰，逻辑严谨。
   - **代码核心**：
     ```cpp
     for(int i=1; i<=n; i++){
         if(i&1) ans += t[i].a - 1; // 先手
         else ans -= t[i].b - 1;    // 后手
     }
     ```

3. **作者：ST_AS_IS_ZHY (赞：1)**
   - **星级**：4
   - **关键亮点**：通过维护 $sum1$ 和 $sum2$ 来实时更新双方的弹珠数量，代码实现较为直观。
   - **代码核心**：
     ```cpp
     if(i % 2) {
         sum2 -= s[i].b;
         s[i].b = 0;
         sum1 --;
         s[i].a --;
     } else {
         sum1 -= s[i].a;
         s[i].a = 0;
         sum2 --;
         s[i].b --;
     }
     ```

### 扩展思路

- **类似题目**：本题的贪心策略可以推广到其他博弈问题中，尤其是双方轮流选择最优策略的题目。例如，洛谷上的 P1005 [NOIP2007 提高组] 矩阵取数游戏，也涉及到双方轮流选择最优策略的问题。
- **推荐题目**：
  1. P1005 [NOIP2007 提高组] 矩阵取数游戏
  2. P1040 [NOIP2003 提高组] 加分二叉树
  3. P1063 [NOIP2006 提高组] 能量项链

### 个人心得

- **调试经历**：在实现贪心策略时，需要注意排序的顺序和回合的奇偶性，确保 Alice 和 Bob 的选择顺序正确。
- **顿悟感想**：贪心策略在博弈问题中非常有效，尤其是在双方轮流选择最优策略的情况下，通过排序和模拟可以简化问题。

---
处理用时：46.49秒