# Count The Blocks

## 题目描述

You wrote down all integers from $ 0 $ to $ 10^n - 1 $ , padding them with leading zeroes so their lengths are exactly $ n $ . For example, if $ n = 3 $ then you wrote out 000, 001, ..., 998, 999.

A block in an integer $ x $ is a consecutive segment of equal digits that cannot be extended to the left or to the right.

For example, in the integer $ 00027734000 $ there are three blocks of length $ 1 $ , one block of length $ 2 $ and two blocks of length $ 3 $ .

For all integers $ i $ from $ 1 $ to $ n $ count the number of blocks of length $ i $ among the written down integers.

Since these integers may be too large, print them modulo $ 998244353 $ .

## 样例 #1

### 输入

```
1```

### 输出

```
10```

## 样例 #2

### 输入

```
2```

### 输出

```
180 10```

# 题解

## 作者：Alex_Wei (赞：21)

> [题面传送门](https://www.luogu.com.cn/problem/CF1327E) & [CF传送门](http://codeforces.ml/problemset/problem/1327/E)。

> 题意简述：在所有的 $n$ 位十进制整数中，求对于每个 $i\leq n$，**极大的**连续的 $i$ 位数字出现了多少次。

---

对于每个 $i$ 分别讨论。

- 如果 $i=n$，答案显然为 $10$。

- 如果 $i<n$，那么放在两边（含有第 $1/n$ 位）的位置共有 $2$ 个，放在中间的位置共有 $n-i-1$ 个。
  
  因为与这连续的 $i$ 个数字相邻的不能是相同的数字，所以根据乘法原理，两边对答案的贡献为 $10\times 9\times 10^{n-i-1}$（自己可能的 $10$ 种乘与他相邻的那一位的 $9$ 种，其余位任意），即 $10^{n-i}\times 9$。
  
  同理，中间位置的贡献为 $10\times 9^2\times 10^{\max(0,n-i-2)}$（当中间位置不存在，即 $i=n-1$ 时，$n-i-2$ 为负数，所以要取 $\max$），即 $10^{n-i-1}\times 9^2$。
  
  所以答案为 $2\times 10^{n-i}\times 9+(n-i-1)\times 10^{n-i-1}\times9^2$，即 $18\times 10^{n-i}+(n-i-1)\times 10^{n-i-1}\times 81$。

预处理 $10$ 的幂次方，代码实现就很简单了。

```cpp
#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
 
const ll mod=998244353;
const int N=2e5+5;
 
ll n,pw[N];

int main(){
	cin>>n,pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*10%mod;
	for(int i=1;i<=n;i++){
		if(i==n)puts("10");
		else cout<<(pw[n-i]*18+(n-i-1)*pw[n-i-1]*81)%mod<<" ";
	}
	return 0;
}
```

---

Upd on 2020.4.15：把代码改整洁了。

---

## 作者：gyh20 (赞：5)

计算贡献。

假设知道有一个长度为 $len$ 的串，分类讨论。

如果 $len=n$ 只有 $10$ 种情况（全部为$0,1\dots9$）

如果这个串的左端点为 $1$ 或右端点为 $n$：
则有 $10\times 9\times 10^{n-len-1}$种方法

（$10$（自己可以随便选）$\times$ $9$ （最近的一位不能相同） $\times 10^{n-len-1}$（其它位随便选）

否则: $10\times 9^2\times 10^{n-len-2}$种方法

（$10$（自己可以随便选）$\times$ $9^2$ （最近的两位不能相同） $\times 10^{n-len-2}$（其它位随便选） 

可以发现，我们可以枚举 $len$ 求答案。

对于第一种情况，特判 $n=len$。

第二种情况在每一种 $len$ 只会出现两次，第三种情况有 $n-len-1$ 次，乘上对应贡献即可，

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define int long long
#define M 998244353
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,k,x,jc[400002],ans;
signed main(){
	n=read();jc[0]=1;for(re int i=1;i<=n*2;++i)jc[i]=jc[i-1]*10%M;
	for(re int i=1;i<=n;++i){
		ans=0;
		if(i==n)ans+=10;
		else if(i==n-1)ans+=180;
		else{
		ans+=(n-i-1)*jc[n-i-2]%M*810ll%M;
		ans+=jc[n-i-1]*180ll%M;
		}
		printf("%lld ",ans%M);
	}
}
```


---

## 作者：Karry5307 (赞：3)

### 题意

写的很明确。

$\texttt{Data Range:}1\leq n\leq 10^5$

### 题解

找规律 txdy！

首先我们设 $s_{i,j}$ 为位数为 $i$，连续段长度为 $j$ 的数量，容易发现这么个结论：

$$s_{i+1,j+1}=s_{i,j}$$

因为你只要把长度为 $j$ 的一段的后面加入一个一样的数就能构成一个长度问 $j+1$ 的 $i+1$ 位数。

然后我们来考虑 $s_{n,1}$。经过一通找规律之后我们可以发现这样一个线性递推式子：

$$s_{n,1}=20s_{n-1,1}-100s_{n-2,1}(n\geq 4)$$

关于这个序列的可线性递推性不难自证，于是直接暴力递推一下就好了。

### 代码

```cpp
// This code is written by Karry5307
#include<bits/stdc++.h>
// Definition
#define For(i,x,y) for(register int i=(x);i<(y);i++)
#define Forr(i,x,y) for(register int i=(x);i<=(y);i++)
#define Rep(i,x,y) for(register int i=(x);i>(y);i--)
#define Repp(i,x,y) for(register int i=(x);i>=(y);i--)
#define ve vector
#define iter iterator
#define pb emplace_back
#define popb pop_back
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x.size())
#define F first
#define S second
using namespace std;
// Typedefs
typedef int ll;
typedef long long int li;
typedef unsigned int ul;
typedef unsigned long long int ull;
typedef double db;
typedef long double ldb;
typedef pair<ll,ll> pii;
typedef pair<li,li> pll;
const ll MAXN=2e5+51,MOD=998244353,inf=0x3f3f3f3f;
// Structures and variables
ll n;
ll x[MAXN]; 
// Fast IO
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-') ch=getchar();
    if(ch=='-') neg=-1,ch=getchar();
    while(isdigit(ch)) num=(num<<3)+(num<<1)+(ch-'0'),ch=getchar();
    return neg==1?num:-num;
} 
inline li readu()
{
    register li num=0;
    register char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) num=(num<<3)+(num<<1)+(ch-'0'),ch=getchar();
    return num;
} 
template<class T>
inline void writep(T x)
{
	if(x<0){return (void)putchar('-'),writep(-x);}
	if(x<10){return (void)putchar(x|48);}
	writep(x/10),putchar((x%10)|48);
}
template<class T>
inline void write(T x,char ch=' '){writep(x),putchar(ch);}
template<class T>
inline void writeln(T x){writep(x),putchar('\n');}
// chkmin and chkmax
template<class T>
inline void chkmax(T &x,const T &y){x=x>y?x:y;}
template<class T>
inline void chkmin(T &x,const T &y){x=x<y?x:y;}
// Functions
template<class T,class Compare>
inline void sort(ve<T>&v,Compare cmp=less<T>()){sort(all(v),cmp);}
template<class T>
inline void reverse(ve<T>&v){reverse(all(v));}
template<class T>
inline void clear(T *arr){memset(arr,0,sizeof(arr));}
template<class T>
inline void setInf(T *arr){memset(arr,0x3f,sizeof(arr));}
// Math funcs
inline ll qpow(ll base,ll exponent)
{
	li res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=(li)res*base%MOD;
		}
		base=(li)base*base%MOD,exponent>>=1;
	}
	return res;
}
inline ll gcd(ll x,ll y)
{
	return !y?x:gcd(y,x%y);
}
inline li lcm(ll x,ll y)
{
	return x/gcd(x,y)*y;
}
// Functions
int main()
{
	x[1]=10,x[2]=180,x[3]=2610;
	for(register int i=4;i<=200000;i++)
	{
		x[i]=((li)20*x[i-1]%MOD-(li)100*x[i-2]%MOD+MOD)%MOD;
	}
	n=read();
	for(register int i=n;i;i--)
	{
		printf("%d ",x[i]);
	}
}
``

