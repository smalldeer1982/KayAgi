# 题目信息

# [ABC373F] Knapsack with Diminishing Values

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc373/tasks/abc373_f

$ N $ 種類の品物があり、 $ i $ 種類目の品物の重みは $ w_i $、価値は $ v_i $ です。どの種類の品物も $ 10^{10} $ 個ずつあります。

高橋君はこれから、品物をいくつか選んで、容量 $ W $ のバッグに入れます。高橋君は、選ぶ品物の価値を大きくしつつ、同じ種類の品物ばかりにならないようにしたいです。そこで高橋君は、$ i $ 種類目の品物を $ k_i $ 個選んだときの **うれしさ** を $ k_i\ v_i\ -\ k_i^2 $ と定義したとき、選んだ品物の重さの総和を $ W $ 以下にしつつ、各種類のうれしさの総和が最大になるように品物を選びます。高橋君が達成できる、うれしさの総和の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3000 $
- $ 1\ \leq\ W\ \leq\ 3000 $
- $ 1\ \leq\ w_i\ \leq\ W $
- $ 1\ \leq\ v_i\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

$ 1 $ 種類目の品物を $ 2 $ 個、$ 2 $ 種類目の品物を $ 1 $ 個選ぶと、うれしさの総和を $ 5 $ にすることができ、これが最適です。 $ 1 $ 種類目の品物についてのうれしさは $ 2\ \times\ 4\ -\ 2^2\ =\ 4 $、$ 2 $ 種類目の品物についてのうれしさは $ 1\ \times\ 2\ -\ 1^2\ =\ 1 $ です。 また、重さの総和は $ 9 $ であり、容量 $ 10 $ のバッグに入ります。

## 样例 #1

### 输入

```
2 10

3 4

3 2```

### 输出

```
5```

## 样例 #2

### 输入

```
3 6

1 4

2 3

2 7```

### 输出

```
14```

## 样例 #3

### 输入

```
1 10

1 7```

### 输出

```
12```

# AI分析结果



# [ABC373F] 递减价值的背包问题

## 题目描述

### 题目背景
$ N $ 种物品，第 $i$ 种物品的重量为 $w_i$，基础价值为 $v_i$，数量无限。选择 $k_i$ 个第 $i$ 种物品时，其产生的快乐值为 $k_i v_i - k_i^2$。现给定容量为 $W$ 的背包，求在总重量不超过 $W$ 的前提下，所有物品快乐值的最大总和。

### 输入格式
- 第 1 行：两个整数 $N$ 和 $W$
- 后续 $N$ 行：每行两个整数 $w_i$ 和 $v_i$

### 输出格式
- 最大快乐值

### 样例
输入样例1：
```
2 10
3 4
3 2
```
输出样例1：
```
5
```

### 数据范围
- $1 \leq N, W \leq 3000$
- $1 \leq w_i \leq W$
- $1 \leq v_i \leq 10^9$

---

## 算法分类
**多重背包优化**（基于贪心预处理的分组背包）

---

## 综合分析与结论

### 核心难点解析
1. **非线性价值函数**：每个物品的价值随选取次数呈二次函数衰减，无法直接应用传统背包模型
2. **无限数量优化**：物品数量无限但实际有效次数有限（约 $\lfloor W/w_i \rfloor$ 次）
3. **时间复杂度瓶颈**：暴力 DP 的 $O(NW^2)$ 复杂度无法通过

### 关键突破点
1. **贪心预处理策略**：
   - 对每个重量 $w$ 预处理可能的最优选择序列
   - 利用优先队列维护当前最优选择，每次取增量最大的物品
2. **分组背包优化**：
   - 将相同重量的物品归为一组
   - 预处理每组在不同选取次数时的最大价值
3. **二次函数特性利用**：
   - 将价值增量 $Δ = v_i - 2k +1$ 分解为独立物品
   - 通过排序保证优先选择高价值增量

### 可视化设计思路
1. **动态规划矩阵展示**：
   - 使用二维网格表示背包容量与物品组别
   - 高亮当前处理的重量组（黄色背景）
   - 用颜色渐变表示价值高低（红色高价值，蓝色低价值）
2. **贪心选择动画**：
   - 展示优先队列中增量值的排序过程
   - 动态演示物品选取次数增加时的价值变化
