# 题目信息

# Woodcutters

## 题目描述

Little Susie listens to fairy tales before bed every day. Today's fairy tale was about wood cutters and the little girl immediately started imagining the choppers cutting wood. She imagined the situation that is described below.

There are $ n $ trees located along the road at points with coordinates $ x_{1},x_{2},...,x_{n} $ . Each tree has its height $ h_{i} $ . Woodcutters can cut down a tree and fell it to the left or to the right. After that it occupies one of the segments $ [x_{i}-h_{i},x_{i}] $ or $ [x_{i};x_{i}+h_{i}] $ . The tree that is not cut down occupies a single point with coordinate $ x_{i} $ . Woodcutters can fell a tree if the segment to be occupied by the fallen tree doesn't contain any occupied point. The woodcutters want to process as many trees as possible, so Susie wonders, what is the maximum number of trees to fell.

## 说明/提示

In the first sample you can fell the trees like that:

- fell the $ 1 $ -st tree to the left — now it occupies segment $ [-1;1] $
- fell the $ 2 $ -nd tree to the right — now it occupies segment $ [2;3] $
- leave the $ 3 $ -rd tree — it occupies point $ 5 $
- leave the $ 4 $ -th tree — it occupies point $ 10 $
- fell the $ 5 $ -th tree to the right — now it occupies segment $ [19;20] $

In the second sample you can also fell $ 4 $ -th tree to the right, after that it will occupy segment $ [10;19] $ .

## 样例 #1

### 输入

```
5
1 2
2 1
5 10
10 9
19 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 2
2 1
5 10
10 9
20 1
```

### 输出

```
4
```

# AI分析结果



# 题目翻译

## 题目描述

小苏西每天睡前都会听童话故事。今天的童话故事是关于伐木工人的，小女孩立刻开始想象伐木工人砍树的情景。她想象了下面描述的场景。

沿路有 $n$ 棵树，分别位于坐标 $x_{1},x_{2},...,x_{n}$ 的点上。每棵树的高度为 $h_{i}$。伐木工人可以砍倒一棵树并让它向左或向右倒下。砍倒后，树会占据区间 $[x_{i}-h_{i},x_{i}]$ 或 $[x_{i},x_{i}+h_{i}]$。未被砍倒的树只占据坐标点 $x_{i}$。只有当被砍倒的树占据的区间不包含任何已被占据的点时，才能进行砍伐。伐木工人希望尽可能多地处理树木，因此苏西想知道最多能砍倒多少棵树。

## 说明/提示

第一个样例的砍伐方式如下：
- 第 1 棵树向左倒，占据区间 $[-1;1]$
- 第 2 棵树向右倒，占据区间 $[2;3]$
- 第 3 棵树保留，占据点 $5$
- 第 4 棵树保留，占据点 $10$
- 第 5 棵树向右倒，占据区间 $[19;20]$

第二个样例中还可以将第 4 棵树向右倒，占据区间 $[10;19]$。

## 样例 #1

### 输入
```
5
1 2
2 1
5 10
10 9
19 1
```

### 输出
```
3
```

## 样例 #2

### 输入
```
5
1 2
2 1
5 10
10 9
20 1
```

### 输出
```
4
```

---

# 算法分类
线性DP

---

# 综合分析与结论

## 核心思路与难点
题目需要选择最大不重叠的砍树方式，两种主流解法：
1. **贪心策略**：优先向左倒（不影响后续选择），无法左倒则向右倒。通过局部最优决策（优先靠左占用更小空间）保证全局最优。
2. **动态规划**：定义 `f[i][0/1/2]` 表示第 i 棵树不倒/左倒/右倒时的最大砍伐数。状态转移需考虑与前驱树的间隔约束。

