# 题目信息

# Hobbits' Party

## 题目描述

Everyone knows that hobbits love to organize all sorts of parties and celebrations. There are $ n $ hobbits living in the Shire. They decided to organize the Greatest Party (GP) that would last for several days. Next day the hobbits wrote a guest list, some non-empty set containing all the inhabitants of the Shire. To ensure that everybody enjoy themselves and nobody gets bored, for any two days (say, days A and B) of the GP there existed at least one hobbit, invited to come on day A and on day B. However, to ensure that nobody has a row, for any three different days A, B, C there shouldn't be a hobbit invited on days A, B and C. The Shire inhabitants are keen on keeping the GP going for as long as possible. Your task is given number $ n $ , to indicate the GP's maximum duration and the guest lists for each day.

## 样例 #1

### 输入

```
4
```

### 输出

```
3
1 2 
1 3 
2 3 
```

## 样例 #2

### 输入

```
5
```

### 输出

```
3
1 2 
1 3 
2 3 
```

# AI分析结果



# 霍比特人的派对

## 题目描述

每个霍比特人都喜欢组织各种派对和庆祝活动。夏尔地区住着 $n$ 个霍比特人，他们决定举办一个持续多天的"最伟大派对（GP）"。第二天，霍比特人们写了一份包含所有居民的宾客名单（非空集合）。为了确保每个人都能尽兴且不会感到无聊，对于 GP 的任意两天（例如天 A 和天 B），必须至少存在一个同时在两天被邀请的霍比特人。同时，为了避免任何冲突，对于任意三个不同的天 A、B、C，不允许存在同时在三天都被邀请的霍比特人。你的任务是给定 $n$，确定 GP 的最长持续时间，并给出每天的宾客名单。

## 样例 #1

### 输入

```
4
```

### 输出

```
3
1 2 
1 3 
2 3 
```

## 样例 #2

### 输入

```
5
```

### 输出

```
3
1 2 
1 3 
2 3 
```

---

**算法分类**：构造、组合数学

---

## 题解分析与结论

题目核心是构造一个满足以下条件的最大天数方案：
1. 任意两天有共同宾客 → 转化为完全图的边覆盖问题
2. 任意三天无共同宾客 → 每个宾客最多出现两次

最优解法基于完全图模型：
- 将每个宾客视为图中的边，连接两个不同的天
- 最大天数 $k$ 满足 $\frac{k(k-1)}{2} \leq n$，构造 $k$ 个顶点的完全图
- 每个边对应唯一的宾客编号，参与对应的两天

---

## 精选题解

### 题解作者：Feyn（5星）
**关键亮点**：
- 直接利用完全图边数公式求解最大天数
- 简洁的双重循环构造宾客分配
- 代码可读性极佳，时间复杂度 $O(k^2)$

**核心代码**：
```cpp
int m,n=1,now,a[N][N],cnt[N];
read(m);
while(n*(n-1)/2<=m) n++; n--;
for(int i=1;i<=n;i++){
    for(int j=i+1;j<=n;j++){
        a[i][++cnt[i]]=++now; // 将宾客分配到两天
        a[j][++cnt[j]]=now;
    }
}
```

---

### 题解作者：王梓涵（4星）
**关键亮点**：
- 分块构造矩阵的思路清晰
- 使用数学推导确定最大天数
- 需要注意浮点运算可能带来的精度问题

**核心实现**：
```cpp
double t = (sqrt(8*n+1)-1)/2;
int num = t + 1;
for(int i=1; i<=num-1; ++i)
    for(int j=i; j<=num-1; ++j)
        a[i][j] = ++cnt; // 上三角填充
for(int i=1; i<=num-1; ++i)
    for(int j=i+1; j<=num; ++j)
        a[j][i] = ++cnt; // 下三角填充
```

---

## 关键思路总结
1. **完全图模型**：将天数视为顶点，宾客视为边，保证每两天有共同宾客
2. **数学极值**：通过 $\frac{k(k-1)}{2} \leq n$ 确定最大天数 $k$
3. **对称构造**：通过双重循环或矩阵分块实现边的均匀分配

---

## 拓展建议
类似构造问题可考虑：
- 拉丁方阵（CF259B）
- 二部图匹配（CF489B）
- 循环赛程表（SPOJ TOUR）

---

## 相似题目推荐
1. [CF1385C - Make It Good](https://www.luogu.com.cn/problem/CF1385C)（构造极值）
2. [CF1348B - Phoenix and Beauty](https://www.luogu.com.cn/problem/CF1348B)（周期性构造）
3. [CF1472D - Even-Odd Game](https://www.luogu.com.cn/problem/CF1472D)（贪心策略）

---
处理用时：137.95秒