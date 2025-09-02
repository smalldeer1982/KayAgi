# 题目信息

# Moscow Gorillas

## 题目描述

In winter, the inhabitants of the Moscow Zoo are very bored, in particular, it concerns gorillas. You decided to entertain them and brought a permutation $ p $ of length $ n $ to the zoo.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ occurs twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

The gorillas had their own permutation $ q $ of length $ n $ . They suggested that you count the number of pairs of integers $ l, r $ ( $ 1 \le l \le r \le n $ ) such that $ \operatorname{MEX}([p_l, p_{l+1}, \ldots, p_r])=\operatorname{MEX}([q_l, q_{l+1}, \ldots, q_r]) $ .

The $ \operatorname{MEX} $ of the sequence is the minimum integer positive number missing from this sequence. For example, $ \operatorname{MEX}([1, 3]) = 2 $ , $ \operatorname{MEX}([5]) = 1 $ , $ \operatorname{MEX}([3, 1, 2, 6]) = 4 $ .

You do not want to risk your health, so you will not dare to refuse the gorillas.

## 说明/提示

In the first example, two segments are correct – $ [1, 3] $ with $ \operatorname{MEX} $ equal to $ 4 $ in both arrays and $ [3, 3] $ with $ \operatorname{MEX} $ equal to $ 1 $ in both of arrays.

In the second example, for example, the segment $ [1, 4] $ is correct, and the segment $ [6, 7] $ isn't correct, because $ \operatorname{MEX}(5, 4) \neq \operatorname{MEX}(1, 4) $ .

## 样例 #1

### 输入

```
3
1 3 2
2 1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
7
7 3 6 2 1 5 4
6 7 2 5 3 1 4```

### 输出

```
16```

## 样例 #3

### 输入

```
6
1 2 3 4 5 6
6 5 4 3 2 1```

### 输出

```
11```

# AI分析结果



## 唯一算法分类  
**枚举与区间维护**

---

## 综合分析与结论  
### 核心思路  
1. **枚举 MEX 值**：对每个可能的 MEX 值（1 到 n+1），计算满足条件的区间数量。  
2. **区间维护**：  
   - 对于 MEX = m，区间必须包含 1 到 m-1 的所有数，且在两个排列中都不包含 m 的位置。  
   - 维护当前必须包含的区间范围 `[l, r]`，表示 1 到 m-1 的数在两个排列中的最左和最右位置的合并范围。  
3. **分情况统计**：  
   - **MEX=1**：区间不能包含两个排列中的 1 的位置，分三段计算贡献。  
   - **MEX≥2**：根据当前 m 的位置是否与 `[l, r]` 相交，分三种情况计算合法区间数，并更新 `[l, r]`。  
   - **MEX=n+1**：仅一种情况（全选区间），直接加 1。  

### 难点与解决  
- **快速判断合法区间范围**：通过维护 `[l, r]` 避免重复计算，确保每次判断时间复杂度为 O(1)。  
- **分情况讨论**：根据 m 的位置在 `[l, r]` 的左侧、右侧或跨段，分别计算贡献。  

### 可视化设计  
1. **区间维护动画**：  
   - 用颜色标记 `[l, r]` 的扩展过程，动态展示每次更新后的区间范围。  
   - 高亮当前处理的 m 的位置，区分其在 `[l, r]` 内外的状态。  
2. **贡献计算演示**：  
   - 用不同颜色标注三种分情况（左、右、跨段），显示合法区间的左右端点范围。  
3. **复古像素风格**：  
   - 使用 8-bit 风格网格表示数组，每个数用像素方块表示。  
   - 音效触发：合法区间统计时播放“得分”音效，更新 `[l, r]` 时播放“移动”音效。  

---

## 题解清单 (≥4星)  
### 1. TernaryTree（5星）  
- **关键亮点**：  
  - 高效维护 `[l, r]` 并分三种情况统计贡献。  
  - 代码简洁，直接处理边界条件。  
