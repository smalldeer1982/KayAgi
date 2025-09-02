# [ABC340C] Divide and Divide

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc340/tasks/abc340_c

黒板に整数 $ N $ が $ 1 $ 個書かれています。  
 高橋君は黒板に書かれている $ 2 $ 以上の整数が全て無くなるまで以下の一連の操作を繰り返します。

- 黒板に書かれている $ 2 $ 以上の整数を $ 1 $ つ選び $ x $ とする。
- 黒板から $ x $ を $ 1 $ 個消す。そして、$ 2 $ 個の整数 $ \left\ \lfloor\ \dfrac{x}{2}\ \right\rfloor,\ \left\lceil\ \dfrac{x}{2}\ \right\rceil $ を新たに黒板に書く。
- この一連の操作を行うために高橋君は $ x $ 円払う必要がある。
 
ここで $ \lfloor\ a\ \rfloor $ は $ a $ 以下の整数のうち最大のものを、$ \lceil\ a\ \rceil $ は $ a $ 以上の整数のうち最小のものを意味します。

操作を行えなくなった時点で高橋君が払った金額の総和は何円ですか？  
 なお、どのような順番で操作を行っても高橋君が払う金額の総和は一定であることが証明できます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^{17} $
 
### Sample Explanation 1

高橋君が行う操作の一例を挙げると次のようになります。 - はじめ、黒板には $ 3 $ が $ 1 $ 個書かれている。 - 高橋君は $ 3 $ を選ぶ。高橋君は $ 3 $ 円を払い、黒板から $ 3 $ を $ 1 $ 個消して $ \left\ \lfloor\ \dfrac{3}{2}\ \right\rfloor\ =\ 1,\ \left\lceil\ \dfrac{3}{2}\ \right\rceil\ =\ 2 $ を新たに黒板に書く。 - 黒板には $ 2 $ が $ 1 $ 個と $ 1 $ が $ 1 $ 個書かれている。 - 高橋君は $ 2 $ を選ぶ。高橋君は $ 2 $ 円を払い、黒板から $ 2 $ を $ 1 $ 個消して $ \left\ \lfloor\ \dfrac{2}{2}\ \right\rfloor\ =\ 1,\ \left\lceil\ \dfrac{2}{2}\ \right\rceil\ =\ 1 $ を新たに黒板に書く。 - 黒板には $ 1 $ が $ 3 $ 個書かれている。 - 黒板から $ 2 $ 以上の整数が全て無くなったので操作を終了する。 操作全体で高橋君は $ 3\ +\ 2\ =\ 5 $ 円払ったので、$ 5 $ を出力します。

## 样例 #1

### 输入

```
3```

### 输出

```
5```

## 样例 #2

### 输入

```
340```

### 输出

```
2888```

## 样例 #3

### 输入

```
100000000000000000```

### 输出

```
5655884811924144128```

# 题解

## 作者：Genius_Star (赞：3)

### 思路：

赛时做的快，懒得找规律，考虑动态规划算法。

定义 $dp_i$ 表示黑板上初始出现数字 $i$ 的代价，则状态转移方程为：

$$dp_i=dp_{\lfloor \frac{i}{2} \rfloor}+dp_{\lceil\frac{i}{2} \rceil}+i$$

但是因为 $N$ 最大为 $10^{17}$，不能朴素开数组转移，考虑记忆化搜索，有用的总状态数不会超过 $2 \log N$，开个 ``map`` 记录 $dp$ 数组即可。

