# 题目信息

# Billiard

## 题目描述

Consider a [billiard table](https://en.wikipedia.org/wiki/Billiard_table) of rectangular size $ n \times m $ with four pockets. Let's introduce a coordinate system with the origin at the lower left corner (see the picture).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF982E/5400ec264949b612eb9900ddf2189fccb1a2c217.png)There is one ball at the point $ (x, y) $ currently. Max comes to the table and strikes the ball. The ball starts moving along a line that is parallel to one of the axes or that makes a $ 45^{\circ} $ angle with them. We will assume that:

1. the angles between the directions of the ball before and after a collision with a side are equal,
2. the ball moves indefinitely long, it only stops when it falls into a pocket,
3. the ball can be considered as a point, it falls into a pocket if and only if its coordinates coincide with one of the pockets,
4. initially the ball is not in a pocket.

Note that the ball can move along some side, in this case the ball will just fall into the pocket at the end of the side.

Your task is to determine whether the ball will fall into a pocket eventually, and if yes, which of the four pockets it will be.

## 说明/提示

The first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF982E/69be840146adfcf731c5725a9e0b894673e7da29.png)The second sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF982E/a92c4ee568a643301b20d63f7451b437aa813098.png)In the third sample the ball will never change its $ y $ coordinate, so the ball will never fall into a pocket.

## 样例 #1

### 输入

```
4 3 2 2 -1 1
```

### 输出

```
0 0```

## 样例 #2

### 输入

```
4 4 2 0 1 1
```

### 输出

```
-1```

## 样例 #3

### 输入

```
10 10 10 1 -1 0
```

### 输出

```
-1```

# AI分析结果


### 💡 Kay的C++算法解析：Billiard 深入学习指南 💡

**引言**  
今天我们来分析“Billiard”这道台球轨迹问题。题目要求判断小球在矩形台球桌上能否落入角落袋口，并确定具体袋口位置。本指南将结合数学建模和算法实现，通过**翻折技巧**和**扩展欧几里得算法**帮你掌握核心解法。

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数学建模与扩展欧几里得算法`

🗣️ **初步分析**：
> 解决台球轨迹问题的核心在于**翻折技巧**——想象将台球桌无限平铺，小球运动轨迹变为直线而非反弹。这就像把台球桌当作镜子反复翻折，使路径拉直。  
> 通过方程 \( an - bm = x - y \) 建模（\( a,b \) 为翻折次数），用扩展欧几里得算法求解最小非负解，最后根据解的奇偶性确定袋口位置。  
> **可视化设计**：采用8位像素风格模拟台球桌翻折。小球沿直线运动，每次触边时播放“翻页”音效，画面镜像翻转；当小球进入袋口时，目标袋口闪烁并播放胜利音效。控制面板支持单步调试，高亮当前方程和奇偶性判断逻辑。

---

## 2. 精选优质题解参考

**题解一（来源：是个汉子）**  
* **点评**：思路清晰直击本质——通过坐标翻转将速度归一化，建立方程 \( an - bm = x - y \)。代码规范：  
  - 边界处理完整（如速度分量为0的特判）  
  - 扩展欧几里得实现标准，解的范围调整巧妙（模运算取最小非负解）  
  - 奇偶性判断逻辑简洁（`a1%2==0` 决定坐标翻转）  
  **亮点**：物理问题到数学模型的转化过程阐释透彻，变量命名合理（如 `rex` 标记X轴翻转）。

**题解二（来源：Leap_Frog）**  
* **点评**：解法高效，代码精简但完整覆盖核心：  
  - 坐标翻转用位运算记录（`u = v<0 ? 1 : 0`）  
  - 方程求解后直接通过 `ra & 1` 位操作判断奇偶性  
  - 空间复杂度优化至 \( O(1) \)  
  **亮点**：数学推导与代码实现高度契合，适合竞赛快速编码。

---

## 3. 核心难点辨析与解题策略

1. **难点1：速度方向归一化**  
   * **分析**：初始速度含负分量或零需特殊处理。优质题解通过坐标翻转（如 \( x = n-x \)）将速度转为 \((1,1)\) 方向，简化问题。  
   💡 **学习笔记**：坐标翻转是减少分支判断的关键技巧。

2. **难点2：翻折建模与方程建立**  
   * **分析**：将反弹转化为直线运动需推导方程 \( an - bm = x-y \)。核心是理解 \( a,b \) 为台球桌横向/纵向翻折次数。  
   💡 **学习笔记**：翻折后小球位置 \( (x+an, y+bm) \) 需同时为袋口坐标的倍数。

3. **难点3：解的有效性检验与袋口映射**  
   * **分析**：扩展欧几里得有解需 \( (x-y) \mod \gcd(n,m) =0 \)。解 \( a,b \) 的奇偶性决定最终袋口——奇数次翻折落对角袋口，偶数次落同侧袋口。  
   💡 **学习笔记**：奇偶性决定物理坐标是否需回翻。

### ✨ 解题技巧总结
- **技巧1：降维归一化**（速度/坐标）减少分支  
- **技巧2：扩展欧几里得解范围调整**（模运算取最小正整数解）  
- **技巧3：位运算优化**（奇偶性用 `&1` 代替 `%2`）  

---

## 4. C++核心代码实现赏析

**通用核心实现**  
```cpp
#include <iostream>
using namespace std;
typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) { x = 1; y = 0; return a; }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

