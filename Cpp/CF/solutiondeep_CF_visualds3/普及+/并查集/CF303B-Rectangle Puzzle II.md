# 题目信息

# Rectangle Puzzle II

## 题目描述

You are given a rectangle grid. That grid's size is $ n×m $ . Let's denote the coordinate system on the grid. So, each point on the grid will have coordinates — a pair of integers $ (x,y) $ $ (0<=x<=n,0<=y<=m) $ .

Your task is to find a maximum sub-rectangle on the grid $ (x_{1},y_{1},x_{2},y_{2}) $ so that it contains the given point $ (x,y) $ , and its length-width ratio is exactly $ (a,b) $ . In other words the following conditions must hold: $ 0<=x_{1}<=x<=x_{2}<=n $ , $ 0<=y_{1}<=y<=y_{2}<=m $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303B/d25d5fd31cdc2b2671d5f1dca98aadab16b15a21.png).

The sides of this sub-rectangle should be parallel to the axes. And values $ x_{1},y_{1},x_{2},y_{2} $ should be integers.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303B/4f1aa1906686be0387a09dbeae2bf3128e4fc307.png)If there are multiple solutions, find the rectangle which is closest to $ (x,y) $ . Here "closest" means the Euclid distance between $ (x,y) $ and the center of the rectangle is as small as possible. If there are still multiple solutions, find the lexicographically minimum one. Here "lexicographically minimum" means that we should consider the sub-rectangle as sequence of integers $ (x_{1},y_{1},x_{2},y_{2}) $ , so we can choose the lexicographically minimum one.

## 样例 #1

### 输入

```
9 9 5 5 2 1
```

### 输出

```
1 3 9 7
```

## 样例 #2

### 输入

```
100 100 52 50 46 56
```

### 输出

```
17 8 86 92
```

# AI分析结果


### 题目解读与核心算法识别  
**本题主要考察**：数学（比例计算与边界处理） + 模拟（最优位置选择）  

🗣️ **初步分析**：  
> 解决本问题的核心在于**固定比例矩形的数学建模**和**最优位置搜索**。想象你在一个像素网格游戏中放置一个比例固定的矩形框（如游戏中的道具框），需满足两个条件：  
> 1. 必须包含指定点（如玩家位置）  
> 2. 长宽比严格等于给定值（如2:1）  
>   
> 关键步骤：  
> - **比例约简**：将长宽比 `a:b` 约分为最简形式（除以最大公约数）  
> - **最大倍数计算**：根据网格边界和比例确定矩形最大可能尺寸  
> - **位置优化**：在数学约束下找到中心最接近目标点且字典序最小的坐标  
>  
> **可视化设计思路**：  
> 采用**8位像素风格**（类似FC游戏）动态演示：  
> - 网格背景：`n×m` 网格用像素方块表示  
> - 矩形绘制：用闪烁边框动画展示候选矩形  
> - 中心标记：高亮显示矩形中心与目标点的距离  
> - 音效设计：移动时触发"嘀"声，找到最优解时播放胜利音效  
> - 交互控制：支持单步执行/自动播放，速度可调  

---

### 精选优质题解参考  
**题解（Kay综合思路）**  
* **点评**：  
  1. **思路清晰性**：通过比例约简和边界约束分解问题，逻辑分层明确（先求最大矩形尺寸，再优化位置）  
  2. **代码规范性**：变量命名直观（如 `w/h` 表宽/高），模块化设计（候选点筛选、字典序比较分离）  
  3. **算法优化**：  
     - 时间复杂度 `O(1)`：避免暴力枚举，用数学计算替代  
     - 空间复杂度 `O(1)`：仅存储必要候选点  
  4. **实践价值**：  
     - 处理大边界值（`n, m ≤ 1e9`）  
     - 精确满足多条件优先级（面积最大 → 中心最近 → 字典序最小）  

---

