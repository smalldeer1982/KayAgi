# 题目信息

# Beaver's Calculator 1.0

## 题目描述

The Smart Beaver from ABBYY has once again surprised us! He has developed a new calculating device, which he called the "Beaver's Calculator $ 1.0 $ ". It is very peculiar and it is planned to be used in a variety of scientific problems.

To test it, the Smart Beaver invited $ n $ scientists, numbered from $ 1 $ to $ n $ . The $ i $ -th scientist brought $ k_{i} $ calculating problems for the device developed by the Smart Beaver from ABBYY. The problems of the $ i $ -th scientist are numbered from $ 1 $ to $ k_{i} $ , and they must be calculated sequentially in the described order, since calculating each problem heavily depends on the results of calculating of the previous ones.

Each problem of each of the $ n $ scientists is described by one integer $ a_{i,j} $ , where $ i $ ( $ 1<=i<=n $ ) is the number of the scientist, $ j $ ( $ 1<=j<=k_{i} $ ) is the number of the problem, and $ a_{i,j} $ is the number of resource units the calculating device needs to solve this problem.

The calculating device that is developed by the Smart Beaver is pretty unusual. It solves problems sequentially, one after another. After some problem is solved and before the next one is considered, the calculating device allocates or frees resources.

The most expensive operation for the calculating device is freeing resources, which works much slower than allocating them. It is therefore desirable that each next problem for the calculating device requires no less resources than the previous one.

You are given the information about the problems the scientists offered for the testing. You need to arrange these problems in such an order that the number of adjacent "bad" pairs of problems in this list is minimum possible. We will call two consecutive problems in this list a "bad pair" if the problem that is performed first requires more resources than the one that goes after it. Do not forget that the problems of the same scientist must be solved in a fixed order.

## 说明/提示

In the first sample $ n=2 $ , $ k_{1}=2 $ , $ a_{1,1}=1 $ , $ a_{1,2}=2 $ , $ k_{2}=2 $ , $ a_{2,1}=3 $ , $ a_{2,2}=4 $ . We've got two scientists, each of them has two calculating problems. The problems of the first scientist require $ 1 $ and $ 2 $ resource units, the problems of the second one require $ 3 $ and $ 4 $ resource units. Let's list all possible variants of the calculating order (each problem is characterized only by the number of resource units it requires): $ (1,2,3,4) $ , $ (1,3,2,4) $ , $ (3,1,2,4) $ , $ (1,3,4,2) $ , $ (3,4,1,2) $ , $ (3,1,4,2) $ .

Sequence of problems $ (1,3,2,4) $ has one "bad" pair ( $ 3 $ and $ 2 $ ), $ (3,1,4,2) $ has two "bad" pairs ( $ 3 $ and $ 1 $ , $ 4 $ and $ 2 $ ), and $ (1,2,3,4) $ has no "bad" pairs.

## 样例 #1

### 输入

```
2
2 1 1 1 10
2 3 1 1 10
```

### 输出

```
0
1 1
2 1
3 2
4 2
```

## 样例 #2

### 输入

```
2
3 10 2 3 1000
3 100 1 999 1000
```

### 输出

```
2
10 1
23 1
49 1
100 2
99 2
98 2
```

# AI分析结果

### 题目内容
# 海狸的计算器1.0

## 题目描述
来自ABBYY的聪明海狸又一次惊艳到了我们！他开发了一种新的计算设备，他称之为 “海狸的计算器1.0”。它非常独特，计划用于各种科学问题。

为了测试它，聪明海狸邀请了n位科学家，编号从1到n。第i位科学家为ABBYY的聪明海狸开发的设备带来了$k_i$个计算问题。第i位科学家的问题从1到$k_i$编号，并且必须按照描述的顺序依次计算，因为计算每个问题在很大程度上取决于前一个问题的计算结果。

n位科学家中每位科学家的每个问题都由一个整数$a_{i,j}$描述，其中i（$1\leq i\leq n$）是科学家的编号，j（$1\leq j\leq k_i$）是问题的编号，$a_{i,j}$是计算设备解决此问题所需的资源单位数量。

