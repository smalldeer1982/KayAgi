# 题目信息

# [USACO09MAR] Moon Mooing G

## 题目描述

A full moon casts some sort of spell on the cows and, like their cousins the wolves and coyotes, they bay at the moon -- mooing instead of howling, of course.

Each 'moo' lasts a certain amount of time. A short 'moo' might last time 1; a longer one might last time 24 or even 1,000,000,000 or longer (cows can really moo when they want to). No 'moo' will last more than or equal to 2^63.

It should come as no surprise that the cows have a pattern to their moos.  Bessie will choose an integer c (1 <= c <= 100) that is the initial length of a moo.

After Bessie moos for length c, the cows calculate times for

subsequent moos. They apply two formulae to each moo time to yield even more moo times. The two formulae are:

```cpp
f1(c)=a1*c/d1+b1 (integer divide, of course) and 
f2(c)=a2*c/d2+b2. 
They then successively use the two new times created by evaluating f1(c) and f2(c) to create even more mooing times. They keep a sorted list of all the possible mooing times (discarding duplicates). 
They are allowed to moo a total of N times (1 <= N <= 4,000,000). Please determine the length of the longest moo before they must quit. 
The constants in the formulae have these constraints: 1 <= d1 < a1; d1 < a1 <= 20; 0 <= b1 <= 20; 1 <= d2 < a2; d2 < a2 <= 20; 0 <= b2 <= 20. 
Consider an example where c=3 and N=10. The constants are: 
a1=4    b1=3     d1=3 
a2=17   b2=8     d2=2 
```
The first mooing time is 3, given by the value of c. The total list of mooing times is:
```cpp
1. c=3             ->  3       6. f2(3)=17*3/2+8  -> 33 
2. f1(3)=4*3/3+3   ->  7       7. f1(28)=4*28/3+3 -> 40 
3. f1(7)=4*7/3+3   -> 12       8. f1(33)=4*33/3+3 -> 47 
4. f1(12)=4*12/3+3 -> 19       9. f1(40)=4*40/3+3 -> 56 
5. f1(19)=4*19/3+3 -> 28      10. f1(47)=4*47/3+3 -> 65 
The tenth time is 65, which would be the proper answer for this set of inputs. 
```
Partial feedback will be provided on the first 50 submissions.
MEMORY LIMIT: 64MB

满月的时候，和狼一样，牛们也在月光下叫，他们从不嚎叫，而是哞叫。

每次哞叫都有一个时长，可能是 $1$ 秒，可能是 $10^9$ 秒或更久，牛们真的非常能叫.当然，没有哞叫时长会超过或等于 $2^{63}$。

牛们的哞叫可以找到规律，这并不奇怪。贝茜会选择一个整数 $c(c\le100)$ 来作为初始时长之后，牛们根据两条公式确定更多的时长：

$f_1(c)=\lfloor a_1c/d_1\rfloor+b_1$

$f_2(c)=\lfloor a_2c/d_2\rfloor+b_2$ 

牛们用这两条公式不断地迭代、计算，算得大量的时长.然后她们将这些时长排序，剔除重复的时长，最后取前 $N(1<N< 4000000)$ 个整数为她们 $N$ 次哞叫的时长.请你计算，第 $N$ 次哞叫的时长是多少。公式中的常量均为整数，满足下列关系： 

$1 \le d_1 < a_1 \le 20$; $0\le b_1 \le 20$;

$1 \le d_2 < a_2 \le 20$; $0\le b_2\le 20$。


## 样例 #1

### 输入

```
3 10 
4 3 3 
17 8 2 
```

### 输出

```
65 
```

# AI分析结果



### 算法分类
**模拟**

### 综合分析与结论
题目要求通过两个递增函数生成有序序列的第N项。所有正确题解均采用双指针模拟合并两个递增序列的思路，确保每次取最小值并处理重复情况。核心难点在于意识到函数生成的序列严格递增，从而无需额外排序，直接通过双指针动态生成。

### 精选题解（评分≥4星）

1. **幽界の冥神（5星）**
   - **关键亮点**：代码简洁，双指针逻辑清晰，直接输出第N项，无需冗余排序。
   - **核心代码**：
     ```cpp
     for (int i = 2; i <= n; i++) {
         LL tmp1 = ff(), tmp2 = fs();
         if (tmp1 < tmp2) f[i] = tmp1, f1++;
         else if (tmp1 > tmp2) f[i] = tmp2, f2++;
         else f[i] = tmp1, f1++, f2++;
     }
     ```

2. **lbh123（5星）**
   - **关键亮点**：代码简洁易懂，严格处理相等情况，避免重复元素。
   - **核心代码**：
     ```cpp
     for (int i = 2; i <= n; i++) {
         ans1 = a1 * ans[id1] / d1 + b1;
         ans2 = a2 * ans[id2] / d2 + b2;
         if (ans1 < ans2) ans[i] = ans1, id1++;
         else if (ans1 > ans2) ans[i] = ans2, id2++;
         else ans[i] = ans1, id1++, id2++;
     }
     ```

3. **x_faraway_x（4星）**
   - **关键亮点**：代码紧凑，合并判断条件，简化逻辑。
   - **核心代码**：
     ```cpp
     a[i] = min(f1, f2);
     if (f1 <= f2) m1++;
     if (f1 >= f2) m2++;
     ```

### 最优关键思路
**双指针模拟归并**：维护两个指针分别指向两个函数生成的当前待处理元素，每次取较小值并移动对应指针，若相等则同时移动避免重复。时间复杂度O(N)，空间复杂度O(N)，完全符合题目约束。

### 拓展思路
类似合并有序数组/链表的场景（如[P1631 序列合并](https://www.luogu.com.cn/problem/P1631)），或需处理动态生成元素的排序问题（如[P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)）。

### 推荐题目
1. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)  
   - 类似双序列合并，需优先队列优化。
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)  
   - 双指针/单调队列维护极值。
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
   - 动态取最小值，优先队列应用。

---
处理用时：181.11秒