时间复杂度为 $O(\log^2 N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n;
map<ll,ll> dp;
ll dfs(ll x){
	if(x<2)
	  return 0;
	if(dp[x])
	  return dp[x];
	ll t=dfs(x/2)+dfs((x+1)/2)+x;
	dp[x]=t;
	return t;
}
int main(){
	n=read();
	write(dfs(n));
	return 0;
}
```


---

## 作者：bigclever (赞：2)

贡献一个和目前所有题解都不一样的规律，而且代码实现非常简单。

以 $n=13$ 的情况为例：

![树](https://cdn.luogu.com.cn/upload/image_hosting/mki8disy.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

- 前 $\lceil \log_2 n \rceil$ 层的数的和均为 $n$。因为在 $x \gt 1$ 时，$\lfloor \frac{x}{2} \rfloor+\lceil \frac{x}{2} \rceil=x$。

- 可以发现前 $\lfloor \log_2 n \rfloor$ 层的数都大于 $1$，所以这些数都是我们需要支付的金额。等到第 $\lceil \log_2 n \rceil+1$ 层时所有数都已经小于等于 $1$ 了，便无需再计算了。

- 所以重点在于第 $\lceil \log_2 n \rceil$ 层。可以发现这一层里只有 $1$ 和 $2$，所以我们可以算出这一层一共有 $2^{\lfloor \log_2 n \rfloor}$ 个数，那么被计入答案的 $2$ 即有 $n-2^{\lfloor \log_2 n \rfloor} \times 1$ 个。

综上，答案即为 $n \times \lfloor \log_2 n \rfloor + 2 \times (n-2^{\lfloor \log_2 n \rfloor})$。

---

## 作者：lml0928 (赞：2)

### Part 0. 题目简述

刚开始黑板上只有一个整数 $n$。

如果当前黑板上有大于 $1$ 的数，那么进行操作，直到黑板上所有数都不大于 $1$。

操作：选择一个大于 $1$ 的数 $x$，然后擦掉它，写上 $\lfloor\dfrac{x}{2}\rfloor$ 和 $\lceil\dfrac{x}{2}\rceil$。

每次操作的花费为选择的数 $x$。

求当黑板上所有数都 $\le 1$ 的时候，一共花了多少钱。

### Part 1. 题目思路

首先看一眼数据范围：$2 \le n \le 10^{17}$。

这么大的数据范围，让我立刻想到这道题是道数学题。

我们可以假定一种操作顺序：先操作 $n$，然后操作除过 $1$ 次 $2$ 的数，操作除过 $2$ 次 $2$ 的数，以此类推。

容易发现，除了最后一次操作外，剩下的操作总花费都是 $n$。

而最后一次，黑板上还有 $1$ 和 $2$ 两种数。花费是 $2$ 乘上 $2$ 的个数。

$2$ 的个数，可以这样求：假设这一层数已经除过了 $cnt$ 次 $2$，那么，这一层就有 $2^{cnt}$ 个数。而这一行的总和一定是 $n$，所以 $2$ 就有 $n - 2^{cnt}$ 个。

时间复杂度 $O(\log n)$，顺利通过此题。

### Part 2. 题目代码

~~献上代码供众人批判~~

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int main()
{
	ull n;
	scanf("%llu", &n);
	ull now = 1;
	int cnt = 0;
	ull res = 0;
	while(true)
	{
		if(now * 2 > n)
		{
			res += 2 * (n - now);
			break;
		}
		now *= 2;
		cnt++;
		res += n;
	}
	printf("%llu", res);
	return 0;
}
```

---

## 作者：spire001 (赞：2)

## 思路
找规律，先写出暴力代码。
```cpp
unsigned long long ans(long long x)
{
	if(x < 2) return 0u;
	if(x & 1) return ans(x / 2) + ans(x / 2 + 1) + x;
	else return 2u * ans(x / 2) + x;
}
```
超时了，分析可知是当 $x$ 为奇数时递归过多导致的超时。  
所以考虑找出 `ans(x)` 与 `ans(x+1)` 的关系。
考虑如果 $x+1$ 与 $x$ 分解，一定会分解出一个相同的数与一个不同的数，不同的数一定相差一，继续递归计算答案也如此，所以 `ans(x)` 与 `ans(x+1)` 的差与 $\log_2x$ 有关。

暴力算出几对数的答案发现有如下规律:
$$
ans_x+\lfloor{\log_2x}\rfloor+2=ans_{x+1}
$$ 
于是可以写出正确代码。
## CODE
```cpp
# include <iostream>
# include <cstring>
# include <algorithm>
# include <cstdlib>
# include <stack>
# include <queue>
# include <vector>
# include <bitset>
# include <iomanip>
# include <cctype>
# define dbg(x) cerr << #x" = " << x << '\n'
using namespace std;

void rc(char &__c)
{
	while(!isalpha((__c = getchar())));
	return;
}
template <typename T>
void Read_base(T & num)
{
	char ch;int f = 1;num = 0;
	for(ch = getchar(); ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -f;
	for(;ch <= '9' && ch >= '0'; ch = getchar()) num = (num << 1) + (num << 3) + (ch ^ 48);
	num *= f; return;
}
void Read() {}
void Write() {}
template <typename T , typename ... args>
void Read(T & num , args &...  _num)
{
	Read_base(num);
	Read(_num...);
	return;
}
template <typename T>
void Write_base(const T num)
{
	if(num > 9) Write_base(num / 10);
	putchar(num % 10 ^ 48);
	return;
}
template <char __c = ' ' , typename T , typename ... args>
void Write(const T num , const args ...  _num)
{
	if(num < 0) {putchar('-');Write_base(-num);}
	else Write_base(num);
	putchar(__c);Write(_num...);
	return;
}

int a[102];
int cmd , T;
long long n , cnt = 0;
unsigned long long ans0 = 0;
int lg(long long x)
{
	int ans = 0;
	while(x)
	{
		ans++;
		x >>= 1;
	}
	return ans + 1;
}
unsigned long long ans(long long x)
{
	if(x < 2) return 0u;
	if(x & 1) return 2u * ans(x / 2) + lg(x / 2) + x;//不要忘了加上x
	else return 2u * ans(x / 2) + x;//懒得算答案大小，索性unsigned long long
}
int main()
{
	Read(n);
	Write(ans(n));
	//dbg(lg(64));
	return 0;
}

---

## 作者：xz001 (赞：2)

记忆化搜索，因为每次变成 $\left \lfloor \frac{n}{2} \right \rfloor $ 和 $\left \lceil \frac{n}{2} \right \rceil  $ 使得真正被遍历到的不同的点数是 $\log$ 级的，所以直接用 ```map``` 做记忆化即可。

代码如下：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

map <int, int> f;

int n;

int dfs (int x) {
	if (x < 2) return 0;
	if (f.count(x)) return f[x];
	return f[x] = dfs (x / 2) + dfs (x / 2 + bool(x % 2)) + x; 
}

signed main() {
	cin >> n;
	cout << dfs(n) << endl;
	return 0;
} 
```

---

## 作者：Otue (赞：1)

考虑每次都分成两半，最多 $\log n$ 层所有数就会变成 $1$ 。

那么直接记忆化搜索，搜过的数不搜第二次，复杂度可以保证 $O(\log n)$。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e5 + 5;

int n;
map<int, int> vis;

int dfs(int n) {
	if (vis[n]) return vis[n];
	if (n == 1) return vis[n] =  0;
	if (n == 2) return  vis[n] =  2;
	if (n == 3) return  vis[n] =  5; 
	// 分成两半，进行搜索
	if (n % 2 == 0) return vis[n] =   n + 2 * dfs(n / 2); 
	return  vis[n] =  n + dfs(n / 2) + dfs(n - n / 2);
}

signed main() {
	cin >> n;
	cout << dfs(n) << endl;
}
```

---

## 作者：SJZ2010 (赞：1)

我们按照题意递归模拟，这显然会 TLE。

于是我们就想到记忆化，我们开个 $10^8$ 大小的数组，每次递归到一个数，如果这个数 $\le 10^8$ 且其答案没被记录，那么我们就将递归出来的答案放入数组中，以后再递归到这个数时可以不用继续递归，直接返回之前存下的答案。效率大大提升。

代码：

```cpp
#include <bits/stdc++.h>

using ll = long long;
using qi = std::queue < int >;
using vi = std::vector < int >;
#define pq std::priority_queue
#define ve std::vector < edge >
#define VE std::vector < EDGE >
#define me(a, b) std::memset(a, b, sizeof(a))

const int N = 1e8 + 5; // This need you to adjust
const double TLS = 1;
const double eps = 1e-9;
const int inf = 0x3f3f3f3f;
const int CPS = CLOCKS_PER_SEC;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
const double TLC = TLS * 0.97 * CPS;

ll n;
__int128 pre[N]; // 记忆化数组

__int128 calc(ll x) // 递归模拟
{
	if (x < N && pre[x]) // 已经算过了，就直接返回
		return pre[x];
	if (x < 2)
		return 0;
	if (x < N)
		return pre[x] = ((x & 1) ? calc(x >> 1) + calc((x >> 1) + 1) + x : (calc(x >> 1) << 1) + x); // 记忆化
	if (x & 1)
		return calc(x >> 1) + calc((x >> 1) + 1) + x;
	return (calc(x >> 1) << 1) + x;
}

void write(__int128 x) // 保险一点用 __int128，要手写输出
{
	if (x / 10)
		write(x / 10);
	putchar(x % 10 + '0');
}

int main()
{
	scanf("%lld", &n);
	write(calc(n));
	return 0;
}

```

---

## 作者：Luxingguang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc340_c)

## 一、思路分析
------------
直接输出从 $1$ 开始，到 $100$ 结束的暴力。容易发现，每当是 $2$ 的次幂时，加数会多 $1$。因此直接 $O(\log(n))$ 切掉这题。

~~虽然可以记忆化搜索~~

## 二、构造代码
------------
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans,n,p=1,cnt=2;
signed main(){
	scanf("%lld",&n);
	if(n==1){
		puts("0");
		return 0;
	}while(p*2<n){
		ans+=p*cnt;
		p*=2;
		cnt++;
	}printf("%lld",ans+cnt*(n-p));
	return 0;
}

```

---

## 作者：Daniel_yao (赞：0)

## Problem
给定一个数 $n$，写在黑板上。每次选择黑板上一个不小于 $1$ 的数 $x$ 擦去，并写上 $\left\lfloor\frac{x}{2}\right\rfloor$ 与 $\left\lceil\frac{x}{2}\right\rceil$，并付出代价 $x$。问最后使黑板上的数全部小于 $1$ 的代价是多少。

## Solve
记 $f_i$ 表示给定的数为 $i$ 时的代价。

这样显然有（最优）子结构。可以 $dp$：

$$
f_i=
\begin{cases}
f_{\left\lfloor\frac{i}{2}\right\rfloor}+f_{\left\lceil\frac{i}{2}\right\rceil}+i & i>1\\
0 & otherwise
\end{cases}
$$


先暴搜，然后暴搜转记搜。

时间复杂度 $O(\log n)$。

## Code 

```cpp
#include <bits/stdc++.h>
#define int long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007

using namespace std;

namespace Read {
  template <typename T>
  inline void read(T &x) {
    x=0;T f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x*=f;
  }
  template <typename T, typename... Args>
  inline void read(T &t, Args&... args) {
    read(t), read(args...);
  }
}

using namespace Read;

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

const int N = 1e5 + 10;

int n, ans;

map<int, int> f;

int solve(int x) {
  if(x < 2) return 0;
  if(f[x]) return f[x];
  return f[x] = solve(x / 2) + solve(ceil(1.0 * x / 2)) + x;
}

signed main() {
  read(n);
  cout << solve(n) << '\n';
  return 0;
}
```

---

## 作者：Elysian_Realme (赞：0)

# AtCoder_abc340 C

## 题意简述

最开始黑板上有一个数 $N$，然后重复执行以下操作：

- 选择一个大于等于 $2$ 的数 $X$，花费 $X$ 的代价擦掉他然后写上 $\lceil \frac N 2\rceil$ 和 $\lfloor \frac N 2\rfloor$。 

## 解题思路

先考虑暴力，dfs 出 $2\sim 20$ 的答案，我们就得到了：

`2 5 8 12 16 20 24 29 34 39 44 49 54 59 64 70 76 82 88 `

到这里，原问题就已经转化成了求数列中第 $N-1$ 项的值（因为 $N\ne 1$）。

找到规律了吗？没有的话就给它差分一下。

`2 3 3 4 4 4 4 5 5 5 5 5 5 5 5 6 6 6 6 `

这样一来，就可以变成求这个差分序列的前缀和。

赛时写[代码](https://atcoder.jp/contests/abc340/submissions/50171160)的时候改了好久（我自己都不知道在写什么，这里加一那里减一的），有些细节可能和上面说的不太一样，很多代码都可以省略（~~总之就是别抄我的~~），时间复杂度 $O(\log N)$。

---

## 作者：Bpds1110 (赞：0)

赛时以为 $O(1)$，就写了记搜找规律，然后没找到。

我们先考虑如何用暴搜（递归）求解。设 $rec(n)$ 为整数 $n$ 要变化至满足条件的最少代价。得出 $rec(n) \gets n + rec(\left \lfloor \frac{n}{2}  \right \rfloor) + rec(\left \lceil \frac{n}{2}  \right \rceil)$。特别地，$rec(1) = 0$，表示 $1$ 已经满足条件，不需变化。画图可发现，改算法的时间复杂度约为 $O(n)$。而 $n \le 10^{17}$，会 TLE。

发现对于每个 $rec(n)$，答案固定不变，所以考虑用记忆化来优化。用 $map_n$ 记录 $rec(n)$ 的值。时间复杂度约为 $O(\log n)$。

```cpp
#include <bits/stdc++.h>
typedef long long ll;

std::map <ll, ll> map;

ll rec(ll n) {
	if (n == 1) return 0;
	if (map[n]) return map[n];
	ll res = n + rec(n / 2) + rec(n / 2 + (n & 1));
	return map[n] = res;
}

int main() {

//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);

	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	ll n; std::cin >> n;
	std::cout << rec(n) << "\n";	

	return 0;
}

```


---

## 作者：Cure_Wing (赞：0)

[AT_abc340_c [ABC340C] Divide and Divide](https://www.luogu.com.cn/problem/AT_abc340_c)

### 思路

定义 $f_i$ 表示把 $i$ 完全分解所需要的金钱。显然 $f_1=1,f_i=f_{\lfloor\frac{i}{2}\rfloor}+f_{\lceil\frac{i}{2}\rceil}+i(i>1)$，即分解 $i$ 的贡献等于分解 $\lfloor\frac{i}{2}\rfloor$ 的贡献加上 $\lceil\frac{i}{2}\rceil$ 的贡献加上 $i$。我们直接从 $n$ 开始进行记忆化搜索，时间复杂度就是 $O(\log n)$。因为不管去搜前一个还是后一个都会导致 $i$ 至少减去一半。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<map>
using std::cin;using std::cout;
long long n;
std::map<long long,long long >p;
inline long long dfs(long long x){
	if(x==1) return 0;
	if(p[x]) return p[x];
	return p[x]=dfs(x/2)+dfs(x-x/2)+x;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;
	cout<<dfs(n);
	return 0;
}
```

---

## 作者：Double_Light (赞：0)

记忆化搜索板子。

先考虑朴素的搜索：如果想要知道 $x$ 的花费（用 $f(x)$ 表示），那么显然有 $f(x)=x+f(\lceil\frac{x}{2}\rceil)+f(\lfloor\frac{x}{2}\rfloor)$ 表示，并且定义 $f(1)=0$。

这样有了递归式，同时有了结束条件，就可以写出如下的搜索：
```cpp
int check(int x){
	if(x==1)return 0;//递归结束条件
	int a,b;//a为上取整，b为下取整
	if(x%2==1)a=(x+1)/2;
	else a=x/2;
	b=x/2;
	return check(a)+check(b)+x;
}
```
但是显然这样的代码时间复杂度会突破天际。事实上，每一次函数 $f(x)$ 会分成 $f(\lceil\frac{x}{2}\rceil)$ 和 $f(\lfloor\frac{x}{2}\rfloor)$ 两个参数大小为原来一半的新函数，直到 $x$ 为 $1$ 停止。观察这个过程可以发现，每次调用就类似于线段树的节点分出两个大小为 $\frac{x}{2}$ 的子节点，故 `check(x)` 运行的次数与区间长度为 $x$ 的线段树的节点个数一样，于是时间复杂度可以达到 $4N$，即 $4\times 10^{17}$。

接下来考虑优化。不难发现 `check` 函数有可能调用许多次相同的参数，这时在每次调用之后，把 $f(x)$ 的值记录下来，如果下次遇到相同的 $x$，就直接取出已经记录过的 $f(x)$ 的值。这就是记忆化。可以考虑用 `map` 来存储。

这样，由于每次 $x$ 都会减少一半，所以时间复杂度就会变成 $O(\log N)$，足以通过本题。

代码：
```cpp
#include<iostream>
#include<map>
#define int long long//别忘开long long
using namespace std;
int n;
map<int,int>m;//m[x]表示check(x)的结果
int check(int x){
	if(x==1)return 0;
	int a,b,ans=0;
	if(x%2==1)a=(x+1)/2;
	else a=x/2;
	b=x/2;
	if(m[b])ans+=m[b];//如果记录过就不用重新算了
	else ans+=check(b);
	if(m[a])ans+=m[a];
	else ans+=check(a);
	return m[x]=ans+x;
}
signed main(){
	m[1]=0;
	cin>>n;
	cout<<check(n);
	return 0;
}
```

---

## 作者：2021zjhs005 (赞：0)

题目叫做“分而分之”，就是对一个数不停地分。

Despriction
------------
给定一个整数 $n$，每次做如下操作：

- 首先写上 $n$。

 - 然后写上 $\lfloor\frac{n}{2}\rfloor$ 和 $\lceil\frac{n}{2}\rceil$，并且擦除 $n$。这个操作的代价是 $n$。
 
 - 选择其中一个数进行第二步操作，如果这个数小于 $2$，则停止**这个数**的操作。否则重复执行操作 $2$（这里的 $n$ 可能会发生变化）。
 
求最少的花费代价。

可以证明，怎么样做，只要不违规，代价都一样。

Solution
------------
可以自己模拟一组：

- 写上 $5$。

- 写上 $2$，$3$，擦除 $5$，代价为 $5$。

- 写上 $1$，$1$，$1$，$2$，擦除 $2$，$3$，代价为 $2+3=5$。

- 写上 $1$，$1$，擦除 $2$，代价为 $2$。

总代价为 $5+5+2=12$。

于是，这个操作可以让我们想到——**记忆化搜索**。

记忆化搜索，就是将做过的一个数如同备忘录一样存下来，等下一做就不用重复地劳动。

如上的例子是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/fc23ni9b.png)

很明显，如果备忘录存下了左子树中 $2$ 的答案，那么右子树种 $2$ 就不用继续操作了。

对于**重复的操作**，解决时间复杂度为 $\Theta(1)$，否则大约是 $\Theta(\log n)$。因此这样的级别**大约**是 $\Theta(\log n)$，足以通过此题。

那么这么大的 $n$，怎么处理呢？

很简单，开个 `map` 即可。

在保证了这些以后，就可以用普通的递归了，注意**分类讨论** $n$ 的奇偶性。

Code
------------
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rrep(i,x,y) for(int i=x;i>=y;i--)
#define sc scanf
#define pr printf
inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

const int N=1e5+1;
int n;
map <int,int> a;

inline int dfs(int x){
    if(x==1) return 0;
    if(a[x]) return a[x];//如果有值，直接返回。
    /* 分类讨论。*/
    if(x&1) a[x]=x+dfs(x/2)+dfs((x-1)/2+1);
    else a[x]=dfs(x/2)*2+x;//套公式就行啦。
    return a[x];//返回。
//感谢 @cj180202 帮忙指出赛时 x pts 的代码的错误——分类讨论。
}
signed main(){
    n=read();
    pr("%lld\n",dfs(n));
    return 0;
}



---

## 作者：fls233666 (赞：0)

一上来一个简单粗暴的想法就是直接模拟整个计算过程。

然而直接模拟整个计算过程是必然会超时的，考虑剪枝。

我们模拟整个计算过程会发现，一些相同的数字在计算过程中被反复求解了多遍，得到的答案是一样的，但是造成了时间的浪费。

于是我们使用**记忆化**，记录求解过的答案，下次遇到时直接调用来减少时间消耗，就可以通过这题。

完整代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<map>
#include<cmath>
#define ll long long
using namespace std;

map <ll,ll> ans;   //记录已经求解过的答案，考虑到数字很大，一般的数组开不下，使用map

void work(ll num){
    ll n1,n2;
    if(num==1)  //如果是1，那么不需要再拆分，代价为0
        return;
    else{
        if(!ans[num]){  //如果这个答案没有求解过，则进行求解
            n1=num/2;  //下取整拆分
            n2=num/2;
            if(num%2)
                n2++;  //上取整拆分
            work(n1);
            work(n2);  //分别求解
            ans[num]=ans[n1]+ans[n2]+num;  //统计答案
        }
    }
} 

int main(){
    ll num;
    ans[1]=0;
    scanf("%lld",&num);
    work(num);
    printf("%lld",ans[num]);
    return 0;
}
```


---

## 作者：_colin1112_ (赞：0)

## 思路

容易得出 ${\lfloor\dfrac{n}{2}\rfloor}+{\lceil\dfrac{n}{2}\rceil}=n$，因此可以推出 ${\lfloor\dfrac{n}{2}\rfloor}+n-{\lfloor\dfrac{n}{2}\rfloor}=n$，然后按照公式进行递归，用 `map` 记忆化即可。

## Code

```c++
#include <bits/stdc++.h>
#define endl '\n'
#define ll long long

using namespace std;
const int E = 1e6 + 5;
ll n;
unordered_map<ll, ll> mp;
inline ll dfs(ll x)
{
    if (mp[x] != 0)
        return mp[x];
    if (x <= 1)
        return 0;
    ll ans = x;
    ans += dfs(x / 2) + dfs(x - x / 2);
    mp[x] = ans;
    return ans;
}
int main()
{
    // mp[2] = 2;
    cin >> n;
    cout << dfs(n);
    return 0;
}
```

---

## 作者：__Dist__ (赞：0)

### C

记搜。

用 `map` 记录答案，如果当前答案已经被搜过到了，那么直接返回答案，否则继续搜索并记录答案。

复杂度大约是 $\text{O}(\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 1e5 + 5;

long long n;
map<long long, long long> mp;

int dfs(int now) {
	if(now < 2) return 0;
	if(now == 2) return 2;
	if(mp[now]) return mp[now];
	int res = now + dfs(now / 2) + dfs((now + 1) / 2);
	mp[now] = res;
	return res;
}

signed main() {
	cin >> n;
	cout << dfs(n);
	return 0;
}
```

---

## 作者：apiad (赞：0)

这一题有两种做法：记忆化搜索，或者打表找规律。

首先，我们把暴力写出来，表格如下：

```
1 0
2 2
3 5
4 8
5 12
6 16
7 20
8 24
9 29
10 34
11 39
12 44
13 49
14 54
15 59
16 64
17 70
18 76
19 82
20 88
```

前面是 $n$，后面的是答案。

有没有发现什么，仔细看看，发现它们之间的差都是比较小的，我们再把差列举做出来。

```
2
3
3
4
4
4
4
5
5
5
5
5
5
5
5
```

其实差可以分为 $\log n$ 段，第 $i$ 段的长度为 $2^i$（$i$ 是从 $0$ 开始的）。然后第 $i$ 段的公差是 $i+2$，因此，我们可以直接 $O(\log n)$ 模拟即可。

对于这样做的证明，我还是不太会，但是在比赛的时候只要你 AC 了，那就行，如果有大佬可以讲讲如何证明，可以在评论区留言。谢谢！

[code](https://atcoder.jp/contests/abc340/submissions/50180182)。

---

## 作者：banned_gutongxing (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc340_c)

## 思路分析

这道题我们可以直接采用记忆化递归的方式，设 $f_i$ 表示当黑板上只有 $i$ 时的权值和，则：
$$
f_i=\begin{cases}
0&i<2\\
i+f_{\lfloor \frac{i}2\rfloor}+f_{\lceil \frac i2\rceil}&i\ge2
\end{cases}
$$

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<int,int> mp;
int Q(int x){
	if(x<2) return 0;
	if(mp.find(x)!=mp.end()) return mp[x];
	mp[x] = x+Q(x/2)+Q((x+1)/2);
	return mp[x];
}
signed main(){
	int n;
	cin >> n;
	cout << Q(n);
	return 0;
}
```



---

