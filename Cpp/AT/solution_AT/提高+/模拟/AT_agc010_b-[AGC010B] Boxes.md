# [AGC010B] Boxes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc010/tasks/agc010_b

$ N $ 個の箱が円環状に並んでおり、$ i $ 番目の箱には $ A_i $ 個の石が入っています。

以下の操作を繰り返して、全ての石を取り除くことができるか判定してください。

- 箱を一か所選ぶ。それを $ i $ 番目としたとき、$ 1 $ から $ N $ の各 $ j $ に対して、$ i+j $ 番目の箱から石をちょうど $ j $ 個取り除く。  
   ただし、$ N+k $ 番目と表される箱は $ k $ 番目の箱と同一視するものとする。

各操作において、取り除きたい個数の石がない箱があるときは、その操作を行えないことに注意してください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ A_i\ ≦\ 10^9 $

### Sample Explanation 1

最初に箱 $ 2 $ を選ぶことで、一回の操作ですべての石を回収できます。

## 样例 #1

### 输入

```
5
4 5 1 2 3```

### 输出

```
YES```

## 样例 #2

### 输入

```
5
6 9 12 10 8```

### 输出

```
YES```

## 样例 #3

### 输入

```
4
1 2 3 1```

### 输出

```
NO```

# 题解

## 作者：zhylj (赞：5)

[广告](zhylj.cc)

考虑差分数组 $d$，一个操作相当于某个数 $d_i\leftarrow d_i-(n-1)$，另外的所有数有 $d_j\leftarrow d_j+1(j\neq i)$，令 $c = \dfrac{n(n+1)}2$，即每次操作减少的数，显然一个必要条件是 $\sum a_i \bmod c = 0$。

设 $m_i$ 代表使用了以 $i$ 开头的操作的次数，再令：

$$M = \frac {\sum a_i}c$$

则有：

$$d_i = (M - m_i) - m_i(n-1) = M - m_in$$

解得：

$$m_i = \frac {M - d_i}n$$

显然要满足的条件为 $m_i$ 为非负整数，这个很容易判断。

```cpp
const int kN = 1e5 + 5;

ll a[kN], d[kN], c, M;

int main() {
	int n; rd(n); c = (ll)n * (n + 1) / 2;
	for(int i = 1; i <= n; ++i) rd(a[i]), M += a[i];
	if(M % c != 0) { printf("NO"); return 0; }
	M /= c;
	for(int i = 1; i <= n; ++i) d[i] = a[i % n + 1] - a[i];
	for(int i = 1; i <= n; ++i)
		if(d[i] > M || (M - d[i]) % n != 0) {
			printf("NO"); return 0;
		}
	printf("YES");
	return 0;
}
```


---

## 作者：Tx_Lcy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_agc010_b)

## 思路

暴力出奇迹！

首先我们可以发现一个规律，每次减的位置一定是数列最小值的位置。

然后暴力减，然后就过了。

时间复杂度 $\mathcal O(\dfrac{\max a_i}{n^2})$，大约在 $10^9$ 左右，所以卡卡也是能过的。