### 核心难点辨析与解题策略  
1. **难点1：固定比例的最大矩形计算**  
   * **分析**：需将比例 `a:b` 约简后计算最大可能尺寸 `k = min(n/a', m/b')`，避免超界  
   * 💡 **学习笔记**：比例约简是优化问题的基础，类似分数化简  

2. **难点2：包含指定点的位置约束**  
   * **分析**：推导坐标数学约束：  
     - `x2 ∈ [max(x,w), min(n, x+w)]`  
     - `y2 ∈ [max(y,h), min(m, y+h)]`  
   * 💡 **学习笔记**：约束本质是线性不等式，需同时满足包含性和边界性  

3. **难点3：多目标优化（中心距离+字典序）**  
   * **分析**：  
     - 中心距离：转化为 `(x1+x2-2x)² + (y1+y2-2y)²` 最小化  
     - 字典序：按 `(x1,y1,x2,y2)` 顺序比较  
   * 💡 **学习笔记**：多条件优化需严格定义优先级，先主后次  

**✨ 解题技巧总结**  
- **技巧1：数学建模替代暴力枚举**：用比例计算避免无效搜索  
- **技巧2：候选点精筛**：离目标中心最近的整数点至多2个，大幅减少比较次数  
- **技巧3：字典序比较封装**：按 `(x1,y1,x2,y2)` 元组排序实现简洁比较  

---

