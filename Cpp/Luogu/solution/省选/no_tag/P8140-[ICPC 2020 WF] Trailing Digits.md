# [ICPC 2020 WF] Trailing Digits

## 题目描述

有一批货，每个价值 $b$ 元，可以把 $n$ 个货打包出售，价格是 $b \times n$ 元（前提是$b \times n\le a$），使末尾含有尽可能多的数字 $d$ ，求最多的 $d$ 数量。

## 说明/提示

对于全部数据，有 $1 \le b < 10^6$ , $0 \le d \le 9$ , $b \le a < 10^{10000}$

## 样例 #1

### 输入

```
57 9 1000```

### 输出

```
2```

## 样例 #2

### 输入

```
57 4 40000```

### 输出

```
3```

## 样例 #3

### 输入

```
57 4 39000```

### 输出

```
2```

# 题解

## 作者：FutaRimeWoawaSete (赞：3)

**P8140 sol**

所以是 corner 题。

我们考虑枚举答案，将当前的数分为前半部分和后半部分。后半部分显然是长度为 $\text{ans}$ 个 $\text d$ 的字符串。
 
对于其求模数对 $\text b$，那么前半部分对于 $\text b$ 的模数 $\text p$ 也可以知晓，设前半部分可以表示成 $\text{10}^{\text v} \times \text x$ 的形式，令 $\text a = \text{10} ^ {\text v},\text c = \text p$，我们使用同余方程求解 $\text{ax} \equiv \text c (\text{mod} \ \text b)$ 的最小整数解 $\text x$，然后比较一下范围超没有即可判断，在这里直接暴力 $\text O(\log_{\text{10}} \text a ^ 2)$ 判断即可。

corner：

- 当 $\text d = \text 0$ 若 $\text x = \text 0$，要将 $\text x$ 加到正整数；

- 可能要特判长度为总长时的情况，我不判反正挂了；

```cpp
/*
也就 1e4，暴力比算了。 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
int b,d,a,mod,mt[Len];
inline int pt(int x)
{
	int rs = 0;
	while(x && x % 10 == d) 
	{
		rs ++;
		x /= 10;
	}
	return rs;
}
char s[Len];
const int Inf = 1e7;
int gcd(int a,int b)
{
	if(!b) return a;
	return gcd(b , a % b);
}
int exgcd(int a,int b,int &x,int &y) 
{
  	if(!b) 
	{
    	x = 1;
    	y = 0;
    	return a;
	}
	int d = exgcd(b , a % b , x , y);
	int t = x;
	x = y;
	y = t - (a / b) * y;
	return d;
}
int get(int a,int b,int mod)
{
	int GCD = gcd(a , mod);
	if(b % GCD) return -1;
	int A = a / GCD , B = b / GCD , MOD = mod / GCD , x , y;
	int rcd = exgcd(A , MOD , x , y);
	x = 1ll * x * B % MOD;
	x %= MOD;
	if(x < 0) x += MOD;
	x %= MOD;
	if(!d && x == 0) x += MOD;
	return x;	
}
int main()
{
	//freopen("03.in","r",stdin);
	scanf("%d %d",&b,&d);scanf("%s",s + 1);
	mod = b;mt[0] = 1;int len = strlen(s + 1);
	for(int i = 1 ; i <= len ; i ++) mt[i] = 1ll * mt[i - 1] * 10 % mod;
	int as = 0 , sm = 0;
	//printf("!%d\n",len);
	for(int i = 1 ; i < len ; i ++) 
	{
		sm = 1ll * sm * 10 % mod + d , sm %= mod;
		int gt = get(mt[i] , mod - sm , mod) , b1 = 0 , b2 = 0;
		if(gt == -1) continue;
		//printf("%d %d %d %d\n",i,gt,mod - sm,mt[i]);
		if(len - i >= 7) b1 = 2;
		else
		{
			int x = 0;
			for(int j = 1 ; j <= len - i ; j ++) x = x * 10 + (s[j] - '0');
			if(x > gt) b1 = 2;
			else if(x == gt) b1 = 1;
			else b1 = 0;
			//printf("%d %d\n",i,b1);
		}
		//if(len == i) b1 = 1;
		b2 = 1;
		for(int j = len - i + 1 ; j <= len ; j ++) 
		{
			if(s[j] - '0' != d)
			{
				if(s[j] - '0' < d) b2 = 0;
				else b2 = 2;
				break;
			}
		}
		if(b1 == 2 || (b1 == 1 && b2)) as = i;
	}
	int ss = 0 , bl = 1;
	for(int i = 1 ; i <= len ; i ++) ss = (1ll * ss * 10 + d) % mod;
	for(int i = 1 ; i <= len ; i ++)
	{
		if(d != s[i] - '0')
		{
			if(d < s[i] - '0') bl = 2;
			else bl = 0;
			break;
		}
	} 
	//printf("%d %d %d %d\n",d,ss,bl,len);
	if(d && !ss && bl) as = len;
	printf("%d\n",as);
	return 0;
}
```

---

## 作者：masterhuang (赞：1)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17773631.html)，第 $17$ 篇！

目前最优复杂度题解。

显然答案具有可二分性。现在考虑判断 $k$ 是否满足条件。

令 $A=10^k,c=d\times\dfrac{10^k-1}{9}$，则我们需要找到最小的非负整数 $x$ 使得 $Ax+c\equiv 0\pmod b$。

这显然是可以通过 **exgcd** $O(\log b)$ 求解的，具体细节看代码。

