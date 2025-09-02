# 题目信息

# [ABC372D] Buildings

## 题目描述

这里有 $N$ 栋房子，从 $1$ 到 $N$ 依次编号。它们按照顺序排成一排。第 $i(1\le i\le N)$ 的房子的高度为 $H_i$。 

对于每一个 $i=1,2,\dots,N$，找到满足以下条件的整数 $j(i<j\le N)$ 的数量：

- 没有一栋在 $i$ 和 $j$ 之间的房子比 $j$ 要高。

## 说明/提示

- $1\le N\le 2\times 10^5$
- $1\le H_i\le N$
- $H_i\not=H_j(i\not= j)$
- 所有输入都为整数

## 样例 #1

### 输入

```
5

2 1 4 3 5```

### 输出

```
3 2 2 1 0```

## 样例 #2

### 输入

```
4

1 2 3 4```

### 输出

```
3 2 1 0```

## 样例 #3

### 输入

```
10

1 9 6 5 2 7 10 4 8 3```

### 输出

```
2 3 3 3 2 1 2 1 1 0```

# AI分析结果



**唯一算法分类**：单调栈

---

### **题解思路与核心难点**

**核心思路**：  
题目要求对于每个位置 `i`，统计右侧满足条件的 `j` 的数量（条件：`i` 到 `j` 之间的所有元素均不超过 `H[j]`）。通过反向维护一个单调递减栈，每次处理 `i` 时，栈的大小即为满足条件的 `j` 的数量。栈中保存的是后续元素中比当前元素大的元素，且维护递减性以保证中间无更高元素。

**解决难点**：  
1. **高效维护有效区间**：单调栈确保栈中元素始终递减，从而保证每个 `j` 的有效性。  
2. **反向处理简化统计**：从右向左遍历，栈的大小直接对应右侧符合条件的 `j` 的数量，无需额外计算区间。  

**可视化设计**：  
- **动画方案**：动态展示从右向左遍历，栈的弹出与压入操作，当前元素高亮，栈内元素以不同颜色标记。  
- **颜色标记**：当前处理元素为红色，栈内元素为绿色，被弹出元素为灰色。  
- **步进控制**：支持暂停/继续、调整速度，观察栈的变化与答案统计的同步更新。  
- **像素风格**：用 8-bit 风格渲染栈和数组，背景音乐为复古电子音效，关键操作（弹出、压入）触发音效。  

---

### **题解评分 (≥4星)**

1. **作者：zlqwq (5星)**  
   - **亮点**：反向维护单调栈，代码简洁高效，时间复杂度 `O(n)`，无需额外数据结构。  
   - **代码片段**：  
     ```cpp
     for (int i = n; i >= 1; --i) {
         sum[i] = stk.size();  // 栈大小即为答案
         while (!stk.empty() && stk.top() < h[i]) stk.pop();
         stk.push(h[i]);
     }
     ```

2. **作者：chatoudp (4星)**  
   - **亮点**：正向单调栈结合差分数组，思路清晰，但代码稍复杂。  
   - **代码片段**：  
     ```cpp
     for (int i = 1; i <= n; i++) {
         while (!st.empty() && a[st.top()] <= a[i]) st.pop();
         if (!st.empty()) t[i] = st.top();
         st.push(i);
     }
     // 差分处理区间加
     ```

3. **作者：hjyowl (4星)**  
   - **亮点**：ST表预处理区间最大值，二分查找有效左端点，思路直观但复杂度略高。  
   - **代码片段**：  
     ```cpp
     int query(int l, int r) {
         int len = r - l + 1;
         int k = log(len) / log(2);
         return max(st[l][k], st[r - (1 << k) + 1][k]);
     }
     ```

---

### **最优思路提炼**

**关键技巧**：  
- **反向单调栈**：从右向左遍历，栈中维护递减序列，栈的大小直接表示有效 `j` 的数量。  
- **时间复杂度优化**：`O(n)` 时间无需预处理，实时维护栈。  

**适用场景**：  
- 统计右侧满足特定单调性条件的问题（如更大元素、无遮挡等）。  

---

### **同类题目推荐**

1. **洛谷 P5788 [模板]单调栈**  
   - 求每个元素右侧第一个更大元素的位置，直接应用单调栈模板。  

2. **洛谷 P1901 发射站**  
   - 利用单调栈统计能量传递，维护递减序列。  

3. **洛谷 P7399 单调栈**  
   - 统计区间极值，结合单调栈优化。  

---

### **代码实现 (zlqwq 题解)**

```cpp
#include <iostream>
#include <stack>
using namespace std;
const int N = 2e5 + 5;
int n, h[N], sum[N];
stack<int> stk;

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> h[i];
    for (int i = n; i >= 1; --i) {
        sum[i] = stk.size();  // 栈大小即为答案
        while (!stk.empty() && stk.top() < h[i]) stk.pop();
        stk.push(h[i]);
    }
    for (int i = 1; i <= n; ++i) cout << sum[i] << " ";
    return 0;
}
```

---

### **可视化算法演示 (伪代码)**

```javascript
// 伪代码：反向单调栈动画演示
const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
let stack = [];
let currentIndex = n;

function draw() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // 绘制当前元素（红色）
    ctx.fillStyle = "#FF0000";
    ctx.fillRect(x, y, width, height);
    // 绘制栈内元素（绿色）
    stack.forEach((val, idx) => {
        ctx.fillStyle = "#00FF00";
        ctx.fillRect(x, y - idx * height, width, height);
    });
}

function step() {
    if (currentIndex < 1) return;
    let currentVal = h[currentIndex];
    let stackSize = stack.length;
    sum[currentIndex] = stackSize;
    // 弹出栈顶比当前小的元素（灰色动画）
    while (stack.length > 0 && stack[stack.length - 1] < currentVal) {
        stack.pop();
        playSound("pop.wav"); // 弹出音效
    }
    stack.push(currentVal);
    playSound("push.wav"); // 压入音效
    currentIndex--;
    draw();
}
```

---
处理用时：343.48秒