## 关键状态转移方程
动态规划解法核心转移逻辑：
```cpp
f[i][0] = max(f[i-1][0], f[i-1][1], f[i-1][2])  // 当前树不砍
f[i][1] = max(
    f[i-1][0] + 1,  // 前一树未砍且当前可左倒
    f[i-1][1] + 1   // 前一树左倒且间隔足够
)
if (x[i] - h[i] > x[i-1] + h[i-1])  // 前一树右倒且间隔足够
    f[i][1] = max(f[i][1], f[i-1][2] + 1)
f[i][2] = max(f[i-1][0], f[i-1][1]) + 1  // 当前树右倒
```

## 可视化设计
**动态规划过程动画方案**：
1. **网格绘制**：用 Canvas 绘制二维网格，行表示树编号，列表示状态（0/1/2）。
2. **颜色标记**：
   - 绿色：当前处理的状态单元
   - 黄色箭头：状态转移来源
3. **步进控制**：用户可单步执行观察每个状态的更新过程，高亮转移路径。
4. **音效触发**：
   - 成功转移时播放清脆音效（8-bit 风格）
   - 状态冲突时播放低沉提示音

---

# 题解清单 (≥4星)

1. **作者：yzx72424（4星）**
   - **亮点**：代码简洁高效，贪心策略实现直接
   - **核心逻辑**：优先左倒，否则右倒，首尾特判
   ```cpp
   for(int i=2;i<=a-1;i++){
       if(xx[i]-h[i]>xx[i-1]) t++;
       else if(xx[i]+h[i]<xx[i+1]){
           t++; xx[i]+=h[i];
       }
   }
   ```

2. **作者：傅思维666（4.5星）**
   - **亮点**：完整 DP 状态定义，详细转移条件注释
   - **代码片段**：
   ```cpp
   f[i][0] = max(f[i-1][0], f[i-1][1]);
   if(x[i] - x[i-1] > h[i]) 
       f[i][1] = max(f[i-1][1]+1, f[i-1][0]+1);
   ```

3. **作者：李若谷（4星）**
   - **亮点**：贪心策略正确性证明详细，代码包含预处理优化
   - **心得**：强调首尾处理对后续选择的影响

---

# 核心代码实现（动态规划）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,f[maxn][3];
struct Tree { int x, h; } t[maxn];

int main() {
    cin >> n;
    for(int i=1; i<=n; i++) 
        cin >> t[i].x >> t[i].h;
    
    f[1][0] = 1;  // 初始状态
    for(int i=2; i<=n; i++) {
        // 不砍的情况取前驱最大值
        f[i][0] = max({f[i-1][0], f[i-1][1], f[i-1][2]});
        
        // 左倒转移
        if(t[i].x - t[i].h > t[i-1].x)
            f[i][1] = max(f[i-1][0], f[i-1][1]) + 1;
        
        // 右倒转移
        if(t[i].x + t[i].h < t[i+1].x || i == n) 
            f[i][2] = max({f[i-1][0], f[i-1][1], f[i-1][2]}) + 1;
    }
    cout << max({f[n][0], f[n][1], f[n][2]});
    return 0;
}
```

---

# 同类型题目推荐
1. P1233 木棍加工（贪心+DP）
2. P2887 [USACO07NOV]Sunscreen G（区间调度）
3. P2258 子矩阵（线性DP优化）

---

# 可视化实现要点
1. **像素风格**：使用16色调色板，树用棕色方块表示，倒下区域用绿色/红色渐变。
2. **自动演示**：通过 setInterval 控制状态转移动画，每步延迟 500ms。
3. **音效触发**：使用 Web Audio API 播放 8-bit 音效：
   ```javascript
   function playSound(freq) {
       let osc = audioCtx.createOscillator();
       osc.frequency.value = freq;
       osc.connect(audioCtx.destination);
       osc.start(); osc.stop(audioCtx.currentTime + 0.1);
   }
   ```

---

**个人心得**：  
- **特判陷阱**：当 n=1 时必须单独处理（多位作者因此 WA）
- **贪心证明**：局部最优性可通过反证法严谨证明，避免直觉错误
- **坐标更新**：贪心法中向右倒后需修改坐标，否则影响后续判断

---
处理用时：92.87秒