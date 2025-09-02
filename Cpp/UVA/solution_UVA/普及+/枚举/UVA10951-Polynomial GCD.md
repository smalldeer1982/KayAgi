# Polynomial GCD

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1892

[PDF](https://uva.onlinejudge.org/external/109/p10951.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10951/27f28d739e35835743ed24591d9545837d82f420.png)

## 样例 #1

### 输入

```
3
3 2 2 1 1
4 1 0 2 2 2
0```

### 输出

```
Case 1: 2 1 2 1```

# 题解

## 作者：Karry5307 (赞：2)

### 题意

多项式在$\bmod\ m$求$\texttt{gcd}$，不讲。

$\texttt{Data Range}:m\leq 1000$且为奇素数，多项式次数$\leq 100$

### 题解

$m$很明显可以出到$998244353$。

既然要你求多项式$\texttt{gcd}$，那么按照原来欧几里得的做法，问题的实质就是要对多项式取模。有三种方法。

第一种，暴力模拟大除法，每一次都除掉一位就可以啦qwq

第二种，既然是任意模数的话，次数也不是很大，所以把$\texttt{NTT}$改成暴力卷积即可（可是代码长而且常数大）。

最后一种，如果你像$\texttt{N}\color{red}\texttt{aCly\_Fish}$一样是个多项式兼卡常神仙，那么你可以写任意模数$\texttt{NTT}$。

但是有坑点：

一，**输入的多项式和你给出的答案次数是从高到低的！**

二，**你的答案中多项式最高次项必须为$1$！**

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=151;
ll mods,pos,test;
ll f[MAXN][MAXN],fd[MAXN];
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
inline ll qpow(ll base,ll exponent,ll mod)
{
	ll res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=(li)res*base%mod;
		}
		base=(li)base*base%mod,exponent>>=1;
	}
	return res;
}
inline void mod(ll fd,ll gd,ll &rd,ll *f,ll *g,ll *r)
{
	if(fd<gd)
	{
		rd=fd;
		for(register int i=0;i<rd;i++)
		{
			r[i]=f[i];
		}
		return;
	}
	ll align=fd,inv=qpow(g[gd-1],mods-2,mods),num;
	static ll tmp[MAXN];
	for(register int i=0;i<fd;i++)
	{
		tmp[i]=f[i];
	}
	while(align>=gd)
	{
		if(!tmp[align-1])
		{
			align--;
			continue;
		}
		num=(li)tmp[align-1]*inv%mods;
		for(register int i=align-1,j=gd-1;j>=0;i--,j--)
		{
			tmp[i]=(tmp[i]-(li)num*g[j]%mods+mods)%mods;
		}
		align--;
	}
	rd=gd-1;
	while(rd&&!tmp[rd-1])
	{
		rd--;
	}
	for(register int i=0;i<rd;i++)
	{
		r[i]=tmp[i];
	}
}
inline ll gcd(ll cur)
{
	if(fd[cur+1]==0)
	{
		return cur;
	}
	else
	{
		mod(fd[cur],fd[cur+1],fd[cur+2],f[cur],f[cur+1],f[cur+2]);
		return gcd(cur+1);
	}
}
inline void solve()
{
	fd[0]=read()+1;
	for(register int i=0;i<fd[0];i++)
	{
		f[0][fd[0]-1-i]=read();
	}
	fd[1]=read()+1;
	for(register int i=0;i<fd[1];i++)
	{
		f[1][fd[1]-1-i]=read();
	}
	pos=gcd(0),printf("Case %d: %d",++test,fd[pos]-1);
	ll inv=qpow(f[pos][fd[pos]-1],mods-2,mods);
	for(register int i=0;i<fd[pos];i++)
	{
		printf(" %d",(li)f[pos][fd[pos]-1-i]*inv%mods);
	}
	puts("");
}
int main()
{
	while(mods=read())
	{
		solve();
		memset(f,0,sizeof(f)),memset(fd,0,sizeof(fd));
	}
}
```

---

## 作者：ganpig (赞：1)

求 GCD，辗转相除即可。

考虑每次从次数较高的多项式 $A$ 中减去次数较低的多项式 $B$ 的 $k$ 倍来消去最高次项，容易求得 $k$ 即为 $B$ 的最高次项的逆元与 $A$ 的最高次项的乘积。

**注意答案的最高次项需要为 $1$。**

### $\text{Code}$

```cpp
#include <bits/stdc++.h>

int T = 0;

int main() {
    int p;
    std::cin >> p;
    if (!p)
        return 0;

    std::vector<long long> inv(p);
    inv[1] = 1;
    for (int i = 2; i < p; i++)
        inv[i] = (p - p / i) * inv[p % i] % p;

    int _;
    std::cin >> _;
    std::deque<int> a(_ + 1);
    for (int &x : a)
        std::cin >> x;
    std::cin >> _;
    std::deque<int> b(_ + 1);
    for (int &x : b)
        std::cin >> x;

    while (a[0] != 0) {
        if (a.size() < b.size())
            a.swap(b);
        long long k = inv[b[0]] * a[0] % p;
        for (int i = 0; i < b.size(); i++)
            a[i] = (a[i] - k * b[i] % p + p) % p;
        while (!a.front() && a.size() >= 2)
            a.pop_front();
    }

    printf("Case %d: %d", ++T, b.size() - 1);
    long long k = inv[b[0]];
    for (int x : b)
        printf(" %d", x * k % p);
    putchar('\n');

    return main();
}
```

---

