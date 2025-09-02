# Exam in MAC

## 题目描述

The Master's Assistance Center has announced an entrance exam, which consists of the following.

The candidate is given a set $ s $ of size $ n $ and some strange integer $ c $ . For this set, it is needed to calculate the number of pairs of integers $ (x, y) $ such that $ 0 \leq x \leq y \leq c $ , $ x + y $ is not contained in the set $ s $ , and also $ y - x $ is not contained in the set $ s $ .

Your friend wants to enter the Center. Help him pass the exam!

## 说明/提示

In the first test case, the following pairs are suitable: $ (0, 0) $ , $ (2, 2) $ , $ (3, 3) $ .

In the third test case, the following pairs are suitable: $ (0, 1) $ , $ (0, 2) $ , $ (0, 4) $ , $ (1, 3) $ , $ (2, 6) $ , $ (3, 4) $ , $ (3, 5) $ , $ (4, 5) $ , $ (4, 6) $ , $ (5, 6) $ .

## 样例 #1

### 输入

```
8
3 3
1 2 3
1 179
57
4 6
0 3 5 6
1 1
1
5 10
0 2 4 8 10
5 10
1 3 5 7 9
4 10
2 4 6 7
3 1000000000
228 1337 998244353```

### 输出

```
3
16139
10
2
33
36
35
499999998999122959```

# 题解

## 作者：66xyyd (赞：7)

## 题意

每一次询问给出一个集合 $s$ 和一个整数 $c$，问有多少对 $(x,y)$ 满足 $0 \le x \le y \le c$ 且 $x+y$ 和 $y-x$ 都不在集合 $s$ 里。
## 题解
### 条件1
先只考虑 $0 \le x \le y \le c$ 这个条件，想一想可知一共有 $(c+1)^2-\frac{1}{2}c(c+1)$ 种情况（对应我代码中的 `_f1` 函数），记为满足条件 $1$ 下的数量。
### 条件2
然后考虑 $0 \le x \le y \le c$ 且 $x+y \in s$ 的情况。对于每一个在 $s$ 中的数 $a$，考虑 $x+y=a$：
$$
\because a-y=x \le y\\
\therefore \lceil\frac{a}{2}\rceil \le y \le a\\
$$
一共 $a-\lceil\frac{a}{2}\rceil+1$ 种情况（对应我代码中的 `_f2` 函数），记为满足条件 $2$ 下的数量（取所有 $a \in s$ 之和）。
### 条件3
考虑 $0 \le x \le y \le c$ 且 $y-x \in s$ 的情况。对于每一个在 $s$ 中的数 $a$，考虑 $y-x=a$：
$$
\because 0 \le x+a=y \le c\\
\therefore 0 \le x+a \le c\\
\therefore 0 \le x \le c-a
$$
一共 $c-a+1$ 种情况（对应我代码中的 `_f3` 函数），记为满足条件 $3$ 下的数量（取所有 $a \in s$ 之和）
### 条件4
考虑 $0 \le x \le y \le c$ 且 $x+y \in s$ 且 $y-x \in s$ 的情况。设 $y-x=a$ 且 $x+y=b$：
$$
\because a+b=(y-x)+(x+y)=2y\\
\therefore 2 \mid a+b
$$
也就是说 $a+b$ 的奇偶性相同。记集合 $s$ 中有 $x$ 个偶数，那么在这种条件下应该有 $\frac{1}{2}x(x+1)$ 种情况。考虑到 $c-x$ 个奇数的话一共就是 $\frac{1}{2}x(x+1)+\frac{1}{2}(c-x)(c-x+1)$ 种情况（对应我代码中的 `_f4` 函数），记为满足条件 $4$ 下的数量。
### 加总
现在来考虑原题目条件。既然要求 $x+y$ 和 $y-x$ 都不在集合 $s$ 中，那么就要从满足条件 $1$ 下的数量中分别扣除满足条件 $2$ 下和满足条件 $3$ 下的数量；同时加上被重复计算的满足条件 $4$ 下的数量。（容斥原理）

