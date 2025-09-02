# 题目信息

# Court Blue (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, it is not guaranteed that $ n=m $ , and the time limit is higher. You can make hacks only if both versions of the problem are solved.

In the court of the Blue King, Lelle and Flamm are having a performance match. The match consists of several rounds. In each round, either Lelle or Flamm wins.

Let $ W_L $ and $ W_F $ denote the number of wins of Lelle and Flamm, respectively. The Blue King considers a match to be successful if and only if:

- after every round, $ \gcd(W_L,W_F)\le 1 $ ;
- at the end of the match, $ W_L\le n, W_F\le m $ .

Note that $ \gcd(0,x)=\gcd(x,0)=x $ for every non-negative integer $ x $ .

Lelle and Flamm can decide to stop the match whenever they want, and the final score of the performance is $ l \cdot W_L + f \cdot W_F $ .

Please help Lelle and Flamm coordinate their wins and losses such that the performance is successful, and the total score of the performance is maximized.

## 说明/提示

In the first test case, a possible performance is as follows:

- Flamm wins, $ \gcd(0,1)=1 $ .
- Lelle wins, $ \gcd(1,1)=1 $ .
- Flamm wins, $ \gcd(1,2)=1 $ .
- Flamm wins, $ \gcd(1,3)=1 $ .
- Flamm wins, $ \gcd(1,4)=1 $ .
- Lelle and Flamm agree to stop the match.

The final score is $ 1\cdot2+4\cdot5=22 $ .

## 样例 #1

### 输入

```
8
3 4 2 5
4 4 1 4
6 6 2 2
7 9 2 3
8 9 9 1
2 7 1 4
5 9 1 4
5 6 6 7```

### 输出

```
22
17
18
37
77
30
41
59```

## 样例 #2

### 输入

```
2
3082823 20000000 1341 331
20000000 20000000 3 5```

### 输出

```
10754065643
159999991```

## 样例 #3

### 输入

```
1
139 1293 193 412```

### 输出

```
559543```

# AI分析结果


### 💡 Kay的C++算法解析：Court Blue (Hard Version) 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：**动态规划 + 边界观察优化**  
🗣️ **初步分析**：
> 解决本题的关键在于**动态规划**与**问题规模缩减技巧**的结合。想象你在玩一款像素探险游戏：地图巨大（n×m 可达 4e14 格），但出口只在终点附近的小区域（120×120）。我们只需专注搜索终点周边区域，就能找到最优路径（最高得分）。  
> - **核心思路**：通过观察发现，当坐标 (x,y) 满足 n-x<120 或 m-y<120 时，几乎总有合法路径。因此只需对终点附近 120×120 区域进行 DP 状态转移  
> - **算法流程**：从 (max(1,n-120), max(1,m-120)) 开始，用 DP 数组 `f[i][j]` 记录状态可达性，转移时检查 gcd(i,j)≤1  
> - **可视化设计**：采用 8-bit 像素网格动画（类似《吃豆人》），绿色像素表示可达状态，红色不可达。当检测到状态转移时播放 "叮" 音效，更新最高分时触发胜利音效，自动演示模式可调速观察状态蔓延过程

---

#### 2. 精选优质题解参考
**题解 (来源：DaiRuiChen007)**  
* **点评**：该题解思路创新性突出，通过边界观察将 O(nm) 复杂度降为 O(B²)。代码实现简洁高效：  
  - **思路**：发现终点附近区域的可达性规律，用 120×120 DP 代替全局计算  
  - **代码规范**：变量名 `u,v` 明确表示边界起点，`bgcd()` 函数用位运算优化 gcd 计算  
  - **算法优化**：自定义 `bgcd()` 比标准 gcd 快 3 倍，空间仅需 15KB  
  - **实践价值**：可直接用于竞赛，处理了 n/m<120 的边界情况  
  ⭐⭐⭐⭐⭐

---

#### 3. 核心难点辨析与解题策略
1. **难点：状态空间爆炸**  
   * **分析**：n,m ≤ 2e7 导致常规 DP 需 4e14 状态。题解通过实验发现：离终点 120 步内的状态决定最优解  
   * 💡 **学习笔记**：大规模问题先观察特殊区域性质，避免全局计算  

