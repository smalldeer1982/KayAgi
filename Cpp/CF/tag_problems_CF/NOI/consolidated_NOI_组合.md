---
title: "AmShZ Farm"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1528F
tag: ['组合数学', 'Stirling 数']
---

# AmShZ Farm

## 题目描述

To AmShZ, all arrays are equal, but some arrays are more-equal than others. Specifically, the arrays consisting of $ n $ elements from $ 1 $ to $ n $ that can be turned into permutations of numbers from $ 1 $ to $ n $ by adding a non-negative integer to each element.

Mashtali who wants to appear in every problem statement thinks that an array $ b $ consisting of $ k $ elements is compatible with a more-equal array $ a $ consisting of $ n $ elements if for each $ 1 \le i \le k $ we have $ 1 \le b_i \le n $ and also $ a_{b_1} = a_{b_2} = \ldots = a_{b_k} $ .

Find the number of pairs of arrays $ a $ and $ b $ such that $ a $ is a more-equal array consisting of $ n $ elements and $ b $ is an array compatible with $ a $ consisting of $ k $ elements modulo $ 998244353 $ .

Note that the elements of $ b $ are not necessarily distinct, same holds for $ a $ .

## 输入格式

The first line of input contains two integers $ n $ and $ k $ $ (1 \le n \le 10^9 , 1 \le k \le 10^5) $ .

## 输出格式

Print a single integer — the answer to the problem modulo $ 998244353 $ .

## 说明/提示

There are eight possible pairs for the second example:

1. $ a = \{1, 1\}, b = \{1, 1\} $
2. $ a = \{1, 1\}, b = \{1, 2\} $
3. $ a = \{1, 1\}, b = \{2, 1\} $
4. $ a = \{1, 1\}, b = \{2, 2\} $
5. $ a = \{1, 2\}, b = \{1, 1\} $
6. $ a = \{1, 2\}, b = \{2, 2\} $
7. $ a = \{2, 1\}, b = \{1, 1\} $
8. $ a = \{2, 1\}, b = \{2, 2\} $

## 样例 #1

### 输入

```
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
8
```

## 样例 #3

### 输入

```
5 4
```

### 输出

```
50400
```

## 样例 #4

### 输入

```
20 100
```

### 输出

```
807645526
```

## 样例 #5

### 输入

```
10000000 10000
```

### 输出

```
883232350
```



---

---
title: "PalindORme"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1605F
tag: ['动态规划 DP', '组合数学']
---

# PalindORme

## 题目描述

An integer array $ a $ of length $ n $ is said to be a PalindORme if ( $ a_{1} $ $ | $ $ a_{2}  $ $ | $ $  \ldots  $ $ | $ $  a_{i}) = (a_{{n - i + 1}}  $ $ | $ $  \ldots  $ $ | $ $  a_{{n - 1}}  $ $ | $ $  a_{n})  $ for all $  1 \leq i \leq n $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

An integer array $ a $ of length $ n $ is considered to be good if its elements can be rearranged to form a PalindORme. Formally, array $ a $ is good if there exists a permutation $ p_1, p_2, \ldots p_n $ (an array where each integer from $ 1 $ to $ n $ appears exactly once) for which $ a_{p_1}, a_{p_2}, \ldots a_{p_n} $ is a PalindORme.

Find the number of good arrays of length $ n $ , consisting only of integers in the range $ [0, 2^{k} - 1] $ , and print it modulo some prime $ m $ .

Two arrays $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ are considered to be different if there exists any $ i $ $ (1 \leq i \leq n) $ such that $ a_i \ne b_i $ .

## 输入格式

The first and only line of the input contains three integers $ n $ , $ k $ and $ m $ ( $ 1 \leq n,k \leq 80 $ , $ 10^8 \lt m \lt 10^9 $ ). It is guaranteed that $ m $ is prime.

## 输出格式

Print a single integer — the number of good arrays modulo $ m $ .

## 说明/提示

