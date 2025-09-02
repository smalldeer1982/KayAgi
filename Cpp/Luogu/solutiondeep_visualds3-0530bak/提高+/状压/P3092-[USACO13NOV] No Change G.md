# 题目信息

# [USACO13NOV] No Change G

## 题目描述

Farmer John is at the market to purchase supplies for his farm.  He has in his pocket K coins (1 <= K <= 16), each with value in the range 1..100,000,000.  FJ would like to make a sequence of N purchases (1 <= N <= 100,000), where the ith purchase costs c(i) units of money (1 <= c(i) <= 10,000).  As he makes this sequence of purchases, he can periodically stop and pay, with a single coin, for all the purchases made since his last payment (of course, the single coin he uses must be large enough to pay for all of these).  Unfortunately, the vendors at the market are completely out of change, so whenever FJ uses a coin that is larger than the amount of money he owes, he sadly receives no changes in return!

Please compute the maximum amount of money FJ can end up with after making his N purchases in sequence.  Output -1 if it is impossible for FJ to make all of his purchases.

约翰到商场购物，他的钱包里有K(1 <= K <= 16)个硬币，面值的范围是1..100,000,000。

约翰想按顺序买 N个物品(1 <= N <= 100,000)，第i个物品需要花费c(i)块钱，(1 <= c(i) <= 10,000)。

在依次进行的购买N个物品的过程中，约翰可以随时停下来付款，每次付款只用一个硬币，支付购买的内容是从上一次支付后开始到现在的这些所有物品（前提是该硬币足以支付这些物品的费用）。不幸的是，商场的收银机坏了，如果约翰支付的硬币面值大于所需的费用，他不会得到任何找零。

请计算出在购买完N个物品后，约翰最多剩下多少钱。如果无法完成购买，输出-1


## 说明/提示

FJ has 3 coins of values 12, 15, and 10.  He must make purchases in sequence of value 6, 3, 3, 2, 3, and 7.


FJ spends his 10-unit coin on the first two purchases, then the 15-unit coin on the remaining purchases.  This leaves him with the 12-unit coin.


## 样例 #1

### 输入

```
3 6 
12 
15 
10 
6 
3 
3 
2 
3 
7 
```

### 输出

```
12 
```

# AI分析结果



# 算法分类
**状压DP**

---

## 综合分析与结论

### 核心算法流程
1. **状态表示**：用二进制状态 `i` 表示已使用的硬币集合，`dp[i]` 表示该状态下能购买的最大物品数  
2. **转移逻辑**：枚举每个未使用的硬币 `j`，计算该硬币从 `dp[i]+1` 开始能覆盖的最大连续物品数，更新 `dp[i|(1<<j)]`  
3. **覆盖计算**：
   - **二分法**：通过前缀和数组二分查找硬币 `j` 的最大覆盖范围，时间复杂度 `O(logn)`  
   - **双指针预处理**：预先计算每个硬币在所有起始点的最大覆盖范围，转移时直接查表，时间复杂度 `O(1)`  
4. **答案统计**：遍历所有满足 `dp[i]=n` 的状态，计算未使用硬币的总面值，取最大值  

### 可视化设计思路
1. **像素化状态展示**：用 8 位像素风格展示二进制状态，每个硬币对应一个像素块，已使用硬币显示为红色，未使用为绿色  
2. **物品覆盖动画**：用进度条表示物品购买进度，硬币使用时触发覆盖动画（如绿色波浪覆盖物品格子）  
3. **音效交互**：  
   - 硬币选中时播放 `8-bit` 点击音效  
   - 状态转移成功时播放短促上升音调  
   - 最终答案计算时播放经典 FC 通关音乐  
4. **自动演示模式**：模拟 AI 逐步执行状压 DP 流程，展示状态转移路径，支持暂停/步进观察  

---

## 题解清单（≥4星）

### 1. [jun1lesszZZ] 状压DP + 二分（★★★★☆）
**亮点**：  
- 清晰定义 `dp[i]` 为状态 `i` 能购买的最大物品数  
- 利用前缀和与二分优化覆盖范围计算  
- 代码中通过 `check()` 函数实现高效区间查询  
**核心代码**：
```cpp
int check(int x, int pos) { // x为硬币面值，pos为起始位置
    int l = pos, r = n, res = pos-1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (sum[mid] - sum[pos-1] <= x) {
            res = mid;
            l = mid + 1;
        } else r = mid - 1;
    }
    return res;
}
```

### 2. [Imakf] 双指针预处理（★★★★★）
**亮点**：  
- 预处理 `far[i][j]` 表示硬币 `i` 从 `j` 开始的最大覆盖  
- 将转移复杂度优化至 `O(1)`，显著提升效率  
- 代码结构简洁，变量命名清晰  
**核心预处理**：
```cpp
// 预处理每个硬币的覆盖范围
for (int i=1; i<=k; i++) {
    int sum = 0, r = 1;
    for (int l=1; l<=n; l++) {
        while (r <= n && sum + cost[r] <= coin[i]) 
            sum += cost[r++];
        far[i][l] = r - 1;
        sum -= cost[l]; // 滑动窗口
    }
}
```

### 3. [asuldb] 单调队列优化（★★★★☆）
**亮点**：  
- 使用单调队列维护 `sum[dp[j]] + coin[j]` 的最大值  
- 减少二分查找次数，提升常数效率  
- 创新性提出类似游戏关卡的自动演示思路  
**核心优化**：
```cpp
deque<int> q;
for (每个状态i的转移) {
    while (!q.empty() && q.back() < new_value) 
        q.pop_back();
    q.push_back(new_value);
    dp[i] = find(q.front()); // 只需一次二分
}
```

---

## 同类型题目推荐
1. **P1433 吃奶酪**（状压DP + 几何距离计算）  
2. **P1171 售货员的难题**（经典TSP状压问题）  
3. **P3959 宝藏**（状压DP + 最小生成树思想）  

---

## 可视化代码片段（Canvas 动画）

```javascript
// 硬币状态像素块绘制
function drawCoins(ctx, state) {
    for (let i=0; i<16; i++) {
        ctx.fillStyle = (state & (1<<i)) ? "#FF5555" : "#55FF55";
        ctx.fillRect(10+i*30, 10, 25, 25); // 每个硬币占30px宽
    }
}

// 物品覆盖动画
function animateCover(ctx, start, end) {
    let current = start;
    const anim = setInterval(() => {
        ctx.fillStyle = "#55FF55";
        ctx.fillRect(start*10, 50, (current-start)*10, 20);
        current++;
        if (current > end) clearInterval(anim);
    }, 100); // 每100ms覆盖一个物品
}
```

---

## 关键调试心得
1. **前缀和下标陷阱**：必须保证 `sum[0]=0`，否则未选硬币时可能错误计算  
2. **二分边界处理**：当硬币无法购买任何物品时返回 `pos-1` 而非 `0`  
3. **状态转移顺序**：必须按状态从小到大枚举，确保子状态已计算完成  
4. **答案初始化**：剩余金额初始值设为 `-1`，避免合法答案 `0` 被误判为无解  

---

## 复古音效设计
```javascript
// Web Audio 音效触发
function playSound(type) {
    const ctx = new AudioContext();
    const osc = ctx.createOscillator();
    osc.type = "square"; // 8-bit 方波音色
    osc.frequency.value = type === "success" ? 880 : 440;
    osc.connect(ctx.destination);
    osc.start();
    osc.stop(ctx.currentTime + 0.1); // 短促音效
}
```

---
处理用时：73.56秒