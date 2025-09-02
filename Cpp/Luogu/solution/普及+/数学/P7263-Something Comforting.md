# Something Comforting

## 题目背景

![Something Comforting](https://mivik.gitee.io/image/nurture/something_comforting.png)

> Cause getting made you want more
>
> And hoping made you hurt more
>
> Someone tell me
>
> Something comforting

## 题目描述

Porter Robinson 花了五年的时间制作了 Something Comforting 这首歌，Mivik 花了五天时间造出了一道和括号序列相关的题。但 Mivik 并不开心，因为他发现他不会造数据了！

Mivik 需要随机生成一个 **合法** 的括号序列，于是 Mivik 想了一会，写出了下面的算法：

```cpp
#include <algorithm>
#include <string>

std::string generate(int n) { // 生成一个长度为 n * 2 的括号序列
	const int len = n * 2;
	bool arr[len]; // 0 代表左括号，1 代表右括号
	for (int i = 0; i < n; ++i) arr[i] = 0;
	for (int i = n; i < len; ++i) arr[i] = 1;
	std::random_shuffle(arr, arr + len); // 随机打乱这个数组
	for (int i = 0, j, sum = 0; i < len; ) {
		sum += arr[i]? -1: 1;
		if (sum < 0) { // 出现了不合法的位置
			for (j = i + 1; j < len; ++j) {
				sum += arr[j]? -1: 1;
				if (sum == 0) break;
			}
			// 现在 i 是第一个不合法的位置，j 是 i 后面第一个合法的位置
			// ( ( ) ) ) ) ( ( ( ) ( )
			//         i     j
			for (int k = i; k <= j; ++k)
				arr[k] ^= 1; // 把这段区间全部反转
			i = j + 1;
		} else ++i;
	}
	std::string ret;
	for (int i = 0; i < len; ++i)
		ret += arr[i]? ')': '(';
	return ret;
}
```

P.S. 为了给其它语言用户带来做题体验，[这里](https://www.luogu.com.cn/paste/wof8zjn8) 提供了多种语言对该算法的描述。

Mivik 十分开心，因为这个算法总能生成合法的括号序列。但不一会儿他就发现这个算法生成的括号序列并不均匀，也就是说，当 $n$ 固定时，所有合法的括号序列出现的概率并不均等。例如，Mivik 发现当 $n=3$ 时，`()()()` 被生成的概率要远大于 `((()))`。

现在 Mivik 给了你一个 $n$ 和一个长度为 $2n$ 的 **合法** 括号序列，假设 `std::random_shuffle` （对于其它语言来说，`shuffle`）能够均匀随机地打乱一个数组，他想问问你这个括号序列通过上文的算法被生成的概率是多少。由于 Mivik 不喜欢小数，你需要输出这个概率对 $998244353$ 取模的结果。如果你不知道如何将一个有理数对质数取模，可以参考 [有理数取模](https://www.luogu.com.cn/problem/P2613)。

## 说明/提示


### 样例解释

样例一：$n$ 为 1 时，无论怎样都只可能会生成 `()` 这一种合法的括号序列，因此概率为 1。

### 数据范围

对于全部数据，有 $1\le n\le 5\cdot 10^5$，且输入的括号序列合法。

Subtask 1（20 pts）：保证 $1\le n\le 5$。

Subtask 2（30 pts）：保证 $1\le n\le 1000$。

Subtask 3（50 pts）：无特殊限制。


## 样例 #1

### 输入

```
1
()```

### 输出

```
1```

## 样例 #2

### 输入

```
3
()(())```

### 输出

```
598946612```

# 题解

## 作者：Mivik (赞：18)


[欢迎到我的博客查看](https://mivik.gitee.io/2021/solution/mivik-round-nurture-something-comforting/)

## 满分做法

我们还是把括号序列转换成那个经典的“走右上右下”的形式，即从 $(0,0)$ 开始行走，左括号是向右上走，右括号是向右下走，那么一个括号序列合法等价与行走轨迹不越过 X 轴。比如下图是 `()(())` 对应的行走轨迹：

![轨迹](https://cdn.luogu.com.cn/upload/image_hosting/dua0xcz0.png)

我们发现，算法最开始随机 random_shuffle 出来的括号序列，对应着一个可能越过了 X 轴，但最终走到了 $(2n,0)$ 的行走轨迹（因为左括号右括号数目相等）。然后仔细观察我们的算法，实际上就是找到第一个低于 X 轴的位置和在这个位置后第一次走回 X 轴的位置，并把中间的一段翻到 X 轴上去了。这样必定能形成最终的合法括号序列。

于是答案就显而易见了。由于在翻转过程中我们的行走轨迹中与 X 轴相交的那些点是不变的，所以如果一个合法的括号序列对应的行走轨迹有 $m$ 个点与 X 轴相交，它就可能由 $2^{m-1}$ 次方种括号序列得到（每一个部分在 X 轴上方或者下方），所以答案就是 $\frac{2^{m-1}}{\binom{2n}n}$。

[mivik.h](https://mivik.gitee.io/mivik.h)

[代码](https://paste.ubuntu.com/p/xg7kRFfWJq/)


---

## 作者：Lonely_NewYear (赞：8)

# 洛谷 P7263 题解

有理数取模就不费赘述了，还没学的[点我](https://www.luogu.com.cn/problem/P2613)。

## 题目分析

### step 1

~~题目给的程序好像有不少人怀疑会错~~

差不多就是从左到右找到第一个不合法的位置，比如下面这个括号序列：

```
( ( ) ) ) ) ( ( ( ) ( )
        ^
        |
      不合法
```

之后找到这个位置后面第一个合法的：

```
( ( ) ) ) ) ( ( ( ) ( )
        ^     ^
        |     |
      不合法 合法
```

最后把这一段翻转：

```
( ( ) ) ( ( ) ) ( ) ( )
        ^     ^
        |     |
      不合法 合法
```

至于翻转后为什么一定正确，可以发现合法其实就是要使当前位置 $sum>0$，因为我们找出的是第一个 $sum\ge 0$, 的位置，所以这个位置之前的 $sum$ 一定一直小于 $0$，而翻转就是取相反数，$sum$ 就必定一直大于 $0$，括号序列就一定是合法的。

### step 2

（目标括号序列指输入给出的，初始序列指程序最初随机生成的）

首先，我们知道 $\texttt{概率}=\frac{\texttt{合法方案数}}{\texttt{总方案数}}$，最初随机生成的括号序列总共有 $C^n_{2n}$ 种可能（就是在 $2n$ 个位置中选 $n$ 个作为左括号）。现在只需要求出能够被程序转化成目标括号序列的随机括号序列有多少种。

我们可以给目标括号序列分个段：（每个极大的括号组分一段）

```
( ( ) )|( ( ) )|( )|( )
```

可以发现每个括号组在初始括号序列中只有两种可能：

1. 被翻转过

2. 没有被翻转

所以就有 $2^4=16$ 中初始括号序列能够被转化为上面那个目标括号序列。

设目标括号序列能够分 $k$ 段，所以对于一种目标括号序列，它的初始括号序列就有 $\frac{2^k}{C^n_{2n}}$ 种可能。

这就是答案。

组合数暴力求解即可，复杂度（别忘了还有有理数取模）是 $O(n\log 998244353)$。

## 代码

```cpp
#include<cstdio>
using namespace std;
const int mod=998244353;
char s[1000002];
long long ksm(long long k,long long b)//有理数取模
{
    long long s=1;
    while(b)
	{
        if(b&1)s=s*k%mod;
        b>>=1;
        k=k*k%mod;
    }
    return s;
}
int main()
{
	int n,sum=0;
	scanf("%d%s",&n,s+1);
	long long ans=1;
	for(int i=1;i<=2*n;i++)
	{
		if(s[i]=='(') sum++;
		else sum--;
		if(sum==0)//新的一段
		{
			ans=ans*2%mod;
		}
	}
	long long num=1;//组合数
	for(int i=n+1;i<=2*n;i++)
	{
		num=num*i%mod;
	}
	for(int i=1;i<=n;i++)
	{
	    num=num*ksm(i,mod-2)%mod;
	}
	printf("%lld",ans*ksm(num,mod-2)%mod);
    return 0;
}
```

谢谢观看！

~~点个赞再走呗~~

---

## 作者：vectorwyx (赞：4)

我们从所给代码中的变量 $sum$ 入手，考虑 $sum$ 与 $i$ 的关系。令 $sum_{i}$ 表示遍历到第 $i$ 个位置时 $sum$ 的大小，则有 $sum_{i}=sum_{i-1}+1$ 或 $sum_{i}=sum_{i-1}-1$。

假设我们在执行代码时取反了 $[i,j]$ 这段区间，那么在取反之前一定有 $sum_{i-1}=0,sum_{i}=-1,sum_{i+1,i+2…,j-1}\le -1,sum_{j}=0$。不难看出取反 $[i,j]$ 这段区间相当于把 $sum_{i…j}$ 都取反。转化一下，区间 $[i,j]$ 能由某种括号序列取反得到，当且仅当 $sum_{i-1}=0,sum_{j}=0$ 且 $\forall k\in [i,j-1],sum_{k} \not= 0$。每有这样的一段区间，所给代码中合法的 $arr$ 序列的方案数就会乘 $2$。满足条件的区间数量就是 $sum$ 数组中 $0$ 的个数，设为 $cnt$，合法的方案数就是 $2^{cnt}$，算概率还需要除以总的方案数。总方案数也不难算，相当于从 $2n$ 个位置里无顺序地选出 $n$ 个位置作为 $1$，即 $C(2n,n)$。最终的答案就是  $\frac{2^{cnt}}{C(2n,n)}$ 对 $998244353$ 取模的结果。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){ int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){ if(ch=='-') fh=-1; ch=getchar(); } while(isdigit(ch)){ x=(x<<1)+(x<<3)+ch-'0'; ch=getchar(); } return x*fh; }

const int yrz=998244353;

int ksm(int x,int y){
	if(y==0) return 1;
	int k=ksm(x,y/2);
	k=1ll*k*k%yrz;
	if(y&1) k=1ll*k*x%yrz;
	return k;
}

int main(){
	int n,sum=0,cnt=0,jc1=1,jc2=1;
	cin>>n;
	fo(i,1,n) jc1=1ll*jc1*i%yrz;
	fo(i,n+1,2*n) jc2=1ll*jc2*i%yrz; 
	char ch=getchar();while(ch!='('&&ch!=')') ch=getchar();
	fo(i,1,n*2){	
		if(ch=='(') ++sum;
		else --sum;
		if(sum==0) ++cnt;
		ch=getchar();
	}
	cout<<1ll*ksm(2,cnt)*ksm(1ll*jc2*ksm(jc1,yrz-2)%yrz,yrz-2)%yrz;
	return 0;
}
```


---

## 作者：Sol1 (赞：3)

易得对于一个长为 $n$ 的括号串 $s$，如果第 $1$ 个括号匹配的是最后一个括号，则生成它的概率为 $\dfrac{2}{\binom{n}{n/2}}$（即，只能恰好全部相同或恰好全部相反，否则经过翻转之后一定不是这个样子）。

然后对于两个串 $A,B$，设生成它们的概率分别为 $P_A,P_B$，则生成 $AB$ 需要如下条件：

1. 生成 $A$；
2. 生成 $B$；
3. $A$ 一侧恰好有 $\dfrac{|A|}{2}$ 个左括号，$B$ 一侧恰好有 $\dfrac{|B|}{2}$ 个左括号。

所以得到概率式：

$$P_{AB}=P_AP_B\cdot\dfrac{\dbinom{|A|}{|A|/2}\dbinom{|B|}{|B|/2}}{\dbinom{|A|+|B|}{|A|/2+|B|/2}}$$

于是直接预处理组合数和每一个括号对应的匹配，$O(n)$ 递推即可。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <stack>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

const int N = 1000005, mod = 998244353;

long long fac[N], inv[N];
int n, match[N];
string s;
stack <int> stk;

inline long long C(long long n, long long r) {
    return fac[n] * inv[r] % mod * inv[n - r] % mod;
}

inline void Read() {
    cin >> n >> s;
}

inline long long Power(long long x, long long y) {
    long long ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return ans;
}

inline void Prefix() {
    fac[0] = fac[1] = 1;
    inv[0] = inv[1] = 1;
    for (int i = 2;i <= (n << 1);i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    for (int i = 2;i <= (n << 1);i++) inv[i] = inv[i] * inv[i - 1] % mod, fac[i] = fac[i - 1] * i % mod;
    for (int i = 0;i < (n << 1);i++) {
        if (s[i] == '(') stk.push(i);
        else {
            match[stk.top()] = i;
            stk.pop();
        }
    }
}

inline void Solve() {
    long long ans = 1;
    for (int i = 0;i < (n << 1);i = match[i] + 1) {
        int l = i, r = match[i], len = r - l + 1;
        //printf("len=%d\n", len);
        long long pr = 2ll * Power(C(len, len / 2), mod - 2) % mod;
        //printf("%lld\n", pr);
        ans = ans * pr % mod * C(len, len / 2) % mod * C(r + 1 - len, r + 1 - len >> 1) % mod * Power(C(r + 1, r + 1 >> 1), mod - 2) % mod;
    }
    printf("%lld", ans);
}

int main() {
    Read();
    Prefix();
    Solve();
	return 0;
}
```

---

## 作者：Unordered_OIer (赞：2)

# P7263
好，很好，又是赛时 nt 挂掉的一道题。

## 题意
给定一段生成括号序列的代码：
```cpp
#include <algorithm>
#include <string>

std::string generate(int n) { // 生成一个长度为 n * 2 的括号序列
	const int len = n * 2;
	bool arr[len]; // 0 代表左括号，1 代表右括号
	for (int i = 0; i < n; ++i) arr[i] = 0;
	for (int i = n; i < len; ++i) arr[i] = 1;
	std::random_shuffle(arr, arr + len); // 随机打乱这个数组
	for (int i = 0, j, sum = 0; i < len; ) {
		sum += arr[i]? -1: 1;
		if (sum < 0) { // 出现了不合法的位置
			for (j = i + 1; j < len; ++j) {
				sum += arr[j]? -1: 1;
				if (sum == 0) break;
			}
			// 现在 i 是第一个不合法的位置，j 是 i 后面第一个合法的位置
			// ( ( ) ) ) ) ( ( ( ) ( )
			//         i     j
			for (int k = i; k <= j; ++k)
				arr[k] ^= 1; // 把这段区间全部反转
			i = j + 1;
		} else ++i;
	}
	std::string ret;
	for (int i = 0; i < len; ++i)
		ret += arr[i]? ')': '(';
	return ret;
}
```
求给出的括号序列通过上述算法被生成出来的概率是多少。

## 题解
我们观察这个算法构造一个合法括号序列的过程：
```
( ( ) ) ) ) ( ( ( ) ( )
        i     j  
( ( ) ) ( ( ) ) ( ) ( )
```
我们发现，每次定下一个 $i,j$，经过反转之后都会形成一个合法的括号串。

也就是说，对于一个合法的括号串，我们都可以对其进行如下分段：

```
( ( ) ) ( ( ) ) ( ) ( )
分段：
( ( ) )|( ( ) )|( )|( )
```

分段后每段都是一个独立的完全嵌套的括号串。

然后我们考虑对每一个独立的合法括号串进行分析，考虑到它要么是被直接生成，要么是被反转得到，也就是说对于每一个分段出来的括号串，它被生成出来一共有 $2$ 种可能。

也就是说，整个串如果被分为 $k$ 段，它被生成出来一共有 $2^k$ 种方法。

然而题目要求我们求的是概率，众所周知，概率 $=\frac{a}{b}$，$a$ 为合法数量，$b$ 为总数量，而所有长度为 $2n$ 的被生成的括号串一共有 $\begin{pmatrix}2n\\n\end{pmatrix}$ 种。

于是我们就得出了一个结论：

$$ans=\dfrac{2^k}{\begin{pmatrix}2n\\n\end{pmatrix}}$$

然后就做完了。最后就是有理数取模，不会的[点这里](https://www.luogu.com.cn/paste/4duxmkm4)。

## Code
```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define N 500005
using namespace std;
typedef long long ll;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
inline void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
inline void writeln(ll x){write(x),putchar('\n');}
char s[N<<1];
inline ll pw(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1)res=(res*a)%mod;
		a=(a*a)%mod,b>>=1;
	}
	return res;
}
ll n,sum,fz=1,fm=1;
inline void calcfz(){
	for(ll i=1;i<=(n<<1);i++){
		sum+=(s[i]=='('?1:-1);
		if(sum==0)fz=fz*2%mod;
	}
}
inline void calcfm(){
	for(ll i=n+1;i<=2*n;i++)fm=fm*i%mod;
	for(ll i=1;i<=n;i++)fm=fm*pw(i,mod-2)%mod;
}
inline ll ans(){return fz*pw(fm,mod-2)%mod;}
int main(){
	n=read();
	scanf("%s",s+1);
	calcfz(),calcfm();
	writeln(ans());
    return 0;
}
```

---

## 作者：_Anchor (赞：2)

# 题意

[传送门](https://www.luogu.com.cn/problem/P7263)

给一个随机生成合法括号序列的程序，给定一个合法括号序列，求随机出这个序列的概率

# 分析

第一要明确的，是我们该如何统计概率，这里总可能情况比较好计算，那么我们就考虑用 个数/总数 来求解概率。

那么接下来，我们先简单的来看一下程序的含义：

```cpp
#include <algorithm>
#include <string>

std::string generate(int n) { // 生成一个长度为 n * 2 的括号序列
	const int len = n * 2;
	bool arr[len]; // 0 代表左括号，1 代表右括号
	for (int i = 0; i < n; ++i) arr[i] = 0;
	for (int i = n; i < len; ++i) arr[i] = 1;
	std::random_shuffle(arr, arr + len); // 随机打乱这个数组
	for (int i = 0, j, sum = 0; i < len; ) {
		sum += arr[i]? -1: 1;
		if (sum < 0) { // 出现了不合法的位置
			for (j = i + 1; j < len; ++j) {
				sum += arr[j]? -1: 1;
				if (sum == 0) break;
			}
			// 现在 i 是第一个不合法的位置，j 是 i 后面第一个合法的位置
			// ( ( ) ) ) ) ( ( ( ) ( )
			//         i     j
			for (int k = i; k <= j; ++k)
				arr[k] ^= 1; // 把这段区间全部反转
			i = j + 1;
		} else ++i;
	}
	std::string ret;
	for (int i = 0; i < len; ++i)
		ret += arr[i]? ')': '(';
	return ret;
}
```

首先给定了长度$n$，生成了长度为$2n$的括号序列

第一步我们把其中$1$~$n$元素初始化为左括号，把$n+1$~$2n$初始化为右括号（程序里下标从$0$开始的）

然后$random$_$shuffle$随机打乱这个括号序列

现在括号序列有$n$个左括号，$n$个右括号，但是不一定合法

接下来的循环就是把不合法的段修正

首先$sum$前缀和用于判断当前合不合法（因为左括号$+1$右括号$-1$，而当右括号个数大于左括号个数就是不合法的，也就是$sum<0$的时候）

那么我们往后枚举，找到一个使得左右括号个数相等的位置，那么此时我们可以发现，把当前第一个不合法位置到第一个合法的位置这一段中的括号序列反转，依然合法，且原括号个数不变，也就不影响正确性

程序就是这样来保证括号序列合法的

那么这样做带给我们什么启发呢？

很容易发现，其实我们每次随机生成，原本的等概率发生变化的地方就是我们把不合法的重新变成合法的这个过程。

那么我们考虑这个过程带来的影响：

正着考虑很难，正好我们又是给定了结果求有多少种起始状态可以到达，那么我们可以考虑给定结果反向思考此时“修正”操作的影响

假设现在给出的是：

$()(())$

因为每次翻转过后，我们会保证的是：假设第一个不合法点为位置$x$，第一个合法点位置为$y$，那么$1$~$x-1$这段区间是合法的，且之后$y+1$~$2n$这段区间也是合法的

也就是说，我们每一组这样的点，对应了序列上的一段区间，且所有的这样的区间之和，恰好完全覆盖了整个序列且相互之间没有重叠

那么我们单独抽离这样的一个区间进行分析：

如果现在我们找到了这样的一个区间，那么这段区间最后会被翻转，那么对于我们答案序列来说，这样的区间就有两种情况：

$1.$是由翻转得到的

$2.$没有翻转原本就是这样的

而翻转得到的这段区间是唯一的（就是任意两个不同的括号序列翻转过后一定不相同）

而没翻转的显然也是唯一的

所以对于每一个有可能翻转的答案区间，它的原始区间都有两种可能的情况，所以我们每遇到这样的一个区间，就把方案数$*2$即可

那么现在的问题就是如何统计有多少个这样的区间，方案数自然就是$2^k$（$k$就是个数）

所以我们考虑这样的区间，根据刚刚的例子，可能的初始序列为：

$()))(($，$)())(($，$()(())$，$)((())$

共四种。

发现每次可能翻转的其实就是最外层的括号，感性证明也很容易，因为我们每次都是找到的一个极大区间进行翻转，我们每次翻转只会影响自己代表的区间，和其它部分完全没有关系

上述例子中，可供翻转的区间就是$[1,2]$和$[3,6]$

那么现在我们也已经知道了如何就初始状态数，最后我们求一下总数，再求其逆元即可

问题变成了：给定$n$，求长度为$2n$的括号序列，满足：其中有$n$个左括号，$n$个右括号，这样情况的方案数

那么我们先把$2n$个括号随机打乱，然后考虑构造合法情况，我们先找出$n$个右括号，除掉全排列去重，然后找出$n$个左括号，除掉全排列去重，然后得到的就是答案

写出来就是
$$
\Large \frac{P_{2n}^{2n}}{P_{n}^{n}*P_{n}^{n}} =\frac{(2n)!}{(n!)^2}
$$
记其为$N$，记$N$的逆元为$N'$，记当前情况方案数为$k$，概率就是$k*N'$

答案$k*N'$

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=false;
	while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
}
template <typename T,typename... Args> inline void read(T& t, Args&... args){read(t);read(args...);}
template <typename T>
inline void write(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
template <typename T>
inline void print(T x){write(x),putchar(' ');}
#define ll long long
#define ull unsigned long long
#define inc(x,y) (x+y>=MOD?x+y-MOD:x+y)
#define dec(x,y) (x-y<0?x-y+MOD:x-y)
#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)
const int N=1e5+5,M=1e6+5,MOD=998244353;
ll QuickPow(ll x){
	ll y=MOD-2,res=1;
	while(y){
		if(y&1) res=res*x%MOD;
		y>>=1;
		x=x*x%MOD;
	}
	return res;
}
ll n,ans=1,ans1=1,sum,w=1;
char ch[N],sta[N];
int main(){
	read(n);
	for(int i=1;i<=2*n;i++) ch[i]=getchar();
	for(int i=1;i<=2*n;i++) ans=ans*i%MOD;
	for(int i=1;i<=n;i++) ans1=ans1*i%MOD;
	ans=QuickPow(ans*QuickPow(ans1*ans1%MOD)%MOD);
	for(int i=1;i<=2*n;i++){
		if(ch[i]=='(') sum++;
		else sum--;
		if(sum==0) w=w*2%MOD;
	}
	write(w*ans%MOD);
	return 0;
}
```









---

## 作者：囧仙 (赞：1)

## 题目大意

- 有一个随机括号序列生成器，首先会随机生成一个**不一定合法的**长度为 $2\times n$ 的由 $n$ 个左括号和 $n$ 个右括号组成的序列。然后顺序枚举，每碰到一个不合法的右括号就找到它最右侧的合法的左括号，并翻转这段区间。

- 现在给出有一个长度为 $2\times n$ 的合法的括号序列，询问随机括号生成器生成出它的概率为多少。结果对 $998244353$ 取模。

## 题解

考虑一个非常重要的结论：**最终序列中一个连续的合法的括号序列，最多只由一次翻转得到**。并且不合法的右括号左侧的括号序列必定是合法的。

补充一下从头开始的括号括号序列的定义。这个序列并不会包含于任何一个括号序列之中。更形式一些的说法，它左侧的所有括号可以组成一个合法的括号序列。

考虑根据题目给出的代码，左括号记为 $+1$ ，右括号记为 $-1$ ，计算其前缀和。

$$\verb!())))((()(()!=\{1,0,-1,-2,-3,-2,-1,0,-1,0,1,0\}$$

到第三个括号的时候，它的前缀值为 $-1$ 。于是我们要找到它右侧第一个合法的左括号（也就是第一个前缀值为 $0$ 的括号，对应于第 $8$ 个）然后进行翻转。

经过观察，我们能够发现，反转的区间**必定中间的值都不大于 $0$** 。因此，最终结果里一段从头开始的合法括号序列最终由不超过一次翻转得到。

这个结论说明了什么呢？**一个从头开始的合法括号区间要么翻转一次，要么不翻转**。

考虑初始生成的括号序列有多少种。假设原先 $2\times n$ 个括号都是左括号，我们选择其中 $n$ 个进行翻转后就是一个满足初步要求的初始序列了，因此总方案数为从 $2n$ 个数中挑选 $n$ 个的结果，即为 $C(2n,n)$ 。

然后最终括号序列之前可能对应多少种括号序列呢？这可以用乘法原理得到。每个从头开始的括号序列都有翻转或者不翻转两种情况，于是最终的答案为：

$$\frac{2^t}{C(2n,n)}$$

其中 $t$ 是从头开始的括号序列的总个数。总时间复杂度为 $\mathcal O(\log_2 n+n)$ 。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
char rdc(){
    char c; while(!isgraph(c=getchar())); return c;
}
const int MOD=998244353;
const int MAXN =5e5+3;
int n,w,s,F[MAXN];
int pwr(int a,int b){
    int r=1; while(b){
        if(b&1) r=1ll*r*a%MOD; b>>=1,a=1ll*a*a%MOD;
    }
    return r;
}
int main(){
    n=qread(),F[0]=1; up(1,2*n,i){
        char c=rdc(); s+=(c=='('?1:-1),F[i]=1ll*F[i-1]*i%MOD; if(s==0) ++w;
    }
    printf("%lld\n",2ll*pwr(F[2*n],MOD-2)*F[n]%MOD*F[n]%MOD*pwr(2,w-1)%MOD);
    return 0;
}
/*
()((()))
*/
```

---

## 作者：do_while_true (赞：1)

模拟一下转换的过程，发现是把随机出来的序列分成若干个段，每个段单独统计的 $sum=0$，而这个段有两种形式，一种是合法匹配，一种是不合法匹配然后被一个一个取反。

所以统计出所给的括号序列有 $m$ 个段，每个段两种方式，则一共有 $2^m$ 种可能，除以所有可能生成的括号序列数即为答案。

$\mathcal{Code}$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
#define re register
#define int long long
const int mod = 998244353;
inline int Max(int x, int y) { return x > y ? x : y; }
inline int Min(int x, int y) { return x < y ? x : y; }
inline int Abs(int x) { return x < 0 ? ~x + 1 : x; }
inline int read() {
	int r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') w = 1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		r = (r << 3) + (r << 1) + (ch ^ 48);
		ch = getchar();
	}
	return w ? ~r + 1 : r;
}
int qpow(int x, int y) { int sumq = 1; while(y) sumq = (y&1) ? (sumq * x % mod) : sumq, x = x * x % mod, y >>= 1; return sumq; }
#undef int
int n, m, sum;
ll ans = 1;
signed main() {
	n = read();
	for(int i = 1; i <= (n << 1); ++i) sum += (getchar() == ')' ? -1 : 1), m += sum == 0, ans = ans * (i <= n ? qpow(i, mod-2) : i) % mod;
	printf("%lld\n", qpow(ans, mod-2) * qpow(2, m) % mod);
	return 0;
}
```

---

## 作者：MuYC (赞：0)

#### 前言(废话)

做这道题的时候，感觉就像规律题。

一开始就想着先打个暴力。

然后顺利的先骗到20分，十分钟后通过找规律做出了这个题。

#### 做法：

官方题解里面貌似没讲 $20$ 分做法 。

这里就来提一嘴：

#### 20分做法

通过观察题目中给出的程序，其中有一段随机生成一个括号序列的过程，我们将这个随机生成的序列全部枚举一遍，再用给定的程序跑一遍，求出有多少个跟给定括号串相同的就行了。

这叫什么？以子之矛攻子之盾？(滑稽

#### Code1

```cpp

#include <bits/stdc++.h>
using namespace std;
string s;
#define int long long
const int Mod = 998244353;
int Now[15];
int n,total = 0,aa = 0;

void generate() {
	const int len = n * 2;
	bool arr[len];
	int cntA = 0;
	for(int i = 0 ; i < len ; i ++) if(Now[i] == 1) cntA ++;
	if(cntA != n) return ;
	aa ++;
	for (int i = 0; i < len; ++i) 
	arr[i] = (Now[i] - 1);
	for (int i = 0, j, sum = 0; i < len; ) {
		sum += arr[i]? -1: 1;
		if (sum < 0) {
			for (j = i + 1; j < len; ++j) {
				sum += arr[j]? -1: 1;
				if (sum == 0) break;
			}
			for (int k = i; k <= j; ++k)
				arr[k] ^= 1;
			i = j + 1;
		} else ++i;
	}
	string ret;
	for (int i = 0; i < len; ++i)
		ret += arr[i]? ')': '(';
	if(ret == s) total ++;
	return ;
}

void DFS(int x) {
	for(int i = 1 ; i <= 2 ; i ++) {
		Now[x] = i;
		if(x == n * 2 - 1) generate();
		else DFS(x + 1);
		Now[x] = 0;
	}
	return ;
}

int quickpower(int x,int y){
	int ans = 1 , op = x;
	while(y) {
		if(y & 1ll) ans *= op , ans %= Mod;
		op *= op , op %= Mod;
		y >>= 1ll;
	}
	return ans;
}

signed main() {
	cin >> n;
	cin >> s;
	DFS(0);
	cout << (total * quickpower(aa,Mod - 2)) % Mod;
	return 0;
}
```

50 分做法没写，而且我现在也没想到这个50分是给哪个算法的，所以就不写。

#### 满分做法：

我们通过观察几组数据:

输入1：
```plain
4
()()()()
```

输出1:
```plain
16 70(后面的70是总方案数)
```

输入2：
```plain
4
()(())()
```

输出2:
```plain
8 70
```

输入3：
```plain
4
(())()()
```

输出3
```plain
8 70
```

输入4：
```plain
4
(())(())
```

输出4
```plain
4 70
```

然后我们就会发现一个规律，实际上答案只与最外层匹配成功的括号数有关。

比如

```plain
4
(())()()
```
只有三对是在外面的，所以方案数是 $2^3$ ，另外的例子同样满足这个规律。

所以我们大胆猜想最后的答案就是:

$\frac{2^{cnt}}{C_{2n}^{n}}$

($cnt$ 表示的是最外面匹配成功的括号对数，被包含在其他合法括号对中的括号对不计算入 $cnt$ ， $C_{2n}^{n}$ 就是所有满足条件的括号串 )

所以就直接用栈跑括号匹配，然后每次匹配的时候假设匹配完后栈清空了就 $cnt ++$

事实证明这个规律确实是正确的，于是我们就用 O($n$)的复杂度水过了这一题。

#### Code2


```cpp

#include <bits/stdc++.h>
using namespace std;
string s;
#define int long long
const int Mod = 998244353,MAXN = 5e5 + 50;
int T[MAXN * 2] = {1};
int n,total = 0,top = 0;
int tack[MAXN * 2];
int P[MAXN * 2];

int quickpower(int x,int y) {
	int ans = 1 , op = x;
	while(y) {
		if(y & 1ll) ans *= op , ans %= Mod;
		op *= op , op %= Mod;
		y >>= 1ll;
	}
	return ans;
}

signed main() {
	cin >> n;
	cin >> s;
	for(int i = 1 ; i <= 2 * n ; i ++) T[i] = (T[i - 1] * i) % Mod;
	int All = T[2 * n] * quickpower((T[n] * T[n]) % Mod,Mod - 2) % Mod;
	for(int i = 0 ; i < 2 * n ; i ++) {
		if(s[i] == '(') top ++ , tack[top] = i + 1;
		else {
			if(tack[top] != 0 && s[tack[top] - 1] == '(') {
				top --;
				if(top == 0) {total ++ ; continue ;}//如果到了栈底,total ++
			}
			else top ++ , tack[top] = i + 1;
		}
	}
	int K = quickpower(2,total);
	cout << K * quickpower(All,Mod - 2) % Mod;
	return 0;
}
```

---

## 作者：ZCETHAN (赞：0)

[传送门](https://www.luogu.com.cn/problem/P7263)
# 分析
- $通俗粗糙的理解$
这是我比赛时的思路，由于题目中给出的是一个合法的序列，则一定可以分成若干个子括号序列。
具体地，如$(())()(()())$，可以分成$(())\;()\;(()())$，则对于每一个子序列，可以将它反过来，也可以不反，就构成了不合法的序列(当然，如果都不反也是一种，此时是合法的)，所以只要求出这样的子序列的个数$x$，则通过题目中给出的方式得到给定序列的原序列个数就是$2^x$。
而分母就是$n$个左括号和右括号能组成的序列个数，即$C_{2n}^n$，然后求个逆元乘起来就可以了。

- $严谨缜密的做法$
这个是强大出题人给出的做法，更加严谨和有技巧。
首先把左括号看成$+1$，右括号是$-1$，则最终每个序列都会得到一条与$x$轴有若干个交点的折线，并且最终会落在$x$轴上(左右括号个数相等)，如此，考察题中给出的构造正确序列的方式，不过就是把在$x$轴下方的线翻折回$x$轴的上方了。看图理解。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210110202345523.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3poYW5nY2hpemM=,size_16,color_FFFFFF,t_70)
所以当前得到的若干个与$x$轴交点之间都存在一个向上或下凸起的东西(doge)，而题目中的方法就是将在下方的翻到上面，这时我们可以把任意一个翻下来或者不翻形成一个原序列。所以总数有$2^{x-1}$，$x$为折线与$x$的交点个数。
而总数依然是$C_{2n}^n$。

# Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 1<<30
using namespace std;
const int MOD=998244353;
const int MAXN=1e6+10;
ll ksm(ll a,ll p){
	ll ret=1;
	while(p){
		if(p&1) ret=ret*a%MOD;
		a=a*a%MOD;p>>=1;
	}return ret;
}
ll inv(ll a){return ksm(a,MOD-2)%MOD;}
//逆元
ll div(ll x){
	ll ret=1;
	for(ll i=1;i<=x;i++)
		ret=ret*(x+i)%MOD*inv(i)%MOD;//要用逆元
	return inv(ret);
}
char s[MAXN];
int main()
{
	ll n,ans=1,sum=0;
	scanf("%lld%s",&n,s+1);
	for(ll i=1;i<=2*n;i++){
		sum+=(s[i]==')'?-1:1);
		if(sum==0) ans=(ans<<1)%MOD;
	}
	printf("%lld\n",ans*div(n)%MOD);
}
```
# Ps
注意在算组合数的时候也是要除的，也一定一定一定要用逆元，就因为这个原因，想到了正解的我在赛场上只有$20pts$，~~然后就出去了，总共只打了$90$分钟~~。

---

## 作者：Legitimity (赞：0)

题目本身不难，但是有一点思维含量，要理解给出的生成代码的原理。


------------
首先先考虑可行的方案总数，也就等于 $arr$ 数组的可能性。可以这样考虑：$arr$ 数组共有 $2 \times n$ 个元素，其中 $n$ 个是 $1$，那么易得 $arr$ 数组总共有 $C^{2 \times n}_{n}$ 可能性。

再考虑对于一个合法的括号序列，有多少种可能的 $arr$ 能生成它。

根据给出的代码，不能想到对于这个括号序列的一段子序列，想要生成它有两种可能：
1. $arr$ 数组的某一个子序列本身对应该子序列（如 $arr=\{0,0,1,1\}$，可生成括号串 $S=(())$

2. $arr$ 数组的某一个子序列取反后对应该子序列（如 $arr=\{1,1,0,0\}$，取反后得 $arr=\{0,0,1,1\}$，对应括号串 $S=(())$

对于括号串中的任意一个子序列，第 $1$ 种生成方式一定存在，所以要考虑存在第 $2$ 种生成方式的子序列。

那么什么时候会翻转 $arr$ 的子段呢？通过给出的代码，就可以发现对于对于下标 $i$ 判断到 $sum<0$ 的情况时（出现多余的右括号），扫描到下标 $j$ 使 $sum=0$，此时对于区间 $[i,j]$ 取反。

因为取反不会改变 $sum$ 的值，只需扫描生成出的括号串，判断 $sum=0$ 的次数 $k$，那么就代表有 $k$ 个独立的子序列有两种生成方式，其它的子序列与 $arr$ 一一对应，所以最后可以生成括号串 $S$ 的可能性为 $2^{k}$ 中。

所有最后的答案为 $\frac{2^k \times n!^2}{(2 \times n)!}$ 的逆元。

代码：
```cpp
#include<bits/stdc++.h>
#include<time.h>
using namespace std;
#define rg register
#define ll long long 
#define inf 0x3f3f3f3f
#define mod 998244353*1LL
inline ll read(){
	rg ll ret=0; char ch=getchar();
    while(!isdigit(ch)){ch=getchar();}
    while(isdigit(ch)){ret=ret*10LL+ch-48;ch=getchar();}
    return ret;
}
ll n,a,tmp,b,now,sum,ans;
char st[500005];
inline ll fac(ll x){
	ll ret=1LL;
	for(rg ll i=1LL;i<=x;++i) ret*=i,ret%=mod;
	return ret;
}//阶乘 
inline ll ksm(ll base,ll p){
    ll ret=1;
    while(p>0){
        if(p&1)
            ret*=base,ret%=mod;
        base*=base; base%=mod; p>>=1LL;
    }
    return ret;
}//快速幂 
int main(){
	n=read(); scanf("%s",st);
	for(rg ll i=0;i<(n<<1LL);++i){
		now+=((st[i]=='(')?1LL:-1LL);
		if(now==0) ++sum; //此时有两种生成方式。 
	}
	tmp=fac(n); b=fac(n<<1LL); a=ksm(2LL,sum)*tmp%mod*tmp%mod; 
	ans=a*ksm(b,mod-2LL)%mod; //求逆元。 
	printf("%lld\n",ans);
	return 0;
} 
```


---

