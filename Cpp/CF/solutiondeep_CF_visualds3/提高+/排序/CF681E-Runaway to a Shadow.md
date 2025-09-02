# 题目信息

# Runaway to a Shadow

## 题目描述

Dima is living in a dormitory, as well as some cockroaches.

At the moment $ 0 $ Dima saw a cockroach running on a table and decided to kill it. Dima needs exactly $ T $ seconds for aiming, and after that he will precisely strike the cockroach and finish it.

To survive the cockroach has to run into a shadow, cast by round plates standing on the table, in $ T $ seconds. Shadow casted by any of the plates has the shape of a circle. Shadow circles may intersect, nest or overlap arbitrarily.

The cockroach uses the following strategy: first he equiprobably picks a direction to run towards and then runs towards it with the constant speed $ v $ . If at some moment $ t<=T $ it reaches any shadow circle, it immediately stops in the shadow and thus will stay alive. Otherwise the cockroach is killed by the Dima's precise strike. Consider that the Dima's precise strike is instant.

Determine the probability of that the cockroach will stay alive.

## 说明/提示

The picture for the first sample is given below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF681E/3b35a58e93815d2d230d24cb7d27ab6d96995987.png)Red color stands for points which being chosen as the cockroach's running direction will cause him being killed, green color for those standing for survival directions. Please note that despite containing a circle centered in $ (-2,2) $ a part of zone is colored red because the cockroach is not able to reach it in one second.

## 样例 #1

### 输入

```
0 0 1 1
3
1 1 1
-1 -1 1
-2 2 1
```

### 输出

```
0.50000000000```

## 样例 #2

### 输入

```
0 0 1 0
1
1 0 1
```

### 输出

```
1.00000000000```

# AI分析结果

---
# 💡 Kay的C++算法解析：Runaway to a Shadow 深入学习指南 💡

<introduction>
  今天我们来一起分析“Runaway to a Shadow”这道C++编程题。这是一道**计算几何**方向的题目，核心是通过圆与圆的位置关系计算有效角度区间，最后求概率。本指南会帮你理清思路、掌握关键技巧，还会用像素动画直观展示算法流程哦！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：计算几何（圆与圆位置关系、角度区间合并）

🗣️ **初步分析**：
> 解决这道题，关键要理解两个核心问题：  
> 1. **蟑螂能跑到哪？** 蟑螂从原点出发，以速度`v`跑`T`秒，最远能到**以原点为圆心、半径`R = v*T`的圆**（记为“活动圆”）。  
> 2. **哪些方向能活？** 若蟑螂沿某个方向跑，能在到达活动圆边缘前（≤T秒）进入任意一个阴影圆（记为“目标圆”），这个方向就是“存活方向”。  

简单比喻：把蟑螂的活动范围看成一个**大披萨饼**，每个阴影圆对应披萨上的“安全扇形”——只要蟑螂选的方向落在任何一个安全扇形里，就能活。我们要算所有安全扇形的总角度，除以整个披萨的圆周（2π），就是存活概率！

### 核心算法流程
1. **计算活动圆半径**：`R = v * T`（蟑螂能跑的最远距离）。  
2. **逐个分析目标圆**：对每个阴影圆，判断它和活动圆是否有交集（即蟑螂能否跑到阴影里）。  
   - 若**目标圆圆心到原点的距离≤目标圆半径**（原点在阴影里）：直接输出概率1.0（必活）。  
   - 若**目标圆与活动圆无交集**（距离太远）：跳过这个圆。  
   - 若有交集：计算这个目标圆对应的**存活角度区间**（从原点看，目标圆覆盖的方向范围）。  
3. **合并角度区间**：把所有存活区间合并（处理跨0度的情况，比如350°到10°的区间），计算总角度。  
4. **求概率**：总角度 ÷ 2π。

