# 题目信息

# The Strict Teacher (Easy Version)

## 题目描述

This is the easy version of the problem. The only differences between the two versions are the constraints on $ m $ and $ q $ . In this version, $ m=2 $ and $ q=1 $ . You can make hacks only if both versions of the problem are solved.

Narek and Tsovak were busy preparing this round, so they have not managed to do their homework and decided to steal David's homework. Their strict teacher noticed that David has no homework and now wants to punish him. She hires other teachers to help her catch David. And now $ m $ teachers together are chasing him. Luckily, the classroom is big, so David has many places to hide.

The classroom can be represented as a one-dimensional line with cells from $ 1 $ to $ n $ , inclusive.

At the start, all $ m $ teachers and David are in distinct cells. Then they make moves. During each move

- David goes to an adjacent cell or stays at the current one.
- Then, each of the $ m $ teachers simultaneously goes to an adjacent cell or stays at the current one.

This continues until David is caught. David is caught if any of the teachers (possibly more than one) is located in the same cell as David. Everyone sees others' moves, so they all act optimally.

Your task is to find how many moves it will take for the teachers to catch David if they all act optimally.

Acting optimally means the student makes his moves in a way that maximizes the number of moves the teachers need to catch him; and the teachers coordinate with each other to make their moves in a way that minimizes the number of moves they need to catch the student.

Also, as Narek and Tsovak think this task is easy, they decided to give you $ q $ queries on David's position. Note: this is the easy version, and you are given only one query.

## 说明/提示

In the first example, the student can just stay at cell $ 2 $ . The teacher, initially located in cell $ 1 $ , can reach cell $ 2 $ in one move. Therefore, the answer is $ 1 $ .

In the second example, the student should just stay at cell $ 1 $ . The teacher, initially located in cell $ 3 $ , can reach cell $ 1 $ in two moves. Therefore, the answer is $ 2 $ .

## 样例 #1

### 输入

```
3
10 2 1
1 4
2
8 2 1
3 6
1
8 2 1
3 6
8```

### 输出

```
1
2
2```

# AI分析结果


### Kay的C++算法解析：The Strict Teacher (Easy Version) 深入学习指南

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`编程技巧应用` (分类讨论与最优策略分析)

🗣️ **初步分析**：
> 解决这道题的关键在于理解一维空间中的追捕最优策略。就像两个守门员协同防守一个突破球员：守门员会封堵两侧路线，球员则选择最有利的逃跑方向。  
> - 核心思路：根据学生位置与教师位置的相对关系分三种情况讨论（左/中/右），每种情况对应不同的最优移动策略。  
> - 难点在于证明每种策略的最优性：学生总是逃向离教师最远的方向，教师则同步压缩空间。  
> - 可视化设计：用8位像素风直线表示教室，不同颜色方块表示角色。关键步骤高亮学生移动方向、教师包围路径，并添加"逼近音效"。自动演示模式将展示三种场景的追捕过程。

---

#### 2. 精选优质题解参考
**题解一（来源：masonxiong）**  
* **点评**：思路最严谨，完整证明相对位置不变性。代码用`sort`规范处理教师位置，时间复杂度O(1)。边界处理清晰（如最左/最右位置计算），变量命名`b[0]`/`b[1]`直观。亮点在于用数学归纳法证明学生无法越过教师，具有教学启发性。

**题解二（来源：封禁用户）**  
* **点评**：代码最简洁（仅10行核心逻辑），用`swap`处理教师排序。实践性强，直接给出三种情况的闭式解。亮点是提出学生应逃向教师中点的策略，但未详细证明最优性。

**题解三（来源：lxyz）**  
* **点评**：分类逻辑完整，变量命名规范（`b1`/`b2`）。强调手写交换比`swap`高效（实际差异可忽略），适合竞赛习惯。不足是中间情况公式`(b2-b1)/2`未解释整数除法特性。

---

#### 3. 核心难点辨析与解题策略
1. **关键点1：相对位置不变性的证明**  
   * **分析**：学生无法越过教师（教师可选择不动拦截），因此初始位置关系决定全程策略。优质题解用反证法：若学生试图穿越，教师原地即可捕获。
   * 💡 学习笔记：位置关系约束是分类讨论的基石。

2. **关键点2：三种情况的策略证明**  
   * **分析**：  
     - 左侧：师生同步向左，学生被逼至墙边（步数=教师到墙距）  
     - 中间：教师双向包夹，学生逃向中点（步数=教师间距/2）  
     - 右侧：镜像左侧情况
   * 💡 学习笔记：最优策略是最大化最小捕获时间。

3. **关键点3：整数除法的合理性**  
   * **分析**：步数需为整数，`(b2-b1)/2`自动向下取整符合移动特性。当间距为奇数时，教师同步移动仍能在下一步捕获。
   * 💡 学习笔记：离散问题中整数除法天然满足场景需求。

