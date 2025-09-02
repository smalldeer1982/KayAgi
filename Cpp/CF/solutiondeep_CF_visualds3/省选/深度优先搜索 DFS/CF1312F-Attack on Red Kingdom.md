# 题目信息

# Attack on Red Kingdom

## 题目描述

The Red Kingdom is attacked by the White King and the Black King!

The Kingdom is guarded by $ n $ castles, the $ i $ -th castle is defended by $ a_i $ soldiers. To conquer the Red Kingdom, the Kings have to eliminate all the defenders.

Each day the White King launches an attack on one of the castles. Then, at night, the forces of the Black King attack a castle (possibly the same one). Then the White King attacks a castle, then the Black King, and so on. The first attack is performed by the White King.

Each attack must target a castle with at least one alive defender in it. There are three types of attacks:

- a mixed attack decreases the number of defenders in the targeted castle by $ x $ (or sets it to $ 0 $ if there are already less than $ x $ defenders);
- an infantry attack decreases the number of defenders in the targeted castle by $ y $ (or sets it to $ 0 $ if there are already less than $ y $ defenders);
- a cavalry attack decreases the number of defenders in the targeted castle by $ z $ (or sets it to $ 0 $ if there are already less than $ z $ defenders).

The mixed attack can be launched at any valid target (at any castle with at least one soldier). However, the infantry attack cannot be launched if the previous attack on the targeted castle had the same type, no matter when and by whom it was launched. The same applies to the cavalry attack. A castle that was not attacked at all can be targeted by any type of attack.

The King who launches the last attack will be glorified as the conqueror of the Red Kingdom, so both Kings want to launch the last attack (and they are wise enough to find a strategy that allows them to do it no matter what are the actions of their opponent, if such strategy exists). The White King is leading his first attack, and you are responsible for planning it. Can you calculate the number of possible options for the first attack that allow the White King to launch the last attack? Each option for the first attack is represented by the targeted castle and the type of attack, and two options are different if the targeted castles or the types of attack are different.

## 样例 #1

### 输入

```
3
2 1 3 4
7 6
1 1 2 3
1
1 1 2 2
3```

### 输出

```
2
3
0```

## 样例 #2

### 输入

```
10
6 5 4 5
2 3 2 3 1 3
1 5 2 3
10
4 4 2 3
8 10 8 5
2 2 1 4
8 5
3 5 3 5
9 2 10
4 5 5 5
2 10 4 2
2 3 1 4
1 10
3 1 5 3
9 8 7
2 5 4 5
8 8
3 5 1 4
5 5 10```

### 输出

```
0
2
1
2
5
12
5
0
0
2```

# AI分析结果

# 💡 Kay的C++算法解析：Attack on Red Kingdom 深入学习指南 💡

<introduction>
  今天我们来一起分析「Attack on Red Kingdom」这道博弈论经典题。两个国王轮流攻击城堡，规则里藏着“不能连续用同类型步兵/骑兵攻击”的限制——要帮白王找到第一次攻击的必胜策略，核心是**组合游戏的SG函数**！本指南会帮你理清楚SG函数的状态定义、大数值下的循环节技巧，还有如何通过异或和判断胜负~
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：组合游戏（SG函数）、循环节优化

🗣️ **初步分析**：
解决这道题的关键，是把每个城堡的防御士兵数看作一个**独立的有向图游戏**，而整个问题是这些子游戏的“和”。根据组合游戏的定理：  
- 总游戏的SG函数 = 所有子游戏SG函数的**异或和**；  
- 总SG为0时，当前玩家必败；否则必胜。  

白王要做的，就是**第一次攻击后让总SG变为0**——这样不管黑王怎么操作，白王都能赢到最后！

### 核心算法的“游戏化比喻”
把每个城堡想象成一个“小关卡”：  
- 关卡状态 = 士兵数`k` + 上一次攻击类型`c`（0=混合，1=步兵，2=骑兵）；  
- SG函数`SG(k,c)`就是这个关卡的“胜负密码”——0表示当前玩家在这个关卡必败，非0则必胜。  

而攻击的规则，对应关卡间的“状态转移”：  
- 混合攻击（c=0）后，下一个状态可以是`k-x`的任意类型（因为混合没有限制）；  
- 步兵攻击（c=1）后，下一个状态不能再是步兵（所以排除`k-y`的c=1）；  
- 骑兵攻击（c=2）同理，排除`k-z`的c=2。  