代码：
```cpp
#include<iostream>
using namespace std;
long long s[300001];
int n;
long long c;
//这些函数刚刚解释过了
inline long long _f1(long long x){
	return (x+1)*(x+1)-(x+1)*x/2;
}
inline long long _f2(long long x){
	return x-(x+x%2)/2+1;
}
inline long long _f3(long long x){
	return (c-x+1);
}
inline long long _f4(long long x){
	return (x*(x+1)/2+(n-x)*(n-x+1)/2);
}
int main(){
	int T;
	cin >> T;
	while(T--){
		long long cnt1=0;
		cin >> n >> c;
		for(int i=1;i<=n;i++){
			cin >> s[i];
			if(s[i]%2==0)	++cnt1;
		}
		long long ans=_f1(c);
		for(int i=1;i<=n;i++){
			//枚举集合中的每一个元素并分别扣除
			ans-=_f2(s[i]);
			ans-=_f3(s[i]);
		}
		ans=ans+_f4(cnt1);
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：5)

![](https://cdn.luogu.com.cn/upload/image_hosting/obhoj4m8.png)

（开赛 $13$ 分钟排行榜 /se /se）

$\textbf{CF1935D *1800}$

> - 给你一个集合 $s$，问有多少数对 $(x,y)$ 满足 $0 \le x \le y \le c$ 且 $y+x,y-x$ 都不在集合 $s$ 中。
> - $1 \le |s| \le 3 \cdot 10^5,0 \le c \le 10^9$。

考虑容斥，答案为数对 $(x,y)$ 的数量减去 $y+x,y-x$ 至少有一个在 $s$ 里的数量，加上 $y+x,y-x$ 都在 $s$ 里的数量。

第一部分是 $\dfrac{(c+1)(c+2)}{2}$，第二部分是 $\sum \limits_{i=1}^n (n-s_i+1)+(\lfloor \dfrac{s_i}{2} \rfloor +1)$，其中前面是是差为 $s$，后面是和为 $s$，注意要保证 $x \le y$。

考虑第三部分的计数，枚举 $x+y = s_i$，相当于问前面有多少 $j$ 满足 $y+x=s_i,y-x=s_j(j \le i)$ 有解且解合法（$0 \le x \le y \le c$）。通过初中数学知识不难解得 $y = \dfrac{s_i+s_j}{2},x = s_i - \dfrac{s_i+s_j}{2}$。首先只有 $s_i \equiv s_j \pmod 2$ 时 $x,y$ 为整数，又注意到由于 $s_j \le s_i$，因此解出的 $x,y$ 一定满足条件，即只需要统计对于 $s_i$ 前面有多少 $s_j$ 与之奇偶性相同，前缀和即可。

题目给出的 $s$ 已经有序，时间复杂度 $\mathcal O(n)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 05.03.2024 22:41:29
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,c,a[N];
void los(){
    cin >> n >> c;
    ll ans = 1ll * (c + 1) * (c + 2) / 2,sum = 0; int ct0 = 0,ct1 = 0;
    for(int i = 1;i <= n;i ++) cin >> a[i],sum += c - a[i] + 1 + a[i] / 2 + 1;
    for(int i = 1;i <= n;i ++){
        ct1 += (a[i] & 1),ct0 += !(a[i] & 1),
        sum -= (a[i] & 1) ? ct1 : ct0;
    }cout << ans - sum << "\n";
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}   
```

---

## 作者：Alex_Wei (赞：4)

### [CF1935D Exam in MAC](https://www.luogu.com.cn/problem/CF1935D)

限制有两条，直接做困难。钦定在集合 $S$ 比钦定不在集合 $S$ 要容易地多，明显容斥。

- 对于 $x + y\in S$，方案数即 $A_0 = \sum_{s\in S} (1 + \lfloor \frac s 2 \rfloor)$；
- 对于 $y - x \in S$，方案数即 $A_1 = \sum_{s\in S} (c - s + 1)$；
- 对于 $x + y\in S$ 且 $y - x \in S$，对于每一对 $s, s'\in S$，如果它们奇偶性相同，则产生 $1$ 组方案。方案数为 $A_2 = \binom {\mathrm{odd} + 1} 2 + \binom {\mathrm{even} + 1} 2$。

答案即 $\binom {c + 2} 2 - A_0 - A_1 + A_2$。

时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1935/submission/250200684)。

---

## 作者：2huk (赞：3)

给定一个集合 $S = \{s_1, s_2, \dots, s_n\}$ 和一个正整数 $c$。保证 $0 \le s_1 < s_2 < \dots < s_n \le c$。

求满足以下条件的二元组 $(x, y)$ 的数量：

- $x, y \in \mathbb Z$；
- $0 \le x \le y \le c$；
- $x+y \not \in S$；
- $y-x \not \in S$。

---

总共 $4$ 个条件。显然条件 $1, 2$ 并不困难，但是直接做条件 $3, 4$ 不好做。

冥显容斥。如果我们令：

- 满足条件 $1, 2$ 的方案数为 $A$；
- 满足条件 $1, 2$ 且不满足条件 $3$ 的方案数为 $B$；
- 满足条件 $1, 2$ 且不满足条件 $4$ 的方案数为 $C$；
- 满足条件 $1, 2$ 但不满足条件 $3, 4$ 的方案数为 $D$；

那么答案为 $A - B - C + D$。考虑分别求解。

> $A$：
>
> - $x, y \in \mathbb Z$；
> - $0 \le x \le y \le c$。

来搞笑的。答案为 $\binom {c+1}2 + c + 1$。

> $B$：
>
> - $x, y \in \mathbb Z$；
> - $0 \le x \le y \le c$；
> - $x+y \in S$。

我们可以枚举 $s_i$。问题变为有多少个 $0 \sim c$ 的整数 $x \le y$ 满足 $x + y = s_i$。

不难发现答案为 $\lceil \frac {s_i + 1}2 \rceil$。

> $C$：
>
> - $x, y \in \mathbb Z$；
> - $0 \le x \le y \le c$；
> - $y-x \in S$。

仍然枚举 $s_i$，转化成有多少个 $0 \sim c$ 的整数 $x \le y$ 满足 $x - y = s_i$。

可以发现，由于 $s_i$ 非负，所以 $x \le y$ 这个条件天然满足了。所以对于每一个 $x$ 都能找到一个合法的 $y$ 满足条件。因此方案数为合法的 $x$ 的数量。

不难发现答案为 $c - s_i + 1$。

