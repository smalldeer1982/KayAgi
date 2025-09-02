# 题目信息

# Grid 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_y

縦 $ H $ 行、横 $ W $ 列のグリッドがあります。 上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ で表します。

グリッドのうち、$ N $ 個のマス $ (r_1,\ c_1),\ (r_2,\ c_2),\ \ldots,\ (r_N,\ c_N) $ は壁のマスであり、それら以外のマスはすべて空マスです。 マス $ (1,\ 1) $ および $ (H,\ W) $ は空マスであることが保証されています。

太郎君は、マス $ (1,\ 1) $ から出発し、右または下に隣り合う空マスへの移動を繰り返すことで、マス $ (H,\ W) $ まで辿り着こうとしています。

マス $ (1,\ 1) $ から $ (H,\ W) $ までの太郎君の経路は何通りでしょうか？ $ 10^9\ +\ 7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 2\ \leq\ H,\ W\ \leq\ 10^5 $
- $ 1\ \leq\ N\ \leq\ 3000 $
- $ 1\ \leq\ r_i\ \leq\ H $
- $ 1\ \leq\ c_i\ \leq\ W $
- マス $ (r_i,\ c_i) $ はすべて相異なる。
- マス $ (1,\ 1) $ および $ (H,\ W) $ は空マスである。

### Sample Explanation 1

経路は次図の $ 3 $ 通りです。 !\[\](https://img.atcoder.jp/dp/grid\_1\_0\_muffet.png)

### Sample Explanation 2

経路が存在しない場合もあります。

### Sample Explanation 4

答えを $ 10^9\ +\ 7 $ で割った余りを出力することを忘れずに。

## 样例 #1

### 输入

```
3 4 2

2 2

1 4```

### 输出

```
3```

## 样例 #2

### 输入

```
5 2 2

2 1

4 2```

### 输出

```
0```

## 样例 #3

### 输入

```
5 5 4

3 1

3 5

1 3

5 3```

### 输出

```
24```

## 样例 #4

### 输入

```
100000 100000 1

50000 50000```

### 输出

```
123445622```

# AI分析结果



## 唯一算法分类
动态规划 + 组合数学（容斥原理）

---

## 综合分析与结论

### 题解思路与核心难点
1. **组合数学基础**  
   无障碍时路径数可用组合数 $\binom{x+y-2}{x-1}$ 计算。当存在障碍时，需通过容斥原理排除经过障碍的路径。

2. **动态规划状态设计**  
   定义 $dp[i]$ 为从起点到第 $i$ 个障碍物且不经过其他障碍物的路径数。通过排序障碍物（按坐标升序），确保每个障碍物的处理仅依赖已处理的前驱。

3. **关键步骤与变量**  
   - **预处理阶乘与逆元**：用于快速计算组合数。  
   - **状态转移方程**：  
     $$ dp[i] = \text{总路径数} - \sum_{j < i} dp[j] \times \text{从障碍 $j$ 到 $i$ 的路径数} $$  
   - **终点处理**：将终点 $(H, W)$ 视为第 $n+1$ 个障碍物，最终答案即为 $dp[n+1]$。

4. **解决难点**  
   - **避免重复扣除**：通过排序确保每个障碍物仅被前驱影响，避免重复计算。  
   - **高效计算组合数**：利用预处理阶乘和逆元将组合数计算复杂度优化到 $O(1)$。

### 可视化设计思路
- **像素化网格与障碍物**：用不同颜色标记障碍物，动态显示当前处理的障碍物及其前驱。  
- **路径数动态更新**：在 Canvas 上以动画形式展示 $dp[i]$ 的计算过程，高亮当前扣除的前驱路径。  
- **音效与交互**：  
  - **音效**：每次扣除路径时播放短促音效，计算完成时播放成功音调。  
  - **自动演示模式**：模拟算法流程，自动按排序顺序处理障碍物，单步执行可观察每个状态的变化。  
- **复古风格**：采用 8-bit 调色板，障碍物显示为红色方块，路径数用绿色数字动态更新。

---

## 题解清单（≥4星）

1. **GaryH（5星）**  
   - **亮点**：代码简洁，状态转移清晰，预处理阶乘逆元高效。  
   - **关键代码**：  
     ```cpp
     dp[i] = C(p[i].x + p[i].y - 2, p[i].x - 1);
     for (int j = 1; j < i; j++) {
         if (p[j].x <= p[i].x && p[j].y <= p[i].y) {
             dp[i] -= dp[j] * C(dx + dy, dx);
         }
     }
     ```

2. **ZolaWatle（4.5星）**  
   - **亮点**：详细推导状态转移方程，注释清晰，适合理解数学原理。  
   - **个人心得**：“排序确保每个障碍物仅被前驱影响，是避免重复的关键。”

3. **DengDuck（4星）**  
   - **亮点**：代码结构紧凑，终点处理巧妙，适合快速实现。  
   - **代码片段**：  
     ```cpp
     a[++k] = {n, m};
     sort(a + 1, a + k + 1);
     dp[k + 1] = C(n + m - 2, n - 1) - sum;
     ```

---

## 核心代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10, mod = 1e9 + 7;

ll fac[N], inv[N], dp[3010];
struct Node { int x, y; } a[3010];

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i-1] * i % mod;
    inv[N-1] = qpow(fac[N-1], mod-2);
    for (int i = N-2; i >= 0; i--) inv[i] = inv[i+1] * (i+1) % mod;
}

