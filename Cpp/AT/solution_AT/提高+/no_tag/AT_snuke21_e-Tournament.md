# Tournament

## 题目描述

[problemUrl]: https://atcoder.jp/contests/snuke21/tasks/snuke21_e



# 题解

## 作者：songhongyi (赞：1)

![](https://s11.ax1x.com/2024/02/25/pFams0I.png)

众所周知，竞赛图在 SCC 缩点后会形成一条拓扑链，表现为不同 SCC 间的全部是从拓扑序小指向拓扑序大。

假设一个竞赛图的 SCC 大小分别是 $a_1 \cdots a_k$，我们在 $a_1,a_1+a_2,a_1+a_2+a_3 \cdots$ 的位置统计答案。

假设我们在某个位置 $i$，这要求我们选出两部分，前 $i$ 个点之间任意，后 $n-i$ 个点之间任意，然后前 $i$ 个点和后 $n-i$ 个点全部是前连向后。

因而，总答案是：
$$
\sum_{i=1}^n\binom n i2^{\binom i 2+\binom {n-i}2}
$$
不难在 $O(n \log n)$ 的复杂度内完成。

---

## 作者：Anoshag_Ruwan (赞：0)

有趣的简单题。

我们知道竞赛图缩点后相当于一个链状的偏序集。考虑 $k$ 个强连通分量的竞赛图，将其缩点再按拓扑序排序后，对于每个 $i<k$，都可以将其划分为 $\{$ 前 $i$ 个强连通分量 $\}$ 和 $\{$ 后 $k-i$ 个强连通分量 $\}$ 两个点集，所有两端在不同点集中的边，其方向只能固定由前者连向后者。于是一个竞赛图的强连通分量数，就相当于找多少个不同的**非空**点集，满足不存在从其补集连向自己的边（它和补集内部的边则不受限制）。枚举每个非空子集产生的贡献即可，$ans=\sum\limits_{i>0}\tbinom{n}{i}2^{f_i}$，其中 $f_i=\tbinom{i}{2}+\tbinom{n-i}{2}$。

```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long frc[10000011],inv[10000011];
const int p=1e9+7;
inline long long add(long long x,long long y){return x+y>=p?x+y-p:x+y;}
inline long long ksm(long long x,long long y){
	long long k=1,l=x;
	while(y){if(y&1)k=k*l%p;l=l*l%p,y>>=1;}
	return k;
}
int main()
{
	long long ans=0,i,j,k,m,n;scanf("%lld",&n); 
	for(i=frc[0]=1;i<=n;i++)frc[i]=frc[i-1]*i%p;
	for(i=n-1,inv[n]=ksm(frc[n],p-2);i>=0;i--)inv[i]=inv[i+1]*(i+1)%p;
	for(i=1;i<=n;i++){
		k=((i*(i-1)>>1)%(p-1)+((n-i)*(n-i-1)>>1)%(p-1))%(p-1);
		ans=add(ans,ksm(2,k)*inv[i]%p*inv[n-i]%p);
	}ans=ans*frc[n]%p;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：masterhuang (赞：0)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17773631.html)，第 $7$ 篇。

前置知识：[竞赛图强联通分量性质](https://www.cnblogs.com/HaHeHyt/p/17788060.html)，只要用到本文的结论 $1$。

---
竞赛图强连通缩点后的 $\texttt{DAG}$ 呈链状, 前面的所有点向后面的所有点连边。
  
通常性的，我们考虑应考虑前 $i$ 个强连通分量，于是我们对所有图缩点后对这样的划线计数：

![](https://dl.img.timecdn.cn/2023/12/05/1086046-20180515205529415-1357982282.png)
  
假设某条线前面有 $1\le i\le n$ 个**点**（注意不是强联通分量），后面有 $n-i$ 个点，则这个竞赛图可以拆成：
  
- 前 $i$ 个点组成的竞赛子图
  
- 后 $n-i$ 个点组成的竞赛子图
  
- 所有前 $i$ 个点向所有后 $n-i$ 个点连的一条有向边
  
于是我们要把 $n$ 个点划分成大小为 $i,n-i$ 两个集合，两个集合内的点要以某种方式连成竞赛图，而后按照第三个条件再连边。
  
记 $s_i=\binom{i}{2}$，则方案数为 $\dbinom{n}{i}2^{s_i}2^{s_{n-i}}$，于是答案为 $\sum\limits_{i=1}^n \dbinom{n}{i}2^{s_i}2^{s_{n-i}}$。
  
复杂度 $O(n\log n)\sim O(n)$ 不等，取决于实现的精细（我代码是带 $\log$ 的）。
  
---
  
此题很难低于 $O(n)$ 的原因：
  
由于 $s_is_j+ij=s_{i+j}$，于是 $2^{s_i}2^{s_{n-i}}=2^{n-i(n-i)}=2^{n^2-ni-i^2}$。此时幂次出现了平方而且要求和，是经典不太可做问题。

代码：
  
```cpp
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=1e5+5,mod=1e9+7;
int n,ans,I[N];
inline int md(int x){return x>=mod?x-mod:x;}
inline int ksm(int x,int p){int s=1;for(;p;(p&1)&&(s=1ll*s*x%mod),x=1ll*x*x%mod,p>>=1);return s;}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n;
	I[1]=1;for(int i=2;i<=n;i++) I[i]=mod-1ll*I[mod%i]*(mod/i)%mod;
	for(int i=1,s=n;i<=n;s=1ll*s*(n-i)%mod*I[i+1]%mod,i++) ans=(ans+1ll*s*ksm(2,(1ll*i*(i-1)+1ll*(n-i)*(n-i-1))/2%(mod-1)))%mod;
	return cout<<ans,0;
}
```

---

