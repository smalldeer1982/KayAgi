# [Violet] 樱花

## 题目背景

又到了一年樱花盛开的时节。Vani 和妹子一起去看樱花的时候，找到了一棵大大的樱花树，上面开满了粉红色的樱花。Vani 粗略估计了一下，一共有足足 $n!$ 片花瓣。



Vani 轻柔地对她说：“你知道吗？这里面的一片花瓣代表着你，我从里面随机摘一片，能和你相遇的概率只有 $1/n!$ 那么小。我该是多么的幸运，才让你今天这么近地站在我面前。相信我，我一定会把这亿万分之一的缘分变为永远。”

粉红的樱花漫天飞舞，妹子瞬间被 Vani 感动了。她轻轻地牵起了他的手，和他相依而坐。这时，她突然看到田野的尽头也长着两棵樱花树，于是慢慢地把头靠在 Vani 的肩上，在他耳边低语：“看到夕阳里的那两棵樱花树了吗？其中一棵树上的一片花瓣是你，另一棵树上的一片花瓣是我，如果有人从这棵摘下一片，从那棵采下一瓣，我们相遇的概率会不会正好是 $1/n!$ 呢？”

Vani 的大脑飞速运作了一下，立即算出了答案。正要告诉妹子，她突然又轻轻地说：“以前你总是说我数学不好，但是这种简单的题我还是会算的。你看假如左边那棵树上有 $x$ 片花瓣，右边那个有 $y$ 片花瓣，那么我们相遇的概率不就是 $1/x+1/y$ 么，不过有多少种情况能使它正好可以等于 $1/n!$ 呢？这个你就帮我算一下吧～”

显然，面对天然呆的可爱妹子，Vani 不但不能吐槽她的渣数学，而且还要老老实实地 帮她算出答案哦。


## 题目描述

求方程：

$$\dfrac{1}{x} + \dfrac{1}{y} = \dfrac{1}{n!}$$ 

的正整数解的组数，答案对 $10^9+7$ 取模。

## 说明/提示

#### 样例 1 解释

共有三个数对 $(x,y)$ 满足条件，分别是 $(3,6),(4,4)$ 和 $(6,3)$。

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n\le 100$ 。
- 对于 $100\%$ 的数据，保证 $1 \le n\le 10^6$。


## 样例 #1

### 输入

```
2
```

### 输出

```
3```

## 样例 #2

### 输入

```
1439
```

### 输出

```
102426508```

# 题解

## 作者：Huami360 (赞：37)

做了题还是忍不住要写一发题解，感觉楼下的不易懂啊。
本题解使用latex纯手写精心打造。

题意：求$\frac{1}{x}+\frac{1}{y}=\frac{1}{n!}$的正整数解总数。

首先，不会线筛素数的先去做下[LuoguP3383](https://www.luogu.org/problemnew/show/P3383)。

开始推导。

$$\frac{1}{x}+\frac{1}{y}=\frac{1}{n!}$$

那么$\frac{1}{x}$和$\frac{1}{y}$肯定是小于$\frac{1}{n!}$的。所以$x$和$y$肯定都是大于$n!$的。


我们令
$$y=n!+k(k∈N^*)$$
原式变为
$$\frac{1}{x}+\frac{1}{n!+k}=\frac{1}{n!}$$
等式两边同乘$x*n!*(n!+k)$得
$$n!(n!+k)+xn!=x(n!+k)$$
移项得
$$n!(n!+k)=x(n!+k)-xn!=xk$$
∴
$$x=\frac{n!(n!+k)}{k}=\frac{(n!)^2}{k}+n!$$
∵$x$为正整数

∴$\frac{(n!)^2}{k}+n!$为正整数，$\frac{(n!)^2}{k}$为正整数,因为$k=y-n!$，而$y$是可以取到任意正整数的，所以$k$也可以取到任意正整数，所以这道题就变成了求$(n!)^2$的约数个数。

求约数个数，线筛的时候我们已经预处理出每个数的最小质因子，直接$for$一遍$1-n$，不断除以它的最小公约数，直到变成1为止，同时每次都使记录质因数的指数的数组++，这就完成了对每个数分解质因数，最后把这些质因数的指数+1乘起来就行了。时间复杂度$O(nlogn)$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,m,n) for(int i=m;i<=n;++i)
#define dop(i,m,n) for(int i=m;i>=n;--i)
#define lowbit(x) (x&(-x))
#define INF 2147483647
using namespace std;
inline int read(){
    int s = 0, w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0',ch = getchar();
    return s * w;
}
const int MAXN = 1000010;
const int MOD = 1000000007;
int n;
int c[MAXN], v[MAXN], prime[MAXN], cnt;
int ans = 1;
int main(){
    n = read();
    /////////
    rep(i, 2, n){
       if(!v[i]){
         v[i] = i;
         prime[++cnt] = i;
       }
       rep(j, 1, cnt){
          if(prime[j] > v[i] || prime[j] > n / i) break;
          v[i * prime[j]] = prime[j];
       }
    }
    ///////线筛
    rep(i, 1, n){  //求质因数指数
       for(int j = i; j != 1; j /= v[j])
          c[v[j]]++;
    }
    rep(i, 1, n) ans = (long long)ans * (c[i] * 2 + 1) % MOD; //long long保存中间过程，既节省了时间、空间复杂度，又不会溢出
    printf("%d\n", ans);
    return 0;
}

