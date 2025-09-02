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
本题需将原数组与目标数组排序后一一对应，计算调整总成本。所有题解均采用排序贪心策略，正确性基于排序后对应位置的差值之和最小。关键点包括正确排序、处理差值方向及使用足够大的数据类型（如`long long`）。

---

### 精选题解

#### 1. 作者：ysy666（⭐⭐⭐⭐⭐）
- **关键亮点**：代码简洁高效，正确使用`long long`避免溢出，排序后直接计算差值。
- **核心代码**：
  ```cpp
  sort(a+1,a+1+n); sort(b+1,b+1+n);
  for(int i=1;i<=n;i++) {
      if(a[i]<b[i]) ans+=(b[i]-a[i])*x;
      else ans+=(a[i]-b[i])*y;
  }
  ```

#### 2. 作者：花千树（⭐⭐⭐⭐⭐）
- **关键亮点**：代码可读性强，注释明确，同样正确处理数据类型。
- **核心代码**：
  ```cpp
  sort(a+1,a+1+n); sort(b+1,b+1+n);
  for(int i=1;i<=n;i++) {
      if(a[i]>b[i]) ans+=(a[i]-b[i])*y;
      else ans+=(b[i]-a[i])*x;
  }
  ```

#### 3. 作者：妖孽寒（⭐⭐⭐⭐）
- **关键亮点**：使用`unsigned long long`强调数据范围，强调注意x/y顺序。
- **心得引用**：“注意x和y不要打反了，我在这吃了好几次亏。”
- **核心代码**：
  ```cpp
  sort(a,a+m); sort(b,b+m);
  for(int i=0;i<m;i++) {
      if(a[i]>b[i]) ans+=(a[i]-b[i])*n2;
      else ans+=(b[i]-a[i])*n1;
  }
  ```

---

### 关键思路与技巧
- **排序对应**：将原数组和目标数组分别排序后一一对应，保证每对元素的调整成本最小。
- **数据类型**：使用`long long`避免溢出，尤其在差值与n较大时。
- **条件判断**：严格区分增加和减少的情况，避免混淆x和y。

---

### 拓展与同类题目
- **类似题目**：
  1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)（贪心排序）
  2. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)（排序后双指针）
  3. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)（贪心策略调整）

---

### 个人心得摘录
- **注意方向**：确保计算差值时用目标减当前或反之，正确应用x/y。（@Kio_）
- **数据范围**：使用足够大的类型存储结果，防止溢出。（@妖孽寒）

---
处理用时：80.47秒