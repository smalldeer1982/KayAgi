# 题目信息

# Bear and Two Paths

## 题目描述

Bearland has $ n $ cities, numbered $ 1 $ through $ n $ . Cities are connected via bidirectional roads. Each road connects two distinct cities. No two roads connect the same pair of cities.

Bear Limak was once in a city $ a $ and he wanted to go to a city $ b $ . There was no direct connection so he decided to take a long walk, visiting each city exactly once. Formally:

- There is no road between $ a $ and $ b $ .
- There exists a sequence (path) of $ n $ distinct cities $ v_{1},v_{2},...,v_{n} $ that $ v_{1}=a $ , $ v_{n}=b $ and there is a road between $ v_{i} $ and $ v_{i+1} $ for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643B/df2239069f54aa7a5a4a8635b063b23acac8c6be.png).

On the other day, the similar thing happened. Limak wanted to travel between a city $ c $ and a city $ d $ . There is no road between them but there exists a sequence of $ n $ distinct cities $ u_{1},u_{2},...,u_{n} $ that $ u_{1}=c $ , $ u_{n}=d $ and there is a road between $ u_{i} $ and $ u_{i+1} $ for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643B/df2239069f54aa7a5a4a8635b063b23acac8c6be.png).

Also, Limak thinks that there are at most $ k $ roads in Bearland. He wonders whether he remembers everything correctly.

Given $ n $ , $ k $ and four distinct cities $ a $ , $ b $ , $ c $ , $ d $ , can you find possible paths $ (v_{1},...,v_{n}) $ and $ (u_{1},...,u_{n}) $ to satisfy all the given conditions? Find any solution or print -1 if it's impossible.

## 说明/提示

In the first sample test, there should be $ 7 $ cities and at most $ 11 $ roads. The provided sample solution generates $ 10 $ roads, as in the drawing. You can also see a simple path of length $ n $ between $ 2 $ and $ 4 $ , and a path between $ 7 $ and $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643B/3628f2a6a8994f3a6e5bdc8bfe5270b9f748a11c.png)

## 样例 #1

### 输入

```
7 11
2 4 7 3
```

### 输出

```
2 7 1 3 6 5 4
7 1 5 4 6 2 3
```

## 样例 #2

### 输入

```
1000 999
10 20 30 40
```

### 输出

```
-1
```

# AI分析结果



# Bear and Two Paths

## 题目描述

Bearland 有 $n$ 个城市，编号为 $1$ 到 $n$。城市之间通过双向道路连接，每条道路连接两个不同城市，且没有重复道路。

Limak 曾想从城市 $a$ 到 $b$，但因无直达道路，选择了一条经过所有城市恰好一次的路径（哈密顿路径）。类似地，他想从城市 $c$ 到 $d$，也存在哈密顿路径但无直达道路。现给定 $n, k$ 和四个互异城市 $a, b, c, d$，判断是否存在满足边数 ≤k 的构造方案，若存在则输出两条路径，否则输出 -1。

## 算法分类
构造

## 题解分析与结论

所有题解的核心思路均为：
1. **特殊判无解**：当 $n=4$ 或 $k < n+1$ 时无法构造
2. **路径构造**：将四个特殊点（$a,b,c,d$）置于路径两端，中间填充剩余节点，通过特定排列使两条路径共享大部分边

关键构造技巧：
- 第一条路径形式：$a \rightarrow c \rightarrow [中间节点] \rightarrow d \rightarrow b$
- 第二条路径形式：$c \rightarrow a \rightarrow [中间节点] \rightarrow b \rightarrow d$
- 中间节点按顺序排列，确保两条路径的中间部分完全一致，从而共享边

## 推荐题解

### 题解1：_xbn（4星）
**亮点**：代码简洁，利用 vector 动态处理中间节点  
**核心思路**：
- 将 $a,c$ 放在路径首部，$d,b$ 放在尾部，中间填充其他节点
- 第二路径通过交换首部顺序实现

```cpp
cout << A << " " << C << " "; 
for (auto v : pr) cout << v << " "; 
cout << D << " " << B << endl;
cout << C << " " << A << " "; 
for (auto v : pr) cout << v << " "; 
cout << B << " " << D << endl;
```

### 题解2：copper_ingot（4星）
**亮点**：条件判断精确，路径构造清晰  
**核心实现**：
```cpp
printf("%d %d", a, c);
for (int i = 1; i <= cnt; i++) printf(" %d", node[i]);
printf(" %d %d\n", d, b);
printf("%d %d", c, a);
for (int i = 1; i <= cnt; i++) printf(" %d", node[i]);
printf(" %d %d\n", b, d);
```

### 题解3：wind_whisper（4星）
**亮点**：路径结构直观，变量命名清晰  
**路径生成**：
```cpp
x[1] = a; x[n] = b; x[2] = c; x[n-1] = d;
// 填充中间节点...
printf("%d %d ", c, a);
for(int i=3; i<=n-2; i++) printf("%d ",x[i]);
printf("%d %d\n", b, d);
```

## 关键思路总结
最优构造通过将中间节点统一顺序排列，使得两条路径共享中间部分的所有边，仅需额外添加 $a-c$ 和 $d-b$ 的边。总边数为 $n+1$，因此当 $k ≥ n+1$ 时可行。

## 拓展与相似题目
1. [CF723E One-Way Reform](https://www.luogu.com.cn/problem/CF723E)（构造欧拉路径）
2. [P2730 构造完全图](https://www.luogu.com.cn/problem/P2730)（图构造）
3. [CF1041D Glider](https://www.luogu.com.cn/problem/CF1041D)（贪心构造）

---
处理用时：177.25秒