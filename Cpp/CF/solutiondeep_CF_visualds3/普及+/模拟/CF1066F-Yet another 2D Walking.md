# 题目信息

# Yet another 2D Walking

## 题目描述

Maksim walks on a Cartesian plane. Initially, he stands at the point $ (0, 0) $ and in one move he can go to any of four adjacent points (left, right, up, down). For example, if Maksim is currently at the point $ (0, 0) $ , he can go to any of the following points in one move:

- $ (1, 0) $ ;
- $ (0, 1) $ ;
- $ (-1, 0) $ ;
- $ (0, -1) $ .

There are also $ n $ distinct key points at this plane. The $ i $ -th point is $ p_i = (x_i, y_i) $ . It is guaranteed that $ 0 \le x_i $ and $ 0 \le y_i $ and there is no key point $ (0, 0) $ .

Let the first level points be such points that $ max(x_i, y_i) = 1 $ , the second level points be such points that $ max(x_i, y_i) = 2 $ and so on. Maksim wants to visit all the key points. But he shouldn't visit points of level $ i + 1 $ if he does not visit all the points of level $ i $ . He starts visiting the points from the minimum level of point from the given set.

The distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is $ |x_1 - x_2| + |y_1 - y_2| $ where $ |v| $ is the absolute value of $ v $ .

Maksim wants to visit all the key points in such a way that the total distance he walks will be minimum possible. Your task is to find this distance.

If you are Python programmer, consider using PyPy instead of Python when you submit your code.

## 说明/提示

The picture corresponding to the first example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1066F/896df4e9ea79d5fd52a150516ea0bd817a9ff17d.png)

There is one of the possible answers of length $ 15 $ .

The picture corresponding to the second example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1066F/df4d50be023876f6bcdf0e6166cef5c64a3a8a11.png)

There is one of the possible answers of length $ 9 $ .

## 样例 #1

### 输入

```
8
2 2
1 4
2 3
3 1
3 4
1 1
4 3
1 2
```

### 输出

```
15
```

## 样例 #2

### 输入

```
5
2 1
1 0
2 0
3 2
0 3
```

### 输出

