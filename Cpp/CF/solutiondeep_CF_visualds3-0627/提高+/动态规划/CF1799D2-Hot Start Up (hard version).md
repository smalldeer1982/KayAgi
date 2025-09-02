# 题目信息

# Hot Start Up (hard version)

## 题目描述

This is a hard version of the problem. The constraints of $ t $ , $ n $ , $ k $ are the only difference between versions.

You have a device with two CPUs. You also have $ k $ programs, numbered $ 1 $ through $ k $ , that you can run on the CPUs.

The $ i $ -th program ( $ 1 \le i \le k $ ) takes $ cold_i $ seconds to run on some CPU. However, if the last program we ran on this CPU was also program $ i $ , it only takes $ hot_i $ seconds ( $ hot_i \le cold_i $ ). Note that this only applies if we run program $ i $ multiple times consecutively — if we run program $ i $ , then some different program, then program $ i $ again, it will take $ cold_i $ seconds the second time.

You are given a sequence $ a_1, a_2, \ldots, a_n $ of length $ n $ , consisting of integers from $ 1 $ to $ k $ . You need to use your device to run programs $ a_1, a_2, \ldots, a_n $ in sequence. For all $ 2 \le i \le n $ , you cannot start running program $ a_i $ until program $ a_{i - 1} $ has completed.

Find the minimum amount of time needed to run all programs $ a_1, a_2, \ldots, a_n $ in sequence.

## 说明/提示

In the first test case, we can do the following:

- Run program $ a_1 = 1 $ on CPU $ 1 $ . It takes $ cold_1 = 3 $ seconds to run.
- Run program $ a_2 = 2 $ on CPU $ 2 $ . It takes $ cold_2 = 2 $ seconds to run.
- Run program $ a_3 = 2 $ on CPU $ 2 $ . The last program run on this CPU was also program $ 2 $ , so it takes $ hot_2 = 1 $ second to run.

In total, we need $ 3 + 2 + 1 = 6 $ seconds to run them all. We can show this is optimal.

In the second test case, we can use do the following:

- Run program $ a_1 = 1 $ on CPU $ 1 $ . It takes $ cold_1 = 5 $ seconds to run.
- Run program $ a_2 = 2 $ on CPU $ 2 $ . It takes $ cold_2 = 3 $ seconds to run.
- Run program $ a_3 = 1 $ on CPU $ 1 $ . The last program run on this CPU was also program $ 1 $ , so it takes $ hot_1 = 2 $ seconds to run.
- Run program $ a_4 = 2 $ on CPU $ 2 $ . The last program run on this CPU was also program $ 2 $ , so it takes $ hot_2 = 1 $ second to run.

In total, we need $ 5 + 3 + 2 + 1 = 11 $ seconds. We can show this is optimal.

## 样例 #1

### 输入

```
9
3 2
1 2 2
3 2
2 1
4 2
1 2 1 2
5 3
2 1
4 3
1 2 3 1
100 100 100
1 1 1
5 2
2 1 2 1 1
65 45
54 7
5 3
1 3 2 1 2
2 2 2
1 1 1
5 1
1 1 1 1 1
1000000000
999999999
5 6
1 6 1 4 1
3 6 4 1 4 5
1 1 1 1 4 1
1 3
3
4 5 6
1 2 3
8 3
3 3 3 1 2 3 2 1
10 10 8
10 10 5```

### 输出

```
6
11
301
225
8
4999999996
11
6
63```

# AI分析结果



## 题目重写
# 热启动（困难版）

## 题目描述

这是该问题的困难版本。与简单版的唯一区别在于 $t$、$n$、$k$ 的限制条件。

你有两个 CPU 和 $k$ 个编号为 $1$ 到 $k$ 的程序。第 $i$ 个程序在 CPU 上运行需要 $cold_i$ 秒，但如果该 CPU 上一次运行的是同一个程序，则只需 $hot_i$ 秒（保证 $hot_i \leq cold_i$）。注意，这种加速仅适用于连续多次运行同一程序的情况。

给定长度为 $n$ 的序列 $a_1,a_2,\ldots,a_n$，你需要按顺序运行这些程序。每个程序必须在前一个程序完成后才能开始。求运行所有程序的最小总时间。

## 样例与提示

样例展示了如何通过合理分配 CPU 获得最优解。例如第一个样例中，将连续的两个程序2分配给同一个 CPU 获得热启动加速。

---

## 唯一算法分类
线性DP

---

## 综合分析与结论
### 核心思路与难点
1. **状态设计**：  
   定义 $dp[i][j]$ 表示处理完前 $i$ 个程序，另一个 CPU 最后运行的程序类型为 $j$ 的最小耗时。由于两个 CPU 对称等价，可以压缩为一维状态 $dp[j]$ 表示当前程序运行后，另一个 CPU 的最后程序类型为 $j$。

