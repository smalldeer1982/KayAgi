# 题目信息

# Obtain Two Zeroes

## 题目描述

You are given two integers $ a $ and $ b $ . You may perform any number of operations on them (possibly zero).

During each operation you should choose any positive integer $ x $ and set $ a := a - x $ , $ b := b - 2x $ or $ a := a - 2x $ , $ b := b - x $ . Note that you may choose different values of $ x $ in different operations.

Is it possible to make $ a $ and $ b $ equal to $ 0 $ simultaneously?

Your program should answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example two operations can be used to make both $ a $ and $ b $ equal to zero:

1. choose $ x = 4 $ and set $ a := a - x $ , $ b := b - 2x $ . Then $ a = 6 - 4 = 2 $ , $ b = 9 - 8 = 1 $ ;
2. choose $ x = 1 $ and set $ a := a - 2x $ , $ b := b - x $ . Then $ a = 2 - 2 = 0 $ , $ b = 1 - 1 = 0 $ .

## 样例 #1

### 输入

```
3
6 9
1 1
1 2
```

### 输出

```
YES
NO
YES
```

# AI分析结果

【题目内容】
# 获得两个零

## 题目描述

给定两个整数 $a$ 和 $b$。你可以对它们进行任意次数的操作（可能为零次）。

每次操作中，你可以选择任意正整数 $x$，并设置 $a := a - x$，$b := b - 2x$ 或 $a := a - 2x$，$b := b - x$。注意，你可以在不同的操作中选择不同的 $x$ 值。

是否有可能同时使 $a$ 和 $b$ 等于 $0$？

你的程序需要回答 $t$ 个独立的测试用例。

## 说明/提示

在示例的第一个测试用例中，可以使用两个操作使 $a$ 和 $b$ 都等于零：

1. 选择 $x = 4$ 并设置 $a := a - x$，$b := b - 2x$。然后 $a = 6 - 4 = 2$，$b = 9 - 8 = 1$；
2. 选择 $x = 1$ 并设置 $a := a - 2x$，$b := b - x$。然后 $a = 2 - 2 = 0$，$b = 1 - 1 = 0$。

## 样例 #1

### 输入

```
3
6 9
1 1
1 2
```

### 输出

```
YES
NO
YES
```

【算法分类】
数学

【题解分析与结论】
所有题解的核心思路都是基于数学分析，判断是否可以通过操作使 $a$ 和 $b$ 同时变为零。主要判断条件包括：
1. $a + b$ 必须是 $3$ 的倍数。
2. 较大数不能超过较小数的两倍。

这些条件确保了在每次操作中，$a$ 和 $b$ 的减少量是合理的，且最终能够同时达到零。

【评分较高的题解】
1. **幻想繁星 (4星)**
   - **关键亮点**：清晰地将问题转化为数学条件，并提供了简洁的代码实现。
   - **代码核心**：
     ```cpp
     if(min(a,b)*2<max(a,b)||(a+b)%3) cout<<"NO"<<endl;
     else cout<<"YES"<<endl;
     ```
   - **个人心得**：通过合并操作，发现每次操作总共减去 $3x$，从而得出 $a + b$ 必须是 $3$ 的倍数。

2. **Rainbow_qwq (4星)**
   - **关键亮点**：通过极端情况分析，进一步验证了较大数不能超过较小数的两倍。
   - **代码核心**：
     ```cpp
     if(a*2<b)return 0;
     return (a+b)%3==0;
     ```
   - **个人心得**：通过模拟操作过程，发现如果一直执行一种操作，较大数仍然无法变为零。

3. **yzy041616 (4星)**
   - **关键亮点**：通过解方程的方式，进一步验证了 $X$ 和 $Y$ 必须为自然数。
   - **代码核心**：
     ```cpp
     if((a+b)%3){cout<<"NO\n";continue;}
     if(a>b+b||b>a+a)cout<<"NO\n";
     else cout<<"YES\n";
     ```
   - **个人心得**：通过解方程，发现 $X$ 和 $Y$ 必须为自然数，从而得出 $a + b$ 必须是 $3$ 的倍数。

【最优关键思路或技巧】
1. **数学转化**：将问题转化为数学条件，判断 $a + b$ 是否为 $3$ 的倍数，以及较大数是否不超过较小数的两倍。
2. **极端情况分析**：通过模拟极端操作，验证较大数不能超过较小数的两倍。

【可拓展之处】
类似的问题可以通过数学转化和极端情况分析来解决，特别是在涉及操作次数和最终状态的题目中。

【推荐题目】
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)

---
处理用时：29.67秒