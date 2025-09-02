# Battling with Numbers

## 题目描述

On the trip to campus during the mid semester exam period, Chaneka thinks of two positive integers $ X $ and $ Y $ . Since the two integers can be very big, both are represented using their prime factorisations, such that:

- $ X=A_1^{B_1}\times A_2^{B_2}\times\ldots\times A_N^{B_N} $ (each $ A_i $ is prime, each $ B_i $ is positive, and $ A_1<A_2<\ldots<A_N $ )
- $ Y=C_1^{D_1}\times C_2^{D_2}\times\ldots\times C_M^{D_M} $ (each $ C_j $ is prime, each $ D_j $ is positive, and $ C_1<C_2<\ldots<C_M $ )

Chaneka ponders about these two integers for too long throughout the trip, so Chaneka's friend commands her "Gece, deh!" (move fast) in order to not be late for the exam.

Because of that command, Chaneka comes up with a problem, how many pairs of positive integers $ p $ and $ q $ such that $ \text{LCM}(p, q) = X $ and $ \text{GCD}(p, q) = Y $ . Since the answer can be very big, output the answer modulo $ 998\,244\,353 $ .

Notes:

- $ \text{LCM}(p, q) $ is the smallest positive integer that is simultaneously divisible by $ p $ and $ q $ .
- $ \text{GCD}(p, q) $ is the biggest positive integer that simultaneously divides $ p $ and $ q $ .

## 说明/提示

In the first example, the integers are as follows:

- $ X=2^2\times3^1\times5^1\times7^2=2940 $
- $ Y=3^1\times7^1=21 $

The following are all possible pairs of $ p $ and $ q $ :

- $ p=21 $ , $ q=2940 $
- $ p=84 $ , $ q=735 $
- $ p=105 $ , $ q=588 $
- $ p=147 $ , $ q=420 $
- $ p=420 $ , $ q=147 $
- $ p=588 $ , $ q=105 $
- $ p=735 $ , $ q=84 $
- $ p=2940 $ , $ q=21 $

In the third example, the integers are as follows:

- $ X=2^1\times5^1=10 $
- $ Y=2^1\times3^1=6 $

There is no pair $ p $ and $ q $ that simultaneously satisfies $ \text{LCM}(p,q)=10 $ and $ \text{GCD}(p,q)=6 $ .

## 样例 #1

### 输入

```
4
2 3 5 7
2 1 1 2
2
3 7
1 1```

### 输出

```
8```

## 样例 #2

### 输入

```
2
1299721 1999993
100000 265
2
1299721 1999993
100000 265```

### 输出

```
1```

## 样例 #3

### 输入

```
2
2 5
1 1
2
2 3
1 1```

### 输出

```
0```

# 题解

## 作者：One_JuRuo (赞：3)

## 思路

首先对于 $p$ 和 $q$，他们都必须是 $Y$ 的倍数，不然 $\gcd$ 就不是 $Y$ 了。

再算出来 $\frac X Y$ 的值，当然如果 $X$ 不是 $Y$ 的倍数，那肯定无解。

因为此题特殊的输入方式，所以我们可以很轻易的得到 $\frac X Y$ 的质因子和个数。

那么对于 $\frac X Y$ 中的一种质因子，要么全给 $p$，要么全给 $q$，如果 $p$ 给一些，$q$ 给一些，$\gcd$ 就会比 $X$ 大，所以一个质因子有两种选择，假设 $\frac X Y$ 有 $k$ 个不同的质因子，那么答案就是 $2^k$。记得答案要取模哦。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long n,m,a[100005],b,ans=1;
map<long long,long long>p1,p2;
inline long long qsm(long long a,long long b)
{
	long long ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%mod;
		a=a*a%mod,b>>=1;
	}
	return ans;
}
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;++i) scanf("%lld",&a[i]);
	for(long long i=1;i<=n;++i) scanf("%lld",&b),p1[a[i]]=b;
	scanf("%lld",&m);
	for(long long i=1;i<=m;++i) scanf("%lld",&a[i]);
	for(long long i=1;i<=m;++i) scanf("%lld",&b),p2[a[i]]=b;
	for(auto i:p2)
	{
		if(p1[i.first]<i.second) printf("0"),exit(0);
		if(p1[i.first]-i.second) ans=ans*2%mod;
		p1[i.first]=0;
	}
	for(auto i:p1)
	{
		if(i.second) ans=ans*2%mod;
	}
	printf("%lld",ans);
	return 0;
}
 
