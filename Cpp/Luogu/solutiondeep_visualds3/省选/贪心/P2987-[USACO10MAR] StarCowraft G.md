# 题目信息

# [USACO10MAR] StarCowraft G

## 题目描述

The beta version of StarCowraft II is ready! Farmer John and Bessie are testing it, trying different strategies in one-on-one battles against each other's armies. The goal in StarCowraft II is to defeat your opponent's army in a battle.

Each player's army fights in a battle. An army comprises as many as three different types of 'units' with respective strengths denoted by constant positive real numbers unknown to the players: cattlebruisers with strength S1, cow templars with strength S2, and ultracows with strength S3. The only given bounding information is that no unit is more than 100 times as strong as any another unit.

An army's total strength is the sum of the individual strengths of each of its units. An army that has, among others units, 23

cattlebruisers would gain 23\*S1 strength just from the cattlebruisers.

When two opposing armies fight in a battle, the army with a higher total strength value wins.  If the armies have exactly equal strength values, one of the players randomly wins.

Farmer John and Bessie played N (0 <= N <= 300) 'test battles'. In the i-th test battle, FJ's army had J1\_i cattlebruisers, J2\_i cow templars, and J3\_i ultracows (0 <= J1\_i + J2\_i + J3\_i <= 1,000). Similarly, Bessie's army had B1\_i cattlebruisers, B2\_i cow templars, and B3\_i ultracows (0 <= B1\_i + B2\_i + B3\_i <= 1,000). After their armies fought against each other, FJ and Bessie recorded the winner as a single 'victory letter' V\_i: 'J' if Farm John won the battle; 'B' if Bessie won.

Although these victory results are the only information that they have, they hope to predict some of the results of additional battles if they are given the unit compositions of two opposing armies. For some battles, though, they know it might not be possible to determine the winner with certainty.

Given the results of the N test battles that Farmer John and Bessie already played, write a program that decides the winner (if possible) for M (1 <= M <= 2,000) new battles.

The results reported for the test battles are correct; there exists at least one set of strength values which are consistent with the results.

For purposes of demonstrating the army strength evaluation functions, consider these test battles fought in a game where we (but neither FJ nor Bessie) know that S1=9.0, S2=7.0, and S3=4.0:

```cpp
---- Farmer John ----    ------- Bessie ------    Battle 
J1  J2  J3 J_Strength    B1  B2  B3 B_Strength   Outcome 
6   5   4    105         5   4   7    101          J 
5   4   2     81         3   5   5     82          B 
9   0  10    121         8   2   7    114          J 
```
These results connote the following deduced results for the reasons shown:

---- Farmer John ----    ------- Bessie ------    Battle

J1  J2  J3 J\_Strength    B1  B2  B3 B\_Strength   Outcome

6   6   4    112         5   4   7    101          J

FJ's army is even stronger than in test battle 1 9   0  10    121         8   2   6    110          J

Bessie's army is even weaker than in test battle 3

《星际争霸2》全面公测啦！Farmer John和Bessie正在测试中——在1v1的战役中使用一些不同的策略来对抗对方的部队。《星际争霸2》的游戏目标就是在战役中打败你对手的军队。

每个选手的军队都在战役中拼杀。一支军队由若干3种不同类型的单位所组成，不同单位有着不同的由正实数表示的，且不被选手所知道的力量值：cattlebruisers 的力量是S1，cow templars 的力量是S2，ultracows的力量是S3。唯一提供的信息是，没有一个单位的力量值超过另一个单位力量值的100倍。

一支军队的总力量值，是其中各自单独的单位的力量值的总和。比如一支军队除了其他单位有23个cattlebruisers，那么这支军队单独从cattlebruisers就能获得23\*S1的力量值。

当两支对立的军队在战役中厮杀，有着更高力量值的军队将获得胜利。如果两支军队的力量值恰好相同，那么将随机产生一个获胜方。

Farmer John 和 Bessie 进行了 N (0 <= N <= 300) 局的“测试战役”。在第 i 局测试战役中，Farmer John 有 J1\_i 个 cattlebruisers，J2\_i 个 cow templars 以及 J3\_i 个 ultracows(0 <= J1\_i + J2\_i + J3\_i <= 1,000)。相似的，Bessie的军队有 B1\_i 个 cattlebruisers，B2\_i 个 cow templars 以及 B3\_i 个 ultracows (0 <= B1\_i + B2\_i + B3\_i <= 1,000)。当他们的军队战斗结束后，FJ 和 Bessie 将胜者以一个单独的“胜利字母” V\_i 记录下来："J"表示 Farmer John 赢得了战役；"B" 表示 Bessie 获胜了。

虽然这些结果是他们唯一所拥有的信息，但是他们希望预测一些额外的战役的结果——如果告知他们两支对立军队的组成。尽管，可能对于一些比赛他们是无法确定到底哪一方一定能获胜的。

