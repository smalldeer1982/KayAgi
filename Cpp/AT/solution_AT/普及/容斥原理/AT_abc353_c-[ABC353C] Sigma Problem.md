# [ABC353C] Sigma Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc353/tasks/abc353_c

正整数 $ x,y $ に対して $ f(x,y) $ を「$ (x+y) $ を $ 10^8 $ で割ったあまり」として定義します。

長さ $ N $ の正整数列 $ A=(A_1,\ldots,A_N) $ が与えられます。次の式の値を求めてください。

$ \displaystyle\ \sum_{i=1}^{N-1}\sum_{j=i+1}^N\ f(A_i,A_j) $

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 3\times\ 10^5 $
- $ 1\leq\ A_i\ <\ 10^8 $
- 入力される数値は全て整数
 
### Sample Explanation 1

\- $ f(A_1,A_2)=50000004 $ - $ f(A_1,A_3)=50000005 $ - $ f(A_2,A_3)=3 $ なので、答えは $ f(A_1,A_2)+f(A_1,A_3)+f(A_2,A_3)\ =\ 100000012 $ です。 総和を $ 10^8 $ で割ったあまりを求めるわけではないことに注意してください。

## 样例 #1

### 输入

```
3
3 50000001 50000002```

### 输出

```
100000012```

## 样例 #2

### 输入

```
5
1 3 99999999 99999994 1000000```

### 输出

```
303999988```

# 题解

## 作者：Guoguo2013 (赞：10)

这次 Atcoder 显然跟求和是过不去了，但这三道题没有一道是正经的求和。

### 思路：

由于题意是每两个数都要加一遍，那他要加就全加上呗，反正也不超 `long long` 的数据范围，全加一遍之后，每个数是重复加了 $N-1$ 遍，这样就可以用 $O(n)$ 的时间复杂度来把每个数加起来。

但我们发现，如果两个数加起来超过 $10^8$ 是要取模的，但所有的 $f(A_i, A_j)$ 加起来后还是有可能超过 $10^8$ 的，那怎么办呢？  
**可以用二分。**  
既然每两个数都要加，那么排个序也就不是问题了。

排完序后，统计一下有多少组数加起来超过 $10^8$，那就把一开始的结果减掉这么多个 $10^8$ 就行了。

对于一个数 $i(1 \le i \le N)$ 找到一个数 $j$，使得：

1. $j>i$
2. $A_j+A_i \ge 10^8$ 且 $A_{j-1}+A_i < 10^8$（如果 $j = i+1$ 第二个条件就可以不用）

这样就能找到整数 $A_i$ 能跟多少个数加起来超过 $10^8$ 了，很显然排完序后，当 $A_j+A_i \ge 10^8$ 那么 $A_j$ 后面的数肯定也成立，而两个小于 $10^8$ 的数加起来也无论如何超不过 $2 \times 10^8$ 的，所以对于整数 $A_i$，有$N-j+1$ 个整数可以跟他加起来超过 $10^8$。  
$j$ 可以用**二分**找出来，当然如果没有 $j$ 满足上面那两个条件，那就没有整数和他加起来超过 $10^8$。

最后再用最初的答案减掉那么多个 $10^8$ 就行了。

二分是 $\log n$ 的时间复杂度，再乘上遍历一遍整个数组 $n$，时间复杂度为 $O(n \log n)$，排序也是 $O(n \log n)$，合起来就是 $O(n \log n)$。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 3e5 + 5;
int n, a[N], daan, gj; // gj表示该减多少个10^8

