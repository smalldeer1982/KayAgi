# [ABC362C] Sum = 0

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc362/tasks/abc362_c

$ N $ 個の整数の組 $ (L_1,R_1),(L_2,R_2),\ldots,(L_N,R_N) $ が与えられます。

以下の条件を満たす長さ $ N $ の整数列 $ X=(X_1,X_2,\ldots,X_N) $ が存在するか判定し、存在するならば一つ出力してください。

- 各 $ i=1,2,\ldots,N $ に対して $ L_i\leq\ X_i\leq\ R_i $
- $ \displaystyle\ \sum_{i=1}^N\ X_i=0 $

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ -10^9\leq\ L_i\leq\ R_i\leq\ 10^9 $
- 入力は全て整数
 
### Sample Explanation 1

数列 $ X=(4,-3,-1) $ は問題の条件をすべて満たします。ほかにも $ (3,-3,0) $ や $ (5,-4,-1) $ などが条件を満たします。

### Sample Explanation 2

条件を満たす整数列 $ X $ は存在しません。

## 样例 #1

### 输入

```
3
3 5
-4 1
-2 3```

### 输出

```
Yes
4 -3 -1```

## 样例 #2

### 输入

```
3
1 2
1 2
1 2```

### 输出

```
No```

## 样例 #3

### 输入

```
6
-87 12
-60 -54
2 38
-76 6
87 96
-17 38```

### 输出

```
Yes
-66 -57 31 -6 89 9```

# 题解

## 作者：_wsq_ (赞：8)

对于第一问，根据题目条件，可以得到如下不等式：
$$
\sum_{i=1}^N L_i\le\sum_{i=1}^N X_i\le\sum_{i=1}^N R_i
$$
直接计算，即可判断 $\sum_{i=1}^N X_i$ 是否可能等于 $0$。

对于第二问，考虑先假设 $X_i=R_i$，此时 $\sum_{i=1}^N X_i=\sum_{i=1}^N R_i$。然后，考虑贪心，给每个数依次减去其减去后使得 $\sum_{i=1}^N X_i\ge0$ 的能减去的最大值即可。

细节见代码。

```cpp
#include <iostream>
using namespace std;
#define maxn 200005
typedef long long ll;
int main(){
    ll n,l[maxn],r[maxn],suml=0,sumr=0;
    cin>>n;
    for(ll i=1;i<=n;i++){
        cin>>l[i]>>r[i];
        suml+=l[i];
        sumr+=r[i];
    }
    if(suml>0||sumr<0){
        cout<<"No";
        exit(0);
    }
    cout<<"Yes"<<endl;
    for(ll i=1;i<=n;i++){
        cout<<r[i]-min(r[i]-l[i],sumr)<<' ';
        sumr-=min(r[i]-l[i],sumr);
    }
    return 0;
}
```

---

## 作者：xuduang (赞：2)

### 题意

给出 $n$ 个区间，问你是否可以在每个区间中找到 $x_i$，使得 $\sum_{i=1}^{n} x_i=0$。

### 分析

贪心。

我们先将可以先得到一个最小值，即所有的左端点相加，记和为 $now$，则如果 $now>0$，则不可能构成 $0$，输出 `No`。

然后遍历每个区间，分两种情况讨论。我们尽可能的使 $now$ 更接近 $0$。

1. $now$ 变成 $0$ 的距离**小于**区间大小。这意味着只要加上这个区间的一部分就能使得 $now$ 变为 $0$。

1. $now$ 变成 $0$ 的距离**大于**区间大小。这意味着需要加上这个区间的全部。

### 代码

```cpp
#include <iostream>
#include <cmath>
#include <string.h>
#include <queue>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n;
int l[N], r[N];
int c[N];
void output()
{
	cout << "Yes\n";
	for(int i = 1; i <= n; i++) cout << c[i] << " ";
	cout << endl;
	exit(0);
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> l[i] >> r[i];
	int now = 0;
	for(int i = 1; i <= n; i++)
	{
		now += l[i];
		c[i] = l[i];
	}
	if(now > 0)//怎么样都不能完成 
	{
		cout << "No\n";
		exit(0);
	}
	for(int i = 1; i <= n; i++)
	{
		int ned = 0 - now;
		if(r[i] - l[i] >= ned)//情况1 
		{
			c[i] = l[i] + ned;
			output();
		}
		//情况2 
		c[i] = r[i];
		now += (r[i] - l[i]);
	}
	cout << "No\n";//还是不行 
	return 0;
}
```

