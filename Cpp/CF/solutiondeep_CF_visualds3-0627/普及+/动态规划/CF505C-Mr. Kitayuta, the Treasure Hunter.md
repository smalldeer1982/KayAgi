# 题目信息

# Mr. Kitayuta, the Treasure Hunter

## 题目描述

The Shuseki Islands are an archipelago of $ 30001 $ small islands in the Yutampo Sea. The islands are evenly spaced along a line, numbered from $ 0 $ to $ 30000 $ from the west to the east. These islands are known to contain many treasures. There are $ n $ gems in the Shuseki Islands in total, and the $ i $ -th gem is located on island $ p_{i} $ .

Mr. Kitayuta has just arrived at island $ 0 $ . With his great jumping ability, he will repeatedly perform jumps between islands to the east according to the following process:

- First, he will jump from island $ 0 $ to island $ d $ .
- After that, he will continue jumping according to the following rule. Let $ l $ be the length of the previous jump, that is, if his previous jump was from island $ prev $ to island $ cur $ , let $ l=cur-prev $ . He will perform a jump of length $ l-1 $ , $ l $ or $ l+1 $ to the east. That is, he will jump to island $ (cur+l-1) $ , $ (cur+l) $ or $ (cur+l+1) $ (if they exist). The length of a jump must be positive, that is, he cannot perform a jump of length $ 0 $ when $ l=1 $ . If there is no valid destination, he will stop jumping.

Mr. Kitayuta will collect the gems on the islands visited during the process. Find the maximum number of gems that he can collect.

## 说明/提示

In the first sample, the optimal route is 0 $ → $ 10 (+1 gem) $ → $ 19 $ → $ 27 (+2 gems) $ →...&#x1; $

In the second sample, the optimal route is 0 $ → $ 8 $ → $ 15 $ → $ 21 $ → $ 28 (+1 gem) $ → $ 36 (+1 gem) $ → $ 45 (+1 gem) $ → $ 55 (+1 gem) $ → $ 66 (+1 gem) $ → $ 78 (+1 gem) $ →... $

In the third sample, the optimal route is 0 $ → $ 7 $ → $ 13 $ → $ 18 (+1 gem) $ → $ 24 (+2 gems) $ → $ 30 (+1 gem) $ →... $

## 样例 #1

### 输入

```
4 10
10
21
27
27
```

### 输出

```
3
```

## 样例 #2

### 输入

```
8 8
9
19
28
36
45
55
66
78
```

### 输出

```
6
```

## 样例 #3

### 输入

```
13 7
8
8
9
16
17
17
18
21
23
24
24
26
30
```

### 输出

```
4
```

# AI分析结果



---

## 0. 题目翻译

# Mr. Kitayuta 的寻宝之旅

## 题目描述

寿世群岛是尤坦波海上的一个由 30001 个小岛组成的群岛。这些岛屿沿直线均匀分布，从西到东编号为 0 到 30000。这些岛屿以蕴藏众多宝藏闻名，总共有 n 颗宝石，第 i 颗宝石位于 p_i 号岛屿。

Mr. Kitayuta 刚刚抵达 0 号岛屿。凭借其卓越的跳跃能力，他将按照以下规则不断向东跳跃：

- 第一步从 0 号岛屿跳跃到 d 号岛屿。
- 后续跳跃遵循以下规则：设前一次跳跃长度为 l（即若前一次从 prev 跳到 cur，则 l = cur - prev）。下一步跳跃长度可以是 l-1、l 或 l+1，且必须保持正数。若无法跳跃则停止跳跃。

求 Mr. Kitayuta 在跳跃过程中能收集到的最大宝石数量。

## 样例 #1

### 输入
```
4 10
10
21
27
27
```
### 输出
```
3
```

---

## 1. 算法分类  
**线性DP**

---

## 2. 题解分析与结论

### 核心思路
所有题解均采用动态规划，核心在于状态设计：

1. **状态压缩关键**：  
   直接存储位置和跳跃步数（`dp[位置][步长]`）会导致 `30000*30000` 的状态爆炸。通过分析跳跃步数的变化量（每次最多±1），推导出跳跃步数变化次数上限约300次，从而将状态优化为 `dp[位置][变化量]`。

2. **状态转移方程**：  
   ```
   dp[i][delta] = max(
       dp[i - step][delta - 1],
       dp[i - step][delta],
       dp[i - step][delta + 1]
   ) + gems[i]
   ```
   其中 `step = d + delta`，`delta` 表示初始步长 `d` 的变化量。

