# [SNCPC2019] To the Park

## 题目描述

宝宝和他的 $(n-1)$ 个同学要去公园。为了方便，他们的老师梦想格子将学生从 1 到 $n$ 编号，并决定将学生分成一些小组，每组恰好由两个学生组成。

由于某种原因，梦想格子要求同组的两个学生的编号必须有一个大于 1 的公约数。注意，每个学生最多只能属于一个小组，并且不需要每个学生都属于一个小组。

请帮助梦想格子组成尽可能多的小组。

## 样例 #1

### 输入

```
3
1
4
6
```

### 输出

```
0
1 2 4
2 2 4 3 6
```

# 题解

## 作者：SDLTF_凌亭风 (赞：2)

来自某不愿意透露姓名的队友。

---
很好玩的构造。

首先考虑答案的上界，很明显 $1$ 是不能进任何一个组的，其次是大于 $\left\lfloor\frac{n}{2}\right\rfloor$ 的素数，然后剩下两两配对。（这个性质看样例也能看出来吧）

然后考虑构造符合这个上界的答案。由于偶数和偶数之间可以相互配对，所以我们可以先考虑奇数，而奇数中奇素数是比较特别的。对于小于 $\left\lfloor\frac{n}{2}\right\rfloor$ 的所有奇素数 $p$ 从大到小考虑，把 $1\sim n$ 中所有没被匹配过的 $p$ 的倍数都拿出来。如果这些数是偶数个那么两两匹配，否则把 $2p$ 拿出来剩下的两两匹配。（因为 $2p$ 必定是个小于 $n$ 的偶数）

这样我们可以保证所有大于 $1$ 的奇数都被匹配掉了（因为一个大于 $1$ 的奇数必定被最大的素因子那个过程匹配掉），剩下的偶数两两匹配就好了。

一个坑点是线性筛不能只筛到 $10^5$，否则会出点小问题。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=1e5+51;
vector<pair<ll,ll> >v;
vector<ll>v2;
ll test,n,ptot,x,y,res;
ll np[MAXN],prime[MAXN],c[MAXN];
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
inline void sieve(ll limit)
{
	np[1]=1;
	for(register int i=2;i<=limit;i++)
	{
		if(!np[i])
		{
			prime[++ptot]=i;
		}
		for(register int j=1;i*prime[j]<=limit;j++)
		{
			np[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				break;
			}
		}
	}
}
inline void solve()
{
	n=read();
	if(n<=3)
	{
		return (void)puts("0");
	}
	v.clear(),v2.clear(),c[1]=1;
	for(register int i=2;i<=n;i++)
	{
		c[i]=0;
	}
	for(register int i=1;prime[i]<=n;i++)
	{
		prime[i]>(n>>1)?(c[prime[i]]=1):1;
	}
	for(register int i=(n>>1);i>=3;i--)
	{
		if(np[i])
		{
			continue;
		}
		v2.push_back(i);
		for(register int j=3;j*i<=n;j++)
		{
			!c[j*i]?(void)v2.push_back(j*i):(void)1;
		}
		v2.size()&1?(void)v2.push_back(i<<1):(void)1;
		for(register int j=0;j<v2.size()-1;j+=2)
		{
			x=v2[j],y=v2[j+1],v.push_back(make_pair(x,y)),c[x]=c[y]=1;
		}
		v2.clear();
	}
	for(register int i=1;i<=n;i++)
	{
		!c[i]?(void)v2.push_back(i):(void)1;
	}
	for(register int i=0;i<v2.size()-1;i+=2)
	{
		x=v2[i],y=v2[i+1],v.push_back(make_pair(x,y)),c[x]=c[y]=1;
	}
	printf("%d ",res=v.size());
	for(register int i=0;i<res;i++)
	{
		printf("%d %d",v[i].first,v[i].second);
		i!=res-1?putchar(' '):1;
	}
	puts("");
}
int main()
{
	test=read(),sieve(100030);
	for(register int i=1;i<=test;i++)
	{
		solve();
	}
}
```

---

