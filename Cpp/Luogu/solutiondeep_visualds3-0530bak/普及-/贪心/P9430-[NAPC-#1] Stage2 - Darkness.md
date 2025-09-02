# 题目信息

# [NAPC-#1] Stage2 - Darkness

## 题目背景

> ![](https://cdn.luogu.com.cn/upload/image_hosting/y68eurqf.png)

## 题目描述

有 $n$ 支军队分布在各地，可以看作在一个平面直角坐标系内。他们都受 kid 的统一指挥，kid 共发出 $m$ 条命令。

命令有如下几种：

- `1 p q` 表示把**每支**军队的位置从 $(x_i,y_i)$ 移到 $(x_i+p,y_i+q)$。
- `2 i`，表示**第 $i$ 支军队**的位置对直线 $y=x$ 作轴对称变换（即交换 $x_i$ 与 $y_i$ 的值）。
- `3 i`，表示查询第 $i$ 支军队现在所处的位置（即输出此时的 $x_i$ 与 $y_i$）。

**请注意 `1` 与 `2` 命令的操作对象不同，前者为全体军队，后者为单支军队。**

本来 kid 可以直接拿望远镜看的，但是天太黑了，只能拜托你编写一个程序告诉他了。

## 说明/提示

### 【数据范围】
该题共有 $10$ 个测试点，每个测试点等分。

- 对于 $20\%$ 的数据，$n,m\leqslant 1000$。
- 对于另外 $30\%$ 的数据，保证没有 `2` 命令。

对于 $100\%$ 的数据，$1\leqslant n\leqslant 10^5$，$1\leqslant m\leqslant 5\times10^5$，$|a_i|,|b_i|,|p|,|q|\leqslant 10^3$，$1\leqslant i\leqslant n$，$op\in\{1,2,3\}$。

### 【样例解释】
| 时间 | $(x_1,y_1)$ | $(x_2,y_2)$ | $(x_3,y_3)$ |
|  :-:  |  :-:  |  :-:  |  :-:  |
| 初始时 | $(1,2)$ | $(2,5)$ | $(6,2)$ |
| 第 $2$ 次命令后 | $(2,6)$ | $(3,9)$ | $(7,6)$ |
| 第 $4$ 次命令后 | $(2,6)$ | $(3,9)$ | $(6,7)$ |
| 第 $6$ 次命令后 | $(-7,5)$ | $(-6,8)$ | $(-3,6)$ |

## 样例 #1

### 输入

```
3 7
1 2
2 5
6 2
3 2
1 1 4
3 3
2 3
3 1
1 -9 -1
3 3```

### 输出

```
2 5
7 6
2 6
-3 6```

# AI分析结果



## 唯一算法分类
**无算法分类**（核心思路为维护全局偏移量）

---

## 综合分析与结论

### 核心思路与算法流程
1. **全局偏移量维护**  
   维护两个全局变量 `dx, dy` 表示全体军队的平移量。所有军队实际坐标为 `(x_i + dx, y_i + dy)`  
   - 操作1：`dx += p, dy += q`（O(1)）  
   - 操作2：交换前还原真实坐标 `(x_i + dx, y_i + dy)` → 交换 → 存储相对坐标 `(new_x - dx, new_y - dy)`  
   - 操作3：直接输出 `x_i + dx, y_i + dy`（O(1)）

2. **可视化设计要点**  
   - **动态位移条**：顶部显示实时变化的 `dx, dy` 数值条  
   - **坐标同步更新**：  
     - 操作1时全体坐标网格向右下方同步平移（不实际移动，通过位移条变化体现）  
     - 操作2时对应坐标格高亮闪烁，交换 x/y 坐标并重新定位  
   - **复古像素风格**：  
     - 使用 16 色调色板，军队编号用 8x8 像素块表示  
     - 背景音乐采用 8-bit 风格循环音轨，关键操作触发短音效  

---

## 题解清单（≥4星）

### 1. [作者：Peaceful_Evening] ⭐⭐⭐⭐⭐
**亮点**：  
- 最简代码结构（仅 30 行）  
- 精准注释说明关键变量作用  
- 时间/空间复杂度最优（O(m)）

### 2. [作者：251Sec] ⭐⭐⭐⭐
**亮点**：  
- 变量命名清晰（`gx, gy` 代替 `dx, dy`）  
- 包含关键公式推导说明 `x[i] = ty + gy - gx`

### 3. [作者：wangbinfeng] ⭐⭐⭐⭐
**亮点**：  
- 封装军队操作为类方法（`swap()` 和 `print()`）  
- 包含快读优化实现

---

## 最优思路与技巧提炼

### 核心技巧：延迟计算与相对坐标
```cpp
// 全局偏移量维护
int dx = 0, dy = 0;

// 操作2处理逻辑（关键代码段）
int tx = x[i] + dx, ty = y[i] + dy; // 还原真实坐标
swap(tx, ty);                       // 执行镜像对称
x[i] = tx - dx;                     // 重新计算相对坐标
y[i] = ty - dy;
```

### 同类型题通用解法
- **P2129 L 国的战斗续之多路出击**（全局偏移量+单点翻转）  
- **CF1000C Covered Points Count**（差分数组+事件处理）  
- **P3368 树状数组 2**（差分思想与单点查询）

---

## 推荐相似题目
1. **P2129** - 全局偏移量+矩阵变换  
2. **P3368** - 差分数组与区间更新  
3. **CF817F** - 动态位运算与延迟更新

---

## 个人心得摘录
> "这道题看上去挺简单，做起来细节点还挺多。维护全局变量时，要特别注意操作2中需要先还原实际坐标再交换" —— Peaceful_Evening  
> "线段树的写法虽然直观，但在 5e5 次操作下会被更优的线性解法吊打" —— STARSczy

---

## 可视化与算法演示

### 动画方案设计
```html
<!-- 核心 HTML 结构 -->
<div id="grid"></div>
<div id="status-bar">
  <span>dx: <span id="dx-val">0</span></span>
  <span>dy: <span id="dy-val">0</span></span>
</div>

<!-- 关键 JavaScript 逻辑 -->
class ArmyAnimator {
  constructor(n) {
    this.dx = 0, this.dy = 0;
    this.armies = Array(n).fill({x:0, y:0}); 
    this.grid = document.getElementById('grid');
  }
  
  // 操作1动画
  moveAll(p, q) {
    animateBar("dx", this.dx += p); 
    animateBar("dy", this.dy += q);
    playSound('move');
  }
  
  // 操作2动画 
  swap(i) {
    flashCell(i); // 高亮闪烁
    const [x, y] = [this.armies[i].x, this.armies[i].y];
    this.armies[i] = {x: y - this.dx, y: x - this.dy};
    updateGridCell(i); 
    playSound('swap');
  }
}
```

### 复古游戏化效果
- **像素渲染**：使用 32x32 像素网格，每个单元格用 `canvas.fillRect()` 绘制  
- **音效设计**：  
  - 操作1：类似《超级马里奥》的跳跃音效  
  - 操作2：短促的《塞尔达传说》剑击声  
  - 背景音乐：循环播放《俄罗斯方块》BGM 的 8-bit 改编版  
- **自动演示模式**：  
  ```js
  function autoDemo(commands) {
    let step = 0;
    const timer = setInterval(() => {
      if(step >= commands.length) clearInterval(timer);
      else executeCommand(commands[step++]); 
    }, 1000);
  }
  ```

---

## 完整参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int x[MAXN], y[MAXN], dx, dy;

int main() {
    int n, m; 
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; i++) 
        scanf("%d%d", &x[i], &y[i]);
    
    while(m--) {
        int op, i; 
        scanf("%d", &op);
        if(op == 1) {
            int p, q; scanf("%d%d", &p, &q);
            dx += p; dy += q;
        } else if(op == 2) {
            scanf("%d", &i);
            int tx = x[i] + dx, ty = y[i] + dy;
            swap(tx, ty);
            x[i] = tx - dx;
            y[i] = ty - dy;
        } else {
            scanf("%d", &i);
            printf("%d %d\n", x[i]+dx, y[i]+dy);
        }
    }
    return 0;
}
```

---
处理用时：87.54秒