---

## 作者：Lame_Joke (赞：2)

- ### 大体思路

  看到这种题，首先考虑的肯定是 DP，虽然但是，这道题不是 DP，是贪心……

  首先判断我们每个数的最大值（$R_{i}$）加起来能否大于 $0$，易证，如果小于的话，就说明这些数和不能为 $0$，输出 `No`。

  接着进入贪心部分，因为还需要构造出一个合法的数组。

  考虑将问题转化为：将最大值的和减成 $0$。

  初始时，我们的答案数组中都是每个数能取的最大值。

  当一个数能取的最小值比最大值小，我们就尽量将其减成最小值，直到和已经为 $0$ 即可。

  最后减完后判断和是否已被减成 $0$，若被减成 $0$，输出 `Yes` 及答案数组，否则输出 `No` 即可。

- ### 具体实现

  ```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  int a[200005],l[200005],r[200005],n;
  int sm=0,r1[200005];
  signed main()
  {
  	scanf("%lld",&n);
  	for(int i=1;i<=n;i++)
  	{
  		scanf("%lld%lld",&l[i],&r[i]);
  		sm+=r[i];
  		r1[i]=r[i];
  	}
  	if(sm<0)             			//最大值和小于0；         
  	{
  		printf("No");				//不可能完成；
  		return 0;
  	}
  	int x;
  	for(int i=1;i<=n;i++)
  	{
  		x=r[i]-l[i];				//x为能减的最大值；
  		if(sm==0) continue;
  		if(sm-x<0)					//无需减完就已经合法；
  		{
  			r1[i]-=sm;
  			sm=0;
  			break;
  		}
  		if(sm>=x)					//尽量减；
  		{
  			r1[i]=r[i]-x;
  			sm-=x;
  		}
  	}
  	if(sm) printf("No");			//如果和为0就可以输出答案了；
  	else
  	{
  		printf("Yes\n");
  		for(int i=1;i<=n;i++) printf("%lld ",r1[i]);
  	}
  }
  ```

---

## 作者：stripe_python (赞：0)

C 比较难的一集。

贪心地去想，计算出最小的和 $l'$ 和最大的和 $r'$。若 $0 \notin [l',r']$，则无法构造。

取一个初始构造 $t=r'$，遍历每对 $[l,r]$，若 $t-r+l > 0$，也就是删掉 $r$，加上 $l$ 还不满足要求，则更新构造。反之，找到 $x \in [l,r]$ 使 $t-x=0$，就输出构造。

复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 200005

int n, l[N], r[N], res[N];
long long ll, rr;

