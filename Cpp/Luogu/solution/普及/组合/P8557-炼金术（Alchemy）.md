# 炼金术（Alchemy）

## 题目描述

铃是一个爱玩游戏的女孩子。

她在游戏中想要炼制一种稀有合金 —— 这需要 $n$ 种金属来合成。

她准备好矿石后建造了 $k$ 个不同的熔炉，当熔炉启动时，会随机炼出这 $n$ 种金属中的一些（也可能什么都没有）。

如果把每个熔炉炼出的金属收集起来，有了全部 $n$ 种金属，就能造出合金了。澪对此很好奇，对铃说：「我考考你，有多少种情况可以炼出合金呢？」这个简单的问题铃很快就会做了，你能求出结果吗？

答案可能很大，请对 $998244353$ 取模（即除以 $998244353$ 的余数）后输出。

## 说明/提示

【样例一解释】  
对于所有成功情况，两个熔炉中的金属如下表：

| 一号  | 二号 |
| :----------: | :----------: |
| $\varnothing$ | $\{1,2\}$ |
| $\{1\}$ | $\{2\}$ |
| $\{1\}$ | $\{1,2\}$ |
| $\{2\}$ | $\{1\}$ |
| $\{2\}$ | $\{1,2\}$ |
| $\{1,2\}$ | $\varnothing$ |
| $\{1,2\}$ | $\{1\}$ |
| $\{1,2\}$ | $\{2\}$ |
| $\{1,2\}$ | $\{1,2\}$ |

一共 $9$ 种，因此答案为 $9$。

【数据范围】  
对于 $30\%$ 的数据，$1\le n,k \le 10$；  
对于 $80\%$ 的数据，$1\le n,k \le 10^6$；  
对于 $100\%$ 的数据，$1\le n,k \le 10^9$。

## 样例 #1

### 输入

```
2 2```

### 输出

```
9```

## 样例 #2

### 输入

```
4 5```

### 输出

```
923521```

## 样例 #3

### 输入

```
233 123```

### 输出

```
81633405```

# 题解

## 作者：zhang_kevin (赞：25)

