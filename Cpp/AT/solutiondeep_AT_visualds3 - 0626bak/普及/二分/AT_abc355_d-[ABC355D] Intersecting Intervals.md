# 题目信息

# [ABC355D] Intersecting Intervals

## 题目描述

### 问题陈述

给你 $N(2 \leq N \leq 5 \times 10^5)$ 个实数区间。第 $i$ $(1 \leq i \leq N)$ 个区间是 $[l _ i, r _ i](0 \leq l_i < r_i \leq 10^9)$ 。求有多少对 $(i, j),(1 \leq i < j \leq N)$ 中，$i$ 和 $j$ 两个区间相交。

## 样例 #1

### 输入

```
3

1 5

7 8

3 7```

### 输出

```
2```

## 样例 #2

### 输入

```
3

3 4

2 5

1 6```

### 输出

```
3```

## 样例 #3

### 输入

```
2

1 2

3 4```

### 输出

```
0```

# AI分析结果



## 算法分类
扫描线算法（事件排序）

## 题解思路与解决难点
### 核心思路
将每个区间的左右端点视为独立事件，左端点标记为「开始」，右端点标记为「结束」。按坐标排序所有事件，处理顺序为：
1. 坐标相同的事件中，左端点优先处理。
2. 遍历事件时：
   - 遇到左端点：当前活动区间数加一。
   - 遇到右端点：将当前活动区间数累加到答案，随后活动区间数减一。

### 解决难点
1. **事件排序规则**：确保坐标相同时左端点优先，避免漏算相交情况。
2. **统计时机**：仅在处理右端点时累加当前活动区间数，此时这些活动区间必与当前区间相交。

## 题解评分（≥4星）
1. **Xuan_qwq（5星）**  
   思路清晰，代码简洁，事件处理直观，时间复杂度O(n log n)。

2. **tder（4星）**  
   详细证明了扫描线的正确性，但代码稍显复杂。

3. **I_Love_DS（4星）**  
   通过二分法巧妙转换问题，但实现复杂度较高。

## 最优思路提炼
**扫描线法**：  
- 将区间端点抽象为事件点，按坐标排序。
- 维护当前活动区间数，处理右端点时累加相交对数。
- 时间复杂度O(n log n)，空间复杂度O(n)，代码简洁高效。

## 同类型题通用解法
对于涉及区间重叠、覆盖或相交的问题，通用解法为：
1. **离散化**端点，转化为事件序列。
2. **按事件顺序处理**，维护关键状态（如当前活动区间数）。
3. **统计贡献**：在特定事件点（如右端点）触发答案累加。

## 推荐题目
1. P1884 [USACO12FEB] Overplanting S（扫描线求面积并）
2. P1904 天际线问题（事件排序处理轮廓）
3. P5490 【模板】扫描线（矩形面积并模板题）

## 个人心得摘录
- **坐标相同的事件顺序**：左端点优先处理，否则会漏算相交。
- **调试教训**：初始未考虑事件顺序导致样例错误，调整后AC。

---

## 可视化算法设计
### 动画方案
1. **像素风格布局**：  
   - 用绿色像素块表示左端点事件，红色表示右端点。
   - 横向时间轴展示事件点排序，纵向显示当前活动区间数。

2. **关键步骤高亮**：  
   - 处理右端点时，显示当前活动区间数并播放短促音效。
   - 答案数值动态更新，背景音乐为8-bit循环旋律。

3. **交互控制**：  
   - 暂停/继续按钮控制动画进度。
   - 步进按钮单步执行事件处理，观察状态变化。

### 核心代码片段（扫描线法）
```cpp
#include <bits/stdc++.h>
using namespace std;

struct Event { int x, type; };
bool operator<(Event a, Event b) {
    return a.x < b.x || (a.x == b.x && a.type < b.type);
}

int main() {
    int n; cin >> n;
    vector<Event> events;
    for (int i = 0; i < n; ++i) {
        int l, r; cin >> l >> r;
        events.push_back({l, 0}); // 左端点类型为0
        events.push_back({r, 1}); // 右端点类型为1
    }
    sort(events.begin(), events.end());
    
    long long ans = 0, active = 0;
    for (auto& e : events) {
        if (e.type == 0) active++;
        else ans += --active;
    }
    cout << ans << endl;
}
```

### 复古游戏化实现（JS伪代码）
```javascript
// 初始化Canvas
const canvas = document.getElementById("gameCanvas");
const ctx = canvas.getContext("2d");
let events = [...]; // 排序后的事件数组
let active = 0, ans = 0;

function drawEvent(e, index) {
    // 绘制像素块：绿色左端点，红色右端点
    ctx.fillStyle = e.type === 0 ? "#00FF00" : "#FF0000";
    ctx.fillRect(index * 10, 0, 8, 8);
}

function playStep() {
    if (events.length === 0) return;
    let e = events.shift();
    if (e.type === 0) {
        active++;
        playSound("start"); // 播放开始音效
    } else {
        ans += active - 1;
        active--;
        playSound("end"); // 播放结束音效
    }
    updateDisplay(ans); // 更新答案显示
}
```

---

## 总结
扫描线法通过事件排序与状态维护，高效解决区间相交问题。其核心在于将问题抽象为事件序列，并在关键点触发统计，适用于各类区间覆盖、重叠或相交的变种题目。

---
处理用时：333.61秒