# [ABC336C] Even Digits

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc336/tasks/abc336_c

非負整数 $ n $ が次の条件を満たすとき、$ n $ を **良い整数** と呼びます。

- $ n $ を $ 10 $ 進法で表したときに、偶数の数字 $ (0,\ 2,\ 4,\ 6,\ 8) $ のみが登場する。
 
例えば $ 0 $、$ 68 $ および $ 2024 $ は良い整数です。

整数 $ N $ が与えられます。良い整数のうち小さい方から $ N $ 番目の整数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{12} $
- $ N $ は整数
 
### Sample Explanation 1

良い整数を小さい方から順に並べると $ 0,\ 2,\ 4,\ 6,\ 8,\ 20,\ 22,\ 24,\ 26,\ 28,\ \dots $ となります。 小さい方から $ 8 $ 番目の良い整数は $ 24 $ なので、これを出力します。

## 样例 #1

### 输入

```
8```

### 输出

```
24```

## 样例 #2

### 输入

```
133```

### 输出

```
2024```

## 样例 #3

### 输入

```
31415926535```

### 输出

```
2006628868244228```

# 题解

## 作者：2huk (赞：5)

## Solution1 二分 + 数位 DP

二分 $mid$，然后求 $0 \sim mid$ 中有多少个好整数。

发现这个形式很像数位 DP。于是套路的将 $mid$ 十进制拆分然后计算。

