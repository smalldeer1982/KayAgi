# 题目信息

# Purification

## 题目描述

You are an adventurer currently journeying inside an evil temple. After defeating a couple of weak zombies, you arrived at a square room consisting of tiles forming an $ n×n $ grid. The rows are numbered $ 1 $ through $ n $ from top to bottom, and the columns are numbered $ 1 $ through $ n $ from left to right. At the far side of the room lies a door locked with evil magical forces. The following inscriptions are written on the door:

 The cleaning of all evil will awaken the door!Being a very senior adventurer, you immediately realize what this means. You notice that every single cell in the grid are initially evil. You should purify all of these cells.

The only method of tile purification known to you is by casting the "Purification" spell. You cast this spell on a single tile — then, all cells that are located in the same row and all cells that are located in the same column as the selected tile become purified (including the selected tile)! It is allowed to purify a cell more than once.

You would like to purify all $ n×n $ cells while minimizing the number of times you cast the "Purification" spell. This sounds very easy, but you just noticed that some tiles are particularly more evil than the other tiles. You cannot cast the "Purification" spell on those particularly more evil tiles, not even after they have been purified. They can still be purified if a cell sharing the same row or the same column gets selected by the "Purification" spell.

Please find some way to purify all the cells with the minimum number of spells cast. Print -1 if there is no such way.

## 说明/提示

The first example is illustrated as follows. Purple tiles are evil tiles that have not yet been purified. Red tile is the tile on which "Purification" is cast. Yellow tiles are the tiles being purified as a result of the current "Purification" spell. Green tiles are tiles that have been purified previously.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329A/04b73f6bd6d4f5c1ba16b8072ebad28ccdfa62cc.png)In the second example, it is impossible to purify the cell located at row $ 1 $ and column $ 1 $ .

For the third example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329A/8ffcc7f3e4ed4b4242d89f880e88ffce0ed4e4ab.png)

## 样例 #1

### 输入

```
3
.E.
E.E
.E.
```

### 输出

```
1 1
2 2
3 3
```

## 样例 #2

### 输入

```
3
EEE
E..
E.E
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
EE.EE
E.EE.
E...E
.EE.E
EE.EE
```

### 输出

```
3 3
1 3
2 2
4 4
5 3```

# AI分析结果

# 💡 Kay的C++算法解析：Purification 深入学习指南 💡

<introduction>
今天我们来一起分析“Purification”这道C++编程题。这道题像是一场“网格净化大挑战”——我们需要用最少的“净化法术”覆盖整个n×n的邪恶网格，同时避开那些不能选的“E”点。本指南会帮你理清思路，掌握核心策略，并通过像素动画直观看到算法运行过程！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`贪心策略与覆盖问题`  

🗣️ **初步分析**：  
解决这道题的关键，就像**用“最少的机器人覆盖整个房间”**——每个机器人（净化点）能打扫整行或整列。要覆盖所有区域，最少需要n个机器人（每行或每列1个）。但机器人只能放在非“E”的位置，且如果存在**全是E的行**和**全是E的列**，它们的交点永远无法被打扫（因为没有机器人能覆盖到），此时无解。  

### 核心思路与难点
1. **无解判断**：如果同时存在“全E行”和“全E列”，直接输出-1；  
2. **贪心选择**：如果所有行都有非E点，就每行选一个非E点（覆盖所有行→覆盖所有网格）；如果所有列都有非E点，就每列选一个非E点（同理）；  
3. **最少次数**：无论选行还是列，次数都是n（刚好覆盖所有行/列）。  

### 可视化设计思路
我们会用**8位FC红白机风格**做动画：  
- 网格用像素块表示：`E`是红色（邪恶），`.`是绿色（可选点），已净化的区域是蓝色；  
- 选点时，该点会闪烁，同时其行和列“刷”地变成蓝色，伴随“叮”的音效；  
- 如果无解，屏幕会变红并播放“错误”提示音；  
- 支持“单步执行”和“自动播放”，让你看清每一步选择。  


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性和实践价值等方面，筛选了3份优质题解，帮你快速掌握核心逻辑：
</eval_intro>

**题解一：Nuclear_Fish_cyq（思路清晰，代码规范）**  
* **点评**：这份题解的逻辑像“分两步走的侦探”——先检查所有行是否有可选点（`flagr`数组），再检查所有列（`flagc`数组）。如果行和列都有问题，直接输出-1；否则选行或列的方案。代码用0~n-1的下标（符合编程习惯），输出时加1转成题目要求的1-based坐标，非常严谨。其“每行/列找第一个可选点”的策略，既高效又符合贪心思想。

