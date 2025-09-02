# 题目信息

# Omkar and Waterslide

## 题目描述

Omkar is building a waterslide in his water park, and he needs your help to ensure that he does it as efficiently as possible.

Omkar currently has $ n $ supports arranged in a line, the $ i $ -th of which has height $ a_i $ . Omkar wants to build his waterslide from the right to the left, so his supports must be nondecreasing in height in order to support the waterslide. In $ 1 $ operation, Omkar can do the following: take any contiguous subsegment of supports which is nondecreasing by heights and add $ 1 $ to each of their heights.

Help Omkar find the minimum number of operations he needs to perform to make his supports able to support his waterslide!

An array $ b $ is a subsegment of an array $ c $ if $ b $ can be obtained from $ c $ by deletion of several (possibly zero or all) elements from the beginning and several (possibly zero or all) elements from the end.

An array $ b_1, b_2, \dots, b_n $ is called nondecreasing if $ b_i\le b_{i+1} $ for every $ i $ from $ 1 $ to $ n-1 $ .

## 说明/提示

The subarray with which Omkar performs the operation is bolded.

In the first test case:

- First operation:
  
   $ [5, 3, \textbf{2}, 5] \to [5, 3, \textbf{3}, 5] $
- Second operation:
  
   $ [5, \textbf{3}, \textbf{3}, 5] \to [5, \textbf{4},           \textbf{4}, 5] $
- Third operation:
  
   $ [5, \textbf{4}, \textbf{4}, 5] \to [5, \textbf{5},           \textbf{5}, 5] $

In the third test case, the array is already nondecreasing, so Omkar does $ 0 $ operations.

## 样例 #1

### 输入

```
3
4
5 3 2 5
5
1 2 3 5 3
3
1 1 1```

### 输出

```
3
2
0```

# AI分析结果

### 题目内容重写
# Omkar 和滑水道

## 题目描述

Omkar 正在他的水上公园建造一个滑水道，他需要你的帮助来确保他尽可能高效地完成这项工作。

Omkar 目前有 $n$ 个支撑物排成一行，第 $i$ 个支撑物的高度为 $a_i$。Omkar 希望从右到左建造他的滑水道，因此他的支撑物必须按高度非递减排列，以支撑滑水道。在一次操作中，Omkar 可以执行以下操作：选择任意一个高度非递减的连续子段，并将其中每个支撑物的高度增加 $1$。

帮助 Omkar 找到他需要执行的最少操作次数，以使他的支撑物能够支撑他的滑水道！

数组 $b$ 是数组 $c$ 的子段，如果 $b$ 可以通过从 $c$ 的开头删除若干个（可能为零或全部）元素，并从 $c$ 的结尾删除若干个（可能为零或全部）元素得到。

数组 $b_1, b_2, \dots, b_n$ 被称为非递减的，如果对于每个 $i$ 从 $1$ 到 $n-1$，都有 $b_i \le b_{i+1}$。

## 说明/提示

Omkar 执行操作的子数组被加粗显示。

在第一个测试用例中：

- 第一次操作：
  
   $ [5, 3, \textbf{2}, 5] \to [5, 3, \textbf{3}, 5] $
- 第二次操作：
  
   $ [5, \textbf{3}, \textbf{3}, 5] \to [5, \textbf{4},           \textbf{4}, 5] $
- 第三次操作：
  
   $ [5, \textbf{4}, \textbf{4}, 5] \to [5, \textbf{5},           \textbf{5}, 5] $

在第三个测试用例中，数组已经是非递减的，因此 Omkar 执行 $0$ 次操作。

## 样例 #1

### 输入

```
3
4
5 3 2 5
5
1 2 3 5 3
3
1 1 1```

### 输出

```
3
2
0```

### 算法分类
贪心

### 题解分析与结论
所有题解的核心思路都是通过贪心策略来计算使数组非递减所需的最少操作次数。具体来说，题解们普遍采用了从前往后或从后往前遍历数组，计算相邻元素之间的差值，并将这些差值累加作为最终答案。这种方法的正确性在于，每次操作可以覆盖多个逆序对，因此只需计算每个逆序对的差值即可。

### 所选高星题解
1. **作者：Lynkcat (赞：3)**  
   - **星级：4**  
   - **关键亮点**：通过直观的表格展示问题，清晰地解释了贪心策略的正确性。代码简洁明了，直接计算相邻元素的差值并累加。  
   - **核心代码**：
     ```cpp
     for (int i=1;i<=n;i++) if (a[i]<a[i-1]) ans+=a[i-1]-a[i];
     ```

2. **作者：Chinese_zjc_ (赞：1)**  
   - **星级：4**  
   - **关键亮点**：详细解释了贪心策略的数学依据，并提供了公式化的总结。代码同样简洁，直接计算并累加差值。  
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;++i) ans+=max(0ll,a[i-1]-a[i]);
     ```

3. **作者：_rxfalty_ (赞：0)**  
   - **星级：4**  
   - **关键亮点**：从右往左遍历数组，进一步验证了贪心策略的正确性。代码实现简单，逻辑清晰。  
   - **核心代码**：
     ```cpp
     for(int i=n; i>1; i--) ans+=max(a[i-1]-a[i],0);
     ```

### 最优关键思路
最优的思路是通过遍历数组，计算相邻元素之间的差值，并将这些差值累加作为最终答案。这种方法的时间复杂度为 $O(n)$，非常高效。

### 可拓展之处
类似的问题可以通过贪心策略解决，例如在数组中进行区间操作以达到某种目标。这类问题通常可以通过分析相邻元素的关系来找到最优解。

### 推荐题目
1. [P1969 积木大赛](https://www.luogu.com.cn/problem/P1969)
2. [P5019 铺设道路](https://www.luogu.com.cn/problem/P5019)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：34.03秒