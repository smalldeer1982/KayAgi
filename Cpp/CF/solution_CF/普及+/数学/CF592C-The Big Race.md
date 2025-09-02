# The Big Race

## 题目描述

Vector Willman and Array Bolt are the two most famous athletes of Byteforces. They are going to compete in a race with a distance of $ L $ meters today.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF592C/9bfd48ba8eef8aa7a96654a450d8ae80783554b5.png)Willman and Bolt have exactly the same speed, so when they compete the result is always a tie. That is a problem for the organizers because they want a winner.

While watching previous races the organizers have noticed that Willman can perform only steps of length equal to $ w $ meters, and Bolt can perform only steps of length equal to $ b $ meters. Organizers decided to slightly change the rules of the race. Now, at the end of the racetrack there will be an abyss, and the winner will be declared the athlete, who manages to run farther from the starting point of the the racetrack (which is not the subject to change by any of the athletes).

Note that none of the athletes can run infinitely far, as they both will at some moment of time face the point, such that only one step further will cause them to fall in the abyss. In other words, the athlete will not fall into the abyss if the total length of all his steps will be less or equal to the chosen distance $ L $ .

Since the organizers are very fair, the are going to set the length of the racetrack as an integer chosen randomly and uniformly in range from 1 to $ t $ (both are included). What is the probability that Willman and Bolt tie again today?

## 说明/提示

In the first sample Willman and Bolt will tie in case $ 1 $ , $ 6 $ or $ 7 $ are chosen as the length of the racetrack.

## 样例 #1

### 输入

```
10 3 2
```

### 输出

```
3/10
```

## 样例 #2

### 输入

```
7 1 2
```

### 输出

```
3/7
```

# 题解

## 作者：Paracelestia (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF592C)

## $\texttt{Description}$

两个人赛跑，一个人步长 $w$，另一个人步长 $b$，问赛道长度取 $[1, t]$ 之间的任意整数时，两人不超过终点能达到的最远距离相等的概率是多少。

$1 \leq t, w, b \leq 5 \cdot 10^{18}$

## $\texttt{Solution}$

设赛道长度为 $s$。

首先 $s$ 取小于 $\min(w, b)$ 的数都是可行的，此时两人一步都不能走。

然后，当 $s$ 是 $\operatorname{lcm}(w, b)$ 的倍数时也是合法的，两人能走的距离都为 $s$。在这种情况下 $s$ 还可以再延长小于 $\min(w, b)$ 的长度，使两人能走的距离不会发生变化。

$s$ 最长不能超过 $t$，最后记得特判。

两种情况统计一下即可，详见代码。答案是分数形式，记得约分。

时间复杂度：$\mathcal{O}(1)$。

## $\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;

#define fi first
#define se second

template<typename T> inline T read() {
    T x = 0, f = 1; char ch = 0;
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch - '0');
    return x * f;
}

template<typename T> inline void write(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

template<typename T> inline void print(T x, char ed = '\n') {
    write(x), putchar(ed);
}

#define ull __int128 // 要开 __int128！

const int N = 1e5 + 10;

ull t, w, b, ans;

signed main() {
    t = read<ull>(), w = read<ull>(), b = read<ull>();
    ull lcm = w / __gcd(w, b) * b;
    ans = (t / lcm - 1) * min(w, b) // lcm(w, b)的倍数及延长
    	 + min({w, b, t % lcm + 1}); // 最后不能超过 t，特判
    ans += min(w, b) - 1; // 两人都走不了
    ull g = __gcd(t, ans); // 约分
    print(ans / g, '/'), print(t / g);
    return 0;
}
```


---

