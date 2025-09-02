# 题目信息

# 眼红的Medusa

## 题目描述

虽然 Miss Medusa 到了北京，领了科技创新奖，但是她还是觉得不满意。原因是：他发现很多人都和她一样获了科技创新奖，特别是其中的某些人，还获得了另一个奖项——特殊贡献奖。而越多的人获得了两个奖项，Miss Medusa就会越眼红。于是她决定统计有哪些人获得了两个奖项，来知道自己有多眼红。

## 说明/提示

对于 $60\%$ 的数据，$0 \leq n, m \leq 1000$，获得奖项的人的编号 $\lt 2 \times 10^9$；

对于 $100\%$ 的数据，$0 \leq n, m \leq 10^5$，获得奖项的人的编号 $\lt 2 \times 10^9$。

输入数据保证第二行任意两个数不同，第三行任意两个数不同。

## 样例 #1

### 输入

```
4 3
2 15 6 8
8 9 2
```

### 输出

```
2 8```

# AI分析结果



### 唯一算法分类
**二分**

---

### 算法分析与结论
#### 核心思路
1. **排序预处理**：对特殊贡献奖数组排序，保持科技创新奖数组原始顺序（输出顺序要求）
2. **二分查找**：对每个科技创新奖元素，在排序后的特殊贡献奖数组中二分查找是否存在
3. **边界处理**：通过调整搜索区间保证不漏解，正确处理等于/大于/小于三种情况

#### 难点对比
| 题解对比点       | 基础二分实现                                   | STL binary_search 实现               | 双指针归并法                         |
|------------------|-----------------------------------------------|---------------------------------------|--------------------------------------|
| **时间复杂度**   | O(n log m)                                    | O(n log m)                            | O(n + m) + 两次排序代价              |
| **空间复杂度**   | O(1)                                         | O(1)                                 | O(n) 结构体存储原始顺序               |
| **实现难度**     | 需手动处理区间收缩和边界条件                  | 极简，但隐藏实现细节                  | 需两次排序和结构体封装               |
| **可读性**       | 高（显式展示二分过程）                        | 极高（一行代码完成查找）             | 中（需理解双指针逻辑）               |
| **适用场景**     | 教学场景（理解二分细节）                      | 快速编码场景                          | 特殊顺序要求场景                     |

#### 二分关键步骤演示（像素动画设计）
```javascript
// 伪代码演示核心二分过程（复古像素风格）
function binarySearchVisual(arr, target) {
    let left = 0, right = arr.length - 1;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        // 高亮当前 mid 元素（黄色像素块）
        highlightBlock(mid, 'yellow'); 
        playSound('beep'); // 8-bit 音效
        
        if (arr[mid] === target) {
            // 命中特效（绿色闪烁 + 上扬音效）
            blinkBlock(mid, 'green');
            playSound('success');
            return mid;
        } else if (arr[mid] < target) {
            // 右移区间（红色箭头动画）
            animateArrow(left, mid + 1);
            left = mid + 1;
        } else {
            // 左移区间（蓝色箭头动画）
            animateArrow(mid - 1, right);
            right = mid - 1;
        }
    }
    // 未找到（灰色像素 + 低沉音效）
    playSound('fail');
    return -1;
}
```

---

### 高星题解推荐（≥4★）
1. **Christopher_Yan（5★）**  
   - 亮点：同时给出 map 和二分两种解法，代码清晰，注释明确  
   - 核心代码片段：  
     ```cpp
     while (l <= r) {
         int mid = (l + r) >> 1;
         if (b[mid] == a[x]) return 1;
         if (b[mid] > a[x]) r = mid - 1;
         else l = mid + 1;
     }
     ```

2. **Starlight237（4★）**  
   - 亮点：使用 STL 的 binary_search 简化代码，适合快速解题  
   - 核心代码片段：  
     ```cpp
     if (binary_search(b+1, b+m+1, a[i])) 
         cout << a[i] << ' ';
     ```

3. **引领天下（4★）**  
   - 亮点：双指针归并思路，避免二分，时间复杂度更低  
   - 核心代码片段：  
     ```cpp
     while (i < n && j < m) {
         if (a[i] == b[j]) { /* 记录结果 */ }
         else if (a[i] < b[j]) i++;
         else j++;
     }
     ```

---

### 最优技巧提炼
1. **区间收缩准则**：当 `arr[mid] < target` 时，`left = mid + 1`（排除左半区）
2. **循环终止条件**：`while (left <= right)` 保证最后一步检查 mid 元素
3. **位运算优化**：用 `(left + right) >> 1` 代替除法，避免溢出
4. **STL 黑盒技巧**：直接调用 `binary_search` 但需确保数组已排序

---

### 同类型题目推荐
1. **P2249 【深基13.例1】查找**（二分查找首个等于目标的位置）
2. **P1102 A-B 数对**（转化为查找 B = A - C）
3. **P2678 跳石头**（二分答案经典题）

---

### 可视化实现要点（复古风格）
1. **像素画布**：用 16x16 像素块表示数组元素，色板限定 8 种颜色
2. **动画效果**：
   - **搜索区间**：红色/蓝色边框高亮当前 left-right 范围
   - **命中特效**：目标块绿色闪烁 + 金币音效
   - **区间收缩**：箭头从 mid 飞向新 left/right
3. **音效设计**：
   - `beep.wav`：每次计算 mid 时的 8-bit 滴答声
   - `success.wav`：找到目标时类似马里奥吃金币的音效
   - `fail.wav`：未找到时的低沉蜂鸣

---

### 教学代码（基础二分实现）
```cpp
#include <algorithm>
using namespace std;

int main() {
    int n, m, a[100010], b[100010];
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < m; ++i) scanf("%d", &b[i]);
    
    sort(b, b + m); // 关键：排序特殊贡献奖数组
    
    for (int i = 0; i < n; ++i) {
        int left = 0, right = m - 1;
        bool found = false;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (b[mid] == a[i]) { found = true; break; }
            if (b[mid] < a[i]) left = mid + 1;
            else right = mid - 1;
        }
        if (found) printf("%d ", a[i]);
    }
    return 0;
}
```

---
处理用时：89.24秒