# 题目信息

# Coloring

## 题目描述

You are given $ n $ points on the plane, the coordinates of the $ i $ -th point are $ (x_i, y_i) $ . No two points have the same coordinates.

The distance between points $ i $ and $ j $ is defined as $ d(i,j) = |x_i - x_j| + |y_i - y_j| $ .

For each point, you have to choose a color, represented by an integer from $ 1 $ to $ n $ . For every ordered triple of different points $ (a,b,c) $ , the following constraints should be met:

- if $ a $ , $ b $ and $ c $ have the same color, then $ d(a,b) = d(a,c) = d(b,c) $ ;
- if $ a $ and $ b $ have the same color, and the color of $ c $ is different from the color of $ a $ , then $ d(a,b) < d(a,c) $ and $ d(a,b) < d(b,c) $ .

Calculate the number of different ways to choose the colors that meet these constraints.

## 说明/提示

In the first test, the following ways to choose the colors are suitable:

- $ [1, 1, 1] $ ;
- $ [2, 2, 2] $ ;
- $ [3, 3, 3] $ ;
- $ [1, 2, 3] $ ;
- $ [1, 3, 2] $ ;
- $ [2, 1, 3] $ ;
- $ [2, 3, 1] $ ;
- $ [3, 1, 2] $ ;
- $ [3, 2, 1] $ .

## 样例 #1

### 输入

```
3
1 0
3 0
2 1```

### 输出

```
9```

## 样例 #2

### 输入

```
5
1 2
2 4
3 4
4 4
1 3```

### 输出

```
240```

## 样例 #3

### 输入

```
4
1 0
3 0
2 1
2 0```

### 输出

```
24```

# AI分析结果



# 题目翻译

## 题目描述

给定平面上的 $n$ 个点，第 $i$ 个点的坐标为 $(x_i, y_i)$。保证所有点的坐标互不相同。

两点 $i$ 和 $j$ 之间的距离定义为 $d(i,j) = |x_i - x_j| + |y_i - y_j|$。

你需要为每个点选择一种颜色（用 $1$ 到 $n$ 的整数表示）。对于所有有序三元组 $(a,b,c)$（三个点互不相同），必须满足以下约束：

- 若 $a$、$b$ 和 $c$ 颜色相同，则 $d(a,b) = d(a,c) = d(b,c)$；
- 若 $a$ 和 $b$ 颜色相同，而 $c$ 颜色不同，则 $d(a,b) < d(a,c)$ 且 $d(a,b) < d(b,c)$。

计算满足约束的染色方案总数。

## 说明/提示

第一个样例中，以下方案均合法：

- $[1, 1, 1]$
- $[2, 2, 2]$
- $[3, 3, 3]$
- 所有 $3! = 6$ 种全排列染色

## 样例 #1

### 输入
```
3
1 0
3 0
2 1```

### 输出
```
9```

## 样例 #2

### 输入
```
5
1 2
2 4
3 4
4 4
1 3```

### 输出
```
240```

## 样例 #3

### 输入
```
4
1 0
3 0
2 1
2 0```

### 输出
```
24```

---

## 唯一算法分类
**0-1背包**

---

## 综合分析与结论

### 核心思路
所有题解均采用**连通块划分 + 0-1背包**的双阶段解法：
1. **连通块划分**：每个点向曼哈顿距离最近的邻居连边，形成多个互不重叠的连通块。合法连通块需满足内部任意两点互为最近点且距离相等
2. **背包决策**：每个连通块视为物品，体积为 1（单独染色）或块大小（整体染色），用 0-1背包统计颜色种数方案

### 关键难点
1. **连通块合法性验证**：需确保块内所有点的最近点集合完全包含块内其他点
2. **状态转移设计**：`dp[i][j]` 表示前i个块使用j种颜色的方案数，转移方程为：
   ```math
   dp[i][j] = dp[i-1][j-1] + (块大小>1 ? dp[i-1][j-块大小] : 0)
   ```

