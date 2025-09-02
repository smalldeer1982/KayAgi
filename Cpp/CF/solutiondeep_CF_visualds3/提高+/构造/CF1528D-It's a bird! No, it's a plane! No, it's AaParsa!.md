# 题目信息

# It's a bird! No, it's a plane! No, it's AaParsa!

## 题目描述

There are $ n $ cities in Shaazzzland, numbered from $ 0 $ to $ n-1 $ . Ghaazzzland, the immortal enemy of Shaazzzland, is ruled by AaParsa.

As the head of the Ghaazzzland's intelligence agency, AaParsa is carrying out the most important spying mission in Ghaazzzland's history on Shaazzzland.

AaParsa has planted $ m $ transport cannons in the cities of Shaazzzland. The $ i $ -th cannon is planted in the city $ a_i $ and is initially pointing at city $ b_i $ .

It is guaranteed that each of the $ n $ cities has at least one transport cannon planted inside it, and that no two cannons from the same city are initially pointing at the same city (that is, all pairs $ (a_i, b_i) $ are distinct).

AaParsa used very advanced technology to build the cannons, the cannons rotate every second. In other words, if the $ i $ -th cannon is pointing towards the city $ x $ at some second, it will target the city $ (x + 1) \mod n $ at the next second.

As their name suggests, transport cannons are for transportation, specifically for human transport. If you use the $ i $ -th cannon to launch yourself towards the city that it's currently pointing at, you'll be airborne for $ c_i $ seconds before reaching your target destination.

