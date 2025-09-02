# Mushroom Gnomes

## 题目描述

很久以前，在蘑菇森林的灌木丛中生活着蘑菇地精。它们以神奇的蘑菇而在邻居中闻名。它们的神奇特性使得它们每分钟可以在相邻的两个蘑菇之间长出另一个蘑菇，而该蘑菇的重量等于两个相邻蘑菇的重量之和。

蘑菇地精喜欢一切都井井有条的，这就是为什么它们总是按照重量递增的顺序将蘑菇种成一行。

地精们种下蘑菇后就去吃饭了。 $x$ 分钟后，他们返回，发现新的蘑菇长大了，因此打破了递增的顺序。

地精们按照正确的顺序重新种植了所有蘑菇，也就是说，他们按照重量递增的顺序重新对蘑菇进行了排序。然后又去吃饭了（地精们是食量很大的）。 再过 $y$ 分钟，蘑菇总重量对 $p$ 取模的值是多少？

## 样例 #1

### 输入

```
2 1 0 657276545
1 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
2 1 1 888450282
1 2
```

### 输出

```
14
```

## 样例 #3

### 输入

```
4 5 0 10000
1 2 3 4
```

### 输出

```
1825
```

# 题解

## 作者：Link_Cut_Y (赞：1)

矩阵快速幂题。个人认为可以评绿。

## 题目大意

一个数列递增序列 $a$，每秒进行一次操作：在数列中每两个相邻元素中间加入一个新的元素，值为这两个元素只和。这样的操作共进行 ${x}$ 秒。

接下来，将操作后的数列再次升序排列，并重复上述操作 ${y}$ 秒。问：最终序列的权值和对 ${p}$ 取模的值。

## 题目分析

可以先手玩一下。

将第 ${i}$ 次的结果记为 ${s_i}$，那么可以发现 ${s_i = 3 \times s_{i - 1} - a_1 - a_n}$，这里可以看做把每个数复制两份，将这两份分别加入到左右两边的空隙里，最后减去首位两个数。

而 ${s_1}$ 易得为原数列的权值和。所以前 ${x}$ 秒的答案就可以用一个矩阵快速幂来算。向量 ${\begin{bmatrix}
 s_i & d
\end{bmatrix}}$ 的每个元素分别表示当前答案和要减去的数。（当然第一次要减去的就是 $a_1 - a_n$，后面以此类推）。可以得到下面的转移矩阵：

${\begin{bmatrix}
 3 & 0 \\
 -1 & 1
\end{bmatrix}}$

前 $x$ 秒算完之后，我们又要算后 ${y}$ 秒的答案。显然，我们可以套用前面计算 ${s_x}$ 的方法，但我们要先知道数列的两端是多少。根据题目，显然是数列的最大值和最小值。

最小值肯定是 ${a_1}$，但是最大值不知道。

根据每次中间元素是两边元素相加，你会想到什么呢？没错，就是斐波那契数列。斐波那契数列每次取前两个数相加，是不是与这道题有点像呢？

手推之后发现确实是这样（手推过程就不写了，大家可以随便找两个变量试试看），最大值当然就是 $F_{x - 1} a_{n - 1} + F_{x} a_n$，其中 $F_i$ 表示斐波那契数列第 $i$ 项。

之后套用计算 $x$ 的公式即可。

## 代码示例

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i ++ )
#define rop(i, a, b) for (int i = (a); i < (b); i ++ )
#define dep(i, a, b) for (int i = (a); i >= (b); i -- )
#define dop(i, a, b) for (int i = (a); i > (b); i -- )
 
using namespace std;
 
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
 
const int N = 1000010;
int w[N], n, x, y, mod;
struct Matrix {
    int a[2][2];
    void clear(int x) {memset(a, x, sizeof a);}
    void makeI() { a[0][0] = 1; a[0][1] = 0; a[1][0] = 0; a[1][1] = 1; }
    bool empty() {return ((a[0][0] == 1) and (a[0][1] == 0) and (a[1][0] == 0) and (a[1][1] == 1));}
    void init(int _00, int _01, int _10, int _11) {
    	a[0][0] = _00, a[0][1] = _01, a[1][0] = _10, a[1][1] = _11;
	}
	
