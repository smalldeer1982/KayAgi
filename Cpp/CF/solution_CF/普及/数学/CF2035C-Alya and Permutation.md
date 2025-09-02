# Alya and Permutation

## 题目描述

Alya has been given a hard problem. Unfortunately, she is too busy running for student council. Please solve this problem for her.

Given an integer $ n $ , construct a permutation $ p $ of integers $ 1, 2, \ldots, n $ that maximizes the value of $ k $ (which is initially $ 0 $ ) after the following process.

Perform $ n $ operations, on the $ i $ -th operation ( $ i=1, 2, \dots, n $ ),

- If $ i $ is odd, $ k=k\,\&\,p_i $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).
- If $ i $ is even, $ k=k\,|\,p_i $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 说明/提示

For the first test case, the value of $ k $ is determined as follows:

 $ k = 0 $ initially.

- On the $ 1 $ st operation, $ 1 $ is odd, so Alya sets $ k $ to be $ k\&p_1 = 0\&2 = 0 $ .
- On the $ 2 $ nd operation, $ 2 $ is even, so Alya sets $ k $ to be $ k|p_2 = 0|1 = 1 $ .
- On the $ 3 $ rd operation, $ 3 $ is odd, so Alya sets $ k $ to be $ k\&p_3 = 1\&3 = 1 $ .
- On the $ 4 $ th operation, $ 4 $ is even, so Alya sets $ k $ to be $ k|p_4 = 1|4 = 5 $ .
- On the $ 5 $ th operation, $ 5 $ is odd, so Alya sets $ k $ to be $ k\&p_5 = 5\&5 = 5 $ .

The final value of $ k $ is $ 5 $ . It can be shown that the final value of $ k $ is at most $ 5 $ for all permutations of length $ 5 $ . Another valid output is $ [2, 3, 1, 4, 5] $ .

For the second test case, the final value of $ k $ is $ 7 $ . It can be shown that the final value of $ k $ is at most $ 7 $ for all permutations of length $ 6 $ . Other valid outputs include $ [2, 4, 1, 6, 3, 5] $ and $ [5, 2, 6, 1, 3, 4] $ .

## 样例 #1

### 输入

```
6
5
6
7
8
9
10```

### 输出

```
5
2 1 3 4 5 
7
1 2 4 6 5 3 
7
2 4 5 1 3 6 7 
15
2 4 5 1 3 6 7 8 
9
2 4 5 6 7 1 3 8 9 
15
1 2 3 4 5 6 8 10 9 7```

# 题解

## 作者：Sakura_Emilia (赞：5)

# Solution

这是一道**结论题**+**构造题**。

需要先猜出结论，然后再来根据结论进行构造。

通过打表观察可以得到如下的结论：

**当 $n$ 为奇数时，$k$ 的最大值为 $n$；当 $n$ 为偶数时，$k$ 的最大值为 $2^{x+1}-1$，其中 $x$ 为二进制下 $n$ 最高位的 $1$ 所在的位数。**

下面根据结论来进行构造。

注意到题目处理的时候是从前往后一位一位的计算的。在构造的时候，如果能放置一个恰当的“隔断器”，让前面的数无论是什么，在迭代计算到“隔断器”时值均为某定值。之后只需要放置特殊的固定后缀，让后缀计算得到需要的构造结果即可。

可以使用 $3$ 和 $1$ 来作为“隔断器”，其中 $3$ 位于偶数下标的位置，$1$ 位于奇数下标的位置。这可以保证无论前面如何计算，经过这个“隔断器”后最终得到的结果一定是定值 $1$。

后面再构造两个数 $n-1$ 和 $n$，由于 $n$ 为奇数，$n$ 的二进制最后一位一定是 $1$，因此这可以保证 $1 \operatorname{or} (n-1)\operatorname{and} n$ 的结果一定是 $n$。

对于偶数情形，可以使用 `std::__lg` 来获取到二进制下 $n$ 最高位的 $1$ 所在的位数，不过需要注意，`__lg(n)+1` 才是二进制下 $n$ 最高位的 $1$ 所在的位数。

也是基于“隔断器”的思想同理构造，采用特定的后缀：$3,1,2^{x}-2,2^{x}-1,n$。

这里需要特别注意，当 $n$ 比较小的时候， $2^{x}-2$ 会直接取到前面的 $1$ 或 $3$，因此需要特判 $n$ 等于 $6$ 的情况。

# Code

```cpp
#include <bits/stdc++.h>
#define Ciallo main
#define int long long
using namespace std;
const int N = 1e6 + 8;

int T, n, k;

inline void solve() {
    cin >> n;
    if(n == 6) {
        cout << "7\n1 2 4 6 5 3\n";
    } else if(n % 2 == 1) {
        cout << n << endl << 2 << ' ';
        for(int i = 4; i <= n - 2; i++)
            cout << i << ' ';
        cout << "3 1 " << n - 1 << ' ' << n << endl;
    } else {
        int num = __lg(n);
        cout << (int) pow(2, num + 1) - 1 << endl << 2 << ' ';
        int a = (int) pow(2, num) - 1;
        for(int i = 4; i <= n - 1; i++)
            if(i != a and i != a - 1)
                cout << i << ' ';
        cout << "3 1 " << a - 1 << ' ' << a << ' ' << n << endl;
    }
}

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
```

