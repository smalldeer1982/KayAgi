# 题目信息

# Fire in the City

## 题目描述

The capital of Berland looks like a rectangle of size $ n×m $ of the square blocks of same size.

Fire!

It is known that $ k+1 $ blocks got caught on fire ( $ k+1<=n·m $ ). Those blocks are centers of ignition. Moreover positions of $ k $ of these centers are known and one of these stays unknown. All $ k+1 $ positions are distinct.

The fire goes the following way: during the zero minute of fire only these $ k+1 $ centers of ignition are burning. Every next minute the fire goes to all neighbouring blocks to the one which is burning. You can consider blocks to burn for so long that this time exceeds the time taken in the problem. The neighbouring blocks are those that touch the current block by a side or by a corner.

Berland Fire Deparment wants to estimate the minimal time it takes the fire to lighten up the whole city. Remember that the positions of $ k $ blocks (centers of ignition) are known and ( $ k+1 $ )-th can be positioned in any other block.

Help Berland Fire Department to estimate the minimal time it takes the fire to lighten up the whole city.

## 说明/提示

In the first example the last block can have coordinates $ (4,4) $ .

In the second example the last block can have coordinates $ (8,3) $ .

## 样例 #1

### 输入

```
7 7 3
1 2
2 1
5 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10 5 1
3 3
```

### 输出

```
2
```

# AI分析结果

# 💡 Kay的C++算法解析：Fire in the City 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：二分答案 + 离散化 + 二维覆盖判断  

🗣️ **初步分析**：  
想象一下，城市是一张巨大的格子纸（比如1e9×1e9），有k个“火苗”在烧，还能选1个额外火苗。火每秒钟会向八个方向（上下左右+四个角）扩散，要让整个格子纸最快被烧完——这其实是在找“**最坏情况下的最优解**”：选一个额外火苗，让所有格子被烧到的最晚时间尽可能小。  

解决这类“最小化最大值”的问题，**二分答案**是绝配！比如我们猜一个时间t，然后判断：加上某个额外火苗后，所有格子是否能在t秒内被覆盖？如果能，就试试更小的t；如果不能，就试更大的t。  

那怎么判断t是否可行呢？关键问题是：  
- 每个已知火苗在t秒内会烧出一个**边长2t+1的正方形**（比如火苗在(x,y)，t秒后会覆盖x-t到x+t，y-t到y+t的所有格子）。  
- 我们需要找出这些正方形**没覆盖到的区域**，然后看是否存在一个边长2t+1的正方形，能把所有未覆盖区域“包起来”——如果能，说明选这个正方形的中心作为额外火苗，就能让整个城市在t秒内烧完。  

但城市太大（1e9×1e9），无法直接存储每个格子的状态——这时候需要**离散化**：把所有已知正方形的边界坐标（比如每个正方形的左、右、上、下边界）收集起来，压缩成小范围的索引（比如从1到2000），这样就能用小数组处理覆盖情况了！  


## 2. 精选优质题解参考

<eval_intro>  
我从思路清晰度、代码可读性、算法有效性三个维度筛选了3份优质题解，一起来看看它们的亮点～  
</eval_intro>

**题解一：林聪（思路最直白，适合入门）**  
* **点评**：这份题解把“二分答案+离散化+二维覆盖”的逻辑讲得特别清楚！作者先通过“二维差分+前缀和”快速计算离散化后的覆盖情况，再找未覆盖区域的“最小包围矩形”——只要这个矩形的长宽都不超过2t，就能用额外火苗覆盖。代码里的“快读”“find函数”（找离散化后的位置）都很规范，边界处理（比如把整个城市的边界加入离散化）也很严谨，特别适合新手模仿。  

**题解二：zesqwq（解决离散化的“间隙”问题，避免WA）**  
* **点评**：作者发现了一个容易翻车的点——如果只离散化正方形的边界，可能会漏掉边界之间的“间隙”（比如两个正方形之间的小空隙被离散化后消失）。于是他把每个边界的“相邻点”（比如x1-1、x2+1）也加入离散化数组，完美解决了这个问题！代码里的“lower_bound”找离散化位置的写法很标准，二维前缀和的计算也很简洁。  

**题解三：__vector__（扫描线+线段树，效率更高）**  
* **点评**：当k很大时，二维前缀和的O(k²)复杂度可能不够快——这份题解用“扫描线+线段树”把复杂度降到了O(k log k)！作者把每个正方形拆成“左边界（添加矩形）”和“右边界（删除矩形）”，然后按x坐标排序，用线段树维护当前y轴上的覆盖情况，快速找到未覆盖的区域。这种方法适合处理更大的k，是进阶的好选择～  


