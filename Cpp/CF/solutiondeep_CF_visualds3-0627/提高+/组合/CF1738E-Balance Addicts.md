# 题目信息

# Balance Addicts

## 题目描述

Given an integer sequence $a_1, a_2, \dots, a_n$ of length $n$, your task is to compute the number, modulo $998244353$, of ways to partition it into several **non-empty** **continuous** subsequences such that the sums of elements in the subsequences form a **balanced** sequence.

A sequence $s_1, s_2, \dots, s_k$ of length $k$ is said to be balanced, if $s_{i} = s_{k-i+1}$ for every $1 \leq i \leq k$. For example, $[1, 2, 3, 2, 1]$ and $[1,3,3,1]$ are balanced, but $[1,5,15]$ is not.

Formally, every partition can be described by a sequence of indexes $i_1, i_2, \dots, i_k$ of length $k$ with $1 = i_1 < i_2 < \dots < i_k \leq n$ such that

1.  $k$ is the number of non-empty continuous subsequences in the partition;
2.  For every $1 \leq j \leq k$, the $j$\-th continuous subsequence starts with $a_{i_j}$, and ends exactly before $a_{i_{j+1}}$, where $i_{k+1} = n + 1$. That is, the $j$\-th subsequence is $a_{i_j}, a_{i_j+1}, \dots, a_{i_{j+1}-1}$.

There are $2^{n-1}$ different partitions in total.

Let $s_1, s_2, \dots, s_k$ denote the sums of elements in the subsequences with respect to the partition $i_1, i_2, \dots, i_k$. Formally, for every $1 \leq j \leq k$,

$$
s_j = \sum_{i=i_{j}}^{i_{j+1}-1} a_i = a_{i_j} + a_{i_j+1} + \dots + a_{i_{j+1}-1}. 
$$
 For example, the partition $[1\,|\,2,3\,|\,4,5,6]$ of sequence $[1,2,3,4,5,6]$ is described by the sequence $[1,2,4]$ of indexes, and the sums of elements in the subsequences with respect to the partition is $[1,5,15]$.

Two partitions $i_1, i_2, \dots, i_k$ and $i'_1, i'_2, \dots, i'_{k'}$ (described by sequences of indexes) are considered to be different, if at least one of the following holds.

-   $k \neq k'$,
-   $i_j \neq i'_j$ for some $1 \leq j \leq \min\left\{ k, k' \right\}$.


## 说明/提示

For the first test case, there is only one way to partition a sequence of length $ 1 $ , which is itself and is, of course, balanced.

For the second test case, there are $ 2 $ ways to partition it:

- The sequence $ [1, 1] $ itself, then $ s = [2] $ is balanced;
- Partition into two subsequences $ [1\,|\,1] $ , then $ s = [1, 1] $ is balanced.

For the third test case, there are $ 3 $ ways to partition it:

- The sequence $ [0, 0, 1, 0] $ itself, then $ s = [1] $ is balanced;
- $ [0 \,|\, 0, 1 \,|\, 0] $ , then $ s = [0, 1, 0] $ is balanced;
- $ [0, 0 \,|\, 1 \,|\, 0] $ , then $ s = [0, 1, 0] $ is balanced.

For the fourth test case, there are $ 4 $ ways to partition it:

- The sequence $ [1, 2, 3, 2, 1] $ itself, then $ s = [9] $ is balanced;
- $ [1, 2 \,|\, 3 \,|\, 2, 1] $ , then $ s = [3, 3, 3] $ is balanced;
- $ [1 \,|\, 2, 3, 2 \,|\, 1] $ , then $ s = [1, 7, 1] $ is balanced;
- $ [1 \,|\, 2 \,|\, 3 \,|\, 2 \,|\, 1] $ , then $ s = [1, 2, 3, 2, 1] $ is balanced.

For the fifth test case, there are $ 2 $ ways to partition it:

- The sequence $ [1, 3, 5, 7, 9] $ itself, then $ s = [25] $ is balanced;
- $ [1, 3, 5 \,|\, 7 \,|\, 9] $ , then $ s = [9, 7, 9] $ is balanced.

For the sixth test case, every possible partition should be counted. So the answer is $ 2^{32-1} \equiv 150994942 \pmod {998244353} $ .

## 样例 #1

### 输入

```
6
1
1000000000
2
1 1
4
0 0 1 0
5
1 2 3 2 1
5
1 3 5 7 9
32
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0```

### 输出

```
1
2
3
4
2
150994942```

# AI分析结果



---

**唯一算法分类**：前缀和与组合数学结合的双指针法

---

### **题解思路、算法要点与解决难点**

1. **核心思路**  
   各题解均基于前缀和与后缀和的对称性，利用序列非负性带来的单调性，通过双指针寻找匹配的极长区间，计算组合数贡献。