**题解二：All_Wrong_Answer（无解判断准确，方案全面）**  
* **点评**：这题解的“无解判断”部分很细致——用`f1`和`f2`分别标记是否存在全E行/列，若同时存在则直接退出。之后尝试“每行选点”和“每列选点”两种方案，确保找到可行解。代码中的`exit(0)`让流程更简洁，适合竞赛场景。

**题解三：SpringFullGarden（用数组记录可选点，代码简洁）**  
* **点评**：这份题解的亮点是用`a[i]`记录第i行的第一个可选点列号，`b[j]`记录第j列的第一个可选点行号。判断时只需检查`a`或`b`是否全非空，就能快速确定方案。代码中的`rd()`函数是快速读入模板，适合处理大数据，很实用。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的“拦路虎”主要有3个，结合优质题解的经验，我们逐一破解：
</difficulty_intro>

1. **难点1：如何判断无解？**  
   * **分析**：如果存在某行全是E（没有可选点），且存在某列全是E，那么它们的交点（比如第i行第j列）无法被任何行或列的净化点覆盖——因为该行没有点能净化它的列，该列也没有点能净化它的行。优质题解都会先检查这两个条件，比如Nuclear_Fish_cyq用`flagr`和`flagc`数组标记每行/列是否有可选点。  
   * 💡 **学习笔记**：无解的本质是“存在无法被覆盖的点”，需同时满足“全E行”和“全E列”。

2. **难点2：为什么最少次数是n？**  
   * **分析**：要覆盖所有行和列，最少需要n个点——每行一个点能覆盖所有行（进而覆盖所有列的点），每列一个点同理。比如样例1选了(1,1)、(2,2)、(3,3)，刚好覆盖3行，所有点都被净化。  
   * 💡 **学习笔记**：贪心策略的核心是“用最少的点覆盖最多的区域”，这里每行/列一个点是最优解。

3. **难点3：如何快速找到每行/列的可选点？**  
   * **分析**：遍历每行/列，找到第一个非E的点即可。比如Nuclear_Fish_cyq的代码中，`for(int j=0;j<n;j++) if(a[i][j])`就是找第i行的第一个可选点。这种“贪心选第一个”的策略既高效（O(n²)时间），又能保证正确性。  
   * 💡 **学习笔记**：不需要找“最优”的点，只要找到“存在”的点即可，因为任何非E点都能覆盖整行/列。


### ✨ 解题技巧总结
- **技巧1：预处理行/列状态**：用数组记录每行/列是否有可选点，避免重复判断；  
- **技巧2：优先尝试行方案**：如果行有解，优先选行（代码更直观）；  
- **技巧3：下标转换要注意**：编程时常用0-based下标，但题目要求1-based，输出时要加1；  
- **技巧4：快速退出无效分支**：用`exit(0)`或`break`减少不必要的计算（比如All_Wrong_Answer的代码）。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**综合优质题解的通用实现**，它结合了Nuclear_Fish_cyq的清晰逻辑和SpringFullGarden的简洁记录，帮你快速掌握整体框架：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了多个优质题解的思路，用0-based下标处理，输出时转1-based，逻辑清晰且高效。
* **完整核心代码**：
  ```cpp
  #include <iostream>
  #include <vector>
  using namespace std;

  const int MAXN = 1010;
  bool grid[MAXN][MAXN];  // grid[i][j]为true表示是'.'（可选点）
  bool has_row[MAXN];     // has_row[i]为true表示第i行有可选点
  bool has_col[MAXN];     // has_col[j]为true表示第j列有可选点

  int main() {
      int n;
      cin >> n;
      for (int i = 0; i < n; ++i) {
          string s;
          cin >> s;
          for (int j = 0; j < n; ++j) {
              grid[i][j] = (s[j] == '.');
              has_row[i] = has_row[i] || grid[i][j];
              has_col[j] = has_col[j] || grid[i][j];
          }
      }

      // 判断无解：存在全E行且存在全E列
      bool all_E_row = false, all_E_col = false;
      for (int i = 0; i < n; ++i) all_E_row = all_E_row || !has_row[i];
      for (int j = 0; j < n; ++j) all_E_col = all_E_col || !has_col[j];
      if (all_E_row && all_E_col) {
          cout << -1 << endl;
          return 0;
      }

      // 优先选行方案
      if (!all_E_row) {
          for (int i = 0; i < n; ++i) {
              for (int j = 0; j < n; ++j) {
                  if (grid[i][j]) {
                      cout << i + 1 << " " << j + 1 << endl;
                      break;
                  }
              }
          }
      } else {  // 选列方案
          for (int j = 0; j < n; ++j) {
              for (int i = 0; i < n; ++i) {
                  if (grid[i][j]) {
                      cout << i + 1 << " " << j + 1 << endl;
                      break;
                  }
              }
          }
      }

      return 0;
  }
  ```
