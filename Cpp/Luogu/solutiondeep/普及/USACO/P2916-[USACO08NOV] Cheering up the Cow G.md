# 题目信息

# [USACO08NOV] Cheering up the Cow G

## 题目描述

Farmer John has grown so lazy that he no longer wants to continue maintaining the cow paths that currently provide a way to visit each of his N (5 <= N <= 10,000) pastures (conveniently numbered 1..N). Each and every pasture is home to one cow. FJ plans to remove as many of the P (N-1 <= P <= 100,000) paths as possible while keeping the pastures connected. You must determine which N-1 paths to keep.

Bidirectional path j connects pastures S\_j and E\_j (1 <= S\_j <= N; 1 <= E\_j <= N; S\_j != E\_j) and requires L\_j (0 <= L\_j <= 1,000) time to traverse. No pair of pastures is directly connected by more than one path.

The cows are sad that their transportation system is being reduced. You must visit each cow at least once every day to cheer her up. Every time you visit pasture i (even if you're just traveling

through), you must talk to the cow for time C\_i (1 <= C\_i <= 1,000).

You will spend each night in the same pasture (which you will choose) until the cows have recovered from their sadness. You will end up talking to the cow in the sleeping pasture at least in the morning when you wake up and in the evening after you have returned to sleep.

Assuming that Farmer John follows your suggestions of which paths to keep and you pick the optimal pasture to sleep in, determine the minimal amount of time it will take you to visit each cow at least once in a day.

For your first 10 submissions, you will be provided with the results of running your program on a part of the actual test data.

POINTS: 300

约翰有N个牧场，编号依次为1到N。每个牧场里住着一头奶牛。连接这些牧场的有P条道路，每条道路都是双向的。第j条道路连接的是牧场Sj和Ej，通行需要Lj的时间。两牧场之间最多只有一条道路。约翰打算在保持各牧场连通的情况下去掉尽量多的道路。 

约翰知道，在道路被强拆后，奶牛会非常伤心，所以他计划拆除道路之后就去忽悠她们。约翰可以选择从任意一个牧场出发开始他维稳工作。当他走访完所有的奶牛之后，还要回到他的出发地。每次路过牧场i的时候，他必须花Ci的时间和奶牛交谈，即使之前已经做过工作了，也要留下来再谈一次。注意约翰在出发和回去的时候，都要和出发地的奶牛谈一次话。请你计算一下，约翰要拆除哪些道路，才能让忽悠奶牛的时间变得最少？


## 说明/提示

```cpp
   +-(15)-+ 
  /        \ 
 /          \ 
1-(5)-2-(5)-3-(6)--5 
   \   /(17)  / 
(12)\ /      /(12) 
     4------+ 

Keep these paths: 
1-(5)-2-(5)-3      5 
       \          / 
    (12)\        /(12) 
        *4------+ 
```
Wake up in pasture 4 and visit pastures in the order 4, 5, 4, 2, 3, 2, 1, 2, 4 yielding a total time of 176 before going back to sleep.


## 样例 #1

### 输入

```
5 7 
10 
10 
20 
6 
30 
1 2 5 
2 3 5 
2 4 12 
3 4 17 
2 5 15 
3 5 6 
4 5 12 
```

### 输出

```
176 
```

# AI分析结果



### 综合分析与结论
本题要求构造生成树，使遍历所有点的总时间最少。所有题解均采用 **Kruskal算法**，核心思路为：
- **边权处理**：将原边权 $L_j$ 转换为 $2 \times L_j + C_{S_j} + C_{E_j}$，以涵盖来回路径及点权。
- **最小生成树**：求转换后图的最小生成树总权值。
- **起点选择**：最终答案需加上最小点权（起点额外计算一次）。

关键正确性在于，每条边被遍历两次，点权贡献次数等于其度数，而起点因出发和返回需额外加一次。通过边权转换，生成树总权已包含所有边权和点权贡献，最后只需补充最小起点权。

---

### 精选题解与评分
#### 1. 作者：nao_nao（⭐⭐⭐⭐⭐）
**关键亮点**：  
- 详细分析度数对点权的影响，推导边权转换公式，帮助深入理解。
- 代码结构清晰，注释明确，变量命名规范。
- 个人心得指出生成树边权的转化逻辑，增强可读性。

**核心代码**：
```cpp
for(int i = 1;i <= m;i ++){
    scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].dis);
    edge[i].dis += edge[i].dis + arr[edge[i].u] + arr[edge[i].v]; // 边权转换
}
```

#### 2. 作者：qwqKanade（⭐⭐⭐⭐）
**关键亮点**：  
- 代码简洁高效，直接应用模板，适合快速实现。
- 明确提示“加上最小点权”的细节，避免遗漏。

**核心代码**：
```cpp
e[num].v = e[num].v*2 + a[e[num].l] + a[e[num].r]; // 边权处理
ans += e[i].v; // 生成树总权
printf("%d", ans + s); // 补充最小点权
```

#### 3. 作者：ShineEternal（⭐⭐⭐⭐）
**关键亮点**：  
- 博客中附带详细推导，结合样例图解，直观展示路径计算。
- 强调起点选择的贪心策略，强化思维训练。

**核心代码**：
```cpp
ans += a[i].dis; // 累加边权
printf("%d\n", ans + Min); // 输出答案
```

---

### 关键技巧总结
1. **边权转换**：将点权与边权结合，通过数学推导简化问题。
2. **贪心选择起点**：最小点权作为起点，降低总时间。
3. **Kruskal模板应用**：快速实现最小生成树，适合稀疏图。

---

### 拓展与类似题目
1. **P3366 【模板】最小生成树**：基础Kruskal/Prim算法练习。
2. **P1991 无线通讯网**：结合连通性与边权限制，类似生成树变形。
3. **P2872 [USACO07DEC] Building Roads S**：处理边权与点权结合的生成树问题。

---

### 个人心得摘录
- **nao_nao**：通过分析遍历路径的环状特性，发现边权转换的必要性。
- **Hiraeth**：调试时发现未处理起点额外点权，强调审题细节的重要性。
- **x_miracle**：通过数学归纳法验证度数对点权的影响，加深理解。

---
处理用时：87.06秒