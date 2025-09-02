# 题目信息

# Nirvana

## 题目描述

Kurt reaches nirvana when he finds the product of all the digits of some positive integer. Greater value of the product makes the nirvana deeper.

Help Kurt find the maximum possible product of digits among all integers from $ 1 $ to $ n $ .

## 说明/提示

In the first example the maximum product is achieved for $ 389 $ (the product of digits is $ 3\cdot8\cdot9=216 $ ).

In the second example the maximum product is achieved for $ 7 $ (the product of digits is $ 7 $ ).

In the third example the maximum product is achieved for $ 999999999 $ (the product of digits is $ 9^9=387420489 $ ).

## 样例 #1

### 输入

```
390
```

### 输出

```
216
```

## 样例 #2

### 输入

```
7
```

### 输出

```
7
```

## 样例 #3

### 输入

```
1000000000
```

### 输出

```
387420489
```

# AI分析结果

### 题目内容重写

# Nirvana

## 题目描述

Kurt 在找到一个正整数的所有数字的乘积时，达到了涅槃。乘积的值越大，涅槃的深度越深。

帮助 Kurt 找到从 $1$ 到 $n$ 的所有整数中，数字乘积的最大值。

## 说明/提示

在第一个样例中，最大乘积为 $389$（数字乘积为 $3\cdot8\cdot9=216$）。

在第二个样例中，最大乘积为 $7$（数字乘积为 $7$）。

在第三个样例中，最大乘积为 $999999999$（数字乘积为 $9^9=387420489$）。

## 样例 #1

### 输入

```
390
```

### 输出

```
216
```

## 样例 #2

### 输入

```
7
```

### 输出

```
7
```

## 样例 #3

### 输入

```
1000000000
```

### 输出

```
387420489
```

### 算法分类
贪心

### 题解分析与结论

本题的核心目标是找到从 $1$ 到 $n$ 的所有整数中，数字乘积的最大值。各题解主要采用了贪心、递归、数位 DP 等方法来解决问题。贪心算法的思路是通过枚举每一位，将当前位减一，并将后面的位设为 9，从而得到最大乘积。递归和数位 DP 则通过分解问题，逐步求解每一位的最大乘积。

### 精选题解

#### 题解1：xiaohuang (赞：6)
- **星级**：★★★★★
- **关键亮点**：使用递归方法，通过枚举每一位，选择直接用那一位的数或者退位，简洁高效。
- **核心代码**：
```cpp
int f(int x) {
    if (x < 10) {
        if (x == 0) return 1; else return x;
    }
    return max((x % 10) * f(x / 10), 9 * f(x / 10 - 1));
}
```
- **实现思想**：递归求解每一位的最大乘积，通过选择当前位或退位来优化结果。

#### 题解2：Diaоsi (赞：4)
- **星级**：★★★★
- **关键亮点**：提供了贪心和数位 DP 两种解法，数位 DP 的解法较为复杂但通用性强。
- **核心代码**：
```cpp
long long dfs(long long pos, long long lst, bool l1, bool l2) {
    if (!pos) return 1;
    if (!l1 && !l2 && f[pos][lst] != -1) return f[pos][lst];
    long long tmp = -INF, up = l1 ? p[pos] : 9;
    for (long long i = 0; i <= up; i++)
        tmp = Max(tmp, ((l2 && !i) ? 1 : i) * dfs(pos - 1, i, (!(l2 && !i)) && (l1 && i == up), (l2 && !i)));
    if (!l1 && !l2) f[pos][lst] = tmp;
    return tmp;
}
```
- **实现思想**：通过数位 DP 记录每一位的状态，逐步求解最大乘积。

#### 题解3：Fan_Tuan (赞：3)
- **星级**：★★★★
- **关键亮点**：通过两层循环，枚举每一位，将当前位减一，并将后面的位设为 9，简洁明了。
- **核心代码**：
```cpp
for (int i = 0; i < len; i++) {
    long long gg = s[i] - '0' - 1;
    if (s[i] == '1') gg = 1;
    for (int j = 0; j < i; j++) gg *= (s[j] - '0');
    for (int j = i + 1; j < len; j++) gg *= 9;
    ans = max(ans, gg);
}
```
- **实现思想**：通过枚举每一位，将当前位减一，并将后面的位设为 9，计算最大乘积。

### 最优关键思路
贪心算法的核心思路是通过枚举每一位，将当前位减一，并将后面的位设为 9，从而得到最大乘积。这种方法简洁高效，适用于大部分情况。

### 拓展思路
类似的问题可以扩展到其他数字操作，如数字和、数字平方和等。贪心算法在这些问题中也有广泛应用。

### 推荐题目
1. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
2. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)
3. [P1062 数列](https://www.luogu.com.cn/problem/P1062)

---
处理用时：35.95秒