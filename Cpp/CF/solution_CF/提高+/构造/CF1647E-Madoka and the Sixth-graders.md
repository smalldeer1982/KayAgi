# Madoka and the Sixth-graders

## 题目描述

After the most stunning success with the fifth-graders, Madoka has been trusted with teaching the sixth-graders.

There's $ n $ single-place desks in her classroom. At the very beginning Madoka decided that the student number $ b_i $ ( $ 1 \le b_i \le n $ ) will sit at the desk number $ i $ . Also there's an infinite line of students with numbers $ n + 1, n + 2, n + 3, \ldots $ waiting at the door with the hope of being able to learn something from the Madoka herself. Pay attention that each student has his unique number.

After each lesson, the following happens in sequence.

1. The student sitting at the desk $ i $ moves to the desk $ p_i $ . All students move simultaneously.
2. If there is more than one student at a desk, the student with the lowest number keeps the place, and the others are removed from the class forever.
3. For all empty desks in ascending order, the student from the lowest number from the outside line occupies the desk.

Note that in the end there is exactly one student at each desk again. It is guaranteed that the numbers $ p $ are such that at least one student is removed after each lesson. Check out the explanation to the first example for a better understanding.

After several (possibly, zero) lessons the desk $ i $ is occupied by student $ a_i $ . Given the values $ a_1, a_2, \ldots, a_n $ and $ p_1, p_2, \ldots, p_n $ , find the lexicographically smallest suitable initial seating permutation $ b_1, b_2, \ldots, b_n $ .

The permutation is an array of $ n $ different integers from $ 1 $ up to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not ( $ 2 $ occurs twice). $ [1,3,4] $ is not a permutation either ( $ n=3 $ but there's $ 4 $ in the array).

For two different permutations $ a $ and $ b $ of the same length, $ a $ is lexicographically less than $ b $ if in the first position where $ a $ and $ b $ differ, the permutation $ a $ has a smaller element than the corresponding element in $ b $ .

## 说明/提示

The description of the first test is below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647E/450e6be80f3badec1beedf83f6c6ee41726c92be.png)The first picture shows the starting permutation, which is the answer. Then the students sitting at desks $ 1, 2 $ are transferred to a $ 5 $ desk. Also, a $ 1 $ student moved from a $ 5 $ desk, and a student from a $ 4 $ disk is transferred to a $ 3 $ desk.

Thus, after all these transfers permutation shown in the second image is obtained. Then, at the desk with the number $ 5 $ , the student with the number $ 3 $ is expelled, and at the desk with the number $ 3 $ , the student with the number $ 5 $ is expelled. (Since their numbers are not the smallest) Then new students with numbers $ 6, 7 $ sit at desks numbered $ 2, 4 $ . And this permutation (after the end of the first lesson) is shown in the third image.

The $ 4 $ image shows the seating arrangement, after the second lesson before all the extra ones were kicked out. And the fifth shows the final seating after $ 2 $ lesson.

## 样例 #1

### 输入

```
5
5 5 3 3 1
1 8 2 9 4```

### 输出

```
1 3 2 5 4```

## 样例 #2

### 输入

```
5
1 3 2 5 2
3 2 5 4 1```

### 输出

```
3 2 5 4 1```

## 样例 #3

### 输入

```
10
10 8 5 3 7 8 6 6 1 1
5 26 24 27 21 4 18 2 28 1```

### 输出

```
5 4 2 6 7 8 3 9 1 10```

# 题解

## 作者：Rad_Forever (赞：4)

[题目链接](https://www.luogu.com.cn/problem/CF1647E)

### 思路

思路与官方题解一样。

考虑到如果 $p$ 不是一个排列，那么一个变化后必然产生新数字 **且每次产生的数字数量是固定的**，计 $maxn=\max\{a_i\}$，$turn=\dfrac{maxn-n}{cnt}$ 即可计算出变化轮次，其中 $cnt$ 表示每一次变化后产生新数字的数量。

接下来考虑怎么最小化初始排列。

考虑到变化次数已知，那么我们直接用倍增处理每一个位置执行 $turn$ 次变化后的位置。

```cpp
for(int j=1;j<=30;++j)
	for(int i=1;i<=n;++i)
		anc[i][j]=anc[anc[i][j-1]][j-1];
for(int i=1;i<=n;++i){
	Getpos[i]=i;
	for(int j=0;j<=30;++j){
		if(turn & (1ll<<j)) Getpos[i]=anc[Getpos[i]][j];
	}
}

```

对于位置 $i$，变化 $turn$ 次后到达 $pos_i$ 的位置。

那么为了使得答案字典序最小，可以使用贪心。

如果我们将 $pos_i=k$ 的 $i$ 作为集合 $S_k$ 的话，那么我们必然有 $b_{\min S_i}=a_{i}$，这里可以自己思考。

接下来将 $a_i \leq n$ 且 $a_i$ 尚且没有存在与 $b$ 中的放入 STL 中的 set。对于每一个没有确定的位置直接二分即可。

[评测记录](https://codeforces.live/contest/1647/submission/149317915)

---

## 作者：WRuperD (赞：1)

### CF1647E
好题！

不难注意到每一轮次新增人数固定，所以我们可以简单算出一共进行了多少轮。

然后转换一下思路，把踢掉人的操作看作保留，但是最后集合内显示出的是当前桌子人集合中编号最小的那个人。于是我们考虑每一个位置上的数初始最后会在这么多轮后去到哪个位置。这个可以通过倍增预处理。

从 1 到 $n$ 贪心地填。对于出现在最终序列中的数，我们看哪些初始位置可以到达最终其所在的位置（注意这些位置在之前一定是空着的），贪心地填向最前面的位置。对于没出现在最终序列中的数，我们把它填在当前可以填的位置的最前的那个位置即可。

---

## 作者：yllcm (赞：0)

为啥官方题解是 $O(n\log n)$ 的啊。给个 $O(n\alpha(n))$ 做法。

显然我们可以通过最终序列的最大值和每次减少数的数量确定操作的轮数。

可以说明原序列的形态完全取决于最终序列的 $a_i\leq n$ 的数的排列形态，即我们只需要关注这些位置的值。因为对于 $a_i\leq n$ 和 $a_i>n$ 的数，可以把它们看成 $0$ 和 $1$，显然形态是确定的。每次操作加入数的位置和顺序都是相同的，所以 $1$ 内部的顺序也是确定的。于是我们只需要关注剩下的数。

可以把操作看成每次操作后并不删除，转移看做一个集合的继承，最后这个位置的答案就是集合内的所有数取 $\min$。于是我们用一些方法求出所有位置最终被转移到什么地方，那么最终序列带来的约束就是原序列中一些位置的 $\min$ 值为某个确定的值。我们把每个约束的最小值填到满足要求的编号最小的位置，剩下位置从前往后用并查集找到合法的最小值即可。

https://codeforces.com/contest/1647/submission/149897614



---