---

## 作者：skydogli (赞：2)

此题也可以用简单的容斥来解决。

首先我们考虑如果定义改为出现了多少个长度为i的（不要求不可拓展）怎么做，那么方案数显然就是$(n-i+1)\times 10^{n-i}\times 10$，分别表示起始位置、其他位置的方案数、我这i个位置选择的数的方案数（0~9）。

然后考虑怎么去掉那些可以拓展的贡献。我们发现，如果长度为$j(j>i)$的数量为$f_j$，那么$f_i$就要减去$(j-i+1)\times f_j$即对于每个长为j的，都会对$f_i$产生$(j-i+1)$的贡献，所以我们现在想求的就是
$$\sum_{j=i+1}^n (j-i+1)\times f_j$$
发现i减小1时，这个答案增加$\sum\limits_{j=i+1}^n f_j$，所以我们记录这个值，每次修改即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MN 200005
#define LL long long
#define mp make_pair
#define fir first
#define sec second
#define pii pair<int,int>
inline void chkmax(int &a,int b){if(a<b)a=b;}
inline void chkmin(int &a,int b){if(a>b)a=b;}
inline int read(){
	   int a=0,fh=1;char c=getchar();
	   while(c>'9'||c<'0'){if(c=='-')fh=-1;c=getchar();}
	   while('0'<=c&&c<='9'){
		   a=a*10+c-48;
		   c=getchar();
	   }
	   return a*fh;
}
#define int long long
vector<int>edg[MN];
int dis(int a,int b,int x,int y){
	return abs(a-x)+abs(b-y);
}
int n,m,k,x[MN],y[MN],u[MN],v[MN];
#define Mod 998244353
LL ans[MN],pw[MN];
signed main(){
	n=read();
	int tmp=0,del=0;
	pw[0]=1;for(int i=1;i<=n;++i)pw[i]=pw[i-1]*10%Mod;
	for(int i=n;i;--i){
		ans[i]+=(n-i+1)*pw[n-i+1]%Mod;
		ans[i]=(ans[i]-del+Mod)%Mod;
		(tmp+=ans[i])%=Mod;
		(del+=tmp+ans[i])%=Mod;//因为一开始就要减两次，所以多减一个ans[i]
	}
	for(int i=1;i<=n;++i)printf("%lld ",ans[i]);
	return 0;
}
 
 ```

---

## 作者：WYXkk (赞：2)

找规律好题。

样例规律非常不明显，所以我们写个 $O(n10^n)$ 的爆搜：

```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
	T f=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
	x*=f;
	return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

