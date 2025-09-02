# 题目信息

# Balance the Bits

## 题目描述

A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters '+' and '1'. For example, sequences '(())()', '()', and '(()(()))' are balanced, while ')(', '(()', and '(()))(' are not.

You are given a binary string $ s $ of length $ n $ . Construct two balanced bracket sequences $ a $ and $ b $ of length $ n $ such that for all $ 1\le i\le n $ :

- if $ s_i=1 $ , then $ a_i=b_i $
- if $ s_i=0 $ , then $ a_i\ne b_i $

If it is impossible, you should report about it.

## 说明/提示

In the first test case, $ a= $ "()()()" and $ b= $ "((()))". The characters are equal in positions $ 1 $ , $ 3 $ , $ 4 $ , and $ 6 $ , which are the exact same positions where $ s_i=1 $ .

In the second test case, $ a= $ "()()((()))" and $ b= $ "(())()()()". The characters are equal in positions $ 1 $ , $ 4 $ , $ 5 $ , $ 7 $ , $ 8 $ , $ 10 $ , which are the exact same positions where $ s_i=1 $ .

In the third test case, there is no solution.

## 样例 #1

### 输入

```
3
6
101101
10
1001101101
4
1100```

### 输出

```
YES
()()()
((()))
YES
()()((()))
(())()()()
NO```

# AI分析结果

### 题目内容重写

#### 平衡括号序列

**题目描述**

一个括号序列被称为平衡的，如果可以通过添加字符 '+' 和 '1' 将其转换为一个合法的数学表达式。例如，序列 '(())()', '()', 和 '(()(()))' 是平衡的，而 ')(', '(()', 和 '(()))(' 不是。

给定一个长度为 $n$ 的二进制字符串 $s$，构造两个长度为 $n$ 的平衡括号序列 $a$ 和 $b$，使得对于所有 $1\le i\le n$：

- 如果 $s_i=1$，则 $a_i=b_i$
- 如果 $s_i=0$，则 $a_i\ne b_i$

如果无法构造，输出 "NO"。

**说明/提示**

在第一个测试用例中，$a= $ "()()()" 和 $b= $ "((()))"。字符在位置 $1$、$3$、$4$ 和 $6$ 相等，这些位置恰好是 $s_i=1$ 的位置。

在第二个测试用例中，$a= $ "()()((()))" 和 $b= $ "(())()()()"。字符在位置 $1$、$4$、$5$、$7$、$8$、$10$ 相等，这些位置恰好是 $s_i=1$ 的位置。

在第三个测试用例中，没有解。

**样例 #1**

**输入**

```
3
6
101101
10
1001101101
4
1100
```

**输出**

```
YES
()()()
((()))
YES
()()((()))
(())()()()
NO
```

### 算法分类
构造

### 题解分析与结论

本题的核心是通过给定的二进制字符串 $s$ 构造两个平衡的括号序列 $a$ 和 $b$，使得在 $s_i=1$ 的位置 $a_i$ 和 $b_i$ 相同，而在 $s_i=0$ 的位置 $a_i$ 和 $b_i$ 不同。主要难点在于如何确保构造的括号序列是平衡的，并且满足给定的条件。

#### 关键思路与技巧
1. **无解条件**：如果 $s$ 的首字符或尾字符为 '0'，或者 $s$ 中 '1' 的数量为奇数，则无法构造满足条件的括号序列。
2. **构造方法**：对于 $s_i=1$ 的位置，前一半填 '('，后一半填 ')'。对于 $s_i=0$ 的位置，交替填 '(' 和 ')'，并在 $a$ 和 $b$ 中互换。
3. **平衡性检查**：确保在构造过程中，括号序列在任何时刻都保持平衡，即左括号的数量始终大于或等于右括号的数量。

#### 推荐题解

1. **作者：hhoppitree (赞：29)**
   - **星级**：5星
   - **关键亮点**：详细解释了无解条件和构造方法，代码清晰且高效。
   - **核心代码**：
     ```cpp
     for (int i = 0; i < n; ++i) {
         if (s[i] == '1') {
             if(cnt) {
                 a[i] = b[i] = '(';
                 --cnt;
             } else{
                 a[i] = b[i] = ')';
             }
         }
     }
     char now = '(';
     for (int i = 0; i < n; ++i) {
         if (s[i] == '0') {
             a[i] = now;
             now ^= '(' ^ ')';
             b[i] = now;
         }
     }
     ```

2. **作者：Wallacewwz (赞：1)**
   - **星级**：4星
   - **关键亮点**：提供了详细的构造思路和代码实现，强调了无解条件的判断。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= n; i++) {
         if (s[i] == '1') {
             cnt1++;
             if (cnt1 <= cnt / 2) {
                 cout << "(";
                 ans.push_back('(');
             } else {
                 cout << ")";
                 ans.push_back(')');
             }
         } else {
             cnt2++;
             if (cnt2 % 2 == 1) {
                 cout << "(";
                 ans.push_back('(');
             } else {
                 cout << ")";
                 ans.push_back(')');
             }
         }
     }
     ```

3. **作者：lzy120406 (赞：1)**
   - **星级**：4星
   - **关键亮点**：通过贪心策略构造括号序列，并提供了详细的代码实现。
   - **核心代码**：
     ```cpp
     for (int i = 0; i < n; ++i) {
         if (s[i] == '1') {
             if (half1 > 0) {
                 a[i] = b[i] = '(';
                 half1--;
             } else {
                 a[i] = b[i] = ')';
             }
         } else {
             if (flip == 0) {
                 a[i] = '(';
                 b[i] = ')';
             } else {
                 a[i] = ')';
                 b[i] = '(';
             }
             flip = 1 - flip;
         }
     }
     ```

### 拓展思路
本题的构造方法可以推广到其他类似的括号序列问题，如构造多个平衡括号序列或处理更复杂的条件。类似的题目可以通过类似的贪心或构造方法解决。

### 推荐题目
1. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1241 括号序列](https://www.luogu.com.cn/problem/P1241)

---
处理用时：34.90秒