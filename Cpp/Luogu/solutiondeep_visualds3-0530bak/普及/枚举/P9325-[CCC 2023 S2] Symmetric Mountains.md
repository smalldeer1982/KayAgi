# 题目信息

# [CCC 2023 S2] Symmetric Mountains

## 题目描述

Rebecca is a tour guide and is trying to market the Rocky Mountains for her magazine. She recently took a beautiful picture consisting of $N$ mountains where the $i\text{-th}$ mountain from the left has a height $h_i$. She will crop this picture for her magazine, by possibly removing some mountains from the left side of the picture and possibly removing some mountains from the right side of the picture. That is, a crop consists of consecutive mountains starting from the $l\text{-th}$ to the $r\text{-th}$ mountain where $l \leq r$. To please her magazine readers, Rebecca will try to find the most symmetric crop.

We will measure the $asymmetric\ value$ of a crop as the sum of the absolute difference for every pair of mountains equidistant from the midpoint of the crop. To help understand that definition, note that the absolute value of $a$ number $v$, written as $|v|$, is the non-negative value of v: for example $\lvert -6 \rvert = 6$ and $|14| = 14$. The asymmetric value of a crop is the sum of all $|h_{l+i} - h_{r-i}|$ for $0 \leq i \leq \frac{r-l}{2}$. To put that formula in a different way, we pair up the mountains working from the outside in toward the centre, calculate the absolute difference in height of each of these pairs, and sum them up.

Because Rebecca does not know how wide the picture needs to be, for all possible crop lengths, find the asymmetric value of the most symmetric crop (the crop with the minimum asymmetric value).

## 说明/提示

Explanation of Output for Sample Input $1$:

We will show why the fifth value from the left is $2$.Let us try to compute all the asymmetric values of crops with length $5$.

The height of the mountains in the first crop is $[3, 1, 4, 1, 5]$. The asymmetric value of this crop is $|3 - 5| + |1 - 1| + |4 - 4| = 2$.

The height of the mountains in the second crop is $[1, 4, 1, 5, 9]$. The asymmetric value of this crop is $|1 - 9| + |4 - 5| + |1 - 1| = 9$.

The height of the mountains in the last crop is $[4, 1, 5, 9, 2]$. The asymmetric value of this crop is $|4 - 2| + |1 - 9| + |5 - 5| = 10$.

Hence, the most symmetric crop of length $5$ is $2$.

Explanation of Output for Sample Input $2$:

This sample satisfies the second subtask. Note that the only crop of length $4$ is $[1, 3, 5, 6]$ which has asymmetric value of $|1 - 6| + |3 - 5| = 7$.

**本题采用捆绑测试**：

- Subtask 1（5 points）：$1\leq N \leq 300$，$0\leq h_i \leq 10^5$。

- Subtask 2（5 points）：$1 \leq N \leq 5000$，$0 \leq h_i \leq 10^5$，保证山的高度从左到右单调不减。

- Subtask 3（5 points）：$1\leq N\leq 5000$，$0 \leq h_i \leq 10^5$。

## 样例 #1

### 输入

```
7
3 1 4 1 5 9 2```

### 输出

```
0 2 0 5 2 10 10```

## 样例 #2

### 输入

```
4
1 3 5 6```

### 输出

```
0 1 3 7```

# AI分析结果



## **唯一算法分类**
**区间动态规划（区间DP）**

---

## **综合分析与结论**
### **核心思路与难点**
题目要求所有长度子区间的最小对称值。各题解主要围绕 **O(n²) 优化**展开，核心思路分为两类：
1. **区间DP**：预处理每个区间的对称值，基于更小区间的结果递推。
2. **中心扩展法**：枚举中心点，向两侧扩展逐步计算不同长度的对称值。

**关键难点**在于避免重复计算对称差值的和。暴力法的 O(n³) 复杂度无法通过，需通过递推或状态复用优化至 O(n²)。

---

## **题解清单（≥4星）**
### **1. ZepX_D 的题解（⭐⭐⭐⭐⭐）**
- **亮点**：中心扩展法，代码简洁高效，实际运行快。
- **思路**：枚举奇偶长度的中心点，向两侧扩展并累加差值，直接更新对应长度的最小值。
- **代码片段**：
  ```cpp
  for (int i = 1; i <= n; i++) {
      s = 0, l = r = i;
      while(l && r <= n) { // 奇数长度扩展
          ans[r-l+1] = min(ans[r-l+1], s);
          l--, r++, s += abs(h[r]-h[l]);
      }
      s = abs(h[i+1]-h[i]), l = i, r = i+1;
      while(l && r <= n) { // 偶数长度扩展
          ans[r-l+1] = min(ans[r-l+1], s);
          l--, r++, s += abs(h[r]-h[l]);
      }
  }
  ```