```

---

## 作者：Falling_Sakura (赞：2)

# 思路

显然，$p$ 和 $q$ 的 $\gcd$ 和 $\operatorname{lcm}$ 满足如下性质：

设 $f_i(p)$ 表示 $p$ 中 $i$ 这个质因子的指数，$S$ 为 $p$ 和 $q$ 的质因子集合的并集。

$\gcd(p,q)$ 是 $p$ 和 $q$ 质因子的最小交集，即 $\forall i\in S,f_i(\gcd(p,q))=\min(f_i(p),f_i(q))$。

同理，$\forall i\in S,f_i(\operatorname{lcm}(p,q))=\max(f_i(p),f_i(q))$。

现在已知：$\operatorname{lcm}(p,q)=X,\gcd(p,q)=Y$，那么就有以下三种情况：

- $\exists i\in S,f_i(X)<f_i(X)$ 直接输出 0，因为不存在一组 $p,q$ 满足条件。
- $f_i(X)=f_i(Y)$，这个时候只有一种情况，即 $f_i(p)=f_i(q)=f_i(X)=f_i(Y)$。
- $f_i(X)>f_i(Y)$，这个时候有两种情况：
	- $f_i(p)=f_i(X),f_i(q)=f_i(Y)$
	- $f_i(p)=f_i(Y),f_i(q)=f_i(X)$

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;
typedef long long LL;
const int MOD = 998244353;

map<int, int> s1, s2; // X Y 中对应的指数
set<int> s;
int n, m, ans = 1;
int a[N], b[N], c[N], d[N];

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]), s.insert(a[i]);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &b[i]);
        s1[a[i]] = b[i];
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++)
        scanf("%d", &c[i]), s.insert(c[i]);
    for(int i = 1; i <= m; i++)
    {
        scanf("%d", &d[i]);
        s2[c[i]] = d[i];
    }
    for(auto &i : s)
    {
        if(s1[i] < s2[i])
        {
            cout << 0 << endl;
            return 0;
        }
        else if(s1[i] == s2[i]) continue;
        else ans = ans * 2 % MOD;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Czy_Lemon (赞：1)

### 大致题意

给你两个质因数分解之后的 $X$ 和 $Y$，让你求有多少对 $(p,q)$ 使得 $\gcd(p,q)=Y,\operatorname{lcm}(p,q)=X$。

### 题目解析

我们可以发现，如果存在 $(p,q)$ 使得 $\gcd(p,q)=Y,\operatorname{lcm}(p,q)=X$，那么 $X$ 为 $Y$ 的倍数。

也就是说当 $X$ 不是 $Y$ 的倍数的时候，答案为 $0$。

然后我们考虑一个 $X$ 的因数 $A_i^{B_i}$：

- 如果 $Y$ 中不存在 $B_i=A_i$，那么可以将 $A_i^{B_i}$ 加入 $p$ 或 $q$ 都可以，有两种情况，$ans=ans \times 2$。
- 如果 $Y$ 中存在 $B_i=A_i$ 且它们对应的指数不相等（但是要保证 $B_i>D_i$，否则 $X$ 就不为 $Y$ 的倍数）那么可以分别放入 $p$ 或 $q$，$ans=ans \times 2$。
- 如果 $Y$ 中存在 $B_i=A_i$ 且它们对应的指数相等，那么放入 $p$ 或 $q$ 没有区别，$ans=ans \times 1$。

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1e5+10;
const int M=2e6+10;
const int mod=998244353;
int n,m,a[N],b[N],c[N],d[N];
int pf[M]={0},qf[M]={0};
inline void input(){
	scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++) scanf("%d",&c[i]);
    for(int i=1;i<=m;i++) scanf("%d",&d[i]);
}
inline void slove(){
	//check if X|Y
	for(int i=1;i<=n;i++) pf[a[i]]=b[i];
	for(int i=1;i<=m;i++) qf[c[i]]=d[i];
	for(int i=1;i<=m;i++){
		//printf("%d : %d %d\n",c[i],pf[c[i]],qf[c[i]]);
		if(pf[c[i]]<qf[c[i]]){
			printf("0\n");
			return;
		}
	}
	//check the number of different factors
	int ans=1;
	for(int i=1;i<=n;i++)
		if(pf[a[i]]>qf[a[i]])
			ans=ans*2%mod;
	printf("%d\n",ans);
	return;
}
int main(){
    input();
    slove();
    return 0;
}
```

[CodeForces](https://codeforces.com/contest/1866/submission/222551981)

---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1866B)

挺简单的。

先讲一下 $\gcd(p,q)$ 的计算方式：对于一个数 $i$，$\gcd(p,q)$ 中将 $i$ 作为质因数所对应的次幂为 $i$ 在 $p$ 与 $q$ 中当质因数所对应的次幂中最小的哪一个，$\text{lcm}(p,q)$ 为最大的那一个。

首先明显的，$X$ 必须是 $Y$ 的倍数，否则你无法找到一个 $p$ 和 $q$ 使得 $\text{lcm}(p,q)=X$ 且 $\gcd(p,q)=Y$。这一个明显就是小学知识。

接下来，我们有一个数 $i$ 以及它在 $X$ 中作为质因数的次幂 $t_i$ 和在 $Y$ 中作为质因数的次幂 $tt_i$。

如果对于其中一个 $i$，$tt_i>t_i$，那么就说明 $X$ 不是 $Y$ 的倍数，直接输出 $0$。