void _main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> l[i] >> r[i], ll += l[i], rr += r[i];
	if (rr < 0 || ll > 0) return cout << "No", void();
	for (int i = 1; i <= n; i++) res[i] = r[i];
	long long cur = rr;
	for (int i = 1; i <= n; i++) {
		if (cur - r[i] + l[i] > 0) res[i] = l[i], cur = cur - r[i] + l[i];
		else {res[i] = r[i] - cur; break;}
	}
	cout << "Yes\n";
	for (int i = 1; i <= n; i++) cout << res[i] << ' ';
} signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	_main();
	return 0;
}
```

---

## 作者：xixisuper (赞：0)

# AT_abc362_c [ABC362C] Sum = 0 题解

我还是太菜，像这种简单构造竟然没能一眼秒，该罚。

建议难度评级：黄。

## 思路

形式化题目：

- 给定 $N$ 对整数，第 $i$ 对整数为 $L_i$、$R_i$。
- 构造出一个长度为 $N$ 的数列 $X_N$，满足 $L_i\le X_i\le R_i$ 且 $\sum_{i=1}^NX_i=0$，如果无法给出构造，输出 `No`。

我们定义数列 $X_N$ 对应的前缀和数列为 $S_N$，根据不等式的性质，有：

$$\forall i\in[1,N],\sum_{k=1}^iL_k\le S_i\le \sum_{k=1}^iR_k$$

并且，我们能够保证对于所有 $S_N\in[\sum_{i=1}^NL_i,\sum_{i=1}^NR_i]$ 的情况，都能构造出对应的数列 $S_N$，也就能构造出对应的 $X_N$。所以，问题转变为在已知 $S_N=0$ 的情况下给出一组对应构造。

无解的情况很明显，就是 $0\notin[\sum_{i=1}^NL_i,\sum_{i=1}^NR_i]$ 的时候。

假设我们已经给出了 $X_{i+1}$ 到 $X_{N}$ 的合法构造，要求 $X_i$ 的合法情况，设 $T=\sum_{k=i+1}^NX_k$，有：

$$
\begin{cases}
X_i\in [L_i,R_i]\\
S_{i-1}+X_i+T=0
\end{cases}
\Longrightarrow
\begin{cases}
X_i\in [L_i,R_i]\\
X_i\in[-(\sum_{k=1}^{i-1}R_k+T),-(\sum_{k=1}^{i-1}L_k+T)]
\end{cases}
$$

不妨设 $l=-(\sum_{k=1}^{i-1}R_k+T)$，$r=-(\sum_{k=1}^{i-1}L_k+T)$，于是：

$$X_i\in[L_i,R_i]\cap [l,r]$$

所以说，$X_i$ 只需要在上述两个集合的交集中任取一个数即可，我采取的策略是当 $L_i\le l$ 时，取 $X_i=l$，否则取 $X_i=L_i$。

最后按顺序输出数列 $X_i$ 即可。

## 代码

代码中的变量名与题解中上述变量名基本一致，除部分变量大小写不同。

```cpp
#include <iostream>
#define ll long long
using namespace std;
const ll N=5e5+10;
ll L[N],R[N],n;
ll Lsum[N],Rsum[N],x[N]; 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;i++){
		cin>>L[i]>>R[i];
		Lsum[i]=Lsum[i-1]+L[i];
		Rsum[i]=Rsum[i-1]+R[i];
	}
	if(Rsum[n]<0||Lsum[n]>0){
		cout<<"No";
		return 0;
	}
	ll T=0;
	for(ll i=n;i>=1;i--){
		ll l=-Rsum[i-1]-T,r=-Lsum[i-1]-T;
		if(L[i]<=l) x[i]=l;
		else x[i]=L[i];
		T+=x[i];
	}
	cout<<"Yes\n";
	for(ll i=1;i<=n;i++) cout<<x[i]<<' ';
	return 0;
}
```

---

## 作者：qhr2023 (赞：0)

## solution

一种贪心加调整的策略。

我们先让所有的 $x$ 取最小值，如果此时的和等于 $0$，直接输出即可。

如果大于 $0$，一定找不到合法序列，无解。

如果小于 $0$，我们就遍历数组，如果当前 $x$ 在合法范围内能使 $sum$ 为 $0$，直接输出即可，否则，$x$ 取最大值，继续调整。我们能保证这个策略可以尽早的找到合法序列，若找不到，就无解。

## code

```cpp
#include <bits/stdc++.h>  
using namespace std; 
long long l[200005], r[200005], n, sum;
void out () {
	puts("Yes");
	for (int i=1; i<=n; i++)
		cout << l[i] << ' ';
	exit(0);
}
int main() {  
	cin >> n;
	for (int i=1; i<=n; i++) 
		cin >> l[i] >> r[i],
		sum+=l[i];
	if (!sum) 
		out();
	if (sum>0) {
		puts("No");
		return 0;
	}
	for (int i=1; i<=n; i++) 
		if (sum+r[i]-l[i]<0)
			sum+=r[i]-l[i],
			l[i]=r[i];
		else 
			l[i]-=sum,
			out();
	puts("No");
    return 0;  
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
先进行判断，如果 $\sum L > 0$ 或者 $\sum R < 0$，那么就不可能构造出 $X$，输出 `No`。

将 $L_i$ 赋值给 $X_i$。循环遍历 $1 \sim n$，如果此时 $\sum X \ge 0$，则结束循环，否则 $X_i$ 加上 $\min(R_i - L_i,- \sum X)$，然后 $\sum X$ 也要加上这个值。

循环结束，如果 $\sum X$ 等于 $0$，则输出 `Yes`，并且输出 $X$ 数组，如果 $\sum X$ 不等于 $0$，则输出 `No`。
### 代码
```cpp
#include<iostream>
#define int long long 
int read(){
 int x=0,t=1;char ch=getchar();
 while(ch<'0'||ch>'9'){if(ch=='-')t=-1;ch=getchar();}
 while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
 return x*t;
}
#define rd read() 
#define N 200005
int l[N],r[N],x[N];
int suml,sumr;
signed main(){
	int n=rd;
	for(int i=1;i<=n;i++){
		l[i]=rd,r[i]=rd,x[i]=l[i];
		suml+=l[i],sumr+=r[i];
	}
	if(suml>0||sumr<0)return puts("No"),0;
	int cur=suml;
	for(int i=1;i<=n&&cur<0;i++){
		x[i]+=std::min(r[i]-l[i],-cur);
		cur+=std::min(r[i]-l[i],-cur);
	}
	if(cur==0){
		puts("Yes");
		for(int i=1;i<=n;i++)std::cout<<x[i]<<" ";
	}else puts("No");
}
```

---

## 作者：Meickol (赞：0)

考虑构造一组特解，每次寻找偏移量，对于每个区间的答案即**区间左端点+偏移量**。

分析一下，前期每个区间的偏移量直接使用该区间最大偏移量 $R[i]-L[i]$ 即可，直至存在从某一刻开始偏移量都变为 $0$，即那一刻往后的位置直接使用 $L[i]$ 作为区间答案即可。

这么做是为了保证**偏移量总和**与**区间左端点位置总和**互为相反数。因为每个区间输出的答案即**区间左端点+偏移量**，这样能保证最终所有区间的答案总和为 $0$。



```c++
#include<bits/stdc++.h>
using namespace std;
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define IOS std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define endl '\n'
typedef long long LL;
const int N=2e5+5;
int n;
LL L[N],R[N],pl,pr;
void solve(){
	cin>>n;
	rep(i,1,n) cin>>L[i]>>R[i],pl+=L[i],pr+=R[i];
	if(pl<=0 && pr>=0){ //当区间[pl,pr]包含0时，才有解
		cout<<"Yes"<<endl;
		LL lsum=-pl; //因为pl必然小于等于0，lsum即取pl的大小
		rep(i,1,n){
			LL p=min(lsum,R[i]-L[i]);
			cout<<L[i]+p<<" ";
			lsum-=p; //当遍历完所有区间时，lsum最终必然变为0，即p的总和会等于lsum，而lsum=-pl，保证了l的总和与p的总和求和结果为0
		}
	}else cout<<"No";
}
int main(){
	IOS;
	int T;
	T=1;
	while(T--){
		solve();
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Defy_HeavenS (赞：0)

## 题意
给定 $N$ 个范围：$[L_1,R_1],[L_2,R_2],\dots ,[L_N,R_N]$。需要构造一个长度为 $N$ 的序列 $X$，满足：

1. $L_i\le X_i\le R_i \;(1\le i\le N)$ 即 $X_i\in [L_i,R_i]$。
2. $\sum_{i=1}^{N} X_i =0$。

## 思路
### 是否存在合法序列
记录两个数，可以取到最大和 $maxs$ 与可以取到最小和 $mins$，说起来比较抽象。看样例：

```
3
3 5
-4 1
-2 3
```

- 可以取到最大和 $maxs$：$5+1+3=9$。
- 可以取到最小和 $mins$：$3+(-4)+(-2)=-3$。

如果 $mins \le 0 \le maxs$ 也就是 $0 \in [mins,maxs]$，那么 $\sum_{i=1}^{N} X_i$ 就有机会等于 $0$，也就是输出`Yes`。

### 如何构造合法序列
两种方法：

1. 由最小和为基础，考虑向上加趋近为 $0$。
2. 同理，由最大和为基础，考虑向下减趋近为 $0$。

这里主要说明方案 $1$：

期望：$mi-\sum_{j=1}^{i} l_j+\sum_{j=1}^{i}r_j=0$（将最小值换成最大值），这样在 $i$ 以后就可以以最小和输出。

如果在一次调整中，$mi-l_i+r_i>0$ 则说明一下子加过了，那么调整一下即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double D;
const int N=2e5+5;
LL n,l[N],r[N],mi,ma;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>l[i]>>r[i];
		mi+=l[i];
		ma+=r[i];
	}
	if(mi>0||ma<0){
		cout<<"No";
	}else{
		cout<<"Yes\n";
		for(int i=1;i<=n;i++){
			if(mi<0){     //需要趋近为0 
				LL k=mi-l[i]+r[i],x=r[i];
				if(k>0){    //加过了，需要调整
					x-=k;
				}
				mi=mi-l[i]+x;
				cout<<x<<" ";
			}else{    //经过前面的调整，后面按最小和输出就可以 
				cout<<l[i]<<" ";
			}
		}
	}
	return 0;
}
/*

*/
```

更深的理解，可以照着代码代一遍样例。

---

## 作者：_zqh_ (赞：0)

> 涉及芝士点：构造

首先判断是否能够成 $0$；

把所有的下界加到一个值 $suml$ 里，上界加到一个值 $sumr$ 里。

则 $suml$ 是该数列的最小值，$sumr$ 是该数列的最大值。

则 $suml \le 0 \le sumr$ 就可以凑成 $0$；

那么考虑构造；

首先把所有数赋成上界，那么就与 $0$ 的距离是 $sumr$。

从 $1$ 开始，不断将上界调整成下界，使其与 $0$ 的距离更近，如果调整到下界会使其变成负数，那么就将其变为 $r - num$。

其中 $r$ 代表上界，$num$ 代表目前数列的和。

### Code

```cpp
#include <bits/stdc++.h>
// #pragma GCC optimize(2)
#define int long long
#define pii pair<int, int>
#define piiii pair<pii, pii>
#define il inline
#define p_q priority_queue
#define u_m unordered_map
#define bt bitset
#define rg register
#define rd Nothing::read
#define wt Nothing::write
#define endl '\n'

using namespace std;

namespace Nothing {
il int read() {
    int f = 1, t = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        t = t * 10 + ch - '0';
        ch = getchar();
    }
    return t * f;
}

il void write(int x, bool s) {
    if (x < 0) {
        putchar('-');
        write(-x, false);
        return;
    }
    if (!s && x == 0)
        return;
    if (s && x == 0) {
        putchar('0');
        return;
    }
    write(x / 10, false);
    putchar(x % 10 + '0');
}
}  // namespace Nothing

const int N1 = 300005;
const int N2 = 1000006;
const int Mod = 998244353;

namespace COMB {
int fac[N2] = {0};
il void Cinit(int p) {
    fac[0] = 1;
    for (int i = 1; i < N2; i++) {
        fac[i] = fac[i - 1] * i % p;
    }
}
il int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) {
            ans = ans * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}
il int C(int n, int m, int p) {
    if (m > n || m < 0) {
        return 0;
    }
    return fac[n] * qpow(fac[m], p - 2, p) % p * qpow(fac[n - m], p - 2, p) % p;
}
il int Lucas(int n, int m, int p) {
    if (!m)
        return 1;
    return (C(n % p, m % p, p) * Lucas(n / p, m / p, p)) % p;
}
il int GCD(int n, int m, int p) {
    return __gcd(n, m) % p;
}
il int LCM(int n, int m, int p) {
    return n * m % p * qpow(GCD(n, m, p), p - 2, p) % p;
}
}  // namespace COMB
using namespace COMB;
using namespace Nothing;

// #define debug 1
// #define multi_test 1
#define IOS 1

int T = 1;

int n;

pii a[200005];

void Init() {
    cin >> n;
    return;
}

void Solve() {
    int SumL, SumR = SumL = 0;
    for (int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        a[i] = {l, r};
        SumL += l;
        SumR += r;
    }
    if (SumL <= 0 && 0 <= SumR) {
        cout << "Yes\n";
        int num = SumR;
        for (int i = 1; i <= n; i++) {
            int nums = max(a[i].first, a[i].second - num);
            cout << nums << " ";
            num -= (a[i].second - nums);
        }
    } else {
        cout << "No";
    }
    return;
}

signed main() {
#ifdef IOS
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#endif
#ifdef debug
    freopen("zqh.in", "r", stdin);
    freopen("zqh.out", "w", stdout);
#endif
#ifdef multi_test
    cin >> T;
#endif
    while (T--) {
        Init();
        Solve();
    }
    return 0;
}
/*

*/
```

---

## 作者：__Floze3__ (赞：0)

## 思路简述

简单构造题。

我们可以不用管任何限制，先直接在每个区间取可选到的最小的数。倘若这样所选之和都大于 $0$，那么一定无解；否则，我们可以通过把每一位上的数字调大使得最终的和为 $0$，最后判断是否可以达到这种状态即可。

## 代码

[赛事提交链接](https://atcoder.jp/contests/abc362/submissions/55536233)

---

## 作者：Cosine_Func (赞：0)

题意很简洁，要求求出 $l_i \le x_i \le r_i$ 且 $\sum_{i=1}^{n}=0$ 的数列 $x$。

由于最终结果于具体数字无关，而只与其和相关，所以考虑贪心算法。先假设数列 $x$ 满足 $x_i=l_i$，如果和大于 $0$，直接输出无解。否则遍历 $1$ 至 $n$，判断 $x_i$ 加上最多可加的值，即 $r_i-x_i$，若大于等于零则直接令数列和为 $0$，$x_i$ 为可以使数列和为零的数，然后输出解；否则，就让 $x_i$ 等于 $r_i$。这样可以保证符合题意。最后，若操作结束之后的数列和不为零，输出无解。

这个过程中，我们需要维护数列的动态和，为了方便，使用树状数组维护。时间复杂度为 $O(n \log n)$，可以通过此题。

温馨提示：十年 OI 一场空，不开 `long long` 见祖宗！~~我因此吃了一发罚时~~。

[参考代码](https://atcoder.jp/contests/abc362/submissions/55564548)

---

## 作者：int_stl (赞：0)

我们不妨先令所有 $X_i = L_i$，接着求出 $S = \displaystyle \sum_{i = 1} ^ N X_i$，然后对 $S$ 进行分类讨论：

- 当 $S = 0$ 时，直接输出即可。

- 当 $S > 0$ 时，我们要将每个 $X_i$ 加上 $\max(-S, R_i - X_i)$，同时 $S$ 也加上相应的值。

- 否则，我们要加的值转换为 $\min(-S, R_i - X_i)$ 即可。

时间复杂度 $O(n)$。

[Submission Link.](https://atcoder.jp/contests/abc362/submissions/55530518)

---

## 作者：cheng2010 (赞：0)

# Sum = 0

## 思路

看起来挺唬人的，其实非常简单。

设输出的数组为 $ans$，初始是设为 $l$，如果总和 $>0$ 那么一定无解，否则把它变成 $r$ 并加上 $l \sim r$ 的贡献，$>0$ 了就把多的减掉即可。

记得开 `long long`！

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+7;
int n;
int l[N],r[N];
int a1,a2;
int ans[N];
int res=0;
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>l[i]>>r[i];
		a1+=l[i];
		a2+=r[i];
		ans[i]=l[i];
		res+=ans[i];
	}
	if(a1>0||a2<0)
	{
		puts("No");
		return 0;
	}
	if(res!=0)
	{
		for(int i=1;i<=n;i++)
		{
			ans[i]=r[i];
			res+=(r[i]-l[i]);
			if(res>=0)
			{
				ans[i]-=res;
				break;
			}
		}
	}
	puts("Yes");
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i]<<" ";
	}
}
```

---

## 作者：luobotianle (赞：0)

首先考虑无解的情况：如果 $\sum^n_{i=1}\limits l_i > 0$ 或 $\sum ^n_{i=1}\limits r_i< 0$，那么一定无解，否则一定有解。

接下来考虑如何构造。我们先取所有的 $l_i$，然后从头到尾扫一遍，如果当前的 $sum$ 还比 $0$ 小就尽可能地向 $0$ 去凑，否则就不动了。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
ll l[N],r[N],n,minn,maxn;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>l[i]>>r[i];
		minn+=l[i];
		maxn+=r[i];
	}
	if(minn<=0&&maxn>=0){
		puts("Yes");
		ll sum=minn;
		for(int i=1;i<=n;i++){
			ll d=min(-sum,r[i]-l[i]);
			sum+=d;
			cout<<l[i]+d<<" ";
		}
	}
	else puts("No");
	return 0;
}
```

---

