# 题目信息

# Special Numbers

## 题目描述

Theofanis really likes sequences of positive integers, thus his teacher (Yeltsa Kcir) gave him a problem about a sequence that consists of only special numbers.

Let's call a positive number special if it can be written as a sum of different non-negative powers of $ n $ . For example, for $ n = 4 $ number $ 17 $ is special, because it can be written as $ 4^0 + 4^2 = 1 + 16 = 17 $ , but $ 9 $ is not.

Theofanis asks you to help him find the $ k $ -th special number if they are sorted in increasing order. Since this number may be too large, output it modulo $ 10^9+7 $ .

## 说明/提示

For $ n = 3 $ the sequence is $ [1,3,4,9...] $

## 样例 #1

### 输入

```
3
3 4
2 12
105 564```

### 输出

```
9
12
3595374```

# AI分析结果

### 题目内容重写

**题目描述**

Theofanis 非常喜欢正整数的序列，因此他的老师（Yeltsa Kcir）给了他一个关于由特殊数字组成的序列的问题。

我们称一个正整数为特殊的，如果它可以表示为不同的非负整数次幂的 $n$ 的和。例如，对于 $n = 4$，数字 $17$ 是特殊的，因为它可以写成 $4^0 + 4^2 = 1 + 16 = 17$，但 $9$ 不是。

Theofanis 请你帮助他找到按递增顺序排列的第 $k$ 个特殊数字。由于这个数字可能太大，输出它模 $10^9+7$ 的结果。

**说明/提示**

对于 $n = 3$，序列是 $[1,3,4,9...]$

**样例 #1**

### 输入

```
3
3 4
2 12
105 564
```

### 输出

```
9
12
3595374
```

### 算法分类
**进制**

### 题解分析与结论

所有题解的核心思路都是将问题转化为进制转换问题，具体来说，将 $k$ 的二进制表示转换为 $n$ 进制表示，从而得到第 $k$ 个特殊数。这种思路的关键在于观察到特殊数的生成方式与二进制数的生成方式类似，只是将基数从 2 替换为 $n$。

### 所选高星题解

1. **作者：smyslenny (4星)**
   - **关键亮点**：通过举例 $n=2$ 的情况，直观地展示了二进制与特殊数之间的关系，代码简洁明了。
   - **代码核心实现**：
     ```cpp
     int sum=1,Ans=0;
     for(int i=0;i<31;i++)
     {
         if(k&(1<<i))
             Ans=(Ans+sum)%mod;
         sum=(sum*n)%mod;
     }
     ```
     这段代码通过遍历 $k$ 的二进制位，将每一位对应的 $n$ 的幂次累加到结果中。

2. **作者：清烛 (4星)**
   - **关键亮点**：直接指出将 $k$ 的二进制表示转换为 $n$ 进制表示，思路清晰，代码简洁。
   - **代码核心实现**：
     ```cpp
     int ans = 0;
     for (int pow = 1; k; k >>= 1, pow = 1ll * pow * n % mod) if (k & 1) ans = (ans + pow) % mod;
     ```
     这段代码通过不断右移 $k$ 并累加对应的 $n$ 的幂次，实现了相同的功能。

3. **作者：XL4453 (4星)**
   - **关键亮点**：通过数学归纳法证明了特殊数的生成方式与二进制数的生成方式类似，代码中使用了快速幂来优化计算。
   - **代码核心实现**：
     ```cpp
     long long pow(long long a,long long b){
         long long ans=1;
         while(b){
             if(b&1)ans=(ans*a)%MOD;
             a=(a*a)%MOD;
             b>>=1;
         }
         return ans;
     }
     ```
     这段代码实现了快速幂算法，用于高效计算 $n$ 的幂次。

### 最优关键思路或技巧
将 $k$ 的二进制表示转换为 $n$ 进制表示，从而得到第 $k$ 个特殊数。这种思路不仅适用于本题，还可以推广到其他进制转换问题中。

### 可拓展之处
类似的问题可以出现在其他进制转换或组合数学的题目中，例如给定一个基数 $n$，要求生成满足某种条件的数字序列。

### 推荐题目
1. [P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)
2. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)
3. [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)

### 个人心得摘录
- **smyslenny**：通过举例 $n=2$ 的情况，直观地展示了二进制与特殊数之间的关系，这种举例方法有助于理解问题的本质。
- **清烛**：直接指出将 $k$ 的二进制表示转换为 $n$ 进制表示，这种直接切入问题核心的思路非常高效。
- **XL4453**：通过数学归纳法证明了特殊数的生成方式与二进制数的生成方式类似，这种严谨的数学推导有助于加深对问题的理解。

---
处理用时：29.96秒