# GCD SUM

## 题目描述

求

$$\sum_{i=1}^n \sum_{j=1}^n \gcd(i, j)$$

## 说明/提示

对于 $30\%$ 的数据，$n\leq 3000$。

对于 $60\%$ 的数据，$7000\leq n\leq 7100$。

对于 $100\%$ 的数据，$n\leq 10^5$。


## 样例 #1

### 输入

```
2```

### 输出

```
5```

# 题解

## 作者：Kelin (赞：149)

$ans=\sum_{k=1}^nk*f[k]$

$f[k]$表示$gcd(i,j)=k$的个数 

$g[k]$表$k|gcd(i,j)$的个数

显然$g[k]=f[k]+f[2k]+...+f[mk]$

而$g[k]=\lfloor\frac nk\rfloor^2$($i$有$\lfloor\frac nk\rfloor$种选择$j$一样所以相乘就是$\lfloor\frac nk\rfloor^2$)

所以$f[k]=\lfloor\frac nk\rfloor^2-(f[2k]+f[3k]+....)$

复杂度是$n*(1+\frac12+\frac13+...+\frac1n)$


所以总复杂的为$O(nH(n)),H(n)$为调和级数

因为$n$不大,这个算法常数小,所以就比算$\sum_{d=1}^n\phi(d)*\lfloor\frac nd\rfloor^2$要快一些

