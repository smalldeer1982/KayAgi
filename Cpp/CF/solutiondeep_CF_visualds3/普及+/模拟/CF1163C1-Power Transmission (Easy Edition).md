# 题目信息

# Power Transmission (Easy Edition)

## 题目描述

This problem is same as the next one, but has smaller constraints.

It was a Sunday morning when the three friends Selena, Shiro and Katie decided to have a trip to the nearby power station (do not try this at home). After arriving at the power station, the cats got impressed with a large power transmission system consisting of many chimneys, electric poles, and wires. Since they are cats, they found those things gigantic.

At the entrance of the station, there is a map describing the complicated wiring system. Selena is the best at math among three friends. He decided to draw the map on the Cartesian plane. Each pole is now a point at some coordinates $ (x_i, y_i) $ . Since every pole is different, all of the points representing these poles are distinct. Also, every two poles are connected with each other by wires. A wire is a straight line on the plane infinite in both directions. If there are more than two poles lying on the same line, they are connected by a single common wire.

Selena thinks, that whenever two different electric wires intersect, they may interfere with each other and cause damage. So he wonders, how many pairs are intersecting? Could you help him with this problem?

## 说明/提示

In the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/2317b27306c4c65175012212cdceb02039be0972.png)In the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/0792ee139dbdc603551bd0c872a1bea92551eac5.png)Note that the three poles $ (0, 0) $ , $ (0, 2) $ and $ (0, 4) $ are connected by a single wire.

In the third example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1163C1/9e20f52f47cf7b9d491a8675d81506c0f862a971.png)

## 样例 #1

### 输入

```
4
0 0
1 1
0 3
1 2
```

### 输出

```
14
```

## 样例 #2

### 输入

```
4
0 0
0 2
0 4
2 0
```

### 输出

```
6
```

## 样例 #3

### 输入

```
3
-1 -1
1 0
3 1
```

### 输出

