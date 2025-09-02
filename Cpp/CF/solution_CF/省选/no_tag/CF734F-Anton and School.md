# Anton and School

## 题目描述

Anton goes to school, his favorite lessons are arraystudying. He usually solves all the tasks pretty fast, but this time the teacher gave him a complicated one: given two arrays $ b $ and $ c $ of length $ n $ , find array $ a $ , such that:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF734F/bffe7b936d76e107bd6e7aac7baeb51f54bd3fd0.png)

where $ a and b $ means bitwise AND, while $ a or b $ means bitwise OR.

Usually Anton is good in arraystudying, but this problem is too hard, so Anton asks you to help.

## 样例 #1

### 输入

```
4
6 8 4 4
16 22 10 10
```

### 输出

```
3 5 1 1 
```

## 样例 #2

### 输入

```
5
8 25 14 7 16
19 6 9 4 25
```

### 输出

```
-1
```

# 题解

## 作者：Caiest_Oier (赞：15)

# [CF734F](https://www.luogu.com.cn/problem/CF734F)  

思维量不高的好玩题。   

想要将这种形式的与和或的信息完全利用起来的难度是很高的，所以我们考虑对其进行一些粗浅的变换。    

首先有一个式子 $a\operatorname{and}b+a\operatorname{or}b=a+b$，这个式子的正确性可以通过按位考虑来证明。    

于是我们直接粗暴地将 $b_i$ 与 $c_i$ 加起来，得到的结果就是 $na_i+\sum_{i=1}^{n}a_i=b_i+c_i$，这样我们就得到了 $n$ 个线性无关的方程组，于是唯一确定了可能的 $a$。   

解这个方程可以选择将 $n$ 个式子加起来再除以 $2n$，就得到了 $\sum_{i=1}^{n}a_i$，对于每个式子略微处理一下就解出来了。

但是满足这个方程是 $a$ 正确的必要不充分条件，所以要验证一下，具体的验证方法就是对于每一个 $i$，按位计算它每一位与和或的值，看与 $b$ 和 $c$ 是否相等就可以了。  

代码：  

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[500003],n,b[500003],c[500003],sum;
int apr[68],fsp[68];
signed main(){
	fsp[0]=1;
	for(int i=1;i<=62;i++)fsp[i]=fsp[i-1]*2ll;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&c[i]);
	for(int i=1;i<=n;i++)sum+=b[i]+c[i];
	if(sum%(2ll*n)!=0){
		puts("-1");
		return 0;
	}
	sum/=(2ll*n);
	for(int i=1;i<=n;i++){
		if((b[i]+c[i]-sum)%n!=0){
			puts("-1");
			return 0;
		}
		a[i]=(b[i]+c[i]-sum)/n;
	}
	for(int i=0;i<=61;i++){
		for(int j=1;j<=n;j++){
			if((fsp[i]&a[j])!=0)apr[i]++;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=61;j++){
			if((a[i]&fsp[j])==0)continue;
			b[i]-=fsp[j]*apr[j];
		}
		for(int j=0;j<=61;j++){
			if((a[i]&fsp[j])!=0)c[i]-=fsp[j]*n;
			else c[i]-=fsp[j]*apr[j];
		}
		if(c[i]!=0||b[i]!=0){
			puts("-1");
			return 0;
		}
	}
	for(int i=1;i<=n;i++)printf("%lld ",a[i]);
	return 0;
}
```


---

## 作者：谁是鸽王 (赞：5)

## 题解 CF734F 【Anton and School】

这种将位运算和普通运算结合起来的题目要拆位来考虑，可以得到$log_{2}($值域$)$的算法，甚至将值域看成常数。

根据

### $a|b+a \& b=a+b$

得到

### $b_i+c_i=\Sigma a_i+na_i$

于是

### $a_i=\frac{b_i+c_i- \Sigma a_i}{n}$

根据这个式子，直接得到$a_i$，注意在除的时候判断整除以免非法情况出现。

此时，我们要判断$b_i$和$c_i$是否真的合法，考虑到位运算的性质，我们开个$cnt[x]$，记录**所有**$a_i$在二进制第$x$位出现的次数，此时，我们只需要检验——

### $b_i=2^k \times cnt[k]$


### $c_i=\Sigma a_i+2^k \times (n-cnt[k])$

这里的$k$满足

### $a_i\&(1<<(k-1))$

总复杂度$O(nlog($值域$))$，相当于$O(n)$，但理论上会爆$unsigned$ $long$ $long$ 但是它没有爆。

极其丑陋的代码

```cpp
#include<bits/stdc++.h>

