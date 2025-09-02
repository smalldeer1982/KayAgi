# Enormous XOR

## 题目描述

You are given two integers $ l $ and $ r $ in binary representation. Let $ g(x, y) $ be equal to the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of all integers from $ x $ to $ y $ inclusive (that is $ x \oplus (x+1) \oplus \dots \oplus (y-1) \oplus y $ ). Let's define $ f(l, r) $ as the maximum of all values of $ g(x, y) $ satisfying $ l \le x \le y \le r $ .

Output $ f(l, r) $ .

## 说明/提示

In sample test case $ l=19 $ , $ r=122 $ . $ f(x,y) $ is maximal and is equal to $ 127 $ , with $ x=27 $ , $ y=100 $ , for example.

## 样例 #1

### 输入

```
7
0010011
1111010```

### 输出

```
1111111```

## 样例 #2

### 输入

```
4
1010
1101```

### 输出

```
1101```

# 题解

## 作者：Alex_Wei (赞：8)

> [题目传送门](https://www.luogu.com.cn/problem/CF1493E)。

> 题意简述：给出长度为 $n$ 的二进制数 $l,r$，求 $\max_{l\leq x\leq y\leq r}\oplus_{i=x}^yi$。

> [在我的 cnblogs 中查看](https://www.cnblogs.com/alex-wei/p/CF1493E.html)。

---

首先，如果 $l,r$ 的最高位不同，那么答案显然为 $2^n-1$。当 $x=2^{n-1}-1,y=2^{n-1}$ 时可以取到。

如果 $l,r$ 的最高位相同，那么我们肯定是选奇数个数，即 $y\equiv x\pmod 2$。如果选偶数个数则最高位为 $0$，显然不优于 $x=y=r$。

注意到**偶数** $i\oplus(i+1)=1$，那么这样选择的方案就可能是 $x\ (x\equiv 1\pmod 2 \land y-x\equiv 0\pmod 4)$ 或 $x\oplus 1\ (x\equiv 1\pmod 2 \land y-x\equiv 2\pmod 4)$ 或 $y\ (x\equiv 0\pmod 2 \land y-x\equiv 0\pmod 4)$ 或 $y\oplus 1\ (x\equiv 0\pmod 2 \land y-x\equiv 2\pmod 4)$。那么显然当 $y=r$ 时最优，且当 $r\equiv 1\pmod 2$ 时答案为 $r$；当 $r\equiv 0\pmod 2\land l\leq r-2$ 时，答案为 $r+1\ (r\oplus 1)$，当 $r\equiv 0\pmod 2\land l>r-2$ 时答案为 $r$。

```cpp
/*
	Powered by C++11.
	Author : Alex_Wei.
*/

#include <bits/stdc++.h>
using namespace std;

int n;
char l[1000005],r[1000005];
int main(){
	scanf("%d%s%s",&n,l+1,r+1);
	if(l[1]!=r[1])for(int i=0;i<n;i++)cout<<'1';
	else if((r[n]&1)||n==1)cout<<r+1;
	else{
		l[n-1]++;
		for(int i=n-1;i;i--)if(l[i]>'1')l[i]='0',l[i-1]++;
		for(int i=0;i<=n+1;i++)if(l[i]!=r[i]||i>n)r[n]=(l[i]<r[i]||i>n)+'0',cout<<r+1,exit(0);
	}
	return 0;
}
```

---

## 作者：7KByte (赞：5)

我们发现 $N$ 非常大，所以直接枚举或 $\texttt{DP}$ 都是不现实的。

所以我们可以找规律。

如果$l,r$的位数不同，肉眼可见答案为长度为 $n$ 的全 $1$ 串。因为 $2^{n-1}\ \rm{xor}\ (2^{n-1}-1)$就是答案。

其他的规律就不是很明显的了，我们可以先写一个程序打表。

```cpp
int s[N];
int f(int l,int r){
	int ans=0;
	rep(x,l,r)rep(y,x,r)ans=max(ans,s[y]^s[x-1]);
	return ans;
}
int main(){
	rep(i,1,N-5)s[i]=s[i-1]^i;
	int r;scanf("%d",&r);
	rep(l,1,r){
		printf("%d   %d\n",l,f(l,r));
	}
	return 0;
}
```

当 $r$ 为全 $1$ 串时，答案就是 $r$ 。

否则答案只有两种情况

- 不论 $l$ 取值如何，答案都为 $r$ 。
- 除了 $l=r$ 或 $l+1=r$ 答案为 $r$ ，其余答案都为 $r+1$ 。

当 $l=r$ 或 $l+1=r$ 时不难证明答案为 $r$，因为就几个可能。

否则我们猜测答案为 $r$ 或 $r+1$，输入几组数据发现只与 $r$ 的取值有关。

我们打印一下 $f(r-2,r)$ 的表，如下：

```cpp
r   f(r-2,r)
3    3
4    7
5    7
6    7
7    7
8    15
9    15
10   11
11   11
12   13
13   13
14   15
15   15
16   31
17   31
18   19
19   19
20   21
21   21
```

除去 $r-2$ 与 $r$ 位数不同的，其他的是两两分组。具体一点，如果 $r$ 的最低位为 $0$ 则答案为 $r+1$ ，否则为 $r$ 。

再验证一下$f(r-k,r)$，发现也是如此。

如果不担心罚时莽一发就过了/kk，这一步具体证明有点复杂，先咕着。

时间复杂度 $\rm O(N)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 1000005
using namespace std;
char s[N],t[N];int n;
int main(){
	scanf("%d",&n);
	scanf("%s%s",s+1,t+1);
	if(s[1]!=t[1]){rep(i,1,n)putchar('1');putchar('\n');return 0;}
	bool flag=true;
	rep(i,1,n)flag&=s[i]==t[i];
	if(flag){puts(t+1);return 0;}
	s[n]++;pre(i,n,1)if(s[i]-'0'>1)s[i]-=2,s[i-1]++;
	flag=true;
	rep(i,1,n)flag&=s[i]==t[i];
	if(flag){puts(t+1);return 0;}
	if(t[n]=='1'){puts(t+1);return 0;}
	t[n]++;puts(t+1);
	return 0;
} 
```

---

## 作者：ifffer_2137 (赞：2)

难得秒切的诈骗题。
### 题意
求 $[l,r]$ 内的最大子段 xor。
### 分析
容易注意到 xor 的一个关键性质，$2x\oplus2x+1=1$。

所以其实中间一大段的贡献只可能是 $0$ 或 $1$，我们声称这是好处理的，接下来先考虑两个端点，相当于选出 $l\le2x+1<2y\le r$ 使得 $2x+1\oplus2y$ 最大。

考虑最高位，如果 $l,r$ 最高位相等，则两个数的 xor 最高位为 $0$，这就比较菜，直接只选 $r$ 就严格更优了，考虑从前面再选两个调整最低位，$r-l\le2$ 就能让最低位为 $1$ 了。

如果最高位不相等，手玩容易构造出 $011\ldots11 \oplus 100\ldots00$ 的情况，显然满足条件且取到答案上界。
### 代码
~~由于比较唐诗所以用了 hash 瞎判了一下 $r-l\le2$。~~
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
#define mkpr make_pair
#define x first
#define y second
#define popcnt __builtin_popcountll
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=0;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
	return w?x:-x;
}
template<class T1,class T2>inline bool Cmn(T1 &x,T2 y){if(y<x)return x=y,1;return 0;}
template<class T1,class T2>inline bool Cmx(T1 &x,T2 y){if(y>x)return x=y,1;return 0;}
template<class T>inline void Dbg(T *a,int l,int r){for(int i=l;i<=r;i++)cout<<a[i]<<' ';cout<<'\n';}
mt19937 rnd(time(NULL));
constexpr int inf=0x3f3f3f3f;
constexpr int maxn=2e5+5;
constexpr int maxm=5e3+5;
constexpr int mod=1e9+1011;
constexpr int base=2137;
constexpr int V=1e9;
constexpr int H=18;
constexpr int W=64;
constexpr int Z=26;
constexpr double eps=1e-9;
inline int Redu(int x){return x-(x>=mod)*mod;}
inline void Add(int &x,int y){x=x+y-(x+y>=mod)*mod;}
inline void _Add(int &x,ll y){x=(x+y)%mod;}
inline void Del(int &x,int y){x=x-y+(x-y<0)*mod;}
inline void _Del(int &x,ll y){x=(x-y)%mod;x+=(x<0)*mod;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int Pow(int a,int x){int s=1;for(;x;x>>=1,a=1ll*a*a%mod)if(x&1)s=1ll*s*a%mod;return s;}
bool Mem1;
int n;
string a,b;
bool check(){
	int va=0,vb=0;
	for(int i=0;i<n;i++) va=(va<<1|(a[i]-'0'))%mod;
	for(int i=0;i<n;i++) vb=(vb<<1|(b[i]-'0'))%mod;
	if((vb-va+mod)%mod<=2) return 0;
	return 1;
}
void Init(){}
void Clear(){}
void Mymain(){
	Clear();
	n=read();
	cin>>a>>b;
	if(a[0]==b[0]){
		if(b[0]=='0') return cout<<"0\n",void();
		for(int i=0;i<n-1;i++) cout<<b[i];
		if(b[n-1]=='1'||check()) cout<<"1\n";
		else cout<<"0\n";
		return;
	}
	for(int i=1;i<=n;i++) cout<<'1';
	cout<<'\n';
}
bool Mem2;
signed main(){
	#ifdef LOCAL
	assert(freopen("data.in","r",stdin));
	assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(0),cout.tie(0);
	Init();int _=1;
	while(_--) Mymain();
	cerr<<"Time: "<<1000.0*clock()/CLOCKS_PER_SEC<<" ms\n";
	cerr<<"Memory: "<<(&Mem1-&Mem2)/1024.0/1024.0<<" MB\n";
	return 0;
}
```

---

## 作者：xfrvq (赞：2)

*2600，但是虚高。

注意到异或的消去性。$2k\oplus(2k+1)=1$。进一步地，分讨答案区间 $x,y$ 奇偶性。

+ $x$ 偶 $y$ 奇，通过观察，结果只能 $0$ 或 $1$。
+ $x$ 奇 $y$ 奇，由于 $x+1$ 异或到 $y$ 是 $0$ 或 $1$，此时答案是 $x$ 或者 $x\oplus 1$。奇数异或 $1$ 会变小，所以这部分答案是可取的最大奇数。
+ $x$ 偶 $y$ 偶，此时答案是 $y$ 或 $y\oplus 1$。偶数异或 $1$ 会变大，所以考虑看可取的最大偶数 $x$，如果 $x-2,x-1\ge l$ 能取，那么答案就是 $x+1$，否则答案是 $x$。
+ $x$ 奇 $y$ 偶，此时答案是 $x\oplus y$ 再异或 $0$ 或者 $1$。不过可以观察 $l,r$ 的 $2^{n-1}$ 的二进制位，若不同，则答案取得到 $2^n-1$（$x=2^{n-1}-1,y=2^{n-1}$），若相同，那么 $x,y$ 一定都有 $2^{n-1}$ 的位导致消掉，答案劣于上面的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n,c[N];
char s[N],t[N];

int main(){
	scanf("%d%s%s",&n,s + 1,t + 1);
	for(int i = 1;i <= n;++i) c[i] = c[i - 1] || (s[i] < t[i]);
	if(c[1]){
		for(int i = 1;i <= n;++i) putchar('1');
		return 0;
	}
	if(t[n] == '1' || !c[n]) return puts(t + 1),0;
	int p = n;
	for(;t[p] == '0' && s[p] == '1';--p);
	for(int i = 1;i <= n;++i) putchar(i < n ? t[i] : ((s[p] == '0' && t[p] == '1') ? '0' : '1');
	return 0;
}
```

---

## 作者：lsj2009 (赞：2)

### Solution

诈骗题。

首先发现如果 $l,r$ 的最高位不同，则答案必然为 $2^n-1$，因为答案不可能再大，且取 $x=2^{n-1}-1,y=2^{n-1}$ 可以取到。

则接下来考虑 $l,r$ 最高位相同的情况下。

考虑一个结论：当 $x\equiv 0\pmod{2}$ 时，$x\oplus(x+1)=1$。

那么我们考虑形如 $(x\oplus(x+1))\oplus((x+2)\oplus(x+3))\cdots \oplus((x+2k)\oplus(x+2k+1))$ 这种结构可以相消成 $0$。

进一步的，答案只有可能是三种：

1. $x$。当 $x\equiv 1\pmod{2}$ 且 $y-x\equiv 0\pmod{4}$ 时。
2. $x\oplus 1$。当 $x\equiv 1\pmod{2}$ 且 $y-x\equiv 2\pmod{4}$ 时。
3. $y$。当 $x\equiv 0\pmod{2}$ 且 $y-x\equiv 0\pmod{4}$ 时。
4. $y\oplus 1$。当 $x\equiv 0\pmod{2}$ 且 $y-x\equiv 2\pmod{4}$ 时。

显然当 $y=r$ 时答案最大，而且我们希望尽可能取后两种，且 $r\equiv 1\pmod{2}$ 时，$r$ 无法变大，取 $x=y$ 即为最佳。

当 $r\equiv 0\pmod{2}$ 时，考虑什么时候答案可以取 $r+1$；如果取不到，我们令 $x=y$ 也可以得到 $r$。

容易发现的是，需要满足 $y-x\equiv 2\pmod{4}$，令 $x$ 尽可能大，取到 $y-2=r-2$，判断一下 $l+2$ 是否不大于 $r$ 即可。

复杂度 $\Theta(n)$。

### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=1e6+5;
char l[N],r[N];
signed main() {
    int n;
    scanf("%d",&n);
    scanf("%s%s",l+1,r+1);
    if(l[1]!=r[1]) {
        rep(i,1,n)
            putchar('1');
        return 0;
    }
    if(r[n]&1)
        return 0&printf("%s\n",r+1);
    ++l[n-1];
    per(i,n-1,0) {
        if(l[i]>49)
            l[i]-=2,++l[i-1];
    }
    bool flag=true;
    rep(i,0,n) {
        if(l[i]!=r[i]) {
            flag=l[i]<r[i];
            break;
        }
    }
    r[n]+=flag;
    printf("%s\n",r+1);
    return 0;
}
```

---

## 作者：wsyhb (赞：1)

## 前言

提供一种基本无脑的**分类讨论**做法。

## 题解

首先一个显然的结论：当 $x$ 为偶数时，$x \oplus (x+1)=1$。（$\oplus$ 表示按位异或）

所以**一个区间中间一段的异或和可以转化为若干个 $1$ 异或起来**。

对区间 $[x,y]$ 的端点 $x,y$ 的奇偶性进行讨论（$l \le x \le y \le r$）：

1. $x$ 奇 $y$ 偶

	- $g(x,y)=x \oplus y \oplus [(y-x-1) \bmod 4=2]$，其中 $[(y-x-1) \bmod 4=2]$ 是中间部分转化成的 $1$ 的个数的奇偶性。
    
	- 从高到低考虑 $x,y$ 的每一位：
		- 对于 $l$ 和 $r$ 完全相同的那一部分二进制位，$x,y$ 只能照搬。
		- 对于 $l$ 和 $r$ 从左到右不相同的第一个二进制位，显然 $l,r$ 这一位分别为 $0,1$，$x,y$ 也只能分别为 $0,1$。
		- 对于剩下的，不包括最右侧两个的二进制位，$x,y$ 分别取 $1,0$ 显然合法，且是最优的（这样 $x,y$ 后面的位可以尽可能不受到 $l,r$ 的限制）。
		- 对于最低位，$x,y$ 分别为 $1,0$。（~~这不是废话吗~~）
        
		- 对于从低到高第二个二进制位，枚举 $x,y$ 的取值并验证合法性，若合法则用于更新答案。（不想再讨论了所以暴力枚举！）
        
	- 由于要枚举从低到高第二个二进制位，所以建议将 $n=1$ 直接特判掉。

1. $x$ 偶 $y$ 奇

	- $g(x,y)=[(y-x+1) \bmod 4=2]$。

	- 由于答案初始值为 $0$，所以只需考虑 $g(x,y)=1$ 的情况，即只需考虑 $x=y-2$。

1. $x$ 奇 $y$ 奇

	- $g(x,y)=x \oplus [(y-x) \bmod 4=2]$。

	- 显然 $x=y$ 时最优，即 $g(y,y)=y$。

1. $x$ 偶 $y$ 偶

	- $g(x,y)=y \oplus [(y-x) \bmod 4=2]$。

	- 显然 $x=y-2$ 时最优，即 $g(y-2,y)=y+1$。

把这些写到代码里，就做完了~

时间复杂度 $O(n)$。

## 代码

为了方便比较二进制大小，以及进行异或，本代码使用结构体存储二进制数，并重载了运算符。

~~写完才发现不用结构体或许实现更简单。~~

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n;
const int max_n=1e6+5;
struct Binary
{
	int v[max_n];
	inline Binary(int x=0)
	{
		for(int i=n-1;i>=0;--i)
			v[i]=0;
		int now=0;
		while(x)
		{
			v[now++]=x&1;
			x>>=1;
		}
		assert(now<=n);
	}
	inline Binary(const char *s)
	{
		for(int i=n-1;i>=0;--i)
			v[i]=s[n-1-i]^'0';
	}
	inline void print()
	{
		for(int i=n-1;i>=0;--i)
			putchar(v[i]^'0');
		putchar('\n');
	}
	inline Binary plus_1()
	{
		static Binary res;
		res=*this;
		for(int i=0;i<=n-1;++i)
		{
			if(!res.v[i])
			{
				for(int j=i;j>=0;--j)
					res.v[j]^=1;
				return res;
			}
		}
		assert(false);
		return Binary();
	}
}l,r,x,y,ans;
inline bool operator < (const Binary &a,const Binary &b)
{
	for(int i=n-1;i>=0;--i)
	{
		if(a.v[i]!=b.v[i])
			return a.v[i]<b.v[i];
	}
	return false;
}
inline bool operator <= (const Binary &a,const Binary &b)
{
	for(int i=n-1;i>=0;--i)
	{
		if(a.v[i]!=b.v[i])
			return a.v[i]<b.v[i];
	}
	return true;
}
inline bool operator != (const Binary &a,const Binary &b)
{
	for(int i=n-1;i>=0;--i)
	{
		if(a.v[i]!=b.v[i])
			return true;
	}
	return false;
}
inline Binary operator ^ (const Binary &a,const Binary &b)
{
	static Binary res;
	for(int i=n-1;i>=0;--i)
		res.v[i]=a.v[i]^b.v[i];
	return res;
}
char sl[max_n],sr[max_n];
int main()
{
	scanf("%d%s%s",&n,sl,sr);
	if(n==1)
	{
		printf("%s\n",sr);
		return 0;
	}
	l=Binary(sl),r=Binary(sr);
	bool flag_same=true;
	for(int i=n-1;i>=2;--i)
	{
		if(flag_same)
		{
			if(l.v[i]==r.v[i])
				x.v[i]=y.v[i]=l.v[i];
			else
			{
				assert(l.v[i]==0&&r.v[i]==1);
				x.v[i]=0,y.v[i]=1;
				flag_same=false;
			}
		}
		else
			x.v[i]=1,y.v[i]=0;
	}
	x.v[0]=1,y.v[0]=0;
	for(int p=0;p<=1;++p)
		for(int q=0;q<=1;++q)
		{
			x.v[1]=p,y.v[1]=q;
			if(l<=x&&x<=y&&y<=r)
				ans=max(ans,x^y^Binary(p==q));
		}
	if(l!=r&&(!l.v[0]||l.plus_1()!=r))
		ans=max(ans,Binary(1));
	if(!r.v[0]&&l!=r&&l.plus_1()!=r)
		ans=max(ans,r.plus_1());
	else
		ans=max(ans,r);
	ans.print();
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

当 $S$ 和 $T$ 第一位不同的时候，显然可以取 $2^{n-1}-1$ 和 $2^{n-1}$，得到最大值 $2^n-1$。

当 $S$ 和 $T$ 第一位相同的时候，显然我们要选奇数个数异或起来，有两种情况：奇偶奇偶奇、偶奇偶奇偶。

偶数和它下一个奇数异或起来是 $1$，因此最终结果可能是左端点、左端点异或 $1$、右端点、右端点异或 $1$。

所以 $r$ 是奇数的时候输出 $r$ 即可。

如果 $r$ 是偶数，我们想输出 $r+1$，至少要满足 $r-l+1 \ge 3$。这时候构造 $(r-2) \oplus (r-1) \oplus r$ 即可。否则输出 $r$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
int n;
string S,T;
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>S>>T;
	if(S[0]=='0'&&T[0]=='1') {
		ffor(i,1,n) cout<<1;
		return 0;	
	}
	if(S==T||T[n-1]=='1') return cout<<T,0;
	roff(i,n-1,0) {
		if(S[i]=='1') S[i]='0';
		else {S[i]='1';break ;}	
	}
	if(S==T) return cout<<T,0;
	ffor(i,0,n-2) cout<<T[i];
	cout<<1;
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

特判一下 $t=0$。

对于 $s$ 第一位为 $0$ 的情况，显然有理论最大值 $n$ 个 $1$。同时，取 $l=0111\dots 1$，$r=1000\dots 0$ 即可取到最大值，特判即可。

否则我们容易发现 $r-l+1$ 为奇数。此时需要特判 $s=t$ 和 $s=t-1$。

设 $s,t$ 不同的第一位为 $j$。若 $t$ 是偶数，$(t-2i+1)\oplus(t-2i)=1$。也就是说只有可能改变最后一位。答案就是 $\max(t,t\oplus1)$。

若 $t$ 为奇数，$(t-2i)\oplus(t-2i-1)=1$，容易发现 $t\geq (t-2i)\oplus 1$，所以答案同样也是 $\max(t,t\oplus1)$。

总复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
string minus1(string s){
	for(int i=s.size()-1;i>=0;i--){
		if(s[i]=='1'){
			s[i]='0';
			break;
		}
		s[i]='1';
	}
	return s;
}
string sxor(string s,string t){
	string ans=s;
	for(int i=0;i<s.size();i++){
		if(s[i]==t[i]) ans[i]='0';
		else ans[i]='1';
	}
	return ans;
}
string max(string s,string t){
	for(int i=0;i<s.size();i++){
		if(s[i]>t[i]) return s;
		if(s[i]<t[i]) return t;
	}
	return s;
}
signed main(){
	int n; cin>>n;
	string s,t; cin>>s>>t;
	if(t=="0"){
		cout<<0;
		return 0;
	}
	if(s[0]=='0'){
		for(int i=1;i<=n;i++) cout<<1;
		return 0;
	}
	if(s==t){
		cout<<t;
		return 0;
	}
	string maxv=t;
	string t1=minus1(t);
	if(t1==s){
		cout<<maxv;
		return 0;
	}
	string t2=minus1(t1);
	maxv=max(maxv,sxor(sxor(t,t1),t2));
	cout<<maxv;
	return 0;
}
```

---

## 作者：Jsxts_ (赞：0)

另一个角度的找规律。

看到区间 xor 先转换成两个前缀异或和。

然后打表找出前缀异或和的规律：

- $x\bmod 4=0$ 时，$pre(x)=x$。
- $x\bmod 4=1$ 时，$pre(x)=1$。
- $x\bmod 4=2$ 时，$pre(x)=x+1$。
- $x\bmod 4=3$ 时，$pre(x)=0$。

那么就是要从 $pre(l-1)\sim pre(r)$ 中找出两个 $pre$ 异或起来最大。

显然区间长度为 $1$ 或 $2$ 时，最优解是 $r$。

那么剩下的区间长度，当 $r$ 为偶数时肯定能取到 $r+1$（此时 $pre(r-3)\oplus pre(r)=r+1$），当 $r$ 为奇数时肯定能取到 $r$（这个显然）。

考虑能否凑出更大的数？
注意，只有 $pre(x)\bmod 4=0,3$ 才能取到，所以后两位一定是一个 $00$，一个 $11$，并且后两位是 $11$ 的不能是 $l-1$（否则其实是当 $x=l-2$ 时 $pre(x)$ 的取值）。

既然是选两个数异或，肯定从高往低位贪心。
但是这题由于已经能取到 $r/r+1$，使得讨论简单了许多：

- 若 $l,r$ 最高位不同，显然可以选一个数是 $0$ 后面全 $1$，一个数是 $1$ 后全 $0$，这样直接输出 $n$ 个 $1$ 即可（这里虽然选择区间是 $[l-1,r]$，但是 $l=2^n$ 的极限情况经讨论是不能满足条件的（因为后两位是 $11$ 的不能是 $l-1$），所以已经略去）。

- 若 $l,r$ 最高位相同，则选出的两个数最高位也会相同，那么此时已经不优于 $r/r+1$ 了（结果最高位为 $0$），可以直接结束贪心。

这样就直接讨论完毕了。

---

## 作者：AFLeartLey0103 (赞：0)

[link](https://www.luogu.com.cn/problem/CF1493E)

本题可以分类讨论进行求解。

首先，若两个数的最高位不相同，那么可以选择 $l = 2^n - 1$，$r = 2^n$ 来得到最大值

否则，由于 $\forall i \in \{j|j=2k,k\in \mathbb{Z}\}, (i \space \text{xor} \space i+1) = 1$，所选的区间的大部分数都可以被消掉，最后只剩下一个或零个 $1$ 和 我们所选的 $x,y$ 。

观察到当 $r$ 的最后一位为 $1$ 时，令 $x = y = r$ 可以获得最大值。

否则，当 $r - l \ge 2$ 时，可以获得最大值，为 $r+1$，具体可以打表理解 ~~( 其实是我不会证 )~~。

那么问题就转化为了：如何判断两个高精度二进制数的差？

其他题解似乎有高精度的做法，但我有一种更简便的做法：哈希。

upd: 显然我代码中的这种哈希做法很好卡，但实测是可以通过的。如果需要防卡的话只需要换一下哈希的种子即可。

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int modd = 998244353;
int main(){
    int len;
    cin >> len;
    string s,t;
    cin >> s >> t;
    //判断最高位是否相同
    if(s[0] != t[0]){for(int i = 0;i<len;++i){cout<<'1';}return 0;}
    //求哈希值
    ll a = 1;
    long long hs = 0,ht = 0;
    for(int i = len-1;~i;--i){
        hs = (hs + (s[i]-'0')*a)%modd;
        ht = (ht + (t[i]-'0')*a)%modd;
        a = a*2%modd;
    }
    //若 r 的最后一位为 0 且 l 与 r 相差大于 1 则答案为 r+1
    if(hs <= ht-2 and t[len-1] == '0')t[len-1] = '1';
    //否则 答案为 r
    cout << t;
    return 0;
}
```

---