---

## 作者：K_J_M (赞：3)

## 题意
给定一个正整数 $n$，现在有一个变量 $k$，初始值为 $0$，请你构造一个 $1\sim n$ 的排列 $p_i$，使得从下标 $1$ 开始经过 $n$ 次操作得到的变量 $k$ 最大。操作具体为：如果当前下标 $i$ 为奇数，那么 $k$ 与上 $p_i$；否则 $k$ 或上 $p_i$。
## Solution
### Step 1：证明答案与 $n$ 的关系
~~一开始把或看成了异或写了好久。~~ 样例还是很良心，给了 $n$ 在 $5\sim 10$ 的答案，而 $n=11$ 的答案是 $11$，因此猜测我们的答案在 $n$ 为奇数时是 $n$，否则答案为 $n$ 的位数的 $2$ 的幂减 $1$。然后证明一下，当 $n$ 为奇数时，最后一次操作为与，而任何一个数与上 $x$ 都会小于等于 $x$。因此答案小于等于 $n$。而 $n$ 为偶数时，我们的答案最多只能将所有位上的数变成一，所以答案为 $n$ 的位数的 $2$ 的幂减一。所以我们如果能构造出这样的序列，那么其结果肯定是最大的。
### Step 2：分析序列构造
首先考虑从 $n$ 的奇偶性质分析。\
若 $n$ 为奇数，考虑将最后一位放置 $n$，这样能够保证我们**可得到的最大值最大**。然后考虑将 $1\sim n-1$ 经过操作变成 $n$。由于 $1$ 或上 $n-1$ 等于 $n$，所以可以构造排列的末尾为 $1,n-2,n-1,n$ 使得结果为最大。无论前面经过什么操作，进入这个末尾时，或上 $1$，最后一位肯定是 $1$，然后与上 $n-2$ 这个奇数，肯定能保证最后一位是 $1$。然后或上 $n-1$，所得结果是 $n$，然后 $n$ 与上 $n$ 能够保证最终结果是 $n$。\
若 $n$ 为偶数，那么最后一次操作是或，若 $n$ 的二进制下的位数是 $s$，那么考虑在最后一位放上 $2^{s-1}-1$，这样可以保证最后一次或操作能够**使 $1$ 经可能的多**。但是还有首位上的 $1$ 没有考虑，所以考虑倒数第二位放上 $n$，这样 $n$ 或上 $2^{s-1}-1$ 等于 $2^s-1$。为了与上 $n$ 能够保留最高位的 $1$，我们希望倒数第三位放上 $n-1$，但是 $n$ 可能是 $100\dots 00$ 形式的，这样 $n-1$ 最高位是 $0$，所以末尾是 $n-1,n,2^{s-1}-1$ 是当 $n$ **不为二的幂**时。\
而当 $n=2^{s-1}$ 时，还是考虑最后两位是 $n,n-1$，这样 $n$ 或上 $n-1$ 等于 $2^s-1$。然后考虑用前面的数凑出 $n$，保证 $n$ 与上 $n$ 是 $n$，考虑末尾是 $1,n-3,n-2,n,n-1$，这样 $1$ 与上 $n-3$ 末尾肯定是 $1$，然后在 $1$ 或上 $n-2$ 等于 $n$，这样就完成了构造。
### Step 3：归纳与总结
综上：当 $n$ 为奇数时，末尾构造 $1,n-2,n-1,n$；当 $n$ 为偶数且 $n≠2^s$ 时，末尾构造 $n-1,n,2^{s-1}-1$；当 $n$ 为偶数时且 $n=2^s$ 时，末尾构造 $1,n-3,n-2,n,n-1$。
### Step 4：代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		if(n&1){
			cout<<n<<endl;
			for(int i=1;i<=n-4;++i) cout<<i+1<<" ";
			cout<<1<<" "<<n-2<<" "<<n-1<<" "<<n<<endl;
		}else{
			int k=log2(n);
			cout<<int(pow(2,k+1))-1<<endl;
			if(int(pow(2,k))==n){
				for(int i=1;i<=n-5;++i) cout<<i+1<<" ";
				cout<<1<<" "<<n-3<<" "<<n-2<<" "<<n-1<<" "<<n<<endl;;
			}else{
				for(int i=1;i<=int(pow(2,k))-2;++i) cout<<i<<" ";
				for(int i=int(pow(2,k));i<=n-2;++i) cout<<i<<" ";
				cout<<n<<" "<<n-1<<" "<<int(pow(2,k))-1<<endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：liugh_ (赞：1)

## [Alya and Permutation](https://codeforces.com/problemset/problem/2035/C)

对 $n$ 的奇偶性分讨。若 $n$ 是奇数，最后一个操作是与，任何数与 $x$ 都不大于 $x$，于是考虑把 $n$ 放在最后，并用 $[1,n-1]$ 中的数中构造出 $n$。由 $n$ 是奇数可知 $1\mid(n-1)=n$，我们需要或两次，同时还要找到一个数使得与上它不影响。要使 $1$ 不被与掉，找一个奇数即可，于是答案序列的末尾可以是 $1,n-2,n-1,n$。

记 $h=2^{\lfloor \log_2 n\rfloor}$。若 $n$ 是偶数，最后一个操作是或。如果能或上 $h-1$ 和 $n$，就能得到最大的答案。同样的，我们需要找到一个数使得与上它不影响，然而若先或上 $h-1$，不论怎么选都会产生影响，于是考虑先或上 $n$，那么只需使 $n$ 的最高位不被与掉，取 $n-1$ 即可，于是答案序列的末尾可以是 $n,n-1,h-1$。

值得注意的是当 $n=h$ 时策略有误，因为我们无法找到一个数使得与上它不影响，此时我们只能尝试用 $[1,n-2]$ 中的数构造出 $n-1$，最后与上 $n-1$ 再或上 $n$。$n-2$ 与 $n-1$ 是最相近的，只差了最低位，那我们再或上 $1$ 是不是就行了？要使 $1$ 不被与掉，找一个奇数即可，于是答案序列的末尾可以是 $1,n-3,n-2,n-1,n$。

---

## 作者：lgx57 (赞：1)

一道神仙构造题。~某位 CM 巨佬不会做，我不说是谁~。

赛时用打表发现了一个神奇的规律，但是不知道怎么证，看着像是对的，结果就对了。

考虑构造如下：

首先令 $p_1=2,p_2=1,p_i=i,( 3\le i \le n)$

如果 $2\mid n$，那么再分两种情况：

1. 若 $n=2^k,k \in Z^{+}$：那么重置第一次的操作，把他变成 $p_i=i,(1 \le i \le n)$。然后交换 $p_{n-2}$ 和 $p_{n-3}$。

2. 否则，找出**最大**的正整数 $k$ 使得 $2^k \le n$，然后把它放到最前面来。

综上，我们完成了这一题的构造。但是我不会证明他的最优性，如果证出来了可以私信我。

[赛时代码](https://codeforces.com/problemset/submission/2035/288348849)

---

## 作者：nothing__ (赞：0)

感谢管理员大大不离不弃一直审核。

对于这题，我们需要分类讨论：

观察样例我们不难发现当 $n$ 是奇数时，$k$ 的最大值为 $n$；当 $n$ 是偶数时，我们 $1$ 到 $n-1$ 扫一遍，对于每一个数或上 $n$，其中最大的就是 $k$。

那么这样的话，我们其实只用考虑最后的三或四个数。

对于偶数：

* 对于倒数第三位，我们 $1$ 到 $n-1$ 扫一遍，找到一个 $j$，使得 $(j|1|n)=k_{max}$，为什么要先或上 $1$ 呢。比如 $6|8=14$，而如果我们使前面的 $k$ 保留最低位的 $1$，那么 $6|8|1=15$ 此时的 $k$ 才最大。如何使前面的 $k$ 保留最低位的 $1$ 呢，我们只需要在倒数第四个位置给出一个奇数就好了。
* 对于倒数第二位，我们同样 $1$ 到 $n-1$ 扫一遍，寻找一个 $p$ 使得 $((j\&p)|n)=k$。
* 对于倒数第一位，我们直接输出 $n$。

对于奇数：

* 把他处理成偶数即可，对于最后四位：$j, p, n-1, n$，其中的 $j$,$p$ 是对于 $n-1$ 的倒数位。

具体实现如下：
```c++
#include<bits/stdc++.h>
using namespace std;
int read() {
	int x=0, w=1; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') w=-1; ch=getchar();}
	while(isdigit(ch)) {x=x*10+(ch-'0'); ch=getchar();}
	return x*w;
}
int main() {
	int T; T=read();
	while(T--) {
		int n; n=read();
		if(n%2==0) {
			int mx=0, j, k, jj;
			for(int i=1;i<n;i++) {
				if((i|n|1)>mx) mx=i|n|1, j=i|1, jj=i;
			}
			for(int i=1;i<n;i++) {
				if(((j&i)|n)==mx&&jj!=i) {k=i; break;}
			}
			printf("%d\n", mx);
			int c;
			for(int i=1;i<=n;i+=2) {
				if(i!=jj&&i!=k) {c=i; break;}
			}
			for(int i=1;i<n;i++) {
				if(i!=jj&&i!=k&&i!=c) printf("%d ", i);
			}
			printf("%d %d %d %d\n", c, jj, k, n);
		}
		else {//奇数就不用考虑倒数第四位了，因为最后一位n本身就是奇数
			int j, k;
			for(int i=1;i<n-1;i++) {
				if((i|(n-1))==n) {j=i; break;}
			}
			for(int i=1;i<n;i++) {
				if(((j&i)|(n-1))==n&&j!=i) {k=i; break;}
			}
			printf("%d\n", n);
			for(int i=1;i<n-1;i++) {
				if(i!=j&&i!=k) printf("%d ", i);
			}
			printf("%d %d %d %d\n", j, k, n-1, n);
		}
	}
	return 0;
}
```

---

