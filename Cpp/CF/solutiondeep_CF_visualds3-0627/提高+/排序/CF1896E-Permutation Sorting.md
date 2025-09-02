# 题目信息

# Permutation Sorting

## 题目描述

You are given a permutation $ ^\dagger $ $ a $ of size $ n $ . We call an index $ i $ good if $ a_i=i $ is satisfied. After each second, we rotate all indices that are not good to the right by one position. Formally,

- Let $ s_1,s_2,\ldots,s_k $ be the indices of $ a $ that are not good in increasing order. That is, $ s_j < s_{j+1} $ and if index $ i $ is not good, then there exists $ j $ such that $ s_j=i $ .
- For each $ i $ from $ 1 $ to $ k $ , we assign $ a_{s_{(i \% k+1)}} := a_{s_i} $ all at once.

For each $ i $ from $ 1 $ to $ n $ , find the first time that index $ i $ becomes good.

 $ ^\dagger $ A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, $ 2 $ and $ 5 $ are already in the correct position so indices $ 2 $ and $ 5 $ become good at $ 0 $ second. After $ 1 $ second, a cyclic shift will be done with $ s=[1, 3, 4] $ , resulting in array $ a=[1, 2, 3, 4, 5] $ . Notice that indices $ 1 $ , $ 3 $ and $ 4 $ become good at $ 1 $ second.

In the second test case, $ 5 $ is already in the correct position, so index $ 5 $ becomes good at $ 0 $ second. After $ 1 $ second, a cyclic shift will be done with $ s=[1, 2, 3, 4, 6] $ , resulting in array $ a=[3, 2, 1, 4, 5, 6] $ . Notice that indices $ 2 $ , $ 4 $ and $ 6 $ become good at $ 1 $ second. After $ 2 $ seconds, a cyclic shift will be done with $ s=[1, 3] $ , resulting in array $ a=[1, 2, 3, 4, 5, 6] $ . Notice that indices $ 1 $ and $ 3 $ become good at $ 2 $ second.

## 样例 #1

### 输入

```
2
5
3 2 4 1 5
6
2 1 4 6 5 3```

### 输出

```
1 0 1 1 0 
2 1 2 1 0 1```

# AI分析结果



### 唯一算法分类
二维数点/偏序问题

---

### 题解思路、算法要点与解决难点

#### 核心逻辑推导
1. **破环为链**：将排列复制一份接在原数组后（长度 2n），使得循环右移转化为线性右移  
2. **目标位置映射**：对元素 a[i]，若 i ≤ a[i]，目标位置为 a[i]；否则为 a[i]+n  
3. **区间覆盖模型**：每个元素的移动轨迹可视为区间 [i, target_i]，答案 = 区间长度 - 被完整包含的区间数  
4. **二维数点**：统计所有左端点 ∈ [i+1, target_i-1] 且右端点 ∈ [i+1, target_i] 的区间数

#### 数据结构选择
- **树状数组**：从后往前扫描处理，维护右端点出现次数，查询区间右端点分布  
- **线段树**：支持区间排序与二分查询（部分解法用于处理更复杂的区间关系）

#### 解决难点
- **循环移位的线性化**：通过复制排列巧妙消除环形结构的复杂性  
- **跳跃次数的动态统计**：利用离线处理与逆序扫描，保证每次查询时只统计已处理的更小区间  
- **跨环区间的特殊处理**：通过将目标位置映射到 2n 范围内，统一处理原环与复制环上的区间关系

---

### 题解评分（≥4星）

#### 1. Register_int（5星）
- **亮点**：最简洁的实现，仅 30 行代码完成核心逻辑  
- **关键代码**：逆序扫描+树状数组，通过 r[i] = a[i] 或 a[i]+n 统一处理跨环情况  
- **优化点**：直接复用原数组空间存储临时变量，减少内存消耗

#### 2. MaxBlazeResFire（4.5星）
- **亮点**：引入 pos[i] 概念，通过区间包含关系的直观解释降低理解难度  
- **代码特色**：独立处理跨环区间的贡献，使用预处理 flag 数组优化空位统计