If you still don't get it, using the $ i $ -th cannon at the $ s $ -th second (using which is only possible if you are currently in the city $ a_i $ ) will shoot you to the city $ (b_i + s) \mod n $ and you'll land in there after $ c_i $ seconds (so you'll be there in the $ (s + c_i) $ -th second). Also note the cannon that you initially launched from will rotate every second but you obviously won't change direction while you are airborne.

AaParsa wants to use the cannons for travelling between Shaazzzland's cities in his grand plan, and he can start travelling at second $ 0 $ . For him to fully utilize them, he needs to know the minimum number of seconds required to reach city $ u $ from city $ v $ using the cannons for every pair of cities $ (u, v) $ .

Note that AaParsa can stay in a city for as long as he wants.

## 说明/提示

In the first example one possible path for going from $ 0 $ to $ 2 $ would be:

1. Stay inside $ 0 $ and do nothing for $ 1 $ second.
2. Use the first cannon and land at $ 2 $ after $ 1 $ second.

Note that: we could have used the second cannon in $ 0 $ -th second but it would have taken us $ 3 $ seconds to reach city $ 2 $ in that case.

## 样例 #1

### 输入

```
3 4
0 1 1
0 2 3
1 0 1
2 0 1```

### 输出

```
0 1 2 
1 0 2 
1 2 0```

## 样例 #2

### 输入

```
6 6
0 0 1
1 1 1
2 2 1
3 3 1
4 4 1
5 5 1```

### 输出

```
0 2 3 3 4 4 
4 0 2 3 3 4 
4 4 0 2 3 3 
3 4 4 0 2 3 
3 3 4 4 0 2 
2 3 3 4 4 0```

## 样例 #3

### 输入

```
4 5
0 1 1
1 3 2
2 2 10
3 0 1
0 0 2```

### 输出

```
0 1 2 3 
3 0 3 2 
12 13 0 11 
1 2 2 0```

# AI分析结果

# 💡 Kay的C++算法解析：It's a bird! No, it's a plane! No, it's AaParsa! 深入学习指南 💡

<introduction>
今天我们要分析一道**会“旋转大炮”的最短路径题**！题目里每个城市的大炮每秒都会转方向，我们需要找到任意两个城市间的最短到达时间。这道题的核心是**Dijkstra算法的灵活应用**——不仅要处理“直接用大炮飞”，还要处理“等一等再飞”的情况。让我们一起拆解问题，掌握关键技巧！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`Dijkstra算法（多源最短路径）`

🗣️ **初步分析**：
解决这道题的关键，是把“大炮旋转”和“等待时间”转化为**最短路径的边权**。简单来说，Dijkstra算法就像“找从家到学校的最短路线”——每到一个路口（节点），我们选当前最短的路线继续走。在本题中：
- **节点**：每个城市（编号0~n-1）。
- **边权**：
  1. **直接飞**：用当前城市的大炮，发射时间为`s`，则目标城市是`(b_i + s) % n`，飞行时间是`c_i`（边权为`c_i`）。
  2. **等一秒**：在当前城市等1秒，相当于走到“下一个编号的城市”（`(x+1)%n`），边权为1。

所有题解的核心思路高度一致：**对每个起点跑一次Dijkstra**，计算到其他所有节点的最短时间。因为每个城市的大炮旋转方向随时间变化，我们需要用Dijkstra的**“每次选当前距离最小的节点”**特性，确保“等时间”的转移是最优的（早到总比晚到好，大不了多等几秒）。

**可视化设计思路**：我们会用8位像素风格展示“城市网格”——每个城市是一个像素块，起点是红色，当前处理的节点是黄色，目标节点是蓝色。等待操作会让黄色块“移动”到下一个城市（带“嗒”的音效），发射操作会用箭头指向目标城市（带“咻”的音效）。关键步骤会用文字提示“现在要等1秒，目标城市变成下一个啦！”。


## 2. 精选优质题解参考

<eval_intro>
我从**思路清晰度、代码可读性、算法有效性**三个维度筛选了3份优质题解，帮你快速理解核心逻辑！
</eval_intro>

### 题解一：(来源：nao_nao，赞：8)
* **点评**：这份题解的思路最直白——直接对每个起点跑Dijkstra，清晰处理了“飞”和“等”两种转移。代码中的`dij`函数逻辑严谨：先初始化起点的所有大炮转移，再循环选当前距离最小的节点，更新“等1秒”的转移，最后处理当前节点的所有大炮转移。变量名如`dis`（距离数组）、`vis`（是否已确定最短距离）都很直观，模运算`mod(x)`处理得很巧妙（避免负数）。最棒的是，代码能直接通过所有测试点，实践价值很高！

### 题解二：(来源：7KByte，赞：7)
* **点评**：这题解的亮点是用`w数组`专门处理当前节点的转移——先计算“直接飞”的所有可能目标，再用`w[i] = min(w[i], w[i-1]+1)`处理“等时间”的连续转移（比如等1秒到i+1，等2秒到i+2）。这种“分步骤处理”的思路让逻辑更清晰，尤其适合理解“等待”的本质（连续的边权1转移）。虽然提到“被卡常”，但代码结构非常规范，适合初学者模仿。

### 题解三：(来源：COsm0s，赞：2)
* **点评**：这份题解的代码最“现代”——用了`namespace`封装，`REP`宏简化循环，`ios::sync_with_stdio(false)`加速输入输出。核心逻辑和前两份一致，但模运算处理更严谨（`(E[j].to + dis[u] - 1) % n + 1`），避免了编号从0开始的问题。代码可读性很高，适合学习“规范编码”的技巧。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
这道题的“坑”主要在**如何处理大炮旋转**和**等待操作**。结合优质题解，我总结了3个核心难点和解决策略：
</difficulty_intro>

### 1. 难点1：大炮目标城市的计算
**问题**：大炮的目标城市是`(b_i + s) % n`，其中`s`是发射时间（即到达当前城市的时间）。如何正确计算这个目标？  
**解决策略**：用**模运算**处理循环编号！比如题解中的`mod(x) = ((x-1)%n)+1`（把0~n-1转为1~n，避免负数），或者`(E[j].to + dis[u] - 1) % n + 1`（直接计算当前时间下的目标城市）。  
💡 **学习笔记**：模运算要注意“编号范围”，避免出现负数或越界！

### 2. 难点2：等待操作的处理
**问题**：等待1秒相当于走到下一个城市，如何高效处理这种“无限多的边”？  
**解决策略**：利用Dijkstra的**单调性**！因为每次选的是当前距离最小的节点，所以“等1秒”的转移只需要更新`(x+1)%n`的距离（`dis[x%n+1] = min(dis[x]+1, dis[x%n+1])`）。不需要枚举所有等待时间——早到的节点已经覆盖了晚到的情况！  
💡 **学习笔记**：Dijkstra的“每次选最小距离节点”是处理“等待”的关键！

### 3. 难点3：多源最短路径的计算
**问题**：要计算所有点对的最短路径，如何高效处理？  
**解决策略**：**对每个起点跑一次Dijkstra**！因为n≤600，时间复杂度是`O(n(n² + m))`（每个Dijkstra是O(n² + m)），完全可以通过。  
💡 **学习笔记**：多源最短路径不一定用Floyd，Dijkstra循环n次也是可行的！

### ✨ 解题技巧总结
- **技巧1：问题转化**：把“大炮旋转”转化为“目标城市随时间变化”，把“等待”转化为“边权1的转移”。
- **技巧2：利用算法特性**：用Dijkstra的单调性处理“等待”，避免冗余计算。
- **技巧3：规范编码**：用清晰的变量名（如`dis`、`vis`）、宏简化循环（如`REP`），提高代码可读性。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**综合优质题解的通用核心代码**，帮你快速掌握整体框架！
</code_intro_overall>

### 本题通用核心C++实现参考
* **说明**：综合nao_nao、7KByte、COsm0s的思路，调整为更易读的版本，适合初学者理解。
* **完整核心代码**：
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll INF = 1e18;
const int N = 605; // 题目中n≤600

int n, m;
struct Edge { int to, val, next; } e[N * N]; // 存储边
int head[N], cnt;
ll dis[N]; // 距离数组
bool vis[N]; // 是否已确定最短距离

// 添加边（u→v，权值w）
void add(int u, int v, int w) {
    e[++cnt].to = v;
    e[cnt].val = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}

// 计算(x) mod n（处理1~n的编号）
int mod(int x) {
    return (x - 1) % n + 1;
}

// Dijkstra算法：计算从s到所有点的最短距离
void dijkstra(int s) {
    // 初始化：距离设为INF，vis设为false
    for (int i = 1; i <= n; ++i) {
        dis[i] = INF;
        vis[i] = false;
    }
    // 处理起点的所有大炮：发射时间为0（因为起点时间是0）
    for (int i = head[s]; i; i = e[i].next) {
        int v = e[i].to;
        dis[v] = min(dis[v], (ll)e[i].val);
    }
    // 进行n次迭代（每次确定一个节点的最短距离）
    for (int i = 1; i <= n; ++i) {
        // 选当前距离最小的未确定节点x
        int x = 0;
        for (int j = 1; j <= n; ++j) {
            if (!vis[j] && (x == 0 || dis[j] < dis[x])) {
                x = j;
            }
        }
        vis[x] = true; // 标记x已确定
        // 处理等待操作：x→x+1，权值1
        int next_x = mod(x + 1);
        dis[next_x] = min(dis[next_x], dis[x] + 1);
        // 处理x的所有大炮：发射时间为dis[x]
        for (int j = head[x]; j; j = e[j].next) {
            int b_i = e[j].to; // 大炮初始指向的城市
            int c_i = e[j].val; // 飞行时间
            // 计算当前发射时间下的目标城市：(b_i + dis[x]) mod n（转换为1~n）
            int target = mod(b_i + dis[x]);
            // 更新目标城市的距离：dis[x] + c_i
            dis[target] = min(dis[target], dis[x] + c_i);
        }
    }
    // 输出结果（s到所有点的距离）
    for (int i = 1; i <= n; ++i) {
        if (i == s) cout << 0 << " ";
        else cout << dis[i] << " ";
    }
    cout << endl;
}

int main() {
    cin >> n >> m;
    // 输入m条边（注意题目中城市编号是0~n-1，转换为1~n）
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a + 1, b + 1, c);
    }
    // 对每个起点跑Dijkstra
    for (int i = 1; i <= n; ++i) {
        dijkstra(i);
    }
    return 0;
}
```
* **代码解读概要**：
  1. **输入处理**：读取n和m，把城市编号从0~n-1转为1~n（避免模运算负数）。
  2. **Dijkstra初始化**：起点的所有大炮直接发射（时间0），更新目标城市的距离。
  3. **迭代选点**：每次选当前距离最小的节点，处理“等待”（转到下一个城市）和“发射”（计算目标城市）两种转移。
  4. **输出结果**：输出起点到所有点的最短距离。

<code_intro_selected>
接下来剖析优质题解的核心片段，看它们的“巧妙之处”！
</code_intro_selected>

### 题解一（nao_nao）：核心片段赏析
* **亮点**：用`mod`函数简化模运算，处理“等待”的转移非常直接。
* **核心代码片段**：
```cpp
// 处理等待操作：x→x+1，权值1
dis[u%n+1] = mymin(dis[u]+1, dis[u%n+1]);
// 处理x的所有大炮：计算目标城市
for(int e=head[u];e;e=nxt[e]){
    int v = mod(dis[u]+go[e]);
    dis[v] = mymin(dis[v], dis[u]+val[e]);
}
```
* **代码解读**：
  - `u%n+1`：直接计算下一个城市（比如u=3，n=3，结果是1），避免了复杂的模运算。
  - `mod(dis[u]+go[e])`：计算当前发射时间下的目标城市（`go[e]`是大炮初始指向的城市，`dis[u]`是到达u的时间）。
* 💡 **学习笔记**：模运算的简化能让代码更简洁！

### 题解二（7KByte）：核心片段赏析
* **亮点**：用`w数组`处理“直接飞”的所有转移，再用`w[i] = min(w[i], w[i-1]+1)`处理“等待”的连续转移。
* **核心代码片段**：
```cpp
memset(w,0x3f,sizeof(w));
// 计算直接飞的所有转移
for(int i=h[x];i;i=e[i].nxt){
    int ed=g(e[i].to+d[x]);
    w[ed]=min(w[ed],d[x]+e[i].val);
}
// 处理等待的连续转移（等1秒到i+1，等2秒到i+2...）
rep(i,1,n*2)w[g(i+1)]=min(w[g(i+1)],w[g(i)]+1);
// 更新全局距离
rep(i,1,n)d[i]=min(d[i],w[i]);
```
* **代码解读**：
  - `w数组`先存储“直接飞”的所有可能目标，再通过`w[i+1] = min(w[i+1], w[i]+1)`，把“等待”转化为连续的边权1转移（比如从ed等k秒到ed+k）。
  - 这种方法把“等待”的逻辑“批量处理”，更直观地展示了“等时间”的本质。
* 💡 **学习笔记**：用辅助数组可以简化复杂的转移逻辑！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你“看得到”Dijkstra的过程，我设计了一个**8位像素风的动画**，像玩FC游戏一样学习算法！
</visualization_intro>

### 动画演示主题：《像素大炮旅行记》
**设计思路**：用FC红白机的像素风格（256x256分辨率，16色调色板），把城市做成32x32的像素块，大炮用箭头表示，等待用“移动”动画，发射用“飞行”动画。音效用8位机的单音效果，强化操作记忆。

### 动画帧步骤与交互关键点
1. **场景初始化**：
   - 屏幕左侧是**城市网格**（n=3时，3x3的像素块，编号1~3），右侧是**控制面板**（开始/暂停、单步、重置按钮，速度滑块）。
   - 背景是蓝色天空，城市块是灰色，起点（比如1号）是红色，目标（比如2号）是蓝色。
   - 播放8位风格的背景音乐（循环的“嘟嘟”声）。

2. **算法启动**：
   - 点击“开始”，红色块（起点1）的所有大炮箭头亮起（比如指向2和3），旁边显示“发射时间0，飞行时间1/3”。
   - 音效：“叮”（初始化完成）。

3. **核心步骤演示**：
   - **选最小距离节点**：当前距离最小的节点是1（距离0），红色块变成黄色（高亮）。
     - 音效：“嗒”（选中节点）。
   - **处理等待**：黄色块移动到下一个城市（2号），旁边显示“等待1秒，距离变为1”。
     - 音效：“嗒”（等待操作）。
   - **处理发射**：黄色块（1号）的大炮箭头指向2号（飞行时间1），2号的距离更新为1（从INF变成1）。
     - 音效：“咻”（发射操作）。
   - **迭代选点**：下一个最小距离节点是2（距离1），黄色块移动到2号，重复处理等待和发射。

4. **目标达成**：
   - 当蓝色块（目标2号）的距离确定时，播放上扬的“叮~”音效，蓝色块闪烁，旁边显示“到达！最短时间1秒”。

5. **交互设计**：
   - **单步执行**：点击“单步”，动画走一步，适合慢慢看细节。
   - **自动播放**：滑动速度滑块，调整动画速度（1x~5x）。
   - **重置**：点击“重置”，回到初始状态，重新开始。

<visualization_conclusion>
通过这个动画，你能清晰看到“选节点→等时间→发射”的完整过程，甚至能“听”到算法的节奏！像玩游戏一样学算法，是不是很有趣？
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
Dijkstra算法是**最短路问题的“万能钥匙”**，除了本题，还能解决很多类似问题。我们来看看它的迁移应用！
</similar_problems_intro>

### 通用思路迁移
- **场景1**：带权图的最短路径（比如城市间的公路，每条路有不同的时间）。
- **场景2**：有状态的最短路径（比如带时间限制的地铁，不同时间的班次不同）。
- **场景3**：多源最短路径（比如计算所有城市间的最短时间，本题就是这种情况）。

### 练习推荐 (洛谷)
1. **洛谷 P1339** - [USACO09OCT]Heat Wave G  
   🗣️ **推荐理由**：最短路模板题，帮你巩固Dijkstra的基本用法（单源最短路径）。
2. **洛谷 P2910** - [USACO08OPEN]Clear And Present Danger S  
   🗣️ **推荐理由**：多源最短路径问题，用Floyd或Dijkstra循环n次都能解决，适合对比两种算法的区别。
3. **洛谷 P4779** - 【模板】单源最短路径（标准版）  
   🗣️ **推荐理由**：Dijkstra的堆优化模板，帮你处理大数据量的情况（n≤1e5）。
4. **洛谷 P5905** - 【模板】全源最短路（Floyd版）  
   🗣️ **推荐理由**：Floyd算法模板，对比本题的Dijkstra循环n次，理解两种多源最短路算法的优劣。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
优质题解的作者们分享了很多“踩坑”经验，帮你少走弯路！
</insights_intro>

> **参考经验 (来自 nao_nao)**：“至少在我提交的时候可以过qwq。”  
> **点评**：这句话的潜台词是“代码要正确！”——很多初学者会忽略模运算的细节（比如编号从0开始还是1开始），导致WA（错误）。提交前一定要测试样例！

> **参考经验 (来自 7KByte)**：“被卡常的赛时代码，不影响阅读。”  
> **点评**：在竞赛中，代码的“常数”很重要（比如用`scanf`比`cin`快）。但初学者先保证**逻辑正确**，再优化常数！

> **参考经验 (来自 COsm0s)**：“用`ios::sync_with_stdio(false)`加速输入输出。”  
> **点评**：这是C++的小技巧——关闭同步后，`cin`和`cout`的速度会快很多，避免大数据量时超时！


<conclusion>
这道题的核心是**把“动态变化的大炮”转化为“静态的最短路径问题”**，用Dijkstra的单调性处理“等待”。通过今天的分析，你不仅掌握了Dijkstra的灵活应用，还学会了“问题转化”的关键技巧！记住：编程的本质是“把复杂问题拆成简单问题”，慢慢来，你一定能掌握！💪
</conclusion>

---
处理用时：97.82秒