# 题目信息

# Dr. Evil Underscores

## 题目描述

Today, as a friendship gift, Bakry gave Badawy $ n $ integers $ a_1, a_2, \dots, a_n $ and challenged him to choose an integer $ X $ such that the value $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ is minimum possible, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

As always, Badawy is too lazy, so you decided to help him and find the minimum possible value of $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ .

## 说明/提示

In the first sample, we can choose $ X = 3 $ .

In the second sample, we can choose $ X = 5 $ .

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
2
1 5```

### 输出

```
4```

# AI分析结果



# Dr. Evil Underscores（中文重写）

## 题目描述

今天，Bakry 给了 Badawy $n$ 个整数 $a_1, a_2, \dots, a_n$ 作为友谊礼物，并挑战他选择一个整数 $X$，使得 $\underset{1 \leq i \leq n}{\max} (a_i \oplus X)$ 的值尽可能小，其中 $\oplus$ 表示按位异或运算。

你的任务是帮助 Badawy 找到这个最小可能值。

## 样例 #1

### 输入
```
3
1 2 3
```

### 输出
```
2
```

## 样例 #2

### 输入
```
2
1 5
```

### 输出
```
4
```

---

### 题解综合分析

#### 核心算法思想
所有题解均围绕**按位分治**和**Trie树结构**展开，核心思路是通过逐位处理二进制位（从高位到低位），根据当前位的分布情况决定最优的X取值，最终组合得到最小最大值。

#### 关键思路对比
1. **Trie树递归法**（基地A_I、Composite_Function）：
   - 建树模拟二进制位的分布
   - 递归处理节点：单子树直接继承，双子树累加当前位权重并取子问题最小值
   - 时间复杂度：$O(n \log C)$，空间复杂度：$O(n \log C)$

2. **直接分治法**（Pengzt、EternalHeart1314）：
   - 不显式建树，直接在数组上按位分治
   - 根据当前位将数组划分为0/1两个子集递归处理
   - 时间复杂度：$O(n \log C)$，空间复杂度：$O(n)$

3. **分治+ST表优化**（ix35）：
   - 结合排序和区间最值查询预处理
   - 通过查找最高不同位的位置进行决策
   - 时间复杂度：$O(n \log n)$

---

### 高分题解推荐（≥4星）

#### 1. 基地A_I（★★★★☆）
**关键亮点**：  
- 简洁优雅的分治实现，无需显式建树  
- 利用vector动态分割数据集，逻辑清晰  
- 代码可读性强，时间复杂度优秀  

**核心代码**：
```cpp
int Solve(vector<int> p, int K) {
    if(p.empty() || K<0) return 0;
    vector<int> p1, p2;
    for(int x : p) (x & (1<<K)) ? p1.push_back(x) : p2.push_back(x);
    if(p1.empty()) return Solve(p2, K-1);
    if(p2.empty()) return Solve(p1, K-1);
    return (1<<K) + min(Solve(p1,K-1), Solve(p2,K-1));
}
```

#### 2. EternalHeart1314（★★★★☆）
**关键亮点**：
- 极简分治实现，代码仅20行
- 通过位运算直接划分集合
- 完美处理边界条件，无冗余操作

**核心代码**：
```cpp
int dfs(vector<int> a, int bit) {
    if(!bit) return 0;
    vector<int> b, c;
    for(int x : a) (x>>(bit-1)&1) ? b.push_back(x) : c.push_back(x);
    if(b.empty()) return dfs(c, bit-1);
    if(c.empty()) return dfs(b, bit-1);
    return (1<<(bit-1)) + min(dfs(b,bit-1), dfs(c,bit-1));
}
```

#### 3. Composite_Function（★★★★☆）
**关键亮点**：
- 显式Trie树实现，结构直观
- 维护每个节点的子节点数量辅助决策
- 递归过程体现树形DP思想

**核心代码**：
```cpp
int ask(int p, int x) {
    if(x<0 || cnt[p]==0) return 0;
    if(cnt[p]==2) return (1<<x) + min(ask(trie[p][0],x-1), ask(trie[p][1],x-1));
    return ask(trie[p][trie[p][0]==0], x-1);
}
```

---

### 最优思路总结
**关键技巧**：  
1. **高位优先决策**：从最高位开始处理，确保高位优先最小化  
2. **分治递归**：根据当前位的0/1分布分割数据集，合并子问题结果  
3. **位运算优化**：使用位掩码和移位操作快速处理二进制位  

**同类型扩展**：  
- 适用于需要按位决策的最值问题（如异或最大值、与运算最大值等）  
- 类似题目特征：二进制位独立性、贪心可分解性  

---

### 推荐练习题
1. [CF1625D - Binary Spiders](https://www.luogu.com.cn/problem/CF1625D)  
   （位运算+贪心分治，难度：紫）  
2. [AT_abc281F - XOR World](https://www.luogu.com.cn/problem/AT_abc281F)  
   （双倍经验题，分治思路完全一致，难度：蓝）  
3. [P4592 [TJOI2018] 异或](https://www.luogu.com.cn/problem/P4592)  
   （可持久化Trie应用，难度：紫）  

---

### 调试心得摘录
- **ix35**提到：需要预处理区间最高不同位，否则分治可能退化为$O(n^2)$  
- **EXODUS**强调：排序是分治正确性的关键，确保同一位的0/1集中分布  
- **slzx2022YuYihan**踩坑：Trie树空间估算不足导致UKE（Runtime Error）

---
处理用时：70.86秒