```

---

## 作者：d3ac (赞：30)

提供一个简洁明了的证明
$$
\frac{1}{x}+\frac{1}{y}=\frac{1}{n!}
$$

$$
\frac{x+y}{xy}=\frac{1}{n!}
$$

$$
xy-n!(x+y)=0
$$

$$
(n!)^2+xy-n!(x+y)=(n!)^2
$$

$$
(x-n!)(y-n!)=(n!)^2
$$

$$
a=(x-n!),b=(y-n!)
$$

$$
ab=(n!)^2
$$

$$
 n!=p_1^{c_1}*p_2^{c_2}*...p_k^{c_k}
$$

$$
(n!)^2=p_1^{2c_1}*p_2^{2c_2}*...p_k^{2c_k}
$$

所以......求一个数的约数有多少个的时候，就是唯一分解之后指数加1再相乘

$$
Ans=(2c_1+1)(2c_2+1)...(2c_k+1)
$$

---

## 作者：Andrew82 (赞：25)

****
谢谢LIdox1536513344大佬指出蒟蒻一处错误
****

analysis

首先先得化简式子，因为这个式子确实看不出来什么


一般看到的题解里有这两种化法：


first：


$\frac{1}{x}+\frac{1}{y}=\frac{1}{n!}$

$\frac{xy}{x+y}=n!$

$xy=n!(x+y)$

$-n!(x+y)+xy=0\leftarrow\rightarrow(n!x+n!y)-xy=0$

**对数学敏感的同学相信写到这一步时就已经可以发现一些东西了,这个式子是十字相乘法拆开括号的后两项!**


****


若设$a=-n!,b=x,c=y$,则$a(b+c)+bc=0$,等式两边同时加上$a^2$


则$a^2+a(b+c)+bc=a^2,(a+c)(a+b)=a^2$


****

于是有$(x-n!)(y-n!)=(n!)^2$

也就是说$(x-n!)|(n!)^2$

那么,$(x-n!)$等价于$(n!)^2$的因子,又由于$(x-n!)$和x的个数相等,那么x的个数和$(n!)^2$的因子的个数一一对应

second：

设$y=n!+k$

则原方程为$x(n!+k)=n!(x+(n!+k))$

即$xn!+xk=n!(x+n!+k),xn!+xk=n!x+(n!)^2+n!k$

也就是$x=\frac{(n!)^2}{k}+n!$

也就是说x的个数等于$(n!)^2$的因子的个数


****
那么本题就是求$(n!)^2$的因子的个数

求因子个数,根据唯一分解定理的推论:

$x=\prod_{i=1}^{m}p_i^{s_i},p_i$是素数

x的约数个数$d(n)=\prod_{i=1}^{m}(s_i+1)$根据乘法原理可证明
****

代码实现

对$(n!)^2$唯一分解的时候,最暴力的做法是直接分解,也就是对每一个n,枚举每个小于$\sqrt n$的质数,时间复杂度为$O(\sqrt n \times n)$,不知为什么居然还在评测机上跑过了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define loop(i,start,end) for(register int i=start;i<=end;++i)
#define anti_loop(i,start,end) for(register int i=start;i>=end;--i)
#define clean(arry,num) memset(arry,num,sizeof(arry))
#define isdegit(a) ((a>='0'&&a<='9'))
#define ll long long

const ll mod=1e9+7;

template<typename T>void read(T &x){
	x=0;char r=getchar();T neg=1;
	while(!isdegit(r)){if(r=='-')neg=-1;r=getchar();}
	while(isdegit(r)){x=(x<<1)+(x<<3)+r-'0';r=getchar();}
	x*=neg;
}

const int maxn=1e6;
ll prime[maxn],nfp=0;
ll v[maxn];
inline void shai(int n){
	clean(prime,0);
	clean(v,0);
	nfp=0;
	loop(i,2,n){
		if(!v[i]){
			v[i]=i;
			prime[++nfp]=i;
		}
		loop(j,1,nfp){
			if(i*prime[j]>n||v[i]<prime[j])
				break;
			v[prime[j]*i]=prime[j];
		}
	}
}

ll fj[maxn];
inline void fenjie(ll a){
	loop(i,1,nfp){
		if(prime[i]*prime[i]>a) break;
		if(a%prime[i]==0){
			while(a%prime[i]==0){
				a/=prime[i];
				++fj[i];
			}
		}
	}
	if(a==1) return;
	int mark=lower_bound(prime+1,prime+1+nfp,a)-prime;
	++fj[mark];
}

int n;

int main(){
	#ifndef ONLINE_JUDGE
	freopen("datain.txt","r",stdin);
	#endif
	read(n);
	shai(n);
	loop(i,2,n){
		fenjie((ll)i);
	}
	ll res=1;
	for(register int i=1;fj[i]!=0;++i){
		res=(res*(fj[i]<<1|1))%mod;
	}
	printf("%lld\n",res);
	return 0;
}

```




但是我们不需要那么暴力

可以利用线性筛里面处理出来的数组v(v[i]是i的最小质因子)来加快我们对于每一个数唯一分解的速度

对于一个数,我们可以每次除去它的最小质因子,并且累加记录,然后对于计算后得到的结果继续除其最小质因子,直到把这个数除成1为止

这样的话,时间复杂度降为$O(nlogn)$,这样就可以过了



```cpp
#include<bits/stdc++.h>
using namespace std;
#define loop(i,start,end) for(register int i=start;i<=end;++i)
#define anti_loop(i,start,end) for(register int i=start;i>=end;--i)
#define clean(arry,num) memset(arry,num,sizeof(arry))
#define isdegit(a) ((a>='0'&&a<='9'))
#define ll long long

const ll mod=1e9+7;

template<typename T>void read(T &x){
	x=0;char r=getchar();T neg=1;
	while(!isdegit(r)){if(r=='-')neg=-1;r=getchar();}
	while(isdegit(r)){x=(x<<1)+(x<<3)+r-'0';r=getchar();}
	x*=neg;
}

const int maxn=1e6;
ll prime[maxn],nfp=0;
ll v[maxn];
inline void shai(int n){
	clean(prime,0);
	clean(v,0);
	nfp=0;
	loop(i,2,n){
		if(!v[i]){
			v[i]=i;
			prime[++nfp]=i;
		}
		loop(j,1,nfp){
			if(i*prime[j]>n||v[i]<prime[j])
				break;
			v[prime[j]*i]=prime[j];
		}
	}
}

ll fj[maxn];
int n;

int main(){
	#ifndef ONLINE_JUDGE
	freopen("datain.txt","r",stdin);
	#endif
	read(n);
	shai(n);
	loop(i,1,n){
		for(int j=i;j!=1;j/=v[j]){
			++fj[v[j]];
			fj[v[j]]%=mod;
		}
	}
	ll res=1;
	for(register int i=1;i<=n;++i){
		res=(res*(fj[i]<<1|1))%mod;
	}
	printf("%lld\n",res);
	return 0;
}

```


其实这也是一种唯一分解的实现方法,但是这种方法要处理一个O(n)的线性筛,所以对于单个数来说没有$O(\sqrt(n))$的快




---

## 作者：天宇裨益 (赞：15)

首先  先对  自己第一篇独立自主思考数学题做个纪念。

  这道题实际上是道规律题，我在刚开始时，先打表找规律，但是由于我刚开始打的是n! 结果没有发现规律。后来经过一会的沉淀，我开始打n 的表。于是我发现所有的质数答案都是3 而4的答案是（5),9的答案是(5),6的答案是（9）8的答案是（7），而16的答案是（9),10的答案是（9）；我一步一步发现(16=2^4,9)(8=2^3,7)(4=2^2,5)(2=2^1,3)有一种（2n+1）的感觉，而（6=2*3，9）（10=2*5,9）实际上我们逐渐发现当sum=2^p1*3^p2*5^p3......答案是（(2p1+1)*(2p2+1)*(2P3+1)）*.....;
  
  而我们处理n!的质因数分解（）就是该题的关键。代码如下。
  

