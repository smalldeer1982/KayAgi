# Let Me Teach You a Lesson (Easy Version)

## 题目描述

This is the easy version of a problem. The only difference between an easy and a hard version is the constraints on $ t $ and $ n $ . You can make hacks only if both versions of the problem are solved.

Arthur is giving a lesson to his famous $ 2 n $ knights. Like any other students, they're sitting at the desks in pairs, but out of habit in a circle. The knight $ 2 i - 1 $ is sitting at the desk with the knight $ 2 i $ .

Each knight has intelligence, which can be measured by an integer. Let's denote the intelligence of the $ i $ -th knight as $ a_i $ . Arthur wants the maximal difference in total intelligence over all pairs of desks to be as small as possible. More formally, he wants to minimize $ \max\limits_{1 \le i \le n} (a_{2 i - 1} + a_{2 i}) - \min\limits_{1 \le i \le n} (a_{2 i - 1} + a_{2 i}) $ .

However, the Code of Chivalry only allows swapping the opposite knights in the circle, i.e., Arthur can simultaneously perform $ a_i := a_{i + n} $ , $ a_{i + n} := a_i $ for any $ 1 \le i \le n $ . Arthur can make any number of such swaps. What is the best result he can achieve?

## 说明/提示

In the first test case, Arthur can swap the second and the fourth knights. Then the total intelligence at both desks will be $ 10 $ .

In the third test case, Arthur can make $ 0 $ operations, which will result in the total intelligence of $ 11 $ at each of the desks.

In the fourth test case, Arthur can swap knights with indices $ 2 $ and $ 5 $ and achieve the difference of $ 2 $ . It can be proven that he cannot improve his result any further.

## 样例 #1

### 输入

```
5
2
6 6 4 4
1
10 17
3
1 10 1 10 1 10
3
3 3 4 5 5 4
5
1 2 3 4 5 6 7 8 9 10```

### 输出

```
0
0
0
2
4```

# 题解

## 作者：Hoks (赞：0)

## 前言
菜猫猫的第二场 VP 中写不出来的题。

摘自 [杂题选做](https://www.luogu.com.cn/training/597433)。
## 思路分析
感觉这种题就很不常规，不好入手。

考虑手玩观察一下。

然后就会注意到重点，只能交换 $a_i$ 和 $a_{i+n}$。

考虑把能交换的数都连边连起来，并把 $2i-1$ 和 $2i$ 连起来。

此时我们给 $2n$ 个数连了 $n$ 条边且没有重边，必然会有环。

此时我们发现图的形态与 $n$ 的奇偶性有关：
1. $n$ 为偶数时：

    我们会发现整个图恰好是一个个的四元环组成的。

    那么对于每个四元环，可以取到的值恰好有 $4$ 种。

    取到极差最小的情况也就是取中间的两种值的情况，直接处理就行了。
2. $n$ 为奇数时：

    此时我们发现整个图恰好是一个大环。

    我们考虑怎么处理这个大环。

    环肯定要破开，而对于极差这种东西感觉也很难做。

    考虑对于极差的问题。

    我们不难发现对于一对数，最多只会有 $4$ 种取值，这四种取值也就分别是**不换+不换/换+不换/不换+换/换+换**。

    那么总共可能的取值也就只有 $4n$ 种。

    考虑使用双指针，用双指针枚举出目前值域区间 $[l,r]$。

    显然的是如果 $[l,r]$ 是可行的，那么 $[l,r+1]$ 也肯定是可行的，然后考虑尽可能的把 $l$ 往又移到不可行就行了。

    那我们现在要做到的就是一个复杂度在 $O(n)$ 以内的判断可行性。

    这个环太乱了，先给它捋直一点。

    具体的我们考虑把有边的点放在一起，然后把环拍成序列。

    比如 $n=7$ 时，得到的序列就是：
    $$1-2,9-10,3-4,11-12,5-6,13-14,7-8$$

    然后来考虑破环成链，由上面观察出来的性质我们知道每组都只有 $4$ 种可能性，但是会被上一组换不换影响。

    那么我们直接枚举第一组换不换的状态，然后按顺序尝试对后面的组操作。

    具体的我们使用 dp 来进行转移，$f_{i,0/1}$ 表示对于第 $i$ 组，和下一组连的那个数**有/无**交换过。

    此时的转移方程式也比较简单了，~~因为懒~~笔者就不多赘述了。

    那么直接用这个 dp 写一个 check 大力双指针移就可以做到 $O(n^2)$ 通过此题了。
## 代码
应该不难实现吧~~懒得再写一份了~~。

---