In the first sample, both the possible arrays $ [0] $ and $ [1] $ are good.

In the second sample, some examples of good arrays are:

- $ [2, 1, 2] $ because it is already PalindORme.
- $ [1, 1, 0] $ because it can rearranged to $ [1, 0, 1] $ which is PalindORme

Note that $ [1, 1, 0] $ , $ [1, 0, 1] $ and $ [0, 1, 1] $ are all good arrays and are considered to be different according to the definition in the statement.

In the third sample, an example of a good array is $ [1, 0, 1, 4, 2, 5, 4] $ . It can be rearranged to an array $ b = [1, 5, 0, 2, 4, 4, 1] $ which is a PalindORme because:

- $ \mathrm{OR}(1, 1) $ = $ \mathrm{OR}(7, 7) $ = $ 1 $
- $ \mathrm{OR}(1, 2) $ = $ \mathrm{OR}(6, 7) $ = $ 5 $
- $ \mathrm{OR}(1, 3) $ = $ \mathrm{OR}(5, 7) $ = $ 5 $
- $ \mathrm{OR}(1, 4) $ = $ \mathrm{OR}(4, 7) $ = $ 7 $
- $ \mathrm{OR}(1, 5) $ = $ \mathrm{OR}(3, 7) $ = $ 7 $
- $ \mathrm{OR}(1, 6) $ = $ \mathrm{OR}(2, 7) $ = $ 7 $
- $ \mathrm{OR}(1, 7) $ = $ \mathrm{OR}(1, 7) $ = $ 7 $

Here $ \mathrm{OR}(l, r) $ denotes $ b_{l} $ $ | $ $ b_{l+1}  $ $ | $ $  \ldots  $ $ | $ $  b_{r} $

## 样例 #1

### 输入

```
1 1 998244353
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 2 999999733
```

### 输出

```
40
```

## 样例 #3

### 输入

```
7 3 796735397
```

### 输出

```
1871528
```

## 样例 #4

### 输入

```
2 46 606559127
```

### 输出

```
177013
```



---

---
title: "Doping"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1750G
tag: ['组合数学', '容斥原理']
---

# Doping

## 题目描述

We call an array $ a $ of length $ n $ fancy if for each $ 1 < i \le n $ it holds that $ a_i = a_{i-1} + 1 $ .

Let's call $ f(p) $ applied to a permutation $ ^\dagger $ of length $ n $ as the minimum number of subarrays it can be partitioned such that each one of them is fancy. For example $ f([1,2,3]) = 1 $ , while $ f([3,1,2]) = 2 $ and $ f([3,2,1]) = 3 $ .

Given $ n $ and a permutation $ p $ of length $ n $ , we define a permutation $ p' $ of length $ n $ to be $ k $ -special if and only if:

- $ p' $ is lexicographically smaller $ ^\ddagger $ than $ p $ , and
- $ f(p') = k $ .

Your task is to count for each $ 1 \le k \le n $ the number of $ k $ -special permutations modulo $ m $ .

 $ ^\dagger $ A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 $ ^\ddagger $ A permutation $ a $ of length $ n $ is lexicographically smaller than a permutation $ b $ of length $ n $ if and only if the following holds: in the first position where $ a $ and $ b $ differ, the permutation $ a $ has a smaller element than the corresponding element in $ b $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 2000 $ , $ 10 \le m \le 10^9 $ ) — the length of the permutation and the required modulo.

The second line contains $ n $ distinct integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \le p_i \le n $ ) — the permutation $ p $ .

## 输出格式

Print $ n $ integers, where the $ k $ -th integer is the number of $ k $ -special permutations modulo $ m $ .

## 说明/提示

In the first example, the permutations that are lexicographically smaller than $ [1,3,4,2] $ are:

- $ [1,2,3,4] $ , $ f([1,2,3,4])=1 $ ;
- $ [1,2,4,3] $ , $ f([1,2,4,3])=3 $ ;
- $ [1,3,2,4] $ , $ f([1,3,2,4])=4 $ .