* **代码解读概要**：  
  1. **输入处理**：读取网格，用`grid`数组记录每个点是否可选，`has_row`和`has_col`记录每行/列是否有可选点；  
  2. **无解判断**：检查是否存在全E行和全E列；  
  3. **选点输出**：优先选行方案（每行找第一个可选点），否则选列方案（每列找第一个可选点）。


<code_intro_selected>
接下来看优质题解的核心片段，学习它们的巧妙之处：
</code_intro_selected>

**题解一：Nuclear_Fish_cyq（行/列状态判断）**
* **亮点**：用`flagr`和`flagc`数组实时记录行/列状态，避免二次遍历。
* **核心代码片段**：
  ```cpp
  bool flagr[100], flagc[100];
  for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
          a[i][j] = (t == '.');
          flagr[i] = flagr[i] || a[i][j];  // 该行是否有可选点
          flagc[j] = flagc[j] || a[i][j];  // 该列是否有可选点
      }
  }
  ```
* **代码解读**：  
  读取每个点时，立刻更新`flagr[i]`（第i行是否有可选点）和`flagc[j]`（第j列是否有可选点）。这种“边读边处理”的方式节省了时间，避免了读完后再遍历一次行和列。  
* 💡 **学习笔记**：预处理时“实时更新状态”是优化代码效率的常用技巧。

**题解二：All_Wrong_Answer（无解判断）**
* **亮点**：用`f1`和`f2`分别标记全E行/列，逻辑直观。
* **核心代码片段**：
  ```cpp
  int f1=0,f2=0;
  for(int i=1;i<=x;i++){
      for(int j=1;j<=x;j++){
          if(m[i][j]=='.') f1=1;
      }
      if(f1==0){f1=2;break;} 
      f1=0;
  } 
  for(int i=1;i<=x;i++){
      for(int j=1;j<=x;j++){
          if(m[j][i]=='.') f2=1; 
      } 
      if(f2==0){f2=2;break;}
      f2=0;
  }
  if(f1==2&&f2==2){cout<<"-1\n";exit(0);}
  ```
* **代码解读**：  
  遍历每行，若某行没有`.`（`f1`始终为0），则`f1=2`（标记存在全E行）；同理遍历每列。如果`f1=2`且`f2=2`，直接输出-1并退出。这种“标记变量”的方式让无解判断更清晰。  
* 💡 **学习笔记**：用不同的值标记状态（比如0=未检查，1=有可选点，2=全E），能避免逻辑混乱。

**题解三：SpringFullGarden（记录可选点位置）**
* **亮点**：用`a[i]`和`b[j]`直接记录每行/列的可选点位置，输出时不用再遍历。
* **核心代码片段**：
  ```cpp
  int a[105], b[105];  // a[i]是第i行的可选点列号，b[j]是第j列的可选点行号
  for(int i = 1; i <= n; i++) {
      string s; cin >> s;
      for(int j = 0; j < n; j++) 
          if(s[j] == '.') mp[i][j + 1] = 1, a[i] = j + 1, b[j + 1] = i;
  }
  ```
* **代码解读**：  
  读取每行时，若遇到`.`，立刻记录`a[i]`（第i行的可选点列号）和`b[j+1]`（第j+1列的可选点行号）。输出时直接用`a[i]`或`b[j]`，不用再遍历找可选点，节省了时间。  
* 💡 **学习笔记**：预处理时记录关键信息，能让后续代码更简洁。


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你“亲眼看到”净化过程，我设计了一个**FC红白机风格的像素动画**，像玩《超级马里奥》一样学算法！
</visualization_intro>

