# 题目信息

# Array

## 题目描述

Chris the Rabbit has been interested in arrays ever since he was a child. At the moment he is researching arrays with the length of $ n $ , containing only integers from $ 1 $ to $ n $ . He is not good at math, that's why some simple things drive him crazy. For example, yesterday he grew keen on counting how many different beautiful arrays there are. Chris thinks that an array is beautiful if it meets one of the two conditions:

- each elements, starting from the second one, is no more than the preceding one
- each element, starting from the second one, is no less than the preceding one

Having got absolutely mad at himself and at math, Chris came to Stewie and Brian to ask them for help. However, they only laughed at him and said that the answer is too simple and not interesting. Help Chris the Rabbit to find the answer at last.

## 样例 #1

### 输入

```
2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
```

### 输出

```
17
```

# AI分析结果



# 中文题目翻译

## 题目描述

Chris 兔子从小就对数组感兴趣。现在他正在研究长度为 $n$ 的数组，这些数组仅包含 $1$ 到 $n$ 的整数。由于数学不好，一些简单的问题会让他抓狂。例如，他最近在计算有多少不同的「美丽数组」。Chris 认为一个数组是美丽的，当且仅当满足以下两个条件之一：

- 每个元素（从第二个开始）都不超过前一个元素
- 每个元素（从第二个开始）都不小于前一个元素

Chris 向 Stewie 和 Brian 求助，但被嘲笑问题太简单。请你帮他找到答案。

## 样例 #1

### 输入
```
2
```

### 输出
```
4
```

## 样例 #2

### 输入
```
3
```

### 输出
```
17
```

---

# 题解分析与结论

**核心思路**：将问题转化为组合数学问题。计算所有单调不降/不增序列的数量，再减去重复计算的全相同序列。

**关键公式**：  
答案 = $2 \times C_{2n-1}^n - n$  
其中 $C_{2n-1}^n$ 为单调不降序列数量，乘以 2 得到两种方向（不降+不增），再减去 $n$ 种全相同序列的重复计算。

**解决难点**：  
1. **组合意义转化**：通过隔板法将序列构造转化为组合数计算。
2. **逆元处理**：使用费马小定理高效计算组合数模大质数。

---

# 精选题解

## 题解1：Prurite（5星）
**亮点**：  
- 清晰的双重转化思路（序列 → 元素集合 → 隔板法组合数）
- 数学推导简洁，完整解释重复项的扣除逻辑

**代码核心**：
```cpp
const int mod = 1e9+7;
LL ans = (2 * C(2*n-1, n) - n + mod) % mod;
// C(n,k) 通过预处理阶乘与逆元实现
```

## 题解2：pufanyi（4星）
**亮点**：  
- 通过动态规划打表发现杨辉三角规律
- 提供代码实现中的逆元快速幂模板

**关键推导**：
```cpp
// 预处理阶乘
for (int i=1; i<=2n; i++) fac[i] = fac[i-1] * i % mod;
// 组合数计算
LL C = fac[2n] * inv(fac[n]^2) % mod;
```

## 题解3：Ryan_Adam（4星）
**亮点**：  
- 最简公式直接给出结论 $C_{2n}^n - n$
- 代码中线性逆元预处理优化效率

**代码片段**：
```cpp
for(int i=2; i<=n; i++) 
    inv[i] = (mod - mod/i) * inv[mod%i] % mod;
ans = ans * inv[i] % mod * (n+i) % mod;
```

---

# 关键技巧与拓展

1. **组合数转化思维**：将序列构造问题转化为元素分配问题（如隔板法）。
2. **逆元快速计算**：掌握阶乘逆元预处理和费马小定理的应用。
3. **对称性利用**：通过镜像对称减少一半计算量（不降与不增对称）。

**同类题目推荐**：  
1. [P1754 球迷购票问题](https://www.luogu.com.cn/problem/P1754)  
2. [P4369 组合数问题](https://www.luogu.com.cn/problem/P4369)  
3. [P3197 越狱](https://www.luogu.com.cn/problem/P3197)

**心得摘录**：  
> “被卡特兰数误导半天，最终发现是更基础的组合模型”——需明确问题本质，避免盲目套用模板。

---
处理用时：54.40秒