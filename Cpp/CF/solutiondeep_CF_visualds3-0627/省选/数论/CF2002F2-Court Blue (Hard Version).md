# 题目信息

# Court Blue (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, it is not guaranteed that $ n=m $ , and the time limit is higher. You can make hacks only if both versions of the problem are solved.

In the court of the Blue King, Lelle and Flamm are having a performance match. The match consists of several rounds. In each round, either Lelle or Flamm wins.

Let $ W_L $ and $ W_F $ denote the number of wins of Lelle and Flamm, respectively. The Blue King considers a match to be successful if and only if:

- after every round, $ \gcd(W_L,W_F)\le 1 $ ;
- at the end of the match, $ W_L\le n, W_F\le m $ .

Note that $ \gcd(0,x)=\gcd(x,0)=x $ for every non-negative integer $ x $ .

Lelle and Flamm can decide to stop the match whenever they want, and the final score of the performance is $ l \cdot W_L + f \cdot W_F $ .

Please help Lelle and Flamm coordinate their wins and losses such that the performance is successful, and the total score of the performance is maximized.

## 说明/提示

In the first test case, a possible performance is as follows:

- Flamm wins, $ \gcd(0,1)=1 $ .
- Lelle wins, $ \gcd(1,1)=1 $ .
- Flamm wins, $ \gcd(1,2)=1 $ .
- Flamm wins, $ \gcd(1,3)=1 $ .
- Flamm wins, $ \gcd(1,4)=1 $ .
- Lelle and Flamm agree to stop the match.

The final score is $ 1\cdot2+4\cdot5=22 $ .

## 样例 #1

### 输入

```
8
3 4 2 5
4 4 1 4
6 6 2 2
7 9 2 3
8 9 9 1
2 7 1 4
5 9 1 4
5 6 6 7```

### 输出

```
22
17
18
37
77
30
41
59```

## 样例 #2

### 输入

```
2
3082823 20000000 1341 331
20000000 20000000 3 5```

### 输出

```
10754065643
159999991```

## 样例 #3

### 输入

```
1
139 1293 193 412```

### 输出

```
559543```

# AI分析结果



## 算法分类
**动态规划**（DP）与**数论**（GCD处理）

---

## 综合分析与结论
### 题目核心思路
在满足每轮后 `gcd(W_L, W_F) ≤1` 的条件下，最大化 `l*W_L + f*W_F`。由于直接枚举所有可能的 `(W_L, W_F)` 不可行（`n, m` 可达 2e7），题解采用动态规划结合数论优化的方式，缩小问题规模至接近 `n` 和 `m` 的有限范围，高效求解。

### 解决难点与关键优化
1. **范围缩小假设**：观察到当 `x` 或 `y` 接近 `n` 或 `m` 时，可能存在最优解，故仅处理最后 `B` 个可能值（`B=120`）。
2. **快速 GCD 计算**：使用位运算优化的 `bgcd` 函数，加速状态转移条件的判断。
3. **动态规划状态设计**：`f[i][j]` 表示是否能到达 `x = n - i` 和 `y = m - j`，通过转移方程判断路径可行性。

### 可视化设计思路
- **动画方案**：在 Canvas 上绘制一个 `L×L` 的网格，每个格子代表 `(i,j)` 的状态（可达/不可达）。当前遍历的格子用绿色高亮，可达状态用蓝色填充，不可达留白。
- **音效与反馈**：遍历时播放轻微音效，找到更优解时触发上扬音调。结束时播放成功音效。
- **复古像素风格**：采用 8-bit 像素风，格子用 16x16 像素块，颜色方案为经典 FC 色调（深蓝、浅蓝、红、黄）。

---

## 题解评分（4星及以上）
### 题解作者：DaiRuiChen007（⭐⭐⭐⭐）
- **关键亮点**：
  - **高效范围限制**：假设最优解在边界附近，将问题规模从 O(nm) 降至 O(B²)。
  - **位运算优化 GCD**：`bgcd` 函数通过奇偶判断和递归减少计算时间。
  - **动态规划剪枝**：仅维护最后 `B` 位的状态，避免存储整个大数组。

---

## 最优思路与代码实现
### 核心代码片段
```cpp
const int L = 120;
bool f[L+5][L+5]; // 状态数组

// 快速 GCD 计算（位运算优化）
int bgcd(int x, int y) {
    if (!x || !y || x == y) return x | y;
    if (x % 2 == 0) return (y % 2 == 0) ? bgcd(x>>1, y>>1) << 1 : bgcd(x>>1, y);
    return (y % 2 == 0) ? bgcd(x, y>>1) : (x < y) ? bgcd((y - x)>>1, x) : bgcd((x - y)>>1, y);
}

void solve() {
    int n, m, a, b;
    scanf("%d%d%d%d", &n, &m, &a, &b);
    memset(f, 0, sizeof(f));
    int u = max(1, n - L), v = max(1, m - L); // 确定处理起点
    ll ans = 0;
    for (int i = 0; i <= n - u; ++i) {
        for (int j = 0; j <= m - v; ++j) {
            if (i == 0 || j == 0) f[i][j] = true;
            else if (bgcd(i + u, j + v) <= 1) {
                f[i][j] = f[i-1][j] | f[i][j-1];
            }
            if (f[i][j]) {
                ans = max(ans, 1LL * a * (i + u) + 1LL * b * (j + v));
            }
        }
    }
    printf("%lld\n", ans);
}
```

---

## 相似题目推荐
1. **洛谷 P1029**：最大公约数与最小公倍数问题（数论+枚举）
2. **洛谷 P1373**：小 a 和 uim 之大逃离（动态规划+状态压缩）
3. **洛谷 P1441**：砝码称重（动态规划+组合优化）

---

## 个人心得摘录
> "打表观察发现小范围构造容易满足条件，结合动态规划剪枝处理大范围数据。"  
> —— 观察与假设的结合是解决大规模问题的关键。

---

## 可视化与复古动画方案
### 实现步骤
1. **Canvas 初始化**：绘制 `121x121` 网格，每个格子对应 `(i,j)` 的状态。
2. **动画循环**：
   - **步进遍历**：每次更新一个格子，高亮当前格子（绿色边框）。
   - **状态标记**：若可达则填充蓝色，不可达留白。
   - **音效触发**：每次更新播放 `beep` 音效，发现更优解时播放 `coin` 音效。
3. **8-bit 风格**：
   - **颜色调色板**：深蓝（#1A237E）、浅蓝（#4FC3F7）、红（#D32F2F）、黄（#FFD600）。
   - **像素绘制**：每个格子用 16x16 像素块，边线为 2 像素宽。

### AI 自动演示
- **自动模式**：以固定速度遍历网格，模拟算法执行过程。
- **手动控制**：支持暂停、单步执行，观察状态转移逻辑。

通过这种设计，学习者可直观观察动态规划的状态转移过程，理解范围剪枝策略的有效性。

---
处理用时：77.72秒