	Matrix operator + (const Matrix& B) {
	    Matrix res; res.clear(0);
	    for (int i = 0; i <= 1; i ++ )
	        for (int j = 0; j <= 1; j ++ )
	            res.a[i][j] = (a[i][j] + B.a[i][j]) % mod;
	    return res;
	}
	Matrix operator * (const Matrix& B) {
	    Matrix res; res.clear(0);
	    for (int i = 0; i <= 1; i ++ )
	        for (int j = 0; j <= 1; j ++ )
	            for (int k = 0; k <= 1; k ++ )
	                (res.a[i][j] += (a[i][k] * B.a[k][j])) %= mod;
	    return res;
	}
	Matrix &operator += (Matrix B) { *this = *this + B; return *this; }
	Matrix &operator *= (Matrix B) { *this = *this * B; return *this; }
};
Matrix operator ^ (Matrix A, int b) {
    Matrix res; res.makeI();
    while (b) {
        if (b & 1) res = res * A;
        A = A * A; b >>= 1;
    }
    return res;
}

int calc(int sum, int minn, int maxn, int k) {
	Matrix t; t.init(3, 0, -1, 1); t = t ^ k;
	Matrix ans; ans.init(sum % mod, (minn + maxn) % mod, 0, 0); ans *= t;
	return ans.a[0][0];
}
Matrix f(int x) {
	Matrix t; t.init(0, 1, 1, 1); if (x < 0) return t; t = t ^ x;
	Matrix ans; ans.init(1, 1, 0, 0); return ans * t;
}
 
