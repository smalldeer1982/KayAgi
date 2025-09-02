# 题目信息

# Xenia and Spies

## 题目描述

Xenia the vigorous detective faced $ n $ $ (n>=2) $ foreign spies lined up in a row. We'll consider the spies numbered from 1 to $ n $ from left to right.

Spy $ s $ has an important note. He has to pass the note to spy $ f $ . Xenia interrogates the spies in several steps. During one step the spy keeping the important note can pass the note to one of his neighbours in the row. In other words, if this spy's number is $ x $ , he can pass the note to another spy, either $ x-1 $ or $ x+1 $ (if $ x=1 $ or $ x=n $ , then the spy has only one neighbour). Also during a step the spy can keep a note and not pass it to anyone.

But nothing is that easy. During $ m $ steps Xenia watches some spies attentively. Specifically, during step $ t_{i} $ (steps are numbered from 1) Xenia watches spies numbers $ l_{i},l_{i}+1,l_{i}+2,...,r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ . Of course, if during some step a spy is watched, he can't do anything: neither give the note nor take it from some other spy. Otherwise, Xenia reveals the spies' cunning plot. Nevertheless, if the spy at the current step keeps the note, Xenia sees nothing suspicious even if she watches him.

You've got $ s $ and $ f $ . Also, you have the steps during which Xenia watches spies and which spies she is going to watch during each step. Find the best way the spies should act in order to pass the note from spy $ s $ to spy $ f $ as quickly as possible (in the minimum number of steps).

## 样例 #1

### 输入

```
3 5 1 3
1 1 2
2 2 3
3 3 3
4 1 1
10 1 3
```

### 输出

```
XXRR
```

# AI分析结果



# Xenia and Spies

## 题目描述

侦探Xenia面对排成一行的$n$个外国间谍（编号1到$n$）。间谍$s$需要将重要纸条传递给间谍$f$。传递规则如下：
1. 每个步骤中，持有纸条的间谍可以传给相邻的间谍，或保持不动。
2. 在$m$个指定的步骤中，Xenia会监视区间$[l_i, r_i]$内的所有间谍，此时该区间内的间谍不能传递纸条（但保持不动不会被发现）。

求从$s$到$f$的最快传递方案，输出每一步的动作序列（'L'左传，'R'右传，'X'不动）。

## 样例输入输出
**输入示例**  
```
3 5 1 3
1 1 2
2 2 3
3 3 3
4 1 1
10 1 3
```
**输出示例**  
```
XXRR
```

---

### 算法分类
**贪心**

---

## 题解对比与分析

### 各题解要点总结

1. **RayAstRa_（4星）**
   - **核心思路**：每次尽量向目标方向移动，若当前步骤受监视则暂停。使用map存储监视时间，通过双重循环处理每个位置移动所需的多个时间步。
   - **亮点**：通过预处理监视时间实现快速查询，利用贪心策略处理连续监视时段。
   - **代码简析**：
     ```cpp
     while (++t) {
         if (k[t].r >= i && k[t].l <= i+1) // 检查当前和下一位置是否被监视
             ans += 'X';
         else break;
     }
     ans += 'R'; // 找到可移动时间后传递
     ```

2. **copper_ingot（5星）**
   - **核心思路**：逐个时间步处理，若当前步骤无法移动则暂停，否则向目标方向移动。使用map快速判断监视状态。
   - **亮点**：代码简洁高效，直接模拟时间推进过程，完美处理时间跳跃。
   - **代码简析**：
     ```cpp
     for (int i = 1; ; i++) {
         pii p = mp[i];
         if (当前或下一位置被监视) ans[i] = 'X';
         else ans[i] = 移动方向;
         if (到达目标) break;
     }
     ```

3. **_lmh_（4星）**
   - **核心思路**：与copper_ingot类似，但使用更紧凑的条件判断。
   - **亮点**：利用map的count优化查询，通过方向标志变量统一处理左右移动逻辑。
   - **代码简析**：
     ```cpp
     while (s < f) {
         ++t;
         if (监视当前或下一位置) putchar('X');
         else putchar('R'), s++;
     }
     ```

### 最优思路提炼
1. **贪心策略**：始终朝目标方向移动，仅在受监视时暂停。
2. **时间处理**：逐个时间步推进，使用map存储监视区间以实现快速查询。
3. **监视判断**：检查当前持有者位置和下一位置是否在监视区间内。

---

## 推荐相似题目
1. [P1086 花生采摘](https://www.luogu.com.cn/problem/P1086) - 贪心策略与时间模拟
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心选择最优操作
3. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144) - 路径选择与状态记录

---
处理用时：138.97秒