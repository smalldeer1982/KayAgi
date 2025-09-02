# 题目信息

# Bouquet (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version, the flowers are specified by enumeration.

A girl is preparing for her birthday and wants to buy the most beautiful bouquet. There are a total of $ n $ flowers in the store, each of which is characterized by the number of petals, and a flower with $ k $ petals costs $ k $ coins. The girl has decided that the difference in the number of petals between any two flowers she will use in her bouquet should not exceed one. At the same time, the girl wants to assemble a bouquet with the maximum possible number of petals. Unfortunately, she only has $ m $ coins, and she cannot spend more. What is the maximum total number of petals she can assemble in the bouquet?

## 说明/提示

In the first test case, you can assemble a bouquet with $ (1, 1, 2, 2), (2, 2, 3), (1, 1), (2, 2) $ . The maximum over all valid bouquets not greater than $ 10 $ is $ 7 $ for $ (2, 2, 3) $ . In the third test case, you can assemble a bouquet with only one flower of any type, so the answer is $ 610 $ . In the fourth test case, you can assemble a bouquet with $ (4, 4, 5) $ , which gives you $ 13 $ petals, and it is the maximum amount of petals that the girl can buy.

## 样例 #1

### 输入

```
5
5 10
1 1 2 2 3
8 20
4 2 7 5 6 1 1 1
8 100000
239 30 610 122 24 40 8 2
11 13
2 4 11 1 1 2 3 5 4 3 2
8 1033
206 206 206 207 207 207 207 1000```

### 输出

```
7
13
610
13
1033```

# AI分析结果



### 算法分类
**滑动窗口**

---

### 题解思路与核心难点

#### 核心算法流程
1. **排序预处理**：所有花朵按花瓣数升序排列，确保窗口内极差可控。
2. **双指针维护窗口**：左指针 `l` 和右指针 `r` 初始指向起点，右指针逐步右移尝试扩大窗口。
3. **动态调整窗口**：当窗口内极差超过 1 或总花费超过 `m` 时，左指针右移缩小窗口。
4. **实时更新最大值**：每次窗口合法时，记录当前窗口总花瓣数并更新全局最大值。

#### 解决难点
- **极差约束**：通过排序将问题转化为相邻元素的极差控制，避免全局极差计算。
- **贪心策略**：滑动窗口确保在满足约束下尽可能包含更多高价值花朵。
- **时间复杂度优化**：滑动窗口将暴力枚举的 O(n²) 优化为 O(n)。

---

### 题解评分（≥4星）

1. **NEKO_Daze（5星）**  
   **亮点**：代码简洁高效，直接维护窗口和 `x` 变量，用 `a[i]-a[j]>1` 判断极差。  
   **代码片段**：  
   ```cpp
   while (i < n) {
       i++; x += a[i];
       while (x > m || a[i] - a[j] > 1) x -= a[j++];
       ans = max(ans, x);
   }
   ```

2. **vorDeal（4星）**  
   **亮点**：通过 `a[r-1] > a[l] + 1` 判断极差，代码逻辑清晰。  
   **代码片段**：  
   ```cpp
   while (r <= n) {
       if (a[r-1] > a[l] + 1 || sum > m) sum -= a[l++];
       else res = max(res, sum), sum += a[r++];
   }
   ```

3. **nightwatch.ryan（4星）**  
   **亮点**：变量命名简练，`cur` 维护当前窗口和，`maxn` 记录最大值。  
   **代码片段**：  
   ```cpp
   for (int l=1, r=1; r<=n; r++) {
       cur += a[r];
       while (a[r] - a[l] > 1 || cur > m) cur -= a[l++];
       if (cur <= m) maxn = max(maxn, cur);
   }
   ```

---

### 最优思路提炼
**核心技巧**：  
1. **排序后双指针**：将极差约束转化为相邻元素的差不超过 1。
2. **动态窗口调整**：右指针贪心扩展，左指针及时收缩。
3. **实时和计算**：直接在指针移动时累加/减去元素值，避免前缀和数组。

**思维突破点**：  
- 极差约束的连续性问题可转化为排序后的滑动窗口。
- 无需单独处理只选 1 种花的情况，窗口自动覆盖最优解。

---

### 同类型题推荐
1. **LeetCode 209. 长度最小的子数组**  
   （滑动窗口求满足和的最小长度）
2. **洛谷 P1638 逛画展**  
   （滑动窗口求覆盖所有类型的最小区间）
3. **LeetCode 1004. 最大连续1的个数 III**  
   （允许有限次操作，求最长连续区间）

---

### 可视化设计

#### 算法演示动画
1. **像素风格设计**：  
   - **颜色方案**：花朵用绿色像素块，左指针红色，右指针蓝色，当前窗口黄色高亮。
   - **网格布局**：花朵按排序后顺序排列为一行，下方显示当前和 `sum` 和最大值 `max`。

2. **关键动画步骤**：  
   - **右指针移动**：蓝色指针右移，黄色区域扩展，播放“滴”声效。
   - **左指针收缩**：红色指针右移，黄色区域缩小，播放“咔”声效。
   - **更新最大值**：最大值更新时，屏幕上方闪烁金色数字。

3. **交互控制**：  
   - **速度调节**：滑块控制动画速度（0.5x~3x）。
   - **单步执行**：按钮逐帧查看指针移动和状态更新。

#### 复古游戏化示例
```javascript
// 伪代码示例：Canvas 绘制滑动窗口
function drawFlowers(flowers) {
    ctx.fillStyle = '#2C3E50'; // 背景色
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    flowers.forEach((f, i) => {
        ctx.fillStyle = (i >= l && i <= r) ? '#F1C40F' : '#27AE60'; // 窗口内黄色，外绿色
        ctx.fillRect(i * 10, 100 - f * 5, 8, f * 5); // 绘制花朵高度
    });
    // 绘制指针
    ctx.fillStyle = '#E74C3C'; // 左指针红色
    ctx.fillRect(l * 10, 110, 8, 10);
    ctx.fillStyle = '#3498DB'; // 右指针蓝色
    ctx.fillRect(r * 10, 110, 8, 10);
}
```

---

### 个人心得摘录
- **调试教训**：多测不清空队列导致 WA（如 IGA_Indigo 的队列未清空）。
- **贪心优化**：枚举相邻两种花时，按价格从低到高购买更优（zjj2024 的代码）。

---

### 核心代码实现（NEKO_Daze 版本）
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[200001];
int main(){
    int t; cin >> t;
    while(t--){
        ll n, m; cin >> n >> m;
        for(int i=1; i<=n; i++) cin >> a[i];
        sort(a+1, a+n+1);
        ll ans=0, i=0, j=1, x=0;
        while(i < n){
            i++;
            x += a[i];
            while(x > m || a[i] - a[j] > 1)
                x -= a[j], j++;
            ans = max(ans, x);
        }
        cout << ans << endl;
    }
}
```

---
处理用时：70.89秒