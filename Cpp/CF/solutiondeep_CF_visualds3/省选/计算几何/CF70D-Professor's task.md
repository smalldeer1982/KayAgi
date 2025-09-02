# 题目信息

# Professor's task

## 题目描述

Once a walrus professor Plato asked his programming students to perform the following practical task.

The students had to implement such a data structure that would support a convex hull on some set of points $ S $ . The input to the program had $ q $ queries of two types:

1\. Add a point with coordinates $ (x,y) $ into the set $ S $ . Note that in this case the convex hull of $ S $ could have changed, and could have remained the same.

2\. Say whether a point with coordinates $ (x,y) $ belongs to an area limited by the convex hull, including the border.

All the students coped with the task. What about you?

## 样例 #1

### 输入

```
8
1 0 0
1 2 0
1 2 2
2 1 0
1 0 2
2 1 1
2 2 1
2 20 -1
```

### 输出

```
YES
YES
YES
NO
```

# AI分析结果

# 💡 Kay的C++算法解析：Professor's task 深入学习指南 💡

<introduction>
  今天我们来一起分析「Professor's task」这道动态凸包的经典题目。动态维护凸包是计算几何中的重要技巧，本题需要我们实现**动态加点**和**查询点是否在凸包内**的功能。本指南会帮你拆解核心思路，理解代码逻辑，并通过像素动画直观感受算法运行过程！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：编程技巧应用（动态维护上下凸壳）

🗣️ **初步分析**：
解决这道题的关键，是把凸包拆成**上凸壳**（像山顶的轮廓，从左到右先升后降）和**下凸壳**（像山谷的轮廓，从左到右先降后升），分别用**有序数据结构（如`std::map`）**维护。简单来说，就像搭一个“不会凹进去的积木塔”——每次加新积木时，要检查周围的积木是否让塔变凹，凹的话就删掉中间的积木！

- **核心思路**：  
  1. 用`map`按横坐标排序存储上下凸壳的点（`map`的键是横坐标`x`，值是纵坐标`y`，保证`x`有序）；  
  2. **加点操作**：先判断点是否在凸包内（用上凸壳的下方、下凸壳的上方判断），不在的话加入凸壳，并删除周围“凹进去”的点（用叉积判断三点是否共线或凹）；  
  3. **查询操作**：判断点是否同时在上凸壳下方、下凸壳上方（含边界）。

- **核心难点**：  
  - 如何用叉积判断“凹点”？（三点`A,B,C`，若`(B-A)×(C-A)`的符号不符合凸壳要求，`B`就是凹点）；  
  - 如何高效找到点的前驱/后继？（`map::lower_bound`可以快速定位）；  
  - 如何处理边界情况（如点在凸壳最左/最右，或横坐标相同）？

- **可视化设计思路**：  
  用8位像素风格展示上下凸壳——上凸壳点用红色，下凸壳用蓝色，连接用同色线。加点时新点闪烁绿色，删除凹点时闪烁红色，叉积计算用橙色箭头表示向量方向。音效配合操作：加点“叮”、删除“咔”、查询“滴”，成功查询播放“胜利”高音，失败播放“提示”低音。


---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等维度筛选了以下优质题解，帮你快速掌握核心技巧：
</eval_intro>

**题解一：作者Elegia（赞24）**  
* **点评**：  
  这是动态凸包的“模板级”题解！思路极其清晰——用`map`分别维护上下凸壳，通过**坐标排序**避免极角排序的精度问题（特别适合整数坐标）。代码规范，变量命名直观（`top`/`down`对应上下凸壳），边界处理严谨（比如判断`map`的`begin()`和`end()`）。亮点是**摊还复杂度分析**（每个点最多被删一次，总时间`O(q log q)`），帮你理解算法效率。

**题解二：作者旋转卡壳（赞9）**  
* **点评**：  
  本题解用**极角排序**维护凸壳，巧妙通过“坐标乘3”减少精度误差（避免`atan2`的浮点误差）。代码结构清晰，注释详细，特别适合想学习极角排序法的同学。亮点是**循环处理凸壳调整**（插入点后，向极角小和大的方向依次删除凹点），逻辑直观。

**题解三：作者OIer_Tan（赞4）**  
* **点评**：  
  本题解用`set`维护上下凸壳，针对性处理了**横坐标相同的点**（删除同`x`的旧点，避免凸壳变形）。代码模块化强（`check_up`/`update_up`等函数分工明确），思路贴近静态凸包的Andrew算法，容易理解。亮点是`set::lower_bound`的灵活使用，快速定位点的位置。