2. **状态转移优化**：  
   - 当当前程序与前一程序相同时（$a_i = a_{i-1}$），直接累加热启动时间  
   - 当程序不同时，维护全局最小值 $minn$ 和前缀和 $s$，通过 $dp[j] = \min(minn + cold, dp[a_i] + hot)$ 快速转移

3. **复杂度优化**：  
   通过滚动变量和前缀和技巧，将时间复杂度从 $O(nk)$ 降为 $O(n)$，空间复杂度保持 $O(k)$

### 可视化设计
1. **动画方案**：  
   - 使用网格展示 DP 数组，高亮当前更新的位置（如 $dp[a_{i-1}]$）  
   - 用流动箭头表示全局最小值 $minn$ 的更新过程  
   - 动态显示前缀和 $s$ 的累加过程

2. **复古风格**：  
   - 8-bit 像素风格界面，DP 数组以 16x16 像素块呈现  
   - 每次状态转移时播放「滴」声效，找到更优解时播放「叮」声效  
   - 背景音乐采用低比特芯片音乐循环播放

3. **交互功能**：  
   - 速度调节滑块控制动画步进间隔  
   - 单步执行按钮观察每步状态变化  
   - 自动演示模式展示算法自动决策过程

---

## 题解清单（≥4星）
1. **thostever（5星）**  
   - 亮点：状态压缩到一维，通过维护全局最小值和滚动变量实现线性复杂度  
   - 代码简洁高效（仅 30 行），实践性极强

2. **2018ljw（4星）**  
   - 创新性引入费用预支思想，将问题转化为前缀和优化问题  
   - 提供数学推导过程，增强理论深度

3. **sjr3065335594（4星）**  
   - 清晰定义辅助函数 $las$ 和 $cal$，强化问题建模  
   - 完整展示从暴力 DP 到线性优化的推导链条

---

## 最优思路与代码实现
### 关键技巧提炼
```cpp
ll minn = 0, s = 0; // 维护全局最小值和累加值
for(int i=1; i<=n; i++) {
    if(a[i] == a[i-1]) {
        s += hot[a[i]]; // 直接热启动
    } else {
        s += cold[a[i]]; 
        // 状态转移方程核心
        dp[a[i-1]] = min(dp[a[i]] + hot_val, minn + cold_val) - cold_val;
        minn = min(minn, dp[a[i-1]]); // 更新全局最小值
    }
}
printf("%lld\n", minn + s);
```

### 完整代码（thostever解法）
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f3f3f3f3f;
int n,m,a[300010];
ll dp[300010],s,minn;
int cold[300010],hot[300010];

void solve() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=m;i++) scanf("%d",&cold[i]);
    for(int i=1;i<=m;i++) scanf("%d",&hot[i]);
    memset(dp,0x3f,sizeof(dp[0])*(m+1));
    dp[0]=0; minn=0; s=0;
    for(int i=1;i<=n;i++) {
        if(a[i]==a[i-1]) {
            s += hot[a[i]];
        } else {
            s += cold[a[i]];
            ll temp = min(dp[a[i]] + hot[a[i]], minn + cold[a[i]]);
            dp[a[i-1]] = temp - cold[a[i]];
            minn = min(minn, dp[a[i-1]]);
        }
    }
    printf("%lld\n",minn+s);
}

int main() {
    int T; scanf("%d",&T);
    while(T--) solve();
    return 0;
}
```

---

## 相似题目推荐
1. **P1776 宝物筛选**（多重背包单调队列优化）  
2. **P1064 金明的预算方案**（依赖背包的状态压缩）  
3. **P1541 乌龟棋**（多维线性DP优化）

---

## 个人心得摘录
> "调试时发现当连续两个相同程序时，必须立即应用热启动，这帮助我找到状态转移缺失的分支。" —— thostever  
> "将问题转化为前缀和形式后，突然意识到可以用全局变量代替二维数组，这是突破的关键时刻。" —— 2018ljw

---

## 可视化方案示意
```javascript
// Canvas绘制核心逻辑（伪代码）
class DPViz {
    constructor() {
        this.grid = new PixelGrid(16, 16); // 16x16像素网格
        this.highlightCell(x, y) { // 高亮当前更新的dp单元格
            grid.setColor(x, y, '#FF00FF'); 
        }
        this.playSound('blip'); // 状态更新音效
    }
    
    animateStep(i) {
        if(a[i] == a[i-1]) {
            this.showFloatingText(`+${hot[a[i]]}`, {x:15,y:i%16}); // 显示热启动增量
        } else {
            this.drawArrow(minnPos, currentPos); // 绘制最小值转移箭头
        }
    }
}
```

通过将复杂的 DP 状态转移转化为动态可视化过程，学习者可以直观理解全局最小值的维护机制和滚动优化的精妙之处。复古像素风格与音效反馈增强了学习过程的趣味性和记忆点。

---
处理用时：76.21秒