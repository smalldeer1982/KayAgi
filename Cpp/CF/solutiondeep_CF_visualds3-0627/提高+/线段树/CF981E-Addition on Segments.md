# 题目信息

# Addition on Segments

## 题目描述

Grisha come to a contest and faced the following problem.

You are given an array of size $ n $ , initially consisting of zeros. The elements of the array are enumerated from $ 1 $ to $ n $ . You perform $ q $ operations on the array. The $ i $ -th operation is described with three integers $ l_i $ , $ r_i $ and $ x_i $ ( $ 1 \leq l_i \leq r_i \leq n $ , $ 1 \leq x_i \leq n $ ) and means that you should add $ x_i $ to each of the elements with indices $ l_i, l_i + 1, \ldots, r_i $ . After all operations you should find the maximum in the array.

Grisha is clever, so he solved the problem quickly.

However something went wrong inside his head and now he thinks of the following question: "consider we applied some subset of the operations to the array. What are the possible values of the maximum in the array?"

Help Grisha, find all integers $ y $ between $ 1 $ and $ n $ such that if you apply some subset (possibly empty) of the operations, then the maximum in the array becomes equal to $ y $ .

## 说明/提示

Consider the first example. If you consider the subset only of the first query, the maximum is equal to $ 1 $ . If you take only the second query, the maximum equals to $ 2 $ . If you take the first two queries, the maximum becomes $ 3 $ . If you take only the fourth query, the maximum becomes $ 4 $ . If you take the fourth query and something more, the maximum becomes greater that $ n $ , so you shouldn't print it.

In the second example you can take the first query to obtain $ 1 $ . You can take only the second query to obtain $ 2 $ . You can take all queries to obtain $ 3 $ .

In the third example you can obtain the following maximums:

- You can achieve the maximim of $ 2 $ by using queries: $ (1) $ .
- You can achieve the maximim of $ 3 $ by using queries: $ (2) $ .
- You can achieve the maximim of $ 5 $ by using queries: $ (1, 2) $ .
- You can achieve the maximim of $ 6 $ by using queries: $ (3) $ .
- You can achieve the maximim of $ 8 $ by using queries: $ (1, 3) $ .
- You can achieve the maximim of $ 9 $ by using queries: $ (2, 3) $ .

## 样例 #1

### 输入

```
4 3
1 3 1
2 4 2
3 4 4
```

### 输出

```
4
1 2 3 4 
```

## 样例 #2

### 输入

```
7 2
1 5 1
3 7 2
```

### 输出

```
3
1 2 3 
```

## 样例 #3

### 输入

```
10 3
1 1 2
1 1 3
1 1 6
```

### 输出

```
6
2 3 5 6 8 9 
```

# AI分析结果



# 题解分析与实现

## 唯一算法分类：动态规划

### 题解思路与核心难点解析
**核心问题**：在多个区间操作中选子集，求可能的最大值集合。  
**关键难点**：  
1. 如何保证所选操作覆盖的位置能够形成最大值  
2. 避免无效操作的组合（如多个区间不相交导致无法叠加）

**主流解法对比**：
1. **动态规划（背包变种）**  
   - 状态设计：`f[j]` 表示最大值 j 的最左起始位置  
   - 转移逻辑：按区间左端点排序，倒序处理每个区间，通过 `max(f[j-x], l_i)` 判断是否能用当前区间扩展最大值  
   - 时间复杂度：O(n²)  
   - 优点：无复杂数据结构，代码简洁，高效  
   - 代表题解：zhaoyp、_edge_

2. **线段树分治+bitset**  
   - 将每个操作打到线段树节点，遍历时维护 bitset 记录可能的值  
   - 时间复杂度：O(q log n + n²/ω)  
   - 优点：理论复杂度低，适用于更高数据规模  
   - 代表题解：一扶苏一、万弘

### 题解评分（≥4星）
1. **zhaoyp（5星）**  
   - 思路清晰，状态设计巧妙，利用最左位置确保覆盖  
   - 代码简洁（30行核心逻辑），滚动数组优化空间  
   - 关键代码片段：  
     ```cpp  
     for(int i=m;i;i--)  
         for(int j=n;j>=a[i].x;j--)  
             if(f[j - a[i].x] <= a[i].r)  
                 f[j] = min(f[j], max(f[j - a[i].x], a[i].l));  
     ```

2. **万弘（4星）**  
   - 线段树分治与 bitset 结合，思路新颖  
   - 代码精简，利用模板减少冗余  
   - 关键优化：  
     ```cpp  
     void dfs(std::bitset<MAXN> pre) {  
         std::bitset<MAXN> cur = pre;  
         for(auto x:rt) cur |= (cur << x);  
         // 递归处理左右子树  
     }  
     ```

