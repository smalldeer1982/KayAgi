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
本题是典型的最大不重叠区间问题，所有题解均采用贪心算法，核心思路为按右端点排序后依次选取不重叠区间。关键在于理解为何按右端点排序能保证最优解（为后续选择留出更多空间），以及实现时的边界处理。

---

### 精选题解推荐
#### 1. 微香玉烛暗（⭐⭐⭐⭐⭐）
**关键亮点**：  
- 结合样例数据逐步推演贪心过程，直观展现算法执行流程  
- 代码结构清晰，变量命名规范（now代替maxx更易理解）  
- 注释精简但切中要点，适合快速理解核心逻辑  

**代码核心**：
```cpp
sort(a+1,a+1+n);
now=a[1].y;
for(int i=2;i<=n;i++) {
    if(a[i].x>=now) {
        ans++;
        now=a[i].y;
    }
}
```

#### 2. user48442（⭐⭐⭐⭐）
**关键亮点**：  
- 通过反例对比左端点排序的缺陷，强化理解  
- 将问题类比为"工作调度"，提供更普适的解题视角  
- 详细注释说明变量含义和算法步骤  

**调试心得**：  
> "一开始我的思路是按照开头排一遍，结果发现不行...最优解是选择结束早的以便后续有更多选择空间"  
> —— 强调试错过程，加深对贪心策略选择的理解

#### 3. CloudStroll（⭐⭐⭐⭐）  
**关键拓展**：  
- 对比贪心与动态规划的应用场景  
- 推荐同类练习题目（P1937）建立知识网络  

**代码亮点**：  
```cpp
struct FARM { long long l,r; };
bool cmp(FARM x,FARM y) { return x.r<y.r; }
// 使用long long避免大数溢出
```

---

### 最优策略总结
**核心技巧**：  
1. **排序策略**：按右端点升序排列（证明：每次选最早结束的区间能为后续留出最大空间）  
2. **贪心实现**：维护当前已选区间的最大右端点值，线性扫描判断是否可加入新区间  
3. **初始值处理**：将第一个元素直接纳入结果集（ans=1），无需特殊条件判断  

**易错点**：  
- 区间端点是否可相等（本题允许Si >= Ej）  
- 数据范围：端点值可能达1e8，但无需特殊处理，普通int足够（但部分题解误用long long）

---

### 同类题目推荐
1. **P1803** 凌乱的yyy / 线段覆盖（同款贪心模板题）  
2. **P2887** 挤奶的时间（带权值的不重叠区间，需DP）  
3. **P2251** 质量检测（滑动窗口变式，训练区间处理思维）

---

### 关键代码实现
所有优秀解法的统一核心结构：  
```cpp
struct Node { int s, e; };
bool cmp(Node a, Node b) { return a.e < b.e; }

sort(v.begin(), v.end(), cmp);
int last = -1, ans = 0;
for(auto &c : v) {
    if(c.s >= last) {
        ans++;
        last = c.e;
    }
}
```

---
处理用时：47.96秒