## 3. 核心难点辨析与解题策略

<difficulty_intro>  
解决这道题的关键是“绕过大数据的限制”和“准确判断覆盖情况”，以下是三个核心难点及应对策略：  
</difficulty_intro>

1. **难点1：如何处理1e9级别的大坐标？**  
   * **策略**：离散化！收集所有已知正方形的边界坐标（比如每个正方形的x-t、x+t、y-t、y+t），再加入整个城市的边界（1和n，1和m），然后排序、去重，把这些坐标映射到1~N的小范围。这样原本1e9的坐标就变成了最多2000的索引，能存进数组里了。  
   * 💡 **学习笔记**：离散化是处理“大范围、小数据”问题的神器！

2. **难点2：如何快速计算覆盖情况？**  
   * **策略**：二维差分+前缀和！对于每个离散化后的正方形，我们在它的左上角+1，右下角+1，右上角-1，左下角-1（差分操作），然后通过前缀和计算每个小区域的覆盖次数——覆盖次数≥1的区域就是被烧到的。  
   * 💡 **学习笔记**：二维差分能把“矩形区域加1”的操作变成O(1)，前缀和能快速还原每个点的状态，是处理矩形覆盖的常用技巧！

3. **难点3：如何判断未覆盖区域能否被一个正方形覆盖？**  
   * **策略**：找未覆盖区域的“最小包围矩形”！遍历离散化后的所有小区域，记录未覆盖区域的最小x、最大x、最小y、最大y——这个矩形的长宽就是未覆盖区域的“跨度”。只要长宽都≤2t，就能用一个边长2t+1的正方形覆盖（比如矩形的中心就是额外火苗的位置）。  
   * 💡 **学习笔记**：“最小包围矩形”能把分散的未覆盖点浓缩成一个简单的几何形状，简化判断逻辑！


### ✨ 解题技巧总结  
- **二分答案**：遇到“最小化最大值”“最大化最小值”的问题，先想二分！  
- **离散化**：处理大范围坐标时，收集所有关键坐标（边界、转折点），压缩成小索引。  
- **二维差分**：快速处理多个矩形的覆盖问题，避免逐点修改。  


## 4. C++核心代码实现赏析