Thus our answer is $ [1,0,1,1] $ .

In the second example, the permutations that are lexicographically smaller than $ [3,2,1] $ are:

- $ [1,2,3] $ , $ f([1,2,3])=1 $ ;
- $ [1,3,2] $ , $ f([1,3,2])=3 $ ;
- $ [2,1,3] $ , $ f([2,1,3])=3 $ ;
- $ [2,3,1] $ , $ f([2,3,1])=2 $ ;
- $ [3,1,2] $ , $ f([3,1,2])=2 $ .

Thus our answer is $ [1,2,2] $ .

## 样例 #1

### 输入

```
4 666012
1 3 4 2
```

### 输出

```
1 0 1 1
```

## 样例 #2

### 输入

```
3 10
3 2 1
```

### 输出

```
1 2 2
```

## 样例 #3

### 输入

```
7 1000000000
7 2 1 3 5 4 6
```

### 输出

```
1 6 40 201 705 1635 1854
```

## 样例 #4

### 输入

```
10 11
10 9 8 7 6 5 4 3 2 1
```

### 输出

```
1 9 9 0 1 5 5 0 1 0
```



---

---
title: "Segment Covering"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1774G
tag: ['倍增', '最近公共祖先 LCA', '组合数学', '容斥原理']
---

# Segment Covering

## 题目描述

ChthollyNotaSeniorious gives DataStructures a number axis with $ m $ distinct segments on it. Let $ f(l,r) $ be the number of ways to choose an even number of segments such that the union of them is exactly $ [l,r] $ , and $ g(l,r) $ be the number of ways to choose an odd number of segments such that the union of them is exactly $ [l,r] $ .

ChthollyNotaSeniorious asked DataStructures $ q $ questions. In each query, ChthollyNotaSeniorious will give DataStructures two numbers $ l, r $ , and now he wishes that you can help him find the value $ f(l,r)-g(l,r) $ modulo $ 998\,244\,353 $ so that he wouldn't let her down.

## 输入格式

The first line of input contains two integers $ m $ ( $ 1 \leq m \leq 2 \cdot 10^5 $ ) and $ q $ ( $ 1 \leq q \leq 2 \cdot 10^5 $ ) — the number of segments and queries, correspondingly.

The $ i $ -th of the next $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 1 \leq x_i < y_i \leq 10^9 $ ), denoting a segment $ [x_i, y_i] $ .

It is guaranteed that all segments are distinct. More formally, there do not exist two numbers $ i, j $ with $ 1 \le i < j \le m $ such that $ x_i = x_j $ and $ y_i = y_j $ .

The $ i $ -th of the next $ q $ lines contains two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i < r_i \leq 10^9 $ ), describing a query.

## 输出格式

For each query, output a single integer — $ f(l_i,r_i)-g(l_i,r_i) $ modulo $ 998\,244\,353 $ .

## 说明/提示

In the first query, we have to find $ f(1, 4) - g(1, 4) $ . The only subset of segments with union $ [1, 4] $ is $ \{[1, 3], [2, 4]\} $ , so $ f(1, 4) = 1, g(1, 4) = 0 $ .

In the second query, we have to find $ f(1, 5) - g(1, 5) $ . The only subsets of segments with union $ [1, 5] $ are $ \{[1, 3], [2, 4], [3, 5]\} $ and $ \{[1, 3], [3, 5]\} $ , so $ f(1, 5) = 1, g(1, 5) = 1 $ .

## 样例 #1

### 输入

```
4 2
1 3
4 6
2 4
3 5
1 4
1 5
```

### 输出

```
1
0
```



---

---
title: "Graph Coloring (hard version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1792F2
tag: ['动态规划 DP', '图论', '组合数学', '快速数论变换 NTT']
---

# Graph Coloring (hard version)

## 题目描述

The only difference between the easy and the hard version is the constraint on $ n $ .

