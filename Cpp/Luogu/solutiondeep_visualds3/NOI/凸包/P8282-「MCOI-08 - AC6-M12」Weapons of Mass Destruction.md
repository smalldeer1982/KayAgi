# 题目信息

# 「MCOI-08 / AC6-M12」Weapons of Mass Destruction

## 题目背景

Garuda Team, I've got some good news. 

The chemical agent used as a catalyst for their WMD is being transported to our shores from the Estovakian mainland. 

This catalyst has already been carried into the outskirts of Gracemeria. 

As a measure of caution against any attempts to destroy it, it has been concealed at Fort Norton in Gracemeria's north. 

If we start advancing again, the enemy will most likely bring the catalyst into Gracemeria at a faster pace. 

If in fact weapons of mass destruction are used on the population of Gracemeria, the resulting devastation can't be expressed in enough words. 

It will lead to unspeakable tragedies. 

We've used this intelligence to come up with a solid proposal on how to prevent this scorched earth policy from being executed in our capital.

Just a minute ago, we received a letter of approval for our prevention plan from the Joint Chiefs of Staff. 

The proposal we put on the table for our scorched earth prevention policy is really quite simple. 

While the enemy transport unit is stationed at Fort Norton, **we'll ambush them.** 

We like to call it our tactic for pre-emptive victory. 

The enemy has loaded this catalyst into their transport vehicles and is able to send them into Gracemeria at any time. 

This plan will be carried out by a handful of our top pilots under absolute secrecy. 

**Fly through Fort Norton's canyon at an extremely low altitude to avoid radar detection, and take out those transport vehicles.** 

We've determined that a high-risk mission of this magnitude could not be executed by anyone other than Garuda Team. 

We're counting on a flawless execution here.

$$_{{\frac{\large\text{ACE COMBAT }\Large6}{\tiny{\text{F i r e s\quad O f\quad L i b e r a t i o n}}}}}\\ \text{Mission 12} \\\Large\text{Weapons of Mass Destruction}\\\tiny -\textit{ Boiling Point }-$$

