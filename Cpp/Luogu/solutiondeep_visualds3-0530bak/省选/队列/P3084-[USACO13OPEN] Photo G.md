# 题目信息

# [USACO13OPEN] Photo G

## 题目描述

Farmer John has decided to assemble a panoramic photo of a lineup of his N cows (1 <= N <= 200,000), which, as always, are conveniently numbered from 1..N.  Accordingly, he snapped M (1 <= M <= 100,000) photos, each covering a contiguous range of cows: photo i contains cows a\_i through b\_i inclusive.  The photos collectively may not necessarily cover every single cow.

After taking his photos, FJ notices a very interesting phenomenon: each photo he took contains exactly one cow with spots!  FJ was aware that he had some number of spotted cows in his herd, but he had never actually counted them.  Based on his photos, please determine the maximum possible number of spotted cows that could exist in his herd.  Output -1 if there is no possible assignment of spots to cows consistent with FJ's photographic results.

农夫约翰决定给站在一条线上的N(1 <= N <= 200,000)头奶牛制作一张全家福照片，N头奶牛编号1到N。


于是约翰拍摄了M(1 <= M <= 100,000)张照片，每张照片都覆盖了连续一段奶牛：第i张照片中包含了编号a\_i 到 b\_i的奶牛。但是这些照片不一定把每一只奶牛都拍了进去。


在拍完照片后，约翰发现了一个有趣的事情：每张照片中都**有且仅有**一只身上带有斑点的奶牛。约翰意识到他的牛群中有一些斑点奶牛，但他从来没有统计过它们的数量。 根据照片，请你帮约翰估算在他的牛群中最多可能有多少只斑点奶牛。如果无解，输出“-1”。


Input

## 说明/提示

There are 5 cows and 3 photos.  The first photo contains cows 1 through 4, etc.


From the last photo, we know that either cow 3 or cow 4 must be spotted. By choosing either of these, we satisfy the first two photos as well.


## 样例 #1

### 输入

```
5 3 
1 4 
2 5 
3 4 
```

### 输出

```
1 
```

# AI分析结果



# 题解分析

## 算法分类
动态规划（单调队列优化）

---

## 题解思路与核心难点

### 核心思路
1. **动态规划状态设计**：定义 `f[i]` 表示第 `i` 头牛必须为斑点牛时，前 `i` 头牛的最大斑点牛数量。
2. **转移条件推导**：
   - **区间最多一个斑点牛**：预处理 `minl[i]` 为所有覆盖 `i` 的区间中最小的左端点，`j` 必须小于 `minl[i]`。
   - **区间至少一个斑点牛**：预处理 `maxl[i]` 为所有右端点小于 `i` 的区间中最大的左端点，`j` 必须大于等于 `maxl[i]`。
3. **单调队列优化**：维护 `j` 的合法范围 `[maxl[i], minl[i])`，用单调队列快速查询区间最大值。

### 解决难点
- **预处理边界**：通过逆向扫描处理 `minl` 和正向扫描处理 `maxl`，确保转移区间的正确性。
- **高效区间最值查询**：利用单调队列的单调性维护候选 `j` 值，保证每次转移的时间复杂度为 O(1)。

---

## 最优题解推荐（≥4星）

### 题解1：x义x（★★★★★）
**亮点**：
- 详细推导了 `minl` 和 `maxl` 的预处理过程。
- 使用虚拟节点 `N+1` 处理边界条件。
- 代码结构清晰，注释明确。

### 题解2：bztMinamoto（★★★★☆）
**亮点**：
- 代码简洁高效，直接处理数组更新。
- 通过 `cmax` 和 `cmin` 简化预处理逻辑。

### 题解3：巨型方块（★★★★☆）
**亮点**：
- 使用双指针代替单调队列，简化代码逻辑。
- 直接维护最后一个有效 `j` 值，避免队列操作。

---

## 关键代码实现
```cpp
// 预处理 minl 和 maxl
for (int i = 1; i <= M; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    minl[r] = min(minl[r], l);
    maxl[r + 1] = max(maxl[r + 1], l);
}
for (int i = N; i >= 1; --i)
    minl[i] = min(minl[i], minl[i + 1]);
for (int i = 1; i <= N + 1; ++i)
    maxl[i] = max(maxl[i], maxl[i - 1]);

// 单调队列优化 DP
int h = 1, t = 1, j = 1;
q[1] = 0;
for (int i = 1; i <= N + 1; ++i) {
    for (; j < minl[i]; ++j) {
        if (f[j] != -1) {
            while (h <= t && f[q[t]] < f[j]) --t;
            q[++t] = j;
        }
    }
    while (h <= t && q[h] < maxl[i]) ++h;
    f[i] = (h <= t) ? f[q[h]] + (i != N + 1) : -1;
}
printf("%d\n", f[N + 1]);
```

---

## 可视化设计

### 动画方案
1. **预处理阶段**：
   - 显示区间覆盖关系，高亮当前处理的区间 `[a_i, b_i]`。
   - 动态更新 `minl` 和 `maxl` 数组的值，用不同颜色区分变化。
2. **DP 阶段**：
   - 用网格表示牛的排列，斑点牛用黄色像素块标记。
   - 展示单调队列的进出过程：新元素进入时弹出较小的值（红色闪烁），队首元素用于更新 `f[i]`（绿色高亮）。
3. **音效设计**：
   - 队列弹出/插入时播放 8-bit 音效。
   - 成功更新 `f[i]` 时播放上升音调，无解时播放下降音调。

### 复古像素风格
- **颜色方案**：使用 16 色调色板，斑点牛用黄色，队列元素用蓝色/红色区分。
- **Canvas 绘制**：以网格布局展示牛的位置，队列状态在右侧面板实时更新。
- **自动演示模式**：按空格键暂停/继续，方向键控制单步执行。

---

## 相似题目推荐
1. **P1886 滑动窗口**（单调队列模板）
2. **P2216 理想的正方形**（二维滑动窗口）
3. **P1725 琪露诺**（单调队列优化 DP）

---

## 总结
本题的难点在于将区间约束转化为动态规划的转移条件，并通过单调队列优化实现高效查询。核心思想是将“恰好一个斑点牛”拆分为两个互补条件，利用预处理和单调性降低时间复杂度。复古风格的动画设计能直观展示队列的维护过程，增强对算法步骤的理解。

---
处理用时：81.17秒