### 可视化设计思路
我们会用**8位像素风**（类似FC游戏）展示算法：  
- 屏幕中央是“蟑螂原点”（黄色像素块），周围画**活动圆**（浅蓝色像素环）。  
- 每个目标圆用**不同颜色的像素块**表示（比如红色、绿色）。  
- 计算存活区间时，用**绿色扇形**标记有效方向；合并区间时，重叠部分变成**深绿色**。  
- 交互设计：“单步”（处理一个目标圆）、“自动播放”（每秒处理一个）、“重置”；关键操作（如计算区间、合并）配**像素音效**（“叮”“嗒”），完成时播“胜利音效”！


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法有效性等方面筛选了2份优质题解，帮你快速理解核心逻辑：
</eval_intro>

**题解一：来源：xzggzh1**
* **点评**：这份题解的思路非常**直白高效**！作者用“事件点”（每个区间的“开始”和“结束”标记）来合并角度区间，逻辑严谨。代码风格规范（比如`dist2`函数计算平方距离，避免浮点数误差），处理跨0度区间的方式很巧妙（拆分成两个区间）。特别是**精度控制**（用`eps=1e-9`比较浮点数），是计算几何题的关键技巧，值得学习！

**题解二：来源：skyskyCCC**
* **点评**：此题解的**区间合并逻辑更直观**——直接存储每个存活区间的“起点-终点”，排序后扫描合并。作者在分析中明确提到“余弦定理的坑点”（处理跨0度的情况），帮我们提前避坑。代码中的`atan2(dy, dx)`计算角度的方式很标准，适合初学者模仿！


## 3. 核心难点辨析与解题策略

<difficulty_intro>
计算几何题的难点在于**细节处理**（比如浮点数精度、区间边界）。结合题解，我提炼了3个核心关键点：
</difficulty_intro>

1.  **关键点1：判断圆与圆的位置关系**  
    * **问题**：如何快速判断目标圆和活动圆是否有交集？  
    * **分析**：设目标圆圆心到原点的距离为`d`，目标圆半径为`r`，活动圆半径为`R`：  
      - 若`d ≤ r`：原点在目标圆内（必活，直接输出1.0）。  
      - 若`d > R + r`：两圆无交集（蟑螂跑不到）。  
      - 否则：两圆有交集（需要计算存活区间）。  
    * 💡 **学习笔记**：用**平方距离**（`dist2`）代替开根号，能减少浮点数误差！

2.  **关键点2：计算存活角度区间**  
    * **问题**：如何求从原点看目标圆的角度范围？  
    * **分析**：  
      1. 用`atan2(dy, dx)`计算目标圆圆心相对于原点的角度`angM`（`dy=y-y0`，`dx=x-x0`，结果范围是[-π, π]，转成[0, 2π]更方便）。  
      2. 用**正弦定理**或**余弦定理**求角度范围`ang`：  
         - 若`R ≥ sqrt(d² - r²)`（蟑螂能跑到目标圆的切线内）：`ang = asin(r/d)`（目标圆对原点的张角）。  
         - 否则：`ang = acos((d² + R² - r²)/(2*d*R))`（两圆交点对应的圆心角）。  
      3. 存活区间是`[angM - ang, angM + ang]`。  
    * 💡 **学习笔记**：`atan2(y, x)`比`atan(y/x)`更安全（能处理x=0的情况）！

3.  **关键点3：合并角度区间（处理跨0度）**  
    * **问题**：如果区间是`[350°, 10°]`（跨0度），怎么合并？  
    * **分析**：把区间拆成`[350°, 360°]`和`[0°, 10°]`，再和其他区间合并。题解一用“事件点”（比如`(350°, +1)`表示开始，`(360°, -1)`表示结束，`(0°, +1)`，`(10°, -1)`）存储，排序后扫描线合并，逻辑清晰！  
    * 💡 **学习笔记**：跨0度的区间要“拆分成两段”，否则合并会出错！