------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
#define ll long long
const int mod=1000000007;
using namespace std;
ll v[1010000],ans,prime[1010000],m;
ll n,cnt,tot,sum,p[1010000];
inline void primes(int n){
	memset(v,0,sizeof(v));
	m=0;for(int i=2;i<=n;i++){
		if(v[i]==0){
			v[i]=i;prime[++m]=i;
		}
		for(int j=1;j<=m;j++){
			if(prime[j]>v[i]||prime[j]>n/i) break;
			v[i*prime[j]]=prime[j];
		}
	}
}
int main(){
    cin>>n;tot=sqrt(n);ans=1;
    primes(n);
	for(int i=2;i<=n;i++){
		cnt=1;if(v[i]!=i) continue;
		for(int j=1;j;j++){
			cnt*=i;p[i]+=n/cnt;
			if(cnt>n) break;
		}
	}  
	for(int i=2;i<=n;i++){
		ans=(ans*(2*p[i]+1))%mod;
	}
	cout<<ans<<endl;
	return 0;
}
```


------------




---

## 作者：巨型方块 (赞：14)

本来想考考fop\_zz的，结果他直接A了哇..

大佬题解http://blog.csdn.net/fop\_zz/article/details/73551108

1/x+1/y=1/n!

先通分

(x+y)/xy=1/n!

再化整数

xy-(x+y)\*n!=0

然后配平

(n!)^2-(x+y)\*n!+xy=(n!)^2

最后

(x-n!)\*(y-n!)=(n!)^2

然后我们发现x，y都要是正整数；

所以原题可以变为

A\*B=(n!)^2;

当A\*B为正整数的时候x,y显然也是正整数；


> 然后我们考虑x的取值，显然，若一个质数p有k个，那么x可以取p^0,p^1....p^k
共(k+1)种情况

乘法原理乘起来就可以了

而且显然，x确定后，y必然也会被确定


那么我们先可以欧拉筛；

求出每个数的最小质因数然后大力就好了；


```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const int N=1e6+5;
bool com[N];
int pri[N],tot,g[N],cnt[N];
int n,m,mo=1e9+7;
Ll ans;
void make(){
    for(int i=2;i<=n;i++){
        if(!com[i])pri[++tot]=i,g[i]=tot;
        for(int j=1;j<=tot;j++){
            if(pri[j]*i>n)break;
            com[pri[j]*i]=1;
            g[pri[j]*i]=j;
            if(i%pri[j]==0)break;
        }
    }
}
int main()
{
    scanf("%d",&n);
    make();
    for(int i=2;i<=n;i++)
        for(int x=i;x!=1;x/=pri[g[x]])cnt[g[x]]++;
    for(int i=1;i<=tot;i++)cnt[i]*=2;
    ans=1;
    for(int i=1;i<=n;i++)ans=ans*(cnt[i]+1)%mo;
    printf("%d",ans);
}

