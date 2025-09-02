# Divisors

## 题目描述

You are given $ n $ integers $ a_1, a_2, \ldots, a_n $ . Each of $ a_i $ has between $ 3 $ and $ 5 $ divisors. Consider $ a = \prod a_i $ — the product of all input integers. Find the number of divisors of $ a $ . As this number may be very large, print it modulo prime number $ 998244353 $ .

## 说明/提示

In the first case, $ a = 19305 $ . Its divisors are $ 1, 3, 5, 9, 11, 13, 15, 27, 33, 39, 45, 55, 65, 99, 117, 135, 143, 165, 195, 297, 351, 429, 495, 585, 715, 1287, 1485, 1755, 2145, 3861, 6435, 19305 $ — a total of $ 32 $ .

In the second case, $ a $ has four divisors: $ 1 $ , $ 86028121 $ , $ 86028157 $ , and $ 7400840699802997  $ .

In the third case $ a = 202600445671925364698739061629083877981962069703140268516570564888699 375209477214045102253766023072401557491054453690213483547 $ .

In the fourth case, $ a=512=2^9 $ , so answer equals to $ 10 $ .

## 样例 #1

### 输入

```
3
9
15
143```

### 输出

```
32```

## 样例 #2

### 输入

```
1
7400840699802997
```

### 输出

```
4```

## 样例 #3

### 输入

```
8 
4606061759128693
4606066102679989
4606069767552943
4606063116488033
4606063930903637
4606064745319241
4606063930904021
4606065559735517```

### 输出

```
1920```

## 样例 #4

### 输入

```
3
4
8
16
```

### 输出

```
10
```

# 题解

## 作者：Alex_Wei (赞：20)

