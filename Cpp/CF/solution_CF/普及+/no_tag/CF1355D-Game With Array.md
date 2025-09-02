# Game With Array

## 题目描述

Petya and Vasya are competing with each other in a new interesting game as they always do.

At the beginning of the game Petya has to come up with an array of $ N $ positive integers. Sum of all elements in his array should be equal to $ S $ . Then Petya has to select an integer $ K $ such that $ 0 \leq K \leq S $ .

In order to win, Vasya has to find a non-empty subarray in Petya's array such that the sum of all selected elements equals to either $ K $ or $ S - K $ . Otherwise Vasya loses.

You are given integers $ N $ and $ S $ . You should determine if Petya can win, considering Vasya plays optimally. If Petya can win, help him to do that.

## 样例 #1

### 输入

```
1 4```

### 输出

```
YES
4
2```

## 样例 #2

### 输入

```
3 4```

### 输出

```
NO```

## 样例 #3

### 输入

```
3 8```

### 输出

```
YES
2 1 5
4```

# 题解

## 作者：一扶苏一 (赞：6)

## 【构造】【CF1355D】 Game With Array

### Analysis

首先 $s \geq 2n$ 的时候，显然可以构造一个 $\{2, 2, 2, \cdots, s - 2n + 2\}$ 的序列，因为 $s \geq 2n$，所以 $s -2n + 2 \geq 2$。取 $k = 1$，一定凑不出来。

而 $s \lt 2n$ 的时候，可以通过手玩几组发现无解。我们来尝试证明这个结论。

反证法，假设当 $s \lt 2n$ 时，存在一个整数 $k$ 和一个和为 $s$ 序列 $a$，满足 $a$ 不存在和为 $k$ 或 $(s - k)$ 的子列。

考虑对于序列 $a$，做出其前缀和数组 $b$。对于每一个 $b_i$，我们标记所有值为 $b_i + ts$ 的整数，其中 $t$ 是满足 $0 \leq t \lt 2k$ 的整数，另外标记整数 $0$。则对于任意正整数 $x$，$x$ 与 $x + k$ 不能被同时标记（否则考虑设 $u \equiv x \pmod s$，$v \equiv x + k \pmod s$，则 $u$ 和 $v$ 是标记 $x$ 和 $x + k$ 的数。而 $v - u \equiv x + k - x \equiv k \pmod s$。换句话说，如果 $v$ 在 $b$ 中的对应位置在 $u$ 后面，则 $v - u = k$，存在和为 $k$ 的子列，否则 $u - v = s - k$，存在和为 $s - k$ 的子列，与假设不符）。

考虑对于 $[0, 2ks)$ 的所有整数，我们这样分组：

$(0, k)$，$(1, k + 1)$，$(2, k + 2)$，$\cdots$ ，$(k - 1, 2k - 1)$

$(2k, 3k)$，$(2k+ 1, 3k + 1)$，$(2k + 2, 3k + 2)$，$(2k + 3, 3k + 3)$，$\cdots$ 

$\cdots$

$\cdots$，$(2ks - k - 1, 2ks - 1)$。

也即将 $x$ 与 $x + k$ 分在一组。注意到这样一共有 $ks$ 组数对。任意一对数之间都至多能标记一个。因此最多能标记 $ks$ 个数。但是考虑一共有 $n$ 个互不相同前缀和值，每个数可以标记 $2k$ 个整数，加上另外标记的 $0$ 并去掉 $b_n + (2k - 1)s = 2ks$不在区间中，实际上一共标记了 $2nk$ 个整数。因为 $s \lt 2n$，所以 $2nk \gt ks$。实际标记数多于最多能标记的个数，矛盾。



没有给出证明的题解都被我撤下来了。

### Code

```cpp
namespace Fusu {

int n, s;

void Main() {
  qr(n); qr(s);
  if ((n << 1) > s) {
    puts("No");
  } else {
    puts("Yes");
    for (int i = 1; i < n; ++i) {
      qw(2, ' ');
      s -= 2;
    }
    qw(s, '\n');
    puts("1");
  }
}

} // namespace Fusu
```



---

## 作者：vigza (赞：4)

# CF1355D
现在我们已知要构造一个长度为 $n$ 的数组，且满足和为 $S$。要求找到一种构造方法，能使任何子串的和都不等于 $K$。
## 解法说明
### 观察
首先我们造一些样例，观察一下性质：

$n = 5$, $S = 15$

试图：

$1\ 2\ 3\ 4\ 5$

然后考虑它子串的可能获得的所有和。

$1\ 2\ 3\ 4\ 5\ 6\ 7\ 8\ 9\ 10\ 11\ 12\ 13\ 14\ 15$