```

---

## 作者：Fatalis_Lights (赞：7)

## 本题为典型爆米花数学题，可边吃爆米花边看（手动滑稽）

## Solution

题意已经说的很清楚了：**求$1/x+1/y=1/n!$ 的正整数解**

通分+移项得： $(x+y)n!-xy=0$

左右同时减去$(n!)^2$，取个负号得： $(n!-x)(n!-y)=(n!)^2$

$(n!-x)(n!-y)=(n!)^2$ <=> 求$(n!)^2$的约数个数

直接用欧拉筛求出素数表：

```cpp
inline void init(int x){
    for(int i=2;i<=x;i++){
        if(!vst[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt;j++){
			if(i*pri[j]>x) break;
            vst[i*pri[j]]=1;
            if(!(i%pri[j])) break;
        }
    }
}
```

可以用唯一分解定理求出答案:

```cpp
inline int count(int k,int p){
    if(k<p) return 0;
    return k/p+count(k/p,p);
}

for(int i=1;i<=cnt;i++)
    	ans*=count(n,pri[i])*2+1, ans%=mod;
```

所以完整代码：

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define N 1000009
#define mod 1000000007
#define ll long long
using namespace std;

int n,cnt,pri[N],vst[N];
ll ans=1;

inline void init(int x){
    for(int i=2;i<=x;i++){
        if(!vst[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt;j++){
			if(i*pri[j]>x) break;
            vst[i*pri[j]]=1;
            if(!(i%pri[j])) break;
        }
    }
} // 欧拉筛 

inline int count(int k,int p){
    if(k<p) return 0;
    return k/p+count(k/p,p);
} // 求素数因子个数

int main(){
    cin>>n;
    init(n);
    for(int i=1;i<=cnt;i++)
    	ans*=count(n,pri[i])*2+1, ans%=mod;
    cout<<ans<<endl;
    return 0;
}
```

然后这个题就这么轻松水过去了。。。

---

## 作者：Creeper_LKF (赞：7)

有没有感觉楼下的题解跑的不够快......

所以有没有什么快一点的呢？

那个4ms的12多k的是我的，然后目前除了在13年的记录之外Rnk1.

于是我们分析算法：

楼下题解的复杂度是O(nlogn+常数的)，平均200ms

有没有什么更快的呢？

我们分析到了
```
A*B=(n!)*(n!)
```

的时候发现最终求的就是约数个数

首先如果求m的约数个数的话，那么对m分解得到
```
m=p1^k1*p2^k2...
```

其中p1,p2,p3...都是质数

那么根据乘法原理

```
Ans = (k1 + 1) * (k2 + 1)...
```

然后对于阶乘来说，对n!做质因数分解实则在分解1 * 2 * ... * n

然而这个就是楼下的做法，然而由于你实则是需要求质因数的指数，而在《初等数论》中有

![公式1](https://cdn.luogu.com.cn/upload/pic/18068.png)

所以我们直接递归（或者非递归地）跑这个公式即可

实际食用：枚举质数（或打表）（在阶乘下质因数等价于质数）（O(n)），然后对于所有质数，跑公式。

n内大约有n/ln(n)个质数，然后每次做都是log的，所以复杂度为O(n/ln(n) * log(n))=O(n)，常数小，瓶颈在筛质数那......

代码如下（12kb不忍直视不敢放）：
```
//Source Code

const int MAXN = 1000111;
const int MODS = 1000000007;

int n, tot;
int prime[MAXN];
bool is_not_prime[MAXN];

inline void Get_Prime(){
    for(int i = 2; i <= n; i++){
        if(!is_not_prime[i])
            prime[++tot] = i;
        for(int j = 1; j <= tot; j++){
            if(i * prime[j] > n) break;
            is_not_prime[i * prime[j]] = true;
            if(!(i % prime[j])) break;
        }
    }
}

inline int Get_D(const int &tar, const int &p){
    if(tar < p) return 0;
    return tar / p + Get_D(tar / p, p);
}

int main(){
    Main_Init();
    n = read();
    Get_Prime();
    long long ans = 1;
    for(int i = 1; i <= tot; i++)
        (ans *= (Get_D(n, prime[i]) << 1) + 1) %= MODS;
    write('\n', ans);
    Main_Init();
    return 0;
}
```

---

## 作者：Hercules (赞：6)

其实就是数学，不要想那么麻烦

直接暴力打出小于sqrt(n)的素数表，再用唯一分解定理就OK

代码~代码~

```c
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10;
const int mod = 1e9 + 7;
long long n, ans = 1, tot, p[MAXN], fj[MAXN], v[MAXN];

int main () {
	scanf("%d", &n);
	//素数表（欧拉筛）
	for(register int i = 2; i <= n; i++) {
		if(!v[i])	v[i] = i, tot++, p[tot] = i;
		for(register int j = 1; j <= tot; j++) {
			if(i * p[j] > n or v[i] < p[j])	break;
			v[p[j] * i] = p[j];
		}
	}
	//求质因子（唯一分解定理）
	for(register int i = 1; i <= n; i++)
		for(register int j = i; j != 1; j /= v[j])
			fj[v[j]]++, fj[v[j]] %= mod;
	for(register int i = 1; i <= n; i++)
		ans = (ans * (fj[i] << 1 | 1)) % mod;
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：kikuss (赞：4)

极其恶心的一道题...

看到这种题肯定是需要化简式子的,因为出题人不会好到给你一个好做的式子

$$\frac{1}{x}+\frac{1}{y}=\frac{1}{n!}$$
$$\frac{x+y}{xy}=\frac{1}{n!}$$
$$xy=(n!)\times (x+y)$$
一个骚操作,两边同时加上$(n!)^2$,为什么,因为方便因式分解...
$$(n!)^2-(n!)\times (x+y)+xy=(n!)^2$$
然后因式分解
$$(n!-x)\times (n!-y)=(n!)^2$$
令$a=(n!-x),b=(n!-y)$,因为$(n!)^2$是确定的,所以确定了$a$,就可以确定$b$,也就可以确定$x,y$了

那么a的方案数是多少?因为$a$是$(n!)^2$的因子,所以$a$的取值的方案数就是$(n!)^2$的因子的方案数

然后根据唯一分解定理
$$n!=p_1^{c_1}\times p_2^{c_2}\times ...\times p_m^{c_m}$$
$$(n!)^2=p_1^{2\times c_1}\times p_2^{2\times c_2}\times ...\times p_m^{2\times c_m}$$
由于每个质因子$p_i$都有$2\times c_i+1$种取值,所以
$$ans=(2\times c_1+1)\times (2\times c_2 +1)\times ...\times(2\times c_m+1)$$
那么最后问题就转化成了对$n!$进行分解质因数,并求质因数的个数

暴力对$1-n$每个数分解质因数,再合并复杂度过高,为$O(n\sqrt n)$

由于$n!$的每个质因子都不超过n,所以我们可以预处理$1-n$内所有质数p,再考虑$n!$内一共有多少个质因子p

我们可以对于在线性筛质数的过程中同时处理一下n以内每个数的最小质因子$p$,然后统计这个数的贡献,在$1-n$中至少包含一个质因子$p$的有$\lfloor\frac{n}{p}\rfloor$,至少包含两个质因子p的有$\lfloor\frac{n}{p^2}\rfloor$...
那么$n!$中质因子$p$的个数就是
$$\lfloor\frac{n}{p}\rfloor+\lfloor\frac{n}{p^2}\rfloor+...+\lfloor\frac{n}{p^{log_{p}{n}}}\rfloor$$

对于每个质因子,我们只需要$log\ n$的时间来求解,所以总复杂度是$O(n\ log\ n)$的

欢迎踩蒟蒻博客[real_l](https://www.cnblogs.com/real-l/p/9839175.html)
# Code
```cpp
#include<bits/stdc++.h>
#define rg register
#define il inline
#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))
#define lol long long
#define in(i) (i=read())
using namespace std;

const lol N=1e6+10,mod=1e9+7;

lol read() {
	lol ans=0,f=1; char i=getchar();
	while(i<'0' || i>'9') {if(i=='-') f=-1; i=getchar();}
	while(i>='0' && i<='9') ans=(ans<<1)+(ans<<3)+i-'0',i=getchar();
	return ans*=f;
}

lol n,cnt,ans=1;
lol g[N],prime[N],c[N];

void init() {
    memset(g,0,sizeof(g));
    for(int i=2;i<=n;i++) {
        if(!g[i]) g[i]=i,prime[++cnt]=i;
        for(int j=1;j<=cnt && i*prime[j]<=n;j++) {
            g[i*prime[j]]=prime[j];
            if(i%prime[j]==0) break;
        }
    }
}

int main()
{ 
    in(n); init();
    for(int i=1;i<=n;i++)
        for(int j=i;j!=1;j/=g[j]) c[g[j]]++;
    for(int i=1;i<=n;i++) ans=ans*(c[i]*2+1)%mod;
    cout<<ans<<endl;
}
```

---

## 作者：henry_y (赞：4)

## 此题解同步在我的博客，可以选择[在博客园阅读](https://www.cnblogs.com/henry-1202/p/9357458.html)，阅读体验更佳~~（就是强行刷访问量）~~

数论好~~（难）~~题

题目要求求出$1/x+1/y=1/n!$ 中$x$和$y$的正整数解的个数

那么我们可以化简一下

很简单就可以化出$(x+y)n!=xy$

但是并没有化掉任何一个未知数，所以这玩意没用

在这个基础上再化简一下

因为$x,y$均为正整数且均$>n$

所以可以设$y=n!+k$

那么原式可化为$(x+n!+k)n!=x(n!+k)$

再整理一下（这里给出运算步骤）

$xn!+(n!)^2+kn!=xn!+kx$

$x=((n!)^2+kn!)/k$

$x=(n!)^2/k+n!$

于是我们向正解迈出了一大步

由题可知，$x,y,n!$均为整数，所以$k$也是整数（如果$k$不是整数，$x$也不会是整数）

然后由这个式子$x=(n!)^2/k+n!$我们可以知道，$k$一定是$(n!)^2$的一个因数，否则会不符合x是整数这个定义

且易得$x$和$k$是一一对应的

那么至此，这个问题就变成了，求$(n!)^2$的因数的个数

用一下欧拉筛法筛出质数，算出质数的每个幂对于我们所求的答案的贡献就可以了

```
#include <cstdio>
using namespace std;
#define mod 1000000007
#define N 1000010
#define ll long long
int p[N],v[N];
ll ans=1,cnt[N];
int n,tot=0;
void eular(){
	v[1]=1;
	for(int i=2;i<=n;i++){
		if(!v[i])v[i]=i,p[++tot]=i;
		for(int j=1;j<=tot;j++){
			if(p[j]>v[i]||p[j]*i>n)break;
			v[i*p[j]]=p[j];
		}
	}
}
int main(){
	scanf("%d",&n);
	eular();
	for(int i=1;i<=tot;i++){
		cnt[i]=0;
		for(ll j=p[i];j<=n;j*=p[i])cnt[i]+=n/j;
		cnt[i]%=mod;
	}
	for(int i=1;i<=tot;i++)ans=(ans*(cnt[i]*2+1))%mod;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：灼眼的夏娜 (赞：2)

### 首先我要向二亚姐姐道个歉，我不应该质疑您的代码

好吧，其实昨天偶然翻到了这道题~~其实我是冲着violet来的~~

发现这题。。。。。。水的一批

很容易得到$xy=(x+y)*n!->xn!+yn!-xy=0$

也就是$(x-n!)*(y-n!)=(n!)^{2}$

所以只要$(x-n!)|(n!)^{2}$就完了

再说明白点，就是求$(n!)^{2}$的约数个数

然而本蒟蒻昨天码完后交上去居然全wa，检查了几遍后也没发现啥问题

就去翻了翻题解，看到二亚姐姐的代码扒了下来和我的拍了拍，然而拍了

半个小时都没拍出锅，于是我就开始质疑，然后就有了开头那句话~~光速打脸~~

我也不知道昨天是怎么扒的，灵异事件，~~难道是我脸黑？~~

不管了，总之后来是调过了（不知道自己是怎么过的），特发此题解

代码其实很简单，线性筛+唯一分解定理

## code

```cpp
#include <bits/stdc++.h>
#define R register

using namespace std;
const int N = 1e6+5;
const int p = 1e9+7;
int n,cnt,prime[N],v[N],num[N];
long long ans = 1;

inline void line_get_prime() {//生动形象的函数名字
	for(R int i = 2;i <= n;++ i) {
        if(!v[i]) { v[i] = i;prime[++cnt] = i; }
        for(R int j = 1;j <= cnt && i * prime[j] <= n;++ j) {
            if(v[i] < prime[j]) break;
            v[i * prime[j]] = prime[j];
        }
    }
}

int main() {
    scanf("%d",&n);
    line_get_prime();
    for(R int i = 1;i <= n;++ i)//质因数分解
        for(R int j = i; j != 1; j /= v[j])
            num[v[j]] ++, num[v[j]] %= p;
    for(R int i = 1;i <= n;++ i) 
        ans *= (num[i] * 2 + 1) ,ans %= p;
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：撤云 (赞：2)

[点击食用效果更佳](https://www.cnblogs.com/hbxblog/p/9868024.html)  

#### 题目链接

[洛谷](https://www.luogu.org/problemnew/show/P1445)  

[狗粮版](https://www.lydsy.com/JudgeOnline/problem.php?id=2721)

#### 前置技能

1. 初中基础的因式分解
2. 线性筛
3. $O(nlog)$的分解质因数
4. 唯一分解定理

#### 题解

首先来分解一下式子

$$\frac{1}{x}+\frac{1}{y}=\frac{1}{n!}$$
通分可化为:
$$\frac{x+y}{xy}=\frac{1}{n!}$$
两边同时乘$xy*(n!)$
$$(x+y)n!=xy$$
移项得:
$$xy-(x+y)n!=0$$
两边同时加上$(n!)^2$
$$xy-(x+y)n!+(n!)^2=(n!)^2$$
通过十字相乘可因式分解为:
$$(x-n!)(y-n!)=(n!)^2$$
$$∵\frac{1}{x}+\frac{1}{y}=\frac{1}{n!}$$
$$∴x,y>n!$$
又因为$x,y$为正整数,所以$(x-n!),(y-n!)$也为正整数,所以我们不妨令
$$X=(x-n!),Y=(y-n!)$$
则原式可以化为:
$$XY=(n!)^2$$
根据唯一分解定理可知($p_i$为质数)
$$n!=P_1^{a_1}P_2^{a_2}P_3^{a_3}...P_n^{a_n}$$

$(n!)^2$的因数个数为:
$$(2*a_1+1)*(2*a_2+1)*(2*a_3+1)*...*(2*a_n+1)$$

所以我们只要算出$a_1,a_2,a_3...a_n$就好了  
至于怎么算,线性筛一遍,在分解质因数,求$a_i$就好了  

#### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000000;
const int mod = 1e9+7;
int prime[N+1],a[N+1],js,v[N+1],c[N+1];
int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9')  f=(c=='-')?-1:1,c=getchar();
    while(c>='0'&&c<='9')  x=x*10+c-'0',c=getchar();
    return x*f;
}
void pd(){
    for(int i=2;i<=N;i++){
        if(!prime[i]) a[++js]=i,v[i]=i;
        for(int j=1;j<=js;j++){
            if(i*a[j]>N)  break;
            prime[i*a[j]]=1;
            v[i*a[j]]=a[j];
        }
    }
}
main(){
    int n=read(),x,ans=1;
    pd();
    v[1]=1;
    for(int i=1;i<=n;i++)
        for(int j=i;j!=1;j/=v[j])
            c[v[j]]++;
    for(int i=1;i<=N;i++)
        ans*=(c[i]*2+1),ans%=mod;
    printf("%lld",ans%mod);
}

```

---

## 作者：Azazеl (赞：1)

蒟蒻数论不好,还望大佬轻喷,因为这篇题解没有证明.

------------

我们想到可以打个表(由于刚开始小蒟蒻题看错了把$n!$变成$n$,于是就打了$\frac{1}{x}+\frac{1}{y}=\frac{1}{n}$的表)   
~~但是之前晚自习的时候手算枚错了于是半天找不到规律~~
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int main() {
	int ans=0;
	for(int n=2;n<=100;n++)
	{
		ans=0;
		for(int x=n+1;x<=2*n;x++)
		{
			if(x==2*n)
			{
				ans++;
				break;
			}
			if(!((n*x)%(x-n))) ans+=2;//稍微想一想就很明显的
		}
		printf("n=%d,ans=%d\n",n,ans);
	}
	return 0;
}
```
$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ $![](https://cdn.luogu.com.cn/upload/image_hosting/z018byh4.png)  
这个时候不难看出至少有这条规律  

- 质数的$ans=3$ 

从这道题的标签```素数判断,质数,筛法```可以看到这道题与质数有关,那么让一个合数与质数扯上关系的~~我唯一知道的~~方法就是分解质因数了，我们来试算几个  

- $4=2^2$  
- $6=2^1*3^1$  
- $8=2^3$  
- $9=3^2$  
- $10=2^1*5^1$  
- $12=2^2*3^1$  
- ······  

这其中$ans$相等的有  
$n=6,10(ans=9)\ \ \ \ \ n=4,9(ans=5)\ \ \ \ \ n=8(ans=7)\ \ \ \ \ n=12(ans=15)$  
捡软柿子捏，我们拿特殊一点的$n=4,9(ans=5)$一组下手，为什么，它们是完全平方数   
众所周知，完全平方数即为$a^2$,而$ans=5=2*2+1$  
嗯，有点意思，或许我们可以~~瞎蒙一波~~猜想这个指数与答案有什么关系，但是一个式子并不能证明什么

同理，我们再用$n=8(ans=7)$时下手,立方数即为$a^3$,而$ans=7=2*3+1$  
有点感觉了，但如果它有多个底数怎么办呢?  

拿$n=6$再来举例，$6=2^1*3^1$,而$ans=9=(1*2+1)*(1*2+1)$  

到这里，我们可以猜想对于一个数$n$，若有:
$$n=2^{p1}*3^{p2}*5^{p3}*7^{p4}*······$$

则  
$$ans=(2*p1+1)(2*p2+1)(2*p3+1)(2*p4+1)······$$  
所以对于$n!$,我们只需要将它分解质因数然后直接求结果就行了。  

$\mathcal{CODE}$（差点写了$1h$,我太弱了）  
```cpp
#include <cstdio>
#define ll long long
#define re register
using namespace std;
const int Siyuan=1e9+7;//膜拜Siyuan
ll n,ans=1,tot,prime[1000005],p[1000005],v[1000005];
int main () {
    scanf("%lld",&n);
    for(re int i=2;i<=n;i++) 
	{
        if(!v[i]) v[i]=i,tot++,prime[tot]=i;
        for(re int j=1;j<=tot;j++) 
		{
            if(i*prime[j]>n||v[i]<prime[j]) break;
            v[prime[j]*i]=prime[j];
        }
    }
    for(re int i=1;i<=n;i++)
    {
    	for(re int j=i;j!=1;j/=v[j]) p[v[j]]++,p[v[j]]%=Siyuan;
	}
        
    for(re int i=1;i<=n;i++) ans=(ans*(p[i]<<1|1))%Siyuan;
    printf("%lld\n",ans);
    return 0;
}
```
之前卡$TLE\ 40pts(P4167)$的代码  
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
const int Siyuan=1e9+7;
ll z=0;
bool prime[1000005];
ll Prime[1000005];
void make_prime(ll n)
{
    prime[0]=prime[1]=true;
    for(ll i=2;i<=n;i++)
    {
        if(!prime[i]) Prime[z++]=i;
        for(ll j=0;j<z&&i*Prime[j]<=n;j++)
        {
            prime[i*Prime[j]]=true;
            if(!(i%Prime[j])) break;
        }
    }
    return;
}
ll p[1000005];
int main() {
	ll ans=1,n,maxn=-1;
	scanf("%lld",&n);
	make_prime(n);
	for(ll i=2;i<=n;i++)
	{
		ll tmp=i;
		for(ll j=2;j<=n;j++)
		{
			if(!tmp) break;
			if(prime[j]) continue;
			while(tmp%j==0) 
			{
				p[j]++;
				tmp/=j;
			}
			maxn=max(maxn,j);
		}
	}
	for(int i=2;i<=maxn;i++) ans=(ans*(2*p[i]+1))%Siyuan;
	printf("%lld",ans);
	return 0;
}
```  
原因就在于分解质因数时太慢了，我们用$v[i]$来存储$i$的最小因子，每次都直接除掉$v[i]$就行了.

至于详细的证明,小蒟蒻不会··· ···希望大佬能够指教。

---

## 作者：zmzx (赞：1)

~~（趁老师不在，偷闲发篇题解）~~

这是一道很标准的数学题，但是不容易想到；

直接推式子：

 1/x+1/y=1/n!       令z=n!

 1/x+1/y=1/z;
 
 (x+y)/xy=1/z;
 
 xy=(x+y)*z
 
 xy-(x+y)*z=0;
 
 xy-(x+y)*z+z^2=z^2;
 
 (x-z)(y-z)=z^2;
 
 然后我们愉快地发现，答案就是z^2(即(n!)^2)的约数的个数；
 
 参照参照**阶乘分解**这道题的做法，我们可以将n!分解质因数，然后统计答案;
 
 （以下阶乘分解会的可以跳过）
 
 关于阶乘分解，显然不能将1~n全部分解再合并，那要怎么做呢？
 
 n!中质因子的个数=1~n中每个数包含质因子p的个数之和;在1~n中，p的倍数有n/p(下取整，下同)个，即至少包含一个质因子p的有n/p个，p^2的倍数，有n/p^2个，即至少包含两个质因子p的有n/p^2个，但其中一个p已经被统计过了,因此在这里我们只加一次；
 
 综上 n!中p的个数为：
 
 （n/p）+(n/p^2)+(n/p^3)+...+(n/p^log(n))=∑(n/p^k)
    
    ( p^k<=n;) 
 
 然后是代码：
 
 
 ```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1e6+10,mod=1e9+7;
typedef long long ll;
ll n;
int p[N],v[N],cnt;
ll ans=1;
inline void get_p(int n)
{
	for(int i=2;i<=n;i++){
		if(v[i]==0){
			v[i]=i;p[++cnt]=i;
		}
		for(int j=1;j<=cnt&&i*p[j]<=n;j++){
			if(p[j]>v[i])break;
			v[i*p[j]]=p[j];
		}
	}
}
ll anss;
int main()
{
	scanf("%lld",&n);
	get_p(n);
	for(int i=1;i<=cnt;i++){
		anss=0;
		for(int j=n;j;j/=p[i])anss+=j/p[i];//记录n！中p的个数
		(ans*=(anss*2+1))%=mod;（注意，我们要分解的是(n!)^2，所以此处要乘(anss*2+1)而非（anss+1））
	}
	printf("%lld",ans);
	return 0;
}
```

 

---

## 作者：太阳骑士 (赞：1)

首先看到这个方程：
$$ \frac{1}{x}+\frac{1}{y}=\frac{1}{n!}$$
将左边通分后并将分子分母调换：
$$\frac{xy}{x+y}=n!$$
再将$x+y$移到右边并两边同时乘以$2$：
$$x(2n!-y)+y(2n!-x)=0$$
由此可得除非$x$和$y$都等于$2n!$，否则其中必有一个是大于$2n!$的。那么我们假设$x$是大于$2n!$的，则易知$x>2n!>y>n!$。
假设$y=n!+k$（$k$为正整数），由上面的式子可以推出：
$$\frac{x-2n!}{x}=\frac{n!-k}{n!+k}$$
于是：
$$x=\frac{n!^{2}}{k}+n!$$
又$x>2n!$且$x$为正整数，所以
$$\frac{n!}{k}>1$$
这里我们就可以知道$k$必须取$n!$的约数，且$k$不能等于$n!$。于是我们只要求出$n!$的约数个数并减去$n!$这个约数即可，但我们之前是假设$x>y$，所以约数还要乘$2$。
$n!$的约数要怎么求可以自行百度。
下面是AC代码：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
bool prime[1000001];
void primes(){	//预处理所有质数 
    memset(prime,1,sizeof(prime));
    prime[0] = 0;
    prime[1] = 0;
    for(int i=2;i<1000001;i++){	//欧拉筛 
        if(prime[i]){
            for(int j=i+i;j<1000001;j+=i){
                prime[j]=0;
            }
        }
    }
}
int cal(int n,int p){	//用来计算n！的约数个数 
    if(n<p) return 0;
    else return n/p+cal(n/p,p);
}
int main(){
	primes();
	int n;
	scanf("%d",&n); 
	int i=2;
	ll cnt=1;
	while(i<=n){
		if(prime[i])
			cnt=(ll)cnt*((2*cal(n,i)+1)%mod)%mod;	//一边计算，一边取模 
		i++;
	}
	printf("%lld",cnt);	//输出答案 
	return 0;
}
```
蒟蒻的一篇题解QAQ

---

## 作者：niolle (赞：1)

```.cpp
/*
很容易得x=n!y/y-n！ 
设k=y-n!
则原式x=n!(k+n!)/k
      x=n!^2+n!k/k
	  x=n!^2/k+n!
	  ∴只有k|n^2时x才为正数
	  ∴k的个数即是x、y的个数
	  易看出k的个数即n!^2约数的个数
	  于是这道题转换为求n^2的约数的个数有多少
	  公式:百度百科自己搜
*/ 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,a,b) for(long long i=a;i<=b;i++)
using namespace std;
typedef long long ll;
const ll mod=1e9+7,MAXN=1e6+10;
ll n,ans[MAXN],pri[MAXN],tot,fir[MAXN],answ=1;
bool book[MAXN];
void pdprime(){
	rep(i,2,MAXN-8){
		if(!book[i]) pri[++tot]=i;
		for(ll j=1;j<=tot && pri[j]*i<=MAXN-8;++j){
			book[i*pri[j]]=1;
			fir[i*pri[j]]=pri[j];
			if(i%pri[j]==0) break;
		}
	}
}
int main()
{
	scanf("%lld",&n);
	pdprime();
	rep(i,1,n) ans[i]=1;
	rep(i,2,n){
		ll x=i;
		while(book[x]){
			ans[fir[x]]+=2;
			x/=fir[x];
		}
		ans[x]+=2;
	}
	rep(i,2,n) answ*=ans[i],answ%=mod;
	printf("%lld",answ);
	return 0;
}```

---

## 作者：QMQMQM4 (赞：0)

# p4167题解

先小声BB一句，1445也叫樱花，解法一样，数据一样，最强双倍经验

## 进入正题

题目让我们求 $\frac{1}{x}+\frac{1}{y} = \frac{1}{n!}$的解的个数

我们先设$n! = m$，通过观察得$ x> n && y > n $那我们就设$x = m+a,y = m+b$

即$\frac{1}{m+a}+ \frac{1}{m+b} = \frac{1}{m}$

通分一下就有$\frac{2m+a+b}{(m+a)(m+b)} = \frac{1}{m}$

然后交叉相乘$2*m^2+(a+b)m = m^2+m(a+b)+ab$

化简一下就有$m^2 = ab$

$m^2$是什么，就是$(n!)^2$因为题目中让求解的个数，即对$m^2$分解质因数即可

因为$m^2$的约数个数即为原方程解的个数

### 约数个数定理

若$n = \prod_{i = 1}^{m}p^{c_{i}}_{i}$

则$n$的约数个数为$\prod_{i=1}^{m}c_{i}+1$

这里我们求出$c_{i}$,由于是$(n!)^2$，需要变为$2*c_{i}+1$

然后就愉快的线性筛了

讲解完毕代码很简单就不注释了

```#include<cstdio>
#include<iostream>
using namespace std;

typedef long long ll;
const int MOD = 1e9+7;
const int maxn = 1e6+5;
int c[maxn],v[maxn],p[maxn],tot,n;
ll ans = 1;

inline int read()
{
	char c = getchar();int x = 0,f = 1;
	while(c<'0'||c>'9') {if(c=='-')f = -1;c = getchar();}
	while(c>='0'&&c<='9') {x = x*10+c-'0';c = getchar();}
	return x*f;
}

void pre(int n)
{
	for(int i = 2;i<=n;++i)
	{
		if(!v[i])
		{
			v[i] = i;
			p[++tot] = i;
		}
		for(int j = 1;j<=tot;++j)
		{
			if(p[j]>v[i]||p[j]>n/i)
				break;
			v[i*p[j]] = p[j];
		}
	}
	for(int i = 1;i<=n;++i)
		for(int j = i;j!=1;j/=v[j])
			c[v[j]]++;
}

int main()
{
	n = read();
	pre(n);
	for(int i = 1;i<=n;++i)
		ans = (ll)ans*(c[i]*2+1)%MOD;
	printf("%lld",ans);
	return 0;
}
```



















---

## 作者：Freopen (赞：0)

好像别的题解都没有我这样推的啊

设$d=\gcd(x,y),a=\frac xd,b=\frac yd$
则有$\frac {a+b}{dab} = \frac 1{n!}$

所以$n! = ab\frac d{a+b}$

考虑右边的分式，发现除掉$gcd$后,$gcd(a+b,ab) = 1$

所以$\frac d{a+b}$是一个整数，设其为$z$

所以我们就需要统计满足$n! = abz , \gcd(a,b) = 1$的三元组$(a,b,z)$个数。

发现$a,b$确定后$z$就唯一确定了。
所以转为统计$ab|n! ,\gcd(a,b) = 1$的二元组$(a,b)$

所以就把$n!$给分解成多个 质因数的次方相乘 的形式然后按照每个质因数拿出多少个给$ab$,给$a$还是给$b$就可以统计方案了。

结合其他题解还可以得出：$\sum_{a,b}[ab|n!][\gcd(a,b)=1] = d((n!)^2)$


$\texttt{AC \ Code}$
```cpp
#include<bits/stdc++.h>
#define maxn 1000006
#define mod 1000000007
using namespace std;

int n;
int pr[maxn/8],mpr[maxn],cnt[maxn/8],cnt_pr;

int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;i++){
		if(!mpr[i]) pr[++cnt_pr]=i,mpr[i]=cnt_pr;
		for(int j=1;pr[j]*i<=n;j++){
			mpr[i*pr[j]] = j;
			if(i % pr[j] == 0) break;
		}
	}
	for(int i=2;i<=n;i++)
		for(int u=i;u>1;u/=pr[mpr[u]])
			cnt[mpr[u]]++;
	int ans = 1;
	for(int i=1;i<=cnt_pr;i++)
		ans = (2ll * ans * cnt[i] + ans) % mod;
	printf("%d\n",ans);
}
```


---

## 作者：ESTELLE_1017 (赞：0)

### 题目描述

这是8.13考试的签到题。

突然发现洛谷有原题23333

不过洛谷上只有T=2的情况啦～

给定T ∈ {1，2},以及一个正整数N。

当T=1时，求1/x + 1/y = 1/N 的正整数解(x,y) 的个数。

当T=2时，求1/x + 1/y = 1/N！ 的正整数解(x,y) 的个数。

### 输入格式

两个整数T和N

### 输出格式

一个整数，表示解的个数

### 输入样例1

1 120

### 输出样例1

63

### 输入样例2

2 1439

### 输出样例2

102426508

### 数据范围

当T=1时，1<=n<=10^12

当T=2时，1<=n<=10^6

### 思路解析

首先我们考虑T=1的情况，式子可以化为：

(x+y) / x * y = 1/N => x * y = (x+y) * N => x * y = x * N + y * N => (y-N) * x = y * N

设 z = y-N => y = z+N .

所以 z * x = (z+N) * N => z * x = z * N + N * N => x = N + N * N / z

因为 x 是正整数，所以N * N 是z的倍数，于是解的个数实际上就是 N * N 的约数个数。

我们~~考虑暴力做法O（n^2)~~ 来思考怎么做。

可以发现，将n分解质因数后

n的约数个数=(sum[i]+1) * (sum[i+1]+1) * ... * (sum[i+...]+1)

其中，sum[i]表示质数i的个数。

至于为什么应该很好想吧，考虑每个质数取0个，1个，2个...sum[i]个。

还不懂的感性理解一下（不是

然后对于T=2的情况，因为N! = 1 * 2 * 3 * ... * N，我们就对于1-n每个数都分解一边质因数然后加起来再用上面的方法算就行了。

~~分解质因数什么的就不用说了吧。~~

### 赋上洛谷原题代码
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int p=1e9+7;
const int N=1e6+5;
int sum[N];
ll n,ans=1;
int main(){
  scanf("%lld",&n);
  for(int i=2;i<=n;i++){
    int m=i;
    for(int j=2;j*j<=m;j++){
      if(m==1) break;
      while(m%j==0){
        sum[j]++;m/=j;
      }
    }
    if(m>1)
      sum[m]++;
  }
  for(int i=1;i<=n;i++)
    if(sum[i])
      ans=(ans*(ll)(sum[i]*2+1))%p;
  printf("%lld",ans);
  return 0;
}

```
双倍经验就是爽！
指路 p1445

