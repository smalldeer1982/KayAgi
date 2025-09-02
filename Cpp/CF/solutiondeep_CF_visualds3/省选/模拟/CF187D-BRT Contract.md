# 题目信息

# BRT Contract

## 题目描述

In the last war of PMP, he defeated all his opponents and advanced to the final round. But after the end of semi-final round evil attacked him from behind and killed him! God bless him.

Before his death, PMP signed a contract with the bus rapid transit (BRT) that improves public transportations by optimizing time of travel estimation. You should help PMP finish his last contract.

Each BRT line is straight line that passes $ n $ intersecting on its ways. At each intersection there is traffic light that periodically cycles between green and red. It starts illuminating green at time zero. During the green phase which lasts for $ g $ seconds, traffic is allowed to proceed. After the green phase the light changes to red and remains in this color for $ r $ seconds. During the red phase traffic is prohibited from proceeding. If a vehicle reaches the intersection exactly at a time when the light changes to red, it should stop, but the vehicle is clear to proceed if the light has just changed to green.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF187D/62435a41fe7e90193c8a9b88800f99834c7d7ef9.png)All traffic lights have the same timing and are synchronized. In other words the period of red (and green) phase is the same for all of traffic lights and they all start illuminating green at time zero.

The BRT Company has calculated the time that a bus requires to pass each road segment. A road segment is the distance between two consecutive traffic lights or between a traffic light and source (or destination) station. More precisely BRT specialists provide $ n+1 $ positive integers $ l_{i} $ , the time in seconds that a bus needs to traverse $ i $ -th road segment in the path from source to destination. The $ l_{1} $ value denotes the time that a bus needs to pass the distance between source and the first intersection. The $ l_{n+1} $ value denotes the time between the last intersection and destination.

In one day $ q $ buses leave the source station. The $ i $ -th bus starts from source at time $ t_{i} $ (in seconds). Decision makers of BRT Company want to know what time a bus gets to destination?

The bus is considered as point. A bus will always move if it can. The buses do not interfere with each other.

## 说明/提示

In the first sample, buses #1, #2 and #5 will reach the destination without waiting behind the red light. But buses #3 and #4 should wait.

In the second sample, first bus should wait at third, fourth and fifth intersections. Second and third buses should wait only at the fifth intersection.

## 样例 #1

### 输入

```
1 3 2
5 2
5
1
2
3
4
5
```

### 输出

```
8
9
12
12
12
```

## 样例 #2

### 输入

```
5 3 7
10 1 1 8 900000005 1000000000
3
1
10
1000000000
```

### 输出

```
1900000040
1900000040
2900000030
```

# AI分析结果

---
# 💡 Kay的C++算法解析：BRT Contract 深入学习指南 💡

