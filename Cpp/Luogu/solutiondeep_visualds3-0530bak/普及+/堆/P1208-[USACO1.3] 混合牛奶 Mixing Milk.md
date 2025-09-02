# 题目信息

# [USACO1.3] 混合牛奶 Mixing Milk

## 题目描述

由于乳制品产业利润很低，所以降低原材料（牛奶）价格就变得十分重要。帮助 Marry 乳业找到最优的牛奶采购方案。

Marry 乳业从一些奶农手中采购牛奶，并且每一位奶农为乳制品加工企业提供的价格可能相同。此外，就像每头奶牛每天只能挤出固定数量的奶，每位奶农每天能提供的牛奶数量是一定的。每天 Marry 乳业可以从奶农手中采购到小于或者等于奶农最大产量的整数数量的牛奶。

给出 Marry 乳业每天对牛奶的需求量，还有每位奶农提供的牛奶单价和产量。计算采购足够数量的牛奶所需的最小花费。

注：每天所有奶农的总产量不少于 Marry 乳业的需求量。

## 说明/提示

【数据范围】  
对于 $100\%$ 的数据：  
$0 \le n,a_i \le 2 \times 10^6$，$0\le m \le 5000$，$0 \le p_i \le 1000$

题目翻译来自 NOCOW。

USACO Training Section 1.3

## 样例 #1

### 输入

```
100 5
5 20
9 40
3 10
8 80
6 30
```

### 输出

```
630
```

# AI分析结果



# 算法分类
**贪心算法**

## 题解思路与核心分析
### 算法核心思想
题目要求以最小成本采购足够的牛奶，本质是典型的贪心问题。核心策略是优先采购单价最低的牛奶，直至满足需求量。关键实现方式有两种：
1. **结构体排序法**：将奶农按单价升序排列，依次批量采购
2. **桶排序法**：利用单价范围有限（0-1000）的特点，统计各单价总产量后线性扫描

### 解决难点对比
| 方法                | 时间复杂度   | 空间复杂度 | 适用场景                   | 优势点                  |
|---------------------|--------------|------------|----------------------------|-------------------------|
| 结构体排序法        | O(m log m)   | O(m)       | 通用场景                   | 代码直观，易理解        |
| 桶排序法            | O(m + 1000)  | O(1000)    | 单价范围有限（如本题条件） | 效率碾压式优势          |

### 关键实现细节
- **结构体排序法**需要处理单价相同时的排序稳定性
- **桶排序法**需注意当单价为0时的特殊处理
- 两种方法都需要注意需求量为0时的边界条件

## 高星题解推荐（≥4星）
1. **远航之曲（5星）**
   - 亮点：创新性使用桶排序，时间复杂度最优
   - 代码片段：
     ```cpp
     int G[1001] = {0};
     for (每个奶农) G[单价] += 产量; // 桶统计
     for (int price=0; ; price++) {
         if (剩余需求 ≤ G[price]) { // 本层能完成采购
             总花费 += 剩余需求 * price;
             break;
         }
         总花费 += G[price] * price;
         剩余需求 -= G[price];
     }
     ```

2. **杨咩咩咩啊（4星）**
   - 亮点：标准结构体解法，最易理解的实现
   - 代码片段：
     ```cpp
     struct node { int price, amount; };
     sort(farmers, farmers+m, [](auto &a, auto &b){
         return a.price < b.price; // 单价优先排序
     });
     for (auto &f : farmers) {
         int buy = min(剩余需求, f.amount);
         总花费 += buy * f.price;
         剩余需求 -= buy;
     }
     ```

3. **yzx4188（4星）**
   - 亮点：无排序暴力解法，思维独特
   - 代码片段：
     ```cpp
     while (需求未满足) {
         int min_price = 找当前最低单价的奶农;
         if (该奶农产量 > 剩余需求) {
             总花费 += 剩余需求 * min_price;
             break;
         }
         总花费 += 奶农产量 * min_price;
         标记该奶农已采购完毕;
     }
     ```

## 最优思路提炼
**桶排序法的降维打击**：当数据存在范围限制时（如本题单价≤1000），将O(m log m)的排序复杂度降为O(m + 1000)，实现效率飞跃。核心步骤：
1. 创建价格桶统计各单价总产量
2. 从最低价（0元）开始线性扫描桶
3. 批量采购当前价格层的全部牛奶，直至满足需求

## 同类题目推荐
1. P1090 [NOIP2004 提高组] 合并果子（贪心+优先队列）
2. P3817 小A的糖果（前缀和+贪心）
3. P1223 排队接水（贪心排序）

## 可视化设计
### 算法演示方案
**8位像素风格贪心模拟器**：
```html
<canvas id="milk-canvas"></canvas>
<script>
// 初始化像素画布（800x600，16色调色板）
const canvas = document.getElementById('milk-canvas');
const ctx = canvas.getContext('2d');
const COLORS = ['#000','#00F','#0F0','#0FF','#F00','#F0F','#FF0','#FFF'];

// 绘制价格桶（每个颜色块代表一个单价层）
function drawBuckets(buckets) {
    let x = 0;
    for (let price in buckets) {
        ctx.fillStyle = COLORS[price % 8];
        ctx.fillRect(x, 0, 20, buckets[price] * 10); // 高度映射产量
        x += 25;
    }
}

// 播放采购动画（带8bit音效）
function animatePurchase(price) {
    const audio = new Audio('data:audio/wav;base64,UklGRl9...'); // 8bit音效
    audio.play();
    // 高亮当前价格块并减少高度...
}
</script>
```

### 交互特性
- **步进控制**：空格键单步执行采购
- **音效反馈**：不同价格层采购时播放不同音高提示
- **自动演示**：按A键启动AI自动采购，速度可调
- **数据对比**：T键切换结构体排序法与桶排序法的可视化对比

## 核心代码实现（桶排序法）
```cpp
#include <iostream>
using namespace std;

int main() {
    int G[1001] = {0}; // 价格桶
    int need, m, total = 0;
    cin >> need >> m;
    
    // 统计各价格总产量
    while (m--) {
        int p, a;
        cin >> p >> a;
        G[p] += a;
    }
    
    // 按价格扫描采购
    for (int price = 0; price <= 1000; ++price) {
        if (need <= 0) break;
        if (G[price] == 0) continue;
        
        int buy = min(need, G[price]);
        total += buy * price;
        need -= buy;
    }
    
    cout << total;
    return 0;
}
```

---
处理用时：90.90秒