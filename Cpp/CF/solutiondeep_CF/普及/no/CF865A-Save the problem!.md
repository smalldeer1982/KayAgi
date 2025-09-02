# 题目信息

# Save the problem!

## 题目描述

Attention: we lost all the test cases for this problem, so instead of solving the problem, we need you to generate test cases. We're going to give you the answer, and you need to print a test case that produces the given answer. The original problem is in the following paragraph.

People don't use cash as often as they used to. Having a credit card solves some of the hassles of cash, such as having to receive change when you can't form the exact amount of money needed to purchase an item. Typically cashiers will give you as few coins as possible in change, but they don't have to. For example, if your change is 30 cents, a cashier could give you a 5 cent piece and a 25 cent piece, or they could give you three 10 cent pieces, or ten 1 cent pieces, two 5 cent pieces, and one 10 cent piece. Altogether there are 18 different ways to make 30 cents using only 1 cent pieces, 5 cent pieces, 10 cent pieces, and 25 cent pieces. Two ways are considered different if they contain a different number of at least one type of coin. Given the denominations of the coins and an amount of change to be made, how many different ways are there to make change?

As we mentioned before, we lost all the test cases for this problem, so we're actually going to give you the number of ways, and want you to produce a test case for which the number of ways is the given number. There could be many ways to achieve this (we guarantee there's always at least one), so you can print any, as long as it meets the constraints described below.

## 样例 #1

### 输入

```
18
```

### 输出

```
30 4
1 5 10 25
```

## 样例 #2

### 输入

```
3
```

### 输出

```
20 2
5 2
```

## 样例 #3

### 输入

```
314
```

### 输出

```
183 4
6 5 2 139
```

# AI分析结果



# Save the problem!

## 题目描述

注意：我们丢失了该题的所有测试用例，因此你需要根据给定的答案生成测试用例。我们将给出答案，你需要输出一个能产生该答案的测试用例。原题描述如下：

人们不再像以前那样经常使用现金。使用信用卡解决了现金带来的一些麻烦，例如当无法准确凑出购买商品所需金额时需要进行找零。通常收银员会尽可能少地给出硬币作为找零，但也不一定必须如此。例如，找零30美分时，收银员可能给一个5美分和一个25美分，或三个10美分，或十个1美分、两个5美分和一个10美分。总共有18种不同的方式可以用1美分、5美分、10美分和25美分硬币凑出30美分。两种方式被认为是不同的，如果它们至少包含某一种硬币的数量不同。给定硬币面额和需要找零的金额，计算有多少种不同的找零方式？

现在需要你反向操作：给定找零方式的数量，构造一个测试用例（金额和硬币面值组合），使得该测试用例的答案等于给定数量。输出任意符合要求的解即可。

## 样例 #1

### 输入

```
18
```

### 输出

```
30 4
1 5 10 25
```

## 样例 #2

### 输入

```
3
```

### 输出

```
20 2
5 2
```

---

**算法分类**：构造

---

### 综合分析与结论

所有题解均采用数学构造法，核心思路是利用1元硬币的万能组合特性。通过固定使用面值1和2的硬币，推导出总金额为2A-1时，找零方式数恰好等于A。这种构造法将原本复杂的动态规划问题转化为简洁的数学公式。

---

### 精选题解

#### 1. 作者：S__X（★★★★☆）
**关键亮点**：完整推导了方案数与金额的关系式，解释了奇偶拆分逻辑。  
**核心思路**：  
设金额为n=2A-1，使用面值1和2的硬币。此时找零方式数为A，因为2元硬币的数量可以从0到A-1，共A种选择。  
**代码片段**：
```cpp
cout<<A*2-1<<" "<<2<<endl;
cout<<1<<" "<<2<<endl;
```

#### 2. 作者：Refined_heart（★★★★☆）
**关键亮点**：代码简洁，直接给出核心公式。  
**实现技巧**：使用位运算优化计算过程。  
**核心代码**：
```cpp
cout<<(A<<1)-1<<" "<<2<<endl;  // 位运算实现2A-1
```

#### 3. 作者：Epi4any（★★★★☆）
**亮点**：明确指出题目允许任意解的特性，强调构造法的适用场景。  
**个人心得**："看到允许输出任意解就立即想到构造特殊解"体现了对题目条件的敏锐把握。

---

### 关键思路总结
1. **硬币组合选择**：固定使用面值1和2，确保能覆盖所有可能的金额组合。
2. **数学建模**：通过方案数A推导金额n=2A-1，建立线性关系式。
3. **逆向构造**：将原本求方案数的动态规划问题转化为简单的代数运算。

---

### 拓展练习
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)（构造覆盖关系）
2. [P1022 计算器的改良](https://www.luogu.com.cn/problem/P1022)（方程构造）
3. [P2615 神奇的幻方](https://www.luogu.com.cn/problem/P2615)（规则构造）

---
处理用时：49.77秒