signed main() {
	scanf("%lld%lld%lld%lld", &n, &x, &y, &mod);
	for (int i = 1; i <= n; i ++ )
		scanf("%lld", &w[i]);
	int sum = 0;
	for (int i = 1; i <= n; i ++ )
		(sum += w[i]) %= mod;
	
	int sum_x = calc(sum, w[1] % mod, w[n] % mod, x);
	Matrix F = f(x - 1);
	
	int sum_y = calc(sum_x, w[1], w[n - 1] * F.a[0][0] % mod + w[n] * F.a[0][1] % mod, y);
	printf("%lld\n", (sum_y + mod) % mod);
	return 0;
}
```

是目前的最优解，不过相信很快就会被打下去。

---

## 作者：Yuby (赞：0)

[题面](https://www.luogu.com.cn/record/63701562)

点数：2600

upd 2022.8.30：修正了一些问题

##### 标签：矩阵快速幂优化 dp

##### 分析：

注意到数据范围大到离谱，显然要对数级别的算法。

注意每次两个蘑菇之间会长出一个大小等于他们之和的蘑菇，所以每次的答案是原来的3倍减去头和尾。

即：$sum=sum\times3-del$。

再结合复杂度计算，个人认为想到矩阵快速幂不难。

这个计算应该不算难，但推出的转移矩阵在下面。

$\begin{matrix}3&0\\-1&1\end{matrix}$

注意前面减去的值和地精回来搞事情之后的是不一样的。，后面的 $del$ 要用斐波那契数列计算。

代码（请勿抄袭）：

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a));
#define pc putchar
#define fast_iostream ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef double db;
const ld EPS=1e-8;
const ll INF=ll(1e9+7);
const ll LLINF=ll(1e18+7);
const ld LDEPS=1e-18;
const ll MAXN=1e6+7;
inline ll max(ll x,ll y){return x>y?x:y;}
inline ll min(ll x,ll y){return x<y?x:y;}
inline ld dmax(ld x,ld y){return x>y?x:y;}
inline ld dmin(ld x,ld y){return x<y?x:y;}
inline ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
inline ll lcm(ll a,ll b){return a*b/gcd(a,b);}
inline ll lowbit(ll x){return x&(-x);}
inline ll read(){ll read_result=0,is_below_0=0;char now_ch=0;while(!isdigit(now_ch)){is_below_0|=now_ch=='-';now_ch=getchar();}while(isdigit(now_ch)){read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);now_ch=getchar();}return is_below_0?-read_result:read_result;}
inline ld dread(){ld x=0,d=0.1;char f=0,ch=getchar();while(!isdigit(ch))f|=(ch=='-'),ch=getchar();while(isdigit(ch)) x=x*10+ch-48,ch=getchar();if(ch=='.'){ch=getchar();while(isdigit(ch))x+=d*(ch^48),d*=0.1,ch=getchar();}return f?-x:x;}
inline void write(ll x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
ll n,x,y,p,MOD,a[MAXN],del,sum;
const ll MAXM=7;//矩阵阶 
struct Matrix
{
	ll m[MAXM][MAXM];
	Matrix(){memset(m,0,sizeof(m));}
	Matrix operator +(const Matrix& xx)
	{
		Matrix res;
		for(ll i=0;i<MAXM;i++)
			for(ll j=0;j<MAXM;j++)
				res.m[i][j]=(m[i][j]+xx.m[i][j])%MOD;
		return res;
	}
	Matrix operator *(const Matrix& b)
	{
		Matrix result;
		for(ll i=0;i<MAXM;i++)
			for(ll j=0;j<MAXM;j++)
				for(ll k=0;k<MAXM;k++)
					result.m[i][j]=(result.m[i][j]+m[i][k]*b.m[k][j]%MOD+MOD)%MOD;
		return result;
	}
	Matrix operator ^(ll b)
	{
		Matrix result,Base;
		for(ll i=0;i<MAXM;i++)result.m[i][i]=1;
		for(ll i=0;i<MAXM;i++)for(ll j=0;j<MAXM;j++)Base.m[i][j]=m[i][j];
		while(b)
		{
			if(b&1)result=result*Base;
			Base=Base*Base;
			b>>=1;
		}
		return result;
	}
}mian,fibo,lxy,now,ans;
ll num[MAXM],aaa[MAXM];
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	n=read(),x=read(),y=read(),p=read();MOD=p;
	for(ll i=1;i<=n;i++)
	{
		a[i]=read()%MOD;
		sum=(sum+a[i])%p;
	}
	if(n==1)
	{
		write(sum);
		return 0;
	}
	mian.m[0][0]=3,mian.m[1][0]=-1,mian.m[1][1]=1;
	num[0]=a[n-1],num[1]=a[n];
	fibo.m[0][0]=0,fibo.m[0][1]=1,fibo.m[1][0]=1,fibo.m[1][1]=1;
	ans.m[0][0]=sum;ans.m[0][1]=(a[1]+a[n])%MOD;
	now=mian^x;
	Matrix abab=ans*now;
	ans=abab;
//	cout<<ans.m[0][0]<<' '<<ans.m[0][1]<<'\n';
	if(!x)
	{
		ans.m[0][1]=a[n];
	}
	else if(x==1)ans.m[0][1]=(a[n-1]+a[n])%MOD;
	else
	{
		fibo=fibo^x;
		for(ll i=0;i<2;i++)
		{
			for(ll j=0;j<2;j++)
			{
				aaa[i]=(aaa[i]+(num[j]*fibo.m[j][i])%MOD)%MOD;
			}
		}
		ans.m[0][1]=aaa[1]%MOD;
	}
//	cout<<ans.m[0][0]<<' '<<aaa[1]<<'\n';
	ans.m[0][1]=(ans.m[0][1]+a[1])%MOD;
	mian=mian^y;
	abab=ans*mian;
	if(y)ans=abab;
	write((ans.m[0][0]+MOD)%MOD);
	return 0;
}
```





---

## 作者：C6H14 (赞：0)

## 一点废话

