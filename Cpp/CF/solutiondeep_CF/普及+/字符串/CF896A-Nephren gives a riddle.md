# 题目信息

# Nephren gives a riddle

## 题目描述

奈芙莲有一个字符串数组 $f_{0\dots\infty}$。

$f_0$ 为 `What are you doing at the end of the world? Are you busy? Will you save us?`。

她想让更多人了解这个数组，所以她定义：

$$
\forall i\ge 1,f_i=\texttt{What are you doing while sending "}+f_{i-1}\\
+\texttt{"? Are you busy? Will you send "}+f_{i-1}+\texttt{"?}
$$

**注意其中的引号。**

奈芙莲会询问 $q$ 次，第 $i$ 次给定 $n,k$，你需要求出 $f_{n,k}$ 的值。**注意字符串从 $1$ 开始。**

## 说明/提示

对于所有数据，$1\le q\le 10,1\le n\le 10^5,1\le k\le 10^{18}$。

## 样例 #1

### 输入

```
3
1 1
1 2
1 111111111111
```

### 输出

```
Wh.```

## 样例 #2

### 输入

```
5
0 69
1 194
1 139
0 47
1 66
```

### 输出

```
abdef```

## 样例 #3

### 输入

```
10
4 1825
3 75
3 530
4 1829
4 1651
3 187
4 584
4 255
4 774
2 474
```

### 输出

```
Areyoubusy```

# AI分析结果



# Nephren 给出谜题

## 题目描述

奈芙莲有一个字符串数组 $f_{0\dots\infty}$。

$f_0$ 为 `What are you doing at the end of the world? Are you busy? Will you save us?`。

她定义递推式：

$$
\forall i\ge 1,f_i=\texttt{What are you doing while sending "}+f_{i-1}\\
+\texttt{"? Are you busy? Will you send "}+f_{i-1}+\texttt{"?}
$$

**注意其中的引号。**

对于 $q$ 次询问，每次给定 $n,k$，求 $f_{n}$ 的第 $k$ 个字符（从1开始计数），若不存在则输出 `.`。

## 综合题解分析

### 算法核心
所有题解均采用递归分解字符串结构的思路，将 $f_n$ 分解为五个固定部分和两个递归部分。通过预计算字符串长度避免直接构造，并处理指数级增长的溢出情况。

### 关键优化点
1. **长度预计算**：建立 $len[n]$ 数组记录各层字符串长度，当 $n \geq 55$ 时长度超过 $10^{18}$，直接视为无穷大。
2. **递归定位**：将字符串分为固定前缀、递归部分、固定中缀、递归部分、固定后缀，通过逐层减去前序长度定位字符位置。
3. **临界处理**：当 $n$ 足够大时，固定前缀长度远小于 $k$，可直接进入递归部分处理。

---

## 精选题解（评分≥4星）

### 题解1：Fuko_Ibuki（5星）
**关键亮点**：
- 预处理长度数组时明确处理溢出值（n≥55）
- 代码结构简洁，将固定部分定义为独立字符串
- 递归逻辑清晰，五段式划分明确

**核心代码**：
```cpp
char work(int n,ll k) {
    if (k>changdu[n]) return '.'; // 越界处理
    if (n==0) return f0[k];       // 基准情况
    if (k<r1) return a1[k];      // 固定前缀
    k -= r1;
    if (k<changdu[n-1]) return work(n-1,k); // 递归部分1
    k -= changdu[n-1];
    if (k<r2) return a2[k];      // 固定中缀
    k -= r2;
    if (k<changdu[n-1]) return work(n-1,k); // 递归部分2
    k -= changdu[n-1];
    if (k<r3) return a3[k];      // 固定后缀
    return '.';
}
```

### 题解2：Leap_Frog（5星）
**关键亮点**：
- 使用常量字符串定义各固定部分
- 显式划分五个区间，注释清晰
- 处理高n值时直接进入递归逻辑

**核心代码**：
```cpp
char dfs(int n,ll k) {
    if (k>f[n]) return '.'; 
    if (n==0) return A[k];       // 基准情况
    if (k<(int)Z1.size()) return Z1[k]; // 固定前缀
    k -= Z1.size();
    if (k<f[n-1]) return dfs(n-1,k);   // 递归部分1
    k -= f[n-1];
    if (k<(int)Z2.size()) return Z2[k]; // 固定中缀
    k -= Z2.size();
    if (k<f[n-1]) return dfs(n-1,k);   // 递归部分2
    k -= f[n-1];
    if (k<(int)Z3.size()) return Z3[k]; // 固定后缀
    return '.';
}
```

### 题解3：__delta_epsilon__（4星）
**关键亮点**：
- 详细数学公式描述递归过程
- 显式处理每个区间的边界条件
- 使用字符串常量增强可读性

**核心代码**：
```cpp
char calc(int n, int l) {
    if (n == 0) return f0[l-1];
    if (l <= s1.size()) return s1[l-1];
    else if (...) // 递归处理各区间
}
```

---

## 关键思路总结
1. **递归分治**：将复杂字符串拆解为固定部分和递归部分，通过不断缩小问题规模定位字符。
2. **预计算优化**：提前计算各层长度并处理溢出值，避免重复计算。
3. **边界处理**：对n≥55的特殊处理是避免数值溢出的关键技巧。

---

## 拓展练习
1. [P1928 外星密码](https://www.luogu.com.cn/problem/P1928)（递归解析嵌套字符串）
2. [P1498 母牛的故事](https://www.luogu.com.cn/problem/P1498)（递推关系与字符串构造）
3. [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)（递归分解数字结构）

---
处理用时：72.42秒