---

## 作者：ESTELLE_1017 (赞：0)

### 题目描述

这是8.13考试的签到题。

突然发现洛谷有原题23333

不过洛谷上只有T=2的情况啦～

给定T ∈ {1，2},以及一个正整数N。

当T=1时，求1/x + 1/y = 1/N 的正整数解(x,y) 的个数。

当T=2时，求1/x + 1/y = 1/N！ 的正整数解(x,y) 的个数。

### 输入格式

两个整数T和N

### 输出格式

一个整数，表示解的个数

### 输入样例1

1 120

### 输出样例1

63

### 输入样例2

2 1439

### 输出样例2

102426508

### 数据范围

当T=1时，1<=n<=10^12

当T=2时，1<=n<=10^6

### 思路解析

首先我们考虑T=1的情况，式子可以化为：

(x+y) / x * y = 1/N => x * y = (x+y) * N => x * y = x * N + y * N => (y-N) * x = y * N

设 z = y-N => y = z+N .

所以 z * x = (z+N) * N => z * x = z * N + N * N => x = N + N * N / z

因为 x 是正整数，所以N * N 是z的倍数，于是解的个数实际上就是 N * N 的约数个数。

我们~~考虑暴力做法O（n^2)~~ 来思考怎么做。

可以发现，将n分解质因数后

