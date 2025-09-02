# Soldier and Number Game

## 题目描述

Two soldiers are playing a game. At the beginning first of them chooses a positive integer $ n $ and gives it to the second soldier. Then the second one tries to make maximum possible number of rounds. Each round consists of choosing a positive integer $ x&gt;1 $ , such that $ n $ is divisible by $ x $ and replacing $ n $ with $ n/x $ . When $ n $ becomes equal to $ 1 $ and there is no more possible valid moves the game is over and the score of the second soldier is equal to the number of rounds he performed.

To make the game more interesting, first soldier chooses $ n $ of form $ a!/b! $ for some positive integer $ a $ and $ b $ ( $ a>=b $ ). Here by $ k! $ we denote the factorial of $ k $ that is defined as a product of all positive integers not large than $ k $ .

What is the maximum possible score of the second soldier?

## 样例 #1

### 输入

```
2
3 1
6 3
```

### 输出

```
2
5
```

# 题解

## 作者：Cry_For_theMoon (赞：6)

&emsp;&emsp;[传送门](https://www.luogu.com.cn/problem/CF546D)

&emsp;&emsp;神仙老师讲数论布置的第一题QwQ

&emsp;&emsp;问题是 $\prod_{i=b+1}^{a} i$ 每次除以一个因数，最多除几次可以除到1

&emsp;&emsp;除以一个合数不划算，把它分解质因数，去除以它的这些质因数，显然可以多除几次。

&emsp;&emsp;因此**每次都会除以一个质数**，那么每次少掉一个质数，如果给定的数是 $A$，就是求 **$A$的质因数个数**。相信来到这道题的人都知道了欧拉筛，筛的时候 $f[prime[j]\,*\,i] = f[i]+1$ 即可，即除以最小质因子以后递推。

&emsp;&emsp;然后考虑这题给定的是乘积，显然一个乘积的质因数都是某一个乘数里的质因数，因为质数不可能再被分解。设 $f(n)$ 是 $n$ 的质因数个数（我不是很清楚有没有专门的函数表示这个，不重要），那么就变成了 $\sum_{i=b+1}^{a}f(i)$。

&emsp;&emsp;线性筛预处理，最后前缀和即可

&emsp;&emsp;注意这题好像卡cin，cout，不过用 scanf 就可以了，没必要快读

&emsp;&emsp;代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXN=5e6+10;
using namespace std; 
long long a,b,ans[MAXN];
long long f[MAXN],prime[MAXN],tot,flag[MAXN];
int t;
void solve(){
	const long long LIMIT=5e6;
	f[1] = 0;
	flag[1] = 1;
	for(long long i = 2;i<=LIMIT;i++){
		if(!flag[i]){
			prime[++tot] = i;
			f[i] = 1;
		}
		for(int j=1;j<=tot;j++){
			if(prime[j] * i > LIMIT)break;
			flag[prime[j] * i] = 1;
			f[prime[j] * i] = f[i] + 1;
			if(i % prime[j] == 0)break;
		}
	}
}
int main(){
	solve();
	scanf("%d",&t);
	for(int i=1;i<=5e6;i++){
		ans[i] = ans[i-1] + f[i];
	}
	while(t--){
		scanf("%d%d",&a,&b);
		printf("%d\n",ans[a]-ans[b]);
	}
	return 0;
}

```


---

## 作者：tuzhewen (赞：4)

我们先来看题目，它说要求$\frac{a!}{b!}$除的次数最多，所以说不能除合数，因为合数是由至少$2$个质数相乘得到的，所以还不如除以质数。那么原问题就成了求$\frac{a!}{b!}$有多少个质因子。

看数据范围，发现$b\le a$，也就是说，$\frac{a!}{b!}$中，$b!$是可以约掉的，那么原问题又成了求解$(b,a]$中有多少个质因子。

这下子问题就不难了，我们先预处理出第$i$位置前有多少个质数，记为$sum_i$（前缀和），然后每次的询问可以做到$O(1)$，答案就是$sum_a-sum_{b-1}$了（简单的前缀和思想）

那么预处理要用线性的筛法，（$5*10^6$，除了线性筛没有什么了吧）

那么代码如下：

```
#include<bits/stdc++.h>
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define D(i,r,l) for(register int i=r;i>=l;i--)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
const int INF=0x3f3f3f3f,N=5e6+5;
using namespace std;
int fr() {
	char ch=getchar();
	int num=0,k=1;
	while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();
	if(ch=='-') k=-1,ch=getchar();
	while(ch<='9'&&ch>='0') num=num*10+ch-'0',ch=getchar();
	return num*k;
}//要用快读！(有些卡常？)
int T,a,b;
int prime[N],num,sum[N];
bool isp[N];
void getprime(int n) {//基本筛法
	F(i,2,n) isp[i]=1;
	F(i,2,n) {
		if(isp[i]) prime[++num]=i,sum[i]=1;//这个位置有一个素数
		F(j,1,num) {
			if(i*prime[j]>n) break;
			isp[i*prime[j]]=false;
			sum[i*prime[j]]=sum[i]+1;//前缀和，这个位置前的所有素数就是上一个素数前所有的素数+1
		}
	}
	F(i,1,n) sum[i]+=sum[i-1];//把前缀和汇总起来
}
int main() {
	T=fr();
	getprime(5000001);//预处理
	while(T--) {
		a=fr(),b=fr();
		printf("%d\n",sum[a]-sum[b]);//输出
	}	
	return 0;
}
```

---

## 作者：Spasmodic (赞：1)

因为我不会直接线性筛，所以扔一个间接线性筛做法。

容易知道题目所求的其实就是 
$$
\sum_{p}V_p\left(\frac{a!}{b!}\right)=\sum_p(V_p(a!)-V_p(b!))
$$
其中 $V_p(n)$ 是 $n$ 中 $p$ 的质因子个数，$p$ 为质数。

所以以下只要考虑
$$
\sum_pV_p(n!)
$$
如何 $O(n)$ 计算即可。

显然有这样的一个公式：
$$
V_p(n!)=\sum_{i=1}^{\infty}\left[\frac{n}{p^i}\right]
$$
因此只需要先 $O(n)$ 的预处理出 $1\sim n$ 中的质数，再对每个质数暴力计算即可。

复杂度是 $O(\pi(n)\times \log n)=O(n)$ 的。

---

## 作者：HoshiuZ (赞：1)

要求除的次数最多，那么当然每次除以这个数的质因子了，也就是问题转化为求$n$的质因子个数。

令$n=\prod_{i=1}^mp_i^{c_i}$，其中$p_i$为质数，$c_i$为正整数，那么问题求的就是$\sum_{i=1}c_i$。

设$sum[x]$表示$x$的质因子个数，易得$sum[xy]=sum[x]+sum[y]$，于是可以用线性筛求出$1$到$5000000$的质因子个数，最后求个前缀和，对于每个输出，前缀和相减即可。
### 代码
```cpp
#include<bits/stdc++.h>
#define N 5000010

using namespace std;

int n,m=0,prime[N],v[N],sum[N];

void init(int n) {
	memset(v,0,sizeof(v));
	for(int i=2;i<=n;i++) {
		if(!v[i]) {
			v[i]=i;
			prime[++m]=i;
			sum[i]=1;
		}
		
		for(int j=1;j<=m;j++) {
			if(prime[j]*i>n||prime[j]>v[i]) break;
			v[prime[j]*i]=prime[j];
			sum[prime[j]*i]=sum[i]+1;
		}
	}
	for(int i=2;i<=n;i++) sum[i]+=sum[i-1];
}

int main() {
	scanf("%d",&n);
	init(N);
	while(n) {
		int a,b;
		scanf("%d%d",&a,&b);
		cout<<sum[a]-sum[b]<<endl;
		n--;
	}
	
	return 0;
}
```


---

## 作者：Rubidium_Chloride (赞：0)

具体而言，$\mathcal{O}(n\ln^2n)$ 的做法长什么样呢，大概就是：

对于一个素因子 $p$，可以得到 $v_p(x!)=\sum\limits_{i=1}^{\infty} \left[\dfrac{x}{p^i}\right]$。

然后线性筛素数，对于每次询问统计 $x!$ 的上述式子即可。

所以可以得到一个非常显然的 $\mathcal{O}(n\ln^2n)$ 的做法。

尝试优化。

我们不需要对于每一个 $p$ 求出上述式子的值，我们只需要知道 $\sum\limits_{p} v_p(x!)$。

也就是 $x!$ 所有的质因子个数。

我们可以单独求出每个 $i(1\le i\le x)$ 的素因数个数，然后前缀和就可以得到 $x!$ 的质因数个数了。

然后根据 CSP2021-J 的阅读程序我们发现可以把这个玩意的预处理扔到线性筛里面去。

这样的复杂度就被优化到了 $\mathcal{O}(n+t)$。

代码就不贴了。

---

## 作者：Arghariza (赞：0)

显然每次的除数 $x$ 一定是质数，因数个数具有可减性（

假设 $a!=\prod\limits_{k=1}^{n}p_k^{q_k},b!=\prod\limits_{j=1}^{m}s_j^{t_j}$ 

$\frac{a!}{b!}=\frac{\prod\limits_{k=1}^{n}p_k^{q_k}}{\prod\limits_{j=1}^{m}s_j^{t_j}}$ ，若存在 $s_k=t_j$ ，两者指数相减，答案即为 $\frac{a!}{b!}$ 因数个数，若两者相乘，因数个数相加。

但是这篇文章不是来讲废话的，大家肯定都会线性筛。

如果外层循环的 $i$ 是个质数，那么因数个数 $f(i)=1$， 当然是除自己之外的。

然后在第二层枚举此时 $f(i\times p(j))=f(i)+1$ ，即 $i$ 乘某个质数的因数个数其实就是这个 $i$ 的因数个数。

然后就可以线性预处理因数个数了，接着阶乘滚一遍因数个数前缀和，可加性和可减性如上。

卡的一批，没卡进最优解。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std; 
namespace mystd {
	inline int read() {
	    int w = 1, q = 0;
	    char ch = ' ';
	    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	    if (ch == '-') w = -1, ch = getchar();
	    while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
	    return w * q;
	}
	
	inline void write(int x) {
	    if (x < 0) {
	        x = ~(x - 1);
	        putchar('-');
	    }
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace mystd;

const int maxt = 1e6 + 1;
const int maxn = 5e6 + 5;

int t, mx, x[maxt], y[maxt];
int tot, f[maxn], p[maxn], v[maxn];

inline int max(int x, int y) { return x > y ? x : y; }

inline void init(int lim) {// 线性筛预处理
	v[1] = 1;
	for (int i = 2; i <= lim; i++) {
		if (!v[i]) p[++tot] = i, f[i] = 1;
		for (int j = 1; j <= tot && i <= lim / p[j]; j++) {
			v[p[j] * i] = 1;
			f[p[j] * i] = f[i] + 1;
			if (i % p[j] == 0) break;
		}
	}
}

signed main() {
	t = read();
	for (int i = 1; i <= t; i++) {
		x[i] = read();
		y[i] = read();
		mx = max(mx, max(x[i], y[i]));
	}
	init(mx);
	for (int i = 1; i <= mx; i++) {// 精髓的前缀和
		f[i] += f[i - 1];
	}
	for (int i = 1; i <= t; i++) {
		write(f[x[i]] - f[y[i]]);// 查询
		puts("");
	}
	return 0;
}
```

---

