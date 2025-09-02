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


### 💡 Kay的C++算法解析：[USACO10MAR] StarCowraft G 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`计算几何（半平面交）`  
🗣️ **初步分析**：  
> 本题的核心是**在未知单位力量的约束下预测战役胜负**。想象你在玩一款策略游戏，需要根据历史对战记录（测试战役）反推兵种隐藏属性，再用这些属性预测新战役结果。  
> - **核心难点**：测试战役转化为线性不等式（半平面），新战役对应判定直线  
> - **解决思路**：  
>   1. 收集所有测试战役的不等式约束（如：6x+5y+4 > 5x+4y+7 ⇒ x+y > 3）  
>   2. 求半平面交得到凸多边形（可行解区域）  
>   3. 判断新战役直线与凸多边形的位置关系  
> - **可视化设计**：  
>   用8位像素网格展示(x,y)平面，历史约束为彩色半透明区域（如FC游戏地图），可行解区域用闪烁方块标记。新战役直线高亮显示，音效随判定结果变化（胜利：8-bit胜利曲；不确定：提示音效）。

---

#### 2. 精选优质题解参考
**题解一（kuikuidadi）**  
* **点评**：思路直击本质，将问题转化为半平面交的几何问题，逻辑清晰度满分。虽无代码，但对核心变量（S1/S2/S3→二维平面点）和算法流程（半平面交→凸多边形判定）的推导极具教学价值，是理解本题的黄金钥匙。  

**题解二（dingyichen）**  
* **点评**：提供完整实现，通过配凑法处理不等式组。亮点在于加入边界约束（100倍规则）和冗余消除。但代码可读性待提升（如b1~b4数组含义需注释），嵌套循环导致O(N²M)复杂度，在大数据时需优化。  

---

#### 3. 核心难点辨析与解题策略
1. **难点：不等式组的几何转化**  
   * **分析**：测试战役需转化为形如ax+by≤c的半平面。关键变量是兵种差值（如J1-B1）。需注意等式处理（如除零问题）和方向判断（胜者决定不等号方向）。  
   * 💡 **学习笔记**：每个战役对应一个半平面，胜者决定平面方向  

2. **难点：可行解区域的边界处理**  
   * **分析**：需显式添加约束：  
     - 正数约束：x>0, y>0  
     - 100倍规则：x≤100y, y≤100x 等  
   * 💡 **学习笔记**：无界区域需人工限定，否则影响判定准确性  

3. **难点：新战役的胜负判定**  
   * **分析**：将新战役转化为直线ax+by=c：  
     - 若凸多边形全在直线一侧 → 确定胜者  
     - 若直线穿过凸多边形 → 结果不确定（U）  
   * 💡 **学习笔记**：几何判定本质是线性规划的可行性验证  

**✨ 解题技巧总结**  
- **技巧1：降维打击** → 利用齐次性将三维(S1,S2,S3)降至二维(x,y)  
- **技巧2：可视化辅助** → 画图理解半平面交和凸多边形  
- **技巧3：边界测试** → 优先验证0值/相等/极端比例情况  

---

#### 4. C++核心代码实现赏析
**本题通用核心实现参考**  
* **说明**：基于半平面交思想，简化dingyichen代码关键逻辑  
* **核心代码**：  
  ```cpp
  #include <vector>
  #include <cmath>
  using namespace std;

  struct Point { double x, y; };
  struct Line { double a, b, c; }; // ax+by=c

  // 求两直线交点（需处理平行情况）
  Point intersect(Line L1, Line L2) {
    double det = L1.a*L2.b - L2.a*L1.b;
    if(fabs(det) < 1e-9) return {NAN, NAN}; // 平行
    return {
      (L2.b*L1.c - L1.b*L2.c)/det,
      (L1.a*L2.c - L2.a*L1.c)/det
    };
  }

  // 关键判定：点是否在半平面内 (ax+by<=c)
  bool inHalfPlane(Point p, Line L) {
    return L.a*p.x + L.b*p.y <= L.c + 1e-9;
  }
  ```
* **解读概要**：  
  1. 将测试战役转为Line结构体存入vector  
  2. 添加边界约束生成初始凸多边形  
  3. 对新战役生成判定线，遍历凸多边形顶点检查位置  

**题解二片段赏析**  
* **亮点**：通过配凑法避免几何计算  
* **核心代码**：  
  ```cpp
  // 枚举已知不等式对(i,j)判定新战役q
  for(int j=total; j>minIdx; j--){
    for(int k=minIdx+1; k<j; k++){
      double det = b3[k]*b2[j] - b2[k]*b3[j];
      double x = (c2*b3[k] - b2[k]*c3)/det;
      double y = (b2[j]*c3 - c2*b3[j])/det;
      if(x>=0 && y>=0){
        if(x*b1[j] + y*b1[k] < c1) 
          { /* 判定为J胜 */ }
  }}}
  ```
* **代码解读**：  
  > 通过解线性组合系数(x,y)将新战役约束c1,c2,c3用已知约束b1,b2,b3表示。若组合系数非负且不等式成立，则判定胜负。  
* 💡 **学习笔记**：配凑法本质是求解线性方程组，但需注意数值稳定性  

---

#### 5. 算法可视化：像素动画演示
**主题**：*星际指挥官：战力解密行动*  
**设计思路**：  
> 采用FC《高级战争》像素风格，将二维平面化为星际地图。单位力量比转为地形高度，半平面作为"势力范围"，凸多边形是"安全区"。  

**关键动画帧**：  
1. **初始化**（8-bit音效）  
   - 网格地图：x/y轴表示S1/S2比值，绿色像素块表示可行解  
   - 控制面板：速度滑块/单步执行/重置  

2. **添加测试战役**（动态绘制）  
   - 每读一条记录：地图新增半透明色块（J胜→蓝色，B胜→红色）  
   - 音效：添加约束时播放"数据录入"音效  

3. **生成可行解区**  
   - 半平面交区域用闪烁金框标记，顶点显示坐标  
   - 背景音乐：《星际争霸》8-bit改编版  

4. **新战役判定**  
   - 画红色判定线分割地图  
   - 自动检测：金框全部在蓝区→播放胜利音效+烟花动画  
   - 金框跨红蓝区→显示"？"图标+不确定音效  

**交互设计**：  
- **AI演示模式**：自动播放战役添加和判定过程，像观看AI解谜  
- **关卡模式**：每通过一个测试战役解锁新技能点  

---

#### 6. 拓展练习与相似问题
**通用技巧迁移**：  
1. 线性规划可行性判定（如资源分配）  
2. 几何约束求解（如机器人运动规划）  
3. 隐藏参数推断（如经济模型校准）  

**洛谷推荐**：  
1. **P1257 平面上的最接近点对**  
   → 巩固分治与几何处理  
2. **P1514 引水入城**  
   → 练习约束转化与覆盖判定  
3. **P5021 赛道修建**  
   → 进阶训练半平面交应用  

---

#### 7. 学习心得分享
> **dingyichen的调试经验**：  
> *"加入边界约束时，发现若未显式处理x>0会导致可行域错误。建议先验证极端情况（如单兵种战役）。"*  
> **Kay总结**：边界条件常是BUG温床，优先测试：  
> - 全零单位战役  
> - 单兵种极端比例战役  

---

通过本指南，你已掌握星际战役的预测奥秘！记住：算法本质是**将现实问题转化为可计算的模型**。下次遇到隐藏参数问题，不妨试试几何化思考！🚀

---
处理用时：111.85秒