int merge(int l, int r, int cnt){
  if (cnt > a[r]) return r + 1;
  while (l < r){
    int mid = l + r >> 1;
    if (a[mid] >= cnt) r = mid;
    else l = mid + 1;
  }
  return l;
}
// 手写的二分函数
signed main(){
  scanf("%lld", &n);
  for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++){
    daan += a[i];
    int now = n - merge(i + 1, n, 100000000 - a[i]) + 1; // now表示当前这个数有多少个跟他加起来超过10^8，如果不想手写二分函数也可以用lower_bound。
    gj += now;
  }
  daan = daan * (n-1) - gj * 100000000;
  printf("%lld\n", daan);
  return 0;
}
```

最后提醒大家一句，$10^8$ 一定要写成 $100000000$，不要写成 $1e8$，要不然会挂的，我就因为这个原因赛时没做出来这道题。

#### 管理大大求过

---

## 作者：Elairin176 (赞：3)

[传送门](https://www.luogu.com.cn/problem/AT_abc353_c)  
来个劣解。
## 题意
设 $\operatorname{f}(a,b)=(a+b)\bmod10^8$，给出长度为 $n$ 的数列 $a$，求 $\sum\limits^{n-1}_{i=1}\sum\limits^n_{j=i+1}\operatorname{f}(a_i,a_j)$.    
## 解法
我们考虑对每个 $i$ 进行考虑。注意到 $\forall i\in[1,n],a_i<10^8$，所以 $\operatorname{f}$ 函数可以表示为：   
$\operatorname{f}(a,b)=\begin{cases}a+b&a+b<10^8\\a+b-10^8&a+b\ge10^8\end{cases}$      
那么我们只需要对于每个 $i$ 把 $a_{i+1}$ 到 $a_n$ 作一次求和，并处理出所有相加大于 $10^8$ 的数字个数即可。    
求和部分很好处理，只需要一个后缀和即可；但是如何统计数字个数呢？     
我们不难发现，$a_i+a_j\ge10^8$ 相当于 $a_j\ge10^8-a_i$.   
那么，我们实际上只需要求出 $a_{i+1}$ 到 $a_n$ 中小于 $10^8-a_i$ 的数字个数即可，也就是 $10^8-a_i$ 在区间内的排名减 $1$。这里用平衡树维护即可。我选择使用常数较小的 01-trie。     
CODE：     
```cpp
//完整缺省源请见洛谷云剪贴板 jo5j6ogx
#define int ll
const int N=3e5,base=32;
int trie[N*2*base+10][2],ans,siz[N*2*base+10],tot=1,n,a[N+10];
ll q[N+10];
il void insert(ll x,int y){
	int u=1,c;
	for(int i=31;i>=0;i--){
		c=(x>>i)&1;
		if(!trie[u][c]){
			trie[u][c]=++tot;
		}
		u=trie[u][c];
		siz[u]+=y;
	}
}
il int rk(ll x){
	int u=1,c,ans=0;
	for(int i=31;i>=0;i--){
		c=(x>>i)&1;
		if(c){
			ans+=siz[trie[u][0]];
		}
		u=trie[u][c];
	}
	ret ans;
}
signed main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	n=read<int>();
	for(int i=1;i<=n;i++){
		a[i]=read<ll>();
		q[i]=q[i-1]+a[i];
		insert(a[i],1);
	}
	for(int i=1;i<n;i++){
		insert(a[i],-1);
		//n-(i+1)+1=n-i
		ll t=n-i-rk((ll)1e8-a[i]);
		ans+=(q[n]-q[i])-t*(ll)1e8+1ll*a[i]*(n-i);
	}
	write(ans);
	ret 0;
}
```

---

## 作者：liaoxingrui (赞：3)

## Content

定义 $f(x,y)$ 为 $(x + y) \operatorname{mod} 10^8$。

求:

$$\sum_{i = 1}^{N - 1} \sum_{j = i + 1}^N f(A_i,A_j)$$

## Solution

我们可以先看一下数据范围：

$$2 \le N \le 3 \times 10^5$$

$$1 \le A_i < 10^8$$

两个数相加，且这两个数都为正整数，都小于 $10^8$，就会轻易发现 $(A_i + A_j) < 2 \times 10^8$，所以 $\operatorname{mod} 10^8$ 后就相当于被减一个 $10^8$ 或没有发生变化。

根据刚刚所推得的，我们就可以知道答案（设有 $x$ 个需要减去 $10^8$ 的函数）:

$$(\sum_{i = 1}^{N - 1} \sum_{j = i + 1}^N A_i + A_j) - x \times 10^8$$

第一个，$\sum_{i = 1}^{N - 1} \sum_{j = i + 1}^N A_i + A_j$，因为每个数都会于其它数字加 $n - 1$ 次，可以得到:

$$\sum_{i = 1}^N A_i \times (n - 1)$$

第二个，$x$，我们可以将数组从小到大排序，然后二分查找 $\sum_{i = 1}^N 10^8 - A_i$（设二分查找答案为 $y$），可以直接得到 $x = n + 1 - y$，因为排序后后面的数一定大于这个数 $A_y$，$A_y + A_i$ 已经大于或等于 $10^8$，则后面的数也会这样。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
long long n,sum;
long long a[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	sum*=(n-1);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		int x=lower_bound(a+i+1,a+n+1,1e8-a[i])-a;
		sum-=(n+1-x)*100000000;
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：CheZiHe929 (赞：2)

### 简要题意

给定一个长度为 $n$ 的序列 $a$，求 $\sum\limits_{i=1}^{n-1} \sum\limits_{j=i+1}^{n} ((a_i+a_j) \mod 10^8)$ 的值。

### 简要思路

可以将本题转化为先计算不取模时的答案，记和 $\ge 10^8$ 的二元组的数量为 $x$，则最后再减去 $x \times 10^8$ 即可。

对于计算满足条件的二元组的数量，可以对于每一个数 $a_i$ 用二分来寻找满足 $a_i + a_j \ge 10^8$ 的 $j$ 的数量（当然要先排序保证单调）。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug puts("#CheZiHe929")
#define Yes puts("Yes")
#define No puts("No")
const int MAXN=3e5+5;
const int p=1e8; 

inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
inline void print(int x){char st[105];int top=0;if(x==0)putchar('0');if(x<0)putchar('-');while(x){if(x>0)st[++top]=x%10+48;else st[++top]=-(x%10)+48;x/=10;}while(top)putchar(st[top--]);}
inline void println(int x){print(x);putchar('\n');}
inline void printsp(int x){print(x);putchar(' ');}
inline void put(int x,int i,int n){i==n?println(x):printsp(x);}

int a[MAXN],ans,x;

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	int n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		ans+=a[i]*(n-1);//不取模时，每个数都在序列里出现了 n-1 次 
	}
	
	std::sort(a+1,a+n+1);//排序保证单调性 
	for(int i=1;i<=n;i++){
		int now=std::lower_bound(a+i+1,a+n+1,p-a[i])-a-1;//最后一个满足 a[i]+a[j]<p 的 j 的位置 
		x+=n-now;
	}
	println(ans-x*p);
	return 0;
}

```

