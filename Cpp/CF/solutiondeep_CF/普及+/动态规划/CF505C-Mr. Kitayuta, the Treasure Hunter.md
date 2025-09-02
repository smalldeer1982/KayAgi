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

### 题目内容重写

**题目描述**

Shuseki群岛是Yutampo海中的一个由30001个小岛组成的群岛。这些岛屿沿一条直线均匀分布，从西向东编号为0到30000。这些岛屿上藏有许多宝藏。总共有n颗宝石分布在Shuseki群岛上，第i颗宝石位于岛屿p_i上。

Mr. Kitayuta刚刚到达了岛屿0。凭借他卓越的跳跃能力，他将按照以下规则在岛屿之间向东跳跃：

- 首先，他将从岛屿0跳跃到岛屿d。
- 之后，他将按照以下规则继续跳跃。设l为上一次跳跃的长度，即如果上一次跳跃是从岛屿prev跳跃到岛屿cur，则l = cur - prev。他将向东跳跃长度为l-1、l或l+1的距离。也就是说，他将跳跃到岛屿(cur + l - 1)、(cur + l)或(cur + l + 1)（如果这些岛屿存在）。跳跃的长度必须为正数，即当l=1时，他不能跳跃长度为0的距离。如果没有有效的目的地，他将停止跳跃。

Mr. Kitayuta将收集他在跳跃过程中访问的岛屿上的宝石。求他能够收集到的最大宝石数量。

**说明/提示**

在第一个样例中，最优路径是0 → 10（+1颗宝石）→ 19 → 27（+2颗宝石）→...

在第二个样例中，最优路径是0 → 8 → 15 → 21 → 28（+1颗宝石）→ 36（+1颗宝石）→ 45（+1颗宝石）→ 55（+1颗宝石）→ 66（+1颗宝石）→ 78（+1颗宝石）→...

在第三个样例中，最优路径是0 → 7 → 13 → 18（+1颗宝石）→ 24（+2颗宝石）→ 30（+1颗宝石）→...

**样例 #1**

**输入**

```
4 10
10
21
27
27
```

**输出**

```
3
```

**样例 #2**

**输入**

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

**输出**

```
6
```

**样例 #3**

**输入**

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

**输出**

```
4
```

### 题解分析与结论

#### 综合分析

该题目是一个典型的动态规划问题，主要难点在于如何优化状态空间以避免内存溢出。大多数题解都采用了将跳跃步数的变化次数作为状态维度的优化策略，从而将状态空间从30000×30000降低到30000×600左右，解决了内存问题。

#### 关键思路与技巧

1. **状态优化**：将跳跃步数的变化次数作为状态维度，而不是直接存储跳跃步数。通过等差数列求和公式，可以证明变化次数最多为300次左右，从而大大减少了状态空间。
2. **动态规划转移方程**：状态转移方程通常为`f[i][j] = max(f[i][j], f[i - (d + j)][j], f[i - (d + j)][j - 1], f[i - (d + j)][j + 1]) + v[i]`，其中`v[i]`表示岛屿i上的宝石数量。
3. **边界处理**：在处理跳跃步数时，需要确保跳跃步数为正数，并且跳跃后的岛屿编号不超过30000。

#### 所选高星题解

1. **作者：zythonc (赞：9)**  
   **星级：5星**  
   **关键亮点**：  
   - 详细分析了状态优化的思路，通过变化次数将状态空间从30000×30000降低到30000×650。  
   - 提供了清晰的转移方程和代码实现，代码简洁且高效。  
   **核心代码**：
   ```cpp
   for(int i=m+1;i<=in;i++){
       for(int o=-320;o<=320;o++){
           if(m+o>0&&m+o<=i) f[i][df+o]=max(f[i][df+o],tm(f[i-(m+o)][df+o],f[i-(m+o)][df+o-1],f[i-(m+o)][df+o+1])+v[i]);
           ans=max(ans,f[i][df+o]);
       }
   }
   ```

2. **作者：A_grasser (赞：3)**  
   **星级：4星**  
   **关键亮点**：  
   - 通过等差数列求和公式证明了变化次数的上限，优化了状态空间。  
   - 提供了详细的转移方程和代码实现，代码可读性较好。  
   **核心代码**：
   ```cpp
   for(int i=d+1;i<=x;i++){
       for(int j=-320;j<=320;j++){
           if(d+j>0 && d+j<=i)
               f[i][370+j]=max(f[i][370+j],max(f[i-(d+j)][370+j],max(f[i-(d+j)][370+j-1],f[i-(d+j)][370+j+1]))+w[i]);
           ans=max(ans,f[i][370+j]);
       }
   }
   ```

3. **作者：cheng_qi (赞：1)**  
   **星级：4星**  
   **关键亮点**：  
   - 详细分析了状态优化的必要性，并通过等差数列求和公式证明了变化次数的上限。  
   - 提供了清晰的转移方程和代码实现，代码简洁且高效。  
   **核心代码**：
   ```cpp
   for(int i=d+1;i<=30000;i++){
       for(int j=-D;j<=D;j++){
           for(int k=-1;k<=1;k++){
               int step = j + d + k;
               if(step < 1 || i + step > 30000 || j + k < -D || j + k > D)
                   continue;
               f[i + step][j + k + D] = max(f[i + step][j + k + D], f[i][j + D] + cnt[i + step]);
           }
           ans = max(ans, f[i][j + D]);
       }
   }
   ```

### 扩展思路与推荐题目

1. **扩展思路**：该题的状态优化思路可以应用于其他类似的动态规划问题，尤其是当状态空间较大时，可以通过分析状态的变化规律来减少状态维度。
2. **推荐题目**：
   - [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的背包问题，考察动态规划的基本应用。
   - [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)：动态规划与贪心结合的问题，考察状态转移的优化。
   - [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)：动态规划与序列处理结合的问题，考察状态的设计与转移。

---
处理用时：62.18秒