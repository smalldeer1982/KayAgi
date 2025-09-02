# 题目信息

# Bowling Frame

## 题目描述

题面涉及到政治敏感内容，请在 Codeforces 查阅。

## 样例 #1

### 输入

```
4
1 2
3 2
3 3
12 0```

### 输出

```
2
2
3
4```

# AI分析结果



## 算法分类
**二分**

---

## 综合分析与结论
本题核心是求最大行数 $n$ 使得 $\frac{n(n+1)}{2} \leq w + b$。关键难点在于证明颜色分配不影响结果，只需总点数足够即可。各解法均围绕如何高效计算此 $n$。

### 二分过程分析
1. **搜索区间**：`left=1`，`right` 初始化为足够大的值（如 $2e5$）。
2. **条件判断**：计算 `mid*(mid+1)/2` 是否 ≤ 总点数 `w+b`。
3. **区间收缩**：若条件成立，尝试更大的 `n`（`left=mid+1`），否则缩小右边（`right=mid-1`）。
4. **终止条件**：`left > right` 时退出，最终 `ans = right`。

### 可视化设计
- **像素动画**：用网格表示区间，当前 `mid` 高亮为黄色，比较结果后更新区间为绿色（可行）或红色（不可行）。
- **音效**：收缩区间时播放“滴”声，找到答案时播放成功音效。
- **自动演示**：模拟二分步骤，每步暂停 500ms，配合音效增强交互。

---

## 题解评分（≥4星）
1. **queenbee（5星）**
   - **亮点**：数学公式直接计算，时间复杂度 $O(1)$，代码简洁。
   - **代码**：利用求根公式避免循环，适合大数据范围。
2. **Hughpig（4星）**
   - **亮点**：累加法思路清晰，代码易读，在小数据范围高效。
   - **注意**：当 $s$ 极大时可能超时，但本题数据范围适用。
3. **LittleDrinks（4星）**
   - **亮点**：与 Hughpig 类似，代码更精简，直接累加终止条件明确。

---

## 最优思路提炼
**关键结论**：颜色分配不影响最大行数，只需总点数足够。  
**数学公式**：$n = \lfloor \frac{\sqrt{8(w+b)+1} -1}{2} \rfloor$，时间复杂度最优。  
**二分实现**：预处理非必须，动态计算 `mid*(mid+1)/2` 更通用。

---

## 同类型题推荐
1. **P1873 砍树**（二分答案）
2. **P2440 木材加工**（二分答案）
3. **P1024 一元三次方程求解**（二分查根）

---

## 个人心得摘录
> “颜色分配看似复杂，但通过数学归纳法可证明其不影响结果。直接关注总点数即可突破思维瓶颈。” —— 沉石鱼惊旋  
> “当输入规模较小时，累加法的代码简洁性胜于一切。” —— Hughpig

---

## 核心代码实现（二分法）
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t;
    cin >> t;
    while(t--) {
        ll w, b;
        cin >> w >> b;
        ll s = w + b;
        ll left = 0, right = 2e5, ans = 0;
        while(left <= right) {
            ll mid = (left + right) / 2;
            if(mid * (mid + 1) / 2 <= s) {
                ans = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 可视化算法演示（二分）
```javascript
// 伪代码示例：Canvas 绘制二分过程
function drawBinaryStep(left, right, mid, result) {
    clearCanvas();
    drawGrid(left, right); // 绘制区间网格
    highlight(mid, result ? 'green' : 'red'); // 高亮 mid
    updateInterval(left, right); // 更新区间颜色
    playSound(result ? 'success' : 'click'); // 触发音效
}

// 自动演示逻辑
async function autoRun() {
    let left = 0, right = 200000, ans = 0;
    while(left <= right) {
        let mid = Math.floor((left + right) / 2);
        drawBinaryStep(left, right, mid, checkCondition(mid));
        await sleep(500); // 暂停观察
        // 更新区间逻辑...
    }
}
```

---
处理用时：200.26秒