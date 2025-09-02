# Almost Identity Permutations

## 题目描述

A permutation $ p $ of size $ n $ is an array such that every integer from $ 1 $ to $ n $ occurs exactly once in this array.

Let's call a permutation an almost identity permutation iff there exist at least $ n-k $ indices $ i $ ( $ 1<=i<=n $ ) such that $ p_{i}=i $ .

Your task is to count the number of almost identity permutations for given numbers $ n $ and $ k $ .

## 样例 #1

### 输入

```
4 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 2
```

### 输出

```
7
```

## 样例 #3

### 输入

```
5 3
```

### 输出

```
31
```

## 样例 #4

### 输入

```
5 4
```

### 输出

```
76
```

# 题解

## 作者：_6_awa (赞：5)

大意：求有多少个全排列有至少 $(n - k)$ 个数 $a_i = i$。

首先看看数据范围：$n \le 1000,k \le 4$

既然 $k$ 这么小，分类讨论都是可以做出来的。

第一种情况：$k = 1$。这时候只有一种情况，那就是原排列，因为交换任意两个数都会导致两个错位。

第二种情况：$k = 2$。表示仅能交换一次。只有一种情况：任取两个数将它们的位置交换。两个数的位置有 $\frac{n \times (n - 1)}{2}$ 种组合。

第三种情况：$k = 3$。表示取三个数将它们的顺序全部打乱，不难发现，只有两种方法：`2 3 1` 和 `3 1 2`。再来看一下排列组合。第一个数的位置为 $i$，第二个数为 $j$，则第三个数的位置就只剩 $n - j$ 种可能。答案相加即可。

第四种情况：$k = 4$。这里就有九种方法了：`2 1 4 3`、`2 4 1 3`、`2 3 4 1`、`3 1 4 2`、`3 4 1 2`、`3 4 2 1`、`4 1 2 3`、`4 3 1 2`、`4 3 2 1`。这时继续枚举就会发现：需要依次枚举三个数的位置，复杂度会超时。怎么办呢？其实，当枚举到第二个数的时候，剩下两个数只剩下 $n - j$ 个空间了，所以必然有 $\frac{(n - j) \times (n - j - 1)}{2}$ 种组合。这样就可以把时间复杂度压缩到 $O(n^2)$，完美通过。

## AC Code:

```cpp
#include <iostream>
using namespace std;
long long n,k,sum = 0;
int main()
{
    cin >> n >> k;
    if(k >= 1)sum += 1;//只有一种
    if(k >= 2)sum += n * (n - 1) / 2;//排列组合方案数
    if(k >= 3)
        for(int i = 1;i <= n - 2;i ++)sum += (1 + i) * i;
    if(k >= 4)
    {
        for(int i = n - 3;i >= 1;i --)
            for(int j = 1;j <= i;j ++)sum += (1 + j) * j / 2 * 9;//优化
    }
    cout << sum;//完美输出
}
```

---

## 作者：Karry5307 (赞：5)

### 题意

给定 $n$ 和 $k$，求至少 $n-k$ 个位置满足 $\pi_i= i$ 的排列 $\pi $ 的个数。

$\texttt{Data Range:}1\leq n\leq 1000,1\leq k\leq 4$

### 题解

本来先做了 E，发现是个套路 meet in the middle，然后顺便看了看 2D。这种简单题能放 2D，像我这种除了数学啥都不会的选手就赚大了。

