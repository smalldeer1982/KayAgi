# 题目信息

# Greg and Friends

## 题目描述

One day Greg and his friends were walking in the forest. Overall there were $ n $ people walking, including Greg. Soon he found himself in front of a river. The guys immediately decided to get across the river. Luckily, there was a boat by the river bank, just where the guys were standing. We know that the boat can hold people with the total weight of at most $ k $ kilograms.

Greg immediately took a piece of paper and listed there the weights of all people in his group (including himself). It turned out that each person weights either 50 or 100 kilograms. Now Greg wants to know what minimum number of times the boat needs to cross the river to transport the whole group to the other bank. The boat needs at least one person to navigate it from one bank to the other. As the boat crosses the river, it can have any non-zero number of passengers as long as their total weight doesn't exceed $ k $ .

Also Greg is wondering, how many ways there are to transport everybody to the other side in the minimum number of boat rides. Two ways are considered distinct if during some ride they have distinct sets of people on the boat.

Help Greg with this problem.

## 说明/提示

In the first test Greg walks alone and consequently, he needs only one ride across the river.

In the second test you should follow the plan:

1. transport two $ 50 $ kg. people;
2. transport one $ 50 $ kg. person back;
3. transport one $ 100 $ kg. person;
4. transport one $ 50 $ kg. person back;
5. transport two $ 50 $ kg. people.

That totals to $ 5 $ rides. Depending on which person to choose at step 2, we can get two distinct ways.

## 样例 #1

### 输入

```
1 50
50
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
3 100
50 50 100
```

### 输出

```
5
2
```

## 样例 #3

### 输入

```
2 50
50 50
```

### 输出

```
-1
0
```

# AI分析结果

# 💡 Kay的C++算法解析：Greg and Friends 深入学习指南 💡

<introduction>
  今天我们来一起分析经典的过河问题——“Greg and Friends”。这道题不仅要计算把所有人送过河的**最少次数**，还要统计**最少次数下的方案数**。通过这道题，我们能学会如何用“状态动态规划（DP）+ 广度优先搜索（BFS）”结合的思路解决“最短路径+计数”问题，赶紧开始吧！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：状态动态规划（DP）+ 广度优先搜索（BFS）

🗣️ **初步分析**：
解决这道题的关键，是把“过河过程”抽象成**状态转移**——每一步的状态由「出发岸剩余的50kg人数」「出发岸剩余的100kg人数」「船的位置」（在出发岸或对岸）三个因素决定。我们需要：
1. **找最短次数**：用BFS的“层级”表示过河次数（每一轮“去对岸+回来”算两次，但最后一次不需要回来）；
2. **统计方案数**：用DP数组记录每个状态的方案数，转移时用**组合数**计算“选多少人上船”的可能性。

简单来说，这就像“玩推箱子游戏”：每一步都要考虑“推哪几个箱子”（选哪几个人上船），同时要记录“走了多少步”（次数）和“有多少种走法”（方案数）。

### 核心算法流程与可视化设计思路
- **状态定义**：用`dp[pos][j][k]`表示「船在`pos`岸（0=对岸，1=出发岸）」「对岸有`j`个50kg的人」「对岸有`k`个100kg的人」时的方案数。
- **转移逻辑**：
  - 当船在出发岸（`pos=1`）：选`c5`个50kg、`c1`个100kg的人上船（总重量≤k，且至少1人），转移到对岸（`pos=0`），方案数增加`组合数(剩余50kg选c5) × 组合数(剩余100kg选c1) × 原状态方案数`。
  - 当船在对岸（`pos=0`）：选`c5`个50kg、`c1`个100kg的人回来（总重量≤k，且至少1人），转移到出发岸（`pos=1`），方案数增加`组合数(对岸50kg选c5) × 组合数(对岸100kg选c1) × 原状态方案数`。
- **可视化设计**：用8位像素风展示「出发岸」「河」「对岸」三个区域，50kg的人用蓝色像素块、100kg用红色，船用黄色。每一步动画展示：
  1. 上船的人高亮（闪烁）；
  2. 船从当前岸移动到另一岸（滑动动画）；
  3. 对岸的人数增加/减少（像素块移动）；
  4. 屏幕上方显示当前次数和方案数。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性三个维度筛选了3份优质题解，它们各有亮点，能帮助你从不同角度理解问题！
</eval_intro>