n的约数个数=(sum[i]+1) * (sum[i+1]+1) * ... * (sum[i+...]+1)

其中，sum[i]表示质数i的个数。

至于为什么应该很好想吧，考虑每个质数取0个，1个，2个...sum[i]个。

还不懂的感性理解一下（不是

然后对于T=2的情况，因为N! = 1 * 2 * 3 * ... * N，我们就对于1-n每个数都分解一边质因数然后加起来再用上面的方法算就行了。

~~分解质因数什么的就不用说了吧。~~

### 赋上洛谷原题代码
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int p=1e9+7;
const int N=1e6+5;
int sum[N];
ll n,ans=1;
int main(){
  scanf("%lld",&n);
  for(int i=2;i<=n;i++){
    int m=i;
    for(int j=2;j*j<=m;j++){
      if(m==1) break;
      while(m%j==0){
        sum[j]++;m/=j;
      }
    }
    if(m>1)
      sum[m]++;
  }
  for(int i=1;i<=n;i++)
    if(sum[i])
      ans=(ans*(ll)(sum[i]*2+1))%p;
  printf("%lld",ans);
  return 0;
}

```

---

## 作者：Edward_Elric (赞：0)

## 分析

首先推式子吧。这式子很简单
$$ \frac{1}{x}+\frac{1}{y}=\frac{1}{!n} $$

化简得
$$xy-!nx-!ny=0$$

进而伪因式分解

$$(x-!n)(y-!n)=(!n)^2$$

令$(x-!n)$为$a$,$(y-!n)$为$b$

则我们要求的就是方程$ab=(!n)^2$的解

这个方程解的个数显然是$(!n)^2$的约数个数。

给出质数唯一分解定理：$n=p_1^{c_1} *  p_2^{c_2} ... * p_m^{c_m}$

则约数个数为$∏_{i=1}^{n}(c[i]+1)$

对于$!n$的$c[i]$可以这样扫。很容易理解。
```cpp
    for(int i=1;i<=tot;i++){
	int p=prime[i];
	for(long long j=p;j<=n;j*=p)
           c[i]+=n/j;
    }
