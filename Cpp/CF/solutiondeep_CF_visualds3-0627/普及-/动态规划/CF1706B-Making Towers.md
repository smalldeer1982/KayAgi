# 题目信息

# Making Towers

## 题目描述

You have a sequence of $ n $ colored blocks. The color of the $ i $ -th block is $ c_i $ , an integer between $ 1 $ and $ n $ .

You will place the blocks down in sequence on an infinite coordinate grid in the following way.

1. Initially, you place block $ 1 $ at $ (0, 0) $ .
2. For $ 2 \le i \le n $ , if the $ (i - 1) $ -th block is placed at position $ (x, y) $ , then the $ i $ -th block can be placed at one of positions $ (x + 1, y) $ , $ (x - 1, y) $ , $ (x, y + 1) $ (but not at position $ (x, y - 1) $ ), as long no previous block was placed at that position.

A tower is formed by $ s $ blocks such that they are placed at positions $ (x, y), (x, y + 1), \ldots, (x, y + s - 1) $ for some position $ (x, y) $ and integer $ s $ . The size of the tower is $ s $ , the number of blocks in it. A tower of color $ r $  is a tower such that all blocks in it have the color $ r $ .

For each color $ r $ from $ 1 $ to $ n $ , solve the following problem independently:

- Find the maximum size of a tower of color $ r $ that you can form by placing down the blocks according to the rules.

## 说明/提示

In the first test case, one of the possible ways to form a tower of color $ 1 $ and size $ 3 $ is:

- place block $ 1 $ at position $ (0, 0) $ ;
- place block $ 2 $ to the right of block $ 1 $ , at position $ (1, 0) $ ;
- place block $ 3 $ above block $ 2 $ , at position $ (1, 1) $ ;
- place block $ 4 $ to the left of block $ 3 $ , at position $ (0, 1) $ ;
- place block $ 5 $ to the left of block $ 4 $ , at position $ (-1, 1) $ ;
- place block $ 6 $ above block $ 5 $ , at position $ (-1, 2) $ ;
- place block $ 7 $ to the right of block $ 6 $ , at position $ (0, 2) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706B/ec98c0f164311a4ec7c2c7d82fee7c9f6eae74e7.png)The blocks at positions $ (0, 0) $ , $ (0, 1) $ , and $ (0, 2) $ all have color $ 1 $ , forming an tower of size $ 3 $ .

In the second test case, note that the following placement is not valid, since you are not allowed to place block $ 6 $ under block $ 5 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706B/39b20d638e1634a0778efb064f52a1e1cffbd150.png)It can be shown that it is impossible to form a tower of color $ 4 $ and size $ 3 $ .

## 样例 #1

### 输入

```
6
7
1 2 3 1 2 3 1
6
4 2 2 2 4 4
1
1
5
5 4 5 3 5
6
3 3 3 1 3 3
8
1 2 3 4 4 3 2 1```

### 输出

```
3 2 2 0 0 0 0 
0 3 0 2 0 0 
1 
0 0 1 1 1 
1 0 4 0 0 0 
2 2 2 2 0 0 0 0```

# AI分析结果



0. **题目翻译**  
# 搭建塔楼

## 题目描述

你有一个由 $n$ 个彩色方块组成的序列。第 $i$ 个方块的颜色为 $c_i$（整数，范围从 $1$ 到 $n$）。

你需要按照以下规则在无限坐标系中依次放置这些方块：

1. 初始时，将第 $1$ 个方块放置在 $(0, 0)$。
2. 对于 $2 \le i \le n$，若第 $i-1$ 个方块位于 $(x, y)$，则第 $i$ 个方块可放置在 $(x+1, y)$、$(x-1, y)$ 或 $(x, y+1)$（但不能是 $(x, y-1)$），且该位置未被占用。

塔楼由 $s$ 个方块组成，这些方块位于同一列 $(x, y), (x, y+1), \ldots, (x, y+s-1)$，其大小为 $s$。颜色为 $r$ 的塔楼要求所有方块颜色均为 $r$。

对每个颜色 $r$（从 $1$ 到 $n$），独立求解以下问题：
- 求按照规则放置方块时，颜色 $r$ 的塔楼可能的最大高度。

## 说明/提示

样例1中，颜色1的塔楼可通过如下方式形成高度为3的塔：
- 方块1在$(0,0)$
- 方块2在$(1,0)$
- 方块3在$(1,1)$
- 方块4在$(0,1)$
- 方块5在$(-1,1)$
- 方块6在$(-1,2)$
- 方块7在$(0,2)$

