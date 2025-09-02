# 题目信息

# Parade

## 题目描述

No Great Victory anniversary in Berland has ever passed without the war parade. This year is not an exception. That’s why the preparations are on in full strength. Tanks are building a line, artillery mounts are ready to fire, soldiers are marching on the main square... And the air forces general Mr. Generalov is in trouble again. This year a lot of sky-scrapers have been built which makes it difficult for the airplanes to fly above the city. It was decided that the planes should fly strictly from south to north. Moreover, there must be no sky scraper on a plane’s route, otherwise the anniversary will become a tragedy. The Ministry of Building gave the data on $ n $ sky scrapers (the rest of the buildings are rather small and will not be a problem to the planes). When looking at the city from south to north as a geometrical plane, the $ i $ -th building is a rectangle of height $ h_{i} $ . Its westernmost point has the x-coordinate of $ l_{i} $ and the easternmost — of $ r_{i} $ . The terrain of the area is plain so that all the buildings stand on one level. Your task as the Ministry of Defence’s head programmer is to find an enveloping polyline using the data on the sky-scrapers. The polyline’s properties are as follows:

- If you look at the city from south to north as a plane, then any part of any building will be inside or on the boarder of the area that the polyline encloses together with the land surface.
- The polyline starts and ends on the land level, i.e. at the height equal to 0.
- The segments of the polyline are parallel to the coordinate axes, i.e. they can only be vertical or horizontal.
- The polyline’s vertices should have integer coordinates.
- If you look at the city from south to north the polyline (together with the land surface) must enclose the minimum possible area.
- The polyline must have the smallest length among all the polylines, enclosing the minimum possible area with the land.
- The consecutive segments of the polyline must be perpendicular.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF35E/23dca3b6890c3864c0838cb5956c4323cb001fd2.png) Picture to the second sample test (the enveloping polyline is marked on the right).

## 样例 #1

### 输入

```
2
3 0 2
4 1 3
```

### 输出

```
6
0 0
0 3
1 3
1 4
3 4
3 0
```

## 样例 #2

### 输入

```
5
3 -3 0
2 -1 1
4 2 4
2 3 7
3 6 8
```

### 输出