> $D$：
>
> - $x, y \in \mathbb Z$；
> - $0 \le x \le y \le c$；
> - $x+y \in S$；
> - $y-x \in S$。

为了看的清楚，我们将 $x+y$ 改成 $y+x$，即 $y+x, y-x \in S$。 

观察一下 $y-x, y+x$ 在数轴上有什么特点：

![](https://cdn.luogu.com.cn/upload/image_hosting/s6t9i74v.png)

也就是 $y$ 是 $y - x$ 和 $y + x$ 的中点。

对于 $S$ 中的元素 $s_i, s_j$，如果两个数 $x, y$ 使得 $y-x = s_i$ 且 $y+x=s_j$，就意味着 $y = \frac 12(s_i + s_j)$。

显然 $y$ 需要是一个整数。这也就意味着 $s_i \equiv s_j \pmod 2$。

所以讨论奇偶性即可。令有 $p$ 个 $s_i$ 为奇，$q$ 个 $s_i$ 为偶，那么答案为 $\binom p2 + p + \binom q2+q$。

---

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
typedef long long ll;
typedef unsigned long long LL;
typedef pair<int, int> PII;

struct FASTREAD {
	template <typename T>
	FASTREAD& operator >>(T& x) {
		x = 0; bool flg = false; char c = getchar();
		while (c < '0' || c > '9') flg |= (c == '-'), c = getchar();
		while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
		if (flg) x = -x; return *this;
	}
	template <typename T>
	FASTREAD& operator >>(vector<T>& x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) >> *it;
		return *this;
	}
}fin;

struct FASTWRITE {
	template <typename T>
	FASTWRITE& operator <<(T x) {
		if (x < 0) x = -x, putchar('-');
		static int buf[35]; int top = 0;
		do buf[top ++ ] = x % 10, x /= 10; while (x);
		while (top) putchar(buf[ -- top] + '0');
		return *this;
	}
	FASTWRITE& operator <<(char x) {
		putchar(x); return *this;
	}
	template <typename T>
	FASTWRITE& operator <<(vector<T> x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) << *it, putchar(' ');
		putchar('\n');
		return *this;
	}
}fout;

const int N = 1e6 + 10;
const int P = 998244353;

int n, c, a[N];

void Luogu_UID_748509() {
	fin >> n >> c;
	int res = (c + 1) * c / 2 + c + 1;
	int c0 = 0, c1 = 0;
	while (n -- ) {
		int x; fin >> x;
		res -= (x + 2) / 2 + (c - x + 1);
		(x % 2 ? c0 : c1) ++ ;
	}
	if (c0) res += c0 * (c0 - 1) / 2 + c0;
	if (c1) res += c1 * (c1 - 1) / 2 + c1;
	fout << res << '\n';
	return;
}

signed main() {
	int Testcases = 1;
	fin >> Testcases;
	while (Testcases -- ) Luogu_UID_748509();
	return 0;
}
```

---

## 作者：fast_photon (赞：2)

## CF1935D  

### 1. 题意  
给你一个正整数 $c$ 和一个自然数集合 $S$（值域为 $c$），问有多少组 $0\le x\le y\le c$，满足 $x+y\notin S,y-x\notin S$。  
$1\le n\le 3\times 10^5,1\le c\le 10^9$

### 2. 分析  
问有多少组值域内的 $x\le y$ 使得 $x+y\in S$ 显然是好做的，遍历 $S$ 并计算即可。  
所以可以考虑容斥。  
为了方便，可以数形结合。我们取横纵坐标均在 $[0,c]$ 的整点。  
+ $x+y\in S$。  
这种相当于若干条在 $x+y=c$ 以下的斜率为 $-1$ 的直线。我们只保留 $y=x$ 以上的部分。  
这一部分的结果等于 $\sum\limits_{x\in S}(\lceil x+1\rceil )$。  
+ $y-x\in S$。  
因为 $x\le y$，所以总有 $0\le y-x\le c$。满足条件的线相当于 $y=x+b$。  
这一部分的结果等于 $\sum\limits_{x\in S}(c-x+1)$。
+ $y-x\in S,x+y\in S$  
即算 $[0,c]-[0,c]$ 正方形内的交点个数。  
若 $a=x+y,b=y-x$，则 $x=\frac{a-b}{2},y=\frac{a+b}{2}$，列出不等式可以发现，$0\le x\le y\le c$ 对于 $0\le b\le a\le c$ 总成立。  
所以只需要额外保证 $a\equiv b\mod 2$。  
这一部分的结果等于 $S$ 中奇偶性相同的无序对个数。  
+ $y-x\notin S,x+y\notin S$  
用 $0\le x\le y\le c$ 的个数减去前两类，加上第三类即可。即容斥。  

长度为 $n$ 的序列中，若元素两两不同，则无序二元组的个数为 $\frac{n(n+1)}{2}$。  

### 3. 代码  
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<algorithm>
#define maxn 200005
#define int long long

using namespace std;


int n, c, sum, cnt0, cnt1;

void work() {
	sum = cnt0 = cnt1 = 0;
	cin >> n >> c;
	int a;
	sum = (c + 1) * (c + 2) / 2;
	for(int i = 1; i <= n; i++) {
		cin >> a;
		sum -= (a + 2) / 2; //第一部分减掉
		sum -= (c - a + 1); //第二部分减掉
		if(a & 1) cnt1++; //奇偶分开统计
		else cnt0++;
	}
	sum += cnt1 * (cnt1 + 1) / 2; //加上
	sum += cnt0 * (cnt0 + 1) / 2; //加上
	cout << sum << '\n';
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int _; cin >> _; while(_--) work();
} 
```