**题解一：(来源：gesong，赞4)**
* **点评**：这份题解的思路非常“直观”——用`f[i][j][k]`表示“第`i`次过程后（船从一边到另一边算一次过程），出发岸还有`j`个50kg、`k`个100kg的人”的方案数。**核心亮点**是用“奇偶性”区分“去对岸”（奇数过程）和“回来”（偶数过程），转移时直接枚举上船的人数，并用组合数计算可能性。代码结构清晰，变量名（如`x`=50kg人数、`y`=100kg人数）含义明确，边界条件（如过程数超过4n则无解）处理严谨，非常适合入门学习。

**题解二：(来源：zztqwq，赞3)**
* **点评**：这份题解的**最大亮点是空间优化**——用滚动数组`f[2][60][60]`代替三维数组（因为船的位置只有0或1两种状态），把空间复杂度从O(n²)降到了O(1)。状态定义也很巧妙：`f[pos][j][k]`表示“船在`pos`岸，对岸有`j`个50kg、`k`个100kg的人”的方案数，转移时直接枚举上船的`c5`和`c1`，计算组合数的方式也很简洁（用预处理的阶乘和逆元）。代码可读性高，适合学习“如何优化DP空间”。

**题解三：(来源：SevenDawns，赞3)**
* **点评**：这份题解把“BFS找最短路径”和“DP统计方案数”结合得很紧密——用队列模拟状态转移，`step[i][j][k]`记录到达该状态的最少次数，`dp[i][j][k]`记录方案数。**核心亮点**是处理“相同状态多次访问”的逻辑：如果新路径的次数更少，就更新次数和方案数；如果次数相同，就累加方案数。这种“BFS+DP”的混合思路，能帮你理解“如何同时找最短路径和计数”。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
这道题的难点在于“如何把现实问题转化为状态转移”，以及“处理组合数和边界条件”。结合优质题解，我帮你提炼了3个核心关键点：
</difficulty_intro>

1.  **关键点1：如何定义“状态”？**
    * **分析**：状态需要包含“当前剩余的人数”和“船的位置”——因为这两个因素直接决定了下一步能做什么。比如，船在出发岸时，只能从出发岸选人参船；船在对岸时，只能从对岸选人参船。优质题解的状态定义（如`f[pos][j][k]`或`f[i][j][k]`）都覆盖了这两个因素。
    * 💡 **学习笔记**：状态定义要“完整覆盖决策所需的信息”，不能遗漏关键因素！

2.  **关键点2：如何计算“方案数”？**
    * **分析**：每次选`c5`个50kg的人上船，有`C(剩余50kg人数, c5)`种选法；选`c1`个100kg的人上船，有`C(剩余100kg人数, c1)`种选法。两者相乘就是这一步的组合数，再乘原状态的方案数，就是新状态的方案数。优质题解都会预处理组合数（用杨辉三角或阶乘+逆元），避免重复计算。
    * 💡 **学习笔记**：组合数是“计数类DP”的常用工具，一定要预处理！

3.  **关键点3：如何判断“最少次数”？**
    * **分析**：最少次数就是“第一个到达目标状态（出发岸没人，船在对岸）的过程数”。因为BFS是按“层级”遍历的，第一次到达目标状态的层数就是最少次数。优质题解都会在每一步检查是否到达目标状态，如果是就直接输出结果。
    * 💡 **学习笔记**：BFS的“层级性”天然适合找最短路径，和DP结合就能同时计数！