很不幸，从 $1$ 到 $S$ 都覆盖了，所以这种构造不存在 $K$ 满足题意。难道就不能构造出一种数列存在 $K$ 吗？

再写一个试试：

$1\ 1\ 1\ 5\ 7$

然后考虑它子串的可能获得的所有和。

$1\ 2\ 3\ 5\ 6\ 7\ 8\ 9\ 10\ 12\ 13\ 14\ 15$

找 $K$ 时，发现它没有 $4$，$11$，对比之前为啥这个构造是可以的？

发现因为再求子串和的时候，我们是对数列中的元素求所有组合情况，而数列一堆 $1$ 会导致重复组合，导致产生子串和可能情况变少，而如果构造的每位数都不同，会很有可能导致 $1$ 到 $S$ 都被覆盖。

### 贪心

这时，我们便有一种贪心的猜想：让数列中出现的不同元素尽可能的少。所以能不能构造数列 $\{1,1,1,1,...,S-(n-1)\}$，使得它是所有数列中不同子串和的数量最少的，如果这个数列都不能找不到 $K$，是不是就能确定其他更具变化性的构造数列就更找不到 $K$ 了？

值得顾虑的是，“$\{1,1,1,1,...,S-(n-1)\}$”等价于“子串和的可能数量最少”吗？

读者自证不难。

### 细化 

推广开，不同元素只有两个，$1$ 和 $x=S-(n-1)$，

通过组合，子串和覆盖的范围就会是 $[1,n-1],[x,S]$，那么是不是如果 $x>n$ 的话，$K$ 取 $n$ 就能构造出来？

然后，居然过了？







### Code
```cpp
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, s;
    cin >> n >> s;
    int x = s - (n - 1);
    if (x > n) {
        cout << "YES" << endl;
        for (int i = 1;i <= n - 1;i++) cout << 1 << ' ';
        cout << x << endl << n;
        return;
    }
    cout << "NO";
}

int main() {
    // freopen("in.txt","r",stdin);
    ios::sync_with_stdio(false);
    int T = 1;
    while (T--) solve();
    return 0;
}
```
#### 蟹蟹阅读~


---

## 作者：Zhao_daodao (赞：0)

# CF1355D solution
给一个不一样的构造方法。

~~我太蒟蒻了没想到其他题解的做法。~~


首先奇偶分析一波 $s$。

### 1. $s$ 是偶数

定义 $p=\frac{s}{2}$。

发现先放 $p+1$，再放 $n-2$ 个 $1$，最后一个是剩下的数，这样构造是可行的。此时 $k=p$，子段和不能是 $p$。

为什么呢？

如果子段不包括 $p+1$，此时剩下的所有数加起来才 $p-1$，不可能比 $p$ 还大。

如果子段包括 $p+1$，此时子段已经比 $p$ 大，不可能是 $p$。

发现这是一种合法的构造方案，只用判断最后一个数是不是 `0` 就可以了。

### 2. $s$ 是奇数

定义 $p=\frac{s-1}{2}$。

发现先放 $p+2$，再放 $n-2$ 个 $1$，最后一个是剩下的数，这样构造是可行的。
此时 $k=p$，子段和不能是 $p+1$、$p$。

为什么呢？

如果子段不包括 $p+2$，剩下的所有数加起来才 $p-1$，不可能比 $p$ 还大。

如果子段包括 $p+2$，此时子段已经比 $p+1$ 大，不可能是 $p$ 或者 $p+1$。

发现这是一种合法的构造方案，只用判断最后一个数是不是 `0` 就可以了。


## 对于无解

通过一番推倒就可以发现上述构造方法是数据的极限。

如果不能通过上述构造方法构造出来，说明这个数据无解。

## 对于 $n=1$
发现此时 $p=0$，怎么办呢？

1. $s\ne 1$
此时直接输出 `s`，`1` 就可以了。

1. $s=1$ 
此时无解，输出 `NO`。

---
如果你将上述分类讨论全部写对，你就可以 `AC` 啦！

