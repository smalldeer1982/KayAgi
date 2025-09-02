# Shocking Arrangement

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ consisting of integers such that $ a_1 + a_2 + \ldots + a_n = 0 $ .

You have to rearrange the elements of the array $ a $ so that the following condition is satisfied:

$$\max\limits_{1 \le l \le r \le n} \lvert a_l + a_{l+1} + \ldots + a_r \rvert < \max(a_1, a_2, \ldots, a_n) - \min(a_1, a_2, \ldots, a_n)$$ 

where  $ |x| $  denotes the absolute value of  $ x $ .More formally, determine if there exists a permutation  $ p_1, p_2, \ldots, p_n $  that for the array  $ a_{p_1}, a_{p_2}, \ldots, a_{p_n} $ , the condition above is satisfied, and find the corresponding array.Recall that the array  $ p_1, p_2, \ldots, p_n $  is called a permutation if for each integer  $ x $  from  $ 1 $  to  $ n $  there is exactly one  $ i $  from  $ 1 $  to  $ n $  such that  $ p_i = x$.

## 说明/提示

In the first test case $ \max(a_1, \ldots, a_n) - \min(a_1, \ldots, a_n) = 9 $ . Therefore, the elements can be rearranged as $ [-5, -2, 3, 4] $ . It is easy to see that for such an arrangement $ \lvert a_l + \ldots + a_r \rvert $ is always not greater than $ 7 $ , and therefore less than $ 9 $ .

In the second test case you can rearrange the elements of the array as $ [-3, 2, -3, 2, 2] $ . Then the maximum modulus of the sum will be reached on the subarray $ [-3, 2, -3] $ , and will be equal to $ \lvert -3 + 2 + -3 \rvert = \lvert -4 \rvert = 4 $ , which is less than $ 5 $ .

In the fourth test example, any rearrangement of the array $ a $ will be suitable as an answer, including $ [-1, 0, 1] $ .

## 样例 #1

### 输入

```
7
4
3 4 -2 -5
5
2 2 2 -3 -3
8
-3 -3 1 1 1 1 1 1
3
0 1 -1
7
-3 4 3 4 -4 -4 0
1
0
7
-18 13 -18 -17 12 15 13```

### 输出

```
Yes
-5 -2 3 4
Yes
-3 2 -3 2 2
Yes
1 1 1 -3 1 1 1 -3
Yes
-1 0 1
Yes
4 -4 4 -4 0 3 -3
No
Yes
13 12 -18 15 -18 13 -17```

# 题解

## 作者：一扶苏一 (赞：9)

# 【CF1798D】Shocking Arrangement

## Description

给出一个长度为 $n$ 的数列 $a$，满足 $\sum_{i = 1}^n a_i = 0$。

你需要重排这个数列，使得重排后满足

$$\max\limits_{1 \le l \le r \le n} \lvert a_l + a_{l+1} + \ldots + a_r \rvert < \max(a_1, a_2, \ldots, a_n) - \min(a_1, a_2, \ldots, a_n)$$

多组数据，$n$ 之和不超过 $3 \times 10^5$，$|a_i| \leq 10^9$。

## Analysis

整蛊题。

首先如果 $a$ 全是 $0$，那么显然无解。

否则考虑从左到右构造新数列，维护新数列的前缀和 $s$。

- 如果 $s \geq 0$，则在剩余未加入的数中随便选择一个非正数添加到新数列末尾。
- 如果 $s < 0$，则在剩余未加入的数中随便选择一个负数添加到新数列末尾。

因为保证了数列之和为 $0$，所以当 $s \geq 0$ 时，你总能找到还没添加的非正数，同理第二种情况你也总能找到未添加的正数。

考虑这样构造的正确性：注意到 $\min a_i \leq s \leq \max a_i$。这是因为每次总会添加一个和 $s$ 异号的数。当 $s \geq 0$ 时，能找到的最小数也是 $\min a_i$，则新的前缀和 $s'$ 满足 $s' \geq s + \min a_i \geq \min a_i$。类似可以证明 $s \leq \max a_i$。