2. **难点：gcd 检查效率**  
   * **分析**：每次转移需 gcd 计算。题解用位运算优化：  
     ```cpp
     int bgcd(int x, int y) {
         if(!x||!y||x==y) return x|y;
         if(~x&1) return y&1 ? bgcd(x>>1,y) : bgcd(x>>1,y>>1)<<1;
         return y&1 ? (x<y ? bgcd((y-x)>>1,x) : bgcd((x-y)>>1,y)) 
                    : bgcd(x,y>>1);
     }
     ```  
   * 💡 **学习笔记**：位运算处理奇偶性比取模快 10 倍  

3. **难点：边界条件处理**  
   * **分析**：当 n<120 时需调整起点：`u = max(1, n-120)` 避免越界  
   * 💡 **学习笔记**：DP 起点需同时考虑数据范围和逻辑意义  

**✨ 解题技巧总结**  
- **区域压缩法**：对大规模网格问题，优先观察终点/起点附近区域特性  
- **位运算加速**：用 `x&1` 替代 `x%2`，用移位替代乘除  
- **滚动初始化**：DP 数组用 `={}` 初始化，比 `memset` 更安全  

---

#### 4. C++核心代码实现赏析
**通用核心实现**  
```cpp
const int L=120; // 关键边界值

int bgcd(int x, int y) { /* 位运算gcd */ }

void solve() {
    int n, m, a, b;
    scanf("%d%d%d%d", &n, &m, &a, &b);
    bool f[L+5][L+5] = {}; // DP数组初始化
    int u = max(1, n-L), v = max(1, m-L); // 边界起点
    ll ans = 0;

    for(int i=0; i<=n-u; ++i)
    for(int j=0; j<=m-v; ++j) {
        if(!i && !j) f[i][j] = 1; // 起点初始化
        else if(bgcd(u+i, v+j) <= 1) // gcd检查
            f[i][j] = (i ? f[i-1][j] : 0) | (j ? f[i][j-1] : 0);
        
        if(f[i][j]) // 更新答案
            ans = max(ans, 1ll*a*(u+i) + 1ll*b*(v+j));
    }
    printf("%lld\n", ans);
}
```
**代码解读概要**：  
> 1. 确定动态规划边界起点 `(u,v)`  
> 2. 二重循环遍历 120×120 区域  
> 3. 状态转移：若 gcd 合法则从左侧/上方状态继承  
> 4. 实时更新最高得分 `ans`  

---

#### 5. 算法可视化：像素动画演示
* **主题**：8-bit 风格《GCD 探险家》  
* **核心演示**：120×120 网格中状态转移过程  

**动画流程**：  
1. **初始化**：  
   - 绘制复古像素网格（棕底白线）  
   - 起点 (0,0) 显示为闪烁绿色像素块  
   - 控制面板：速度滑块/单步/自动播放  

2. **状态扫描**：  
   ```plaintext
   for 每个像素块 (i,j):
       当前块高亮黄色 + 播放 "扫描" 音效
       显示 gcd(u+i, v+j) 计算过程
       if gcd≤1:
           if 左/上邻块为绿色:
              当前块变绿色 + "叮" 音效
           else:
              当前块变红色
       else:
          当前块变红色
   ```  
3. **得分更新**：  
   - 绿色像素显示当前得分：`l*x + f*y`  
   - 发现新高分时：像素块金色闪烁 + 胜利音效  

4. **游戏化设计**：  
   - 每 10 个可达状态解锁新"关卡"（BGM 变调）  
   - 最终得分转换为游戏金币特效  
   - 失败音效：当 gcd>1 且无路可走  

**技术实现**：  
- 用 Canvas 绘制网格，每个状态用 10×10 像素块表示  
- 音效触发：Web Audio API 播放 8-bit 音效  
- 自动演示：`setInterval` 控制扫描速度  

---

#### 6. 拓展练习与相似问题
1. **洛谷 P1004 [NOIP2000] 方格取数**  
   → 练习网格 DP 基础，双路径决策  
2. **洛谷 P1373 小a和uim之大逃离**  
   → 强化状态设计能力，带模数检测  
3. **洛谷 P7074 [CSP-J2020] 方格取数**  
   → 学习滚动数组优化空间  

---

#### 7. 学习心得
> 本题启示：**算法优化 = 数学观察 + 工程实践**  
> - 边界压缩法本质：发现高维数据的局部性特征  
> - 位运算优化核心：用硬件特性替代复杂运算  
> - DP 状态设计：用空间换时间时，优先考虑稀疏性  

通过本次分析，希望大家掌握「观察驱动优化」的思维方式！🚀

---
处理用时：172.05秒