### **2. 玄学OIER荷蒻 的题解（⭐⭐⭐⭐）**
- **亮点**：标准区间DP实现，递推关系清晰。
- **思路**：定义 `dp[i][j]` 为区间 `[i,j]` 的对称值，递推式 `dp[i][j] = dp[i+1][j-1] + |h[i]-h[j]|`。
- **代码片段**：
  ```cpp
  for (int len = 2; len <= n; len++) {
      for (int i = 1; i <= n-len+1; i++) {
          int j = i + len - 1;
          dp[i][j] = dp[i+1][j-1] + abs(h[i] - h[j]);
          minn[len] = min(minn[len], dp[i][j]);
      }
  }
  ```

### **3. Loser_Syx 的题解（⭐⭐⭐⭐）**
- **亮点**：奇偶分治预处理，复用计算结果。
- **思路**：分奇偶长度维护两个数组，从右向左递推，复用相邻区间的计算结果。
- **代码片段**：
  ```cpp
  for(int i = 2; i <= n; i++) {
      if(i % 2 == 1) { // 奇数长度处理
          int l = n-i+1, r = n;
          while(r >= i) {
              a[r] = a[r-1] + abs(h[r] - h[l]);
              cz = min(cz, a[r]);
              --l; --r;
          }
      } else { // 偶数长度处理
          // 类似逻辑处理偶数
      }
  }
  ```

---

## **最优思路提炼**
### **关键思路**
- **中心扩展法**：以每个可能的中心点为起点，向两侧逐步扩展，计算对称差值并直接更新对应长度的最小值。此方法无需存储中间状态，时间复杂度严格 O(n²)，且实际常数较小。
- **递推公式**：对称值 `s` 的更新通过 `s += |h[l]-h[r]|` 实现，逐步覆盖所有可能的子区间。

### **优势**
- **空间优化**：无需二维数组，空间复杂度 O(n)。
- **高效遍历**：天然避免无效区间计算，实际运行速度优于区间DP。

---

## **同类型题推荐**
1. **最长回文子串（LeetCode 5）**：中心扩展法的经典应用。
2. **回文子串计数（LeetCode 647）**：类似对称性扩展思想。
3. **分割回文串 II（LeetCode 132）**：结合动态规划与对称性处理。

---

## **可视化与算法演示**
### **动画方案**
1. **中心扩展过程**：
   - **初始状态**：高亮当前中心点（红色方块）。
   - **扩展步骤**：每次向左右扩展一格，显示新增的对称对（如 `(l, r)`），并用绿色标记新增的差值 `|h[l]-h[r]|`。
   - **更新最小值**：右侧面板显示当前长度下的最小对称值，实时更新。

2. **复古像素风格设计**：
   - **颜色方案**：山脉用 8-bit 的蓝绿色渐变，当前操作元素用高对比色（红/黄）。
   - **音效**：每次扩展播放短促的“哔”声，找到更优解时播放上扬音效。

### **交互控制**
- **步进控制**：支持暂停/继续，调整动画速度（1x/2x/5x）。
- **模式切换**：可对比中心扩展法与区间DP的扩展路径差异。

---

## **核心代码实现（ZepX_D 题解）**
```cpp
#include <iostream>
#include <cstring>
using namespace std;

int h[5010], ans[5010];

int main() {
    ios::sync_with_stdio(0);
    int n; cin >> n;
    memset(ans, 0x3f, sizeof(ans));
    for (int i = 1; i <= n; i++) cin >> h[i];
    
    for (int i = 1; i <= n; i++) { // 处理奇数长度
        int s = 0, l = i, r = i;
        while (l >= 1 && r <= n) {
            ans[r - l + 1] = min(ans[r - l + 1], s);
            l--, r++;
            if (l >= 1 && r <= n) s += abs(h[l] - h[r]);
        }
    }
    
    for (int i = 1; i < n; i++) { // 处理偶数长度
        int s = abs(h[i] - h[i+1]), l = i, r = i+1;
        ans[2] = min(ans[2], s);
        while (l >= 1 && r <= n) {
            l--, r++;
            if (l >= 1 && r <= n) {
                s += abs(h[l] - h[r]);
                ans[r - l + 1] = min(ans[r - l + 1], s);
            }
        }
    }
    
    ans[1] = 0; // 长度为1时不对称值为0
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    return 0;
}
```

---
处理用时：102.81秒