而任何区间的和都可以写成两个前缀和相减的形式。设 $s_i$ 是长度为 $i$ 的前缀和，则 $|\sum_{i = l}^r a_i| = |s_r - s_{l}| \leq \max a_i - \min a_i$。任何区间都满足这个限制，自然区间和绝对值的最大值也满足这个限制。正确性得证。

## Code

写代码时把正数和非负数分别排了个序，现在看起来似乎是不必要的。

```cpp
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

int T;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  for (std::cin >> T; T; --T) {
    int n;
    std::cin >> n;
    std::vector<int> a(n), b, c;
    std::generate(a.begin(), a.end(), []() { int x; std::cin >> x; return x; });
    if (*std::max_element(a.begin(), a.end()) == 0) {
      std::cout << "No\n";
      continue;
    }
    std::cout << "Yes\n";
    for (auto i : a) 
      if (i < 0) b.push_back(i);
      else c.push_back(i);
    std::sort(b.begin(), b.end());
    std::sort(c.begin(), c.end(), std::greater<int>());
    int sum = 0;
    for (int i = 1, j = 0, k = 0; i <= n; ++i) {
      if (sum >= 0 && j < b.size()) {
        std::cout << b[j] << ' ';
        sum += b[j++];
      } else {
        std::cout << c[k] << ' ';
        sum += c[k++];
      }
    }
    std::cout << '\n';
  }
}
```

---

## 作者：ncwzdlsd (赞：3)

特判一种情况：如果序列全是 $0$，显然不存在方案。

考虑转化一下左边的式子为前缀和的形式，即 $\max_{1\leq l\leq r\leq n}|s_r-s_{l-1}|$，等价于前缀和最大值与前缀和最小值之差。

于是得到转化后的条件式：

$$
\max_{i\in [0,n]} s_i-\min_{i\in [0,n]} s_i<\max_{i\in[1,n]} a_i-\min_{i\in[1,n]} a_i
$$

构造时我们只需要令 $\max_{i\in [0,n]} s_i\leq\max_{i\in[1,n]} a_i,\min_{i\in [0,n]} s_i\geq\min_{i\in[1,n]} a_i$ 即可。

从左至右构造答案序列 $b$，如果当前的前缀和非正，填入一个正数；否则填入一个负数。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=3e5+5;
int a[maxn],b[maxn];

void solve()
{
    int n;cin>>n;
    bool flag=0;
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i];
        if(a[i]) flag=1;
    }
    if(!flag) return cout<<"No"<<endl,void();
    int sum=0;
    sort(a+1,a+n+1);
    int l=1,r=n,cnt=0;
    while(l<=r)
    {
        if(sum<=0) sum+=a[r],b[++cnt]=a[r],r--;
        else sum+=a[l],b[++cnt]=a[l],l++;
    }
    cout<<"Yes"<<endl;
    for(int i=1;i<=n;i++) cout<<b[i]<<' ';
    cout<<endl;
}

int main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int t;cin>>t;
    while(t--) solve();
    return 0;
}
```

---

## 作者：masonpop (赞：1)

简单小构造。一般这种 CF 的构造题最忌等价分析，只要找到一组容易构造的特例就容易解决。

首先全是 $0$ 则无解。否则，考虑 $\sum\limits_{i=l}^ra_i=S_r-S_{l-1}$。其中前缀和 $S_i=\sum\limits_{j=1}^ia_j$。设 $a$ 中最大的非负数是 $x$，绝对值最大的非正数是 $-y$，其中 $x,y\ge0$。

直接考虑充分条件，即直接让任意 $1\le i\le n$，$S_i\in[-y,x]$。

那么，可以如下操作：从小往大枚举下标 $i$，同时维护前缀和 $S_i$，每次加进去一个和当前前缀和符号相反的数即可。（因为和是 $0$，因此一定能找到一个这样的数），用数学归纳法容易证明这样的正确性。[代码](https://codeforces.com/contest/1798/submission/219792049)。

---

