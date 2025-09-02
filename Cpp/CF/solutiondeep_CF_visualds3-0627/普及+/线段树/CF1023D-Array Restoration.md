# 题目信息

# Array Restoration

## 题目描述

Initially there was an array $ a $ consisting of $ n $ integers. Positions in it are numbered from $ 1 $ to $ n $ .

Exactly $ q $ queries were performed on the array. During the $ i $ -th query some segment $ (l_i, r_i) $ $ (1 \le l_i \le r_i \le n) $ was selected and values of elements on positions from $ l_i $ to $ r_i $ inclusive got changed to $ i $ . The order of the queries couldn't be changed and all $ q $ queries were applied. It is also known that every position from $ 1 $ to $ n $ got covered by at least one segment.

We could have offered you the problem about checking if some given array (consisting of $ n $ integers with values from $ 1 $ to $ q $ ) can be obtained by the aforementioned queries. However, we decided that it will come too easy for you.

So the enhancement we introduced to it is the following. Some set of positions (possibly empty) in this array is selected and values of elements on these positions are set to $ 0 $ .

Your task is to check if this array can be obtained by the aforementioned queries. Also if it can be obtained then restore this array.

If there are multiple possible arrays then print any of them.

## 说明/提示

In the first example you can also replace $ 0 $ with $ 1 $ but not with $ 3 $ .

In the second example it doesn't really matter what segments to choose until query $ 10 $ when the segment is $ (1, 3) $ .

The third example showcases the fact that the order of queries can't be changed, you can't firstly set $ (1, 3) $ to $ 6 $ and after that change $ (2, 2) $ to $ 5 $ . The segment of $ 5 $ should be applied before segment of $ 6 $ .

There is a lot of correct resulting arrays for the fourth example.

## 样例 #1

### 输入

```
4 3
1 0 2 3
```

### 输出

```
YES
1 2 2 3
```

## 样例 #2

### 输入

```
3 10
10 10 10
```

### 输出

```
YES
10 10 10 
```

## 样例 #3

### 输入

```
5 6
6 5 6 2 2
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
3 5
0 0 0
```

### 输出

```
YES
5 4 2
```

# AI分析结果



## 算法分类
**贪心算法、区间覆盖**

## 题解思路与核心难点

### 核心思路
1. **必须存在最大值q**：若原数组没有q且无法用0替换得到，直接无解。
2. **区间最小值约束**：对每个数x，其第一次和最后一次出现的位置之间的最小值必须等于x，否则存在更小值覆盖导致矛盾。
3. **0的填充策略**：优先填充q，否则填充当前可覆盖的最大合法值（如左右相邻数或维护的动态最大值集合）。

### 解决难点
- **动态维护最大值**：通过`set`或稀疏表快速判断当前区间的合法性。
- **处理0的填充**：需在不破坏已有条件的前提下选择最大可能值，避免后续冲突。

---

## 题解评分 (≥4星)

1. **ysner（⭐⭐⭐⭐⭐）**
   - **亮点**：用`set`动态维护当前区间最大值，代码简洁高效。
   - **代码可读性**：逻辑清晰，注释较少但结构明确。
   - **优化**：O(n)预处理区间边界，O(n)遍历检查。

2. **tangml（⭐⭐⭐⭐）**
   - **亮点**：稀疏表快速查询区间最小值，预处理0填充相邻值。
   - **优化**：预处理左右相邻非零值填充0，避免复杂动态维护。

3. **chengni（⭐⭐⭐⭐）**
   - **亮点**：权值线段树维护最大值，动态插入/删除区间标记。
   - **创新**：非`set`实现，适合不熟悉STL的读者。

---

## 最优思路提炼

### 关键技巧
1. **区间最小值约束**：预处理每个数的左右边界，检查区间内最小值。
2. **动态最大值维护**：遍历时用`set`或线段树维护当前覆盖区间的最大值。
3. **0的贪心填充**：
   - **优先填充q**：若原数组无q，必须用0填充。
   - **填充当前最大值**：确保不影响后续约束。

### 代码片段（ysner解法核心）
```cpp
set<int> Q;
for (int i = 1; i <= n; i++) {
    if (a[i] == 0) {
        if (未填充q) a[i] = q;
        else a[i] = Q.empty() ? 1 : *--Q.end();
    } else {
        if (是x的第一次出现) Q.insert(x);
        if (是x的最后一次出现) Q.erase(x);
        if (a[i] < 当前最大值) return 不合法;
    }
}
```

---

## 同类型题目推荐
1. **P1972 [SDOI2009]HH的项链**（区间覆盖与统计）
2. **P3582 [POI2015]KIN**（区间最值与动态维护）
3. **P2894 [USACO08FEB]Hotel G**（线段树区间覆盖）

---

## 可视化设计

### 动画方案
1. **像素风格显示**：
   - 每个元素显示为像素块，颜色对应数值。
   - **高亮**：当前处理的元素（红色边框），填充的0（闪烁黄色）。
   
2. **动态区间覆盖**：
   - 用颜色渐变展示每个数的覆盖区间（如q用深色，1用浅色）。
   - **区间检查**：显示区间最小值的查询过程（绿色箭头扫描）。

3. **音效与交互**：
   - **正确填充**：8-bit上升音效。
   - **错误提示**：短促“哔”声，元素闪烁红色。
   - **自动演示**：按步执行，可暂停/调速。

### 复古风格代码（JavaScript片段）
```javascript
// 初始化Canvas
const canvas = document.getElementById('pixel-canvas');
const ctx = canvas.getContext('2d');
// 绘制像素块
function drawBlock(x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x * 10, y * 10, 8, 8);
}
// 播放音效
function playSound(effect) {
    const audio = new Audio(`sfx/${effect}.wav`);
    audio.play();
}
```

---

## 总结
通过贪心策略动态维护区间最大值，结合区间最值检查确保合法性，优先填充关键值q是解题的核心。可视化设计通过像素动画和音效交互，生动展示算法执行过程，适合教学与调试。

---
处理用时：67.09秒