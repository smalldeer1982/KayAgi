# 题目信息

# Empty Graph

## 题目描述

— Do you have a wish?



 — I want people to stop gifting each other arrays.

O_o and Another Young Boy



An array of $ n $ positive integers $ a_1,a_2,\ldots,a_n $ fell down on you from the skies, along with a positive integer $ k \le n $ .

You can apply the following operation at most $ k $ times:

- Choose an index $ 1 \le i \le n $ and an integer $ 1 \le x \le 10^9 $ . Then do $ a_i := x $ (assign $ x $ to $ a_i $ ).

Then build a [complete](https://en.wikipedia.org/wiki/Complete_graph) undirected weighted graph with $ n $ vertices numbered with integers from $ 1 $ to $ n $ , where edge $ (l, r) $ ( $ 1 \le l < r \le n $ ) has weight $ \min(a_{l},a_{l+1},\ldots,a_{r}) $ .

You have to find the maximum possible diameter of the resulting graph after performing at most $ k $ operations.

The diameter of a graph is equal to $ \max\limits_{1 \le u < v \le n}{\operatorname{d}(u, v)} $ , where $ \operatorname{d}(u, v) $ is the length of the shortest path between vertex $ u $ and vertex $ v $ .

## 说明/提示

In the first test case, one of the optimal arrays is $ [2,4,5] $ .

The graph built on this array:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1712D/6f5937a14546fd0344ab2a7ad56768b75a98a230.png) $ \operatorname{d}(1, 2) = \operatorname{d}(1, 3) = 2 $ and $ \operatorname{d}(2, 3) = 4 $ , so the diameter is equal to $ \max(2,2,4) = 4 $ .

## 样例 #1

### 输入

```
6
3 1
2 4 1
3 2
1 9 84
3 1
10 2 6
3 2
179 17 1000000000
2 1
5 9
2 2
4 2```

### 输出

```
4
168
10
1000000000
9
1000000000```

# AI分析结果



# Empty Graph

## 题目描述

— 你有愿望吗？



 — 我希望人们不要再互赠数组了。

O_o 与另一个少年



从天上掉下来一个包含 $n$ 个正整数的数组 $a_1,a_2,\ldots,a_n$ 和一个正整数 $k \le n$。

你最多可以进行 $k$ 次如下操作：

- 选择一个下标 $1 \le i \le n$ 和一个整数 $1 \le x \le 10^9$。将 $a_i$ 赋值为 $x$。

然后构建一个包含 $n$ 个顶点（编号从 1 到 n）的完全无向加权图，其中边 $(l, r)$（$1 \le l < r \le n$）的权重为 $\min(a_{l},a_{l+1},\ldots,a_{r})$。

你需要找到在进行最多 $k$ 次操作后，可能得到的图的最大直径。

图的直径定义为所有顶点对中最短路径的最大值：$\max\limits_{1 \le u < v \le n}{\operatorname{d}(u, v)}$，其中 $\operatorname{d}(u, v)$ 是顶点 $u$ 到 $v$ 的最短路径长度。

## 说明/提示

第一个测试用例的最优数组为 $[2,4,5]$。

构建的图中：
$\operatorname{d}(1, 2) = \operatorname{d}(1, 3) = 2$，$\operatorname{d}(2, 3) = 4$，故直径为 $\max(2,2,4) = 4$。

---

### 综合分析与结论

**核心思路**：所有题解均基于以下两个关键性质：
1. 两点间最短路要么是直接边权，要么是全局最小值的两倍
2. 图的直径必然出现在相邻点对的路径上

**最优解法**结合了贪心与二分：
1. **贪心策略**：优先将前k-1小的元素改为$10^9$，转化为k=1的情况
2. **二分答案**：验证是否存在修改方案使直径达到目标值

### 高星题解推荐

#### 1. Gokix（4.5星）
**亮点**：将k>1问题转化为k=1的巧妙贪心策略，通过维护相邻min和全局min的优雅实现
```cpp
for(i=1;i<k;i++) a[b[i].id]=MD; // 前k-1小改为1e9
for(i=1;i<=n;i++) { // 枚举修改第k个位置
    u=a[i];a[i]=MD;
    mx = max(原ans1, 新相邻min);
    ans = max(ans, min(mx, 新全局min*2));
}
```

#### 2. Jr_Zlw（4星）
**亮点**：简洁的二分检查函数，利用前缀和快速统计需要修改的元素数量
```cpp
bool check(int mid) {
    int cnt=0;
    for(int i=1;i<=n;i++) if(2*a[i]<mid) cnt++;
    // 检查相邻点对的修改需求
    return cnt + 所需相邻修改 <=k;
}
```

#### 3. 0htoAi（4星）
**亮点**：分类讨论k的不同情况，清晰处理边界条件
```cpp
if(K==1) {
    // 处理k=1的特殊情况
} else {
    // 处理k>1的一般情况
}
```

---

### 关键技巧总结
1. **问题转化**：通过将前k-1小元素改为极大值，将复杂问题简化为k=1的情况
2. **路径性质**：直径必然出现在相邻点对的最短路径上
3. **二分验证**：通过预处理前缀和快速计算修改次数
4. **全局维护**：同时维护相邻min和全局min的极值

---

### 推荐练习
1. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)（二分答案经典题）
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)（最短距离最大化问题）
3. [P2217 [HAOI2007] 分割矩阵](https://www.luogu.com.cn/problem/P2217)（最值优化与二分结合）

---
处理用时：54.10秒