![示意图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706B/ec98c0f164311a4ec7c2c7d82fee7c9f6eae74e7.png)

---

1. **唯一算法分类**  
线性DP

---

2. **综合分析与结论**  
**核心思路**：  
发现同色方块形成塔楼的关键条件——相邻同色方块的位置索引差必须为奇数。通过维护每个颜色的最近位置奇偶性，实现动态规划求解。

**算法要点**：  
- **状态定义**：对每个颜色维护两个状态（偶索引结尾、奇索引结尾的最大高度）
- **转移方程**：当遇到颜色$c$的第$i$个方块时（索引奇偶性为$p$）：
  ``` 
  dp[c][p] = max(dp[c][p], dp[c][¬p] + 1)
  ```
- **数据结构**：使用二维数组`f[color][0/1]`记录状态

**可视化设计**：  
- **像素网格**：Canvas绘制动态网格，每个方块按出现顺序飞入对应位置
- **高亮机制**：同色方块形成塔时，列显示为闪烁金色边框
- **状态追踪**：右侧面板实时显示各颜色奇偶状态的最大高度
- **音效设计**：方块放置时播放8-bit音效，塔高更新时触发"升级"音效

---

3. **题解清单 (≥4星)**  
1. **cachejtt（4.5星）**  
   - 亮点：利用奇偶差直接计数，代码简洁高效
   - 关键代码：`if (las[c]==0 || (i-las[c])%2==1) ans[c]++`

2. **ExplodingKonjac（4星）**  
   - 亮点：双状态DP清晰展示转移过程
   - 关键代码：`f[a[i]][i&1] = max(f[a[i]][i&1], f[a[i]][!(i&1)]+1)`

3. **Jeremiahy（4星）**  
   - 亮点：完整数学证明，解释奇偶差必然性
   - 心得："间隔偶数步的绕路策略"的比喻生动

---

4. **最优代码实现**  
```cpp
// 核心代码（ExplodingKonjac解法）
#include <bits/stdc++.h>
using namespace std;
int T,n,a[100005],f[100005][2];

int main() {
    cin >> T;
    while(T--) {
        cin >> n;
        memset(f,0,sizeof(f));
        for(int i=1;i<=n;i++) {
            cin >> a[i];
            int p = i&1;
            f[a[i]][p] = max(f[a[i]][p], f[a[i]][!p]+1);
        }
        for(int i=1;i<=n;i++) 
            cout << max(f[i][0],f[i][1]) << " ";
        cout << "\n";
    }
    return 0;
}
```

---

5. **同类型题推荐**  
- P1091 合唱队形（线性DP状态设计）
- P1439 LCS（序列位置特性应用）
- P1868 饥饿的奶牛（区间选择与奇偶性）

---

6. **可视化动画脚本**  
```javascript
// 伪代码示例（Canvas绘制核心逻辑）
class TowerAnimator {
  constructor() {
    this.colors = [/* 颜色序列 */];
    this.dp = [[0,0],...]; // 状态数组
    this.highlightCol = -1; // 当前高亮颜色
  }

  drawFrame() {
    ctx.clearRect(0,0,W,H);
    // 绘制网格线
    drawGrid();
    
    // 绘制当前方块下落动画
    const block = this.blocks[frame];
    block.y += vy; 
    drawBlock(block);

    // 更新DP状态面板
    if(block.y > targetY) {
      const c = block.color;
      const p = block.idx % 2;
      this.dp[c][p] = Math.max(this.dp[c][p], this.dp[c][1-p]+1);
      playSound('blip.mp3');
      this.highlightCol = c; // 触发高亮
    }
  }
}
```

---

7. **复古游戏化要素**  
- **像素风格**：16色限定调色板，使用NES经典蓝绿色系
- **音效设计**：
  - 方块放置：FC风格短促"滴"声
  - 塔高更新：马里奥吃金币音效
  - 错误操作：塞尔达解谜失败音
- **自动演示模式**：AI按最佳路径自动放置方块，速度可调
- **得分系统**：连续形成塔楼触发连击加分，显示8-bit数字特效

---

通过上述分析，本题的核心在于发现奇偶位置的动态规划特性，多种题解殊途同归。可视化设计应重点展现状态转移与位置奇偶性的内在联系。

---
处理用时：85.26秒