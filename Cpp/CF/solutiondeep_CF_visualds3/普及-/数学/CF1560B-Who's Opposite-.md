# 题目信息

# Who's Opposite?

## 题目描述

Some number of people (this number is even) have stood in a circle. The people stand in the circle evenly. They are numbered clockwise starting from a person with the number $ 1 $ . Each person is looking through the circle's center at the opposite person.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1560B/a3a7851777ae33a1527beddaa8761afd1adfcbd6.png)A sample of a circle of $ 6 $ persons. The orange arrows indicate who is looking at whom.You don't know the exact number of people standing in the circle (but this number is even, no doubt). It is known that the person with the number $ a $ is looking at the person with the number $ b $ (and vice versa, of course). What is the number associated with a person being looked at by the person with the number $ c $ ? If, for the specified $ a $ , $ b $ , and $ c $ , no such circle exists, output -1.

## 说明/提示

In the first test case, there's a desired circle of $ 8 $ people. The person with the number $ 6 $ will look at the person with the number $ 2 $ and the person with the number $ 8 $ will look at the person with the number $ 4 $ .

In the second test case, there's no circle meeting the conditions. If the person with the number $ 2 $ is looking at the person with the number $ 3 $ , the circle consists of $ 2 $ people because these persons are neighbors. But, in this case, they must have the numbers $ 1 $ and $ 2 $ , but it doesn't meet the problem's conditions.

In the third test case, the only circle with the persons with the numbers $ 2 $ and $ 4 $ looking at each other consists of $ 4 $ people. Therefore, the person with the number $ 10 $ doesn't occur in the circle.

## 样例 #1

### 输入

```
7
6 2 4
2 3 1
2 4 10
5 3 4
1 3 2
2 5 4
4 3 2```

### 输出

```
8
-1
-1
-1
4
1
-1```

# AI分析结果