### 大数值的“循环节魔法”
题目中士兵数`a_i`能到`1e18`，直接计算每个`k`的SG值会超时！但`x,y,z`很小（最多5），SG状态会**进入循环**——就像绕操场跑圈，跑一段后重复之前的步骤。我们只需要找到循环的起点`pre`和长度`len`，就能用`(k-pre)%len + pre`快速算出大`k`的SG值~

### 可视化设计思路
我会用**8位像素风**做动画：  
- 每个城堡是带数字的像素块，颜色表示上一次攻击类型（蓝=混合，绿=步兵，红=骑兵）；  
- 总SG值显示在屏幕顶部，用闪烁的像素字提示“当前总状态”；  
- 攻击时，选中的城堡会“跳一下”，攻击类型对应的颜色亮起，然后数值减少，SG值更新；  
- 循环节出现时，用“旋转的像素箭头”提示“进入循环啦！”，并重复播放一段状态序列~


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性和算法有效性三个维度，筛选了3份优质题解——它们都抓住了SG函数和循环节的核心，适合入门学习！
</eval_intro>

**题解一：(来源：Froggy，赞12)**
* **点评**：这份题解是“SG函数+循环节”的标准模板！思路上先讲清楚状态定义（`SG(k,c)`），再推导转移方程，最后用`map`记录最近5个状态找循环节——逻辑链完整到“一步都不缺”。代码里的`Add`函数巧妙计算每个`k`的SG值，`Get`函数快速处理大数值，尤其是`mex`函数的实现（找未出现的最小非负整数），简直是“教科书级”的简洁。从实践角度看，代码能直接应对`1e18`的输入，边界处理（比如`max(k-x,0)`）也很严谨，是必学的参考！

**题解二：(来源：dead_X，赞1)**
* **点评**：这道题解的亮点是“接地气”——作者提到自己“降智好久才想通统计方法”，还跑去看CF官方题解确认循环节长度（最多36），让我们看到真实的解题过程。代码里的`init`函数用`unordered_map`记录状态找循环节，`solve`函数计算大数值的SG值，结构清晰。尤其是作者把`f[i][3]`用位运算压缩状态（`(f[i][0]<<4)+(f[i][1]<<2)+f[i][2]`），节省了内存，是值得学习的小技巧！

**题解三：(来源：Hoks，赞0)**
* **点评**：这份题解的“康复训练”定位很准！作者直接点出“类似题目CF273E”，帮助我们迁移思路——这就是“举一反三”的关键！代码里的`prework`函数预处理所有`x,y,z`（1~5）的SG状态，`get`函数计算循环节后的SG值，虽然预处理部分有点复杂，但胜在“通用性强”。尤其是作者用`vector<tuple>`记录状态找循环节，让我们看到不同的实现方式~


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的“三座大山”，其实是**状态定义**、**循环节处理**和**总SG计算**。结合优质题解，我帮你拆解成可操作的策略：
</difficulty_intro>

1.  **关键点1：如何定义SG函数的状态？**
    * **分析**：因为“步兵/骑兵不能连续用同类型攻击”，所以状态必须包含**当前士兵数`k`**和**上一次攻击类型`c`**（0=混合，1=步兵，2=骑兵）。比如`SG(k,1)`表示当前士兵数是`k`，上一次是步兵攻击——这时候下一次不能再用步兵，所以转移时要排除`k-y`的`c=1`状态。
    * 💡 **学习笔记**：状态定义要覆盖“影响后续操作的所有因素”！

2.  **关键点2：如何处理1e18的大数值？**
    * **分析**：`x,y,z`很小（最多5），SG状态的转移只和最近5个`k`有关——所以状态会进入循环。我们可以用`map`记录最近5个状态的组合，如果重复出现，就找到了循环的起点`pre`和长度`len`。之后用`(k-pre)%len + pre`快速计算大`k`的SG值，复杂度从`O(1e18)`降到`O(循环节长度)`！
    * 💡 **学习笔记**：大数值问题，先找“循环规律”！

3.  **关键点3：如何统计必胜的第一次攻击？**
    * **分析**：总SG初始值是`sum`（所有城堡`SG(a_i,0)`的异或和）。对于每个城堡，第一次攻击有三种选择（混合、步兵、骑兵），对应将其SG值从`v0`变为`v`。要让攻击后的总SG为0，需要满足`sum ^ v0 ^ v = 0`（等价于`v0 ^ v = sum`）。我们只需要统计所有满足`v0 ^ v = sum`的攻击次数即可！
    * 💡 **学习笔记**：必胜条件是“改变一个子游戏的SG，让总异或和为0”！