#### 3. do_it_tomorrow（4星）
- **亮点**：图文结合解释破环为链与区间连线，适合初学者理解  
- **可改进点**：代码注释较少，变量命名可读性待提升

---

### 最优思路与技巧提炼

#### 核心技巧
```c++
// 树状数组离线处理核心代码（Register_int 解法）
for(int i = 2 * n; i; i--) {
    if(!r[i]) continue;
    if(i <= n) ans[a[i]] = r[i] - i + ask(i-1) - ask(r[i]);
    add(r[i], 1);
}
```

#### 思维突破点
- **跳跃次数与区间覆盖的等价转换**：每个被完整包含的区间对应一次跳跃减少  
- **逆序处理保证时序性**：从后往前扫描时，已处理的区间必然在当前区间右侧，避免重复统计

---

### 同类型题与算法套路
1. **二维偏序问题**：统计满足 i < j 且 a[i] > a[j] 的逆序对（P1908）  
2. **区间覆盖统计**：求线段覆盖区域中被完全包含的线段数（CF1896E）  
3. **循环结构线性化**：环形均分纸牌问题转化为线性前缀和（P2512）

---

### 推荐相似题目
1. **P1972 [SDOI2009]HH的项链**（区间不同数个数，树状数组离线处理）  
2. **P3368 【模板】树状数组 2**（区间修改+单点查询，练习基础操作）  
3. **CF1520F2 Guess the K-th Zero (Hard version)**（交互式二维数点问题）

---

### 可视化与算法演示设计

#### 动画方案
1. **像素风格展示**  
   - **数据结构**：8-bit 风格的树状数组节点，用绿色像素块表示已存储的右端点  
   - **元素移动**：蓝色方块表示当前处理的区间[i, target_i]，红色箭头显示跳跃次数计算过程  
   - **音效设计**：  
     - 成功统计区间时播放 "ping" 音效  
     - 树状数组更新时触发 8-bit 电子音

2. **交互控制**  
   ```javascript
   // 伪代码：Canvas 绘制树状数组更新
   function drawUpdate(pos) {
       ctx.fillStyle = '#FF0000'; // 高亮当前处理位置
       ctx.fillRect(pos * gridSize, 0, gridSize, gridSize);
       setTimeout(() => {
           ctx.fillStyle = '#00FF00'; // 恢复已更新节点颜色
           updateBITAnimation(pos);
       }, 500);
   }
   ```

3. **自动演示模式**  
   - 按元素初始位置排序后自动播放处理流程  
   - 右侧信息面板显示当前区间长度与已跳过的区间数

---

### 个人心得摘录
> "**wusixuan**：当发现循环移位的相对位置不变性后，问题立刻转化为经典的区间包含统计，这种将动态过程转化为静态几何关系的能力需要大量题目积累"

> **Mashu77**：调试时发现跨环区间的贡献计算容易遗漏，最终通过将目标位置统一映射到 2n 范围解决了边界问题

---

### 核心代码实现（Register_int 解法）
```c++
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e6 + 10;
int c[MAXN], n;

void add(int k) { for (; k <= 2*n; k += k&-k) c[k]++; }
int ask(int k) { int res=0; for (; k; k&=k-1) res += c[k]; return res; }

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        vector<int> a(n+1), r(2*n+1), ans(n+1);
        for(int i=1; i<=n; ++i) {
            scanf("%d", &a[i]);
            if(i <= a[i]) r[i]=a[i], r[i+n]=a[i]+n;
            else r[i] = a[i]+n;
        }
        for(int i=2*n; i>=1; --i) {
            if(!r[i]) continue;
            if(i <= n) ans[a[i]] = r[i]-i + ask(i-1) - ask(r[i]);
            add(r[i]);
        }
        for(int i=1; i<=n; ++i) printf("%d ", ans[i]);
        printf("\n");
        memset(c, 0, sizeof(c));
    }
}
```

---
处理用时：79.92秒