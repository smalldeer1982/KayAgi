# [ARC159B] GCD Subtraction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc159/tasks/arc159_b

変数 $ a,b $ があり、初め $ a=A,\ b=B $ です。

高橋君は $ a,b $ がともに $ 1 $ 以上の間、次の操作を繰り返すことにしました。

- $ a $ と $ b $ の最大公約数を $ g $ とする。そして、$ a,b $ をそれぞれ $ a-g,b-g $ に置き換える。
 
操作は何回行われますか。

## 说明/提示

### 制約

- $ 1\ \leq\ A,B\ \leq\ 10^{12} $
- $ A,B $ は整数
 
### Sample Explanation 1

$ a=15,b=9 $ の状態から以下のように操作が行われます。 - $ g=3 $ とする。そして、$ a,b $ がそれぞれ $ 12(=15-3),6(=9-3) $ に置き換えられる。 - $ g=6 $ とする。そして、$ a,b $ がそれぞれ $ 6(=12-6),0(=6-6) $ に置き換えられる。$ b $ が $ 1 $ 以上でなくなったため、操作の繰り返しはここで終了する。

## 样例 #1

### 输入

```
15 9```

### 输出

```
2```

## 样例 #2

### 输入

```
1 1```

### 输出

```
1```

## 样例 #3

### 输入

```
12345678910 10987654321```

### 输出

```
36135```

# 题解

## 作者：Daniel_yao (赞：8)


# 题目大意


给出两个整数 $a,b$。当 $a, b$ 均为正数时，重复执行以下操作：

- 令 $g = \gcd(a,b)$。
- $a \to a-g,b \to b-g$。

问将会执行多少次操作？

# 思路点拨

考虑暴力的按照题意模拟，欣喜的发现竟然能过 `12345678910 10987654321` 这组样例，速速交了一发，T 飞了。

hack 样例是 `1000000000 1000000001`，发现每一次操作的 $\gcd$ 都是 $1$，所以每一次只会减 $1$。时间复杂度被卡到了 $O(ans)$，显然过不去。

于是开始在暴力的基础上猛地优化：

对于 $|a-b|=1$ 的情况，每一次操作的 $\gcd$ 都是 $1$，则答案为 $\min(a,b)$。（会减 $\min(a,b)$ 次 $1$，故操作数为 $\min(a,b)$）。

对于 $a=b$ 的情况，$\gcd(a,b)=a$，所以答案为 $1$。

我们可以发现，时间复杂度的瓶颈在于 $a$ 与 $b$ 互质时，每次只会将 $a$ 和 $b$ 减 $1$。考虑将这些减 $1$ 操作合并。令 $x$ 表示 $a$ 与 $b$ 会减 $x$ 次 $1$，就有 $\gcd(a-x,b-x)\ne 1$，且最小化 $x$，我们又令 $d$ 为 $a-x$ 和 $b-x$  的公约数，则：

$a-x \equiv b-x\pmod{d}$

$a \equiv b\pmod{d}$

$d \mid a-b$

于是枚举 $a-b$ 的因子（即 $a$，$b$ 的公约数 $d$），求出最小 $x$ 就行了。

由于 $a-x \equiv0\pmod{d}$，所以 $x \equiv a\pmod{d}$，知道 $d$ 之后可以快速求 $x$。

将减 $1$ 操作合并后，其他的正常跑就行。

时间复杂度 $O(\sqrt n \log n)$。

# 代码实现

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

inline int read() {
  rint x=0,f=1;char ch=getchar();
  while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
  return x*f;
}

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

int a, b, ans; 

void quick(int p) {
  int x = b;
  for (int i = 2; i * i <= p; i++) {
    if(p % i == 0) {
      if(a % i == b % i) x = min(x, a % i);
      if(a % (p / i) == b % (p / i)) x = min(x, a % (p / i));
    }
  }
  if(a % p == b % p) x = min(x, a % p);
  a -= x, b -= x, ans += x;
  return ;
}

