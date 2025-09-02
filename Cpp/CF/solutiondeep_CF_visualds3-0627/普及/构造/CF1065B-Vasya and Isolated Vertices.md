# 题目信息

# Vasya and Isolated Vertices

## 题目描述

Vasya has got an undirected graph consisting of $ n $ vertices and $ m $ edges. This graph doesn't contain any self-loops or multiple edges. Self-loop is an edge connecting a vertex to itself. Multiple edges are a pair of edges such that they connect the same pair of vertices. Since the graph is undirected, the pair of edges $ (1, 2) $ and $ (2, 1) $ is considered to be multiple edges. Isolated vertex of the graph is a vertex such that there is no edge connecting this vertex to any other vertex.

Vasya wants to know the minimum and maximum possible number of isolated vertices in an undirected graph consisting of $ n $ vertices and $ m $ edges.

## 说明/提示

In the first example it is possible to construct a graph with $ 0 $ isolated vertices: for example, it should contain edges $ (1, 2) $ and $ (3, 4) $ . To get one isolated vertex, we may construct a graph with edges $ (1, 2) $ and $ (1, 3) $ .

In the second example the graph will always contain exactly one isolated vertex.

## 样例 #1

### 输入

```
4 2
```

### 输出

```
0 1
```

## 样例 #2

### 输入

```
3 1
```

### 输出

```
1 1
```

# AI分析结果



## 算法分类
贪心

---

## 题解思路与算法分析
### 核心思路
**最小值**：每条边可连接两个孤立顶点，最小孤立顶点数为 `max(0, n-2m)`  
**最大值**：构造完全图，找到最小的 `k` 使得 `k(k-1)/2 ≥ m`，最大孤立顶点数为 `n-k`

### 解决难点
1. **最小值推导**：贪心地用每条边消除两个孤立顶点，直接数学计算。
2. **最大值推导**：通过完全图性质，利用二分法或数学公式快速找到满足边数的最小顶点数。

### 可视化设计
- **动画展示**：顶点用像素点表示，边连接时触发音效。  
- **关键步骤高亮**：红色标记当前完全图顶点数 `k`，绿色显示剩余孤立顶点。  
- **交互控制**：支持暂停/步进，调节动画速度观察构造过程。

---

## 题解评分（≥4星）
1. **NuoCarter (5星)**  
   使用二分法高效计算最大值，代码简洁，处理所有边界条件。
2. **DarkShadow (4星)**  
   正确实现贪心策略，循环简单但时间复杂度稍高。
3. **jiangjiangQwQ (4星)**  
   二分法结合特判，代码规范易读。

---

## 最优思路提炼
```cpp
// 最小值计算
long long min_isolated = max(0LL, n - 2*m);

// 最大值：二分法找最小k满足k*(k-1)/2 >= m
long long l=0, r=n, k=0;
while(l <= r) {
    long long mid = (l+r)/2;
    if(mid*(mid-1)/2 >= m) {
        k = mid;
        r = mid-1;
    } else l = mid+1;
}
long long max_isolated = n - k;
```

---

## 同类型题目推荐
1. **P1334 瑞瑞的木板** - 贪心构造最优解  
2. **P1115 最大子段和** - 极值问题的贪心策略  
3. **P1223 排队接水** - 时间安排中的贪心思想

---

## 可视化与复古动画
- **像素风格**：顶点用8位方块表示，边连接时播放 "blip" 音效。  
- **自动演示**：AI自动构建完全图，每步显示当前边数和孤立顶点数。  
- **音效交互**：找到最优解时播放胜利音效，背景循环8-bit音乐。

---

## 核心代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;
    // 最小值
    cout << max(0LL, n - 2*m) << " ";
    
    // 二分求最大值
    long long l=0, r=n, k=0;
    while(l <= r) {
        long long mid = (l+r)/2;
        if(mid*(mid-1)/2 >= m) {
            k = mid;
            r = mid-1;
        } else l = mid+1;
    }
    cout << n - k;
    return 0;
}
```

---
处理用时：150.05秒