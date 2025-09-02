# 题目信息

# Surrounded

## 题目描述

So, the Berland is at war with its eternal enemy Flatland again, and Vasya, an accountant, was assigned to fulfil his duty to the nation.

Right now the situation in Berland is dismal — their both cities are surrounded! The armies of flatlanders stand on the borders of circles, the circles' centers are in the surrounded cities. At any moment all points of the flatland ring can begin to move quickly in the direction of the city — that's the strategy the flatlanders usually follow when they besiege cities.

The berlanders are sure that they can repel the enemy's attack if they learn the exact time the attack starts. For that they need to construct a radar that would register any movement at the distance of at most $ r $ from it. Thus, we can install a radar at such point, that at least one point of the enemy ring will be in its detecting range (that is, at a distance of at most $ r $ ). Then the radar can immediately inform about the enemy's attack.

Due to the newest technologies, we can place a radar at any point without any problems. But the problem is that the berlanders have the time to make only one radar. Besides, the larger the detection radius $ (r) $ is, the more the radar costs.

That's why Vasya's task (that is, your task) is to find the minimum possible detection radius for the radar. In other words, your task is to find the minimum radius $ r $ $ (r>=0) $ such, that a radar with radius $ r $ can be installed at some point and it can register the start of the movements of both flatland rings from that point.

In this problem you can consider the cities as material points, the attacking enemy rings - as circles with centers in the cities, the radar's detection range — as a disk (including the border) with the center at the point where the radar is placed.

## 说明/提示

The figure below shows the answer to the first sample. In this sample the best decision is to put the radar at point with coordinates $ (2,0) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF190B/d8b028b093bb3a5b506b76e0b869d1e14653f9f5.png)The figure below shows the answer for the second sample. In this sample the best decision is to put the radar at point with coordinates $ (0,0) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF190B/621697dde00296bbf818d1a40e69e6ac2914a652.png)

## 样例 #1

### 输入

```
0 0 1
6 0 3
```

### 输出

```
1.000000000000000```

## 样例 #2

### 输入

```
-10 10 3
10 -10 3
```

### 输出

```
11.142135623730951```

# AI分析结果

# 💡 Kay的C++算法解析：Surrounded 深入学习指南 💡

今天我们来一起分析“Surrounded”这道C++编程题。这道题看起来是关于几何的，但其实只要理解了**两个圆的位置关系**，就能轻松解决！本指南会帮你梳理思路，掌握核心算法，还能通过像素动画直观看到过程哦～


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：数学（几何计算）

🗣️ **初步分析**：  
解决“Surrounded”的关键，是理解**两个圆的位置关系**，并算出能“连接”它们的最小雷达半径。打个比方：假设两个敌人环是**两个气球**（红色和蓝色），我们要吹一个**最小的绿色泡泡**（雷达范围），让这个泡泡同时碰到两个气球——这就是题目要的最小半径！  

数学上，我们需要做三件事：  
1. **算圆心距**：红气球中心到蓝气球中心的距离（记为`D`，用勾股定理计算：`D = √[(x1-x2)² + (y1-y2)²]`）；  
2. **判位置关系**：看`D`和两个气球半径的关系（是离得远？还是一个包着另一个？还是已经碰到？）；  
3. **算最小半径**：根据关系套公式（后面会详细讲）。  

具体来说：  
- 如果两个气球**离得很远**（`D > 红半径 + 蓝半径`）：泡泡要填中间的空隙，`r = (D - 红半径 - 蓝半径) / 2`；  
- 如果一个气球**完全包着另一个**（`D < |红半径 - 蓝半径|`）：泡泡要从里面“撑”到外面，`r = (|红半径 - 蓝半径| - D) / 2`；  
- 其他情况（已经碰到或重叠）：泡泡不用大小，`r = 0`。  

**可视化设计思路**：我们用8位像素风格画两个圆（红、蓝），圆心用黄色亮点标记，圆心距用虚线连接。计算`D`时虚线闪烁（伴随“滴”音效），判断位置关系时数值高亮（伴随“叮”音效），生成泡泡时绿色像素块慢慢扩大（伴随“嗡”音效）——就像玩FC游戏一样！自动播放模式会像“贪吃蛇AI”一样逐步演示，完成时还会播放胜利音效～


## 2. 精选优质题解参考

为了帮你快速掌握，我筛选了3份思路清晰、代码规范的优质题解：

### 题解一（作者：王梓涵）
* **点评**：这份题解的思路超级直白！直接用`pow`算平方、`sqrt`算圆心距，然后分三种情况判断——完全贴合题目逻辑。代码里用`fixed << setprecision(10)`控制输出精度，完美满足题目要求（误差≤1e-6）。最棒的是，它没有多余的复杂结构，新手也能一眼看懂！

### 题解二（作者：wang_freedom）
* **点评**：这个题解的亮点是**用结构体组织圆的数据**（把圆的x、y、r放在一起），还贴心地**交换了大小圆**（确保`a`是小圆、`b`是大圆），让“内含”的判断条件更简单（不用写`abs`）。代码里用`ios::sync_with_stdio(0)`加速输入输出，是竞赛中的常用技巧哦～

