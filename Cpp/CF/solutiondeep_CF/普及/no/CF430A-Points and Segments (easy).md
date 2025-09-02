# 题目信息

# Points and Segments (easy)

## 题目描述

Iahub isn't well prepared on geometry problems, but he heard that this year there will be a lot of geometry problems on the IOI selection camp. Scared, Iahub locked himself in the basement and started thinking of new problems of this kind. One of them is the following.

Iahub wants to draw $ n $ distinct points and $ m $ segments on the $ OX $ axis. He can draw each point with either red or blue. The drawing is good if and only if the following requirement is met: for each segment $ [l_{i},r_{i}] $ consider all the red points belong to it ( $ r_{i} $ points), and all the blue points belong to it ( $ b_{i} $ points); each segment $ i $ should satisfy the inequality $ |r_{i}-b_{i}|<=1 $ .

Iahub thinks that point $ x $ belongs to segment $ [l,r] $ , if inequality $ l<=x<=r $ holds.

Iahub gives to you all coordinates of points and segments. Please, help him to find any good drawing.

## 样例 #1

### 输入

```
3 3
3 7 14
1 5
6 10
11 15
```

### 输出

```
0 0 0```

## 样例 #2

### 输入

```
3 4
1 2 3
1 2
2 3
5 6
2 2
```

### 输出

```
1 0 1 ```

# AI分析结果



### 题目内容中文重写
#### 题目名称：Points and Segments (easy)

**题目描述**  
Iahub 在几何问题上准备不足，但他听说今年的IOI选拔营会有大量几何题。他把自己关在地下室思考新问题，其中之一如下：  

Iahub 想在OX轴上绘制 $n$ 个不同的点和 $m$ 条线段。每个点可染为红色或蓝色。要求满足：对于每条线段 $[l_i, r_i]$，计算其包含的红点数量 $r_i$ 和蓝点数量 $b_i$，需满足 $|r_i - b_i| \le 1$。  

点 $x$ 属于线段 $[l, r]$ 当且仅当 $l \le x \le r$。  
给定所有点和线段的坐标，请构造任意一种合法染色方案。  

---

### 算法分类  
构造  

---

### 题解分析与结论  
**核心思路**：将点按坐标排序后交替染色（如红蓝交替）。无论线段如何分布，该策略均可保证每条线段内红蓝点数差不超过1。  

**解决难点**：  
1. **线段无关性**：无需处理线段的具体位置，仅需保证整体交替染色即可满足所有线段要求。  
2. **构造证明**：通过数学归纳或分奇偶分析，证明交替染色在任何区间内的差值最多为1。  

**最优思路**：  
- 将点排序后，按顺序交替染色（如奇偶位染色）。  
- 时间复杂度：$O(n \log n)$，来自排序步骤。  

---

### 高星题解推荐  
#### 1. 题解作者：Y_ATM_K（★★★★★）  
**关键亮点**：  
- 明确给出排序后交替染色的构造性证明，逻辑严谨。  
- 代码简洁高效，直接通过排序后奇偶位染色。  
**核心代码**：  
```cpp
sort(a+1, a+1+n);
for(int i=1; i<=n; ++i)
    ans[a[i].u] = i & 1; // 按排序后的位置奇偶性染色
```

#### 2. 题解作者：yaaaaaan（★★★★☆）  
**关键亮点**：  
- 通过结构体记录原始序号，排序后染色再还原顺序，处理清晰。  
- 代码可读性强，适合理解构造过程。  
**核心代码**：  
```cpp
sort(a+1, a+n+1, cmp);
for(int i=1; i<=n; i++)
    b[a[i].ii] = i % 2; // 交替染色并记录原始序号
```

#### 3. 题解作者：luuia（★★★★☆）  
**关键亮点**：  
- 提供数学证明，详细分析四种区间情况的差值。  
- 代码完整还原初始顺序，体现对输出格式的细致处理。  
**个人心得**：  
> “交替染色避免了相邻点同色，从而保证区间差值≤1。”  

---

### 拓展与举一反三  
**类似问题套路**：  
- **交替构造**：适用于需要平衡两种状态的问题（如CF1118B：奇偶分组）。  
- **无关输入处理**：某些题目中部分输入不影响解法，可忽略（如本题的线段数据）。  

**推荐题目**：  
1. [CF1156C - Match Points](https://www.luogu.com.cn/problem/CF1156C)（贪心+排序）  
2. [P1104 纪念品分组](https://www.luogu.com.cn/problem/P1104)（排序后双指针构造）  
3. [CF978B File Name](https://www.luogu.com.cn/problem/CF978B)（交替模式处理）

---
处理用时：106.24秒