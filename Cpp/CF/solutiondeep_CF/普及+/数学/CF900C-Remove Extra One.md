# 题目信息

# Remove Extra One

## 题目描述

You are given a permutation $ p $ of length $ n $ . Remove one element from permutation to make the number of records the maximum possible.

We remind that in a sequence of numbers $ a_{1},a_{2},...,a_{k} $ the element $ a_{i} $ is a record if for every integer $ j $ ( $ 1<=j&lt;i $ ) the following holds: $ a_{j}&lt;a_{i} $ .

## 说明/提示

In the first example the only element can be removed.

## 样例 #1

### 输入

```
1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
5 1 2 3 4
```

### 输出

```
5
```

# AI分析结果



# Remove Extra One

## 题目描述

给定一个长度为 $n$ 的排列 $p$，删除其中一个元素，使得剩余序列中"记录"的数量最多。当存在多个解时，输出数值最小的元素。

我们定义序列 $a_1,a_2,...,a_k$ 中的元素 $a_i$ 为记录，当且仅当对于所有 $j < i$ 都有 $a_j < a_i$。

## 样例

### 样例 #1
输入：
```
1
1
```
输出：
```
1
```

### 样例 #2
输入：
```
5
5 1 2 3 4
```
输出：
```
5
```

---

## 题解分析

### 精选题解（评分≥4星）

#### 题解作者：LJ07（★★★★☆）
**关键思路**：
1. 维护当前最大值和次大值，分类讨论每个元素的贡献
2. 当元素是当前最大值时，删除它会使总记录数-1
3. 当元素介于最大值和次大值之间时，删除最大值会使其成为新记录
4. 时间复杂度 O(n)，空间复杂度 O(n)

**核心代码**：
```cpp
int main() {
    int n, a[N], delta[N] = {0};
    int max1 = 0, max2 = 0; // 最大值和次大值的索引
    
    for (int i = 1; i <= n; i++) {
        if (a[i] > a[max1]) {
            delta[i]--;      // 情况1：自身是记录
            max2 = max1;     // 更新次大值
            max1 = i;        // 更新最大值
        } else if (a[i] > a[max2]) {
            delta[max1]++;   // 情况3：删除max1可使当前元素成为记录
            max2 = i;        // 更新次大值
        }
    }
    
    // 找出最大贡献的最小元素
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        if (delta[i] > delta[ans] || 
           (delta[i] == delta[ans] && a[i] < a[ans])) {
            ans = i;
        }
    }
    cout << a[ans];
}
```

#### 题解作者：Robin_kool（★★★★☆）
**亮点**：
1. 使用双指针动态维护最大次大值
2. 贡献数组记录每个元素的净收益
3. 处理了贡献相等时取较小值的边界条件

**调试心得**：
> 最初未考虑贡献相等时取较小值的情况，通过添加 `a[i] < a[ans]` 的判断修正

#### 题解作者：Raymondzll（★★★★☆）
**优化点**：
1. 简化变量命名，使用 x,y 代替 max1,max2
2. 直接在遍历过程中更新贡献值
3. 代码行数最精简（仅20行核心逻辑）

---

## 最优解法总结

**核心算法**：
- **双指针维护极值**：在遍历时动态维护当前最大值和次大值
- **贡献度差分**：通过 delta 数组记录删除每个元素对总记录数的影响
- **贪心比较**：先比较贡献度，贡献度相同时取较小元素

**关键技巧**：
1. **分类讨论思想**：将元素的记录可能性分为三种情况处理
2. **空间换时间**：使用 O(n) 的额外空间存储贡献值，避免重复计算
3. **极值更新策略**：通过值比较和索引交换实现 O(1) 复杂度的极值维护

---

## 拓展练习

1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)  
   （树状数组维护前驱最大值）
   
2. [P1776 宝物筛选](https://www.luogu.com.cn/problem/P1776)  
   （动态维护极值的背包问题）

3. [P2947 [USACO09MAR] Look Up S](https://www.luogu.com.cn/problem/P2947)  
   （单调栈维护右侧第一个更大元素）

---
处理用时：58.22秒