什么你说杜教筛?那玩意常数更大.做杜教筛不如去做[这个](https://www.luogu.org/problemnew/show/P4213)

```cpp
#include<cstdio>
#define re register int
long long n,ans,f[100010];
int main(){
    scanf("%lld",&n);
    for(re i=n;i;--i){
        f[i]=n/i*(n/i);
        for(re j=i<<1;j<=n;j+=i)f[i]-=f[j];
        ans+=f[i]*i;
    }
    printf("%lld",ans);
return 0;
}
```

---

## 作者：魍魉° (赞：74)

贴一篇不需要反演的题解。

直接计算复杂度过高无法接受

考虑枚举所有$gcd$值计算

若$gcd=k$

对于所有$gcd\left ( x,y \right )=1$，有$gcd\left ( xk,yk \right )=k\left ( xk\leq n,yk\leq n \right )$

所以$gcd=k$的个数为
$$2*\sum_{i=1}^{\left \lfloor \frac{n}{k} \right \rfloor}\varphi \left ( i \right )-1$$
$\left ( x,y \right )$与$\left ( y,x \right )$均可行，但$\left ( 1,1 \right )$只能计算一次

线性筛一遍欧拉函数，然后求前缀和

复杂度$O\left ( n \right )$

```cpp
#include<cstdio>
#define LL long long
const int N=100050;
int prime[N],cnt=0,phi[N];
LL n,sum[N],ans=0;
void init()
{
    phi[1]=1;
    for(int i=2;i<=n;i++)
    {
        if (!phi[i]) prime[++cnt]=i,phi[i]=i-1;
        for(int j=1;j<=cnt;j++)
        {
            if (prime[j]*i>n) break;
            if (i%prime[j]==0)
            {
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            else phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }		
    }
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+phi[i];
}
int main()
{
    scanf("%lld",&n);
    init();
    for(LL i=1;i<=n;i++) 
        ans+=(sum[n/i]*2-1)*i;
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：FifthAxiom (赞：45)

## 题目大意

给定正整数$n$，求
$$\sum_{i = 1}^n\sum_{j = 1}^n\gcd(i,j)\quad(0)$$

## 前置知识

欧拉函数：定义数论函数$\phi$（数论函数指定义域为正整数，值域为具有特定意义的数集的一类函数），有
$$\phi(n)=\begin{cases}1\quad (n=1) \\ \text{1到n-1内与n互质的数的个数}\quad otherwise\end{cases}$$
欧拉函数有一个奇怪的性质
$$\sum_{d|n}\phi(d)=n$$
下面我们简单证明一下

$\text{proof}$:

若$p$是素数，显然有
$$\phi(p)=p-1$$
那么，对于正整数$kp$，与其不互质的数只有$1,p,2p,3p\dots, kp$，故
$$\phi(kp)=k(p-1) \quad(1)$$
对于素数幂$p^k$，由$(1)$可知
$$\phi(p^k)=p^{k-1}(p-1)=p^k-p^{k-1}$$
对于
$$\sum_{d|p^k}\phi(d) \quad(2)$$
显然，$d$只能取$1,p,p^2,p^3\dots,p^k$。那么有
$$\begin{aligned}&(2)\\&=(\sum_{d=1}^k\phi(p^d))+1\\&=(\sum_{d=1}^kp^d-p^{d-1})+1\\&=p^k-p^{k-1} +p^{k-1}-p^{k-2}+\dots -p+p-1+1\\&=p^k\end{aligned}$$
因为$\phi$是积性函数，即若$n\perp m$，$\phi(nm)=\phi(n)\phi(m)$，由正整数唯一分解定理可知$\sum_{d|n}\phi(d)=n$。

Q.E.D.

~~这个证明窝自己搞出来的，嘿嘿~~

那么回到本题，有
$$\begin{aligned}&(0)\\&=\sum_{i = 1}^n\sum_{j = 1}^n\sum_{d|\gcd(i,j)}\phi(d)\\&=\sum_{i = 1}^n\sum_{j = 1}^n\sum_{d|i,d|j}\phi(d) \quad\text{d|gcd(i,j)可以写成d|i,d|j，不难理解吧}\\&=\sum_{i = 1}^n\sum_{j = 1}^n\sum_{d=1}^n\phi(d)[d|i][d|j] \quad\text{[P]中若P为真则[P]=1，否则[P]=0}\\&=\sum_{d=1}^n\phi(d)\sum_{i=1}^n\sum_{j=1}^n[d|i][d|j]\\&=\sum_{d=1}^n\phi(d)\lfloor\dfrac{n}{d}\rfloor^2 \end{aligned}$$
至此，我们可以线性筛出$1$到$n$中的$\phi$，然后把最后的柿子for一遍就行啦（当然用整除分块更好，但此题里$n$的范围太小，直接搞也可以）

## 代码

```cpp
#include <cstdio>
#include <cstring>

const int MAXN = 100010;

int prime[MAXN], v[MAXN], phi[MAXN], sumPhi[MAXN], cnt, n;

void eular(int n) {//线性筛筛欧拉函数
    memset(v, 0, sizeof(v));
    sumPhi[1] = phi[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (!v[i]) {
            prime[++cnt] = v[i] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= cnt; j++) {
            if (prime[j] > v[i] || i * prime[j] > n) break;
            v[i * prime[j]] = prime[j];
            phi[i * prime[j]] = phi[i] * (i % prime[j] ? prime[j] - 1 : prime[j]);
        }
        sumPhi[i] = sumPhi[i - 1] + phi[i];//求欧拉函数的前缀和，如果整除分块的话就要用
    }
}

int main() {
    scanf("%d", &n);
    eular(n);

    long long ans = 0;
    for (int l = 1, r; l <= n; l = r + 1) {//这里是整除分块写法，如果不懂可以直接for 1 to n
        r = n / (n / l);
        ans += (long long) (sumPhi[r] - sumPhi[l - 1]) * (n / l) * (n / l);
    }
    printf("%lld\n", ans);
    return 0;
}
```

谢谢大家观看资瓷！

20191022 update:修复题解区markdown轩然

---

## 作者：ziiidan (赞：26)

一道非常不错的欧拉函数题，巧妙地运用了欧拉函数的性质

本人题解写得少，风格不太好看麻烦谅解一下

题目大意：

求解  

$ \sum_{i=1}^{n} \sum_{j=1}^{n} gcd(i,j)$



我们化简一下这个式子：

 $ \sum_{i=1}^{n} \sum_{j=1}^{n} gcd(i,j)$
 


$ = \sum_{i=1}^{n} \sum_{j=1}^{n}\sum_{d|gcd(i,j)}φ(d)$
 


（以上的转换用到了一个知识点：一个数等于它的因子的欧拉函数之和）
 


$ = \sum_{i=1}^{n} \sum_{j=1}^{n} \sum_{d|i,j}φ(d)$
 


（以上的转换是因为：如果这个数是$i$和$j$的最大公约数的因子，那么这个数一定既是$i$的因子，又是$j$的因子）
 


$ = \sum_{d=1}^{n}φ(d)*(n/i)*(n/i)$
 


（我们转变一下，从枚举$i$和$j$传为枚举$φ(d)$，直接统计每个$φ(d)$对答案有多少次的贡献）

代码如下：


 ```cpp
#include<iostream>
#include<cstdio>

using namespace std;

const int maxn = 100005;

int n, cnt;

long long ans;
long long phi[maxn], prime[maxn], sum[maxn]; // 数据比较大，要开longlong 

bool check[maxn];

void Euler_Phi(int num) //预处理出来1 ~ n的欧拉函数的值 
{
	check[1] = true;
	phi[1] = 1;
	for(register int i = 2; i <= num; i++)
	{
		if(!check[i])
		{
			prime[++cnt] = i;
			phi[i] = i - 1;
		}
		for(register int j = 1; j <= cnt && i * prime[j] <= num; j++)
		{
			check[i * prime[j]] = true;
			if(i % prime[j] != 0) phi[i * prime[j]] = phi[i] * (prime[j] - 1);    //如果对欧拉函数的线性递推有疑问的话，可以按照欧拉函数的公式自己手动模拟一下 
			else {
				phi[i * prime[j]] = phi[i] * prime[j]; 
				break;
			}
		}
	}
	for(register int i = 1; i <= num; i++) sum[i] = sum[i - 1] + phi[i]; // 用于主函数里数论分块的优化，不用数论分块优化的话可以忽略 
}

int main()
{
	cin >> n;
	Euler_Phi(n);
	register int l, r;  // 以下的这个循环为数论分块，用来优化时间，如果看不懂下面的这个循环直接换为按照推出来的最终式子来枚举 
	for(l = 1; l <= n; l = r + 1) 
	{
		r = n / (n / l);
		ans += (sum[r] - sum[l - 1]) * (n / l) * (n / l);
	}
	cout << ans << '\n';
	return 0;
}
```

对本题有什么疑问的话直接在讨论区发或者洛谷私信都可以，本人看到后及时回复。

谢谢阅读。

---

## 作者：流逝丶 (赞：19)

首先将题目化简为

$\sum_{i=1}^{n}\sum_{j=1}^{n}\gcd(i,j)$;

我们枚举i，j约数d

$\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{d|i,j}\gcd(i,j)==d$;

再进行变换得$\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{d|i,j}d*\gcd(i/d,j/d)==1$

将约数的枚举提前$\sum_{d=1}^{n}d\sum_{i=1}^{\frac{n}{d}}\sum_{j=1}^{\frac{n}{d}}\gcd(i,j)==1$

将最后一个sum变换$\sum_{d=1}^{n}d(\sum_{i=1}^{\frac{n}{d}}{(2*\sum_{j=1}^{i}\gcd(i,j)==1)}-1)$

发现最后一个sum就是欧拉函数$\phi(i)$

最后一步变换得$\sum_{d=1}^{n}d(2*\sum_{i=1}^{\frac{n}{d}}{\phi(i)}-1)$

对欧拉函数进行线性筛并求前缀和方便查询

时间复杂度O(n)

然后就可以AC 这道题了

完整代码

```cpp
#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
const int maxn=1e5+5;
int n,cnt;
LL ans;
int phi[maxn],pri[maxn],vis[maxn];
LL sum[maxn];
inline void get_phi(int x){
	phi[1]=1;
	for(int i=2;i<=x;++i){
		if(!vis[i]){
			pri[++cnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=cnt&&pri[j]*i<=x;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){
				phi[i*pri[j]]=phi[i]*pri[j];
				break;
			}
			phi[i*pri[j]]=phi[i]*(pri[j]-1);
		}
	}
	for(int i=1;i<=x;++i)sum[i]=sum[i-1]+phi[i];
}
int main(){
	scanf("%d",&n);
	get_phi(n);
	for(int i=1;i<=n;++i)
		ans+=(2*sum[n/i]-1)*i;
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：subarude (赞：12)

### 一篇~~随意口胡瞎推式子~~的题解

听机房的大佬们说这个推式子的方式叫欧拉反演？~~qwq原来我会这东西~~



------------


- **前备知识**

$$\sum_{d|n}\varphi(d)=n$$

~~（详见欧拉函数的性质qwq）~~



------------


- **进入正题**

题目要求的东西是
$$\sum_{i=1}^{n} \sum_{j=1}^{n}gcd(i,j)$$

由那个前备知识可以得到
$$gcd(i,j)=\sum_{d|gcd(i,j)}\varphi(d)$$

那么我们我们阔以把要求的式子化为
$$\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{d|gcd(i,j)}\varphi(d)$$

$d|gcd(i,j)$显然又可以写成$d|i\ and\ d|j$即$d|i,j$

则

$$\text{原式}=\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{d|i,j}\varphi(d)\qquad\qquad\qquad$$

$$=\sum_{d=1}^{n}\varphi(d)\sum_{i=1}^{n}\sum_{j=1}^{n}[d|i][d|j]$$

$$=\sum_{d=1}^{n}\varphi(d)\sum_{i=1}^{n}[d|i]\sum_{j=1}^{n}[d|j]$$

$$=\sum_{d=1}^{n}\varphi(d)\lfloor\frac{n}{d}\rfloor\lfloor\frac{n}{d}\rfloor\qquad\quad$$

$$=\sum_{d=1}^{n}\varphi(d)\lfloor\frac{n}{d}\rfloor^{2}\qquad\qquad$$


时间复杂度为$O(n)$



------------



~~放上丑陋的代码qwq~~

```cpp
#include <cstdio>
#include <iostream>
#define int long long
using namespace std;

inline int read() {
	int op = 1, a = 0; char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') op = -1;
	for (; c >= '0' && c <= '9'; c = getchar()) a = a * 10 + c - '0';
	return op * a;
}

const int maxn = 2000003;

int cnt;
int phi[maxn];
int prime[maxn];

void Euler() {
	phi[1] = 1;
	for (int i = 2; i <= maxn - 3; i++) {
		if (!phi[i]) prime[++cnt] = i, phi[i] = i - 1;
		for (int j = 1; j <= cnt && i * prime[j] <= maxn - 3; j++) {
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else phi[i * prime[j]] = phi[i] * phi[prime[j]];
		}
	}
}

int n, ans;

signed main() {
	n = read();
	Euler(); 
	for (int i = 1; i <= n; i++)
		ans += phi[i] * (n / i) * (n / i);
	cout << ans << '\n';
	return 0;
}
```



------------


这个东西还可以稍微扩展一下，把其中一个$n$换成$m$

$$\sum_{i=1}^{n} \sum_{j=1}^{m}gcd(i,j)\qquad$$

$$=\sum_{i=1}^{n}\sum_{j=1}^{m}\sum_{d|i,j}\varphi(d)\qquad\quad$$

$$\qquad=\sum_{d=1}^{min(n,m)}\varphi(d)\sum_{i=1}^{n}\sum_{j=1}^{m}[d|i][d|j]$$

$$\qquad=\sum_{d=1}^{min(n,m)}\varphi(d)\sum_{i=1}^{n}[d|i]\sum_{j=1}^{m}[d|j]$$

$$=\sum_{d=1}^{min(n,m)}\varphi(d)\lfloor\frac{n}{d}\rfloor\lfloor\frac{m}{d}\rfloor\quad$$


---

## 作者：青衫白叙 (赞：8)

楼下的题解已经很好了，，但是我有(~~看到了~~)更好的做法(真的是看到，不是找的。。)。。。。

[dalao的blog](http://www.cnblogs.com/candy99/p/mobius.html)    欢迎大家成为dalao的第100个粉

不多说了，直接上图

 ![](https://cdn.luogu.com.cn/upload/pic/9222.png) 

然后有一点很重要啊。。

关于如何O(n)求欧拉函数，还可以同时把欧拉筛做掉，这样才可以O（n）解决此问题。

证明什么的。。自己去dalao的blog里翻翻还是找得到的。。（我好懒啊。。不想找。。）

然后还是找出来了啊。。[欧拉函数](http://www.cnblogs.com/candy99/p/6200660.html)

核心代码：

```cpp
int p[N],n;ll phi[N];bool notp[N];
void seive(int n){
    phi[1] = 1;
    for(int i=2;i<=n;++i) {
        if(!notp[i]) p[++p[0]] = i, phi[i] = i-1;
        for(int j=1;j<=p[0] && i*p[j]<=n;++j) {
            notp[i*p[j]] = 1;
            if(i%p[j]==0){phi[i*p[j]]=phi[i]*p[j];break;}
            phi[i*p[j]] = phi[i]*(p[j]-1);
        }
    }
    for(int i=1;i<=n;++i) phi[i] += phi[i-1];                   // 最后求了一下前缀和。。
}
ll cal(int n,int m){
    ll ans = 0;int r;
    for(int i=1;i<=n;i=r+1) {
        r = min(n/(n/i), m/(m/i));
        ans += (phi[r]-phi[i-1]) * (n/i) * (m/i);
    }
    return ans;
}
```
其他的，，好像没了吧。。。那就这样吧。。复杂度 O(n) 哦。。


---

## 作者：万弘 (赞：6)

要求
$$\sum_{i=1}^n\sum_{j=1}^ngcd(i,j)$$
枚举$gcd(i,j)=x$，即
$$\sum_{i=1}^n\sum_{j=1}^n\sum_{x=1}^n[gcd(i,j)=x]\times x$$
$$=\sum_{i=1}^n\sum_{j=1}^n\sum_{x=1}^n[gcd(i/x,j/x)=1]\times x$$
变换顺序得
$$\sum_{x=1}^nx\times \sum_{i=1}^n\sum_{j=1}^n[gcd(i/x,j/x)=1]$$
由欧拉函数定义，$\varphi(n)=\sum_{i=1}^n[gcd(i,n)=1]$
原式化为
$$\sum_{x=1}^nx\times ((\sum_{i=1}^{n/x}2\varphi(i))-1)\text{  有序对所以乘2，但(x,x)只有一次}$$

考虑先$O(n)$筛法求$\varphi,sum(n)=\sum_{i=1}^n\varphi(i)=sum(n-1)+\varphi(n)$  
最后就是
$$\sum_{x=1}^nx\times (2sum(n/x)-1)$$
时间复杂度$O(n)$
```cpp
/**********/
#define MAXN 1000011
ll phi[MAXN],sum[MAXN],p[MAXN],cnt=0;
bool vis[MAXN];
void sieve(ll n)
{
	vis[1]=1;
	phi[1]=1;
	for(ll i=2;i<=n;++i)
	{
		if(!vis[i])
		{
			phi[i]=i-1;
			p[++cnt]=i;
		}
		for(ll j=1;j<=cnt&&i*p[j]<=n;++j)
		{
			vis[i*p[j]]=1;
			phi[i*p[j]]=phi[i]*(p[j]-1);
			if(i%p[j]==0)
			{
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
		}
	}
	for(ll i=1;i<=n;++i)sum[i]=sum[i-1]+phi[i];
}
int main()
{
	ll n=read(),ans=0;
	sieve(n);
	for(ll i=1;i<=n;++i)
		ans+=i*sum[n/i]*2-i;
	printf("%lld",ans);
	return 0;
}
```

Ext:  
如果有很多组(如1e5）询问呢？

---

## 作者：御坂美琴0502 (赞：6)

## 一道数学题

$\sum_{i=1}^{n}$
$\sum_{j=1}^{n}$
$gcd(i,j)$

### 暴力代码30分...
```cpp
for(register int i=1;i<=n;++i)
    for(register int j=1;j<=n;++j)
        sum+=gcd(i,j);
```

### 于是开始推式子

$\sum_{d=1}^{n}d \sum_{i=1}^{n} \sum_{j=1}^{n}$ $[gcd(i,j)==d]$

$\sum_{d=1}^{n}d \sum_{i=1}^{n/d} \sum_{j=1}^{n/d}$ $[gcd(i,j)==1]$

### 通过莫比乌斯反演得

$\sum_{d=1}^{n}d \sum_{i=1}^{n }[i$ $mod$ $d==0] \mu(\frac{i}{d}) [\frac{n}{i}]^2$  

$\sum_{d=1}^{n}d \sum_{d|i} \mu(\frac{i}{d}) [\frac{n}{i}]^2$  

$\sum_{i=1}^{n} \sum_{d|i} d\mu(\frac{i}{d})[\frac{n}{i}]^2$  

### 出现了，欧拉函数！

$\sum_{i=1}^{n}\varphi(i)[\frac{n}{i}]^2$ 


#### 然后因为数据太水，直接写欧拉函数卡过了^_^！
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll sum,ans,n;
inline ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}
inline ll euler(ll n)
{
    ll tmp=n;
    for(register ll i=2;i*i<=n;++i)
    {
        if(n%i) continue;
        tmp=tmp-tmp/i;
        do n/=i;
        while(n%i==0);
    }
    if(n>1) tmp=tmp-tmp/n;
    return tmp;
}
int main()
{
    scanf("%lld",&n);
    for(register ll i=1;i<=n;++i) 
    	sum+=euler(i)*(n/i)*(n/i);
    cout<<sum<<endl;
}

```


---

## 作者：hongzy (赞：6)

## 题意

求$\sum_{i=1}^{n}\sum_{j=1}^{n} gcd(i,j)$，$n<=10^5$

## 题解

推一下式子，这个过程是莫比乌斯反演的经典套路

$$\sum_{i=1}^{n}\sum_{j=1}^{n} gcd(i,j)$$

$$=\sum_{d=1}^{n}\sum_{i=1}^{n}\sum_{j=1}^{n} [gcd(i,j) = d]$$

$$=\sum_{d=1}^{n}d\sum_{i'=1}^{\lfloor \frac{n}{d}\rfloor}\sum_{j'=1}^{\lfloor \frac{n}{d}\rfloor} [gcd(i',j') = 1]$$

$$=\sum_{d=1}^{n}d\sum_{i'=1}^{\lfloor \frac{n}{d}\rfloor}\sum_{j'=1}^{\lfloor \frac{n}{d}\rfloor} e(gcd(i',j'))$$

用莫比乌斯函数展开$e$函数：

$$=\sum_{d=1}^{n}d\sum_{i'=1}^{\lfloor \frac{n}{d}\rfloor}\sum_{j'=1}^{\lfloor \frac{n}{d}\rfloor} \sum_{d'|gcd(i',j')}\mu(d')$$

$$=\sum_{d=1}^{n}d\sum_{i'=1}^{\lfloor \frac{n}{d}\rfloor}\sum_{j'=1}^{\lfloor \frac{n}{d}\rfloor} \sum_{d'|i',d'|j'}\mu(d')$$

变换枚举顺序，把$d'$提前:

$$=\sum_{d=1}^{n} d\sum_{d'=1}^{n}\mu(d') \sum_{i'=1,d'|i'}^{\lfloor \frac{n}{d}\rfloor}\sum_{j'=1,d'|j'}^{\lfloor \frac{n}{d}\rfloor} 1$$

$$=\sum_{d=1}^{n} d\sum_{d'=1}^{n}\mu(d') \sum_{i'=1}^{\lfloor \frac{n}{dd'}\rfloor}\sum_{j'=1}^{\lfloor \frac{n}{dd'}\rfloor} 1$$

$$=\sum_{d=1}^{n} \sum_{d'=1}^{n}id(d)\mu(d') \lfloor \frac{n}{dd'}\rfloor \lfloor \frac{n}{dd'}\rfloor$$

枚举$k=dd'$：

$$=\sum_{k=1}^{n}\sum_{d=1}^{n}id(d)\mu(\lfloor \frac{k}{d}\rfloor) \lfloor \frac{n}{k}\rfloor \lfloor \frac{n}{k}\rfloor$$

$$=\sum_{k=1}^{n}(id*\mu)(k) \lfloor \frac{n}{k}\rfloor \lfloor \frac{n}{k}\rfloor$$

注意狄利克雷卷积的性质：$id*\mu=\phi$

$$=\sum_{k=1}^{n}\phi(k) \lfloor \frac{n}{k}\rfloor \lfloor \frac{n}{k}\rfloor$$

于是可以线性筛$O(n)$预处理$\phi$，然后通过数论分块$O(\sqrt n)$计算答案.

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

typedef long long LL;

const int MAXN = 100100;

bool tag[MAXN];
int n, pr[MAXN], cnt, phi[MAXN];
LL phis[MAXN], ans;

void sieve(int n) { //线性筛模版 
	memset(tag, 1, sizeof tag); tag[1] = false;
	phi[1] = phis[1] = 1;
	for(int i = 2; i <= n; i ++) {
		if(tag[i]) {
			pr[++ cnt] = i;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= cnt && i * pr[j] <= n; j ++) {
			tag[i * pr[j]] = false;
			if(i % pr[j] == 0) {
				phi[i * pr[j]] = phi[i] * pr[j];
				break ;
			}
			phi[i * pr[j]] = phi[i] * (pr[j] - 1);
		}
		phis[i] = phis[i - 1] + phi[i]; //phis为欧拉函数的前缀和. 
	}
}

int main() {
	scanf("%d", &n);
	sieve(n);
	for(int i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i); //j为当前块的右端点，i为左端点 
		ans += (n / i) * 1ll * (n / i) * (phis[j] - phis[i - 1]);
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：BlueArc (赞：6)

记f(n)=gcd(1,n)+gcd(2,n)+...+gcd(n-1,n)

则答案为2\*[f(2)+f(3)+..+f(n)]+gcd(1,1)+gcd(2,2)+...+gcd(n,n)

=2\*[f(2)+f(3)+..+f(n)]+(1+n)\*n/2

注意到所有的gcd(x,n)的值都是n的约数，可以把这些约数分类,设g(n,i)表示满足条件为gcd(x,n)=i且x为正整数的x的个数

则f(n)=sigma{i\*g(n,i),i为n的约数}

因为gcd(x,n)=i的充要条件为gcd(x/i,n/i)=1，因此满足条件的x/i有

phi(n/i)个(phi为欧拉函数),所以g(n,i)=phi(n/i)

再用前缀和递推出s[n]=f(2)+f(3)+...+f(n)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long //还是自觉换long long 更好吧
const int maxn=100000+5;
int phi[maxn];
int f[maxn];
int s[maxn];
void phi_table(int n)
{
 for(int i=2;i<=n;i++) phi[i]=0;
 phi[1]=1;
 for(int i=2;i<=n;i++) if(!phi[i]) 
  for(int j=i;j<=n;j+=i)
  {
   if(!phi[j]) phi[j]=j;
   phi[j]=phi[j]/i*(i-1);
  }
} 
 main()
{
 int n;
 cin>>n;
 phi_table(n);
 for(int i=1;i<=n;i++)
  for(int j=i*2;j<=n;j+=i)
  f[j]+=i*phi[j/i];
 for(int i=1;i<=n;i++) s[i]=s[i-1]+f[i];
 cout<<s[n]*2+(1+n)*n/2;
 return 0;
}

```

---

## 作者：decoqwq (赞：3)

莫比乌斯反演

这道题就是让你求$\sum_{d=1}^n\sum_{i=1}^{n}\sum_{j=1}^n(gcd(i,j)=d)$

把式子改为$\sum_{d=1}^n\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor} \sum_{j=1}^{\lfloor \frac{n}{d} \rfloor}(gcd(i,j)=1) $，求和的时候我们乘上$d$即可

然后就是莫比乌斯反演基本套路，后面那一截$\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor} \sum_{j=1}^{\lfloor \frac{n}{d} \rfloor}(gcd(i,j)=1)$就相当于$\sum_{k=1}^{\lfloor\frac{n}{d}\rfloor}\mu(k)\lfloor\frac{n}{id}\rfloor\lfloor\frac{n}{jd}\rfloor$

然后枚举$n$，后面整除分块，时间复杂度大概是$O(n\sqrt n)$？

qwq

```cpp
#include <bits/stdc++.h>
using namespace std;
int mu[2000010],prime[400020],cnt,vis[2000010],n,m;
void shai()
{
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!vis[i])
        {
            prime[++cnt]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++)
        {
            vis[i*prime[j]]=1;
            if(i%prime[j]==0)
            {
                break;
            }
            mu[i*prime[j]]=-mu[i];
        }
        mu[i]+=mu[i-1];
    }
}
int main()
{
    cin>>n;
    shai();
    m=n;
    unsigned long long ans=0;
    for(int i=1;i<=m;i++)
    {
        n=m;
        n/=i;
        unsigned long long perans=0;
        for(int j=1;j<=n;j++)
        {
            int l=(n/(n/j));
            perans+=(unsigned long long)(mu[l]-mu[j-1])*(unsigned long long)(n/j)*(unsigned long long)(n/j);
            j=l;
        } 
        perans*=(unsigned long long)i;
        ans+=perans;
    }
    cout<<ans;
}
```

---

## 作者：huangzirui (赞：2)

题意：

求

$$\sum\limits^n_{i=1}\sum\limits^n_{j=1} \text{gcd}(i,j)$$

---

考虑 $\text{gcd}(i,j)$ 的值有哪些。

原式等于

$$\sum\limits_S\sum\limits^n_{i=1}\sum\limits^n_{j=1} S \cdot [\text{gcd}(i,j)=S]$$

$$\sum\limits_S\sum\limits_{Si \leq n}\sum\limits_{Sj \leq n} S \cdot [\text{gcd}(i,j)=1]$$

**不妨先考虑 $j\leq i$ 时**，那么若 $\text{gcd}(i,j)=1$ ， $j$ 的取值显然就有 $\varphi (i)$ 种。

那么原式就转化为

$$\sum\limits_S\sum\limits_{Si \leq n} S\ \cdot\ \varphi(i)$$

$$\sum\limits_S\sum\limits_{i=1}^{\left\lfloor\frac{n}{S}\right\rfloor} S\ \cdot\ \varphi(i)$$

前缀和优化即可。

另外这种方法只计算了 $i\leq j$ 的答案，最后答案还要特殊处理，这里不赘述。

算符复杂度 $O(n)$ ，可以通过此题。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
	char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int maxn=100010;
int i,j,k,n,m;
int prime[maxn],is_prime[maxn],num,phi[maxn];
ll Sum[maxn];
int main(){
	cin>>n;
	phi[1]=1;
	for(i=2;i<=n;i++)is_prime[i]=1;
	for(i=2;i<=n;i++){
		if(is_prime[i]){
			prime[++num]=i;
			phi[i]=i-1;
		}
		for(j=1;j<=num && prime[j]*i<=n;j++){
			is_prime[prime[j]*i]=0;
			phi[prime[j]*i]=phi[i]*(prime[j]-1);
			if(i%prime[j]==0){
				phi[prime[j]*i]=phi[i]*prime[j];
				break;
			}
		}
	}
	for(i=1;i<=n;i++)Sum[i]=Sum[i-1]+phi[i];
	ll ans=0;
	for(int S=1;S<=n;S++)
		ans+=(ll)S*(Sum[n/S]*2-1);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：laphets (赞：2)

这个题 主要是 用来教大家2个思想。


暴力的30分就不说了。

有40分是 7000-7100 考虑打表。 在自己电脑上 暴力跑出7000-7100的答案(大概要5分钟),然后输出来 存到程序里,直接输出即可。

这种技巧适用于 数据比较少的情况,要综合考虑代码长度(表太大了 cpp文件会太大)和打表的时间。





```cpp
    for (int n=7000;n<=7100;n++)
    {
        ll ans=0;
        for (int i=1;i<=n;i++)
        {
            for (int j=i+1;j<=n;j++)
                ans+=gcd(i,j)*2;
            ans+=i;
        }
        printf("f[%d]=%I64d;\n",n,ans);
    }
f[7000]=275797760;
f[7001]=275818761;
f[7002]=275909661;
f[7003]=275957900;
f[7004]=276059136;
f[7005]=276136101;
f[7006]=276211445;
f[7007]=276344088;
f[7008]=276499480;
f[7009]=276547721;
f[7010]=276616365;
f[7011]=276735228;
f[7012]=276784296;
f[7013]=276805333;
f[7014]=276928189;
f[7015]=277019184;
f[7016]=277082288;
f[7017]=277122041;
f[7018]=277231645;
f[7019]=277252700;
f[7020]=277537280;
f[7021]=277630645;
f[7022]=277665749;
f[7023]=277705536;
f[7024]=277782704;
f[7025]=277848609;
f[7026]=277911813;
f[7027]=277932892;
f[7028]=278030072;
f[7029]=278147405;
f[7030]=278286229;
f[7031]=278334776;
f[7032]=278444744;
f[7033]=278491761;
f[7034]=278526925;
f[7035]=278675500;
f[7036]=278724736;
f[7037]=278772965;
f[7038]=278953037;
f[7039]=278974152;
f[7040]=279184840;
f[7041]=279224729;
f[7042]=279296077;
f[7043]=279317204;
f[7044]=279404000;
f[7045]=279447661;
f[7046]=279521765;
f[7047]=279634760;
f[7048]=279698152;
f[7049]=279792113;
f[7050]=279966413;
f[7051]=280013164;
f[7052]=280116272;
f[7053]=280156229;
f[7054]=280191493;
f[7055]=280282448;
f[7056]=280543520;
f[7057]=280564689;
f[7058]=280599973;
f[7059]=280683164;
f[7060]=280777624;
f[7061]=280825733;
f[7062]=280952861;
f[7063]=280998240;
f[7064]=281061776;
f[7065]=281173025;
f[7066]=281208349;
f[7067]=281256908;
f[7068]=281430400;
f[7069]=281451605;
f[7070]=281585637;
f[7071]=281625696;
f[7072]=281803424;
f[7073]=281850321;
f[7074]=281970093;
f[7075]=282036468;
f[7076]=282139744;
f[7077]=282220157;
f[7078]=282255541;
f[7079]=282276776;
f[7080]=282480296;
f[7081]=282529185;
f[7082]=282564589;
f[7083]=282623572;
f[7084]=282813048;
f[7085]=282903613;
f[7086]=282967357;
f[7087]=283015400;
f[7088]=283093272;
f[7089]=283177593;
f[7090]=283247021;
f[7091]=283292580;
f[7092]=283417536;
f[7093]=283466333;
f[7094]=283501797;
f[7095]=283655352;
f[7096]=283719176;
f[7097]=283768065;
f[7098]=283948557;
f[7099]=283997212;
f[7100]=284136752;
```
下面是正解：
f[d]表示gcd=d的(i,j)有多少对.   那么sum(f[d]\*d)就是答案。 所以如何求f[d]是关键。

直接求f[d]有困难,我们可以用g[d]表示gcd是d的倍数的(i,j)有多少对,如何减去f[2\*d],f[3\*d],f[4\*d],f[5\*d]...

g[d]=(n/d)\*(n/d). 可以按n,n-1,n-2...1的顺序来求f[d].

所以总时间应该是n/1+n/2+n/3+n/4+...n/n.  这个东西 欧拉当年研究过的,有兴趣的可以百度一下,只要记住它是nlogn级别的就好(想一想筛法)。这个结论很常用,请大家记住。


```cpp
    for (int d=n;d>=1;d--)
    {
        f[d]=1ll*(1ll*n/d) * 1ll*(n/d);
        for (int i=d+d;i<=n;i+=d) f[d]-=f[i];
        ans+=f[d]*d;
    }
    printf("%I64d\n",ans);

```

---

## 作者：Lates (赞：1)

## 前置芝士

- 数论分块，一点点莫比乌斯反演

## 正文
题目要求
$$\sum_{i=1}^{n}\sum_{j=1}^{n}gcd(i,j)$$

然后再去重。

可以想到枚举$n$以内的$p$，把对答案的贡献改成$p\times gcd(i,j)=p$的数的个数

$$\sum_{p=1}^{n}p\sum_{i=1}^{n}\sum_{j=1}^{n}[gcd(i,j)=p]$$

化简式子

$$\sum_{p=1}^{n}p\sum_{i=1}^{\left \lfloor \frac{n}{p} \right \rfloor }\sum_{j=1}^{\left \lfloor \frac{n}{p} \right \rfloor }[gcd(i,j)=1]$$

因为$[gcd(i,j)=1]$只有$gcd(i,j)=1$有$1$的贡献，否则没有，所以可以替换为$\varepsilon(gcd(i,j))$

$\varepsilon(x)$即为当$x=1$时对答案贡献为$1$，否则为$0$

所以现在转化为了

$$\sum_{p=1}^{n}p\sum_{i=1}^{\left \lfloor \frac{n}{p} \right \rfloor }\sum_{j=1}^{\left \lfloor \frac{n}{p} \right \rfloor }\varepsilon(gcd(i,j))$$

由$Dirichlet$卷积得

$\varepsilon =\mu*1 \Leftrightarrow    \varepsilon(n)=\sum_{d|n}\mu(d)$

所以原式转化为
$$\sum_{p=1}^{n}p\sum_{i=1}^{\left \lfloor \frac{n}{p} \right \rfloor }\sum_{j=1}^{\left \lfloor \frac{n}{p} \right \rfloor }\sum_{d|gcd(i,j)}\mu(d)$$

转化一下求和顺序

$$\sum_{p=1}^{n}p\sum_{d=1}{\mu(d)}\sum_{i=1}^{\left \lfloor \frac{n}{p} \right \rfloor }[d\ |\ i]\sum_{j=1}^{\left \lfloor \frac{n}{p} \right \rfloor}[d\ | \ j]$$

后面两个即为求$\left \lfloor \frac{n}{p} \right \rfloor$中$d$的倍数，易知其答案为$\left \lfloor \frac{n}{pd} \right \rfloor$

所以答案转化为

$$ans=\sum_{p=1}^{n}p\sum_{d=1}\mu(d)\left \lfloor \frac{n}{pd} \right \rfloor\left \lfloor \frac{n}{pd} \right \rfloor$$

后面那玩意用数论分块和前缀和即可。

$Code：$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define int long long 
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
const int MAX=100005;
int n,tot,p[MAX],f[MAX],mu[MAX];
inline void Gmu(){
	mu[1]=1;tot=0;
	for(register int i=2;i<=n;++i){
		if(!f[i]){
			p[++tot]=i;
			mu[i]=-1;
		}
		for(register int j=1;j<=tot&&i*p[j]<=n;++j){
			f[i*p[j]]=1;
			if(i%p[j]==0){
				mu[i*p[j]]=0;
				break;
			}
			mu[i*p[j]]=-mu[i];
		}
	}
	for(register int i=1;i<=n;++i)mu[i]+=mu[i-1]; 
} 
int res,ans;
inline void solve(int n,int p){
	res=0;
	for(register int l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		res+=(mu[r]-mu[l-1])*(n/l)*(n/l);
	}
	ans+=res*p;
}
signed main(){
	n=read();
	Gmu();
	for(register int p=1;p<=n;++p)solve(n/p,p);
	printf("%lld\n",ans);
	return 0;
}
```
写得有什么问题麻烦私信笔者，谢谢

---

## 作者：big_news (赞：1)

## 打表出奇迹

~~给你一个数让你输出一个数你不打表你难道要想正解吗？~~

~~话说回来搞出这张表来还真是麻烦，隔壁\*\*\*都arc了我的表才打完。。。~~

## 分段打表

首先就是让你求一个n\*n的矩阵的前缀和，那么想到递推：
```cpp
f[i] = f[i-1] + 2 * calc(i) - i
```
其中`calc(i)`表示$\sum\limits_{k\in [1,i]}(i,k)$，也就是这个n\*n的新矩阵比原来n-1\*n-1的矩阵多出来的一行和一列的值，然后再减掉(i,i) = i，因为元素(i,i)被算了两遍。

下面是generator:
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
using namespace std;

#define LL long long

const LL N = 1e5;
const LL SEQ = 1e2; // 每一段的长度

LL f[N * 2];
LL gcd(LL a,LL b) {return b ? gcd(b, a%b) : a;}
LL calc(LL n){
	LL cnt = 0;
	for(int i=1;i<=n;i++) cnt += 2 * gcd(i,n);
	return cnt;
}

int main()
{
	freopen("p2398.data","w",stdout);
	printf("%lld,",f[1] = 1);
	for(LL i=2;i<=N;i++){
	    f[i] = f[i-1] + calc(i) - i; 
		if(!(i % SEQ)) printf("%lld,",f[i]);		
	}
}
```

然后就做完了？

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
using namespace std;

#define LL long long

const int CN = 1e5+5;

const LL SEQ = 1e2;
const LL F[CN] = {1,31080,139848,336784,.../* 省略，自己去跑generator */};

int n; LL ans;
LL gcd(LL a,LL b) {return b ? gcd(b, a%b) : a;}
LL calc(LL k){
	LL cnt = 0;
	for(int i=1;i<=k;i++) cnt += 2 * gcd(i,k);
	return cnt;
}

int main()
{
    scanf("%d",&n);

    if(n < SEQ){
    	ans = F[0]; // ans_1 = f[ 1 ]
    	for(int i=2;i<=n;i++) ans = ans + calc(i) - i;
	}
	else{
		int p = n / SEQ; 
		ans = F[p]; // ans_1 = f[ p * SEQ ]
		p *= SEQ; // 初始位置
		for(int i=p+1;i<=n;i++) ans = ans + calc(i) - i; //推出来
	}
    
    printf("%lld",ans);

    return 0;
}
```

---

## 作者：Tari (赞：1)

我们知道：
$$\sum_{d|n}\varphi(d)=n$$
所以：

原式
$$=\sum_{i=1}^N\sum_{j=1}^N\sum_{d|gcd(i,j)}\varphi(d)$$
把$d$提出来
$$=\sum_{i=1}^{\lfloor \frac{N}{d} \rfloor} \sum_{j=1}^{\lfloor \frac{N}{d} \rfloor} \sum_{d=1}^N\varphi(d)$$
$$=\sum_{d=1}^{N}\varphi(d)\lfloor \frac{N}{d} \rfloor\lfloor \frac{N}{d} \rfloor$$
于是筛 $\varphi$ 的前缀和，再整除分块就好了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
namespace Luitaryi {
const int N=100010;
int n,p[N/2],cnt; ll ans;
ll phi[N]; bool v[N];
inline void PRE() { v[1]=phi[1]=1;
  for(R i=2;i<=n;++i) {
    if(!v[i]) p[++cnt]=i,phi[i]=i-1;
    for(R j=1;j<=cnt&&i*p[j]<=n;++j) { R tmp=i*p[j];
      v[tmp]=true; if(i%p[j]==0) {
        phi[tmp]=phi[i]*p[j]; break;
      } phi[tmp]=phi[i]*(p[j]-1);
    }
  } for(R i=1;i<=n;++i) phi[i]+=phi[i-1];
}
inline void main() {
  scanf("%d",&n); PRE();
  for(R l=1,r;l<=n;l=r+1) r=n/(n/l),ans+=(phi[r]-phi[l-1])*(n/l)*(n/l);
  printf("%lld\n",ans);
}
} signed main() {Luitaryi::main(); return 0;}
```


---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P2398)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;比较简单。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;根据题意，我们要求这样一个东西：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle\sum_{i=1}^n\sum_{j=1}^n\gcd(i,j)$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到$\gcd$之类的东西，我们很自然地想到了枚举它，式子就变成了：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle\sum_{d=1}^nd\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}[\gcd(i,j)=1]$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;其中方括号返回命题为真为$1$，否则为$0$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;令$p=\lfloor\frac{n}{d}\rfloor$,则有：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\displaystyle\sum_{d=1}^nd\sum_{i=1}^p\sum_{j=1}^p[\gcd(i,j)=1]$     
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这个问题就变成了求区间$[1,p]$中的互质数对数的问题，可以用$\phi$函数解决。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$\phi(n)$表示小于$n$且与$n$互质的数的个数。则$\sum_{i=1}^p\phi(i)$为$[1,p]$中满足$j<i$的互质数对$(i,j)$的个数，再乘以$2$就是答案（可能需要特判$(1,1)$漏算或者算重的情况）
# 代码
```cpp
#include <cstdio>

typedef long long LL;

const int MAXN = 1e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar(); int f = 1;
	while( s < '0' || '9' < s ){ f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ){ x = ( x << 3 ) + ( x << 1 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ), x = -x; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

int prime[MAXN], pn;
LL phi[MAXN], pp[MAXN];
int N;
bool isPrime[MAXN];

void EulerSieve( const int siz )
{
	isPrime[1] = true, phi[1] = 0;
	for( int i = 2 ; i <= siz ; i ++ )
	{
		if( ! isPrime[i] ) prime[++pn] = i, phi[i] = i - 1;
		for( int j = 1 ; j <= pn && 1ll * i * prime[j] <= siz ; j ++ )
		{
			isPrime[i * prime[j]] = true;
			if( ! ( i % prime[j] ) )
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			phi[i * prime[j]] = phi[i] * ( prime[j] - 1 );
		}
		pp[i] = phi[i] + pp[i - 1];
	}
}

int main()
{
	read( N );
	EulerSieve( N );
	LL res = 0;
	for( int d = 1 ; d <= N ; d ++ )
		res += 1ll * d * ( 2ll * pp[N / d] + 1 );
	write( res ), putchar( '\n' );
	return 0;
}
```

---

## 作者：Dijkspfa (赞：1)

提供另外一种O(n)的做法，具体证明略(bu)去(hui)，以下简单推式子。尝试着用LateX ,希望不要有什么误差……

第一步转化和下面On做法的题解相同

$\sum_{i=1}^{n}\sum_{j=1}^{n} gcd(i,j)$

$=\sum_{d=1}^{n}d\sum_{i=1}^{n}\sum_{j=1}^{n} [gcd(i,j) = d]$

$=\sum_{d=1}^{n}d\sum_{i=1}^{n/d}\sum_{j=1}^{n/d}[gcd(i,j) = 1]$

将上式关于i,j的求和简化:

原式  $=\sum_{d=1}^{n}d*(2*\sum_{i=1}^{n/d}\sum_{j=1}^{i}[gcd(i,j) = 1]-\sum_{i=1}^{n/d}[gcd(i,i) = 1])$

$=\sum_{d=1}^{n}d*(2*\sum_{i=1}^{n/d}\sum_{j=1}^{i}[gcd(i,j) = 1]-1)$

$=\sum_{d=1}^{n}2*d*\sum_{i=1}^{n/d}φ(i) - d$

到这里式子就推完了，实际实现时求一下phi函数以及前缀和再求解，过程都是线性的。

tip : phi函数求前缀和记得开long long，不然最后一个点会炸……

代码如下：



```cpp
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
const int mxn = 100007;
int n,pri[mxn];
bool not_pri[mxn];
long long ans,phi[mxn];
inline void gt_phi()
{
    phi[1] = 1;
    for(int i = 2;i <= n;i++)
    {
        if(!not_pri[i]) pri[++pri[0]] = i,phi[i] = i-1;
        for(int j = 1;j <= pri[0]&&i*pri[j] <= n;j++)
        {
            not_pri[i*pri[j]] = 1;
            if(i%pri[j] == 0) {phi[i*pri[j]] = phi[i]*pri[j];break;}
            phi[i*pri[j]] = phi[i]*(pri[j]-1);
        }
    }
}
int main()
{
    scanf("%d",&n);
    gt_phi();
    for(int i = 1;i <= n;i++) phi[i]+=phi[i-1];
    for(int i = 1;i <= n;i++) ans += (ll)2*i*phi[n/i]-i;
    cout<<ans;
    return 0;
}
```

---

## 作者：a18071114 (赞：1)

此题利用dp的思想，分为两个数组，代表的意义分别是：

一、gcd值为d的数对个数（暂设为f数组）

二、gcd值为d的倍数的数对个数（暂设为a数组）

其中一可以用公式推导出答案，二可以用数学方法推得

然后关于一与二的关系，可以用dp的思想推导出：

f[i]：=a[i]-f[i\*2]-```-f[i\*（n div i）]；
因为a[i]直接由朱学公式推得，并且不影响之后的结果，所以在程序里不用开数组了
P.S.关于错误30分的同学，注意输入的n也要是int64！！！
因为a[i]的数学公式里最坏情况是n*n要超longint，而计算机运行的时候乘法是把n值累加到第一个n变量里然后再附值给a[i]

```delphi





```cpp
```
var i,j:longint;
  f:array[1..100000]of int64;
  n,z:int64;
begin
  readln(z);n:=0;
  for i:=z downto 1 do
  begin
    f[i]:=(z div i)*(z div i);
    for j:=2 to z div i do
      f[i]:=f[i]-f[j*i];
    n:=n+f[i]*i;
  end;
  writeln(n);
end.
bzoj2005是类似题（加强版）但如果理解这个想法后也都变简单了```cpp
```

---

## 作者：ZORO (赞：0)

# $Description$

求$\sum\limits_{i=1}^n\sum\limits_{j=1}^n gcd(i,j)$

# $Solution$

> 这种$gcd$计数的题一般思想是枚举$gcd$。

对于这道题，有一下几种做法，循序渐进

### 暴力：$O(n^2logn)$

就是暴力枚举所有数求$gcd$，期望得分不清楚，大概$20pts$

可以优化$gcd$函数，记忆化一下。

画个矩阵发现可以只求下三角，即只求$\sum\limits_{i=1}^n\sum\limits_{j=1}^{j<i}gcd(i,j)$，将答案$*2$后再单独用等差数列求和公式处理对角线上的情况$(i==j)$，一顿操作猛如虎，但因为会$MLE$仍然无法通过$70pts$

### 离正解只差一步的暴力:$O(n\sqrt n)$

枚举所有数$i$，设组成数对的另一个数为$j$，仍是只考虑$i<j$的情况。设$gcd(i,j)=k$，则$gcd(\frac{i}{k} ,\frac{j}{k})=1$，符合这样的数$\frac{j}{k}$的个数就应该是$\phi(\frac{i}{k})$，所以$O(\sqrt n)$枚举$i$的所有因数为$gcd$，$ans+=gcd\cdot \phi(\frac{i}{gcd})$。总复杂度$O(n\sqrt n)$。



$70pts$肯定是稳过的，至此离正解只差一步。

### 正解$O(nln n)$

上面枚举因子$O(\sqrt n)$显然是可以优化的，可以先枚举$gcd$，再枚举另一个因子得出$i=gcd*x$，和上面方法是等效的，调和级数$O(ln n)$总复杂度$O(n ln n)$

# $Code$

```c++
int n,prime[maxn],pcnt,is_not_prime[maxn];
int phi[maxn];
ll ans;
void Get_Phi(int x)
{
	is_not_prime[1]=1;
	for(re int i=2;i<=x;++i)
	{
		if(!is_not_prime[i]) prime[++pcnt]=i,phi[i]=i-1;
		for(re int j=1;j<=pcnt;++j)
		{
			if(i*prime[j]>x) break;
			is_not_prime[i*prime[j]]=1;
			if(!(i%prime[j]))
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			else phi[i*prime[j]]=phi[i]*phi[prime[j]];
		}
	}
}
int vis[maxn];
int main()
{
    n=read();
    Get_Phi(n);
    for(re int i=1;i<=n;++i)//枚举gcd
		for(re int j=2;j*i<=n;++j)//枚举数对中较大的数/gcd的结果，从2枚举是为了不考虑对角线 
		{
			ans+=(ll)phi[j]*i;
		}
	ans*=2;//上三角下三角 
	ans+=(ll)(1+n)*n/2;//统计对角线 
	printf("%lld\n",ans);
	return 0;
}
```











---

## 作者：COUPDETAT (赞：0)

看这题之前 先来几道类似的

# [GCD SUM](<https://www.luogu.org/problem/P2398>)

题意简单明了 十分友善

如果用欧拉函数的方法做可以很轻松的过掉 

详情请看[仪仗队](<https://www.luogu.org/problem/P2158>)

![img](https://cdn.luogu.com.cn/upload/pic/1149.png)

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<iostream>
using namespace std;
int p[1000000],phi[1000000],vis[1010101];
long long ans;
int  main(){
	
    int n;
    scanf("%d",&n);
    if(n==1){
    	cout<<0;
    	return 0;
	}
    phi[1]=1;
    for(int i=2;i<=n;i++)
    {
    	if(!vis[i])
    	p[++p[0]]=i,phi[i]=i-1;
    	for(int j=1;j<=p[0]&&i*p[j]<=n;j++)
    	{
    		vis[i*p[j]]=1;
    		if(i%p[j]==0)
    		{
    			phi[i*p[j]]=phi[i]*p[j];
    			break;
			}
			else phi[i*p[j]]=phi[i]*(p[j]-1);
		}
		//ans+=phi[i];
	}
	n--;
    ans=0;
    for(int i=1;i<=n;i++)
    {
    	ans+=phi[i];
	}
    cout<<ans*2+1;
    return 0;
}
```

代码会及其冗长

但是如果换个思路

![img](D:\OneDrive - langlangago\Pictures\2608.png)

观察这张图片 可以得到以下几个性质

1.相同点的标号等于他们的GCD

2.设一个点坐标为x,y  以gcd(x,y)为gcd的个数等于$(n/x)*(m/x)$

3.考虑对第二步从右上到左下容斥 

![](http://101.200.56.58/wp-content/uploads/2019/10/%E5%9B%BE%E7%89%87.png)

这样 我们只需要枚举gcd即可

# p2398

```cpp
#include<cstdio>
int main()
{
	long long n,m,a[100000],ans=0;
	scanf("%lld",&n);m=n;
	for(int i=1;i<=n;i++) a[i]=(n/i)*(m/i);
	for(int i=n;i>=1;i--) {
		for(int j=2;j<=n/i;j++)
			a[i]-=a[j*i];ans+=(a[i]*i);
	}	printf("%lld",ans);
}
```

# p1447

```cpp
#include<cstdio>
int main()
{
	long long n,m,a[100000],ans=0;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) a[i]=(n/i)*(m/i);
	for(int i=n;i>=1;i--) {
		for(int j=2;j<=n/i;j++)
			a[i]-=a[j*i];ans+=(a[i]*(i*2-1));
	}	printf("%lld",ans);
}
```



---

## 作者：aiyougege (赞：0)

#### Solution
![](https://cdn.luogu.com.cn/upload/pic/21263.png)

这个做法是我类比[YY的GCD](https://www.luogu.org/problemnew/show/P2257)得到的.

然后这个$h(t)$可以**线性筛**也可以直接**枚举因子**.

不过我真的没有注意到这个玩意就是欧拉函数.

和这个题非常类似的一道题: [能量采集](https://www.luogu.org/problemnew/show/P1447).

发现现在的莫比乌斯反演题很多都是套路.
什么除法分块, 换元(更改枚举顺序)……


注意: 我一开始求$h(i)$是枚举$i$的每一个因子, 错了.
后来利用一个数去更新它的倍数, 对了.

#### Code
```c++
#include<iostream>
#include<cstdio>
#include<cmath>
#define N 100005
using namespace std;

typedef long long ll;

int tot;
int mu[N];
int sum[N];
bool mark[N];
int prime[N];
ll number[N];

void getmu(int n){
    mu[1]=1;
    for(int i=2;i<=n;i++){
    	if(!mark[i]){
    		prime[++tot]=i;
    		mu[i]=-1;
    	}
        for(int j=1;prime[j]*i<=n;j++){
            if(prime[j]*i>=n)break;
            mark[prime[j]*i]=1;
            if(i%prime[j]==0){
    			mu[prime[j]*i]=0;
    			break;
    		}
            mu[prime[j]*i]=-mu[i];
        }
    }
    for(int i=1;i<=n;++i)
        for(int j=i;j<=n;j+=i)
            number[j]+=i*mu[j/i];
    // for(int i=1;i<=n;++i){
    // 	for(int d=2;d<=sqrt(i);++d)
    // 		if(i%d==0)
    // 			number[i]+=(ll)d*mu[i/d]+(ll)(i/d)*mu[d];
        // if(number[i]>0)
        // printf("%d %d\n",i,number[i]);
    // }
    for(int i=1;i<=n;++i)
    sum[i]=sum[i-1]+number[i];
}    
ll query(int n){
    int last;
    ll ans=0;
    for(ll i=1;i<=n;i=last+1){
        last=n/(n/i);
        ans+=(n/i)*(n/i)*(sum[last]-sum[i-1]);
    }
    return ans;
}

int main(){
    getmu(100000);
    int n,T=1;
    while(T--){
        scanf("%d",&n);
        printf("%lld\n",query(n));
    }
    return 0;
}
```

---