#define RP(t,a,b) for(register int (t)=(a),edd_=(b);t<=edd_;++t)
#define qit return puts("-1"),0

using namespace std;typedef unsigned long long ll;
template<class ccf> inline ccf qr(ccf k){
    char c=getchar();
    ccf x=0;
    int q=1;
    while(c<48||c>57)q=c==45?-1:q,c=getchar();
    while(c>=48&&c<=57)x=x*10+c-48,c=getchar();
    return q==-1?-x:x;
}

const int maxn=200005;
ll a[maxn];
ll b[maxn];
ll c[maxn];
ll cnt[65];
ll n;ll sum;

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    n=qr(1);
    RP(t,1,n)
	b[t]=qr(1ll);
    RP(t,1,n)
	c[t]=qr(1ll);
    RP(t,1,n)
	sum+=b[t]+c[t];
    if(sum%(n<<1))
	qit;
    sum/=(n<<1);
    RP(t,1,n){
	a[t]=b[t]+c[t]-sum;
	if(a[t]%n)
	    qit;//宏
	else
	    a[t]/=n;
	RP(i,1,63)
	    if((a[t]&(1ll<<(i-1))))
		cnt[i]++;
    }
    
    ll temp=0;
    RP(t,1,n){
	temp=0;
	RP(i,1,63)
	    if(a[t]&(1ll<<(i-1)))
		temp+=cnt[i]*(1ll<<(i-1));
	if(temp!=b[t])
	    qit;//宏
	temp=sum;
	RP(i,1,63)
	    if(a[t]&(1ll<<(i-1)))
		temp+=(n-cnt[i])*(1ll<<(i-1));
	if(temp!=c[t])
	    qit;//宏
    }
    
    RP(t,1,n)
	cout<<a[t]<<' ';
    puts("");
    return 0;
}
 

```

---

## 作者：灯芯糕 (赞：5)

## $solution$  :
这道题做法很巧妙，需要对位运算有足够了解：
1. $( a $ & $ b )$ $+$ $( a $ | $ b )$ $=$ $a+b$ ，所以有 $Σb+Σc=2nΣa$

2. 看下面代码里的数位优化，可以将复杂度由 $O(n^2)$ 降为  $O(n)$

知道了这两点就可以开始构造了！

首先我们根据性质1,求出每个 $a_i$ 的值，然后检验此时的a数组是否满足题目所给的等式（要用性质2降复杂度），然后输出即可！

## $code:$
```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>

#define ll long long
#define db double
#define inf 0x7fffffff
#define rg register int
#define end {puts("-1");exit(0);}//这个要看一眼

using namespace std;

ll tot;
int n,s[33];
int a[200001];
int b[200001];
int c[200001];//如题

inline int qr(){ char ch; //（加速）
	while((ch=getchar())<'0'||ch>'9');
	int res=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
		res=res*10+(ch^48);
	return res;
}

int main(){ n=qr();
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	for(rg i=1;i<=n;++i)
		tot+=(b[i]=qr());
	for(rg i=1;i<=n;++i){
		tot+=(c[i]=qr());
		if(c[i]<b[i])end //剪枝（加速）
	}
	if(tot%(n<<1))end //剪枝（必须有！）
	else tot/=n<<1;
	for(rg i=1;i<=n;++i){
		a[i]=b[i]+c[i]-tot;
		if(a[i]%n)end //剪枝（必须有！）
		else a[i]/=n;
	} rg m,j,x,y;  //至少洛谷数据不会爆 long long
	for(rg i=1;i<=n;++i)
		for(m=a[i],j=1;m;m>>=1,++j)
		    if(m&1)++s[j]; //数位优化
	for(rg i=1;i<=n;++i){ x=y=0;
	    for(m=a[i],j=1;j<=30;m>>=1,++j)
			if(m&1)x+=s[j]<<j-1,y+=n<<j-1;//这个if看仔细了
			else y+=s[j]<<j-1;  
		if(x!=b[i]||y!=c[i])end //最有效的剪枝！（不得不有！）
	}
	for(rg i=1;i<=n;++i)
		printf("%d ",a[i]);
	return 0;
}


