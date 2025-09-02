# Fadi and LCM

## 题目描述

Today, Osama gave Fadi an integer $ X $ , and Fadi was wondering about the minimum possible value of $ max(a, b) $ such that $ LCM(a, b) $ equals $ X $ . Both $ a $ and $ b $ should be positive integers.

 $ LCM(a, b) $ is the smallest positive integer that is divisible by both $ a $ and $ b $ . For example, $ LCM(6, 8) = 24 $ , $ LCM(4, 12) = 12 $ , $ LCM(2, 3) = 6 $ .

Of course, Fadi immediately knew the answer. Can you be just like Fadi and find any such pair?

## 样例 #1

### 输入

```
2```

### 输出

```
1 2```

## 样例 #2

### 输入

```
6```

### 输出

```
2 3```

## 样例 #3

### 输入

```
4```

### 输出

```
1 4```

## 样例 #4

### 输入

```
1```

### 输出

```
1 1```

# 题解

## 作者：Aw顿顿 (赞：7)

## 题意

给定一个 $x$，存在一些二元组 $(a,b)$，使得 $\text{lcm}(a,b)=x$。

要求找出这些二元组中，使得 $\max(a,b)$ 最小的那个二元组。

## 解法

假设存在一个不互质的二元组 $(a,b)$，满足题目条件，不妨设 $a\le b$，那么：

$\left(a,\dfrac{b}{\gcd(a,b)}\right)$ 依然是一组满足条件的二元组，并且使得 $\max(a,b)$ 更小了。

对于新的这一个二元组，我们可以继续进行这个操作，直到两个数互质，那么，我们可以得出结论：**题目所求的二元组，一定满足 $a$ 与 $b$ 互质**，或者说是 $\gcd(a,b)=1$。

那么我们可以考虑枚举 $i$，枚举范围从 $1$ 到 $\sqrt{x}$，如果 $i$ 不是 $x$ 的因数，那么这个 $i$ 对于我们解题是没有帮助的，对于每一个剩下的 $i$，令：

$$a=i\qquad b=\dfrac{x}{i}$$

这时候注意几个显然的特性：

- $a\le b$，因为我们从小到大枚举。
- $a,b$ 一定是 $x$ 的因数。

此时，如果能够满足 $\text{lcm}(a,b)=x$，就取 $\min(res,b)$ 即可。

为什么是 $b$ 呢？因为 $b\ge a$ 啊。但是另一个问题是，为什么这么枚举呢——为什么不存在其他的解法呢？首先 $a,b\le x$ 是显然的，同时，我们已经证明了这两个数必然互质，那么这么枚举就是正确的。

