# 题目信息

# Package Delivery

## 题目描述

Johnny drives a truck and must deliver a package from his hometown to the district center. His hometown is located at point $ 0 $ on a number line, and the district center is located at the point $ d $ .

Johnny's truck has a gas tank that holds exactly $ n $ liters, and his tank is initially full. As he drives, the truck consumes exactly one liter per unit distance traveled. Moreover, there are $ m $ gas stations located at various points along the way to the district center. The $ i $ -th station is located at the point $ x_{i} $ on the number line and sells an unlimited amount of fuel at a price of $ p_{i} $ dollars per liter. Find the minimum cost Johnny must pay for fuel to successfully complete the delivery.

## 说明/提示

In the first sample, Johnny's truck holds $ 4 $ liters. He can drive $ 3 $ units to the first gas station, buy $ 2 $ liters of gas there (bringing the tank to $ 3 $ liters total), drive $ 3 $ more units to the third gas station, buy $ 4 $ liters there to fill up his tank, and then drive straight to the district center. His total cost is $ 2·5+4·3=22 $ dollars.

In the second sample, there is no way for Johnny to make it to the district center, as his tank cannot hold enough gas to take him from the latest gas station to the district center.

## 样例 #1

### 输入

```
10 4 4
3 5
5 8
6 3
8 4
```

### 输出

```
22
```

## 样例 #2

### 输入

```
16 5 2
8 2
5 1
```

### 输出

```
-1
```

# AI分析结果



### 综合分析与结论

#### 核心思路与算法要点
1. **贪心策略**：每次在当前加油站尽可能少加油，仅满足到达下一个更便宜的加油站；若无法到达则加满油。
2. **数据结构**：通过单调栈预处理每个加油站之后第一个油价更低的加油站，确保贪心选择的正确性。
3. **边界处理**：将终点视为油价为-1的虚拟加油站，简化终点判断逻辑。

#### 解决难点
- **贪心选择验证**：证明在加油站i到其目标加油站j之间所有油价比i高，因此优先在i加油最优。
- **时间复杂度优化**：单调栈预处理复杂度为O(m)，结合排序总复杂度O(m log m)，满足题目规模要求。

#### 可视化设计思路
- **颜色标记**：当前加油站用黄色高亮，下一个更便宜加油站用绿色标记，油箱剩余量用进度条显示。
- **动画演示**：车辆移动时实时显示油量消耗，加油时弹出油价和加油量，终点到达后展示总花费。
- **复古像素风格**：用8-bit像素风格绘制加油站和小车，音效提示加油动作和终点到达。

---

### 题解清单（≥4星）

| 题解作者 | 评分 | 关键亮点 |
|---------|------|----------|
| jdsb    | ⭐⭐⭐⭐⭐ | 思路清晰，代码简洁，利用单调栈高效预处理 |
| run_away | ⭐⭐⭐⭐ | 与jdsb思路一致，变量命名更规范 |
| Leaper_lyc | ⭐⭐⭐⭐ | 代码风格优良，处理边界干净利落 |

---

### 最优思路与技巧提炼

#### 关键代码实现（jdsb版）
```cpp
// 预处理下一个更便宜加油站
a[m+1] = {d, -1}; // 终点虚拟站
stack<int> st;
for(int i=m;i>=0;i--) {
    while(!st.empty() && a[st.top()].p > a[i].p) st.pop();
    nxt[i] = st.empty() ? m+1 : st.top();
    st.push(i);
}

// 贪心加油过程
int res = n; // 剩余油量
for(int i=0;i<=m;i++) {
    int need = max(0, min(a[nxt[i]].x - a[i].x, n) - res);
    ans += 1LL * need * a[i].p;
    res = res - (a[i+1].x - a[i].x - need);
}
```

#### 核心技巧
- **单调栈预处理**：反向遍历加油站，维护严格递增栈，快速找到每个站的后续最低油价。
- **虚拟终点处理**：将终点视为油价最低的加油站，避免特殊边界判断。

---

### 同类型题目推荐

1. **P1016 [NOIP1999 提高组] 旅行家的预算**  
   （油箱容量限制下的贪心加油策略）

2. **CF729D Sea Battle**  
   （区间覆盖与贪心选择）

3. **P9749 [CSP-J 2023] 公路**  
   （加油站问题的变种，需处理油耗与补给）

---

### 可视化算法演示（伪代码逻辑）

```javascript
// 初始化画布与参数
const canvas = initCanvas();
let truckPos = 0, fuel = n, cost = 0;

// 主循环
for (let i = 0; i <= m; ) {
    const nextStation = nxt[i];
    const maxDist = a[nextStation].x - a[i].x;
    
    // 计算加油量
    const need = Math.max(0, Math.min(maxDist, n) - fuel);
    cost += need * a[i].p;
    fuel += need;
    
    // 动画：加油特效
    showGasPouring(i, need);
    
    // 移动到下一个站
    animateTruckMove(a[i+1].x, () => {
        fuel -= (a[i+1].x - a[i].x);
    });
    
    // 边界检测
    if (fuel < 0) showGameOver();
    i = nextStation;
}
```

---

### 复古游戏化设计要点

1. **像素艺术**：  
   - 加油站用绿色像素块表示，油价用浮动数字显示。  
   - 车辆用8x8像素小车，移动时有轮胎动画。  

2. **音效设计**：  
   - `加油音效`：低音贝司声（表示花费）  
   - `到达终点`：胜利小号音效  

3. **AI演示模式**：  
   - 自动播放时可暂停观察当前油价决策逻辑  
   - 按空格键单步执行，查看每站加油量计算  

---

### 个人心得摘录

> **jdsb调试经验**：  
> "将终点处理为虚拟加油站极大简化了代码逻辑，避免了最后一段距离的特殊判断。"

> **Leaper_lyc踩坑教训**：  
> "初始未将起点0作为加油站处理，导致无法处理起点加油的情况。"  

---

通过上述分析与实现，该题的贪心策略得以高效应用，结合数据结构的预处理和边界处理，能够在O(m log m)时间复杂度内解决问题，适合大规模数据。

---
处理用时：76.34秒