聪明海狸开发的计算设备非常不寻常。它依次解决问题，一个接一个。在某个问题解决后，在下一个问题被考虑之前，计算设备分配或释放资源。

对于计算设备来说，最昂贵的操作是释放资源，这比分配资源要慢得多。因此，希望计算设备的每个后续问题所需的资源不少于前一个问题。

您将获得科学家们提供的用于测试的问题信息。您需要以这样一种顺序安排这些问题，使得此列表中相邻 “坏” 对问题的数量尽可能少。如果在此列表中，先执行的问题比后执行的问题需要更多的资源，我们将这两个连续的问题称为 “坏对”。不要忘记，同一科学家的问题必须按固定顺序解决。

## 说明/提示
在第一个样例中，$n = 2$，$k_1 = 2$，$a_{1,1} = 1$，$a_{1,2} = 2$，$k_2 = 2$，$a_{2,1} = 3$，$a_{2,2} = 4$。我们有两位科学家，每位都有两个计算问题。第一位科学家的问题需要1和2个资源单位，第二位科学家的问题需要3和4个资源单位。让我们列出所有可能的计算顺序（每个问题仅由其所需的资源单位数量来表征）：$(1,2,3,4)$，$(1,3,2,4)$，$(3,1,2,4)$，$(1,3,4,2)$，$(3,4,1,2)$，$(3,1,4,2)$。

问题序列$(1,3,2,4)$有一对 “坏” 对（3和2），$(3,1,4,2)$有两对 “坏” 对（3和1，4和2），而$(1,2,3,4)$没有 “坏” 对。

## 样例 #1
### 输入
```
2
2 1 1 1 10
2 3 1 1 10
```
### 输出
```
0
1 1
2 1
3 2
4 2
```
## 样例 #2
### 输入
```
2
3 10 2 3 1000
3 100 1 999 1000
```
### 输出
```
2
10 1
23 1
49 1
100 2
99 2
98 2
```
### 算法分类
贪心

### 综合分析与结论
这两篇题解提供了不同的解题思路。_Weslie_ 的题解给出了动态规划和贪心两种做法，动态规划通过三维状态转移方程计算最小 “坏对” 数，但只能通过数据范围较小的A1；贪心做法将序列分成不下降子段，利用优先队列维护，能通过A2，但会在A3中MLE。Confringo 的题解先分析出答案等于取走单独一个序列需要连续子段的最小值的最大值，然后根据数据范围不同采用不同实现方式，时间复杂度为 $O(nk)$，能满足题目数据范围要求。整体来看，Confringo的题解思路更简洁清晰，对题目核心的把握更准确，实现方式也更具通用性。

### 所选的题解
- **Confringo的题解**：★★★★
  - **关键亮点**：通过分析得出答案等于取走单独一个序列需要连续子段的最小值的最大值这一结论，基于此结论根据不同数据范围给出合理实现方式，思路简洁清晰，能适应题目所有数据范围。

### 重点代码及核心实现思想
Confringo题解代码实现思路：
```cpp
// 读入所有数据，计算sum_k
// 如果 sum_k <= 2 * 10^5
// 生成序列，维护cnt变量表示取走这个数和它前面的数需要的连续子段的最小值
// 保存每个数的三个属性：cnt值、大小、属于的序列编号
// 使用std::sort排序输出
// 如果 sum_k > 2 * 10^5
// 直接按照上述结论计算答案
```

### 最优关键思路或技巧
通过分析得出答案等于取走单独一个序列需要连续子段的最小值的最大值这一关键结论，简化了问题求解过程，避免了复杂的动态规划状态转移或贪心策略设计。

### 可拓展之处
此类题目属于序列操作优化问题，类似套路是先分析问题的上下界，若能证明上下界相等，则可直接得出答案，再根据数据范围选择合适的实现方式。

### 洛谷相似题目推荐
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1980 计数问题](https://www.luogu.com.cn/problem/P1980)

---
处理用时：55.57秒