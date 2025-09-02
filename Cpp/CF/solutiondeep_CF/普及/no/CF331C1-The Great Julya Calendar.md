# 题目信息

# The Great Julya Calendar

## 题目描述

Yet another Armageddon is coming! This time the culprit is the Julya tribe calendar.

The beavers in this tribe knew math very well. Smart Beaver, an archaeologist, got a sacred plate with a magic integer on it. The translation from Old Beaverish is as follows:

"May the Great Beaver bless you! May your chacres open and may your third eye never turn blind from beholding the Truth! Take the magic number, subtract a digit from it (the digit must occur in the number) and get a new magic number. Repeat this operation until a magic number equals zero. The Earth will stand on Three Beavers for the time, equal to the number of subtractions you perform!"

Distinct subtraction sequences can obviously get you different number of operations. But the Smart Beaver is ready to face the worst and is asking you to count the minimum number of operations he needs to reduce the magic number to zero.

## 说明/提示

In the first test sample the minimum number of operations can be reached by the following sequence of subtractions:

  $ 24→20→18→10→9→0 $

## 样例 #1

### 输入

```
24
```

### 输出

```
5```

# AI分析结果



# The Great Julya Calendar

## 题目描述

又一场末日即将来临！这次是七月部落的日历引发的灾难。

海狸们擅长数学。考古学家 Smart Beaver 获得了一个刻有魔法整数的神圣石板，翻译如下：

"愿伟大的海狸保佑你！愿你的查克拉开启，第三只眼永远不要因目睹真理而失明！取魔法数，减去它的一个数位（该数位必须存在于数中），得到新的魔法数。重复此操作直到魔法数为零。地球将在三只海狸上停留的时间等于你执行减法操作的次数！"

不同的减法顺序显然会导致不同的操作次数。但 Smart Beaver 已准备好面对最坏情况，请你计算将魔法数减到零所需的最小操作次数。

## 样例 #1

### 输入

```
24
```

### 输出

```
5
```

## 算法分类
贪心

---

## 题解分析与结论

### 核心思路
所有题解均围绕贪心策略展开，**每次减去当前数字中的最大数位**。该策略的数学本质是：通过每次最大幅度减少数值，从而最小化总操作次数。

### 题解对比
1. **fengqiao17（4星）**
   - **关键亮点**：代码最简练，直接遍历数位取最大值
   - **实现技巧**：使用临时变量 `tmp` 分解数位，避免污染原值
   - **代码核心**：
     ```cpp
     while (n != 0) {
       int tmp = n, maxi = -1;
       while (tmp) { maxi = max(maxi, tmp%10); tmp /= 10; }
       n -= maxi; cnt++;
     }
     ```

2. **Auto_Accepted（4星）**
   - **数据结构创新**：利用优先队列维护最大值
   - **可读性优势**：堆结构直观体现"取最大值"的意图
   - **代码核心**：
     ```cpp
     priority_queue<int> p;
     while(j) { p.push(j%10); j /= 10; }
     n -= p.top();
     ```

3. **XCH_0803（4星）**
   - **变量命名规范**：`maxn` 明确表示最大值
   - **循环控制简洁**：双循环结构清晰分离数位分解与减法操作

### 最优思路总结
1. **贪心策略**：每次减去最大数位能最快速降低数值
2. **数位分解技巧**：通过 `tmp%10` 和 `tmp/=10` 循环逐位提取
3. **临界处理**：当减到个位数时直接归零

---

## 相似题目推荐
1. [P2698 硬币游戏](https://www.luogu.com.cn/problem/P2698) - 贪心策略选择硬币
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 优先队列维护最小值
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443) - BFS求最短路径（与贪心有相似的最优子结构思想）

---

## 题解中的编程心得
- **fengqiao17** 提醒："不要直接拿 `n` 取数位，否则会影响结果"，强调临时变量的必要性
- **Auto_Accepted** 通过堆结构实现时，发现"替身变量 `j`"能避免数值污染
- **pikabi** 在记忆化搜索中验证了 `f[now]` 的单调性，深化对问题本质的理解

---
处理用时：69.49秒