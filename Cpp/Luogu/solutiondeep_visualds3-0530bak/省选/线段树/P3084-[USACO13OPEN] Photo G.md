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



### 算法分类
**动态规划（单调队列优化）**

---

### 题解思路与核心难点
#### **核心思路**
通过动态规划定义 `f[i]` 表示第 `i` 头牛必须为斑点牛时，前 `i` 头牛的最大数量。转移时需满足两个约束：
1. **最多一个斑点牛**：每个照片区间只能有一个斑点牛，确定转移区间的右边界 `minl[i]`。
2. **至少一个斑点牛**：每个照片区间必须有一个斑点牛，确定转移区间的左边界 `maxl[i]`。

#### **关键步骤**
1. **预处理 `minl` 和 `maxl`**：
   - `minl[i]`：所有包含 `i` 的区间中最小的左端点。
   - `maxl[i]`：所有右端点小于 `i` 的区间中最大的左端点。
2. **单调队列优化**：维护 `j` 的范围在 `[maxl[i], minl[i]-1]`，队列中存储当前可转移的最优 `f[j]`。

#### **解决难点**
- **区间约束的动态处理**：通过从右往左和从左往右两次扫描预处理 `minl` 和 `maxl`，确保转移区间的正确性。
- **高效求区间最大值**：利用单调队列维护滑动窗口内的最大值，时间复杂度从 O(N²) 优化到 O(N)。

---

### 题解评分 (≥4星)
1. **x义x（5星）**
   - **亮点**：清晰的预处理逻辑，完整注释代码，直观的单调队列实现。
   - **代码可读性**：结构清晰，关键步骤注释详细。
2. **bztMinamoto（4.5星）**
   - **亮点**：代码简洁高效，预处理与队列优化结合紧密。
   - **优化技巧**：使用 `cmin` 和 `cmax` 宏简化代码。
3. **Froggy（4星）**
   - **亮点**：差分约束的启发式优化（SLF+阈值判断），适合理解图论思路。
   - **适用场景**：小规模数据或教学演示。

---

### 最优思路提炼
1. **状态定义与转移区间**：
   - `f[i]` 必须由满足 `maxl[i] ≤ j < minl[i]` 的 `f[j]` 转移而来。
2. **预处理技巧**：
   - `minl` 从右向左扫描，继承 `minl[i+1]`。
   - `maxl` 从左向右扫描，继承 `maxl[i-1]`。
3. **单调队列优化**：
   - 队列维护递减的 `f[j]`，保证队首为当前窗口最大值。
   - 动态调整队首和队尾，确保 `j` 在合法区间内。

---

### 同类型题与算法套路
- **类似动态规划优化**：滑动窗口最大值（洛谷 P1886）、最大子段和（单调队列优化）。
- **区间约束处理**：需同时满足多个区间条件时，预处理左右边界是关键。

---

### 推荐题目
1. **P1886 滑动窗口**（单调队列基础）
2. **P3957 跳房子**（动态规划+单调队列优化）
3. **P2569 股票交易**（复杂状态转移与队列优化）

---

### 个人心得摘录
- **调试教训**：`minl` 和 `maxl` 的初始化需覆盖全部可能值，避免遗漏边界（如 `N+1`）。
- **顿悟点**：将“恰好一个”拆解为“至少一个”和“至多一个”，是解决区间约束的核心思路。

---

### 可视化算法演示
#### **动画设计**
1. **数据初始化**：
   - 绘制数轴，标记牛的位置 `1~N`。
   - 用不同颜色块表示照片区间，高亮当前处理的区间。
2. **预处理步骤**：
   - 显示 `minl[i]` 和 `maxl[i]` 的计算过程，用箭头标注继承关系。
3. **单调队列操作**：
   - 队列元素以颜色区分有效性，红色表示超出 `maxl[i]`，绿色表示合法。
   - 动态显示队列入队（从右侧添加）、出队（左侧弹出）过程。
4. **状态转移**：
   - 当前 `i` 位置高亮，从队列中选取最大值 `f[j]`，显示 `f[i] = f[j]+1`。

#### **复古像素风格**
- **8位像素UI**：数轴用像素网格表示，队列元素显示为方块。
- **音效设计**：
  - 移动指针时播放“滴”声。
  - 找到合法 `j` 时播放上升音调，无解时播放下降音调。
- **自动演示模式**：按空格暂停/继续，方向键控制单步执行。

---

### 核心代码片段
```cpp
// 预处理 minl 和 maxl
for (int i = N; i >= 1; i--)
    minl[i] = min(minl[i], minl[i+1]);
for (int i = 1; i <= N+1; i++)
    maxl[i] = max(maxl[i], maxl[i-1]);

// 单调队列优化转移
int h = 1, t = 0, j = 1;
for (int i = 1; i <= N+1; i++) {
    while (j < minl[i]) { // 扩展右边界
        if (f[j] != -1) {
            while (h <= t && f[q[t]] < f[j]) t--;
            q[++t] = j;
        }
        j++;
    }
    while (h <= t && q[h] < maxl[i]) h++; // 收缩左边界
    f[i] = (h <= t) ? f[q[h]] + (i != N+1) : -1;
}
```

---

### 总结
本题通过动态规划与单调队列优化的结合，高效解决了区间约束下的极值问题。预处理技巧和队列维护是核心，适合作为动态规划优化的经典案例教学。

---
处理用时：73.24秒