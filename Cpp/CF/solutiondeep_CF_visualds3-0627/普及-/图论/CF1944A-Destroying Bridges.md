# 题目信息

# Destroying Bridges

## 题目描述

There are $ n $ islands, numbered $ 1, 2, \ldots, n $ . Initially, every pair of islands is connected by a bridge. Hence, there are a total of $ \frac{n (n - 1)}{2} $ bridges.

Everule lives on island $ 1 $ and enjoys visiting the other islands using bridges. Dominater has the power to destroy at most $ k $ bridges to minimize the number of islands that Everule can reach using (possibly multiple) bridges.

Find the minimum number of islands (including island $ 1 $ ) that Everule can visit if Dominater destroys bridges optimally.

## 说明/提示

In the first test case, since no bridges can be destroyed, all the islands will be reachable.

In the second test case, you can destroy the bridge between islands $ 1 $ and $ 2 $ . Everule will not be able to visit island $ 2 $ but can still visit island $ 1 $ . Therefore, the total number of islands that Everule can visit is $ 1 $ .

In the third test case, Everule always has a way of reaching all islands despite what Dominater does. For example, if Dominater destroyed the bridge between islands $ 1 $ and $ 2 $ , Everule can still visit island $ 2 $ by traveling by $ 1 \to 3 \to 2 $ as the bridges between $ 1 $ and $ 3 $ , and between $ 3 $ and $ 2 $ are not destroyed.

In the fourth test case, you can destroy all bridges since $ k = \frac{n \cdot (n - 1)}{2} $ . Everule will be only able to visit $ 1 $ island (island $ 1 $ ).

## 样例 #1

### 输入

```
6
2 0
2 1
4 1
5 10
5 3
4 4```

### 输出

```
2
1
4
1
5
1```

# AI分析结果



## 算法分类
无算法分类

---

## 综合分析与结论

### 核心思路
本题核心在于数学观察：完全图中，若想将 1 号节点完全孤立，必须摧毁其所有 `n-1` 条直接连接的桥。当 `k ≥ n-1` 时，可以达成此目标，答案为 1；否则，由于完全图的冗余连接特性，所有节点仍能通过其他路径连通，答案为 `n`。

### 难点与解决
- **关键观察**：完全图的强连通性决定了只要 1 号节点保留至少一个连接，所有节点仍可达。
- **核心判断条件**：`k` 是否足够切断所有与 1 号节点直接相连的桥。

---

## 题解清单（≥4星）

### 1. zcr0202（5星）
**亮点**：代码极度简洁，直接命中核心判断条件，无冗余逻辑。  
**代码片段**：
```cpp
if(k >= n - 1) cout << "1\n";
else cout << n << '\n';
```

### 2. Guizy（5星）
**亮点**：给出数学证明，明确说明剩余桥数 `n-k` 的正向作用。  
**关键结论**：  
> 当 `k < n-1` 时，每个岛至少有 `n-k` 座桥通向其他岛，答案必为 `n`。

### 3. Hacker_Cracker（5星）
**亮点**：强调图的强连通性，通过分类讨论清晰呈现逻辑。  
**示意图**：  
![](https://cdn.luogu.com.cn/upload/image_hosting/hhjbwix8.png)

---

## 最优思路提炼
**关键技巧**：利用完全图的冗余性，仅需判断能否切断所有直接连接。  
**思维模式**：极值思维，最优策略为集中破坏目标节点的所有直接连接。

---

## 同类型题推荐
- **CF 1005E1**：完全图的连通性分析  
- **P5089**：构造性贪心与极值判断  
- **ABC 327E**：数学推导与条件分界

---

## 可视化设计（复古像素风格）

### 核心逻辑演示
1. **Canvas 初始化**：绘制 `n` 个像素方块代表岛屿，1 号岛为红色，其余为蓝色。
2. **桥的绘制**：白色线段表示初始桥，被摧毁时变为黑色。
3. **关键步骤**：  
   - 当 `k ≥ n-1`：逐帧将 1 号岛的所有桥染黑，最终仅剩红色方块。  
   - 当 `k < n-1`：随机摧毁 `k` 条桥（非 1 号连接），保留至少一条白色桥，所有方块保持连通。

### 交互功能
- **步进控制**：允许调节 `n` 和 `k`，单步执行桥的摧毁过程。  
- **音效触发**：  
  - 桥摧毁时播放 8-bit 爆炸音效（短促 "boom"）。  
  - 最终结果时，成功隔离 1 号岛播放低沉音，否则欢快音。

### 像素风格参数
- **调色板**：16 色，红（#FF0000）、蓝（#0000FF）、白（#FFFFFF）、黑（#000000）。  
- **动画帧率**：10 FPS，模拟复古卡带效果。

---

## 核心代码实现
```cpp
#include <iostream>
using namespace std;

int main() {
    int T, n, k;
    cin >> T;
    while (T--) {
        cin >> n >> k;
        cout << (k >= n-1 ? 1 : n) << endl;
    }
    return 0;
}
```

---

## 个人心得
**顿悟点**：完全图的强连通性使得任何部分破坏无法阻止间接路径，除非切断所有直接连接。  
**调试教训**：需验证边界条件（如 `k = 0` 或 `k = n(n-1)/2`）的正确性。

---
处理用时：108.00秒