# 题目信息

# [USACO08JAN] Artificial Lake G

## 题目背景

USACO 2008 January Gold

## 题目描述

The oppressively hot summer days have raised the cows' clamoring to its highest level. Farmer John has finally decided to build an artificial lake. For his engineering studies, he is modeling the lake as a two-dimensional landscape consisting of a contiguous sequence of N soon-to-be-submerged levels (1 ≤ N ≤ 100,000) conveniently numbered 1..N from left to right.


Each level i is described by two integers, its width Wi (1 ≤ Wi ≤ 1,000) and height (like a relative elevation) Hi (1 ≤ Hi ≤ 1,000,000). The heights of FJ's levels are unique. An infinitely tall barrier encloses the lake's model on the left and right. One example lake profile is shown below.

          
```cpp
         *             *  :
         *             *  :
         *             *  8
         *    ***      *  7
         *    ***      *  6
         *    ***      *  5
         *    **********  4 <- height
         *    **********  3
         ***************  2
         ***************  1
Level    |  1 |2|  3   |
```
In FJ's model, he starts filling his lake at sunrise by flowing water into the bottom of the lowest elevation at a rate of 1 square unit of water per minute. The water falls directly downward until it hits something, and then it flows and spreads as room-temperature water always does. As in all good models, assume that falling and flowing happen instantly. Determine the time at which each elevation's becomes submerged by a single unit of water.


```cpp
WATER              WATER OVERFLOWS                     
       |                       |                           
     * |          *      *     |      *      *            *
     * V          *      *     V      *      *            *
     *            *      *    ....    *      *~~~~~~~~~~~~*
     *    **      *      *~~~~** :    *      *~~~~**~~~~~~*
     *    **      *      *~~~~** :    *      *~~~~**~~~~~~*
     *    **      *      *~~~~**~~~~~~*      *~~~~**~~~~~~*
     *    *********      *~~~~*********      *~~~~*********
     *~~~~*********      *~~~~*********      *~~~~*********
     **************      **************      **************
     **************      **************      **************
     After 4 mins        After 26 mins       After 50 mins

     Lvl 1 submerged     Lvl 3 submerged     Lvl 2 submerged
```
Warning: The answer will not always fit in 32 bits.

夏日那让人喘不过气的酷热将奶牛们的烦躁情绪推到了最高点。最终，FJ决定建一个人工湖供奶牛消暑之用。为了使湖看起来更加真实，FJ决定将湖的横截面建成N(1 <= N <= 100,000)个连续的平台高低错落的组合状，所有的平台从左到右按1..N依次编号。当然咯，在湖中注入水后，这些平台都将被淹没。    平台i在设计图上用它的宽度W\_i(1 <= W\_i <= 1,000)和高度（你可以理解为该平台顶离FJ挖的地基的高度）H\_i(1 <= H\_i <= 1,000,000)来描述的。所有平台的高度都是独一无二的。湖的边缘可以视为无限高的平台。下面给出了一张FJ的设计图：


按FJ的设想，在坑挖好后，他会以1单位/分钟的速度往最低的那个平台上注水。水在离开水管后立即下落，直到撞到平台顶或是更早些时候注入的水。然后，与所有常温下的水一样，它会迅速地流动、扩散。简单起见，你可以认为这些都是在瞬间完成的。FJ想知道，对于每一个平台，它的顶部是从哪个时刻开始，与水面的距离至少为1单位长度。


## 样例 #1

### 输入

```
3
4 2
2 7
6 4```

### 输出

```
4
50
26```

# AI分析结果



---

**唯一算法分类**：单调栈

---

### **题解思路、算法要点与解决难点**

#### **核心思路**：
- **问题本质**：从最低平台开始注水，模拟水蔓延到相邻平台的过程，记录每个平台被完全覆盖的时间。
- **关键观察**：水总是优先填满当前最低的区域，之后向左右更低的平台扩散。填满后，平台合并为更大的虚拟平台，继续处理新的最低点。

#### **算法实现对比**：
1. **单调栈**（幻·光、zhaozejian）：
   - 维护单调递减栈，保证栈顶始终是当前待处理的最低平台。
   - 当新平台高度大于栈顶时，弹出栈顶并计算其注水时间，合并宽度到新平台。
   - 时间复杂度：O(N)，每个平台入栈出栈一次。
   - **解决难点**：通过栈结构高效处理平台合并顺序，避免重复计算。

2. **双向链表**（LOVE_Ynoi、巨型方块）：
   - 使用链表维护平台左右关系，动态删除已处理平台。
   - 每次找到当前最低平台，计算时间后合并到相邻较低的一侧。
   - **解决难点**：链表操作需处理指针更新，合并后的宽度累加需同步到相邻平台。