### ✨ 解题技巧总结
- **技巧1：预处理组合数**：用杨辉三角或阶乘+逆元预处理组合数，避免重复计算。
- **技巧2：用滚动数组优化空间**：如果状态只依赖前一步，可以用滚动数组把空间复杂度从O(n²)降到O(1)。
- **技巧3：用奇偶性区分状态**：比如“去对岸”和“回来”可以用过程数的奇偶性区分，简化转移逻辑。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我选了**zztqwq的代码**作为通用核心实现——它用滚动数组优化了空间，思路清晰，代码简洁，非常适合作为模板！
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码来自zztqwq的题解，用滚动数组优化空间，预处理阶乘和逆元计算组合数，状态定义简洁，转移逻辑清晰。
* **完整核心代码**：
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    inline int read() {
        int x=0,f=1;char c=getchar();
        while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
        while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
        return x*f;
    }
    const int mod=1e9+7,N=310;
    inline int qpow(int a,int n) {
        int ans=1;
        while(n) {
            if(n&1)ans=(long long)ans*a%mod;
            a=(long long)a*a%mod;
            n>>=1;
        }
        return ans;
    }
    int inv[N],p[N];
    int binom(int n,int m) {
        if(n<0||m<0||n<m)return 0;
        return (long long)p[n]*inv[n-m]%mod*inv[m]%mod;
    }
    int f[2][60][60]; // f[pos][j][k]: 船在pos岸，对岸有j个50kg、k个100kg的方案数
    int main() {
        // 预处理阶乘p和逆元inv
        p[0]=inv[0]=1;
        for(int i=1;i<=50;i++){
            p[i]=(long long)p[i-1]*i%mod;
            inv[i]=qpow(p[i],mod-2);
        }
        int n=read(),K=read(),tot5=0,tot1=0;
        for(int i=1;i<=n;i++){
            int x=read();
            tot5+=(x==50);
            tot1+=(x==100);
        }
        memset(f,0,sizeof(f));
        f[1][0][0]=1; // 初始状态：船在出发岸（1），对岸0人
        for(int i=1;i<=4*n;i++){ // 最多4n次过程（超过则无解）
            int cur=i&1; // 当前船的位置（0=对岸，1=出发岸）
            memset(f[cur^1],0,sizeof(f[cur^1])); // 清空下一个状态
            for(int j=0;j<=tot5;j++){
                for(int k=0;k<=tot1;k++){
                    if(f[cur][j][k]==0)continue; // 该状态无方案，跳过
                    if(cur==1){ // 船在出发岸：去对岸
                        for(int c5=0;c5<=tot5-j;c5++){
                            for(int c1=0;c1<=tot1-k;c1++){
                                if(c5==0&&c1==0)continue; // 至少1人
                                if(50*c5+100*c1>K)continue; // 不超过载重
                                // 新状态：船到对岸（cur^1=0），对岸j+c5个50kg，k+c1个100kg
                                f[cur^1][j+c5][k+c1]=(f[cur^1][j+c5][k+c1]+
                                    (long long)binom(tot5-j,c5)*binom(tot1-k,c1)%mod*f[cur][j][k]%mod)%mod;
                            }
                        }
                    }else{ // 船在对岸：回来
                        for(int c5=0;c5<=j;c5++){
                            for(int c1=0;c1<=k;c1++){
                                if(c5==0&&c1==0)continue;
                                if(50*c5+100*c1>K)continue;
                                // 新状态：船到出发岸（cur^1=1），对岸j-c5个50kg，k-c1个100kg
                                f[cur^1][j-c5][k-c1]=(f[cur^1][j-c5][k-c1]+
                                    (long long)binom(j,c5)*binom(k,c1)%mod*f[cur][j][k]%mod)%mod;
                            }
                        }
                    }
                }
            }
            // 检查是否到达目标状态：船在对岸（cur^1=0），对岸有tot5个50kg、tot1个100kg
            if(f[cur^1][tot5][tot1]){
                printf("%d\n%d",i,f[cur^1][tot5][tot1]);
                return 0;
            }
        }
        printf("-1\n0"); // 无解
        return 0;
    }
    ```
* **代码解读概要**：
  1. **预处理组合数**：用`p[i]`存i的阶乘，`inv[i]`存i的逆元，`binom(n,m)`计算组合数`C(n,m)`。
  2. **初始化状态**：`f[1][0][0]=1`表示初始时船在出发岸（1），对岸0人，方案数1。
  3. **状态转移**：循环处理每一次过程（i从1到4n），根据船的位置（cur）枚举上船的人数（c5、c1），更新下一个状态的方案数。
  4. **检查目标状态**：每一步结束后，检查是否到达“对岸有所有的人”的状态，如果是就输出次数和方案数。

---
<code_intro_selected>
接下来，我们剖析两份优质题解的核心片段，看看它们的亮点！
</code_intro_selected>

**题解一：(来源：gesong)**
* **亮点**：用“过程数的奇偶性”区分“去对岸”和“回来”，逻辑直观。
* **核心代码片段**：
    ```cpp
    for (int i=1;i<=4*n;i++)
        for (int j=0;j<=x;j++)
            for (int k=0;k<=min(y,n-j);k++){
                if (i&1){ // 奇数过程：去对岸
                    for (int a=0;a<=x-j;a++)
                        for (int b=0;b<=y-k;b++)
                            if (!(a==0&&b==0)&&50*a+100*b<=m)
                                f[i][j][k]=(f[i][j][k]+f[i-1][j+a][k+b]*C[j+a][a]%mod*C[k+b][b]%mod)%mod;
                    if (f[i][0][0]){cout <<i<<endl<<f[i][0][0];return 0;}
                }
                else{ // 偶数过程：回来
                    for (int a=0;a<=j;a++)
                        for (int b=0;b<=k;b++)
                            if (!(a==0&&b==0)&&50*a+100*b<=m)
                                f[i][j][k]=(f[i][j][k]+f[i-1][j-a][k-b]*C[x-j+a][a]%mod*C[y-k+b][b]%mod)%mod;
                }
            }
    ```
* **代码解读**：
  - `i&1`判断过程数的奇偶性：奇数表示“去对岸”，偶数表示“回来”。
  - 去对岸时，枚举从出发岸选`a`个50kg、`b`个100kg的人，更新`f[i][j][k]`（`j`是出发岸剩余的50kg人数，`k`是剩余的100kg人数）。
  - 回来时，枚举从对岸选`a`个50kg、`b`个100kg的人，更新`f[i][j][k]`。
* 💡 **学习笔记**：用奇偶性区分状态，能简化转移逻辑，避免额外的变量存储船的位置！

**题解二：(来源：SevenDawns)**
* **亮点**：用BFS队列模拟状态转移，同时记录步数和方案数。
* **核心代码片段**：
    ```cpp
    struct kk{ll i,j,k;}sh[1000001]; // 队列：存储状态（出发岸的50kg、100kg人数，船的位置）
    void bfs(ll i1,ll j1,ll wh){
        sh[0]={i1,j1,wh}; ll l=0,r=1;
        while(l<r){
            ll nowi=sh[l].i,nowj=sh[l].j,nowh=sh[l].k; l++;
            if(nowh==1){ // 船在出发岸：去对岸
                for(ll x=0;x<=nowi;x++)
                    for(ll y=0;y<=nowj;y++){
                        if(50*x+100*y>w||(x==0&&y==0))continue;
                        ll xi=nowi-x,xj=nowj-y,xwh=0;
                        if(step[xi][xj][xwh]){
                            if(step[nowi][nowj][nowh]+1==step[xi][xj][xwh])
                                dp[xi][xj][xwh]=(dp[xi][xj][xwh]+b[nowi+1][x+1]*b[nowj+1][y+1]%mod*dp[nowi][nowj][nowh]%mod)%mod;
                        }else{
                            step[xi][xj][xwh]=step[nowi][nowj][nowh]+1;
                            dp[xi][xj][xwh]=b[nowi+1][x+1]*b[nowj+1][y+1]%mod*dp[nowi][nowj][nowh]%mod;
                            sh[r++]={xi,xj,xwh};
                        }
                    }
            }
            // ... 对岸回来的逻辑类似
        }
    }
    ```
* **代码解读**：
  - 用队列`sh`存储待处理的状态，`step[i][j][k]`记录到达该状态的最少步数，`dp[i][j][k]`记录方案数。
  - 处理出发岸的状态时，枚举上船的`x`（50kg）和`y`（100kg），计算新状态`xi`（剩余50kg）、`xj`（剩余100kg）、`xwh`（船到对岸）。
  - 如果新状态已经被访问过：如果步数相同，累加方案数；否则更新步数和方案数。
* 💡 **学习笔记**：BFS+DP的混合思路，能直观地模拟“每一步的选择”，适合理解状态转移的过程！

---

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你更直观地“看”到算法的执行过程，我设计了一个**8位像素风的动画**，结合复古游戏元素，让学习更有趣！
</visualization_intro>

  * **动画演示主题**：《像素过河大冒险》——你将扮演“船老大”，指挥50kg（蓝色）和100kg（红色）的像素人过河，目标是用最少次数把所有人送到对岸。

  * **核心演示内容**：
    - 展示“出发岸→河→对岸”的像素场景；
    - 每一步动画展示“选人参船→船移动→对岸人数变化”；
    - 实时显示当前次数和方案数。

  * **设计思路简述**：
    - 用8位像素风（FC红白机风格）营造复古氛围，降低学习压力；
    - 用不同颜色区分50kg和100kg的人，清晰展示人数变化；
    - 加入“上船闪烁”“船滑动”等动画效果，强化操作记忆；
    - 用音效（如“叮”表示上船，“呜”表示船移动，“滴”表示到达对岸）增强互动感。

  * **动画帧步骤与交互关键点**：
    1. **场景初始化**：
       - 屏幕左侧是“出发岸”（绿色草地），右侧是“对岸”（棕色土地），中间是“河”（蓝色水）；
       - 出发岸有`tot5`个蓝色像素块（50kg）和`tot1`个红色像素块（100kg）；
       - 船（黄色矩形）在出发岸；
       - 顶部显示“次数：0”“方案数：1”；
       - 控制面板（底部）有“单步”“自动”“重置”按钮，以及速度滑块。
    2. **第一步：去对岸**：
       - 枚举上船的人：比如选2个蓝色像素块（50kg），这两个像素块开始闪烁（红色边框）；
       - 船滑动到对岸（从左到右），伴随“呜”的音效；
       - 对岸的蓝色像素块增加2个，出发岸的蓝色像素块减少2个；
       - 顶部次数变为“1”，方案数根据组合数更新。
    3. **第二步：回来**：
       - 从对岸选1个蓝色像素块回来，该像素块闪烁；
       - 船滑动回出发岸，伴随“呜”的音效；
       - 出发岸的蓝色像素块增加1个，对岸的蓝色像素块减少1个；
       - 顶部次数变为“2”。
    4. **目标达成**：
       - 当出发岸的像素块为0，船在对岸时，播放“胜利”音效（上扬的8位音乐），屏幕显示“成功！最少次数：X，方案数：Y”。
    5. **交互控制**：
       - 单步：点击一次执行一步；
       - 自动：按设定速度（滑块调节）自动执行；
       - 重置：回到初始状态，重新开始。

  * **旁白提示**：
    - （选人参船时）“现在要选2个50kg的人上船，注意看他们的闪烁！”；
    - （船移动时）“船要去对岸啦，听‘呜’的声音！”；
    - （到达对岸时）“这次送了2个人过去，次数变成1啦！”。

<visualization_conclusion>
通过这个像素动画，你能清晰地看到“状态转移”的每一步——从选人参船到船移动，再到人数变化。复古游戏元素让学习更轻松，音效和动画效果帮你记住关键步骤！
</visualization_conclusion>

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
这道题的“状态DP+计数”思路，能解决很多“最短路径+方案数”的问题。比如：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - **问题1**：求从A点到B点的最短路径数（状态是当前位置，转移是走一步，计数是路径数）；
    - **问题2**：求爬楼梯的最少步数和方案数（每次爬1或2步，状态是当前楼层，转移是爬1或2步）；
    - **问题3**：求迷宫的最短路径数（状态是当前坐标，转移是上下左右走，计数是路径数）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1809** - 过河问题
          * 🗣️ **推荐理由**：经典的过河问题，求最少次数，能帮你巩固“状态定义”的思路。
    2.  **洛谷 P2669** - 金币
          * 🗣️ **推荐理由**：动态规划统计方案数，能帮你熟练掌握“组合数+DP”的技巧。
    3.  **洛谷 P3956** - 棋盘
          * 🗣️ **推荐理由**：状态DP+最短路径，能帮你拓展“多状态因素”的处理能力。

---

## 7. 学习心得与经验分享 (若有)

<insights_intro>
题解中有些作者的心得很有价值，我帮你摘录了两条：
</insights_intro>

> **参考经验 (来自lmy_2011)**：“刚开始我以为这题是数学题，用‘慢者相伴’的方法，但后来发现要考虑载重k，太麻烦了。最后才意识到是动态规划题——状态转移能覆盖所有情况！”
>
> **点评**：这很典型！很多问题看起来像数学题，但其实用动态规划能更系统地解决。遇到问题时，先想“能不能抽象成状态转移”，而不是直接套数学公式。

> **参考经验 (来自SevenDawns)**：“我在处理相同状态时，一开始直接标记为‘已访问’，结果漏掉了‘次数相同但方案数不同’的情况。后来改成‘次数相同则累加方案数’，才解决了问题！”
>
> **点评**：这提醒我们——在“计数类BFS”中，不能像普通BFS那样标记“已访问”就跳过，要考虑“相同状态的不同方案数”，否则会统计不全！

---

<conclusion>
本次关于“Greg and Friends”的分析就到这里啦！这道题的核心是“状态DP+计数”，通过抽象状态、处理组合数、用BFS找最短次数，你就能解决这类问题。记住：**状态定义要完整，组合数要预处理，边界条件要严谨**！下次遇到类似问题，你一定能轻松解决！💪
</conclusion>

---
处理用时：222.11秒