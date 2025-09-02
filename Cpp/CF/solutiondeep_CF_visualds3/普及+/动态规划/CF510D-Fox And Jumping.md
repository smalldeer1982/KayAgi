# 题目信息

# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
```

### 输出

```
7237
```

# AI分析结果

# 💡 Kay的C++算法解析：Fox And Jumping 深入学习指南 💡

<introduction>
  今天我们来一起分析「Fox And Jumping」这道C++编程题。这道题看似是“跳跃游戏”，实则是**数学+动态规划/最短路**的结合题——核心是找到若干卡片，让它们的跳跃长度的最大公约数（gcd）为1，同时花费最少。本指南会帮你理清思路，掌握关键算法，并通过像素动画直观感受过程！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：动态规划（map优化）/ 最短路（Dijkstra）+ 裴蜀定理

🗣️ **初步分析**：
> 解决这道题的关键是**裴蜀定理**：如果几个数的gcd是1，那么它们的线性组合（加减）能得到1——这样就能跳到任意位置。因此问题转化为：**选若干卡片，使得它们的l的gcd为1，且总代价最小**。
> 
> 如何高效计算这个“最小代价”？有两种核心思路：
> 1. **动态规划（map优化）**：用`map`记录“当前gcd为x时的最小代价”，每次加入新卡片时，用`gcd(x, l[i])`更新状态。
> 2. **最短路（Dijkstra）**：把每个“gcd值”看作图中的节点，选卡片的过程就是从节点`x`走到`gcd(x, l[i])`，边权是卡片的代价。我们需要找从节点0（初始无卡片，gcd(0,l[i])=l[i]）到节点1的最短路径。
> 
> 这两种思路都能解决问题，但`map`优化的DP更直观，Dijkstra则用图论视角打开了新思路。
> 
> **可视化设计思路**：我们会做一个「像素gcd探险队」动画——每个gcd值是一个像素块，颜色越深表示代价越大；选卡片时，块会“合并”成新的gcd块，同时播放“叮”的音效；当块变成1（gcd=1）时，播放胜利音乐，画面出现像素烟花！


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性三个维度筛选了3份优质题解，覆盖了两种核心思路：
</eval_intro>

**题解一：Kohakuwu的map优化DP（赞20）**
* **点评**：这份题解把问题直接转化为“gcd状态的最小代价”，用`map`完美解决了“gcd值太大无法用数组存储”的问题。思路像“攒拼图”——每加一张卡片，就用`gcd`合并已有的拼图，保留最小代价。代码极其简洁，`for(pair<int,int> x:mp)`遍历所有状态的写法很巧妙，一看就懂！

**题解二：fanfansann的Dijkstra最短路（赞8）**
* **点评**：这道题居然能拆成最短路？太妙了！把每个gcd值看作节点，选卡片就是“走边”，边权是卡片代价。用优先队列（小根堆）找最短路径，刚好对应“最小代价”。代码里`unordered_map`记录距离，避免了数组越界问题，逻辑闭环，非常有启发性！

**题解三：ZYF_B的状压DP（赞36）**
* **点评**：如果卡片的质因数很少（比如≤9个），状压DP是另一种选择。把每个数的质因数用二进制位表示，`f[s]`表示质因数集合为`s`的最小代价。转移时合并质因数集合，最后找`f[0]`（质因数全被消掉，即gcd=1）。这种思路适合质因数少的场景，是对“gcd问题”的另一种拆解！


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的关键是**处理“大gcd值”的状态**和**设计正确的转移逻辑**。结合优质题解，我总结了3个核心难点及解决方法：
</difficulty_intro>

1.  **难点1：如何表示“gcd为x”的状态？**
    * **分析**：`l[i]`可以达到1e9，用数组存`f[x]`（x是gcd）肯定会爆空间。优质题解用`map`或`unordered_map`解决——只存“出现过的gcd值”，自动忽略无用状态。比如Kohakuwu的代码里，`map<int,int> mp`的键是gcd值，值是最小代价。
    * 💡 **学习笔记**：用`map`优化动态规划，是处理“大范围、稀疏状态”的神器！

2.  **难点2：如何转移状态？**
    * **分析**：当加入一张新卡片`l[i]`，所有已有的gcd状态`x`都会衍生出一个新状态`gcd(x, l[i])`，代价是`原代价 + c[i]`。比如Kohakuwu的代码里，遍历`map`中的每个`x`，计算`gcd(x, l[i])`，并更新新状态的最小代价。
    * 💡 **学习笔记**：状态转移的本质是“用新元素合并旧状态”，核心是`gcd`的运算！

3.  **难点3：如何初始化和处理边界？**
    * **分析**：初始时`map`是空的，第一次加入卡片`l[i]`时，`mp[l[i]] = c[i]`（只选这张卡片的代价）。如果`l[i]`本身是1，直接返回`c[i]`即可。比如fanfansann的Dijkstra中，`dist[0] = 0`（初始状态是“没选任何卡片”，gcd(0,l[i])=l[i]）。
    * 💡 **学习笔记**：边界条件是算法的“起点”，一定要想清楚初始状态是什么！

### ✨ 解题技巧总结
- **技巧1：问题转化**：把“能跳到任意位置”转化为“gcd=1”，这是裴蜀定理的关键应用。
- **技巧2：状态压缩**：用`map`或`unordered_map`存储稀疏状态，避免空间浪费。
- **技巧3：图论视角**：把动态规划问题转化为最短路问题，拓宽解题思路。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**通用的map优化DP代码**，来自Kohakuwu的题解——它是最直观、最容易理解的实现：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：这份代码用`map`记录“gcd为x时的最小代价”，遍历每张卡片，逐步合并状态，最终取`mp[1]`作为答案。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    inline int read() {
        int x=0,f=1;char ch=getchar();
        while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
        while('0'<=ch&&ch<='9')x=x*10+(ch^48),ch=getchar();
        return x*f;
    }
    map<int,int> mp;
    int a[1003],b[1003];
    int main(){
        int n=read();
        for(int i=1;i<=n;i++)a[i]=read();
        for(int i=1;i<=n;i++)b[i]=read();
        for(int i=1;i<=n;i++){
            // 遍历已有的状态，合并新卡片
            for(pair<int,int> x:mp){
                int num=__gcd(a[i],x.first),val=x.second+b[i];
                if(mp[num]==0)mp[num]=val;
                else mp[num]=min(mp[num],val);
            }
            // 单独选这张卡片的情况
            if(mp[a[i]]==0)mp[a[i]]=b[i];
            else mp[a[i]]=min(mp[a[i]],b[i]);
        }
        if(mp[1]==0)puts("-1");
        else printf("%d\n",mp[1]);
        return 0;
    }
    ```