You are given an undirected complete graph on $ n $ vertices. A complete graph is a graph where each pair of vertices is connected by an edge. You have to paint the edges of the graph into two colors, red and blue (each edge will have one color).

A set of vertices $ S $ is red-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through red edges and vertices from $ S $ . Similarly, a set of vertices $ S $ is blue-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through blue edges and vertices from $ S $ .

You have to paint the graph in such a way that:

- there is at least one red edge;
- there is at least one blue edge;
- for each set of vertices $ S $ such that $ |S| \ge 2 $ , $ S $ is either red-connected or blue-connected, but not both.

Calculate the number of ways to paint the graph, and print it modulo $ 998244353 $ .

## 输入格式

The first (and only) line contains one integer $ n $ ( $ 3 \le n \le 5 \cdot 10^4 $ ).

## 输出格式

Print one integer — the number of ways to paint the graph, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
```

### 输出

```
50
```

## 样例 #3

### 输入

```
100
```

### 输出

```
878752271
```

## 样例 #4

### 输入

```
1337
```

### 输出

```
520628749
```

## 样例 #5

### 输入

```
42013
```

### 输出

```
906821221
```



---

---
title: "Quantifier"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2081E
tag: ['动态规划 DP', '组合数学']
---

# Quantifier

## 题目描述

给定一棵包含 $n+1$ 个节点的有根树，节点编号为 $0$ 到 $n$，其中根节点为 $0$，其唯一的子节点是 $1$。现有 $m$ 个不同芯片，编号为 $1$ 到 $m$，每个芯片颜色为黑色或白色。初始时，这些芯片按编号升序从上到下排列在边 $(0,1)$ 上。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2081E/58bf900e143672111ffad5778f71f85a1474d17a.png) 

芯片的初始位置。树节点以蓝色显示。你可以按任意顺序执行以下操作任意次（包括零次）：
1. 选择两条边 $(u,v)$ 和 $(v,w)$，其中 $u$ 是 $v$ 的父节点，$v$ 是 $w$ 的父节点，且边 $(u,v)$ 上至少有一个芯片。将边 $(u,v)$ 上的最底部芯片移动到边 $(v,w)$ 的最顶部位置（即置于该边所有现有芯片之上）。
2. 选择两条边 $(u,v)$ 和 $(v,w)$，其中 $u$ 是 $v$ 的父节点，$v$ 是 $w$ 的父节点，且边 $(v,w)$ 上至少有一个芯片。将边 $(v,w)$ 上的最顶部芯片移动到边 $(u,v)$ 的最底部位置（即置于该边所有现有芯片之下）。
3. 选择同一边上两个相邻的同色芯片，交换它们的位置。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2081E/6b3fd794319ff8c895e98bf884db81759bf5fe7e.png) 

允许的操作。每个芯片 $i$ 有一个移动范围，定义为从根节点到节点 $d_i$ 的简单路径上的所有边。操作过程中必须确保没有芯片被移动到其移动范围之外的边上。

最终，你需要将所有芯片移回边 $(0,1)$。可以发现芯片的顺序可能发生变化。请计算最终边 $(0,1)$ 上芯片排列的可能方案数对 $998\,244\,353$ 取模的结果。

芯片的排列定义为从顶到底的芯片编号组成的长度为 $m$ 的序列。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 5000$）。接下来描述每个测试用例。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$1 \le n, m \le 5000$）——树的大小减一（即树有 $n+1$ 个节点）和芯片数量。

第二行包含 $n$ 个整数 $p_1, p_2, \ldots, p_n$（$0 \le p_i < i$）——节点 $1$ 到 $n$ 的父节点。保证当且仅当 $i=1$ 时 $p_i = 0$（根的唯一子节点是 $1$）。

第三行包含 $m$ 个整数 $c_1, c_2, \ldots, c_m$（$c_i \in \{0, 1\}$）——每个芯片的颜色（$0$ 表示黑色，$1$ 表示白色）。

第四行包含 $m$ 个整数 $d_1, d_2, \ldots, d_m$（$1 \le d_i \le n$）——每个芯片的移动范围。

保证所有测试用例的 $n$ 总和不超过 $5000$，$m$ 总和不超过 $5000$。

## 输出格式

对于每个测试用例，输出一个整数——可能排列数对 $998\,244\,353$ 取模的结果。


## 说明/提示

第一个测试用例中，可以达成 $2$ 种排列：(1,2) 和 (2,1)。

第二个测试用例中，可以达成 $8$ 种排列：(1,2,3,4)、(1,2,4,3)、(1,3,2,4)、(1,3,4,2)、(1,4,2,3)、(1,4,3,2)、(2,1,3,4) 和 (2,1,4,3)。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3 2
0 1 1
0 1
2 3
4 4
0 1 1 2
0 0 1 1
1 2 3 3
6 6
0 1 1 1 4 5
0 0 0 0 1 1
5 6 1 2 4 3
16 15
0 1 1 3 1 3 4 3 3 7 1 6 11 5 8 10
1 0 1 1 0 1 1 1 1 0 1 1 0 0 0
12 14 13 10 9 16 11 14 13 15 16 10 2 2 5
```

