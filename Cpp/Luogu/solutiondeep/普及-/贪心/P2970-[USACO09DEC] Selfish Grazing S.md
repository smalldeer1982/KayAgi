# 题目信息

# [USACO09DEC] Selfish Grazing S

## 题目描述

Each of Farmer John's N (1 <= N <= 50,000) cows likes to graze in a certain part of the pasture, which can be thought of as a large one-dimeensional number line. Cow i's favorite grazing range starts at location S\_i and ends at location E\_i (1 <= S\_i < E\_i; S\_i < E\_i <= 100,000,000).

Most folks know the cows are quite selfish; no cow wants to share any of its grazing area with another. Thus, two cows i and j can only graze at the same time if either S\_i >= E\_j or E\_i <= S\_j. FJ would like to know the maximum number of cows that can graze at the same time for a given set of cows and their preferences.

Consider a set of 5 cows with ranges shown below:

```cpp
  ... 1    2    3    4    5    6    7    8    9   10   11   12   13 ...
  ... |----|----|----|----|----|----|----|----|----|----|----|----|----
Cow 1:      <===:===>          :              :              :
Cow 2: <========:==============:==============:=============>:
Cow 3:          :     <====>   :              :              :
Cow 4:          :              :     <========:===>          :
Cow 5:          :              :     <==>     :              :
```
These ranges represent (2, 4), (1, 12), (4, 5), (7, 10), and (7, 8), respectively.

For a solution, the first, third, and fourth (or fifth) cows can all graze at the same time. If the second cow grazed, no other cows could graze. Also, the fourth and fifth cows cannot graze together, so it is impossible for four or more cows to graze.

约翰有N(1≤N≤50000)头牛，约翰的草地可以认为是一条直线．每只牛只喜欢在某个特定的范围内吃草．第i头牛喜欢在区间(Si，Ei)吃草，1≤Si<Ei≤1,000,000,00.

奶牛们都很自私，他们不喜欢和其他奶牛共享自己喜欢吃草的领域，因此约翰要保证任意

两头牛都不会共享他们喜欢吃草昀领域．如果奶牛i和奶牛J想要同时吃草，那么要满足：Si>=Ej或者Ei≤Sj．约翰想知道在同一时刻，最多可以有多少头奶牛同时吃草？


## 样例 #1

### 输入

```
5 
2 4 
1 12 
4 5 
7 10 
7 8 
```

### 输出

```
3 
```

# AI分析结果



### 综合分析与结论
该问题核心是**最大不相交区间调度**，所有题解均采用贪心算法。核心正确思路是：按右端点升序排序后依次选择不重叠区间。题解差异主要体现在代码风格与解释深度上，核心思路一致。

---

### 精选题解（评分≥4星）

#### 1. 微香玉烛暗（5星）
**关键亮点**：
- 提供详细的样例推导过程，直观展现贪心策略的正确性
- 代码简洁规范，含结构体运算符重载实现排序
- 解释中明确指出"结束时间影响后续选择"的关键点

**核心代码**：
```cpp
sort(a+1,a+1+n);
now=a[1].y;
for(int i=2;i<=n;i++) 
    if(a[i].x>=now) 
        ans++, now=a[i].y;
```

#### 2. CloudStroll（4星）
**关键亮点**：
- 对比贪心与DP的应用场景，扩展知识边界
- 代码模块化设计（Read_In/Solve/Write_Out）
- 注释清晰，变量命名规范

**核心代码**：
```cpp
sort(farm+1,farm+1+N,cmp);
for(i=1;i<=N;i++)
    if(farm[i].l>=end)
        ans++, end=farm[i].r;
```

#### 3. user48442（4星）
**关键亮点**：
- 通过反例证明按左端点排序的错误，强化理解
- 将问题类比为"工作调度"，建立跨问题思维连接
- 代码含详细注释，适合新手学习

**个人心得引用**：
> "一开始尝试按左端点排序时发现反例，转而思考结束时间的影响，最终理解贪心的本质是给后续留下最大选择空间"

---

### 关键思路与技巧总结
1. **排序策略**：按右端点升序排序（正确性关键）
2. **贪心选择**：每次选当前可选的结束最早的区间
3. **实现要点**：
   - 维护`last_end`记录已选区间的最大右端点
   - 遍历时仅需比较当前区间左端点与`last_end`
4. **复杂度**：O(nlogn)时间（排序主导），O(1)空间

---

### 拓展练习推荐
1. [P1803 活动安排问题](https://www.luogu.com.cn/problem/P1803)（同类基础题）
2. [P2251 质量检测](https://www.luogu.com.cn/problem/P2251)（区间覆盖变形）
3. [P2949 工作调度](https://www.luogu.com.cn/problem/P2949)（带权值的进阶版）

---

### 核心代码实现
以微香玉烛暗的代码为例：
```cpp
struct node { int x,y; };
bool operator < (const node &a, const node &b) {
    return a.y < b.y;
}

sort(a+1, a+n+1);
int ans = 1, now = a[1].y;
for(int i=2; i<=n; ++i) {
    if(a[i].x >= now) {
        ++ans;
        now = a[i].y;
    }
}
```
**实现思想**：结构体按右端点排序后，线性扫描维护当前已选区间的最大右端点，遇到左端点不小于当前右端点的区间则选中。

---
处理用时：42.64秒