**注意**：当 $d=0$ 且解出 $x=0$ 时，需要把 $x$ 加到最小正整数。

然后考虑最终数 $\le a$ 的条件，只需 $Ax+c\le a$，把 $Ax+c$ 表示为字符串，进行 $O(len)$ 比较即可。

瓶颈在于二分加比较，复杂度 $O(len\log len)$。

---

注意到二分不同值时比较的不同位只有 $\lg b$ 级别，即前几位是解出来的 $x$，后面大多数为都是 $d$，于是存在 $O(len)$ 预处理 $O(\lg b)$ 比较的做法。留作思考（我懒得写了）。

于是最优复杂度可以看作 $O(len)$，于是可以加强到 $a=10^{10^7},b=10^9$ 这样。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=1e4+5;
int b,d;LL x,y;string a;
inline int ksm(int x,int p,const int mod){int s=1;for(;p;(p&1)&&(s=1ll*s*x%mod),x=1ll*x*x%mod,p>>=1);return s;}
void exgcd(int a,int b,LL &x,LL &y)
{
	if(!b) return x=1,y=0,void();
	exgcd(b,a%b,x,y);LL t=x-(a/b)*y;x=y;y=t;
}
inline int eq(int a,int b,int c)
{
	int t=__gcd(a,b);if(c%t) return -1;
	exgcd(a,b,x,y);b/=t;x=(x%b+b)*(c/t)%b;return (!x&&!d)?b:x;
}//exgcd 求解最小解，注意最小解要对 b/gcd 取模，而不是对 b 取模，注意 d=0 的 Corner Case
inline int pw(int k,const int mod){return ((ksm(10,k,9*mod)-1+9*mod)/9)%mod;}//求 c 的小手段
inline bool cmp(string b,string a){if(b.size()^a.size()) return b.size()<a.size();return b<=a;}//O(len) 比较
inline bool chk(int k)
{
	int a=ksm(10,k,b),c=1ll*(b-d)*pw(k,b)%b,t=eq(a,b,c);
	if(t==-1) return 0;string s=t?to_string(t):"";
	while(k--) s+=(d+'0');return cmp(s,::a);
}//二分判断答案，要注意同余方程无解的情况
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>b>>d>>a;
	int l=1,r=a.size(),mid,ans=0;
	while(l<=r) mid=(l+r)>>1,(chk(mid))?(ans=mid,l=mid+1):r=mid-1;
	return cout<<ans,0;
}
```

---

## 作者：Eterna (赞：0)

对于答案为 $k$ 的一组解，它一定为 $10^k x+\underbrace{dd \dots dd}_{k 个 d}$ 的形式。

对于一个解合法若不考虑 $a$ 的限制，条件为 $10^k x+\underbrace{dd \dots dd}_{k 个 d} \equiv 0 \pmod{b} $。

设 $10^k x+\underbrace{dd \dots dd}_{k 个 d}=p\times b$，其中 $p$ 未知。有 $10^k x -pb = -\underbrace{dd \dots dd}_{k 个 d}$，是一个 exgcd 的形式。

预处理 $\displaystyle \underbrace{dd \dots dd}_{k 个 d}\bmod b$，和 $10^k\bmod b$ 跑出最小的 $x$。

从到小枚举 $k$，然后将 $10^k x+\underbrace{dd \dots dd}_{k 个 d}$ 与 $a$ 比较大小即可。比较大小可以直接将 $x$ 后面拼 $k$ 个 $d$ 与 $a$ 继续字符串比较。




```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=10005;
int b,d,p[N],pd[N];string a;
inline bool check(string t)
{
	if(a.size()!=t.size())return t.size()<a.size();
	int n=a.size();
	for(int i=0;i<n;i++)if(a[i]!=t[i])return t[i]<a[i];
	return 1;
}
inline void exgcd(int A,int B,int &x,int &y)
{
	if(!B)return x=1,y=0,void();
	exgcd(B,A%B,y,x),y-=A/B*x;
}
inline void find(int a,int b,int &x,int c)
{
	c=(c%b+b)%b;
	int X,Y,gcd=__gcd(a,b),H=b/gcd;
	if(c%gcd)return x=-1,void();
	exgcd(a,b,X,Y),x=(X*c/gcd%H+H)%H,x+=(!x&&!d)*H;
}
inline bool chk(int x)
{
	int X;
	find(p[x],b,X,-pd[x]);
	if(X==-1)return 0;
	string t=X?to_string(X):"";
	for(int i=1;i<=x;i++)t=t+char(d+'0');
	return check(t);
}
signed main()
{
	cin>>b>>d>>a;p[0]=1;
	for(int i=1;i<=a.size();i++)p[i]=p[i-1]*10%b,pd[i]=(pd[i-1]*10+d)%b;
	for(int i=a.size();i>=0;i--)if(chk(i)){cout<<i<<'\n';return 0;}
	return 0;
}
```

---

## 作者：yhy2024 (赞：0)

发现最后答案可写成 $x10^k+\underbrace{d \ldots d}_{k 个 d}$。

枚举 $k$，令 $a=10^k$，$c=\underbrace{d \ldots d}_{k 个 d}=d \times \frac{10^k-1}{9}$。则有同余方程：$ax+c\equiv0\pmod b$。写成二元一次：$ax+by=-c$。扩展欧几里得解出最小解 $x$，判一下原数合法。

一个特判，如果 $d=0$ 并且 $x=0$ 要把 $x$ 变成正数，加个 $\frac{b}{\gcd(a,b)}$，如果前面是 $0$ 后面再多 $0$ 也不合法。

---

