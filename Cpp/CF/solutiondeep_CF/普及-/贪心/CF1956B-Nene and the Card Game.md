# 题目信息

# Nene and the Card Game

## 题目描述

You and Nene are playing a card game. The deck with $ 2n $ cards is used to play this game. Each card has an integer from $ 1 $ to $ n $ on it, and each of integers $ 1 $ through $ n $ appears exactly on $ 2 $ cards. Additionally, there is a table where cards are placed during the game (initially, the table is empty).

In the beginning of the game, these $ 2n $ cards are distributed between you and Nene so that each player receives $ n $ cards.

After it, you and Nene alternatively take $ 2n $ turns, i.e. each person takes $ n $ turns, starting with you. On each turn:

- The player whose turn is it selects one of the cards in his hand. Let $ x $ be the number on it.
- The player whose turn is it receives $ 1 $ point if there is already a card with the integer $ x $ on the table (otherwise, he receives no points). After it, he places the selected card with the integer $ x $ on the table.

Note that turns are made publicly: each player can see all the cards on the table at each moment.

Nene is very smart so she always selects cards optimally in order to maximize her score in the end of the game (after $ 2n $ rounds). If she has several optimal moves, she selects the move that minimizes your score in the end of the game.

More formally, Nene always takes turns optimally in order to maximize her score in the end of the game in the first place and to minimize your score in the end of the game in the second place.

Assuming that the cards are already distributed and cards in your hand have integers $ a_1, a_2, \ldots, a_n $ written on them, what is the maximum number of points you can get by taking your turns optimally?

## 说明/提示

In the first test case, the integers written on your cards are $ 1 $ , $ 1 $ , $ 2 $ and $ 3 $ . The integers written on Nene's cards are $ 2 $ , $ 3 $ , $ 4 $ and $ 4 $ . The game may proceed as follows:

1. You select one of the cards with an integer $ 1 $ written on it and place it on the table.
2. Nene selects one of the cards with an integer $ 4 $ written on it and places it on the table.
3. You select the card with an integer $ 1 $ written on it, receive $ 1 $ point, and place the selected card on the table.
4. Nene selects the card with an integer $ 4 $ written on it, receive $ 1 $ point, and places the selected card on the table.
5. You select the card with an integer $ 2 $ written on it and place it on the table.
6. Nene selects the card with an integer $ 2 $ written on it, receive $ 1 $ point, and places the selected card on the table.
7. You select the card with an integer $ 3 $ written on it and place it on the table.
8. Nene selects the card with an integer $ 3 $ written on it, receive $ 1 $ point, and places the selected card on the table.

At the end of the game, you scored $ 1 $ point, and Nene scored $ 3 $ . It can be shown that you cannot score more than $ 1 $ point if Nene plays optimally, so the answer is $ 1 $ .

In the second test case, if both players play optimally, you score $ 2 $ points and Nene scores $ 6 $ points.

## 样例 #1

### 输入

```
5
4
1 1 2 3
8
7 4 1 2 8 8 5 5
8
7 1 4 5 3 4 2 6
3
1 2 3
1
1```

### 输出

```
1
2
1
0
0```

# AI分析结果



# Nene and the Card Game

## 题目描述

你和 Nene 正在玩一个卡牌游戏。游戏使用一副有 $2n$ 张卡牌的牌组，每张卡牌上写着 $1$ 到 $n$ 之间的整数，且每个整数恰好出现两次。游戏开始时，这 $2n$ 张卡牌被分配给你和 Nene，每人各拿 $n$ 张。

游戏进行 $2n$ 轮，由你作为先手开始，双方轮流行动。每轮中：

- 当前回合玩家从手牌中选择一张卡牌，设其数字为 $x$。
- 若桌面上已有数字 $x$ 的卡牌，则该玩家得 1 分。
- 将选中的卡牌放入桌面（无论是否得分）。

Nene 总是采取最优策略最大化自己的得分，并在得分相同的情况下最小化你的得分。已知你的手牌为 $a_1, a_2, \ldots, a_n$，求你在最优策略下能获得的最大得分。

---

## 题解综合分析

### 关键结论
玩家的得分等于其手牌中「对子」（同一数字出现两次）的数量。无论对方如何操作，玩家总能通过先出完所有对子来确保这些得分。

### 算法要点
1. **对子判定**：统计每个数字在玩家手牌中的出现次数。
2. **计数实现**：遍历手牌数组，记录出现次数为2的数字个数。

### 解决难点
- **博弈分析**：当双方各持一张相同数字的卡牌时，后手方（Nene）总能通过响应策略获得该分。
- **最优策略证明**：对子必须由玩家主动分两次打出才能得分，而单牌无法在对方干扰下得分。

---

## 精选题解（评分：★★★★☆）

### 题解作者：lailai0916
**关键亮点**  
简洁明了地指出对子得分的必然性，代码使用数组计数，清晰高效。
```cpp
int ans = 0;
for(int i=1; i<=n; i++) {
    if(a[i] == 2) ans++;
}
```

### 题解作者：ztrztr
**关键亮点**  
通过排序简化对子判定，时间复杂度稳定为 O(n log n)。
```cpp
sort(a+1, a+n+1);
int same = 0;
for(int i=1; i<=n; i++) 
    if(a[i] == a[i-1]) same++;
```

### 题解作者：破壁人罗辑
**关键亮点**  
详细推导双方对子数量关系，明确后手得分机制。
```cpp
sort(a,a+n);
int p=0;
for(int i=1; i<n; i++)
    if(a[i]==a[i-1]) p++;
```

---

## 举一反三

### 同类题目推荐
1. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)  
   **考察点**：配对问题与贪心策略
2. [P1102 A-B数对](https://www.luogu.com.cn/problem/P1102)  
   **考察点**：统计特定数对数量
3. [P2676 Bookshelf B](https://www.luogu.com.cn/problem/P2676)  
   **考察点**：最优选择策略

### 关键技巧
- **哈希计数**：快速统计元素频率（如 `unordered_map`）
- **排序优化**：通过预处理简化配对判断
- **博弈分析**：后手方的最优响应策略模型

---

## 心得分野

### 调试经验
- **对子判定陷阱**：当输入数据包含多个相同数字时，必须确保正确统计所有配对情况。
- **初始化细节**：多测试用例场景需重置计数数组，避免数据污染。

### 核心顿悟
「双方单牌的得分必然属于后手方」这一性质是解题的关键突破口，将复杂博弈问题转化为简单的计数问题。

---
处理用时：75.82秒