具体的是[代码](https://atcoder.jp/contests/abc336/submissions/49299679)。

## Solution2 五进制

我们可以将 $n$ 转化成五进制。例如 $(7)_{10} = (12)_5$。将这个五进制数看作是十进制数，然后将每一位乘 $2$。

注意题目中 $0$ 也算好整数，所以 $n$ 应当减一。所以上面说的实际上是 $n = 8$ 的情况。

时间复杂度 $\mathcal O(\log n)$。[代码](https://atcoder.jp/contests/abc336/submissions/49346832)。

---

## 作者：heyx0201 (赞：3)

# ABC336C Even Digits 题解
## Des.
> 给定一个 $N$，求第 $N$ 个好的整数，好的整数指的是每一位都为偶数（$0, 2, 4, 6, 8$）的数。

## Sol.
首先观察得出，$0 \sim 9$ 以内共有 $5$ 个偶数，所以每一位只有 $5$ 种可能。

然后枚举法：列出一开始的一些数。为了方便观察，这里标一下号（$0$ 开始）：
```
(0) 0, (1) 2, (2) 4, (3) 6, (4) 8, (5) 20, (6) 24, (7) 26, (8) 28, (9） 40, (10) 42, (11) 44, (12) 46, (13) 48, ......
```
然后，把这些序号转换成 $5$ 进制：
```
0, 1, 2, 3, 4, 10, 11, 12, 13, 14, 20, 21, 22, 23......
```
把他们和原数做对比：
```
0, 2, 4, 6, 8, 20, 22, 24, 26, 28, 40, 42, 44, 46......
0, 1, 2, 3, 4, 10, 11, 12, 13, 14, 20, 21, 22, 23......
```
~~你发现了吗~~发现：下面的数乘 $2$ 就等于上面的数！

而题目给出了序号，但是从 $1$ 开始，所以我们要将 $n$ 减去 $1$，然后转成五进制，最后乘二输出。

注意要特判 $n=1$ 的情况，因为 $n=1$ 那么 $n-1$ 就为 $0$，如果此时 $n=0$ 那么无法转成 $5$ 进制，因为进制转换要判断 $n \neq 0$，如果 $n$ 直接为 $0$，那么程序没有输出。

不过好像不一定要用数组，可以用 `vector`，一开始 `v.resize(1)`，处理完后如果 `v.size()` 还等于 $1$ 的话就直接输出，否则不输出前面的 $0$。

## Cod.
得到思路后，这题代码似乎非常简单，但还是贴一下吧。
```cpp
#include <bits/stdc++.h>

using namespace std;

long long n, a[70], tot;

int main() {
  cin >> n;
  n--;
  if (!n) {
    cout << 0;
    return 0;
  }
  for (; n; n /= 5) {
    a[++tot] = n % 5;
  }
  for (int i = tot; i; i--) {
    cout << a[i] * 2;
  }
  return 0;
}
```

---

## 作者：xz001 (赞：2)

首先按照题目要求，每个数位有 $5$ 种情况，因此第 $x$ 个数相当于把 $x$ 五进制分解后每一位乘二（因为只能是偶数），由于 $0$ 为第一个数，所以分解前 $x$ 要减一。

代码如下：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define swap(a, b) 	a ^= b, b ^= a, a ^= b
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int n, sum = 1, cnt;



stack <int> s;

signed main() {
    cin >> n;
    if (n == 1) {
    	puts("0");
    	return 0;
	}
    -- n;
    while (n) {
    	s.push(n % 5);
    	n /= 5;
	}
	while (s.size()) cout << s.top() * 2, s.pop();
    return 0;
}


```

---

## 作者：封禁用户 (赞：2)

这题真的很水，~~不过我赛时没做出来。~~

## 思路

我们可以将这道题转换后的数看成是由 $2,4,6,8,0$ 这五个数组成的五进制数。

那如何把转换后的数看成一个正常的五进制数呢？

这里，我们可以把上面的 $2,4,6,8,0$ 看成 $1,2,3,4,0$，也就是除上 $2$。所以输出的时候把经转换得到的正常的五进制数乘 $2$ 输出即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
signed main(){
	int n,ans=0,s=1;
	cin>>n;
	--n;//因为第1个符合要求的数是0，所以要减掉
	while(n){
		ans+=(n%5)*s;
		s*=10;
		n/=5;
	}cout<<ans*2<<endl;
	return 0;
}
```

---

## 作者：Guizy (赞：1)

## 题目大意

给你一个 $n$，求第 $n$ 个用偶数组成的自然数。

## 思路

一开始，我先想把它转换成 $5$ 进制，再处理输出。但是，这样做出来，每个答案都多 $2$。因为第一个数字是 $0$，所以我们要算的是 $n-1$。

## 实现

- 注意特判 $n=1$ 的情况，因为这时 $n-1=0$，可能会什么也不输出。

- 给 $0,2,4,6,8$ 打个表，处理会更方便。

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n;
int ans[100001],cnt;
int b[5]={0,2,4,6,8};//表

int main(){
	
	scanf("%lld",&n);
	if(n==1){//特判
		printf("0");
		return 0;
	}
	n--;
	
	while(n){
		ans[++cnt]=b[n%5];//转5进制
		n/=5;
	}
	for(int i=cnt;i>=1;i--){
		printf("%lld",ans[i]);
	}
	
	return 0;
}
```

---

## 作者：BIG_CUTE_BUG (赞：0)

[题传](https://www.luogu.com.cn/problem/AT_abc336_c)

## 思路

不难发现，这题本质是将一个十进制数 $n_{10}$ 转为五进制数 $n_5$，最后将每位数位上的数字 $\times 2$。


但注意，$n_{10}$ 是从 $1$ 开始编号的，$n_5$ 是从 $0$ 开始编号的，所以还得将 $n_{10}-1$ 才可一一对应。

求得时候就先将 $n_{10}-1$，然后从大到小拆位即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[20];
signed main()
{
	long long n;
	cin>> n; n--;
	if(!n) putchar('0'), exit(0); //0 的时候特判
	a[0]= 1; bool t= 0;
	for(int i= 1; i<= 17; i++) a[i]= a[i- 1]* 5; //预处理 5 的次幂
	for(int i= 17; i>= 0; i--) //从大到小拆位
	{
		if(a[i]<= n)
		{
			cout<< (n/ a[i])* 2;
			n%= a[i];
			t= 1;
		}
		else if(t) cout<< 0;
	}
	return 0;
}
```

---

## 作者：Cure_Wing (赞：0)

[AT_abc336_c [ABC336C] Even Digits](https://www.luogu.com.cn/problem/AT_abc336_c)

### 思路

我们观察到，每一位的数字都有 $0,2,4,6,8$ 五个数字可填，但当位数大于 $1$ 时首位不能为 $0$，于是我们得到位数为 $i(i>1)$ 的良心的数有 $4\times5^{i-1}$ 个。我们发现，如果位数为 $q$ 的最高位要进 $1$ 那么最多要经过 $5^{q-1}$ 个数。我们把位数 $(1\sim p)$ 的良心的数的个数相加，如果这个结果恰好大于或等于 $N$，那么我们就得到了 $N$ 的位数 $p$。我们在倒推回去，将 $N$ 除以在当前长度下遍历一次需要的数的个数，就是 $N$ 在第 $p$ 位遍历的次数。再乘以 $2$ 就是对应位置的值。我们把 $N$ 对上一个和取模，得到的就是 $N$ 在 $p$ 位良心的数的排名。如此反复即可得到原数。但是考虑到一位良心的数有 $5$ 个，不符合规律，于是我们对 $0$ 特判，然后将 $N$ 减一，在如上做就没有问题了。

时间复杂度 $O(\log_5N)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
long long n,ans,l[25];
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;if(n==1){cout<<0;return 0;}
	l[1]=1;l[2]=5;--n;//懒得做的话直接从足够高的位往下做就可以了，不需要求位数
	for(int i=3;i<=22;++i) l[i]=l[i-1]*5;//处理遍历一次需要的数
	for(int i=22;i>=1;--i){
		ans=ans*10+n/l[i]*2;//相除得答案
		n%=l[i];//取余继续算
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Saint_ying_xtf (赞：0)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

这一道题，我们看到 $(0,2,4,6,8)$。就想着是不是可以等效为 $(0,1,2,3,4)$。

我们就想到可以用五进制来解决，因为第 $n$ 个数可以理解为 $n$ 转成五进制，但是发现第 $1$ 个数为 $0$。所以我们将 $n-1$ 转成五进制，然后直接每一位乘 $2$ 即可。

```cpp
int n;
stack<int> st;

void solve(){
	cin >> n;
	if(n==1){
		cout<<0;
		exit(0);
	}n--;
	while(n){
		st.push(n%5);n/=5;
	}while(!st.empty()) {
		cout<<st.top() * 2;
		st.pop();		
	}
}
```

---

