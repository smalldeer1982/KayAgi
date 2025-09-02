# Two Divisors

## 题目描述

You are given $ n $ integers $ a_1, a_2, \dots, a_n $ .

For each $ a_i $ find its two divisors $ d_1 > 1 $ and $ d_2 > 1 $ such that $ \gcd(d_1 + d_2, a_i) = 1 $ (where $ \gcd(a, b) $ is the greatest common divisor of $ a $ and $ b $ ) or say that there is no such pair.

## 说明/提示

Let's look at $ a_7 = 8 $ . It has $ 3 $ divisors greater than $ 1 $ : $ 2 $ , $ 4 $ , $ 8 $ . As you can see, the sum of any pair of divisors is divisible by $ 2 $ as well as $ a_7 $ .

There are other valid pairs of $ d_1 $ and $ d_2 $ for $ a_{10}=24 $ , like $ (3, 4) $ or $ (8, 3) $ . You can print any of them.

## 样例 #1

### 输入

```
10
2 3 4 5 6 7 8 9 10 24```

### 输出

```
-1 -1 -1 -1 3 -1 -1 -1 2 2 
-1 -1 -1 -1 2 -1 -1 -1 5 3```

# 题解

## 作者：whhsteven (赞：12)

### 题目链接

洛谷：[CF1366D](https://www.luogu.com.cn/problem/CF1366D)

CF：[CF1366D](https://codeforces.com/problemset/problem/1366/D)

### 题意简述

给出 $n$ 个数 $a_1 \sim a_n$，对于每一个 $a_i$，求出其 $2$ 个因子 $d_1,d_2$，满足 $\gcd(d_1 + d_2, a_i) = 1$。

如果不存在，输出 $-1$。

### 解

容易想见，当 $a = p^k(p \in \mathbb{P}, k \in \mathbb{N})$ 时，不存在这样的 $2$ 个因子。这是因为，$p^k$ 的任一因子都是 $p$ 的幂，则两因子之和依然有 $p^\alpha$ 因子，不可能与 $p^k$ 互质。

那么当 $a$ 有不小于 $2$ 个质因子时，如何构造出 $d_1$ 和 $d_2$ 呢？

简单的想法是取 $d_1 = p_1, d_2 = p_2$，这里 $p_1 \not= p_2$ 是 $a$ 的 $2$ 个质因子。不过很快可以发现，这种做法无法保证 $(d_1+d_2) \not | \ \ a$。$30$ 即为一个容易举出的反例。

那么应该怎样做呢？若 $a = p^kq$，且 $p^k || a$ 即 $p \not| \ \ q$，则 $d_1 = p^k, d_2 = q$ 是满足要求的。

已经确定 $p^k \perp q$，现在需要证明 $p^k + q$ 不会成为 $a$ 的因子。

反证。我们假设 $(p^k + q) | a$，即 $(p^k + q) | p^kq$。易见，我们可以写出如下形式：

$$d(p^k + q) = p^kq$$

此处 $d \in \mathbb{N^+}$。

从而，在 $d$ 和 $(p^k + q)$ 中至少有一个是 $q$ 的倍数。

若 $q | d$，则

$$\begin{aligned}
qd^\prime(p^k+q) &= p^kq \\
d^\prime(p^k+q) &= p^k
\end{aligned}$$

很明显，这不可能成立。

若 $q | (p^k + q)$，则 $p^k$ 必然是 $q$ 的倍数。那么 $q$ 只能是 $p$ 的幂。然而前面已经限定 $p \not| \ \ q$，矛盾，故同样不成立。

综上，即得证 $d_1 = p^k, d_2 = q$ 是满足要求的一组构造。

数论证明真是妙趣横生。

&nbsp;

按当前（2021 年 6 月 25 日）的默认排序，现存题解中只有最后两篇明确提及考虑到了加和可能不互质的情形。这里通过较为详细的证明来明晰这个构造的正确性。

代码参考其它题解即可。

---

## 作者：peterwuyihong (赞：7)

题意：给定 $n\le 5\times10^5$ 个数 $1\le a\le10^7$，求出是否存在两个不为 $1$ 的约数使得他们的和和 $a$ 互质。

首先有一个显然的事实，$a$ 为 $p^k$ 的时候，必然不可能，原因显然。

否则 $a$ 必有一个质因数 $p$，另一个因数 $g$，$g=\dfrac a{p^k}$，$a$ 中有 $k$ 个 $p$，那么必然 $\gcd(p+g,a)=1$。

证明：$\gcd(p+g,p^kg)=\gcd(p+g,p^{k+1})=\gcd(p+g,p)=\gcd(p,g)=1$

于是你就做完了，筛出每个数的 $\text{lpf}$，即最小质因子，除光这个最小质因子，如果剩一个 $1$，那么就是 $p^k$ 的情况，否则就是输出 $p$ 和剩下的这个数。

复杂度 $O(a+n\log a)$，但后面这只 $\log$ 极大跑不满。

```cpp
#define maxn 10000010
int n,x;
int pri[maxn],lpf[maxn],tot;
void shai(int n){
	rep(i,2,n){
		if(!lpf[i])pri[lpf[i]=++tot]=i;
		for(int j=1;j<=lpf[i]&&i*pri[j]<=n;j++)lpf[i*pri[j]]=j;
	}
}
int a[500005],b[500005];
signed main(){
	shai(10000000);
	cin>>n;
	rep(i,1,n){
		cin>>x;
		if(x==1){
			a[i]=b[i]=-1;
			continue;
		}
		int p=pri[lpf[x]];
		while(x%p==0)x/=p;
		if(x==1){
			a[i]=b[i]=-1;
			continue;
		}
		a[i]=p,b[i]=x;
	}
	rep(i,1,n)cout<<a[i]<<' ';cout<<endl;
	rep(i,1,n)cout<<b[i]<<' ';cout<<endl;
}
```


---

## 作者：VinstaG173 (赞：5)

首先，我们很容易~~从分析样例~~看出当 $a=p^k$（$p$ 为质数，$k$ 为自然数）时不存在满足条件的 $d_1,d_2$，因为其所有大于 $1$ 的因数都被 $p$ 整除。

然后我们发现对于某个有至少两个不同质因数的 $a$，只要取其两个互质的因数当 $d_1,d_2$ 即可。

因此我们想到线性筛可以筛出最小质因数，然后将原数中包含的所有最小质因子除去，就得到了答案。

Code:
```cpp
#include<cstdio>
int mp[10000003];
int pr[1000003],cnt;
inline void sieve()
{
    mp[1]=1;
    for(int i=2;i<=1e7;++i)
    {
        if(!mp[i])
        {
            pr[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*pr[j]<=1e7;++j)
        {
            mp[i*pr[j]]=pr[j];
            if(i%pr[j]==0)break;
        }
    }
}
int n,x,a[500003],b[500003];
int main()
{
    scanf(" %d",&n);
    sieve();
    for(int i=0;i<n;++i)
    {
        scanf(" %d",&x);
        if(!mp[x])
        {
            a[i]=b[i]=-1;continue;
        }
        int p=mp[x];
        while(x%p==0)x/=p;
        if(x==1)
        {
            a[i]=b[i]=-1;continue;
        }
        a[i]=p;b[i]=x;
    }
    for(int i=0;i<n;++i)printf("%d ",a[i]);
    printf("\n");
    for(int i=0;i<n;++i)printf("%d ",b[i]);
    return 0;
}
```

---

## 作者：KellyFrog (赞：5)

这题还是挺好想的。

首先，质因数分解，$x=n_1^{k_1}\cdot n_2^{k_2}\cdot ...\cdot n_{m}^{k_m}$，$n_i$互不相同且为质数。

显然当$m=1$时没有解。

我们选$n_1^{k_1}$和$\frac{x}{n_1^{k_1}}$即可。为了方便，我们令$a=n_1^{k_1}$，$b=\frac{x}{n_1^{k_1}}$，显然$\gcd(a,b)=1$

可通过反证法证明：

若$\gcd(a+b,n)> 1$，则一定存在$p^q|n$且$p^q|a+b$，又因为$a$、$b$中有且只有一个数可被$p^q$整除（上面分解的定义），与$p^q|a+b$矛盾，故假设不成立。

用稍微改装一下线性筛记录每数因数中出现的最小质数就行了。复杂度$O(\max x+n\log \max x)$，$\log$是后面找质因数指数来的。

code:

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e7 + 5;

int low[MAXN];
vector<int> v1, v2;

int main() {
	int t, x;
	cin >> t;
	for(int i = 2; i < MAXN; i++) {
		if(low[i] == 0) {
			low[i] = i;
			for(int j = 2; i * j < MAXN; j++) {
				if(low[i * j] == 0) {
					low[i * j] = i;
				}
			}
		}
	}
	while(t--) {
		cin >> x;
		int l = low[x], ans = 1, x2 = x;
		if(low[x] == x) { //质数
			v1.push_back(-1), v2.push_back(-1);
			continue;
		}
		while(x2 % l == 0) {
			x2 /= l;
			ans *= l;
		}
		if(x2 == 1) { //只有一个质因数
			v1.push_back(-1), v2.push_back(-1);
			continue;
		}
		v1.push_back(ans), v2.push_back(x / ans);
	}
	for(auto i : v1) {
		cout << i << ' ';
	}
	cout << endl;
	for(auto i : v2) {
		cout << i << ' ';
	}
	cout << endl;
	return 0;
}
```

---

## 作者：LCuter (赞：3)

欢迎在 [我的个人博客](https://lcuter.gitee.io/2020/06/18/CF1366D%20%E9%A2%98%E8%A7%A3/#more) 观看。

## CF1366D 题解

### $\text{Description}$

给定 $n$ 个数，对每个数 $a$ 求出一对正整数 $x,y$ 满足 $x|a,y|a,\gcd(x+y,a)=1$。

$n\le 5\times 10^5,a\le 10^7$

### $\text{Solution}$

设 $d=\gcd(x,y),x'=x/d,y'=y/d$，则 $x+y=d(x'+y')$，注意到 $d|a$，则 $\gcd(d(x'+y'),a)\ge d$，故 $d$ 只能为 $1$，即 $x,y$ 互质。

那么我们选择 $a$ 的最小质因子，并取 $x$ 为其在 $a$ 中的最大幂，取 $y$ 为 $a/x$ 即可。

若一个数为质数幂，则无解。

### $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define REG register
using namespace std;
inline void read(int& x){
	static char c;
	while(!isdigit(c=getchar()));x=c^48;
	while(isdigit(c=getchar()))x=(x*10)+(c^48);
}

const int U=10000005;

int n;

int Vis[U],Prm[U],cnt,Lef[U],Div[U],tmp,D1[500005],D2[500005];

inline void Euler(){
	Lef[U]=1,Div[U]=0;
	for(REG int i=2;i<=U-5;++i){
    	if(!Vis[i]) Prm[++cnt]=i,Lef[i]=i,Div[i]=1;
    	for(REG int j=1;j<=cnt&&i*Prm[j]<=U-5;++j){
        	Vis[i*Prm[j]]=1;
        	if(!(i%Prm[j])) Lef[i*Prm[j]]=Lef[i]*Prm[j],Div[i*Prm[j]]=Div[i];
        	else Lef[i*Prm[j]]=Prm[j],Div[i*Prm[j]]=Div[i]+1;
        }
    }
}

inline void Work(){
	read(n),Euler();
	for(REG int i=1;i<=n;++i){
    	read(tmp);
    	if(Div[tmp]<=1) D1[i]=D2[i]=-1;
    	else D1[i]=Lef[tmp],D2[i]=tmp/Lef[tmp];
    }
	for(REG int i=1;i<n;++i) printf("%d ",D1[i]);
	printf("%d\n",D1[n]);
	for(REG int i=1;i<=n;++i) printf("%d ",D2[i]);
}

int main(){Work();}
```



---

## 作者：Hadtsti (赞：2)

### 题意简述

$n(1\le n\le2\times10^5)$ 次询问，每次给出正整数 $x(2\le x\le 10^7)$，要求判断是否存在 $x$ 的 $2$ 个不为 $1$ 的因数 $d_1,d_2$，使得 $\gcd(d_1+d_2,x)=1$，若存在则输出解，不存在输出 $-1$。

### 题目分析

比较好推的结论题。先给出结论：**当且仅当 $x=p^k$（$p$ 为质数，$k$ 为正整数）时，不存在符合条件的 $d_1,d_2$。**

充分性证明：若 $x=p^k$（$p$ 为质数，$k$ 为正整数），则对于所有的 $d|x$ 且 $d≠1$，有 $p|d$。因此 $p|(d_1+d_2)$，又有 $p|x$，则 $p|\gcd(d_1+d_2,x)$，得到 $\gcd(d_1+d_2,x)\ge p>1$。因此不存在符合条件的 $d_1,d_2$。

必要性证明：若 $x$ 不是质数的正整数次幂，则对其进行质因数分解得到 $x=p_1^{a_1}\times p_2^{a_2}\times\cdots\times p_k^{a_k}$。取 $d_1=p_i^{a_i}(1\le i\le k),d_2=\frac{x}{d_1}$，则 $\gcd(d_1,d_1+d_2)=\gcd(d_2,d_1+d_2)=\gcd(d_1,d_2)=1$。因此 $\gcd(d_1+d_2,x)=\gcd(d_1+d_2,d_1d_2)=1$，$d_1,d_2$ 满足题意。

有了这样一个结论，我们就只需要线性筛一下 $2\sim10^7$ 的所有质数。线性筛能顺便计算出每个数的最小质因数，所以每次根据 $x$ 的最小质因数 $p$ 判断 $x$ 是否是 $p$ 的正整数次幂即可。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,ans1[500010],ans2[500010],v[10000010],p[1000010],cnt,y;//v：最小质因数，p：质数 
int main()
{
    for(int i=2;i<=10000000;i++)
    {
        if(!v[i])
            p[++cnt]=i;
        for(int j=1;j<=cnt&&i*p[j]<=10000000;j++)
        {
            v[i*p[j]]=p[j];
            if(i%p[j]==0)
				break;
        }
    }//线性筛 
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        if(!v[x])//质数没预处理质因数，特判 
	        ans1[i]=ans2[i]=-1;//无解 
	    else
	    {
	    	y=v[x];
	        while(y<=x/v[x]&&(x/y)%v[x]==0)//计算 p 的次数（其实可以优化，但是没必要） 
				y*=v[x];
	        if(x==y)
	            ans1[i]=ans2[i]=-1;//无解 
	        else
	        	ans1[i]=y,ans2[i]=x/y;
		} 
    }
    for(int i=1;i<=n;i++)
		printf("%d ",ans1[i]);
    printf("\n");
    for(int i=1;i<=n;i++)
		printf("%d ",ans2[i]);
    return 0;
}
```


---

## 作者：ignited (赞：2)

考场上差三分钟写出正解……

题目里面每给一个$a_i$，我们就可以将它质因数分解。

$a_i=\prod\limits_{j=1}^{maxn}p_j^{k_j}$

$maxn$表示$a_i$的质因数种数，$p_j[j=1,2,\cdots,n]$均为质数，$k_j[j=1,2,\cdots,n]>0$。

我们可以构造出$maxn\geq2$符合条件的情况。

取$d_1=p_1^{k_1},d_2=\prod\limits_{j=2}^{maxn}p_j^{k_j}=\dfrac{a_i}{d_1}$即可。

下面证明这个解的正确性。

对于$a_i$任意一个质因数$p_j$，$d_1,d_2$中有且仅有一个数是$p_j$的倍数，所以$d_1+d_2$一定不是$p_j$的倍数。

从而$d_1+d_2$不是$a_i$所有质因数的倍数。

$\therefore \gcd(d_1+d_2,a_i)=1$

当$maxn=1$时显然不成立。这时两个数只能是那唯一一个质因数的幂，不合条件。

时间复杂度$\Theta(n\sqrt{n})$常数很小可以卡过去。

---

## 作者：Leasier (赞：1)

前置芝士：[线性筛](https://www.luogu.com.cn/blog/cicos/notprime)

如果 $a_i = 1$ 或 $a_i = p^k$（$p$ 为质数，$k$ 为正整数），则显然无解。

否则，考虑构造 $d_{i, 1} = \operatorname{LPF}(a_i)$（Least Prime Factor，简称 LPF），再从 $a_i$ 中除去所有 $d_{i, 1}$ 的倍数即可得到 $d_{i, 2}$。

由线性筛的原理可得：筛掉一个合数的质因数一定是其最小质因数。

据此原理在线性筛的过程中记录 LPF 即可。时间复杂度为 $O(n \log a_i + N)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int N = 1e7 + 7, M = 5e5 + 7;
int prime[N], lpf[N], ansa[M], ansb[M];
bool p[N];

inline void init(){
	int cnt = 0;
	p[0] = p[1] = true;
	for (register int i = 2; i < N; i++){
		if (!p[i]){
			prime[++cnt] = i;
			lpf[i] = i;
		}
		for (register int j = 1; j <= cnt && i * prime[j] < N; j++){
			int t = i * prime[j];
			p[t] = true;
			lpf[t] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}

void write(int n){
	if (n < 0){
		putchar('-');
		n = -n;
	}
	if (n >= 10) write(n / 10);
	putchar(n % 10 + '0');
}

int main(){
	int n;
	scanf("%d", &n);
	init();
	for (register int i = 1; i <= n; i++){
		int a, t;
		scanf("%d", &a);
		t = a;
		while (t % lpf[a] == 0){
			t /= lpf[a];
		}
		if (t == 1){
			ansa[i] = ansb[i] = -1;
		} else {
			ansa[i] = lpf[a];
			ansb[i] = t;
		}
	}
	for (register int i = 1; i <= n; i++){
		write(ansa[i]);
		putchar(' ');
	}
	putchar('\n');
	for (register int i = 1; i <= n; i++){
		write(ansb[i]);
		putchar(' ');
	}
	return 0;
}
```

---

## 作者：XioasDog (赞：0)

# CF1366D Two Divisors

因为本人很蠢，在这里提供一种不太一样的暴力做法。

首先我们注意到如果 $d_1$ 和 $d_2$ 有相同的质因数，那么一定不合法。

所以我们可以发现当原数只有一个质因数时一定无解。

其他情况下，我们使构成两数的质因数完全不相同。

接下来引出一个小结论：本题中我们只需要考虑质因子的幂次小于等于1的情况。

证明：好吧根本不会证,我就是来这里寻求帮助的(因为我就是使用上面这个奇怪结论过了题,但是无法证明)。

略过正确性,我们考虑复杂度。

因为值域是小于等于 $10^7$ 的,所以最多有8个不同的质因数,我们直接搜索,暴力枚举每个质因数是属于 $d_1$ 还是 $d_2$ 还是都不属于。这样是 $3^8n$ 的。显然不能过,然后考虑一个很抽象的优化,如果质因数包含2就一定要选2(显然)。然后我们就有 $\frac{1}{2}$ 的概率使得复杂度变成 $3^7n$。即使非常的抽象并且感觉优化不到任何东西。但实实在在地过了(所以这是一个正确性和复杂度都没有保证的垃圾算法)。

求助大佬给出证明。

代码:[code](https://codeforces.com/problemset/submission/1366/232611531)。

---

## 作者：封禁用户 (赞：0)

### 分析

结论：

+ 当 $n$ 为质数的正整数次幂时，不存在解。

证明： 令 $n = p^k$，$p$ 为质数且 $k$ 为正整数，则  $d=p^t$ 且 $t \le k$，所以 $d_1+d_2$ 是 $p$ 的整数倍，$n$ 也是 $p$ 的整数倍，与 $n$ 的最大公因数不为 $1$。  

而当 $n$ 不是质数的整数次幂时，我们令 $n = p_1^{k_1} \times p_2 ^ {k_2} \times \dots p_m ^ {k_m}$，其中 $1 < m$，我们令 $d_1 = p_1$，$d_2 = \frac{n}{p_1^{k_1}}$，则 $\gcd(d_1+d_2,n)$ 一定等于 $1$。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
const int len = 446,p[] = {0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009,1013,1019,1021,1031,1033,1039,1049,1051,1061,1063,1069,1087,1091,1093,1097,1103,1109,1117,1123,1129,1151,1153,1163,1171,1181,1187,1193,1201,1213,1217,1223,1229,1231,1237,1249,1259,1277,1279,1283,1289,1291,1297,1301,1303,1307,1319,1321,1327,1361,1367,1373,1381,1399,1409,1423,1427,1429,1433,1439,1447,1451,1453,1459,1471,1481,1483,1487,1489,1493,1499,1511,1523,1531,1543,1549,1553,1559,1567,1571,1579,1583,1597,1601,1607,1609,1613,1619,1621,1627,1637,1657,1663,1667,1669,1693,1697,1699,1709,1721,1723,1733,1741,1747,1753,1759,1777,1783,1787,1789,1801,1811,1823,1831,1847,1861,1867,1871,1873,1877,1879,1889,1901,1907,1913,1931,1933,1949,1951,1973,1979,1987,1993,1997,1999,2003,2011,2017,2027,2029,2039,2053,2063,2069,2081,2083,2087,2089,2099,2111,2113,2129,2131,2137,2141,2143,2153,2161,2179,2203,2207,2213,2221,2237,2239,2243,2251,2267,2269,2273,2281,2287,2293,2297,2309,2311,2333,2339,2341,2347,2351,2357,2371,2377,2381,2383,2389,2393,2399,2411,2417,2423,2437,2441,2447,2459,2467,2473,2477,2503,2521,2531,2539,2543,2549,2551,2557,2579,2591,2593,2609,2617,2621,2633,2647,2657,2659,2663,2671,2677,2683,2687,2689,2693,2699,2707,2711,2713,2719,2729,2731,2741,2749,2753,2767,2777,2789,2791,2797,2801,2803,2819,2833,2837,2843,2851,2857,2861,2879,2887,2897,2903,2909,2917,2927,2939,2953,2957,2963,2969,2971,2999,3001,3011,3019,3023,3037,3041,3049,3061,3067,3079,3083,3089,3109,3119,3121,3137};
int ans[500010][2],n,x;
int main()
{
	memset(ans,-1,sizeof(ans));
	read(n);
	F(i,1,n) 
	{
		read(x);
		F(j,1,len)
			if(x % p[j] == 0) 
			{
				int now = x;
				x /= p[j];
				while(x % p[j] == 0) x /= p[j];	
				if(x == 1) break;
				ans[i][0] = now/x;
				ans[i][1] = x;
				break;
			}			 
	}
	F(i,1,n) write(ans[i][0]),putchar(' ');
	putchar('\n');
	F(i,1,n) write(ans[i][1]),putchar(' ');
	return 0;
}

```


---

## 作者：Stinger (赞：0)

非常好想的一道题。

既然要求 $d_1+d_2$ 与 $a_i$ 互质，那么必须要求 $d_1$ 与 $d_2$ 互质。但是光这样还不够，因为 $a_i$ 有可能还有其它的不能表示为 $d_1^{r_1}\times d_2^{r_2}$ 的因数，则可能 $d_1+d_2$ 与 $a_i$ 不互质。比如 $d_1=3,d_2=7,a_i=42$ 就是典型的例子。那我们干脆直接钦定 $d_1^{r_1}\times d_2^{r_2}=a_i$，找到这样的 $d_1$ 与 $d_2$ 即可。容易想到随便找一个 $a_i$ 的约数作为 $d_1$，然后当 $a_i\% d_1=0$ 时不停将 $a_i$ 除以 $d_1$。如果除完了 $a_i$ 为 $1$ 无解，否则除完后的 $a_i$就是 $d_2$ 了。

```cpp
#include <cstdio>

const int N = 1e7;
int d[10000005], d2[500005], Prime[10000005], a[500005], cnt;

int main() {
	int n;
	scanf("%d", &n);
	for (int i(1); i <= n; ++ i) scanf("%d", a + i);
	for (int i(2); i <= N; ++ i) {
		if (!d[i]) Prime[++ cnt] = i;
		for (int j(1); j <= cnt && i * Prime[j] <= N; ++ j) {
			d[i * Prime[j]] = Prime[j];
			if (i % Prime[j] == 0) break;
		}
	}
	for (int i(1); i <= n; ++ i) {
		if (!d[a[i]]) continue;
		int t(d[a[i]]);
		d2[i] = a[i];
		while (d2[i] % t == 0) d2[i] /= t;
	}
	for (int i(1); i <= n; ++ i)
		if (!d[a[i]] || d2[i] == 1) printf("%d ", -1);
		else printf("%d ", d[a[i]]);
	puts("");
	for (int i(1); i <= n; ++ i)
		if (!d[a[i]] || d2[i] == 1) printf("%d ", -1);
		else printf("%d ", d2[i]);
	return 0;
}
```

---

