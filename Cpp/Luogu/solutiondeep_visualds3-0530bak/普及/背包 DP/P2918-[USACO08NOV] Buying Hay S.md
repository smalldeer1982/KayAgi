# 题目信息

# [USACO08NOV] Buying Hay S

## 题目描述

Farmer John is running out of supplies and needs to purchase H (1 <= H <= 50,000) pounds of hay for his cows.

He knows N (1 <= N <= 100) hay suppliers conveniently numbered 1..N. Supplier i sells packages that contain P\_i (1 <= P\_i <= 5,000) pounds of hay at a cost of C\_i (1 <= C\_i <= 5,000) dollars. Each supplier has an unlimited number of packages available, and the packages must be bought whole.

Help FJ by finding the minimum cost necessary to purchase at least H pounds of hay.

约翰的干草库存已经告罄，他打算为奶牛们采购 $H(1 \leq H \leq 50000)$ 磅干草。

他知道 $N(1 \leq N\leq 100)$ 个干草公司，现在用 $1$ 到 $N$ 给它们编号。第 $i$ 公司卖的干草包重量为 $P_i (1 \leq P_i \leq 5,000)$ 磅，需要的开销为 $C_i (1 \leq C_i \leq 5,000)$ 美元。每个干草公司的货源都十分充足， 可以卖出无限多的干草包。

帮助约翰找到最小的开销来满足需要，即采购到至少 $H$ 磅干草。

## 说明/提示

FJ can buy three packages from the second supplier for a total cost of 9.


## 样例 #1

### 输入

```
2 15 
3 2 
5 3 
```

### 输出

```
9 
```

# AI分析结果



**唯一算法分类**：动态规划（完全背包）

---

### **题解思路与解决难点**

1. **核心思路**  
   - **完全背包变种**：将每个供应商的干草包视为可无限取的物品，求解满足至少 `H` 磅的最小费用。  
   - **状态扩展**：需考虑购买量超过 `H` 但更优的情况，状态转移范围需覆盖 `H` 到 `H + max_p`（`max_p` 是单个干草包的最大重量，即 5000），避免遗漏更优解。

2. **关键难点**  
   - **“至少”条件处理**：需在 `H ≤ j ≤ H + 5000` 范围内寻找最小值，而非仅 `j = H`。  
   - **状态转移方程**：`f[j] = min(f[j], f[j - p[i]] + c[i])`，其中 `f[j]` 表示达到至少 `j` 磅的最小费用。

3. **算法优化**  
   - **扩展背包容量**：将容量上限设为 `H + 5000`，确保覆盖所有可能更优的解。  
   - **初始化优化**：初始时 `f[0] = 0`（零磅费用为零），其余设为极大值（表示不可达）。

---

### **题解评分 (≥4星)**

1. **EarthGiao (5星)**  
   - **亮点**：详细解释为何扩展到 `H + 5000`，代码清晰，注释完整。  
   - **代码**：正确初始化并遍历所有可能区间，最终取最小值。

2. **CCF_zkskyer (4星)**  
   - **亮点**：代码简洁，状态转移逻辑明确，但解释较简略。  
   - **优化点**：通过 `h + Max` 扩展范围，避免遗漏解。

3. **Sunbread (4星)**  
   - **亮点**：代码规范，数学证明覆盖范围合理性，适合进阶理解。  
   - **实践性**：直接使用 `H + 5000` 范围，逻辑清晰。

---

### **最优思路与技巧提炼**

- **状态扩展法**：将背包容量扩展至 `H + max_p`，确保覆盖所有可能更优解。  
- **反向定义优化**：将费用作为状态值，重量作为约束（如 `Egg_eating_master` 的解法），减少状态转移次数。  
- **动态规划初始化**：合理设置初始值（`f[0] = 0`，其他为极大值），避免无效状态干扰。

---

### **同类型题与算法套路**

1. **类似问题**  
   - **P1510 精卫填海**：最小化体积以满足容量需求。  
   - **P2563 买干草**：完全背包求至少达到指定重量的最小费用。  
   - **P1616 疯狂的采药**：完全背包模板题，求最大价值。

2. **通用解法**  
   - **完全背包变种**：处理“至少”条件时扩展背包容量，状态转移时取最小值。

---

### **推荐题目**

1. **P2918 [USACO08NOV] Buying Hay S**（本题）  
2. **P1510 精卫填海**（最小体积满足需求）  
3. **P2563 [USACO12MAR] 买干草 Buying Hay**（完全背包变种）

---

### **个人心得摘录**

- **EarthGiao**：调试时发现需扩展范围，否则样例无法通过。  
- **Hiraeth**：初始仅处理到 `H`，结果部分错误，后通过扩展范围修正。  
- **flyfree**：尝试直接处理到 `H`，但未考虑超量更优情况，代码存在漏洞。

---

### **可视化与算法演示**

1. **动画设计**  
   - **网格展示**：在 Canvas 绘制一维数组 `f[]`，横轴为重量，纵轴为费用。  
   - **颜色标记**：  
     - 红色：当前更新的 `j` 位置。  
     - 绿色：已确定的最小费用。  
   - **步进控制**：单步执行物品循环，高亮当前处理的供应商和重量范围。

2. **复古像素风格**  
   - **8位音效**：每次状态更新时播放短促音效，找到最优解时播放胜利音效。  
   - **Canvas 绘制**：用像素块表示费用值，颜色深浅表示费用高低。

```javascript
// 示例：动态规划状态更新（伪代码）
function animateDP() {
  for (let i = 0; i < suppliers.length; i++) {
    for (let j = suppliers[i].p; j <= H + 5000; j++) {
      // 更新 f[j]，高亮当前 j 和供应商 i
      ctx.fillStyle = (f[j] < Infinity) ? "#00FF00" : "#FF0000";
      ctx.fillRect(j * 10, 0, 10, 10);
      playSound("update");
    }
  }
}
```

---

### **核心代码实现**

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int MAX_H = 55000;
int f[MAX_H], p[105], c[105];

int main() {
    int n, h;
    cin >> n >> h;
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= n; i++) cin >> p[i] >> c[i];
    
    for (int i = 1; i <= n; i++) {
        for (int j = p[i]; j <= h + 5000; j++) {
            f[j] = min(f[j], f[j - p[i]] + c[i]);
        }
    }
    
    int ans = 0x3f3f3f3f;
    for (int i = h; i <= h + 5000; i++) ans = min(ans, f[i]);
    cout << ans << endl;
    return 0;
}
```

---
处理用时：146.06秒