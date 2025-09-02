# 题目信息

# Quarrel

## 题目描述

Friends Alex and Bob live in Bertown. In this town there are $ n $ crossroads, some of them are connected by bidirectional roads of equal length. Bob lives in a house at the crossroads number $ 1 $ , Alex — in a house at the crossroads number $ n $ .

One day Alex and Bob had a big quarrel, and they refused to see each other. It occurred that today Bob needs to get from his house to the crossroads $ n $ and Alex needs to get from his house to the crossroads $ 1 $ . And they don't want to meet at any of the crossroads, but they can meet in the middle of the street, when passing it in opposite directions. Alex and Bob asked you, as their mutual friend, to help them with this difficult task.

Find for Alex and Bob such routes with equal number of streets that the guys can follow these routes and never appear at the same crossroads at the same time. They are allowed to meet in the middle of the street when moving toward each other (see Sample 1). Among all possible routes, select such that the number of streets in it is the least possible. Until both guys reach their destinations, none of them can stay without moving.

The guys are moving simultaneously with equal speeds, i.e. it is possible that when one of them reaches some of the crossroads, the other one leaves it. For example, Alex can move from crossroad $ 1 $ to crossroad $ 2 $ , while Bob moves from crossroad $ 2 $ to crossroad $ 3 $ .

If the required routes don't exist, your program should output -1.

## 样例 #1

### 输入

```
2 1
1 2
```

### 输出

```
1
1 2 
2 1 
```

## 样例 #2

### 输入

```
7 5
1 2
2 7
7 6
2 3
3 4
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7 6
1 2
2 7
7 6
2 3
3 4
1 5
```

### 输出

```
6
1 2 3 4 3 2 7 
7 6 7 2 1 5 1 
```

# AI分析结果

# 💡 Kay的C++算法解析：Quarrel 深入学习指南 💡

<introduction>
今天我们来一起分析「Quarrel」这道有趣的C++编程题。题目里Alex和Bob闹别扭了，却不得不互相走对方的路线——Bob要从1到n，Alex要从n到1，还不能在同一时间出现在同一个路口。我们的任务是帮他们找到**最短且长度相同**的路线。这道题会用到一个经典的算法思想，跟着Kay一起拆解问题吧！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：**BFS（广度优先搜索）的状态扩展**  

🗣️ **初步分析**：  
解决这道题的关键，在于把「两个人的同步移动」转化为**状态的搜索**。想象一下：我们需要同时跟踪Alex和Bob的位置，以及「当前轮到谁走下一步」——这三个信息组合起来就是一个**状态节点**（比如「Alex在A点，Bob在B点，接下来轮到Alex移动」）。而BFS擅长处理这种**无权图的最短路径问题**（每一步的代价都是1），因为它能按「步骤顺序」逐层扩展状态，第一个到达终点的状态就是最短解。  

- **题解思路**：所有题解的核心都是「状态BFS」——把（Alex位置, Bob位置, 移动阶段）作为BFS的节点，每次扩展时根据当前阶段让对应的人移动（Alex先走或Bob先走），同时保证Bob移动后不与Alex当前位置重合。  
- **核心难点**：如何定义状态、处理移动的同步性、记录路径并回溯。  
- **可视化设计思路**：我们会用像素动画展示两人的移动——比如用红色像素块代表Alex，蓝色代表Bob，每个状态节点用网格中的两个色块表示。动画会高亮当前移动的人（比如红色闪烁表示Alex要走），并用箭头显示下一步的方向，同时弹出文字提示「Alex从1走到2啦！」。  
- **游戏化元素**：加入「步数进度条」（像FC游戏的关卡进度），每完成一步播放「叮」的像素音效；到达终点时播放胜利旋律，同时屏幕弹出「任务完成！」的像素字。


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性和实践价值三个维度筛选了以下优质题解，它们都准确抓住了「状态BFS」的核心，值得大家学习～
</eval_intro>

**题解一：(来源：xh39)**  
* **点评**：这份题解的思路非常「纯粹」——直接把两人的状态（位置+谁先走）作为BFS节点，用结构体`IOI2020_lianjieqingtianshu`记录每个状态的位置、距离、父节点和移动阶段。状态转移时，严格区分「Alex先走」（Alex移动，Bob不动）和「Bob先走」（Bob移动，且不能到Alex当前位置）两种情况，逻辑严谨。代码中用`marka`和`markb`数组标记已访问的状态，避免重复搜索，效率很高。最值得学习的是**路径记录**：用`fa`字段回溯父状态，最后反转输出路径，完美解决了「从终点到起点」的记录问题。

