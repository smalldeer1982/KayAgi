# 题目信息

# The Strict Teacher (Easy Version)

## 题目描述

This is the easy version of the problem. The only differences between the two versions are the constraints on $ m $ and $ q $ . In this version, $ m=2 $ and $ q=1 $ . You can make hacks only if both versions of the problem are solved.

Narek and Tsovak were busy preparing this round, so they have not managed to do their homework and decided to steal David's homework. Their strict teacher noticed that David has no homework and now wants to punish him. She hires other teachers to help her catch David. And now $ m $ teachers together are chasing him. Luckily, the classroom is big, so David has many places to hide.

The classroom can be represented as a one-dimensional line with cells from $ 1 $ to $ n $ , inclusive.

At the start, all $ m $ teachers and David are in distinct cells. Then they make moves. During each move

- David goes to an adjacent cell or stays at the current one.
- Then, each of the $ m $ teachers simultaneously goes to an adjacent cell or stays at the current one.

This continues until David is caught. David is caught if any of the teachers (possibly more than one) is located in the same cell as David. Everyone sees others' moves, so they all act optimally.

Your task is to find how many moves it will take for the teachers to catch David if they all act optimally.

Acting optimally means the student makes his moves in a way that maximizes the number of moves the teachers need to catch him; and the teachers coordinate with each other to make their moves in a way that minimizes the number of moves they need to catch the student.

Also, as Narek and Tsovak think this task is easy, they decided to give you $ q $ queries on David's position. Note: this is the easy version, and you are given only one query.

## 说明/提示

In the first example, the student can just stay at cell $ 2 $ . The teacher, initially located in cell $ 1 $ , can reach cell $ 2 $ in one move. Therefore, the answer is $ 1 $ .

In the second example, the student should just stay at cell $ 1 $ . The teacher, initially located in cell $ 3 $ , can reach cell $ 1 $ in two moves. Therefore, the answer is $ 2 $ .

## 样例 #1

### 输入

```
3
10 2 1
1 4
2
8 2 1
3 6
1
8 2 1
3 6
8```

### 输出

```
1
2
2```

# AI分析结果



## 算法分类
**组合数学**

---

## 题解思路与难点分析

### 核心思路
题目本质是博弈论中的极大极小问题。学生与两位教师的最优策略为：
1. **学生**：选择移动方向，使得被捕获的时间最大化。
2. **教师**：协同移动，最小化捕获时间。

通过分类讨论三种情况，直接计算最优步数：
1. **学生在所有教师左侧**：教师向左逼近，步数为左教师位置减1。
2. **学生在教师中间**：教师向中间包夹，步数为两教师间距的一半（向下取整）。
3. **学生在所有教师右侧**：教师向右逼近，步数为右教师到终点的距离。

### 数学推导
- **中间情况公式**：两教师间距为 `d`，每次移动可缩小2单位距离，故步数为 `d/2`（取整）。
- **左右端点公式**：教师需移动到端点，步数为距离端点的距离。

### 解决难点
- **正确分类**：需先对教师位置排序，确保区间划分正确。
- **移动顺序**：学生先动，教师后动，但最优策略下学生无法逃脱包围。

---

## 题解评分（≥4星）

1. **masonxiong**（★★★★★）
   - **亮点**：详细分析相对位置不变性，解释三种情况的数学推导，代码简洁高效。
   - **代码**：排序后直接分类输出，逻辑清晰。

2. **封禁用户**（★★★★☆）
   - **亮点**：公式简洁，给出学生位置在中点时取中间值的思路，代码简短。
   - **不足**：未深入解释移动顺序的影响。

3. **MingRi_Doctor**（★★★★☆）
   - **亮点**：代码结构清晰，注释明确，直接使用 `swap` 处理教师位置。
   - **不足**：公式推导部分稍简略。

---

## 最优代码实现

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t, n, m, q, a, b[2];
    for (cin >> t; t--; ) {
        cin >> n >> m >> q >> b[0] >> b[1] >> a;
        sort(b, b + 2); // 确保教师位置有序
        if (a < b[0]) cout << b[0] - 1 << '\n';
        else if (a > b[1]) cout << n - b[1] << '\n';
        else cout << (b[1] - b[0]) / 2 << '\n';
    }
    return 0;
}
```

---

## 同类型题套路
- **包围策略**：数轴上多点协同移动，计算最优相遇时间。
- **贪心分类**：根据目标位置与关键点的相对位置，分区间处理。

---

## 推荐题目
1. **CF2005B2**（本题困难版，教师数更多）
2. **P1037 覆盖**（区间覆盖与移动策略）
3. **P1514 引水入城**（最优路径规划）

---

## 可视化与算法演示

### 动画设计
- **像素风格数轴**：用方格表示位置，教师（红色方块）、学生（蓝色方块）。
- **步进演示**：高亮当前移动的教师/学生，显示步数。
- **音效**：移动时播放“滴”声，捕获时播放胜利音效。

### 关键步骤
1. **初始排序**：自动排列教师位置。
2. **分类移动**：
   - 左侧：教师左移，学生退至端点。
   - 中间：教师同步向中间移动，间距减2。
   - 右侧：教师右移，学生退至终点。

### 复古风格控制
- **Canvas 绘制**：8位色块表示位置，动态更新。
- **自动模式**：模拟最优策略移动流程，可暂停/调速。

---

## 个人心得
- **初始位置排序**是避免逻辑错误的关键。
- **公式取整验证**：中间情况需确保向下取整的正确性，可通过样例测试。

---
处理用时：116.38秒