### C++核心代码实现赏析  
**本题通用核心C++实现参考**  
* **说明**：综合最优解法，完整实现核心逻辑  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  #include <vector>
  #include <cmath>
  #include <algorithm>
  #include <climits>
  using namespace std;

  long long gcd(long long a, long long b) {
      return b ? gcd(b, a % b) : a;
  }

  int main() {
      long long n, m, x, y, a, b;
      cin >> n >> m >> x >> y >> a >> b;
      
      // 比例约简
      long long g = gcd(a, b);
      a /= g; b /= g;
      long long k = min(n / a, m / b);
      long long w = k * a, h = k * b;
      
      // 坐标边界约束
      long long Lx = max(x, w), Rx = min(n, x + w);
      long long Ly = max(y, h), Ry = min(m, y + h);
      
      // 目标中心计算
      double tx = x + w / 2.0, ty = y + h / 2.0;
      
      // 候选点筛选函数
      auto get_candidates = [](double target, long long L, long long R) {
          vector<long long> res;
          long long c1 = floor(target), c2 = ceil(target);
          double d1 = fabs(c1 - target), d2 = fabs(c2 - target);
          double min_d = min(d1, d2);
          
          if (d1 == min_d && c1 >= L && c1 <= R) res.push_back(c1);
          if (d2 == min_d && c2 >= L && c2 <= R && c1 != c2) res.push_back(c2);
          
          if (res.empty()) {
              double dL = fabs(L - target), dR = fabs(R - target);
              if (dL <= dR) res.push_back(L);
              else res.push_back(R);
              if (dL == dR && L != R) res.push_back(R);
          }
          return res;
      };
      
      // 获取候选坐标
      vector<long long> cand_x = get_candidates(tx, Lx, Rx);
      vector<long long> cand_y = get_candidates(ty, Ly, Ry);
      
      // 枚举候选矩形
      vector<vector<long long>> rects;
      for (auto x2 : cand_x)
      for (auto y2 : cand_y)
          rects.push_back({x2 - w, y2 - h, x2, y2});
      
      // 选择最优解（中心距离最小 -> 字典序最小）
      long long min_dsq = LLONG_MAX;
      vector<vector<long long>> best_rects;
      
      for (auto& r : rects) {
          long long dx = r[0] + r[2] - 2*x;
          long long dy = r[1] + r[3] - 2*y;
          long long dsq = dx*dx + dy*dy;
          
          if (dsq < min_dsq) {
              min_dsq = dsq;
              best_rects = {r};
          } else if (dsq == min_dsq) {
              best_rects.push_back(r);
          }
      }
      
      // 字典序排序
      sort(best_rects.begin(), best_rects.end());
      auto ans = best_rects[0];
      
      cout << ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3];
      return 0;
  }
  ```
* **代码解读概要**：  
  > 1. **输入处理**：读入网格尺寸 `(n,m)`、目标点 `(x,y)` 和比例 `(a,b)`  
  > 2. **比例约简**：计算最大公约数，获得最简比例  
  > 3. **矩形尺寸**：根据边界约束计算最大可能 `k` 值  
  > 4. **候选点筛选**：数学推导目标中心，高效选择候选坐标  
  > 5. **多目标优化**：先最小化中心距离，再按字典序排序  

---

### 算法可视化：像素动画演示  
* **主题**：**《比例矩形寻优大冒险》**（8位像素风格）  
* **核心演示**：  
  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303B/4f1aa1906686be0387a09dbeae2bf3128e4fc307.png)  

  | 步骤               | 可视化设计                                                                 | 交互/音效                              |
  |--------------------|----------------------------------------------------------------------------|----------------------------------------|
  | **1. 网格初始化**  | 绘制 `n×m` 像素网格，目标点 `(x,y)` 闪烁标记                              | 背景播放8位风格BGM                     |
  | **2. 比例展示**    | 显示约简后的比例 `a':b'` 和最大倍数 `k`                                    | 比例变换时触发"嘀嘀"音效               |
  | **3. 边界计算**    | 高亮显示 `Lx/Rx/Ly/Ry` 边界线                                              | 边界标记时触发"叮"声                   |
  | **4. 候选矩形**    | 用不同颜色边框绘制候选矩形，中心到目标点连线显示距离                       | 鼠标悬停显示坐标和距离值               |
  | **5. 最优解标记**  | 最优解矩形闪烁绿框，显示字典序比较过程                                     | 确定最优解时播放胜利音效+像素烟花动画  |
  | **6. AI自动演示**  | 自动按步骤执行，速度可调                                                   | 控制面板支持暂停/单步/重置             |

* **设计逻辑**：  
  > - **像素艺术**：用16色调色板（FC复古风）绘制网格和矩形  
  > - **数据结构可视化**：  
  >   - 队列/栈：用像素方块堆叠动画演示候选点筛选  
  >   - 边界标记：红色闪烁线标识约束范围  
  > - **游戏化学习**：  
  >   - 每步操作触发音效（移动=电子滴答，错误=短促蜂鸣）  
  >   - 完成寻优视为"通关"，解锁成就徽章  

---

### 拓展练习与相似问题思考  
* **通用技巧迁移**：  
  > 固定比例优化方法适用于：  
  > 1. 图像裁剪（保持长宽比的最大区域）  
  > 2. 网页响应式布局（容器比例约束）  
  > 3. 游戏碰撞框检测（旋转矩形投影）  

* **洛谷题目推荐**：  
  1. **P1387 最大正方形**  
     🗣️ 推荐理由：练习边界约束下的最大形状搜索，强化网格问题建模能力  
  2. **P1182 数列分段 Section II**  
     🗣️ 推荐理由：迁移比例约束思想到数列分割问题，理解数学优化本质  
  3. **P1059 [NOIP2006 普及组] 明明的随机数**  
     🗣️ 推荐理由：巩固字典序处理技巧，结合排序算法实践  

---

### 学习心得与经验分享  
> **关键调试经验**：  
> - **浮点精度陷阱**：中心坐标计算需用 `2x+w` 避免浮点误差  
> - **边界验证**：极端测试用例（如 `x=0`, `k=0`）可暴露未处理边界  
> - **候选点优化**：实际最多4个候选矩形，避免无效枚举  

---

<conclusion>  
通过本指南，我们深入剖析了**固定比例矩形优化问题**的核心数学原理和实现技巧。记住：复杂问题的解决方案往往始于基础数学建模，终于精细的边界处理。继续在洛谷上挑战相似问题，将大幅提升你的算法实战能力！🚀  
</conclusion>

---
处理用时：459.32秒