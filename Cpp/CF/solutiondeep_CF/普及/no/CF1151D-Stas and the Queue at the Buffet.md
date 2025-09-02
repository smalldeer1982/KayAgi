# 题目信息

# Stas and the Queue at the Buffet

## 题目描述

During a break in the buffet of the scientific lyceum of the Kingdom of Kremland, there was formed a queue of $ n $ high school students numbered from $ 1 $ to $ n $ . Initially, each student $ i $ is on position $ i $ . Each student $ i $ is characterized by two numbers — $ a_i $ and $ b_i $ . Dissatisfaction of the person $ i $ equals the product of $ a_i $ by the number of people standing to the left of his position, add the product $ b_i $ by the number of people standing to the right of his position. Formally, the dissatisfaction of the student $ i $ , which is on the position $ j $ , equals $ a_i \cdot (j-1) + b_i \cdot (n-j) $ .

The director entrusted Stas with the task: rearrange the people in the queue so that minimize the total dissatisfaction.

Although Stas is able to solve such problems, this was not given to him. He turned for help to you.

## 说明/提示

In the first example it is optimal to put people in this order: ( $ 3, 1, 2 $ ). The first person is in the position of $ 2 $ , then his dissatisfaction will be equal to $ 4 \cdot 1+2 \cdot 1=6 $ . The second person is in the position of $ 3 $ , his dissatisfaction will be equal to $ 2 \cdot 2+3 \cdot 0=4 $ . The third person is in the position of $ 1 $ , his dissatisfaction will be equal to $ 6 \cdot 0+1 \cdot 2=2 $ . The total dissatisfaction will be $ 12 $ .

In the second example, you need to put people in this order: ( $ 3, 2, 4, 1 $ ). The total dissatisfaction will be $ 25 $ .

## 样例 #1

### 输入

```
3
4 2
2 3
6 1
```

### 输出

```
12```

## 样例 #2

### 输入

```
4
2 4
3 3
7 1
2 3
```

### 输出

```
25```

## 样例 #3

### 输入

```
10
5 10
12 4
31 45
20 55
30 17
29 30
41 32
7 1
5 5
3 15
```

### 输出

```
1423```

# AI分析结果

### 题目内容重写
在克雷姆兰科学学院的食堂休息期间，形成了由 $n$ 个高中生组成的队列，编号从 $1$ 到 $n$。最初，每个学生 $i$ 站在位置 $i$。每个学生 $i$ 有两个属性 $a_i$ 和 $b_i$。学生 $i$ 的不满意度等于 $a_i$ 乘以他左边的人数，加上 $b_i$ 乘以他右边的人数。形式化地，学生 $i$ 站在位置 $j$ 时的不满意度为 $a_i \cdot (j-1) + b_i \cdot (n-j)$。

校长交给 Stas 一个任务：重新排列队列中的人，使得总不满意度最小。

### 算法分类
贪心、排序

### 题解分析与结论
所有题解的核心思路都是通过化简不满意度公式，将其拆分为固定部分和可变部分，然后通过排序和贪心策略来最小化总不满意度。具体来说，不满意度公式可以化简为 $(a_i - b_i) \cdot j + (b_i \cdot n - a_i)$，其中 $(b_i \cdot n - a_i)$ 是固定值，而 $(a_i - b_i) \cdot j$ 是可变部分。为了使总不满意度最小，应该将 $(a_i - b_i)$ 较大的学生放在队列的前面，即让较大的 $(a_i - b_i)$ 乘以较小的 $j$。

### 评分较高的题解
1. **作者：da32s1da (5星)**
   - **关键亮点**：简洁明了地推导了不满意度公式，并直接通过排序和贪心策略实现了最小化总不满意度。代码清晰且高效。
   - **核心代码**：
     ```cpp
     sort(a+1,a+n+1);
     for(int i=1;i<=n;i++)Ans+=1ll*a[i]*(n-i+1);
     ```

2. **作者：OIerWu_829 (4星)**
   - **关键亮点**：使用结构体存储学生属性，并通过自定义排序规则实现了贪心策略。代码结构清晰，易于理解。
   - **核心代码**：
     ```cpp
     sort(p + 1, p + 1 + n, cmp);
     for (LL i = 1; i <= n; i++)
         ans += (p[i].a - p[i].b) * i - p[i].a + p[i].b * n;
     ```

3. **作者：Second_Gardenia (4星)**
   - **关键亮点**：详细解释了贪心策略的推导过程，并通过优先队列实现了排序。代码简洁且高效。
   - **核心代码**：
     ```cpp
     sort(s + 1, s + n + 1, greater<int>());
     for (i = 1; i <= n; i++)
         sum += 1ll * s[i] * i;
     ```

### 最优关键思路或技巧
1. **公式化简**：将不满意度公式化简为 $(a_i - b_i) \cdot j + (b_i \cdot n - a_i)$，分离出固定部分和可变部分。
2. **贪心策略**：将 $(a_i - b_i)$ 较大的学生放在队列的前面，以最小化总不满意度。
3. **排序实现**：通过排序或优先队列实现贪心策略，确保较大的 $(a_i - b_i)$ 乘以较小的 $j$。

### 可拓展之处
类似的问题可以通过公式化简和贪心策略来解决，例如在任务调度、资源分配等问题中，通过优化目标函数的可变部分来达到最优解。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得摘录
- **作者：midsummer_zyl**：十年 OI 一场空，不开龙龙（`long long`）见祖宗。强调了在计算过程中使用 `long long` 的重要性。
- **作者：OYL2007**：原来错了好多遍，最后这里想了想，虽然运算和不会越界，但单个数据有越界的可能，如果不加的话其实会有一个点卡住。强调了在代码中处理数据溢出的重要性。

---
处理用时：31.57秒