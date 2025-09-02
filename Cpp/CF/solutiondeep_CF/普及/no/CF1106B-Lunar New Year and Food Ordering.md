# 题目信息

# Lunar New Year and Food Ordering

## 题目描述

Lunar New Year is approaching, and Bob is planning to go for a famous restaurant — "Alice's".

The restaurant "Alice's" serves $ n $ kinds of food. The cost for the $ i $ -th kind is always $ c_i $ . Initially, the restaurant has enough ingredients for serving exactly $ a_i $ dishes of the $ i $ -th kind. In the New Year's Eve, $ m $ customers will visit Alice's one after another and the $ j $ -th customer will order $ d_j $ dishes of the $ t_j $ -th kind of food. The $ (i + 1) $ -st customer will only come after the $ i $ -th customer is completely served.

Suppose there are $ r_i $ dishes of the $ i $ -th kind remaining (initially $ r_i = a_i $ ). When a customer orders $ 1 $ dish of the $ i $ -th kind, the following principles will be processed.

1. If $ r_i > 0 $ , the customer will be served exactly $ 1 $ dish of the $ i $ -th kind. The cost for the dish is $ c_i $ . Meanwhile, $ r_i $ will be reduced by $ 1 $ .
2. Otherwise, the customer will be served $ 1 $ dish of the cheapest available kind of food if there are any. If there are multiple cheapest kinds of food, the one with the smallest index among the cheapest will be served. The cost will be the cost for the dish served and the remain for the corresponding dish will be reduced by $ 1 $ .
3. If there are no more dishes at all, the customer will leave angrily. Therefore, no matter how many dishes are served previously, the cost for the customer is $ 0 $ .

If the customer doesn't leave after the $ d_j $ dishes are served, the cost for the customer will be the sum of the cost for these $ d_j $ dishes.

Please determine the total cost for each of the $ m $ customers.

## 说明/提示

In the first sample, $ 5 $ customers will be served as follows.

1. Customer $ 1 $ will be served $ 6 $ dishes of the $ 2 $ -nd kind, $ 1 $ dish of the $ 4 $ -th kind, and $ 1 $ dish of the $ 6 $ -th kind. The cost is $ 6 \cdot 3 + 1 \cdot 2 + 1 \cdot 2 = 22 $ . The remain of the $ 8 $ kinds of food will be $ \{8, 0, 2, 0, 4, 4, 7, 5\} $ .
2. Customer $ 2 $ will be served $ 4 $ dishes of the $ 1 $ -st kind. The cost is $ 4 \cdot 6 = 24 $ . The remain will be $ \{4, 0, 2, 0, 4, 4, 7, 5\} $ .
3. Customer $ 3 $ will be served $ 4 $ dishes of the $ 6 $ -th kind, $ 3 $ dishes of the $ 8 $ -th kind. The cost is $ 4 \cdot 2 + 3 \cdot 2 = 14 $ . The remain will be $ \{4, 0, 2, 0, 4, 0, 7, 2\} $ .
4. Customer $ 4 $ will be served $ 2 $ dishes of the $ 3 $ -rd kind, $ 2 $ dishes of the $ 8 $ -th kind. The cost is $ 2 \cdot 3 + 2 \cdot 2 = 10 $ . The remain will be $ \{4, 0, 0, 0, 4, 0, 7, 0\} $ .
5. Customer $ 5 $ will be served $ 7 $ dishes of the $ 7 $ -th kind, $ 3 $ dishes of the $ 1 $ -st kind. The cost is $ 7 \cdot 3 + 3 \cdot 6 = 39 $ . The remain will be $ \{1, 0, 0, 0, 4, 0, 0, 0\} $ .

In the second sample, each customer is served what they order except the last one, who leaves angrily without paying. For example, the second customer is served $ 6 $ dishes of the second kind, so the cost is $ 66 \cdot 6 = 396 $ .

In the third sample, some customers may not be served what they order. For example, the second customer is served $ 6 $ dishes of the second kind, $ 6 $ of the third and $ 1 $ of the fourth, so the cost is $ 66 \cdot 6 + 666 \cdot 6 + 6666 \cdot 1 = 11058 $ .

## 样例 #1

### 输入

```
8 5
8 6 2 1 4 5 7 5
6 3 3 2 6 2 3 2
2 8
1 4
4 7
3 4
6 10
```

