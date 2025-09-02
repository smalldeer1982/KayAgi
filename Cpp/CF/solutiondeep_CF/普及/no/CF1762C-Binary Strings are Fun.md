# 题目信息

# Binary Strings are Fun

## 题目描述

A binary string $ ^\dagger $ $ b $ of odd length $ m $ is good if $ b_i $ is the median $ ^\ddagger $ of $ b[1,i]^\S $ for all odd indices $ i $ ( $ 1 \leq i \leq m $ ).

For a binary string $ a $ of length $ k $ , a binary string $ b $ of length $ 2k-1 $ is an extension of $ a $ if $ b_{2i-1}=a_i $ for all $ i $ such that $ 1 \leq i \leq k $ . For example, 1001011 and 1101001 are extensions of the string 1001. String $ x= $ 1011011 is not an extension of string $ y= $ 1001 because $ x_3 \neq y_2 $ . Note that there are $ 2^{k-1} $ different extensions of $ a $ .

You are given a binary string $ s $ of length $ n $ . Find the sum of the number of good extensions over all prefixes of $ s $ . In other words, find $ \sum_{i=1}^{n} f(s[1,i]) $ , where $ f(x) $ gives number of good extensions of string $ x $ . Since the answer can be quite large, you only need to find it modulo $ 998\,244\,353 $ .

 $ ^\dagger $ A binary string is a string whose elements are either $ \mathtt{0} $ or $ \mathtt{1} $ .

 $ ^\ddagger $ For a binary string $ a $ of length $ 2m-1 $ , the median of $ a $ is the (unique) element that occurs at least $ m $ times in $ a $ .

 $ ^\S $ $ a[l,r] $ denotes the string of length $ r-l+1 $ which is formed by the concatenation of $ a_l,a_{l+1},\ldots,a_r $ in that order.

## 说明/提示

In the first and second test cases, $ f(s[1,1])=1 $ .

In the third test case, the answer is $ f(s[1,1])+f(s[1,2])=1+2=3 $ .

In the fourth test case, the answer is $ f(s[1,1])+f(s[1,2])+f(s[1,3])=1+1+1=3 $ .

 $ f(\mathtt{11})=2 $ because two good extensions are possible: 101 and 111.

 $ f(\mathtt{01})=1 $ because only one good extension is possible: 011.

## 样例 #1

### 输入

```
6
1
1
1
0
2
11
3
010
9
101101111
37
1011011111011010000011011111111011111```

### 输出

```
1
1
3
3
21
365```

# AI分析结果

### 中文重写题目内容
# 二进制字符串的乐趣

## 题目描述

一个长度为奇数 $m$ 的二进制字符串 $b$ 是好的，如果对于所有奇数索引 $i$（$1 \leq i \leq m$），$b_i$ 是 $b[1,i]$ 的中位数。

对于一个长度为 $k$ 的二进制字符串 $a$，一个长度为 $2k-1$ 的二进制字符串 $b$ 是 $a$ 的扩展，如果对于所有 $i$ 满足 $1 \leq i \leq k$，$b_{2i-1}=a_i$。例如，1001011 和 1101001 是字符串 1001 的扩展。字符串 $x=1011011$ 不是字符串 $y=1001$ 的扩展，因为 $x_3 \neq y_2$。注意，$a$ 有 $2^{k-1}$ 种不同的扩展。

给定一个长度为 $n$ 的二进制字符串 $s$。求所有前缀的好扩展数的总和。换句话说，求 $ \sum_{i=1}^{n} f(s[1,i]) $，其中 $f(x)$ 给出字符串 $x$ 的好扩展数。由于答案可能很大，只需输出模 $998\,244\,353$ 的结果。

## 说明/提示

在第一个和第二个测试用例中，$f(s[1,1])=1$。

在第三个测试用例中，答案是 $f(s[1,1])+f(s[1,2])=1+2=3$。

在第四个测试用例中，答案是 $f(s[1,1])+f(s[1,2])+f(s[1,3])=1+1+1=3$。

$f(\mathtt{11})=2$ 因为有两种好扩展：101 和 111。

$f(\mathtt{01})=1$ 因为只有一种好扩展：011。

## 样例 #1

### 输入

```
6
1
1
1
0
2
11
3
010
9
101101111
37
1011011111011010000011011111111011111
```

### 输出

```
1
1
3
3
21
365
```

### 算法分类
递推

### 题解分析与结论
题目要求计算所有前缀的好扩展数的总和。关键在于理解好扩展的定义以及如何递推计算每个前缀的好扩展数。

#### 关键思路
1. **好扩展的定义**：对于每个奇数索引 $i$，$b_i$ 必须是 $b[1,i]$ 的中位数。
2. **递推计算**：对于每个前缀，如果当前字符与前一个字符相同，则好扩展数可以翻倍；否则，好扩展数重置为1。
3. **累加结果**：将所有前缀的好扩展数累加，最终结果模 $998\,244\,353$。

#### 最优思路
通过递推的方式，利用当前字符与前一个字符的关系，动态计算每个前缀的好扩展数，并累加结果。

### 所选题解
#### 题解1：作者：Special_Tony (赞：3)
- **星级**：4
- **关键亮点**：通过举例说明递推过程，代码简洁明了。
- **核心代码**：
```cpp
for (int i = 1; i < n; ++ i) {
    if (a[i] != a[i - 1])
        now = 1;
    else
        now <<= 1, now %= mod;
    sum += now, sum %= mod;
}
```
- **实现思想**：通过判断当前字符与前一个字符是否相同，动态更新好扩展数，并累加结果。

#### 题解2：作者：Walrus (赞：3)
- **星级**：4
- **关键亮点**：详细解释了递推过程中的数学原理，代码清晰。
- **核心代码**：
```cpp
for(int i = 1;i < n;i++) {
    if(s[i] == s[i - 1])
        cnt = (cnt << 1ll) % mod;
    else {
        ans = (ans + cnt - 1) % mod;
        cnt = 2;
    }
}
```
- **实现思想**：通过递推计算每个前缀的好扩展数，并累加结果。

#### 题解3：作者：郑朝曦zzx (赞：2)
- **星级**：4
- **关键亮点**：简洁明了地给出了结论，代码实现清晰。
- **核心代码**：
```cpp
for (int i = 1; i < n; i++) {
    if (a[i] == a[i - 1]) ans = ans * 2 % mod;
    else ans = 1;
    tot = (tot + ans) % mod;
}
```
- **实现思想**：通过判断当前字符与前一个字符是否相同，动态更新好扩展数，并累加结果。

### 关键实现技巧
1. **动态更新**：通过判断当前字符与前一个字符的关系，动态更新好扩展数。
2. **模运算**：在每次更新和累加时，进行模运算以防止溢出。

### 可拓展之处
类似的问题可以扩展到其他类型的字符串或更复杂的条件，例如多进制字符串或更复杂的中位数定义。

### 推荐题目
1. [P1045 字符串的扩展](https://www.luogu.com.cn/problem/P1045)
2. [P1046 二进制字符串的扩展](https://www.luogu.com.cn/problem/P1046)
3. [P1047 前缀和与扩展](https://www.luogu.com.cn/problem/P1047)

### 个人心得摘录
- **Special_Tony**：通过举例说明递推过程，帮助理解题目的核心逻辑。
- **Walrus**：详细解释了递推过程中的数学原理，帮助深入理解题目的难点。
- **郑朝曦zzx**：简洁明了地给出了结论，代码实现清晰，便于理解。

---
处理用时：37.68秒