---

## 作者：过氧化氢_syq0057 (赞：2)

### Description

题意：给你一个序列 $A_1...A_n$，求 $\displaystyle\sum_{i=1}^{N-1} \displaystyle\sum_{j=i+1}^N f(A_i,A_j)$。

其中 $f(A_i,A_j)=(x+y) \bmod 10^8$。

### Solution

好像数学题被我硬做了。。。

注意拆分是错的，式子只是对于每个 $A_i,A_j$ 单独加和再取模最后相加。

注意到 $A_i<10^8$，我们可以考虑把取模变成相减。

每个 $A_i$ 都会和它后面的 $A_j$ 会被选入 $f(A_i,A_j)$ 仅一次，当且仅当 $A_i+A_j \ge 10^8$ 时取模是必要的，于是我们统计对于每个 $A_i$ 在 $A_{i+1}...A_n$ 中有多少个相加不小于 $10^8$ 的 $A_j$ ，最后减去对应个数的 $10^8$ 即可。

考虑用分块和二分查询区间不小于一个数的数。

时间复杂度 $O(n \sqrt n \log{\sqrt n})$。

其实两秒的时限应该能想到点什么了。

这里 $n$ 固定了查询次数和区间长度都是固定的，可以把块长开大一点，朴素的 $\sqrt n$ 可能过不了。

### Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;
const int N = 1000005;
const int M = 200005;
#define ll long long
const int INF = 0x3f3f3f3f;
const ll mod = 100000000;
int n;
int sn;
int blk[N];
ll a[N], d[N];
ll ans, cnt;
inline int Min(int x, int y) {
	if (x < y) return x;
	return y;
}
int query(int l, int r, ll k) {
	int res = 0;
	for (int i=l; i<=Min(blk[l]*sn,r); i++)
		if (a[i] >= k)
			res++;
	if (blk[l] != blk[r])
		for (int i=(blk[r]-1)*sn+1; i<=r; i++)
			if (a[i] >= k)
				res++;
	int L, R, mid, s;
	for (int i=blk[l]+1; i<blk[r]; i++) {
		L = (i - 1) * sn + 1, R = i * sn, s = 0;
		while (L <= R) {
			mid = (L + R) >> 1;
			if (d[mid] >= k) R = mid - 1, s = i * sn - mid + 1;
			else L = mid + 1;
		}
		res += s;
	}
	return res;
}
int main() {
	scanf("%d", &n);
	sn = pow(n, 0.6);//块长开大一点
	for (int i=1; i<=n; ++i) {
		blk[i] = (i - 1) / sn + 1;
		scanf("%lld", &a[i]), d[i] = a[i];
	}
	for (int i=1; i<=n/sn+1; ++i)
		sort(d + 1 + (i - 1) * sn, d + 1 + i * sn);//每个块单独排序
	for (int i=1; i<n; ++i) {
		cnt += (ll)query(i + 1, n, mod - a[i]);
	}
	ans = -cnt * mod;
	for (int i=1; i<=n; ++i)
		ans += a[i] * (n - 1);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：OIer_Tan (赞：2)

赛时切 D 然后做不了 C，难绷。

[题目传送门](https://www.luogu.com.cn/problem/AT_abc353_c)

## 题意

对于正整数 $x$ 和 $y$，定义 $f(x, y)$ 为 $(x + y)$ 除以 $10^8$ 的余数。

给你一个长度为 $N$ 的正整数序列 $A = (A_1, \ldots, A_N)$。求下面表达式的值：

$\displaystyle \sum_{i=1}^{N-1}\sum_{j=i+1}^N f(A_i,A_j)$ .

## 思路

显然直接算是不好算的，所以可以考虑先将 $\sum^{N-1}_{i=1}\sum^{N}_{j=i+1}(A_i+A_j)$ 算出来，即 $(N-1)\sum^{N}_{i=1}A_i$，再考虑取模的问题。

接下来的问题就是考虑如何计算有多少对 $A_i+A_j\ge10^8$ 的问题。

我们发现，在这里排序之后并不会影响答案，可以按升序排序后用双指针往中间缩，因为在 $A_i+A_j\ge10^8$ 的情况下，$A_{i+1}+A_j\ge10^8$ 是显然正确的。

总复杂度为 $O(N\log N)$。

## 代码

```cpp
#include <bits/stdc++.h>

#ifndef CRT
#define endl '\n'
#endif

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 3e5 + 5 ;

ll n , a [N] , ans = 0 , cnt = 0 ;

int main ()
{
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		cin >> a [i] ;
	}
	sort ( a + 1 , a + 1 + n ) ;
	ll r = n ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		r = max ( r , i ) ;
		while ( r > i && a [r] + a [i] >= ll ( 1e8 ) )
		{
			r -- ;
		}
		cnt += n - r ;
	}
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		ans += a [i] * ( n - 1 ) ;
	}
	ans -= cnt * ll ( 1e8 ) ;
	cout << ans << endl ;
	return 0 ;
} 
```

---

## 作者：Dtw_ (赞：1)

[at](https://atcoder.jp/contests/abc353/tasks/abc353_c)
# 题目大意

对于 $x$ 和 $y$, 定义 $f(x,y)$ 为 $(x + y) \bmod 10^8$ 。

给你一个长为 $N$ 的正整数序列 $A = (A_1, \ldots, A_N)$ 求这个式子的值。

$\displaystyle \sum_{i=1}^{N-1}\sum_{j=i+1}^N f(A_i,A_j)$.

# 思路
首先我们可以知道，如果不取模那么每个数都会被加 $(N-1)$ 次（打个表就可以知道）。

并且我们看到 $A_i < 10^8$ 所以有任意的 

当 $A_i + A_j < 10^8$ 时：

$f(A_i, A_j) = A_i + A_j$

否则

$f(A_i, A_j) = A_i + A_j - 10^8 $

所以我们可以把所有的数都先加上 $(N-1)$ 遍，最后在统计出来有几对是大于 $10^8$ 的，在统一减掉。

至于如何快速统计，我们可以把 $A$ 排序，这不会对答案造成影响（手动模拟就可以知道）。

然后对于每一个 $A_i$ 去二分最大的 $A_j$ 使得 $A_i + A_j < 10^8$ 然后就可以得出剩下的 $(N-j)$ 个都是需要减掉的，统计出来就可以了。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define fi first
#define se second

#define IN(o) insert(o)

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 1e8;

const int N = 1e6 + 10;

int n;

int a[N]; 

signed main()
{
	cin >> n;
	int res = 0;
	for(int i=1; i<=n; i++)
	{
		cin >> a[i];
		res += (n - 1) * a[i];
	}
	sort(a+1, a+n+1);
	for(int i=1; i<=n; i++)
	{
		int l = i+1;
		int r = n;
		int p = i;
		while(l <= r)
		{
			int mid = (l + r) / 2;
			if(a[mid] + a[i] < P)
			{
				l = mid + 1;
				p = mid;
			}
			else
			{
				r = mid - 1;
			}
		}
		res -= (n - p) * P;
	}
	cout << res;
	return 0;
}




```

---

## 作者：WorldMachine (赞：1)

## ABC353C 题解

~~偷懒小寄巧~~

**比赛时** 如果发现时间复杂度较大的算法能过就不要花太多时间去优化（前提是排行榜不按照运行时间排序）。

### 题目大意

给你一个长度为 $n$ 的序列 $a_i$，求：
$$
\sum_{i=1}^{n-1}\sum_{j=i+1}^n((a_i+a_j)\bmod10^8)
$$
$2\leq n\leq 3\times 10^5,1\leq a_i<10^8.$

### Solution

由于 $a_i+a_j<2\times 10^8$，因此取模最多只会减去 $10^8$。

原式化为：（$[P]$ 的值当 $P$ 成立时为 $1$，不成立为 $0$）
$$
\sum_{i=1}^{n-1}\sum_{j=i+1}^n(a_i+a_j-[a_i+a_j\geq 10^8]\cdot10^8)
$$
即：
$$
\sum_{i=1}^{n-1}(n-i)a_i+\sum_{i=1}^{n-1}\sum_{j=i+1}^na_j-10^8\cdot\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}[a_j\geq10^8-a_i]
$$
第一部分可以直接求，第二部分可以后缀和，重点是第三部分。

正解复杂度为 $\mathcal O(n\log n)$，需要离散化，但是可以发现 $2$ 秒钟的时间限制跑 $10^8$ 绰绰有余，于是直接记录后缀和，$\text{sum}_i$ 表示大于等于 $i$ 的数有多少个，第三部分就可以直接做了。

时间复杂度为 $\mathcal O(n+V)$，其中 $V$ 为值域，即 $10^8$。

注意要特判 $a_i\geq 5\times10^7$ 的情况，这时 $a_i\geq 10^8-a_i$，第三部分会多算一个。

```cpp
#include <bits/stdc++.h>
using namespace std;
void read(int &a) { a = 0; char c = getchar(); while (c < '0' || c > '9') c = getchar(); while (c >= '0' && c <= '9') a = a * 10 - '0' + c, c = getchar(); }
typedef long long ll;
const int N = 300005, p = 100000000;
int n, a[N], s[p + 5];
ll cnt, sum[N], ans;
int main() {
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]), s[a[i]]++;
	for (int i = p; i >= 1; i--) s[i] += s[i + 1];
	for (int i = n; i >= 1; i--) sum[i] = sum[i + 1] + a[i];
	for (int i = 1; i < n; i++) ans += (ll)a[i] * (n - i);
	for (int i = 1; i < n; i++) ans += sum[i + 1];
	for (int i = 1; i <= n; i++) cnt += s[p - a[i]] - (a[i] >= p / 2);
	ans -= cnt / 2 * p;
	printf("%lld", ans);
}
```

---

## 作者：_Weslie_ (赞：0)

### Idea

因为 $a_i<10^8$，所以 $0<a_i+a_j<2\times 10^8$。

考虑对于 $a_i+a_j<10^8$ 和 $a_i+a_j\ge 10^8$ 的情况分开讨论。

在 $a_i+a_j<10^8$ 时，这一组数对答案的贡献即为 $a_i+a_j$。

反之，则贡献为 $a_i+a_j-10^8$。

所以我们可以对 $a$ 序列从小到大排序，排序之后序列满足单调性。

可以对于每一个 $i$，二分出一个 $j$ 使 $a_i+a_j\ge10^8$ 且 $a_i+a_{j-1}<10^8$。这一部分是 $\operatorname{O}(n\log n)$ 的。

因为有单调性，所以对于任意的 $k$ 使 $k\ge j$，$a_i+a_k\ge 10^8$。

我们可以发现，最后对于每一个 $i$，会减掉 $n-j+1$ 个 $10^8$。

而设要减 $cnt$ 个 $10^8$，则答案为：

$$\sum_{i=1}^{n}\sum_{j=1}^{n}(a_i+a_j)-cnt\times 10^8$$

如何求每一对 $a_i+a_j$ 呢？考虑拆开：每一个 $a_i$ 会被加 $n-1$ 次（与 $n-1$ 个 $a_j$ 相加） ，所以设 $a$ 数组总和为 $sum$，则每一对 $a_i+a_j$ 的总和为 $sum\times(n-1)$。这里是 $\operatorname{O}(n)$ 的。

所以我们就能在 $\operatorname{O}(n\log n)$ 的时间复杂度内解决了。

### Tip

- 本题可能会爆 ```int```。

### Code
```
#include<bits/stdc++.h>
using namespace std;
long long sum;
long long cnt=0;
int n,a[300005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	a[n+1]=100000000; 
	for(int i=1;i<=n;i++){
		int x=100000000-a[i];
		int _=lower_bound(a+i+1,a+n+2,x)-a;
	//	cout<<_<<' ';
		cnt+=(n-_+1);
		sum+=a[i];
	}
	sum=1ll*sum*(n-1);
	sum-=cnt*100000000;
	cout<<sum;
	return 0;
}
```

---

## 作者：zhangyuhaoaa (赞：0)

## 题意

设 $f(x, y)$ 为 $(x+y) \bmod 10^8$。给出正整数序列 $A=(A_1,\dots,A_N)$。求出 $\sum_{i=1}^{N-1} \sum_{j=i+1}^{N}f(A_i,A_j)$。

## 思路

这道题其他的都非常的简单，但是这个取余却有一些难度，我们可以追寻取余的本质，那就是把大于这个数的部分删掉，然后我们就可以找到有几组两个数加起来比模数要大，然后统计下来，最后把这些数减掉即可。

## code

```cpp
#include <bits/stdc++.h>
#define re register
#define il inline
#define int long long
#define endl '\n'
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int P = 100000000;
const int INF = 0x3f3f3f3f3f3f3f3f;

const int maxn = 1e6 + 5;

int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return x * f;
}

