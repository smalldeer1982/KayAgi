# 题目信息

# Bad Ugly Numbers

## 题目描述

You are given a integer $ n $ ( $ n > 0 $ ). Find any integer $ s $ which satisfies these conditions, or report that there are no such numbers:

In the decimal representation of $ s $ :

- $ s > 0 $ ,
- $ s $ consists of $ n $ digits,
- no digit in $ s $ equals $ 0 $ ,
- $ s $ is not divisible by any of it's digits.

## 说明/提示

In the first test case, there are no possible solutions for $ s $ consisting of one digit, because any such solution is divisible by itself.

For the second test case, the possible solutions are: $ 23 $ , $ 27 $ , $ 29 $ , $ 34 $ , $ 37 $ , $ 38 $ , $ 43 $ , $ 46 $ , $ 47 $ , $ 49 $ , $ 53 $ , $ 54 $ , $ 56 $ , $ 57 $ , $ 58 $ , $ 59 $ , $ 67 $ , $ 68 $ , $ 69 $ , $ 73 $ , $ 74 $ , $ 76 $ , $ 78 $ , $ 79 $ , $ 83 $ , $ 86 $ , $ 87 $ , $ 89 $ , $ 94 $ , $ 97 $ , and $ 98 $ .

For the third test case, one possible solution is $ 239 $ because $ 239 $ is not divisible by $ 2 $ , $ 3 $ or $ 9 $ and has three digits (none of which equals zero).

## 样例 #1

### 输入

```
4
1
2
3
4```

### 输出

```
-1
57
239
6789```

# AI分析结果

### 题目内容
# 糟糕的丑数

## 题目描述
给定一个整数 $n$（$n > 0$）。找出满足以下条件的任意整数 $s$，若不存在这样的数则报告：
在 $s$ 的十进制表示中：
- $s > 0$；
- $s$ 由 $n$ 位数字组成；
- $s$ 中任意一位数字都不等于 $0$；
- $s$ 不能被其数位上的任意一个数字整除。

## 说明/提示
在第一个测试用例中，不存在由一位数字组成的 $s$ 的可能解，因为任何这样的解都能被它自身整除。
对于第二个测试用例，可能的解有：$23$、$27$、$29$、$34$、$37$、$38$、$43$、$46$、$47$、$49$、$53$、$54$、$56$、$57$、$58$、$59$、$67$、$68$、$69$、$73$、$74$、$76$、$78$、$79$、$83$、$86$、$87$、$89$、$94$、$97$ 和 $98$。
对于第三个测试用例，一个可能的解是 $239$，因为 $239$ 不能被 $2$、$3$ 或 $9$ 整除，并且有三位数字（且都不等于零）。

## 样例 #1
### 输入
```
4
1
2
3
4
```
### 输出
```
-1
57
239
6789
```

### 算法分类
构造

### 题解综合分析与结论
这些题解的核心思路都是通过构造符合条件的数字来解决问题。难点在于如何构造出一个满足所有条件的 $n$ 位整数，即不能被其数位上的任意一个数字整除。各题解通过利用不同数字的整除特性来进行构造。
1. **AutumnKite**：利用能被 $7$ 整除的数 $777\cdots 777$，在其基础上构造 $777\cdots 774$，因为 $777\cdots 77x$（$x > 0$）不能被 $7$ 整除且 $74\bmod 4\ne 0$，满足条件，同时特判了 $n = 1$ 的情况。
2. **Lylighte**：列举出 $2$ 到 $9$ 这些数字整除的特征，发现切入点为 $3$ 的整除性质，构造 $233\cdots 3$（$n - 1$ 个 $3$）这样的数，证明其满足条件，同样特判了 $n = 1$ 的情况。
3. **andyli**：直接构造第 $n$ 位为 $2$，其余数位为 $3$ 的正整数，指出该数不能被 $2$ 或 $3$ 整除，特判 $n = 1$，时间复杂度为 $\mathcal O(n)$。
4. **chenyilai**：先输出 $n - 1$ 个 $2$ 再输出 $9$，但考虑到数字有 $9$ 的倍数个 $2$ 时 $\bmod\,9 = 0$ 的情况进行判断，特判了 $n = 1$。
5. **StudyingFather**：构造 $233\ldots 3$（开头一个 $2$，后面 $n - 1$ 个 $3$），并指出这种构造满足要求，特判了 $n = 1$。

### 所选的题解
- **AutumnKite（4星）**
  - **关键亮点**：巧妙利用能被 $7$ 整除的数的特性来构造，切入点独特，代码简洁明了。
  ```cpp
  int n;
  void solve(){
      read(n);
      if (n == 1) return print(-1), void(0);
      for (register int i = 1; i < n; ++i) putchar('7');
      putchar('4'), putchar('\n');
  }
  ```
- **Lylighte（4星）**
  - **关键亮点**：详细列举各数字整除特征，从 $3$ 的整除性质切入构造，思路清晰。
  - **代码核心思想**：根据 $3$ 的整除性质，构造 $233\cdots 3$（$n - 1$ 个 $3$）这样的数，通过判断 $n$ 是否为 $1$ 进行输出。
  ```cpp
  // 此处未给出具体代码，根据思路推测核心代码结构如下
  int n;
  cin >> n;
  if (n == 1) cout << -1 << endl;
  else {
      cout << 2;
      for (int i = 1; i < n; ++i) cout << 3;
      cout << endl;
  }
  ```
- **andyli（4星）**
  - **关键亮点**：简洁地构造出符合要求的数字，明确指出时间复杂度，代码逻辑清晰。
  ```cpp
  int main()
  {
      int q;
      io.read(q);
      while (q--) {
          int n;
          io.read(n);
          if (n == 1) {
              writeln(-1);
              continue;
          }
          io.putch('2');
          for (int i = 2; i <= n; i++)
              io.putch('3');
          writeln();
      }
      return 0;
  }
  ```

### 最优关键思路或技巧
利用数字的整除特性来构造满足条件的数是关键技巧。例如利用 $3$ 的整除性质构造出大部分数位为 $3$ 的数，或者利用能被 $7$ 整除的数的形式进行调整构造。同时，要注意对 $n = 1$ 的特殊情况进行特判。

### 拓展
同类型题可考察不同数字整除特性的组合运用，类似算法套路是深入分析数字特性，找到切入点进行构造。

### 洛谷题目推荐
1. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：涉及数学构造和数论知识。
2. [P1463 [POI2002][HAOI2007]反素数](https://www.luogu.com.cn/problem/P1463)：通过分析数字特性进行构造求解。
3. [P2602 [ZJOI2010]数字计数](https://www.luogu.com.cn/problem/P2602)：利用数字的组成和特性解决计数问题。

### 个人心得
无。

---
处理用时：61.56秒