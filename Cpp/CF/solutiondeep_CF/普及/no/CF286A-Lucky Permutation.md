# 题目信息

# Lucky Permutation

## 题目描述

A permutation $ p $ of size $ n $ is the sequence $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct integers, each of them is from $ 1 $ to $ n $ $ (1<=p_{i}<=n) $ .

A lucky permutation is such permutation $ p $ , that any integer $ i $ $ (1<=i<=n) $ meets this condition $ p_{pi}=n-i+1 $ .

You have integer $ n $ . Find some lucky permutation $ p $ of size $ n $ .

## 样例 #1

### 输入

```
1
```

### 输出

```
1 
```

## 样例 #2

### 输入

```
2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4
```

### 输出

```
2 4 1 3 
```

## 样例 #4

### 输入

```
5
```

### 输出

```
2 5 3 1 4 
```

# AI分析结果



# Lucky Permutation

## 题目描述

一个长度为 $n$ 的排列 $p$ 是指由 $1$ 到 $n$ 的不同整数组成的序列 $p_1, p_2, ..., p_n$。

幸运排列满足对于所有整数 $i$ $(1 \le i \le n)$，有 $p_{p_i} = n - i + 1$。

给定整数 $n$，构造一个幸运排列。若不存在则输出 `-1`。

## 样例

### 样例 #1
输入：1  
输出：1 

### 样例 #2
输入：2  
输出：-1

### 样例 #3
输入：4  
输出：2 4 1 3 

### 样例 #4
输入：5  
输出：2 5 3 1 4 

---

**算法分类**：构造

---

### 综合分析与结论

所有题解均基于 **模4分组构造法**：当 $n \bmod 4 \in \{0,1\}$ 时存在解，否则无解。核心思路是将元素分为四元组循环交换，并处理中间元素（若存在）。

#### 高分题解推荐

1. **liuyifan（4星）**
   - **关键亮点**：高效分组处理，代码简洁
   - **代码核心**：
     ```cpp
     for(reg int i=1;i<=n>>1;i+=2) {
         ans[i] = i+1;
         ans[i+1] = n-i+1;
         ans[n-i+1] = n-i;
         ans[n-i] = i;
     }
     if(n%4) ans[(n>>1)+1] = (n>>1)+1;
     ```

2. **pyz51（5星）**
   - **关键亮点**：详细构造示例与数学证明
   - **代码核心**：
     ```cpp
     for(i=1; i+1 < n-i; i+=2) {
         a[i] = i+1;
         a[i+1] = n-i+1;
         a[n-i+1] = n-i;
         a[n-i] = i;
     }
     if(m == 1) a[i] = i;
     ```

3. **minVan（4星）**
   - **关键亮点**：清晰的条件判断与分组逻辑
   - **代码核心**：
     ```cpp
     for(int i=1; i<=(n>>1); i+=2) {
         a[i] = i+1, a[i+1] = n-i+1;
         a[n-i+1] = n-i, a[n-i] = i;
     }
     ```

---

### 关键思路总结

1. **模4判断**：仅当 $n \bmod 4 \in \{0,1\}$ 时有解
2. **四元组构造**：每个四元组满足 $p_i=i+1, p_{i+1}=n-i+1, p_{n-i+1}=n-i, p_{n-i}=i$
3. **中间处理**：当 $n$ 为奇数时，中间元素 $p_{(n+1)/2} = (n+1)/2$

---

### 拓展与练习

**相似题目推荐**：
1. [CF1152A - Neko Finds Grapes](https://www.luogu.com.cn/problem/CF1152A)（模数构造）
2. [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)（排列构造基础）
3. [CF1365D Solve The Maze](https://www.luogu.com.cn/problem/CF1365D)（构造性思维）

---
处理用时：47.18秒