给出已经结束的 N 场测试战役的结果，写一个程序来确定(如果可能的话)M (1 <=M <=2,000)场额外战役的获胜方。

所有给出的测试战役的结果都是正确的。至少存在一种合法的力量值的取值符合这些结果。


## 说明/提示

First two games correspond to the examples in the description. The result of the last game cannot be determined with only the information that Farmer John and Bessie currently have. Specifically, both S\_1=9.0, S\_2=7.0, S\_3=4.0 and S\_1=12.0, S\_2=20.0, S\_3=10.0 are consistent with the &quot;test battles,&quot; but they give different results when plugged in the third &quot;new battle.&quot;


## 样例 #1

### 输入

```
3 3 
J 6 5 4 5 4 7 
B 5 4 2 3 5 5 
J 9 0 10 8 2 7 
6 6 4 5 4 7 
9 0 10 8 2 6 
3 4 8 4 4 6 
```

### 输出

```
J 
J 
U 
```

# AI分析结果


### 💡 Kay的C++算法解析：StarCowraft G 深入学习指南 💡

**引言**  
今天我们一起分析《StarCowraft G》这道关于单位战斗力推断的题目。本指南将帮助你理解半平面交的核心思想，掌握解题技巧，并通过像素化动画直观感受算法执行过程。

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`半平面交`（计算几何）

🗣️ **初步分析**：  
> 解决本题的关键在于将战斗结果转化为几何约束。想象你在绘制一张"战斗力地图"，每个已知战斗结果就像一条分界线，划分出FJ/Bessie的胜利区域。这些分界线围成的凸多边形区域就是所有可能的战斗力解。  
> - 核心难点在于处理300+不等式约束（包括战斗结果和单位强度比限制），并用半平面交算法求解可行域。  
> - 可视化设计：用像素网格表示S1-S2平面，战斗分界线用不同颜色绘制。凸多边形区域用闪烁的边界线标记，顶点用旋转的星标突出显示。  
> - 复古游戏化：采用《星际争霸》像素风格，单位用像素兵种图标表示。关键操作时播放"激光"音效，求解完成时播放胜利音乐。

---

## 2. 精选优质题解参考

**题解一（kuikuidadi）**  
* **点评**：思路清晰直指几何本质，将战斗转化为半平面约束，用凸多边形顶点判断新战斗结果。亮点在于完整呈现算法框架，虽然未提供代码，但理论推导严谨（如正确处理单位强度比约束）。实践价值高，可直接用于竞赛场景。

**题解二（dingyichen）**  
* **点评**：采用代数配凑法替代几何解法，通过线性组合推导不等式关系。亮点在代码完整且处理了边界条件（如单位数量差为0的情况）。但实现较复杂（双重循环枚举约束对），时间复杂度O(N²M)较高，在极端数据可能超时。

---

## 3. 核心难点辨析与解题策略

1. **约束条件转化**  
   * **分析**：将战斗结果J/B转化为ax+by+c>0/<0形式时需注意方向（如Bessie胜利需取负值）。单位强度比约束需转化为S1≥0.01等6个边界条件。  
   * 💡 学习笔记：每个不等式对应半平面，方向由法向量决定。

2. **半平面交算法实现**  
   * **分析**：需按极角排序直线，用双端队列维护半平面边界。关键在正确处理平行线（保留内侧约束）和精度控制（eps=1e-8）。  
   * 💡 学习笔记：凸多边形顶点数≤约束数，可用单调队列优化。

3. **新战斗结果判定**  
   * **分析**：线性函数在凸多边形的极值必在顶点处。遍历所有顶点检查f(S1,S2)=d1S1+d2S2+d3符号是否一致。  
   * 💡 学习笔记：若所有顶点f>0则FJ必胜，f<0则Bessie必胜，否则不确定。

### ✨ 解题技巧总结
- **几何转化法**：将代数约束可视化为半平面，利用计算几何工具求解
- **顶点极值原理**：凸区域上线性函数的最值总在边界顶点
- **精度容错处理**：浮点比较用相对误差eps避免精度陷阱
- **边界特判**：单独处理d1=d2=0的退化情况

---

## 4. C++核心代码实现赏析

