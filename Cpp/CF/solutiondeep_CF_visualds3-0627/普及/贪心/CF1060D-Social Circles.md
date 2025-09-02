# 题目信息

# Social Circles

## 题目描述

You invited $ n $ guests to dinner! You plan to arrange one or more circles of chairs. Each chair is going to be either occupied by one guest, or be empty. You can make any number of circles.

Your guests happen to be a little bit shy, so the $ i $ -th guest wants to have a least $ l_i $ free chairs to the left of his chair, and at least $ r_i $ free chairs to the right. The "left" and "right" directions are chosen assuming all guests are going to be seated towards the center of the circle. Note that when a guest is the only one in his circle, the $ l_i $ chairs to his left and $ r_i $ chairs to his right may overlap.

What is smallest total number of chairs you have to use?

## 说明/提示

In the second sample the only optimal answer is to use two circles: a circle with $ 5 $ chairs accomodating guests $ 1 $ and $ 2 $ , and another one with $ 10 $ chairs accomodationg guests $ 3 $ and $ 4 $ .

In the third sample, you have only one circle with one person. The guest should have at least five free chairs to his left, and at least six free chairs to his right to the next person, which is in this case the guest herself. So, overall number of chairs should be at least 6+1=7.

## 样例 #1

### 输入

```
3
1 1
1 1
1 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
1 2
2 1
3 5
5 3
```

### 输出

```
15
```

## 样例 #3

### 输入

```
1
5 6
```

### 输出

```
7
```

# AI分析结果



---

### **题解思路与算法要点**

#### **核心贪心策略**
1. **问题转化**：将每个客人视为一个节点，其左侧需求（`l[i]`）和右侧需求（`r[i]`）需与相邻节点的对应需求重叠。目标是最大化重叠部分。
2. **贪心选择依据**：对 `l` 和 `r` 数组分别排序，按顺序配对 `max(l[i], r[i])`，总椅子数为 `Σmax(l[i], r[i]) + n`。
3. **正确性证明**：排序后，较大 `l` 与较大 `r` 配对，最小化总椅子数。反证法可证：若存在更优配对，则违反排序后的单调性。

#### **解决难点**
- **如何发现排序策略**：直觉上，两人相邻的最优条件是 `l[i]` 和 `r[j]` 相近。排序后对应位置取 `max` 确保每个配对的重叠最大化。
- **单独成圈的特殊处理**：当 `n=1` 时，总椅子数为 `max(l[1], r[1]) + 1`，与公式一致。

---

### **题解评分（≥4星）**

| 题解作者       | 评分 | 关键亮点                                 |
|----------------|------|------------------------------------------|
| Itst           | ★★★★☆ | 代码简洁，直接点明贪心策略               |
| king_xbz       | ★★★★☆ | 详细推导二元组模型，解释全局问题转化思路 |
| 彭骐飞         | ★★★★☆ | 通过调整法证明正确性，提供反例验证       |

---

### **最优思路与技巧提炼**
- **关键贪心策略**：排序后对应位置取 `max(l[i], r[i])`，总和加 `n`。
- **实现细节**：
  - 必须使用 `long long` 避免溢出。
  - 双数组排序时间复杂度为 `O(n log n)`，符合题目约束。

---

### **同类型题目与算法套路**
- **常见场景**：区间调度、最小化配对代价、最大化重叠。
- **类似题目**：
  1. **洛谷 P1094** [纪念品分组](https://www.luogu.com.cn/problem/P1094)（排序后贪心配对）
  2. **洛谷 P1223** [排队接水](https://www.luogu.com.cn/problem/P1223)（排序最小化总等待时间）
  3. **洛谷 P1968** [美元汇率](https://www.luogu.com.cn/problem/P1968)（贪心选择最优交易时机）

---

### **代码实现核心片段**
```cpp
#include<bits/stdc++.h>
using namespace std;
int l[100005], r[100005];

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> l[i] >> r[i];
    sort(l + 1, l + n + 1);
    sort(r + 1, r + n + 1);
    long long ans = n;
    for (int i = 1; i <= n; i++) ans += max(l[i], r[i]);
    cout << ans;
    return 0;
}
```

---

### **可视化与算法演示设计**
#### **贪心过程动画**
1. **像素风格界面**：
   - 用两种颜色方块表示 `l` 和 `r` 数组，初始乱序排列。
   - 排序过程：方块按数值大小滑动到有序位置，伴随“排序音效”。
   - 配对动画：排序后，`l[i]` 和 `r[i]` 方块闪烁，取较大值并累加到总椅子数。
2. **交互功能**：
   - **步进控制**：点击“下一步”触发一次配对，高亮当前操作。
   - **自动播放**：以 1秒/步的速度自动演示，背景音乐为 8-bit 风格循环。
3. **音效设计**：
   - 排序完成时播放上升音调。
   - 每次配对时播放“点击”音效，错误配对时播放警告音。

---

### **总结**
本题通过排序和贪心配对，将复杂问题转化为有序序列的最优匹配。其核心思想是**通过排序构造单调性，使得每一步局部最优解能导向全局最优**。可视化设计中，复古像素风格和音效增强了学习趣味性，帮助理解贪心策略的渐进过程。

---
处理用时：76.72秒