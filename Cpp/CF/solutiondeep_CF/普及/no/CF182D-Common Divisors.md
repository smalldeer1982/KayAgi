# 题目信息

# Common Divisors

## 题目描述

Vasya has recently learned at school what a number's divisor is and decided to determine a string's divisor. Here is what he came up with.

String $ a $ is the divisor of string $ b $ if and only if there exists a positive integer $ x $ such that if we write out string $ a $ consecutively $ x $ times, we get string $ b $ . For example, string "abab" has two divisors — "ab" and "abab".

Now Vasya wants to write a program that calculates the number of common divisors of two strings. Please help him.

## 说明/提示

In first sample the common divisors are strings "abcd" and "abcdabcd".

In the second sample the common divisor is a single string "a". String "aa" isn't included in the answer as it isn't a divisor of string "aaa".

## 样例 #1

### 输入

```
abcdabcd
abcdabcdabcdabcd
```

### 输出

```
2
```

## 样例 #2

### 输入

```
aaa
aa
```

### 输出

```
1
```

# AI分析结果



# Common Divisors

## 题目描述

Vasya 最近在学校学习了数的约数概念，决定推广到字符串领域。字符串 $a$ 是字符串 $b$ 的约数，当且仅当存在正整数 $x$ 使得将 $a$ 重复 $x$ 次拼接后得到 $b$。例如字符串 "abab" 有两个约数："ab" 和 "abab"。

现在需要计算两个字符串的公共约数数量。

## 样例 #1

### 输入
```
abcdabcd
abcdabcdabcdabcd
```

### 输出
```
2
```

## 样例 #2

### 输入
```
aaa
aa
```

### 输出
```
1
```

**算法分类**：字符串、数学

---

### 题解综合分析

各题解核心思路均围绕两个关键点：1. 字符串循环节判定 2. 公约数统计。主流解法分为三类：

1. **KMP/PMT系**：利用前缀函数求最小循环节，将问题转化为求循环次数的公约数数量
2. **哈希系**：枚举可能的公约数长度，通过哈希快速验证分段匹配
3. **exKMP系**：通过Z函数直接计算循环节匹配长度

关键优化点：利用字符串循环节性质将问题分解为字符串验证+数论计算，将时间复杂度从 O(n²) 优化至 O(n)

---

### 精选题解

#### 1. OldVagrant（5星）
**亮点**：
- 通过KMP快速求解最小循环节
- 将问题转化为求两个数的公约数数量
- 线性时间复杂度 O(n + m)
- 代码包含高效读入优化

**关键代码**：
```cpp
// KMP求最小循环节核心部分
for(int i=2,j=0;i<=n;neA[i]=j,i++){
    while(j&&a[i]!=a[j+1]) j=neA[j];
    if(a[i]==a[j+1]) j++;
}
int p = n - neA[n];
while(n % p) p = neA[p]; // 调整至最小循环节长度

// 公约数统计
for(int i=1,j=n/p;i<=j;i++) 
    if(j%i==0) fac[i]=1;
for(int i=1,j=m/p;i<=j;i++) 
    if(j%i==0) ans += fac[i];
```

#### 2. 山田リョウ（4星）
**亮点**：
- 使用exKMP的Z函数快速判断循环节
- 代码简洁，逻辑清晰
- 线性时间复杂度 O(n + m)

**核心实现**：
```cpp
void exkmp(char*s,int*z,int n){
    for(int i=1,j=0,k=z[0]=0;i<n;++i){
        if(i<=k&&z[i-j]<=k-i) z[i]=z[i-j];
        else for(z[i]=(k+1>i?k+1-i:0);i+z[i]<n&&s[z[i]]==s[i+z[i]];++z[i]);
        if(z[i]+i-1>k) k=z[i]+i-1,j=i;
    }
}

// 判断循环节条件
if(z[i] + i == len && ...)
```

#### 3. Allanljx（4星）
**亮点**：
- 哈希解法直观易懂
- 使用滚动哈希优化验证过程
- 调和级数时间复杂度 O(n logn)

**关键技巧**：
```cpp
// 预处理哈希
for(int i=1;i<=l1;i++) 
    h1[i] = h1[i-1]*27 + s1[i]-'a';

// 分段验证
for(int j=i;j<=l1;j+=i)
    if(分段哈希 != 首段哈希) 标记失败
```

---

### 最优思路提炼

**关键技巧**：
1. **循环节定理**：若字符串由循环节构成，其长度必为最小循环节的整数倍
2. **KMP/exKMP加速**：利用字符串匹配算法快速求最小循环节
3. **数论转化**：将字符串问题转化为公约数统计问题

**实现要点**：
- 预处理最小循环节长度
- 验证两字符串的循环节一致性
- 统计循环次数的公约数数量

---

### 拓展练习

1. [P3435 OKR-Periodicity](https://www.luogu.com.cn/problem/P3435) - 强化版循环节问题
2. [CF1473B String LCM](https://codeforces.com/problemset/problem/1473/B) - 相同解法应用
3. [P4391 Radio Transmission](https://www.luogu.com.cn/problem/P4391) - 循环节基础练习

---

### 调试心得

在OldVagrant的代码中发现：
> "读入部分使用getchar特判处理，避免空字符干扰"  
> 说明处理输入边界的重要性，特别是当题目未明确保证输入格式时

山田リョウ提到：
> "发现循环节条件为z[i]+i==n，通过Z函数巧妙避免重复计算"  
> 体现对字符串算法的深刻理解，Z函数的多用途特性应用

---
处理用时：74.13秒