注意到直接转化成至多 $k$ 个位置满足 $\pi_i\neq i$ 之后相当于恰好 $k$ 个位置满足 $\pi_i\neq i$ 的前缀和，然后用二项式系数算出这些位置的方案数乘上错排即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=2e5+51;
ll n,kk,binom,res;
ll d[10]={1,0,1,2,9};
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read(),kk=read(),binom=1;
	for(register int i=0;i<=kk;i++)
	{
		res+=d[i]*binom,binom=binom*(n-i)/(i+1);
	}
	printf("%lld\n",res);
}
```

---

## 作者：xiaohuang (赞：3)

[更好的阅读体验](https://xiaohuang888.github.io/2019/08/26/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FCodeforces888D%20Almost%20Identity%20Permutations/)

### Description in Chinese

给出$n$和$k$计算满足至少有$n - k$个位置的值$a_i = i$的$1 \sim n$的全排列的个数。

### Solution

观察题目，发现$k$的范围是$1 \sim 4$，我们不妨来分类讨论。

1. 当$k = 1$时，有$n - 1$个位置的数是固定的，也就是有$1$个位置是自由的，呵呵，因为要填$1 \sim n$，发现填的数也只有一种。

2. 当$k = 2$时，有$n - 2$个位置是固定的，还有$2$个位置是可以自由填数的，选位置的方案有$\binom{n}{2}$，我们先计算有$n - 2$个位置固定且仅有$n - 2$个位置固定的情况，每一个选位置的方案可以有$(2 - 1) \times  = 1$种放法，因为每一个位置不能填自己的编号。

```
 id: 1 2
num: 2 1
```

所以一共有$\binom{n}{2} \times 1$种，然后再加上$k = 1$的情况，即答案为$\binom{n}{2} \times 1 + 1 =\binom{n}{2} + 1$。

1. 当$k = 3$时，同情况$2$，答案为$\binom{n}{3} \times 2 + \binom{n}{2} \times 1 + 1 = 2 \times \binom{n}{3} + \binom{n}{2} + 1$。

2. 当$k = 4$时，同情况$2$，答案为$\binom{n}{4} \times 9 + \binom{n}{3} \times 2 + \binom{n}{2} \times 1 + 1 = 9 \times \binom{n}{4} + 2 \times \binom{n}{3} + \binom{n}{2} + 1$。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

typedef long long LL;
int n, k;
inline LL Combination(int x, int y) {//求组合数
    LL ret = 1;
    for (int i = x; i >= x - y + 1; i--)
        ret *= i;
    for (int i = 1; i <= y; i++)
        ret /= i;
    return ret;
}
int main() {
    scanf("%d%d", &n, &k);
    if (k == 1) printf("1\n"); else
    if (k == 2) printf("%lld\n", Combination(n, 2) + 1); else
    if (k == 3) printf("%lld\n", Combination(n, 2) + Combination(n, 3) * 2 + 1); else
    if (k == 4) printf("%lld\n", Combination(n, 2) + Combination(n, 3) * 2 + Combination(n, 4) * 9 + 1);//分类讨论
    return 0;
}
```

---

## 作者：littlesnake (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF888D)

首先我们看一眼数据范围：$n \le 10^3,k \le 4$。

$k$ 非常小，因此我们可以从 $k$ 来入手。

挨个枚举 $k$ 不就是了吗？

- 当 $k=1$ 时，只有一种情况，就是原排列，让 $ans$ 加上 $1$。
- 当 $k=2$ 时，就只能交换 $1$ 次，所以让 $ans$ 加上 $\frac{n \times (n-1)}{2}$。
- 当 $k=3$ 时，可以取出 $3$ 个数，并且把它们的顺序打乱。如果第一个数的位置为 $x$，第二个数为 $y$，那么第三个就只有 $n-j$ 种情况。
- 当 $k=4$ 时，需要枚举 $3$ 个数，但 $(10^3)^3=1000^3=10^9$，而通常计算机每秒钟只能运算到 $10^8$，因此会超时。但其实我们在枚举到第 $2$ 个数时，已经可以得出答案 $\frac{(n-j) \times (n-j-1)}{2}$ 了。