```

---

## 作者：Silviasylvia (赞：5)

很套路的一个题，看见 `*2500` 才来做的，结果发现是道完全没意思的题。

注意到题目中给了 and 和也给了 or 和，不难想到 $a|b+a\&b=a+b$，然后把所有的 $b_i$ 和 $c_i$ 累加起来，得到的就是 $2n\sum a$。如果不能整除就直接输出无解。

再注意到，$b_i+c_i$ 实际上是 $na_i+\sum a$，根据这个可以把每个 $a_i$ 求出来。

最后判一下是否合法，把每一位拆开，开个桶记录每一位 1 的个数，就做完了。

代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define int long long
#define YES puts("YES")
#define NO puts("NO")
#define Yes puts("Yes")
#define No puts("No")
#define edl puts("")
#define mc cerr<<"qwq\n"
#define error goto gg
#define def gg:
#define rd(x) x=read()
#define opl(x) printf("%lld",x)
#define opls(x) printf("%lld ",x)
#define opd(x) printf("%d",x)
#define opds(x) printf("%d ",x)
#define ver(x) for(int i=head[x];i;i=nxt[i])
#define up(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define pu(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define ft(x) for(int i=head[x];i;i=nxt[i])
#define upn up(i,1,n)
#define upm up(j,1,m)
#define pun pu(i,n,1)
#define pum pu(j,m,1)
#define up_(x) up(i,1,x)
#define pu_(x) pu(j,x,1)
#define ep emplace_back
#define fp for(auto to:
#define pf )
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
#define mkp make_pair
#define fi first
#define se second
#define mii map<int,int>
#define mis map<int,string>
#define msi map<string,int>
#define mvi map<vector<int>,int>
#define miv map<int,vector<int>>
#define rdn rd(n)
#define rdm rd(m)
#define rdk rd(k)
using namespace std;
int n, m, k;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}

#define inf 1000000000000000000ll
ll Max(ll a=-inf,ll b=-inf,ll c=-inf,ll d=-inf,ll e=-inf,ll f=-inf,ll g=-inf,ll h=-inf)
{
	return max(max(max(a,b),max(c,d)),max(max(e,f),max(g,h)));
}
ll Min(ll a=inf,ll b=inf,ll c=inf,ll d=inf,ll e=inf,ll f=inf,ll g=inf,ll h=inf)
{
	return min(min(min(a,b),min(c,d)),min(min(e,f),min(g,h)));
}
#undef inf
int bb[202020],c[202020];
int a[202002];
int b[33];
signed main()
{
	int T=1;
	while(T--)
	{
		rdn;
		upn rd(bb[i]);
		upn rd(c[i]);
		int sum=0;
		upn
		{
			sum+=bb[i];sum+=c[i];
		}
		if(sum%(n+n)!=0)
		{
			puts("-1");
			return 0;
		}
		sum/=n+n;
		upn
		{
			int x=bb[i]+c[i];
			x-=sum;
			if(x%n!=0)
			{
				puts("-1");
				return 0;
			}
			a[i]=x/n;
		}
		upn
		{
			up(j,0,32)
			{
				if(a[i]&(1ll<<j))
				{
					b[j]++;
				}
			}
		}
		upn
		{
			int f1=0,f2=0;
			up(j,0,32)
			{
				if(a[i]&(1ll<<j))
				{
					f1+=(1ll<<j)*n;
					f2+=(1ll<<j)*b[j];
				}
				else
				{
					f1+=(1ll<<j)*b[j];
				}
			}
			if(f1!=c[i]||f2!=bb[i])
			{
			//	cout<<f1<<" "<<f2<<" "<<a[i];edl;
				puts("-1");
				return 0;
			}
		}
		upn opls(a[i]);
		edl;
	}
}
```


---

## 作者：rickyxrc (赞：4)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

一道……构造题？

## 题目大意

有一个数列 $A$，通过 $A$ 构造出数列 $B$ 和 $C$，其中 $B_i = \sum_{k=1}^n A_i \operatorname{and} A_k$，$C_i = \sum_{k=1}^n A_i \operatorname{or} A_k$，现在给定 $B$ 和 $C$，要求你给出任意一组合法的 $A$ 或报告无解。

## 解题思路

要解这个题，我们首先要观察到这样一个性质：

