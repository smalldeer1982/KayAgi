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



# 题目翻译

## 题目描述

有一个 $H$ 行 $W$ 列的网格。从上往下第 $i$ 行、从左往右第 $j$ 列的格子用 $(i,j)$ 表示。

网格中有 $N$ 个障碍物格子 $(r_1,c_1),(r_2,c_2),\ldots,(r_N,c_N)$，其余都是空格子。保证 $(1,1)$ 和 $(H,W)$ 是空格子。

太郎君要从 $(1,1)$ 出发，通过不断向右或向下移动到相邻的空格子，最终到达 $(H,W)$。求这样的路径有多少种？答案对 $10^9+7$ 取模。

## 输入格式
第一行输入 $H,W,N$
接下来 $N$ 行每行两个整数 $r_i,c_i$

## 输出格式
输出路径数模 $10^9+7$ 的结果

## 样例
### 样例1
输入：
3 4 2
2 2
1 4

输出：
3

### 样例2
输入：
5 2 2
2 1
4 2

输出：
0

## 数据范围
- $2 \leq H,W \leq 10^5$
- $1 \leq N \leq 3000$
- 所有坐标互不相同且保证起点终点为空

---

# 唯一算法分类：线性DP

## 综合分析与结论

### 核心思路
采用动态规划结合组合数学的容斥原理，将终点视为特殊障碍物，通过排序障碍物构建转移顺序。预处理组合数实现$O(1)$查询，状态转移方程采用减法原理排除非法路径。

### 关键状态转移方程
设 $dp[i]$ 表示到第$i$个障碍且不经过其他障碍的方案数：
$$ dp[i] = C(x_i+y_i-2, x_i-1) - \sum_{j<i} dp[j] \cdot C(\Delta x+\Delta y, \Delta x) $$
其中 $\Delta x = x_i-x_j$, $\Delta y = y_i-y_j$

### 可视化设计思路
1. **动态网格图**：在Canvas中绘制网格坐标系，障碍物用红色方块标记，当前处理的障碍物用闪烁特效
2. **DP矩阵跟踪**：右侧显示排序后的障碍物列表，实时高亮正在计算的$dp[i]$值
3. **组合数路径演示**：用绿色路径显示当前计算的合法路径数，红色路径表示被减去的非法路径
4. **复古像素风格**：采用16色调色板（如#FF0000障碍物、#00FF00路径），8-bit音效在状态更新时触发"哔"声，找到最终解时播放胜利音效

---

# 题解清单（4星以上）

1. **GaryH（★★★★★）**
   - 亮点：最早提出将终点视为障碍物的思路，代码结构清晰，预处理阶乘逆元高效计算组合数
   - 核心代码段：
     ```cpp
     rep(i,1,n+1){
         dp[i] = C(p[i].fi+p[i].se-2, p[i].fi-1);
         rep(j,1,i-1){
             int XL=p[i].fi-p[j].fi,YL=p[i].se-p[j].se;
             dp[i] -= dp[j]*C(XL+YL,XL)%mod;
         }
     }
     ```

2. **ZolaWatle（★★★★☆）**
   - 亮点：详细推导组合数的数学原理，变量命名规范易读
   - 个人心得："将障碍物排序后，每个状态只需考虑之前的障碍，这种有序性保证了容斥的正确性"

3. **qiuweilin666（★★★★☆）**
   - 亮点：采用结构体存储障碍物，代码模块化程度高
   - 优化技巧：通过提前计算逆元降低时间复杂度

---

# 核心代码实现

```cpp
const int MOD = 1e9+7;
ll fac[N*2], inv[N*2], dp[3005];

void init() {
    fac[0] = 1;
    for(int i=1; i<=2e5; i++) 
        fac[i] = fac[i-1] * i % MOD;
    inv[200000] = pow(fac[200000], MOD-2);
    for(int i=2e5-1; i>=0; i--)
        inv[i] = inv[i+1] * (i+1) % MOD;
}

ll C(int n, int m) {
    return fac[n] * inv[m] % MOD * inv[n-m] % MOD;
}

int main() {
    init();
    vector<PII> obs = {{1,1}, {H,W}}; // 包含起点终点
    sort(obs.begin(), obs.end());
    
    for(int i=0; i<obs.size(); i++) {
        auto [x,y] = obs[i];
        dp[i] = C(x+y-2, x-1);
        for(int j=0; j<i; j++) {
            auto [xj,yj] = obs[j];
            if(xj <= x && yj <= y) {
                int dx = x - xj, dy = y - yj;
                dp[i] = (dp[i] - dp[j] * C(dx+dy, dx)) % MOD;
            }
        }
    }
    cout << (dp.back() + MOD) % MOD;
}
```

---

# 相似题目推荐

1. **CF559C Gerald and Giant Chess**  
   - 同类问题，障碍物处理方式完全一致
   
2. **洛谷P1373 小a和uim大逃离**  
   - 二维DP与组合计数的结合应用

3. **AtCoder DP Contest H - Grid 1**  
   - 本题的简化版本，无障碍物时的基础模型

---

# 可视化代码片段（Canvas动画）

```javascript
// 初始化网格
function drawGrid() {
    ctx.fillStyle = "#333"; // 暗灰色背景
    ctx.fillRect(0,0,canvas.width,canvas.height);
    
    // 绘制障碍物（红色方块）
    obstacles.forEach(([x,y],i) => {
        ctx.fillStyle = i === current ? "#FF0" : "#F00";
        ctx.fillRect(x*cellSize, y*cellSize, cellSize-2, cellSize-2);
    });
    
    // 绘制DP值
    ctx.fillStyle = "#0F0";
    dpValues.forEach((val,i) => {
        ctx.fillText(`dp[${i}]=${val}`, 600, 20+i*20);
    });
}

// 动画更新
function animateStep() {
    if(current >= dp.length) return;
    
    // 高亮当前障碍物
    drawGrid();
    // 播放音效
    beep(440 + current*10, 50); 
    
    // 模拟计算过程
    setTimeout(() => {
        current++;
        requestAnimationFrame(animateStep);
    }, 500);
}
```

---
处理用时：75.01秒