### ✨ 解题技巧总结
- **技巧1：用平方距离减少误差**：计算距离时先算平方（`dist2`），避免开根号带来的精度损失。  
- **技巧2：角度统一到[0, 2π]**：`atan2`的结果如果是负数，加2π转成正数，方便区间处理。  
- **技巧3：事件点合并区间**：把每个区间的“开始”和“结束”标记为事件点（比如`(start, +1)`、`(end, -1)`），排序后扫描，统计当前“激活”的区间数量，累加有效长度。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个**综合版核心代码**，整合了题解的优点，逻辑清晰：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了两份题解的思路，优化了精度处理和区间合并逻辑，适合初学者理解。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <cmath>
    using namespace std;

    const double eps = 1e-9;
    const double PI = acos(-1.0);
    typedef pair<double, double> PDD; // (角度, 事件类型：+1开始/-1结束)

    inline double dist2(double x1, double y1, double x2, double y2) {
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    }

    int main() {
        int x0, y0, v, T, n;
        cin >> x0 >> y0 >> v >> T >> n;
        double R = (double)v * T; // 活动圆半径
        vector<PDD> events;

        for (int i = 0; i < n; ++i) {
            int x, y, r;
            cin >> x >> y >> r;
            double dx = x - x0, dy = y - y0;
            double d_sq = dist2(x, y, x0, y0);
            double d = sqrt(d_sq);

            // 情况1：原点在目标圆内（必活）
            if (d_sq <= (double)r * r + eps) {
                cout << "1.0000000000" << endl;
                return 0;
            }
            // 情况2：两圆无交集（跳过）
            if (R + r < d - eps) continue;

            // 计算角度区间
            double angM = atan2(dy, dx); // 目标圆圆心的角度（[-π, π]）
            if (angM < 0) angM += 2 * PI; // 转成[0, 2π]
            double ang;
            if (R + eps >= sqrt(d_sq - (double)r * r)) {
                ang = asin(r / d); // 张角
            } else {
                ang = acos((d_sq + R * R - (double)r * r) / (2 * d * R)); // 余弦定理
            }
            double L = angM - ang, R_ang = angM + ang;

            // 处理跨0度的情况（拆分成两个事件）
            if (L < 0) {
                events.emplace_back(L + 2 * PI, 1); // [L+2π, 2π]开始
                events.emplace_back(2 * PI, -1);    // [L+2π, 2π]结束
                events.emplace_back(0, 1);          // [0, R_ang]开始
                events.emplace_back(R_ang, -1);     // [0, R_ang]结束
            } else if (R_ang > 2 * PI) {
                events.emplace_back(L, 1);          // [L, 2π]开始
                events.emplace_back(2 * PI, -1);    // [L, 2π]结束
                events.emplace_back(0, 1);          // [0, R_ang-2π]开始
                events.emplace_back(R_ang - 2 * PI, -1); // 结束
            } else {
                events.emplace_back(L, 1);          // 正常区间开始
                events.emplace_back(R_ang, -1);     // 正常区间结束
            }
        }

        // 合并事件点：排序后扫描
        sort(events.begin(), events.end());
        double total = 0, last = 0;
        int active = 0;
        for (auto &e : events) {
            double angle = e.first;
            int type = e.second;
            if (active > 0) {
                total += angle - last; // 累加有效区间长度
            }
            active += type;
            last = angle;
        }

        printf("%.10lf\n", total / (2 * PI));
        return 0;
    }
    ```
* **代码解读概要**：  
  1. **输入处理**：读取蟑螂的初始位置、速度、时间，以及目标圆的数量。  
  2. **活动圆半径**：计算`R = v*T`（蟑螂能跑的最远距离）。  
  3. **逐个处理目标圆**：  
     - 计算目标圆与原点的距离`d`，判断是否在目标圆内（直接输出1.0）或无交集（跳过）。  
     - 计算目标圆的角度`angM`和张角`ang`，得到存活区间`[L, R_ang]`。  
     - 处理跨0度的情况（拆分成两个事件点）。  
  4. **合并区间**：排序事件点，扫描统计有效区间的总长度。  
  5. **输出概率**：总长度 ÷ 2π。


<code_intro_selected>
接下来剖析两份题解的**核心片段**，看它们的亮点：
</code_intro_selected>

**题解一：来源：xzggzh1**
* **亮点**：用“事件点”处理区间合并，逻辑严谨，适合复杂区间。
* **核心代码片段**：
    ```cpp
    // 处理跨0度的情况
    if (angL < 0) {
        a.push_back(make_pair(angL+2*PI,1)); // [angL+2π, 2π]开始
        a.push_back(make_pair(2*PI,-1));    // 结束
        a.push_back(make_pair(0,1));        // [0, angR]开始
        a.push_back(make_pair(angR,-1));     // 结束
    } else if (angR > 2*PI) {
        // 类似处理...
    }
    // 合并事件点
    sort(a.begin(),a.end());
    for (last = ans = x = 0, it = a.begin(); it != a.end(); it ++ ) {
        if (x > 0) ans += it->first-last;
        x += it->second;
        last = it->first;
    }
    ```
* **代码解读**：  
  - 每个事件点是`(角度, 类型)`：`+1`表示区间开始，`-1`表示结束。  
  - 排序后扫描，`x`记录当前激活的区间数量（`x>0`表示在有效区间内），累加有效长度`ans`。  
* 💡 **学习笔记**：事件点是合并区间的“万能工具”，不管区间多复杂都能处理！

**题解二：来源：skyskyCCC**
* **亮点**：直接存储区间对，合并逻辑更直观，适合初学者。
* **核心代码片段**：
    ```cpp
    // 存储区间对（start, end）
    if(tot+eg>2.0*pi){
        ve[sum++]=mp(0,tot+eg-2.0*pi); // 拆成[0, tot+eg-2π]
        ve[sum++]=mp(tot-eg,2.0*pi);   // [tot-eg, 2π]
    } else if(tot-eg<0.0){
        ve[sum++]=mp(tot-eg+2.0*pi,2.0*pi); // [tot-eg+2π, 2π]
        ve[sum++]=mp(0,tot+eg);             // [0, tot+eg]
    } else ve[sum++]=mp(tot-eg,tot+eg); // 正常区间
    // 合并区间
    sort(ve,ve+sum);
    for(int i=0;i<sum;i++){
        if(i==0||ve[i].first>leftt){
            ans+=ve[i].second-ve[i].first;
            leftt=ve[i].second;
        } else if(ve[i].second>leftt){
            ans+=ve[i].second-leftt;
            leftt=ve[i].second;
        }
    }
    ```
* **代码解读**：  
  - 直接存储每个区间的`(start, end)`，排序后扫描：  
    - 如果当前区间的`start`大于上一个区间的`end`（无重叠），直接累加长度。  
    - 否则（有重叠），累加`当前end - 上一个end`的长度。  
* 💡 **学习笔记**：直接存储区间对的方式更直观，但要注意排序和边界处理！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你更直观“看”到算法流程，我设计了一个**8位像素风动画**，结合“披萨切分”的游戏元素，边玩边学！
</visualization_intro>

### 动画演示主题：《蟑螂的安全披萨》
我们把蟑螂的活动范围做成一个**像素披萨**（直径约200像素），每个目标圆对应一块“安全馅料”，合并后的安全扇形就是“能吃的部分”，最后算“能吃的面积占比”（概率）。

### 核心设计细节
#### 1. 场景与UI初始化（FC风格）
- **背景**：浅灰色像素块（模拟桌子），中央是**蟑螂原点**（黄色1x1像素块）。  
- **活动圆**：浅蓝色像素环（半径`R`，用`drawCircle`函数画）。  
- **控制面板**：屏幕下方有4个按钮（像素风格）：  
  - 🔹 单步（处理一个目标圆）、🔹 自动（每秒处理一个）、🔹 重置、🔹 调速滑块（1x-5x速度）。  
- **背景音乐**：循环播放8位风格的“披萨店BGM”（轻快的电子音）。

#### 2. 算法动态演示（关键帧）
- **步骤1：目标圆出现**：每处理一个目标圆，屏幕上弹出一个**彩色像素块**（比如红色），标注圆心坐标和半径（用8位字体显示）。  
- **步骤2：计算存活区间**：  
  - 用**绿色像素**画扇形（从`angM-ang`到`angM+ang`），扇形边缘闪烁3次（提示“这是安全方向”）。  
  - 播放“叮”的音效（像素风格，频率440Hz）。  
- **步骤3：合并区间**：  
  - 如果新扇形和已有扇形重叠，重叠部分变成**深绿色**（提示“已合并”）。  
  - 播放“嗒”的音效（频率330Hz）。  
- **步骤4：完成计算**：  
  - 所有目标圆处理完后，屏幕显示**总安全角度**和**概率**（用大字体显示）。  
  - 播放“胜利音效”（上扬的8位音调，比如“叮—叮”）。

#### 3. 交互与游戏化元素
- **单步模式**：点击“单步”按钮，手动处理每个目标圆，适合仔细观察每个步骤。  
- **自动模式**：点击“自动”，算法自动运行，像“披萨师傅切馅料”一样，逐步完成计算。  
- **调速滑块**：拖动滑块调整自动播放速度（1x最慢，5x最快）。  
- **积分奖励**：每处理一个目标圆得10分，合并一个区间得20分，总分显示在屏幕右上角（鼓励“多练多得”）。

### 为什么这样设计？
- **像素风格**：唤起童年游戏记忆，降低学习压力。  
- **游戏化元素**：积分、音效、动画让算法“活”起来，不再是枯燥的公式。  
- **可视化重点**：用颜色区分“安全/非安全”方向，用闪烁提示关键操作，帮你快速抓住核心逻辑！


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
计算几何的核心是**坐标与图形的数学转换**，本题的思路能迁移到很多场景，比如：
</similar_problems_intro>

### 通用思路迁移
- **场景1**：无人机避障（计算无人机能飞的安全区域）。  
- **场景2**：雷达探测范围（合并多个雷达的探测区间）。  
- **场景3**：灯光覆盖范围（计算灯光能照亮的角度）。

### 洛谷练习推荐（计算几何入门）
1. **洛谷 P1257** - 平面上的最接近点对  
   🗣️ **推荐理由**：练习“距离计算”和“分治算法”，巩固浮点数精度处理技巧。  
2. **洛谷 P1355** - 神秘大三角  
   🗣️ **推荐理由**：练习“三角形面积计算”和“点与三角形的位置关系”，培养几何思维。  
3. **洛谷 P2319** - 回旋镖的飞行  
   🗣️ **推荐理由**：练习“线段与圆的交点”，拓展圆相关的计算几何知识。  


## 7. 学习心得与经验分享 (若有)

<insights_intro>
两份题解都提到了**精度处理**和**跨0度区间的处理**，这些是计算几何题的“必踩坑点”，我帮你总结了2条关键经验：
</insights_intro>

> **经验1**：用`eps`比较浮点数（来自题解一）  
> 作者用`eps=1e-9`来比较浮点数（比如`d_sq <= r*r + eps`），避免因浮点数精度误差导致的错误（比如`0.999999999`被误判为`1.0`）。  
> **点评**：这是计算几何题的“保命技巧”！所有浮点数比较都要加`eps`，否则会出现“明明正确却WA”的情况。

> **经验2**：跨0度区间要拆分（来自题解二）  
> 作者提到“弧度范围是[0, 2π]，所以要处理`a-b<0`和`a+b>2π`的情况”，并给出了拆分方法。  
> **点评**：跨0度的区间是“隐形陷阱”，如果不拆分，合并时会漏掉这部分区间，导致结果偏小！


<conclusion>
本次关于“Runaway to a Shadow”的分析就到这里啦！计算几何题看似复杂，其实只要**拆解问题（圆位置→角度区间→合并）**、**注意细节（精度、边界）**，就能轻松解决。  
记住：编程的乐趣在于“把数学变成可见的动画”——下次遇到计算几何题，不妨试试用像素动画可视化思路，你会发现“难题目”也能变“小游戏”！💪
</conclusion>
---

---
处理用时：120.12秒