### 输出

```
2
8
108
328459046
```



---

---
title: "Student's Camp"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF708E
tag: ['动态规划 DP', '排列组合']
---

# Student's Camp

## 题目描述

Alex studied well and won the trip to student camp Alushta, located on the seashore.

Unfortunately, it's the period of the strong winds now and there is a chance the camp will be destroyed! Camp building can be represented as the rectangle of $ n+2 $ concrete blocks height and $ m $ blocks width.

Every day there is a breeze blowing from the sea. Each block, except for the blocks of the upper and lower levers, such that there is no block to the left of it is destroyed with the probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/422afcf1e06a5628bae49992f52449e3f10a781f.png). Similarly, each night the breeze blows in the direction to the sea. Thus, each block (again, except for the blocks of the upper and lower levers) such that there is no block to the right of it is destroyed with the same probability $ p $ . Note, that blocks of the upper and lower level are indestructible, so there are only $ n·m $ blocks that can be destroyed.

The period of the strong winds will last for $ k $ days and $ k $ nights. If during this period the building will split in at least two connected components, it will collapse and Alex will have to find another place to spend summer.

Find the probability that Alex won't have to look for other opportunities and will be able to spend the summer in this camp.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=1500 $ ) that define the size of the destructible part of building.

The second line of the input contains two integers $ a $ and $ b $ ( $ 1<=a<=b<=10^{9} $ ) that define the probability $ p $ . It's guaranteed that integers $ a $ and $ b $ are coprime.

The third line contains a single integer $ k $ ( $ 0<=k<=100000 $ ) — the number of days and nights strong wind will blow for.

## 输出格式

Consider the answer as an irreducible fraction is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/80a3a0e00c79b470772b3be90efd3e0d2e457bd7.png). Print one integer equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/554b30b982e35fb63eb76dd412a37e11659c08f3.png). It's guaranteed that within the given constraints ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/7e61bb4a29a39d49b7ec2c70e2cceae658d627bd.png).

## 说明/提示

In the first sample, each of the four blocks is destroyed with the probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/fda96725ccc697b767e5edbf0d5cfb5ba17d9aa2.png). There are $ 7 $ scenarios that result in building not collapsing, and the probability we are looking for is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/dda8ba13f4feb6c7325a04d07cb771a7084c4ba2.png), so you should print ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/823f9bb4d7539823cd6e4037b4f9a35cb2e52f03.png)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/2ecb6c84ea76dfa6c7235391533a743f1c25b7f8.png)

## 样例 #1

### 输入

```
2 2
1 2
1

```

### 输出

```
937500007

```

## 样例 #2

### 输入

```
5 1
3 10
1

```

### 输出

```
95964640

```

## 样例 #3

### 输入

```
3 3
1 10
5

```

### 输出

```
927188454

```



---

