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



# 算法分类  
动态规划  

---

## 题解思路与算法要点  
### 核心思路  
采用动态规划，状态定义为 `dp[i][o]` 表示到达岛屿 `i` 时，跳跃长度相对于初始值 `d` 的变化量为 `o` 时的最大宝石数。通过数学推导发现变化量 `o` 的绝对值上限约为 300，因此将状态空间压缩至 `30000*600` 的合理范围内。  

### 解决难点  
1. **状态压缩**：发现跳跃长度每次最多变化 ±1，利用等差数列求和公式推导出变化量上限约为 ±300，将第二维从 30000 压缩至 600。  
2. **转移方程**：`dp[i][o] = max(前驱状态) + gems[i]`，需检查 `o-1, o, o+1` 的合法性。  
3. **初始化处理**：起始点 `0` 和第一次跳跃到 `d` 的特殊情况需单独处理。  

### 可视化设计  
- **网格展示**：x 轴表示变化量 `o`（-300~300），y 轴表示岛屿位置 `i`，颜色亮度表示 `dp[i][o]` 的值。  
- **动画效果**：每次更新状态时，高亮当前岛屿 `i` 和对应的 `o`，用箭头从前驱位置指向当前格子。  
- **音效触发**：状态更新时播放 "blip" 音效，找到更优解时播放上扬音调。  
- **像素风格**：用 8-bit 色块表示状态值，深色代表低值，亮黄色代表高值。  

---

## 题解评分 (≥4星)  
1. **zythonc（★★★★☆）**  
   - 思路清晰，数学推导完整  
   - 代码简洁，偏移量处理优雅  
   - 核心代码段：  
     ```cpp  
     for(int i=m+1;i<=in;i++)  
       for(int o=-320;o<=320;o++)  
         f[i][df+o] = max(...)  
     ```  

2. **cheng_qi（★★★★☆）**  
   - 状态转移方程解释到位  
   - 代码注释详细，边界处理明确  
   - 核心片段：  
     ```cpp  
     for(int j=-D;j<=D;j++)  
       for(int k=-1;k<=1;k++)  
         step = j + d + k;  
     ```  

3. **A_grasser（★★★★☆）**  
   - 修复代码错误，可读性强  
   - 使用万能头简化代码结构  
   - 亮点代码：  
     ```cpp  
     f[i][370+j] = max(..., ..., ...) + w[i]  
     ```  

---

## 最优思路提炼  
**关键技巧**：  
1. **变化量压缩**：通过数学分析将跳跃长度变化量约束在 [-300, 300] 区间。  
2. **滚动偏移**：使用 `df=320` 或 `370` 等偏移量处理负下标问题。  
3. **三重状态转移**：每个状态仅依赖前驱的三种可能变化（-1,0,+1），时间复杂度 O(N*K)。  

**代码实现要点**：  
```cpp  
memset(dp, -INF, sizeof(dp));  
dp[d][offset] = gems[0] + gems[d];  
for (int i = d+1; i <= max_pos; i++) {  
    for (int o = -300; o <= 300; o++) {  
        int prev_jump = d + o;  
        if (prev_jump <= 0) continue;  
        int prev_pos = i - prev_jump;  
        dp[i][o+offset] = max({dp[prev_pos][o-1], dp[prev_pos][o], dp[prev_pos][o+1]}) + gems[i];  
    }  
}  
```  

---

## 相似题目推荐  
1. [P1095 守望者的逃离](https://www.luogu.com.cn/problem/P1095) - 跳跃与魔法值管理的动态规划  
2. [P1434 滑雪](https://www.luogu.com.cn/problem/P1434) - 状态转移依赖方向变化  
3. [P1941 飞扬的小鸟](https://www.luogu.com.cn/problem/P1941) - 跳跃高度与速度变化的动态规划  

---

## 可视化代码片段  
```javascript  
// 8-bit 风格 Canvas 绘制  
const canvas = document.getElementById('grid');  
const ctx = canvas.getContext('2d');  
const colors = ['#000000', '#1D2B53', '#7E2553', '#008751', '#AB5236',  
               '#5F574F', '#C2C3C7', '#FFF1E8', '#FF004D', '#FFA300'];  

function drawDP(i, o, value) {  
    const x = (o + 300) * 4; // 每个格子 4px  
    const y = i * 4;  
    const colorIdx = Math.min(9, Math.floor(value / 10));  
    ctx.fillStyle = colors[colorIdx];  
    ctx.fillRect(x, y, 4, 4);  
    playSound('blip'); // 触发音效  
}  
```  

---

## 个人心得摘录  
> "手算等差数列发现变化量上限约 300，这是状态压缩的关键。调试时发现偏移量设置不足会导致越界，最终设为 320 确保安全。" —— zythonc  
> "记忆化搜索比递推更直观，但要注意递归深度和缓存初始化。" —— __Hacheylight__  

---

## 复古像素动画设计  
1. **颜色方案**：采用 NES 经典的 56 色调色板，用深蓝表示低宝石数，红黄渐变表示高值。  
2. **自动演示**：按岛屿顺序逐步点亮格子，遇到更优解时闪烁三次。  
3. **音效设计**：  
   - `jump.wav`：每次状态更新时短促播放  
   - `treasure.wav`：收集到宝石时播放  
   - `game_over.wav`：遍历结束时触发  
4. **AI 模式**：算法自动以 30fps 速度遍历所有岛屿，按最优路径高亮显示。

---
处理用时：117.28秒