```
14
-3 0
-3 3
0 3
0 2
1 2
1 0
2 0
2 4
4 4
4 2
6 2
6 3
8 3
8 0
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Parade 深入学习指南 💡

<introduction>
今天我们来一起分析“Parade”这道C++编程题。这道题需要我们找到多个矩形的轮廓线顶点，是扫描线和线段树结合的经典应用。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`扫描线与线段树应用`

🗣️ **初步分析**：
解决“Parade”这道题，关键在于理解并运用“扫描线”与“线段树”的组合。扫描线就像一把“移动的尺子”，从左到右扫描所有矩形的左右边界，而线段树则像“高度记录员”，实时维护当前扫描位置的最大高度。当扫描线遇到矩形边界时（左边界是“开始覆盖”，右边界是“结束覆盖”），线段树会更新对应区间的高度，从而记录下高度变化的点，这些点就是轮廓线的顶点。

- **题解思路**：所有题解的核心思路高度一致：先离散化所有矩形的左右边界坐标，避免坐标范围过大；然后用扫描线按顺序处理每个边界事件（左边界或右边界），同时用线段树维护当前覆盖区间的最大高度；最后记录所有高度变化的点，形成轮廓线。不同题解的差异主要在线段树的实现细节（如递归/非递归、是否维护两个线段树）和离散化的处理方式。
- **核心难点**：如何高效维护区间最大高度（线段树的设计）、如何处理离散化后的坐标、如何避免重复记录顶点。
- **可视化设计**：我们将设计一个8位像素风格的动画，用彩色方块表示矩形，扫描线用金色竖线从左到右移动，线段树节点用堆叠的像素块动态显示当前最大高度。当扫描线遇到边界事件时，对应线段树节点颜色变化（左边界变绿色，右边界变红色），并播放“叮”的音效。高度变化时，轮廓线顶点以闪烁的白色像素点标出。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性等，以下题解因逻辑清晰、实现高效被选为优质参考（≥4星）：
</eval_intro>

**题解一：作者EnofTaiPeople**
* **点评**：此题解思路简洁直接，使用非递归线段树维护区间最大值，代码风格规范（如`mp`数组用于离散化，`tg`数组存储线段树标记）。离散化处理和线段树更新逻辑非常巧妙，特别是利用非递归线段树减少了递归调用的开销，适合竞赛环境。代码中对边界的处理（如`l^r^1`的判断）体现了对线段树结构的深刻理解，是学习线段树优化的好例子。

**题解二：作者Unordered_OIer**
* **点评**：此题解详细解释了线段树维护区间最大值的逻辑，代码结构工整（如`pushdown`函数明确下传标记）。离散化步骤清晰，变量名（如`lsh`表示离散化数组）易于理解。特别地，作者提到“因空间开小导致WA”的调试经历，提醒我们注意线段树的空间复杂度（通常需开4倍节点数），这对学习者有实际参考价值。

**题解三：作者BqtMtsZDnlpsT**
* **点评**：此题解提出用两个线段树分别维护左边界和右边界的最大值，解决了普通线段树可能遗漏的细节（如矩形交界处的高度变化）。这种“分情况处理”的思路非常巧妙，代码中`update`函数的条件判断（`l[i]+1`和`r[i]`的处理）体现了对问题本质的深刻理解，适合学习如何优化线段树的应用场景。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，提炼思考方向和策略：
</difficulty_intro>

1.  **关键点1：如何离散化坐标？**
    * **分析**：题目中矩形的左右边界范围可能很大（如`-1e9`到`1e9`），直接处理会导致内存和时间超限。优质题解通常将所有边界坐标存入数组，排序后去重（如`sort`和`unique`函数），将原坐标映射到离散化后的索引（如`lower_bound`查找）。这样既保留了坐标的相对顺序，又将范围压缩到`O(n)`级别。
    * 💡 **学习笔记**：离散化是处理大范围坐标问题的“降维神器”，核心是保留坐标的相对顺序。

2.  **关键点2：如何用线段树维护区间最大高度？**
    * **分析**：线段树的每个节点对应一个离散化后的区间，节点值存储该区间的最大高度。当处理左边界时（矩形开始覆盖），对线段树对应区间执行“取最大值”操作；处理右边界时（矩形结束覆盖），可能需要回退高度（但本题中矩形按高度排序，只需覆盖更高的矩形即可）。优质题解通常用`lazy tag`优化区间更新，避免重复计算。
    * 💡 **学习笔记**：线段树的`pushdown`和`pushup`是维护区间信息的关键，本题中`pushdown`用于下传最大高度标记，`pushup`用于合并子节点的最大值。

3.  **关键点3：如何记录轮廓线的顶点？**
    * **分析**：轮廓线的顶点出现在高度变化的位置。扫描线每处理完一个事件（左/右边界），需比较当前最大高度与前一高度。若不同，则记录两个顶点（前一高度到当前高度的竖直线）。优质题解通过遍历离散化后的坐标，检查相邻坐标的高度差来避免重复记录（如`if(tg[l]!=tg[l-1])`）。
    * 💡 **学习笔记**：顶点记录的核心是“高度变化”，需确保每个变化点只记录一次。

### ✨ 解题技巧总结
- **问题分解**：将大问题拆分为离散化、线段树维护、顶点记录三个子问题，逐个解决。
- **线段树优化**：非递归线段树减少递归调用开销，适合竞赛环境；双线段树处理边界细节，避免遗漏。
- **调试技巧**：遇到WA时，优先检查离散化是否正确（如是否包含所有边界）、线段树空间是否足够（如开4倍节点数）。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，先看一个综合优质题解的通用核心实现，帮助把握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合EnofTaiPeople和Unordered_OIer的思路，采用离散化+线段树维护区间最大值，代码简洁高效，适合学习。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    const int N = 3e5 + 5;

    int mp[N], mt, n, tg[N << 2]; // tg为线段树标记数组
    struct Rect { int h, l, r; } g[N];
    vector<pair<int, int>> ans;

    int main() {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        n = scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d%d", &g[i].h, &g[i].l, &g[i].r);
            mp[++mt] = g[i].l; mp[++mt] = g[i].r;
        }
        // 离散化处理
        sort(mp + 1, mp + mt + 1);
        mt = unique(mp + 1, mp + mt + 1) - mp;
        // 按高度排序矩形（高的后处理，覆盖低的）
        sort(g + 1, g + n + 1, [](const Rect& a, const Rect& b) { return a.h < b.h; });

        // 线段树初始化（非递归）
        int m = 1; while (m < mt) m <<= 1;
        for (int i = 1; i <= n; ++i) {
            int l = lower_bound(mp + 1, mp + mt, g[i].l) - mp + m - 1;
            int r = lower_bound(mp + 1, mp + mt, g[i].r) - mp + m;
            while (l ^ r ^ 1) {
                if ((l & 1) ^ 1) tg[l ^ 1] = max(tg[l ^ 1], g[i].h);
                if (r & 1) tg[r ^ 1] = max(tg[r ^ 1], g[i].h);
                l >>= 1; r >>= 1;
            }
        }
        // 下传标记，计算每个位置的最大高度
        for (int i = 1; i < m; ++i) {
            if (tg[i]) {
                tg[i << 1] = max(tg[i << 1], tg[i]);
                tg[i << 1 | 1] = max(tg[i << 1 | 1], tg[i]);
            }
        }
        // 记录高度变化的顶点
        int last_h = 0;
        for (int i = 1; i < mt; ++i) {
            int cur_h = tg[m + i];
            if (cur_h != last_h) {
                ans.emplace_back(mp[i], last_h);
                ans.emplace_back(mp[i], cur_h);
                last_h = cur_h;
            }
        }
        // 输出结果
        printf("%d\n", (int)ans.size());
        for (auto [x, y] : ans) printf("%d %d\n", x, y);
        return 0;
    }
    ```