**题解二：(来源：C6H14)**  
* **点评**：这道题解的思路和题解一一致，但用了更简洁的状态表示——用`f[x][y][0/1]`记录（Alex在x，Bob在y，当前轮到谁走）的父状态。代码中用队列同时存储两人的位置和移动阶段，逻辑清晰。美中不足的是输入输出部分用了自定义的`read`/`write`函数（可能是为了速度），对新手来说 slightly 不友好，但核心的BFS逻辑完全没问题～


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题时，大家最容易卡壳的地方往往是「如何把两个人的移动结合起来」。结合优质题解的共性，Kay帮大家提炼了三个核心关键点：
</difficulty_intro>

1.  **关键点1：如何定义「状态」？**  
    * **分析**：状态必须包含「Alex的位置」「Bob的位置」和「当前轮到谁走」——这三个信息才能唯一确定下一步的可能。比如状态`(a, b, 1)`表示「Alex在a，Bob在b，接下来轮到Alex移动」；状态`(a, b, 0)`表示「接下来轮到Bob移动」。优质题解都用结构体或三维数组存储这些信息，确保不遗漏任何细节。  
    * 💡 **学习笔记**：状态定义是BFS的「基石」，要覆盖所有影响下一步的因素！

2.  **关键点2：Bob移动的条件是什么？**  
    * **分析**：题目规定「两人不能同时在同一路口」，所以当轮到Bob移动时，他不能走到Alex**当前的位置**（注意：Alex此时还没动！）。比如Alex在a，Bob在b，轮到Bob走时，Bob只能走到与b相邻且不等于a的节点。题解中用`_[i].v != list[l].va`（题解一）或`x == v`（题解二）来判断这个条件，非常严谨。  
    * 💡 **学习笔记**：条件判断要「抠题目细节」，不能漏看任何限制！

3.  **关键点3：如何记录并输出路径？**  
    * **分析**：BFS的路径记录需要「从终点回溯到起点」——因为BFS是按步骤扩展的，终点的父节点是上一步的状态，以此类推直到起点。比如题解一中用`list[i].fa`存储父状态的索引，最后从终点`l`开始，依次访问`fa`直到`-1`，再反转输出路径（因为回溯是从终点到起点）。  
    * 💡 **学习笔记**：路径记录的核心是「父指针」，回溯后别忘反转！


### ✨ 解题技巧总结
- **技巧A：状态压缩**：把多个变量（如两人位置、移动阶段）合并成一个状态，用结构体或多维数组存储，这是处理「多主体同步问题」的常用技巧。  
- **技巧B：标记已访问**：用二维数组（如`marka[a][b]`）标记「Alex在a，Bob在b，轮到Alex走」的状态已被访问，避免重复搜索，降低时间复杂度。  
- **技巧C：路径回溯**：用「父指针」记录每个状态的来源，最后从终点倒推到起点，再反转输出，这是BFS路径记录的标准做法。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**综合优质题解的通用核心实现**——它整合了题解一的状态结构体和题解二的简洁逻辑，适合新手理解～
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码基于题解一的思路优化，用结构体存储状态，BFS扩展，路径回溯清晰，适合入门学习。
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 1005;
vector<int> adj[MAXN];  // 邻接表存图
struct State {
    int a, b;           // Alex的位置a，Bob的位置b
    int dis;            // 当前步数（Alex和Bob各走一步算1步）
    int fa;             // 父状态的索引
    bool alex_turn;     // 是否轮到Alex走（true=Alex先走，false=Bob先走）
} q[MAXN * MAXN * 2];   // 状态队列（足够大的空间）