3. **一扶苏一（4星）**  
   - 详细分析线段树分治与 bitset 的配合  
   - 提供可视化分步解释，适合进阶学习  
   - 核心逻辑：  
     ```cpp  
     void calc(const int o) {  
         bt[o] |= bt[o] << op[p].x; // bitset 快速转移  
         if (叶节点) ans |= bt[o];  
     }  
     ```

### 最优思路提炼
**关键技巧**：  
- **状态压缩**：将区间覆盖条件转化为动态规划的转移条件，通过最左位置判断操作叠加的可行性  
- **逆向处理**：按左端点排序后倒序处理区间，确保每个区间的左端点尽可能大，避免后效性  
- **滚动数组**：仅保留前一状态，空间复杂度优化至 O(n)

**思维突破点**：  
- 最大值的形成需要至少一个位置被所有相关区间覆盖，用最左位置确保这一点  
- 将区间选择问题转化为背包问题的变种，x_i 作为物品重量，区间覆盖条件作为转移限制

---

### 同类型题与算法套路
**类似问题特征**：  
- 操作子集选择影响最终状态（如区间覆盖、元素叠加）  
- 需要高效处理多维条件（如位置限制+数值叠加）

**推荐题目**：  
1. P4095 [HEOI2013] Eden的新背包问题（多重背包+区间查询）  
2. P5026 Lycanthropy（区间操作与最值统计）  
3. P3737 [HAOI2014] 穿越栅栏（网格路径与动态规划）

---

### 可视化与复古游戏化设计
**动态规划演示方案**：  
1. **网格动画**：  
   - 用 Canvas 绘制 n×n 网格，纵轴为当前处理区间，横轴为可能的最大值 j  
   - 高亮当前转移的 `j` 和 `j-x_i`，用不同颜色标记成功/失败的转移  
   - 显示 `f[j]` 的更新过程，如从红色（不可行）变为绿色（可行）

2. **复古像素风格**：  
   - 8-bit 音效：转移成功时播放上升音调，失败时短促“滴”声  
   - 像素字体显示当前处理的区间编号和已找到的可行 y 值  

**线段树分治演示方案**：  
1. **树形结构展开**：  
   - 在 Canvas 上绘制线段树，点击节点展开其包含的操作  
   - 显示 bitset 的二进制位变化，用闪烁效果表示位数变化  
   - 背景音乐随递归深度变化音调  

**交互控制**：  
- 步进按钮：单步执行区间处理或线段树遍历  
- 速度滑块：调整动画播放速度（0.5x~4x）  
- 模式切换：对比 DP 与线段树分治的实时性能差异  

---

### 核心代码实现（zhaoyp）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 5;
int n, m, f[maxn];
struct node { int l, r, x; } a[maxn];

void DP() {
    memset(f, 0x3f, sizeof(f));
    f[0] = 1; // 初始状态：最大值为0的位置是1
    for (int i = m; i >= 1; i--) // 倒序处理区间
        for (int j = n; j >= a[i].x; j--) // 逆序背包转移
            if (f[j - a[i].x] <= a[i].r) // 判断能否转移
                f[j] = min(f[j], max(a[i].l, f[j - a[i].x]));
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) 
        scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].x);
    sort(a + 1, a + m + 1, [](node x, node y) { 
        return x.l < y.l; // 按左端点升序排序
    });
    DP();
    // 输出部分省略
}
```

**代码要点**：  
- 排序确保处理顺序正确  
- 倒序循环避免重复计数  
- `max(a[i].l, f[j - x])` 确保新区间覆盖原有最左位置  

---

### 个人心得摘录
- **zhaoyp**：通过逆向处理解决后效性，是动态规划的经典技巧  
- **万弘**：线段树分治天然适合处理区间影响问题，与 bitset 结合实现高效状态合并  
- **sanaka87**：暴力枚举位置可能被数据误导，需谨慎验证正确性  

---

### 可视化算法步骤（动态规划）
1. **初始化**：显示全灰网格，`f[0] = 1` 标记为绿色  
2. **处理区间 i**：  
   - 高亮当前区间 `[l_i, r_i]` 和对应的 `x_i`  
   - 对每个 `j` 从 n 到 `x_i`：  
     - 若 `f[j-x_i] ≤ r_i`，计算新左端点并更新 `f[j]`  
     - 成功更新时标记为黄色闪烁，最终稳定为绿色  
3. **完成转移**：所有可行 `j` 显示为绿色，输出结果列表  

**颜色标记**：  
- 红色：`f[j]` 初始不可行  
- 绿色：转移后可行  
- 黄色：当前正在更新的状态

---
处理用时：116.32秒