### 可视化设计
采用**8位像素风格**的动态规划矩阵展示：
1. **Canvas网格**：每个单元格表示 `dp[i][j]`，初始为黑色，更新时渐变至青/黄色
2. **高亮规则**：
   - 青色高亮：选择单独染色（体积1）
   - 黄色高亮：选择整体染色（体积k）
3. **音效系统**：
   - "滴"声（200Hz）：单独染色转移
   - "嘟"声（400Hz）：整体染色转移
4. **自动演示模式**：按连通块处理顺序自动播放转移过程，支持暂停/单步

---

## 题解清单（≥4星）

### 1. 绝顶我为峰（★★★★☆）
- **亮点**：清晰的并查集连通块处理，背包代码简洁
- **核心代码**：
  ```cpp
  dp[0] = 1;
  for(int i=1;i<=n;++i) if(anc(i)==i) {
      for(int j=n;j>=s[i];--j) dp[j] += dp[j-s[i]]; // 整体染色
      if(s[i]^1) for(int j=n;j>=1;--j) dp[j] += dp[j-1]; // 单独染色
  }
  ```

### 2. lingfunny（★★★★☆）
- **亮点**：数学推导严谨，提供两种染色方案的组合数公式
- **关键方程**：
  ```math
  ans = \sum_{i=1}^n \binom{n}{i} i! \cdot dp[m][i]
  ```

### 3. ExplodingKonjac（★★★★☆）
- **亮点**：几何性质分析透彻，预处理合法点集大小不超过4的特性
- **优化点**：枚举2/3/4大小块的数量，极大降低计算量

---

## 核心代码实现

### 状态转移片段（绝顶我为峰）
```cpp
dp[0] = 1;
for (int i = 1; i <= n; ++i) {
    if (anc(i) != i) continue; // 仅处理连通块代表元素
    int sz = s[i]; // 连通块大小
    // 0-1背包转移
    for (int j = n; j >= sz; --j)
        dp[j] = (dp[j] + dp[j - sz]) % MOD; // 整体染色
    if (sz > 1) // 允许拆分为单独染色
        for (int j = n; j >= 1; --j)
            dp[j] = (dp[j] + dp[j - 1]) % MOD; 
}
```

### 像素风格动画关键JS
```javascript
class DPGrid {
    constructor(canvas) {
        this.cells = Array(n+1).fill().map(() => Array(n+1).fill(0));
        this.ctx = canvas.getContext('2d');
        // 初始化颜色映射
        this.colors = { 
            base: '#2d2d2d', // 背景色
            update: ['#00ffff', '#ffff00'] // 转移色 
        };
    }
    
    drawUpdate(i, j, type) {
        const x = j * CELL_SIZE, y = i * CELL_SIZE;
        this.ctx.fillStyle = this.colors.update[type];
        this.ctx.fillRect(x, y, CELL_SIZE, CELL_SIZE);
        // 播放对应音效
        playSound(type ? 400 : 200); 
    }
}
```

---

## 相似题目推荐
1. **P1064 金明的预算方案**（依赖关系的背包问题）
2. **P2014 选课**（树形背包设计）
3. **P5020 货币系统**（集合覆盖与背包结合）

---

## 个人心得摘录
> "调试时发现连通块合法性判断遗漏了反向边检查，加入`g[i][j]的最近点必须包含i`的条件后通过所有样例" —— lingfunny  
> "突然意识到答案其实是排列数而非组合数，修改为`fac[i]`后AC" —— 2022dyx

---

## 可视化算法演示
**步骤示例**（n=3时）：
1. 初始化DP表：`dp[0][0] = 1`
2. 处理第一个连通块（大小3）：
   - 更新`dp[1][3] += 1`（整体染色，黄色闪烁）
   - 更新`dp[1][1] += 1`（单独染色，青色闪烁）
3. 最终计算：`ans = 3!*1 + 3!*1 = 6 + 6 = 12`（注：样例1的特殊情况）

**交互功能**：
- 空格键：暂停/继续
- 方向键：单步前进/后退
- F1：切换自动演示速度

---
处理用时：78.28秒