### 题目分析报告：CF1560B Who's Opposite?

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数学推理`与`模拟应用`  
🗣️ **初步分析**：  
> 解决本题的关键在于理解**圆圈编号的对称性**。想象一个像素风格的钟表盘，人物均匀分布（总人数为偶数），每个人通过圆心直视对面的人。核心规律是：**相对两人的编号差等于总人数的一半**（即 `|a-b| = n/2`）。  
> - 核心思路：通过已知的 `a` 和 `b` 计算总人数 `n = 2 * |a-b|`，再根据 `c` 的位置计算其对面点。
> - 难点：需处理无解情况（编号超出 `n`）和对面点的位置计算（分前半圆和后半圆）。
> - 可视化设计：采用**8位像素风格圆盘**，用不同颜色标记 `a, b, c` 的位置，动态绘制穿过圆心的箭头表示“对视”关系。当计算出对面点时，触发胜利音效并高亮目标位置。

---

## 2. 精选优质题解参考

### 题解一（来源：ARGV）
* **点评**：  
  思路直击核心——通过 `|a-b|` 推导总人数 `n`，无解条件 `(a>n || b>n || c>n)` 严谨覆盖边界。代码简洁高效：用分支计算对面点（`c±diff`），避免复杂运算。变量名 `diff` 清晰体现核心数学关系，适合竞赛直接复用。

### 题解二（来源：OnlyExtreme）
* **点评**：  
  亮点在于**分类讨论对面点的位置**（`c > n/2` 减半，`c < n/2` 加半），逻辑直观易理解。先交换 `a, b` 保证有序，提升可读性。代码规范，`long long` 预防溢出，实践价值高。

### 题解三（来源：Chinshyo）
* **点评**：  
  创新性使用**取模运算**统一计算对面点 `(c+n/2)%n`，辅以特判 `0` 值（输出 `n`），代码更紧凑。交换 `a, b` 确保计算一致性，但 `n` 的推导公式 `2+(b-a-1)*2` 稍显复杂，可优化为直接 `2*|a-b|`。

---

## 3. 核心难点辨析与解题策略

1.  **难点1：理解圆圈对称性**  
    * **分析**：相对点编号差恒为 `n/2`。若 `a, b` 不满足 `|a-b|=n/2`，则无解。  
    * 💡 **学习笔记**：圆圈问题优先寻找**位置与编号的数学关系**。

2.  **难点2：处理无解条件**  
    * **分析**：无解场景有两种——编号超出总人数 `n`（如 `a=2,b=3` 时 `n=2`，但 `3>2`），或 `n<2`（实际圆圈至少需2人）。  
    * 💡 **学习笔记**：先计算 `n`，再校验所有编号是否合法。

3.  **难点3：计算对面点位置**  
    * **分析**：对面点取决于 `c` 在圆中的位置：
      - 前半圆（`c ≤ n/2`）：对面点为 `c + n/2`
      - 后半圆（`c > n/2`）：对面点为 `c - n/2`  
    * 💡 **学习笔记**：分支或取模均可实现，但需注意编号从 `1` 开始。

### ✨ 解题技巧总结
- **技巧1：问题抽象化**  
  将实际场景转化为数学模型（如 `n=2*|a-b|`）。  
- **技巧2：边界全覆盖**  
  无解条件需同时校验 `a, b, c` 与 `n` 的关系。  
- **技巧3：计算优化**  
  对面点可用 `(c + n/2 - 1) % n + 1` 避免分支，但需理解取模原理。

---

## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考
* **说明**：综合优质题解思路，采用分支计算对面点，平衡效率和可读性。
* **完整核心代码**：
  ```cpp
  #include <iostream>
  #include <algorithm>
  using namespace std;

  int main() {
      int t;
      cin >> t;
      while (t--) {
          int a, b, c;
          cin >> a >> b >> c;
          int diff = abs(a - b);
          int n = 2 * diff;

          // 无解条件：a,b,c任一超过n 或 n<2
          if (a > n || b > n || c > n || n < 2) {
              cout << -1 << endl;
          } else {
              // 计算对面点
              if (c > diff) cout << c - diff << endl;
              else cout << c + diff << endl;
          }
      }
      return 0;
  }
  ```
* **代码解读概要**：  
  > 1. 读入测试数据量 `t`。  
  > 2. 计算 `diff = |a-b|`，总人数 `n = 2*diff`。  
  > 3. 无解时输出 `-1`，否则根据 `c` 位置输出对面点（`c±diff`）。

---

### 优质题解片段赏析

**题解一（ARGV）**  
* **亮点**：无解条件严谨，分支计算高效。  
* **核心代码片段**：
  ```cpp
  if (abs(a-b)*2 < max(a,b) || abs(a-b)*2 < c) {
      cout << -1 << endl;
  } else {
      if (abs(a-b) + c > abs(a-b)*2) cout << c - abs(a-b) << endl;
      else cout << c + abs(a-b) << endl;
  }
  ```
* **代码解读**：  
  > - `abs(a-b)*2` 即总人数 `n`。  
  > - 无解条件 `n < max(a,b) || n < c` 覆盖所有边界。  
  > - 分支计算：若 `c + diff > n` 则对面点为 `c-diff`，否则为 `c+diff`。  
* 💡 **学习笔记**：优先处理无解条件能提升代码健壮性。

**题解二（OnlyExtreme）**  
* **亮点**：位置分类明确，交换保证 `a<b` 简化计算。  
* **核心代码片段**：
  ```cpp
  if (a > b) swap(a, b);
  n = (b - a) * 2;
  if (c > n/2) cout << c - n/2 << endl;
  else if (c < n/2) cout << c + n/2 << endl;
  else cout << n << endl;  // c正好在n/2时对面是n
  ```
* **代码解读**：  
  > - `swap(a, b)` 确保 `b > a`，避免重复计算绝对值。  
  > - 三类分支覆盖 `c` 在圆的前/中/后位置。  
* 💡 **学习笔记**：有序化输入是简化逻辑的常用技巧。

**题解三（Chinshyo）**  
* **亮点**：取模运算统一对面点计算。  
* **核心代码片段**：
  ```cpp
  int n = 2 + (b - a - 1) * 2;  // 等价于 2*|a-b|
  int ans = (c + n/2) % n;
  if (ans == 0) cout << n << endl;
  else cout << ans << endl;
  ```
* **代码解读**：  
  > - `(c + n/2) % n` 将对面点映射到 `[1, n]` 范围内。  
  > - 特判取模结果 `0` 的情况（实际应为 `n`）。  
* 💡 **学习笔记**：取模适合数学思维强的学习者，但需理解编号偏移。

---

## 5. 算法可视化：像素动画演示

### 设计思路
**主题**：复古像素圆盘探险  
**核心演示**：动态展示圆圈编号对称性，通过圆心箭头连接对视点。  
**交互设计**：  
1. **初始化（8位像素风）**：  
   - 圆盘分割为 `n` 个扇形，编号 `1~n` 用不同颜色像素块表示。  
   - 控制面板含 `开始/暂停`、`单步`、`重置` 按钮及速度滑块。  
2. **关键步骤演示**：  
   - **高亮当前操作**：`a, b, c` 闪烁，并显示 `diff=|a-b|` → `n=2*diff`。  
   - **无解提示**：若 `a,b,c > n`，播放失败音效，圆盘显示红色 `❌`。  
   - **对面点计算**：  
     - `c` 发射像素箭头穿过圆心，命中对面点（`c±diff`）。  
     - 命中时播放胜利音效，目标块放大闪烁。  
3. **游戏化元素**：  
   - **音效**：命中（8位“叮”声）、无解（短促蜂鸣）、胜利（上扬旋律）。  
   - **关卡模式**：  
     - 第1关：样例 `6,2,4→8`（教学）。  
     - 第2关：无解案例 `2,3,1→-1`（挑战）。  

### 技术实现
```javascript
// 伪代码：绘制圆盘与箭头
function drawCircle(n) {
  for (let i=1; i<=n; i++) {
    const angle = (i-1) * (2*Math.PI/n);
    const x = centerX + radius * cos(angle);
    const y = centerY + radius * sin(angle);
    drawPixelBlock(x, y, color[i]); // 8位色块
    drawText(x, y, i); // 编号
  }
}

function drawArrow(c, target) {
  const startAngle = (c-1) * (2*Math.PI/n);
  const endAngle = (target-1) * (2*Math.PI/n);
  drawLine( // 穿过圆心的箭头
    pointOnCircle(startAngle),
    pointOnCircle(endAngle)
  );
}
```

---

## 6. 拓展练习与相似问题思考

1. **洛谷 P1145** - 约瑟夫问题  
   🗣️ 练习圆圈报数模拟，强化位置计算技巧。  
2. **洛谷 P1320** - 压缩技术  
   🗣️ 训练矩阵对称位置处理，迁移圆心对视思想。  
3. **CF1560A** - Dislike of Threes  
   🗣️ 同场竞赛题，巩固数学模拟能力。  

---

## 7. 学习心得与经验分享
> 本次题解未包含作者个人调试心得，但 Kay 强调：  
> **核心经验**：圆圈问题务必先推导**数学关系**（如 `n=2*|a-b|`），再处理边界。动手画图（如样例圆盘）能快速验证思路！

--- 

💡 **Kay的结语**：理解圆圈对称性是本题钥匙，掌握数学建模和边界处理，你也能成为像素世界的算法冒险家！下次挑战见！

---
处理用时：260.96秒