$a \operatorname{or} b = \sum_{i=0}2^i \max(a_i,b_i),a \operatorname{and} b = \sum_{i=0}2^i\min(a_i,b_i)$（$a_i$ 和 $b_i$ 是数的二进制拆分低 $i$ 位）

那我们不难发现：

$$\begin{aligned}\max(a,b) + \min(a,b) &= a+b \\ a \operatorname{or} b + a \operatorname{and} b &= a+b\end{aligned}$$

插一嘴：这里和 $\gcd(a,b)\operatorname{lcm}(a,b) = ab$ 有异曲同工之妙。

回归正题，我们将 $B$ 与 $C$ 逐项相加，得出来的式子如下：

$$\begin{aligned}(B+C)_i &= \sum_{k=1} a_i + a_k \\ &= na_i \sum_{a \in A}a \end{aligned}$$

于是我们可以将所有的项加起来：

$$\begin{aligned}\sum_{i=1}^n(B+C)_i &= \sum_{i=1}^n na_i\sum_{a\in A}a \\ &= n\sum_{a\in A}a + n\sum_{a\in A}a \\ &= 2n \sum_{a\in A}a \end{aligned}$$

我们就得到了每一项的总和，将上面构造的项依次减去它即可。

无解的情况就是要除的部分整除不了。

还有就是，在构造出原序列之后，我们还需要通过原序列构造出 $A$ 数列，来二次检验答案的正确性（hack:`1 3 5`）。

那我们如何快速计算呢？这里考虑按位计算贡献。当且仅当 $a$ 和 $b$ 的二进制第 $i$ 位同为 $1$ 时才会对答案造成 $2^i$ 的贡献。

所以我们按位统计贡献即可，复杂度线对。

```cpp
#include <stdio.h>
#include <vector>

typedef long long i64;
const i64 mod = 1, maxn = 200007;

i64 li[maxn], n, u, v, diff, flg1, d, c1, sum, cnt[65], a[maxn], b[maxn], c[maxn];

int main()
{
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d", &u), a[i] += u, li[i] += u;
    for (int i = 1; i <= n; i++)
        scanf("%d", &u), b[i] += u, li[i] += u;
    for (int i = 1; i <= n; i++)
        sum += li[i];

    if (sum % (2 * n))
        return puts("-1") & 0;
    sum /= (2 * n);

    for (int i = 1; i <= n; i++)
        if ((li[i] - sum) % n)
            return puts("-1") & 0;
        else
            c[i] = (li[i] - sum) / n;

    for (int i = 1; i <= n; i++)
        for (int bit = 0; bit < 30; bit++)
            if (c[i] & (1ll << bit))
                cnt[bit]++;

    for (int i = 1; i <= n; i++)
    {
        i64 res = 0;
        for (int bit = 0; bit < 30; bit++)
            if (c[i] & (1ll << bit))
                res += (1ll << bit) * cnt[bit];
        if (res != a[i])
            return puts("-1") & 0;
    }

    for (int i = 1; i <= n; i++)
        printf("%d ", c[i]);

    return 0;
}
```


---

## 作者：Nephren_Sakura (赞：1)