ll s[10];int n;
int dig[10];
void dfs(int x)
{
	if(x==n+1)
	{
		int l=1,r=1;
		while(l<=n)
		{
			r=l;
			while(dig[r]==dig[l]) ++r;
			++s[r-l];l=r;
		}
		return;
	}
	F(i,1,10) {dig[x]=i;dfs(x+1);}
}
int main()
{
	for(n=1;n<=8;++n)
	{
		Set(s);
		dfs(1);
        cout<<n<<":";
		F(i,1,n) cout<<s[i]<<ends;
		cout<<endl;
	}
	return 0;
}
```

运行结果：

```plain
1:10 
2:180 10 
3:2610 180 10 
4:34200 2610 180 10 
5:423000 34200 2610 180 10 
6:5040000 423000 34200 2610 180 10 
7:58500000 5040000 423000 34200 2610 180 10 
8:666000000 58500000 5040000 423000 34200 2610 180 10 
```

发现 $n$ 的答案就是 $n-1$ 的答案在前面再加一个数。

假设我们把所有序列都反过来，那么就得到了一个序列 $\{a_n\}$。

由于 $a_n,a_{n-1},a_{n-2},\cdots,a_1$ 是 $n$ 的答案，那么我们可以得到：

$$1\times a_n+2\times a_{n-1}+\cdots+n\times a_1=n10^n$$

这是对于一共有多少个数位的算两次：左边是所有块长与块个数的乘积；右边是对于每个数算一遍。

发现这个就是二阶前缀和的形式，于是

$$a_n=n10^n-2(n-1)10^{n-1}+(n-2)10^{n-2}=10^{n-2}(81n+18)\;(n\ge2)$$

……没了

$\texttt{code:}$

```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
	T f=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
	x*=f;
	return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

