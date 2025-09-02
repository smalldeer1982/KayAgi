# 题目信息

# Line

## 题目描述

There are $ n $ people in a horizontal line, each looking either to the left or the right. Each person counts the number of people in the direction they are looking. The value of the line is the sum of each person's count.

For example, in the arrangement LRRLL, where L stands for a person looking left and R stands for a person looking right, the counts for each person are $ [0, 3, 2, 3, 4] $ , and the value is $ 0+3+2+3+4=12 $ .

You are given the initial arrangement of people in the line. For each $ k $ from $ 1 $ to $ n $ , determine the maximum value of the line if you can change the direction of at most $ k $ people.

## 说明/提示

In the first test case:

- $ k=1 $ : change the direction of $ 1 $ person to make the line RLR. The total value is $ 2+1+0=3 $ .
- $ k=2 $ : change the direction of $ 2 $ people to make the line RLL. The total value is $ 2+1+2=5 $ .
- $ k=3 $ : change the direction of $ 2 $ people to make the line RLL. The total value is $ 2+1+2=5 $ . Note that you have to change the direction of at most $ k $ people.

In the second test case, it is optimal to only change the direction of the first person for all $ k $ from $ 1 $ to $ 5 $ (that is, make the line RRRLL).

## 样例 #1

### 输入

```
6
3
LLR
5
LRRLL
1
L
12
LRRRLLLRLLRL
10
LLLLLRRRRR
9
LRLRLRLRL```

### 输出

```
3 5 5 
16 16 16 16 16 
0 
86 95 98 101 102 102 102 102 102 102 102 102 
29 38 45 52 57 62 65 68 69 70 
44 50 54 56 56 56 56 56 56```

# AI分析结果



### 综合分析与结论

**题目核心**：通过贪心策略选择改变方向能带来最大增益的人，以求得每个 k 的最大总和。  
**贪心关键**：改变方向后的增益与位置有关，越靠近两端的增益越大。  
**难点**：如何高效选择最优的修改顺序，并正确处理所有 k 的查询。

### 题解评分（≥4星）

1. **ScottSuperb（5星）**  
   - **亮点**：双指针从两端向中间处理，O(n)时间复杂度，无需排序。  
   - **核心代码**：  
     ```cpp
     for (dis = 0; dis < n2; ++dis) {
         if (s[dis] == 'L') ans += n - dis - 1 - dis, ++cnt;
         if (s[n - dis - 1] == 'R') ans += n - dis - 1 - dis, ++cnt;
     }
     ```
   - **优势**：直接按位置处理，高效且节省空间。

2. **lihanwen12（4星）**  
   - **亮点**：显式计算每个位置的增益并排序，思路清晰。  
   - **核心代码**：  
     ```cpp
     sort(a + 1, a + n + 1, cmp);
     for (int i = 1; i <= n; ++i) ans += a[i].up;
     ```
   - **优势**：代码易懂，适合理解贪心的基本思路。

3. **Epi4any（4星）**  
   - **亮点**：处理负数增益，代码结构简洁。  
   - **核心代码**：  
     ```cpp
     if (c == 'L') ans += l, p[i] = max(r - l, 0);
     else ans += r, p[i] = max(l - r, 0);
     ```
   - **优势**：正确处理无效修改，避免错误累加。

### 最优思路提炼

1. **贪心策略**：每个位置的增益为 `(n-1-2*i)`（左改右）或 `(2*i-n+1)`（右改左），优先选择增益最大的位置。  
2. **实现技巧**：  
   - 从两端向中间遍历，按距离处理（Scott解法）。  
   - 显式排序后取前 k 大（lihanwen解法）。  

### 同类型题目

1. **P1090 合并果子**：每次选最小的两个数合并，贪心选择最小代价。  
2. **P1223 排队接水**：按接水时间排序，贪心求最小平均等待时间。  
3. **P1803 线段覆盖**：按右端点排序，选择不重叠的最大线段数。

### 个人心得摘录

- **ScottSuperb**：巧妙利用位置与增益的关系，避免排序，极大优化时间复杂度。  
- **lihanwen12**：通过显式排序简化问题，适合快速验证贪心正确性。  
- **Epi4any**：强调开 `long long` 的重要性，避免溢出问题。

---

### 可视化与算法演示

**动画设计**：  
1. **像素风格网格**：用不同颜色表示方向（L-红，R-蓝），改变方向后颜色切换。  
2. **增益高亮**：当前处理的左右端点显示为黄色，增益数值动态显示。  
3. **音效**：  
   - 改变方向时播放上升音调（增益正）或下降音调（增益负）。  
   - 背景音乐为 8-bit 循环风格。  
4. **自动演示**：按 `dis` 顺序逐步处理左右端点，显示当前总和和剩余可修改次数。

**代码片段（JS伪代码）**：  
```javascript
// 初始化 Canvas
const grid = new PixelGrid(n);
// 处理每个 dis
for (let dis = 0; dis < n/2; dis++) {
    const left = dis, right = n - dis - 1;
    grid.highlight(left, 'yellow');
    grid.highlight(right, 'yellow');
    // 计算增益并更新动画
    updateSum(leftGain, rightGain);
    playSound(leftGain > 0 ? 'up' : 'down');
}
```

---

### 题解核心代码

**ScottSuperb 的完整代码**  
```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    int t, n, n2, dis, cnt;
    while (t--) {
        n = read();
        string s;
        ll ans = 0;
        for (int i = 0; i < n; ++i)
            s += getchar(), ans += s[i] == 'L' ? i : n - i - 1;
        for (cnt = dis = 0, n2 = n >> 1; dis < n2; ++dis) {
            if (s[dis] == 'L') ans += n - dis - 1 - dis, ++cnt, write(ans);
            if (s[n - dis - 1] == 'R') ans += n - dis - 1 - dis, ++cnt, write(ans);
        }
        while (n >= ++cnt) write(ans);
        putchar('\n');
    }
    return 0;
}
```

**核心贪心逻辑**：从两端开始，按距离处理每个位置，直接累加最大增益。

---
处理用时：235.96秒