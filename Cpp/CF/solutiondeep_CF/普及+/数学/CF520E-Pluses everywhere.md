# 题目信息

# Pluses everywhere

## 题目描述

Vasya is sitting on an extremely boring math class. To have fun, he took a piece of paper and wrote out $ n $ numbers on a single line. After that, Vasya began to write out different ways to put pluses ("+") in the line between certain digits in the line so that the result was a correct arithmetic expression; formally, no two pluses in such a partition can stand together (between any two adjacent pluses there must be at least one digit), and no plus can stand at the beginning or the end of a line. For example, in the string 100500, ways 100500 (add no pluses), 1+00+500 or 10050+0 are correct, and ways 100++500, +1+0+0+5+0+0 or 100500+ are incorrect.

The lesson was long, and Vasya has written all the correct ways to place exactly $ k $ pluses in a string of digits. At this point, he got caught having fun by a teacher and he was given the task to calculate the sum of all the resulting arithmetic expressions by the end of the lesson (when calculating the value of an expression the leading zeros should be ignored). As the answer can be large, Vasya is allowed to get only its remainder modulo $ 10^{9}+7 $ . Help him!

## 说明/提示

In the first sample the result equals $ (1+08)+(10+8)=27 $ .

In the second sample the result equals $ 1+0+8=9 $ .

## 样例 #1

### 输入

```
3 1
108
```

### 输出

```
27```

## 样例 #2

### 输入

```
3 2
108
```

### 输出

```
9```

# AI分析结果



# Pluses everywhere

## 题目描述

Vasya 在数学课上无聊时，在一行上写了 $n$ 个数字。他想在所有正确放置恰好 $k$ 个加号的方式中，计算所有表达式值的总和。正确放置要求加号不能相邻，不能在开头或结尾。计算结果需对 $10^9+7$ 取模。

## 样例

### 输入1
```
3 1
108
```
### 输出1
```
27```

### 输入2
```
3 2
108
```
### 输出2
```
9```

---

### 综合题解分析

#### 关键思路
所有优质题解均采用组合数学思想，核心是计算每个数字在不同位数的贡献。核心技巧包括：
1. **贡献拆分**：将每个数字的贡献拆分为作为个位、十位、百位等不同位数的情形
2. **组合数预处理**：通过预处理阶乘和逆元快速计算组合数
3. **分治边界处理**：单独处理最后一个数字无法放置加号的特殊情形
4. **前缀和优化**：使用前缀和快速计算数字区间贡献

#### 最优题解推荐

##### 1. Heartlessly（⭐⭐⭐⭐⭐）
**核心亮点**：  
- 最清晰的数学推导，将贡献拆分为两个独立部分处理
- 完美处理边界条件，代码结构简洁
- 使用前缀和预处理优化时间复杂度至 O(n)

**关键代码**：
```cpp
for (int cur = 1, i = 1; i <= n - m; ++i, cur = 1ll * cur * 10 % MOD)
    ans = (ans + 1ll * cur * (1ll * pre[n - i] * c(n - 1 - i, m - 1) % MOD + 
    1ll * a[n - i + 1] * c(n - i, m) % MOD) % MOD) % MOD;
```

##### 2. QwQcOrZ（⭐⭐⭐⭐）
**核心亮点**：
- 巧妙的贡献拆分方式，将出现次数与数值分离
- 特判处理最后一位的特殊情况
- 使用前缀和与组合数分离计算

**关键洞见**：
```cpp
ans=(ans+a[n-i-1]*base[i]%p*C(k-1,n-i-2)%p)%p;
ans=(ans+(a[n-i]-a[n-i-1]+p)%p*base[i]%p*C(k,n-i-1)%p)%p;
```

##### 3. _Passerby_（⭐⭐⭐⭐）
**核心亮点**：
- 详细的数学推导过程
- 使用双重循环拆解贡献
- 清晰的边界条件处理说明

**公式推导**：
$$Ans = \sum_{j=0}^n10^j\times \left [ {{n-j-2}\choose {k-1}}\sum_{p=1}^{n-j-1}a_p +a_{n-j}\times {{n-p-1}\choose k}\right ]$$

---

### 关键技巧总结
1. **组合数预处理模板**：
```cpp
void init() {
    fac[0] = 1;
    for(int i=1;i<=n;i++) fac[i] = fac[i-1]*i%MOD;
    inv[n] = quickPow(fac[n], MOD-2);
    for(int i=n-1;i>=0;i--) inv[i] = inv[i+1]*(i+1)%MOD;
}
int C(int n, int m) {
    return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}
```

2. **贡献计算范式**：
```cpp
for(int i=0; i<n; i++){
    // 常规贡献
    ans += 前缀和 * 10^i * C(剩余位置, k-1)
    // 末尾特判
    ans += 末尾数字 * 10^j * C(前缀位置, k)
}
```

---

### 拓展练习
1. [P1591 阶乘数码](https://www.luogu.com.cn/problem/P1591)  
   （组合数计算与数位统计）
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)  
   （卡特兰数递推与组合分析）
3. [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)  
   （组合数与快速幂的综合应用）

---
处理用时：51.49秒