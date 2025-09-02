# [CERC2019] Zeldain Garden

## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[Zeldain Garden](https://contest.felk.cvut.cz/19cerc/solved/garden.pdf)」**

## 题目描述

Boris 是 Rock Anywhere Transport（RAT）公司的首席执行官，该公司专门支持音乐产业。特别是，他们为许多流行的摇滚乐队提供折扣运输。这一次，Boris 不得不将大量优质的墨西哥音乐会扬声器从北海港口转移到遥远的内陆首都。由于预计收货量很大，Boris 不得不组织多辆卡车以确保运输顺畅。运送货物通过该国的众多卡车被称为车队。

Boris 希望通过一个车队一次性运输所有货物，一个扬声器都不留下。欧盟的严格规定要求，在大规模运输音频技术设备的情况下，车队中的所有卡车必须携带完全相同数量的设备。

为了满足所有规定，Boris 希望提前做一些计划，尽管他还不知道扬声器的确切数量，这对车队中卡车的数量和容量的选择有很大影响。为了检查各种情况，对于每个可能的容货量，Boris 计算出所谓的“可变性”，即在不违反规定的情况下，可以为该容货量创建的不同车队的数量。如果两个车队由不同数量的卡车组成，那么它们就不同了。

例如，$6$ 个扬声器货物的可变性为 $4$，因为它们可以均匀地分为 $1$、$2$、$3$ 或 $6$ 辆卡车。

### 简要题意

给定 $l,r$，求 $l\sim r$ 中所有数的因数个数之和。

## 样例 #1

### 输入

```
2 5
```

### 输出

```
9
```

## 样例 #2

### 输入

```
12 12
```

### 输出

```
6
```

## 样例 #3

### 输入

```
555 666
```

### 输出

```
852```

# 题解

## 作者：zhuweiqi (赞：8)

一眼数论题。

