# 题目信息

# [USACO09MAR] Look Up S

## 题目描述

Farmer John's N (1 <= N <= 100,000) cows, conveniently numbered 1..N, are once again standing in a row. Cow i has height H\_i (1 <= H\_i <= 1,000,000).

Each cow is looking to her left toward those with higher index numbers. We say that cow i 'looks up' to cow j if i < j and H\_i < H\_j. For each cow i, FJ would like to know the index of the first cow in line looked up to by cow i.

Note: about 50% of the test data will have N <= 1,000. 

约翰的 $N(1\le N\le10^5)$ 头奶牛站成一排，奶牛 $i$ 的身高是 $H_i(1\le H_i\le10^6)$。现在，每只奶牛都在向右看齐。对于奶牛 $i$，如果奶牛 $j$ 满足 $i<j$ 且 $H_i<H_j$，我们可以说奶牛 $i$ 可以仰望奶牛 $j$。 求出每只奶牛离她最近的仰望对象。

Input

## 说明/提示

FJ has six cows of heights 3, 2, 6, 1, 1, and 2.


Cows 1 and 2 both look up to cow 3; cows 4 and 5 both look up to cow 6; and cows 3 and 6 do not look up to any cow.

【输入说明】$6$ 头奶牛的身高分别为 3,2,6,1,1,2。

【输出说明】奶牛 #1,#2 仰望奶牛 #3，奶牛 #4,#5 仰望奶牛 #6，奶牛 #3 和 #6 没有仰望对象。

【数据规模】

对于 $20\%$ 的数据：$1\le N\le10$；

对于 $50\%$ 的数据：$1\le N\le10^3$；

对于 $100\%$ 的数据：$1\le N\le10^5,1\le H_i\le10^6$。


## 样例 #1

### 输入

```
6 
3 
2 
6 
1 
1 
2 
```

### 输出

```
3 
3 
0 
6 
6 
0 
```

# AI分析结果



### 综合分析与结论
本题要求为每个元素找到右侧第一个更大元素的位置。核心解法为**单调栈**和**倒序跳跃法**，均能达到O(n)时间复杂度。两种方法的对比：
- **单调栈**：维护递减序列，利用栈结构快速定位最近更大元素，代码简洁直观。
- **倒序跳跃法**：倒序遍历时利用已有结果跳跃比较，避免重复遍历，空间更优。

### 高评分题解推荐
#### 1. [Seanq的单调栈解法] ★★★★★
**关键亮点**：
- 标准单调栈实现，维护递减序列
- 栈中存储索引，直接映射答案
- 代码规范，解释清晰

**核心代码**：
```cpp
stack<int> s;
for(int i = n; i >= 1; i--) {
    while(!s.empty() && a[s.top()] <= a[i]) s.pop();
    ans[i] = s.empty() ? 0 : s.top();
    s.push(i);
}
```
**实现思想**：倒序维护单调递减栈，栈顶即为当前元素的最近更大元素索引。

#### 2. [胡萝卜的倒序跳跃法] ★★★★☆
**关键亮点**：
- 倒序处理+跳跃指针优化
- 利用已有结果减少比较次数
- 代码简洁高效（击败样例仅需0ms）

**调试心得**：
> "注意循环条件中的`a[j]>0`防止死循环，需将a[0]设为极大值"

**核心代码**：
```cpp
for(i = n-1; i >= 1; i--) {
    j = i+1;
    while(a[i] >= a[j]) j = ans[j];
    ans[i] = j;
}
```

#### 3. [Iowa_BattleShip的数组模拟栈] ★★★★☆
**关键亮点**：
- 数组模拟栈提升效率
- 同向比较逻辑清晰
- 处理严格递增序列更优

**核心代码**：
```cpp
int q[N], tail = 0;
for(int i = 1; i <= n; i++) {
    while(tail && a[i] > a[q[tail]]) 
        ans[q[tail--]] = i;
    q[++tail] = i;
}
```

### 最优思路总结
**关键技巧**：
1. **单调栈维护有序性**：存储递减序列索引，快速定位最近更大元素。
2. **倒序处理跳跃指针**：利用已计算结果的传递性，将比较次数均摊至O(1)。

### 拓展与举一反三
1. **类似问题**：
   - 循环数组找更大元素（[P5788](https://www.luogu.com.cn/problem/P5788)）
   - 二维矩阵中的更大元素（[P719](https://www.luogu.com.cn/problem/P719)）
   - 温度间隔问题（[P739](https://www.luogu.com.cn/problem/P739)）

2. **思维延伸**：
   - 单调栈可处理"下一个更大/更小"、"直方图面积"等问题
   - 跳跃指针法适用于链式依赖问题（如并查集路径压缩）

### 推荐练习题
1. [P1901 发射站](https://www.luogu.com.cn/problem/P1901) - 单调栈经典应用
2. [P5788 模板题](https://www.luogu.com.cn/problem/P5788) - 循环数组下的单调栈变种
3. [P2866 Bad Hair Day](https://www.luogu.com.cn/problem/P2866) - 单调栈计数问题

---
处理用时：48.12秒