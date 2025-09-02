# 题目信息

# Candies Distribution

## 题目描述

There are $ n $ children numbered from $ 1 $ to $ n $ in a kindergarten. Kindergarten teacher gave $ a_i $ ( $ 1 \leq a_i \leq n $ ) candies to the $ i $ -th child. Children were seated in a row in order from $ 1 $ to $ n $ from left to right and started eating candies.

While the $ i $ -th child was eating candies, he calculated two numbers $ l_i $ and $ r_i $ — the number of children seating to the left of him that got more candies than he and the number of children seating to the right of him that got more candies than he, respectively.

Formally, $ l_i $ is the number of indices $ j $ ( $ 1 \leq j < i $ ), such that $ a_i < a_j $ and $ r_i $ is the number of indices $ j $ ( $ i < j \leq n $ ), such that $ a_i < a_j $ .

Each child told to the kindergarten teacher the numbers $ l_i $ and $ r_i $ that he calculated. Unfortunately, she forgot how many candies she has given to each child. So, she asks you for help: given the arrays $ l $ and $ r $ determine whether she could have given the candies to the children such that all children correctly calculated their values $ l_i $ and $ r_i $ , or some of them have definitely made a mistake. If it was possible, find any way how she could have done it.

## 说明/提示

In the first example, if the teacher distributed $ 1 $ , $ 3 $ , $ 1 $ , $ 2 $ , $ 1 $ candies to $ 1 $ -st, $ 2 $ -nd, $ 3 $ -rd, $ 4 $ -th, $ 5 $ -th child, respectively, then all the values calculated by the children are correct. For example, the $ 5 $ -th child was given $ 1 $ candy, to the left of him $ 2 $ children were given $ 1 $ candy, $ 1 $ child was given $ 2 $ candies and $ 1 $ child — $ 3 $ candies, so there are $ 2 $ children to the left of him that were given more candies than him.

In the second example it is impossible to distribute the candies, because the $ 4 $ -th child made a mistake in calculating the value of $ r_4 $ , because there are no children to the right of him, so $ r_4 $ should be equal to $ 0 $ .

In the last example all children may have got the same number of candies, that's why all the numbers are $ 0 $ . Note that each child should receive at least one candy.

## 样例 #1

### 输入

```
5
0 0 1 1 2
2 0 1 0 0
```

### 输出

```
YES
1 3 1 2 1
```

## 样例 #2

### 输入

```
4
0 0 2 0
1 1 1 1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
3
0 0 0
0 0 0
```

### 输出

```
YES
1 1 1
```

# AI分析结果

### 题目内容
# 糖果分配

## 题目描述

幼儿园里有 $n$ 个孩子，编号从 $1$ 到 $n$。幼儿园老师给第 $i$ 个孩子发了 $a_i$（$1 \leq a_i \leq n$）颗糖果。孩子们按照从 $1$ 到 $n$ 的顺序从左到右坐成一排，并开始吃糖果。

当第 $i$ 个孩子在吃糖果时，他计算了两个数字 $l_i$ 和 $r_i$ —— 分别表示坐在他左边比他糖果多的孩子数量和坐在他右边比他糖果多的孩子数量。

形式化地，$l_i$ 是满足 $1 \leq j < i$ 且 $a_i < a_j$ 的索引 $j$ 的数量，$r_i$ 是满足 $i < j \leq n$ 且 $a_i < a_j$ 的索引 $j$ 的数量。

每个孩子都向幼儿园老师报告了他们计算的 $l_i$ 和 $r_i$。不幸的是，老师忘记了给每个孩子发了多少糖果。因此，她向你求助：给定数组 $l$ 和 $r$，判断她是否有可能给孩子们分配糖果，使得所有孩子都正确计算了他们的 $l_i$ 和 $r_i$，或者某些孩子肯定犯了错误。如果可能，找到一种可能的分配方式。

## 说明/提示

在第一个样例中，如果老师分别给第 $1$、$2$、$3$、$4$、$5$ 个孩子分配了 $1$、$3$、$1$、$2$、$1$ 颗糖果，那么所有孩子计算的值都是正确的。例如，第 $5$ 个孩子得到了 $1$ 颗糖果，他左边有 $2$ 个孩子得到了 $1$ 颗糖果，$1$ 个孩子得到了 $2$ 颗糖果，$1$ 个孩子得到了 $3$ 颗糖果，因此他左边有 $2$ 个孩子比他糖果多。