这道题需要用到排列组合的知识，不会的建议去[看我的博客](https://www.luogu.com.cn/blog/zyc-Kevin-Luogu-blog/pai-lie-zu-he)。

我们可以先从这 $n$ 种金属入手。

对于任意一种金属，它可以被任意 $1 \sim k$ 个熔炉所造出来，方案总数为：

$$C^1_k+C^2_k+C^3_k+\cdots\cdots+C^{k-1}_k+C^k_k = 2^k-1$$

现在有 $n$ 种金属，每一种金属有 $2^k-1$ 种方法，总方案数为 $(2^k-1)^n$，配上快速幂模板即可。

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
#define endl '\n'
using namespace std;
const int mod = 998244353;

int ksm(int a, int b){
    int ans = 1;
    while(b){
        if(b & 1)
			ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}

int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, k, ans = 0;
	cin >> n >> k;
	cout << ksm(ksm(2, k)-1, n) << endl;
	return 0;
}
```


---

## 作者：Andy_L (赞：15)

$\color{#E74C3C}\text{温馨提示:}$

$\color{#E74C3C}\text{遇见题解勿抄袭，棕名封号两行泪。}$

[题目传送门](https://www.luogu.com.cn/problem/P8557)

### 思路

我们观察一下样例和题目，发现它有两种情况：

1. 它可能什么金属都不掉；

1. 它可能掉金属。

又因为有 $k$ 个熔炉，所以对于每一种金属，有 $2^k$ 种分配方法，而它有不可能一个熔炉都没有，所以要 $-1$ ，即 $2^k-1$ 种方法。这只是一种金属的，一共有 $n$ 种，所以总共是 $(2^k-1)^n$ 种方法。

观察数据发现 $1 \le n,k \le 10^9$ ，所以要用快速幂。

----

$$\text{Code}$$

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll mod=998244353;
ll n,k;
ll ksm(ll x,ll y)//快速幂
{
    ll ans=1;
    while(y)
    {
        if(y&1) ans=ans*x%mod;
        y>>=1;
        x=x*x%mod;
    }
    return ans;
}
int main()
{
    cin>>n>>k;
    cout<<ksm((ksm(2,k)-1+mod)%mod,n)<<"\n";
    return 0;
}
```

$$\text{The End}$$

---

## 作者：koobee (赞：7)

这是本人第一篇题解。

首先来分析一下。

一共 $k$ 个熔炉，对于第 $i$ 种金属，它在每个熔炉里都可有可不有，但在 $k$ 个熔炉中必须要有，故第 $i$ 种金属有 $2^k-1$ 种情况。因此，一共就有 $m^n$ 种情况，其中 $m$ 为 $2^k-1$ 。

然而，数据很大，所以乘方需要用快速幂。（如果不用只有 $80$ 分）。

标程：

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n, k, mod = 998244353, mul = 1;
long long m = 1;
typedef long long ll;
ll Pow(ll a, ll b){ //快速幂
	ll mul = 1;
	while(b > 0){
		if(b % 2 == 1) mul = mul * a % mod;
		a = a * a % mod;
		b /= 2;
	}
	return mul;
}
int main(){
	cin>>n>>k;
	mul = Pow(2, k);
	mul--;
	m = Pow(mul, n);
	cout<<m<<endl;
	return 0;
}
```


---

## 作者：zhangyuanxiao (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P8557)

## 题目大意
- 有 $k$ 个不同的熔炉，每个熔炉可能炼出 $n$ 种金属中的一种（或者什么都没有）。
- 求出一共有多少种情况，使每种金属至少被一个熔炉炼出。
- $1\le n,k \le 10^9$，答案对 $998244353$ 取模。

## 分析
- 对于第 $i$ 种金属（$1\le i \le n$）：$k$ 个熔炉中，每个熔炉有两种情况：炼出或没炼出。$k$ 个熔炉总共有 $2^k$ 种情况。因为每种金属要至少被一个熔炉炼出，所以去掉每个熔炉都没有炼出第 $i$ 种金属的情况，有 $2^k-1$ 种情况。因为有 $n$ 种金属，每种金属都有 $2^k-1$ 种情况，所以总共有 $(2^k-1)^n$ 种情况。
- 本题数据范围较大，记得开 **long long**，否则只能拿 $10$ 分。
- 如果直接用 for 循环计算幂，时间复杂度为 $O(n+k)$，无法通过 $n,k \le 10^9$ 的数据，只能拿 $80$ 分，所以需要使用**快速幂**算法把时间复杂度优化至 $O(\log n+\log k))$ ，可以通过本题。

## 代码

```cpp
#include<iostream>
using namespace std;

const int mod=998244353;
long long n,k,ans;//一定要开long long

long long qpow(long long a,long long p){//快速幂
	long long base=a,anss=1;
	while(p){
		if(p&1){
			anss*=base;
			anss%=mod;
		}
		base*=base;
		base%=mod;
		p=p>>1;
	}
	return anss;
}

int main(){//套公式
	cin>>n>>k;
	ans=qpow(2,k);
	ans-=1;
	ans=qpow(ans,n);
	cout<<ans;
	return 0;
}
```

如发现错误，欢迎私信指出。


---

## 作者：c202201 (赞：5)

$n$ 中金属，每种金属都可以由 $k$ 个机器制作而成。对于其中一个金属而言，每个机器有制作或不制作两种情况，共 $2^k$ 种，减去所有机器都不制作的情况，一个金属有 $2^k-1$ 种制作情况。

$n$ 个金属没有区别，因此总方案数为 $(2^k-1)^n$。快速幂解决即可。

代码如下：

```cpp
#include <bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int mod=998244353;
il int read(){
	int x(0);
	char ch(getchar());
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x;
}
int n,k;
il int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
signed main(){
	n=read(),k=read();
	printf("%lld",ksm(ksm(2,k)-1+mod,n));
	return 0;
}
```

完结撒花~

---

## 作者：SmallBlack (赞：2)

#### 前言：

没有打比赛。赛后看题，确实是放第一题的难度。

#### 题意简述

- 有 $k$ 个熔炉，每个熔炉有可能出现 $1-n$ 种金属中的若干种，也有可能没有。
- 求 $k$ 个熔炉的产物中所有金属都出现的情况数。
- $1\le n,k \le10^9$，答案对 $998244353$ 取模。

#### 做题思路

这类题目最大的特点就是可以转换思考角度。

换个说法，因为如果对于每一个熔炉进行分析以解决问题，要考虑各个金属是否出现，还要考虑重复情况，情况会太多太杂，容易搞混。
所以我们尝试**从单种金属的角度**思考。

因为 $n$ 种金属的产生情况**互不影响**，所以我们只**考虑一种金属的情况**，最后用乘法原理计算 $n$ 次方即可。

那么对于单一金属，第 $i$ 个熔炉**只有出现与不出现两种情况**。一共 $k$ 个熔炉，依据乘法原理，一共有 $2^k$ 种情况。

但是金属不可以在所有熔炉中都不出现，所以总数需要减一。

所以对于一种金属，有 $2^k-1$ 种方案满足。

那么对于 $n$ 种金属，有 $(2^k-1)^n$ 种方案满足条件。

使用快速幂 $O(\log k+\log n)$ 解决即可。

#### 代码实现

```
// Problem: P8557 炼金术（Alchemy）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8557
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Date:2022-10-03 07:44:21
// By:SmallBlack
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
	long long s=0,k=1;
	char c=getchar();
	while(!isdigit(c))
	{
		k=(c=='-')?-1:1;
		c=getchar();
	}
	while(isdigit(c))
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s*k;
}
#define d read()
#define ll long long
#define Maxn 10010
#define Size 10010
#define mp make_pair
#define pb push_back
#define fi first
#define se second
ll ksm(ll a,ll b,ll m)
{
	ll ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%m;
		a=a*a%m;
		b>>=1;
	}
	return ans;
}
int main()
{
	ll n=d,k=d,M=998244353;
	printf("%lld\n",ksm(ksm(2,k,M)-1,n,M));
}
```

#### 后记

发现很多的组合问题都可以在一定条件下通过构造结构来解决。

~~或许是一种少背公式的技巧？~~

---

## 作者：myEnd (赞：2)

这个题没啥难度。

根据题面，容易发现对于每个金属，方案数是一样的，所以只要讨论出对于一种金属的方案数，然后再 $n$ 次方即可。

考虑一种金属，对于每个熔炉，有 出、不出 两种情况，所以对于一共 $k$ 个熔炉，共有 $2^k$ 种情况。但是不能每个熔炉都没有出，所以要减去一种情况。所以实际上是有：$2^k-1$ 种情况符合条件。

因为一共有 $n$ 种金属，所以一共有：

$$\left(2^k-1\right)^n$$

种情况。


对了，这里有一个性质：若 $a \equiv b \pmod m$，则 $a^k \equiv b^k \pmod m$。

稍微证明一下：考虑 $a=xm+p, b=ym+p(0 < p < m)$，根据二项式定理，除了 $p^k$ 项，都有 $xm$ 或 $ym$ 这个因子，所以都是 $m$ 的整数倍。所以 $a^k \equiv xm(\cdots) + p^k \equiv p^k \pmod m$、$b^k \equiv ym(\cdots) + p^k \equiv p^k \pmod m$。所以原性质成立且还有 $a^k \equiv (a \mod m)^k \pmod m$。

所以就可以转化为：

$$\left((2^k-1) \mod 998244353\right)^n \mod 998244353$$

考虑两次快速幂即可。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

constexpr int mo=998244353;

inline int qpow(int k, int po, const int& mo)
{
	int res = 1;
	while(po)
	{
		if(po&1) res=res*k%mo;
		k=k*k%mo;
		po>>=1;
	}
	return res;
}

signed main()
{
	int n, k;
	cin >> n >> k;
	swap(n, k);
	n = qpow(2, n, mo)-1;
	cout << (qpow(n, k, mo)%mo);
	return 0;
}
```