观察到数据范围是 $m\leq 10^{12}$，因此我们需要使用 $O(\sqrt{m})$ 及以下时间复杂度的做法才能通过，首先考虑 $O(m)$ 的筛倍数法，即枚举每个因数 $i$，找到最小的 $L$ 和 $R$ 使得 $n\leq i\times L$ 并且 $i\times R\leq m$，这意味着范围内一共有 $R-L+1$ 个数有 $i$ 这个因数，然后考虑优化，我们在枚举因数 $i$ 的时候可以顺便把 $L$ 至 $R$ 范围内的所有正整数也当成因数把贡献值加上，这样一来，由于约数总是成对出现的，我们只需要枚举所有不大于 $\sqrt{m}$ 的因数，那些大于 $\sqrt{m}$ 的因数就自然而然地也会被筛一遍了，我们的时间复杂度就可以降为 $O(\sqrt{m})$ 了，考虑到当 $x$ 是完全平方数时因数 $\sqrt{x}$ 会被重复计算两次，故我们需要将贡献值减去范围内的完全平方数的个数。参考代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	ll l,r,L,R,ans=0;
	scanf("%lld%lld",&l,&r);
	for(ll i=1;i*i<=r;i++) if(i*i>=l) ans--;
	for(ll i=1;i*i<=r;i++){
		l=max(l,i*i);
		L=(l+i-1)/i;
		R=r/i;
		if(L<=R) ans+=(R-L+1)<<1;
	}
	printf("%lld",ans);
    return 0;
}
```

---

## 作者：hjqhs (赞：2)

一眼丁真，鉴定为玩原神玩的。  
记 $f(x)$ 为 $[1,x]$ 中 $x$ 的因数数量。题目就是求 $f(y)-f(x-1)$。由于 $1 \le N \le M \le 10^{12}$，所以线性做法会超时。我们知道 $f(x)=\sum_{i=1}^{x} \frac{x}{i}$，我们意识到，对于一些连贯的 $i$，$\frac{x}{i}$ 的值是一样的！比如 $m=8$ 时，$i=5,6,7,8$ 时 $\frac{x}{i}$ 是一样的，所以我们在我们线性做法的基础上，找到一个 $\frac{x}{i}$ 值直接将指针指向下一个 $\frac{x}{i}$ 值不同的位置上，然后继续遍历即可。
```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=b;i>=a;--i)
#define pv(i,p) for(int i=0;i<p.size();++i)
#define ptc putchar
#define il inline
#define reg register
// #define push_back pb
#define mp make_pair
#define eb emplace_back
// #define ret; return 0;
using namespace std;
const int N=100005;
const int MOD=998244353;
const int INF=0x3f3f3f3f;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
int Max(int a,int b){return a>b?a:b;}
int MAX(int a,int b,int c){return Max(a,Max(b,c));}
int Min(int a,int b){return a<b?a:b;}
int MIN(int a,int b,int c){return Min(a,Min(b,c));}
void Swap(int&a,int&b){int tmp=a;a=b;b=tmp;}
int read(){
  int x=0,f=1;
  char ch=getchar();
  while(ch<'0'||ch>'9'){
    if(ch=='-')f=-1;
    ch=getchar();
  }
  while(ch>='0'&&ch<='9'){
    x=(x<<3)+(x<<1)+(ch^48);
    ch=getchar();
  }
  return x*f;
}
int x,y;
int solve(int n){
  int res=0;
  for(int l=1,r;l<=n;l=r+1){
    r=n/(n/l);
    res+=(n/l*(r-l+1));
  }
  return res;
}
void solve(){
  cin>>x>>y;
  cout<<solve(y)-solve(x-1);
}
signed main(){
  // freopen(,,stdin);
  // freopen(,,stdout);
  ios::sync_with_stdio(0);
  cin.tie(0);
  solve();
  return 0;
}
```

---

## 作者：jqQt0220 (赞：1)

upd 2023.9.28：增加对公式的推导过程。

------

乍一看似乎不是很难，第一眼就想到用分解质因数法。我们先知道一个数分解质因数成了：
$$a_1^{p_1}\cdot a_2^{p_2}\cdot a_3^{p_3}\cdot\ \dots\ \cdot a_n^{p_n}$$
根据奥数老师教的选择等于次方加一，这个数的因数个数就是：
$$(p_1+1)(p_2+1)(p_3+1)\dots(p_n+1)$$
但是一看数据范围：$1\le N\le M\le 10^{12}$，明显不行。

于是转化一下思维，我们可以考虑 $1\sim n$ 中某个数的贡献，即 $1\sim n$ 中有多少数有 $i$ 这个因子，也就是 $1\sim n$ 中有多少 $i$ 的倍数，这个值就是 $\left\lfloor\dfrac{n}{i}\right\rfloor$。于是就有了求 $1\sim n$ 所有数因数之和的公式：
$$\sum_{i=1}^{n}\left\lfloor\dfrac{n}{i}\right\rfloor$$

然而这是线性复杂度，$10^{12}$ 的数据范围直接一个个算肯定会炸，所以我们要优化。

不难发现，一些区间里的 $\left\lfloor\dfrac{n}{i}\right\rfloor$ 的值是相等的。那么如果区间左端点为 $i$，相应的贡献值即为 $\left\lfloor\dfrac{n}{i}\right\rfloor$，右端点就是 $\left\lfloor\dfrac{n}{\left\lfloor\dfrac{n}{i}\right\rfloor}\right\rfloor=j$（很好理解，就是求出贡献值为 $\left\lfloor\dfrac{n}{i}\right\rfloor$ 的最大的数），这个区间加的总贡献值就是 $\left\lfloor\dfrac{n}{i}\right\rfloor\cdot(j-i+1)$。设上面这个公式是函数 $f(n)$，于是我们只需要算出 $f(m)-f(n-1)$ 就行了。

**注意：十年 OI 一场空，不开 long long 见祖宗。**

AC Code:
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
ll f(ll x)
{
    ll s=0;
    for(ll i=1,j;i<=x;i=j+1)
        j=x/(x/i),s+=(x/i)*(j-i+1);//套公式
    return s;
}
ll n,m;
int main()
{
    scanf("%lld%lld",&n,&m);
    ll as=f(m)-f(n-1);//算
    printf("%lld",as);
    return 0;
}
```

~~看到这了不点个赞吗~~

---

## 作者：wzt2012 (赞：1)

### 题目大意

计算出给定区间内所有数的因数个数。

### 解决方法

- 我们知道，$n$ 之内的所有因数个数的计算方法为：$n\div 1+n\div2+n\div3\dots n\div n$;

但是，直接枚举会超时。

我们只要在计算的时候跳转一下即可。

那么怎么跳转呢？

我们来举个例子，我们枚举 $n$ 为 $6$ 时，

我们枚举到 $n\div (4,5,6)$ 这三个数的时候，贡献都为 $1$，我们就直接将答案都为 $1$ 的这些直接全部计算出来，然后跳到下一种情况即可。


### 参考代码

```
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL fun(LL n){
    LL l, r;
    LL ans = 0;
    for(l = 1; l <= n; l = r + 1){
        r = n / (n / l);
        ans += n / l *(r - l + 1);
    }
    return ans;
}
int main(){
    int t;
    LL x, y;
    cin >> x >> y;
    printf("%lld\n", fun(y) - fun(x - 1));
    return 0; 
}
```

---

## 作者：ainivolAGEM (赞：0)