[题目传送门](https://www.luogu.com.cn/problem/CF60E)

[My blog](https://www.luogu.com.cn/blog/128433/#)

调代码调到怀疑人生，最后发现是最大数找错了……

## 思路

由于地精吃了一次饭后回来搞事情，所以得把两段分开来计算。

~~有病~~

先处理吃饭前的一段：

假设第 $x$ 分钟时有 $m$ 个蘑菇，蘑菇重量为 $a_1,a_2 \ldots a_m$，总重量为 $\sum_{i=1}^m a_i$，记作 $sum_x$，$sum_0$ 就是开始时所有蘑菇的总重量。

显然 $a_1,a_m$ 分别是 $x=0$ 时的左右蘑菇重量。

那么下一秒就会长出 $m-1$ 个蘑菇：$a_1+a_2,a_2+a_3 \ldots a_{m-1}+a_m$，这些新长出的蘑菇总重量为 $\sum_{i=1}^{m-1}(a_i+a_{i+1})$。

此时的总重量为：

$$
\begin{aligned} sum_{x+1} & = sum_x + \sum_{i=1}^{m-1} (a_i+a_{i+1}) \\

& = sum_x + \sum_{i=1}^m a_i +\sum_{i=2}^{m-1}a_i \\

& = sum_x + 2 * \sum_{i=1}^m a_i - a_1 - a_m \\

& = sum_x + 2*sum_x - a_1 -a_m \\

& = 3*sum_x - a_1 - a_m

\end{aligned}
$$

于是我们得到关于 $\{sum_i\}$ 的递推式：

$sum_i = 3*sum_{i-1} - a_1 - a_n$

在地精们吃完第一次饭前蘑菇的总重量就是 $sum_x$，手推封闭形式或者矩阵都可以计算，~~像我这么懒肯定选择复制矩阵模板~~。

再看吃完后的情况：

由于地精重新排了一次序，所以需要重新找到 $a_1$ 和 $a_m$。

$a_1$ 简单啊，就是 $t=0$ 时的最小值，恶心的是 $a_m$，也就是 $t=x$ 时的最大值。

稍加思索就可以知道，$a_m$ 在排序前肯定处于 $t=0$ 时最大值和次大值之间，令 $p,q$ 分别为 $t=0$ 时的最大值和次大值，手推一下 $p$ 和 $q$ 之间的序列：

- $t=0$，序列为 $p,q$

- $t=1$，序列为 $p,p+q,q$

- $t=2$，序列为 $p,2p+q,p+q,p+2q,q$

- $t=3$，序列为 $p,3p+q,2p+q,3p+2q,p+q,2p+3q,p+2q,p3q,q$

观察得到 $t>0$ 时，最大值可以表示成 $Fib_t*p+Fib_{t-1}*q$，其中 $Fib$ 为 $Fib_0=Fib_1=1$ 的斐波那契数列，信不过的可以用数学归纳法证明一下，~~但OIer谁证明啊~~。

那么用矩阵快速幂就能求出最大值了。

## 代码

为了方便做题，我把矩阵运算封装了一下

```cpp
matrix a,b,c,d,f;//a为sum的系数矩阵，b[1][1]为蘑菇总重量，b[2][1]为a1+am，d、f用于求第二次的a1+am
ll n,x,y,ma,mi=1145141919810,cnt;
int main()
{
	n=read(),x=read(),y=read(),maxn=read();
	a.n=a.m=2;
	d.n=b.n=2,d.m=b.m=1;
	f.n=f.m=2;
	f[1][1]=f[1][2]=f[2][1]=1;
	a[1][1]=3;
	a[1][2]=-1;
	a[2][2]=1;
	ll xx=0;
	for (register int i=1;i<=n;++i)
	{
		ll tmp=read();
		if (i==1 || i==n)
			cnt=(cnt+tmp)%maxn;
		if (i==1)
			mi=tmp;
		if (i==n)
			ma=tmp;
		if (i==n-1)
			xx=tmp;
		b[1][1]=(b[1][1]+tmp)%maxn;
	}
	if (n==1)
	{
		write(ma%maxn);
		return 0;
	}
	b[2][1]=cnt%maxn;
	c=a^x;
	b=c*b;//吃饭前
	d[1][1]=ma,d[2][1]=xx;
	if (!x)
		b[2][1]=ma;
	else if (x==1)
			b[2][1]=ma+xx;
		else
		{
			f=f^(x-1);
			d=f*d;
			b[2][1]=d.sum();
		}
	b[2][1]=(b[2][1]+mi)%maxn;
//	if (x)
//	{
//		ll tmp=0;
//	}
//	else
//		b[2][1]=(ma%maxn+mi%maxn)%maxn;
	c=a^y;
	b=c*b;//吃饭后
	write((b[1][1]+maxn)%maxn);
	return 0;
}
```


---