### 题解三（作者：neil021110）
* **点评**：这份题解的代码超简洁！直接用`sqrt(pow(...))`算圆心距，分三种情况输出——没有冗余的变量。尤其值得学习的是，它用`printf("%.15lf", ...)`控制输出精度，比`cout`更灵活（比如处理0的时候不会输出多余的小数）。


## 3. 核心难点辨析与解题策略

在解决这道题时，大家常遇到三个“卡壳点”，我帮你梳理了对策：

### 1. 如何正确计算圆心距？
* **难点**：容易忘记用`double`类型，导致整数溢出或精度丢失。  
* **对策**：用勾股定理计算（`D = √[(x1-x2)² + (y1-y2)²]`），并且把`dx`、`dy`、`D`都定义为`double`类型（比如`double dx = x1 - x2;`）。  
* 💡 **学习笔记**：圆心距是几何题的基础，一定要用浮点数计算！

### 2. 如何判断两圆的位置关系？
* **难点**：容易混淆“外离”“内含”的条件。  
* **对策**：记住两个关键值：  
  - 半径和（`r_sum = r1 + r2`）：外离的判断条件是`D > r_sum`；  
  - 半径差绝对值（`r_diff = abs(r1 - r2)`）：内含的判断条件是`D < r_diff`。  
* 💡 **学习笔记**：外离看“和”，内含看“差”，其余情况都是相交/相切！

### 3. 如何记对不同情况的公式？
* **难点**：公式容易记反（比如把`(D - r_sum)/2`写成`(r_sum - D)/2`）。  
* **对策**：用“气球比喻”辅助记忆：  
  - 外离：两个气球离得远，中间的空隙是`D - r_sum`，泡泡要填一半，所以`r = (D - r_sum)/2`；  
  - 内含：大气球包着小气球，内层到外层的距离是`r_diff - D`，泡泡要撑一半，所以`r = (r_diff - D)/2`。  
* 💡 **学习笔记**：公式的本质是“填补空隙的一半”，这样就不会记错啦！

### ✨ 解题技巧总结
- **用结构体组织数据**：把圆的x、y、r放在一起，代码更清晰；  
- **交换大小圆**：让“内含”的判断更简单（不用写`abs`）；  
- **控制输出精度**：用`fixed << setprecision(15)`或`printf("%.15lf", ...)`，避免误差；  
- **处理边界情况**：比如相切时`r=0`，直接输出即可。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考
* **说明**：综合了优质题解的思路，用结构体组织数据，逻辑清晰，适合新手学习。  
* **完整核心代码**：
  ```cpp
  #include <iostream>
  #include <cmath>
  #include <iomanip>
  using namespace std;

  // 用结构体存储圆的信息（x坐标、y坐标、半径）
  struct Circle {
      int x, y, r;
  };

  int main() {
      Circle c1, c2;
      cin >> c1.x >> c1.y >> c1.r;  // 输入第一个圆
      cin >> c2.x >> c2.y >> c2.r;  // 输入第二个圆

      // 计算圆心距D（勾股定理）
      double dx = c1.x - c2.x;
      double dy = c1.y - c2.y;
      double D = sqrt(dx * dx + dy * dy);

      double r_sum = c1.r + c2.r;    // 半径和
      double r_diff = abs(c1.r - c2.r);  // 半径差绝对值
      double res;

      // 判断位置关系，计算最小半径
      if (D > r_sum) {
          res = (D - r_sum) / 2;  // 外离：填空隙的一半
      } else if (D < r_diff) {
          res = (r_diff - D) / 2;  // 内含：撑内层的一半
      } else {
          res = 0.0;  // 相交/相切：不需要半径
      }

      // 输出结果，保留15位小数（满足题目精度要求）
      cout << fixed << setprecision(15) << res << endl;
      return 0;
  }
  ```
* **代码解读概要**：  
  1. 用`struct Circle`存储圆的信息（x、y、r），让代码更整洁；  
  2. 计算圆心距`D`（勾股定理）；  
  3. 算半径和`r_sum`、半径差`r_diff`；  
  4. 分三种情况算最小半径`res`；  
  5. 用`fixed << setprecision(15)`输出高精度结果。


### 针对各优质题解的片段赏析

#### 题解一（作者：王梓涵）
* **亮点**：直接计算，逻辑清晰，适合新手入门。  
* **核心代码片段**：
  ```cpp
  double di1 = pow(x1 - x2, 2);
  double di2 = pow(y1 - y2, 2);
  double di = sqrt(di1 + di2); // 算圆心距
  ```
* **代码解读**：  
  用`pow`函数算`(x1-x2)²`和`(y1-y2)²`，再用`sqrt`算根号——这是最直接的圆心距计算方式。虽然`pow`的效率略低，但对于本题的输入规模完全够用！  
* 💡 **学习笔记**：简单问题用简单方法，不用追求“高端技巧”～

#### 题解二（作者：wang_freedom）
* **亮点**：用结构体和`swap`优化判断条件。  
* **核心代码片段**：
  ```cpp
  struct circle{
      int x,y,r;
  }a,b;
  if(a.r>b.r) swap(a,b); // 确保a是小圆，b是大圆
  ```
