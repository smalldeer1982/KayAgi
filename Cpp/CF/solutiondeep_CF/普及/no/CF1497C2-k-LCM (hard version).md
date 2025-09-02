# 题目信息

# k-LCM (hard version)

## 题目描述

It is the hard version of the problem. The only difference is that in this version $ 3 \le k \le n $ .

You are given a positive integer $ n $ . Find $ k $ positive integers $ a_1, a_2, \ldots, a_k $ , such that:

- $ a_1 + a_2 + \ldots + a_k = n $
- $ LCM(a_1, a_2, \ldots, a_k) \le \frac{n}{2} $

Here $ LCM $ is the [least common multiple](https://en.wikipedia.org/wiki/Least_common_multiple) of numbers $ a_1, a_2, \ldots, a_k $ .

We can show that for given constraints the answer always exists.

## 样例 #1

### 输入

```
2
6 4
9 5```

### 输出

```
1 2 2 1 
1 3 3 1 1```

# AI分析结果

### 题目翻译
# k-LCM (困难版本)

## 题目描述

这是该问题的困难版本。唯一的不同之处在于，在这个版本中 $3 \le k \le n$。

给定一个正整数 $n$，找到 $k$ 个正整数 $a_1, a_2, \ldots, a_k$，满足：

- $a_1 + a_2 + \ldots + a_k = n$
- $LCM(a_1, a_2, \ldots, a_k) \le \frac{n}{2}$

这里 $LCM$ 是 $a_1, a_2, \ldots, a_k$ 的[最小公倍数](https://en.wikipedia.org/wiki/Least_common_multiple)。

我们可以证明，在给定的约束条件下，答案总是存在的。

## 样例 #1

### 输入

```
2
6 4
9 5```

### 输出

```
1 2 2 1 
1 3 3 1 1```

### 算法分类
构造

### 题解分析与结论
本题的核心思路是通过构造一组数，使得它们的和为 $n$，且它们的最小公倍数不超过 $\frac{n}{2}$。由于 $1$ 不影响最小公倍数，因此大多数题解都采用了先输出 $k-3$ 个 $1$，然后将问题简化为 $k=3$ 的情况。对于 $k=3$ 的情况，题解们根据 $n$ 的奇偶性进行了不同的构造，确保最小公倍数不超过 $\frac{n}{2}$。

### 精选题解
1. **作者：Yizhixiaoyun (赞：6)**
   - **星级：4.5**
   - **关键亮点**：思路清晰，代码简洁，直接通过输出 $k-3$ 个 $1$ 简化问题，然后根据 $n$ 的奇偶性进行构造。
   - **代码核心思想**：先输出 $k-3$ 个 $1$，然后根据 $n$ 的奇偶性输出剩余的三个数。
   ```cpp
   for(register int i=k;i>3;--i){
       n--;
       cout<<"1 ";
   }
   if(n%2==1) cout<<"1 "<<n/2<<" "<<n/2<<endl;
   else if(n%4!=0) cout<<"2 "<<n/2-1<<" "<<n/2-1<<endl;
   else cout<<n/2<<" "<<n/4<<" "<<n/4<<endl;
   ```

2. **作者：EuphoricStar (赞：2)**
   - **星级：4**
   - **关键亮点**：与Yizhixiaoyun的思路相似，代码实现略有不同，同样简洁高效。
   - **代码核心思想**：先输出 $k-3$ 个 $1$，然后根据 $n$ 的奇偶性输出剩余的三个数。
   ```cpp
   n -= (k - 3);
   for (int i = k; i > 3; --i) {
       printf("1 ");
   }
   if (n & 1) {
       printf("1 %d %d\n", n / 2, n / 2);
   } else if ((n / 2) & 1) {
       printf("2 %d %d\n", n / 2 - 1, n / 2 - 1);
   } else {
       printf("%d %d %d\n", n / 2, n / 4, n / 4);
   }
   ```

3. **作者：StayAlone (赞：0)**
   - **星级：4**
   - **关键亮点**：详细解释了构造思路的正确性，代码简洁且易于理解。
   - **代码核心思想**：先输出 $k-3$ 个 $1$，然后根据 $n$ 的奇偶性输出剩余的三个数。
   ```cpp
   while (k > 3) printf("1 "), --k, --n;
   if (n % 2) printf("1 %d %d\n", n / 2, n / 2);
   else if (n % 4) printf("2 %d %d\n", n / 2 - 1, n / 2 - 1);
   else printf("%d %d %d\n", n / 2, n / 4, n / 4);
   ```

### 最优关键思路
1. **利用 $1$ 不影响最小公倍数的性质**，先输出 $k-3$ 个 $1$，将问题简化为 $k=3$ 的情况。
2. **根据 $n$ 的奇偶性进行构造**：
   - 若 $n$ 为奇数，输出 $1, \frac{n}{2}, \frac{n}{2}$。
   - 若 $n$ 为偶数但 $n \mod 4 \neq 0$，输出 $2, \frac{n}{2}-1, \frac{n}{2}-1$。
   - 若 $n \mod 4 = 0$，输出 $\frac{n}{2}, \frac{n}{4}, \frac{n}{4}$。

### 可拓展之处
类似的问题可以通过构造法解决，尤其是当问题涉及到最小公倍数或最大公约数时，可以考虑利用 $1$ 的性质来简化问题。

### 推荐题目
1. [CF1497C1 k-LCM (easy version)](https://www.luogu.com.cn/problem/CF1497C1)
2. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
3. [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)

---
处理用时：42.45秒