#### **共同要点**：
- 初始找到最低平台作为起点。
- 合并平台时累加宽度，计算时间增量为 `(相邻平台高度差) × 合并后总宽度`。
- 边界处理：设置虚拟无限高边界防止越界。

---

### **题解评分 (≥4星)**

| 作者          | 星级 | 关键亮点                                                                 |
|---------------|------|--------------------------------------------------------------------------|
| 幻·光         | ★★★★☆ | 清晰的单调栈思路，代码注释详细，图解辅助理解。                           |
| LOVE_Ynoi     | ★★★★☆ | 双向链表实现简洁，分步说明逻辑，代码可读性强。                           |
| 巨型方块      | ★★★★  | 代码极简，直接模拟物理过程，适合快速理解核心思想。                       |

---

### **最优思路/技巧提炼**

1. **单调栈维护合并顺序**：
   - 栈内保持高度递减，确保每次处理最低未填平台。
   - 合并时累加宽度，时间增量由 `高度差 × 合并宽度` 计算。

2. **双向链表动态合并**：
   - 删除已处理节点，合并宽度到相邻平台。
   - 通过 `pre[]` 和 `nxt[]` 数组维护平台关系。

3. **边界处理技巧**：
   ```cpp
   h[0] = h[n+1] = INF; // 防止越界
   ```

---

### **同类型题与算法套路**

- **相似问题**：接雨水（LeetCode 42）、柱状图中最大矩形（LeetCode 84）。
- **通用套路**：单调栈处理有序高度问题，双向链表维护动态合并关系。

---

### **推荐题目**
1. [P2947 [USACO09MAR] Look Up S](https://www.luogu.com.cn/problem/P2947)（单调栈经典）
2. [P1901 发射站](https://www.luogu.com.cn/problem/P1901)（单调栈能量传递）
3. [P2422 良好的感觉](https://www.luogu.com.cn/problem/P2422)（区间最小值贡献问题）

---

### **个人心得摘录**
- **幻·光**：图解展示栈合并过程，强调“水往低处流”的物理直觉。
- **LOVE_Ynoi**：注释中提醒 `long long` 的必要性，避免溢出错误。
- **zengzidi**：通过栈顶第二个元素计算高度差，解决合并后的新高度问题。

---

### **可视化算法演示设计**

#### **核心逻辑动画**：
1. **像素风格平台展示**：
   - 每个平台用不同颜色表示高度，宽度按比例显示。
   - 当前处理平台高亮为红色，合并后变为相邻平台颜色。

2. **关键步骤动态标记**：
   - **栈操作**：入栈时显示绿色边框，出栈时红色闪烁。
   - **时间计算**：显示 `时间 += 高度差 × 宽度` 的公式浮动提示。
   - **链表合并**：用箭头连接相邻平台，合并时箭头动态调整。

3. **交互控制**：
   - **步进控制**：支持暂停/继续/单步，速度可调。
   - **音效反馈**：入栈时“滴答”声，出栈时“水流”声，合并时“碰撞”声。

#### **复古游戏化实现**：
```javascript
// 伪代码：Canvas 绘制平台
function drawPlatforms() {
  ctx.fillStyle = '#8B4513'; // 棕色复古色调
  platforms.forEach(p => {
    ctx.fillRect(p.x, CANVAS_H - p.height, p.width, p.height);
  });
  // 高亮当前处理平台
  ctx.fillStyle = '#FF0000';
  ctx.fillRect(current.x, CANVAS_H - current.height, current.width, current.height);
}

// 音效触发（Web Audio API）
function playSound(effect) {
  const oscillator = audioCtx.createOscillator();
  oscillator.type = 'square'; // 8-bit 方波音色
  oscillator.frequency.setValueAtTime(effect === 'merge' ? 440 : 880, audioCtx.currentTime);
  oscillator.connect(audioCtx.destination);
  oscillator.start();
  oscillator.stop(audioCtx.currentTime + 0.1);
}
```

---

### **核心代码片段**
```cpp
// 幻·光的单调栈核心逻辑
while (!q.empty() && h[f] >= h[q.top()]) {
    int u = q.top();
    q.pop();
    ans[u] = now + width[u];
    now += (min(h[f], h[q.top()]) - h[u]) * width[u];
    merged_width += width[u];
}
q.push(f);
width[f] += merged_width;

// LOVE_Ynoi的双向链表合并逻辑
ans[now] = t + w[now];
t += w[now] * (min(h[pre[now]], h[nxt[now]]) - h[now]);
nxt[pre[now]] = nxt[now];
pre[nxt[now]] = pre[now];
w[nxt[now]] += w[now]; // 合并到右侧
```

---

通过结合单调栈的高效性与链表的动态合并能力，此题展现了处理有序区间合并问题的典型范式。可视化设计通过复古像素风格和音效反馈，使算法流程更具直观性与趣味性。

---
处理用时：82.32秒