# 题目信息

# Pocket Book

## 题目描述

One day little Vasya found mom's pocket book. The book had $ n $ names of her friends and unusually enough, each name was exactly $ m $ letters long. Let's number the names from $ 1 $ to $ n $ in the order in which they are written.

As mom wasn't home, Vasya decided to play with names: he chose three integers $ i $ , $ j $ , $ k $ ( $ 1<=i&lt;j<=n $ , $ 1<=k<=m $ ), then he took names number $ i $ and $ j $ and swapped their prefixes of length $ k $ . For example, if we take names "CBDAD" and "AABRD" and swap their prefixes with the length of $ 3 $ , the result will be names "AABAD" and "CBDRD".

You wonder how many different names Vasya can write instead of name number $ 1 $ , if Vasya is allowed to perform any number of the described actions. As Vasya performs each action, he chooses numbers $ i $ , $ j $ , $ k $ independently from the previous moves and his choice is based entirely on his will. The sought number can be very large, so you should only find it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample Vasya can get the following names in the position number $ 1 $ : "AAB", "AAA", "BAA" and "BAB".

## 样例 #1

### 输入

```
2 3
AAB
BAA
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 5
ABABA
BCGDG
AAAAA
YABSA
```

### 输出

```
216
```

# AI分析结果



### 中文重写题目

**题目名称**：口袋书

**题目描述**：

有一天，小Vasya发现了妈妈的记事本。本子上记录了她朋友的$n$个名字，每个名字恰好由$m$个字母组成。这些名字按书写顺序编号为$1$到$n$。

妈妈不在家时，Vasya决定用这些名字做游戏：他选择三个整数$i, j, k$（$1 \leq i < j \leq n$，$1 \leq k \leq m$），然后交换编号为$i$和$j$的两个名字的前$k$个字母的前缀。例如，若名字为"CBDAD"和"AABRD"，交换长度为$3$的前缀后，结果将变为"AABAD"和"CBDRD"。

你需要计算，在允许进行任意次上述操作的情况下，编号为$1$的名字最终可能有多少种不同的形式。由于答案可能很大，请对$10^9+7$取模。

**样例说明**：

在第一个样例中，Vasya可以通过操作使编号为$1$的名字变为"AAB"、"AAA"、"BAA"、"BAB"共4种形式。

**样例输入1**：
```
2 3
AAB
BAA
```
**样例输出1**：
```
4
```

**样例输入2**：
```
4 5
ABABA
BCGDG
AAAAA
YABSA
```
**样例输出2**：
```
216
```

---

### 算法分类
**组合数学**

---

### 题解分析与结论

#### 核心思路
所有题解均基于同一关键观察：**每一列的字符选择独立，最终结果等于各列不同字符数量的乘积**。  
- **交换操作的独立性**：通过交换前缀，每个位置的字符可以自由组合到第一个字符串的对应列。
- **乘法原理**：各列的可能选择数独立，总方案数为各列可能数的乘积。

#### 题解对比
1. **莫奈的崖径（5星）**  
   - **亮点**：思路简洁清晰，代码高效，直接通过位标记统计每列不同字符数。
   - **代码核心**：
     ```cpp
     for (每列i) {
         memset(标记数组, 0, sizeof(标记数组));
         cnt = 0;
         for (每个字符串j) 
             if (!标记过该字符) 标记并计数++;
         ans = (ans * cnt) % mod;
     }
     ```

2. **qingchenMC（4星）**  
   - **亮点**：通过样例详细验证思路，强调“每列独立”的数学证明。
   - **关键代码**：
     ```cpp
     memset(vis, 0, sizeof(vis));
     for (每个字符串j) 
         if (!vis[当前字符]) vis标记并计数++;
     ans *= cnt;
     ```

3. **Phoenix114514（4星）**  
   - **亮点**：简化题意描述，强调排列组合本质，代码结构清晰。
   - **代码片段**：
     ```cpp
     for (列j) {
         bool数组标记字符是否出现;
         for (每个字符串i) 更新标记数组;
         ans *= 不同字符数;
     }
     ```

---

### 最优思路总结
- **独立列处理**：将字符串的每一列视为独立的选择空间。
- **位标记去重**：使用布尔数组快速统计每列的不同字符数量。
- **乘法取模**：逐列计算并累乘，避免数值溢出。

---

### 拓展与同类题
- **类似套路题**：若操作允许更复杂的交换（如任意位置而非前缀），需重新建模独立性。
- **推荐题目**：
  1. [P2181 对角线](https://www.luogu.com.cn/problem/P2181)（组合数计算）
  2. [P2822 组合数问题](https://www.luogu.com.cn/problem/P2822)（组合数性质+前缀和）
  3. [P1246 编码](https://www.luogu.com.cn/problem/P1246)（排列组合应用）

---

### 个人心得摘录
- **莫奈的崖径**：“只要懂了题意就很好看懂代码”——强调问题抽象的重要性。  
- **qingchenMC**：“发现情况数是每列不同字母个数相乘，别的题解也都提到了”——验证思路时需回归数学本质。  
- **The_jester_from_Lst**：“题面好抽象”——提醒仔细理解题意，避免误读操作规则。

---
处理用时：71.86秒