* **代码解读概要**：代码首先读取输入并离散化左右边界；然后按高度排序矩形（高的后处理以覆盖低的）；使用非递归线段树维护每个离散化区间的最大高度；最后遍历离散化坐标，记录高度变化的顶点。核心逻辑是线段树的区间更新和标记下传。

---
<code_intro_selected>
接下来，剖析优质题解的核心代码片段，点出亮点和关键思路。
</code_intro_selected>

**题解一：作者EnofTaiPeople**
* **亮点**：非递归线段树实现，减少递归调用开销，适合处理大数据量。
* **核心代码片段**：
    ```cpp
    // 线段树区间更新部分
    int l = lower_bound(mp+1, mp+mt, g[i].l) - mp + m - 1;
    int r = lower_bound(mp+1, mp+mt, g[i].r) - mp + m;
    while (l ^ r ^ 1) {
        if ((l & 1) ^ 1) tg[l ^ 1] = g[i].h;
        if (r & 1) tg[r ^ 1] = g[i].h;
        l >>= 1; r >>= 1;
    }
    ```
* **代码解读**：这里将离散化后的左右边界转换为线段树的叶节点索引（`m`是线段树大小）。`while (l ^ r ^ 1)`循环处理左右边界的父节点，将当前矩形的高度`g[i].h`更新到对应的线段树节点。`(l & 1) ^ 1`判断左边界是否为左子节点，`r & 1`判断右边界是否为右子节点，确保只更新覆盖区间的节点。
* 💡 **学习笔记**：非递归线段树通过位运算直接操作节点索引，比递归实现更高效，适合竞赛中的时间限制。

**题解二：作者Unordered_OIer**
* **亮点**：递归线段树实现，代码结构清晰，`pushdown`函数明确下传标记。
* **核心代码片段**：
    ```cpp
    // 线段树更新函数
    void modify(ll x, ll l, ll r, ll h) {
        if (t[x].r < l || t[x].l > r) return;
        if (t[x].l >= l && t[x].r <= r) {
            t[x].mx = max(t[x].mx, h);
            pushdown(x); // 下传标记
            return;
        }
        modify(x << 1, l, r, h);
        modify(x << 1 | 1, l, r, h);
    }
    ```
* **代码解读**：递归线段树的`modify`函数先判断当前节点是否完全覆盖目标区间，若是则更新最大值并下传标记（`pushdown`）；否则递归处理左右子节点。`pushdown`函数将当前节点的最大值传递给子节点，确保子节点的最大值正确。
* 💡 **学习笔记**：递归线段树代码更易理解，适合初学者掌握线段树的核心逻辑。

**题解三：作者BqtMtsZDnlpsT**
* **亮点**：双线段树分别维护左边界和右边界的最大值，避免边界遗漏。
* **核心代码片段**：
    ```cpp
    // 两个线段树分别处理左/右边界
    t[0].update(l[i], r[i]-1, 1, L, 1, h[i]); // 左边界或中间
    t[1].update(l[i]+1, r[i], 1, L, 1, h[i]); // 右边界或中间
    ```