int n, x;
int ans = 0;
int a[maxn];
int b[maxn]; 

signed main() {
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    fst;
    
    cin >> n;
    x = n + 1;
    for (int i = 1; i <= n; ++ i ) {
    	cin >> a[i];
    	b[i] = b[i - 1] + a[i];
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++ i ) {
		x = max(x, i + 1);
		while (x > i + 1 && a[i] + a[x - 1] >= P) {
			x --;
		}
		ans += n - x + 1;
	}
	ans = -ans * P;
	for (int i = 1; i < n; ++ i ) {
		ans += b[n];
	}
	cout << ans;

    return 0;
}
```

---

## 作者：huangzhixia (赞：0)

这 AT abc 在 CDE 题都出这求和题挺少见的。

不难想到，对于每个 $(i,j)$，如果 $a_i + a_j$ 是小于 $10^8$ 的，贡献就为 $a_i + a_j$。考虑 $(i,j)$，并且 $a_i + a_j > 10^8$，答案的贡献为 $10^8 - 1$。设 $sum$ 为所有 $a_i + a_j$，$cnt$ 为 $a_i + a_j > 10^8$ 的个数，则答案为 $sum - cnt \times 10^8$。

计算 $sum$ 难度不大，$sum = \sum _ {i = 1} ^ n a_i \times (n - 1)$。

考虑计算 $cnt$，首先 sort 一遍，然后缩放计算 $cnt$，详细见官解。

代码略。

---

## 作者：HasNoName (赞：0)

### 思路

题目可以转化为 $\displaystyle \sum_{i=1}^{N-1}\sum_{j=i+1}^N A_i+A_j$ 减去 $A_i+A_j$ 大于等于 $10^8$ 的个数乘 $10^8$。

考虑如何计算 $A_i+A_j\ge10^8$ 的个数。

可以使用树状数组。

每次只需要减去所有数中比 $10^8-A_i$ 小的数的个数乘 $10^8$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=600005,MOD=1e8;
unordered_map<int,int>d;
typedef long long ll;
ll a[N],f[N],n,c[N],b[N];
int lowbit(int x)
{
    return x&(-x);
}
void add(int x)//树状数组
{
    if(x>n+n+2)return;
    c[x]++;
    add(x+lowbit(x));
}
ll get(int x)
{
    if(x==0)return 0;
    return c[x]+get(x-lowbit(x));
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        b[i]=a[i];
        b[i+n]=MOD-a[i]-1;//为了得到比MOD-a[i]小的个数
        f[i]=f[i-1]+a[i];//前缀和
    }
    sort(b+1,b+n+n+1);
    int k=0;
    b[0]=-1000;
    for(int i=1;i<=n+n;i++)
    {
        if(b[i]!=b[i-1])d[b[i]]=++k;
    }
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        ans-=(i-1-get(d[MOD-a[i]-1]))*MOD;
        add(d[a[i]]);//将这个数加入数列中
    }
    for(int i=1;i<=n;i++)//得到所有a[i]+a[j]的和的和
    {
        ans+=f[n]-f[i]+a[i]*(n-i);
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：ThisIsLu (赞：0)

可以注意到，任意两个数的和最多减 $1$ 个 $10^8$。

所以，对 $a_i$ 进行排序，这样一来，对于一个 $i$，我们可以找到一个最小的 $j$，满足 $a_i+a_j> 10^8$，由于单调性，所有在 $j$ 之后的元素都满足相加大于 $10^8$，$a_i$ 的贡献即：$\sum_{j=1}^{i-1}a_j-10^8(i-j)$。

求和直接用前缀和维护即可，至于 $j$ 可以使用二分或双指针维护。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
long long ans;
const int N=3e5+5,mod=1e8;
int n,a[N];
long long s[N];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    s[0]=0;
    for(int i=1;i<=n;i++){
        s[i]=s[i-1]+a[i];
        int op=lower_bound(a+1,a+i,mod-a[i])-a;
        ans+=s[i-1]+1ll*(i-1)*a[i];
        if(op<i){
            ans-=1ll*(i-op)*mod;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：xxboyxx (赞：0)

### 翻译

定义 $f(x,y)$ 为 $(x+y)$ 除以 $10^8$ 的余数。

给你一个长度为 $N$ 的正整数序列 $A$，求以下式子的值 $\displaystyle \sum_{i=1}^{N-1}\sum_{j=i+1}^N f(A_i,A_j)$。

### 思路

观察这个式子，能够发现其实就是求序列中的数两两求和并取模，那么可以打乱顺序。我们可以先求两两相加的总和，再减去和大于 $10^8$ 的次数乘上 $10^8$。因为可以打乱顺序，我们先将这个式子排序，设排序后的序列为 $B$，对于 $x$ 与 $y$，$y>x$，若 $B_x+B_y\ge10^8$，那么对于一个大于 $y$ 且小于等于 $N$ 的正整数 $z$，一定有 $B_x+B_z\ge10^8$。有了上面这条性质，就可以利用二分解决。

### 注意

一定要开长整型！

### 代码

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int n,s=0,sum=0,ans=0;
int a[300005];
signed main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
	}
	sum*=(n-1);//计算两两相加的和 
	sort(a+1,a+n+1);
	for (int i=1;i<=n;i++)
	{
		int k=lower_bound(a+i+1,a+n+1,1e8-a[i])-a;//在k之后的与a[i]相加都大于等于1e8 
		sum-=(n+1-k)*100000000;//每次减1e8 
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：2huk (赞：0)

> - 求 $\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^n ((a_i + a_j) \bmod 10^8)$。
> - $n \le 3 \times 10^8$，$\color{red}a_i < 10^8$。

注意到数据范围中 $a_i < 10^8$，所以 $a_i + a_j < 2 \times 10^8$，所以 $\lfloor (a_i + a_j) / 10^8 \rfloor \le 1$。

这启发我们可以先忽略取模计算答案，即先计算 $\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^n (a_i + a_j)$，再计算有多少对 $(i, j)$ 满足 $a_i + a_j \ge 10^8$，那么答案需要减去数对数量乘 $10^8$。

前一问实现极易，维护前缀和即可。后一问可以将 $a$ 排序，然后枚举 $i$ 并二分求得 $j$ 的数量，当然双指针也是可行的。

```cpp
int n, a[N], sum, res;

