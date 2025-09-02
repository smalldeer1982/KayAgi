# 题目信息

# [ABC361C] Make Them Narrow

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc361/tasks/abc361_c

長さ $ N $ の数列 $ A $ が与えられます。  
 $ A $ のうち丁度 $ K $ 要素を自由に選んで消し、残った要素を順序を保って連結した数列を $ B $ とします。  
 ( $ B $ の最大値 ) $ - $ ( $ B $ の最小値 ) としてありうる最小値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ K\ <\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ 10^9 $
 
### Sample Explanation 1

$ A=(3,1,5,4,9) $ から丁度 $ 2 $ 要素を自由に選んで消すことを考えます。 - 例えば $ 2 $ 要素目の $ 1 $ 、 $ 5 $ 要素目の $ 9 $ を消すと、消した後の数列 $ B=(3,5,4) $ となります。 - このとき $ B $ の最大値は $ 5 $ 、最小値は $ 3 $ なので ( $ B $ の最大値 ) $ - $ ( $ B $ の最小値 ) $ =2 $ となり、これは達成可能な最小値です。

## 样例 #1

### 输入

```
5 2

3 1 5 4 9```

### 输出

```
2```

## 样例 #2

### 输入

```
6 5

1 1 1 1 1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
8 3

31 43 26 6 18 36 22 13```

### 输出

```
18```

# AI分析结果



**唯一算法分类**  
排序 + 滑动窗口

---

### **综合分析与结论**

**题目核心**  
给定数组删除 K 个元素后，求剩余元素极差的最小值。关键在于排序后连续区间的极差最优性。

**算法流程**  
1. **排序数组**：将原数组从小到大排序，使极差计算仅需首尾差值。  
2. **滑动窗口枚举**：枚举所有长度为 `N-K` 的连续子区间，计算极差取最小值。  
   - 窗口左端点 `i` 的范围：`0 ≤ i ≤ K`（左边删 i 个，右边删 `K-i` 个）  
   - 极差公式：`a[n-K+i] - a[i+1]`（排序后的数组下标从 1 开始）  

**时间复杂度**  
排序 `O(N log N)` + 窗口遍历 `O(N)`，总复杂度 `O(N log N)`。

**可视化设计**  
- **动画方案**：  
  1. 初始显示排序后的数组，高亮当前窗口（如红色框）。  
  2. 步进时窗口左移，动态更新极差值（显示在右侧面板）。  
  3. 最终高亮最优窗口，展示极差结果。  
- **复古像素风格**：用 8-bit 色块表示数组元素，极差数值用像素字体显示。  
- **音效**：窗口移动时播放“滴”声，找到最优解时播放胜利音效。

---

### **题解评分 (≥4星)**

1. **ganyu1（5星）**  
   - **亮点**：代码简洁，循环逻辑清晰，直接枚举左右删除数量。  
   - **代码片段**：  
     ```cpp
     for(int i=0; i<=k; i++)
         ans = min(ans, a[n-k+i] - a[1+i]);
     ```

2. **joe_zxq（4星）**  
   - **亮点**：左端点从 1 开始，更直观的窗口计算。  
   - **代码片段**：  
     ```cpp
     for(int i=1; i<=k+1; i++)
         ans = min(ans, a[i+n-k-1] - a[i]);
     ```

3. **DrAlfred（4星）**  
   - **亮点**：变量命名清晰，注释明确，适合教学。  
   - **代码片段**：  
     ```cpp
     for (int i=0; i<=k; i++)
         ans = min(ans, a[i+n-k] - a[i+1]);
     ```

---

### **最优思路提炼**

**关键贪心策略**  
排序后最优解必为某连续子数组的极差。通过枚举删除左右元素的数量，保留中间连续段，直接计算首尾差值。

**实现技巧**  
- 排序后窗口极差仅需首尾元素差，无需计算区间内最值。  
- 循环变量 `i` 控制左右删除数量，窗口长度固定为 `N-K`。

---

### **同类型题与算法套路**

**相似题目特征**  
- 涉及极差最小化或最大化。  
- 允许删除/保留特定数量元素。  
- 最优解常通过排序后处理连续区间。

**推荐题目**  
1. [洛谷 P1102 A-B数对](https://www.luogu.com.cn/problem/P1102)（排序后滑动窗口）  
2. [LeetCode 1984. 学生分数的最小差值](https://leetcode.cn/problems/minimum-difference-between-highest-and-lowest-of-k-scores/)  
3. [Codeforces 978B. File Name](https://codeforces.com/problemset/problem/978/B)（删除连续元素）

---

### **代码实现**

**核心代码（ganyu1版本）**  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n, k, a[N], ans = INT_MAX;

int main() {
    cin >> n >> k;
    for(int i=1; i<=n; i++) cin >> a[i];
    sort(a+1, a+n+1);
    for(int i=0; i<=k; i++)
        ans = min(ans, a[n-k+i] - a[1+i]);
    cout << ans;
    return 0;
}
```

---

### **可视化与复古动画示例（伪代码）**

```javascript
// 伪代码：Canvas绘制排序数组与滑动窗口
function drawArray(ctx, a, n, currentWindow) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    for (let i = 0; i < n; i++) {
        // 绘制8-bit色块
        ctx.fillStyle = (i >= currentWindow.start && i <= currentWindow.end) ? '#FF0000' : '#00FF00';
        ctx.fillRect(i * 30, 100 - a[i], 25, 25);
    }
    // 显示当前极差
    ctx.fillText(`极差: ${currentWindow.diff}`, 10, 150);
}

// 自动播放滑动窗口
let i = 0;
const animate = () => {
    if (i > k) return;
    const start = i + 1;
    const end = n - k + i;
    const diff = a[end] - a[start];
    drawArray(ctx, a, n, {start, end, diff});
    i++;
    requestAnimationFrame(animate);
};
animate();
```

**音效与交互**  
- 移动窗口时播放 `beep.wav`（8-bit音效）。  
- 最优解时播放 `win.wav`（胜利音效）。

---
处理用时：104.40秒