```
9
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Yet another 2D Walking 深入学习指南 💡

<introduction>
今天我们来一起分析“Yet another 2D Walking”这道C++编程题。这道题的关键在于理解分层访问的规则，并通过动态规划找到最短路径。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：动态规划（DP）应用

🗣️ **初步分析**：
解决“Yet another 2D Walking”这道题，关键在于理解并运用动态规划（DP）。动态规划就像搭积木——先解决小问题（低层级的访问），再用小问题的解组合出大问题（高层级的访问）的最优解。在本题中，DP主要用于记录处理完每一层后停留在该层两个端点（左上/右下）的最小距离，从而通过层间转移推导出全局最优解。

- **题解思路**：所有题解均采用动态规划。核心思路是：将点按等级（max(x,y)）分层，每层确定两个端点（最左上端点和最右下端点），用`dp[i][0/1]`表示处理完第i层后停留在左/右端点的最小距离。通过比较上一层两个端点到当前层两个端点的转移路径，更新当前层的DP值。
- **核心难点**：如何准确定义每层的左右端点？如何设计状态转移方程？如何处理初始状态（从(0,0)出发）？
- **可视化设计**：计划采用8位像素风格动画，用不同颜色的像素块表示不同层级的点（如蓝色代表第1层，绿色代表第2层等）。动画中，每处理一层时，高亮左右端点的移动路径（红色箭头），并动态显示DP数组的更新过程（数值变化）。关键转移步骤伴随“叮”的音效，完成所有层级时播放胜利音效。

---

## 2. 精选优质题解参考

<eval_intro>
为了更好地理解解题过程，我从思路清晰度、代码规范性、算法有效性等方面筛选了以下优质题解：
</eval_intro>

**题解一：作者p_b_p_b**
* **点评**：此题解思路清晰，代码结构完整。作者首先将点按等级排序，然后逐层确定左右端点（通过自定义比较函数cmpx和cmpy），最后用DP转移计算最小距离。代码中虽然变量名较简洁（如`a[]`存储点，`p[z][0/1]`存储左右端点），但逻辑连贯。亮点在于通过`sort(a+1,a+n+1,cmp)`快速分层，并用`dp[z][x]`记录状态，空间复杂度为O(n)，适合处理大数量级数据（n≤2e5）。

**题解二：作者ncwzdlsd**
* **点评**：此题解对状态转移方程的描述非常明确，直接给出了`f(i,0)`和`f(i,1)`的转移公式，便于理解。代码中用`l[i]`和`r[i]`表示第i层的左右端点，变量命名直观。状态转移部分通过两次`min`操作完成，逻辑简洁。亮点在于将分层逻辑与DP转移分离，代码可读性强。

**题解三：作者littlewyy**
* **点评**：此题解不仅提供了代码，还详细解释了策略的合理性（如“同层路径必为端点间路径”的证明），适合学习者理解背后的算法原理。代码中通过`Lef[i]`和`Rig[i]`存储各层端点，并用`getDis`函数计算曼哈顿距离，模块化设计优秀。亮点在于对“端点选择”的数学证明，帮助学习者从“知其然”到“知其所以然”。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下几个核心难点。结合优质题解的共性，我为大家提炼了思考方向和策略：
</difficulty_intro>

1.  **关键点1**：如何准确定义每层的左右端点？
    * **分析**：同一层级的点分布在一个倒L形区域（如max(x,y)=k的点满足x=k或y=k）。左右端点需满足：左端点是该层中x最小（若x相同则y最大）的点（最左上），右端点是x最大（若x相同则y最小）的点（最右下）。优质题解通过自定义排序函数（如`cmpx`和`cmpy`）快速筛选端点。
    * 💡 **学习笔记**：端点的定义需保证同层内路径最短（端点间路径覆盖所有点）。

2.  **关键点2**：如何设计状态转移方程？
    * **分析**：状态`dp[i][0/1]`表示处理完第i层后停留在左/右端点的最小距离。转移时需考虑上一层的两个端点（左/右）到当前层两个端点的四种组合，取最小值。例如，`dp[i][0]`（当前层左端点）的最小值可能来自上一层左端点→当前层右端点，或上一层右端点→当前层右端点，再加上当前层内左右端点的距离（覆盖同层所有点）。
    * 💡 **学习笔记**：状态转移的核心是枚举所有可能的上一层状态，取最优解。

3.  **关键点3**：如何处理初始状态（从(0,0)出发）？
    * **分析**：初始时，Maksim在(0,0)，需走到第一层的左右端点之一。优质题解通常将初始状态设为`dp[0][0]=dp[0][1]=0`（虚拟第0层的两个端点为(0,0)），然后从第一层开始计算。
    * 💡 **学习笔记**：虚拟层的设计是处理初始状态的常用技巧。

### ✨ 解题技巧总结
- **问题分层**：将原问题按等级分层，转化为层间转移问题。
- **端点筛选**：通过自定义排序函数快速确定每层的左右端点，减少计算量。
- **状态压缩**：用二维DP数组（左/右端点）记录状态，避免复杂的多状态管理。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了多个优质题解的思路，采用动态规划，清晰展示分层、端点筛选和状态转移的核心逻辑。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long LL;
    const int MAXN = 2e5 + 5;

    struct Point {
        int x, y;
        int level() const { return max(x, y); }
    };

    Point points[MAXN];
    vector<Point> layers[MAXN]; // 每层的点
    LL dp[MAXN][2]; // dp[i][0]表示处理完第i层后在左端点，dp[i][1]在右端点

    // 比较函数：筛选左端点（x最小，x相同则y最大）
    bool cmp_left(const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y > b.y;
    }

    // 比较函数：筛选右端点（x最大，x相同则y最小）
    bool cmp_right(const Point& a, const Point& b) {
        if (a.x != b.x) return a.x > b.x;
        return a.y < b.y;
    }

    // 计算曼哈顿距离
    LL manhattan(const Point& a, const Point& b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }

    int main() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> points[i].x >> points[i].y;
        }

        // 按等级分层
        sort(points, points + n, [](const Point& a, const Point& b) {
            return a.level() < b.level();
        });
        int max_level = points[n - 1].level();
        for (int i = 0; i < n; ++i) {
            layers[points[i].level()].push_back(points[i]);
        }

        // 处理每层的左右端点
        vector<Point> left(MAXN), right(MAXN);
        for (int l = 1; l <= max_level; ++l) {
            if (layers[l].empty()) continue;
            sort(layers[l].begin(), layers[l].end(), cmp_left);
            left[l] = layers[l].front();
            sort(layers[l].begin(), layers[l].end(), cmp_right);
            right[l] = layers[l].front();
        }

        // 初始化DP：虚拟第0层的端点为(0,0)
        dp[0][0] = dp[0][1] = 0;
        Point start = {0, 0};

        // 动态规划计算
        for (int l = 1; l <= max_level; ++l) {
            if (layers[l].empty()) continue;
            LL cost = manhattan(left[l], right[l]); // 同层内路径长度
            dp[l][0] = min(
                dp[l-1][0] + manhattan(right[l-1], right[l]) + cost,
                dp[l-1][1] + manhattan(left[l-1], right[l]) + cost
            );
            dp[l][1] = min(
                dp[l-1][0] + manhattan(right[l-1], left[l]) + cost,
                dp[l-1][1] + manhattan(left[l-1], left[l]) + cost
            );
        }

        cout << min(dp[max_level][0], dp[max_level][1]) << endl;
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先将点按等级分层，然后为每层筛选左右端点。通过动态规划，从第0层（起点(0,0)）开始，逐层计算处理完每层后停留在左/右端点的最小距离。状态转移时，考虑上一层两个端点到当前层两个端点的四种组合，取最小值加上同层内路径长度。

---
<code_intro_selected>
接下来，我们剖析优质题解中的核心代码片段，理解其亮点和关键逻辑。
</code_intro_selected>

**题解一：作者p_b_p_b**
* **亮点**：通过`sort(a+1,a+n+1,cmp)`快速分层，用`p[z][0/1]`存储每层端点，代码简洁高效。
* **核心代码片段**：
    ```cpp
    sort(a+1,a+n+1,cmp);
    memset(dp,0x3f,sizeof(dp));
    dp[0][0]=dp[0][1]=0;
    for (i=j=z=1;i<=n;i=j+1,++z,++j) {
        while (id(a[j+1])==id(a[j])) ++j;
        p[z][0]=p[z][1]=a[i];
        for (k=i+1;k<=j;k++) {
            if (cmpx(a[k],p[z][0])) p[z][0]=a[k];
            if (cmpy(a[k],p[z][1])) p[z][1]=a[k];
        }
        for (x=0;x<2;x++)
            for (y=0;y<2;y++)
                dp[z][x]=min(dp[z][x],dp[z-1][y]+dis(p[z-1][y],p[z][!x])+dis(p[z][!x],p[z][x]));
    }
    ```
* **代码解读**：
    - `sort(a+1,a+n+1,cmp)`按等级排序，将同层点连续存储。
    - `p[z][0/1]`通过遍历同层点，用`cmpx`和`cmpy`筛选左右端点。
    - 状态转移部分，`dp[z][x]`通过上一层的两个状态（y=0/1）计算最小值，`dis(p[z-1][y],p[z][!x])`是层间转移距离，`dis(p[z][!x],p[z][x])`是同层内路径长度。
* 💡 **学习笔记**：分层后遍历同层点筛选端点，是处理此类问题的高效方法。

**题解二：作者ncwzdlsd**
* **亮点**：状态转移方程明确，直接给出`f(i,0)`和`f(i,1)`的计算方式。
* **核心代码片段**：
    ```cpp
    for(int i=1;i<=cnt;i++) {
        f[i][0] = min(f[i-1][0] + dis(l[i-1], r[i]), f[i-1][1] + dis(r[i-1], r[i])) + dis(l[i], r[i]);
        f[i][1] = min(f[i-1][0] + dis(l[i-1], l[i]), f[i-1][1] + dis(r[i-1], l[i])) + dis(l[i], r[i]);
    }
    ```
* **代码解读**：
    - `l[i]`和`r[i]`是第i层的左右端点。
    - `f[i][0]`表示处理完第i层后在左端点的最小距离，其值为上一层左/右端点到当前层右端点的距离取最小值，加上同层内左右端点的距离（`dis(l[i], r[i])`）。
    - `f[i][1]`同理，计算上一层到当前层左端点的最小距离。
* 💡 **学习笔记**：状态转移方程是DP的核心，需明确每一步的来源和计算方式。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解动态规划的状态转移和层间路径，我们设计一个“像素探险家”主题的8位像素动画，模拟Maksim的路径选择过程。
</visualization_intro>

  * **动画演示主题**：像素探险家的分层寻宝之旅
  * **核心演示内容**：展示Maksim从(0,0)出发，逐层访问关键点，每一层选择左或右端点作为路径起点/终点，动态计算最短路径。

  * **设计思路简述**：采用8位像素风格（FC红白机色调），用不同颜色的像素块表示不同层级（如第1层蓝色、第2层绿色）。每一层的左右端点用金色和银色像素块标记，路径用红色箭头动态绘制。通过音效（如“叮”提示层间转移，“胜利”音效提示完成所有层）增强操作记忆。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
        - 屏幕左侧显示像素网格（10x10），右侧显示控制面板（开始/暂停、单步、调速滑块）。
        - 初始点(0,0)用黄色像素块标记，背景音乐播放8位风格的轻快旋律。

    2.  **分层展示**：
        - 按等级从小到大显示各层点（如第1层蓝色块出现在max(x,y)=1的位置），层号用白色文字标注。

    3.  **端点筛选动画**：
        - 同层点中，左端点（最左上）用金色边框闪烁，右端点（最右下）用银色边框闪烁，伴随“滴”的音效。

    4.  **状态转移演示**：
        - 单步执行时，上一层的左/右端点（金色/银色块）到当前层的右/左端点（银色/金色块）的路径用红色虚线绘制，同时右侧显示DP数组的更新（如`dp[2][0] = min(10, 15) → 10`）。
        - 自动播放时，路径箭头动态延伸，DP数值实时更新，关键步骤（如最小值选择）用放大字体高亮。

    5.  **完成所有层**：
        - 最后一层处理完成时，所有路径用绿色实线覆盖，播放上扬的“胜利”音效，屏幕显示“最短路径长度：15”（如样例1）。

  * **旁白提示**：
      - “看，第1层的左端点是(1,1)，右端点是(1,2)！”
      - “现在计算从第1层的右端点到第2层的左端点的距离，加上第2层内的路径长度。”
      - “听到‘叮’声了吗？这表示我们完成了一次状态转移！”

<visualization_conclusion>
通过这样的动画，我们能直观看到每一层的端点选择如何影响总路径长度，动态规划的状态转移不再抽象，而是变成了可“看见”的像素路径！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
理解并掌握了本题的动态规划解法后，我们可以进一步思考分层处理和状态转移的通用思路。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 分层处理：适用于需按某种顺序（如等级、阶段）处理子问题的场景（如任务调度、资源分配）。
      - 端点筛选：在几何问题中，筛选极值点（如最左、最右）可简化路径计算（如旅行商问题的变种）。
      - 状态转移：记录关键状态（如位置、方向）的最优解，是解决多阶段决策问题的通用方法。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1006** - 传纸条  
        * 🗣️ **推荐理由**：经典动态规划问题，需处理二维路径的状态转移，与本题的分层思想有相似之处。
    2.  **洛谷 P1182** - 数列分段 Section II  
        * 🗣️ **推荐理由**：涉及分段处理和状态定义，可练习如何将大问题拆解为子问题。
    3.  **洛谷 P1853** - 投资的最大效益  
        * 🗣️ **推荐理由**：分层处理不同年份的投资，需设计状态转移方程，与本题的层间转移逻辑类似。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了解题过程中的思考，这些经验对我们很有启发：
</insights_intro>

> **参考经验 (来自作者littlewyy)**：“通过拆分，复杂问题简单化。画图可知，等级为i的点组成倒L字，同层最优路径必为端点间路径。”
>
> **点评**：作者的经验提醒我们，遇到复杂问题时，画图分析（如观察点的分布规律）是关键。通过几何直观，可以快速发现问题的本质（如端点间路径最优），从而简化状态设计。

-----

<conclusion>
本次关于“Yet another 2D Walking”的C++解题分析就到这里。希望这份学习指南能帮助大家理解动态规划的应用，掌握分层处理和状态转移的技巧。记住，多画图、多拆分，复杂问题也能迎刃而解！下次再见～💪
</conclusion>

---
处理用时：382.06秒