## 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
int const N=1e5+10;
int a[N],minp,minx,maxx,n;
inline void solve(){
	for (int i=minp;i<=n;++i) a[i]-=i-minp+1;
	for (int i=1;i<minp;++i) a[i]-=n-minp+1+i;
	minp=1;minx=a[1];maxx=0;
	for (int i=2;i<=n;++i){
		if (a[i]<minx){minx=a[i];minp=i;}
		maxx=max(maxx,a[i]);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for (int i=1;i<=n;++i) cin>>a[i];
	minp=1;minx=a[1];maxx=0;
	for (int i=2;i<=n;++i){
		if (a[i]<minx){minx=a[i];minp=i;}
		maxx=max(maxx,a[i]);
	}
	while (minx>0) solve();
	if (maxx || minx) cout<<"NO\n";
	else cout<<"YES\n";
	return 0;
}
```


---

## 作者：凌寒 (赞：3)

## AT2303 题解
### 题目描述
* 一列 $n$ 个数字 $a_{i}$ 构成一个环，每次可以从任意一个位置开始，依次将环上的数字 $-1, -2, -3,...,-n$ ，询问是否存在一种方案使最终数列所有数值都是 $0$ ，注意操作次数不定。

### 思路
* 逆向思维，它让我们每次减到 $0$ ，可以考虑反向假设原序列中所有数为 $0$ 从任意点开始每次 $+1, +2, +3,...,+n$ 看能否构成原序列。

* 能否构成原序列我们有以下三个判断依据：

1. 不难看出，这样每一次操作构造出的序列的和的增加量 $x = \frac{n  * (n + 1)}{2}$ ，那么最终构建出的序列总和 $sum =\sum_{i = 1}^{n}a_{i} $ ,一定有 $sum$ 能被 $x$ 整除。若不能整除则说明构不成原序列，这是我们的第一个判断依据。

2. 通过 $+1, +2, +3,...,+n$ 我们不难想到差分的思想。构建差分数组 $c_{i} = a_{i + 1} - a_{i}$ ，每次操作的结果可以分为两种情况，$c_{i} + 1$ 或者 $c_{i} + (1 - n)$。我们令总操作数为 $M = \frac{sum}{x} $ 。如果可以构成原序列，一定有 $(M - c_{i})$ 被 $n$ 整除。这是我们的第二个判断依据。

3. 令以位置 $i$ 开头的操作数为 $m_{i}$ ，总操作数为 $M = \frac{sum}{x} $ 。则有： $c_{i} =(M - m_{i}) +  m_{i}(1-n)$ ；化简： $m_{i} = \frac{M - c_{i}}{n} \ge 0$ 。即 $m_{i}$ 一定为非负数，这是我们的第三个判断依据。

* 具体实现见代码即注释，如下：

------------

### AC CODE

```cpp
// **Crystal_gan && Gan_shin**
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <bitset>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

template <class T>
inline void read(T &x)
{
	x = 0;
	char ch = getchar(), flag = 0;
	while (ch < '0' || ch > '9')
		flag |= ch == '-', ch = getchar();
	while (ch >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	if (flag)
		x = -x;
}
template <class T, class... T1>
inline void read(T &x, T1 &...x1)
{
	read(x), read(x1...);
}
template <class T>
inline bool chkmin(T &a, T b)
{
	return a > b ? a = b, 1 : 0;
}
template <class T>
inline bool chkmax(T &a, T b)
{
	return a < b ? a = b, 1 : 0;
}

const int N = 1e5 + 10;
LL n, sum;
LL a[N], c[N], x;
int main()
{
	// freopen("AT2303.in", "r", stdin);
	// freopen("AT2303.out", "w", stdout);
	read(n);
	// 每次操作和的增加量 x 
	x = n * (n + 1) / 2;
	// 序列总和为 sum
	for (int i = 1; i <= n; i++)
		read(a[i]), sum += a[i];
	// 操作总次数
	LL M = sum / x;
	// 判断依据1：
	if (sum % x != 0) {
		printf("NO\n");
		return 0;
	}
	// 构建差分数组
	for (int i = 1; i <= n; i++)
		c[i] = a[i % n + 1] - a[i];
	for (int i = 1; i <= n; i++)
		// 判断依据2和3：
		// 如果 (M - c[i]) / n < 0 或者 n 不能整除 (M - c[i]) 说明无解
		// n > 0, 所以只需要判断 (M - c[i]) < 0 即可
		if ((M - c[i]) % n != 0 || M - c[i] < 0) {
			printf("NO\n");
			return 0;
		}

	printf("YES\n");
	return 0;
}

```


---

## 作者：Kreado (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_agc010_b)。

#### 思路

本题是一个简单的思维题。

我们令 $p$ 表示操作次数，每次操作数列和的变化为 $\dfrac{n(n+1)}{2}$，容易得到 $p=\dfrac{2\sum_{i=1}^n a_i}{n(n+1)}$，当然，$p$ 要为正整数。

考虑差分，令 $d_i$ 表示 $p$ 次操作后 $a_i$ 和 $a_{i-1}$ 的差，可以得到 `d[i]=a[i%n+1]-a[i]`，由于是一个连续数字的环，所以每次操作只会有两种情况，$d_i+1$ 或者 $d_i+(1-n)$，设 $x$ 表示情况一数量的总和，则有 $d_i=p-nx$，所以只需 $x$ 为正整数即可。

#### CODe

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll Maxn=1e5+7;
ll n,a[Maxn],sum,d[Maxn];
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]),sum+=a[i];
	if((sum)%((n*n+n)/2)) return printf("NO"),0;
	for(ll i=1;i<=n;i++) d[i]=a[i%n+1]-a[i];
	ll p=sum*2/(n*n+n);
	for(ll i=1;i<=n;i++)
		if(d[i]>p||(p-d[i])%n) return printf("NO"),0;
	printf("YES");
	return 0;
}

```


---

## 作者：k2saki (赞：1)

看见这种区间$\texttt{+1,+2...+n}$就立马想到了差分，然后题目就转化成了：先求出差分数组，然后每次操作将一个值 $c_i$变成$c_i-(n-1)$，然后让其他所有值都 +1。

然后就可以求出每个$c_i$被-(n-1)的次数。

总次数为$\sum_{i=1}^na[i]/((n+1)*n/2)$  
若此式不为正整数，直接输出 NO。

每个数被操作的次数可以 $O(1)$ 求出，设总次数为 k，当前这个次数为$s_i$，则有

$c_i=(k-s_i)-(n-1)*s_i$

$c_i=k-s_i*n$

$s_i=\frac{k-c_i}{n}$

判断$s_i$是否为非负整数就可以了，不需要开数组。

---

## 作者：litble (赞：1)

[戳我＝￣ω￣＝](https://blog.csdn.net/litble/article/details/83183748)

首先我们可以知道要做$m=\frac{\sum a}{\frac{n(n+1)}{2}}$次这样的操作才可能把石子取完（当然$m$如果不是非负整数就肯定输出NO）。

然后对于一个盒子$i$和它前面的盒子$i-1$，它们可能会被做两种类型的操作，一种叫做$i$取1个$i-1$取$n$个，一种叫做$i$取$x+1$个$i-1$取$x$个，则第一种操作会使$d_i=a_i-a_{i-1}$的值增加$n-1$，第二种会使$d_i$减少$1$。

如果最后都取完，则$d_i$显然一样了，所以设第一种操作做了$x$次，则第二种做了$m-x$次，$(n-1)x-(m-x)+d_i=0$，解得$x=\frac{m-d_i}{n}$，如果解出来不是非负整数肯定输出NO。

于是我们知道了这$m$次操作是从哪个盒子开始取第一个石子，也就知道了每个盒子里应该有多少石子，检验一遍即可（这个扫两遍就可以求了，具体可以看代码）。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
int read() {
	int q=0;char ch=' ';
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
	return q;
}
typedef long long LL;
const int N=100005;
LL sum,nowadd,nows,a[N],orz[N],m;int n;
int work() {
	int js=0;
	for(RI i=0;i<n;++i) {
		int b=a[i]-a[(i-1+n)%n];
		if((m-b)%n||m-b<0) return 0;
		orz[i]=(m-b)/n,js+=orz[i];
	}
	if(js!=m) return 0;
	for(RI i=0;i<n;++i) {
		nows+=orz[i],nowadd+=nows;
		if(a[i]<nowadd) return 0;
		a[i]-=nowadd;
	}
	for(RI i=0;i<n;++i) {
		nows-=orz[i],nowadd-=1LL*n*orz[i],nowadd+=nows;
		if(a[i]!=nowadd) return 0;
	}
	return 1;
}
int main()
{
	n=read();
	for(RI i=0;i<n;++i) a[i]=read(),sum+=a[i];
	if(sum%(1LL*(n+1)*n/2)) {puts("NO");return 0;}
	m=sum/(1LL*(n+1)*n/2);
	if(work()) puts("YES");
	else puts("NO");
	return 0;
}
```

---

## 作者：SalN (赞：0)

Link: [AT2303 [AGC010B] Boxes](https://www.luogu.com.cn/problem/AT2303)


### 题目描述

$N$ 个数字 $A_i$（顺时针给出）构成一个环，每次可以从一个起点出发顺时针给这个环依次 $-1,-2,...,-n$，问是否存在一种方案使得能把所有数恰好都减成 $0$

这个题目相当于

在一个 $N$ 个数字（初始为 $0$ ）的序列每次找一个位置依次 $+1,+2,+3,...,+n$，问是否可能和原序列相等

----

考虑一下 满足 的情况

设每加一组（指一轮 $+1,+2,...,+n)$ 共加了 $s$，显然 $s=\frac{1}{2}(1+n)n$

设总共加了 $k$ 组，因为每一组加的和一定为 $s$ 且总数一定，有

$$ k=\frac{1}{s} \sum\limits A_i,s|\sum\limits A_i$$

看看只有一个环的情况，我们可以将每个位置分成两种， ⌈ 变换 ⌋ 的为从 $N$ 变成 $1$ 的， ⌈ 不变换 ⌋ 的为从 $i$ 变成 $i+1$ 的，⌈ 变换 ⌋ 的贡献是 $1-N$，⌈ 不变换 ⌋ 的贡献是 $1$

特别的，我们可以令 $A_0\gets A_n$ 方便处理头和尾相连的地方，也可以取模或者特判，随你喜欢，怎么都行

之后考虑 $A_{i-1}$ 和 $A_{i}$，这个过程中产生的总贡献为 $A_i-A_{i-1}$，设 $X_i$ 为这个位置环中变换的个数，则不变换的个数为 $k-X_i$，那么有

$$ (1-N)X_i+(k-X_i)=A_i-A_{i-1} $$

$$ X_i=\frac{A_{i-1}-A_i+k}{N} $$

$X_i$ 肯定是整数的说，所以 $N|A_{i-1}-A_i+k$，还有就是 $0\leq X_i\leq k$，有时候 $X_i$ 这玩意会跑一个负数出来，那是不合法的，同时可能会导致其它组跑了 $k$ 次以上

如果满足这些，跑出来的总变换数就是 $\sum X_i=\sum \frac{A_{i-1}-A_i+k}{N} =k$，不用额外判断

而差分与原序列一致且总数一致所以序列是唯一的且与原序列相同，以上条件就是充要条件

----

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define MN 101000

using namespace std;

int n, a[MN], fl=1;
/* 这个fl是答案，1为 "YES"，0为 "NO"  */
int s, k, suma;

signed main() {
	scanf("%lld", &n);
	for(int i=1; i<=n; ++i) {
		scanf("%lld", a+i);
		suma+=a[i]; // A_i 的和 
	}
	s=(1+n)*n/2; // 加一组的和 
	if(suma%s!=0) fl=0; // 不满足 s|sum A_i 的情况 
	a[0]=a[n], k=suma/s; 
	/* 特殊处理环，计算组数 */ 
	for(int i=1; i<=n; i++) {
		int xn=k-a[i]+a[i-1]; 
		if(xn%n!=0||xn/n<0||xn/n>k)
		/* 不满足 N|k-a[i]+a[i-1]，不满足 0<=X_i<=k */ 
			{ fl=0; break; }
	}
	if(fl) printf("YES\n");
	else printf("NO\n");
	return 0;
}
```


---

## 作者：elijahqi (赞：0)

 http://www.elijahqi.win/archives/1357

http://agc010.contest.atcoder.jp/tasks/agc010_b



因为是一个排列所以我们应该来研究他们的差有什么关系  我们可以知道每个数之间差的形成都是由于 排列而形成的 有可能我是一头一尾 那么差就是-(n-1) 其他则为+1  那么我不妨把第一位在末尾重新加一下  然后算出他们的差 通过这个差我们可以解一个一元一次方程 分别求出每个位置有多少个排列是从这里开始的 只要这个排列数不<0或者不是整数那么就可能是答案 注意1的时候要提前特判输出yes
```
#include<cstdio>
#define N 110000
inline char gc(){
	static char now[1<<16],*T,*S;
	if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
	return *S++;
}
inline int read(){
	int x=0;char ch=gc();
	while (ch<'0'||ch>'9') ch=gc();
	while (ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=gc();}
	return x;
}
int n,a[N],differ[N];
int main(){
	freopen("box.in","r",stdin);
	n=read();long long sum=0;long long sum1=0;
	if (n==1){printf("YES");return 0;}
	sum1=(long long)n*(n+1)>>1;
	for (int i=1;i<=n;++i) a[i]=read(),sum+=a[i];a[n+1]=a[1];
	for (int i=1;i<=n;++i) differ[i]=a[i+1]-a[i];int k=sum/sum1;
	if (sum%sum1){printf("NO");return 0;}
	for (int i=1;i<=n;++i){
		double x=(differ[i]-k)/(-1.0*n);
		if (x<0){printf("NO");return 0;}
		int xx=x;if (xx!=x){printf("NO");return 0;}
	}
	printf("YES");
	return 0;
}
```

---

## 作者：fpjo (赞：0)

考虑用操作构成原数列。

显然 $\sum_{i=1}^{n}a_i\equiv0 \mod \frac{(n+1)n}{2}$ ，且总操作数 $M=\frac{\sum_{i=1}^{n}a_i}{\frac{(n+1)n}{2}}$ 。

因为操作为 $+n,+1,+2,...,+n-1$ ，考虑差分数组，令 $d_i=a_{i+1}-a_i$,可以发现 $d_i$ 的变化就 2 种，+1 或 +(1-n) 。

令以位置 $i$ 为开头的操作数为 $m_i$ , 可知 $m_i(1-n)+(M-m_i)=d_i$ 。所以 $m_i=\frac{M-d_i}{n}$ ，且 $m_i$ 必须是非负整数。

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long const MAXN=1e5+10;
long long n,sum;
long long a[MAXN],d[MAXN],c[MAXN];

signed main(){
	//freopen("in1.txt","r",stdin);
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++){scanf("%lld",&a[i]);sum+=a[i];}
	long long kkk=(long long)(1+n)*n/2;
	if(sum%kkk!=0){printf("NO\n");return 0;}
	else{
		for(int i = 1; i <= n; ++i)d[i]=a[i%n+1]-a[i];
		sum/=kkk;
		for(long long i=1;i<=n;i++){
			if((sum-d[i])%n!=0){printf("NO\n");return 0;}
			int num=(sum-d[i])/n;
			if(num<0){printf("NO\n");return 0;}
		}
		//if(cnt!=m){printf("NO\n");return 0;}
	}
	printf("YES\n");
	return 0;
}
```

---

