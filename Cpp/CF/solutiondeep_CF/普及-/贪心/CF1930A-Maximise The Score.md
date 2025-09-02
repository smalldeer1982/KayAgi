# 题目信息

# Maximise The Score

## 题目描述

There are $ 2n $ positive integers written on a whiteboard. Being bored, you decided to play a one-player game with the numbers on the whiteboard.

You start with a score of $ 0 $ . You will increase your score by performing the following move exactly $ n $ times:

- Choose two integers $ x $ and $ y $ that are written on the whiteboard.
- Add $ \min(x,y) $ to your score.
- Erase $ x $ and $ y $ from the whiteboard.

Note that after performing the move $ n $ times, there will be no more integers written on the whiteboard.

Find the maximum final score you can achieve if you optimally perform the $ n $ moves.

## 说明/提示

In the first test case, you can only make one move. You select $ x=2 $ and $ y=3 $ , and your score will be $ \min(x,y)=2 $ .

In the second test case, the following is a sequence of moves that achieves a final score of $ 2 $ :

- In the first move, select $ x=1 $ and $ y=1 $ . Then, add $ \min(x,y)=1 $ to the score. After erasing $ x $ and $ y $ , the integers left on the whiteboard are $ 1 $ and $ 2 $ .
- In the second move, select $ x=1 $ and $ y=2 $ . Then, add $ \min(x,y)=1 $ to the score. After removing $ x $ and $ y $ , no more integers will be left on the whiteboard.

 It can be proved that it is not possible to get a score greater than $ 2 $ .In the third test case, you will perform the move thrice, adding $ 1 $ to the score each time.

## 样例 #1

### 输入

```
3
1
2 3
2
1 1 2 1
3
1 1 1 1 1 1```

### 输出

```
2
2
3```

# AI分析结果



### 中文重写题目

# 最大化分数

## 题目描述

白板上写有 $2n$ 个正整数。出于无聊，你决定用这些数字进行单人游戏。

初始得分为 $0$，你需要执行以下操作恰好 $n$ 次：

1. 选择白板上的两个整数 $x$ 和 $y$
2. 将 $\min(x,y)$ 加入得分
3. 擦除 $x$ 和 $y$

求通过最优操作能获得的最大最终得分。

## 样例

输入：
```
3
1
2 3
2
1 1 2 1
3
1 1 1 1 1 1
```
输出：
```
2
2
3
```

---

### 题解综合分析

所有题解均采用贪心策略，核心思路为：
1. 将数组排序
2. 累加所有奇数位元素之和

**正确性证明**：排序后，每次选取相邻两数中的较小值。此时较小值即为前者，且该策略可确保每个次小值不被更大数浪费，全局最优。

---

### 精选题解（评分≥4星）

#### 1. 作者：Little_x_starTYJ（5星）
**核心亮点**：
- 数学推导清晰，完整证明排序后奇数位和即答案
- 代码简洁规范，处理多组数据时初始化完善

**代码核心**：
```cpp
sort(a + 1, a + 1 + n);
for (int i = 1; i <= n; i += 2)
    ans += a[i];
```

#### 2. 作者：xzz_0611（4星）
**核心亮点**：
- 公式推导清晰，给出分步数学表达式
- 代码片段简明，突出核心逻辑

**关键推导**：
$$\sum_{i=1}^{n} A_{2i-1} \quad \text{（A为升序排列后数组）}$$

#### 3. 作者：ACtheQ（4星）
**个人心得**：
> "易发现，让选的两数越接近越好，这样不会让大的数浪费掉。排序后每次取相邻数即可。"

**代码特点**：
- 使用位运算判断奇偶，提升可读性
- 完整处理多组数据重置逻辑

---

### 关键思路总结
1. **排序贪心**：升序排列后，每对取前一个元素
2. **奇位累加**：最终答案为所有奇数索引元素之和
3. **复杂度**：$O(n \log n)$ 时间复杂度，由排序主导

---

### 拓展建议
1. **同类问题**：贪心策略常用于需要全局最优的配对问题，如区间调度、任务分配等
2. **变形思考**：若改为取较大值的最大和，可考虑降序排列取偶数位

---

### 推荐练习题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心+优先队列
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223) - 时间安排贪心
3. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995) - 极值交替选择策略

---
处理用时：48.22秒