[AC记录](https://codeforces.com/contest/1355/submission/228867329)
# code time
```cpp
//码风很丑，看看就好
#include<bits/stdc++.h>
using namespace std;
signed main(){
    int n,s;
    cin>>n>>s;
    if(n==1&&s==1)cout<<"NO\n",exit(0);
    if(n==1){
        cout<<"YES\n";
        cout<<s<<"\n";
        cout<<1<<"\n";
        exit(0);
    }
    if(s%2==1){
        int k=(s-1)/2;
        if(k<n)cout<<"NO\n";
        else if(s-(k+2)-(n-2)<=0)cout<<"NO\n";
        else{
            cout<<"YES\n";
            cout<<k+2<<" ";
            for(int i=1;i<=n-2;i++)
                cout<<"1 ";
            cout<<s-(k+2)-(n-2)<<"\n";
            cout<<k;
        }
    }
    if(s%2==0){
        int k=s/2;
        if(k+1<n)cout<<"NO\n";
        else if(s-(k+1)-(n-2)<=0)cout<<"NO\n";
        else{
            cout<<"YES\n";
            cout<<k+1<<" ";
            for(int i=1;i<=n-2;i++)
                cout<<"1 ";
            cout<<s-(k+1)-(n-2)<<"\n";
            cout<<k;
        }
    }
}
```

---

## 作者：_Winham_ (赞：0)

题目意思：

给定一个 $n$ 和一个 $s$，其中 $n$ 代表要构造一个长度为 $n$，而 $s$ 代表这个序列和为 $s$。现在问你能不能在这个序列中找不到一个字段的和为 $k$ 或 $s - k$。

---

思路：

暴力是肯定不行的，因为肯定是 $TLE$ 的，所以我们要找一下规律。

现在我们先考虑什么为 $YES$ 什么为 $NO$。但可以发现所有的序列只要 $2 \times n$ 大于 $s$，则这个序列是肯定的不成立的，相反只要 $2 \times n$ 小于等于 $s$ 则就是成立的。

而接下来我们来找一下为 $YES$ 的规律。而我们能发现不管只要为 $YES$ 的序列，只要能输出 $n - 1$ 个 $2$，在输出 $s - 2 \times ( n + 1 ) $就行了。

但可能会有人问为什么？其实原理很简单原理很简单，因为前面都是 $2$ 的话显然不可能满足 $1$ 和 $s-1$ 的要求。而前面的 $2$ 与 后面的 $s - 2 \times ( n + 1 )$ 是根本不可能满足这个要求的。

---

代码：

```cpp
#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
using namespace std;
#define LL long long
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;
int n,s;
int main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	cin>>n>>s;
	if(2*n>s){
		cout<<"NO"<<endl;
		return 0;
	}
	cout<<"YES"<<endl;
	for(int i=1;i<n;i++)cout<<2<<" ";
	cout<<s-2*(n+1)<<endl<<1<<endl;
	return 0;
}

```

---

## 作者：sto_5k_orz (赞：0)

构造题。

分类讨论：

当 $s\ge 2n$ 时，可以构造出一个前 $n-1$ 个是 $2$，并且剩下一个是 $s-2(n-1)=s-2n+2$ 的序列，取到 $k=1$，没有子段和是 $1$ 或者 $s-1$ 的。

那么当 $s<2n$ 呢？无解？

无解！

口胡了几组发现都无解。

根据容斥原理，必定有一个是 $1$。

那么子段和就可以精准地调节了。

经过证明，此题代码仅仅七行，属于标准的水题。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int n, s; cin >> n >> s; if(s < 2 * n) puts("NO"), exit(0); puts("YES");
	for(int i = 1; i < n; i++) cout << 2 << ' '; cout << s - 2 * n + 2 << endl << 1;
	return 0;
}
```

---

## 作者：oimaster (赞：0)

## 题面

给定两个数字 $N$ 和 $S$ ，满足 $\left(1 \leq N \leq S \leq 10^{6}\right)$，让你求一个长度为 $N$ 的数列，每个元素的和为 $S$，同时任何一个子序列的和都不能等于 $K$ 或 $S-K$。你要构造出这个数列和 $K$，或者说这是不可能的。**本题不是多测。**

## 思路

这道题其实是一道构造题。

首先，我们判断，当 $S < 2N$ 时，是一定无法构成的。这可以证明。 

否则，我们按照以下方法构造：

1. 输出 `Yes`；
2. 然后输出 $N-1$ 个 $2$；
3. 再输出 $S-2\left(N-1\right)$；
4. 最后，输出 $1$。

这种方法可以保证结果合法。为什么？首先前面所有的都是 $2$，已经太大了，不可能满足 $1$ 的要求。再看 $S-1$，显然，不管是前面的 $2$ 和后面的 $S-2\left(N-1\right)$ 都不可能满足这个要求。所以，这种方法一定是 `Accepted` 的。

## 代码

这道题我的代码写得太丑陋，所以挂上了标程。

```c++
#include <iostream>
using namespace std;

int main() {
	int n, s;
	cin >> n >> s;
	
	if (2 * n <= s) {
		cout << "YES\n";
		for (int i = 0; i < n - 1; i++) {
			cout << 2 << ' ';
			s -= 2;
		}
		cout << s << '\n' << 1;
	} else {
		cout << "NO";
	}
	return 0;
}
```

---

