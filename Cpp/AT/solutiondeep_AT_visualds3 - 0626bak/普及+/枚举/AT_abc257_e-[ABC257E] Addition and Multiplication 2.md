# 题目信息

# [ABC257E] Addition and Multiplication 2

## 题目描述

高桥君有一个整数 $x$ 。一开始的时候， $x=0$ 。

高桥君可以无限执行以下操作：

- 选择一个整数 $i$ （ $1 \leq i \leq 9$ ）。支付 $C_i$ 日元，把 $x$ 变为 $10x+i$ 。

高桥君有 $N$ 日元，问 $x$ 最大是多少？

### 约束 ###

$1 \leq N \leq 10^6$

$1 \leq C_i \leq N$

保证 $N,C_i$ 都是整数。

## 样例 #1

### 输入

```
5
5 4 3 3 2 5 3 5 3```

### 输出

```
95```

## 样例 #2

### 输入

```
20
1 1 1 1 1 1 1 1 1```

### 输出

```
99999999999999999999```

# AI分析结果



### 唯一算法分类
贪心算法

---

### 综合分析与结论
**核心思路**：  
1. **位数最大化**：优先用最便宜的数字构造最长位数，确保数值的位数最大。  
2. **高位贪心替换**：从高位到低位，尽可能替换更大的数字，但要保证剩余金额足够填满后续位数的最低价。

**解决难点**：  
- 正确推导替换条件：当前剩余金额必须满足 `剩余金额 - 当前数字花费 ≥ 剩余位数 × 最便宜单价`，确保后续位数能填满。  
- 时间复杂度优化：通过双循环（外层位数、内层数字选择）将复杂度控制在 O(9L)，适用于 N ≤ 1e6。

**可视化设计**：  
1. **动画步骤**：  
   - 初始状态展示所有数字的花费，高亮最便宜的数字。  
   - 逐位生成结果：高亮当前处理的位，遍历 9→1 检查替换条件，满足时播放音效并更新金额。  
   - 颜色标记：已确定的位（绿色）、当前尝试的数字（黄色）、不可选数字（灰色）。  
2. **复古像素风格**：  
   - 使用 8-bit 数字块表示每个位，背景色块显示当前金额和剩余位数需求。  
   - 音效：选择成功时播放“升级”音效，替换失败时短促“错误”音效。  

---

### 题解清单（≥4星）
1. **ikunTLE（5星）**  
   - 亮点：代码简洁，逻辑清晰，外层循环逐位处理，内层从9到1贪心替换。  
   - 关键代码：`if(n-a[j]>=(l-i)*minn)` 确保剩余金额足够填充后续位数。  

2. **DengDuck（4.5星）**  
   - 亮点：详细注释，强调“位数优先”原则，变量命名易懂。  
   - 关键代码：`(n - c[j]) >= (len - i) * mn` 条件判断与ikunTLE一致。  

3. **沉石鱼惊旋（4星）**  
   - 亮点：分阶段处理（先计算最大位数，再置换剩余金额），代码结构清晰。  
   - 关键思想：通过 `s = n - cnt * mn` 计算可置换的剩余金额，逐个替换高位。  

---

### 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, c[10], min_cost = INT_MAX;
    cin >> n;
    for (int i = 1; i <= 9; i++) {
        cin >> c[i];
        min_cost = min(min_cost, c[i]);
    }
    int max_len = n / min_cost; // 最大位数
    for (int i = 0; i < max_len; i++) { // 逐位处理
        for (int j = 9; j >= 1; j--) { // 贪心选最大数字
            if (n >= c[j] && (n - c[j]) >= (max_len - i - 1) * min_cost) {
                cout << j;
                n -= c[j];
                break;
            }
        }
    }
    return 0;
}
```

---

### 同类型题与套路
**通用解法**：  
- **位数贪心**：优先最大化位数，再逐位优化数值（如 [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)）。  
- **价格置换**：在总成本约束下，用高价替换低价以提升结果（如背包问题的贪心优化）。  

**相似题目推荐**：  
1. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995)  
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)  
3. [P1016 旅行家的预算](https://www.luogu.com.cn/problem/P1016)  

---

### 个人心得摘录
- **调试教训**：初始代码未正确处理剩余金额的分配，导致位数不足。  
- **顿悟点**：替换条件中的 `(剩余位数 × 最便宜单价)` 是保证后续填满的关键。  

---

### 复古游戏化动画示例（伪代码）
```javascript
// 初始化 Canvas 和音效
const canvas = initCanvas();
const beepSuccess = loadSound('8bit-success.wav');
const beepError = loadSound('8bit-error.wav');

function animateStep(bitPos, currentN) {
    highlightCurrentBit(bitPos); // 高亮当前处理位
    for (let j = 9; j >= 1; j--) {
        drawNumberAttempt(j); // 显示尝试的数字
        if (checkCondition(j, currentN, bitPos)) {
            beepSuccess.play();
            updateN(currentN - cost[j]); // 扣钱动画
            fillBitWith(j, bitPos); // 填充数字
            break;
        } else {
            beepError.play();
        }
    }
}
```

---
处理用时：105.24秒