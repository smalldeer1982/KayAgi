# 「SWTR-2」Crystal Balls

## 题目背景

$\mathrm{Ethan}$ 有一些可以释放强大能量的水晶球，他将要用这些水晶球合成可以消灭敌人的魔法。

- $a\equiv b\mathrm{\ (mod\ m)}$ 表示 $a$ 和 $b$ 对模 $m$ 同余，即 $(a-b)/m$ 为整数。

## 题目描述

$\mathrm{Ethan}$ 有 $n$ 个水晶球，现在他将这些水晶球排成一行，每一个水晶球上面有一个能量值，且**要么是绿色，要么是紫色**。

- 下文中，$P$ 代表紫色，$G$ 代表绿色。

$\mathrm{Ethan}$ 现在要按以下方式取走这些水晶球：

1. 取走**最左端**的水晶球。

2. 假设取走的水晶球的颜色为 $c_1$，能值为 $x_1$，**剩余最左端**的水晶球的颜色为 $c_2$，能量为 $x_2$，取出水晶的次数为 $cnt$（包括这一次）。

- 如果 $c_1=c_2$，那么 $\mathrm{Ethan}$ 会将这两个水晶球合成为一个大水晶球（本次取出的水晶球仍计入答案总数内，详情见样例），颜色为 $c_1$，能量值为 $x_1 \times x_2$，放在水晶球序列的**最左端**。

- 如果，$c_1=P,c_2=G,cnt\equiv 1\mathrm{\ (mod\ 2)}$，那么 $\mathrm{Ethan}$ 会将剩下的水晶球的**颜色反转**（即绿色变紫色，紫色变绿色）。

- 如果仍不能满足上面的条件，那么 $\mathrm{Ethan}$ 会将剩下的水晶球**序列翻转**。

就这样，直到最后只剩下一个球，此时 $\mathrm{Ethan}$ 会直接取走最后一个球，求取走的水晶球的**能量值之和**。

由于答案很大，请对 $p$ 取模。

## 说明/提示

---

### 样例说明

**样例 $1$：**

$\mathrm{Ethan}$ 首先会取出最左端的水晶球，颜色为 ```G```，答案加上它上面所写上的数字，即 $1$，剩下的水晶球翻转，序列变为 $4\ 3\ 2$ ```GGP```。（因为 $c_1=G,c_2=P$，取出水晶球的次数为奇数，不满足条件 $1,2$，所以序列翻转）。

再取出最左端的水晶球，颜色为 ```G```，答案加上 $4$，接着把剩下来最左端的水晶球与取走的水晶球合并成一个大的水晶球，写上的数字为 $12$，序列变为 $12\ 2$ ```GP```。

取出最左边的水晶球，颜色为 ```G```，答案加上 $12$，剩下的水晶球序列翻转，序列变为 $2$ ```P```。

取出最后一个的水晶球，答案加上 $2$，最终答案为 $1+4+12+2=19$。

**样例 $2$：**

先取出 $3$，$c_1=P,c_2=G,cnt=1$，颜色翻转

取出 $7$，$c_2=c_3=P$，将 $x_3$ 乘上 $x_2$，得到 $x_3=35$

取出 $35$，最终答案为 $3+7+35=45$

---

### 数据范围与约定

本题采用 $\mathrm{Subtask}$ 制。

$\mathrm{Subtask}\ 1:n\leq 2000,a_i\leq 10^9,p\leq 10^9,15\%$。

$\mathrm{Subtask}\ 2:n\leq 5\times 10^4,a_i\leq 10^9,p\leq 10^9,15\%$。

$\mathrm{Subtask}\ 3:n\leq 5\times 10^4,a_i\leq 10^{18},p\leq 10^{18},20\%$。

$\mathrm{Subtask}\ 4:n\leq 10^6,a_i\leq 10^9,p\leq 10^9,20\%$。

$\mathrm{Subtask}\ 5:n\leq 10^6,a_i\leq 10^{18},p\leq 10^{18},30\%$。

---

对于所有测试点，时间限制 $1s$，空间限制 $16MB$。

## 样例 #1

### 输入

```
4 998244353
1 2 3 4
GPGG```

### 输出

```
19```

## 样例 #2

### 输入

```
3 998244353
3 7 5
PGG```