> [题面传送门](https://www.luogu.com.cn/problem/CF1033D)。

> 题意简述：给出 $n$ 个数 $a_{1,2,\cdots,n}$ 满足 $3\leq d(a_i)\leq 5$，求 $d(\prod a_i)$。

> - 其中，$d(i)$ 表示 $i$ 的约数个数。

因为 $3\leq d(a_i)\leq 5$ 这个限制条件已经非常严格了，所以思路并不是很难想。

---

前置知识：约数（因数）个数定理：

对于一个大于 $1$ 的正整数 $n$ 可以分解质因数 $n=\prod p_i^{c_i}$，则 $d(n)=\prod(c_i+1)$。

---

分析：

根据因数个数定理和题目给出的限制条件，不难发现 **$a_i$ 最多只有 $2$ 个质因子。**

以上面的发现作为突破口进行分类讨论：

---

当 $a_i$ 只有 $1$ 个质因子时：设 $a_i=p^c$，现在只需要求出 $p,c$ 即可：

根据题目给出的限制条件可知，$2\leq c\leq 4$（为什么？想一想 $^1$）。
  
首先判断 $a_i$ 是否是一个数的平方：
  
- 如果是，则判断 $\sqrt {a_i}$ 是否是一个数的平方：
  
  - 如果是，则 $p=\sqrt[4]{a_i}$，$c=4$。
    
  - 否则 $p=\sqrt{a_i}$，$c=2$。
   
- 否则**二分**判断 $a_i$ 是否是一个数的三次方：
   
  - 如果是，则 $p=\sqrt[3]{a_i}$，$c=3$。
     
  - 否则 $a_i$ 有两个质因子，跳过。
     
求出 $p,c$ 过后，我们给质因子 $p$ 的计数器加上 $c$ 即可，计数器可用 STL 容器 ```map <long long,int>``` 模拟。
    
- 判断 $x$ 是否是一个数的平方：求出 $y=\lfloor \sqrt x \rfloor$，如果 $y^2=x$，则 $x$ 是 $y$ 的平方。

---

当 $a_i$ 有 $2$ 个不同的质因子时：设 $a_i=p_1^{c_1}\times p_2^{c_2}$。

根据题目给出的限制条件可知，$c_1=c_2=1$（为什么？想一想 $^2$），即 $a_i=p_1\times p_2$。也就是说 $a_i$ 为两个不相同的质数的乘积，约数个数为 $4$。

接下来要处理每个质因子在这些数中出现的次数 **（下文中“这些数”指质因子个数为 $2$ 的数）**。

由于数据范围太大，导致我们无法 $O(n\sqrt {a_i})$ 分解质因数。~~什么？你说 Pollard-rho？这是啥算法？~~

但是不难发现，我们**并不关心分解质因数后的结果，只关心质因子出现次数**。

所以首先将这些数去重并存在另一个数组 $b$ 里，记录每个数 $b_i$ 在原数组 $a$ 中出现的次数 $num_i$。

也许你会说，对于每个 $b_i$，将答案直接乘上 $(num_i+1)^2$ 不就行了？~~不会吧，不会吧，不会真的有人这么说吧。~~

但是如果同一个质因数在不同的 $b_i$ 中出现，那么这样做就是错的。

所以需要先求出所有在至少 $2$ 个 $b_i$ 中出现过的质因子 $p$：两两求 $\gcd$ ，如果 $\gcd$ 不为 $1$ 就是一个 “公共质因子”（为什么？想一想 $^3$）。

然后对于每个 $b_i$：

- 对于每个 $p_j$，如果 $p_j|b_i$，那么将质因子 $p_j$ 的计数器加上 $num_i$。

- 设 $b_i$ 不在 $p$ 中的质因子个数为 $c$，则将答案乘上 $(num_i+1)^c$。

最后对于所有质因子计数器（即 map 里所有的 ``pair <long long,int> it``），将答案乘上计数器的数值 $+1$（即 ```ans*=(it.second+1)```；为什么要加 $1$？想一想 $^4$），得到的结果就是最后的答案。

---

代码：

```cpp
/*
	Powered by C++11.
	Author : Alex_Wei.
*/

#include <bits/stdc++.h>
using namespace std;

//#pragma GCC optimize(3)
//#define int long long

#define ll long long
#define pii pair <int,int>
#define pll pair <ll,ll>
#define fi first
#define se second
#define pb push_back

const int N=2e6+5;
const int mod=998244353;

map <ll,int> fc,num;

ll sqr(ll x) {
	ll y=sqrt(x);
	return y*y==x?y:0;
}

ll cbr(ll l,ll r,ll v){
	if(l==r)return (l*l*l==v?l:0);
	ll m=l+r>>1;
	return m*m*m>=v?cbr(l,m,v):cbr(m+1,r,v);
}

bool check(ll x) {
	ll y=sqr(x);
	if(y){
		ll z=sqr(y);
		z?fc[z]+=4:fc[y]+=2;
		return 1;
	}
	else{
		y=cbr(1,2e6,x);
		if(y) {fc[y]+=3; return 1;}
	} return 0;
}

ll n,a[N],ans=1;
vector <ll> buc;

int main() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		ll x; cin>>x;
		if(!check(x)) {
			if(!num[x])buc.pb(x);
			num[x]++;
		}
	}
	for(int i=0;i<buc.size();i++)
		for(int j=i+1;j<buc.size();j++){
			ll x=__gcd(buc[i],buc[j]);
			if(x>1&&fc.find(x)==fc.end())fc[x]=0;
			// 这里必须加 fc.find(x)==fc.end()，不然会收获 WA on test 14 
		}
	for(ll i:buc){
		int c=2,d=num[i];
		for(pll it:fc) if(i%it.fi==0) fc[it.fi]+=d,c--;
		ans=ans*(c==0?1:(c==1?d+1:(d+1)*(d+1)))%mod;
	}
	for(pll it:fc) ans=ans*(it.se+1)%mod;
	cout<<ans<<endl;
	
	return 0;
}
```

---

注释：

$1$：根据因数个数定理和题目条件，当质因子个数为 $1$ 时有 $3\leq c+1\leq 5$，所以 $2\leq c\leq 4$。

$2$：根据因数个数定理和题目条件，当质因子个数为 $2$ 时有 $3\leq (c_1+1)(c_2+1) \leq 5$。又因为 $c_1,c_2$ 都是正整数，所以 $c_1=c_2=1$。

$3$：设 $\gcd(b_i,b_j)=p\ (p\neq 1)$，因为 $b_i\neq b_j$ 且都是两个质因子的乘积，所以 $b_i$ 或 $b_j$ 不可能是另外一个数的倍数，即 $p\neq b_i,b_j$。又因为 $p\neq 1$，所以 $p$ 只可能是 $b_i,b_j$ 的公共质因子。

$4$：根据因数个数定理 $d(n)=\prod (a_i+1)$ 易知。

求赞 qwq。

---

2021.1.23：修改一处错误。

---

## 作者：peterwuyihong (赞：5)

垃圾题目，卡常。

使用 Pollard-rho ，把所有质数与指数算出来，思维难度： xxs 。

卡常难度：WC2017 挑战（误。

从网上贺来了各种最快的板子，拼凑起来极草。

优化小妙招： [更快地分解质因数](https://www.luogu.com.cn/blog/Peterprpr/sp30755) 。

丑代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Fastio {
struct Reader {
	template<typename T>
	Reader& operator >> (T& x) {
		char c = getchar();
		T f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		x = 0;
		while (c >= '0' && c <= '9') {
			x = x * 10 + (c - '0');
			c = getchar();
		}
		x *= f;
		return *this;
	}
	Reader& operator >> (char& c) {
		c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		return *this;
	}
	Reader& operator >> (char* str) {
		int len = 0;
		char c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		while (c != '\n' && c != ' ') {
			str[len++] = c;
			c = getchar();
		}
		str[len] = '\0';
		return *this;
	}
	Reader(){}
} cin;
const char endl = '\n';
struct Writer {
	template<typename T>
	Writer& operator << (T x) {
		if (x == 0) { putchar('0'); return *this; }
		if (x < 0) { putchar('-'); x = -x; }
		static int sta[45];
		int top = 0;
		while (x) { sta[++top] = x % 10; x /= 10; }
		while (top) { putchar(sta[top] + '0'); --top; }
		return *this;
	}
	Writer& operator << (char c) {
		putchar(c);
		return *this;
	}
	Writer& operator << (char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer& operator << (const char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer(){}
} cout;
} // namespace Fastio
#define cin Fastio :: cin
#define cout Fastio :: cout
#define endl Fastio :: endl
/* --------------- fast io --------------- */ // end
#define int long long
#define maxn 1000010
long long gcd(long long a, long long b) {
    int ret = 0;
    while(a) {
        for( ; !(a & 1) && !(b & 1); ++ret, a >>= 1, b >>= 1);
        for( ; !(a & 1); a >>= 1);
        for( ; !(b & 1); b >>= 1);
        if(a < b) swap(a, b);
        a -= b;
    }
    return b << ret;
}
inline long long mod_add(long long x, long long y, long long m){
    return (x += y) < m ? x : x - m;
}
inline long long ksc(long long x, long long y, long long m){
    long long res = x * y - (long long)((long double)x * y / m + 0.5) * m;
    return res < 0 ? res + m : res;
}
int Abs(int a){
	if(a>=0)return a;
	return -a;
}
int ksm(int a,int b,int p){
	int ans=1;
	for(;b;b>>=1,a=ksc(a,a,p))
	if(b&1)ans=ksc(ans,a,p);
	return ans;
}
signed pri[maxn],lpf[maxn],tot;
void shai(int n){
	for(int i=2;i<=n;i++){
		if(!lpf[i])pri[lpf[i]=++tot]=i;
		for(int j=1;j<=lpf[i]&&i*pri[j]<=n;j++)lpf[i*pri[j]]=j;
	}
}
const int p[] = {2, 3, 5, 7, 17, 19, 61};
bool MR(int n) {
	if(n<=1000000)return pri[lpf[n]]==n;
    if (n == 1)
        return 0;
    int i;
    for (i = 0; i < 7; ++i)
        if (!(n % p[i]))
            return n == p[i];
    int r = n - 1, x, y;
    int j, t = 0;
    while (!(r & 1))
        r >>= 1, ++t;
    for (i = 2; i < 7; ++i) {
        for (j = 0, y = ksm(p[i], r, n); j < t && y > 1; ++j)
            x = y, y = (__int128)x * x % n;
        if (y > 1 || (j && x != n - 1))
            return 0;
    }
    return 1;
}
int f(int x,int c,int n){
	return ((__int128)x*x+c)%n;
}
long long seq[maxn];
long long PR(long long n){
    while (1){
        long long x = rand() % n, y = x, c = rand() % n, u = 1, v, t = 0;
        long long *px = seq, *py = seq;
        while (1){
            *py++ = y = mod_add(ksc(y, y, n), c, n);
            *py++ = y = mod_add(ksc(y, y, n), c, n);
            if((x = *px++) == y) break;
            v = u;
            u = ksc(u, abs(y - x), n);
            if (!u) return gcd(v, n);
            if (++t == 32){
                t = 0;
                if ((u = gcd(u, n)) > 1 && u < n) return u;
            }
        }
        if (t && (u = gcd(u, n)) > 1 && u < n) return u;
    }
}
signed n;
int x;
long long ans=1;
const int P=998244353;
unordered_map<int,int>M;
vector<int>G;
vector<int>fac(int x){
	vector<int>v,w;
	if(x<=1000000){
		while(x-1)v.push_back(pri[lpf[x]]),x/=pri[lpf[x]];
		return v;
	}
	if(MR(x))return vector<int>{x};
	int p=x;
	while(p==x)p=PR(x);
	v=fac(p),w=fac(x/p);
	v.insert(v.end(),w.begin(),w.end());
	sort(v.begin(),v.end());
	return v;
}
signed main(){
	cin>>n;
	shai(1000000);
	for(int i=1;i<=n;i++){
		cin>>x,G=fac(x);
		for(auto j:G)M[j]++;
	}
	for(auto it:M)
	ans=ans*(it.second+1)%P;
	cout<<ans;
}
```


---

## 作者：BLUESKY007 (赞：4)

安利一下自己的博客$qwq$[戳这里^__^](https://www.cnblogs.com/--BLUESKY007/)   
题目大意:给定$n(1\leq n\leq500)$个数$a_1,a_2\cdots,a_n(1\leq a_i\leq2\cdot10^{18})$,每个数有$3\sim5$个因数,求$\prod_{i=1}^{n}a_i$的因数个数  
这道题是一个交互题(虽说并不觉得有交互的必要...可能只是为了$hack$或者造数据方便吧),非常纯的数$(du)$学$(liu)$,题目难度不在于结论,而在于代码实现  
小学数学告诉我们以下结论:一个正整数$x$可以被分解成唯一形式$x=p_{1}^{a_{1}}\cdot p_{2}^{a_{2}}\cdot \cdots \cdot p_{k}^{a_{k}}(p_i\text{为质数})$,$x$的因数个数为$\prod_{i=1}^{k}(a_i+1)$.所以这道题的本质是质因数分解.  
对于一个数$x$进行质因数分解最快的方式是枚举$2\sim\sqrt{x}$的质数$p$判断$p$是否能整除$x$进行分解,但是题目数据范围$a_i\leq10^{18}$,如果要对$a_i$直接质因数分解需要枚举$2\sim10^9$内所有质数,若按照这种思路还需要预处理$10^9$内的质数表.  
但是这样做并不可行,$10^9$内的质数表即使用线性筛也无法在$1s$和$256M$的限制内完成.此时注意到题目上还有未使用到的条件:每个数有$3\sim5$个因数.所以此题唯一的入手点就是这个具有奇特性质的条件.  
考虑一个数$x$有$3\sim5$个因数可能的特殊性质,发现$x$有$(1)p_1\cdot p_2,(2)p_1^2,(3)p_1^3,(4)p_1^4$四种可能的分解形式,对于$(2)(3)(4)$三种分解形式,我们可以考虑二分求出$p_1$($cmath$并不支持求$\sqrt[3]{x},\sqrt[4]{x}$),如果满足$(2)(3)(4)$中任意一种分解,那么直接计数即可,如果三种分解形式都不满足,那么考虑对于$p_1\cdot p_2$形式的数的分解,如果$p_1,p_2$的次数都为$1$那么可以不分解这样的$x$,直接乘$(cnt+1)^2$,如果$p_1,p_2$的次数有至少一个不为$1$,那么对于$x$一定存在一个数$y(y\neq x)$使得$gcd(x,y)>1$,此时的$gcd(x,y)$就是$x,y$的一个质因数,也即$x,y$都完成了质因数分解.至此所有可分解的数都完成了质因数分解,不可分解的数都满足两个质因数次数为$1$,所以剩下的只需要求$\prod_{i=1}^{k}(a_i+1)$即可.  
下面放$AC$代码$\downarrow\downarrow\downarrow$  
```cpp
#include<cstdio>//CF1033D
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<map>

using namespace std;

const int MOD=998244353;

int n;

long long a[502];

map<long long,long long>mp,mmp;

long long gcd(long long u,long long v){
    if(v==0){
        return u;
    }
    return gcd(v,u%v);
}

long long bs2(long long l,long long r,long long u){
    if(l==r){
        return l;
    }
    long long mid=(l+r)>>1;
    if(mid*mid<u){
        return bs2(mid+1,r,u);
    }
    else{
        return bs2(l,mid,u);
    }
}

long long bs3(long long l,long long r,long long u){
    if(l==r){
        return l;
    }
    long long mid=(l+r)>>1;
    if(mid*mid*mid<u){
        return bs3(mid+1,r,u);
    }
    else{
        return bs3(l,mid,u);
    }
}

long long bs4(long long l,long long r,long long u){
    if(l==r){
        return l;
    }
    long long mid=(l+r)>>1;
    if(mid*mid*mid*mid<u){
        return bs4(mid+1,r,u);
    }
    else{
        return bs4(l,mid,u);
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n;i++){
        long long rep;
        rep=bs4(1,40000,a[i]);
        if(rep*rep*rep*rep==a[i]){
            mp[rep]+=4;
            continue;
        }
        rep=bs3(1,1300000,a[i]);
        if(rep*rep*rep==a[i]){
            mp[rep]+=3;
            continue;
        }
        rep=bs2(1,1500000000,a[i]);
        if(rep*rep==a[i]){
            mp[rep]+=2;
            continue;
        }
        bool flag=false;
        for(auto ite:mp){
            if(a[i]%ite.first==0){
                mp[ite.first]++;
                mp[a[i]/ite.first]++;
                flag=true;
                break;
            }
        }
        if(!flag){
            for(auto ite2:mmp){
                if(ite2.first==a[i]){
                    mmp[a[i]]++;
                    flag=true;
                    break;
                }
                long long g=gcd(a[i],ite2.first);
                if(g>1){
                    mp[g]+=ite2.second+1;
                    mp[a[i]/g]++;
                    mp[ite2.first/g]+=ite2.second;
                    mmp[ite2.first]=0;
                    flag=true;
                    break;
                }
            }
        	if(!flag){
           		mmp[a[i]]++;
        	}
        }
    }
    for(auto ite2:mmp){
        for(auto ite:mp){
            if(ite2.first%ite.first==0){
                mp[ite.first]+=ite2.second;
                mp[ite2.first/ite.first]+=ite2.second;
                mmp[ite2.first]=0;
                break;
            }
        }
    }
    long long ans=1;
    for(auto ite:mp){
        ans*=(ite.second+1);
        ans%=MOD;
    }
    for(auto ite:mmp){
        ans*=(ite.second+1);
        ans%=MOD;
        ans*=(ite.second+1);
        ans%=MOD;
    }
    printf("%lld\n",ans);
    fflush(stdout);
    return 0;
}
```

---

## 作者：npqenqpve (赞：3)

- 考虑约数个数定理，设分解质因数后质数 $p_i$ 的指数为 $a_i$，那么约数个数为所以 $a_i+1$ 的乘积，就可以只统计质因子及其指数
- 很明显，有 $3\sim5$ 个因子的数只可能是
  1. 两个素数的积
  2. 某素数的 $2 \sim 4$ 次方
- 对于情况2，可以使用 pow 函数来开根，但是有精度问题，建议二分求得。
- 情况1略微复杂，考虑该情况下，如果 $a_i$ 的质因子集合不与任何 $a_j$ 的质因子集合有交，则答案应该 $ans\gets ans\times2$，否则总是和某个数有非 $1$ 的公因子，由于情况1的 $a_i$ 不会与 $a_j$ 倍数关系（这里暂时不考虑相等），所以总存在 $j$ 满足 $i\neq j$ 且 $\gcd(a_i,a_j)\neq 1$，即 $a_i$ 的某个质因子，从而将 $a_i$ 分解。
- coner case：存在两数相等的情况。

---

## 作者：Priestess_SLG (赞：0)

~~季度绳操，这题为什么打了一个交互的 tag 啊~~

首先这个题可以 Pollard-Rho 分解每一个质因数。但是因为这是~~可爱 [aimat](/user/746544) 姐姐出模拟赛~~才会干的事，所以需要思考一个更加聪明的算法。

记 $d(x)$ 表示 $x$ 所有不同正因子的数量。

对于每一个 $a_i$，考虑分类讨论：

+ $d(a_i)=3$，此时 $a_i=p^2$，$p\in\text{prime}$。
+ $d(a_i)=5$，此时 $a_i=p^4$，$p\in\text{prime}$。
+ $d(a_i)=4$，此时 $a_i=p^3$，$p\in\text{prime}$。
+ $d(a_i)=4$，此时 $a_i=p_1p_2$，$p_1,p_2\in\text{prime}$。

前三种情况都很简单，可以直接二分求解，最后一种情况可以 Pollard-Rho 找出其的两个质因数，？？？

> [Milthm](/user/761125)：我想把你做成我的晚餐！！！
>
> [Milthm](/user/761125)：我想把你做成掉渣饼

发现 $n\le 500$，这么好的条件，怎么能不利用！然后发现其实不需要直到每一个质因子具体的值，其实只需要知道她们相对出现的次数。因此考虑把所有上面第 $4$ 类情况的数全部存储下来，然后枚举每一个数对 $(a_i,a_j)$，并分类讨论：

+ $\gcd(a_i,a_j)=1$，则两个数的质因子之间互相独立。
+ $\gcd(a_i,a_j)=p$，$p\in\text{prime}$，则两个数之间共用了一个质因子 $p$。
+ $\gcd(a_i,a_j)=a_i$，此时 $a_i$ 必须等于 $a_j$，两个数共用两个相同的质因子。

最后直接一遍扫描把所有的质因子出现的次数增加 $1$ 然后乘起来，就得到了答案。

代码：

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define int long long
#define F(i,x,y) for(int i=x;i<=y;++i)
#define G(i,x,y) for(int i=x;i>=y;--i)
#define FD(x,y) for(int i=x;i*i<=y;++i)
#define GD(x,y) for(int i=x;i*i>=y;--i)
#define adde(x,y) z[x].eb(y);
#define Adde(x,y) z[x].eb(y),z[y].eb(x)
#define addew(x,y,w) z[x].eb(y,w)
#define Addew(x,y,w) z[x].eb(y,w),z[y].eb(x,w)
#define FIMX(X) memset(X,0x3f,sizeof X)
#define FIMI(X) memset(X,-0x3f,sizeof X)
#define FI0(X) memset(X,0,sizeof X)
#define FIN(X) memset(X,-1,sizeof X)
#define PII pair<int,int>
#define PDD pair<double,double>
#define PIII tuple<int,int,int>
#define rng(X) X.begin(),X.end()
#define VI vector<int>
#define VII vector<PII>
#define VD vector<double>
using ull=unsigned long long;
using namespace std;
const int N=5010,mod=998244353;
int a[N];
unordered_map<int,int>mp,en;
signed main(){
    int n;cin>>n;
    F(i,1,n)cin>>a[i];
    F(i,1,n){
        {int t=sqrtl(sqrtl(a[i]));
        if(t*t*t*t==a[i]){mp[t]+=4;continue;}}
        {int t=cbrtl(a[i]);
        if(t*t*t==a[i]){mp[t]+=3;continue;}}
        {int t=sqrtl(a[i]);
        if(t*t==a[i]){mp[t]+=2;continue;}}
        int G=a[i];
        F(j,1,n)
            if(__gcd(a[i],a[j])!=1&&__gcd(a[i],a[j])!=a[i])G=__gcd(a[i],a[j]);
        ++mp[G];if(G==a[i])++en[G];else ++mp[a[i]/G];
    }
    int s=1;
    for(auto &[_,x]:mp)s=s*(x+1)%mod;
    for(auto &[_,x]:en)s=s*(x+1)%mod;
    cout<<s<<'\n';
    return 0;
}
```

---