题目传送门：[link](https://www.luogu.com.cn/problem/CF734F)

首先，位运算有一个很明显的性质：$a|b+a\&b=a+b$。

$\therefore b_i+c_i$

$=a_i\&a_1+a_i\&a_2+\dots+a_i\&a_n+a_i|a_1+a_i|a_2+\dots+a_i|a_n$

$=(a_i\&a_1+a_i|a_1)+(a_i\&a_2+a_i|a_2)+\dots+(a_i\&a_n+a_i|a_n)$

$=a_1+a_i+a_2+a_i+\dots+a_n+a_i$

$=\sum\limits_{i=1}^{n}a_i+n \times a_i$

所以只要知道 $\sum\limits_{i=1}^{n}a_i$ 就可以求出 $a_i$ 了。

同样，根据上面的式子，我们可以推导出：

$\sum\limits_{i=1}^{n}(b_i+c_i)$

$={\sum\limits_{i=1}^{n}a_i+n \times a_1}+{\sum\limits_{i=1}^{n}a_i+n \times a_2}+\dots+{\sum\limits_{i=1}^{n}a_i+n \times a_n}$

$={n \times \sum\limits_{i=1}^{n}a_i+n \times \sum\limits_{i=1}^{n}a_i}$

$=2 \times n \times \sum\limits_{i=1}^{n}a_i$

$\therefore \sum\limits_{i=1}^{n}a_i=\sum\limits_{i=1}^{n}(b_i+c_i) \div (2 \times n)$

这样的话我们就可以求出 $a$ 序列了。

但我们还剩下一步：判断 $a$ 序列是否真的合法。

如果直接判断的话时间复杂度是 $O(n^2)$ 的，显然不可行。

定义 $sum_i$ 表示 $a$ 序列中 共有几个数满足第 $i$ 位为 $1$。

~~别问我为什么要打空格，问就是奇怪的敏感词屏蔽~~

以 $b$ 序列来举例：

定义一个计数器 $ans$，

考虑每一位的贡献。若当前枚举到的数是第 $j$ 个数，且第 $i$ 位为 $1$，$ans$ 加上 $2^i \times sum_i$。

其中 $2^i$ 表示第 $i$ 位的位权，$sum_i$ 表示 $1$ 的出现次数。

最后判断 $ans$ 是否等于 $b_j$ 即可。

对于 $c$ 序列，$ans$ 加上 $2^i \times (n-sum_i)$，其余同理。

除此之外，还需判断在计算 $a$ 序列时是否可以整除。如果不能，直接判断无解。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n=read(),b[1000005],c[1000005],s,a[1000005],sum[1000005];
int hp(int x){
	int ans=0;
	while(x)
		ans++,x/=2;
	return ans;
}
signed main(){
	for(int i=1; i<=n; i++)
		b[i]=read(),s+=b[i];
	for(int i=1; i<=n; i++)
		c[i]=read(),s+=c[i];
	if(s%(2*n)){
		cout<<-1;
		return 0;
	}//判断无解
	s/=2;
	s/=n;
	for(int i=1; i<=n; i++){
		a[i]=b[i]+c[i]-s;
		if(a[i]%n){
			cout<<-1;
			return 0;
		}//判断无解
		a[i]/=n;
		for(int j=a[i]; j; j-=(j&-j))
			sum[hp(j&-j)-1]++;//计数器增加
	}
	for(int i=1; i<=n; i++){
		int ans=0;
		for(int j=0; j<63; j++)
			if(a[i]&(1ll<<j))
				ans+=sum[j]*(1ll<<j);
		if(ans!=b[i]){
			cout<<-1;
			return 0;
		}
		ans=s;
		for(int j=0; j<63; j++)
			if(a[i]&(1ll<<j))
				ans+=(n-sum[j])*(1ll<<j);
		if(ans!=c[i]){
			cout<<-1;
			return 0;
		}
	}
	for(int i=1; i<=n; i++)
		cout<<a[i]<<' ';
    return 0;
}
```

---

## 作者：stOqwqOrz (赞：1)

[LG CF734F](luogu.com.cn/problem/CF734F)

[CF734F](https://codeforces.com/problemset/problem/734/F)

**简要题意**

- 给定 $b_j=\sum_{i=1}^n (a_i\& a_j),c_j=\sum_{i=1}^n (a_i|a_j)$，构造出一组 $a$ 满足上述条件，或者判断无解

- $n\leq 2\times 10^5$，$V\leq 10^9$，$2s$，$250\operatorname{MB}$

**题解**

- 首先将这种位运算转换为 $+,-$ 运算，$a\&b + a|b =a+b$，那么 $b_i+c_i=Sum+na_i$，$\sum b_i+\sum c_i=2nSum$，那么就可以构造出一组解 $a$

- 然后反过来检查 $a$ 是否满足条件，用 $b$ 检查就够了。具体的因为是 $\&$ 运算，所以提前预处理出每一位有多少个 $a_i$ 会有贡献，对于每个 $a_i$ 的每一位算出贡献加起来，最后判断是否等于 $b_i$ 即可

- 时间复杂度为 $O(n\log V)$，空间复杂度为 $O(n)$

**参考代码**

```cpp
const int N=2e5+10;
int n,a[N],b[N],c[N],d[31];

signed main(){
//start at 17:05
//end at 17:08
#ifdef LOCAL
    Fin("1");
#endif
    n=read();int sum=0;
    FOR(i,1,n) b[i]=read(),sum+=b[i];
    FOR(i,1,n) c[i]=read(),sum+=c[i];
    sum/=(2*n);
    FOR(i,1,n) a[i]=(b[i]+c[i]-sum)/n;
    FOR(i,1,n) {
        FOR(j,0,30) {
            if(a[i]&(1<<j)) ++d[j];
        }
    }
    FOR(i,1,n) {
        int res=0;
        FOR(j,0,30) {
            if(a[i]&(1<<j)) {
                res+=d[j]*(1<<j);
            }
        }if(res!=b[i]) {puts("-1");return 0;}
    }FOR(i,1,n) cout<<a[i]<<' ';cout<<endl;
#ifdef LOCAL        
    fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
    return 0;
}
```

---

## 作者：violin_wyl (赞：0)

## CodeForces734F



#### 解析：

题目看起来非常复杂，想要直接构造明显不行，我们考虑怎么消掉一些东西。

这里就有一个小技巧了 $a \& b+a|b=a+b$​​ ~~疯狂暗示~~。

我们求一下 $b_i+c_i$​​

则有：
$$
b_i+c_i=(a_1\&a_i+a_1|a_i+a_2\&a_i+a_2|a_i+\ldots+a_n\&a_i+a_n\&a_i)\\
b_i+c_i=(a_1+a_i+a_2+a_i+\ldots+a_n+a_i)\\
b_i+c_i=a_i\times n+\sum_{i=1}^{n}a_i
$$
所以 $\sum_{i = 1}^{n} b_i+c_i$ ：
$$
\sum_{i = 1}^{n}b_i+c_i=\sum_{i=1}^{n}a_i\times n+(\sum_{i=1}^{n}a_i)\times n\\
\sum_{i = 1}^{n}b_i+c_i=2\times n\times\sum_{i=1}^{n}a_i
$$
也就是 $\sum_{i = 1}^{n} b_i+c_i$ 是我们构造出来的 $a$ 数组的和的 $2n$ 倍。

其中 $\sum_{i = 1}^{n} b_i+c_i$​ 是我们已知的，则 $\frac{\sum_{i = 1}^{n} b_i+c_i}{2\times n}$​ 即为 $\sum_{i=1}^{n}a_i$​​

接下来我们怎么做，考虑用 $(b[i]+c[i])-(b[i-1]+c[i-1])$​
$$
(b[i]+c[i])-(b[i-1]+c[i-1])=\sum_{i=1}^{n}a_i+a_i\times n-\sum_{i=1}^{n}a_i+a_{i-1}\times n\\
(b[i]+c[i])-(b[i-1]+c[i-1])=a_i\times n-a_{i-1}\times n\\
(b[i]+c[i])-(b[i-1]+c[i-1])=(a_i-a_{i-1})\times n
$$
我们做一个差分，则 $\frac{(b[i]+c[i])-(b[i-1]+c[i-1])}{n}$ 即为 $(a_i-a_{i-1})$​。

有了 $a$ 数组的差分数组，和 $a$ 数组的和，还不会构造吗？

简单说一下吧，对差分数组求前缀和，构造出来了一个首位为 $0$​​​ 的 $a$​​​ 数组，求一下现在的 $sum$​​​ 比 $\frac{\sum_{i = 1}^{n} b_i+c_i}{2\times n}$​​​​​​ 差多少（前提 $n|(\frac{\sum_{i = 1}^{n} b_i+c_i}{2\times n} - sum)$​​​​​），然后加一下。

你以为这就完了？你构造出来的数组真的是答案吗？他能和 $b,c$ 匹配吗？

很明显，我们需要用构造的数组反推 $b,c$ ，推出来的必须完全一样，但反推是 $O(n^2)$ 的 ~~好烦~~，还需要优化。

由于与运算和或运算在二进制下每个位置互不影响，所以我们对 $\log(n)$ 个位置分别考虑，记 $g_k$ 表示 $\sum_{i=1}^{n} a_i\&(1<<k)$，即在二进制下的第 $k$ 位对于每一个 $a_i$ 有多少个1，则易得：（自行分析）
$$
b_{i,k}=\begin{cases}
0& a_{i,k}=0\\
g_k& a_{i,k}=1
\end{cases}
$$

$$
c_{i,k}=\begin{cases}
g_k& a_{i,k}=0\\
n& a_{i,k}=1
\end{cases}
$$

然后求和就好了。

## code

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
const int INF = INT_MAX;
inline int read ( )
{
    int x = 0, f = 1;
    char ch = getchar ( );
    while (ch < '0' || ch > '9') {if (ch == '-') f = - 1; ch = getchar ( );}
    while (ch >= '0' && ch <='9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar ( );}
    return x * f;
}
int n;
int b[N], c[N], sum1, sum2;
int a[N], g[N], A[N][100], B[N], C[N];
bool check()
{
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= 31; j++)
            A[i][j] = (a[i] & (1 << j)) ? 1 : 0, g[j] += A[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= 31; j++)
        {
            int x = A[i][j] ? g[j] : 0;
            int y = A[i][j] ? n : g[j];
            B[i] += x << j; C[i] += y << j;
        }
    for (int i = 1; i <= n; i++) if (B[i] != b[i] || C[i] != c[i]) return false;
    return true;
}
signed main()
{
    n = read ( );
    for (int i = 1; i <= n; i++) b[i] = read ( ), sum1 += b[i];
    for (int i = 1; i <= n; i++)
    {
        c[i] = read ( ); sum1 += c[i];
        if (c[i] < b[i]) {printf ("-1\n"); return 0;}
    }
    if (__gcd(sum1, (2 * n)) != 2 * n) {printf ("-1\n"); return 0;}
    sum1 /= (2 * n);
    for (int i = 2; i <= n; i++)
    {
        int t = b[i] + c[i] - (b[i - 1] + c[i - 1]);
        if (__gcd(t, n) != n) {printf ("-1\n"); return 0;}
        a[i] = t / n;
    }
    for (int i = 1; i <= n; i++) a[i] = a[i] + a[i - 1], sum2 += a[i];
    int f = abs (sum2 - sum1);
    if (__gcd (f, n) != n) {printf ("-1\n"); return 0;}
    for (int i = 1; i <= n; i++) a[i] += (f / n);
    if (check ()) for (int i = 1; i <= n; i++) printf ("%lld ", a[i]);
    else {printf ("-1\n"); return 0;}
    return 0;
}
```

---

## 作者：1saunoya (赞：0)

先考虑反过来怎么做。

算一下每一位的贡献，大概是这样。

```cpp
	rep(i,1,n)per(j,30,0)if(a[i]>>j&1)++cnt[j];
	rep(i,1,n){
		ll tmp=0;
		rep(j,0,30)if(a[i]>>j&1)tmp+=(1ll<<j)*cnt[j];
		if(b[i]!=tmp)ed();
		tmp=0;
		rep(j,0,30)if(a[i]>>j&1)tmp+=(1ll<<j)*n;else tmp+=(1ll<<j)*cnt[j];
		if(c[i]!=tmp)ed();
	}
```


考虑构造。

$(x | y) + (x \& y) == x+y$。

所以直接搞就完事了。

$2 \times n \times \sum a =  \sum b+ c$。

因为 $b_i + c_i = \sum (a_i+a_j) = a_i \times n + \sum a$

$b_i + c_i - \sum a = a_i \times n$。

然后判定一下就做完了。

```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
using namespace std;
using ll=long long;
void cmax(int&x,const int&y){x=x>y?x:y;}
void cmin(int&x,const int&y){x=x<y?x:y;}
int n;
const int N=2e5+1;
int a[N],b[N],c[N];
void ed(){cout<<-1<<'\n';exit(0);}
int cnt[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>n;
	rep(i,1,n)cin>>b[i];
	rep(i,1,n)cin>>c[i];
	rep(i,1,n)if(b[i]>c[i])ed();
	//a*2n=b+c
	ll sum=0;
	rep(i,1,n)sum+=b[i],sum+=c[i];
	if(sum%(n*2))ed();
	else sum/=n*2;
	rep(i,1,n){
		a[i]=b[i]+c[i]-sum;
		if(a[i]%n)ed();
		else a[i]/=n;
	}
	rep(i,1,n)per(j,30,0)if(a[i]>>j&1)++cnt[j];
	rep(i,1,n){
		ll tmp=0;
		rep(j,0,30)if(a[i]>>j&1)tmp+=(1ll<<j)*cnt[j];
		if(b[i]!=tmp)ed();
		tmp=0;
		rep(j,0,30)if(a[i]>>j&1)tmp+=(1ll<<j)*n;else tmp+=(1ll<<j)*cnt[j];
		if(c[i]!=tmp)ed();
	}
	rep(i,1,n)cout<<a[i]<<' ';
	return 0;
}
```

---

