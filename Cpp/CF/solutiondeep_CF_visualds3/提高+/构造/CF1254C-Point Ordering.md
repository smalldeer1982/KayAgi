# 题目信息

# Point Ordering

## 题目描述

This is an interactive problem.

Khanh has $ n $ points on the Cartesian plane, denoted by $ a_1, a_2, \ldots, a_n $ . All points' coordinates are integers between $ -10^9 $ and $ 10^9 $ , inclusive. No three points are collinear. He says that these points are vertices of a convex polygon; in other words, there exists a permutation $ p_1, p_2, \ldots, p_n $ of integers from $ 1 $ to $ n $ such that the polygon $ a_{p_1} a_{p_2} \ldots a_{p_n} $ is convex and vertices are listed in counter-clockwise order.

Khanh gives you the number $ n $ , but hides the coordinates of his points. Your task is to guess the above permutation by asking multiple queries. In each query, you give Khanh $ 4 $ integers $ t $ , $ i $ , $ j $ , $ k $ ; where either $ t = 1 $ or $ t = 2 $ ; and $ i $ , $ j $ , $ k $ are three distinct indices from $ 1 $ to $ n $ , inclusive. In response, Khanh tells you:

- if $ t = 1 $ , the area of the triangle $ a_ia_ja_k $ multiplied by $ 2 $ .
- if $ t = 2 $ , the sign of the cross product of two vectors $ \overrightarrow{a_ia_j} $ and $ \overrightarrow{a_ia_k} $ .

Recall that the cross product of vector $ \overrightarrow{a} = (x_a, y_a) $ and vector $ \overrightarrow{b} = (x_b, y_b) $ is the integer $ x_a \cdot y_b - x_b \cdot y_a $ . The sign of a number is $ 1 $ it it is positive, and $ -1 $ otherwise. It can be proven that the cross product obtained in the above queries can not be $ 0 $ .

You can ask at most $ 3 \cdot n $ queries.

Please note that Khanh fixes the coordinates of his points and does not change it while answering your queries. You do not need to guess the coordinates. In your permutation $ a_{p_1}a_{p_2}\ldots a_{p_n} $ , $ p_1 $ should be equal to $ 1 $ and the indices of vertices should be listed in counter-clockwise order.

## 说明/提示

The image below shows the hidden polygon in the example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1254C/662320cdf58665333639b68f5fe0cd63c31bc0cd.png)The interaction in the example goes as below:

- Contestant reads $ n = 6 $ .
- Contestant asks a query with $ t = 1 $ , $ i = 1 $ , $ j = 4 $ , $ k = 6 $ .
- Jury answers $ 15 $ . The area of the triangle $ A_1A_4A_6 $ is $ 7.5 $ . Note that the answer is two times the area of the triangle.
- Contestant asks a query with $ t = 2 $ , $ i = 1 $ , $ j = 5 $ , $ k = 6 $ .
- Jury answers $ -1 $ . The cross product of $ \overrightarrow{A_1A_5} = (2, 2) $ and $ \overrightarrow{A_1A_6} = (4, 1) $ is $ -2 $ . The sign of $ -2 $ is $ -1 $ .
- Contestant asks a query with $ t = 2 $ , $ i = 2 $ , $ j = 1 $ , $ k = 4 $ .
- Jury answers $ 1 $ . The cross product of $ \overrightarrow{A_2A_1} = (-5, 2) $ and $ \overrightarrow{A_2A_4} = (-2, -1) $ is $ 1 $ . The sign of $ 1 $ is $ 1 $ .
- Contestant says that the permutation is $ (1, 3, 4, 2, 6, 5) $ .

## 样例 #1

### 输入

```
6

15

-1

1```

### 输出

```
1 1 4 6

2 1 5 6

2 2 1 4

0 1 3 4 2 6 5```

# AI分析结果

# 💡 Kay的C++算法解析：Point Ordering 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：编程技巧应用（交互查询与凸包性质）