**通用核心实现参考**  
```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <deque>
using namespace std;

const double EPS = 1e-8;
struct Point { double x, y; };
struct Line { Point s, e; double ang; };

// 半平面交核心实现
vector<Point> halfPlaneIntersection(vector<Line> lines) {
    // 排序/去重/双端队列求解（因篇幅省略具体实现）
    // 返回凸多边形顶点集合
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<Line> constraints;
    
    // 添加单位强度比约束：0.01<=S1,S2<=100, S1<=100S2, S2<=100S1
    constraints.push_back({{0.01,-1000}, {0.01,1000}}); // S1>=0.01
    // ... 添加其他5个边界约束

    // 处理已知战斗
    while (N--) {
        char result; 
        double j1,j2,j3,b1,b2,b3;
        cin >> result >> j1 >> j2 >> j3 >> b1 >> b2 >> b3;
        double a = j1 - b1, b = j2 - b2, c = j3 - b3;
        if (result == 'B') a = -a, b = -b, c = -c; // Bessie胜取反
        
        // 构造战斗约束直线
        Point p1 = {0, -c/b}, p2 = {100, -(a*100+c)/b}; // 示例构造
        constraints.push_back({p1, p2, atan2(b, a)});
    }
    
    // 求解可行域凸多边形
    vector<Point> poly = halfPlaneIntersection(constraints);
    
    // 处理新战斗
    while (M--) {
        double j1,j2,j3,b1,b2,b3;
        cin >> j1 >> j2 >> j3 >> b1 >> b2 >> b3;
        double d1 = j1 - b1, d2 = j2 - b2, d3 = j3 - b3;
        
        // 退化情况处理
        if (fabs(d1)<EPS && fabs(d2)<EPS) {
            cout << (fabs(d3)<EPS ? "U" : (d3>0?"J":"B")) << endl;
            continue;
        }
        
        // 检查凸多边形顶点符号
        int pos = 0, neg = 0;
        for (auto p : poly) {
            double val = d1 * p.x + d2 * p.y + d3;
            if (val > EPS) pos++;
            else if (val < -EPS) neg++;
        }
        
        if (pos && !neg) cout << "J\n";
        else if (neg && !pos) cout << "B\n";
        else cout << "U\n";
    }
    return 0;
}
```

**代码解读概要**：  
> 核心分为三阶段：① 收集N场战斗的线性约束+6条边界约束 ② 半平面交算法求凸多边形 ③ 对M个新战斗，用顶点极值原理判定结果。注意退化情况单独处理。

---

## 5. 算法可视化：像素动画演示

**动画主题**：*《星际争霸》像素指挥官*

**核心演示**：半平面交求解与战斗结果预测  
![](https://via.placeholder.com/400x200/000000/FFFFFF?text=半平面交像素动画示意图)

**设计思路**：  
> 采用8位机像素风格，S1-S2平面转化为星际地图。不同单位用像素图标表示（🐮cattlebruiser/⚔️cow templar/👾ultracow）

**关键帧流程**：  
1. **战场初始化**：  
   - 背景：深空网格地图，坐标轴标注S1/S2范围[0.01,100]  
   - 控制台：开始/步进/速度滑块按钮（复古街机风格）  
   - 音效：星际基地环境音效（持续低频嗡嗡声）

2. **约束绘制（每场战斗）**：  
   ``` 
   [战斗1] J 6 5 4 5 4 7 → 直线: (6-5)S1+(5-4)S2+(4-7)>0
   ```
   - 视觉：红色激光从坐标点(0.01,0.01)射出，动态绘制直线  
   - 音效：激光"咻"声 + 单位登场音效（根据单位类型不同音调）

3. **半平面交过程**：  
   - 算法步进：显示当前处理的约束线（高亮闪烁）  
   - 双端队列：左侧显示当前维护的边界线队列（像素化列表）  
   - 凸多边形：每步更新可行域（半透明绿色填充）  
   - 音效：约束添加时"叮"声，可行域缩小"嗡"声

4. **新战斗预测**：  
   - 输入新单位组合：显示FJ/Bessie的像素兵力布局  
   - 遍历顶点：凸多边形顶点逐个闪烁，显示当前点f(S1,S2)值  
   - 判定结果：J/B胜利时播放胜利号角，U时显示问号图标

5. **游戏化扩展**：  
   - 关卡系统：每5场战斗为一关，过关解锁新单位皮肤  
   - 积分奖励：快速正确预测+10分，动画暂停时显示连击数  
   - AI演示模式：自动展示最优约束添加顺序（贪心策略）

---

## 6. 拓展练习与相似问题思考

**技巧迁移场景**：  
1. 资源分配优化（线性约束求最优解）  
2. 碰撞检测（几何约束求交集）  
3. 机器学习分类（线性可分问题）

**洛谷推荐**：  
1. **P4196 凸多边形**  
   → 巩固半平面交模板实现  
2. **P2742 圈奶牛**  
   → 练习几何约束转化能力  
3. **P3256 星际战争**  
   → 类似单位战力评估问题  

---

## 7. 学习心得与经验分享

**题解二作者经验**：  
> *"手动添加0.01边界约束时，因忽略方向导致WA多次... 务必验证约束方向！"*

**Kay点评**：  
> 这个教训非常典型。几何问题中约束方向直接影响可行域形状。建议：  
> 1. 用简单点（如(1,1)）验证约束符号  
> 2. 绘制小规模约束验证方向  
> 3. 边界约束单独测试  

---

**结语**  
通过半平面交将战斗问题转化为几何约束，是计算几何的经典应用。掌握顶点极值原理和约束转化技巧，你就能像星际指挥官一样精准预测战局！下次遇到类似问题，记得画出你的"战斗力地图"哦 🚀

---
处理用时：182.19秒