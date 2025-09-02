# 题目信息

# Division into Teams

## 题目描述

Petya loves football very much, especially when his parents aren't home. Each morning he comes to the yard, gathers his friends and they play all day. From time to time they have a break to have some food or do some chores (for example, water the flowers).

The key in football is to divide into teams fairly before the game begins. There are $ n $ boys playing football in the yard (including Petya), each boy's football playing skill is expressed with a non-negative characteristic $ a_{i} $ (the larger it is, the better the boy plays).

Let's denote the number of players in the first team as $ x $ , the number of players in the second team as $ y $ , the individual numbers of boys who play for the first team as $ p_{i} $ and the individual numbers of boys who play for the second team as $ q_{i} $ . Division $ n $ boys into two teams is considered fair if three conditions are fulfilled:

- Each boy plays for exactly one team ( $ x+y=n $ ).
- The sizes of teams differ in no more than one ( $ |x-y|<=1 $ ).
- The total football playing skills for two teams differ in no more than by the value of skill the best player in the yard has. More formally: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF149C/3138f273213b60ee92a7f26382963c42eacb0d68.png)

Your task is to help guys divide into two teams fairly. It is guaranteed that a fair division into two teams always exists.

## 说明/提示

Let's consider the first sample test. There we send the first and the second boy to the first team and the third boy to the second team. Let's check all three conditions of a fair division. The first limitation is fulfilled (all boys play), the second limitation on the sizes of groups ( $ |2-1|=1<=1 $ ) is fulfilled, the third limitation on the difference in skills ( $ (2+1)-(1)=2<=2 $ ) is fulfilled.

## 样例 #1

### 输入

```
3
1 2 1
```

### 输出

```
2
1 2 
1
3 
```

## 样例 #2

### 输入

```
5
2 3 3 1 1
```

### 输出

```
3
4 1 3 
2
5 2 
```

# AI分析结果



### 题目重写

#### 题目描述

Petya 非常喜欢足球，尤其是当父母不在家时。每个早晨他都会到院子里，召集朋友们踢一整天的球。偶尔他们会休息一下吃点东西或做些杂务（例如浇花）。

足球的关键在于比赛开始前公平地分成两队。院子里有 $n$ 个男孩（包括 Petya）在踢球，每个男孩的足球技能用非负特征值 $a_i$ 表示（数值越大，男孩踢得越好）。

设第一队的人数为 $x$，第二队为 $y$，第一队的男孩编号为 $p_i$，第二队的为 $q_i$。将 $n$ 个男孩分为两队的公平性需满足以下条件：

1. 每个男孩只属于一队（$x + y = n$）。
2. 两队人数差不超过 1（$|x - y| \leq 1$）。
3. 两队技能总和之差的绝对值不超过全场最高技能值，即 $|\sum_{i=1}^x a_{p_i} - \sum_{i=1}^y a_{q_i}| \leq \max(a_1, a_2, \dots, a_n)$。

你需要帮助他们公平分队，题目保证存在解。

#### 样例 #1

##### 输入
```
3
1 2 1
```

##### 输出
```
2
1 2 
1
3 
```

---

### 算法分类
**构造**

---

### 题解分析与结论

所有题解的核心思路均为**排序后交替分配**：
1. 将技能值排序（升序或降序均可）。
2. 按奇偶位置交替分配到两队。
3. 通过数学归纳法证明此方法满足差值约束。

#### 关键思路与技巧
1. **排序策略**：无论升序或降序，交替分配均能保证总和差不超过最大值。
2. **编号处理**：使用结构体或 `pair` 保存原始编号，排序后按奇偶输出。
3. **数学证明**：每对相邻元素的差值之和不超过最大值，从而总差值被限制。

---

### 精选题解

#### 题解作者：BYWYR（★★★★☆）
**关键亮点**：
- 提供完整的数学归纳证明。
- 代码结构清晰，使用结构体排序。
- 处理了奇偶分配的边界条件。

**核心代码**：
```cpp
sort(a+1, a+1+n); // 按技能值降序排序
for(int i=1; i<=n; i++) {
    if(i%2) team1[++cnt1] = a[i].num; // 奇数位分到队1
    else team2[++cnt2] = a[i].num;     // 偶数位分到队2
}
```

---

### 拓展与相似题目
1. **CF455A Boredom**（相似贪心构造）：[题目链接](https://www.luogu.com.cn/problem/CF455A)
2. **P1094 纪念品分组**（分组差值约束）：[题目链接](https://www.luogu.com.cn/problem/P1094)
3. **CF1607H Banquet Preparations**（构造分块策略）：[题目链接](https://www.luogu.com.cn/problem/CF1607H)

---
处理用时：102.21秒