### ✨ 解题技巧总结
- **问题分解**：将连续移动转化为位置关系+距离计算的离散问题
- **边界优先处理**：先排序教师位置确保`b1<b2`，避免后续分支冗余
- **闭式解优化**：直接数学计算替代模拟，复杂度从O(n)降至O(1)

---

#### 4. C++核心代码实现赏析
**通用核心实现**  
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int t, n, m, q, a, b1, b2;
    cin >> t;
    while (t--) {
        cin >> n >> m >> q >> b1 >> b2 >> a;
        if (b1 > b2) swap(b1, b2);  // 确保b1<=b2
        if (a < b1) cout << b1 - 1;
        else if (a > b2) cout << n - b2;
        else cout << (b2 - b1) / 2;  // 整数除法
        cout << '\n';
    }
    return 0;
}
```
* **说明**：综合优质题解的最简实现，完整处理输入输出流
* **解读概要**：先排序教师位置，再用三类条件分支直接输出数学解

**题解一（masonxiong）**  
```cpp
sort(b, b + 2);
if (a < b[0]) cout << b[0] - 1;
else if (a > b[1]) cout << n - b[1];
else cout << (b[1] - b[0]) / 2;
```
* **亮点**：使用标准库排序确保位置关系
* **解读**：`sort(b, b+2)`将教师位置升序排列，避免手动交换。数组索引`b[0]`/`b[1]`比单独变量更易扩展
* 💡 学习笔记：标准库函数提升代码可读性与可扩展性

**题解二（封禁用户）**  
```cpp
if (b1 > b2) swap(b1, b2);
if (a < b1) cout << b1 - 1;
else if (a < b2) cout << (b2 - b1) / 2;
else cout << n - b2;
```
* **亮点**：最简分支结构与清晰的边界条件
* **解读**：`swap`保证`b1`为左教师。中间情况`a<b2`隐含`a>b1`，减少比较次数
* 💡 学习笔记：利用条件隐含关系简化逻辑判断

**题解三（lxyz）**  
```cpp
if (b1 > b2) { /* 手动交换 */ }
if (a < b1) cout << b1 - 1;
else if (a > b1 && a < b2) cout << (b2 - b1) / 2;
else if (a > b2) cout << a - b2;  // 注意此处与通用解差异
```
* **亮点**：强调手动交换可能优化性能（实际场景差异可忽略）
* **解读**：显式写`a>b1&&a<b2`增强可读性。右侧解用`a-b2`而非`n-b2`，需注意题目描述中学生也可移动
* 💡 学习笔记：竞赛中需严格对照题目描述验证公式

---

#### 5. 算法可视化：像素动画演示
![](https://cdn.luogu.com.cn/upload/image_hosting/7xqpqbcw.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
* **主题**：8位像素风"教室大追捕"  
* **核心演示**：三种位置场景的策略动画（教师红/蓝方块，学生绿方块）  

**交互设计**：  
1. **场景初始化**：像素直线标单元格（1-n），控制面板含速度滑块/暂停键  
2. **关键动画帧**：  
   - 左侧场景：学生向左逃逸时播放"疾走音效"，教师同步左移高亮  
   - 中间场景：双教师向中心靠拢，间距每减2像素触发"包围音效"  
   - 捕获时刻：学生方块闪烁红光+胜利音效  
3. **AI演示模式**：自动切换三种初始位置，速度可调  

**设计逻辑**：  
> 像素移动直观展示位置关系变化，音效强化策略感知（如包围音效提示教师协作）。速度控制帮助理解步数计算本质是距离转化。

---

#### 6. 拓展练习与相似问题思考
**技巧迁移**：位置最优策略问题常见于：  
1. 多人追捕游戏AI设计  
2. 分布式机器人协同围堵  
3. 网络传输路径优化  

**洛谷推荐**：  
1. **P1258 小车问题**  
   🗣️ 两车接送问题，同样需要分阶段计算最优时间  
2. **P1514 引水入城**  
   🗣️ 区间覆盖问题，训练分类讨论能力  
3. **P1095 守望者的逃离**  
   🗣️ 动态规划+贪心抉择，强化最优策略设计  

---

#### 7. 学习心得与经验分享
> 本次题解未包含作者个人调试心得，但Kay建议：  
> **关键验证点**：  
> - 测试教师位置未排序的边界用例  
> - 验证中间情况间距为奇数时的捕获步数一致性  
> **调试技巧**：  
> 用`cout`输出中间距离值，对照手工计算验证分支正确性

---
### 总结  
本题通过位置关系分类和最优策略分析，展现了离散数学在算法中的巧妙应用。核心在于将动态追捕转化为静态距离计算，这种"问题转化思维"是算法设计的精髓。大家可尝试修改为m>2的版本，思考多教师协同策略！🚀

---
处理用时：124.13秒