🗣️ **初步分析**：  
这道题是**交互题**——我们不能直接看到点的坐标，只能通过两种“查询工具”问问题，最终要排出凸包的逆时针顺序（且第一个点必须是1）。关键在于利用**凸包的性质**和**查询的信息**：  
- 叉积符号（t=2）像“方向指南针”：能告诉我们一个点在某条线段的**左侧（+1）**还是**右侧（-1）**（比如，查询`2 1 j k`，就是看k在1-j线段的左边还是右边）。  
- 面积的两倍（t=1）像“距离测量仪”：当线段固定时（比如1-j），面积越大，说明点k到这条线段的**距离越远**（因为面积=底×高÷2，底固定时，面积和高成正比）。  

凸包的核心性质是：**固定一条边，其他点到这条边的距离会形成“单峰函数”**——先增大到一个最高点（对踵点），再减小。我们的目标就是：  
1. 找到1号点的下一个点`se`（用叉积找“最右侧”的点）；  
2. 找到所有点到1-se边的**最远点`mx`**（用面积查询）；  
3. 将其他点按距离排序，并用叉积区分“左侧”和“右侧”，最终拼接成逆时针顺序。  

**可视化设计思路**：  
我们会用**8位像素风**（像FC红白机游戏）展示整个过程：  
- 点用不同颜色的像素块表示（1号红、se蓝、mx黄、其他绿）；  
- 线段用白色像素线连接；  
- 关键操作（比如找se、查面积）会有**闪烁效果**和**像素音效**（比如找se时播放“叮”声，查面积时播放“滴滴”声）；  
- AI自动演示模式会像“贪吃蛇找食物”一样，一步步展示每个查询和决策。


## 2. 精选优质题解参考

<eval_intro>
我从**思路清晰度、代码可读性、算法有效性**三个维度筛选了3份优质题解，它们的思路各有特色，但都完美符合题目要求～
</eval_intro>

**题解一：Falashiro（赞：5）**  
* **点评**：这份题解的思路**像“搭积木”一样直白**！作者先通过叉积找到1的下一个点`se`（遍历所有点，找最右侧的点），再用面积查询找到最远点`mx`，最后按距离排序并分类。代码风格非常规范——变量名`x`（当前se）、`maxn`（最大面积）、`t[i].s`（面积）都很易懂，甚至作者自己说“代码可读性挺高”～ 更棒的是，它的询问次数只有`3n-6`次，远低于题目限制，非常高效！

**题解二：Mine_King（赞：3）**  
* **点评**：作者的思路**像“切蛋糕”**——把凸包用1-2线段分成左右两部分，分别处理每部分的点。他用叉积区分左右侧，用面积找最高点，再按“左小右大”排序。代码里用`vector`存左右点，`sort`和`reverse`处理顺序，结构清晰。更贴心的是，作者还配了**图示**（比如直线切割凸包的图），帮我们直观理解！

**题解三：Imakf（赞：3）**  
* **点评**：这份题解的思路**很“灵活”**——作者没强求找到相邻点，而是直接用1-2线段分割凸包（因为分割后的子凸包中，1-2一定是相邻的）！他用**双端队列**和**栈**维护点的顺序，像“整理队伍”一样把点按逆时针排好。虽然代码里用了`deque`和`stack`，但逻辑很顺，适合学过数据结构的同学参考～


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的“拦路虎”主要有3个，结合优质题解的思路，我们一起拆穿它们！
</difficulty_intro>

1. **难点1：怎么找到1号点的下一个点`se`？**  
   * **分析**：凸包上，1的下一个点`se`满足：**所有其他点都在1-se线段的右侧**（叉积为-1）。所以我们可以从`se=2`开始，遍历点3到n，每次查询`2 1 se i`——如果结果是-1，说明i在se的右侧，替换se为i！  
   * 💡 **学习笔记**：找“最右侧”的点，其实是在找凸包的“边界”，叉积是我们的“方向探测器”！

2. **难点2：怎么用面积信息排序？**  
   * **分析**：固定1-se边后，面积的两倍就是点到这条边的**相对距离**。我们要找距离最大的点`mx`（对踵点），因为凸包上的点到这条边的距离会“先增后减”——`mx`就是“峰值”。  
   * 💡 **学习笔记**：面积是“距离的代言人”，找峰值就是找凸包的“最高点”！

