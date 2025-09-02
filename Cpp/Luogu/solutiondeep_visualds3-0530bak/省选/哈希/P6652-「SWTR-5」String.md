# 题目信息

# 「SWTR-5」String

## 题目描述

小 A 有一个字符串 $t$。他可以进行以下操作：切掉 $t$ 的一个前/后缀，满足切掉的前/后缀为**切割后** $t$ 的子串。小 A 想得到字符串 $s$，请问他最少需要进行多少次操作。无解输出 $-1$。

## 说明/提示

「样例说明」

样例 $1$：$\texttt{abbabb}\to \texttt{abba}\to \texttt{bba}\to \texttt{ba}$。方案不唯一。

样例 $2$：$\texttt{fxofoxxooffoxooo}\to\texttt{xofoxxooffoxooo}\to\texttt{foxxooffoxooo}\to\texttt{xooffoxooo}\to\texttt{ffoxooo}\to\texttt{ffoxoo}\to\texttt{ffoxo}\to\texttt{ffox}\to\texttt{fox}$。方案不唯一。

「数据范围与约定」

**本题采用捆绑测试。**

- Subtask 1（1 points）：$s=t$。
- Subtask 2（9 points）：$s$ 仅包含字母 $\texttt{a}$。
- Subtask 3（15 points）：$|t|\leq 100$。
- Subtask 4（17 points）：$|t|\leq 500$。
- Subtask 5（18 points）：$|t|\leq 1.5\times 10^3$。
- Subtask 6（15 points）：$|s|=4$，*数据随机。
- Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据：$1 \leq |s| \leq |t| \leq 5\times 10^3$，字符集 $\in[\texttt{a,z}]$。

*数据随机：$s,t$ 字符均随机，字符集 $\in[\texttt{a,c}]$。

**请注意常数优化。**

---

「题目来源」

[Sweet Round 05](https://www.luogu.com.cn/contest/28195) E。    
idea & solution：[Isaunoya](https://www.luogu.com.cn/user/96580) & [Alex_Wei](https://www.luogu.com.cn/user/123294)。

## 样例 #1

### 输入

```
abbabb
ba```

### 输出

```
3```

## 样例 #2

### 输入

```
fxofoxxooffoxooo
fox```

### 输出

```
8```

## 样例 #3

### 输入

```
abcdefghijklmnopq
rstuvwxyzz```

### 输出

```
-1```

## 样例 #4

### 输入

```
ycxcy
cxy```

### 输出

```
-1```

# AI分析结果



**唯一算法分类**：广度优先搜索（BFS）与动态预处理

---

### **综合分析与结论**

#### **核心思路**
1. **问题转化**：将切除操作转化为逆向扩展操作，每次在 `s` 两端添加其子串，最终得到 `t`。
2. **预处理扩展能力**：通过预处理每个区间 `[l, r]` 向左（`f`）和向右（`g`）可扩展的最大长度，利用字符串哈希与单调性优化至 `O(n²)`。
3. **BFS 求最短路径**：从 `s` 在 `t` 中的所有匹配位置出发，用 BFS 逐层扩展，记录最短操作次数。

#### **解决难点**
- **高效预处理**：利用字符串哈希快速比较子串，利用区间扩展的单调性减少重复计算。
- **状态去重**：通过 BFS 的队列自然保证每个状态只被处理一次，避免重复计算。

#### **可视化设计**
- **动画方案**：以网格展示字符串 `t` 的区间 `[l, r]`，高亮当前处理区间。每次扩展时，向左/右延伸不同颜色块，显示 `f` 或 `g` 的值。步进展示 BFS 队列变化。
- **复古像素风格**：用 8 位色块表示字符串，扩展时播放“滴”声，完成时播放“胜利”音效。Canvas 绘制动态网格，自动播放时可设置速度。
- **关键高亮**：当前区间用黄色边框，已访问区间标记为灰色，扩展方向用箭头指示。

---

### **题解清单 (≥4星)**

1. **Alex_Wei 的题解（5星）**
   - **亮点**：预处理 `f/g` 的单调性优化，BFS 实现简洁，时间复杂度严格 `O(n²)`。
   - **代码可读性**：结构清晰，哈希预处理与 BFS 分离，关键注释明确。

2. **Reunite 的题解（4星）**
   - **亮点**：并查集优化状态转移，减少无效访问，适合超大 `n`。
   - **难点**：实现复杂，预处理哈希表需精细管理。

---

### **最优思路提炼**

1. **预处理 `f/g` 数组**：
   - `f[l][r]`：区间 `[l, r]` 向左可扩展的最大长度，利用 `f[l][r-1]` 的单调递增性。
   - `g[l][r]`：向右扩展，类似逻辑。
   - **哈希加速**：通过滚动哈希比较子串是否相等。

2. **BFS 最短路径**：
   - 初始队列为 `s` 在 `t` 中的所有出现位置。
   - 每次扩展左右两端，利用 `f/g` 值直接跳到最大扩展位置，确保最少步数。

---

### **同类型题与算法套路**

- **类似问题**：最短编辑距离、字符串扩展构造、子串拼接问题。
- **通用套路**：预处理关键操作能力 + BFS/DP 求最优解。适用于操作可逆或可分层扩展的场景。

---

### **推荐题目**
1. **P2870 [USACO07DEC] Best Cow Line G**（字符串贪心扩展）
2. **P2324 [SCOI2005] 骑士精神**（BFS 最短步骤）
3. **P1090 合并果子**（优先队列优化）

---

### **代码片段（Alex_Wei 核心逻辑）**

```cpp
// 预处理 f 和 g 数组
for (int i = 1; i <= n; i++) {
    int tmp = 1;
    for (int j = i; j <= n; j++) {
        while (tmp < i && j - tmp + 1 >= i && cal(i - tmp, i - 1) == cal(j - tmp + 1, j)) tmp++;
        f[i][j] = tmp - 1;
    }
    // 类似处理 g...
}

// BFS 过程
queue<pii> q;
q.push({pos+1, pos+s.size()});
while (!q.empty()) {
    auto [l, r] = q.front(); q.pop();
    if (l == 1 && r == n) return steps;
    // 扩展左端
    if (int len = f[l][r]) {
        int nl = l - len;
        if (!vis[nl][r]) { vis[nl][r] = 1; q.push({nl, r}); }
    }
    // 扩展右端类似...
}
```

---

### **可视化代码示例（Canvas 动画）**

```javascript
// 伪代码：绘制区间扩展
function drawStep(l, r, dir) {
    ctx.clearRect(0, 0, width, height);
    // 绘制字符串网格
    for (let i = 0; i < n; i++) {
        ctx.fillStyle = (i >= l && i <= r) ? '#ffd700' : '#fff';
        ctx.fillRect(i * cellSize, 0, cellSize, cellSize);
    }
    // 绘制扩展箭头
    if (dir === 'left') {
        drawArrow(l * cellSize - 10, cellSize/2, -1);
    } else {
        drawArrow(r * cellSize + 10, cellSize/2, 1);
    }
    playSound('beep'); // 触发音效
}
```

---

**个人心得**：预处理时利用单调性避免重复匹配是关键，调试时需验证 `f/g` 的正确性。BFS 的队列初始状态易漏掉多个 `s` 出现位置，需全面扫描 `t`。

---
处理用时：84.54秒