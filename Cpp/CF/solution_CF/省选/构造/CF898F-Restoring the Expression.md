# Restoring the Expression

## 题目描述

A correct expression of the form a+b=c was written; $ a $ , $ b $ and $ c $ are non-negative integers without leading zeros. In this expression, the plus and equally signs were lost. The task is to restore the expression. In other words, one character '+' and one character '=' should be inserted into given sequence of digits so that:

- character'+' is placed on the left of character '=',
- characters '+' and '=' split the sequence into three non-empty subsequences consisting of digits (let's call the left part a, the middle part — b and the right part — c),
- all the three parts a, b and c do not contain leading zeros,
- it is true that a+b=c.

It is guaranteed that in given tests answer always exists.

## 样例 #1

### 输入

```
12345168
```

### 输出

```
123+45=168
```

## 样例 #2

### 输入

```
099
```

### 输出

```
0+9=9
```

## 样例 #3

### 输入

```
199100
```

### 输出

```
1+99=100
```

## 样例 #4

### 输入

```
123123123456456456579579579
```

### 输出

```
123123123+456456456=579579579
```

# 题解

## 作者：Hoks (赞：5)

## 前言
[题目链接](https://www.luogu.com.cn/problem/CF898F)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-cf898f)内食用更佳。

~~duel 到的 +1。（什么时候整个统计一下吧）~~
## 题意分析
因为是让我们放一个加号和等号，很明显，左边两个数的长度的最大值最小也只能是右边那个数的长度 $-1$。这样我们的枚举量就会大大减小。

接着考虑字符串如何处理，首先考虑哈希，但是并不存在哈希加这种东西，所以我们要把哈希的 $op$ 调为 $10$。显然，这样的话，哈希的正确性会大大降低，最好是使用双哈希。~~但是我比较懒，所以这篇写的是单哈希。~~

最后记得判前导零。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,mod=123456791;
char s[1000010];
int op[1000010],h[1000010];
int read()
{
    char c=getchar();int x=0,f=1;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
int has(int l,int r){return ((h[r]-h[l-1]*op[r-l+1])%mod+mod)%mod;}
void print(int l,int r)
{
    for(int i=1;i<l;i++) putchar(s[i]);putchar('+');
    for(int i=l;i<r;i++) putchar(s[i]);putchar('=');
    for(int i=r;i<=n;i++) putchar(s[i]);
}
bool check(int l,int r){return (s[l]!='0'?true:l==r);}
void check1(int l,int r)
{
    if(l-1<=0) return;
    unsigned long long a=has(1,l-1),b=has(l,r-1),c=has(r,n);
    if((a+b)%mod==c&&check(l,r-1)&&check(r,n)){print(l,r);exit(0);}
}
signed main()
{
    scanf("%s",s+1);n=strlen(s+1);op[0]=1;
    for(int i=1;i<=n;i++) 
    {
        op[i]=op[i-1]*10%mod;
        h[i]=(h[i-1]*10+s[i]-'0')%mod;
    }
    for(int i=n/3;i<=(n>>1);i++)
    {
        check1(i+1,n-i+1);check1(i,n-i+1);
        check1(n-i*2+2,n-i+1);check1(n-i*2+1,n-i+1);
    }
    return 0;
}
```


---

## 作者：xixike (赞：4)

# Solution

很明显的一道哈希题，那么我们考虑哈希能否支持加法。

我们~~通过列举大量式子~~发现，普通的哈希是不行的，但是我们换一个乘数，也就是令 $Base = 10$，那么是不是就可以支持加法了呢。

但是这样一来，冲突的概率就大了很多，所以要双哈希，而且~~由于是 CF 的题~~这道题非常毒瘤的把 998244353，1000000007 等常见模数全部卡掉了 QwQ，恶心至极。所以要换一些模数。

然后就是具体过程。

我们可以枚举**等号**的位置，假设等号后面的数长为 $len$，由于加法最多进一位，所以**加号**前的数长度为 $len$ 或 $len - 1$，**加号**后面的数同理。

另外注意这道题还要判前导 0。

这道题最麻烦的就是边界的处理，我整整做了一个晚上啊啊啊啊啊啊啊。

# Code

(有注释)

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long

using namespace std;

const ll N = 1e6 + 10;
const ll mod1 = 1e9 + 21;//双哈希模数
const ll mod2 = 1e9 + 33;
ll n, pos1 = N, pos2 = N;//pos1: 加号位置	pos2: 等号位置
ll fx[N], f[N];//双哈希两个数组
ll gx[N], g[N];
char s[N];

inline ll Hash1(ll l, ll r){//去第一个哈希值
	return (f[r] - f[l - 1] * fx[r - l + 1] % mod1 + mod1) % mod1;
}

inline ll Hash2(ll l, ll r){//取第二个哈希值
	return (g[r] - g[l - 1] * gx[r - l + 1] % mod2 + mod2) % mod2;
}

inline bool check(int l, int r){//判断是否有前导0，1为没有，0为有
	if(s[l] != '0') return 1;//第一位不为0，直接返回1
	for(int i = l + 1; i <= r; i++)
		if(s[i] == '0') return 0;
	return 1;
}

inline bool checkr1(int len, int n, int flag){//判断第二个加数长度为 len 或 len - 1 时，等式是否成立。flag = 0时，长度为 len - 1，flag = 1时，长度为 len
	int l = n - (len << 1) + flag;//l 为第一个加数右边界
	if(l < 1) return 0;
    //第一个加数 + 第二个加数 == 和
	return ((Hash1(1, l) + Hash1(l + 1, n - len)) % mod1) == Hash1(n - len + 1, n) && check(l + 1, n - len);
}

inline bool checkr2(int len, int n, int flag){//第二个哈希
	int l = n - (len << 1) + flag;
	if(l < 1) return 0;
	return ((Hash2(1, l) + Hash2(l + 1, n - len)) % mod2)== Hash2(n - len + 1, n) && check(l + 1, n - len);
}

inline bool checkl1(int len, int n, int flag){//判断第一个加数的情况，其它同上
	int l = len + flag - 1;
	if(l < 1) return 0;
	return ((Hash1(1, l) + Hash1(l + 1, n - len)) % mod1) == Hash1(n - len + 1, n) && check(l + 1, n - len);
}

inline bool checkl2(int len, int n, int flag){
	int l = len + flag - 1;
	if(l < 1) return 0;
	return ((Hash2(1, l) + Hash2(l + 1, n - len)) % mod2) == Hash2(n - len + 1, n) && check(l + 1, n - len);
}

inline void updater(int len, int flag){//当第二个加数符合条件时，更新加号和等号的位置
	if(n - (len << 1) + flag < pos1) pos1 = n - (len << 1) + flag, pos2 = n - len;
}

inline void updatel(int len, int flag){//同理
	if(len + flag - 1 < pos1) pos1 = len + flag - 1, pos2 = n - len;
}

signed main(){
	//  freopen("a.in", "r", stdin);
	//  freopen("a.out", "w", stdout);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	fx[0] = 1, gx[0] = 1;
	for(ll i = 1; i <= n; i++){
		fx[i] = fx[i - 1] * 10 % mod1;
		f[i] = (f[i - 1] * 10 + s[i] - '0') % mod1;
		gx[i] = gx[i - 1] * 10 % mod2;
		g[i] = (g[i - 1] * 10 + s[i] - '0') % mod2;
	}
	for(int len = n / 3; len <= (n >> 1); len++){
		if(!check(n - len + 1, n)) continue;//和 有前导0，直接跳过
		if(checkr1(len, n, 0) && checkr2(len, n, 0)) updater(len, 0);//第二个加数长度为 len - 1
		if(checkr1(len, n, 1) && checkr2(len, n, 1)) updater(len, 1);//第二个加数长度为 len
		if(checkl1(len, n, 0) && checkl2(len, n, 0)) updatel(len, 0);//第一个加数长度为 len - 1
		if(checkl1(len, n, 1) && checkl2(len, n, 1)) updatel(len, 1);//第二个加数长度为 len
	}
	for(ll i = 1; i <= pos1; i++)//输出
		putchar(s[i]);
	putchar('+');
	for(ll i = pos1 + 1; i <= pos2; i++)
		putchar(s[i]);
	putchar('=');
	for(ll i = pos2 + 1; i <= n; i++)
		putchar(s[i]);
	puts("");
	return 0;
}
```


---

## 作者：81179332_ (赞：2)

update: 丢人啊，$19260817$，咱也不知道当时为啥背成了 $19760817$

恭喜 $1e9+7,1e9+9,998244353$ 叒叒被卡。

考虑如果等式右面是一个 $n$ 位数，那么等式左边至少有一个数为 $n-1$ 位或 $n$ 位。

所以我们枚举等号的位置，此时只有 $4$ 个位置放加号可能使等号成立。

对于这四个位置中的一个，我们使用`base`为 $10$ 的哈希判断等式是否成立，即将等号左边的两个字符串的哈希值加起来，判断是否等于等号右边字符串的哈希值。

虽然 $19260817$ 火遍了大江南北，但是在国外应该知名度不高，所以我们使用 $19260817$ 和 $1e9+9$作为双哈希的两个模数。

```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<cstring>
using namespace std;
inline long long read()
{
	long long x = 0;
	int f = 1;
	char ch = getchar();
	for(;!isdigit(ch);ch = getchar())
		if(ch == '-')
			f = -1;
	for(;isdigit(ch);ch = getchar())
		x = x * 10 + (ch ^ 48);
	return x * f;
}

const int N = 1000010,mod1 = 19260817,mod2 = 1e9 + 9;

int n;
char s[N];
long long h1[N],h2[N],b1[N],b2[N],base = 10;

void init()
{
	b1[0] = b2[0] = 1;
	for(int i = 1;i <= n;i++)
	{
		h1[i] = (h1[i - 1] * base + s[i] - '0') % mod1;
		h2[i] = (h2[i - 1] * base + s[i] - '0') % mod2;
		b1[i] = b1[i - 1] * base % mod1;
		b2[i] = b2[i - 1] * base % mod2;
	}
}

long long get1(int l,int r)
{
	int res = h1[r] - h1[l - 1] * b1[r - l + 1] % mod1 + mod1;
	return res - mod1 * (res >= mod1);
}
long long get2(int l,int r)
{
	int res = h2[r] - h2[l - 1] * b2[r - l + 1] % mod2 + mod2;
	return res - mod2 * (res >= mod2);
}

int sum1,sum2;

bool NoZero(int pos1,int pos2)
{
	if(!pos1 || pos2 - pos1 != 1 && s[pos1 + 1] == '0' || pos2 != n - 1 && s[pos2 + 1] == '0')
		return 0;
	return 1;
}
bool check(int pos1,int pos2)
{
	return (get1(1,pos1) + get1(pos1 + 1,pos2)) % mod1 == sum1
	    && (get2(1,pos1) + get2(pos1 + 1,pos2)) % mod2 == sum2
		&& NoZero(pos1,pos2);
}

void P(int pos1,int pos2)
{
	for(int i = 1;i <= pos1;i++)
		putchar(s[i]);
	putchar('+');
	for(int i = pos1 + 1;i <= pos2;i++)
		putchar(s[i]);
	putchar('=');
	for(int i = pos2 + 1;i <= n;i++)
		putchar(s[i]);
	puts("");
	exit(0);
}

int main()
{
	scanf("%s",s + 1),n = strlen(s + 1);
	init();

	for(int i = n - 1;i >= 2;i--)
	{
		if(i < n - i)
			break;
		sum1 = get1(i + 1,n),sum2 = get2(i + 1,n);
		int len = n - i;
		if(check(len,i))
			P(len,i);
		if(check(len - 1,i))
			P(len - 1,i);
		if(check(i - len + 1,i))
			P(i - len + 1,i);
		if(check(i - len,i))
			P(i - len,i);
	}
}
```

---

## 作者：MikukuOvO (赞：2)

我们考虑枚举等号的位置，根据加法的性质，我们不难发现加号的可能位置数量级为$O(1)$。

更准确来说，如果等号后面长度为$len$，那么只有四种可能，要么加号左面的为$len,len-1$或者右面为这两个数，我们考虑使用哈希来判断即可，这里我们将$base$取$10$，这样就具有加法的性质了。

$!!!$注意：模数不要使用常用模数，真的有人卡了$1e9+7$和$1e9+9$。。。

```cpp
const int N=1e6+5;
const int base=10;
const ll mod1=1e9+7;
const ll mod2=1e8+9;

int n;
ll sum1,sum2;
ll h1[N],h2[N],f1[N],f2[N];
char s[N];

void init()
{
    f1[0]=f2[0]=1;
    for(int i=1;i<=n;++i) h1[i]=(h1[i-1]*base+s[i]-'0')%mod1;
    for(int i=1;i<=n;++i) h2[i]=(h2[i-1]*base+s[i]-'0')%mod2;
    for(int i=1;i<=n;++i) f1[i]=f1[i-1]*base%mod1;
    for(int i=1;i<=n;++i) f2[i]=f2[i-1]*base%mod2;
}
ll get1(int l,int r)
{
    return (h1[r]-h1[l-1]*f1[r-l+1]%mod1+mod1)%mod1;
}
ll get2(int l,int r)
{
    return (h2[r]-h2[l-1]*f2[r-l+1]%mod2+mod2)%mod2;
}
bool nozero(int x,int y)
{
    if(!x||(y-x!=1&&s[x+1]=='0')||(y!=n-1&&s[y+1]=='0')) return false;
    return true;
}
bool check(int x,int y)
{
    if(x==1&&y==3)
    {
        P(sum1);P(sum2);
        P(get1(1,x)+get1(x+1,y));
        P(get2(1,x)+get2(x+1,y));
    }
    return ((get1(1,x)+get1(x+1,y))%mod1==sum1)&&((get2(1,x)+get2(x+1,y))%mod2==sum2)&&nozero(x,y);
}
void printans(int x,int y)
{
    for(int i=1;i<=x;++i) pc(s[i]);
    pc('+');
    for(int i=x+1;i<=y;++i) pc(s[i]);
    pc('=');
    for(int i=y+1;i<=n;++i) pc(s[i]);
}
int main()
{
    fio();
    scanf("%s",s+1),n=strlen(s+1);
    init();
    for(int i=n-1;i>=2;--i)
    {
        sum1=get1(i+1,n),sum2=get2(i+1,n);
        int len=n-i;
        if(check(len,i)) printans(len,i),end();
        if(check(len-1,i)) printans(len-1,i),end();
        if(check(i-len+1,i)) printans(i-len+1,i),end();
        if(check(i-len,i)) printans(i-len,i),end();
    }
    end();
}
```

---

## 作者：Crazyouth (赞：1)

## 鲜花

我使用了双哈希 $998244353$ 和 $1000000007$，在调试的时候过不去，换成了 $1000000009$，还是挂了，于是看了数据：

![](https://cdn.luogu.com.cn/upload/image_hosting/h01jh8ki.png)

（图中数字为第 $78$ 个点的数据的前若干位。）

## 分析

我们可以枚举 `+` 的位置，然后注意到两个数的和的位数不超过两个数位数较大者加一，于是确定 `+` 之后 `=` 的位置只有 $O(1)$ 种，具体地，我们可以看两个数的和与哪个加数位数相关（是相同的位数或者是位数加一），这样 `=` 的位置就只有至多 $4$ 个，分别枚举一下并判断等式能否成立。

判断成立的时候，我们把两个加数的和取模后与等号后面的数的 hash 值拿出来判断是否相等，如果是的话就可以直接输出了（哈希冲突概率极小）。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod[2]={998244389,998244853};
const int N=1e6+10;
int sum[N][2],p10[N][2],inv10[N][2],n;
string s;
inline int qpow(int b,int p,int t)
{
	int ret=1;
	while(p)
	{
		if(p&1) ret=ret*b%mod[t];
		b=b*b%mod[t];
		p>>=1;
	}
	return ret;
}
inline int hsh(int l,int r,int t)
{
	return (sum[r][t]-sum[l-1][t]+mod[t])%mod[t]*inv10[n-r+1][t]%mod[t];
}
void check(int l,int r)
{
//	cout<<"hsh("<<1<<','<<l<<")="<<hsh(1,l,0)<<'\n';
//	cout<<"hsh("<<l+1<<','<<r<<")="<<hsh(l+1,r,0)<<'\n';
//	cout<<"hsh("<<r+1<<','<<n<<")="<<hsh(r+1,n,0)<<'\n';
	for(int k=0;k<2;k++)
	{
		if((hsh(1,l,k)+hsh(l+1,r,k))%mod[k]!=hsh(r+1,n,k))
		return;
	}
	for(int i=1;i<=l;i++) cout<<s[i];
	cout<<'+';
	for(int i=l+1;i<=r;i++) cout<<s[i];
	cout<<'=';
	for(int i=r+1;i<=n;i++) cout<<s[i];
	exit(0);
}
signed main()
{
	cin>>s;
	n=s.size();
	s=' '+s;
	p10[0][0]=p10[0][1]=inv10[0][0]=inv10[0][1]=1;
	for(int i=1;i<=n;i++) for(int t=0;t<2;t++) p10[i][t]=p10[i-1][t]*10%mod[t],inv10[i][t]=qpow(p10[i][t],mod[t]-2,t);
	for(int i=1;i<=n;i++)
	{
		for(int t=0;t<2;t++)
		{
			sum[i][t]=sum[i-1][t]+(s[i]-'0')*p10[n-i+1][t]%mod[t];
//			assert(sum[i][t]);
			sum[i][t]%=mod[t];
		}
	}
	if(s[1]=='0')
	{
		cout<<"0+";
		for(int i=2;i<=n/2+1;i++) cout<<s[i];
		cout<<'=';
		for(int i=2;i<=n/2+1;i++) cout<<s[i];
		return 0; 
	}
	for(int i=1;i<=n/2;i++)
	{
		if(s[i+1]=='0')
		{
			if(s[i+2]=='0') continue;
			else check(i,i+1);
			continue;
		}
		if((n-i)%2)
		{
			check(i,(n-i)/2+i);
			check(i,(n-i)/2+i+1);
		}
		else check(i,(n-i)/2+i);
		check(i,n-i);
		if(i<n-i-1)
		check(i,n-i-1);
	}
}

---

## 作者：__Louis__ (赞：1)

##  CF898F Restoring the Expression 题解

### 题目描述

给定一个字符串，在其中添加一个加号和一个等号，让等式成立。同时满足没有前导0且加号在等号前面。

数据范围 $|s| \le 10^6$

### 非常暴力的做法

枚举加号和等号的位置，取模来 $O(n)$ 判断等式是否成立。

- 注意模数要有两个，或者找到一个比较好的 $mod$。

### 如何 $ O(1)$ 判断？

很明显，我们可以做一个前缀和，来纪录区间 $[1,r ]$ 的大小。然后利用位置原理就可以 $O(1)$ 求出了，类似于字符串哈希。

### 减少枚举的次数。

即使 $O(1)$ 判断，仍然发现复杂对于 $|s|$ 来说不友好，于是我们减少枚举次数。 

仔细想会发现，加法对于位数的影响不大，准确的说，如果知道了和，就可以很好地确定了两个加数的位数大小。

简单来说：设两个加数的最大位数为 $h$, 则和的位数只可能为 $h$ 或者 $h+1$。 

然后就可以愉快的特殊判断写过这道题了。

### AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10;
const int mod=520040527;//所谓的好模数 
int p[maxn],arr[maxn];
int _10[maxn];
int n;
string s;
void init(){
	_10[0]=1;
	for(int i=1;i<=1000000;i++){
		_10[i]=_10[i-1]*10%mod;
	}
	for(int i=1;i<=n;i++){
		arr[i]=(arr[i-1]*10+s[i]-'0')%mod;
	}
}
int get(int l,int r){//位置原理判断 
	return (arr[r]+mod*mod-arr[l-1]*+_10[r-l+1])%mod;
}
bool b_=true;// 只用输出一次 
void check(int a,int b){
	//判断前导0 
	if(a+1!=b&&s[a+1]=='0') return; 
	if(b+1!=n&&s[b+1]=='0') return;
	
	if(((get(1,a)+get(a+1,b)-get(b+1,n)+mod)%mod)==0){
		
		for(int i=1;i<=a;i++){
			cout<<s[i];
		}
		cout<<'+';
		for(int i=a+1;i<=b;i++){
			cout<<s[i];
		}
		cout<<'=';
		for(int i=b+1;i<=n;i++){
			cout<<s[i];
		}
		b_=false;
	}
}
signed main(){
	cin>>s;
	n=s.size();
	s=' '+s;
	init();
	for(int i=n-1;i>=n/2;i--){
		int k=n-i;//判断大概位置 
		if(b_)	check(k,i);
		if(b_) check(k-1,i);//位数有可能有加减，都要check 
		if(b_) check(i-k,i);
		if(b_)  check(i-k+1,i);
	}
}
```

---

## 作者：ncwzdlsd (赞：1)

## 题意

给定一个数字串，要求在串中插入“+”和“=”，使得这个数字串变成一个成立的等式。要求如下：

1. 加号必须在等号前面

2. 加数与和都不能有前导 $0$，且非空。

## 题解

前置芝士：[字符串 Hash](https://ncwzdlsd.top/articles/string-hash/)（安利一下自己的博客 QwQ）

~~这道题有一种小学奥数题的感觉。~~

首先我们可以考虑一种暴力做法，枚举加号和等号的位置，显然会喜提 TLE。于是乎我们需要优化它。

显然，当我们确定了等号的位置之后，一定有唯一的加号位置与之对应。

那么，如何判断这个等式是否成立呢？我们可以用 Hash 来解决这个问题。为了实现 Hash 值的加法操作，我们只需要把乘的数设定为 $10$ 即可。

对于一个已经确定的等号位置，我们该如何找到加号呢？利用小学的数学知识可以知道，如果和为 $n$ 位数，那么两个加数中的每一个各有两种可能，要么是 $n$ 位，要么是 $n-1$ 位，于是乎我们只需要对这四种情况分类即可。

对于题里的两个要求，我们可以写一个函数来检查当前状态是否符合。

据说 CF 会卡单模法，要用双哈希，不过单模法还是能切掉这道题的，只不过不能选一些常用的模数了，可以选用的模数之一：$123456791$。

由于我用的是单模法，所以代码应该是最短的，代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long//习惯
using namespace std;
const int N=1000005,mod=123456791;
int power[N]={1},hh[N],n;
char s[N];
inline int hashh(int a,int b)//区间a到b的哈希值，用于判断等式能否成立
{
	return (hh[b]-hh[a-1]*power[b-a+1]%mod+mod)%mod;
}
inline int check(int a,int b)//判断前导0和是否非空
{
	if(!a) return 0;
	if(b-a!=1&&s[a+1]=='0') return 0;
	if(b!=n-1&&s[b+1]=='0') return 0;	
	return 1;
} 
inline void out(int a,int b)//输出1~a位、a+1~b位组成的式子
{
	for(int i=1;i<=a;i++) cout<<s[i];	
	cout<<'+';
	for(int i=a+1;i<=b;i++) cout<<s[i];
	cout<<'=';
	for(int i=b+1;i<=n;i++) cout<<s[i];
	exit(0);//注意退出
} 
signed main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		hh[i]=(hh[i-1]*10%mod+s[i]-'0')%mod;
	for(int i=1;i<=n;i++)
		power[i]=power[i-1]*10%mod;
   //上面的递归操作，为了求哈希值做准备
	for(int i=n-1;i>=2;i--)
	{
		if(i<n-i)
			continue;
		int sum1=hashh(i+1,n),len=n-i;
		if((hashh(1,len)+hashh(len+1,i))%mod==sum1&&check(len,i)) out(len,i);
		if((hashh(1,len-1)+hashh(len,i))%mod==sum1&&check(len-1,i)) out(len-1,i);
		if((hashh(1,i-len)+hashh(i-len+1,i))%mod==sum1&&check(i-len,i)) out(i-len,i);
		if((hashh(1,i-len+1)+hashh(i-len+2,i))%mod==sum1&&check(i-len+1,i)) out(i-len+1,i);
	}
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：1)

很久以前做的题了。过来水篇题解。

看到这道题，很快啊，想到以前看到过满足加法的哈希：

哈希的定义是将字符串转化为 $\sum \limits_{i = l}^{r} s_i b^{r - i}$ 的形式。如果 $s_i$ 是数字，就相当于将字符串转为 $b$ 进制数。显然，在这道题中，可以把 $b$ 取成 $10$，这就等于把字符串变成十进制数。这样，字符串问题就变成数学问题了：将原字符串分为三部分，使得前两部分哈希值的和等于第三部分。

枚举第一个加号的位置或者等号位置，答案应该很好求。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

using LL = long long;

const int N = 1000010, Base = 10, mod = 520040527;
LL p[N], h[N];
char s[N];
int n;

LL get(int l, int r) {
	return ((h[r] - h[l - 1] * p[r - l + 1]) % mod + mod) % mod;
}

bool Leading_Zero(int l, int r) {
	return (s[l] != '0' ? true : l == r);
}

void print(int a, int b) {
	for (int i = 1; i < a; i ++ ) putchar(s[i]); putchar('+');
	for (int i = a; i < b; i ++ ) putchar(s[i]); putchar('=');
	for (int i = b; i <= n; i ++ ) putchar(s[i]);
}

void check(int r1, int r2) {
	if (r1 - 1 <= 0) return;
	ULL a = get(1, r1 - 1), b = get(r1, r2 - 1), c = get(r2, n);
	if ((a + b) % mod == c && Leading_Zero(r1, r2 - 1) && Leading_Zero(r2, n)) {
		print(r1, r2); exit(0);
	}
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	
	p[0] = 1;
	for (int i = 1; i <= n; i ++ ) {
		h[i] = (h[i - 1] * Base + s[i] - '0') % mod;
		p[i] = (p[i - 1] * Base) % mod;
	}
	
	for (int i = n / 3; i <= n >> 1; i ++ ) {
		check(i + 1, n - i + 1); check(i, n - i + 1);
		check(n - i * 2 + 2, n - i + 1); check(n - i * 2 + 1, n - i + 1);
	}
	
	puts("No Answer");
	return 0;
}
```

关于哈希模数：随手打的竟然过了。事实证明不需要双哈希。

---

## 作者：0xFF (赞：1)

#### 题目大意


------------
在一个数字串中插入加号和等号使得等式成立。


#### 思路分析


------------
由于题目要求满足在十进制下加法成立，故使用十进制哈希维护。

对于哈希使用多个模数以避免哈希冲突。

最朴素的做法是枚举加号和等号的位置，时间复杂度 $\Theta(n^2)$ 显然无法通过本题，考虑等式的特性，被加数或者加数的位数与和的位数最多相差一，枚举被加数的长度分类讨论即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>

using namespace std;

const int N = 1e6 + 5, inf = 0x3f3f3f3f;
typedef long long LL;

inline int read(){
	LL x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}

LL mod[5], hashs[5][N] , p[5][N];
LL flag , lens;
char str[N];

LL get_hashs (LL l, LL r, LL k) {
	return ((hashs[k][r] - hashs[k][l - 1] * p[k][r - l + 1] % mod[k]) % mod[k] + mod[k]) % mod[k];
}

void print(LL pos1, LL pos2) {
	for (LL i = 1; i <= lens; i++) {
		printf("%c",str[i]);
		if (i == pos1) printf("+");
		if (i == pos2) printf("=");
	}
	exit(0);
	return ;
}
int main(){
	mod[1] = 2147483647, mod[2] = 998244353, mod[3] = 19260817, mod[4] = 1000000007;
	scanf("%s",str+1);
	lens = strlen(str + 1);
	p[1][0] = p[2][0] = p[3][0] = p[4][0] = 1;
	for (LL i=1;i<=lens;i++) {
		for (LL j=1;j<=4;j++) {
			hashs[j][i] = (hashs[j][i - 1] * 10 + str[i] - '0') % mod[j];
			p[j][i] = p[j][i - 1] * 10 % mod[j];
		}
	}
	for (LL i=1;i<=lens/2;i++) {
		flag = 1;
		for (LL j = 1; j <= 4; j++) {
			LL pos1 = i, pos2 = lens - i;
			LL tmp1 = get_hashs(1, pos1, j), tmp2 = get_hashs(pos1 + 1, pos2, j), tmp3 = get_hashs(pos2 + 1, lens, j);	
			if (((tmp1 % mod[j] + tmp2 % mod[j]) % mod[j] != tmp3 % mod[j] )|| ((str[1] == '0' || str[pos1 + 1] == '0' || str[pos2 + 1] == '0') && (pos2 != pos1 + 1))) {
				flag = 0;
				break;
			}
		}
		if (flag) print(i, lens - i);
		flag = 1;
		for (LL j=1;j<=4;j++) {
			LL pos1 = i, pos_3 = lens - i - 1;
			LL tmp1 = get_hashs(1, pos1, j), tmp2 = get_hashs(pos1 + 1, pos_3, j), tmp3 = get_hashs(pos_3 + 1, lens, j);
			if (((tmp1 % mod[j] + tmp2 % mod[j]) % mod[j] != tmp3 % mod[j] )|| ((str[pos1 + 1] == '0' || str[pos_3 + 1] == '0') && (pos_3 != pos1 + 1))) {
				flag = 0;
				break;
			}
		}
		if (flag) print(i, lens - i - 1);
		if ((lens - i) % 2 == 0) {
			flag = 1;
			for (LL j=1;j<=4;j++) {
				LL pos1 = i, pos_3 = i + (lens - i) / 2;
				LL tmp1 = get_hashs(1, pos1, j), tmp2 = get_hashs(pos1 + 1, pos_3, j), tmp3 = get_hashs(pos_3 + 1, lens, j);
				if (((tmp1 % mod[j] + tmp2 % mod[j]) % mod[j] != tmp3 % mod[j] )|| ((str[pos1 + 1] == '0' || str[pos_3 + 1] == '0') && (pos_3 != pos1 + 1))) {
					flag = 0;
					break;
				}
			}
			if (flag) print(i, i + (lens - i) / 2);
		}
		else {
			flag = 1;
			for (LL j=1;j<=4;j++) {
				LL pos1 = i, pos_3 = i + (lens - i) / 2;
				LL tmp1 = get_hashs(1, pos1, j), tmp2 = get_hashs(pos1 + 1, pos_3, j), tmp3 = get_hashs(pos_3 + 1, lens, j);
				if (((tmp1 % mod[j] + tmp2 % mod[j]) % mod[j] != tmp3 % mod[j] )|| ((str[pos1 + 1] == '0' || str[pos_3 + 1] == '0') && (pos_3 != pos1 + 1))) {
					flag = 0;
					break;
				}
			}
			if (flag) print(i, i + (lens - i) / 2);
			flag = 1;
			for (LL j=1;j<=4;j++) {
				LL pos1 = i, pos_3 = 1 + i + ((lens - i)>>1);
				LL tmp1 = get_hashs(1, pos1, j), tmp2 = get_hashs(pos1 + 1, pos_3, j), tmp3 = get_hashs(pos_3 + 1, lens, j);
				if (((tmp1 % mod[j] + tmp2 % mod[j]) % mod[j] != tmp3 % mod[j] )|| ((str[pos1 + 1] == '0' || str[pos_3 + 1] == '0') && (pos_3 != pos1 + 1))) {
					flag = 0;
					break;
				}
			}
			if (flag) print(i, 1 + i + ((lens - i) >> 2));
		}
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

先介绍一种暴力做法：枚举加号和等号的位置O(n^2)，在通过高精度加起来O(n)，总时间复杂度O(n^3)肯定过不了。

第一个优化：一个n位数加一个k（k<=n）位数，结果要么是n位数，要么是n+1位数，因此，当我们枚举等号的位置时，对于每个等号，加号最多4种可能。

第二个优化：求和，因为这个字符串并不会变，所以我们可以使用 哈希来判断。注意这是codeforces，最好是写双哈希。

本蒟蒻码风可能不太好，大佬勿喷。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000005;
const int P=10;
const int mod1=20040911;
const int mod2=1000000009;
int p1[N]={1},p2[N]={1},h1[N],h2[N],n;
char s[N];
inline int gh1(int a,int b)
{
	return (h1[b]-h1[a-1]*p1[b-a+1]%mod1+mod1)%mod1;
}
inline int gh2(int a,int b)
{
	return (h2[b]-h2[a-1]*p2[b-a+1]%mod2+mod2)%mod2;
}
inline int can(int a,int b)
{
	if(!a)
		return 0;
	if(b-a!=1&&s[a+1]=='0')
		return 0;
	if(b!=n-1&&s[b+1]=='0')
		return 0;	
	return 1;
} 
inline void out(int a,int b)
{
	for(int i=1;i<=a;i++)
		putchar(s[i]);	
	putchar('+');
	for(int i=a+1;i<=b;i++)
		putchar(s[i]);
	putchar('=');
	for(int i=b+1;i<=n;i++)
		putchar(s[i]);
	exit(0);
} 
main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		h1[i]=(h1[i-1]*P%mod1+s[i]-'0')%mod1;
	for(int i=1;i<=n;i++)
		p1[i]=p1[i-1]*P%mod1;
	for(int i=1;i<=n;i++)
		h2[i]=(h2[i-1]*P%mod2+s[i]-'0')%mod2;
	for(int i=1;i<=n;i++)
		p2[i]=p2[i-1]*P%mod2;
	for(int i=n-1;i>=2;i--)
	{
		if(i<n-i)
			continue;
		int sum1=gh1(i+1,n),sum2=gh2(i+1,n),len=n-i;
		if((gh1(1,len)+gh1(len+1,i))%mod1==sum1&&(gh2(1,len)+gh2(len+1,i))%mod2==sum2
		&&can(len,i))
			out(len,i);
		if((gh1(1,len-1)+gh1(len,i))%mod1==sum1&&(gh2(1,len-1)+gh2(len,i))%mod2==sum2
		&&can(len-1,i))
			out(len-1,i);
		if((gh1(1,i-len)+gh1(i-len+1,i))%mod1==sum1&&(gh2(1,i-len)+gh2(i-len+1,i))%mod2==sum2
		&&can(i-len,i))
			out(i-len,i);
		if((gh1(1,i-len+1)+gh1(i-len+2,i))%mod1==sum1&&(gh2(1,i-len+1)+gh2(i-len+2,i))%mod2==sum2
		&&can(i-len+1,i))
			out(i-len+1,i);
	}
	return 0;
}

```

---

## 作者：Priestess_SLG (赞：0)

简单题。不知道为什么有 $2300$。

考虑判断等式 $a+b=c$ 是否成立。直接做需要 $O(n)$ 的高精度计算，考虑优化。根据模运算的基本性质，可以知道，对于任意一个正整数 $p$，若 $a+b=c$ 成立，则 $(a\bmod p+b\bmod p)\bmod p=c\bmod p$ 也必然成立。因此考虑选取大模数 $p$，然后类似于哈希的方法计算一个前缀 $\bmod\ p$ 的值，从而 $O(1)$ 直接计算出某一个区间 $\bmod\ p$ 的值。此时枚举加号和等号的位置可以做到 $O(n^2)$。

考虑继续优化。容易发现加号和等号的合法组合只有 $O(n)$ 级别（位数原因），因此只枚举位数意义下可能成立的符号组合即可。时间复杂度降低到 $O(n)$，可以通过。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int base = 10, mod = 123456791;
const int N = 1000100;
char s[N];
int bit[N], h[N], n;
inline int get(int x, int y) {
    return (h[y] - h[x - 1] * bit[y - x + 1] % mod + mod) % mod;
}
int ok(int l, int r) {
    if (l > 1) {
        int x = get(1, l - 1), y = get(l, r - 1), z = get(r, n);
        if ((x + y) % mod != z) return 0;
        if (1 != l - 1 && s[1] == '0') return 0;
        if (l != r - 1 && s[l] == '0') return 0;
        if (r != n && s[r] == '0') return 0;
        for (int i = 1; i < l; ++i) cout << s[i];
        cout << "+";
        for (int i = l; i < r; ++i) cout << s[i];
        cout << "=";
        for (int i = r; i <= n; ++i) cout << s[i];
        cout << '\n';
        exit(0);
        return 1;
    } return 0;
}
signed main() {
    // cin.tie(0)->sync_with_stdio(false);
    scanf("%s", s + 1);
    bit[0] = 1;
    for (int i = 1; i < N; ++i) {
        bit[i] = bit[i - 1] * base % mod;
        h[i] = h[i - 1] * base + s[i] - '0';
        h[i] %= mod;
    }
    n = strlen(s + 1);
    for (int i = n / 3; i <= n / 2; ++i) {
        ok(i + 1, n - i + 1);
        ok(i, n - i + 1);
        ok(n - i - i + 1, n - i + 1);
        ok(n - i - i + 2, n - i + 1);
    }
    cout << "-1\n";
    return 0;
}
```

---

## 作者：2022linzhiyi (赞：0)

## 题意
在一个数字字符串中按顺序添加一个加号和等于号，使得算式成立。
## 做法
首先枚举等号后面的数，记其长度为 $k$，由于加法的性质，前面两个数的较大数的位数一定是 $k$ 或 $k-1$，因此只需要枚举 $2 \times 2 = 4$ 次，利用 $base = 10$ 的哈希判断相加是否相等即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N=1e6+10,P=10,mod=998444333;
int n;
char ch[N];
ull h[N],p[N]={1};
ull get(int l,int r) {
	return ((h[r]-h[l-1]*p[r-l+1]%mod)+mod)%mod;
}
bool pd(int l,int r) {
	if (l > r) return false;
	if (l < 1) return false;
	if (l == r) return true;
	if (ch[l] == '0') return false;
	return true;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> (ch+1);
	n=strlen(ch+1);
	for (int i=1;i<=n;i++) h[i]=(h[i-1]*P+ch[i]-'0')%mod, p[i]=p[i-1]*10%mod;
	for (int i=1;i<=n;i++) {
		int l1,r1,l2,r2;
		l1=1, r1=n-i, l2=n-i+1, r2=i-1;		
		if (r1 < i && pd(l1,r1) && pd(l2,r2) && (get(l1,r1)+get(l2,r2))%mod == get(i,n)) {
			for (int j=l1;j<=r1;j++) cout << ch[j];
			cout << '+';
			for (int j=l2;j<=r2;j++) cout << ch[j];
			cout << '=';
			for (int j=i;j<=n;j++) cout << ch[j];
			return 0;
		}
		l1=1, r1=n-i+1, l2=n-i+2, r2=i-1;
		if (r1 < i && pd(l1,r1) && pd(l2,r2) && (get(l1,r1)+get(l2,r2))%mod == get(i,n)) {
			for (int j=l1;j<=r1;j++) cout << ch[j];
			cout << '+';
			for (int j=l2;j<=r2;j++) cout << ch[j];
			cout << '=';
			for (int j=i;j<=n;j++) cout << ch[j];
			return 0;
		}
		l1=1, r1=i*2-n-1, l2=i*2-n, r2=i-1;
		if (r1 < i && pd(l1,r1) && pd(l2,r2) && (get(l1,r1)+get(l2,r2))%mod == get(i,n)) {
			for (int j=l1;j<=r1;j++) cout << ch[j];
			cout << '+';
			for (int j=l2;j<=r2;j++) cout << ch[j];
			cout << '=';
			for (int j=i;j<=n;j++) cout << ch[j];
			return 0;
		}	
		l1=1, r1=i*2-n-2, l2=i*2-n-1, r2=i-1;
		if (r1 < i && pd(l1,r1) && pd(l2,r2) && (get(l1,r1)+get(l2,r2))%mod == get(i,n)) {
			for (int j=l1;j<=r1;j++) cout << ch[j];
			cout << '+';
			for (int j=l2;j<=r2;j++) cout << ch[j];
			cout << '=';
			for (int j=i;j<=n;j++) cout << ch[j];
			return 0;
		}	
	}
	return 0;
}
```

---

## 作者：CQ_Bab (赞：0)

# 前言
其实和 [AT_abc339_f](https://www.luogu.com.cn/problem/AT_abc339_f) 有点像，但是这道题要难一点。
# 思路
首先可以想到去进行 hash 判断加起来是否相等，注意这里是 $10$ 进制，但是这里会发现一个性质就是对于一个加法如果和的位数为 $x$ 那么加数中必定有一个数的位数为 $x$ 或 $x-1$，那么有了这个就可以去枚举等号的位置然后判断四种情况是否有一种满足即可。

这里我们可以写 check 函数去检查，但是这里主要需要判前导零，这里可以用一种很简单的方式来判断就是先看第二个的开头是否为 $0$ 如果为零且此加数的长度大于 $1$ 那么一定有前导零，注意这道题还需要用双 hash。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define in(x) scanf("%lld",&x)
#define fire signed
#define il inline
il void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
string s;
const int mod=1e9+7,ba=10,N=1e6+10,mod1=133333331;
int jc[N],f[N],dp[N],jc1[N];
int get(int l,int r) {
	return (f[r]-f[l-1]*jc[r-l+1]%mod+mod)%mod;
}
int get1(int l,int r) {
	return (dp[r]-dp[l-1]*jc1[r-l+1]%mod1+mod1)%mod1;
}
bool check(int a,int b,int c,int d,int e,int f) {
	if(s[c]=='0'&&d-c+1>1) return false;
	if((get(a,b)+get(c,d))%mod==get(e,f)&&(get1(a,b)+get1(c,d))%mod1==get1(e,f)) return 1;
	return false;
}
fire main() {
	cin>>s;
	int n=s.size();
	s=" "+s;
	jc[0]=jc1[0]=1;
	rep(i,1,n) jc[i]=jc[i-1]*ba%mod,f[i]=(f[i-1]*ba%mod+(s[i]-'0')%mod)%mod,dp[i]=(dp[i-1]*ba%mod1+(s[i]-'0'))%mod1,jc1[i]=(jc1[i-1]*ba)%mod1;
	int ans=false,jia=false;
	rep1(i,n,(n+1)/2) {
		if(i<n-i) continue;
		int len=n-i+1;
		if(check(1,len,len+1,i-1,i,n)) jia=len,ans=i;
		if(check(1,len-1,len,i-1,i,n)&&len>1) jia=len-1,ans=i;
		if(check(1,(i-1)-len,(i-1)-len+1,i-1,i,n)) jia=(i-1)-len,ans=i;
		if(check(1,(i-1)-(len-1),(i-1)-(len-1)+1,i-1,i,n)&&len>1) jia=(i-1)-(len-1),ans=i;
		if(ans&&jia) {
			if(!check(1,jia,jia+1,ans-1,ans,n)) ans=jia=false;
			else {
				rep(i,1,n) {
					if(i==ans) cout<<'=';
					cout<<s[i];
					if(i==jia) cout<<'+';
				}
				return false;
			}
		}
	}
	return false;
}
```

---

## 作者：封禁用户 (赞：0)

#### 错误思路

每次枚举加号的位置，然后通过哈希二分等号的位置，但是哈希取了模，所以没有单调性，所以错误。

#### 正确思路

此题与字符串有关，所以与长度有关。我们可以发现一个性质，加数中必有一数的位数为和的位数或和的位数减一，即可分四种情况讨论： $ lena = lenc $ ， $ lenb = lenc $ ， $ lena = lenc - 1 $ ， $ lenb = lenc - 1 $ 就可以了。

哈希的进制数要设为 $ 10 $

#### 代码

```
#include<iostream>
#include<cstring>
using namespace std;
#define int long long
#define m 10
#define p 520040527
int len,a[1000005],h[1000005],pw[1000005],ans1,ans2;
char s[1000005];
int query(int l,int r){
	if(r<l)return 0;
	return (h[r]-h[l-1]*pw[r-l+1]%p+p)%p;
}
bool check(int lb,int lc){
	if((!a[1])&&lb!=2)return 0;
	if((!a[lb])&&lc-1!=lb)return 0;
	if((!a[lc])&&lc!=len)return 0;
	if((h[lb-1]+query(lb,lc-1))%p!=query(lc,len))return 0;
	return 1;
}
signed main(){
	cin>>(s+1);
	len=strlen(s+1);
	pw[0]=1;
	for(int i=1;i<=len;++i){
		a[i]=s[i]-'0';
		h[i]=(h[i-1]*m%p+a[i])%p;
		pw[i]=pw[i-1]*m%p;
	}
	//hash
	for(int i=1;i<=len;++i){//等号后一个的位置 
		if(1){ 
			//lena=lenc
			int ra=len-i+1;//a的末位 
			if(check(ra+1,i)){
				ans1=i;
				ans2=ra;
				break;			
			}
			//lenb=lenc
			int lb=(i-1)-(len-i);//b的开头
			if(lb>=2&&check(lb,i)){
				ans1=i;
				ans2=lb-1;
				break; 				
			}		
		}
		if(1){
			//lena=lenc-1 
			int ra=len-i;//a的末位 
			if(check(ra+1,i)){
				ans1=i;
				ans2=ra;
				break;
			}
			//lenb=lenc-1
			int lb=(i-1)-(len-i-1);//b的开头
			if(lb>=2&&check(lb,i)){
				ans1=i;
				ans2=lb-1;
				break; 			
			}	
		}
	}
	for(int i=1;i<=ans2;++i)cout<<a[i];
	cout<<"+";
	for(int i=ans2+1;i<=ans1-1;++i)cout<<a[i];
	cout<<"=";
	for(int i=ans1;i<=len;++i)cout<<a[i];
	return 0;
}
//1145141919180

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF898F)

首先考虑加法性质。发现如果确定等式右边的位数，即可确定等号位置，那么加号位置只有四种情况，可以直接 $O(1)$ 枚举得到。于是可以 $O(n)$ 枚举等式右边的位数。

等式是否成立可以直接用 $10$ 进制的哈希实现，显然这样的哈希满足加法性质，于是直接判断即可。

注意到 $hash(l,r)=hash(r)-hash(l-1)base^{r-l+1}$，于是可以 $O(1)$ 判断子串哈希，证明略去。

细节要判断前导零，以及当计算 $hash(l,r)$ 时 $l>r$ 无解的情况。

这题卡掉了许多常规模数，但是如果选择合适的模数还是可以单哈希过。具体模数见讨论区。

时间复杂度 $O(n)$。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
#define ull unsigned long long 
using namespace std;
int read()
{
    int x=0,f=1;
	char ch=getchar();
    while(ch<'0'||ch>'9')
    {
      	if(ch=='-')
      		f=-1;
      	ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
      	x=x*10+ch-'0';
      	ch=getchar();
    }
    back x*f;
}
ll mod=520040527;
char a[2000005];
ll ans[2000005],base[2000005],hashr,hashl1,hashl2,len,lsbl=1;
void hash1()
{
	ans[0]=1,base[0]=1;
	for(ri i=1;i<=len;i++)
	{
		ans[i]=(ans[i-1]*10%mod+a[i]-'0')%mod;
		base[i]=base[i-1]*10%mod;
	}
	back ;
}
ll gethash(int l,int r)
{
	if(l>r||(a[l]=='0'&&l!=r))
		back -1e9;
	back (ans[r]-ans[l-1]*base[r-l+1]%mod+mod)%mod;
}
int zero1(int l,int r)
{
	if(l==r||a[l]!='0')
		back 1;
	back 0;
}
int main()
{
	cin>>a+1;
	len=strlen(a+1);
	hash1();
	for(ri i=len/3;i<=len/2;i++)
	{
		int lenr=len-i+1;
		if(zero1(lenr,len)==0)
			continue;
		hashr=gethash(lenr,len);
		hashl1=gethash(1,i-1),hashl2=gethash(i,lenr-1);
		if((hashl1+hashl2)%mod==hashr)
		{
			for(ri j=1;j<=len;j++)
			{
				cout<<a[j];
				if(j==i-1)
					cout<<"+";
				if(j==lenr-1)
					cout<<"=";
			}
			back 0;
		}
		hashl1=gethash(1,i),hashl2=gethash(i+1,lenr-1);
		if((hashl1+hashl2)%mod==hashr)
		{
			for(ri j=1;j<=len;j++)
			{
				cout<<a[j];
				if(j==i)
					cout<<"+";
				if(j==lenr-1)
					cout<<"=";
			}
			back 0;
		}
		hashl1=gethash(1,lenr-i-1),hashl2=gethash(lenr-i,lenr-1);
		if((hashl1+hashl2)%mod==hashr)
		{
			for(ri j=1;j<=len;j++)
			{
				cout<<a[j];
				if(j==lenr-i-1)
					cout<<"+";
				if(j==lenr-1)
					cout<<"=";
			}
			back 0;
		}
		hashl1=gethash(1,lenr-i),hashl2=gethash(lenr-i+1,lenr-1);
		if((hashl1+hashl2)%mod==hashr)
		{
			for(ri j=1;j<=len;j++)
			{
				cout<<a[j];
				if(j==lenr-i)
					cout<<"+";
				if(j==lenr-1)
					cout<<"=";
			}
			back 0;
		}
	}
	
	back 0;
}
```

---

## 作者：infinities (赞：0)

思路：
考虑到加法只可能为 $(n-1)$ 位或 $n$ 位的数加上另外一个数才能产生 $n$ 位的结果，我们枚举等于号的位置，算出和的位数，然后只有四个可能能放加号的位置，判断即可。

但是发现高精度加法为 $O(n)$，无法胜任 $n \le 10^6$ 的数据范围。于是想到hash，不用高精，只需判一下两个加数的hash值加起来对 $mod$ 取模是否等于和的hash值。

这里快速计算字符串中 $l-r$ 的hash值有两种方法(第二种估计会T)。

1. $O(1)$ 做法，预处理出 $10^i$ 和前缀 $1-i$ 对应的hash值， $\operatorname{hash}(l-r)$ 就等于 $\operatorname{hash}(1-r) - \operatorname{hash}(1-l) * 10^{r - l+1}$。

2. 估计是只有我这种屑才能想到的屑做法。复杂度 $O(\log n)$，维护后缀，$\operatorname{hash}(l-r)$ 就等于 $[\operatorname{hash}(l-n) - \operatorname{hash}(r-n)] / 10^{n - r}$，可以看出要在模意义下做除法，所以需要计算逆元，复杂而且估计会T飞。

注意一些细节：

- hash的base我们取10，可以直接进行加法。

- 注意特判前导零，而且零自己没有前导零。

- 判断加数之和是否等于和以及判断前导零最好单独写两个函数，不然会很乱。

- 记一些知名度低的大质数，这题卡了不少有名的大质数。

- 实在被卡到自闭可以使用双模数，或者用讨论区中某巨佬提供的可以过的大质数。

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define rint register int
const int maxn = 1e6 + 2333;
const int mod = 1126654447;
int read(){
    int x = 0,f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

using std::ios;
using std::cin;
using std::cout;
using std::max;
using std::min;
using std::sort;
using std::unique;
using std::lower_bound;
using std::swap;
using std::abs;
using std::acos;
using std::queue;
using std::map;
using std::string;
char s[maxn];
int base = 10, ba[maxn], sum[maxn], len;
void init(){
	sum[0] = ba[0] = 1;
	for(int i = 1; i <= len; i++)
	    sum[i] = ((sum[i - 1] * base) % mod + s[i] - '0') % mod, ba[i] = (ba[i - 1] * base) % mod;
}
int hash(int l, int r){
	if(l > r || l < 0 || r < 0)return -2147483647;
	return ((sum[r] - (sum[l - 1] * ba[r - l + 1]) % mod) + mod) % mod;
}
bool zero(int l, int r){
	if(s[l] != '0' || r - l + 1 < 2)return 1;
	return 0;
}
bool ch(int l1, int r1, int l2, int r2, int c){
	if((hash(l1, r1) + hash(l2, r2)) % mod == c && zero(l1, r1) && zero(l2, r2))return 1;
	return 0;
}
void print(int l1, int r1, int l2, int r2){
	for(int i = l1; i <= r1; i++)cout << s[i];
    cout << "+";
	for(int i = l2; i <= r2; i++)cout << s[i];
	cout << "=";
	for(int i = r2 + 1; i <= len; i++)cout << s[i];
}
signed main(){
	cin >> s + 1;
	len = strlen(s + 1);
	init();
	for(int i = len / 2; i <= len; i++){
		int n = len - i + 1;
		if(i - n < 0 || !zero(i + 1, n))continue;
		int c = hash(i, len);
		if(ch(1, n - 1, n, i - 1, c)){
			print(1, n - 1, n, i - 1);
			return 0;
		}
		if(ch(1, n, n + 1, i - 1, c)){
			print(1, n, n + 1, i - 1);
			return 0;
		} 
		if(ch(1, i - n - 1, i - n, i - 1, c)){
		    print(1, i - n - 1, i - n, i - 1);
			return 0;
		}
		if(ch(1, i - n, i - n + 1, i - 1, c)){
		    print(1, i - n, i - n + 1, i - 1);
			return 0;
		}
	}
}
```

---