---

## 作者：int08 (赞：2)

# 前言
几乎是历史最难第一题。（如果按大月赛规模来算）
# Solution

看见这个数据，我几乎就已经认为这是一道复杂度为 $O(1)$ 的结论题。~~但事实证明我是错的。~~

我们来思考一下，为什么我们看到这道题没有思路:

因为我们不知道每个熔炉里装了哪些金属，一号熔炉里既可能同时装着 $1,2$ 号金属，也可能一个金属都不装，全部留给二号熔炉。

放到其他熔炉也是这样，所以很难用一个数学表达式把它写出来。

但是转念一想：**如果我们不从熔炉角度考虑，我们从金属角度考虑，这道题是不是会变简单。**

其实想到这一点之后，这题已经几乎做出来了。

还是先拿样例举例：$1$ 号金属可能放在一号熔炉里，也可能放在二号熔炉里，也有可能同时放在两个熔炉里，但至少要放在某一个熔炉，绝对不能不在任何一个熔炉里。

所以这块金属有 $3$ 种放法，同理 $2$ 号金属也有 $3$ 种放法。所以最后答案为 $9$。

接下来我们就扩展到正常的数据：对于某一块金属来说，它可以放在这一个熔炉里，也可以不放在这一个熔炉里。情况数为 $2$。因为有 $k$ 个熔炉，所以这一块金属放在这 $k$ 个熔炉中的情况总数就是 $2^k$。