### ✨ 解题技巧总结
- **状态设计**：覆盖所有影响后续操作的因素（比如本题的“上一次攻击类型”）；  
- **循环节找法**：记录最近几个状态的组合，重复即循环；  
- **异或和计算**：总SG是子游戏的异或，必胜条件是“改变一个子游戏的SG，让总异或为0”；  
- **边界处理**：士兵数不能为负，用`max(k-x, 0)`处理。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**综合优质题解的通用核心代码**——它整合了Froggy的简洁性和dead_X的高效性，能完整解决问题！
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了Froggy和dead_X的思路，用`map`找循环节，`Get`函数处理大数值，逻辑清晰易读。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <vector>
    #include <map>
    #include <cstring>
    using namespace std;
    typedef long long ll;

    int mex(int a, int b, int c) {
        bool vis[4] = {false};
        if (a != -1) vis[a] = true;
        if (b != -1) vis[b] = true;
        if (c != -1) vis[c] = true;
        for (int i = 0; ; ++i) if (!vis[i]) return i;
    }

    vector<vector<int>> sg;
    map<vector<vector<int>>, int> mp;
    int pre, len;

    void add_state(int x, int y, int z) {
        int k = sg.size();
        vector<int> new_sg(3);
        // 计算SG(k, 0)（混合攻击后）
        int s0 = (k - x >= 0) ? sg[k - x][0] : -1;
        int s1 = (k - y >= 0) ? sg[k - y][1] : -1;
        int s2 = (k - z >= 0) ? sg[k - z][2] : -1;
        new_sg[0] = mex(s0, s1, s2);
        // 计算SG(k, 1)（步兵攻击后，不能再用步兵）
        new_sg[1] = mex(s0, -1, s2);
        // 计算SG(k, 2)（骑兵攻击后，不能再用骑兵）
        new_sg[2] = mex(s0, s1, -1);
        sg.push_back(new_sg);
    }

    int get_sg(ll k) {
        if (k < pre) return k;
        return pre + (k - pre) % len;
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(0);
        int T; cin >> T;
        while (T--) {
            int n, x, y, z;
            cin >> n >> x >> y >> z;
            vector<ll> a(n);
            for (int i = 0; i < n; ++i) cin >> a[i];
            
            // 初始化SG数组
            sg.clear();
            mp.clear();
            sg.push_back({0, 0, 0}); // k=0时的SG值
            for (int i = 1; i < 5; ++i) add_state(x, y, z); // 先算前5个状态
            
            // 找循环节
            while (true) {
                vector<vector<int>> key(sg.end() - 5, sg.end());
                if (mp.count(key)) {
                    pre = mp[key];
                    len = sg.size() - 5 - pre;
                    break;
                }
                mp[key] = sg.size() - 5;
                add_state(x, y, z);
            }
            
            // 计算总SG和统计方案数
            int sum = 0;
            int cnt[4] = {0}; // 统计v0^v的次数
            for (ll num : a) {
                ll v0_k = get_sg(num);
                int v0 = sg[v0_k][0]; // 初始状态是k=num，上一次没攻击（等价于c=0）
                
                // 三种攻击对应的新SG值
                ll v1_k = get_sg(max(num - x, 0LL));
                int v1 = sg[v1_k][0]; // 混合攻击后，上一次是c=0
                
                ll v2_k = get_sg(max(num - y, 0LL));
                int v2 = sg[v2_k][1]; // 步兵攻击后，上一次是c=1
                
                ll v3_k = get_sg(max(num - z, 0LL));
                int v3 = sg[v3_k][2]; // 骑兵攻击后，上一次是c=2
                
                sum ^= v0;
                cnt[v0 ^ v1]++;
                cnt[v0 ^ v2]++;
                cnt[v0 ^ v3]++;
            }
            cout << cnt[sum] << endl;
        }
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码分四部分：1. `mex`函数计算未出现的最小非负整数；2. `add_state`函数计算每个`k`的SG值；3. `get_sg`函数处理大数值的循环节；4. `main`函数读入数据、找循环节、计算总SG和统计方案数。核心逻辑是**先预处理SG状态找循环节，再快速计算每个城堡的SG值，最后统计满足条件的攻击次数**。

---

<code_intro_selected>
接下来剖析优质题解的核心片段，看看它们的“巧妙之处”！
</code_intro_selected>

**题解一：(来源：Froggy)**
* **亮点**：用`vector<vector<int>>`记录最近5个状态，找循环节的方式直接易懂。
* **核心代码片段**：
    ```cpp
    while("zz has no dick! /fn"){
        vt tmp(sg.end()-5,sg.end());
        if(mp.count(tmp)){  //找到了循环节
            pre=mp[tmp],len=sg.size()-5-pre;  
            break;
        }
        mp[tmp]=sg.size()-5;
        Add();
    }
    ```
* **代码解读**：
    > 这段代码是“找循环节的关键”！`sg.end()-5`到`sg.end()`是最近5个状态的组合，用`map`记录这些组合第一次出现的位置。如果再次出现，说明从`mp[tmp]`到当前位置是一个循环——`pre`是循环起点，`len`是循环长度。比如`sg.size()-5-pre`就是循环的长度，因为`sg.end()-5`对应的是`k=sg.size()-5`的状态~
* 💡 **学习笔记**：找循环节的核心是“记录足够多的历史状态，重复即循环”！

**题解二：(来源：dead_X)**
* **亮点**：用位运算压缩状态，节省内存。
* **核心代码片段**：
    ```cpp
    f[i][3]=(f[i][0]<<4)+(f[i][1]<<2)+f[i][2];
    for(int j=i-4; j<=i; ++j) 
        s=(s<<6)+f[j][3];
    ```
* **代码解读**：
    > 这段代码把每个`k`的三个SG值（`f[i][0]`、`f[i][1]`、`f[i][2]`）压缩成一个整数`f[i][3]`（用左移4位、2位合并）。然后把最近5个`k`的`f[j][3]`合并成一个更大的整数`s`，用`unordered_map`记录`s`的位置——这样比存`vector`更省内存，查询更快！
* 💡 **学习笔记**：位运算可以高效压缩状态，适合记录小数值的组合！

**题解三：(来源：Hoks)**
* **亮点**：预处理所有`x,y,z`（1~5）的SG状态，通用性强。
* **核心代码片段**：
    ```cpp
    for(int x=1;x<=5;x++) for(int y=1;y<=5;y++) for(int z=1;z<=5;z++){
        int i=1;
        for(int k=0;k<3;k++) f[x][y][z][k].emplace_back(0);
        map<vector<tuple<int,int,int>>,int>mp;
        while(1){
            // 计算SG值
            if(i>=4){
                vector<tuple<int,int,int>>a;
                for(int j=i-4;j<=i;j++) 
                    a.emplace_back(f[x][y][z][0][j],f[x][y][z][1][j],f[x][y][z][2][j]);
                if(mp.count(a)){ pre[x][y][z]=mp[a]; break; }
                mp[a]=i-4;
            }i++;
        }
    }
    ```
* **代码解读**：
    > 这段代码预处理了所有`x,y,z`（1~5）的SG状态——因为题目中`x,y,z`的输入范围是1~5（看样例）。预处理后，每次测试用例直接取对应`x,y,z`的SG状态，不用重新计算，速度更快！比如`f[x][y][z][k][w]`表示当`x,y,z`为当前值时，`k`类型攻击、`w`士兵数的SG值~
* 💡 **学习笔记**：预处理是“以空间换时间”的常用技巧，适合输入范围小的情况！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你“亲眼看到”SG函数和循环节的工作过程，我设计了一个**8位像素风动画**——像玩FC游戏一样学算法！
</visualization_intro>

  * **动画演示主题**：像素城堡的“SG冒险”（白王的必胜攻击计划）
  * **核心演示内容**：展示每个城堡的SG状态变化、总SG异或和的计算，以及循环节的出现。
  * **设计思路简述**：用FC游戏的复古风格降低学习门槛，用“跳跃的城堡”“闪烁的攻击类型”强化操作记忆，用“循环箭头”提示规律——让抽象的SG函数变得“看得见、摸得着”！

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化 (FC风格)**：
          * 屏幕左侧是3个像素城堡（对应样例1的输入），每个城堡上显示士兵数（比如7、6、3），下方用彩色方块标记上一次攻击类型（初始是蓝色=混合）。
          * 屏幕右侧是“控制面板”：有“开始/暂停”“单步”“重置”按钮，速度滑块，还有“总SG值”显示区（初始是`SG(7,0)^SG(6,0)^SG(3,0)`）。
          * 背景播放8位风格的轻松BGM（比如《超级马里奥》的小关卡音乐）。

    2.  **算法启动：计算初始SG**：
          * 每个城堡开始“闪烁”，下方弹出文字气泡：“计算SG(7,0) = ?”。
          * 动画逐步展示`k=0`到`k=7`的SG值计算过程（比如`SG(0,0)=0`，`SG(1,0)=mex(SG(0,0), SG(0,1), SG(0,2))=1`……）。
          * 计算完成后，城堡下方显示`SG(7,0)=2`，总SG值更新为`2^SG(6,0)^SG(3,0)`。

    3.  **循环节展示**：
          * 当计算到`k=10`时，动画突然“慢下来”，屏幕中央出现旋转的像素箭头，旁边文字提示：“发现循环节！起点pre=5，长度len=6”。
          * 重复播放`k=5`到`k=10`的SG状态序列，让你看到“循环的规律”。

    4.  **第一次攻击的选择**：
          * 白王开始选择攻击：点击第一个城堡（士兵数7），弹出三个攻击类型按钮（蓝=混合，绿=步兵，红=骑兵）。
          * 选择“混合攻击”：城堡士兵数变为`7-x=7-2=5`（对应样例1的输入`x=2`），下方攻击类型变为蓝色，SG值更新为`SG(5,0)=1`。
          * 总SG值变为`2^1 ^ SG(6,0) ^ SG(3,0)`——如果这个值为0，屏幕顶部弹出“白王必胜！”的像素字，伴随胜利音效（8位的“叮~叮~”）。

    5.  **交互控制**：
          * 单步模式：点击“单步”按钮，动画一步步展示SG计算、攻击选择、总SG更新的过程。
          * 自动模式：调整速度滑块（从“慢”到“快”），动画自动播放，像“AI玩游戏”一样展示完整流程。
          * 重置按钮：恢复初始状态，重新开始演示。

  * **旁白提示**：
      * （计算SG时）“SG(k,c)是这个城堡的胜负密码——0必败，非0必胜！”
      * （循环节出现时）“看！这些状态重复了，这就是循环节——不用算到1e18啦！”
      * （攻击后总SG为0时）“总SG变成0了！白王不管黑王怎么操作，都能赢到最后~”

<visualization_conclusion>
通过这个动画，你不仅能看到SG函数的计算过程，还能直观理解“循环节”和“总SG异或和”的作用——原来博弈论也能玩得这么有意思！
</visualization_conclusion>


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
SG函数是组合游戏的“万能钥匙”，掌握它能解决一大类博弈问题！来看看它的其他应用场景：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * **场景1**：取石子游戏（比如每次取1~3个，不能连续取同数量）——状态是石子数+上一次取的数量；
      * **场景2**：棋盘游戏（比如在网格上移动棋子，不能走回头路）——状态是棋子位置+上一步方向；
      * **场景3**：多堆石子游戏（比如Nim游戏的变形）——每个堆是一个子游戏，总SG是异或和。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1290** - 《欧几里得的游戏》
          * 🗣️ **推荐理由**：这是SG函数的基础题，帮你巩固“状态定义”和“转移方程”的思路。
    2.  **洛谷 P2148** - 《[SDOI2009]E&D》
          * 🗣️ **推荐理由**：需要找循环节的SG函数题，和本题的“大数值处理”思路一致。
    3.  **洛谷 P3235** - 《[HNOI2014]江南乐》
          * 🗣️ **推荐理由**：多堆石子的SG函数题，帮你练习“总SG异或和”的计算。
    4.  **洛谷 CF273E** - 《Dima and Horses》
          * 🗣️ **推荐理由**：和本题类似的“操作限制”博弈题，帮你迁移思路。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
题解作者们的“踩坑经历”是最宝贵的学习资料——让我们看看他们的心得：
</insights_intro>

> **参考经验 (来自 Froggy)**：“当时没学博弈论的我在这场 CF 后痛定思痛了 QAQ。”
>
> **点评**：这位作者的经历很真实！博弈论的核心是“状态转移”和“SG函数”，没学过的话确实会“两眼一抹黑”。建议大家先学组合游戏的基础（比如Nim游戏、SG函数定义），再做这道题——基础不牢，地动山摇！

> **参考经验 (来自 dead_X)**：“最后发现枚举所有操作分别算出操作后的SG值就可以了。”
>
> **点评**：作者的“降智时刻”其实是很多人的共性——一开始想复杂了，后来才发现“直接枚举三种攻击”就够了。这提醒我们：**解决问题要从“小处着手”，先想最直接的方法，再优化**！


<conclusion>
本次关于「Attack on Red Kingdom」的分析就到这里啦！关键是掌握**SG函数的状态定义**、**循环节优化**和**总异或和的必胜条件**。记住：博弈论的本质是“状态的转移”，只要把状态定义清楚，问题就解决了一半~ 下次我们再一起探索更有趣的博弈问题！💪
</conclusion>

---
处理用时：152.68秒