3. **复古像素风格**：
   - 背包容量以 8x8 像素块表示
   - 价值更新时触发音效（8-bit 风格电子音）
   - 自动演示模式可调节速度观察状态转移

---

## 最优题解推荐

### ⭐⭐⭐⭐⭐ [wangshulin] 贪心预处理 + 分组背包
**核心思路**：
1. 预处理每个重量 $w$ 的最优选择序列
2. 通过优先队列维护当前最优增量
3. 使用倒序背包更新避免重复计算

**代码亮点**：
```cpp
for(int i = 1; i <= W; i++){
    priority_queue<int> q;
    for(auto val : vec[i]) q.push(val - 1);
    for(int j = 1; j*i <= W; j++){
        f[j] = f[j-1] + q.top();
        q.push(q.top()-2); q.pop();
    }
    // 背包更新部分
    for(int j = W; j >= i; j--)
        for(int k=1; k*i<=j; k++)
            dp[j] = max(dp[j], dp[j-k*i] + f[k]);
}
```

### ⭐⭐⭐⭐ [DengDuck] 动态规划 + 优先队列优化
**创新点**：
- 将二次价值函数转换为差分序列
- 利用优先队列维护可用物品集合

### ⭐⭐⭐⭐ [Hadtsti] 斜率优化实现
**算法优势**：
- 通过数学变形转化为线性规划问题
- 使用单调队列维护最优决策点

---

## 关键代码实现

### 贪心预处理核心代码
```cpp
vector<int> vec[3001]; // 按重量分类
long long dp[3001] = {0};

// 预处理每个重量组
for(int w = 1; w <= W; w++){
    priority_queue<int> pq;
    for(int v : vec[w]) 
        pq.push(v - 1); // 初始增量
    
    vector<long long> f(w_max+1, 0);
    for(int k=1; k*w<=W; k++){
        f[k] = f[k-1] + pq.top();
        int new_val = pq.top() - 2;
        pq.pop();
        pq.push(new_val);
    }
    
    // 分组背包更新
    for(int j=W; j>=w; j--)
        for(int k=1; k<=j/w; k++)
            dp[j] = max(dp[j], dp[j-k*w] + f[k]);
}
```

---

## 同类题目推荐
1. **P1776 宝物筛选**（多重背包单调队列优化）
2. **P1757 通天之分组背包**（分组背包基础）
3. **P4095 [HEOI2013]Eden 的新背包问题**（多重背包+离线查询）

---

## 可视化实现方案

### 8-bit 风格设计
```javascript
// Canvas初始化
const canvas = document.getElementById('dp-grid');
const ctx = canvas.getContext('2d');
const CELL_SIZE = 16; // 16x16像素

// 绘制DP矩阵
function drawDPGrid() {
    for(let i=0; i<=W; i++){
        // 背包容量轴
        for(let j=0; j<=N; j++){
            // 物品组别轴
            let color = getColorByValue(dp[i][j]);
            ctx.fillStyle = color;
            ctx.fillRect(j*CELL_SIZE, i*CELL_SIZE, CELL_SIZE, CELL_SIZE);
            
            // 当前处理组高亮
            if(j == currentGroup) {
                ctx.strokeStyle = '#FFD700'; // 金色边框
                ctx.strokeRect(j*CELL_SIZE, i*CELL_SIZE, CELL_SIZE, CELL_SIZE);
            }
        }
    }
}

// 音效触发
function playSound(freq, duration) {
    const audioCtx = new AudioContext();
    const oscillator = audioCtx.createOscillator();
    oscillator.type = 'square';
    oscillator.frequency.setValueAtTime(freq, audioCtx.currentTime);
    oscillator.connect(audioCtx.destination);
    oscillator.start();
    oscillator.stop(audioCtx.currentTime + duration/1000);
}
```

---

## 总结与心得
1. **贪心选择正确性**：通过二次函数导数特性证明每次取最大增量的正确性
2. **时间复杂度优化**：将 $O(NW^2)$ 优化至 $O(W^2 \log W)$ 的关键在于预处理
3. **调试技巧**：使用极限数据验证（如 $w_i=1$ 时需处理 3000 次选择）
4. **空间优化**：滚动数组的应用减少内存消耗至 $O(W)$

---
处理用时：78.20秒