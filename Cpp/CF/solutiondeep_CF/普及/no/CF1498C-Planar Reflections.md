# 题目信息

# Planar Reflections

## 题目描述

Gaurang has grown up in a mystical universe. He is faced by $ n $ consecutive 2D planes. He shoots a particle of decay age $ k $ at the planes.

A particle can pass through a plane directly, however, every plane produces an identical copy of the particle going in the opposite direction with a decay age $ k-1 $ . If a particle has decay age equal to $ 1 $ , it will NOT produce a copy.

For example, if there are two planes and a particle is shot with decay age $ 3 $ (towards the right), the process is as follows: (here, $ D(x) $ refers to a single particle with decay age $ x $ )

1. the first plane produces a $ D(2) $ to the left and lets $ D(3) $ continue on to the right;
2. the second plane produces a $ D(2) $ to the left and lets $ D(3) $ continue on to the right;
3. the first plane lets $ D(2) $ continue on to the left and produces a $ D(1) $ to the right;
4. the second plane lets $ D(1) $ continue on to the right ( $ D(1) $ cannot produce any copies).

In total, the final multiset $ S $ of particles is $ \{D(3), D(2), D(2), D(1)\} $ . (See notes for visual explanation of this test case.)

Gaurang is unable to cope up with the complexity of this situation when the number of planes is too large. Help Gaurang find the size of the multiset $ S $ , given $ n $ and $ k $ .

Since the size of the multiset can be very large, you have to output it modulo $ 10^9+7 $ .

Note: Particles can go back and forth between the planes without colliding with each other.

## 说明/提示

Let us explain the first example with four test cases.

Test case 1: ( $ n = 2 $ , $ k = 3 $ ) is already explained in the problem statement.

See the below figure of this simulation. Each straight line with a different color represents the path of a different particle. As you can see, there are four distinct particles in the multiset. Note that the vertical spacing between reflected particles is for visual clarity only (as mentioned before, no two distinct particles collide with each other)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1498C/df04d989fa23babd02f74b8b57d3f2d7886e9f14.png)Test case 2: ( $ n = 2 $ , $ k = 2 $ ) is explained as follows:

1. the first plane produces a $ D(1) $ to the left and lets $ D(2) $ continue on to the right;
2. the second plane produces a $ D(1) $ to the left and lets $ D(2) $ continue on to the right;
3. the first plane lets $ D(1) $ continue on to the left ( $ D(1) $ cannot produce any copies).

Total size of multiset obtained $ \{D(1), D(1), D(2)\} $ is equal to three.

Test case 3: ( $ n = 3 $ , $ k = 1 $ ), there are three planes, but decay age is only one. So no new copies are produced while the one particle passes through the planes. Hence, the answer is one.

Test case 4: ( $ n = 1 $ , $ k = 3 $ ) there is only one plane. The particle produces a new copy to the left. The multiset $ \{D(2), D(3)\} $ is of size two.

## 样例 #1

### 输入

```
4
2 3
2 2
3 1
1 3```

### 输出

```
4
3
1
2```

## 样例 #2

### 输入

```
3
1 1
1 500
500 250```

### 输出

```
1
2
257950823```

# AI分析结果

### 题目内容重写
Gaurang 生活在一个神秘的宇宙中。他面前有 $n$ 个连续的二维平面。他向这些平面发射了一个衰变年龄为 $k$ 的粒子。

粒子可以直接穿过平面，但每个平面会产生一个与原粒子相同但方向相反的粒子，且其衰变年龄为 $k-1$。如果粒子的衰变年龄为 $1$，则不会产生副本。

例如，如果有两个平面，且发射了一个衰变年龄为 $3$ 的粒子（向右），过程如下：（这里，$D(x)$ 表示一个衰变年龄为 $x$ 的粒子）

1. 第一个平面产生一个 $D(2)$ 向左，并让 $D(3)$ 继续向右；
2. 第二个平面产生一个 $D(2)$ 向左，并让 $D(3)$ 继续向右；
3. 第一个平面让 $D(2)$ 继续向左，并产生一个 $D(1)$ 向右；
4. 第二个平面让 $D(1)$ 继续向右（$D(1)$ 不会产生任何副本）。

