# 题目信息

# [POI 2014] BAR-Salad Bar

## 题目描述

Bytea went to a salad bar.

There are $n$ fruits one next to another on the bar counter.

Specifically, these are apples and oranges.

Bytea can pick any contiguous part of the line of fruits for her salad.

The fruits she chooses will be added to the salad either from left to right or from right to left.

As Bytea loves oranges, she requires that throughout the salad making process, the number of oranges    in it should always be no smaller than the number of apples, regardless of whether these are added %    from left to right or from right to left.

Help Bytea out by writing a program that will find the longest contiguous part of the line of fruits    that satisfies her requirements.

有一个长度为n的字符串，每一位只会是p或j。求一个最长子串，使得不管是从左往右还是从右往左取，都保证每时每刻已取出的p的个数不小于j的个数。


## 说明/提示

有一个长度为n的字符串，每一位只会是p或j。求一个最长子串，使得不管是从左往右还是从右往左取，都保证每时每刻已取出的p的个数不小于j的个数。


## 样例 #1

### 输入

```
6
jpjppj
```

### 输出

```
4
```

# AI分析结果



# 算法分类：单调栈与预处理数组

## 题解思路、算法要点与解决难点

### 核心思路
将 `p` 视为 $1$，`j` 视为 $-1$，计算前缀和数组 `sum`。合法子串 `[l, r]` 需满足：
1. `sum[l-1]` 是区间 `[l-1, r]` 的最小值。
2. `sum[r]` 是该区间的最大值。

### 算法要点
1. **预处理 `to[i]` 数组**：表示从 `i` 开始的最远右端点，满足区间内的 `sum` 均不小于 `sum[i]`，且 `sum[to[i]]` 是最大值。
2. **利用 `nxt[i]` 数组**：记录下一个与 `sum[i]` 相同值的位置，帮助扩展 `to[i]`。
3. **从后往前处理**：通过维护指针 `las` 和 `nxt`，高效构造 `to` 数组。

### 解决难点
- **高效确定最远右端点**：通过 `nxt` 数组跳过无效区间，利用相邻 `sum` 差为 $\pm 1$ 的性质，确保线性时间预处理。
- **双条件验证**：合法区间需同时满足前缀和和后缀和的单调性，通过维护 `to` 数组确保两者条件。

---

## 题解评分 (≥4星)

1. **bztMinamoto（5星）**  
   - **亮点**：通过 `to` 和 `nxt` 数组线性预处理，代码简洁高效，核心思路清晰。
   - **代码**：预处理 `nxt` 和 `to` 数组，枚举左端点直接取 `to[i-1]`。

2. **haoguhao（4星）**  
   - **亮点**：贪心遍历，维护前后缀和，及时清零避免干扰，代码易实现。
   - **代码**：双指针遍历，`s1` 和 `s2` 动态更新，时间复杂度 $O(n)$。

3. **qyy_abc（4星）**  
   - **亮点**：线段树+单调栈维护区间极值，思路系统化，适合理解数据结构应用。
   - **代码**：线段树二分找右端点，单调栈维护合法右端点集合。

---

## 最优思路提炼

### 关键步骤
1. **前缀和转换**：将字符转化为数值，便于区间判断。
2. **预处理 `to` 数组**：通过相邻 `sum` 差为 $\pm 1$ 的性质，快速确定每个左端点的最远右端点。
3. **双指针遍历优化**：直接跳过无效字符（如开头/结尾的 `j`），减少无效计算。

### 代码片段
```cpp
int n, sum[N], head[N], nxt[N], to[N];
char str[N];
// 预处理nxt数组
for (res i = n; i >= 0; i--) {
    res x = sum[i] - minx;
    nxt[i] = head[x];
    head[x] = i;
    to[i] = i;
}
// 构造to数组
for (res i = n, pre = n; i >= 1; i--) {
    if (str[i] == 'j') pre = i - 1;
    else {
        if (nxt[i-1] >= 0 && sum[to[nxt[i-1]]] >= sum[pre])
            pre = to[nxt[i-1]];
        to[i-1] = pre;
        ans = max(ans, pre - i + 1);
    }
}
```

---

## 相似题目推荐
1. **P1972 [SDOI2009] HH的项链**  
   - 利用前缀和与预处理数组统计区间信息。

2. **P2216 [HAOI2007] 理想的正方形**  
   - 滑动窗口结合单调队列维护二维区间极值。

3. **P1638 逛画展**  
   - 双指针维护满足条件的最小区间。

---

## 可视化设计

### 动画方案
1. **前缀和曲线绘制**：在 Canvas 上绘制 `sum` 数组的折线图，高亮当前区间 `[l, r]`。
2. **指针移动效果**：用红色/蓝色方块标记 `l` 和 `r`，动态展示扩展过程。
3. **区间极值标记**：当 `sum[l-1]` 为最小值时，用绿色背景填充；`sum[r]` 为最大值时用黄色。

### 复古像素风格
- **调色板**：使用 8-bit 风格的 16 色，如深蓝（背景）、红（`l`）、绿（`sum` 最小值）、黄（`sum` 最大值）。
- **音效**：指针移动时播放“滴”声，找到合法区间时播放“成功”音效。

---

## 核心逻辑演示
```javascript
// 伪代码：Canvas绘制与动画更新
function draw() {
    ctx.clearRect(0, 0, width, height);
    // 绘制sum曲线
    for (let i = 0; i < n; i++) {
        let y = height - (sum[i] - minSum) * scale;
        ctx.fillRect(i * 10, y, 5, 5);
    }
    // 高亮当前区间
    ctx.fillStyle = 'rgba(255,0,0,0.3)';
    ctx.fillRect(l * 10, 0, (r - l + 1) * 10, height);
    // 标记极值点
    ctx.fillStyle = 'green';
    ctx.fillRect((l-1)*10, height - (sum[l-1]-minSum)*scale, 10, 5);
}
```

---

通过上述分析与设计，可系统化理解问题核心，并高效实现算法。

---
处理用时：89.04秒