---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
动态凸包的核心难点在于“维护凸壳的单调性”和“高效处理边界”，结合优质题解，我总结了3个关键问题的解决策略：
</difficulty_intro>

1. **关键点1：如何用叉积判断“凹点”？**  
   * **分析**：  
     对于上凸壳的三点`A(x1,y1), B(x2,y2), C(x3,y3)`（`x1<x2<x3`），若`(B-A)×(C-A) ≥ 0`，说明`B`在`AC`的下方，是凹点，需要删除。下凸壳则判断`≤ 0`（`B`在`AC`的上方）。叉积的计算公式是`(x2-x1)*(y3-y1) - (y2-y1)*(x3-x1)`，用`long long`避免溢出！  
   * 💡 **学习笔记**：叉积是判断三点凸凹的“神器”，符号决定方向！

2. **关键点2：如何快速找到点的前驱/后继？**  
   * **分析**：  
     用`map`或`set`的`lower_bound`函数（`O(log n)`时间）找到第一个`x`不小于当前点的`x`的位置，前驱就是`lower_bound`的前一个迭代器（注意判断是否是`begin()`）。例如`check_top`函数中，`it = top.lower_bound(x)`找到后继，`--it`得到前驱。  
   * 💡 **学习笔记**：有序数据结构的`lower_bound`是动态凸包的“导航仪”！

3. **关键点3：如何处理横坐标相同的点？**  
   * **分析**：  
     凸壳上的点横坐标必须严格单调（否则会出现垂直边，无法构成凸形）。因此，若新点`x`已存在，直接覆盖旧点（如`top[x] = y`），或删除旧点后插入新点（如OIer_Tan的`update_up`函数中，先删除同`x`的点）。  
   * 💡 **学习笔记**：横坐标相同的点只能留一个，否则凸壳会“竖起来”！

### ✨ 解题技巧总结
- **技巧A：拆分凸壳**：把凸包拆成上下两部分，分别维护，降低问题复杂度；  
- **技巧B：有序数据结构**：用`map`/`set`保持点的`x`有序，快速查找前驱/后继；  
- **技巧C：边界检查**：处理`map`的`begin()`和`end()`，避免迭代器越界；  
- **技巧D：叉积溢出**：用`long long`存储叉积结果，避免整数溢出！


---

## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个**通用核心实现**（综合Elegia、xukuan等题解的思路），帮你把握整体框架：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码用`map`维护上下凸壳，实现了加点和查询的核心逻辑，结构清晰，适合入门学习。
* **完整核心代码**：
  ```cpp
  #include <iostream>
  #include <map>
  using namespace std;

  typedef long long ll;
  map<int, int> top, down; // 上凸壳、下凸壳（x→y）

  // 计算叉积 (a.x*b.y - a.y*b.x)
  ll cross(int x1, int y1, int x2, int y2) {
      return (ll)x1 * y2 - (ll)x2 * y1;
  }

  // 检查点(x,y)是否在上凸壳下方（含边界）
  bool check_top(int x, int y) {
      auto it = top.lower_bound(x);
      if (it == top.end()) return false; // 在凸壳右侧
      if (it->first == x) return y <= it->second; // 同x，y不超过凸壳
      if (it == top.begin()) return false; // 在凸壳左侧
      auto jt = it; --jt; // 前驱
      return cross(it->first - jt->first, it->second - jt->second, 
                   x - jt->first, y - jt->second) <= 0;
  }

  // 检查点(x,y)是否在下凸壳上方（含边界）
  bool check_down(int x, int y) {
      auto it = down.lower_bound(x);
      if (it == down.end()) return false;
      if (it->first == x) return y >= it->second;
      if (it == down.begin()) return false;
      auto jt = it; --jt;
      return cross(it->first - jt->first, it->second - jt->second, 
                   x - jt->first, y - jt->second) >= 0;
  }

  // 删除上凸壳中的凹点it
  bool remove_top(map<int, int>::iterator it) {
      if (it == top.begin()) return false;
      auto jt = it, kt = it; --jt; ++kt;
      if (kt == top.end()) return false;
      // 三点jt→it→kt，若叉积≥0则it是凹点
      if (cross(it->first - jt->first, it->second - jt->second, 
                kt->first - jt->first, kt->second - jt->second) >= 0) {
          top.erase(it);
          return true;
      }
      return false;
  }

  // 插入点(x,y)到上凸壳
  void insert_top(int x, int y) {
      if (check_top(x, y)) return; // 已在凸壳内，无需插入
      top[x] = y;
      auto it = top.find(x), jt = it;
      // 向左删除凹点
      if (it != top.begin()) {
          --jt;
          while (remove_top(jt++)) --jt;
      }
      // 向右删除凹点
      if (++jt != top.end()) {
          while (remove_top(jt--)) ++jt;
      }
  }

  // 删除下凸壳中的凹点it（逻辑与remove_top相反）
  bool remove_down(map<int, int>::iterator it) {
      if (it == down.begin()) return false;
      auto jt = it, kt = it; --jt; ++kt;
      if (kt == down.end()) return false;
      if (cross(it->first - jt->first, it->second - jt->second, 
                kt->first - jt->first, kt->second - jt->second) <= 0) {
          down.erase(it);
          return true;
      }
      return false;
  }

  // 插入点(x,y)到下凸壳（逻辑与insert_top相反）
  void insert_down(int x, int y) {
      if (check_down(x, y)) return;
      down[x] = y;
      auto it = down.find(x), jt = it;
      if (it != down.begin()) {
          --jt;
          while (remove_down(jt++)) --jt;
      }
      if (++jt != down.end()) {
          while (remove_down(jt--)) ++jt;
      }
  }

  int main() {
      int q, op, x, y;
      cin >> q;
      while (q--) {
          cin >> op >> x >> y;
          if (op == 1) { // 加点
              insert_top(x, y);
              insert_down(x, y);
          } else { // 查询
              cout << (check_top(x, y) && check_down(x, y) ? "YES" : "NO") << endl;
          }
      }
      return 0;
  }
  ```