```
最后套上约数个数公式:，这题就做完了
```cpp
	for(int i=1;i<=cnt;i++)
		tot=tot*(ans[i]*2+1)%mod;
```
## 复杂度分析

首先求质数我们需要$O(n)$

结合质数分布定理:求$!n$的$c[i]$大概是$O(\dfrac{n}{lnn} lnn≈n)$

第一个式子是分布定理，第二个是调和级数

最后求约数个数$O(n)$扫过去即可

综上复杂度为$O(n)$

---

## 作者：四氧化二磷 (赞：0)

# [Violet] 樱花
【题目描述】
原题来自：HackerRank Equations

求不定方程：

$$ \frac {1}{x} + \frac {1}{y} = \frac {1}{n!}. $$
　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　正整数解的组数.
                                                                
                                                                

------------

　
 
　　算法：数论
  
　　通过各种奇怪的交叉相乘，换元，同加 n! 等方式之后我们可以得到下面这个简洁的式子。
  
  $$ {(x-n!)}{(y-n!)} = {(n!)}^{2}. $$
  
　　很显然题目就是要求$(n!)^{2}$的因数个数。
  
　　欧拉筛。但是$ n! $似乎太大了，从1到$n$依次分解复杂度O($ {n}^{2} $)，自然是会炸的。
  
　　我们联想到了数竞里经典的“求100!末尾有多少个0”的算法：每一个2的倍数中都至少有一个因数2，每一个3的倍数中都至少有一个3，每个4的倍数中至少还有一个2.
  
　　每一个质数$ p $的倍数中都有至少有一个$ p $;
  
　　每一个$ p^{2} $的倍数中至少还有一个$ p $;
  
　　每一个$ p^{n} $的倍数中至少有$ {n} $个$ p $;
  
　　容易得到在[1,n]中的所有数分解质因数后质因数$p$的个数和为$ \sum ^{n}_{i=2,i++} \sum ^{m=[log _{p}i]}_{j=1,j++}[i*p^{-j}] $.
  
　　丢桶里.**输出时不要忘记乘二加一**。
  
　　乘二是因为$ {(n!)}^2 $,加一是因为因子个数定理。
  
code：
```
#include<bits/stdc++.h>
using namespace std;
long long tot,n,p[1010110];
bool b[1001010];
long long bb[1000100],ans=1;
inline long long read(){
	long long res=0,f=1,ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
	return res*f;
}
inline void mkprim(long long k){
	for(long long i=2;i<=k;i++){
		if(b[i])continue;p[++tot]=i;
		for(long long j=i*2;j<=k;j+=i)b[j]=1;
	}
	return;
}
int main(){
	n=read();
	mkprim(n);
	/*
	for(int i=2;i<=n;i++){
		long long ii=i;
		for(int j=1;j<=tot;j++){
			while(ii%p[j]==0)
			ii/=p[j],bb[j]++;
			if(ii==1)break;
		}
	}
	*/
	for(long long i=1;i<=tot;i++)
	{
		for(long long j=p[i];j<=n;j*=p[i])
		bb[i]+=(n/j);bb[i]%=1000000007;
    } 
	for(int i=1;i<=tot;i++)ans=ans*(bb[i]*2+1),ans%=1000000007;
	printf("%lld",ans);
	return 0;
} 
```

---

## 作者：amazingOZR (赞：0)

抱歉之前那个题解的latex打崩了……

\frac{1}{x}+\frac{1}{y}=\frac{1}{n!}

\frac{x+y}{xy}=\frac{1]{n!}

xy-n!(x+y)=0

(x-n!)(y-n!)=(n!)^{2}


---