下面代码就好写了。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,k,ans;
int main(){
    cin>>n>>k;
    if(k>=1){
        ans+=1;
    }
    if(k>=2){
        ans+=n*(n-1)/2;
    }
    if(k>=3){
        for(int i=1;i<=n-2;i++)ans+=(1+i)*i;
    }
    if(k>=4){
        for(int i=n-3;i>=1;i--){
            for(int j=1;j<=i;j++)ans+=(1+j)*j/2*9;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：落花月朦胧 (赞：1)

# CF888D Almost Identity Permutations 题解

## 题目大意

给出 $n, k$， 求满足下面条件的数组的个数
+ 至少有 $n - k$ 位的 $a_i=i$ 即有 $k$ 位错放。

## 解

题目大意可以理解为一个关于错放的问题。

[错放问题求解](https://www.cnblogs.com/Zheng-XiangYu/p/15874365.html#%E9%80%92%E6%8E%A8%E6%B1%82%E9%94%99%E6%94%BE%E6%95%B0%E9%87%8F)

但是本题有一个“至少”。

有 $k$ 个数错排，又可以理解为在 $n$ 里选择 $k$ 个数错排，根据乘法原理可以得到答案应该是:$C(n, k)\times f_k$，其中 $f_k$ 表示 $k$ 个数错排的方案数量。

当 $k=1$ 时只有一种方案数。

答案就是 $\sum_{i=2}^{k}(C(n,i)\times f_i)+1$ 其中的加 1 是加的 $i=1$ 时的 1。
## Code
```cpp
#include <bits/stdc++.h>

using i64 = long long;
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);std::cout.tie(0);
	
	int n, k;
	std::cin >> n >> k;
	
	std::vector<std::vector<i64> > c(n + 1, std::vector<i64>(n + 1));
	
	c[0][0] = c[1][0] = c[1][1] = 1;
	for (int i = 2; i <= n; i++) {
		c[i][0] = 1;
 		for (int j = 1; j <= i; j++) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]);
		}
	}
	
	std::vector<i64> f(n + 1);
	f[1] = 0, f[2] = 1;
	for (int i = 3; i <= n; i++) {
		f[i] = (i - 1) * (f[i - 1] + f[i - 2]);
	}
	
 	i64 ans = 1;
	for (int i = 2; i <= k; i++) {
		ans += c[n][i] * f[i];
	}
	std::cout << ans << std::endl;
	
		
	return 0;
}

```


---

## 作者：两年打铁 (赞：1)

假蓝题，我们对于，k=1明显答案是1,对于2-k考虑，

选出k个数使这些数错排，那再乘个错排就行了，最后把2-k的答案累加

```
#include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define int long long 
using namespace std;

inline void read(int &x)
{
	x=0;char ch=getchar();int pd=1;
	while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x*=pd;
}
inline void write(const int &x)
{
	char ggg[10001];int s=0;int tmp=x;
	if(tmp==0){putchar('0');return;}
	if(tmp<0){tmp=-tmp;putchar('-');}
	while(tmp>0){ggg[s++]=tmp%10+'0';tmp/=10;}
	while(s>0){putchar(ggg[--s]);}
}

int c[1010][1010];
int f[10];
int ans=1,n,k;

void init()
{
	for(register int i=0;i<=1000;++i)
	{
		c[i][0]=1;
		for(register int j=1;j<=i;++j)
		{
			c[i][j]=c[i-1][j]+c[i-1][j-1];
		}
	}
	f[1]=0;
	f[2]=1;
	for(register int i=3;i<=4;++i)
	{
		f[i]=(i-1)*(f[i-1]+f[i-2]);
	} 
}


signed main()
{
	init();
	read(n);
	read(k);
	for(register int i=2;i<=k;++i)
	{
		ans+=c[n][i]*f[i];
	}
	write(ans);
	return 0;
}

```


---

## 作者：Priestess_SLG (赞：0)

$k$ 很小，考虑对 $k$ 的值暴力分讨。

计算出 $F_i$ 表示长度为 $i$ 的排列 $p$ 满足 $\forall j\in [1,i],p_i\neq i$ 的不同排列 $p$ 的数量。有 $F_0=1$，$F_1=0$，$F_2=1$，$F_3=2$，$F_4=9$。

然后枚举 $1\sim k$ 中的每一个 $i$ 钦定排列中有 $i$ 个位置的元素满足 $p_j\neq j$ 另外 $n-i$ 个满足 $p_j=j$。此时有 $F_i\binom{n}{i}$ 种不同的排列满足条件。特殊的 $k=1$ 时答案为 $1$。

因此时间复杂度为 $O(n)$ 可以通过。

---

## 作者：Cuiyi_SAI (赞：0)

## 题目大意

给出 $n$ 和 $k$，计算满足**至少**有 $(n-k)$ 个位置的值 $a_i=i$ 的长度为 $n$ 的排列个数。

---

## 解题思路

我们考虑 $F_n$ 表示存在 $n$ 个 $a_i\ne i$ 的位置，显然 $answer=\sum\limits_{i=0}^{k}F_i$，问题转化为求 $F_i$。

对于 $F_k$

- 考虑有 $(n-k)$ 个位置是 $a_i=i$ 的，可以枚举这些数在原排列中的位置，显然顺序已经被确定了，因此共有 $C_{n}^{n-k}=C_{n}^{k}$ 种选择。

- 考虑剩下的 $k$ 个位置，那么摆放的顺序必须是乱的，也就是说在这 $k$ 个位置中，必须满足对于任意 $i$ 都有 $a_i\ne i$，因此这就是个错排问题。考虑 $f_k$ 表示 $k$ 个数的错排方案数，那么这剩下的 $k$ 个数就有 $f_k$ 种填法。

因为乘法原理，所以最终有 $F_k=C_{n}^{k}\times f_k$。

由于 $k\le 4$，对于错排方案数 $f_i$ ，我们有递推式 $f_i=(i-1)(f_{i-1}+f_{i-2})$，可以线性预处理。组合数也直接暴力算即可。最后统计答案就可以通过此题。

## CODE：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,f[5]={1,0,1,2,9};
long long c(int x,int y)
{
	if(y==0) return 1;
	if(y==1) return x;
	if(y>x/2) return c(x,x-y);
	__int128 fac1=1,fac2=1;
	for(int i=x-y+1;i<=x;i++) fac1*=i;
	for(int i=1;i<=y;i++) fac2*=i;
	return (long long)fac1/fac2;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	__int128 ans=0;
	for(int i=0;i<=k;i++)
	  ans+=(c(n,i)*f[i]);
	cout<<(long long)ans;
	return 0;
}

```


---

## 作者：Endt (赞：0)

# Almost Identity Permutations-题解

给出 $n$ 和 $k$ 计算满足至少有 $n-k$ 个位置的值 $a_i=i$ 的 $1\sim n$ 的排列个数。

### 分析

至少有 $n-k$ 个位置的值 $a_i=i$ 的 $1\sim n$ 的排列个数，即 $1\sim n$ 的排列中至多有 $k$ 个位置错排的排列数。

我们可以枚举错排数的个数 $t(0\le t\le k)$，从中选取 $n-t$ 个数不错排（方案数为 $C_n^{n-t}$），每一种方案又有 $D_i$ 种方式安排错排的那部分数的位置。

那么最终答案是 $\overset k{\sum\underset{t=0}}D_t\times C_n^{n-t}$。

$D$ 可以用递推公式求，$C$ 可以暴力求。时间复杂度可以通过这道题。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;

long long d[10];//错排数
long long C(long long n,long long m){//组合数
	long long ans=1;
	for(long long i=n;i>n-m;--i)ans*=i;
	for(long long i=1;i<=m;++i)ans/=i;
	return ans;
}

long long n,m;
int main(){
	d[0]=1;
	for(int i=2;i<=5;++i){//递推求错排方案数
		d[i]=(i-1)*(d[i-1]+d[i-2]);
	}
	scanf("%lld%lld",&n,&m);
	long long ans=0;
	for(long long i=0;i<=m;++i)ans+=d[i]*C(n,i);//统计 答案
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：BMTXLRC (赞：0)

观察题目数据：$n\leqslant 1000,1\leqslant k\leqslant 4$。发现 $k$ 的范围奇小无比。

对于每一组 $n,k$，我们先不要思考总共答案是多少，即我们先把题目中“至少”两字去掉后再考虑。

我们首先考虑 $k=1$ 的时候，也就是说除了一个数不一样，其他都必须一样，那很显然是不存在的，只存在所有都一样的情况，换句话说 $k=1$ 时 $ans=1$。

考虑 $k=2$，在保证有两个绝对不同的时候，其他必须相同。那很显然这两个必须是一个交换的状态，也只有一种可能，那我就可以选出这两个数，有多少种选出的方案就有多少去掉“至少”的答案。即 

$$
ans=C_{n}^{n-k}
$$

在加上“至少”两字后，我们只需要把所有 $k<2$ 的情况加入即可：

$$
ans=C_n^{n-k}+1=C_n^k+1
$$

考虑 $k=3$，对于剩下的三个不同，我们应该怎么选？这是可以枚举得到的，两种分别是 $(2,3,1)$ 和 $(3,1,2)$，那就是说我只需要选出这三个数，再把他们有多少种排列的方式乘上即可，最后加入 $k<3$ 的情况：

$$
ans=C_{n}^{n-k}\times 2+C_n^{k-1}+1=C_n^k\times 2+C_n^{k-1}+1
$$

考虑 $k=4$，对于剩下的四个不同，我们也可以枚举，先固定第一位（有 $3$ 种情况），固定第二位也有 $3$ 种情况，而剩下两位就自然固定了，也就是说选出 $4$ 个数相同的情况下，这 $4$ 个数有 $9$ 种排列方式，所以答案就是：

$$
ans=C_n^k\times 9+C_n^{k-1}\times 2+C_n^{k-2}+1
$$

至此所有的情况都枚举完了，考虑组合数咋求（为了方便我们把所有 $C_n^{n-k}$ 都替换成了 $C_n^k$），这题没有取模，又由于 $n\leqslant 1000$，所以我们可以暴力求，但是要开 `long long`，时间复杂度 $\mathcal{O}(k)$（差不多等于没有）。

代码如下：

```cpp
//CF888D
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int C(int n,int k){
    int ans=1;
    for(register int i=n;i>=n-k+1;i--) ans=ans*i;
    for(register int j=1;j<=k;j++) ans=ans/j;
    return ans;
}
signed main(){
    scanf("%lld %lld",&n,&k);
    if(k==1) printf("1");
    if(k==2) printf("%lld",C(n,2)+1);
    if(k==3) printf("%lld",C(n,3)*2+C(n,2)+1);
    if(k==4) printf("%lld",C(n,4)*9+C(n,3)*2+C(n,2)+1);
}
```

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15558537.html)

# 题目大意

给出 $n$ 和 $k$ 计算满足至少有 $n-k$ 个位置的值 $a_i=i$ 的 $1\cdots n$ 的全排列的个数。

# 题目分析

反过来想，$n-k$ 个位置 $a_i=i$，也就是 $k$ 个位置 $a_i\neq i$，**即错排问题。**

详见 [$\texttt{\color{black}P1595~信封问题}$](https://www.luogu.com.cn/problem/P1595)。

求 $k$ 个数的错排个数，有递推公式：

$$d_i=(i-1)\times(d_{i-1}+d_{i-2})$$

$d_i$ 表示第 $i$ 个数的错排个数。其中 $d_1=0$，$d_2=1$。

所以我们要在 $n$ 个位置中选择 $k$ 个位置放置数，所以答案为 $C_{n}^{i}\times d_i +1$，其中 $1\le i\le k$。

注意最后要加 $1$，因为我们没有计算 $k=1$ 时的情况。

注意：

+ 记得开 $\rm long~long$。

# 代码

```cpp
#define int long long

const int ma=1005;

int dp[ma];

int C[ma][ma];

int n,k;

inline void init()
{
	C[0][0]=1;
	
	for(register int i=1;i<=1e3;i++)
	{
		C[i][0]=1;
		 
		for(register int j=1;j<=i;j++)
		{
			C[i][j]=C[i-1][j]+C[i-1][j-1];
		}
	}
}

#undef int

int main(void)
{
	#define int long long
	
	n=read(),k=read();
	
	init();
	
	if(k==1)
	{
		printf("1\n");
	}
	
	else
	{
		int ans(0);
		
		dp[2]=1;
		
		for(register int i=3;i<=n;i++)
		{
			dp[i]=(i-1)*(dp[i-1]+dp[i-2]);
		}
		
		for(register int i=2;i<=k;i++)
		{
			ans+=C[n][i]*dp[i];
		}
		
		printf("%lld\n",ans+1);
	}
	
	return 0;
}

---