ll C(int n, int m) {
    if (n < m || m < 0) return 0;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
    int h, w, n;
    cin >> h >> w >> n;
    init();
    for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
    a[n+1] = {h, w};
    sort(a + 1, a + n + 2, [](Node x, Node y) {
        return x.x == y.x ? x.y < y.y : x.x < y.x;
    });

    for (int i = 1; i <= n + 1; i++) {
        dp[i] = C(a[i].x + a[i].y - 2, a[i].x - 1);
        for (int j = 1; j < i; j++) {
            if (a[j].x <= a[i].x && a[j].y <= a[i].y) {
                int dx = a[i].x - a[j].x, dy = a[i].y - a[j].y;
                dp[i] = (dp[i] - dp[j] * C(dx + dy, dx) % mod + mod) % mod;
            }
        }
    }
    cout << dp[n+1];
    return 0;
}
```

---

## 同类型题与类似套路

1. **CF559C Gerald and Giant Chess**  
   - 几乎相同的题意，直接套用本题解法。

2. **路径计数排除特定点**  
   - 如洛谷 P1373，需结合状态压缩或特殊条件处理。

3. **组合数优化动态规划**  
   - 如 AtCoder DP Contest 中的其他题目，常需预处理数学工具加速状态转移。

---

## 推荐题目
1. [CF559C Gerald and Giant Chess](https://www.luogu.com.cn/problem/CF559C)  
2. [P1373 小a和uim之大逃离](https://www.luogu.com.cn/problem/P1373)  
3. [AT4546 Grid 2](https://www.luogu.com.cn/problem/AT4546) （本题）

---

## 个人心得摘录
- **排序是关键**：障碍物必须按坐标升序排序，确保动态规划的无后效性。  
- **调试技巧**：组合数计算易出错，需验证预处理阶乘和逆元的正确性。  
- **思维陷阱**：终点应视为障碍物，否则会漏算最后一步的扣除。

---

## 可视化与复古风格实现
```html
<!DOCTYPE html>
<html>
<body>
<canvas id="canvas" width="800" height="600"></canvas>
<script>
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
// 8-bit 调色板
const colors = { grid: '#2c3e50', obstacle: '#e74c3c', path: '#2ecc71' };
let obstacles = [{x:3,y:3}, {x:5,y:5}]; // 示例障碍物
let dp = new Array(obstacles.length + 1).fill(0);

// 绘制网格和障碍物
function drawGrid() {
    ctx.fillStyle = colors.grid;
    // 绘制逻辑...
}

// 动态更新 dp 值（伪代码）
function updateDP(index) {
    // 高亮当前障碍物和前驱...
    // 播放音效...
}
</script>
</body>
</html>
```
- **动画效果**：障碍物处理时闪烁，路径数动态显示。  
- **音效**：使用 Web Audio API 播放 8-bit 音效，增强交互感。

---
处理用时：96.32秒