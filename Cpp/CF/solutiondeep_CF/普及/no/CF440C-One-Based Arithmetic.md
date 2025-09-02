# 题目信息

# One-Based Arithmetic

## 题目描述

Prof. Vasechkin wants to represent positive integer $ n $ as a sum of addends, where each addends is an integer number containing only 1s. For example, he can represent 121 as 121=111+11+–1. Help him to find the least number of digits 1 in such sum.

## 样例 #1

### 输入

```
121
```

### 输出

```
6
```

# AI分析结果



# One-Based Arithmetic

## 题目描述

Prof. Vasechkin 希望将正整数 $n$ 表示为若干个仅由 1 组成的整数的加减组合。例如，121 可以表示为 121=111+11-1。请找到这种表示中所需的最少 1 的个数。

## 样例 #1

### 输入
```
121
```

### 输出
```
6
```

**算法分类**：深度优先搜索（DFS） + 剪枝

---

### 题解综合分析

#### 核心思路对比
1. **Shine 的 DFS 解法**  
   - 从最高位逐位消减，每次处理有两种策略：  
     a. 用当前位数的 1 组成的数多次相减  
     b. 用更高一位的 1 组成的数减去当前值，转化为处理余数  
   - 通过最优性剪枝（sum >= ans 时直接返回）优化搜索  
   - 关键数据结构：预先生成的 1 组成的数数组 one[17]

2. **ForeverCIL 的递归解法**  
   - 递归分解问题，每次用 dig 位的 1 处理当前值：  
     a. 尽可能多地使用 dig 位的 1（use = x / A[dig]）  
     b. 对余数选择两种处理方式：  
        i. 继续用 dig-1 位的 1 处理余数  
        ii. 用 dig 位的 1 减去余数，转化为对新余数的处理  
   - 通过 min() 函数直接取最优解  
   - 预生成 1 组成的数数组 A[20]

#### 解决难点
- **指数级搜索空间优化**：利用 1 组成数数量有限的特性（最多 15 种），将问题转化为分层处理  
- **减法转换技巧**：将减法操作转化为更高位数的 1 减去当前值的加法形式  
- **最优性剪枝**：在 DFS 中及时终止无效分支  

---

### 高星题解推荐

#### 1. ForeverCIL 的递归解法（⭐⭐⭐⭐⭐）
**关键亮点**：  
- 递归设计简洁，利用数学性质将问题分解为两种策略的最小值  
- 预处理 1 组成的数数组提升效率  
- 代码可读性极强，仅需 20 行核心逻辑  

**核心代码**：
```cpp
ll dfs(ll x, ll dig) {
    ll use = x / A[dig];
    x %= A[dig];
    if (x == 0) return dig * use;
    return dig * use + min(
        dig + dfs(A[dig] - x, dig - 1), // 减法转换策略
        dfs(x, dig - 1)                 // 继续处理余数策略
    );
}
```

#### 2. Shine 的 DFS 解法（⭐⭐⭐⭐）
**关键亮点**：  
- 显式处理正负数，适用性更广  
- 通过逐位削减小技巧降低问题规模  
- 最优性剪枝提升搜索效率  

**核心代码**：
```cpp
void dfs(ll x, int sum) {
    if (sum >= ans) return; // 剪枝
    if (x == 0) ans = sum;
    ll h = pow(10, t-1);    // 计算当前位数阈值
    // 两种策略处理余数
    dfs(reta, sum + sa);    // 直接削除策略
    dfs(retb, sum + sb);    // 高位减法策略
}
```

---

### 最优技巧总结
1. **分层递归分解**：将问题按数位分层处理，从高位到低位逐步消减  
2. **减法转换技巧**：用更高位数的 1 减去余数，将减法转化为加法处理  
3. **预处理加速**：预生成 1 组成的数数组避免重复计算  
4. **剪枝优化**：在 DFS 中及时终止非最优路径  

---

### 同类题目推荐
1. [P2327 火柴棒等式](https://www.luogu.com.cn/problem/P2327)  
   **相似点**：枚举特定结构的数进行组合  

2. [P1217 回文质数](https://www.luogu.com.cn/problem/P1217)  
   **相似点**：数位特性分析与递归搜索  

3. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)  
   **相似点**：动态规划与分层处理思想

---
处理用时：76.18秒