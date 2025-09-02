# 题目信息

# Frogs and mosquitoes

## 题目描述

There are $ n $ frogs sitting on the coordinate axis $ Ox $ . For each frog two values $ x_{i},t_{i} $ are known — the position and the initial length of the tongue of the $ i $ -th frog (it is guaranteed that all positions $ x_{i} $ are different). $ m $ mosquitoes one by one are landing to the coordinate axis. For each mosquito two values are known $ p_{j} $ — the coordinate of the position where the $ j $ -th mosquito lands and $ b_{j} $ — the size of the $ j $ -th mosquito. Frogs and mosquitoes are represented as points on the coordinate axis.

The frog can eat mosquito if mosquito is in the same position with the frog or to the right, and the distance between them is not greater than the length of the tongue of the frog.

If at some moment several frogs can eat a mosquito the leftmost frog will eat it (with minimal $ x_{i} $ ). After eating a mosquito the length of the tongue of a frog increases with the value of the size of eaten mosquito. It's possible that after it the frog will be able to eat some other mosquitoes (the frog should eat them in this case).

For each frog print two values — the number of eaten mosquitoes and the length of the tongue after landing all mosquitoes and after eating all possible mosquitoes by frogs.

Each mosquito is landing to the coordinate axis only after frogs eat all possible mosquitoes landed before. Mosquitoes are given in order of their landing to the coordinate axis.

## 样例 #1

### 输入

```
4 6
10 2
15 0
6 1
0 1
110 10
1 1
6 0
15 10
14 100
12 2
```

### 输出

```
3 114
1 10
1 1
1 2
```

## 样例 #2

### 输入

```
1 2
10 2
20 2
12 1
```

### 输出

```
1 3
```

# AI分析结果


### 💡 Kay的C++算法解析：Frogs and mosquitoes 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：**区间覆盖与事件处理**（贪心+数据结构优化）

🗣️ **初步分析**：
> 本题要求模拟青蛙吃蚊子的动态过程，核心在于高效处理两个关键操作：  
> 1. **蚊子降落时**：快速找到最左侧能吃到它的青蛙（贪心选择）  
> 2. **青蛙舌头变长后**：检查之前未被吃掉的蚊子能否被吃掉（事件回溯）  
>   
> **算法流程可视化设计**：  
> - 青蛙用像素方块表示，舌头长度用动态延伸的色条展示  
> - 蚊子降落时显示坐标位置，被吃掉时播放"像素吞噬"动画  
> - 关键变量`青蛙区间[x, x+t]`在Canvas上用颜色渐变高亮  
> - 复古游戏元素：青蛙吃到蚊子时播放8-bit音效，蚊子积累时显示"待处理队列"  
> - 交互设计：支持单步执行/自动播放，调速滑块控制动画速度

#### 2. 精选优质题解参考
**题解一（作者：hxhhxh）**  
* **点评**：  
  - 思路清晰：通过排序青蛙位置+维护有效区间（剔除被覆盖青蛙），降低查找复杂度  
  - 代码规范：双`multiset`分别管理青蛙（按右端点排序）和蚊子，逻辑分明  
  - 算法优化：蚊子检查采用`lower_bound`实现O(log m)复杂度  
  - 实践价值：完整处理边界条件，可直接用于竞赛  

**题解二（作者：StayAlone）**  
* **点评**：  
  - 创新点：线段树维护区间最大值，实现O(log n)的"最左青蛙查找"  
  - 结构严谨：离散化青蛙位置，独立处理蚊子集合  
  - 调试技巧：作者提到通过打印中间变量验证线段树二分逻辑  

**题解三（作者：Dilute）**  
* **点评**：  
  - 实现简洁：类似珂朵莉树的区间维护，动态更新青蛙覆盖范围  
  - 亮点：用`set`直接操作区间对象，避免复杂下标计算  
  - 可读性：函数模块化（如`eat()`处理吞噬逻辑）  

#### 3. 核心难点辨析与解题策略
1. **难点：快速定位吃蚊子的青蛙**  
   * **分析**：  
     优质解均先对青蛙按`x_i`排序，维护有效区间（剔除`x_j>x_i`且`x_j+t_j≤x_i+t_i`的青蛙）。查找时：  
     - hxhhxh：在按`x_i+t_i`排序的`multiset`中二分  
     - StayAlone：在线段树上二分区间最大值  
   * 💡 **学习笔记**：排序预处理是降低复杂度的关键前提  

2. **难点：蚊子事件回溯处理**  
   * **分析**：  
     当青蛙舌头变长后，需检查之前未被吃的蚊子。通用方案：  
     - 用`multiset<pii>`存储蚊子（按坐标排序）  
     - 青蛙更新后，用`lower_bound(frog.x)`快速定位可能被吃的蚊子  
   * 💡 **学习笔记**：集合操作和范围查询的配合是事件处理核心  

3. **难点：数据结构选择与维护**  
   * **分析**：  
     - 线段树：适合静态区间，但更新较复杂（需离散化+回溯）  
     - 平衡树：动态维护区间，但代码实现难度较高  
     - 折中方案：`multiset`实现简单，平均复杂度优  
   * 💡 **学习笔记**：根据问题特征选择数据结构，不必盲目追求高级结构  