```
0
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Power Transmission (Easy Edition) 深入学习指南 💡

<introduction>
今天我们来一起分析“Power Transmission (Easy Edition)”这道C++编程题。本指南将帮助大家梳理题目思路，理解如何统计平面直线相交对数，并掌握关键解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`枚举与统计（含共线点处理）`

🗣️ **初步分析**：
> 解决这道题的关键在于：首先找出所有不同的直线（处理共线点的重复问题），然后统计这些直线中斜率不同的对数（相交的条件是斜率不同）。  
> 简单来说，我们需要两步走：第一步是“去重”——把共线的点对归为同一条直线；第二步是“统计”——计算不同直线中斜率不同的对数。  
> 核心难点在于如何高效去重（避免重复计算同一条直线）和如何用整数运算表示斜率（避免浮点精度问题）。  
> 优质题解（如FFTotoro的解法）通过标记点对的方式去重：枚举每对点(i,j)，找到所有与(i,j)共线的点k，将这些点对(i,k)、(j,k)等统一标记为已处理，确保每条直线只被计算一次。然后，用向量(dx, dy)表示直线的斜率方向（dx=x_i-x_j，dy=y_i-y_j），通过判断dx1*dy2是否等于dx2*dy1来比较斜率是否相同（避免浮点运算）。  
> 可视化设计上，我们可以用像素动画模拟枚举点对、标记共线点、统计直线斜率的过程：例如，用不同颜色的像素点表示平面上的点，当枚举点对(i,j)时，高亮这两个点并检查其他点是否共线（绿色标记共线点），标记完成后这些点对变为灰色（已处理），最后统计所有直线的斜率（用不同颜色线段表示），计算相交对数时线段交叉处闪烁。

---

## 2. 精选优质题解参考

<eval_intro>
通过对题解的思路清晰度、代码规范性、算法有效性等维度评估，以下题解评分≥4星，值得重点学习：
</eval_intro>

**题解一：来源（FFTotoro）**
* **点评**：这份题解思路非常清晰！它通过“标记已处理点对”的方法巧妙解决了共线点的重复问题。代码中使用二维布尔数组`b`标记已处理的点对，避免同一条直线被多次计算。关键函数`pd`通过向量叉积判断三点共线（数学上等价于斜率相同），逻辑简洁且准确。算法时间复杂度为O(n³)（n≤100时完全可行），空间复杂度合理。代码变量命名直观（如`v`存储共线点索引，`d`存储直线向量），边界处理严谨（如枚举i<j避免重复）。实践价值高，可直接用于竞赛环境。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下几个关键点或难点。结合优质题解的共性，我为大家提炼了核心思考方向和策略：
</difficulty_intro>

1.  **关键点1：如何避免重复计算同一条直线？**
    * **分析**：题目中，共线的点对（如A-B、A-C、B-C）属于同一条直线，需避免重复统计。FFTotoro的题解通过标记数组`b[i][j]`实现：当处理点对(i,j)时，找到所有与(i,j)共线的点k，将(i,k)、(j,k)等点对标记为已处理（`b[i][j]=true`），后续枚举时直接跳过。
    * 💡 **学习笔记**：标记法是解决重复问题的常用技巧，核心是找到“唯一标识”（如点对(i,j)）并记录已处理状态。

2.  **关键点2：如何用整数运算表示斜率，避免浮点精度问题？**
    * **分析**：直接使用浮点数（如double）存储斜率可能因精度误差导致错误。优质题解用向量(dx, dy)表示直线的斜率方向（dx=x_i-x_j，dy=y_i-y_j），并通过判断dx1*dy2是否等于dx2*dy1来比较斜率是否相同（数学上等价于斜率相等）。
    * 💡 **学习笔记**：用向量的整数比（最简形式）表示斜率，是处理精度问题的经典方法。

3.  **关键点3：如何统计不同直线的相交对数？**
    * **分析**：两条直线相交的条件是斜率不同。统计所有不同直线后，计算其中斜率不同的对数即可。注意每对直线被计算两次（i和j，j和i），最终结果需除以2。
    * 💡 **学习笔记**：总对数=总直线数选2的组合数 - 斜率相同的直线对数选2的组合数。

### ✨ 解题技巧总结
<summary_best_practices>
-  **共线点处理**：通过向量叉积（(y2-y1)*(x3-x1) == (x2-x1)*(y3-y1)）快速判断三点共线。
-  **重复标记**：用二维数组标记已处理的点对，确保每条直线只统计一次。
-  **斜率表示**：用向量(dx, dy)的整数比代替浮点数，避免精度问题。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了FFTotoro题解的核心思路，通过标记点对去重，并使用向量表示斜率，是简洁高效的典型实现。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef pair<int, int> pii;

    // 判断三点是否共线（向量叉积为0）
    bool pd(pii a, pii b, pii c) {
        return (b.second - a.second) * (c.first - a.first) == 
               (b.first - a.first) * (c.second - a.second);
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int n;
        cin >> n;
        vector<pii> a(n);
        for (auto &p : a) cin >> p.first >> p.second;

        vector<vector<bool>> vis(n, vector<bool>(n, false)); // 标记已处理的点对
        vector<pii> dirs; // 存储各直线的方向向量(dx, dy)

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (vis[i][j]) continue; // 已处理过，跳过

                vector<int> collinear = {i, j}; // 存储所有与(i,j)共线的点的索引
                for (int k = j + 1; k < n; ++k) {
                    if (pd(a[i], a[j], a[k])) {
                        collinear.push_back(k);
                    }
                }

                // 标记所有共线点对为已处理
                for (int u : collinear) {
                    for (int v : collinear) {
                        if (u < v) vis[u][v] = true;
                    }
                }

                // 计算方向向量(dx, dy)，并存储
                int dx = a[i].first - a[j].first;
                int dy = a[i].second - a[j].second;
                dirs.emplace_back(dx, dy);
            }
        }

        // 统计斜率不同的直线对数
        int total = 0;
        for (int i = 0; i < dirs.size(); ++i) {
            for (int j = i + 1; j < dirs.size(); ++j) {
                // 斜率不同的条件：dx1*dy2 != dx2*dy1
                if (dirs[i].first * dirs[j].second != dirs[i].second * dirs[j].first) {
                    total++;
                }
            }
        }

        cout << total << endl;
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取所有点的坐标，然后枚举每对点(i,j)。对于每对点，找到所有与(i,j)共线的点，将这些点对标记为已处理（避免重复统计同一条直线）。接着，计算该直线的方向向量(dx, dy)并存储。最后，枚举所有直线的方向向量，统计斜率不同的对数，输出结果。

---
<code_intro_selected>
接下来，我们将剖析FFTotoro题解的核心代码片段，并点出其亮点和关键思路。
</code_intro_selected>

**题解一：来源（FFTotoro）**
* **亮点**：通过标记数组`vis`避免重复统计共线点对，用向量叉积判断三点共线，逻辑简洁高效。
* **核心代码片段**：
    ```cpp
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++){
            if(vis[i][j])continue;
            vector<int> v={i,j};
            for(int k=j+1;k<n;k++)
                if(pd(a[i],a[j],a[k]))v.emplace_back(k);
            for(auto &u:v)for(auto &v:v)vis[u][v]=true;
            dirs.emplace_back(a[i].first - a[j].first, a[i].second - a[j].second);
        }
    ```
* **代码解读**：
    > 这段代码是去重和统计直线的核心。外层循环枚举点对(i,j)（i<j避免重复），若`vis[i][j]`为true则跳过（已处理）。然后，通过`pd`函数找到所有与(i,j)共线的点k，存入`v`数组。接着，将`v`中所有点对(u,v)标记为已处理（`vis[u][v]=true`），确保后续枚举时不会重复计算同一条直线。最后，计算(i,j)的方向向量(dx, dy)并存入`dirs`数组。
* 💡 **学习笔记**：标记法的关键是找到“唯一标识”（这里是点对(i,j)），并确保所有属于同一直线的点对都被标记，避免重复。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解“枚举点对-标记共线点-统计直线斜率”的过程，我设计了一个8位像素风格的动画演示方案。
</visualization_intro>

  * **动画演示主题**：`像素直线探险家`（复古FC游戏风格）

  * **核心演示内容**：展示如何枚举点对、标记共线点、统计直线斜率，并最终计算相交对数。

  * **设计思路简述**：采用8位像素风（如FC游戏的简洁色块），通过颜色变化和动画效果突出关键步骤（如共线点标记、斜率统计），配合音效强化操作记忆（如标记时的“叮”声）。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕左侧是16x16像素的平面网格，用不同颜色的像素点表示输入的n个点（如红色点）。
          * 右侧是控制面板，包含“单步”“自动播放”“重置”按钮和速度滑块。
          * 播放8位风格的背景音乐（轻快的电子音效）。

    2.  **枚举点对(i,j)**：
          * 初始时所有点对为灰色。当枚举到(i,j)时，这两个点变为黄色并闪烁（“当前处理点对”）。
          * 音效：“滴”的提示音。

    3.  **查找共线点**：
          * 遍历其他点k，若k与(i,j)共线（通过`pd`函数判断），则k变为绿色并滑入(i,j)的“共线点列表”（右侧显示）。
          * 音效：每找到一个共线点，播放“叮”声。

    4.  **标记已处理点对**：
          * 将(i,j)及所有共线点对（如(i,k)、(j,k)）从灰色变为深蓝色（“已处理”）。
          * 音效：标记完成时播放“唰”的音效。

    5.  **统计直线斜率**：
          * 每处理完一条直线，右侧生成一个像素线段（颜色随机，如蓝色）表示该直线的方向向量(dx, dy)。
          * 线段下方显示向量值（如“(2,1)”）。

    6.  **计算相交对数**：
          * 所有直线统计完成后，两两比较斜率。若斜率不同，两条线段交叉处闪烁红色光效。
          * 音效：每找到一对相交直线，播放“啵”声，最终输出总对数时播放“胜利”音效。

  * **旁白提示**：
      * （枚举点对时）“现在我们处理点对(i,j)，看看有哪些点和它们共线~”
      * （标记时）“这些点对已经被处理过了，后面就不用再管啦！”
      * （统计斜率时）“这条直线的方向向量是(dx, dy)，代表它的斜率哦~”

<visualization_conclusion>
通过这样的像素动画，我们可以直观看到每一步的操作，理解共线点处理和斜率统计的核心逻辑，学习起来更轻松！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解本题后，我们可以进一步思考如何将“枚举-去重-统计”的思路应用到其他问题中。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 本题的“枚举点对+标记去重”思路可用于统计平面上的其他几何特征（如最大共线点数、不同直线的交点数）。
      * 用向量表示斜率的方法可推广到需要比较直线方向的问题（如判断线段是否平行、求多边形边的方向分布）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1358** - `邮票`
          * 🗣️ **推荐理由**：需要枚举所有可能的组合并去重，锻炼“枚举+标记”的思维。
    2.  **洛谷 AT_abc248_e** - `K-colinear Line`
          * 🗣️ **推荐理由**：本题作者提到的拓展题，要求统计包含至少K个点的直线数，进一步巩固共线点处理技巧。
    3.  **洛谷 P1119** - `灾后重建`
          * 🗣️ **推荐理由**：涉及图论中的最短路径动态更新，锻炼动态问题的枚举与统计能力。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
FFTotoro在题解中提到：“再没见过这么水的*1900了……”，这提醒我们，遇到看似复杂的题目时，关键是抓住核心（如本题的“共线去重”和“斜率比较”），问题可能迎刃而解。
</insights_intro>

> **参考经验**：FFTotoro提到，处理共线点时，通过标记点对避免重复是关键。他在调试中发现，若不标记共线点对，会导致同一条直线被多次统计，最终结果错误。

> **点评**：这个经验非常实用！在处理几何问题时，“去重”是常见需求，标记法是简单有效的解决方案。动手前先想清楚“如何避免重复”，能少走很多弯路。

-----

<conclusion>
本次关于“Power Transmission (Easy Edition)”的C++解题分析就到这里。希望这份学习指南能帮助大家掌握枚举、去重和统计的核心技巧。记住，多动手写代码、多调试，几何问题也能轻松解决！下次我们再一起探索新的编程挑战！💪
</conclusion>

-----

---
处理用时：147.96秒