bool visited_a[MAXN][MAXN];  // 标记Alex先走时的状态(a,b)是否已访问
bool visited_b[MAXN][MAXN];  // 标记Bob先走时的状态(a,b)是否已访问
int path_a[MAXN * 2], path_b[MAXN * 2];  // 存储最终路径（a是Alex的路径，b是Bob的）
int path_len = 0;

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 初始化队列：起点是Alex在1，Bob在n，轮到Alex先走（dis=0）
    int front = 0, rear = 1;
    q[0] = {1, n, 0, -1, true};
    visited_a[1][n] = true;

    while (front < rear) {
        State curr = q[front];
        // 终止条件：Alex到达n，Bob到达1，且当前是Alex先走（说明两人都走完了）
        if (curr.a == n && curr.b == 1 && curr.alex_turn) {
            cout << curr.dis << endl;
            // 回溯路径：从当前状态倒推到起点
            for (int i = front; i != -1; i = q[i].fa) {
                if (q[i].alex_turn) {  // 只有Alex先走的状态才是完整的一步（两人各走了一次）
                    path_a[path_len] = q[i].a;
                    path_b[path_len] = q[i].b;
                    path_len++;
                }
            }
            // 输出路径（回溯是倒序，所以要反转）
            for (int i = path_len - 1; i >= 0; --i) {
                cout << path_a[i] << " ";
            }
            cout << endl;
            for (int i = path_len - 1; i >= 0; --i) {
                cout << path_b[i] << " ";
            }
            cout << endl;
            return 0;
        }

        // 扩展状态
        if (curr.alex_turn) {
            // Alex先走：Alex移动到相邻节点，Bob不动，切换到Bob先走
            for (int next_a : adj[curr.a]) {
                if (!visited_a[next_a][curr.b]) {
                    visited_a[next_a][curr.b] = true;
                    q[rear] = {next_a, curr.b, curr.dis, front, false};
                    rear++;
                }
            }
        } else {
            // Bob先走：Bob移动到相邻节点，且不能等于Alex当前的位置（curr.a）
            for (int next_b : adj[curr.b]) {
                if (next_b != curr.a && !visited_b[curr.a][next_b]) {
                    visited_b[curr.a][next_b] = true;
                    q[rear] = {curr.a, next_b, curr.dis + 1, front, true};
                    rear++;
                }
            }
        }
        front++;
    }

    // 没有找到路径
    cout << -1 << endl;
    return 0;
}
```
* **代码解读概要**：  
  1. **图的存储**：用邻接表`adj`存储道路（因为n可以达到1000，邻接表更高效）。  
  2. **状态队列**：用结构体`State`存储每个状态的关键信息，队列`q`按BFS顺序扩展。  
  3. **状态扩展**：  
     - 当`alex_turn`为`true`时，Alex移动到相邻节点，Bob不动，切换到Bob先走（`alex_turn=false`）。  
     - 当`alex_turn`为`false`时，Bob移动到相邻节点（不能等于Alex当前位置），切换到Alex先走，同时步数加1（因为两人各走了一次）。  
  4. **路径回溯**：找到终点状态后，通过`fa`字段倒推父状态，存储路径后反转输出。


---
<code_intro_selected>
接下来看题解一中的**核心状态扩展片段**，它完美体现了「同步移动」的逻辑～
</code_intro_selected>

**题解一：(来源：xh39)**
* **亮点**：用`firsta`字段明确区分「Alex先走」和「Bob先走」，状态转移逻辑清晰。
* **核心代码片段**：
```cpp
if(list[l].firsta){
    // Alex先走：遍历Alex的相邻节点
    for(i=head[list[l].va];i;i=_[i].next){
        if(!marka[_[i].v][list[l].vb]){
            marka[_[i].v][list[l].vb]=1;
            list[r].dis=list[l].dis+1;
            list[r].va=_[i].v;  // Alex移动到新位置
            list[r].vb=list[l].vb;  // Bob不动
            list[r].firsta=0;  // 切换到Bob先走
            list[r].fa=l;  // 记录父状态
            r++;
        }
    }
}else{
    // Bob先走：遍历Bob的相邻节点，且不能等于Alex当前位置
    for(i=head[list[l].vb];i;i=_[i].next){
        if(!markb[list[l].va][_[i].v]&&_[i].v!=list[l].va){
            markb[list[l].va][_[i].v]=1;
            list[r].dis=list[l].dis+1;
            list[r].va=list[l].va;  // Alex不动
            list[r].vb=_[i].v;  // Bob移动到新位置
            list[r].firsta=1;  // 切换到Alex先走
            list[r].fa=l;  // 记录父状态
            r++;
        }
    }
}
```
* **代码解读**：  
  这段代码是BFS的「核心扩展逻辑」——  
  - 当`firsta`为`true`（Alex先走）：Alex从当前位置`list[l].va`移动到相邻节点`_[i].v`，Bob的位置`list[l].vb`不变，然后把`firsta`设为`0`（下一轮Bob走）。  
  - 当`firsta`为`false`（Bob先走）：Bob从当前位置`list[l].vb`移动到相邻节点`_[i].v`，但必须满足`_[i].v != list[l].va`（不能和Alex当前位置重合），然后把`firsta`设为`1`（下一轮Alex走）。  
  每一步都用`marka`或`markb`标记已访问的状态，避免重复搜索。
* 💡 **学习笔记**：状态转移的关键是「明确谁在走，走后切换阶段」，不要混淆两人的移动顺序！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让大家更直观地「看」到两人的移动，Kay设计了一个**8位像素风的动画**——像玩FC游戏一样，跟着Alex和Bob一起走路线！
</visualization_intro>

### 动画设计方案
#### **1. 整体风格**  
- **8位像素风**：参考《超级马里奥兄弟》的配色（红、蓝、黄为主），用16x16的像素块表示路口（节点），用2x2的像素块表示道路（边）。  
- **UI布局**：  
  - 左侧是「地图区域」：显示所有路口和道路，Alex用红色像素块（带白色帽子），Bob用蓝色像素块（带黄色帽子）。  
  - 右侧是「控制面板」：有「开始/暂停」「单步执行」「重置」按钮，以及「速度滑块」（从「慢」到「快」）。  
  - 底部是「信息栏」：显示当前步数、Alex的位置、Bob的位置，以及文字提示（如「Alex要从1走到2啦！」）。


#### **2. 核心动画流程**
以**样例1**（输入：2 1，道路1-2）为例，展示关键帧：  
1. **初始化**：  
   - 地图显示两个路口（1号在左，2号在右），道路连接它们。  
   - Alex在1号（红色），Bob在2号（蓝色）。  
   - 信息栏显示：「步数：0，Alex在1，Bob在2」。  
   - 播放8位风格的背景音乐（轻快的钢琴旋律）。

2. **第一步：Alex先走**：  
   - 红色像素块（Alex）闪烁3次，伴随「叮」的音效。  
   - Alex从1号移动到2号（红色块滑向右侧的2号路口）。  
   - 信息栏更新：「Alex走到了2号！接下来轮到Bob走～」。  
   - 状态变为（Alex在2，Bob在2，Bob先走）？不——等一下，样例1中Bob要从2走到1，所以下一步Bob移动：  
   - 蓝色像素块（Bob）闪烁3次，伴随「叮」的音效。  
   - Bob从2号移动到1号（蓝色块滑向左侧的1号路口）。  
   - 信息栏更新：「Bob走到了1号！两人都到达终点～」。  

3. **终点状态**：  
   - 播放胜利音效（上扬的8位音符），屏幕中央弹出像素字「任务完成！」。  
   - 地图上用绿色框高亮Alex的路径（1→2）和Bob的路径（2→1）。  


#### **3. 交互设计**
- **单步执行**：点击「单步」按钮，动画只走一步，方便观察每一步的状态变化。  
- **自动播放**：拖动「速度滑块」可以调整播放速度（最慢1秒/步，最快0.1秒/步）。  
- **重置动画**：点击「重置」按钮，回到初始状态，重新开始演示。  


#### **4. 技术实现小细节**
- **Canvas绘制**：用HTML5的Canvas绘制像素块——比如`ctx.fillStyle = "#FF0000"; ctx.fillRect(x*16, y*16, 16, 16)`绘制红色的Alex。  
- **音效触发**：用Web Audio API播放8位音效——比如「叮」的音效是频率440Hz的正弦波，持续100ms。  
- **状态同步**：动画的每一步都对应代码中的`State`结构体，比如「Alex在a，Bob在b，轮到谁走」会同步显示在信息栏。  


<visualization_conclusion>
通过这个像素动画，大家可以清楚地看到「状态是如何扩展的」——Alex和Bob轮流移动，每一步都不重叠，直到到达终点。是不是比看代码更直观？😉
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
「状态BFS」的思路不仅能解决这道题，还能处理很多「多主体同步移动」的问题。比如：
</similar_problems_intro>

### **通用思路迁移**
- **场景1**：两个机器人在网格中移动，不能碰撞，求最短路径。  
- **场景2**：两人轮流取石子，求必胜策略（本质是状态的扩展）。  
- **场景3**：迷宫中两个人同时出发，求相遇的最短时间。  


### **洛谷练习推荐**
1. **洛谷 P1141** - 01迷宫  
   🗣️ **推荐理由**：这道题需要用BFS处理「翻转01」的状态，锻炼「状态扩展」的能力。  
2. **洛谷 P1379** - 八数码问题  
   🗣️ **推荐理由**：经典的「状态BFS」问题，需要把棋盘状态压缩成字符串，练习状态的表示和记录。  
3. **洛谷 P2921** - [USACO08DEC]Patting Heads S  
   🗣️ **推荐理由**：虽然是数论问题，但需要用「状态标记」避免重复计算，锻炼「剪枝」的思维。  


## 7. 学习心得与经验分享 (若有)

<insights_intro>
题解一中的作者提到「不可以不看暴力」，这让Kay很有感触——很多复杂的算法都是从暴力优化来的！
</insights_intro>

> **参考经验 (来自 xh39)**：「暴力是O(n⁴)，把两人同时走一步拆成Alex先走、Bob再走，就优化到了O(n³)。」  
> **点评**：这位作者的经验告诉我们——**暴力思路是优化的起点**。比如这道题，暴力是同时枚举两人的下一步，但拆分成「轮流走」后，状态数从n⁴降到了n³，效率提升了一个量级。以后遇到复杂问题，先想暴力解法，再找优化点！


<conclusion>
本次关于「Quarrel」的分析就到这里啦！这道题的核心是「把两人的状态结合起来BFS」——只要想通这一点，剩下的就是代码实现和细节处理。记住：编程的乐趣在于「拆解问题」，把大问题拆成小步骤，再一步步解决～  

下次我们再一起探索新的算法挑战！💪
</conclusion>

---
处理用时：119.36秒