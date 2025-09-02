# 题目信息

# Clique Problem

## 题目描述

数轴上有 $n$ 个点，第 $i$ 个点的坐标为 $x_i$，权值为  $w_i$。两个点 $i,j$ 之间存在一条边当且仅当 $abs(x_i-x_j)\geq w_i+w_j$ 。 你需要求出这张图的最大团的点数。

团的定义：两两之间有边的顶点集合。

## 样例 #1

### 输入

```
4
2 3
3 1
6 1
0 2
```

### 输出

```
3
```

# AI分析结果



## 算法分类
贪心算法

---

## 题解思路与核心难点
### 核心思路
将每个点转换为区间 `[x_i-w_i, x_i+w_i]`，问题转化为选择最多互不重叠的区间。使用经典贪心策略：按右端点排序后，每次选择结束最早的合法区间。

### 解决难点
1. **数学变形**：将原式 `|x_i-x_j| >= w_i+w_j` 转化为几何意义上的区间不重叠条件
2. **问题转化**：发现最大团对应互不重叠的区间集合
3. **贪心策略**：正确性证明（结束最早的区间能为后续留下更多空间）

---

## 题解评分（≥4星）
1. **NaCly_Fish（5星）**
   - 思路清晰，推导过程完整
   - 代码结构规范，含快读优化
   - 核心排序逻辑与贪心实现简洁高效

2. **Siyuan（4星）**
   - 简洁的代码实现
   - 使用索引排序节省内存
   - 变量命名可读性稍逊于最优解

3. **Randyhoads（4星）**
   - 代码极简，变量命名直观
   - 运算符重载实现排序规则
   - 缺少详细注释但逻辑清晰

---

## 最优思路提炼
1. **区间转换**：`l = x-w`, `r = x+w` 建立几何模型
2. **排序策略**：按右端点升序排列（关键证明点）
3. **贪心选择**：维护当前最右端点，跳过重叠区间

**代码核心逻辑**：
```cpp
sort(a, a+n, [](node x, node y){return x.r < y.r;});
int cnt = 0, last_r = -INF;
for(auto seg : a){
    if(seg.l >= last_r){
        cnt++;
        last_r = seg.r;
    }
}
```

---

## 相似题目推荐
1. [P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803)
2. [CF1029C Maximal Intersection](https://codeforces.com/problemset/problem/1029/C)
3. [LeetCode 435. Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/)

---

## 可视化设计
### 动画方案
1. **像素风格演示**  
   ![区间选择动图](https://assets.leetcode.com/uploads/2021/11/25/example1.png)
   - **颜色标记**：
     - 红色：当前遍历的区间
     - 绿色：已选中的区间
     - 灰色：被跳过的重叠区间
   - **操作提示**：显示当前区间的 `[l, r]` 与已选最右端点

2. **控制面板功能**：
   - 步进速度调节（0.5x-3x）
   - 重置/单步执行按钮
   - 显示已选区间数量

3. **音效设计**：
   - 选中区间：8-bit 上升音效
   - 跳过区间：短促低音
   - 完成选择：经典FC过关音效

---

## 核心代码实现
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

struct Segment {
    int l, r;
    bool operator<(const Segment& o) const { return r < o.r; }
} seg[200005];

int main() {
    int n, x, w;
    cin >> n;
    for(int i=0; i<n; ++i){
        cin >> x >> w;
        seg[i] = {x-w, x+w};
    }
    sort(seg, seg+n);
    
    int ans = 0, last = -2e9;
    for(auto& s : seg){
        if(s.l >= last){
            ans++;
            last = s.r;
        }
    }
    cout << ans;
}
```

---

## 关键学习点
1. **问题转化思维**：将抽象的图论条件转化为几何模型
2. **经典贪心模板**：活动选择问题的标准解法
3. **数学分析技巧**：通过不等式变形发现几何性质

---
处理用时：98.15秒