![](https://cdn.luogu.com.cn/upload/image_hosting/3e1iqxjw.png)

## 题目描述

为了摧毁敌方装载有 WMD 催化剂的车队，你需要在超低空穿过 Fort Norton 的峡谷以接近他们。

Fort Norton 抽象为**平面上两个关于 $y$（$y\in[0,10^7]$）的线性分段函数** $A(y):y\mapsto x$ 以及 $B(y):y\mapsto x$，其中对于任意实数 $y\in [0,10^7]$，**满足 $A(y) \le B(y)$**。

你和你的 F-15E 抽象为一质点，**初始位置是 $(X_1,0)$**，保证 $A(0)\leq X_1\leq B(0)$；**同时具有初速度 $(v_0,\theta_0)$，表示初速的大小和方向**。

为了避免敌方发现，你不能大功率开动发动机。你的动力刚好足够在保持平飞的时候保持匀速。

当然你可以转向。由于你是 Ace Combat 的主角，你的转向全部用 PSM 完成。具体来说，你的飞行轨迹应为一条由若干线段组成的折线。但是在转向中会受到阻力。**如果方向改变后的角与改变前的角的差的绝对值为 $\alpha$，则速度大小会减小 $\alpha$**。如果你不改变方向，那么你会一直做匀速直线运动。

由于 Ghost Eye 很着急完成任务，所以**你的 $y$ 坐标必须随时间递增**。

同时，你需要保证在任意时刻，你所在的位置 $(x,y)$ 满足 $A(y)\le x\le B(y)$。

PSM 转向的过载很大，因此你需要保证**转向次数不超过 $\bf 3\times 10^6$**。~~否则你就会像 Prez 一样 g-LOC 并一头栽在仪表盘上。~~

求任何一个转向方案，使得你运动到 $(X_2,10^7)$ 上（**即，速度不能在运动过程中变为 $\bf0$ 或负数**），同时转向次数不超过 $3\times 10^6$。类似的，保证 $A(10^7)\leq X_2\leq B(10^7)$。

## 说明/提示

样例解释（缩小 $10^6$ 倍）：

![](https://cdn.luogu.com.cn/upload/image_hosting/5g98x901.png)

**注意质点在运动过程中可以碰到边界，也可以沿着边界运动一段。**

---

对于 $100\%$ 的数据，保证 $2\leq n,m\leq 10^6$，$0\leq x,y,p,q\leq 10^7$，$x_1\leq X_1\leq p_1$，$x_n\leq X_2\leq p_m$，$0\leq \theta_0<\pi$，$0\leq v_0\leq 10^9$。

对于 $100\%$ 的数据，实数精度不超过 $12$ 位。

对于 $100\%$ 的数据，**保 证 有 解**。


- Subtask 1（3 pts）：$n,m\leq 6$；$v_0\ge 50$。
- Subtask 2（8 pts）：$n,m\leq 6$。
- Subtask 3（17 pts）：$n,m\leq 200$。
- Subtask 4（13 pts）：$n,m\leq 1500$。
- Subtask 5（17 pts）：$n,m\leq 5000$。
- Subtask 6（19 pts）：$n,m\leq 10^5$。
- Subtask 7（23 pts）：无特殊限制。

**请注意浮点数输出效率。**

---

idea：Sol1，solution：Sol1 & w33z8kqrqk8zzzx33，code：Sol1，data：w33z8kqrqk8zzzx33

## 样例 #1

### 输入

```
5 4 4000000 9000000 13 0
3000000 0
1000000 1000000
2000000 4000000
6000000 8000000
7000000 10000000
5000000 0
4000000 2000000
6000000 6000000
10000000 10000000```

### 输出

```
1
4
4000000.0000000000 0.0000000000
3000000.0000000000 2000000.0000000000
4000000.0000000000 6000000.0000000000
9000000.0000000000 10000000.0000000000```

# AI分析结果

# 💡 Kay的C++算法解析：「MCOI-08 / AC6-M12」Weapons of Mass Destruction 深入学习指南 💡

今天我们来一起分析这道结合了**计算几何视线追踪**与**单调栈数据结构**的编程题。本指南将帮助大家梳理题目核心，理解“找尖点”的算法逻辑，并掌握用单调栈高效维护凸包的技巧。


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用`（侧重**单调栈维护凸包**与**视线追踪**）

🗣️ **初步分析**：  
解决这道题，关键像“在峡谷里找最远能看到的路”——你驾驶战机在峡谷（由左右边界的分段函数围成）中飞行，必须保证每一步都沿着“能看到的最远路径”走（这样转向角度最小）。这个“最远能看到的点”就是题解里说的**尖点**：从当前点出发，能同时“碰到”左右边界的最远点（或者说，左右边界在视线中“交汇”的点）。  

### 核心算法逻辑  
1. **尖点定义**：从当前点O出发，能看到的最远点P，满足线段OP完全在峡谷内，且P是左右边界的“交汇点”（即再往前飞就会撞到边界）。  
2. **算法流程**：从起点开始，不断找当前点的尖点，跳到尖点后重复此过程，直到到达终点——这样的路径转向最少（因为每一步都走“最远直路”）。  
3. **难点与解决**：如何高效找尖点？题解用**单调栈维护两侧凸包**：把左右边界的点分别存入两个单调栈，栈里的点保持“凸性”（即每个点都是当前视角下最“靠边”的点）。当栈底的点满足“视线交汇”时，就是尖点。  

### 可视化设计思路  
我们会用**8位像素风**模拟峡谷飞行：  
- 峡谷边界用不同颜色的像素块表示（左边界蓝色，右边界红色），战机是黄色小飞机；  
- 找尖点时，从战机位置发射“激光”（白色线段），碰到边界时高亮交点；  
- 跳到尖点时，飞机有“滑跃”动画，伴随“叮”的音效；  
- 路径完成时，整个路径闪烁，播放胜利音效（8位版“通关音乐”）。  


## 2. 精选优质题解参考

为了帮大家理解，我筛选了2份思路清晰、代码有效的优质题解：

### 题解一：镜音リン（核心思路讲解）  
* **点评**：这份题解把“尖点”的概念讲得很透——用“激光扫描”的比喻解释尖点的形成，再用“单调栈维护凸包”的方法解决高效查找问题。虽然没有给出完整代码，但逻辑推导（反证法证明“最优路径必过尖点”）非常严谨，能帮大家理解问题本质。特别是“单调栈维护凸包”的思路，直接点出了线性复杂度的关键，对想深入的同学很有启发。

### 题解二：Sol1（代码实现参考）  
* **点评**：这份题解的代码是“能跑的”！作者用双端队列模拟单调栈，分别处理左右边界的点：左边界的点用栈底维护最靠右的视线，右边界用栈顶维护最靠左的视线。代码中的`Link`函数计算向量，`cosAng`比较角度（利用余弦递减性简化判断），逻辑非常清晰。虽然变量命名有点“硬核”（比如`qhd`/`qtl`表示队列头尾），但整体结构规范，能直接参考实现。


## 3. 核心难点辨析与解题策略

### 关键点1：如何理解“尖点”？  
**分析**：尖点是“当前点能看到的最远合法点”——想象你站在O点，左右都是墙，你能看到的最远点就是左右墙在你视线中“刚好碰到一起”的点。如果不过这个点，路径肯定要绕弯（转向更多）。  
**解决策略**：用“向量角度比较”判断视线是否被遮挡——如果新点的视线角度比栈里的点更“偏”，说明栈里的点被遮挡了，可以弹出。

### 关键点2：如何维护两侧的凸包？  
**分析**：左右边界的点是分段的，直接遍历会重复计算。单调栈能维护“凸性”：左边界的栈里，每个点都是当前视角下最靠右的；右边界的栈里，每个点都是当前视角下最靠左的。这样栈底/栈顶的点就是当前的尖点。  
**解决策略**：左边界用“左单调栈”（栈底是最靠右的点），右边界用“右单调栈”（栈顶是最靠左的点），每次处理新点时弹出不满足凸性的点。

### 关键点3：如何保证线性时间复杂度？  
**分析**：如果每次找尖点都遍历所有点，复杂度会是O(n²)，无法通过大数据。  
**解决策略**：单调栈的“弹栈”操作保证每个点只被处理一次——弹出的点不会再被访问，因此总复杂度是O(n)。

### ✨ 解题技巧总结  
- **问题转化**：把“找任意路径”转化为“找转向最少的路径”，简化问题。  
- **数据结构选择**：单调栈是处理“凸包维护”“视线追踪”问题的神器，能把非线性问题线性化。  
- **角度比较技巧**：用余弦值比较角度（避免计算反正切），减少精度误差。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考  
* **说明**：本代码综合了Sol1的思路，调整了变量命名，更易读。  
* **完整核心代码**：  
```cpp
#include <iostream>
#include <vector>
#include <deque>
#include <iomanip>
using namespace std;

const int MAXN = 2e6 + 10; // 左右边界点总数不超过2e6
const double Y_END = 1e7;

struct Point {
    double x, y;
    int type; // 0:左边界，1:右边界
    Point() : x(0), y(0), type(0) {}
    Point(double x, double y) : x(x), y(y), type(0) {}
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
};

Point p[MAXN];
int fa[MAXN]; // 每个点的前驱（尖点）
deque<int> q; // 双端队列维护单调栈

// 计算向量的"角度余弦值"（用于比较方向）
double cosAng(const Point& v) {
    // 这里简化：向量与y轴正方向的夹角余弦（因为y必须递增）
    return v.y / sqrt(v.x*v.x + v.y*v.y);
}

// 计算两点间的向量（保证y递增）
Point link(int u, int v) {
    if (p[u].y < p[v].y) swap(u, v);
    return p[u] - p[v];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    double X1, X2, v0, a0;
    cin >> n >> m >> X1 >> X2 >> v0 >> a0;

    // 初始化起点（0号点）和终点（n+m+1号点）
    p[0] = Point(X1, 0);
    p[n+m+1] = Point(X2, Y_END);

    // 读左边界点（1~n号，type=0）
    for (int i = 1; i <= n; i++) {
        double tx, ty;
        cin >> tx >> ty;
        p[i] = Point(tx, ty);
    }

    // 读右边界点（n+1~n+m号，type=1）
    for (int i = 1; i <= m; i++) {
        double tx, ty;
        cin >> tx >> ty;
        p[n+i] = Point(tx, ty);
        p[n+i].type = 1;
    }

    // 处理所有点，维护单调栈
    q.push_back(0); // 起点入队
    for (int i = 1; i <= n+m+1; i++) {
        if (p[i].type == 0) { // 左边界点：维护栈底（最靠右的视线）
            while (q.size() >= 2) {
                int u = q[0], v = q[1];
                double cos1 = cosAng(link(i, u));
                double cos2 = cosAng(link(u, v));
                if (cos1 > cos2) { // 新点的视线更靠右，弹出栈底
                    q.pop_front();
                } else break;
            }
            fa[i] = q.front();
            q.push_front(i); // 左边界点放栈底
        } else { // 右边界点：维护栈顶（最靠左的视线）
            while (q.size() >= 2) {
                int u = q[q.size()-1], v = q[q.size()-2];
                double cos1 = cosAng(link(i, u));
                double cos2 = cosAng(link(u, v));
                if (cos1 < cos2) { // 新点的视线更靠左，弹出栈顶
                    q.pop_back();
                } else break;
            }
            fa[i] = q.back();
            q.push_back(i); // 右边界点放栈顶
        }
    }

    // 回溯路径（从终点到起点）
    vector<Point> path;
    int u = n+m+1;
    while (u != 0) {
        path.push_back(p[u]);
        u = fa[u];
    }
    path.push_back(p[0]); // 加起点

    // 输出结果（反向，因为路径是从终点到起点）
    cout << fixed << setprecision(10);
    cout << "1\n" << path.size() << "\n";
    for (auto it = path.rbegin(); it != path.rend(); it++) {
        cout << it->x << " " << it->y << "\n";
    }

    return 0;
}
```
* **代码解读概要**：  
  1. **输入处理**：读取左右边界点，初始化起点（0号）和终点（n+m+1号）。  
  2. **单调栈维护**：用双端队列处理左右边界点，左边界点放栈底（维护最靠右的视线），右边界点放栈顶（维护最靠左的视线）。  
  3. **路径回溯**：从终点出发，通过`fa`数组找前驱，直到回到起点，输出路径。


### 针对各优质题解的片段赏析

#### 题解二：Sol1（核心代码片段）  
* **亮点**：用双端队列模拟单调栈，处理左右边界的逻辑分开，代码简洁。  
* **核心代码片段**：  
```cpp
for (int i = 1;i <= n + m + 1;i++) {
    if (!p[i].type) { // 左边界
        while (qhd < qtl - 1 && Link(i, que[qhd]).cosAng() > Link(que[qhd], que[qhd + 1]).cosAng()) qhd++;
        fa[i] = que[qhd];
        que[--qhd] = i;
    } else { // 右边界
        while (qhd < qtl - 1 && Link(i, que[qtl - 1]).cosAng() < Link(que[qtl - 1], que[qtl - 2]).cosAng()) qtl--;
        fa[i] = que[qtl - 1];
        que[qtl++] = i;
    }
}
```
* **代码解读**：  
  - `Link(i, que[qhd])`计算新点i到栈底点的向量，`cosAng()`比较角度——左边界点如果新向量的余弦更大（更靠右），说明栈底点被遮挡，弹出。  
  - `fa[i]`记录i的前驱（尖点），然后把i加入栈底（左边界）或栈顶（右边界）。  
* **学习笔记**：双端队列是处理“两端操作”的单调栈的好工具，左右边界分开处理能避免逻辑混乱。


## 5. 算法可视化：像素动画演示

### 动画主题：像素战机的峡谷冒险  
**设计思路**：用8位像素风模拟峡谷飞行，让“找尖点”的过程变直观——复古风格能降低学习压力，音效和动画能强化记忆。

### 动画帧步骤与交互关键点  
1. **场景初始化**：  
   - 屏幕左侧是8位像素的峡谷（左蓝右红），右侧是控制面板（开始/暂停、单步、速度滑块）。  
   - 背景播放8位版《Ace Combat》BGM（轻快版）。  

2. **算法启动**：  
   - 起点（黄色小飞机）在峡谷底部，发射白色激光（视线），碰到左右边界时高亮交点。  
   - 队列用“像素方块堆”展示，栈底/栈顶的点闪烁。  

3. **核心步骤演示**：  
   - **找尖点**：激光碰到边界时，交点用绿色高亮，伴随“叮”的音效；  
   - **跳到尖点**：飞机沿白色线段滑到尖点，路径变成蓝色，尖点标记为黄色；  
   - **栈操作**：弹出栈底/栈顶时，方块有“消失”动画，伴随“咻”的音效。  

4. **终点达成**：  
   - 飞机到达终点时，整个路径闪烁，播放8位版胜利音乐（“通关”音效）；  
   - 弹出提示框：“路径完成！转向次数：X”。  

### 交互设计  
- **单步执行**：点击“下一步”，飞机移动一步，激光更新；  
- **自动播放**：滑块调节速度（1~5倍），飞机自动找尖点；  
- **重置**：回到起点，重新开始。  


## 6. 拓展练习与相似问题思考

### 通用思路迁移  
本题的“视线追踪+单调栈维护凸包”思路，可用于：  
- **路径规划**：比如机器人在迷宫中找最短路径；  
- **计算几何**：比如求凸包的“可见点”问题；  
- **数据结构**：比如单调栈解决“最大矩形”问题。

### 洛谷练习推荐  
1. **P1116 车厢重组**：用单调栈处理顺序问题，练栈的基本操作；  
2. **P1259 黑白棋子的移动**：类似“视线追踪”，练路径规划；  
3. **P3388 割点**：计算几何中的点定位问题，练单调栈维护凸包。


## 7. 学习心得与经验分享

### 镜音リン的经验  
> “单调栈维护凸包的关键是‘每个点只被处理一次’——栈里的点一旦被弹出，就不会再被访问，这样总复杂度是O(n)。”  
**点评**：这句话点出了线性复杂度的核心！很多同学怕“栈操作”会重复，但只要保证“每个点只进栈一次”，就能避免O(n²)的情况。

### Sol1的经验  
> “用余弦值比较角度能避免计算反正切的精度问题——因为余弦在[0,π]上是递减的，直接比较大小就行。”  
**点评**：这是计算几何的常用技巧！精度问题是编程题的“坑”，用余弦/正弦比较角度能减少误差。


## 结语  
这道题的核心是“找尖点”，而单调栈是高效解决的关键。希望这份指南能帮大家理解“视线追踪”的逻辑，掌握单调栈的用法。记住：编程的难点往往是“把问题转化为数据结构能处理的形式”——多练、多想，你也能成为“像素战机的Ace”！💪

---
处理用时：96.09秒