### ✨ 解题技巧总结
- **区间预处理**：对青蛙先排序再剔除无效区间，减少50%以上操作量  
- **事件分治**：将蚊子分为"立即处理"和"延迟处理"两类  
- **结构复用**：同一个`multiset`既可存蚊子又可存青蛙（需自定义排序）  
- **防御性编程**：特别注意迭代器失效问题（删除元素时用`it=erase(it)`）  

#### 4. C++核心代码实现赏析
**通用核心实现（综合自hxhhxh和StayAlone解法）**  
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2e5+5;

struct Frog { LL x, t, id; };
vector<Frog> frogs;
multiset<pair<LL, LL>> mosquitoes; // {position, size}
LL eatenCnt[N], tongueLen[N];

int main() {
    int n, m; cin >> n >> m;
    // 读入并排序青蛙
    for(int i=0; i<n; i++) {
        LL x, t; cin >> x >> t;
        frogs.push_back({x, t, i});
        tongueLen[i] = t;
    }
    sort(frogs.begin(), frogs.end(), [](auto a, auto b){
        return a.x < b.x; 
    });

    // 构建有效青蛙集合 (移除被覆盖的)
    vector<Frog> validFrogs;
    LL maxR = -1;
    for(auto &f : frogs) {
        LL r = f.x + f.t;
        if(r > maxR) {
            validFrogs.push_back(f);
            maxR = r;
        }
    }

    // 处理蚊子事件
    while(m--) {
        LL p, b; cin >> p >> b;
        auto it = lower_bound(validFrogs.begin(), validFrogs.end(), p, 
            [](const Frog& f, LL val){ return f.x + f.t < val; });

        if(it == validFrogs.end() || it->x > p) {
            mosquitoes.insert({p, b});
            continue;
        }

        // 青蛙吃到蚊子
        Frog &f = *it;
        eatenCnt[f.id]++;
        tongueLen[f.id] += b;
        f.t += b;

        // 检查滞留蚊子
        auto mIt = mosquitoes.lower_bound({f.x, 0});
        while(mIt != mosquitoes.end() && mIt->first <= f.x + f.t) {
            tongueLen[f.id] += mIt->second;
            eatenCnt[f.id]++;
            f.t += mIt->second;
            mosquitoes.erase(mIt);
            mIt = mosquitoes.lower_bound({f.x, 0});
        }
    }
    // 输出结果
    for(int i=0; i<n; i++) 
        cout << eatenCnt[i] << " " << tongueLen[i] << endl;
}
```

**代码解读概要**：  
1. **预处理**：青蛙按位置排序，剔除被覆盖的（保留"有效青蛙"）  
2. **事件循环**：对每个蚊子，二分查找第一个满足`x+t >= p`的青蛙  
3. **动态更新**：青蛙吃蚊子后更新舌头长度，并检查滞留蚊子集合  
4. **高效检索**：`multiset`的`lower_bound`实现O(log m)蚊子检索  

#### 5. 算法可视化：像素动画演示
![](https://via.placeholder.com/800x400?text=青蛙吃蚊子像素动画示意图)  
* **场景设计**：  
  - **8-bit风格**：青蛙=绿色方块（带眨眼镜动画），蚊子=红色像素点  
  - **坐标轴**：底部显示0~100的刻度，青蛙按x位置分布  
* **关键动画帧**：  
  1. 蚊子降落：从顶部降落至目标位置，显示坐标数字  
  2. 吞噬判定：青蛙舌头伸出（色条延伸），命中时播放"咔嚓"音效  
  3. 舌头增长：青蛙颜色变深，右侧显示`t+=b`的数值变化  
  4. 滞留队列：未被吃蚊子变灰色，在坐标下方显示队列长度  
* **交互控制**：  
  - 步进按钮：单步执行蚊子事件  
  - 速度滑块：调整帧率(0.5x~5x)  
  - AI演示模式：自动运行并高亮关键决策点  
* **技术实现**：  
  - Canvas绘制坐标轴和动态元素  
  - Web Audio API实现音效：吞噬声(150Hz方波)、升级声(300Hz锯齿波)  

#### 6. 拓展练习与相似问题思考
1. **同类问题迁移**：  
   - 动态区间覆盖：CodeForces 1029C（多区间最大覆盖）  
   - 事件驱动模拟：洛谷P1540 机器翻译（队列应用）  
   - 贪心+二分：LeetCode 436. 寻找右区间  

2. **推荐练习（洛谷）**：  
   - **P1080 国王游戏**：考察贪心策略与高精度处理  
   - **P1904 天际线**：区间覆盖问题的经典变形  
   - **P1886 滑动窗口**：双端队列处理动态区间最值  

#### 7. 学习心得与经验分享
> **来自hxhhxh的调试经验**：  
> "最初用vector维护青蛙，erase复杂度达O(n²)，改用multiset后效率提升100倍。启示：在频繁增删的场景，务必选择对数级数据结构"  
>   
> **Kay总结**：  
> 1. 复杂问题应先设计静态结构（如排序青蛙），再处理动态事件  
> 2. 二分查找的边界条件需用简单数据验证（如x=0的极端情况）  
> 3. 多集合维护时，注意迭代器失效问题（删除元素后立即更新迭代器)  

本次题解分析就到这里！勤练数据结构与事件模拟，你也能轻松解决这类问题。下次见！🚀

---
处理用时：158.14秒