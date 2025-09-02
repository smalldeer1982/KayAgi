# 题目信息

# Longest Max Min Subsequence

## 题目描述

You are given an integer sequence $ a_1, a_2, \ldots, a_n $ . Let $ S $ be the set of all possible non-empty subsequences of $ a $ without duplicate elements. Your goal is to find the longest sequence in $ S $ . If there are multiple of them, find the one that minimizes lexicographical order after multiplying terms at odd positions by $ -1 $ .

For example, given $ a = [3, 2, 3, 1] $ , $ S = \{[1], [2], [3], [2, 1], [2, 3], [3, 1], [3, 2], [2, 3, 1], [3, 2, 1]\} $ . Then $ [2, 3, 1] $ and $ [3, 2, 1] $ would be the longest, and $ [3, 2, 1] $ would be the answer since $ [-3, 2, -1] $ is lexicographically smaller than $ [-2, 3, -1] $ .

A sequence $ c $ is a subsequence of a sequence $ d $ if $ c $ can be obtained from $ d $ by the deletion of several (possibly, zero or all) elements.

A sequence $ c $ is lexicographically smaller than a sequence $ d $ if and only if one of the following holds:

- $ c $ is a prefix of $ d $ , but $ c \ne d $ ;
- in the first position where $ c $ and $ d $ differ, the sequence $ c $ has a smaller element than the corresponding element in $ d $ .

## 说明/提示

In the first example, $ S = \{[1], [2], [3], [1, 3], [2, 1], [2, 3], [3, 1], [3, 2], [2, 1, 3], [3, 2, 1]\} $ . Among them, $ [2, 1, 3] $ and $ [3, 2, 1] $ are the longest and $ [-3, 2, -1] $ is lexicographical smaller than $ [-2, 1, -3] $ , so $ [3, 2, 1] $ is the answer.

In the second example, $ S = \{[1]\} $ , so $ [1] $ is the answer.

## 样例 #1

### 输入

```
4
4
3 2 1 3
4
1 1 1 1
9
3 2 1 3 2 1 3 2 1
1
1```

### 输出

```
3
3 2 1
1
1
3
3 1 2
1
1```

## 样例 #2

### 输入

```
10
2
1 2
10
5 2 1 7 9 7 2 5 5 2
2
1 2
10
2 2 8 7 7 9 8 1 9 6
9
9 1 7 5 8 5 6 4 1
3
3 3 3
6
1 6 4 4 6 5
6
3 4 4 5 3 3
10
4 1 4 5 4 5 10 1 5 1
7
1 2 1 3 2 4 6```

### 输出

```
2
1 2
5
5 1 9 7 2
2
1 2
6
2 7 9 8 1 6
7
9 1 7 5 8 6 4
1
3
4
1 4 6 5
3
4 5 3
4
5 4 10 1
5
2 1 3 4 6```

# AI分析结果



**算法分类**  
贪心 + 单调栈

---

### 题解思路与核心难点

**核心思路**  
1. **最长子序列构造**：子序列长度等于不同元素个数，通过维护栈结构，交替在奇偶位置选择极大/极小值  
2. **字典序优化**：奇数位乘以-1后字典序最小，等价于奇数位尽可能大，偶数位尽可能小  
3. **元素唯一性**：用 `vis[]` 标记已选元素，`last[]` 记录元素最后出现位置  

**关键难点对比**  
| 解法 | 核心数据结构 | 时间复杂度 | 解决难点技巧 |  
|-----|------------|----------|-------------|  
| [chenmingeng] | 双端队列（栈） | O(n) | 交替比较条件，二次弹栈处理相邻元素 |  
| [Z1qqurat] | 线段树+set | O(n logn) | 动态维护可选区间的极值 |  
| [wujingfey] | 单调栈 | O(n) | 分奇偶维护单调性，vis+last双重校验 |  

**结论**  
chenmingeng的线性解法通过交替单调栈实现最优时空复杂度，其核心创新点在于：
1. **奇偶位置交替比较方向**：奇数位弹栈条件为 `a[stk.back()] < a[i]`，偶数位为 `a[stk.back()] > a[i]`  
2. **二次弹栈机制**：允许连续弹两个元素以优化后续选择空间  
3. **last[]边界校验**：仅当栈顶元素后续还有出现时才允许弹栈  

---

### 题解评分（≥4星）

| 题解作者 | 评分 | 亮点 |  
|---------|-----|-----|  
| chenmingeng | ⭐⭐⭐⭐ | 线性时间，双弹栈机制，代码简洁 |  
| Z1qqurat | ⭐⭐⭐⭐ | 线段树动态极值维护，思路严谨 |  
| kotatsugame（Z1qqurat列表） | ⭐⭐⭐⭐ | set维护区间右界，极值查询高效 |  

---

### 关键代码实现（chenmingeng解法）

```cpp
vector<int> stk(n), vis(n);
int top = -1;
for (int i = 0; i < n; ++i) {
    if (vis[a[i]]) continue;
    // 弹栈条件：交替比较方向且后续仍有该元素
    while (top >= 0 && (top & 1 ? a[stk[top]] > a[i] : a[stk[top]] < a[i]) 
           && lst[a[stk[top]]] > i) {
        vis[a[stk[top--]]] = 0;
    }
    // 二次弹栈：处理相邻两个元素
    while (top >= 1 && (top & 1 ? a[stk[top-1]] < a[i] : a[stk[top-1]] > a[i]) 
           && lst[a[stk[top]]] > i) {
        vis[a[stk[top--]]] = 0;
        vis[a[stk[top--]]] = 0;
    }
    stk[++top] = i;
    vis[a[i]] = 1;
}
```

---

### 可视化设计（栈操作）

**动画方案**  
1. **元素流动**：数组元素从左到右流动，经过栈时根据条件弹入/弹出  
2. **颜色标记**：  
   - 红色：当前元素  
   - 蓝色：奇数位栈元素（需最大化）  
   - 绿色：偶数位栈元素（需最小化）  
3. **弹栈高亮**：当满足 `a[i] > 栈顶（奇）` 或 `a[i] < 栈顶（偶）` 时，栈顶闪烁并消失  
4. **last[]提示线**：显示每个元素的最后出现位置，弹栈时校验该位置  

**复古像素效果**  
- **8-bit音效**：弹栈时播放“哔”声，元素入栈时“叮”声  
- **像素网格**：栈结构用方格表示，元素ID以16x16像素块展示  
- **自动演示**：按空格键切换手动/自动模式，速度滑块控制步进间隔  

---

### 相似题目推荐
1. [P2870 - 最长公共子序列](https://www.luogu.com.cn/problem/P2870)（贪心构造）  
2. [P1090 - 合并果子](https://www.luogu.com.cn/problem/P1090)（优先队列极值选择）  
3. [P1908 - 逆序对](https://www.luogu.com.cn/problem/P1908)（分治/线段树维护区间）  

---

**总结**  
本题通过交替单调栈巧妙平衡了长度与字典序要求，其核心在于动态调整比较方向与边界校验。可视化设计中融入游戏化元素可显著提升对贪心策略的理解深度。

---
处理用时：66.27秒