void Luogu_UID_748509() {
	fin >> n;
	for (int i = 1; i <= n; ++ i ) fin >> a[i];
	sort(a + 1, a + n + 1);
	
	for (int i = 1; i <= n; ++ i ) {
		res += a[i] * (i - 1) + sum;
		sum += a[i];
	}
	
	for (int i = 1; i < n; ++ i ) {
		int l = i + 1, r = n, j = -1;
		while (l <= r) {
			int mid = l + r >> 1;
			if (a[mid] + a[i] >= 1e8) j = mid, r = mid - 1;
			else l = mid + 1;
		}
		if (~j) res -= (n - j + 1) * P;
	}
	
	fout << res;
}
```

---

## 作者：yegengghost (赞：0)

赛事只打出前两题是不是没救了。

根据数据范围可知，对于数组中任何两个值加起来一定不大于 $2 \times 10^8$，所以对于单个取余，只需减去一个 $10^8$ 即可。

可以用二分查找出当前值的另一半的起点，记为 $num$，即 $10^8-a_i$。

既然要二分，就得先排序，再维护一个前缀和，那么不取余时的答案就是 $qzh_{i-1}+(i-1)\times a_i$。

加了这么多 $a_i$，剪掉的 $10^8$ 的数量也就是当前的下标减去上述的起点的值乘上该数，那么每个 $a_i$ 对答案的贡献也就变成了 $qzh_{i-1}+(i-1)\times a_i - (i-num)\times 10^8$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const long long MOD=1e8;
const int N=3e5+114514;
int n;
int a[N];
int qzh[N];
int ans;
int read()
{
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
signed main()
{
    n=read();
    for(int i=1;i<=n;i++)
    	a[i]=read();
    sort(a+1,a+1+n);//不排序怎么二分捏？ 
    for(int i=1;i<=n;i++)
    	qzh[i]=qzh[i-1]+a[i];//维护前缀和 
    for(int i=2;i<=n;i++)
    {
    	int num=lower_bound(a+1,a+i,MOD-a[i])-a;//二分找起点 
    	//cout<<num<<'\n';
    	ans+=qzh[i-1]+(i-1)*a[i]-(i-num)*MOD;//每一个值对答案的贡献 
	}
	cout<<ans<<'\n';
    return 0;
}

```

我觉得这其中有些可以用 $\KaTeX$，但是不敢用是不是又没救了。

---