3. **难点3：怎么得到逆时针顺序？**  
   * **分析**：找到`mx`后，用叉积查询`2 1 mx i`——如果结果是-1，说明i在1-mx的左侧，按距离**升序**排；如果是1，说明在右侧，按距离**降序**排。最后拼接顺序：1 → se → 左侧点 → mx → 右侧点，就是逆时针！  
   * 💡 **学习笔记**：分类排序的关键是“顺应凸包的弯曲方向”，叉积帮我们分清“左右”！

### ✨ 解题技巧总结
- **技巧1：用叉积定方向**：叉积的符号直接对应点的相对位置，是交互题中“问方向”的利器。  
- **技巧2：用面积定距离**：当线段固定时，面积和距离成正比，不用算坐标也能比较距离！  
- **技巧3：利用凸包的单峰性质**：凸包上的点到任意边的距离都是“先增后减”，找到峰值就能分割点集！


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**综合优质题解思路的通用代码**，它能帮你快速理解整体框架～
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了Falashiro和Mine_King的思路，结构清晰，容易调试。
* **完整核心代码**：
  ```cpp
  #include <iostream>
  #include <vector>
  #include <algorithm>
  using namespace std;

  const int MAXN = 1005;
  int n;
  struct Node { long long s; int pos; };
  Node t[MAXN];

  // 询问函数：opt是t=1或t=2，i,j,k是三个点
  int ask(int opt, int i, int j, int k) {
      cout << opt << " " << i << " " << j << " " << k << endl;
      cout.flush(); // 必须刷新输出！
      int res; cin >> res;
      return res;
  }

  bool cmpLeft(Node a, Node b) { return a.s < b.s; } // 左侧升序
  bool cmpRight(Node a, Node b) { return a.s > b.s; } // 右侧降序

  int main() {
      cin >> n;
      int se = 2; // 初始se是2

      // 步骤1：找1的下一个点se
      for (int i = 3; i <= n; ++i) {
          if (ask(2, 1, se, i) == -1) {
              se = i;
          }
      }

      // 步骤2：找最远点mx（对踵点）
      long long maxS = -1;
      int mx = 0;
      for (int i = 2; i <= n; ++i) {
          if (i == se) continue;
          t[i].pos = i;
          t[i].s = ask(1, 1, se, i);
          if (t[i].s > maxS) {
              maxS = t[i].s;
              mx = i;
          }
      }

      // 步骤3：分类左右侧并排序
      vector<Node> left, right;
      for (int i = 2; i <= n; ++i) {
          if (i == se || i == mx) continue;
          int sign = ask(2, 1, mx, i);
          if (sign == -1) left.push_back(t[i]);
          else right.push_back(t[i]);
      }
      sort(left.begin(), left.end(), cmpLeft);
      sort(right.begin(), right.end(), cmpRight);

      // 输出结果
      cout << "0 1 " << se;
      for (auto &p : left) cout << " " << p.pos;
      cout << " " << mx;
      for (auto &p : right) cout << " " << p.pos;
      cout << endl;
      return 0;
  }
  ```
* **代码解读概要**：  
  1. **询问函数**：封装了交互的输入输出，必须用`cout.flush()`确保数据发送！  
  2. **找se**：遍历所有点，用叉积找最右侧的点；  
  3. **找mx**：查询所有点的面积，记录最大的点；  
  4. **分类排序**：用叉积区分左右侧，分别按升序/降序排列；  
  5. **输出**：按1→se→左侧→mx→右侧的顺序输出，就是逆时针！

---

<code_intro_selected>
再看优质题解中的**核心片段**，学习它们的“巧妙细节”～
</code_intro_selected>

**题解一：Falashiro的“找se”片段**
* **亮点**：用最简洁的循环找到se，逻辑直白到“一眼就能懂”！
* **核心代码片段**：
  ```cpp
  int se = 2;
  for (int i = 3; i <= n; ++i) {
      cout << "2 1 " << se << " " << i << endl;
      fflush(stdout);
      int res; cin >> res;
      if (res == -1) se = i; // 找到更右侧的点，替换se
  }
  ```
* **代码解读**：  
  为什么res=-1就要替换se？因为叉积为-1说明i在1-se的**右侧**——而se是1的下一个点，所有其他点都应该在它的右侧！所以每次找到更右的点，就更新se～  
* 💡 **学习笔记**：循环的核心是“贪心”——每次选最右侧的点，最终得到的就是1的下一个点！