* **代码解读**：  
  用`struct circle`把圆的信息包起来，再交换`a`和`b`的半径——这样“内含”的判断条件就变成`b.r - a.r > dis`（不用写`abs`），更简洁！  
* 💡 **学习笔记**：交换变量可以简化条件判断，是常用的小技巧～

#### 题解三（作者：neil021110）
* **亮点**：用`printf`控制输出，更灵活。  
* **核心代码片段**：
  ```cpp
  printf("%.15lf",(d-r1-r2)/2);
  ```
* **代码解读**：  
  `printf("%.15lf", ...)`表示输出15位小数，比`cout`的`setprecision`更直接。比如输出0的时候，`printf`会自动处理成`0.000000000000000`，不会有多余的字符～  
* 💡 **学习笔记**：`printf`在精度控制上更灵活，竞赛中常常用到！


## 5. 算法可视化：像素动画演示 (核心部分)

### 动画演示主题：像素泡泡连气球
我们用**8位FC游戏风格**设计动画，模拟“吹泡泡连气球”的过程，让你直观看到算法的每一步！

### 设计思路简述
采用FC游戏的像素风格（比如《超级马里奥》的配色），用简单的几何图形和音效强化记忆：  
- 红色像素块代表第一个敌人环，蓝色代表第二个；  
- 黄色亮点标记圆心，虚线连接圆心（表示圆心距）；  
- 绿色像素块代表雷达泡泡，慢慢扩大直到碰到两个环；  
- 音效：计算圆心距时“滴”，判断关系时“叮”，泡泡扩大时“嗡”，完成时播放胜利音效。


### 动画帧步骤与交互关键点
1. **场景初始化**（FC风格）：  
   - 背景是浅灰色（类似FC的底色），红色圆在左（圆心(50, 100)），蓝色圆在右（圆心(250, 100)）；  
   - 控制面板在底部：“开始/暂停”“单步”“重置”按钮，速度滑块（1x～5x）；  
   - 8位风格的背景音乐（比如《坦克大战》的BGM）循环播放。

2. **计算圆心距**：  
   - 虚线连接两个圆心，闪烁三次（每次0.5秒），伴随“滴”的音效；  
   - 右上角显示圆心距`D`的数值（比如`D=6.0`）。

3. **判断位置关系**：  
   - 比如“外离”：右上角显示`D > r_sum`（`r_sum=4.0`），数值高亮为红色；  
   - 伴随“叮”的音效，中间出现一个小绿圆（半径0.5）。

4. **生成雷达泡泡**：  
   - 绿圆慢慢扩大（每帧半径加0.1），直到碰到红圆和蓝圆；  
   - 扩大时伴随“嗡”的音效，右上角实时显示当前半径`r`；  
   - 当绿圆碰到两个环时，停止扩大，显示“完成！r=1.0”，播放胜利音效（类似FC游戏的过关声）。

5. **交互设计**：  
   - 单步执行：点击“单步”按钮，每步显示一个动作（比如算圆心距→判关系→扩泡泡）；  
   - 自动播放：滑动速度滑块调整播放速度（1x最慢，5x最快）；  
   - 重置：点击“重置”按钮，回到初始状态，重新演示。


## 6. 拓展练习与相似问题思考

### 通用思路/技巧迁移
本题的**几何计算思路**（圆心距、两圆位置关系）可以迁移到很多问题：  
- 计算两个圆的交点；  
- 找覆盖多个点的最小圆；  
- 游戏中的碰撞检测（比如子弹碰到敌人）。


### 练习推荐 (洛谷)
以下是几道巩固几何计算的题目，建议尝试：

1. **洛谷 P1452** - 圆与圆的位置关系  
   🗣️ **推荐理由**：直接考察两圆的位置关系，和本题完全对应，帮你快速巩固知识点！

2. **洛谷 P2398** - [USACO09OCT] Barn Echoes G  
   🗣️ **推荐理由**：需要计算两点间距离（类似圆心距），是几何计算的变形应用。

3. **洛谷 P3948** - 数据结构  
   🗣️ **推荐理由**：结合了几何计算和数据结构，拓展你的思维（比如用哈希表存储圆的信息）。


## 7. 学习心得与经验分享 (若有)

在题解中，作者**Moon_Wind**提到：“注意一下，这里要输出整数0，不然第9个点过不去。”  
* **点评**：这个经验超实用！比如当两圆相交时，输出`0`而不是`0.0`，否则会因为格式错误丢分。这提醒我们：**一定要注意题目要求的输出格式**（比如是否需要小数点，保留几位小数）！


## 总结
本次关于“Surrounded”的分析就到这里啦！这道题的核心是**几何中的两圆位置关系**，只要掌握了圆心距的计算、位置关系的判断和公式，就能轻松解决。  

记住：编程中的几何题并不可怕，用“气球”“泡泡”这样的比喻辅助理解，再结合可视化动画，就能把抽象的数学变成直观的游戏～  

下次我们再一起探索新的编程挑战！💪

---
处理用时：200.42秒