3. **实现技巧**：  
   - 使用偏移量（如+300）处理负数下标  
   - 预处理宝石分布到数组  
   - 滚动数组优化空间（部分题解）

### 可视化设计要点

#### 动态规划矩阵动画
- **8位像素风格**：  
  - 用16色调色板绘制30000x600的DP矩阵，每个格子表示 `dp[i][delta]`。  
  - 当前处理位置用绿色闪烁边框标记，前驱状态用黄色高亮。  
  - 宝石收集数用颜色渐变表示（深红→亮红）。  

- **音效系统**：  
  - 状态更新时播放短促的「嘀」声  
  - 发现新最大值时播放金币音效  
  - 背景播放8位风格循环音乐  

- **AI自动演示**：  
  自动从 `d` 开始向右扫描，优先选择变化量绝对值较小的状态进行转移，模拟人类解题的贪心策略。

---

## 3. 高分题解推荐 (≥4星)

### 题解1：zythonc (★★★★☆)
**亮点**：  
- 最早提出变化量压缩思路  
- 代码简洁，使用 `tm()` 函数优化三元比较  
**不足**：变量命名可读性不足

### 题解2：A_grasser (★★★★☆)
**亮点**：  
- 完整的状态转移推导过程  
- 代码添加详细注释  
**不足**：未处理边界情况的注释

### 题解3：__Hacheylight__ (★★★★★)
**亮点**：  
- 提供递推与记忆化两种实现  
- 数学证明变化量范围  
- 包含错误处理逻辑 `ok()` 函数  

---

## 4. 核心代码实现

### 状态转移核心片段
```cpp
// 以A_grasser题解为例
for(int i=d+1; i<=max_island; i++){
    for(int delta=-300; delta<=300; delta++){
        int step = d + delta;
        if(step <=0 || i-step <0) continue;
        
        dp[i][delta+300] = max({
            dp[i-step][delta+299],  // delta-1
            dp[i-step][delta+300],  // delta
            dp[i-step][delta+301]   // delta+1
        }) + gems[i];
    }
}
```

### 完整代码（A_grasser版）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,w[30007],f[30007][740],ans;
int main(){
    cin>>n>>d;
    int x,max_p=0;
    for(int i=1;i<=n;i++) scanf("%d",&x), w[x]++, max_p=max(max_p,x);
    memset(f,-0x3f,sizeof(f));
    f[d][370]=w[0]+w[d];
    ans=f[d][370];
    for(int i=d+1;i<=max_p;i++){
        for(int j=-320;j<=320;j++){
            int step=d+j;
            if(step>0 && step<=i)
                f[i][370+j]=max({f[i-step][370+j],f[i-step][370+j-1],f[i-step][370+j+1]})+w[i];
            ans=max(ans,f[i][370+j]);
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 5. 相似题目推荐
1. **P1091 合唱队形**（线性DP+状态设计）  
2. **P2858 [USACO06FEB]Treats for the Cows**（区间DP）  
3. **P1541 乌龟棋**（多维状态DP）

---

## 6. 可视化实现要点（复古像素版）

### Canvas初始化
```javascript
const GRID_SIZE = 8; // 8x8像素块
const DP_COLS = 600, DP_ROWS = 30000/50; // 压缩行数
const palette = ["#000","#f00","#0f0","#00f","#ff0","#f0f"];

function drawDP() {
  ctx.fillStyle = "#000";
  ctx.fillRect(0,0,canvas.width,canvas.height);
  
  // 绘制DP网格
  for(let i=0; i<DP_ROWS; i++) {
    for(let j=0; j<DP_COLS; j++) {
      let val = dp[i][j];
      ctx.fillStyle = val>0 ? palette[1+(val%5)] : palette[0];
      ctx.fillRect(j*GRID_SIZE, i*GRID_SIZE, GRID_SIZE-1, GRID_SIZE-1);
    }
  }
}
```

### 音效触发逻辑
```javascript
function playSound(type) {
  const ctx = new AudioContext();
  const osc = ctx.createOscillator();
  osc.type = "square";
  osc.frequency.value = type==='coin' ? 880 : 440;
  osc.connect(ctx.destination);
  osc.start(); osc.stop(ctx.currentTime + 0.1);
}
```

---

## 7. 关键优化思想
**变化量压缩**：通过数学推导证明跳跃步数的变化量绝对值不会超过300，将状态维度从 `O(N^2)` 压缩到 `O(N√N)`，这是此类跳跃问题的通用优化思路。

---
处理用时：106.42秒