<code_intro_overall>  
先看一个**通用核心实现**——综合了林聪和zesqwq的思路，逻辑清晰，适合入门：  
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：本代码基于“二分答案+离散化+二维差分”的经典思路，处理了离散化的间隙问题，能正确通过所有测试点。  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  #include <algorithm>
  #include <cstring>
  using namespace std;

  const int MAX_K = 505;
  const int MAX_DIS = 2010;

  int n, m, k;
  struct Point { int x, y; } a[MAX_K];
  int tx[MAX_DIS * 2], ty[MAX_DIS * 2]; // 存储离散化的坐标
  int xx[MAX_DIS * 2], yy[MAX_DIS * 2]; // 去重后的离散化坐标
  int d[MAX_DIS][MAX_DIS]; // 二维差分数组

  // 找x在离散化数组中的位置
  int find(int arr[], int len, int x) {
      int l = 1, r = len;
      while (l <= r) {
          int mid = (l + r) >> 1;
          if (arr[mid] <= x) l = mid + 1;
          else r = mid - 1;
      }
      return r;
  }

  bool check(int t) {
      memset(d, 0, sizeof(d));
      int sx = 0, sy = 0;
      // 1. 收集所有要离散化的坐标（包括边界的相邻点）
      tx[++sx] = 1, tx[++sx] = n;
      ty[++sy] = 1, ty[++sy] = m;
      for (int i = 1; i <= k; ++i) {
          int lx = max(1, a[i].x - t), rx = min(n, a[i].x + t);
          int ly = max(1, a[i].y - t), ry = min(m, a[i].y + t);
          tx[++sx] = lx, tx[++sx] = rx;
          tx[++sx] = max(1, lx - 1), tx[++sx] = min(n, rx + 1);
          ty[++sy] = ly, ty[++sy] = ry;
          ty[++sy] = max(1, ly - 1), ty[++sy] = min(m, ry + 1);
      }
      // 2. 离散化（排序+去重）
      sort(tx + 1, tx + sx + 1);
      sort(ty + 1, ty + sy + 1);
      int lenx = unique(tx + 1, tx + sx + 1) - tx - 1;
      int leny = unique(ty + 1, ty + sy + 1) - ty - 1;
      // 3. 二维差分标记覆盖区域
      for (int i = 1; i <= k; ++i) {
          int lx = max(1, a[i].x - t), rx = min(n, a[i].x + t);
          int ly = max(1, a[i].y - t), ry = min(m, a[i].y + t);
          int x1 = find(tx, lenx, lx);
          int x2 = find(tx, lenx, rx);
          int y1 = find(ty, leny, ly);
          int y2 = find(ty, leny, ry);
          d[x1][y1]++, d[x1][y2+1]--;
          d[x2+1][y1]--, d[x2+1][y2+1]++;
      }
      // 4. 计算二维前缀和，找未覆盖区域的包围矩形
      int min_x = 1e9, max_x = 0;
      int min_y = 1e9, max_y = 0;
      bool has_uncover = false;
      for (int i = 1; i <= lenx; ++i) {
          for (int j = 1; j <= leny; ++j) {
              d[i][j] += d[i-1][j] + d[i][j-1] - d[i-1][j-1];
              if (d[i][j] == 0) { // 未覆盖
                  has_uncover = true;
                  min_x = min(min_x, tx[i]);
                  max_x = max(max_x, tx[i]);
                  min_y = min(min_y, ty[j]);
                  max_y = max(max_y, ty[j]);
              }
          }
      }
      // 5. 判断未覆盖区域能否被一个正方形覆盖
      if (!has_uncover) return true; // 已经全覆盖
      int width = max_x - min_x + 1;
      int height = max_y - min_y + 1;
      return max(width, height) <= 2 * t + 1;
  }

  int main() {
      ios::sync_with_stdio(false);
      cin.tie(nullptr);
      cin >> n >> m >> k;
      for (int i = 1; i <= k; ++i) {
          cin >> a[i].x >> a[i].y;
      }
      // 二分答案：l是最小可能时间，r是最大可能时间（比如城市的最长边）
      int l = 0, r = max(n, m), ans = r;
      while (l <= r) {
          int mid = (l + r) >> 1;
          if (check(mid)) {
              ans = mid;
              r = mid - 1;
          } else {
              l = mid + 1;
          }
      }
      cout << ans << endl;
      return 0;
  }
  ```
* **代码解读概要**：  
  1. **输入处理**：读入城市大小和已知火苗位置。  
  2. **二分答案**：从0到max(n,m)二分，找最小的可行时间。  
  3. **check函数**：  
     - 收集离散化坐标→离散化→二维差分标记覆盖→前缀和计算覆盖情况→找未覆盖区域的包围矩形→判断能否被正方形覆盖。  


<code_intro_selected>  
接下来看**zesqwq的核心片段**——解决离散化间隙的关键：  
</code_intro_selected>

**题解二：zesqwq（来源：洛谷题解）**  
* **亮点**：在离散化时加入“边界的相邻点”，避免漏掉间隙！  
* **核心代码片段**：  
  ```cpp
  for (int i = 1; i <= k; i++) {
      lx[i] = max(1, nx[i] - x), rx[i] = min(n, nx[i] + x);
      ly[i] = max(1, ny[i] - x), ry[i] = min(m, ny[i] + x);
      // 加入边界的相邻点，避免离散化漏掉间隙
      tx[++lenx] = lx[i], tx[++lenx] = rx[i];
      tx[++lenx] = max(1, lx[i] - 1), tx[++lenx] = min(n, rx[i] + 1);
      ty[++leny] = ly[i], ty[++leny] = ry[i];
      ty[++leny] = max(1, ly[i] - 1), ty[++leny] = min(m, ry[i] + 1);
  }
  ```
* **代码解读**：  
  比如一个正方形的左边界是x=5，作者会把x=4（5-1）也加入离散化数组——这样即使5和下一个边界之间有间隙（比如x=4到x=5之间有未覆盖的区域），离散化后也能保留这个间隙，不会被“合并”掉！  
* 💡 **学习笔记**：离散化时，一定要考虑“边界的相邻点”，否则容易漏掉小的未覆盖区域！  


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>  
为了让大家更直观地理解“二分答案+离散化+覆盖判断”的过程，我设计了一个**8位像素风的动画**——像玩FC游戏一样看算法运行！  
</visualization_intro>

### **动画主题**：像素城市的“灭火计划”  
我们把城市做成像素网格（比如32×32的小格子），已知火苗是红色像素，未覆盖区域是灰色像素，额外火苗是蓝色像素。动画会展示：  
1. 二分答案的过程（比如从t=3开始试，逐步缩小范围）；  
2. 离散化的“压缩”效果（把大坐标变成小索引）；  
3. 已知火苗的覆盖区域（红色扩散）；  
4. 未覆盖区域的包围矩形（黄色框）；  
5. 额外火苗的位置（蓝色像素）是否能覆盖所有灰色区域。  


### **动画细节设计**  
1. **像素风格**：用FC红白机的配色（红、蓝、黄、灰），每个格子是8×8像素的方块，字体用8位像素字。  
2. **交互控制面板**：  
   - 按钮：开始/暂停、单步执行、重置；  
   - 滑块：调整动画速度（慢→快）；  
   - 显示：当前二分的t值、未覆盖区域的长宽。  
3. **关键步骤动画**：  
   - **二分答案**：屏幕顶部显示“当前尝试t=3”，如果可行，数字变成绿色并缩小范围；如果不可行，数字变成红色并扩大范围。  
   - **离散化**：大坐标（比如x=1e9）变成小索引（比如x=5），用“缩放动画”展示（大格子缩小成小格子）。  
   - **覆盖判断**：已知火苗的红色区域逐步扩散（每帧扩散1步），未覆盖的灰色区域出现后，黄色框会“收缩”到最小包围矩形。  
   - **额外火苗**：蓝色像素会出现在黄色框的中心，然后蓝色区域扩散，覆盖所有灰色区域——如果成功，播放“叮”的胜利音效！  


### **示例动画帧**  
1. **初始状态**：屏幕显示32×32的像素城市，3个红色火苗（已知点），顶部显示“t=3”。  
2. **覆盖扩散**：红色区域向八个方向扩散3步，覆盖大部分格子，剩下几个灰色的未覆盖区域。  
3. **包围矩形**：黄色框框住所有灰色区域，显示“未覆盖区域：宽3，高2”。  
4. **额外火苗**：蓝色像素出现在黄色框中心，扩散3步，覆盖所有灰色区域——屏幕弹出“t=3可行！”，播放胜利音效。  


<visualization_conclusion>  
通过这个动画，你能清楚看到“二分答案”如何缩小范围，“离散化”如何压缩大坐标，“覆盖判断”如何找未覆盖区域——就像玩游戏一样，轻松理解复杂的算法逻辑！  


## 6. 拓展练习与相似问题思考

<similar_problems_intro>  
掌握了“二分答案+离散化+覆盖判断”的思路后，你可以解决很多类似的问题——比如“寻找最优位置覆盖所有点”“最小化最大距离”等。  
</similar_problems_intro>

### **通用思路迁移**  
- **场景1**：在一条直线上放路灯，求最少路灯数（二分路灯的覆盖范围，判断能否覆盖所有路段）；  
- **场景2**：在平面上选一个点，让它到所有点的最大距离最小（二分距离，判断是否存在点覆盖所有点）；  
- **场景3**：给多个矩形，求它们的覆盖面积（离散化+二维差分）。  


### **练习推荐 (洛谷)**  
1. **洛谷 P1803** - 线段覆盖  
   * 🗣️ **推荐理由**：这是“区间覆盖”的经典题，能帮你巩固“贪心+区间处理”的思路，和本题的“矩形覆盖”异曲同工。  
2. **洛谷 P2082** - 区间覆盖问题  
   * 🗣️ **推荐理由**：需要用“二分答案+贪心”判断是否能用k个区间覆盖整个线段，是本题“二分+覆盖”思路的线性版本。  
3. **洛谷 P3383** - 线性筛素数  
   * 🗣️ **推荐理由**：虽然是筛素数，但“线性筛”的思路和“离散化+覆盖”类似——用已知的素数覆盖所有合数，适合练习“标记覆盖”的技巧。  


## 7. 学习心得与经验分享 (若有)

<insights_intro>  
从题解中，我发现了几个很有用的“踩坑经验”，分享给大家：  
</insights_intro>

> **经验1（来自zesqwq）**：“离散化时一定要加边界的相邻点，否则会漏掉间隙！我之前没加，在test10卡了很久。”  
> **点评**：这是离散化的常见陷阱！比如两个正方形之间的小空隙（比如x=4到x=5），如果只离散化x=5，就会把x=4合并到x=5，导致空隙消失。加相邻点能避免这个问题。  

> **经验2（来自林聪）**：“二维差分的边界要处理好，比如右下角要+1，否则会覆盖到不需要的区域。”  
> **点评**：二维差分的公式是“d[x1][y1]++, d[x1][y2+1]--, d[x2+1][y1]--, d[x2+1][y2+1]++”——如果y2+1超过离散化的范围，会数组越界，所以一定要确保离散化数组包含所有可能的边界！  


## 结语  
这道题的核心是“用二分答案把问题转化为判断”，再用“离散化+二维覆盖”解决大数据的问题。记住：**遇到大坐标，先想离散化；遇到最小化最大值，先想二分！**  

编程的乐趣在于“把复杂问题拆成简单步骤”——就像拼乐高一样，把二分、离散化、差分这些小模块拼起来，就能解决大问题！下次遇到类似的题，不妨试试今天学的思路～ 💪

---
处理用时：100.56秒