我们只需要初始化存储 $b_{\min}$ 的变量即可，因为只有它决定了答案的大小，我们的 $a_{\min}$ 跟着它更新就行了。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int x,res1=9223372036854775807,res2;
signed main(void){
	cin>>x;
	for(int i=1;i*i<=x;++i){
		if(x%i)continue;//如果不是因数就跳过
		int a=i,b=x/i;//分配二元组
		if(a*b/__gcd(a,b)==x){//如果 lcm(a,b)=x
			res1=min(res1,b);//那么取最小值
			if(res1==b)res2=a;
            //如果取得了最小值，就更新另一个值
		}
	}cout<<res2<<" "<<res1;//输出
	return 0;
}
```

---

## 作者：Meatherm (赞：5)

不是楼下说的 $O(\sqrt n)$ 级别算法，多了一个 $\log$。

设 $a\leq b$ 且 $\text{lcm}(a,b)=X$。显然如果 $a,b$ 不互质，我们把 $b$ 约去一个 $\gcd(a,b)$ 之后 $\text{lcm}(a,b)$ 仍然是 $X$。而这一对 $a,b$ 比原来的小，所以可以得到一个结论，就是 $a,b$ 一定互质。

所以从 $1$ 到 $\sqrt{n}$ 枚举，找到最小的一对互质因数，它们的 $\text{lcm}=X$ 即可。

```cpp
# include <bits/stdc++.h>
# define int long long
# define rr register
using namespace std;
int X;
int ans=1e17;
int ansb;
signed main(void){
	cin>>X;
	for(rr int i=1;i*i<=X;++i){
		if(X%i)
			continue;
		int a=i,b=X/i;
		if(a*b/std::__gcd(a,b)==X){
			ans=std::min(ans,b);
			if(ans==b)
				ansb=a;
		}
	}
	cout<<ansb<<" "<<ans;
	return 0;
}
```

---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1285C)     
水题。    
首先，我们要明白一个事情：本题中，$\operatorname{lcm}(a,b)$ 是一定为 $a\times b$ 的。   
只有这样，才能让 $a$ 和 $b$ 尽量小。      
之后，我们枚举 $a$，范围是 $[1,\lfloor\sqrt{x}\rfloor]$。我们每一次枚举都要先判断范围内的数字是否是 $x$ 的因数，不是就跳过这一次枚举，是就继续。如果 $\operatorname{lcm}(a,x\div a)=x$，我们用一个变量来存枚举时 $a$ 的最大值。原因是因为这样的枚举下，$a\le b$。      
最后枚举结束，输出 $a$ 和 $x\div a$ 就可以。   
CODE：    
```
#include <iostream>
using namespace std;
inline long long gcd(long long a,long long b){//最大公因数
	return b?gcd(b,a%b):a;
}
inline long long lcm(long long a,long long b){//最小公倍数
	return a/gcd(a,b)*b;//防止溢出
}
inline long long max(long long a,long long b){//求最大值
	return a>b?a:b;
}
long long x,a,b,q,maxx;
int main(void){
	cin>>x;
	for(long long i=1;i<=x/i;i++){//枚举
		if(x%i){//不是x因数就跳过
			continue;
		}
		if(lcm(i,x/i)==x){//满足条件的就取
			maxx=max(maxx,i);
		}
	}
	cout<<maxx<<" "<<x/maxx;//输出
}
```


---

## 作者：时间重洗 (赞：1)

这道题是2020年1月10日CF比赛的C题（不用讲也都知道）

#### 题目大意：

给你一个整数x，找出一对满足：

1. 最小公约数为x
2. 两个数中最大的数最小

~~（本人语文及其不好，看不懂还是看翻译吧！）~~

#### 本人的想法

似乎许多大佬都是根号级算法。我在看题目的时候，最先想到的是~~暴力~~质因数分解

根据唯一定理 ，x=p1^a1 * p2^a2 * ...... * pk^ak

~~(我不会LaTeX，就将就一下吧）~~

那我们就将这k个数（将pi^ai看做一个数），分成两份，让分出来最大的数最小，就行了（若将pi^ai分成pi^(ai-k)和pi^k,最小公约数一定不是x，而两个数都选择x的因子，互质，就能满足最小）

#### 代码实现

由于这是暴力+质因数分解，代码很好理解的

```cpp
#include<cmath>
#include<stdio.h>
#include<cstring>
#include<iostream>
#include<algorithm>
//#define int long long
using namespace std;
const int MAXN=1005;
const int MAXM=1000005;
bool v[MAXM];  
int n,m,tot,ans1,ans2,a[MAXN],prime[MAXM];
inline int Max(int a,int b){return a<b?b:a;}
inline void primes(){
	memset(v,1,sizeof v);
	v[0]=v[1]=0;
	for(int i=2;i<=MAXM;i++){
		if(v[i]) prime[++m]=i;
		for(int j=1;j<=m;j++){
			if(i*prime[j]>MAXM) break;
			v[i*prime[j]]=0;
			if(i%prime[j]==0) break;
		}
	}
	return;
}
inline int Quickpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=ans*a;
		b/=2;a*=a;
	}
	return ans;
}
inline void work(int x){
	for(register int i=1;i<=m&&prime[i]*prime[i]<=x;++i)
		if(x%prime[i]==0){
			int sum=0;
			while(x%prime[i]==0){
				sum++;
				x/=prime[i];
			}
			a[++tot]=Quickpow(prime[i],sum);
		}
	if(x>1) a[++tot]=x;
}
inline void dfs(int i,int s1){
	if(i>tot){
		int Maxn=Max(s1,n/s1);
		//printf("%lld\n",Maxn);
		if(Maxn<ans2) ans1=n/Maxn,ans2=Maxn;
		return ;
	}
	dfs(i+1,s1);
	dfs(i+1,s1*a[i]);
}
template <typename T> void in(register T& a){
    register T x=0,f=1;
	register char c=getchar();
    while(!isdigit(c)){
	    c=='-'?f=-1:f=1;
		c=getchar();
	}
    while(isdigit(c)){
        x=(x<<1)+(x<<3)+c-'0';
	    c = getchar();
	}
    a=x*f;
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ans1=ans2=999999999999;
	in(n);
	primes();
	work(n);
	dfs(1,1);
	printf("%lld %lld",ans1,ans2);
	return o;
}
```


---

## 作者：ImNot6Dora (赞：0)

数学思维题。

首先发现，当 $a,b$ 两数最小时，$\operatorname{lcm}(a,b)=a\times b=x$。对于原理也非常好解释。举个例子，当 $x=48$ 时，可以选择 $\operatorname{lcm}(16,24)=48$，也可以选择 $\operatorname{lcm}(3,16)=48$，当然可以发现，第二种选择满足要求，而观察一下第二种数据，容易发现，$3\times16=48$！你可能会觉得这只是万分之一的概率，然而当你自己找几组数据的时候，发现所有的答案 $a,b$ 都满足 $\operatorname{lcm}(a,b)=a\times b=x$！其实这是必然的，因为 $a,b$ 互质时，$\max(a,b)$ 才**可能**最小。

既然如此，我们就枚举从 $1$ 到 $\sqrt{n}$ 的所有数字，当满足 $\operatorname{lcm}(a,b)=a\times b=x$ 的时候，我们就进行比较标记。

# AC C++ CODE：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll lcm(ll a,ll b){//求lcm 
	return a*b/__gcd(a,b);	
}
ll ans=LONG_LONG_MAX,ans1;
int main(){
	ll x;
	cin>>x;
	for(ll i=1;i*i<=x;i++){
		if(x%i==0&&lcm(i,x/i)==x){//此处i为a，x/i为b 
			if(ans>max(i,x/i)){//当max(a,b)更小 
				ans=max(i,x/i);//标记较大值 
				ans1=min(i,x/i);//标记较小值 
			}
		}
	} 
	cout<<ans1<<' '<<ans;//别忘了较小值先输出 
	return 0;
}

```
By ImNot6Dora