* **代码解读概要**：  
  代码分为三部分：1. 叉积计算（`cross`）；2. 检查点是否在凸壳内（`check_top`/`check_down`）；3. 插入点并维护凸壳（`insert_top`/`insert_down`）。主函数处理输入输出，调用上述函数完成操作。


<code_intro_selected>
接下来剖析优质题解的核心片段，看看高手的“巧思”：
</code_intro_selected>

**题解一：Elegia的insert_top函数**  
* **亮点**：用`map`的迭代器巧妙处理左右删除，逻辑简洁。
* **核心代码片段**：
  ```cpp
  void insert_top(int x, int y) {
      if (check_top(x, y)) return;
      top[x] = y;
      iterator it = top.find(x), jt = it;
      if (it != top.begin()) {
          --jt;
          while (remove_top(jt++)) --jt;
      }
      if (++jt != top.end())
          while (remove_top(jt--)) ++jt;
  }
  ```
* **代码解读**：  
  1. 先检查点是否在凸壳内，不在则插入`top[x] = y`；  
  2. `jt`初始指向`it`（新点位置），向左移动一位（`--jt`），然后循环删除凹点（`remove_top(jt++)`）——每次删除后`jt`会递增，所以要`--jt`回到当前位置；  
  3. 向右移动`jt`（`++jt`），同理循环删除凹点。  
* 💡 **学习笔记**：迭代器的“先动后调”技巧，避免重复计算！

**题解二：旋转卡壳的insert函数**  
* **亮点**：用极角排序维护凸壳，处理精度问题。
* **核心代码片段**：
  ```cpp
  void insert(p x) {
      if(cross(x-*pre,*suc-x)<=0) return ; // 在凸包内
      S.insert(x);
      set<p>::iterator cur=S.find(x),i=PRE(cur),j=PRE(i);
      while(cross(*cur-*j,*i-*j)>=0) S.erase(i),i=j,j=PRE(j); // 向左删
      i=SUC(cur);j=SUC(i);
      while(cross(*cur-*j,*i-*j)<=0) S.erase(i),i=j,j=SUC(j); // 向右删
  }
  ```
* **代码解读**：  
  1. `PRE`/`SUC`函数处理循环迭代器（凸壳是环形的）；  
  2. 插入点后，向左删除凹点（`cross(*cur-*j,*i-*j)>=0`），向右删除凹点（`<=0`）；  
  3. 极角排序让凸壳按逆时针顺序排列，方便环形处理。  
* 💡 **学习笔记**：极角排序适合环形凸壳，但要注意精度！


---

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解“动态维护凸壳”的过程，我设计了一个**8位像素风动画**，像玩FC游戏一样看算法运行！
</visualization_intro>

### 动画设计说明
- **风格**：仿FC红白机的8位像素风，背景浅灰色，点用2x2像素块表示，凸壳线用1x1像素线连接。
- **核心元素**：
  - 上凸壳点：红色像素块，连线红色；
  - 下凸壳点：蓝色像素块，连线蓝色；
  - 新点：绿色闪烁（2帧）；
  - 凹点：红色闪烁（1帧）后消失；
  - 叉积向量：橙色箭头（从前驱指向当前点，再指向后继）。