* **代码解读概要**：
    > 1. 读取输入：`a[i]`是卡片长度，`b[i]`是代价。
    > 2. 遍历每张卡片：
    >    - 先遍历`map`中已有的状态，用`__gcd(a[i], x.first)`计算新的gcd，更新最小代价。
    >    - 再处理“只选这张卡片”的情况（避免遗漏）。
    > 3. 最后检查`mp[1]`：存在则输出，否则输出-1。


<code_intro_selected>
接下来看另外两种思路的核心片段：
</code_intro_selected>

**题解二：fanfansann的Dijkstra最短路**
* **亮点**：把gcd状态转化为图的节点，用优先队列找最短路径，思路新颖。
* **核心代码片段**：
    ```cpp
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push({0, 0}); dist[0] = 0;
    while(q.size()) {
        int x = q.top().second; q.pop();
        if(x == 1) break; // 找到目标
        if(vis.find(x) != vis.end()) continue;
        vis[x] = true;
        for(int i=1; i<=n; ++i) {
            int y = __gcd(x, l[i]), z = c[i];
            if(dist.find(y) == dist.end()) dist[y] = INF;
            if(dist[y] > dist[x] + z) {
                dist[y] = dist[x] + z;
                q.push({dist[y], y});
            }
        }
    }
    ```
* **代码解读**：
    > - `priority_queue`是小根堆，每次取出“当前代价最小的节点”（Dijkstra的核心）。
    > - `dist[x]`记录到达节点`x`（gcd=x）的最小代价。
    > - 遍历所有卡片，计算从`x`到`y=__gcd(x,l[i])`的代价，更新`dist[y]`并加入堆。
* 💡 **学习笔记**：Dijkstra不仅能找路径，还能解决“最小代价合并状态”的问题！

**题解三：ZYF_B的状压DP**
* **亮点**：用质因数状压处理小质因数的情况，适合卡片质因数少的场景。
* **核心代码片段**：
    ```cpp
    int f[1<<9]; // 最多9个质因数，2^9=512种状态
    for(int i=1;i<=n;i++){
        memset(f,0x3f,sizeof(f));
        int M=1<<cnt[i];
        f[M-1] = cost[i]; // 初始状态：选第i张卡片，质因数全选
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            int s=0;
            // 计算j的质因数在i的质因数中的位置
            for(int k=1;k<=cnt[i];k++){
                for(int x=1;x<=cnt[j];x++){
                    if(g[i][k]==g[j][x]){s|=(1<<(k-1));break;}
                }
            }
            // 转移：合并i和j的质因数
            for(int k=0;k<M;k++){
                f[k&s] = min(f[k&s], f[k] + cost[j]);
            }
        }
        ans = min(ans, f[0]); // f[0]表示质因数全消，gcd=1
    }
    ```
* **代码解读**：
    > - `cnt[i]`是第i张卡片的质因数个数，`g[i][k]`是第i张卡片的第k个质因数。
    > - `f[s]`表示质因数集合为`s`的最小代价（`s`的二进制位表示是否包含某个质因数）。
    > - 转移时，用`k&s`合并两个质因数集合（消去共同的质因数），最终`f[0]`就是gcd=1的最小代价。