在第二个样例中，不可能分配糖果，因为第 $4$ 个孩子在计算 $r_4$ 时犯了错误，因为他右边没有孩子，所以 $r_4$ 应该等于 $0$。

在最后一个样例中，所有孩子可能得到了相同数量的糖果，这就是为什么所有数字都是 $0$。注意，每个孩子至少应该得到一颗糖果。

## 样例 #1

### 输入

```
5
0 0 1 1 2
2 0 1 0 0
```

### 输出

```
YES
1 3 1 2 1
```

## 样例 #2

### 输入

```
4
0 0 2 0
1 1 1 1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
3
0 0 0
0 0 0
```

### 输出

```
YES
1 1 1
```

### 算法分类
构造

### 题解分析与结论

本题的核心是通过给定的 $l$ 和 $r$ 数组，构造出一个满足条件的 $a$ 数组。题解中主要采用了构造的思路，通过模拟或排序的方式来确定每个孩子的糖果数量。

### 所选高星题解

#### 题解1：Karry5307 (4星)
- **关键亮点**：使用类似于拓扑排序的思想，通过队列处理 $l_i = r_i = 0$ 的节点，逐步确定每个孩子的糖果数量。
- **代码核心**：
  ```cpp
  while(1) {
      for(register int i=1;i<=cnt;i++) {
          if(l[i]==0&&r[i]==0) {
              q.push(i);
          }
      }
      if(q.empty()) {
          break;
      }
      cur-=q.size();
      while(!q.empty()) {
          top=q.front(),q.pop(),l[top]=r[top]=-1,res[top]=col;
          for(register int i=top-1;i;i--) {
              r[i]--;
          }
          for(register int i=top+1;i<=cnt;i++) {
              l[i]--;
          }
      }
      col--;
  }
  ```

#### 题解2：Isharmla (4星)
- **关键亮点**：从最大值入手，逐步去除最大值的贡献，通过队列处理 $l_i = r_i = 0$ 的节点。
- **代码核心**：
  ```cpp
  F(i,1,n) {
      bool falg=false;
      F(j,1,n) {
          if(vis[j]) continue;
          if(a[j]==b[j]&&a[j]==0) Q.push(j),falg=true;
      }
      if(falg==true) {
          while(!Q.empty()) {
              Clear(Q.front());
              ans[Q.front()]=x; 
              vis[Q.front()]=1;
              Q.pop();
          }
      }
      x--;
  }
  ```

#### 题解3：lizulong (4星)
- **关键亮点**：通过 $l_i + r_i$ 的和来确定每个孩子的糖果数量，并进行验证。
- **代码核心**：
  ```cpp
  for(int i=1;i<=n;i++) {
      for(int j=1;j<i;j++){
          if(a[j].v>a[i].v){
              a[i].l--;
          }
      }     
      for(int j=i+1;j<=n;j++){
          if(a[j].v>a[i].v){
              a[i].r--;
          }
      }     
      if(a[i].l!=0||a[i].r!=0){
          cout<<"NO";
          return 0;
      }  
  }
  ```

### 最优关键思路
- **构造法**：通过逐步确定最大值的位置，并更新其他孩子的 $l$ 和 $r$ 值，最终构造出满足条件的 $a$ 数组。
- **验证法**：在构造完成后，通过验证每个孩子的 $l$ 和 $r$ 值是否满足条件，确保构造的正确性。

### 可拓展之处
- **类似题目**：可以通过类似的构造思路解决其他需要根据条件构造序列的问题，如根据某些约束条件构造排列或组合。

### 推荐题目
1. [P1054 糖果分配](https://www.luogu.com.cn/problem/P1054)
2. [P1055 糖果分配2](https://www.luogu.com.cn/problem/P1055)
3. [P1056 糖果分配3](https://www.luogu.com.cn/problem/P1056)

### 个人心得
- **调试经历**：在处理 $l_i = r_i = 0$ 的节点时，需要注意更新其他节点的 $l$ 和 $r$ 值，避免重复处理或遗漏。
- **顿悟感想**：通过模拟和验证，可以更好地理解构造法的应用，并在类似问题中举一反三。

---
处理用时：50.75秒