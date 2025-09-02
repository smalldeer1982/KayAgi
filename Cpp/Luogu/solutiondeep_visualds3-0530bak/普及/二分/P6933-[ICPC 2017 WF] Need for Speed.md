# 题目信息

# [ICPC 2017 WF] Need for Speed

## 题目描述

![](https://cdn.luogu.com.cn/upload/image_hosting/c7b5cigq.png)

Sheila 是一名学生，她开着一辆典型的学生车：这辆车又旧又慢，生锈并且快要散架了。最近，车速表上的指针掉了下来。她把它粘回去了，但可能放错了角度。因此，当车速表显示速度为 $s$ 时，她的真实速度是 $s+c$，其中 $c$ 是一个未知常数（可能为负）。 

Sheila 详细记录了最近的一次旅程，并希望利用这些记录来计算 $c$。这次旅程由 $n$ 段组成。在第 $i$ 段中，她行驶的距离为 $d_{i}$，车速表在整个段落中显示的速度为 $s_{i}$。整个旅程花费的时间为 $t$。请帮助 Sheila 计算 $c$。

注意，虽然 Sheila 的车速表可能显示负数，但她的真实速度在旅程的每一段中都是大于零的。

## 说明/提示

时间限制：1 秒，内存限制：512 MB。

spj 提供者：@[shenyouran](/user/137367)。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 5
4 -1
4 0
10 3
```

### 输出

```
3.000000000
```

## 样例 #2

### 输入

```
4 10
5 3
2 2
3 6
3 1
```

### 输出

```
-0.508653377
```

# AI分析结果



## 算法分类
**二分查找**

---

## 题解思路、算法要点与解决难点

### 核心思路
所有题解均采用**浮点数二分法**求解未知常数 $c$。核心逻辑为：

1. **确定二分范围**：
   - **左边界**：$c$ 必须满足 $s_i + c > 0$ → $l = -\min(s_i)$
   - **右边界**：取极大值（如 $10^9$）避免溢出

2. **Check函数**：计算 $c = mid$ 时的总时间 $\sum \frac{d_i}{s_i + mid}$，与 $t$ 比较决定二分方向：
   - 总时间 > $t$ → $c$ 偏小 → 向右半区间搜索
   - 总时间 ≤ $t$ → $c$ 偏大 → 向左半区间搜索

3. **精度控制**：循环终止条件设为 $r-l < 1e-7$，确保输出精度在 $10^{-6}$ 内。

### 解决难点
| 难点                | 解决方案                                 |
|---------------------|----------------------------------------|
| 浮点数精度控制       | 使用相对误差判断（如 while(r-l >= 1e-7)）|
| 输入数据类型陷阱     | 所有非整数变量用 double 存储           |
| 初始左边界计算       | 取 $-\min(s_i)$ 确保所有段速度为正     |

---

## 题解评分（≥4星）

1. **一只小咕咕（5星）**
   - **亮点**：完整解释浮点二分细节，代码简洁，注释清晰
   - **代码**：初始化边界合理，误差控制精准

2. **Flaw_Owl（4.5星）**
   - **亮点**：详细推导边界条件，提供单位换算说明
   - **代码**：包含输入优化，输出精度调整合理

3. **Genshin_ZFYX（4星）**
   - **亮点**：幽默注释增加可读性，强调数据类型陷阱
   - **代码**：错误处理边界条件的示例代码

---

## 最优思路/技巧提炼

### 关键实现技巧
- **边界初始化**：$l = -\min(s_i)$ 避免速度非正
- **浮点二分模板**：
  ```cpp
  while (r - l >= 1e-7) {
      double mid = (l + r) / 2;
      if (check(mid)) l = mid;
      else r = mid;
  }
  ```
- **Check函数优化**：直接累加避免中间变量

---

## 同类型题与算法套路
- **适用场景**：单调函数求根、物理参数校准
- **类似题目**：
  1. [P1024 一元三次方程求解](https://www.luogu.com.cn/problem/P1024)
  2. [P1314 智能质量检测](https://www.luogu.com.cn/problem/P1314)
  3. [P3382 三分法模板](https://www.luogu.com.cn/problem/P3382)

---

## 个人心得摘录
> "被输入数据的 double 类型坑了好久，必须用 %lf 读取" —— Genshin_ZFYX  
> "初始右边界取小了会 WA，直接设 1e9 更安全" —— lyas145

---

## 可视化与算法演示设计

### 核心动画方案
1. **动态二分区间**：
   - **颜色标记**：当前 $mid$ 值（红色），$l/r$ 边界（蓝色）
   - **步进控制**：单步展示计算总时间与比较过程

2. **像素风格 Canvas 实现**：
   ```javascript
   // 伪代码：绘制二分区间
   function drawRange(l, r, mid) {
       ctx.fillStyle = "#0000FF"; // 蓝色边界
       ctx.fillRect(l * scaleX, 0, 2, canvas.height);
       ctx.fillRect(r * scaleX, 0, 2, canvas.height);
       
       ctx.fillStyle = "#FF0000"; // 红色mid
       ctx.fillRect(mid * scaleX, 0, 2, canvas.height);
   }
   ```

3. **8-bit 音效**：
   - **步进音效**：短促 "哔" 声（Web Audio API）
   - **找到解**：上升音阶（频率 400Hz → 800Hz）

---

## 核心代码实现
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n;
double t, d[1005], s[1005];

bool check(double c) {
    double sum = 0;
    for (int i = 0; i < n; ++i)
        sum += d[i] / (s[i] + c);
    return sum > t; // 总时间偏大 → c 需增大
}

int main() {
    scanf("%d%lf", &n, &t);
    double min_s = 1e9;
    for (int i = 0; i < n; ++i) {
        scanf("%lf%lf", &d[i], &s[i]);
        min_s = min(min_s, s[i]);
    }
    
    double l = -min_s + 1e-7, r = 1e9;
    while (r - l > 1e-7) {
        double mid = (l + r) / 2;
        check(mid) ? l = mid : r = mid;
    }
    printf("%.9lf\n", l);
    return 0;
}
```

---
处理用时：70.65秒