**题解二：Mine_King的“分左右侧”片段**
* **亮点**：用vector存左右点，结构清晰，适合处理“分割凸包”的场景！
* **核心代码片段**：
  ```cpp
  vector<pair<long long, int>> r, l;
  for (int i = 3; i <= n; ++i) {
      printf("2 1 2 %d\n", i); fflush(stdout);
      int x; cin >> x;
      if (x == -1) r.emplace_back(0, i); // 右侧
      else l.emplace_back(0, i); // 左侧
  }
  ```
* **代码解读**：  
  作者用1-2线段分割凸包，把点分成左右两部分（r存右侧，l存左侧）。之后分别处理每部分的点，避免了“混在一起排序”的混乱～  
* 💡 **学习笔记**：分割点集是处理凸包的常用技巧，能把复杂问题拆成两个简单问题！

**题解三：Imakf的“双端队列维护顺序”片段**
* **亮点**：用双端队列（deque）和栈（stack）整理点的顺序，像“排队”一样自然！
* **核心代码片段**：
  ```cpp
  deque<int> Ans;
  stack<int> Tmp;
  if (!pt[0].empty()) Ans.push_back(pt[0][0].ind);
  for (int i = 1; i < (int)pt[0].size(); ++i) {
      cout << "2 1 " << pt[0][i].ind << " " << Ans.back() << endl;
      int pos; cin >> pos;
      if (pos < 0) { // 不符合顺序，弹出队尾
          Tmp.push(Ans.back());
          Ans.pop_back();
      }
      Ans.push_back(pt[0][i].ind);
  }
  while (!Tmp.empty()) { // 把栈里的点加回队尾
      Ans.push_back(Tmp.top());
      Tmp.pop();
  }
  ```
* **代码解读**：  
  作者用双端队列存左侧点，每次加新点时，检查是否符合凸包的顺序（pos<0说明顺序不对）。如果不对，就把队尾的点弹出栈，最后再把栈里的点加回——这样就能保证队列里的点是逆时针顺序！  
* 💡 **学习笔记**：数据结构是“工具”，双端队列和栈能帮我们灵活调整顺序！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你“亲眼看到”算法的每一步，我设计了一个**8位像素风的动画**——《凸包探险家》！像玩红白机游戏一样，跟着1号点找遍凸包的每一个点～
</visualization_intro>

### **动画主题**：凸包探险家（FC风格）
**核心演示内容**：展示从“找se”→“找mx”→“分类排序”的完整过程，用像素块、音效和动画让你直观理解！

### **设计思路**
- **8位像素风**：用FC游戏的配色（红、蓝、黄、绿、白），营造复古的学习氛围；  
- **音效强化记忆**：关键操作配不同的像素音效（比如找se的“叮”声、查面积的“滴滴”声）；  
- **游戏化关卡**：把每个步骤做成“小关卡”（找se→关卡1，找mx→关卡2，分类排序→关卡3），完成关卡有“星星奖励”，增加成就感！

### **动画帧步骤与交互**

#### 1. **初始场景（8位像素风）**
- 屏幕显示一个16x16的像素平面，点用不同颜色的方块表示：  
  - 1号点：红色方块（闪烁，提示“我是起点！”）；  
  - 其他点：绿色方块（静止）；  
- 下方控制面板：  
  - 按钮：开始/暂停、单步、重置；  
  - 滑块：速度调节（慢→快）；  
  - 开关：AI自动演示（默认关闭）；  
- 背景播放**8位风格的轻松BGM**（像《超级马里奥》的背景音乐）。

#### 2. **关卡1：找se（1的下一个点）**
- **动画过程**：  
  1. 初始se是蓝色方块（点2）；  
  2. 逐个检查点3到n：  
     - 当前检查的点（比如点3）闪烁，屏幕下方显示“查询：2 1 2 3”；  
     - 弹出“等待回复...”的文字，然后显示“回复：-1”；  
     - 播放“叮”的音效，se从点2变成点3（蓝色方块移动到点3）；  
  3. 直到遍历完所有点，se变成最终的蓝色方块，屏幕显示“关卡1完成！获得1颗星～”。