最终，粒子的多重集 $S$ 为 $\{D(3), D(2), D(2), D(1)\}$。

Gaurang 无法处理当平面数量过多时的复杂情况。请帮助 Gaurang 找到多重集 $S$ 的大小，给定 $n$ 和 $k$。

由于多重集的大小可能非常大，请输出其对 $10^9+7$ 取模的结果。

### 算法分类
动态规划

### 题解分析与结论
本题的核心在于通过动态规划来模拟粒子的衰变过程。大多数题解都采用了动态规划的思路，但状态定义和转移方程有所不同。以下是各题解的对比与总结：

1. **Composite_Function** 的题解：
   - 状态定义：$\text{dp[i][j]}$ 表示能量为 $i$，前面有 $j$ 个平面。
   - 转移方程：$\text{dp[i][j]} = \text{dp[i][j - 1]} + \text{dp[i - 1][n - j]}$。
   - 优点：状态定义清晰，转移方程简洁，时间复杂度为 $O(nk)$。
   - 评分：4星

2. **httohu** 的题解：
   - 状态定义：$f(k,i,0/1)$ 表示当前粒子寿命为 $k$，位置为 $i$，方向为左/右。
   - 转移方程：$f(k,i,0)=1+\sum\limits_{j=i}^n{f(k-1,j,1)}$，$f(k,i,1)=1+\sum\limits_{j=1}^{i-1}{f(k-1,j+1,0)}$。
   - 优点：考虑了粒子的方向，状态转移方程较为复杂但全面。
   - 评分：3星

3. **vectorwyx** 的题解：
   - 状态定义：$f_{i,j,0/1}$ 表示衰变期为 $j$ 的粒子从第 $i$ 个平面的左面/右面穿过时产生的粒子数。
   - 转移方程：$f_{i,j,0}=f_{i+1,j,0}+f_{i-1,j-1,1}$，$f_{i,j,1}=f_{i-1,j,1}+f_{i+1,j-1,0}$。
   - 优点：状态定义详细，转移方程清晰，时间复杂度为 $O(nk)$。
   - 评分：4星

### 最优题解
1. **Composite_Function** 的题解（4星）
   - 关键亮点：状态定义简洁，转移方程易于理解，代码实现清晰。
   - 核心代码：
     ```cpp
     for (int i = 1; i <= k; ++i)
         for (int j = 1; j <= n; ++j)
             dp[i][j] = (dp[i][j - 1] + dp[i - 1][n - j]) % mod;
     ```

2. **vectorwyx** 的题解（4星）
   - 关键亮点：状态定义全面，考虑了粒子的方向，转移方程清晰。
   - 核心代码：
     ```cpp
     fo(j,1,k){
         go(i,n,1) f[i][j][0]=(f[i+1][j][0]+f[i-1][j-1][1])%lmq;
         fo(i,1,n) f[i][j][1]=(f[i-1][j][1]+f[i+1][j-1][0])%lmq;
     }
     ```

### 关键思路与技巧
- **状态定义**：根据粒子的衰变年龄和平面数量定义状态，考虑粒子的方向可以更全面地模拟过程。
- **转移方程**：通过当前状态和前一状态的关系，推导出粒子的衰变和分裂过程。
- **优化**：使用动态规划避免重复计算，时间复杂度为 $O(nk)$。

### 可拓展之处
- 类似题目可以考察粒子的其他属性，如速度、质量等，增加问题的复杂性。
- 可以扩展到三维空间，考虑粒子的空间运动。

### 推荐题目
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)

### 个人心得摘录
- **Composite_Function**：最近在刷思维题，附上有趣的：CF1733E。
- **httohu**：一开始向左飞的方程没写 $j+1$ 一直在调，还是太菜了。画个图就知道啦。
- **vectorwyx**：注意要先枚举第二维。

---
处理用时：39.68秒