### 动画基本信息
- **主题**：像素探险家净化邪恶网格（致敬《塞尔达传说》的 dungeon 探索）；  
- **风格**：8位像素风（16色调色板，仿FC游戏画面）；  
- **音效**：8位芯片音乐（BGM：轻松的冒险曲；选点时“叮”；无解时“嗡”；净化完成时“啾”）。

### 动画帧步骤与交互设计
1. **初始化场景**：  
   - 屏幕显示n×n的像素网格，`E`是红色（邪恶），`.`是绿色（可选点）；  
   - 底部控制面板有“开始”“单步”“自动”“重置”按钮，以及速度滑块（1x~5x）；  
   - 左侧显示当前选中的方案（“行模式”或“列模式”）。

2. **无解演示**：  
   - 如果存在全E行和全E列，网格会整体变红，顶部弹出“无法净化！”的像素文字，伴随“嗡”的音效；  
   - 点击“重置”可重新开始。

3. **行模式净化**：  
   - 第1步：选中第1行的第一个绿色点（比如(1,1)），该点闪烁3次，伴随“叮”的音效；  
   - 第2步：该点的行和列“刷”地变成蓝色（已净化），屏幕左侧显示“净化第1行+第1列！”；  
   - 第3步：依次处理第2行、第3行……直到所有行都选完；  
   - 完成时，整个网格变成蓝色，顶部弹出“净化成功！”，伴随“啾”的音效和像素烟花动画。

4. **列模式净化**：  
   - 类似行模式，但按列选点，比如先选第1列的第一个绿色点，再选第2列……

### 交互与游戏化元素
- **单步模式**：点击“单步”按钮，每一步都暂停，让你仔细看选点和净化过程；  
- **自动模式**：点击“自动”，算法会按速度滑块的速度自动执行，像“AI探险家”一样完成净化；  
- **积分奖励**：每选对一个点，获得10分；完成所有选点，获得“净化大师”称号（像素奖牌动画）。


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
这道题的**贪心覆盖策略**能解决很多类似问题，比如“用最少的灯照亮所有房间”“用最少的监控覆盖所有道路”。以下是几道洛谷的拓展练习：
</similar_problems_intro>

### 通用思路迁移
- **场景1**：用最少的路由器覆盖所有房间（每个路由器覆盖整层楼）；  
- **场景2**：用最少的监控摄像头覆盖所有道路（每个摄像头覆盖整条街）；  
- **场景3**：用最少的油漆桶刷完所有墙面（每个油漆桶刷整行或整列）。

### 洛谷练习推荐
1. **洛谷 P1090 合并果子**  
   - 🗣️ **推荐理由**：这是贪心算法的经典题，需要用最少的次数合并果子，锻炼“选最优解”的思维，和本题的“选最少点”思路一致。  
2. **洛谷 P1251 餐巾计划问题**  
   - 🗣️ **推荐理由**：这道题需要用贪心+动态规划解决“最少成本购买餐巾”的问题，能帮你巩固“贪心策略结合其他算法”的能力。  
3. **洛谷 P2089 烤鸡**  
   - 🗣️ **推荐理由**：这道题需要用枚举+贪心找到所有可能的烤鸡配方，锻炼“遍历所有可能性”的能力，和本题的“遍历行/列找可选点”思路类似。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解中的“小技巧”能帮我们少走弯路，比如：
</insights_intro>

> **参考经验（来自Nuclear_Fish_cyq）**：“我习惯用0~n-1的下标，所以输出时要加1转成题目要求的1-based坐标。”  
> **点评**：很多初学者会在“下标转换”上出错（比如把0-based的i直接输出成i），这位作者的经验提醒我们：**编程习惯要和题目要求对应**，输出前一定要检查下标是否正确。

> **参考经验（来自All_Wrong_Answer）**：“用exit(0)可以快速退出无效分支，避免不必要的计算。”  
> **点评**：在竞赛中，时间很宝贵，用`exit(0)`或`return`快速终止无效流程，能节省时间，也让代码更简洁。


<conclusion>
本次关于“Purification”的分析就到这里！这道题的核心是**贪心覆盖策略**——用最少的点覆盖最多的区域。记住：判断无解的条件、优先选行/列的策略、下标转换的细节，这些都是解题的关键。下次遇到类似的“覆盖问题”，不妨想想今天的思路，相信你能快速解决！💪
</conclusion>

---
处理用时：263.05秒