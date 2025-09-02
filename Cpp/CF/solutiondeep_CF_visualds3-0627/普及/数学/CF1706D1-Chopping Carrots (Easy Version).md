# 题目信息

# Chopping Carrots (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本间的区别仅为 $n$、$k$、$a_i$ 和 $\sum n$ 的上界。

注意不正常的空间限制。

给出长度为 $n$ 的整数数组 $ a_1, a_2, \ldots, a_n $，以及一个整数 $k$。

一个长度为 $n$ 的整数数组 $ p_1, p_2, \ldots, p_n $ 的花费为 $\max\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right) - \min\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right)$。
此处，$ \lfloor \frac{x}{y} \rfloor $ 表示 $x$ 除以 $y$ 的整数部分。
请找到花费最小的数组 $p$，且满足对任意 $ 1 \le i \le n$ 都有 $ 1 \le p_i \le k $。

## 说明/提示

在第一个测试组中，最优的数组是 $ p = [1, 1, 1, 2, 2] $。
$ \lfloor \frac{a_i}{p_i} \rfloor $ 得到的结果数组为 $ [4, 5, 6, 4, 5] $。
数组 $p$ 的花费为 $ \max\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) - \min\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) = 6 - 4 = 2 $。
可以证明，没有（满足题目条件的）数组的花费更小。

在第二个测试组中，最优的数组之一为 $ p = [12, 12, 12, 12, 12] $，它使得所有的 $ \lfloor \frac{a_i}{p_i} \rfloor $ 的值都为 $0$。

在第三个测试组中，唯一可能的数组为 $ p = [1, 1, 1] $。

## 样例 #1

### 输入

```
7
5 2
4 5 6 8 11
5 12
4 5 6 8 11
3 1
2 9 15
7 3
2 3 5 5 6 9 10
6 56
54 286 527 1436 2450 2681
3 95
16 340 2241
2 2
1 3```

### 输出

```
2
0
13
1
4
7
0```

# AI分析结果



**唯一算法分类**: 数论

---

### 题解思路与算法要点

#### 核心数学模型
设 $v_i = \lfloor \frac{a_i}{p_i} \rfloor$，要求最小化 $\max(v_i) - \min(v_i)$。关键思路是枚举最小值 $mn$，并计算此时各元素能达到的 $\max(v_i)$，最终取所有情况中的最小差值。

#### 数学推导与优化
1. **值域分析**  
   - 最小值 $mn$ 的可能范围：$[\lfloor \frac{a_1}{k} \rfloor, a_1]$（因 $a$ 递增）
   - 每个 $a_i$ 对应 $v_i$ 的可能取值数量为 $O(\sqrt{a_i})$（数论分块性质）

2. **关键公式**  
   对于给定 $mn$，求 $p_i$ 的下界：
   $$
   p_i \leq \left\lfloor \frac{a_i}{mn} \right\rfloor \quad \text{且} \quad p_i \leq k
   $$
   此时 $v_i = \left\lfloor \frac{a_i}{p_i} \right\rfloor$ 应尽可能接近 $mn$

3. **实现优化**  
   - **数论分块**：预处理每个 $a_i$ 的 $v_i$ 可能值，避免重复计算（Erica_N_Contina 解法）
   - **二分搜索**：快速找到满足 $v_i \geq mn$ 的最小 $p_i$（蒟蒻炒扇贝解法）

---

### 题解评分（≥4星）

| 作者              | 评分 | 亮点                                                                 |
|-------------------|------|----------------------------------------------------------------------|
| 蒟蒻炒扇贝        | ⭐⭐⭐⭐ | 二分法快速确定 $p_i$，时间复杂度 $O(Vn\log k)$ 可控                   |
| Erica_N_Contina   | ⭐⭐⭐⭐ | 数论分块预处理 + 动态维护极值，复杂度优化到 $O(n\sqrt{n})$             |
| cachejtt (D2解法) | ⭐⭐⭐⭐ | 优先队列动态调整极值，时间复杂度 $O(n\sqrt{a_i})$，适合大值域场景      |

---

### 最优思路提炼
**枚举最小值 + 数论分块优化**  
1. 预处理每个 $a_i$ 的所有可能 $v_i$ 值（使用数论分块）
2. 维护全局数组 `mx[]`，其中 `mx[v]` 表示当最小值为 $v$ 时，所有元素能取到的最小最大值
3. 枚举最小值 $mn$ 并更新答案：`ans = min(ans, mx[mn] - mn)`

**代码片段**  
```cpp
// 数论分块预处理
for(int i=1; i<=n; i++){
    int tot=0;
    for(int l=1, r; l<=a[i]; l=r+1){
        r = a[i]/(a[i]/l);
        if(l > k) break;  // p_i 不能超过 k
        te[++tot] = a[i]/l;
    }
    // 倒序维护最大值链
    for(int j=tot; j>=1; j--){
        mx[te[j]] = max(mx[te[j]], te[j+1]);
    }
}
```

---

### 同类题目推荐
1. [P3579 PON](https://www.luogu.com.cn/problem/P3579) - 基于数论分块的最值问题
2. [P2261 余数求和](https://www.luogu.com.cn/problem/P2261) - 利用数论分块优化求和
3. [P2111 考场的阴谋](https://www.luogu.com.cn/problem/P2111) - 极值差最小化问题

---

### 可视化设计（像素风格）

**动画流程**  
1. **初始界面**  
   - 8位像素风格，左侧显示数组 $a$，右侧为值域网格（0~max(a)）
   - 每个 $a_i$ 下方显示其对应的可能 $v_i$ 值（不同颜色块）

2. **枚举最小值**  
   - 红色光标在值域网格上移动，表示当前枚举的 $mn$
   - 对每个 $a_i$，高亮其 $v_i \geq mn$ 的最大块（蓝色闪烁）

3. **动态维护极值**  
   - 绿色横线标记当前全局最大值，紫色横线标记最小值
   - 每次更新时播放 8-bit 音效（类似《超级马里奥》金币声）

**交互功能**  
- **步进控制**：按方向键逐帧观察枚举过程
- **自动演示**：AI 自动选择使差值最小的路径，用黄色路径标记
- **音效系统**：使用 Web Audio API 播放复古音效，如：
  - 选中最小值：`beep(440, 50)`
  - 找到更优解：`beep(880, 100)`

---

**核心 JS 伪代码**  
```javascript
class PixelVisualizer {
  constructor(canvas) {
    this.grid = new PixelGrid(canvas, {palette: 16}); // 16色复古调色板
    this.playSound('startup'); // 启动音效
  }

  drawStep(mn) {
    this.grid.highlightCell(mn, 'red'); // 高亮当前最小值
    for(let ai of a) {
      let vi = this.calcVi(ai, mn);
      this.grid.drawBar(ai, vi, 'blue'); // 绘制当前 vi 值
    }
    this.playSound('step');
  }
}
```

---

### 个人心得摘录
> "枚举最小值时，发现某些情况无法取到，必须额外判断 `if(minn==mn)`，否则会计算错误。调试时通过输出中间变量才定位到问题。" —— 蒟蒻炒扇贝

**教训**：数学推导中的边界条件必须严格验证，避免理论最优解在实际中不可达。

---
处理用时：67.74秒