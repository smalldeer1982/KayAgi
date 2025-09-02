# 题目信息

# Turtle and Piggy Are Playing a Game 2

## 题目描述

Turtle and Piggy are playing a game on a sequence. They are given a sequence $ a_1, a_2, \ldots, a_n $ , and Turtle goes first. Turtle and Piggy alternate in turns (so, Turtle does the first turn, Piggy does the second, Turtle does the third, etc.).

The game goes as follows:

- Let the current length of the sequence be $ m $ . If $ m = 1 $ , the game ends.
- If the game does not end and it's Turtle's turn, then Turtle must choose an integer $ i $ such that $ 1 \le i \le m - 1 $ , set $ a_i $ to $ \max(a_i, a_{i + 1}) $ , and remove $ a_{i + 1} $ .
- If the game does not end and it's Piggy's turn, then Piggy must choose an integer $ i $ such that $ 1 \le i \le m - 1 $ , set $ a_i $ to $ \min(a_i, a_{i + 1}) $ , and remove $ a_{i + 1} $ .

Turtle wants to maximize the value of $ a_1 $ in the end, while Piggy wants to minimize the value of $ a_1 $ in the end. Find the value of $ a_1 $ in the end if both players play optimally.

You can refer to notes for further clarification.

## 说明/提示

In the first test case, initially $ a = [1, 2] $ . Turtle can only choose $ i = 1 $ . Then he will set $ a_1 $ to $ \max(a_1, a_2) = 2 $ and remove $ a_2 $ . The sequence $ a $ becomes $ [2] $ . Then the length of the sequence becomes $ 1 $ , and the game will end. The value of $ a_1 $ is $ 2 $ , so you should output $ 2 $ .

In the second test case, one of the possible game processes is as follows:

- Initially $ a = [1, 1, 2] $ .
- Turtle can choose $ i = 2 $ . Then he will set $ a_2 $ to $ \max(a_2, a_3) = 2 $ and remove $ a_3 $ . The sequence $ a $ will become $ [1, 2] $ .
- Piggy can choose $ i = 1 $ . Then he will set $ a_1 $ to $ \min(a_1, a_2) = 1 $ and remove $ a_2 $ . The sequence $ a $ will become $ [1] $ .
- The length of the sequence becomes $ 1 $ , so the game will end. The value of $ a_1 $ will be $ 1 $ in the end.

In the fourth test case, one of the possible game processes is as follows:

- Initially $ a = [3, 1, 2, 2, 3] $ .
- Turtle can choose $ i = 4 $ . Then he will set $ a_4 $ to $ \max(a_4, a_5) = 3 $ and remove $ a_5 $ . The sequence $ a $ will become $ [3, 1, 2, 3] $ .
- Piggy can choose $ i = 3 $ . Then he will set $ a_3 $ to $ \min(a_3, a_4) = 2 $ and remove $ a_4 $ . The sequence $ a $ will become $ [3, 1, 2] $ .
- Turtle can choose $ i = 2 $ . Then he will set $ a_2 $ to $ \max(a_2, a_3) = 2 $ and remove $ a_3 $ . The sequence $ a $ will become $ [3, 2] $ .
- Piggy can choose $ i = 1 $ . Then he will set $ a_1 $ to $ \min(a_1, a_2) = 2 $ and remove $ a_2 $ . The sequence $ a $ will become $ [2] $ .
- The length of the sequence becomes $ 1 $ , so the game will end. The value of $ a_1 $ will be $ 2 $ in the end.

## 样例 #1

### 输入

```
5
2
1 2
3
1 1 2
3
1 2 3
5
3 1 2 2 3
10
10 2 5 2 7 9 2 5 10 7```

### 输出

```
2
1
2
2
7```

# AI分析结果



### 题目重写

**题目名称：乌龟和猪在玩游戏 2**

#### 题目描述

乌龟和猪在玩一个数列游戏。给定一个序列 $a_1, a_2, \ldots, a_n$，乌龟先手。双方轮流操作，规则如下：

1. 当前序列长度为 $m$。若 $m=1$，游戏结束。
2. **乌龟的回合**：选择 $i \in [1, m-1]$，将 $a_i$ 设为 $\max(a_i, a_{i+1})$，并删除 $a_{i+1}$。
3. **猪的回合**：选择 $i \in [1, m-1]$，将 $a_i$ 设为 $\min(a_i, a_{i+1})$，并删除 $a_{i+1}$。

乌龟希望最终 $a_1$ 尽可能大，猪希望尽可能小。双方均采取最优策略，求最终 $a_1$ 的值。

---

### 题解分析与结论

#### 核心思路
所有题解均指出：**最终结果为排序后数组的中位数**，即第 $\lfloor n/2 \rfloor + 1$ 小的数。其本质原因是：
1. 乌龟每次操作会保留当前区间的较大值，相当于间接排除较小元素。
2. 猪每次操作会保留当前区间的较小值，相当于间接排除较大元素。
3. 最终双方博弈的结果等价于交替删除极值，最终剩余中间元素。

#### 最优题解摘录

##### 题解作者：Defy_HeavenS（4星）
**关键亮点**：
- 通过模拟样例分析双方策略，明确「删极值」的等价逻辑。
- 结合奇偶性解释中间值的选取规则。
- 代码简洁且符合逻辑。

**代码核心**：
```cpp
sort(a+1, a+1+n);
cout << a[n/2 + 1] << "\n";
```

##### 题解作者：zsq9（3.5星）
**关键亮点**：
- 直接给出排序后取中间值的结论。
- 代码简短，但未深入解释等价逻辑。

**代码核心**：
```cpp
sort(c+1, c+1+b);
cout << c[b/2+1];
```

##### 题解作者：wawatime1（3.5星）
**关键亮点**：
- 明确「删最大/最小」的简化思路。
- 代码清晰，但未完全展开策略分析。

**代码核心**：
```cpp
sort(a+1, a+1+n);
printf("%d\n", a[(n+1)/2]);
```

---

### 关键技巧总结
1. **博弈等价性**：将复杂操作抽象为交替删除极值，最终剩余中位数。
2. **排序性质**：无论操作顺序如何，最终结果仅与元素大小顺序相关。
3. **奇偶统一公式**：$\lfloor n/2 \rfloor + 1$ 可覆盖所有长度情况。

---

### 类似题目推荐
1. [CF1761B](https://codeforces.com/problemset/problem/1761/B)：博弈中交替删除元素的极值问题。
2. [P7072 取数游戏](https://www.luogu.com.cn/problem/P7072)：双方交替取数的最优策略。
3. [AT_abc194E](https://atcoder.jp/contests/abc194/tasks/abc194_e)：序列操作中保留特定极值的策略。

---

### 个人心得摘录
- **Defy_HeavenS**：通过手动模拟样例发现「删极值」的规律，验证了排序取中位数的正确性。
- **qiuqiu1231**：强调先模拟再归纳的重要性，避免直接陷入复杂操作分析。
- **mc_xiexie**：指出乌龟和猪的操作等价于删除当前序列的最小/最大值，最终剩余中间元素。

---
处理用时：57.11秒