<introduction>
今天我们来一起分析“BRT Contract”这道C++编程题。这道题的核心是模拟公交车在多个红绿灯路口的行驶过程，计算不同出发时间下到达终点的时间。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用（数据结构优化与预处理）`

🗣️ **初步分析**：
> 解决“BRT Contract”的关键在于高效处理红绿灯的周期性等待问题。红绿灯的周期是 `g`（绿灯）+ `r`（红灯）秒，所有红绿灯同步。公交车经过每个路口时，若遇到红灯需等待至绿灯。问题的难点在于：如何快速判断每个出发时间的公交车会在哪个路口首次遇到红灯，并计算后续的等待时间。

- **核心思路**：多个题解采用“预处理+数据结构优化”策略。通过倒序预处理每个路口的“首次红灯位置”，利用线段树或`map`维护区间覆盖，将大值域的问题转化为区间查询问题。例如，预处理每个路口 `i` 出发时，首次遇到红灯的位置 `j`，并记录从 `j` 到终点的时间，从而快速计算任意出发时间的总耗时。
- **核心算法流程**：倒序遍历路口，维护一个数据结构（如线段树或`map`），记录每个时间模周期 `g+r` 的余数对应的首次红灯位置。对于每个路口 `i`，计算其出发时间模周期的余数范围，若该范围属于红灯区间，则记录该位置为首次红灯点。
- **可视化设计**：采用8位像素风格，用不同颜色的方块表示绿灯（绿色）、红灯（红色）和公交车（黄色）。动画中，公交车从起点出发，每到达一个路口，检查当前时间模周期的余数：若为绿灯则继续行驶（黄色方块右移），若为红灯则等待（黄色方块闪烁，背景变红），直到绿灯亮起。数据结构（如线段树）的区间覆盖过程用动态的像素块叠加显示，关键步骤（如更新区间、查询首次红灯位置）用箭头高亮。

---

## 2. 精选优质题解参考

<eval_intro>
为了更好地理解解题过程，我从思路清晰度、代码规范性、算法有效性等方面筛选了以下优质题解：
</eval_intro>

**题解一：Zimse 的动态开点线段树解法（来源：用户 Zimse）**
* **点评**：此题解思路清晰，采用动态开点线段树维护时间模周期的余数区间，倒序预处理每个路口的首次红灯位置。代码结构规范，变量命名（如`d`表示前缀和，`f`表示从当前路口到终点的时间）直观易懂。算法时间复杂度为 `O(n log n + q)`，通过动态开点线段树高效处理大值域区间覆盖问题，是正解的典型代表。亮点在于将模周期的余数区间转化为线段树节点，避免了离散化的复杂操作。

**题解二：一粒夸克 的乱搞做法（来源：用户 一粒夸克）**
* **点评**：此解法通过记忆化优化模拟过程，在随机数据下效率接近线性。代码简洁（如用`ans`数组记录已计算的路口耗时），但最坏情况可能退化为 `O(qn)`（如第34个测试点）。亮点在于观察到“遇到红灯后后续耗时固定”的性质，通过记忆化减少重复计算，适合理解问题的核心规律。

**题解三：Durancer 的 Map 解法（来源：用户 Durancer）**
* **点评**：此题解巧妙利用`map`的区间覆盖特性，替代线段树处理大值域问题。代码中`Insert`函数通过调整`map`的键值对覆盖区间，`Find`函数快速查询首次红灯位置，思路新颖且易于理解。亮点在于用`map`的迭代器操作实现高效区间管理，适合学习数据结构的灵活应用。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下几个核心难点。结合优质题解的共性，我为大家提炼了思考方向和策略：
</difficulty_intro>

1.  **关键点1：如何高效判断首次红灯位置？**
    * **分析**：公交车到达路口 `i` 的时间为 `t`，若 `t % (g+r) >= g` 则需等待。直接模拟每个出发时间会超时。优质题解通过预处理，倒序计算每个路口 `i` 出发时，首次遇到红灯的位置 `j`，并记录从 `j` 到终点的时间。例如，用线段树或`map`维护时间模周期的余数区间，快速查询首次红灯位置。
    * 💡 **学习笔记**：预处理是解决周期性问题的关键，倒序遍历可利用后续路口的信息简化当前计算。

2.  **关键点2：如何处理大值域的区间覆盖？**
    * **分析**：时间模周期的余数范围是 `0 ~ g+r-1`，若 `g+r` 很大（如1e9），传统线段树无法存储所有节点。动态开点线段树或`map`的区间覆盖技术可解决此问题：仅创建需要的节点，用键值对表示区间覆盖关系。
    * 💡 **学习笔记**：动态数据结构（如动态开点线段树、`map`）适合处理大值域的区间问题，避免空间浪费。

3.  **关键点3：如何计算等待时间与后续耗时？**
    * **分析**：若在路口 `j` 遇到红灯，需等待 `(g+r - (t % (g+r)))` 秒。后续耗时是固定的（因为等待后出发时间模周期为0），可预处理从 `j` 到终点的时间 `f[j]`。例如，`f[j] = (到达j的时间 + 等待时间) + f[下一个红灯位置]`。
    * 💡 **学习笔记**：利用周期性，将问题分解为“首次红灯前的行驶时间”+“首次红灯后的固定耗时”，简化计算。

### ✨ 解题技巧总结
<summary_best_practices>
- **问题分解**：将总耗时分解为“首次红灯前的行驶时间”和“首次红灯后的固定耗时”，通过预处理后者简化计算。
- **模运算应用**：利用时间模周期的余数判断红绿灯状态，将连续时间问题转化为周期性区间问题。
- **动态数据结构**：大值域区间覆盖问题用动态开点线段树或`map`处理，避免空间爆炸。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。这有助于我们对整体解题框架有一个把握。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了Zimse的动态开点线段树思路，结合预处理和区间查询，是正解的典型实现。
* **完整核心代码**：
    ```cpp
    #include <cstdio>
    #include <algorithm>
    #include <vector>

    #define int long long
    #define Lid (ch[id][0])
    #define Rid (ch[id][1])

    using namespace std;

    int read() {
        int qrx=0, qry=1; char qrc=getchar();
        while(qrc<'0'||qrc>'9') { if(qrc=='-') qry=-1; qrc=getchar(); }
        while(qrc>='0'&&qrc<='9') qrx=qrx*10+qrc-48, qrc=getchar();
        return qrx*qry;
    }

    const int N=2e6+7, Mod=998244353, INF=1e12+7;
    int n, m, G, R, d[N], X[N], f[N], Q, rt=1;
    int ch[N*8][2], tot=1, val[N*8];

    void pushdown(int id, int len) {
        if(val[id] && len>1) {
            if(!Lid) Lid=++tot;
            if(!Rid) Rid=++tot;
            val[Lid]=val[Rid]=val[id], val[id]=0;
        }
    }

    void update(int L, int R, int id, int l, int r, int x) {
        pushdown(id, R-L+1);
        if(l<=L && r>=R) val[id]=x, pushdown(id, R-L+1);
        else {
            int M=(L+R)>>1;
            if(l<=M) update(L, M, Lid, l, r, x);
            if(r>M) update(M+1, R, Rid, l, r, x);
        }
    }

    int query(int L, int R, int id, int x) {
        pushdown(id, R-L+1);
        if(L==R) return val[id];
        int M=(L+R)>>1;
        if(x<=M) return query(L, M, Lid, x);
        else return query(M+1, R, Rid, x);
    }

    int Query(int t) {
        int p=query(0, m-1, rt, t%m);
        int ans=t+X[p]+f[p];
        if(p<=n) ans+=m-(X[p]+t)%m;
        return ans;
    }

    signed main() {
        n=read(), G=read(), R=read(), m=G+R;
        for(int i=1; i<=n+1; i++) d[i]=read(), X[i]=X[i-1]+d[i];
        update(0, m-1, rt, 0, m-1, n+1);
        for(int i=n, p=0; i>=1; i--) {
            p=m-X[i]%m, f[i]=Query(p)-X[i]-p, p=X[i]%m;
            if(p<=G) update(0, m-1, rt, G-p, m-1-p, i);
            else update(0, m-1, rt, 0, m-1-p, i), update(0, m-1, rt, m-p+G, m-1, i);
        }
        Q=read();
        for(int i=1; i<=Q; i++) printf("%lld\n", Query(read()));
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取输入，计算前缀和 `X` 表示到达各路口的累计时间。通过动态开点线段树 `rt` 维护时间模周期的余数区间，倒序预处理每个路口 `i` 的首次红灯位置 `p`，并计算从 `i` 到终点的时间 `f[i]`。查询时，通过线段树找到首次红灯位置 `p`，计算总耗时为 `t + X[p] + f[p] + 等待时间`。

---
<code_intro_selected>
接下来，我们将剖析优质题解的核心代码片段，点出各自的亮点和关键思路。
</code_intro_selected>

**题解一：Zimse 的动态开点线段树解法（来源：用户 Zimse）**
* **亮点**：动态开点线段树高效处理大值域区间覆盖，倒序预处理首次红灯位置。
* **核心代码片段**：
    ```cpp
    void pushdown(int id, int len) {
        if(val[id] && len>1) {
            if(!Lid) Lid=++tot;
            if(!Rid) Rid=++tot;
            val[Lid]=val[Rid]=val[id], val[id]=0;
        }
    }

    void update(int L, int R, int id, int l, int r, int x) {
        pushdown(id, R-L+1);
        if(l<=L && r>=R) val[id]=x, pushdown(id, R-L+1);
        else {
            int M=(L+R)>>1;
            if(l<=M) update(L, M, Lid, l, r, x);
            if(r>M) update(M+1, R, Rid, l, r, x);
        }
    }
    ```
* **代码解读**：
    > `pushdown` 函数处理线段树的懒标记下传，仅在需要时创建子节点（动态开点）。`update` 函数更新区间 `[l, r]` 为 `x`（表示该区间内的时间模周期余数对应的首次红灯位置是 `x`）。通过动态开点，避免了大值域下的空间浪费，适合处理 `g+r` 很大的情况。
* 💡 **学习笔记**：动态开点线段树通过“按需创建节点”解决大值域问题，`pushdown` 是实现懒标记的关键。

**题解二：一粒夸克 的乱搞做法（来源：用户 一粒夸克）**
* **亮点**：记忆化优化模拟过程，随机数据下高效。
* **核心代码片段**：
    ```cpp
    for(int i=1; i<=n; i++) {
        if(x%(g+r)>=g) {
            x+=(g+r-x%(g+r));
            if(~ans[i]) {
                x+=ans[i]; break;
            }
            vec.push_back(make_pair(i,x));
        }
        x+=a[i];
    }
    for(auto it:vec) ans[it.first]=x-it.second;
    ```
* **代码解读**：
    > 模拟公交车行驶过程，若遇到红灯则等待，并记录该路口 `i` 到终点的耗时 `ans[i]`。后续相同路口遇到红灯时，直接使用 `ans[i]` 避免重复计算。`vec` 存储需要记忆的路口，循环结束后更新 `ans` 数组。
* 💡 **学习笔记**：记忆化适用于重复子问题，可显著减少计算量，但需注意最坏情况的时间复杂度。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“首次红灯位置查询”和“等待时间计算”的过程，我设计了一个8位像素风格的动画演示方案。
</visualization_intro>

  * **动画演示主题**：`像素公交的红绿灯挑战`

  * **核心演示内容**：公交车从起点出发，经过多个红绿灯路口，遇到红灯时等待，最终到达终点。动画展示每个路口的红绿灯状态（绿/红）、当前时间模周期的余数、首次红灯位置查询过程。

  * **设计思路简述**：采用FC红白机风格，用绿色方块表示绿灯，红色方块表示红灯，黄色方块表示公交车。通过步进控制和高亮提示，帮助学习者观察每个步骤的时间变化和逻辑判断。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕左侧显示像素化的道路（横向排列的方块，每个方块代表一个路口），右侧显示控制面板（开始/暂停、单步、重置按钮，速度滑块）。
        - 顶部显示当前时间 `t` 和模周期余数 `t % (g+r)`。

    2.  **出发与行驶**：
        - 公交车（黄色方块）从起点（最左端）出发，每到达一个路口，计算当前时间模周期的余数。
        - 绿灯（绿色背景）：公交车继续右移，时间增加路段行驶时间。
        - 红灯（红色背景）：公交车停止（闪烁），时间增加等待时间（`g+r - 余数`），背景变为绿色后继续行驶。

    3.  **首次红灯位置查询**：
        - 线段树/`map` 的区间覆盖过程用动态的蓝色方块叠加显示，每个方块代表一个时间模周期的余数区间。
        - 查询时，用白色箭头指向对应的区间，高亮首次红灯位置的路口。

    4.  **目标达成**：
        - 公交车到达终点时，播放“叮”的音效，终点方块闪烁绿色，显示总耗时。

  * **旁白提示**：
    - “当前时间模周期余数是5，绿灯（g=10），可以通过！”
    - “余数是12，超过绿灯时间（g=10），需要等待3秒！”
    - “线段树查询到首次红灯位置是第3个路口，后续耗时已预处理，总时间加上即可。”

<visualization_conclusion>
通过这个像素动画，我们能直观看到公交车在每个路口的决策过程，以及线段树如何高效处理大值域的区间查询，从而理解预处理和数据结构优化的核心作用。
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的解法后，我们可以进一步思考该算法/技巧的适用范围和变形应用。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 周期性问题（如红绿灯、任务调度）：利用模运算将连续时间转化为周期性区间。
      - 首次事件查询（如首次碰撞、首次满足条件）：通过预处理和数据结构（线段树、`map`）快速定位。
      - 大值域区间管理：动态开点线段树、`map` 适用于值域大但实际覆盖区间少的场景。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1821 [FJOI2007] 树的路径覆盖**  
          * 🗣️ **推荐理由**：考察路径覆盖的预处理和动态规划，与本题的预处理思想类似。
    2.  **洛谷 P1073 [NOIP2009 提高组] 最优贸易**  
          * 🗣️ **推荐理由**：涉及区间查询和最优决策，锻炼数据结构的灵活应用。
    3.  **洛谷 P3834 [模板] 可持久化线段树 2**  
          * 🗣️ **推荐理由**：深入理解线段树的动态开点和区间查询，为解决大值域问题打基础。

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，这些经验对我们很有借鉴意义：
</insights_intro>

> **参考经验 (来自用户 lfxxx)**：“模拟考最后一题是这道题，要是数组开大就场切了，最后不小心挂了15分。”
>
> **点评**：数组大小是编程中常见的边界问题。在处理大值域或多测试用例时，需根据题目数据范围合理设置数组大小（如本题中动态开点线段树的节点数）。调试时可通过打印中间变量或小规模测试用例验证逻辑。

---

<conclusion>
本次关于“BRT Contract”的C++解题分析就到这里。希望这份学习指南能帮助大家理解红绿灯问题的核心规律，掌握预处理和数据结构优化的技巧。记住，多动手编写代码、调试测试，是提升编程能力的关键！下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：146.71秒