2. **算法实现关键点**  
   - **前缀和与后缀和**：预处理前缀和 `pre[i]` 和后缀和 `suf[i]`，满足 `pre[i] = pre[i-1] + a[i]`，`suf[i] = suf[i+1] + a[i+1]`。  
   - **双指针匹配**：从左端 `l=1` 和右端 `r=n-1` 开始，寻找满足 `pre[l] = suf[r]` 的区间。  
   - **极长区间处理**：对每个匹配的值扩展极长区间 `[l_p, r_p]` 和 `[r_l, r_r]`，统计其长度。  
   - **组合数贡献**：对于每对区间，计算组合数之和 `ΣC(len1, k)*C(len2, k)`，利用范德蒙德卷积优化为 `C(len1+len2, len1)`。  
   - **中间点特判**：若总和为偶数且存在中点 `pre[i] = sum/2`，则贡献 `2^cnt`。

3. **解决难点**  
   - **单调性优化**：利用非负性保证前缀和单调不减，避免重复计算。  
   - **组合数快速计算**：预处理阶乘与逆元，支持 O(1) 组合数查询。  
   - **极长区间边界处理**：通过扩展指针确定区间范围，避免遗漏或重复。

---

### **最优思路提炼**

1. **对称性与双指针**  
   从两端向中间推进，每次找到对称的前缀和与后缀和，将问题分解为独立区间贡献的乘积。

2. **组合数乘积优化**  
   将极长区间的组合数求和转换为 `C(len1+len2, len1)`，时间复杂度从 O(n) 降为 O(1)。

3. **预处理与单调性利用**  
   预处理组合数工具，利用非负性保证区间唯一性，避免复杂判断。

---

### **题解评分（≥4星）**

1. **TKXZ133（5星）**  
   - **亮点**：通过映射统计每个值的出现次数，数学推导清晰，代码简洁。  
   - **关键代码**：`C(mp[x] + mp[sum-x], mp[x])` 处理贡献，特判中点乘幂。

2. **Alex_Wei（5星）**  
   - **亮点**：双指针实现极长区间扩展，逻辑严密，时间复杂度严格线性。  
   - **关键代码**：`while扩展区间` 和 `ΣC(len1, k)*C(len2, k)` 的组合数求和。

3. **elbissoPtImaerD（4星）**  
   - **亮点**：代码可读性强，双指针与组合数求和直观。  
   - **关键代码**：`for(k=0; k<=min(len1, len2); k++)` 枚举组合数。

---

### **核心代码实现**

**TKXZ133 的预处理与主逻辑**  
```cpp
// 预处理阶乘与逆元
fac[0] = 1;
for (int i = 1; i <= L; i++) fac[i] = fac[i-1] * i % mod;
inv[L] = q_pow(fac[L], mod-2);
for (int i = L; i >= 1; i--) inv[i-1] = inv[i] * i % mod;

// 主逻辑
map<int, int> mp;
for (int i = 1; i < n; i++) mp[sum[i]]++; // 统计前缀和出现次数
int pos = 1;
while (sum[pos] * 2 < sum[n]) {
    if (sum[pos] != sum[pos+1]) 
        ans = ans * C(mp[sum[pos]] + mp[sum[n]-sum[pos]], mp[sum[pos]]) % mod;
    pos++;
}
if (sum[n] % 2 == 0) 
    ans = ans * q_pow(2, mp[sum[n]/2]) % mod; // 特判中点
```

---

### **算法可视化设计**

1. **动画演示**  
   - **Canvas 绘制**：横向条形图表示序列，上方标注前缀和，下方标注后缀和。  
   - **双指针移动**：红色指针 `l` 从左向右，蓝色指针 `r` 从右向左移动，高亮当前比较的 `pre[l]` 和 `suf[r]`。  
   - **匹配成功**：绿色闪烁显示匹配区间，右侧显示当前贡献的组合数公式。  
   - **极长区间扩展**：用黄色框标出 `[l_p, r_p]` 和 `[r_l, r_r]`，动态绘制区间长度。

2. **复古像素风格**  
   - **8位色彩**：使用红、蓝、绿、黄等纯色块表示不同区域，背景为网格像素。  
   - **音效**：指针移动时播放“滴”声，匹配成功播放“叮”声，计算贡献时播放短旋律。

3. **交互控制**  
   - **步进控制**：用户可点击单步执行，观察指针移动和区间扩展。  
   - **自动模式**：AI自动运行，模拟双指针决策过程，速度可调。

---

### **相似题目推荐**

1. **CF1777C Quiz**  
   - 利用前缀和与组合数统计合法分割方式。

2. **Luogu P2679 子串**  
   - 双序列分割问题，需处理对称性子结构。

3. **LeetCode 647 回文子串**  
   - 基于中心扩展的回文对称性判断，可结合前缀和优化。

---

**总结**：本题通过前缀和与双指针技巧，将回文分割问题转化为组合数统计，利用单调性优化计算，是典型的分治与组合数学结合问题。

---
处理用时：71.92秒