signed main() {
  a = read(), b = read();
  while(a && b) {
    if(a < b) swap(a, b);
    int gcd = __gcd(a, b);
    a /= gcd, b /= gcd;
    if(a == 0 || b == 0) break;
    if(a == b) {ans++; break;}
    if(a == b + 1) {ans += b; break;}
    quick(a - b);
  }
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：Xy_top (赞：4)

仅是优化了暴力然后过的，想看正解者可以跳过了。

设 $i$，$j$ 的 $\gcd$ 为 $k$，每次将 $i$，$j$ 都减去 $k$ 其实就相当于把 $i$，$j$ 除以 $k$ 后再减一，容易证明，这不会影响后续的操作和答案。

当 $k>1$ 时，$i$，$j$ 每次都会至少除以 $2$，$\log n$ 次就结束了。

重点是 $k=1$ 时，$i$，$j$ 减了之后 $k>1$ 还行，要是不停地减一，不停地互素，$k=1$ 咋办？此时就需要优化这个方法。

如果我们能找到一个数 $m$ 使得 $i\equiv j(\bmod$ $m)$，那么我们再减去某个数后就会使 $i$ 和 $j$ 能同时被 $m$ 整除了！当然，$m$ 一定大于 $1$。设 $i=k_1m+b_1$，$j=k_2m+b_1$，$b_1$ 一定要最小，这样才是减很多一之后第一个 $\gcd$ 不为 $1$ 的。

如何求得最小的 $b1$ 呢，$i$ 和 $j$ 可能和多个东西同余。不妨设 $i>j$，$i-j$ 得到 $k_1m-k_2m$ 也就是说 $i-j$ 也是 $m$ 的倍数，那么我们枚举 $i-j$ 的因数就可以 $\sqrt{n}$ 处理这个了。

$\log_n$ 次操作结束，所以最终复杂度为 $O(\sqrt{n}\cdot\log n)$。

别忘记开 LL，我的某位同学因为 A 题没开吃了好几次罚时。

冗长的 AC 代码：

```cpp
#include <iostream>
#define int long long
using namespace std;
long long a, b, ans;
long long gcd (long long x, long long y) {
	if (y == 0) return x;
	return gcd (y, x % y);
}
void fun (long long x) {
	long long t = b;
	for (int i = 2; i * i <= x; i ++) {
		if (x % i == 0) {
			if (a % i == b % i) t = min (t, a % i);
			if (a % (x / i) == b % (x / i) ) t = min (t, a % (x / i) );
		}
	}
	if (a % x == b % x) t = min (t, a % x);
	a -= t;
	b -= t;
	ans += t;
}
signed main () {
	cin >> a >> b;
	while (a != 0 && b != 0) {
		if (a < b) swap (a, b);
		int t = gcd (a, b);
		a /= t; b /= t;
		-- a; -- b; ++ ans;
		if (a == 0 || b == 0) break;
		if (a - b == 1) {ans += b; break;}
		if (a == b) {++ ans; break;}
		fun (a - b);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：luxiaomao (赞：3)

## 前言（~~废话~~）

数学题 + 思维题，用来练练手还是不错的。

~~我才不会告诉你我写了好久的证明呢。~~

## 分析

### 题意

题意应该是非常好理解了，

给出两个整数 $a$，$b$。当 $a$，$b$ 均为正数时，重复执行以下操作：

- 令 $g = \gcd(a,b)$。

- $a \to a-g$，$b \to b-g$。

问将会执行多少次操作？

~~对没错我就是照抄题面因为没什么好解释的。~~

### 模拟 $\to$ 优化

首先我想到的就是模拟，迅速敲出代码然后竟然能过样例的大数，可把蒟蒻高兴的。

然而这是道绿题 QAQ。

如果给一个数据类似于 `1000000000 999999999`，你就会发现，如果纯粹模拟的话每次只会减去 $1$ ，你将会收获 `TLE`。。。

那么我们考虑如何快速地求出要减掉几个 $1$ ，然后一次性减掉即可。

就上文所说的情况，有：

$$\gcd(a,b) = 1$$

令 $x$ 为我们要求的次数（减掉多少个 $1$）：

$$\gcd(a-x,b-x) \not= 1$$

令 $c = \gcd(a-x,b-x)$，则有：

$$a-x \equiv b-x \pmod{c}$$

$$a \equiv b \pmod{c}$$

$$(a-b) \bmod c = 0$$

是不是有一点头绪了？（~~感觉没有~~），继续往下：

$$\because a-x \equiv 0 \pmod c $$

$$x\equiv a \pmod c$$

那么式子推到了这里，我们枚举 $c$（其实换个说法，就是 $a-b$ 的因子），然后就可以在极小的常数时间内推出 $x$。

根据题意，减一减到 $\gcd(a,b) \not= 1$ 的时候也就不能减一了，换句话讲，我们求出来的 $x$ 必须是最小值，在枚举 $c$ 的时候记得刷新最小值就可以。

## Code Time

看高清附注释代码 QAQ。

```cpp
#include <bits/stdc++.h>
using namespace std;

long long a, b, ans; //看好数据范围，别忘了开 long long 喔。

void fun(long long x) { //快速减去多个 1。
    long long t = b;
    for (long long i = 2; i * i <= x; i++) {
        if(x % i == 0) {
        if(a % i == b % i) t = min(t, a % i);
        if(a % (x / i) == b % (x / i)) t = min(t, a % (x / i));
        }
    }
    if(a % x == b % x) t = min(t, a % x);
    a -= t, b -= t, ans += t;
    return;
}//一个月前敲的码，一两个变量名可能和数学推导中的不一样，见谅。

int main() {
    scanf("%lld%lld",&a,&b);
    while(a!=0 && b!=0) {
        if(a < b) swap(a, b); //因为刚才推出来的式子会用到 a-b，所以保持 a>b 方便计算。
        long long g = __gcd(a, b); //白嫖 c++ 帮忙写的 gcd 哈哈哈。
        a /= g, b /= g;
        if(a == 0 || b == 0)break;
        if(a == b) //两数相等，直接减为 0，这里特判一下加快速度。
        {
            ans++; 
            break;
        }
        if(a == b + 1) //也是特判加速，如果 a=b+1 说明接下来必须要减 b 次1（有兴趣的同学可以简单证明一下）
        {
            ans += b;
            break;
        }
        fun(a - b);//无法特判，上文数学推导所说的情况
    }
    printf("%lld",ans);
    return 0^_^0;//卖个萌QAQ
}
```

自认为码风还算干净，如果大家有什么不懂的欢迎私信问我。

---

## 作者：DengDuck (赞：3)

首先发现第一个规律，就是互质的两个数字 $a,b$ 问题 $(a,b)$ 的答案和 $(ad,bd)$ 的答案是一样的，当然 $d>0$，为什么呢？

这是因为 $d$ 作为 $a,b$ 的 $\gcd$ 值，后面的过程将一直有 $d|a,d|b$，可以将其看成一个基本单位。

好了现在对于互质的 $a,b$，我们想象一下，在操作中第一个让其 $\gcd$ 不为 $1$ 的 $\gcd$ 为多少？我们设为 $p$。

那么显然有：

$$
a\equiv b\pmod p
$$

我们找到一个最小的 $p$ 即可。

注意，这个 $p$ 总是为质数。

于是我们可以加速这一过程，时间复杂度为 $\mathcal O(n)$ 级别的。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL gcd(LL a,LL b)
{
	if(!b)return a;
	return gcd(b,a%b);
} 
const LL N=2e6;
LL a,b,t,cnt,tot[N+5],f[N+5];
int main()
{
	for(int i=2;i<=N;i++)
	{
		if(!f[i])
		{
			tot[++tot[0]]=i;
		}
		for(int j=1;j<=tot[0]&&tot[j]*i<=N;j++)
		{
			f[tot[j]*i]=1;
			if(i%tot[j]==0)break; 
		}
	}
	cin>>a>>b;
	while(a>0&&b>0)
	{
		do
		{
			t=gcd(a,b);
			a/=t,b/=t;
		}while(t!=1);		
		if(a>b)swap(a,b);
		if(a+1==b)
		{
			cnt+=a;
			break;
		}
		if(a==1)
		{
			cnt++;
			break;
		}
		LL t=b-a;
		for(int i=1;tot[i]*tot[i]<=b&&i<=tot[0];i++)
		{			
			if(b%tot[i]==a%tot[i])
			{
				if(a%t>a%tot[i])t=tot[i];
			}
		}
		cnt+=a%t;
		a-=a%t,b-=b%t;			
	}
	cout<<cnt<<endl;
}
```

---

## 作者：良心WA题人 (赞：2)

## 前言

一开始看错题以为是除去 $\gcd(a,b)$ 然后打暴力白吃罚时。挺难受的，不过题是真的好题。

## 题意

给定 $a,b$，每次操作将 $a$ 替换为 $a-\gcd(a,b)$，$b$ 替换为 $b-\gcd(a,b)$ ，问让 $a$ 和 $b$ 其中一个变为 $0$ 会操作多少次。

## 思路

因为 $\gcd(a,b)=gcd(b,a-b)$，令 $t=|a-b|$，$g=gcd(a,b)$，则 $g\mid t$。而一个很有用的性质是差是不变的。又因为 $g\mid a-g,g\mid b-g$，那么 $g$ 一定只增不减，所以 $g$ 的取值是少于 $d(t)$ 的。现在考虑在什么时候会发生变化，那么就是求最小的 $cnt$，使得 $p\mid t$ 且 $p\nmid g$，有 $cnt\times g\equiv a\mod p$ 。这个可以用扩展欧几里得做。

时间复杂度 $O(\sqrt t\log_2 a)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll exgcd(ll a,ll b,ll&x,ll&y)
{
	if(!b)
	{
		x=1,y=0;
		return a;
	}
	ll g=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return g;
}
ll calc(ll a,ll b,ll p)
{
	ll x,y,g=exgcd(a,p,x,y);
	if(b%g)
		return 1e18;
	x*=b/g;
	p/=g;
	return (x%p+p)%p;
}
int main()
{
	ll a,b;
	scanf("%lld%lld",&a,&b);
	ll ans=0;
	while(a>=1&&b>=1)
	{
		ll t=abs(a-b),g=__gcd(a,b),cnt=min(a,b)/g;
		for(ll i=1;1ll*i*i<=t;i++)
			if(!(t%i))
			{
				if(g%i)
					cnt=min(cnt,calc(g,a%i,i));
				if(g%(t/i))
					cnt=min(cnt,calc(g,a%(t/i),t/i));
			}
		a-=cnt*g,b-=cnt*g;
		ans+=cnt;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：__Aaaaaaaa (赞：1)

题面翻译：给定两个整数 $A$ 和 $B$ ，都小于 $10^{12}$。  
每次将 $A$ 和 $B$ 减去它们当前的最大公约数，求最少多少次后会使其中一个为 $0$。

个人认为评级为绿。  
我的思想比较暴力，有一个读者可以自证~~不难~~的结论：$A$ 和 $B$ 的最大公约数只会逐渐增大，不可能会变小。  
然后又有一个读者可以自证~~不难~~的结论：每次可以在题面所给的操作后增加一个操作——将 $A$ 和 $B$ 同时除以 $(A,B)$，自然地，除了之后 $(A,B)$ 变成了 $1$。这样做可以保证最后的次数等同于题面所询问的次数。  
于是我们就可以每次暴力维护和修改 $A-B$ 的所有约数（个数不会超过 $10^6$），然后暴力找最少 $A$ 和 $B$ 减去几次 $1$ 可以使得它们存在更大的最大公约数，每次除以之后 $A$ 和 $B$ 的差值至少会除以 $2$，这样操作的次数不会超过 $\log_2 {d(A-B)}$ 次，$d(n)$ 表示 $n$ 的约数个数，于是复杂度最坏也就是 $O(d(n) \log_2 {d(A-B)})$。  
### Don't talk much:
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
const ll INF=2e18;
const ll N=3e6+10;
ll gcd(ll a,ll b){
	return b?gcd(b,a-a/b*b):a;
}
ll p[N],a[N];
ll C;
ll f[N];
bool st[N];
ll m,id;
ll ans;
ll A,B;
void dfs(){
	if(A==0||B==0){
		return;
	}
	if(A==A/B*B){
		ans++;
		return;
	}
	ll x=1;
	ll step=INF;
	for(ll i=1;i<=m;i++){
		st[i]=1;
		if(f[i]==1)
			continue;
		if(A-A/f[i]*f[i]<step){
			step=A%f[i];
			x=i;
		}
	}
	if(f[x]==1){
		ans+=B;
		return;
	}
	A-=step,B-=step;
	ll g=gcd(A,B);
	A/=g,B/=g,C/=g;
	for(ll i=1;i<=m;i++){
		if(C!=C/f[i]*f[i]){
			st[i]=0;
		}
	}
	ll backup=m;
	m=0;
	for(ll i=1;i<=backup;i++){
		if(st[i]){
			f[++m]=f[i];
		}
	}
	ans+=step;
	dfs();
}
int main(){
	scanf("%lld%lld",&A,&B);
	if(A<B)swap(A,B);
	C=A-B;
	for(ll i=2;i<=C/i;i++){
		if(C==C/i*i){
			p[++id]=i;
			while(C==C/i*i)
				C/=i,a[id]++;
		}
	}
	if(C>1)p[++id]=C,a[id]=1;
	f[m=1]=1;
	for(ll i=1;i<=id;i++){
		ll backup=m;
		ll pk=1;
		for(ll j=1;j<=a[i];j++){
			pk*=p[i];
			for(ll k=1;k<=backup;k++)
				f[++m]=pk*f[k];
		}
	}
	C=A-B;
	dfs();
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：FyFive (赞：1)

> 题意:
>
>每次操作使得 $a \rightarrow a- \gcd(a,b)$，$b \rightarrow b- >\gcd(a,b)$，问能操作多少次。

一开始打暴力跑样例特别快，以为暴力复杂度是对的，然后直接交暴力发现很快就开始 T 了，不信邪以为是常数问题，知道后来意识到复杂度是 $O(ans)$ 的，很是消愁。

用来卡飞自己的 hack 是 ``100000000000 99999999999``，答案是 ``99999999999``。对于这一组数据，不难发现其实每次减的 $\gcd(a,b)$ 均为同一个值，这让我们联想到，对于答案特别大的数据，必定有相当多个连续段，其中每一次减去的值都相同。

那么不难想到，只需要计算出当前需要减多少次才能让 $a$ 和 $b$ 的 $\gcd$ 发生变化，就可以通过此题了。

记 $c$ 为 $|a-b|$，不难发现 $c$ 的值是始终不会变的。那么，在每一次操作前，使 $a$、$b$ 互质，也就是让 $a$、$b$ 的 $\gcd$ 变成 $1$，就可以得到这样一个性质：
- $a$ 和 $b$ 的 $\gcd$ 变化的时候，就是 $\gcd(b,c)$ 不为 $1$ 的时候。

那么暴力看 $c$ 的约数就行了。

#### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a,b,c,g,ans;
int bel[10005],top;
inline void mins(int x)
{
    top=0;
    for(int i=2;i*i<=x;++i) if(x%i==0) {bel[++top]=i; while(x%i==0) x/=i;}
    if(x!=0) bel[++top]=x;
}
signed main()
{
    cin>>a>>b; if(a<b) swap(a,b); c=a-b;
    if(c==0)
    {
        cout<<1<<endl;
        return 0;
    }
    while(a!=0&&b!=0)
    {
        g=__gcd(a,b);
        a/=g; b/=g; c/=g;
        if(c==1)
        {
            ans+=b;
            b=0;
        }
        mins(c);
        int mxs=0;
        for(int i=1;i<=top;++i) mxs=max(mxs,(b/bel[i])*bel[i]);
        ans+=b-mxs; a-=b-mxs; b=mxs;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：lzqy_ (赞：1)

因为边界情况吃了 $8$ 发罚时。被送走了。


设 $a=k_1g,b=k_2g$，那么单次操作后变成 $a=(k_1-1)g,b=(k_2-1)g$，而 $\gcd(k_1-1,k_2-1)$ 不一定等于 $1$，所以 $g$ 是只增不减的。

又因为每次增加做的是乘法，所以 $g$ 只有 $O(\log n)$ 种取值。考虑一次性对于一个 $g$ 执行完所有操作。


假设对于当前的 $g$ 将 $x$ 次操作，那么有 $\gcd(k_1-i,k_2-i)=1(i<x)$ 且存在 $d$ 满足 $d|k_1-x,d|k_2-x$，即 $k_1\bmod d=k_2 \bmod d=x$。

此时一个关键的观察是将 $k_1,k_2$ 作差后，结果就是 $d$ 的倍数了。所以直接 $O(\sqrt n)$ 暴力枚举 $|k_1-k_2|$ 的差的因子，然后求出最小的 $x$ 即可。

时间复杂度 $O(\sqrt n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
using namespace std;
const int maxn=110;
const ll inf=1ll<<60;
il ll read(){
	ll x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll calc(ll A,ll B){
	if(!A||!B) return 0;
	ll tmp=gcd(A,B); A/=tmp,B/=tmp;
	if(A<=100||B<=100){
		ll sum=0,tmp;
		while(A>=1&&B>=1)
			tmp=gcd(A,B),A-=tmp,B-=tmp,sum++;
		return sum;
	}
	if(abs(A-B)==1) return min(A,B);
	if(abs(A-B)==0) return 1;
	ll x=abs(A-B),qx=sqrt(x),Mn=inf;
	for(int i=1;i<=qx;i++)
		if(x%i==0){
			if(i>1) Mn=min(Mn,min(A,B)%i);
			if(x/i>1) Mn=min(Mn,min(A,B)%(x/i));
		}
//	printf("!!!!%lld\n",Mn);
	return calc(A-Mn,B-Mn)+Mn;
}
int main(){
	ll A=read(),B=read();
	printf("%lld\n",calc(A,B)); 
	return 0;
}

```

---

## 作者：ny_Dacong (赞：0)

# 思路

这道题直接模拟会超时，因为**暴力的时间复杂度与答案挂钩**，如果答案很大就会超时。

比如 `114514191981 1000000009` 这个数据的答案是 `250000003`，一个相当大的结果。这样跑下来时间直接起飞。而样例三 `12345678910 10987654321` 的答案是 `36135`，不算大，所以可以较快地得出结果。

为什么暴力的时间复杂度与答案挂钩呢？我们来分析一下。

设 $p = a \div g,q = b \div g$，因为 $g = \gcd (a,b)$，所以 $p,q$ 均为整数且**互质**。

当进行一次操作之后，$a,b$ 都同时减去了 $g$。也就是说 $a' = (p-1)g,b' = (q-1)g$，

此时 $\gcd (a',b')$ 便有了两种情况：如果 $p-1,q-1$ 仍然互质，那么 $\gcd (a',b') = g$，否则等于 $g \times \gcd (p-1,q-1)$。

假如此时是第一种情况，$g$ 不变，那么 $p,q$ 就会**再减一个** $1$。假如这种互质情况持续了很久，一共持续了 $x$ 次，那么这重复的 $x$ 次就会十分浪费，不如一次计算出 $x$，更省时。

这也是为什么复杂度与答案相关。其原因就在于重复计算了多次相同的情况。

所以当 $\gcd (p,q) = 1$ 时，我们要找到一个**最小的** $x$ 使得 $\gcd (p-x,q-x) \not = 1$。

怎么计算呢？我们设 $d = \gcd (p-x,q-x)$，那么 $p-x \equiv q-x \pmod d$。

继续推式子，得 $p \equiv q \pmod d$，也就是说 $|p-q| \equiv 0 \pmod d$。

也就是说 $d$ 是 $|p-q|$ 的一个因数。因此枚举这个 $d$，就可以求出 $x$，然后记录最小的一个即可。

>为什么要**最小的** $x$？
>
>是因为此时 $p-x,q-x$ 不再互质，那么 $\gcd (a',b')$ 的值就会改变，那么此时需要用新的 $g$ 值来计算。如果用其他的 $x$ 值会产生错误的结果。

# AC 代码

这道题是我的考试题目，考场上思路已经八九不离十了，但是脑子太抽还是写挂了。

感觉写数学题代码最需要脑子。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,ans = 0,Gcd,x;
long long findx(long long x,long long y){
	long long Abs = abs(x-y),res = y;
	for(long long i = 2; i <= Abs/i; i++){
		if(Abs%i == 0){
			if(a%i == b%i){
				res = min(res,a%i);
			}
			if(a%(Abs/i) == b%(Abs/i)){
				res = min(res,a%(Abs/i));
			}
		}
	}
	if(a%Abs == b%Abs){
		res = min(res,a%Abs);
	}
	return res;
}
int main(){
//	freopen("ggcd.in","r",stdin);
//	freopen("ggcd.out","w",stdout);
	scanf("%lld%lld",&a,&b);
	while(a >= 1 && b >= 1){
		if(a < b){
			swap(a,b);
		}
		Gcd = __gcd(a,b);
		a /= Gcd,b /= Gcd;
		if(!a || !b){
			break;
		}
		if(a == b){
			ans++;
			break;
		}
		if(a == b+1){
			ans += b;
			break;
		}
		x = findx(a,b);
		ans += x,a -= x,b -= x;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：_ZSR_ (赞：0)

### [[ARC159B] GCD Subtraction ](https://www.luogu.com.cn/problem/AT_arc159_b)

假设 $a=k_1 \times g,b=k_2 \times g$，减完后 $a$ 变成 $(k_1-1) \times g$，$b$ 变成 $(k_2-1) \times g$，因为 $\gcd(k_1-1,k_2-1)$ 可能不等于 $1$，所以 $g$ 是单调不降的。考虑一个最小的 $x$，使得 $\gcd(k_1-x,k_2-x) \neq 1$。如果我们可以找到这个 $x$，就可以对同一个 $g$ 执行完所有操作。

根据 $x$ 的定义，存在一个 $d$ 使得 $d \mid k_1-x,d \mid k_2-x$，即 $d \mid |k_1-k_2|$。所以可以枚举 $|k_1-k_2|$ 的所有因数，找到最小的 $x$ 即可。

因为一个数的约数最多只有 $\sqrt{n}$ 个，而 $g$ 最多只有 $\log n$ 种取值，所以时间复杂度为 $O(\sqrt{n} \log n)$。

code
```
#include <bits/stdc++.h>
using namespace std;
#define int long long 
int A,B;
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
int calc(int a,int b)
{
    if (!a||!b) return 0;
    int g=gcd(a,b);
    a/=g,b/=g;
    if (abs(a-b)==1) return min(a,b);
    if (abs(a-b)==0) return 1;
    int x=abs(a-b),minn=0x3f3f3f3f;
    for (int i=1;i*i<=x;++i)
    {
        if (x%i==0)
        {
            if (i>1) minn=min(minn,min(a,b)%i);
            if (x/i>1) minn=min(minn,min(a,b)%(x/i));
        }
    }
    return calc(a-minn,b-minn)+minn;
}
signed main()
{
    scanf("%lld%lld",&A,&B);
    printf("%lld\n",calc(A,B));
    return 0;
}
```


---