**前情提要：**[更好的阅读体验。](https://www.luogu.com.cn/blog/tomby-gz-2011/solution-p9611)

## 题目大意

[题目](https://www.luogu.com.cn/problem/P9611)里写了，就是求 $N \sim M$ 的所有因数之和。

## 题目分析

首先看数据范围，$1 \leq N \leq M \leq 10^{12}$，看来暴力是没希望了。

那么考虑 $\sqrt{N}$ 的做法，我们考虑 $1 \sim N$ 中的一个数 $i$，计算 $1 \sim N$ 之中有多少个 $i$ 的倍数，就可以求 $1 \sim N$ 的因数和了，对于一个 $i$，它的值为 $\lfloor \frac{n}{i} \rfloor$。那么 $1 \sim N$ 的公式之和就是：

$$\sum^n_{i = 1} \lfloor \frac{n}{i} \rfloor$$

但是一个个算肯定是不可能的，$10^{12}$ 不会给你任何机会，所以还要优化。

可以发现，有些区间里的 $\lfloor \frac{n}{i} \rfloor$ 是相同的。假设一个区间的左端点 $l$ 的值为 $\lfloor \frac{n}{i} \rfloor$，则右端点为 $\lfloor \frac{n}{\lfloor \frac{n}{i} \rfloor} \rfloor$，设总值为 $F ( n )$，则区间的总值为：

$$F ( n ) = ( r - l + 1 ) \times \lfloor \frac{n}{i} \rfloor$$

那么对于 $N \sim M$ 这个区间，只需要计算 $F ( M ) - F ( n - 1 )$ 就可以了。

**注意！十年 OI 一场空，不开 long long 见祖宗！**

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m;
ll GetNum(ll t){
	ll j,sum=0;
	for(ll i=1;i<=t;i=j+1){
		j=t/(t/i);
		sum+=(j-i+1)*(t/i);
	}
	return sum;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	cout<<GetNum(m)-GetNum(n-1);
}
```

---

## 作者：littleqwq (赞：0)

## P9611 [CERC2019] Zeldain Garden 题解

重点就是求 $l$ 到 $r$ 的区间里，所有数的因数个数之和，看看数据范围，惊人的 $10^{12}$，如果直接求，必爆，那么经过推算后，我们其实可以知道一个原理，假设一个左端点为 $o$，它的右端点为 $p$，$o$ 就等于 $k÷o$，$p$ 就等于 $k÷o$，可以发现他们的贡献值是一样的！！！而我们知道一个空间的大小是 $p-o+1$ 那么大，那么它区间内的贡献值就是 $(p-o+1)×(k÷o)$，这是一个函数，而我们要求的是区间内的，也就是 $r$ 到 $l-1$ 的范围内，所以把两个得到的值相减即可！！！

ACcode:

```
#include<bits/stdc++.h>
using namespace std;
#define LL long long
LL l,r;
LL s(LL k){
	LL sum=0;
	LL p;
	for(LL o=1;o<=k;o=p+1){//根据上面的公式，不能加1循环
		p=k/(k/o);
		sum=sum+(k/(k/o)-o+1)*(k/o);//公式
	}
	return sum;
}
int main(){
	cin>>l>>r;
	cout<<s(r)-s(l-1)<<endl;
	return 0;
} 
```

---

## 作者：watcher_YBH (赞：0)

# 思路：
[[题目]](https://www.luogu.com.cn/problem/P9611)

首先，我们需要了解一个求 $1 \sim n$ 中所有数的因数的公式：

$$f(n) = \left\lceil\frac{n}{1}\right\rceil + \left\lceil\frac{n}{2}\right\rceil + \left\lceil\frac{n}{3}\right\rceil + ... + \left\lceil\frac{n}{n-1}\right\rceil + \left\lceil\frac{n}{n}\right\rceil$$

首先，我们可以利用这个公式求出 $f(m) - f(n)$，再加上 $n$ 的贡献就可以了。

但我们会发现，这样的算法会超时，于是，我们考虑一个优化：

当 $x = 10$ 时，$f(x)$ 中会有几个贡献相同的单项式。
$$\left\lceil\frac{n}{6}\right\rceil = \left\lceil\frac{n}{7}\right\rceil = \left\lceil\frac{n}{8}\right\rceil = \left\lceil\frac{n}{9}\right\rceil = \left\lceil\frac{n}{10}\right\rceil$$

所以，$1 \sim n$ 中贡献相同的单项式的区间为 $i \sim \left\lceil\frac{n}{\left\lceil\frac{n}{i}\right\rceil}\right\rceil$，则我们就可以利用这个公式来优化。

# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define max(a,b) ((a)>(b)?a:b)
#define min(a,b) ((a)<(b)?a:b)
using namespace std;
const int MAX = 1e5+5;
int n,m,ans;
int f(int x){
	int z = 0;
	//  n/i+...+n/n
	for(int l = 1,r; l<=x; l = r+1)// 公式加优化
	//这里，(x/l)为这个单项式的贡献，而x/(x/l)则是贡献为(x/l)的最大的l
		r = x/(x/l),z += (r-l+1)*(x/l);
	return z;
}
signed main(){
	cin>>n>>m;
	ans += f(m)-f(n);// 计算f(m)-f(n)
	for(int i = 1; i<=sqrt(n); i++)// 单独计算n的贡献
		ans += (n%i == 0)*2;
	ans -= ((int)(sqrt(n))*(int)(sqrt(n)) == n);// 是平方数就减一
	cout<<ans;
	return 0;
}

```



---

