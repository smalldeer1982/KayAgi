# 题目信息

# Balance

## 题目描述

A system of $ n $ vessels with water is given. Several pairs of vessels are connected by tubes with transfusion mechanisms. One may transfer an integer amount of liters of water between two vessels connected by such tube (tube works in both directions). There might be multiple tubes between two vessels. Total number of tubes equals $ e $ . Volume of each vessel equals $ v $ liters. Of course, the amount of the water in any vessel cannot exceed $ v $ liters in the process of transfusions.

Given the initial amounts $ a_{i} $ of water in the vessels and the desired amounts $ b_{i} $ find a sequence of transfusions that deals with the task. Total number of transfusions must not exceed $ 2·n^{2} $ .

## 样例 #1

### 输入

```
2 10 1
1 9
5 5
1 2
```

### 输出

```
1
2 1 4
```

## 样例 #2

### 输入

```
2 10 0
5 2
4 2
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
2 10 0
4 2
4 2
```

### 输出

```
0
```

# AI分析结果

### 题目翻译
# 平衡

## 题目描述
给定一个由 $n$ 个装有水的容器组成的系统。若干对容器通过带有输液装置的管子相连。可以在通过这种管子相连的两个容器之间转移整数升的水（管子双向工作）。两个容器之间可能有多根管子。管子的总数为 $e$。每个容器的容积为 $v$ 升。当然，在转移过程中，任何容器中的水量都不能超过 $v$ 升。

给定容器中初始的水量 $a_{i}$ 和期望的水量 $b_{i}$，找出一个能完成任务的转移序列。转移的总次数不能超过 $2·n^{2}$。

## 样例 #1
### 输入
```
2 10 1
1 9
5 5
1 2
```
### 输出
```
1
2 1 4
```

## 样例 #2
### 输入
```
2 10 0
5 2
4 2
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
2 10 0
4 2
4 2
```
### 输出
```
0
```

### 综合分析与结论
- **思路对比**：
    - **xyf007**：先判断总水量是否相等，若相等则依次满足每个水桶的要求，任取两个水桶，一个水量多于目标值，一个少于目标值，进行水的转移，使用递归函数实现转移过程。
    - **清烛**：先判断每个连通块内的总水量是否相等，若相等则将问题转化到生成树上，从叶子节点开始调整，使其满足目标水量，然后将其删除，转化为规模更小的子问题。
    - **Mobius127**：同样先判断每个连通块内的总水量是否相等，若相等则将图缩小到生成森林，对于子树，用子树外未锁定的点去满足根节点的条件。
- **算法要点对比**：
    - **xyf007**：使用递归函数 `f(s, t, d)` 进行水的转移，暴力存储所有路径。
    - **清烛**：使用深度优先搜索构建生成树，使用队列处理叶子节点，递归调整节点的水量。
    - **Mobius127**：使用深度优先搜索，让非锁定节点尽量往后挪或往根节点聚拢。
- **解决难点对比**：
    - **xyf007**：需要处理两点不连通的情况，递归转移水时要注意操作次数的限制。
    - **清烛**：代码细节较多，递归调整水量时要考虑容量限制。
    - **Mobius127**：需要理解如何让非锁定节点移动来满足根节点的条件。

### 所选题解
- **xyf007（4星）**
    - **关键亮点**：思路清晰，代码实现较为简单，通过递归函数实现水的转移，并且对总水量不相等的情况进行了特判。
    - **核心代码**：
```cpp
void Transfer(int s, int t, int d) {
  if (s == t || g[s][t].empty()) return;
  int pre = g[s][t][g[s][t].size() - 2], cnt = std::min(a[pre], d);
  ans.emplace_back(pre, t, cnt);
  a[pre] -= cnt;
  a[t] += cnt;
  Transfer(s, pre, d);
  if (cnt < d) {
    ans.emplace_back(pre, t, d - cnt);
    a[pre] -= d - cnt;
    a[t] += d - cnt;
  }
}
```
核心实现思想：从 $s$ 向 $t$ 运输 $d$ 的水，先尽量多的从 $t$ 之前的点向 $t$ 运输水，然后递归调用 `Transfer` 函数，若第一次运输的水量不够，再补足不足的水。

### 最优关键思路或技巧
- 先判断总水量或每个连通块内的总水量是否相等，若不相等则无解，避免无效计算。
- 将图转化为生成树或生成森林，简化问题。
- 从叶子节点或子树的根节点入手，逐步调整节点的水量，将问题转化为规模更小的子问题。

### 拓展思路
同类型题可能会改变容器的容量限制、转移的规则或增加其他条件。类似算法套路包括树的遍历、递归处理子问题等。

### 推荐题目
- [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)
- [P1396 营救](https://www.luogu.com.cn/problem/P1396)
- [P2820 局域网](https://www.luogu.com.cn/problem/P2820)

### 个人心得
题解中未包含个人心得。

---
处理用时：26.70秒