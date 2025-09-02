# 题目信息

# Soldier and Cards

## 题目描述

Two bored soldiers are playing card war. Their card deck consists of exactly $ n $ cards, numbered from $ 1 $ to $ n $ , all values are different. They divide cards between them in some manner, it's possible that they have different number of cards. Then they play a "war"-like card game.

The rules are following. On each turn a fight happens. Each of them picks card from the top of his stack and puts on the table. The one whose card value is bigger wins this fight and takes both cards from the table to the bottom of his stack. More precisely, he first takes his opponent's card and puts to the bottom of his stack, and then he puts his card to the bottom of his stack. If after some turn one of the player's stack becomes empty, he loses and the other one wins.

You have to calculate how many fights will happen and who will win the game, or state that game won't end.

## 说明/提示

First sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF546C/13fabc002be9b868c475a6223b80932fbf64aac8.png)Second sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF546C/baf8f9cbd8baa7b7a7d1f276ff7ae6d3445560b3.png)

## 样例 #1

### 输入

```
4
2 1 3
2 4 2
```

### 输出

```
6 2```

## 样例 #2

### 输入

```
3
1 2
2 1 3
```

### 输出

```
-1```

# AI分析结果



【题目中文翻译】
# 士兵与纸牌

## 题目描述

两名无聊的士兵在玩纸牌战争。他们的牌堆恰好包含 $n$ 张不同的牌，编号从 1 到 n。两人以任意方式分配这些牌（可能数量不同）。游戏规则如下：

每轮战斗双方各取出自己牌堆顶部的牌。数值较大者获胜，将两张牌按特定顺序放入自己牌堆底部：先放对方的牌，再放自己的牌。当某一方牌堆为空时游戏结束，另一方获胜。

需要计算战斗次数及胜者，或判断游戏是否无限进行。

## 输入格式
第一行为总牌数 n  
第二行先给出第一个士兵的牌数 k1，随后 k1 个整数表示其牌序  
第三行格式同第二行，表示第二个士兵的牌

## 输出格式
若游戏结束，输出战斗次数和胜者编号（1或2）  
若无限循环，输出 -1

---

**算法分类**：队列、模拟

---

### 精选题解分析

1. **Cappuccino_mjj（5星）**
   - **核心思路**：使用双队列直接模拟战斗过程，设置1e6次循环上限避免死循环。
   - **亮点**：代码结构清晰，队列操作规范，循环上限设置合理。
   - **代码核心**：
     ```cpp
     while (!q1.empty() && !q2.empty()) {
         cnt++;
         if (cnt >= 1e6) { cout << -1; return 0; }
         int t1 = q1.front(), t2 = q2.front();
         q1.pop(); q2.pop();
         if (t1 > t2) {
             q1.push(t2); q1.push(t1);
         } else {
             q2.push(t1); q2.push(t2);
         }
     }
     ```

2. **莊·3001（4星）**
   - **核心思路**：同队列模拟，采用相同循环上限，代码简洁。
   - **亮点**：循环条件处理干净利落，胜负判断直接。
   - **代码核心**：
     ```cpp
     for (int i = 1; ; i++) {
         if (i > 1e6) { puts("-1"); return 0; }
         if (p.empty()) { printf("%d 2\n", i-1); return 0; }
         if (q.empty()) { printf("%d 1\n", i-1); return 0; }
         // 战斗逻辑同上
     }
     ```

---

### 关键思路总结
- **数据结构选择**：队列完美契合"顶部取牌、底部加牌"的操作特性。
- **循环终止条件**：通过设置足够大的循环上限（如1e6次）判断无限循环，平衡了效率与正确性。
- **模拟细节**：注意获胜方需**先放对方牌再放自己牌**的顺序，这是题目规则的易错点。

---

### 举一反三
1. **队列应用**：[P1540 机器翻译](https://www.luogu.com.cn/problem/P1540)  
   （模拟内存缓存置换）
2. **循环检测**：[P1562 还是N皇后问题](https://www.luogu.com.cn/problem/P1562)  
   （状态哈希判断重复）
3. **复杂模拟**：[P2058 海港](https://www.luogu.com.cn/problem/P2058)  
   （时间窗口与队列结合）

---

### 题解中的调试心得
- **Sea_Level**提到循环变量`j`的初始值需要注意，因为循环内计数从1开始，实际战斗次数需减1。
- **晨·曦**采用数组模拟时，提到牌序调整的细节，强调数组移动操作的易错性。

---
处理用时：80.50秒