### 输出

```
45```

## 样例 #3

### 输入

```
10 998244353
12345 23456 34567 45678 56789 67890 78901 89012 90123 101234
GPPGPGGGPG```

### 输出

```
104157290```

# 题解

## 作者：Alex_Wei (赞：5)

$\color{#00ff00}T2.\ Crystal\ Balls$

[$\color{#00ff00}\text{题面}$](https://www.luogu.org/problem/P5672)

$\color{#00ff00}\text{官方题解}$

---

本来想开 $300ms$ 时限卡掉 $\log$ 快速乘和 $\mathrm{cin}$ 的，后来一想**做人不能像 $\mathrm{CSP-S\ D1T3}$ 出题人一样毒瘤，于是开大了时限**

~~让我们一起赞美良心出题人吧！~~

本题主要考察的是快速乘（因为两个 $\mathrm{long\ long}$ 相乘会溢出）和~~带有技巧的~~暴力

暴力分：$15\%$

---

- 如何表示颜色反转？

用一个变量 $(mask)$ 表示当前序列颜色是否反转 $(0=N,1=Y)$，初始值为 $0$

如果颜色反转，就将 $mask$ 异或 $1$（即 $0$ 变为 $1$，$1$ 变为 $0$） 即可

---

- 如何表示这个序列？

用两个变量 $(head,tail)$ 表示当前序列的首和尾，初始值分别为 $1,n$

再用一个变量 $(dir)$ 表示当前的方向，初始值为 $1$

每次从序列里面取出水晶球，就将 $head$ 加上 $dir$

如果序列翻转，就将 $head,tail$ 互换，$dir=-dir$（即 $1$ 变为 $-1$，$-1$ 变为 $1$）

---

有意思的是，这并不是原来的题面

在一次巧合中，出题人们发现了：在原来的题意下，最多只会有 $2$ 次翻转

然后我们紧急修改了题面

~~让我们一起赞美良心出题人吧！~~

---

代码：最慢的一个测试点约 $150ms$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
inline ll read()
{
	ll x=0,sign=1;char s=getchar();
	while(!isdigit(s)){if(s=='-')sign=-1;s=getchar();}
	while(isdigit(s))x=(x<<1)+(x<<3)+(s^48),s=getchar();
	return x*sign;
}
inline void print(ll x)
{
	if(x<10)putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
const int N=1e6+5;
ll n,mod,a[N],ans;
int head,tail,mask,dir=1;
char s[N];
inline void mult(ll &x,ll y){x=(x*y-(ll)((ld)x/mod*y)*mod+mod)%mod;}
inline void add(ll &x,ll y){x=(x+y)%mod;}
bool id(char x){return x=='G';}
int main()
{
	n=read(),mod=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	scanf("%s",s+1);
	head=1,tail=n;
	for(int i=1;i<n;i++){
		add(ans,a[head]);
		ll c1=id(s[head])^mask,c2=id(s[head+dir])^mask;
		if(c1==c2){
			mult(a[head+dir],a[head]);
			head+=dir;
		}
		else if(c1==0&&c2==1&&i%2){
			mask^=1;
			head+=dir;
		}
		else{
			head+=dir;
			dir=-dir;
			swap(head,tail);
		}
	}
	add(ans,a[head]);
	print(ans);
	return 0;
}
```

---

## 作者：mlvx (赞：4)

~~随机跳题随到了，看见题解区还有位，顺手来站个坑。~~

首先看数据范围，$n\le10^6$，暴力模拟是 $O(n^2)$ 的，会超时。

---

观察三种操作：

1. $c_1=c_2$，合并两个球。

2. $c_1=\texttt{P},c_2=\texttt{G},cnt\equiv1\pmod2$，将颜色翻转。

3. 不满足上述操作，翻转序列。

---

对于第一个操作，直接判断即可。

若当前取走的是 $i$ 号球，则 $a_{i+1}\gets a_i\times a_{i+1}$。

注意 $p\le10^{18}$，乘起来再模会爆，可以使用 `__int128`，也可以快速乘。

---

对于第二个操作，我们可以开一个标记变量，记为 $flag$，表示颜色是否翻转过。

若 $flag=0$，第二个操作的条件为 $c_1=\texttt{P},c_2=\texttt{G},cnt\equiv1\pmod2$；若 $flag=1$，第二个操作的条件为 $c_1=\texttt{G},c_2=\texttt{P},cnt\equiv1\pmod2$。

颜色翻转对于第一个操作并没有影响，因为颜色相同的球不管怎么翻转还是颜色相同的。

---

对于第三个操作，我们可以不翻转数组，类似双指针，直接开两个变量 $l,r$，再开一个变量 $rev$，表示是否翻转。

若需要翻转，则从 $r$ 开始向左操作；否则从 $l$ 开始向右操作。

直到 $l=r$ 时跳出循环，再将答案加上 $a_l$ 即可。

---

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e6+100;
int n,flag,rev,cnt,l,r;ll mod,ans,a[N];char c[N];//flag 表示颜色是否翻转，cnt 表示操作次数
int main(){
	cin>>n>>mod,l=1,r=n;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),a[i]%=mod;
	scanf("%s",c+1);
	while(l<r){
		cnt++;
		if(rev){//翻转过
			ans=(ans+a[r])%mod;//记录答案 
			if(c[r]==c[r-1])a[r-1]=(__int128)a[r]*a[r-1]%mod;
			else if((cnt&1)&&(!flag&&c[r]=='P'&&c[r-1]=='G'||flag&&c[r]=='G'&&c[r-1]=='P'))flag^=1;//颜色翻转
			else rev^=1;//序列翻转
			a[r--]=0;//被拿走
		}else{//未翻转
			ans=(ans+a[l])%mod;//记录答案
			if(c[l]==c[l+1])a[l+1]=(__int128)a[l]*a[l+1]%mod;
			else if((cnt&1)&&(!flag&&c[l]=='P'&&c[l+1]=='G'||flag&&c[l]=='G'&&c[l+1]=='P'))flag^=1;//颜色翻转
			else rev^=1;//序列翻转
			a[l++]=0;//被拿走
		} 
	}return cout<<(ans+a[l])%mod,0;//最后记得要模
}
```

---

## 作者：pomelo_nene (赞：3)

$\ \ \ \ \ \ \ $表示做这道题做的心态爆炸，开始交了个高精上去然后挂了0分，后面有巨佬提醒我快速乘，但是我没信。。。

---

## 题目分析

$\ \ \ \ \ \ \ $看见$n \leq 10^6$，估摸着不是dp就是贪心，但是仔细一看，它的序列一直都在按照一个规则进行删去，除去打表找规律，我们发现这就是一道模拟

$\ \ \ \ \ \ \ $所以说我们就开始打模拟

---

## 题目解决 || 心路历程

- $0$分

$\ \ \ \ \ \ \ $交了个高精上去，结果没发现直接是开$10^6$个vector，MLE爆零

- $15\&30$分

$\ \ \ \ \ \ \ $拿不到满分，于是把它开到$40\%$的数据点，然后太慢T爆了，稍微改了下常数然后就行了

- $50$分做法1

$\ \ \ \ \ \ \ $我们发现因为我们的高精过于垃圾，所以说我们不如不打高精

$\ \ \ \ \ \ \ $直接模拟，代码如下

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<queue>
#include<set>
#define mp make_pair
using namespace std;
typedef pair<long long,char> Crystal;
long long n,p,cnt;
long long ans; 
long long a[1000005];
char str[1000005];
deque<Crystal> DQ;
int main(){
//	freopen("新建文本文档.txt","r",stdin);
//	freopen("asf.out","w",stdout);
	scanf("%lld %lld",&n,&p);
	for(long long i=1;i<=n;++i)	scanf("%lld",&a[i]),a[i]%=p;
	cin>>str+1;
//	for(long long i=1;i<=n;++i)	DQ.push_back(mp(a[i],str[i]));
	bool fw=true,colornormal=true;
	int l=1,r=n;
	while(l<r)
	{
		++cnt;
		if(fw)
		{
			Crystal now=mp(a[l],str[l]);
			ans+=a[l];
			ans%=p;
			++l;
			Crystal asf=mp(a[l],str[l]);
			if(now.second==asf.second)
			{
				a[l]=now.first*asf.first%p;
				str[l]=str[l-1];
			}
			else
			{
				if(colornormal)
				{
					if(!(cnt&1))	fw=!fw;
					else if(now.second=='P' && asf.second=='G' && cnt&1)	colornormal=!colornormal;
					else	fw=!fw;
				}
				else
				{
					if(!(cnt&1))	fw=!fw;
					else if(now.second=='G' && asf.second=='P' && cnt&1)	colornormal=!colornormal;
					else	fw=!fw;
				}
			}
		}
		else
		{
			Crystal now=mp(a[r],str[r]);
			ans+=a[r];
			ans%=p;
			--r;
			Crystal asf=mp(a[r],str[r]);
			if(now.second==asf.second)
			{
				a[r]=a[r]*a[r+1]%p;
				str[r]=str[r+1];
			}
			else
			{
				if(colornormal)
				{
					if(!(cnt&1))	fw=!fw;
					else if(now.second=='P' && asf.second=='G' && cnt&1)	colornormal=!colornormal;
					else	fw=!fw;
				}
				else
				{
					if(!(cnt&1))	fw=!fw;
					else if(now.second=='G' && asf.second=='P' && cnt&1)	colornormal=!colornormal;
					else	fw=!fw;
				}
			}
		}
	}
	ans+=a[l];
	ans%=p;
	printf("%lld\n",ans);
	return 0;
}
```

- $50$分做法2

$\ \ \ \ \ \ \ $我们发现我们还没用__int128。。。。

- 满分做法

$\ \ \ \ \ \ \ $我们发现程序MLE和TLE的最关键是我们的高精空间太大/跑得太慢

$\ \ \ \ \ \ \ $对于我们程序的瓶颈就在于乘法这个阶段

$\ \ \ \ \ \ \ $其实我们有快速幂，也有快速乘，原理也是一样的，拆分成二进制，每次修改，详细可见代码（其实就是把乘改成加法）

$\ \ \ \ \ \ \ $对于其他的小细节：

> - 我们存一个翻转，用一个bool就完了，若为true则从左边，否则从右边

> - 存下序列用数组，开两个指针l，r

> - 存颜色翻转类似

于是这就是一道玄学题了

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<queue>
#include<set>
#define mp make_pair
using namespace std;
typedef pair<long long,char> Crystal;
long long n,p,cnt;
long long ans; 
long long a[1000005];
char str[1000005];
deque<Crystal> DQ;
long long QuickMultiplication(long long x,long long p,long long mod)
{
	long long res=0,base=x;
	while(p)
	{
		if(p&1)	res=(res+base)%mod;
		p>>=1;
		base=(base+base)%mod;
	}
	return res%mod;
}
int main(){
//	freopen("新建文本文档.txt","r",stdin);
//	freopen("asf.out","w",stdout);
	scanf("%lld %lld",&n,&p);
	for(long long i=1;i<=n;++i)	scanf("%lld",&a[i]),a[i]%=p;
	scanf("%s",str+1);
//	for(long long i=1;i<=n;++i)	DQ.push_back(mp(a[i],str[i]));
	bool fw=true,colornormal=true;
	int l=1,r=n;
	while(l<r)
	{
		++cnt;
		if(fw)
		{
			Crystal now=mp(a[l],str[l]);
			ans+=a[l];
			ans%=p;
			++l;
			Crystal asf=mp(a[l],str[l]);
			if(now.second==asf.second)
			{
				a[l]=QuickMultiplication(now.first,asf.first,p);
				str[l]=str[l-1];
			}
			else
			{
				if(colornormal)
				{
					if(!(cnt&1))	fw=!fw;
					else if(now.second=='P' && asf.second=='G' && cnt&1)	colornormal=!colornormal;
					else	fw=!fw;
				}
				else
				{
					if(!(cnt&1))	fw=!fw;
					else if(now.second=='G' && asf.second=='P' && cnt&1)	colornormal=!colornormal;
					else	fw=!fw;
				}
			}
		}
		else
		{
			Crystal now=mp(a[r],str[r]);
			ans+=a[r];
			ans%=p;
			--r;
			Crystal asf=mp(a[r],str[r]);
			if(now.second==asf.second)
			{
				a[r]=QuickMultiplication(a[r],a[r+1],p);
				str[r]=str[r+1];
			}
			else
			{
				if(colornormal)
				{
					if(!(cnt&1))	fw=!fw;
					else if(now.second=='P' && asf.second=='G' && cnt&1)	colornormal=!colornormal;
					else	fw=!fw;
				}
				else
				{
					if(!(cnt&1))	fw=!fw;
					else if(now.second=='G' && asf.second=='P' && cnt&1)	colornormal=!colornormal;
					else	fw=!fw;
				}
			}
		}
	}
	ans+=a[l];
	ans%=p;
	printf("%lld\n",ans);
	return 0;
}
```

$\ \ \ \ \ \ \ $

---

## 作者：3ksc03_is_sb (赞：0)

[传送门](https://www.luogu.com.cn/problem/P5672)  
## 题目大意
有四种操作：  
1. 每次从最左边拿一个球，$sum$ 加上 $x1$
2. 如果 $c1=c2$ 则 $x2$ 加上 $x1$
3. 如果 $c1=P$ 且 $c2=G$ 且 $cnt \bmod 2=1$，则颜色反转(如果是 $P$ 就变成 $G$，如果是 $G$ 就变成 $P$)。
4. 否则序列反转

## 思路
首先第一眼看上去是模拟，但看见 $n\le10^6$ 之后，我就发现这 $O(n^2)$ 的模拟一定会超时。  
然后当我看到序列反转时，就萌生起了双指针的念头：$l$ 为左指针，$r$ 为右指针。  
但有了这个还不够，我们会发现合并时会有乘法。这个如果用普通乘法会爆，用高精度会 TLE 。所以我们会有一个新的东东：快速乘！！！模板如下：  
```cpp
ll fastm(ll a,ll b){
	ll c=(ld)a/mod*b;
	ll res=(ull)a*b-(ull)c*mod;
	return res;
}
```
看到这份代码有没有感到十分奇怪？ 它中间是直接用了乘法操作的啊！这不直接爆掉了吗？

但是它就是可以算出正确答案来。因为它其实很巧妙的运用了自动溢出这个操作，我们的代码中的 $c$ 就表示 $\lfloor
 a\times b\div mod\rfloor$，所以我们要求的就变成了  $a\times b-\lfloor a\times b\div mod\rfloor\times mod$，虽然这两个部分都是会溢出的，但（unsigned）保证了它们溢出后的差值基本不变，所以即使它会溢出也不会影响最终结果的！   
## 代码 
关键的都在注释里了。  
```cpp
#include<bits/stdc++.h>//万能头
#define ll long long
#define ld long double
#define ull unsigned long long
#define I return 
#define love 0
#define Lougu ;
using namespace std;
ll n,mod;
ll a[1000001];
string s;
ll sum;
ll fastm(ll a,ll b){
	ll c=(ld)a/mod*b;
	ll res=(ull)a*b-(ull)c*mod;
	return res;
}//快速乘
int main(){
	cin>>n>>mod;
	for(int i=0;i<n;i++) cin>>a[i];//注意，下表从0开始
	cin>>s;
	ll l=0,r=n-1,c=0,f=1,c1=0,c2=0;
	//c为是否颜色反转，0为否。c1表示第一个球的颜色，c2表示第二个球的颜色，f表示序列遍历方向
	for(int i=1;i<=n;i++){
		sum+=a[l];//拿出第一个
		sum%=mod;
		if(c==0){//未反转前
			c1=s[l]=='G'?0:1;
			c2=s[l+f]=='G'?0:1;
		}
		if(c==1){//反转后
			c1=s[l]=='P'?0:1;
			c2=s[l+f]=='P'?0:1;
		}
		if(c1==c2) {
			a[l+f]=fastm(a[l+f],a[l]);
			l=l+f;
		} //合并
		else if(c1==1&&c2==0&&i%2==1) {
			c^=1;
			l=l+f;
		} //改颜色
		else {
			l=l+f;
			swap(l,r);
			f=-f;
		}//改序列遍历方向（反转）
	}
	cout<<sum;//输出
	I love Lougu//华丽结尾
}
```

---

## 作者：Lcm_simida (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P5672)

大体思路：

对于本题的三种情况，我们可以用以下方法解决。

第一种我们可以直接判断 $b[num]$ 和 $b[i]$ 是否相等。

而对于第二种情况反转颜色的问题，我们不可能用枚举来改变颜色，这样肯定超时，因此我们可以使用变量 $f2$ 来判断现在是否反转，因每反转两次就相当于没有翻转。

对于第三种情况，我们可以使用双指针加用 $f1$ 标记现在是从左边还是右边取，这样便可以解决。

## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
long long n,a[1000100];
int b[1000100];
long long P,f1=0,f2=0,ans=0,cnt=0,l,r,x;
int main(){
	ios::sync_with_stdio(0);cin.tie(),cout.tie();
	cin>>n>>P;
	for(int i=1;i<=n;i++){//读入
		cin>>x;
		a[i]=x%P;
	}
	cin>>s;
	s=' '+s;
	for(int i=1;i<=n;i++){
		if(s[i]=='G') b[i]=0;//转成 0 1 形式，方便标记
		else b[i]=1;
	}
	l=1,r=n;
	while(l<r){
		if(f1==0){//没被标记
			int num=l;
			ans=((__int128)ans+a[num])%P;
			cnt=cnt^1;
			l++;
			if(b[num]==b[l]){
				a[l]=((__int128)a[l]*a[num]%P+P)%P;//转__int128
			}else if(((b[num]+f2)%2==1)&&((b[l]+f2)%2==0)&&cnt%2==1){
				f2++;
			}else{
				f1^=1;
			}
		}else{//被标记
			int num=r;
			ans=(((__int128)ans+a[num])%P+P)%P;
			cnt=cnt^1;
			r--;
			if(b[num]==b[r]){
				a[r]=((__int128)a[r]*a[num]%P+P)%P;//转__int128
			}else if(((b[num]+f2)%2==1)&&((b[r]+f2)%2==0)&&cnt%2==1){
				f2++;
			}else{
				f1^=1;
			}
		}
		f2=f2%2;
//		cout<<ans<<" "<<l<<" "<<r<<"\n";
	}
	cout<<(ans+a[l]+P)%P;
	return 0;
}

```

---

## 作者：syr1125 (赞：0)

### v1.0

# -0x3f 扯淡
~~毒瘤~~小清新模拟题。

# 0x00 准备

你要知道以下知识点：

+ [快速乘](https://blog.csdn.net/weixin_60536621/article/details/121193239?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522170497693016800213067131%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=170497693016800213067131&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-121193239-null-null.142^v99^pc_search_result_base3&utm_term=%E5%BF%AB%E9%80%9F%E4%B9%98&spm=1018.2226.3001.4187)

# 0x01 分析

题意很清楚，就不解释了。

我们维护一个 **head** 和一个 **tail**，用于记录水晶球序列的头和尾。

显然，当 $head = tail$ 时，取出最后一个球，并输出答案。

### 操作一：合并

需要用到快速乘，用合并出的球替换**现在序列**最左端的球。

### 操作二：颜色反转

用一个变量记录颜色是否反转，如果反转则所有判断反转即可

### 操作三：序列反转

用一个变量记录序列是否反转，如果反转改为从 tail 操作。

# 0x02 代码 + 解析

模拟题的难点不在于思路，而在于代码。

```cpp
#include <bits/stdc++.h>
#define int long long //别忘了开 long long 
using namespace std;

//定义 
int n, mod, a[1000005];
char color[1000005];

int qkml(int a, int b, int p) //快速乘 (QuicK MuLtiply) 
{
	if (b == 0) return 0;
	int r = qkml(a, b / 2, p);
	r = (r + r) % p;
	if (b % 2) r = (r + a) % p;
	return r;
}

int add(int a, int b) //相加也不要忘了取模 
{
	return (a % mod + b % mod) % mod;
}

signed main()
{
	string s;
	ios::sync_with_stdio(false); //关掉流通步 
	cin >> n >> mod;
	for (int i = 1; i <= n; i ++) cin >> a[i];
	cin >> s;
	for (int i = 1; i <= n; i ++) color[i] = s[i - 1];
	
	int head = 1, tail = n, cnt = 0, ans = 0;
	bool clr = false, rvs = false; //颜色是否反转 (CoLoR), 序列是否反转 (ReVerSe) 
	while (head <= tail)
	{
		cnt ++; //cnt 先 ++ 
		if (tail == head)
		{
			ans = add(ans, a[head]);
			cout << ans;
			return 0; //好习惯在这里 
		}
		if (!rvs)
		{
			ans = add(ans, a[head]);
			if (color[head] == color[head + 1]) a[head + 1] = qkml(a[head], a[head + 1], mod), head ++;
			//不能写成 a[++ head] = qkml(a[head], a[head - 1], mod)，原因见下 
			else if (color[head] == 'P' && color[head + 1] == 'G' && cnt % 2 == 1 && !clr) clr = true, head ++;
			else if (color[head] == 'G' && color[head + 1] == 'P' && cnt % 2 == 1 && clr) clr = false, head ++;
			else rvs = true, head ++;
		}
		else
		{
			ans = add(ans, a[tail]);
			if (color[tail] == color[tail - 1]) a[tail - 1] = qkml(a[tail], a[tail - 1], mod), tail --;
			else if (color[tail] == 'P' && color[tail - 1] == 'G' && cnt % 2 == 1 && !clr) clr = true, tail --;
			else if (color[tail] == 'G' && color[tail - 1] == 'P' && cnt % 2 == 1 && clr) clr = false, tail --;
			else rvs = false, tail --;
		}
	}
	//不需要好习惯了，知道为什么吗？ 
}
```

[更高的代码可读性](https://www.luogu.com.cn/paste/b7ciy4y9)

# 0x3f 坑点
首先，合并**不能**写成 ```a[++ head] = qkml(a[head], a[head - 1], mod)```，因为 **=** 是按从右往左的运算顺序结合的，应改为 ```a[++ head] = qkml(a[head], a[head + 1], mod);```

其他坑点：

+ 开 long long
+ 关流通步，或用 scanf
+ 每一次运算都要取模

## update
无

---

## 作者：ni_ju_ge (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P5672)
## 题意
给定一个长度为 $n$ 的排列，每项又分为 $P$ 和 $G$ 两种类型，每次取出最左端的一个数，将它加到 $s$ 中，记此项类型为 $c_1$，剩余最左项的类型为 $c_2$，操作次数为 $cnt$。

 - 若 $c_1 = c_2$，那么将剩余最左端的数替换为两个数的乘积。
 - 若 $c_1 = P,c_2 = G,cnt \bmod 2 = 1$，那么将剩余项的类型取反。
 - 否则就将剩余项的顺序倒转。

求 $s$ 对 $p$ 取余的值。

## 思路
因为 $n$ 的范围很大，所以暴力修改必定超时，因此需要对三种修改分别考虑：
 - 第一种情况，暴力修改即可，但 $a_i$ 在 $10^{18}$ 的范围中，会爆 long long，需要使用快速乘。
 - 第二种情况，发现一共只有两种颜色，考虑用 $t$ 来表示是否需要取反，每一次取反操作就改变一次 $t$。
 - 第三种情况，发现调换整个序列其实就是换成另一边开始取球，可以使用 $l,r$ 来表示两个端点，使用 $k$ 来表示方向，每次执行此操作就交换 $l,r$ 并将 $k$ 取反，此时，$l$ 就为题面中的 $c_1$ 对应的水晶球，$l+k$ 就是题面中的 $c_2$ 对应的水晶球。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
long long a[1000001],l,r,t,x,y,n,k,s,p;
string str;
void qmult(long long &c1,long long c2) {//快速乘模版 
	c1=(c1*c2-(long long)((long double)c1/p*c2)*p+p)%p;
}
int main() {
	cin>>n>>p;
	for(int i=0; i<n; i++)cin>>a[i];
	cin>>str;
	l=0;//左端点 
	r=n-1;//右端点 
	k=1;
	t=0;
	for(int i=1; i<=n; i++) {
		s+=a[l];
		s%=p;
		if(t==0) {//不取反 
			if(str[l]=='G')x=0;
			else x=1;
			if(str[l+k]=='G')y=0;
			else y=1;
		}
		if(t==1) {//取反 
			if(str[l]=='G')x=1;
			else x=0;
			if(str[l+k]=='G')y=1;
			else y=0;
		}
		if(x==y) {
			qmult(a[l+k],a[l]);
			l=l+k;
		} else if(x==1&&y==0&&i%2==1) {
			t^=1;
			l=l+k;
		} else {
			l=l+k;
			swap(l,r);
			k=-k;
		}
	}
	cout<<s;
}
```

---

