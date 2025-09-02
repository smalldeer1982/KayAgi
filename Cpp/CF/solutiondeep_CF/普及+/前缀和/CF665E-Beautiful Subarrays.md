# 题目信息

# Beautiful Subarrays

## 题目描述

One day, ZS the Coder wrote down an array of integers $ a $ with elements $ a_{1},a_{2},...,a_{n} $ .

A subarray of the array $ a $ is a sequence $ a_{l},a_{l+1},...,a_{r} $ for some integers $ (l,r) $ such that $ 1<=l<=r<=n $ . ZS the Coder thinks that a subarray of $ a $ is beautiful if the bitwise xor of all the elements in the subarray is at least $ k $ .

Help ZS the Coder find the number of beautiful subarrays of $ a $ !

## 样例 #1

### 输入

```
3 1
1 2 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 2
1 2 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3 3
1 2 3
```

### 输出

```
2
```

# AI分析结果



# Beautiful Subarrays

## 题目描述

有一天，ZS程序员写下了一个包含$n$个整数的数组$a$，元素为$a_1,a_2,...,a_n$。

数组$a$的子数组定义为满足$1 \leq l \leq r \leq n$的序列$a_l,a_{l+1},...,a_r$。当子数组中所有元素的按位异或值至少为$k$时，ZS认为这个子数组是美丽的。

请帮助ZS计算数组中所有美丽子数组的数量！

## 样例 #1

### 输入
```
3 1
1 2 3
```

### 输出
```
5
```

## 样例 #2

### 输入
```
3 2
1 2 3
```

### 输出
```
3
```

## 样例 #3

### 输入
```
3 3
1 2 3
```

### 输出
```
2
```

---

### 综合题解分析

#### 关键算法思路
所有高分题解均采用**异或前缀和 + 01Trie树**的组合解法：
1. 定义前缀异或和数组$s$，其中$s_i = a_1 \oplus a_2 \oplus ... \oplus a_i$
2. 将问题转化为求$s_r \oplus s_{l-1} \geq k$的二元组数量
3. 使用01Trie树动态维护历史前缀和，支持快速查询满足条件的数对

#### 最优思路亮点
1. **按位处理策略**：从最高位到最低位逐位决策，通过比较当前位异或结果与k的对应位，决定是否累加子树计数或继续搜索
2. **动态插入机制**：在枚举右端点时，将前一个前缀和插入Trie树，确保查询范围始终为历史数据
3. **位运算优化**：使用位掩码操作快速提取特定位，通过移位运算模拟二进制位比较

---

### 精选题解推荐

#### 1. 作者：Kobe303（⭐⭐⭐⭐⭐）
**核心亮点**：
- 最清晰的位处理逻辑，分离k的位判断与异或计算
- 简洁的Trie树插入/查询实现，维护经过次数而非传统end标记
- 完整处理等于k的情况

**关键代码解析**：
```cpp
int query(int x, int y) {  // x:当前前缀和，y:阈值k
    int p = 1, res = 0;
    for(int i=30; ~i; --i) {
        int c1 = (x>>i)&1, c2 = (y>>i)&1;
        if(c2) p = trie[p][c1^1];        // 必须异或得1
        else {                            // 可接受1或0
            res += cnt[trie[p][c1^1]];    // 异或得1直接累加
            p = trie[p][c1];             // 继续检查异或得0的情况
        }
    }
    return res + cnt[p];  // 最后加上等于的情况
}
```

#### 2. 作者：wanghaoyu1008（⭐⭐⭐⭐）
**独特优势**：
- 采用移位掩码处理32位整数
- 使用独立计数器数组优化空间
- 处理k=0的特殊情况技巧

**核心实现**：
```cpp
int work(int s) {
    int sum = 0, p = k, q = s;
    for(int i=0; i<=30; i++) {
        if(p的最高位为1) {
            // 必须选择异或得1的分支
        } else {
            // 累加异或得1的子树大小
        }
        p <<= 1; q <<= 1; // 移位处理下一位
    }
    // 插入当前前缀和到Trie
}
```

---

### 关键技巧总结
1. **异或性质转化**：将区间异或转化为两前缀和的异或
2. **二进制逐位决策**：通过高位到低位的位优先处理策略
3. **Trie树动态维护**：使用路径计数而非传统终点标记
4. **空间优化**：预分配大数组替代动态节点创建

---

### 拓展练习推荐
1. [P4735 最大异或和](https://www.luogu.com.cn/problem/P4735) - 动态维护异或区间
2. [P5283 异或粽子](https://www.luogu.com.cn/problem/P5283) - 前k大异或值问题 
3. [P4592 异或序列](https://www.luogu.com.cn/problem/P4592) - 树链剖分+异或特性

---

### 调试心得摘录
> "必须先将s0=0插入Trie，否则会漏算以第一个元素开头的子数组" —— 作者SentoAyaka  
> "k的最后一位要特殊处理，因为循环结束时可能刚好等于k" —— 作者mango09  
> "Trie树数组大小要按最大位数*元素数计算，否则RE" —— 作者TLE_Automat

---
处理用时：48.32秒