噢对了，由于某一块金属**不能不放在任何一个熔炉里**，所以在情况总数中应该减去这么一种情况，总情况数应该为 $2^k-1$。

同时又因为有 $n$ 块金属，所以最后答案为 $(2^k-1)^n$。

与此同时，（看一眼本题的数据规模）这道题的数据让我们必须要写快速幂。

不知道怎么写的康这里：[P1226 【模板】快速幂||取余运算](https://www.luogu.com.cn/problem/P1226)
## 注意逝项
1、虽然这道题的数据好像在整型范围之内，不过还是开个 long long 保险一点吧。

2、如果快速幂写的不太好，就需要特判。

# AC code

```cpp
#include<iostream>
using namespace std;
typedef long long ll;
const ll mod=998244353;
ll fast_power(ll b,ll p,ll m){
    ll r=1;
    while (p>0){
        if(p&1){
            r=r*b%m;
        }
        p>>=1;
        b=(b*b)%m;
    }
    return r;
}
ll n,k;
int main(){
    scanf("%lld%lld",&n,&k);
    printf("%lld",fast_power((fast_power(2,k,mod)+mod-1)%mod,n,mod));
    return 0;
}
```
# The End.

---

## 作者：olegekei (赞：2)

## 背景
本人较弱，赛时没推出来柿子，而是打了个暴力（打表）才找到的规律（而且暴力写完后还把 $n$ 和 $k$ 读入的顺序搞反了，调半天也没过样例），所以本篇题解主要围绕打表找规律。
## 暴力思路
每层 dfs 枚举每个熔炉，同时枚举当前熔炉可能炼出的金属，最后搜到底层时 check 一下是否每种金属数量都至少为 $1$ 即可。

但是考虑到枚举每个熔炉可能炼出的金属数量是不定的，枚举的时候很麻烦，所以本人用了二进制优化了一下枚举过程，下面是暴力代码：
```cpp
#include<iostream>
#define lowbit(x) x&-x
using namespace std;
int n,k;
int ans=0,vis[32767];
void check(){
	for(int i=k;i;i-=lowbit(i)){
		if(!vis[lowbit(i)])return;
	}
	ans++;
}
void dfs(int dep){
	if(dep>n){check();return;}
	for(int i=0;i<=k;i++){
		for(int j=i;j;j-=lowbit(j)){
			vis[lowbit(j)]++;
		}
		dfs(dep+1);
		for(int j=i;j;j-=lowbit(j)){
			vis[lowbit(j)]--;
		}
	}
}

main(){
cin>>k>>n;//因为一开始搞反了顺序，所以又反着输入了一下n和k
//则此时k的值代表金属数量，n则代表熔炉数量
k=(1<<k)-1;
dfs(1);
cout<<ans;
}
```
然后有了暴力程序，就可以开始打表了:
| k\n | 1 | 2 | 3 | 4 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| 1 | 1 | 1 | 1 | 1 |
| 2 | 3 | 9 | 27 | 81 |
| 3 | 7 | 49 | 343 | 2401 |
| 4 | 15 | 225 | 3375 | 50625 |

---
观察上表，$n=1$ 时的答案都为 $2^k-1$，再单独观察 $k=1,2,3,4$，发现答案就是相应 $n=1$ 时的答案 $ans$ 的 $n$ 次方，即 $ans^n$，将表格扩大范围后上述结论同样适用，则最终的答案为：

$$(2^k-1)^n$$

但是数据范围较大，所以需要加个快速幂，轻松 AC。

代码：
```cpp
#include<iostream>
using namespace std;
long long n,k,mod=998244353;
long long quick(long long bas,long long b){
	long long ans=1;
	while(b!=0){
		if(b & 1) ans=(ans*bas)%mod;
		bas=(bas*bas)%mod;
		b>>=1;
	}
	return ans;
}
int main(){
cin>>n>>k;
long long ans=quick(quick(2,k)-1,n);
cout<<ans;
}
```

---

## 作者：Ginger_he (赞：2)

## 题目描述

给定 $n$，定义集合 $s=\{x\in Z|1\le x\le n\}$。

有 $k$ 个本质不同的集合，每个集合中有若干个元素，每个元素均属于集合 $s$，求使得这 $k$ 个集合的并集为 $s$ 的方案数，答案对 $998244353$ 取模。

## 题解

每个集合最多有 $n$ 个元素，每个元素可以**选或不选**，所以对于一个集合，它的情况数为

$$2^n$$

又因为共有 $k$ 个本质不同的集合，所以总的情况数为

$$(2^n)^k$$

不难发现，上面的式子计算的是并集**最多**有 $n$ 个元素的情况。如果要去掉不符合条件的情况，则要减去并集最多有 $n-1$ 个元素的情况，这样又会有重复，然后又是同样的方法递归下去。从根本来说，这就是一个**简单容斥**。

所以答案为

$$\sum_{i=0}^n(2^{n-i})^k\times(-1)^i=\sum_{i=0}^n(2^k)^{n-i}\times(-1)^i$$

根据**二项式定理**，上述式子可以化为

$$(2^k-1)^n$$

于是我们就可以在 $\Theta(\log k+\log n)$ 的时间内解决这个问题。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll p=998244353;
ll n,k;
ll quickpow(ll a,ll b)
{
    ll res=1;
    while(b)
    {
        if(b&1)
            res=res*a%p;
        b>>=1;
        a=a*a%p;
    }
    return res;
}
int main()
{
    scanf("%lld%lld",&n,&k);
    printf("%lld\n",quickpow((quickpow(2,k)-1+p)%p,n));
    return 0;
}
```

---

## 作者：251Sec (赞：1)

很巧妙的计数题。（也可能是因为我没怎么写计数题……这题的结论我赛时是猜出来的）

尝试把“炉子中出现金属”改成“每种金属选择若干个炉子”。显然每种金属选炉子的方法有 $2^k$ 种。（每个炉子可以决策选或不选）。排除一个都不选的情况就是 $2^k-1$。

有 $n$ 种金属，因此答案为 $(2^k-1)^n$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int p = 998244353;
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
int n, k;
int main() {
    scanf("%d%d", &n, &k);
    printf("%lld", qpow(qpow(2, k) - 1, n));
    return 0;
}
```

---

## 作者：二叉苹果树 (赞：1)

## 分析题意

首先，将题意化简：对于给定的 $n$ 个元素，要求每个元素在 $k$ 个集合中至少出现 $1$ 次，求总方案数。

更具体的，设 $k$ 个集合分别为 $A_1$ ~ $A_k$，每组合法的集合方案满足：

$$\bigcup_{1 \le i\le k}A_i=\{x\in \mathbb{N_+}|x\le n\}$$

由题意可知，不同种方案与排列顺序有关。也就是说，我们认为当 $n=2,k=2$ 时，$A_1=\{1\},A_2=\{2\}$ 与 $A_1=\{2\},A_2=\{1\}$ 是两组不同的方案。

如果将 $n$，$m$ 换成具体数字，很明显这是一道高中集合数学题。考虑到每种元素必须出现至少 $1$ 次，而在每个集合中有出现与不出现的 $2$ 种情况。根据乘法原理，每个元素的出现情况为 $2^k-1$种，这里减去的 $1$ 种即为当该元素在 $k$ 个集合里都不出现的情况。除此以外，其他的方式都是符合题意的。

同样的，对于 $n$ 个不同种元素，由乘法原理也可以知道，总方案数为各个元素的方案数之积，故最终要求的总方案数即为:

$$\left(2^k-1\right)^n \mod 998244353$$

## 具体做法

数据范围为 $1\le n,k \le 10^9$，$n,k$ 在计算中均作为指数存在，并且要求对大质数取模，不难想到快速幂。

具体代码实现如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
long long fastpow(long long b,long long p,long long k)
{
    long long result=1;
    while (p)
    {
		if (p%2==1)
			result=result*b%k;
		p/=2;
		b=b*b%k;
	}
    return result%k;
}
const int mod=998244353;
int main()
{
    int n,k;;
    n=read();
    k=read();
    long long p=(fastpow(2,k,mod)+mod-1)%mod;
    long long ans=fastpow(p,n,mod)%mod;
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：Asimplename (赞：1)

对于任意一个金属，它都可以进 $k$ 个容器中的若干个，所以最终可以取出这种金属的合法情况共有 $2^k - 1$ 种。而共有 $n$ 个金属，所以最终答案就为 ${(2^k-1)}^n$ 对 $998244353$ 取余的结果。可以使用快速幂解决。

```cpp
#include<iostream>
#define int long long
using namespace std;
int n,k;
const int mod = 998244353;
int Quickpow(int a, int b){
	int ans = 1;
	int ind = a;
	while(b != 0){
		if(b & 1){
			ans = ans * ind % mod;
		}
		ind = ind * ind % mod;
		b >>= 1;
	}
	return ans;
}
signed main (){
	cin >> n >> k;
	cout << Quickpow(Quickpow(2, k) - 1, n);
	return 0;
}

---

## 作者：yuheng_wang080904 (赞：0)

## 思路

如果列举每个熔炉炼出哪些金属，则最后的式子将会很难推出。 _~~（反正我失败了）~~_

那么我们可以考虑每个金属被哪个熔炉炼出。要使得每个金属都有，那么它至少需要被一个熔炉炼出，每个金属对于每个熔炉来说可以炼出或者不炼出，一共 $2^k$ 种情况，但是我们要去除都不炼出的一种，因此对于每个金属来说有 $2^k-1$ 种情况。而每个金属又是互不相同，互不干涉的，因此由乘法原理知情况总数为 $(2^k-1)^n$，直接用快速幂算出结果。

最后写个赛时小技巧：如果你用了一开始的方法，算不出式子的话，你可以将样例的前两个的输出分解质因数，并根据输入猜出式子!

## 代码

接下来放上代码，简单的快速幂。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
long long n,k;
long long fastpow(long long a,int b){
    if(b==1)return a%mod;
    else if(b%2)return a%mod*fastpow(a%mod*a%mod,b/2)%mod;
    else return fastpow(a%mod*a%mod,b/2)%mod;
}
int main(){
    cin>>n>>k;
    cout<<fastpow(fastpow(2,k)%mod-1,n)%mod<<endl;
    return 0;
}
```


---

## 作者：FunKingDoor (赞：0)

我们把问题看成每一个金属去选炉子。

对于每个炉子有放/不放两种选择，所以总共的选法有 $2^k$ 种。

但是不能每一个炉子都不放这个金属，所以还要减去 $1$。

最后，用乘法原理把每个金属的方案数乘起来，即：$(2^k-1)^n$ 种。

直接暴力乘一定会炸，套一个快速幂板子即可。

AC code：

```cpp
#include<iostream>
using namespace std;

#define int long long

const int mod = 998244353;

int qpow(int a, int b){
    int res = 1;
    while(b){
        if(b & 1){
            res *= a;
            res %= mod;
        }
        b >>= 1;
        a *= a;
        a %= mod;
    }
    return res;
}

signed main(){
    int n, k;
    cin >> n >> k;
    cout << qpow(qpow(2, k) - 1, n);
    return 0;
}
```


---

## 作者：Sktic (赞：0)

[P8557 炼金术（Alchemy）](https://www.luogu.com.cn/problem/P8557)



~~通过看比赛名称我们可以知道这是一道数学题。~~



直接看熔炉选元素不是很容易想出来，我们考虑转换思路，变成元素选熔炉。



根据乘法原理可得，共有 $k$ 个熔炉，那么这个元素总共有 $2^k$ 种出现情况（每个熔炉中出现或者不出现），但是要注意当每个熔炉这个元素都不出现时这种情况是不合法的，于是考虑减掉变成 $2^k-1$ 种。



又因为每个熔炉本质不同，所以 A 熔炉炼出了 $1$ ，B 熔炉练出了 $2$ 和 A 熔炉炼出了 $2$ ，B 熔炉练出了 $1$ 是两种不同的方案。因此根据乘法原理，各个元素的方案数之积即为：

$$(2^k-1)^n \bmod 998244353$$



于是考虑快速幂边取模边运算，可以通过本题。



AC Code:

```C++
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
const int mod=998244353;
typedef long long ll;
inline ll qpow(ll x,ll y)
{
	ll ans=1;
	while(y)
	{
		if(y&1)
			ans=(ans%mod*x%mod)%mod;
		x=(x%mod*x%mod)%mod;
		y>>=1;
	}
	return ans%mod;
}
int main()
{
	ios::sync_with_stdio(false);
	ll n,k;
	cin>>n>>k;
	cout<<qpow((qpow(2,k)-1)%mod,n)%mod;
	return 0;
}
```



---

## 作者：Moeebius (赞：0)

## Preface
~~组合数学好（水）题。~~
## Analysis
首先，我们发现整体统计是比较不可做的。

所以考虑将 $n$ 种金属用乘法原理拆开，分别考虑。

对于每一种金属，可能的情况共有 $2^k$ 种（**每个熔炉选择放或不放**），排除掉不合法的一种（所有熔炉均不放），剩下的即为答案。

乘法原理可知答案即为 $(2^k-1)^n$。

---

## 作者：XCH_0803 (赞：0)

这道题一眼看出来是一道数学题。

它有 $n$ 种金属，$k$ 个熔炉，

多了一种金属你至少需要一个熔炉去把它炼出来。

那么 $f[n][k]$ $=$ $f[n - 1][k]$ $\times$ $(2 ^ k - 1)$

直到 $n$ $=$ $0$，$f[0][k]$ $=$ $1$

所以通项公式是 $(2 ^ k - 1)^n$

我们还有一个要注意的，那就是 $n$ 和 $k$ 都小于等于 $10^9$ 所以我们要用快速幂来解决这道题。

话不多说，上代码

```c
#include<bits/stdc++.h>
using namespace std;
long long ksm(int x,int mi){//快速幂板子 
	long long res=1;
	for(res=1;mi;mi>>=1,x=(long long)x*x%998244353){
		if(mi&1){
			res=res*x%998244353;
		}
	}
	return res;
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	long long n,k;
	cin>>n>>k;
	cout<<ksm(ksm(2,k)-1,n)%998244353;//直接套用公式并取余,输出 
	return 0;
}
```


---

## 作者：Jeremiahy (赞：0)

## 分析

从每个熔炉炼哪些金属来考虑，会难以统计，于是我们可以**枚举每块金属在哪些熔炉里炼**。

每个金属可以选择任意数量的熔炉，但必须选择至少一个，所以状态总数为 $2^k-1$，有 $n$ 块金属，答案就是 $(2^k-1)^n$，注意取模。

求次幂使用快速幂即可。

#### 核心代码

```cpp
inline int qpow(int a, int n) {//快速幂
	int ans = 1;
	while (n) {
		if (n & 1)
			(ans *= a) %= p;
		(a *= a) %= p;
		n >>= 1;
	}
	return ans % p;
}
signed main () {
	cin >> n >> k;
	cout << qpow(qpow(2, k) - 1, n) % p;//公式计算
	return 0;
}
```


---