#### 3. **关卡2：找mx（最远点）**
- **动画过程**：  
  1. 1号（红）和se（蓝）用白色线段连接；  
  2. 逐个查询点2到n的面积：  
     - 当前点（比如点4）下方显示“面积：15”（用像素数字）；  
     - 如果面积比之前的大，点4变成黄色（mx），闪烁并播放“胜利”音效；  
  3. 遍历完所有点，mx是最终的黄色方块，屏幕显示“关卡2完成！获得2颗星～”。

#### 4. **关卡3：分类排序**
- **动画过程**：  
  1. 1号（红）和mx（黄）用白色线段连接；  
  2. 逐个查询点的叉积：  
     - 当前点（比如点5）闪烁，屏幕显示“查询：2 1 mx 5”；  
     - 如果回复是-1，点5变成浅绿色（左侧）；如果是1，变成深绿色（右侧）；  
  3. 排序：  
     - 浅绿色点按面积**从左到右**排列（升序）；  
     - 深绿色点按面积**从右到左**排列（降序）；  
     - 每个点移动时播放“沙沙”的音效；  
  4. 所有点排好序后，用白色线段按逆时针连接，播放“通关”音效，屏幕显示“全部完成！获得3颗星～”。

#### 5. **交互控制**
- **单步模式**：点击“单步”按钮，动画走一步；  
- **自动模式**：点击“自动”，动画按滑块速度播放；  
- **AI演示**：点击“AI自动演示”，动画会像“贪吃蛇找食物”一样，自动完成所有步骤；  
- **重置**：点击“重置”，回到初始场景，重新开始。

<visualization_conclusion>
通过这个动画，你不仅能“看”到算法的每一步，还能在游戏中记住关键逻辑——比如“叉积定方向”“面积定距离”！下次遇到类似的问题，你一定能快速回忆起这个过程～
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心思路（叉积定方向、面积定距离、凸包的单峰性质）能解决很多**凸包相关的问题**！以下是几个相似的练习：
</similar_problems_intro>

### **通用思路迁移**
- **场景1**：求凸包的直径（最远点对）——用旋转卡壳找对踵点，类似本题找mx；  
- **场景2**：判断点是否在凸包内——用叉积判断点在所有边的左侧；  
- **场景3**：求凸包的面积——用叉积计算多边形面积，类似本题的面积查询。

### **洛谷练习推荐**
1. **洛谷 P2742** - 【模板】凸包  
   🗣️ **推荐理由**：基础凸包模板题，帮你巩固“找凸包顶点”的核心逻辑！  
2. **洛谷 P1113** - 杂物  
   🗣️ **推荐理由**：用凸包面积解决实际问题，类似本题的“面积查询”！  
3. **洛谷 P3829** - 【模板】旋转卡壳  
   🗣️ **推荐理由**：学习旋转卡壳算法，找凸包的直径，和本题“找mx”的思路一致！  
4. **洛谷 P4166** - [SCOI2007] 最大土地面积  
   🗣️ **推荐理由**：用凸包和旋转卡壳求最大四边形面积，是本题的进阶版！


## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解的作者们分享了很多“踩坑”经验，这些都是“实战秘诀”！
</insights_intro>

> **参考经验（来自Falashiro）**：“我自认为自己代码可读性挺高的。”  
> **点评**：代码的可读性比“写得快”更重要！比如变量名用`se`（下一个点）、`mx`（最远点），而不是`a`、`b`，能让别人（包括未来的自己）一眼看懂你的思路～  

> **参考经验（来自Imakf）**：“这是我CF上做的第一道交互题。”  
> **点评**：交互题的核心是“用查询获取信息”，不要怕“第一次”！只要掌握了“问什么、怎么问”，就能解决大部分交互题～  

> **参考经验（来自Mine_King）**：“感谢凸包之神 djwj223 提供的思路。”  
> **点评**：遇到不会的问题，多参考别人的思路！站在巨人的肩膀上，能更快找到解决方法～


## 结语
本次关于《Point Ordering》的分析就到这里啦！这道题的核心是**利用凸包的性质和交互查询的信息**，把“看不见的点”排成逆时针顺序。记住：叉积是“方向指南针”，面积是“距离测量仪”，凸包的单峰性质是“排序的钥匙”～  

编程的乐趣在于“用逻辑解决问题”，下次遇到新的挑战，不妨想想今天学的思路——你一定能解决！💪

---
处理用时：118.64秒