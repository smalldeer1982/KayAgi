# 题目信息

# Polycarp and Div 3

## 题目描述

Polycarp likes numbers that are divisible by 3.

He has a huge number $ s $ . Polycarp wants to cut from it the maximum number of numbers that are divisible by $ 3 $ . To do this, he makes an arbitrary number of vertical cuts between pairs of adjacent digits. As a result, after $ m $ such cuts, there will be $ m+1 $ parts in total. Polycarp analyzes each of the obtained numbers and finds the number of those that are divisible by $ 3 $ .

For example, if the original number is $ s=3121 $ , then Polycarp can cut it into three parts with two cuts: $ 3|1|21 $ . As a result, he will get two numbers that are divisible by $ 3 $ .

Polycarp can make an arbitrary number of vertical cuts, where each cut is made between a pair of adjacent digits. The resulting numbers cannot contain extra leading zeroes (that is, the number can begin with 0 if and only if this number is exactly one character '0'). For example, 007, 01 and 00099 are not valid numbers, but 90, 0 and 10001 are valid.

What is the maximum number of numbers divisible by $ 3 $ that Polycarp can obtain?

## 说明/提示

In the first example, an example set of optimal cuts on the number is 3|1|21.

In the second example, you do not need to make any cuts. The specified number 6 forms one number that is divisible by $ 3 $ .

In the third example, cuts must be made between each pair of digits. As a result, Polycarp gets one digit 1 and $ 33 $ digits 0. Each of the $ 33 $ digits 0 forms a number that is divisible by $ 3 $ .

In the fourth example, an example set of optimal cuts is 2|0|1|9|201|81. The numbers $ 0 $ , $ 9 $ , $ 201 $ and $ 81 $ are divisible by $ 3 $ .

## 样例 #1

### 输入

```
3121
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1000000000000000000000000000000000
```

### 输出

```
33
```

## 样例 #4

### 输入

```
201920181
```

### 输出

```
4
```

# AI分析结果

### 题目重写

#### Polycarp 和 Div 3

##### 题目描述

Polycarp 喜欢能被 3 整除的数字。

他有一个非常大的数字 $s$。Polycarp 想从中切割出尽可能多的能被 3 整除的数字。为此，他可以在任意相邻的数字之间进行垂直切割。最终，经过 $m$ 次切割后，将得到 $m+1$ 个部分。Polycarp 会分析每个部分，并统计其中能被 3 整除的数字的个数。

例如，如果原始数字是 $s=3121$，Polycarp 可以通过两次切割将其分成三部分：$3|1|21$。最终，他将得到两个能被 3 整除的数字。

Polycarp 可以进行任意次数的垂直切割，每次切割都在相邻的数字之间进行。切割后的数字不能包含多余的前导零（即，数字可以以 0 开头，但只有当该数字恰好为 '0' 时才允许）。例如，007、01 和 00099 不是有效的数字，但 90、0 和 10001 是有效的。

Polycarp 最多能得到多少个能被 3 整除的数字？

##### 说明/提示

在第一个样例中，最优的切割方式是 3|1|21。

在第二个样例中，不需要进行任何切割。数字 6 本身就是一个能被 3 整除的数字。

在第三个样例中，必须在每对相邻数字之间进行切割。最终，Polycarp 将得到一个数字 1 和 33 个数字 0。每个数字 0 都能被 3 整除。

在第四个样例中，最优的切割方式是 2|0|1|9|201|81。数字 $0$、$9$、$201$ 和 $81$ 都能被 3 整除。

##### 样例 #1

###### 输入

```
3121
```

###### 输出

```
2
```

##### 样例 #2

###### 输入

```
6
```

###### 输出

```
1
```

##### 样例 #3

###### 输入

```
1000000000000000000000000000000000
```

###### 输出

```
33
```

##### 样例 #4

###### 输入

```
201920181
```

###### 输出

```
4
```

### 题解分析与结论

#### 综合分析

本题的核心问题是如何通过切割数字字符串，得到尽可能多的能被 3 整除的子数字。大多数题解采用了动态规划（DP）或贪心算法来解决这个问题。

1. **动态规划（DP）**：多个题解使用了 DP 的思路，通过维护一个数组 $f_i$ 表示前 $i$ 个字符最多能划分出多少段能被 3 整除的数字。转移方程通常为 $f_i = \max(f_{i-1}, f_j + 1)$，其中 $j$ 是满足 $\sum_{k=j}^i a_k \equiv 0 \pmod{3}$ 的位置。为了优化时间复杂度，许多题解通过数学分析将 $j$ 的枚举范围限制在 $[i-2, i]$ 内，从而将复杂度从 $O(n^2)$ 降低到 $O(n)$。

2. **贪心算法**：部分题解采用了贪心的策略，通过遍历字符串，累加当前数字的和，当满足某些条件（如当前数字是 3 的倍数，或累加和是 3 的倍数）时，立即进行切割。这种方法的优势在于实现简单，且时间复杂度为 $O(n)$。

3. **前缀和优化**：多个题解使用了前缀和来快速计算任意区间的和，从而判断是否能被 3 整除。这种方法在 DP 和贪心中都有应用，能够有效提升算法的效率。

#### 最优关键思路

- **DP 优化**：通过数学分析，将 DP 的转移范围限制在 $[i-2, i]$ 内，从而将时间复杂度从 $O(n^2)$ 降低到 $O(n)$。这是解决本题的关键优化点。
  
- **贪心策略**：在遍历字符串时，当满足某些条件（如当前数字是 3 的倍数，或累加和是 3 的倍数）时，立即进行切割。这种策略简单且高效，适用于大多数情况。

#### 推荐题解

1. **SUPERLWR 的题解**（4星）
   - **关键亮点**：采用了贪心算法，思路清晰，代码简洁，时间复杂度为 $O(n)$。
   - **代码核心**：
     ```cpp
     for(int i=0;i<len;i++) {
         pre+=str[i]-'0';
         cnt++;
         if(cnt==3||pre%3==0||(str[i]-'0')%3==0) {
             ans++;
             pre=0;
             cnt=0;
         }
     }
     ```

2. **Diaоsi 的题解**（4星）
   - **关键亮点**：使用了 DP 优化，通过数学分析将转移范围限制在 $[i-2, i]$ 内，时间复杂度为 $O(n)$。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++) {
         for(int j=i;j>=Max(1,i-2);j--) {
             f[i]=Max(f[i],f[j-1]+((sum[i]-sum[j-1])%3==0?1:0));
         }
     }
     ```

3. **wutiruo 的题解**（4星）
   - **关键亮点**：使用了 DP 和前缀和优化，思路清晰，代码简洁，时间复杂度为 $O(n)$。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++) {
         r=(r+s[i]-48)%3;
         dp[i]=dp[i-1];
         if(maxv[r]!=-1) dp[i]=max(dp[i],dp[maxv[r]]+1);
         maxv[r]=i;
     }
     ```

#### 推荐题目

1. **洛谷 P1044 [NOIP2003 普及组] 栈**（题号：P1044）
   - **考察知识点**：动态规划、卡特兰数

2. **洛谷 P1020 [NOIP1999 普及组] 导弹拦截**（题号：P1020）
   - **考察知识点**：动态规划、贪心算法

3. **洛谷 P1091 [NOIP2004 提高组] 合唱队形**（题号：P1091）
   - **考察知识点**：动态规划、最长上升子序列

---
处理用时：49.06秒