### 输出

```
22
24
14
10
39
```

## 样例 #2

### 输入

```
6 6
6 6 6 6 6 6
6 66 666 6666 66666 666666
1 6
2 6
3 6
4 6
5 6
6 66
```

### 输出

```
36
396
3996
39996
399996
0
```

## 样例 #3

### 输入

```
6 6
6 6 6 6 6 6
6 66 666 6666 66666 666666
1 6
2 13
3 6
4 11
5 6
6 6
```

### 输出

```
36
11058
99996
4333326
0
0
```

# AI分析结果

### 题目内容重写

#### 题目描述

春节即将来临，Bob计划去一家著名的餐厅——“Alice's”。

餐厅“Alice's”提供 $n$ 种食物。第 $i$ 种食物的价格始终为 $c_i$。最初，餐厅有足够的食材来提供恰好 $a_i$ 份第 $i$ 种食物。在除夕夜，$m$ 位顾客将依次光顾Alice's，第 $j$ 位顾客将点 $d_j$ 份第 $t_j$ 种食物。第 $(i + 1)$ 位顾客只有在第 $i$ 位顾客完全被服务后才会到来。

假设第 $i$ 种食物剩余 $r_i$ 份（初始时 $r_i = a_i$）。当顾客点 $1$ 份第 $i$ 种食物时，将按照以下原则进行处理：

1. 如果 $r_i > 0$，顾客将得到 $1$ 份第 $i$ 种食物。该份食物的价格为 $c_i$。同时，$r_i$ 将减少 $1$。
2. 否则，顾客将得到 $1$ 份最便宜的可用食物（如果有的话）。如果有多个最便宜的食物，将选择其中编号最小的。价格为所提供食物的价格，相应食物的剩余份数将减少 $1$。
3. 如果没有任何食物剩余，顾客将愤怒地离开。因此，无论之前提供了多少份食物，顾客的费用为 $0$。

如果顾客在 $d_j$ 份食物被提供后没有离开，顾客的费用将是这些 $d_j$ 份食物的总价格。

请确定每位 $m$ 位顾客的总费用。

### 算法分类
模拟

### 题解分析与结论

#### 题解1：qnickx (赞：3)
- **星级**：4
- **关键亮点**：使用优先队列来动态维护最便宜的食物，实时更新食物的剩余数量，确保每次都能快速找到最便宜的食物。
- **核心代码**：
  ```cpp
  priority_queue< pair<ll,ll> > q;
  for(register int i=1;i<=n;i++) {
      q.push(make_pair(-c[i],(ll)i));
  }
  ```
  **实现思想**：通过优先队列存储食物的价格和编号，每次顾客点餐时，优先从队列中取出最便宜的食物进行服务。

#### 题解2：Anguei (赞：2)
- **星级**：4
- **关键亮点**：使用`map`来简化代码，排序后直接通过`map`查找食物的位置，减少了查找时间。
- **核心代码**：
  ```cpp
  std::map<int, int> map;
  rep(i, 1, n) map[x[i].id] = i;
  ```
  **实现思想**：通过`map`存储排序后的食物位置，快速定位顾客点餐的食物。

#### 题解3：DengDuck (赞：0)
- **星级**：4
- **关键亮点**：使用排序和指针来快速找到最便宜的食物，减少了查找时间，代码简洁明了。
- **核心代码**：
  ```cpp
  sort(a+1,a+n+1,cmp);
  for(int i=1;i<=n;i++)b[a[i].num]=i;
  ```
  **实现思想**：通过排序和指针维护最便宜的食物，确保每次都能快速找到最便宜的食物。

### 最优关键思路或技巧
1. **优先队列**：使用优先队列来动态维护最便宜的食物，确保每次都能快速找到最便宜的食物。
2. **排序与指针**：通过排序和指针来快速找到最便宜的食物，减少了查找时间。
3. **`map`优化**：使用`map`来简化代码，快速定位顾客点餐的食物。

### 可拓展之处
1. **动态维护数据结构**：在处理动态数据时，优先队列和`map`是非常有用的数据结构，可以应用于其他需要动态维护最小或最大值的场景。
2. **排序与指针**：在处理需要快速查找的场景时，排序和指针的组合可以大大提高效率。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P3378 【模板】堆](https://www.luogu.com.cn/problem/P3378)
3. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)

---
处理用时：30.98秒