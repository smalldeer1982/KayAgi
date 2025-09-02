# 题目信息

# [ICPC 2020 Shanghai R] Walker

## 题目描述

As a world-famous traveler, Prof. Pang's research interest is to travel as many places as possible in his life.

We have a segment $[0, n]$. There are two travelers on it. The first one is on position $p_1$ with velocity $v_1$ (which means s/he can walk $v_1$ unit on the segment per second). The second one is on position $p_2$ with velocity $v_2$.

From their respective beginning points, travelers can walk on the segment. They cannot walk outside the segment. Whenever they want to change their direction, they can turn around immediately.

Please help Prof. Pang to calculate the minimum  possible time by which every position of the segment is passed by at least one traveler.

## 样例 #1

### 输入

```
2
10000.0 1.0 0.001 9999.0 0.001
4306.063 4079.874 0.607 1033.423 0.847```

### 输出

```
5001000.0000000000
3827.8370013755```

# AI分析结果



**唯一算法分类**  
二分

---

### **题解思路、算法要点与解决难点**  
**核心思路**：问题可分解为三种情况：  
1. 单人覆盖全程  
2. 两人相向而行覆盖端点  
3. 二分中点分治覆盖区间  

**二分算法关键点**：  
1. **搜索区间**：初始区间为两人位置 `[p1, p2]`（需先交换保证 p1≤p2）  
2. **收缩条件**：计算中点 `mid`，比较两人覆盖各自区间的时间 `t1` 和 `t2`  
   - 若 `t1 < t2`：向右收缩（`l = mid`）  
   - 否则：向左收缩（`r = mid`）  
3. **精度控制**：采用 `1e-7` 或固定循环次数（如 100 次）避免死循环  
4. **答案更新**：每次二分时更新全局最小时间  

**解决难点**：  
- 需要同时考虑两人行走路径的最优性（先走边界还是先走中间）  
- 二分过程中需动态维护最小时间，而非单纯判断可行性  

---

### **题解评分 (≥4星)**  
1. **wylnh（4.5星）**  
   - 思路清晰，完整覆盖三种情况  
   - 代码简洁，交换处理保证 p1≤p2  
   - 使用 `eps=1e-7` 控制精度  

2. **佬头（4星）**  
   - 详细说明二分单调性原理  
   - 采用固定循环次数（1000次）避免精度问题  
   - 代码中 `check()` 函数明确时间比较逻辑  

3. **chen_zhe（4星）**  
   - 转载官方题解，思路权威  
   - 明确提到“二分时间”的替代方案  
   - 简练概括所有可能情况  

---

### **最优思路或技巧提炼**  
1. **区间交换优化**：若 `p1 > p2`，交换两人参数保证从左到右有序  
2. **动态更新答案**：在二分循环内部持续更新 `ans = min(ans, max(t1, t2))`  
3. **路径计算优化**：  
   - 单人覆盖时间公式：`(min(pos, n-pos) + n) / v`  
   - 分治时路径计算：`t1 = (mid + min(mid-p1, p1)) / v1`（先走短边）  
4. **精度处理**：避免浮点误差，统一使用 `1e-7` 或固定二分次数  

---

### **同类型题与算法套路**  
**通用二分套路**：  
1. **二分答案**：当问题可转化为“判断时间 t 是否可行”时，二分 t 值  
2. **区间分治**：在有序区间上二分分割点，比较两侧属性  

**相似题目**：  
1. 洛谷 P1873（砍树，二分最大高度）  
2. 洛谷 P2678（跳石头，二分最小距离）  
3. 洛谷 P1182（数列分段，二分最大段和）  

---

### **个人心得摘录**  
- **精度陷阱**：题目要求 `1e-6` 精度，但实际需设置 `1e-7`（因浮点运算累积误差）  
- **调试技巧**：交换两人位置后，需同步交换速度参数，避免逻辑错误  
- **思维误区**：曾误以为两人必须同步到达中点，实际只需覆盖区间即可  

---

### **可视化与算法演示**  
**动画方案**：  
1. **初始化**：线段 `[0, n]`，两人初始位置 p1、p2 用不同颜色标记  
2. **二分过程**：  
   - **Step 1**：显示当前区间 `[l, r]`，计算中点 `mid`  
   - **Step 2**：动态绘制两人路径（红色箭头表示行走方向）  
   - **Step 3**：比较 `t1` 和 `t2`，高亮较长时间，收缩区间  
   - **Step 4**：更新全局最小时间 `ans`，显示于面板  
3. **复古风格**：  
   - **像素网格**：用 8-bit 风格绘制线段和移动轨迹  
   - **音效触发**：每次更新 mid 时播放“哔”声，找到更优解时播放“叮”声  
   - **自动模式**：AI 按最优路径自动执行，速度可调  

**关键代码片段（JS）**：  
```javascript
function visualizeBinarySearch(p1, p2, n) {
  let l = p1, r = p2, ans = Infinity;
  while (r - l > 1e-7) {
    const mid = (l + r) / 2;
    const t1 = calculateTime(p1, mid, v1);
    const t2 = calculateTime(p2, n - mid, v2);
    ans = Math.min(ans, Math.max(t1, t2));
    if (t1 < t2) l = mid;
    else r = mid;
    drawStep(l, r, mid, t1, t2); // 更新画布
  }
}
```

---

**推荐代码实现**  
```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-7;

int main() {
    int T; cin >> T;
    while (T--) {
        double n, p1, v1, p2, v2;
        cin >> n >> p1 >> v1 >> p2 >> v2;
        if (p1 > p2) swap(p1, p2), swap(v1, v2);
        
        double ans = min( (min(p1, n-p1)+n)/v1, (min(p2, n-p2)+n)/v2 );
        ans = min(ans, max( (n-p1)/v1, p2/v2 ));
        
        double l = p1, r = p2;
        while (r - l > eps) {
            double mid = (l + r) / 2;
            double t1 = (mid + min(mid-p1, p1)) / v1;
            double t2 = (n-mid + min(n-p2, p2-mid)) / v2;
            ans = min(ans, max(t1, t2));
            t1 < t2 ? l = mid : r = mid;
        }
        printf("%.10f\n", ans);
    }
    return 0;
}
```

---
处理用时：79.43秒