- **交互控制**：
  - 控制面板：“单步”（→）、“自动”（▶️）、“重置”（🔄），速度滑块（1-5档，对应100ms-500ms/步）；
  - 信息提示：底部文字框显示当前操作（如“插入点(2,0)”“删除凹点(1,0)”），叉积结果（如“叉积=3≥0，删除点B”）。
- **音效设计**：
  - 加点：“叮”（高频短音）；
  - 删除：“咔”（低频短音）；
  - 查询：“滴”（中频短音）；
  - 成功：“哆唻咪”（上扬音阶）；
  - 失败：“嗡”（低沉短音）；
  - BGM：循环播放8位风格的《超级马里奥》背景音（可选）。

### 动画关键帧示例
1. **初始状态**：屏幕显示3个点（0,0）、（2,0）、（2,2），上凸壳是（0,0）→（2,2），下凸壳是（0,0）→（2,0）；
2. **插入点(0,2)**：
   - 新点（0,2）闪烁绿色，检查发现不在凸壳内；
   - 插入上凸壳，`top[0] = 2`（覆盖旧点（0,0））；
   - 向左无点，向右检查（0,2）→（2,2），无凹点，停止；
3. **查询点(1,1)**：
   - 点（1,1）闪烁黄色，找到上凸壳前驱（0,2）、后继（2,2），计算叉积`(2-0,2-2)×(1-0,1-2) = 2×(-1) - 0×1 = -2 ≤0`（在上凸壳下方）；
   - 找到下凸壳前驱（0,0）、后继（2,0），叉积`(2-0,0-0)×(1-0,1-0) = 2×1 -0×1=2≥0`（在下凸壳上方）；
   - 播放“成功”音效，文字提示“点(1,1)在凸包内”。

<visualization_conclusion>
通过这个动画，你能清晰看到“加点→检查→调整凸壳”的完整过程，叉积的作用、凹点的删除都变得“可视化”了！
</visualization_conclusion>


---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
动态凸包的技巧不仅能解决本题，还能应用在**平面区域查询**、**最小包围盒**等问题中。以下是几道相似练习：
</similar_problems_intro>

### 通用思路迁移
- **场景1**：维护平面上的点集，查询点是否在凸包内（本题）；
- **场景2**：动态维护凸包，查询最远点对（旋转卡壳法）；
- **场景3**：动态维护凸包，计算最小包围矩形（需要凸包的四个切点）。

### 洛谷练习推荐
1. **洛谷 P2521** - [HAOI2011] 防线修建  
   * 🗣️ **推荐理由**：本题维护**上凸壳**，是动态凸包的入门题，帮助你巩固“拆分凸壳”的技巧。
2. **洛谷 P3187** - [HNOI2007] 最小矩形覆盖  
   * 🗣️ **推荐理由**：本题需要**静态凸包**的旋转卡壳法，是动态凸包的拓展，帮助你理解凸包的应用。
3. **洛谷 P4166** - [SCOI2007] 最大土地面积  
   * 🗣️ **推荐理由**：本题需要**静态凸包**的枚举技巧，帮助你掌握凸包的“面积计算”应用。
4. **洛谷 P5471** - [NOI2019] 弹跳  
   * 🗣️ **推荐理由**：本题用到**凸包优化**的动态规划，是凸包技巧的高级应用，挑战你的思维！


---

## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解中的“踩坑经验”能帮你少走弯路，以下是我摘录的精华：
</insights_intro>

> **经验1（来自Elegia）**：“坐标排序比极角排序精度高，尤其是整数坐标的题目。”  
> **点评**：极角排序用`atan2`会有浮点误差，坐标排序用整数比较，完全避免误差，是本题的“最优选择”！

> **经验2（来自旋转卡壳）**：“极角排序时坐标乘3，可以减少精度误差。”  
> **点评**：若必须用极角排序，缩放坐标是“救急技巧”——将坐标乘以一个小整数，让浮点计算更稳定。

> **经验3（来自OIer_Tan）**：“横坐标相同的点要删除旧点，否则凸壳会变形。”  
> **点评**：凸壳上的点横坐标必须严格单调，否则会出现垂直边，无法构成凸形，这是很多初学者的“隐藏bug”！


---

<conclusion>
本次关于「Professor's task」的分析就到这里！动态凸包的核心是“拆分凸壳+有序维护+叉积判断”，只要掌握这三点，就能解决大部分动态凸包问题。记得多动手写代码，多画示意图，算法会越来越“直观”！下次我们再一起挑战更难的计算几何问题～💪
</conclusion>

---
处理用时：157.92秒