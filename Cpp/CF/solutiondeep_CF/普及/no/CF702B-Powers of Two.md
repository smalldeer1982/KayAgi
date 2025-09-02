# 题目信息

# Powers of Two

## 题目描述

You are given $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Find the number of pairs of indexes $ i,j $ ( $ i&lt;j $ ) that $ a_{i}+a_{j} $ is a power of $ 2 $ (i. e. some integer $ x $ exists so that $ a_{i}+a_{j}=2^{x} $ ).

## 说明/提示

In the first example the following pairs of indexes include in answer: $ (1,4) $ and $ (2,4) $ .

In the second example all pairs of indexes $ (i,j) $ (where $ i&lt;j $ ) include in answer.

## 样例 #1

### 输入

```
4
7 3 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
3
```

# AI分析结果



# Powers of Two

## 题目描述

给定 $n$ 个整数 $a_1,a_2,...,a_n$，求满足 $i<j$ 且 $a_i + a_j$ 是 2 的幂次的索引对 $(i,j)$ 的数量（即存在某个整数 $x$ 使得 $a_i + a_j = 2^x$）。

## 说明/提示

样例1中满足条件的索引对为 $(1,4)$ 和 $(2,4)$。样例2中所有索引对均满足条件。

---

**算法分类**: 枚举、哈希表

---

### 综合分析结论

所有题解均采用哈希表（map）统计元素出现次数，并枚举可能的2的幂次方。核心优化点在于如何高效处理配对关系，避免重复计算。关键思路是预处理所有可能的2的幂次方，利用哈希表快速查找补数，并保证i<j的条件。

---

### 优质题解推荐

#### 1. IntrepidStrayer（4星）
**关键亮点**：逆向遍历数组避免重复，每次处理完元素后更新哈希表  
**核心代码思想**：
```cpp
for(枚举每个2的幂x) {
    map.clear();
    for(从后向前遍历数组) {
        ans += map中(x - a[i])的计数;
        将a[i]加入map;
    }
}
```
通过倒序遍历确保元素配对时i<j的条件自然成立，每次处理新幂次方时清空map保证独立计数。

#### 2. Eason_AC（4星）
**关键亮点**：正向遍历逐步更新哈希表，代码简洁  
**核心代码片段**：
```cpp
map<int, int> vis;
for(int i = 1; i <= n; ++i) {
    read(x);
    for(int j = 1; j <= 30; ++j)
        ans += vis[(1 << j) - x];
    vis[x]++;
}
```
在遍历时动态维护哈希表，当前元素只与之前处理过的元素配对，自然满足i<j的条件。

#### 3. ACtheQ（4星）
**关键亮点**：使用unordered_map优化查询速度，枚举0-30次方  
**代码亮点**：
```cpp
unordered_map<int, int> cnt;
for(int i=1; i<=n; i++) {
    cin >> a[i];
    for(int x=0; x<31; x++)
        ans += cnt[(1<<x) - a[i]];
    cnt[a[i]]++;
}
```
通过位运算快速计算2的幂次，利用unordered_map的O(1)查询特性提升效率。

---

### 最优思路提炼
1. **预处理幂次**：枚举所有可能的2的幂次（0 ≤ x ≤ 31，对应2⁰到2³¹）
2. **哈希表统计**：用哈希表记录已处理元素的出现次数
3. **动态维护顺序**：遍历元素时先查询补数数量再更新哈希表，保证i<j
4. **避免重复计算**：通过遍历顺序或数据结构的更新策略保证每个配对只计算一次

---

### 拓展与心得
**常见变式**：  
- 两数之和为特定值的变形（如立方数、质数等）
- 需考虑元素顺序的配对问题

**调试经验**：  
- 注意数值溢出（使用long long）
- 避免浮点运算（如log2直接使用位移代替）
- 相同元素的特殊处理（组合数公式）

---

### 推荐练习题
1. [P1102 A-B数对](https://www.luogu.com.cn/problem/P1102)（哈希统计差值为定值）
2. [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)（滑动窗口与哈希结合）
3. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)（异或特性与位运算应用）

---
处理用时：77.93秒