const ll p=998244353;
ll qp(ll x){if(!x) return 1;ll w=qp(x>>1);w=w*w%p;return x&1?w*10%p:w;}
int main()
{
	ll n=rd();
	UF(i,n,2) printf("%lld ",(81*i+18)*qp(i-2)%p);
	cout<<10<<endl;
	return 0;
}
```

按照惯例，说句闲话：

**找 规 律 t x d y！！！**

---

## 作者：ix35 (赞：2)

对于每个 $i$ 讨论一下。

连续 $i$ 个数可能出现的位置可以分为：边界和中间。

边界即以 $1$ 开头或者以 $n$ 结尾的段。

以 $1$ 开头为例，那么 $1\ldots i$ 这些位置上的数都是一样的，有 $10$ 种方案，而 $i+1$ 位置上的数不能与 $i$ 相同（题目中说的区间有极长性），有 $9$ 种方案，$i+2\ldots n$ 位置上的数都随意填，所以有 $10\times 9\times 10^{n-i-1}$。

以 $n$ 结尾的方案是一模一样的。

再考虑中间的段，即不以 $1$ 和 $n$ 开头或结尾的连续 $i$ 个位置，不难发现有 $n-i-1$ 种位置。

对于每种位置，连续的这一段都是 $10$ 种方案，而这一段两侧的两个位置都不能与这一段相同，所以分别有 $9$ 种方案，别的位置任意，所以方案数为 $810\times 10^{n-i-2}$。

总的方案数也就是：

$$180\times 10^{n-i-1}+(n-i-1)\times 810\times 10^{n-i-2}$$

不放代码了。

---

## 作者：Polaris_Dane (赞：0)

其实比较简单吧

我们分别算每一种的答案

对于连续长度为$x$的一块，他有$10$种取值

而且他有$n-x+1$种放置方法

其中有两种贴边，方法为$2*9*10^{n-i}$

因为长度限制为$x$，故他们旁边的块颜色不能相同

剩下的随便放

还有剩下的$n-x-1$种情况放在中间

方法数为$10*(n-i-1)*9*9*10^{n-i-2}$

特判一下$n-1$和$n$

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<set>
#include<queue>
#define M 1001000
#define inf 0x3f3f3f3f
#define LL long long
#define int long long
const int mod=998244353;
using namespace std;
inline int read(){
	int f=1,x=0;char s=getchar();
	while (!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while (isdigit(s)){x=(x<<1)+(x<<3)+(s^48),s=getchar();}
	return x*f;
}
int n;
inline int qpow(int a,int b){
	int ans=1;while (b>0){
		if (b&1) ans=(ans*a)%mod;
		a=(a*a)%mod,b>>=1;
	}
	return ans;
}
signed main(void){
	n=read();
	for (int i=1;i<=n;i++){
		if (i<=n-2) printf("%lld ",(2*9%mod*qpow(10,n-i)%mod+10*(n-i-1)*9%mod*9%mod*qpow(10,n-i-2)%mod)%mod);
		if (i==n-1) printf("%lld ",180);
		if (i==n) printf("%lld ",10);
	}
	return 0;
}

```


---

## 作者：ASC_8384 (赞：0)

通过暴力，显然前几项为 `1, 18, 261, 3420, 42300, 504000, 5850000, 66600000` 的 10 倍，通过查询 [OEIS](https://oeis.org/search?q=10%2C180%2C+2610%2C+34200%2C&sort=&language=english&go=Search) 可知数列通项公式$a_n = 9*(10^{n-11}) - a_n-11 + sum_{i=10}^{n-1} a_i) (n >= 11)$

~~可以用杜教板子（BM）线性递推式~~

---

