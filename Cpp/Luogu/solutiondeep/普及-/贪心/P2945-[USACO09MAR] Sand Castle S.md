# 题目信息

# [USACO09MAR] Sand Castle S

## 题目描述

Farmer John has built a sand castle! Like all good castles, the walls have crennelations, that nifty pattern of embrasures (gaps) and merlons (filled spaces); see the diagram below. The N (1 <= N <= 25,000) merlons of his castle wall are conveniently numbered 1..N; merlon i has height M\_i (1 <= M\_i <= 100,000); his merlons often have varying heights, unlike so many.

He wishes to modify the castle design in the following fashion: he has a list of numbers B\_1 through B\_N (1 <= B\_i <= 100,000), and wants to change the merlon heights to those heights B\_1, ..., B\_N in some order (not necessarily the order given or any other order derived from the data).

To do this, he has hired some bovine craftsmen to raise and lower the merlons' heights. Craftsmen, of course, cost a lot of money. In particular, they charge FJ a total X (1 <= X <= 100) money per unit height added and Y (1 <= Y <= 100) money per unit height

reduced.

FJ would like to know the cheapest possible cost of modifying his sand castle if he picks the best permutation of heights. The answer is guaranteed to fit within a 32-bit signed integer.

Note: about 40% of the test data will have N <= 9, and about 60% will have N <= 18.

## 说明/提示

FJ's castle starts with heights of 3, 1, and 1. He would like to change them so that their heights are 1, 2, and 2, in some order. It costs 6 to add a unit of height and 5 to remove a unit of height.


FJ reduces the first merlon's height by 1, for a cost of 5 (yielding merlons of heights 2, 1, and 1). He then adds one unit of height to the second merlon for a cost of 6 (yielding merlons of heights 2, 2, and 1).


## 样例 #1

### 输入

```
3 6 5 
3 1 
1 2 
1 2 
```

### 输出

```
11 
```

# AI分析结果



### 综合分析与结论
本题核心是贪心策略：将原数组与目标数组排序后一一对应，通过升/降操作计算最小费用。所有题解均采用该思路，差异仅在于代码实现（排序方式、容器选择）。

---

### 高星题解推荐

#### 1. 作者：ysy666（★★★★★）
**关键亮点**  
- 代码简洁清晰，直接使用STL排序  
- 变量命名规范，注释明确  
- 处理逻辑直观（差值直接乘对应费用）  
**核心代码**  
```cpp
sort(a+1,a+1+n);
sort(b+1,b+1+n);
for(int i=1;i<=n;i++) {
    if(a[i]<b[i]) ans+=(b[i]-a[i])*x; 
    else ans+=(a[i]-b[i])*y;
}
```

#### 2. 作者：autoint（★★★★☆）  
**关键亮点**  
- 使用优先队列实现降序排序，展示不同实现方式  
- 强调时间复杂度分析（堆排序的O(nlogn)特性）  
**核心代码**  
```cpp
priority_queue<int> a,b;
while(!a.empty()){
    u=a.top(); v=b.top();
    if(u<v) ans+=(v-u)*x;
    else if(u>v) ans+=(u-v)*y;
}
```

#### 3. 作者：Kio_（★★★★☆）  
**个人心得**  
- 特别提醒注意增减方向：a[i]<b[i]时需增加而非减少  
- 强调测试时的踩坑经历（运算符顺序错误）  
**核心代码**  
```cpp
if(a[i]-b[i]<0) num+=(b[i]-a[i])*x;  // 明确注释防止方向混淆
else num+=(a[i]-b[i])*y;
```

---

### 最优关键思路
**排序配对法**：将原数组与目标数组分别排序后对应位置计算差值。数学证明可通过反证法：若存在非单调配对更优，则交换后总成本必减小。

---

### 拓展应用
1. **同类问题**：元素配对最小化调整代价（如P1094 纪念品分组）  
2. **变种考法**：多维配对（如同时考虑高度和宽度）、动态调整（如P1090 合并果子）  
3. **思维延伸**：将离散问题转化为有序序列匹配是贪心经典套路

---

### 推荐练习题
1. P1094 纪念品分组（贪心+双指针）  
2. P1223 排队接水（排序确定最优时序）  
3. P1803 线段覆盖（区间调度与排序策略）

---
处理用时：52.21秒