* **代码解读**：`t[0]`维护“左边界或中间”位置的最大高度（即矩形左边界到右边界-1的区间），`t[1]`维护“右边界或中间”位置的最大高度（即矩形左边界+1到右边界的区间）。通过两个线段树的差值，准确捕捉边界处的高度变化。
* 💡 **学习笔记**：当问题涉及边界细节时，分情况维护不同数据结构是有效的优化手段。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解扫描线和线段树如何协作生成轮廓线，我们设计一个8位像素风格的动画，让算法“动起来”！
</visualization_intro>

  * **动画演示主题**：`像素扫描线大冒险`

  * **核心演示内容**：扫描线从左到右移动，遇到矩形边界时，线段树节点动态更新最大高度，轮廓线顶点随高度变化生成。

  * **设计思路简述**：采用FC红白机风格的像素画面（8色调色板，如深蓝背景、亮绿矩形、金色扫描线），用动态像素块表示线段树节点的高度。关键操作（如线段树更新、高度变化）伴随“叮”的音效，增强操作记忆。每生成一个顶点，视为“小关卡”完成，播放像素星星动画，增加成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕左侧显示离散化后的坐标轴（像素点表示），右侧显示线段树结构（堆叠的像素块，每块高度代表当前区间的最大高度）。
          * 控制面板包含“单步”、“自动播放”按钮和速度滑块（1x-5x）。
          * 播放8位风格的轻快背景音乐（类似《超级马里奥》的经典旋律）。

    2.  **扫描线启动**：
          * 金色扫描线（1像素宽）从最左端（坐标最小值）开始，向右移动。
          * 每个矩形的左右边界用红色（左）和蓝色（右）像素点标出，鼠标悬停显示“左边界”或“右边界”。

    3.  **处理边界事件**：
          * 扫描线遇到左边界时，对应线段树节点（绿色像素块）向上扩展，高度变为当前矩形的高度，播放“叮”音效。
          * 遇到右边界时，对应线段树节点（红色像素块）收缩，高度回退（若当前高度被更高矩形覆盖则无变化），播放“咚”音效。
          * 线段树节点的高度实时更新，用数字显示具体值（如“h=3”）。

    4.  **记录顶点**：
          * 扫描线每处理完一个事件（左/右边界），比较当前最大高度与前一高度。若不同，生成两个顶点（前一高度到当前高度的竖直线），用白色闪烁像素点标出。
          * 顶点坐标显示在屏幕上方（如“(-3, 0) → (-3, 3)”），并添加到结果列表。

    5.  **目标达成**：
          * 扫描线到达最右端时，播放胜利音效（上扬的“啦”声），所有顶点以彩虹色闪烁，结果列表完整显示。
          * 支持“回放”功能，重新演示关键步骤。

  * **旁白提示**：
      * （扫描线移动时）“看！扫描线正在检查每个矩形的边界，线段树会记录当前最高的矩形高度～”
      * （处理左边界时）“遇到左边界！线段树的这个节点要长高啦～”
      * （生成顶点时）“高度变化了！这里就是轮廓线的一个顶点哦～”

<visualization_conclusion>
通过这样的像素动画，我们能清晰看到扫描线如何移动、线段树如何更新高度，以及顶点如何生成。这种“可视化学习”能让抽象的算法变得生动有趣！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
扫描线与线段树的组合是处理区间覆盖、轮廓线问题的通用方法，以下是相关拓展练习：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 扫描线+线段树可处理矩形覆盖面积统计（如P5490）、区间最值维护（如HH的项链）、轮廓线生成（如本题）等问题。核心是将二维问题降为一维，用扫描线处理事件，线段树维护一维区间信息。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P5490** - `【模板】扫描线`
          * 🗣️ **推荐理由**：扫描线算法的经典模板题，帮助掌握矩形面积并的计算，巩固离散化和线段树的应用。
    2.  **洛谷 P1856** - `[IOI1998] 多边形覆盖`
          * 🗣️ **推荐理由**：本题是矩形覆盖的变形，需处理多个矩形的交叠，适合练习扫描线的细节处理。
    3.  **洛谷 P1972** - `[SDOI2009] HH的项链`
          * 🗣️ **推荐理由**：虽然是区间查询问题，但线段树维护区间信息的思路与本题类似，适合拓展线段树的应用场景。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解提到了调试中的经验，这些对我们非常有帮助：
</insights_intro>

> **参考经验 (来自Unordered_OIer)**：“调试时发现空间开小导致WA，后来将线段树节点数从`4*N`扩大到`8*N`才通过。”
>
> **点评**：线段树的空间复杂度通常为`4*N`（N为离散化后的坐标数），但本题中矩形边界可能较多（如`2n`个），需适当扩大空间（如`8*N`）。这提醒我们，处理大数据量时要预留足够的空间，避免RE或WA。

-----

<conclusion>
本次关于“Parade”的C++解题分析就到这里。通过扫描线和线段树的组合，我们能高效解决轮廓线问题。希望这份指南能帮助大家理解算法核心，并在实践中灵活运用！下次挑战新题时，记得先想“如何用扫描线分解问题，用线段树维护关键信息”哦～💪
</conclusion>

---
处理用时：160.43秒