- **核心代码**：  
  ```cpp
  for (int m = 2; m <= n; m++) {
      k1 = s[m], k2 = t[m];
      if (k1 > k2) swap(k1, k2);
      if (l <= k1 && k1 <= r || l <= k2 && k2 <= r) {
          l = min(l, k1);
          r = max(r, k2);
          continue;
      }
      // 分情况计算贡献
      l = min(l, k1);
      r = max(r, k2);
  }
  ```

### 2. lizhous（4星）  
- **关键亮点**：  
  - 通过 `get` 和 `geter` 函数清晰计算区间数。  
  - 代码模块化，易于理解。  

### 3. 寻逍遥2006（4星）  
- **关键亮点**：  
  - 简化了分情况讨论的逻辑。  
  - 代码简短，直接合并位置处理。  

---

## 最优思路提炼  
1. **维护区间范围**：逐步扩展 `[l, r]` 确保包含所有必要元素。  
2. **分情况统计**：根据 m 的位置与当前 `[l, r]` 的关系，快速计算合法区间数。  
3. **预处理位置映射**：通过数组 `s` 和 `t` 快速查询每个数的位置。  

---

## 同类题目推荐  
1. **CF1770E**：统计满足条件的子数组数量（维护区间性质）。  
2. **Luogu P1972**：区间去重计数（分块维护）。  
3. **Luogu P5490**：扫描线求矩形面积并（区间合并）。  

---

## 个人心得摘录  
> "考场上脑瘫了交了 N 发。显然考虑两个排列中满足 MEX=x 的区间有哪些。" —— 作者：Feyn  
**总结**：调试时需注意边界条件，避免重复提交。  

---

## 可视化与算法演示  
### 动画方案  
1. **初始化**：  
   - 绘制两个排列的像素网格，标记每个数的位置。  
2. **维护 `[l, r]`**：  
   - 每次更新时用绿色方块标记 `l` 和 `r`。  
3. **处理 m 的位置**：  
   - 红色方块表示当前 m 的位置，若在 `[l, r]` 内则闪烁提示。  
4. **贡献统计**：  
   - 合法区间用蓝色边框标注，统计时显示贡献值。  

### 复古风格设计  
- **颜色方案**：  
  - 合法区间：蓝色（#00FFFF）。  
  - 当前 m 位置：红色（#FF0000）。  
  - 背景音乐：8-bit 循环音轨。  
- **交互功能**：  
  - 步进控制：按空格单步执行。  
  - 自动播放：AI 模式展示算法流程。  

---

## 代码核心实现  
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;

int n, s[N], t[N];
ll ans;

int main() {
    cin >> n;
    for (int i = 1, x; i <= n; i++) cin >> x, s[x] = i;
    for (int i = 1, x; i <= n; i++) cin >> x, t[x] = i;
    
    // 处理 MEX=1
    int k1 = s[1], k2 = t[1];
    if (k1 > k2) swap(k1, k2);
    ans += (k1-1)*k1/2 + (n-k2)*(n-k2+1)/2;
    if (k1 < k2) ans += (k2-k1-1)*(k2-k1)/2;

    // 处理 MEX=2~n
    int l = k1, r = k2;
    for (int m = 2; m <= n; m++) {
        int a = s[m], b = t[m];
        if (a > b) swap(a, b);
        if ((a >= l && a <= r) || (b >= l && b <= r)) {
            l = min(l, a);
            r = max(r, b);
            continue;
        }
        if (b < l) ans += (ll)(l - b) * (n - r + 1);
        else if (a > r) ans += (ll)l * (a - r);
        else if (a < l && b > r) ans += (ll)(l - a) * (b - r);
        l = min(l, a);
        r = max(r, b);
    }
    cout << ans + 1; // 加上 MEX=n+1
    return 0;
}
```

---
处理用时：261.91秒