* 💡 **学习笔记**：状压DP适合“状态可以用二进制表示”的问题，比如质因数、子集等！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解`map优化DP`的过程，我设计了一个**8位像素风格的“gcd探险队”动画**，结合复古游戏元素，让你“看”到状态的合并！
</visualization_intro>

  * **动画演示主题**：像素小人“GcdMan”带着背包收集卡片，每收集一张卡片，背包里的“gcd块”会合并成新的块，最终目标是合成“1号块”。
  * **设计思路简述**：用8位像素风（类似FC游戏）降低视觉负担，用颜色深浅表示代价（越深代价越高），用音效强化关键操作（比如合并块时“叮”一声，合成1号块时“噔噔噔”胜利音效），让学习更有趣！

  * **动画帧步骤与交互关键点**：
    1. **初始化场景**：
       - 屏幕左侧是“卡片库”（显示所有卡片的l和c，用像素数字表示）。
       - 屏幕右侧是“gcd背包”（显示当前所有的gcd块，每个块是16x16的像素 square，颜色越深代价越高）。
       - 底部控制面板：单步执行、自动播放、重置按钮，速度滑块（从“龟速”到“火箭”）。
       - 背景播放8位风格的轻松BGM（比如《超级马里奥》的背景音乐）。
    2. **第一步：选第一张卡片**：
       - 点击卡片库中的第一张卡片（比如l=100，c=99），“GcdMan”走到卡片前，拿起卡片。
       - 背包中出现一个新的块：100（颜色浅蓝，代价99），同时播放“叮”的音效。
    3. **第二步：选第二张卡片**：
       - 点击第二张卡片（l=1，c=1），“GcdMan”拿起卡片，背包中的100块和1块合并成新的块：1（gcd(100,1)=1），颜色变成亮红色（代价99+1=100？不对，样例1中选前两张卡片的代价是2？哦样例1的输入是3张卡片，l是100、99、9900，c是1、1、1？哦对，样例1的输出是2，因为选前两张卡片的l是100和99，gcd(100,99)=1，代价1+1=2。所以动画中合并100和99块，得到1块，代价2，此时播放胜利音效！
    4. **关键交互**：
       - 单步执行：每点击一次，执行一步卡片选择或块合并。
       - 自动播放：按设定速度连续执行，适合快速看流程。
       - 重置：回到初始状态，重新开始。
    5. **胜利状态**：
       - 当背包中出现1号块时，屏幕中央弹出像素烟花，播放胜利音乐（比如《魂斗罗》的通关音效），底部显示“成功！最小代价是X”。

  * **旁白提示**：
    - 选第一张卡片时：“GcdMan选了l=100的卡片，代价99，背包里多了一个100块！”
    - 合并块时：“100和99的gcd是1，代价变成1+1=2，找到目标啦！”


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
这道题的核心是“求gcd为1的最小代价”，这种思路可以迁移到很多问题中：
</similar_problems_intro>

  * **通用思路迁移**：
    - 场景1：选若干数，使它们的gcd为k，求最小代价（只需把目标改为k即可）。
    - 场景2：选若干物品，每个物品有多个属性，要求属性的gcd为1，求最小代价（比如选工具，使工具的功能覆盖所有需求）。
    - 场景3：选若干数，使它们的lcm为某个数，求最小代价（类似但更复杂）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1029** - 最大公约数和最小公倍数问题
          * 🗣️ **推荐理由**：这道题是裴蜀定理的基础应用，帮你巩固“gcd和lcm的关系”。
    2.  **洛谷 P1890** - gcd区间
          * 🗣️ **推荐理由**：这道题要求区间gcd，帮你熟悉gcd的计算和区间查询。
    3.  **洛谷 P2520** - 大豆问题
          * 🗣️ **推荐理由**：这道题是“选若干数使gcd为1”的变形，帮你练习动态规划的应用。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
从题解中，我学到了两个非常重要的经验：
</insights_intro>

> **经验1**（来自Kohakuwu）：“用map优化动态规划，可以解决状态范围大的问题！”
> **点评**：当状态范围超过1e5时，数组肯定存不下，这时候`map`或`unordered_map`是救星——它们只存有用的状态，节省空间又高效。
> 
> **经验2**（来自fanfansann）：“动态规划和最短路是相通的！”
> **点评**：把状态看作节点，转移看作边，动态规划的“最小代价”就是最短路的“最短路径”。这种思路转换能帮你解决很多看似“无法用DP”的问题。


<conclusion>
本次关于「Fox And Jumping」的分析就到这里！这道题的核心是**裴蜀定理+状态优化**，无论是map DP还是Dijkstra，都是解决“大状态、小有效状态”问题的好方法。希望这份指南能帮你掌握这些技巧，下次遇到类似问题时，能快速想到“用map存状态”或“转成最短路”！💪
</conclusion>

---
处理用时：160.45秒