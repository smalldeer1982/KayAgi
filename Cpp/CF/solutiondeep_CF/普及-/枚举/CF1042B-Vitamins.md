# 题目信息

# Vitamins

## 题目描述

Berland shop sells $ n $ kinds of juices. Each juice has its price $ c_i $ . Each juice includes some set of vitamins in it. There are three types of vitamins: vitamin "A", vitamin "B" and vitamin "C". Each juice can contain one, two or all three types of vitamins in it.

Petya knows that he needs all three types of vitamins to stay healthy. What is the minimum total price of juices that Petya has to buy to obtain all three vitamins? Petya obtains some vitamin if he buys at least one juice containing it and drinks it.

## 说明/提示

In the first example Petya buys the first, the second and the fourth juice. He spends $ 5 + 6 + 4 = 15 $ and obtains all three vitamins. He can also buy just the third juice and obtain three vitamins, but its cost is $ 16 $ , which isn't optimal.

In the second example Petya can't obtain all three vitamins, as no juice contains vitamin "C".

## 样例 #1

### 输入

```
4
5 C
6 B
16 BAC
4 A
```

### 输出

```
15
```

## 样例 #2

### 输入

```
2
10 AB
15 BA
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
10 A
9 BC
11 CA
4 A
5 B
```

### 输出

```
13
```

## 样例 #4

### 输入

```
6
100 A
355 BCA
150 BC
160 AC
180 B
190 CA
```

### 输出

```
250
```

## 样例 #5

### 输入

```
2
5 BA
11 CB
```

### 输出

```
16
```

# AI分析结果

### 题目中文重写
## 维生素

### 题目描述
Berland商店出售 $n$ 种果汁。每种果汁都有其价格 $c_i$。每种果汁都包含一些维生素。有三种类型的维生素：维生素“A”、维生素“B”和维生素“C”。每种果汁可以包含一种、两种或所有三种维生素。

Petya 知道他需要所有三种维生素才能保持健康。Petya 为获得所有三种维生素而必须购买的果汁的最低总价是多少？如果 Petya 购买至少一种含有某种维生素的果汁并饮用它，他就会获得该维生素。

### 说明/提示
在第一个样例中，Petya 购买了第一、第二和第四种果汁。他花费了 $5 + 6 + 4 = 15$ 并获得了所有三种维生素。他也可以只购买第三种果汁并获得三种维生素，但它的成本是 $16$，这不是最优的。

在第二个样例中，Petya 无法获得所有三种维生素，因为没有果汁含有维生素“C”。

### 样例 #1
#### 输入
```
4
5 C
6 B
16 BAC
4 A
```
#### 输出
```
15
```

### 样例 #2
#### 输入
```
2
10 AB
15 BA
```
#### 输出
```
-1
```

### 样例 #3
#### 输入
```
5
10 A
9 BC
11 CA
4 A
5 B
```
#### 输出
```
13
```

### 样例 #4
#### 输入
```
6
100 A
355 BCA
150 BC
160 AC
180 B
190 CA
```
#### 输出
```
250
```

### 样例 #5
#### 输入
```
2
5 BA
11 CB
```
#### 输出
```
16
```

### 题解综合分析与结论
这些题解主要围绕如何找出购买果汁以获得三种维生素的最小花费展开，涵盖了暴力贪心、动态规划、深度优先搜索（DFS）和状态压缩等多种算法思路。
- **暴力贪心**：枚举所有可能的果汁组合情况，计算每种组合的花费并取最小值。如览遍千秋、Viston、yfct 的题解，思路直观但代码冗长，对于维生素种类增多的情况扩展性差。
- **动态规划**：通过定义状态和状态转移方程来求解最优解。如周子衡、Dog_Two 的题解，状态定义和转移方程的设计是关键，能有效解决问题，但代码复杂度相对较高。
- **深度优先搜索（DFS）**：通过递归搜索所有可能的购买方案，同时使用剪枝优化减少不必要的搜索。如 km_xyx、sinsop90 的题解，剪枝策略的设计是优化的重点。
- **状态压缩**：将维生素的组合状态用二进制数表示，简化状态的表示和处理。如 ZigZagKmp、SIXIANG32、wky32768 的题解，能降低时间和空间复杂度，提高代码效率。

### 评分较高的题解
- **ZigZagKmp（5星）**
    - **关键亮点**：思路清晰，使用背包 + 状压的方法，将维生素状态用二进制表示，通过状态转移方程求解最小花费，代码简洁高效，时间复杂度为 $O(n)$。
    - **核心代码**：
```cpp
for(register int i=1;i<=n;++i){
    for(register int j=7;j>=0;--j){
        f[j|pv[i]]=min(f[j|pv[i]],f[j]+w[i]);
    }
}
```
- **SIXIANG32（4星）**
    - **关键亮点**：详细解释了状压 DP 的思路和实现过程，对于初学者友好，代码结构清晰，易于理解。
    - **核心代码**：
```cpp
for(int p=1;p<=n;p++)
    for(int i=7;i>=0;i--)
        f[i|k[p]]=min(f[i|k[p]],f[i]+v[p]);
```
- **周子衡（4星）**
    - **关键亮点**：使用动态规划思想，通过定义四维状态数组进行状态转移，同时进行了空间优化，代码实现严谨。
    - **核心代码**：
```cpp
for(int i=1;i<=n;i++)
{
    for(int A=1;A>=0;A--)
    {
        for(int B=1;B>=0;B--)
        {
            for(int C=1;C>=0;C--)
            {
                ans[A][B][C]=min(ans[A][B][C], ans[A&&!all[i].a][B&&!all[i].b][C&&!all[i].c]+all[i].prc);
            }
        }
    }
}
```

### 最优关键思路或技巧
- **状态压缩**：将维生素的组合状态用二进制数表示，如将维生素“A”表示为 `001`，“B”表示为 `010`，“C”表示为 `100`，可以方便地进行状态的合并和转移，降低时间和空间复杂度。
- **动态规划**：通过定义合理的状态和状态转移方程，逐步求解最优解，避免了暴力枚举的高复杂度。

### 可拓展之处
同类型题或类似算法套路包括：
- 多维背包问题：当物品有多个属性时，可使用类似的状态定义和转移方程求解。
- 状态压缩 DP 在集合问题中的应用：如旅行商问题（TSP），将城市的访问状态用二进制表示，通过状态转移求解最短路径。

### 推荐洛谷题目
- P1879 [USACO06NOV]Corn Fields G：状态压缩 DP 求解农场种植方案。
- P1171 售货员的难题：旅行商问题，可使用状态压缩 DP 求解。
- P2704 [NOI2001] 炮兵阵地：状态压缩 DP 求解炮兵阵地的布置方案。

### 个人心得摘录与总结
- **SIXIANG32**：作者回忆了以前用贪心方法做题容易被 Hack 的经历，此次使用状压 DP 解决问题，强调了状压 DP 的优势，总结是要不断学习新的算法和思路，避免使用容易出错的贪心方法。
- **km_xyx**：作者认为这是一道水搜索题，提到使用 DFS 剪枝可以 AC，总结是对于搜索问题，合理的剪枝策略可以提高效率。 

---
处理用时：36.99秒