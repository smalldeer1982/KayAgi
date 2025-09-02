# 题目信息

# Good Trip

## 题目描述

There are $ n $ children in a class, $ m $ pairs among them are friends. The $ i $ -th pair who are friends have a friendship value of $ f_i $ .

The teacher has to go for $ k $ excursions, and for each of the excursions she chooses a pair of children randomly, equiprobably and independently. If a pair of children who are friends is chosen, their friendship value increases by $ 1 $ for all subsequent excursions (the teacher can choose a pair of children more than once). The friendship value of a pair who are not friends is considered $ 0 $ , and it does not change for subsequent excursions.

Find the expected value of the sum of friendship values of all $ k $ pairs chosen for the excursions (at the time of being chosen). It can be shown that this answer can always be expressed as a fraction $ \dfrac{p}{q} $ where $ p $ and $ q $ are coprime integers. Calculate $ p\cdot q^{-1} \bmod (10^9+7) $ .

## 说明/提示

For the first test case, there are no pairs of friends, so the friendship value of all pairs is $ 0 $ and stays $ 0 $ for subsequent rounds, hence the friendship value for all excursions is $ 0 $ .

For the second test case, there is only one pair possible $ (1, 2) $ and its friendship value is initially $ 1 $ , so each turn they are picked and their friendship value increases by $ 1 $ . Therefore, the total sum is $ 1+2+3+\ldots+10 = 55 $ .

For the third test case, the final answer is $ \frac{7}{9} = 777\,777\,784\bmod (10^9+7) $ .

## 样例 #1

### 输入

```
4
100 0 24
2 1 10
1 2 1
3 1 2
2 1 1
5 2 4
1 2 25
3 2 24```

### 输出

```
0
55
777777784
40000020```

# AI分析结果

### 题目内容重写
# 美好的旅行

## 题目描述

一个班级中有 $n$ 个孩子，其中有 $m$ 对是朋友。第 $i$ 对朋友的友谊值为 $f_i$。

老师要进行 $k$ 次远足，每次远足时她会随机、等概率且独立地选择一对孩子。如果选中的是一对朋友，那么他们的友谊值会在后续的所有远足中增加 $1$（老师可能会多次选择同一对孩子）。如果选中的不是朋友，则他们的友谊值始终为 $0$，并且在后续远足中也不会改变。

求所有 $k$ 次远足中被选中的对的友谊值之和的期望值（在被选中时的值）。可以证明，答案总可以表示为分数 $\dfrac{p}{q}$，其中 $p$ 和 $q$ 是互质的整数。请计算 $p\cdot q^{-1} \bmod (10^9+7)$。

## 说明/提示

对于第一个测试用例，没有朋友对，因此所有对的友谊值始终为 $0$，故所有远足的友谊值之和为 $0$。

对于第二个测试用例，只有一对朋友 $(1, 2)$，他们的初始友谊值为 $1$，因此每次被选中时他们的友谊值都会增加 $1$。因此，总和为 $1+2+3+\ldots+10 = 55$。

对于第三个测试用例，最终答案为 $\frac{7}{9} = 777\,777\,784\bmod (10^9+7)$。

## 样例 #1

### 输入

```
4
100 0 24
2 1 10
1 2 1
3 1 2
2 1 1
5 2 4
1 2 25
3 2 24
```

### 输出

```
0
55
777777784
40000020
```

### 算法分类
概率论

### 题解分析与结论
该题目考察的是概率论中的期望计算，特别是动态期望的计算。题解的核心思路是通过分析每次远足对友谊值的影响，逐步推导出期望值的计算公式。大多数题解都采用了类似的方法，即通过计算每对朋友被选中的概率及其对总期望的贡献来求解。

### 所选高星题解
1. **题解作者：Diaоsi (赞：18)**  
   - **星级：5星**  
   - **关键亮点**：通过直观的期望递推公式，简洁地计算了每轮远足对期望值的影响。代码实现简洁，时间复杂度为 $O(n)$。  
   - **核心代码**：
     ```cpp
     for(int i=1;i<=k;i++)
         ans=(ans+sum*p%lpw)%lpw,
         sum=(sum+m*p%lpw)%lpw;
     ```
   - **实现思想**：通过循环每次远足，更新期望值和友谊值总和的期望。

2. **题解作者：Svemit (赞：11)**  
   - **星级：4星**  
   - **关键亮点**：从动态规划的角度出发，推导出期望值的递推公式，并通过组合数学的方法进行计算。  
   - **核心代码**：
     ```cpp
     for(int i = 0; i < k; i ++) {
         f = g + p * (s + m * (Z)i * p);
         g = f;
     }
     ```
   - **实现思想**：通过动态规划的方式，逐步计算每轮远足后的期望值。

3. **题解作者：Chazz (赞：0)**  
   - **星级：4星**  
   - **关键亮点**：通过数学推导，直接得出期望值的公式，避免了复杂的递推过程。  
   - **核心代码**：
     ```cpp
     ull s = ((k * to) % MOD + (m * (((k * (k - 1)) >> 1) % MOD) % MOD)) % MOD;
     cout << frac_mod(s, bo) << endl;
     ```
   - **实现思想**：通过数学公式直接计算期望值，减少了计算复杂度。

### 最优关键思路
最优的思路是通过数学推导直接得出期望值的公式，避免了复杂的递推过程。这种方法不仅简洁，而且计算效率高，适合在竞赛中使用。

### 拓展与举一反三
类似的问题可以考察动态期望的计算，特别是在每次操作后状态发生变化的情况下。例如，可以考虑每次操作后某些概率或期望值发生变化的问题。

### 推荐题目
1. [P1654 OSU!](https://www.luogu.com.cn/problem/P1654)  
2. [P4317 花神的数论题](https://www.luogu.com.cn/problem/P4317)  
3. [P1850 换教室](https://www.luogu.com.cn/problem/P1850)

---
处理用时：43.03秒