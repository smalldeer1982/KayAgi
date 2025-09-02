# 题目信息

# Electrification

## 题目描述

At first, there was a legend related to the name of the problem, but now it's just a formal statement.

You are given $ n $ points $ a_1, a_2, \dots, a_n $ on the $ OX $ axis. Now you are asked to find such an integer point $ x $ on $ OX $ axis that $ f_k(x) $ is minimal possible.

The function $ f_k(x) $ can be described in the following way:

- form a list of distances $ d_1, d_2, \dots, d_n $ where $ d_i = |a_i - x| $ (distance between $ a_i $ and $ x $ );
- sort list $ d $ in non-descending order;
- take $ d_{k + 1} $ as a result.

If there are multiple optimal answers you can print any of them.

## 样例 #1

### 输入

```
3
3 2
1 2 5
2 1
1 1000000000
1 0
4
```

### 输出

```
3
500000000
4
```

# AI分析结果



## 唯一算法分类
**几何**

---

## 综合分析与结论

### 核心思路与数学推导
所有题解均基于关键性质：**使第 $k+1$ 小距离最小的 $x$，一定对应排序后数组中某个长度为 $k+1$ 的连续区间**。  
- **数学证明**：若存在非连续区间，其最大距离必然大于等于连续区间的最大距离。因此最优解必为连续区间的中点。  
- **关键公式**：对连续区间 $[a_i, a_{i+k}]$，取中点 $x = a_i + \frac{a_{i+k}-a_i}{2}$，此时第 $k+1$ 小距离为 $\frac{a_{i+k}-a_i}{2}$。需找到最小的 $a_{i+k}-a_i$。

### 算法对比与优化
- **O(n) 枚举法**：直接遍历所有连续 $k+1$ 长度的区间，计算长度并取最小值（最优解法）。  
- **O(n log V) 二分法**：二分可能的距离值，验证是否存在满足条件的区间。  
- **堆优化法**：维护最小堆存储区间长度，时间复杂度略高但正确性一致。

### 可视化设计
- **动画方案**：在数轴上动态绘制排序后的点，高亮当前遍历的连续区间 $[a_i, a_{i+k}]$，计算区间长度并标记中点。  
- **颜色标记**：红色高亮当前区间，绿色标记历史最小区间，蓝色显示中点位置。  
- **复古风格**：8位像素风格数轴，音效提示区间更新与答案确定。

---

## 题解清单（≥4星）

1. **wanghaoyu120104（5星）**  
   - **亮点**：O(n) 时间复杂度，代码简洁易懂，直接枚举连续区间。  
   - **关键代码**：  
     ```cpp
     for (int i=1; i<=n-k; i++) {
         if (mi > a[i+k] - a[i]) {
             mi = a[i+k] - a[i];
             ans = a[i] + mi/2;
         }
     }
     ```

2. **cosf（4星）**  
   - **亮点**：数学推导清晰，强调区间连续性与中点选择逻辑。  
   - **核心思想**：枚举每个点作为第 $k+1$ 远端点，取中点最小化距离。

3. **SamuelXuch（4星）**  
   - **亮点**：代码高效，无冗余操作，直接维护最小区间长度。  
   - **个人心得**：提到“最短区间中点即为最优解”，强化关键性质。

---

## 最优思路提炼
1. **连续区间性质**：最优解对应排序后的连续 $k+1$ 点区间。  
2. **中点取法**：取区间中点 $x$ 使得最大距离最小化。  
3. **滑动窗口遍历**：直接枚举所有可能的连续区间，取长度最小者。

---

## 同类型题与套路
- **常见套路**：排序后利用滑动窗口/双指针寻找极值，适用于一维几何极值问题。  
- **相似题目**：  
  - 洛谷 P1091（滑动窗口求极值）  
  - 洛谷 P2217（连续区间中位数优化）  
  - 洛谷 P1638（最小覆盖区间）

---

## 推荐题目
1. **P1091** 合唱队形（滑动窗口极值）  
2. **P2217** [HAOI2007] 分割矩阵（中位数优化）  
3. **P1638** 逛画展（最小覆盖窗口）

---

## 个人心得摘录
- **Leaper_lyc**：调试时发现区间长度判断错误，最终通过二分验证修正。  
- **rickyxrc**：初次尝试未注意排序，导致 WA，后加排序后 AC。  
- **米奇**：比赛时未想到连续区间性质，经提示后豁然开朗。

---

## 可视化与算法演示
### 核心数学过程
1. **初始化**：数轴上按升序排列所有点，高亮前 $k+1$ 个点。  
2. **滑动窗口**：逐个右移区间，计算长度 $\Delta = a_{i+k} - a_i$。  
3. **更新最优解**：若 $\Delta$ 更小，更新最小值并标记中点。  
4. **动态标记**：红色边框表示当前区间，绿色填充标记历史最优。

### 复古游戏化设计
- **像素风格**：16 色数轴，点用 8x8 像素方块表示。  
- **音效设计**：  
  - 区间滑动：8-bit “滴”声。  
  - 更新最优解：上扬音效。  
- **自动演示**：AI 模拟滑动过程，按步长 100ms 自动播放。

### 代码片段（Canvas 绘制）
```javascript
function drawInterval(ctx, a, i, k, minIdx) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // 绘制所有点
    a.forEach((x, idx) => {
        ctx.fillStyle = (idx >= i && idx <= i + k) ? '#FF0000' : '#0000FF';
        ctx.fillRect(x * scale, 50, 8, 8);
    });
    // 标记最优中点
    if (minIdx !== -1) {
        ctx.fillStyle = '#00FF00';
        ctx.fillRect((a[minIdx] + (a[minIdx + k] - a[minIdx])/2) * scale, 45, 8, 8);
    }
}
```

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int t, n, k, a[N];

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> a[i];
        sort(a + 1, a + n + 1); // 确保输入有序
        int min_len = INT_MAX, ans = 0;
        for (int i = 1; i <= n - k; i++) {
            int len = a[i + k] - a[i];
            if (len < min_len) {
                min_len = len;
                ans = a[i] + len / 2;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---
处理用时：108.70秒