---

## 作者：2020kanade (赞：1)

讲真，这题该和 C 题换个位置，$1500$ 不能再难了，高中数学没学到当我没说。

考虑所有可能的数对一共有四种：合法、违反第一类、违反第二类以及一二类都违反。根据人类智慧容斥原理，从前往后分别设它们的数量为 $A,B,C,D$，答案是 $A-B-C+D$。

由高中数学知识我们可得 $A=\frac{(c+1)(c+2)}{2},B=\sum (\lfloor \frac{a_i}{2}\rfloor +1),C=\sum (c-a_i+1)$，第一个用等差数列求和公式，后两个打表都能打出来。

对于 $D$ 的计算，我们考虑以下的二元一次方程组：

$
\left\{ 
  	\begin{array}{c}
    x+y=d_1
    \\y-x=d_2 
    \end{array}
\right. 
$

解得

$
\left\{ 
  	\begin{array}{c}
    x=\frac{d_1-d_2}{2}
    \\y=\frac{d_1+d_2}{2}
    \end{array}
\right. 
$

由数对的合法性限制，我们要求 $d_1\ge d_2$ 且它们奇偶性相同（否则不是整数）。

由上面的二元一次方程组的解，当 $x,y$ 唯一时，将 $d_1,d_2$ 视为未知数，则方程组有唯一解。换言之，一对 $(d_1,d_2)$ 可以确定唯一的一对同时违反两种约束的 $(x,y)$，这一部分转化为 $(d_1,d_2)$ 的计数。

注意到题中所给集合各数均不同，结合我们上面的推论可得出，对于每个 $d_1$，合法的 $d_2$ 满足 $d_2\le d_1$ 且 $d_2$ 与 $d_1$ 奇偶性一致。

由于输入数据有序，对元素分奇偶后读入时在线计算即可。

时间复杂度 $\Theta(n)$。

```cpp
//written by Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
void syncoff()//fuck you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
#define endl '\n'
const int N=5e5+11;
using ll=long long;
using i128=__int128;
using ld=long double;
const ll JT=998244353;
const ll GEH=1e9+7;
const ll ZLH=1e9+9;
int t,n,k,m,q;
void solve()
{
	ll c;
	ll ans1=0,ans2=0,ans3=0,ans4=0;
	cin>>n>>c;ans1=1ll*(1ll+c)*(c+2ll)/2ll;
	vector<ll> drc1(n+3,0),drc2(n+3,0),c1(n+3,0),c2(n+3,0),a(n+3,0);
	vector<ll> ods(n+3,0),eds(n+3,0);
	int lst1=0,lst2=0;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		ans2+=a[i]/2+1;ans3+=c-a[i]+1;
		if(a[i]&1) c1[++lst1]=a[i],ans4+=(lst1);
		else c2[++lst2]=a[i],ans4+=(lst2);
	}
	cout<<ans1-ans2-ans3+ans4<<endl;
}
int main()
{
    cin>>t;
    while(t--) solve();
    return 0;
}

```

---

## 作者：OPEC (赞：0)

解题一共有 $4$ 个部分: 

1. 一共有 $\frac{(c+1)\times(c-1)}{2}$ 种方案。

2. $x+y$ 不成立的有 $\frac{\sum^{n}_{i=1}a_i}{2}+1$ 种方案。

3. $x-y$ 不成立的有 $\sum^{n}_{i=1}c-a_i+1$ 种方案。

4. $x+y$ 和 $x-y$ 都不成立时，减去 $\frac{o \times (o−1)}{2}+\frac{e ×(e−1)}{2}$ 种方案。

其中 $o$ 为奇数个数，$e$ 为偶数个数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=3e5+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t,n,c;
int a[N];
void solve()
{
	cin>>n>>c;
	int odd=0,even=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]%2)
		{
			odd++;
		}
		else
		{
			even++;
		}
	}
	int tmp=odd*(odd-1)/2+even*(even-1)/2;
	int sum=(c+1)*(c+2)/2;
	for(int i=1;i<=n;i++)
	{
		int t1=a[i]/2+1;
		int t2=c-a[i]+1;
		sum-=t1+t2-1;
	}
	sum+=tmp;
	cout<<sum<<'/n';
}
signed main()
{
	fst
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：liluhexuan (赞：0)

很明显，如果要正着得到答案，是不好求的。所以，我们可以换一种思路，求总方案数，减去不合法的方案数，这样的时间复杂度是 $O(n)$。

求解分为四个部分：

1. 总方案数有 $(c+1)\times (c+2) \div 2$ 个。
2. $x+y$ 不成立的有 $\sum_{i=1}^n a_i \div 2+1$ 个。
3. $x-y$ 不成立的有 $\sum_{i=1}^n c-a_i+1$ 个。
4. 又因有一些时候 $x+y$ 等于 $y-x$，所以还要减去 $odd^* \times (odd-1) \div 2+even^* \times (even-1) \div 2$ 个

最后，又因为 $0+x=x-0$，所以要减去 $n$ 种方案。成型之后就是 $(c+1)\times (c+2) \div 2 - \sum_{i=1}^n a_i \div 2+1 - \sum_{i=1}^n c-a_i+1 +n +odd \times (odd-1) \div 2+even \times (even-1) \div 2$

```cpp
#include<iostream>
using namespace std;
#define int unsigned long long
const int N=3e5+10;
int n,c,a[N];
void slove(){
	cin>>n>>c;
	int x=0,y=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]%2==1) x++;
		else y++;
	}
	x=x*(x-1)/2,y=y*(y-1)/2;
	int sum=(c+1)*(c+2)/2;
	for(int i=1;i<=n;i++){
		int t1=a[i]/2+1;
		int t2=c-a[i]+1;
		sum=sum-t1-t2+1;
	}
	cout<<sum+x+y<<endl;
}
signed main(){
	int T;
	scanf("%lld",&T);
	while(T--) slove();
	return 0;
}
```
本蒟蒻的第一篇题解，求通过。

$odd^* $ 代表奇数个数，$even^* $ 代表偶数个数。

---

## 作者：mountain_climber (赞：0)

### CF1935D *1800

观察发现这道题要计数的解有 $4$ 个性质，分别是：

- 性质一：$x,y \in \mathbb{Z}$
- 性质二：$0 \leq x \leq y \leq c$
- 性质三：$x+y \notin \mathbb{S}$
- 性质四：$y-x \notin \mathbb{S}$

如果直接求解会比较麻烦，但是不难发现，最终求的解集可以用容斥原理拆分，集合关系具体如下图：

![图1.1](https://cdn.luogu.com.cn/upload/image_hosting/h59opyxj.png)

由于求的是红色集合的大小（计数）而不是输出元素，所以分别讨论以下四个集合的大小即可。

1. 满足性质一、性质二集合的大小

不难发现，就是从 $c+1$ 个数中选两个数，可以相等，考虑到他们可以相等还具有大小关系，所以分开计算两个数不同的情况和两个数相同的情况，两部分加起来就是 $\frac{(c+1) \times c}{2}+(c+1)$。

2. 满足性质一、性质二、不满足性质三集合的大小

不满足性质三，就是满足 $x+y \in \mathbb{S}$。要统计这个数量，可以对于每个 $s_{i}$，进行统计，可以十分容易的发现总数是 $\lceil \frac{s_{i}+1}{2} \rceil$。具体来说，就是从 $(0,s_{i})$ 到 $(\lfloor \frac{s_{i}}{2} \rfloor, s_{i}-\lfloor \frac{s_{i}}{2} \rfloor)$ 的数量，建议读者举例子推导。

3. 满足性质一、性质二、不满足性质四集合的大小

不满足性质四，就是满足 $y-x \in \mathbb{S}$。要统计这个数量，同样可以对于每个 $s_{i}$，进行统计。转换一下，发现对于所有 $s_{i} \leq y \leq c$，都能找到对应的 $x$ 使其满足 $y-x=s_{i}$。所以总数就是 $c-s_{i}+1$。

4. 满足性质一、性质二、不满足性质三且不满足性质四集合的大小

不满足性质三，且不满足性质四，就是满足 $x+y \in \mathbb{S}, y-x \in \mathbb{S}$，图形化一下：

![图1.2](https://cdn.luogu.com.cn/upload/image_hosting/44l4bmxq.png)

之后发现，只要两个点的中点坐标是整数，也就是 $(s_{i}-s{j}) \bmod 2=0$，换句话说只要 $s_{i} \equiv s_{j}(\bmod 2)$ 就存在满足条件的一组 $(x,y)$，所以我们只需要分别统计奇数和偶数的数量然后参照最开始推过式子，在偶数和奇数中分别统计即可，设有 $cnt_{1}$ 个奇数和 $cnt_{2}$ 个偶数，总数即为 $\frac{cnt1 \times c}{2}+cnt1+\frac{cnt2 \times c}{2}+cnt2$。

最终，我们可以推出整道题的答案：
$\frac{(c+1) \times c}{2}+(c+1)-\sum_{1}^{n} \lceil \frac{s_{i}+1}{2} \rceil-\sum_{1}^{n}(c-s_{i}+1)+\frac{cnt1 \times c}{2}+cnt1+\frac{cnt2 \times c}{2}+cnt2$。

最后贴一下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+10;
int t,n,c,a[N];
int clac(int x){
    return x*(x-1)/2;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin>>t;
    while(t--){
        cin>>n>>c;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        int aa=clac(c+1)+c+1,bb=0,cc=0,dd=0;
        for(int i=1;i<=n;i++){
            bb+=ceil(double((a[i]+1.0)/2.0));
            cc+=c-a[i]+1;
        }
        int cnt1=0,cnt2=0;
        for(int i=1;i<=n;i++){
            if(a[i]%2) cnt1++;
            else cnt2++;
        }
        dd=clac(cnt1)+clac(cnt2)+cnt1+cnt2;
        cout<<aa-bb-cc+dd<<endl;
    }
    return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## 题目大意

给定一个大小为 $n$ 的集合 $S$，其中元素大小 $\le c$，问满足以下条件的数对 $(x, y)$ 的个数有多少对：

1. $x, y \in \mathbb{Z}, 0 \le x \le y \le c$。
2. $x + y \notin S, y - x \notin S$。

$1 \le n \le 3 \times 10^5, 0 \le c \le 10^9$。

## 题目思路

首先发现这个一看就很容斥的样子，考虑容斥完我们要计算什么：

$$ans = \sum_{i = 0}^c \sum_{j = i}^c 1 - \sum_{i = 0}^c \sum_{j = i}^c [i + j \in S] - \sum_{i = 0}^c \sum_{j = i}^c [j - i \in S] + \sum_{i = 0}^c \sum_{j = i}^c [i + j \in S] \times [j - i \in S]$$

考虑第一项的值，就是 $\frac{(c + 1)(c + 2)}{2}$。

考虑第二项的值，发现对于每一个 $i \le \frac{s_i}{2}$，都有一个与之对应的 $j$，就是 $\sum\limits_{i = 1}^n \left(\frac{s_i}{2} + 1\right)$。

考虑第三项的值，发现对于每一个 $s_i \le i \le c$，都有一个与之对应的 $j$，就是 $\sum\limits_{i = 1}^n \left(c - s_i + 1\right)$。

考虑第四项的值，在此之前，我们要想明白一个事情，对于一对 $(i, j)$ 如果产生贡献，那么**只会**对应到一组 $(s_x, s_y)$ 上，换句话说，$i = \frac{s_x - s_y}{2}, j = \frac{s_x + s_y}{2}$，**当且仅当**满足这个条件，才会对答案产生贡献，不难发现就是奇数的 $s$ 两两组合，偶数的 $s$ 两两组合。

然后直接计算即可。

## 题目代码

Code：

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )
 
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;
 
char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}
 
template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }
 
const int N = 3e5 + 5;
 
int t, n, c;
int a[N];
 
void Solve () {
	cin >> t;
	while ( t -- ) {
		cin >> n >> c;
		for ( int i = 1; i <= n; i ++ ) {
			cin >> a[i];
		}
		int res = 0, res2 = 0, sum = 0;
		for ( int i = 1; i <= n; i ++ ) {
			res += ( a[i] & 1 );
			sum += a[i] / 2 + 1;
			sum += c - a[i] + 1;
		}
		res2 = n - res;
		cout << ( c + 1 ) * ( c + 2 ) / 2 - sum + res * ( res + 1 ) / 2 + res2 * ( res2 + 1 ) / 2 << '\n';
	}
}
 
signed main () {
#ifdef judge
	freopen ( "test.in", "r", stdin );
	freopen ( "test.out", "w", stdout );
	freopen ( "test.err", "w", stderr );
#endif
	Solve ();
	return 0;
}
```

---

## 作者：DerrickLo (赞：0)

简单容斥。

我们发现答案就是 $(x,y)$ 数对的总数减去满足 $x+y\in s$ 或 $y-x\in s$ 的数对 $(x,y)$ 的个数。

这个个数就能用容斥计算。令 $a=|\{(x,y)|x+y\in s\}|$，$b=|{\{(x,y)|y-x\in s\}}|$，$c=|\{(x,y)|(x+y\in s)\cap(y-x\in s)\}|$，那么个数就是 $a+b-c$。

然后我们考虑这三个数怎么算。

对于 $a$，枚举 $s_i$，很明显满足 $x+y=s_i$ 的 $x\le \lfloor\frac{s_i}{2}\rfloor$ ，那么 $(x,y)$ 的个数就是 $\lfloor\frac{s_i}{2}\rfloor+1$，求个和即可。

对于 $b$，同样地枚举 $s_i$，满足 $y-x=s_i$ 的 $x\le c-s_i$，那么 $(x,y)$ 的个数就是 $c-s_i+1$，加起来就是 $b$。

对于 $c$，考虑到若 $x+y=s_i$ 且 $y-x=s_j$，那么必然有 $2|s_i-s_j$，所以我们对于每个数求一下它前面有多少个与它同奇偶的数就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,c,s[300005];
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>c;
		for(int i=1;i<=n;i++)cin>>s[i];
		int ans=(c+1)*(c+2)/2;
		for(int i=1;i<=n;i++)ans-=s[i]/2+1;
		for(int i=1;i<=n;i++)ans-=c-s[i]+1;
		int cnt0=0,cnt1=0;
		for(int i=1;i<=n;i++){
			cnt0+=(s[i]%2==0),cnt1+=(s[i]%2==1);
			if(s[i]%2==0)ans+=cnt0;
			else ans+=cnt1;
		}
		cout<<ans<<"\n";
	}
}
```

---

## 作者：破壁人罗辑 (赞：0)

[题目传送门(洛谷)](https://www.luogu.com.cn/problem/CF1935D)

[题目传送门(codeforces)](https://codeforces.com/problemset/problem/1935/D)

## 题意简述：

给出两个整数 $c,n$ 和一个数集 $S=\{s_1,s_2,\cdots,s_n\}$，求出所有满足 $0\leq x\leq y\leq c,x+y\notin S,y-x\notin S$ 的数对 $(x,y)$ 的数量。

## 解题思路

考虑使用排除法：\
符合要求的数对个数等于总数对个数 $\frac{c(c+1)}{2}+c+1$ 减去不符合要求的数对个数。

满足 $x+y=s_i$ 的数对 $(x,y)$ 共有 $(0,s_i),(1,s_i-1),\cdots,(\lfloor\frac{s_i}{2}\rfloor,\lceil\frac{s_i}{2}\rceil)$ 共 $\lfloor\frac{s_i}{2}\rfloor+1$ 个。

满足 $y-x=s_i$ 的数对 $(x,y)$ 共有 $(0,s_i),(1,s_i+1),\cdots,(c-s_i,c)$ 共 $c-s_i+1$ 个，其中存在部分数对 $(x,y)$ 即 $(x,x+s_i)$ 满足 $2x+s_i=x+y=s_j$，个数为数集中奇偶性与 $s_i$ 相同且大于等于 $s_i$ 的元素个数。

数集按照从小到大的顺序给出，所以读入时可以直接预处理出数集中的奇偶数个数，然后从小到大扫一遍，对于每一个 $s_i$ 进行相应的操作即可。

## 代码展示

AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[300000];
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,c,k[2]={0,0};scanf("%d%d",&n,&c);
		long long ans=c+1+(((c+1)*(long long)c)>>1);
		for(int i=0;i<n;i++){
			scanf("%lld",a+i);
			ans-=(a[i]>>1)+1;
			k[a[i]&1]++;
		}
		for(int i=0;i<n;i++){
			k[a[i]&1]--;
			ans-=c-a[i]-k[a[i]&1];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：bluewindde (赞：0)

题意：给定集合 $s$，$|s| = n$，值域 $c$，求满足 $0 \le x \le y \le c$，且 $x + y \notin s$，$y - x \notin s$ 的数对 $(x, y)$ 数量。

考虑对于每个 $i = y - x$ 计数。（因为对 $i = x + y$ 计数太麻烦了导致没有场切）

设 $f(i)$ 表示满足 $0 \le x \le y \le c$，且 $x + y = i$ 的数对 $(x, y)$ 的个数，有

$$f(i) = \begin{cases}c - i + 1 & i \notin s\\0 & i \in s\end{cases}$$

设 $h(i)$ 表示 $s$ 中大于 $i$ 的与 $i$ 奇偶性相同的数的个数，处理方法后文会讲。

设 $g(i)$ 表示满足 $0 \le x \le y \le c$，且 $x + y \notin s$，$y - x = i$ 的数对 $(x, y)$ 的个数，有

$$g(i) = \begin{cases}f(i) - h(i) & i \notin s\\0 & i \in s\end{cases}$$

那么答案为

$$\sum\limits_{i = 0}^{c}g(i)$$

首先有一种很显然的暴力，枚举每个 $i \in [0, c]$，暴力计数，可以在枚举的过程中处理 $h(i)$。

```cpp
int odd = 0;
int even = 0;
int cnt = n;
int ans = 0;
for (int i = c; i >= 0; --i) {
    if (cnt && s[cnt] == i) {
        if (s[cnt] & 1) {
            ++odd;
        } else {
            ++even;
        }
        --cnt;
        continue;
    }
    ans += c - i + 1;
    if (i & 1) {
        ans -= odd;
    } else {
        ans -= even;
    }
}
```

这样无法通过此题，考虑优化。

$f(i)$ 是一个等差数列，$\sum f(i) = \dfrac{(c + 1) \cdot (c + 2)}{2}$。

对于 $i \in (s_{x-1}, s_x)$，$h(i)$ 的值是固定的。因此可以只枚举 $s_i$，分类讨论处理区间 $(s_{i-1}, s_i)$ 的 $h(i)$ 之和，详细见代码。

最终时间复杂度优化到 $O(n)$。

```cpp
#include <iostream>

#define int long long

using namespace std;

int T, n, c;
int s[3000050];

signed main() {
#ifndef ONLINE_JUDGE
    freopen("CF1935D.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> c;
        for (int i = 1; i <= n; ++i) {
            cin >> s[i];
        }
        s[0] = -1;
        int odd = 0;
        int even = 0;
        int ans = (c + 1) * (c + 2) / 2;
        for (int i = n; i; --i) {
            ans -= c - s[i] + 1;
            if (s[i] & 1) {
                ++odd;
            } else {
                ++even;
            }
            int len = s[i] - s[i - 1] - 1;
            int odd_num;
            int even_num;
            if (s[i] & 1) {
                if (s[i - 1] & 1) {
                    odd_num = len >> 1;
                    even_num = len - odd_num;
                } else {
                    odd_num = len >> 1;
                    even_num = len >> 1;
                }
            } else {
                if (s[i - 1] & 1) {
                    odd_num = len >> 1;
                    even_num = len >> 1;
                } else {
                    even_num = len >> 1;
                    odd_num = len - even_num;
                }
            }
            ans -= even_num * even;
            ans -= odd_num * odd;
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：wnsyou (赞：0)

# [Exam in MAC](https://www.luogu.com.cn/problem/CF1935D)

## 题意

$t$ 组数据。

给定一个大小为 $n$ 的集合 $s$ 和一个整数 $c$，保证 $0 \leqslant s_i \leqslant c(1 \leqslant i \leqslant n)$。

求有多少对整数数对 $(x,y)$，满足：

- $0\leqslant x \leqslant y \leqslant c$。
- $x + y \notin s$ 且 $y - x \notin s$。

### 数据范围

- $1 \leqslant n \leqslant 3 \times 10^5, 1 \leqslant c \leqslant 10^9$。
- $0 \leqslant s_i \leqslant c(1 \leqslant i \leqslant n)$​。
- $s_i < s_{i + 1}(1 \leqslant i < n)$。

## 思路

容斥题。

求不满足两个条件的数对个数，可以转化为总数对个数减满足其中任意一个条件(即 $x + y \in s$ 或 $y - x \in s$)的数对个数，再加满足两个条件的数对个数。

1. 总数对个数：对于 $x = 0$，$y$ 有 $c + 1$ 种取法；对于 $x = 1$，$y$ 有 $c$ 种取法……总个数为 $\frac{(c + 2) \times (c + 1)}{2}$。
2. 满足 $x + y \in s$ 的数对个数：由于 $s$ 中的元素**互不相同**，那么只要分别处理每个 $x + y = s_i$ 的数对个数即可。注意 $x \leqslant y$，总个数为 $\left\lfloor \frac{s_i}{2} \right\rfloor + 1$。
3. 满足 $y - x \in s$ 的数对个数：同理，也只需要分别处理每个 $y - x = s_i$ 的数对个数即可。转换式子，$y = x + s_i$，由于 $0 \leqslant y \leqslant c$，所以 $0 \leqslant x \leqslant c - s_i$，总个数为 $c - s_i + 1$。
4. 满足 $x + y \in s$ 且 $y - x \in s$ 的数对个数：假设 $x + y = s_i,y - x = s_j$，推一下式子，可得 $\begin{cases}2 \times x = s_i - s_j\\ 2 \times y = s_i + s_j\end{cases}$。由于 $x$ 和 $y$ 都是整数，则 $s_i - s_j$ 和 $s_i + s_j$ 都必须是偶数。易得当 $s_i$ 和 $s_j$ 奇偶性相同时存在数对 $(x,y)$。很明显，$y =\frac{s_i + s_j}{2} \leqslant c$。令 $a$ 为 $s$ 中元素的奇数个数，$b$ 为 $s$ 中元素的偶数个数，总个数为 $\frac{(a + 1) \times a}{2}+\frac{(b + 1) \times b}{2}$​。

**记得答案要开 `long long`。**

### 复杂度

- 时间：$O(n)$。
- 空间：$O(1)$。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int T, n, c, sum[2]; // sum[0] 记录偶数个数，sum[1] 记录奇数个数
long long ans; // 答案开 long long

void Solve () {
  cin >> n >> c;
  ans = 1ll * (c + 2) * (c + 1) / 2; // 初始数对个数
  for (int i = 1, x; i <= n; i++) {
    cin >> x, ans -= x / 2 + 1 + c - x + 1, sum[x % 2]++; // 减去满足任意一个条件的数对个数
  }
  cout << ans + 1ll * (sum[0] + 1) * sum[0] / 2 + 1ll * (sum[1] + 1) * sum[1] / 2; // 加上满足两个条件的数对个数
  sum[0] = sum[1] = 0;
}

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T--; Solve(), cout << '\n') {}
  return 0;
}
```

---

## 作者：xlpg0713 (赞：0)

C 大于 D。

## 题意
给定集合 $s$，求 $0\le x\le y\le c$ 的对数，使得 $x+y\notin s\land y-x\notin s$。

## 题解
直接算不好做，考虑正难则反，算和或差在 $s$ 中的数对数。

对于 $a\in s$，要求 $x+y=a$，因为有 $x\le y$，易于计算方案数为 $\lfloor\frac{a}{2}\rfloor+1$。

对于 $a\in s$，要求 $y-x=a$，显然答案是 $c-a+1$。

但是这样会算重，要减去和与差都在 $s$ 中的。若：

$$y+x=a$$
$$y-x=b$$

则 $y=\frac{a+b}{2},x=\frac{a-b}{2}$。

只要 $a+b$ 和 $a-b$ 组成的二元组不同，$x$ 和 $y$ 不相同。

$s$ 是升序给定的，考虑其中四个元素 $a<b<c<d$。若有和相同的一定是 $a+d=b+c$，显然差不同。差相同也可推得。

即对于一个数，随便选它后面（前面）的一个组成二元组一定不同。

但是注意到 $x,y\in\mathbf{Z}$，$s$ 中选出的数必须奇偶相同，扫一遍 $s$，统计奇数和偶数个数就可。

复杂度 $O(n)$。

```cpp
#include<iostream>
#define int long long
int T, n, c, a[300005];
signed main(){
    std::ios::sync_with_stdio(false);
    std::cin >> T; while(T--){
        std::cin >> n >> c;
        int A = 0, B = 0, C = 0;
        for(int i = 1; i <= n; i++){
            std::cin >> a[i];
            A += a[i] / 2 + 1;
            B += c - a[i] + 1;
        }
        int o = 0, e = 0;
        for(int i = 1; i <= n; i++)
            C += a[i] & 1 ? o : e,
            a[i] & 1 ? o++ : e++;
        std::cout << (c+1)*(c+2)/2-A-B+C+n << '\n';
    }
}
```

---