int main() {
    ll n, m, x, y, vx, vy;
    cin >> n >> m >> x >> y >> vx >> vy;
    
    // 特判速度分量为0
    if (vx == 0) { /* 处理代码略 */ }
    if (vy == 0) { /* 处理代码略 */ }

    // 坐标翻转使速度朝正方向
    bool flip_x = (vx < 0), flip_y = (vy < 0);
    if (flip_x) x = n - x;
    if (flip_y) y = m - y;

    // 求解 an - bm = x - y
    ll a, b, g = exgcd(n, -m, a, b);
    if ((x - y) % g) { cout << -1; return 0; }

    // 调整解为非负最小
    ll t = (x - y) / g;
    a *= t; b *= t;
    ll mod = m / abs(g);
    a = (a % mod + mod) % mod;
    b = (a * n - (x - y)) / m;

    // 奇偶性决定袋口
    ll px = (a % 2) ? n : 0;
    ll py = (b % 2) ? m : 0;
    if (flip_x) px = n - px; // 回翻坐标
    if (flip_y) py = m - py;
    cout << px << " " << py;
}
```
**代码解读概要**：  
1. 速度0分量直接特判  
2. 负速度方向通过坐标翻转归一化  
3. 扩展欧几里得求解方程  
4. 调整解范围后按奇偶性映射袋口  
5. 坐标回翻输出结果  

---

**题解一片段赏析（是个汉子）**  
* **亮点**：解范围调整逻辑清晰  
* **核心代码**：
  ```cpp
  a1 = (a % m1 + m1 - 1) % m1 + 1; // 取最小正整数解
  if (a1 % 2 == 0) ansx = n - ansx; // 奇偶性判断
  ```
* **代码解读**：  
  > 通过模运算将解 \( a \) 调整到 \( [1, m1] \) 范围，避免负值。`a1 % 2 == 0` 时，因翻折次数为偶，袋口取反向（如左上变右下）。  
* 💡 **学习笔记**：最小正整数解保证物理合理性，奇偶性是坐标映射钥匙。

---

**题解二片段赏析（Leap_Frog）**  
* **亮点**：位运算高效判断奇偶性  
* **核心代码**：
  ```cpp
  u ^= ra & 1; // 异或翻转标记
  v ^= rb & 1;
  printf("%d %d", u ? n : 0, v ? m : 0);
  ```
* **代码解读**：  
  > `ra & 1` 取二进制末位（等价奇偶判断），`u ^= 1` 实现翻转标记切换。最终输出时若 `u=1` 说明需取 \( n \)（右侧袋口）。  
* 💡 **学习笔记**：位运算提升效率，异或实现状态切换。

---

## 5. 算法可视化：像素动画演示

**主题**：8位像素风台球桌翻折模拟  
**核心演示**：小球直线运动→触边翻折→袋口判定  

### 设计细节：
1. **场景初始化**  
   - 16色像素网格：绿色台面、棕色边框、红色袋口  
   - 小球像素精灵：蓝色圆点+黄色速度箭头  
   - 控制面板：步进/播放/速度滑块（复古按钮UI）

2. **关键帧流程**  
   ```mermaid
   graph LR
   A[初始位置] --> B{是否触边？}
   B -- 是 --> C[播放翻页音效+镜面翻转动画]
   C --> D[更新方程 an-bm=x-y 显示]
   B -- 否 --> E[小球沿直线移动]
   E --> F{到达袋口？}
   F -- 是 --> G[袋口闪烁+胜利音效]
   ```

3. **交互设计**  
   - **单步调试**：按帧展示，高亮当前方程参数  
   - **自动模式**：小球AI匀速移动（速度滑块控制）  
   - **奇偶性提示**：解 \( a,b \) 显示为二进制，末位闪烁标红  

4. **游戏化元素**  
   - 每完成一次翻折+1分，成功入袋按步数评星（★~★★★）  
   - 背景音乐：FC风格8bit循环BGM  
   - 音效设计：  
     * 翻折：书页翻动声  
     * 入袋：超级马里奥金币音  

---

## 6. 拓展练习与相似问题思考

**通用技巧迁移**：  
翻折建模与扩展欧几里得适用于：  
1. 光线反射路径问题  
2. 网格图最短路径搜索  
3. 周期性运动轨迹分析  

**洛谷练习推荐**：  
1. **P1516 青蛙的约会**  
   → 同类方程 \( ax+by=c \) 求解，巩固扩展欧几里得  
2. **P1082 同余方程**  
   → 基础数论训练，理解模运算本质  
3. **P1292 倒酒问题**  
   → 不定方程应用，强化边界思维  

---

## 7. 学习心得与经验分享

> **经验摘录**：  
> _“调试时发现忽略速度0的特判，导致90%测试点失败。建议先画状态转移图再编码。”_  
> **Kay点评**：边界条件永远是第一陷阱！物理问题需先枚举所有初始状态（如速度分量零/负），再推进核心算法。

---

**结语**  
通过翻折技巧将物理问题转化为数学方程，再借扩展欧几里得求解——这是计算思维的典范。试着用本指南的可视化工具模拟不同参数，你会更直观理解奇偶性与袋口映射的奥秘。下次遇到类似问题，记得先问：**能否翻折？**

---
处理用时：210.83秒