---

## 作者：Steve_xh (赞：0)

**2023/5/9：更新了一些由于作者实力有限而写错造成概念错误的点。**

# 题面

[题目传送门](https://www.luogu.com.cn/problem/CF1285C)

给定正整数 $X$，求两个数 $a,b$ 使 $a$ 和 $b$ 最大公倍数为 $X$ 并使 $a,b$ 最大值最小。

# 思路

首先我们要知道，求 $a$ 和 $b$ 的最小公倍数可以用 `a*b/__gcd(a,b)`，也就是 $a$ 和 $b$ 的乘积除以 $a$ 和 $b$ 的最大公约数。其中 `__gcd()` 是 C++ 自带的函数，能更加方便求最大公约数。

那么就剩下处理 $a$ 和 $b$ 了。怎么找呢？我们设 $A$ 和 $B$ 的最小公倍数为 $X$，则 $\gcd(X\div A,X\div B)=1$。这个大家都知道，但是还有一点，就是当 $A$ 和 $B$ 是 $X$ 的因数时，结果比当 $A$ 和 $B$ 非 $X$ 因数时要更优。为什么？因为当 $A$ 和 $B$ 为 $X$ 的因数时，$A$ 与 $B$ **互质**，我们看回求最小公倍数的方法，可以发现 $A$ 和 $B$ 不互质的时候 $A\times B>X$，则总是能找到另一个数 $C=X\div A$，$C$ 比 $B$ 小却 $A$ 和 $C$ 的最小公倍数是 $X$！这显然是更优的解法。

所以这样我们只需要从 $1$ 到 $\sqrt X$ 遍历就行了。时间复杂度 $O(\sqrt n)$，那么时间问题就解决了。那么剩下的根据题意模拟即可：若 $a,b$ 的最小公倍数等于 $X$ 并且 $a,b$ 的最大值小于俩答案最大值就更新答案。

# 代码

``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int x,ana=numeric_limits<int>::max(),anb=ana;//numeric_limits是我在上一届csp阅读程序学到的（笑）
inline int lcm(int a,int b){//方便求最小公倍数
    return a*b/__gcd(a,b);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>x;
    for(int i=1;i*i<=x;i++){
        if(x%i!=0)//如果不是x的因数直接跳过
            continue;
        int a=i,b=x/i;//是x的倍数，并且相乘为x
        if(lcm(a,b)==x&&max(a,b)<max(ana,anb))//题意模拟
                ana=a,anb=b;
    }
    cout<<ana<<" "<<anb;
    return 0;
}
```

---

## 作者：wz20201136 (赞：0)

既然要使 $\max(a,b)$ 最小，一定要让两个值都尽可能的小。考虑到只有当 $a$ 或 $b$ 中某质因子的次数等于 $X$ 中此质因子的个数时，才会对满足条件有帮助。所以只有 $a$ 和 $b$ 中的质因子次数都等于 $X$ 中此质因子次数或等于零，且 $X$ 中每个质因子都只在 $a$ 和 $b$ 中有且仅有出现一次时（也就是 $\gcd(a,b)=1$），才有可能取到最小的 $a$，$b$。

由于 $X$ 的质因子种类数很少（不会超过15个），可以直接分解质因数后暴力二进制枚举 $a$ 包含那些质因子，所有方案取最小值即可。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=15;
int p[MAXN],c[MAXN],num[MAXN],N,X;
signed main()
{
	cin>>X;
	int ans1=X,ans2=X;
	for(int i=2;i*i<=X;i++)
	{
		if(X%i!=0) continue;
		p[++N]=i,num[N]=1;
		while(X%i==0) c[N]++,X/=i,num[N]*=p[N];
	}
	if(X!=1) p[++N]=num[N]=X,c[N]=1;
	for(int s=0;s<(1<<N);s++)
	{
		int a1=1,a2=1;
		for(int i=1;i<=N;i++)
		{
			if(((1ll<<i-1)&s)!=0) a1*=num[i];
			else a2*=num[i];
		}
		if(max(a1,a2)<max(ans1,ans2)) ans1=a1,ans2=a2;
	}
	cout<<ans1<<' '<<ans2<<endl;
	return 0;
}
```

---

## 作者：jimmy2021 (赞：0)

对于一组题目描述中的 $(a, b)$，不妨设 $a \leq b$，那么我们可以构造另一组满足要求的二元组 $(a, \dfrac{b}{\gcd(a, b)})$，而且还使得 $\max(a, b)$ 更小了（下称这种操作为`二元组“变优”方案`）。

> Q：证明二元组 $(a, b)$ 与二元组 $(a, \dfrac{b}{\gcd(a, b)})$ 是等价的
> 
> A：根据最小公倍数公式 $\text{lcm}(a, b) = \dfrac{a \times b}{\gcd(a, b)}$，我们可以让 $b$ 去除以 $\gcd(a, b)$，而此时 $a$ 和 $b$ 就互质了，所以相当于将 $\text{lcm}(a, b)$ 先除以 $\gcd(a, b)$（对 $b$ 的操作），再乘 $\gcd(a, b)$（分母变为 $1$ 了，相当于乘分母），相当于没有操作，证毕。

所以我们直接枚举 $n$ 的各个因子（假设当前枚举的因子是 $i$），如果 $\text{lcm}(i, \dfrac{n}{i}) = n$，那么更新答案。

> Q：为什么这样枚举就可以枚举完所有答案呢？
> 
> A：因为 $i$ 与 $\dfrac{n}{i}$ 的乘积为 $n$，所以要让最小公倍数为 $n$，那么 $\gcd(i, \dfrac{n}{i})$ 一定为 $1$，所以无法按照上面二元组“变优”方案让其“变优”了。证毕。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <limits.h>
#include <cstring>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f, INF_BIT = 0x3f;

const int N = 1e5 + 10;

LL n;

LL gcd(LL a, LL b){
    return b ? gcd(b, a % b) : a;
}
LL lcm(LL a, LL b){
    return a / gcd(a, b) * b;
}

LL ansma = LLONG_MAX, ans1, ans2;

int main(){
    scanf("%lld", &n);
    
    for(LL i = 1;i <= n / i;i++){
        if(n % i) continue;
        if(lcm(i, n / i) != n) continue;
        if(ansma > n / i){
            ansma = n / i;
            ans1 = i, ans2 = n / i;
        }
    }
    
    printf("%lld %lld\n", ans1, ans2);
    return 0;
}
```

---

## 作者：Play_with (赞：0)

[CF1285C Fadi and LCM](https://www.luogu.com.cn/problem/CF1285C)
### [前置芝士](https://zhuanlan.zhihu.com/p/77669220)
------------
### 题意

给出一个数，求出以它为最小公倍数的一对数，且它们的最大值应尽量小。

------------
### 分析
我们规定那对数从小到大为 $a$ 和 $b$，题目给出的数为 $x$。  
于是有  

### $x=\operatorname{lcm}(a,b)=\dfrac{a \times b}{\gcd(a,b)}=\dfrac{a }{\gcd(a,b)}\times b$

再讨论这个式子。  

既然 $a$ 被除去了这对数的最小公倍数，所以它们在拆分后会互质。  
所以我们得到了本题的基础，$x$ 可以被拆分成互质的两个数。利用这一点，加上些许优化，可以得到几乎完美的代码。

------------
### 优化
STL 自带求最小公倍数的函数：
```cpp
__gcd( , )
```

同时，在枚举时若是从 $1$ 开始枚举，必须要将 $\sqrt{\smash[b]{x}}$ 个数全部历遍，因为 $a$ 的值是单调递增的。但若以此为原理，从 $\sqrt{\smash[b]{x}}$ 开始历遍，则只需将第一个符合条件的数输出即可。即使是最坏的情况，时间复杂度也仅为 $O(\sqrt{\smash[b]{x}})$。

------------
#### 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x;
int main(){
	cin>>x;
	for(long long i=sqrt(x);i;i--)
		if(x%i==0&&__gcd(i,x/i)==1){
			cout<<i<<" "<<x/i;
			return 0;//x有因数,且x和x/i互质
		}
}
```

---