如果 $tt_i<t_i$，那么我们可以考虑把 $i^{tt_i}$ 放在 $p$ 的因数集内，也可以把 $i^{t_i}$ 放在 $p$ 的因数集内，有 $2$ 种情况。并且这里我们并不能把诸如 $i^{tt_i+1}$ 这种数放在 $p$ 的因数集内，否则就会因为计算方式导致 $i$ 在 $\gcd(p,q)$ 中的次幂变为 $tt_i+1$，但我们要的是 $tt_i$，所以不可行。

如果是 $tt_i=t_i$，那么由于两数相等，选哪个放在 $p$ 中都无所谓，有 $1$ 种情况。

[AC记录及代码](https://codeforces.com/contest/1866/submission/222458713)

---

## 作者：zzy0618 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1866B)

### 大体思路

最好判断的一种无解的情况，就是 $X$ 不是 $Y$ 的倍数。根据题目给出的特殊输入，只需判断对于 $Y$ 的每个质因子，$X$ 是否比它含有相同甚至更多的这个质因子。

然后是计算数对的数量。

如果 $\gcd(x,y)=z$，则 $x,y$ 必然是 $z$ 的倍数。

对于 $\frac{X}{Y}$ 每一种质因子，我们只能把它所有的个数全部给 $p$ 或 $q$，不然他们的 $\gcd$ 就会变大。因此，对于这个质因子，我们只需要将答案乘以 $2$ 即可。

过程中，只需要另开一个 ```map```，得出 $\frac{X}{Y}$ 的表示，分类判断。

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,mod=998244353;
int n,m,ans=1;
int a[N],b[N];//有了 map，没有按照题目给出的开数组
map<int,int> mp;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1,x;i<=n;++i)cin>>x,mp[a[i]]+=x;
	cin>>m;
	for(int i=1;i<=m;++i)cin>>b[i];
	for(int i=1,x;i<=m;++i)cin>>x,mp[b[i]]-=x;
	for(map<int,int>::iterator it=mp.begin();it!=mp.end();++it){
		if(it->second<0){cout<<0;return 0;}//无解
		if(it->second>0)ans=ans*2%mod;//注意是大于 0
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：jr_inf (赞：0)

前置知识：如果 $p=x^a,q=x^b$，那么 $\gcd(p,q)=x^{\min(a,b)},\operatorname{lcm}(p,q)=x^{\max(a,b)}$。

对于每个 $x \in a_i$，令 $x$ 在 $Y$ 中的指数为 $d_i$（实际上不一定），计算贡献时，考虑将 $b_i$ 与 $d_i$ 分别放入 $p$ 和 $q$ 中：
- 如果 $b_i < d_i$，贡献为 $0$。（不存在 $\operatorname{lcm}(p,q) < \gcd(p,q)$ 的情况）
- 如果 $b_i = d_i$，贡献为 $1$。（在下面代码中表现为不乘）
- 如果 $b_i > d_i$，贡献为 $2$。

最后将每个 $x \in a_i$ 的贡献相乘，即为答案。

code:
```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
const int N=1e5+10,mod=998244353;
int ans=1,n,m,a[N],b[N],c[N],d[N];
map<int,int> ma,ma2;
signed main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]),ma2[a[i]]=b[i];
	scanf("%d",&m);
	for(int i=1;i<=m;i++)scanf("%d",&c[i]);
	for(int i=1;i<=m;i++)scanf("%d",&d[i]),ma[c[i]]=d[i];
	for(int i=1;i<=n;i++)if(b[i]>ma[a[i]])ans=ans*2%mod;
	for(int i=1;i<=m;i++)if(ma2[c[i]]<ma[c[i]])ans=0;
	printf("%d",ans);
}
```


---

## 作者：wanghaoran00 (赞：0)

### 翻译
一个可以分解为 $\prod_{i = 1}^{n} A_{i}^{B_{i}}$ 的数 $x$ 和一个可以分解为 $\prod_{i = 1}^{m} C_{i}^{D_{i}}$ 的数 $y$，求满足 $\operatorname{lcm}(x,y)=x$，$\gcd(x,y)=y$ 的 $ans \bmod 998244353$ 有多少对。$A_{i}$ 和 $C_{i}$ 为递增的质数。

### 思路

~~暴力出奇迹~~，每存在一个 $y$ 存在 $x$ 不存在的因数，则无法构成最大公因数为 $x$ 输出 $0$ 其他乘 $2$ 即可。

AC code

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int ans,n,m,a[100005],b[100005],x,p[2000005],q[2000005];
signed main(){
	ans=1;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&x);
		p[a[i]]=x;
	}
	scanf("%lld",&m);
	for(int i=1;i<=m;i++){
		scanf("%lld",&b[i]);
	}
	for(int i=1;i<=m;i++){
		scanf("%lld",&x);
		q[b[i]]=x;
	}
	for(int i=0;i<=2000000;i++){
		if(p[i]<q[i]){
			printf("0");
			return 0;
		}
		if(p[i]>q[i]){
			ans*=2;
			ans%=998244353;
		}
	}
	cout<<ans;
	return 0;
}
```

---

