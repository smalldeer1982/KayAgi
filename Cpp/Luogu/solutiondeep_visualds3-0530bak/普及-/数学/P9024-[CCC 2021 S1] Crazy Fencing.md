# 题目信息

# [CCC 2021 S1] Crazy Fencing

## 题目描述

栅栏由 $N$ 块木板组成。

因为是栅栏，所以第 $i$ 块的右边界与第 $i+1$ 块的左边界的高度一样。

告诉你这些木板的边界的高度与这些木板的宽度，输出这些木板的总面积。

## 说明/提示

样例解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/doy8i2lm.png)![](https://cdn.luogu.com.cn/upload/image_hosting/3q9oe7v5.png)

$N\leq 10000$，高度和宽度 $\leq 100$。

译自 [CCC2021 S2](https://cemc.math.uwaterloo.ca/contests/computing/past_ccc_contests/2021/ccc/seniorEF.pdf)。

## 样例 #1

### 输入

```
3
2 3 6 2
4 1 1
```

### 输出

```
18.5```

## 样例 #2

### 输入

```
4
6 4 9 7 3
5 2 4 1
```

### 输出

```
75.0```

# AI分析结果



---

**算法分类**  
几何

---

**题解思路与算法要点**  
- **核心公式**：梯形面积公式 $S = \frac{(a + b) \times h}{2}$，其中 $a$、$b$ 为相邻木板的高度，$h$ 为木板宽度。  
- **关键推导**：将每块木板抽象为直角梯形，相邻木板共享边界高度，确保公式的连续性。  
- **解决难点**：正确映射题目描述的物理结构到数学模型，理解“右边界与下一块左边界高度相同”的条件。  
- **实现方法**：遍历所有木板，按公式累加面积，注意浮点数精度与输出格式（保留一位小数）。  

---

**题解评分（≥4星）**  
1. **lichenzhen（5星）**  
   - 代码结构清晰，输入处理简洁，变量命名合理。  
   - 直接应用公式，无冗余操作。  
2. **zhuweiqi（4星）**  
   - 使用标准输入输出，代码简洁，但变量名 `a` 和 `h` 可优化。  
3. **lailai0916（4星）**  
   - 采用现代 C++ 风格（如 `ios::sync_with_stdio`），适合竞赛场景。  

---

**最优思路提炼**  
- **公式直接应用**：无需复杂数据结构，仅需遍历高度数组，依次计算相邻两高度的梯形面积。  
- **输入处理技巧**：高度数组长度为 $n+1$，确保每个木板正确对应相邻高度。  
- **浮点精度保障**：在计算时显式转换类型（如 `(double)` 或 `*1.0`），避免整数除法错误。  

---

**同类型题与算法套路**  
- **通用几何公式**：矩形、三角形面积计算，多边形分解为简单形状求和。  
- **常见套路**：将物理模型映射到数学公式（如时间/空间复杂度允许时，直接模拟）。  

---

**推荐题目**  
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)（几何覆盖问题）  
2. [P1428 小鱼比可爱](https://www.luogu.com.cn/problem/P1428)（简单计数与几何位置关系）  
3. [P1058 立体图](https://www.luogu.com.cn/problem/P1058)（三维几何投影）  

---

**个人心得摘录**  
- **输入顺序注意**：高度数组比木板数量多一，需循环读取 `n+1` 个元素。  
- **输出格式陷阱**：必须保留一位小数，否则判题系统会判错。  

---

**可视化与算法演示**  
```javascript
// 伪代码：Canvas 绘制梯形累加动画
function visualize() {
  let heights = [2, 3, 6, 2];   // 示例输入高度
  let widths = [4, 1, 1];       // 示例输入宽度
  let totalArea = 0;

  for (let i = 0; i < widths.length; i++) {
    // 高亮当前梯形
    drawTrapezoid(heights[i], heights[i+1], widths[i], "red");
    // 计算面积并更新总和
    let area = (heights[i] + heights[i+1]) * widths[i] / 2;
    totalArea += area;
    // 显示公式与中间结果
    showFormula(`S = (${heights[i]} + ${heights[i+1]}) × ${widths[i]} / 2 = ${area}`);
    showTotal(`当前总面积: ${totalArea.toFixed(1)}`);
    // 播放音效
    playSound("step_complete");
  }
}
```

**复古像素风格设计**  
- **颜色方案**：16 色调色板，梯形用绿/蓝交替填充，当前操作梯形用红色边框。  
- **动画流程**：  
  1. 逐步绘制每个梯形，填充像素块。  
  2. 显示当前公式计算，右侧面板更新累加值。  
  3. 背景播放 8-bit 风格音乐，完成时触发“胜利”音效。  
- **交互功能**：支持暂停/继续，调节动画速度（如 500ms/step）。  

---

**核心代码实现**  
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int heights[n + 1];
    for (int i = 0; i <= n; i++) cin >> heights[i];
    
    double total = 0;
    for (int i = 0; i < n; i++) {
        int width;
        cin >> width;
        total += (heights[i] + heights[i + 1]) * width / 2.0;
    }
    
    printf("%.1f\n", total);
    return 0;
}
```

**代码要点**  
- 输入高度数组长度为 `n + 1`，确保每个木板取相邻高度。  
- 使用 `2.0` 避免整数除法错误，输出保留一位小数。  

---

---
处理用时：72.34秒