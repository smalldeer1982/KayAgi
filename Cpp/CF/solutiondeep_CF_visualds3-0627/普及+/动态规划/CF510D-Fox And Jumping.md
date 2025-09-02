# 题目信息

# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
```

### 输出

```
7237
```

# AI分析结果



# Fox And Jumping

## 题目描述

狐狸 Ciel 正在玩一个游戏。游戏中有一条无限长的纸带，单元格用整数（正、负、零）索引。开始时她站在单元格 0 处。

有 $n$ 张卡片，每张卡片有 2 个属性：长度 $l_{i}$ 和费用 $c_{i}$。若支付 $c_{i}$ 美元，她可以使用第 $i$ 张卡片。使用后，她可以跳跃长度 $l_{i}$，即从单元格 $x$ 跳到 $(x-l_{i})$ 或 $(x+l_{i})$。

她希望能在纸带上跳到任意单元格（可能需要经过中间单元格）。为此，她希望购买若干卡片，支付尽可能少的费用。若可能，计算最小费用。

## 说明/提示

第一个样例中，购买一张卡不够：例如购买长度为 100 的卡，无法跳到非 100 倍数的单元格。最佳方案是购买前两张卡，即可跳到任意单元格。

第二个样例中，即使购买所有卡，也无法跳到非 10 倍数的单元格，输出 -1。

---

## 唯一算法分类
**线性DP**

---

## 综合分析与结论

### 核心思路与难点
题目转化为**选择若干卡片使其长度的最大公约数为 1**的最小费用问题，基于裴蜀定理。关键难点在于处理高维状态，两种主流解法：

1. **状压DP**（ZYF_B）  
   将每个数的质因数分解为状态（最多 9 个质因数），用位压缩表示质因数集合。状态转移方程为：  
   $$f[new\_state] = \min(f[new\_state], f[old\_state] + cost)$$  
   需维护质因数交集，时间复杂度 $O(n^2 2^9)$。

2. **Map 动态规划**（Kohakuwu）  
   用 `map` 存储各 gcd 值的最小费用。遍历每个卡片时，更新所有可能的新 gcd 值：  
   $$new\_gcd = \gcd(current\_gcd, l_i)$$  
   $$map[new\_gcd] = \min(map[new\_gcd], map[current\_gcd] + c_i)$$  
   状态数由输入的因数决定，实际运行效率较高。

### 可视化设计思路
- **Canvas 网格绘制**：每个格子表示一个 gcd 值，颜色深浅表示费用高低。  
- **高亮转移**：当前处理的卡片用闪烁边框标记，新产生的 gcd 状态用绿色高亮。  
- **音效触发**：状态更新时播放「滴」声，找到 gcd=1 时播放胜利音效。  
- **8 位像素风格**：用复古调色板（如 #FF6B6B、#4ECDC4）渲染网格，背景音乐采用芯片音乐循环。

---

## 题解清单（≥4星）

### 1. ZYF_B 的状压DP（⭐⭐⭐⭐⭐）
**亮点**：  
- 质因数分解预处理，位运算高效处理状态转移。  
- 时间复杂度严格可控，适合大规模数据。

### 2. Kohakuwu 的 Map 动态规划（⭐⭐⭐⭐⭐）
**亮点**：  
- 代码简洁，仅需 30 行核心逻辑。  
- 利用 STL 自动管理状态，避免手动处理因数。

### 3. fanfansann 的 Dijkstra 最短路（⭐⭐⭐⭐）
**亮点**：  
- 将问题建模为最短路，`gcd` 为节点，费用为边权。  
- 优先队列优化，确保每次扩展最小费用路径。

---

## 最优思路与代码实现

### 核心代码（Kohakuwu 的 Map 解法）
```cpp
#include <bits/stdc++.h>
using namespace std;
map<int,int> mp;
int a[1003],b[1003];
signed main(){
    int n=read();
    for(int i=1; i<=n; i++) a[i]=read();
    for(int i=1; i<=n; i++) b[i]=read();
    for(int i=1; i<=n; i++) {
        for(auto x:mp) {
            int num=__gcd(a[i],x.first), val=x.second+b[i];
            if(!mp[num] || mp[num]>val) mp[num]=val;
        }
        if(!mp[a[i]] || mp[a[i]]>b[i]) mp[a[i]]=b[i];
    }
    printf("%d\n", mp[1] ? mp[1] : -1);
}
```

### 实现思想
1. **初始化**：遍历每个卡片，维护 `map<gcd, cost>`。  
2. **状态转移**：对每个卡片，用当前所有可能的 gcd 值生成新状态。  
3. **更新规则**：若新 gcd 费用更低则更新，否则保留原值。

---

## 同类型题与拓展
- **裴蜀定理应用**：洛谷 P4549（模板题）  
- **质因数分解+状压**：洛谷 P1072（分解质因数优化）  
- **隐式图最短路**：洛谷 P3951（小凯的疑惑）

---

## 可视化代码片段（Canvas 动画）
```javascript
// 绘制 GCD 状态网格
function drawGrid() {
    ctx.fillStyle = '#2d3436';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    Object.entries(gcdStates).forEach(([gcd, cost], index) => {
        const x = (index % 5) * 100 + 10;
        const y = Math.floor(index / 5) * 100 + 10;
        ctx.fillStyle = costColorMap(cost);
        ctx.fillRect(x, y, 80, 80);
        ctx.fillStyle = '#ffffff';
        ctx.font = '16px "Press Start 2P"';
        ctx.fillText(`GCD: ${gcd}`, x + 5, y + 20);
        ctx.fillText(`$${cost}`, x + 5, y + 50);
    });
}
```

---

## 个人心得摘录
> 「Dijkstra 方法中，初始状态设为 gcd=0 是关键，因为任何数与 0 的 gcd 是其本身。这相当于从空集合开始逐步添加卡片。」—— fanfansann  
> 「质因数分解时注意去重，否则位状态会爆炸。」—— ZYF_B

---

## 复古游戏化设计
- **像素调色板**：使用 #FF5252（红）、#4FB0C6（蓝）、#FFD93D（黄）模拟 FC 风格。  
- **音效设计**：状态更新触发 8-bit「blip」音效，胜利时播放「1UP」音效。  
- **自动演示模式**：AI 按费用升序选择卡片，每步延迟 500ms，展示最优路径生成过程。

---
处理用时：120.51秒