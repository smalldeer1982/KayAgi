# 题目信息

# New Year Transportation

## 题目描述

New Year is coming in Line World! In this world, there are $ n $ cells numbered by integers from $ 1 $ to $ n $ , as a $ 1×n $ board. People live in cells. However, it was hard to move between distinct cells, because of the difficulty of escaping the cell. People wanted to meet people who live in other cells.

So, user tncks0121 has made a transportation system to move between these cells, to celebrate the New Year. First, he thought of $ n-1 $ positive integers $ a_{1},a_{2},...,a_{n-1} $ . For every integer $ i $ where $ 1<=i<=n-1 $ the condition $ 1<=a_{i}<=n-i $ holds. Next, he made $ n-1 $ portals, numbered by integers from 1 to $ n-1 $ . The $ i $ -th ( $ 1<=i<=n-1 $ ) portal connects cell $ i $ and cell $ (i+a_{i}) $ , and one can travel from cell $ i $ to cell $ (i+a_{i}) $ using the $ i $ -th portal. Unfortunately, one cannot use the portal backwards, which means one cannot move from cell $ (i+a_{i}) $ to cell $ i $ using the $ i $ -th portal. It is easy to see that because of condition $ 1<=a_{i}<=n-i $ one can't leave the Line World using portals.

Currently, I am standing at cell $ 1 $ , and I want to go to cell $ t $ . However, I don't know whether it is possible to go there. Please determine whether I can go to cell $ t $ by only using the construted transportation system.

## 说明/提示

In the first sample, the visited cells are: $ 1,2,4 $ ; so we can successfully visit the cell $ 4 $ .

In the second sample, the possible cells to visit are: $ 1,2,4,6,7,8 $ ; so we can't visit the cell $ 5 $ , which we want to visit.

## 样例 #1

### 输入

```
8 4
1 2 1 2 1 2 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
8 5
1 2 1 2 1 1 1
```

### 输出

```
NO
```

# AI分析结果



**唯一算法分类**  
模拟/递推

---

### **题解思路、算法要点与解决难点**

**核心逻辑**：从起点1出发，按照传送规则（i → i+a[i]）逐步跳跃，直到到达或超过目标t。  
**关键变量**：当前所在位置`pos`，通过循环更新`pos += a[pos]`。  
**解决难点**：  
1. 路径唯一性：每个位置只能跳一次，无需回溯或复杂搜索。  
2. 终止条件：当`pos == t`时成功，`pos > t`或遍历完所有可能位置时失败。  

**对比题解**：  
- **线性递推**（Register、HNYLMS_MuQiuFeng）：直接模拟跳跃过程，时间复杂度O(n)，空间O(1)。  
- **标记数组**（RainFestival）：用数组记录可达性，空间O(n)，但同样线性完成。  
- **图论算法**（Lips）：虽然正确，但使用Dijkstra冗余，复杂度O(n log n)。  

---

### **题解评分 (≥4星)**

1. **Register的题解（5星）**  
   - 思路清晰，代码简洁，直接模拟跳跃过程。  
   - 循环条件`i < t`巧妙避免无效计算。  
   - 时间复杂度最优。  

2. **empty_zhm的递推代码（4星）**  
   - 核心逻辑与Register一致，但代码更短。  
   - 可读性稍弱（如`j += N[j]`的写法）。  

3. **RainFestival的标记数组法（4星）**  
   - 思路直观，用数组标记可达性。  
   - 额外空间O(n)，但适合教学演示。  

---

### **最优思路/技巧提炼**

**关键技巧**：  
- **线性跳跃**：利用路径唯一性，直接模拟无需回溯。  
- **循环条件优化**：`while (pos < t) pos += a[pos]`，确保及时终止。  

**代码片段**：  
```cpp
int pos = 1;
while (pos < t) pos += a[pos];
cout << (pos == t ? "YES" : "NO");
```

---

### **同类型题推荐**

1. **P1036 选数**（DFS简单路径）  
2. **P1219 八皇后**（回溯唯一路径）  
3. **P1706 全排列问题**（唯一递推生成）  

---

### **可视化与算法演示**

**动画方案**：  
1. **像素网格**：用Canvas绘制n个单元格，1号绿色，t号红色。  
2. **跳跃过程**：  
   - 当前单元格高亮黄色，跳跃时显示箭头到`pos+a[pos]`。  
   - 每步播放“跳跃音效”（短促哔声）。  
3. **结束效果**：  
   - 到达t时单元格闪烁，播放成功音效（上扬音调）。  
   - 超过t时显示灰色，播放失败音效（低音）。  

**复古风格**：  
- **8位调色板**：绿（#00FF00）、红（#FF0000）、黄（#FFFF00）。  
- **音效**：Web Audio生成方波音效。  

**交互设计**：  
- 速度滑块控制步进间隔（100ms~1s）。  
- 按钮：开始/暂停/重置。  

---

### **代码实现（核心逻辑）**

```cpp
#include <iostream>
using namespace std;

int main() {
    int n, t, a[30001];
    cin >> n >> t;
    for (int i = 1; i < n; ++i) cin >> a[i];
    
    int pos = 1;
    while (pos < t) pos += a[pos];
    
    cout << (pos == t ? "YES" : "NO");
    return 0;
}
```

---

### **总结**

本题通过唯一路径的线性递推即可高效解决，无需复杂算法。可视化设计以像素风格和音效增强理解，适合教学演示。

---
处理用时：54.88秒