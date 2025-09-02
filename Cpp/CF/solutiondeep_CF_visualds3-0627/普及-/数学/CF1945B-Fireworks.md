# 题目信息

# Fireworks

## 题目描述

One of the days of the hike coincided with a holiday, so in the evening at the camp, it was decided to arrange a festive fireworks display. For this purpose, the organizers of the hike bought two installations for launching fireworks and a huge number of shells for launching.

Both installations are turned on simultaneously. The first installation launches fireworks every $ a $ minutes (i.e., after $ a, 2 \cdot a, 3 \cdot a, \dots $ minutes after launch). The second installation launches fireworks every $ b $ minutes (i.e., after $ b, 2 \cdot b, 3 \cdot b, \dots $ minutes after launch).

Each firework is visible in the sky for $ m + 1 $ minutes after launch, i.e., if a firework was launched after $ x $ minutes after the installations were turned on, it will be visible every minute from $ x $ to $ x + m $ , inclusive. If one firework was launched $ m $ minutes after another, both fireworks will be visible for one minute.

What is the maximum number of fireworks that could be seen in the sky at the same time?

## 说明/提示

In the first set of input data, the fireworks are visible in the sky for $ 5 $ minutes. Since the first installation launches fireworks every $ 6 $ minutes, and the second one every $ 7 $ minutes, two fireworks launched from the same installation will not be visible in the sky at the same time. At the same time, after $ 7 $ minutes from the start of the holiday, one firework from the first and one from the second camp will be visible. Thus, it is possible to see no more than $ 2 $ fireworks simultaneously.

In the third set of input data, $ 17 $ fireworks will be visible after $ 112 $ minutes:

- $ 9 $ fireworks launched from the first installation at times \[ $ 56, 63, 70, 77, 84, 91, 98, 105, 112 $ \];
- $ 8 $ fireworks launched from the second installation at times \[ $ 56, 64, 72, 80, 88, 96, 104, 112 $ \].

## 样例 #1

### 输入

```
6
6 7 4
3 4 10
7 8 56
5 6 78123459896
1 1 1
1 1 1000000000000000000```

### 输出

```
2
7
17
28645268630
4
2000000000000000002```

# AI分析结果



## 算法分类
**数论**

---

## 题解思路与难点分析

### 核心模型
- **烟花共存条件**：每个烟花在发射后持续可见的时间为 `m+1` 分钟（即从发射时刻 `x` 到 `x+m`）。
- **最大可见数目**：需找到一个长度为 `m+1` 的时间区间，使得该区间内两个装置的发射次数之和最大。

### 关键公式推导
- **最优时间区间选择**：当两个装置同时发射的时刻（如 `t = LCM(a,b)`）作为区间起点时，此时发射次数达到最大值。
- **次数计算**：在 `t` 到 `t+m` 的区间内，装置1发射次数为 `⌊m/a⌋`，装置2为 `⌊m/b⌋`，加上初始的两个烟花，总次数为：  
  **`ans = ⌊m/a⌋ + ⌊m/b⌋ + 2`**

### 解决难点
1. **如何确定最优区间**：通过数论分析，发现当两个装置同时发射时（`t` 是 `a` 和 `b` 的公倍数），后续发射的烟花在时间上最密集。
2. **避免大数计算**：直接使用公式，无需显式计算 `LCM(a,b)`，避免溢出问题（如 `a,b ≤ 1e18` 时）。

---

## 高星题解推荐 (4~5星)

### 1. spfa_ (5星)
- **亮点**：简洁明了，直接给出公式推导，代码清晰。
- **核心思路**：将问题转化为求 `m` 分钟内两个等差数列的项数之和加2。

### 2. littlebug (5星)
- **亮点**：详细推导最优时间点，结合 `LCM` 分析，代码规范。
- **关键点**：证明 `T = LCM(a,b)` 时，后续发射次数达到最大。

### 3. __qkj__ (4星)
- **亮点**：明确数学模型的转化，代码简洁。
- **注意点**：需确认 `+2` 的来源（初始两个烟花）。

---

## 最优思路提炼
- **公式直接应用**：无需复杂推导，直接计算 `⌊m/a⌋ + ⌊m/b⌋ + 2`。
- **数学直觉**：选择两个装置同时发射的时刻作为起点，最大化后续发射次数。

---

## 相似题目推荐
1. **P1072 [NOIP2009 提高组] Hankson 的趣味题**（数论，公约数/公倍数应用）
2. **P1516 青蛙的约会**（扩展欧几里得，线性同余方程）
3. **P2261 [CQOI2007] 余数求和**（数论分块，区间计数）

---

## 代码实现
```cpp
#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long a, b, m;
        cin >> a >> b >> m;
        cout << (m / a) + (m / b) + 2 << '\n';
    }
    return 0;
}
```

---

## 可视化算法演示
### 核心步骤动画设计
1. **初始化**：显示两个装置发射时间轴，用不同颜色标记（红/蓝）。
2. **选择起点**：高亮 `t = LCM(a,b)` 时刻，显示两个烟花同时发射。
3. **区间标记**：在时间轴上绘制 `[t, t+m]` 区间，用绿色背景表示可见时间段。
4. **计算次数**：逐帧显示每个装置在区间内的发射点，并统计数目：
   - 装置1：`t+a, t+2a, ...`（红色标记），总数 `⌊m/a⌋`。
   - 装置2：`t+b, t+2b, ...`（蓝色标记），总数 `⌊m/b⌋`。
5. **结果汇总**：显示公式 `⌊m/a⌋ + ⌊m/b⌋ + 2`，动态填入计算结果。

### 复古像素风格设计
- **Canvas 绘制**：时间轴以网格表示，每个发射点为像素方块。
- **音效触发**：每次发射时播放 8-bit 音效，完成计算时播放胜利音效。
- **自动演示**：AI 模拟推导过程，逐步高亮关键步骤。

---

## 个人心得
- **模型转换**：将时间区间覆盖问题转化为等差数列项数统计是关键。
- **避免溢出**：直接使用公式而非计算 `LCM`，避免大数处理问题。

---
处理用时：194.36秒