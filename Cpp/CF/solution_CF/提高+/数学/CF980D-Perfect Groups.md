# Perfect Groups

## 题目描述

SaMer has written the greatest test case of all time for one of his problems. For a given array of integers, the problem asks to find the minimum number of groups the array can be divided into, such that the product of any pair of integers in the same group is a perfect square.

Each integer must be in exactly one group. However, integers in a group do not necessarily have to be contiguous in the array.

SaMer wishes to create more cases from the test case he already has. His test case has an array $ A $ of $ n $ integers, and he needs to find the number of contiguous subarrays of $ A $ that have an answer to the problem equal to $ k $ for each integer $ k $ between $ 1 $ and $ n $ (inclusive).

## 样例 #1

### 输入

```
2
5 5
```

### 输出

```
3 0
```

## 样例 #2

### 输入

```
5
5 -4 2 1 8
```

### 输出

```
5 5 3 2 0
```

## 样例 #3

### 输入

```
1
0
```

### 输出

```
1
```

# 题解

## 作者：_Life_ (赞：17)

### 结论：
若 $ab=n^2,bc=m^2$  ,则 $ac=k^2$ 

### 证明：
根据唯一分解定理
$$a=p_1^{a_1}p_2^{a_2}p_3^{a_3}\cdots p_k^{a_k}$$
$$b=p_1^{b_1}p_2^{b_2}p_3^{b_3}\cdots p_k^{b_k}$$
$$c=p_1^{c_1}p_2^{c_2}p_3^{c_3}\cdots p_k^{c_k}$$

因为 $ab$ 为平方数
$$a_1+b_1\equiv 0 \pmod 2$$
$$a_2+b_2\equiv 0 \pmod 2$$
$$\cdots$$
$$a_k+b_k\equiv 0 \pmod 2$$

又因为 $bc$ 为平方数
$$c_1+b_1\equiv 0 \pmod 2$$
$$c_2+b_2\equiv 0 \pmod 2$$
$$\cdots$$
$$c_k+b_k\equiv 0 \pmod 2$$

得到
$$a_1+c_1\equiv 0 \pmod 2$$
$$a_2+c_2\equiv 0 \pmod 2$$
$$\cdots$$
$$a_k+c_k\equiv 0 \pmod 2$$
即 $ac$ 为平方数 原命题得证

### 题意：
将一个串划分为多个子集（不要求连续），要求同一子集内两任意元素的积为平方数

定义一个串的答案为所需的最少子集个数

一个长度为 $n$ 的串有 $\frac{n(n+1)}{2}$ 个**非空子串**，求答案为 $1,2,3,\cdots ,n$ 的非空子串个数

### 题解:
因为上面的结论，所以把 $a_i \times a_j$ 为平方数的用并查集合并

然后求出每个区间内的集合数即可 总时间复杂度 $O(n^2)$

TIPs:
1. $-10^8 \leq a_i \leq 10^8$，两个相乘会爆`int`
2. 注意 $a_i=0$ 的情况

### 代码：
```cpp
//CF980D
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define int long long
int n,x[5001],fa[5001],ans[5001],num[5001];
int find(int x)
{
	if(fa[x]==x)
		return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
	fa[find(x)]=find(y);
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&x[i]),fa[i]=i;
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
			if(x[i]*x[j]>0)
			{
				int tmp=(int)sqrt(x[i]*x[j]);
				if(tmp*tmp==x[i]*x[j])
					merge(i,j);
			}
	for(int i=1;i<=n;i++)
	{
		int tot=0;
		memset(num,0,sizeof(num));
		for(int j=i;j<=n;j++)
			if(x[j]==0)
				ans[max(1ll,tot)]++;
			else
			{
				if(!num[find(j)])
					num[find(j)]=1,tot++;
				ans[tot]++;
			}
	}
	for(int i=1;i<=n;i++)
		printf("%lld ",ans[i]);
}
```

---

## 作者：lenlen (赞：12)

### Problem

题目大意： 给定一个序列 $a$，定义一个序列 $b$ 的价值是将 $b$ 分成最少几组，满足每一组里面两两相乘都是平方数的组数。求 $a$ 的所有子序列的价值之和。

数据范围： $n \leq 5000$。

### Solution

这一个题需要证明一个引理：若 $ab=x^2,bc=y^2$，则 $ac=z^2(x,y,z \in \mathbb N)$。这个引理在大佬 $@_Life_$ 的题解里面已经详细证明，就不赘述了。

然后我们可以把所有相乘为平方数的数全部用并查集维护起来，然后枚举每一个子序列 $[a_l,a_r]$，计算他的价值就好。

但是这样时间复杂度是 $O(n^3)$ 的，所以我们需要进一步优化。注意到当我们固定 $l$ 后，$r$ 每增加 $1$ 都只会加入一个数进去，判断一下这个数能不能放进现有的组里面就可以了，时间复杂度 $O(n^2)$。

注意几个点：

1. sqrt 中若是负数会超时（奇怪），我使用 $k=\sqrt {ab}$，再判断 $k^2$ 等不等于 $ab$ 来判断平方数的，这里我卡了好久，特别是没想到会是这里超时。

2. 特判一下 $0$ 的存在。

3. $-10^8 \leq a_i \leq 10^8$，所以 $a_i \times a_j$ 会超 int，判断的时候记得乘 $1ll$。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=7232;
int n,a[N];
int fa[N],vis[N],sum,ans[N];
int getfa(int x)
{
    if(fa[fa[x]]==fa[x]) return fa[x];
    if(x==fa[x]) return x;
    return fa[x]=getfa(fa[x]);
}
const int Mt=1e5;
inline char getc()
{
	static char buf[Mt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mt,stdin),p1==p2)?EOF:*p1++;
}
inline int read()//为了解决超时。。。。其实并不需要
{
	int r=0,f=1;char c=getc();
	while(!isdigit(c)){if(c=='-')f=-1;c=getc();}
	while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getc();
	return r*f;
}
int mx(int x,int y){return x>y?x:y;}
int main()
{
	n=read();
    for(int i=1;i<=n;++i) fa[i]=i,a[i]=read();
    for(int i=1;i<=n;++i)
    {
        for(int j=i+1;j<=n;++j)
        {
            if(1ll*a[j]*a[i]>0) 
            {
                int k=sqrt(1ll*a[i]*a[j]);//临时转成long long，一开始开也可以，我为了节省空间
                if(1ll*k*k==1ll*a[i]*a[j]) fa[(fa[fa[i]]==fa[i]?fa[i]:getfa(fa[i]))]=(fa[fa[j]]==fa[j]?fa[j]:getfa(fa[j]));
            } 
        }
    }
    for(int l=1;l<=n;++l)
    {
        sum=0;
        for(int r=l;r<=n;++r)
        {
            if(a[r]==0) ++ans[mx(1,sum)];//特判0
            else
            {
                int fr=(fa[fa[r]]==fa[r]?fa[r]:getfa(fa[r]));
                if(vis[fr]!=l) 
                {
                    vis[fr]=l;
                    ++sum;
                }
                ++ans[sum];
            }
        }
    }
    for(int i=1;i<=n;++i) printf("%d ",ans[i]);
}


```


---

## 作者：inexistent (赞：5)

请关注我的[博客](https://www.cnblogs.com/qixingzhi/p/9291443.html)以查看代码，并获得更好的效果！（逃

出处： Codeforces

主要算法：数学

难度：4.7

思路分析：
       
   题目大意：先抛出了一个问题——“已知一个序列，将此序列中的元素划分成几组（不需要连续）使得每一组中的任意两个数的乘积都是完全平方数。特殊的，一个数可以为一组。先要求最少分几组。”在这个问题的基础上，给出一个长度为n的序列，该序列有\(\frac{n(n+1)}{2}\)个子序列，求每个子序列对于上面这个问题最少划分几次。并分别统计最少划分k次的子序列有几个。

　　题目由于是英文的，好长时间没读懂，而且还读错。注意he needs to find the number of contiguous subarrays这句，是连续的子序列，所以子序列仅仅只有\(\frac{n(n+1)}{2}\)个。

　　首先我们能够发现，对于两个数\(a,b\)，如果a或b本身包含了某一个完全平方数作为因数，那么这个因数的存在是完全没有意义的。例如20和18，分别含有完全平方因子4和9，我们让着两个数分别除去它们的完全平方因子，得到5和2。其实这对结果完全没有影响，如果5*2不是完全平方数，那么20*18也一定不是完全平方数。因为本身4和9就作为整体被提了出来，有他们没他们，剩下的数依然需要找到完全平方。因此第一步预处理，将所有数都出去它们的所有完全平方因子。

　　除去完全平方因子有什么用？当两个数已经被除去完全平方因子时，两个数的乘积为完全平方数，当且仅当这两个数相等。这应该很好理解，因为再也没有完全平方因子了，只有两个数相等才有可能是完全平方。所以相同的数就可以分为一组。因此我们就可以将问题转化为了，在一个序列中，有几个不同的数。

　　作为刚才这一切，我们就可以通过O(n^3)求解问题了，最外围枚举子序列长度，然后枚举起点，然后扫描。但是对于n = 5000，爆到不知哪里去了。

　　我们需要做一些优化，由于题目恶心到O(n^2 log n)都过不去，只能O(n^2)出解。

　　有两种方法，一种是离散化+桶（也挺方便的）；但我选择的是记录f数组——f[i]表示在a[i]之前最靠近a[i]的并且等于a[i]的数的位置，如果不存在这样的数，则令f[i] = -1。O(n^2)先预处理一下这个东西（友情提醒，用map只需要O(n))。然后我们就可以做了，第一层循环扫起点L，第二层循环从1~n，于是这时候我就能方便地统计不同的数的个数。如果当前的数a[i]存在f[i]，并且满足\(f[i] > L\)，这就意味着相同的数在当前起点的右边已经出现过了，也就没必要再统计一遍；否则++number。扫描到每一个点时都++ans[number]就可以了。

　　另外0怎么办？0可以放在任意一组，因为任何数乘以0都是0。所以碰到0就不能++number，那number==0的时候怎么办啊！那么当number==0时，就特殊地当number为1吧！注意，只是当它为1，并不是置成1。

代码注意点：
　　注意在将一个数的完全平方因子除掉的时候不能使用if语句，这样的话1024就会被你处理成16，然而16很明显可以继续除的（例子有很多很多）。用while是最靠谱的。

---

## 作者：honglan0301 (赞：4)

## 题目分析

其实不需要并查集或者筛质数……根据其它题解中提到的唯一分解定理，对于任意 $a,b,c∈Z^*$, 若 $ab,ac$ 均为完全平方数，则 $ac$ 也为完全平方数。

那么可以对于每个数，预处理出在它前面最近的一个能放到一组中的数。统计答案时对于每个左端点 $l$, 枚举 $r$, 每次只需要判断新加入的数是否能放到原有的组中，时间复杂度 $O(n^2)$, 可以通过本题。

注意特判 $0$。

## 代码

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int n,a[5005],ans[5005],maxl[5005],nowans;
signed main()
{
	cin>>n; for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) for(int j=i-1;j>=1;j--)
	{
		long long kk=(long long)a[i]*a[j]; if(kk<=0) continue; long long xx=sqrt(kk);
		if(xx*xx==kk) {maxl[i]=j; break;}
	}
	for(int i=1;i<=n;i++)
	{
		nowans=0;
		for(int j=i;j<=n;j++) {if(maxl[j]<i&&a[j]) {nowans++;} ans[nowans]++;}
	}
	cout<<ans[0]+ans[1]<<" "; for(int i=2;i<=n;i++) cout<<ans[i]<<" ";
}
```
加快读之后容易跑到最优解。


---

## 作者：zztqwq (赞：4)

？为什么都写的那么复杂

考虑没有 $0$ 的情况，那么一个显然的性质：若 $a\times b,b\times c$ 为完全平方数，那么 $a\times c$ 也是完全平方数。随便证一下就好了。维护一个并查集，若 $a_i\times a_j$ 为完全平方数那么就把他们塞到一个集合里，那么问题就变成了区间有多少个集合，不难写出 $\mathcal O(n^2)$ 的做法。

如果有 $0$，为了仍然满足条件，把所有 $0$ 塞到一个集合里就行了。特判一下整个区间全是 $0$ 的情况就行了。

代码就不放了吧。

---

## 作者：Y2y7m (赞：2)

看到平方数，想到其性质偶指奇约，于是想到将每个数变成：

$$a_i=p_1^{k_1}\times p_2^{k_2}\times p_3^{k_3}\times .....$$

我们将指数 $k$ 都取模 $2$ 后将所有指数弄出来组成 $01$ 串（指数为 $0$ 也要取出来）。

这样问题转化成：计算每一个区间内不同数的个数。

这显然可以 $O(n^2)$ 做。

但是这样我们需要筛出 $10^8$ 内所有质数，这样复杂度很炸。

想到在进行分解质因数的时候只需要枚举到 $\sqrt{n}$，于是我们可以筛出小于 $10^4$ 的所有质数，然后分解完后，就会剩下 $1$ 或者大于 $10^4$ 的质数，在分解的时候我们就可把小的质数先扔进 $01$ 串中的对应位置，然后将这些大的质数拿出来离散化然后重新编号再放回 $01$ 串中，这样就可以哈希了。

这样复杂度正确。

有几个细节：

1.可以先预处理出 $2$ 的次幂。

2.注意数的正负，如果是遇到负数就将这个数的哈希值变成负的。

3.特判 $0$（统计答案时）。

code：

```cpp
//
//  main.cpp
//  Perfect Groups
//
//  Created by Y2y7m on 2023/8/24.
//  Copyright © 2023年 Slip. All rights reserved.
//

#include <iostream>
#include <algorithm>
using namespace std;
#define int long long
const int maxn=5e3+10,mod=1e9+9,maxv=1e5+10;
int n;
int a[maxn],b[maxn],f[maxn];
int tmp[maxn],tc;
int prime[maxv],cnt;
int pos[maxv];
bool stat[maxv];
void init()
{
    for(int i=2;i<=1e5;i++)
    {
        if(!stat[i]) prime[++cnt]=i;
        for(int j=2;j<=cnt&&i*prime[j]<=1e5;j++)
        {
            stat[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
    for(int i=1;i<=cnt;i++)
    {
        if(prime[i]>1e4) break;
        pos[prime[i]]=i;
    }
}
bool vis[maxn];
int ans[maxn];
int power[6000010];
bool flag[maxn];
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    init();
    power[0]=1;
    for(int i=1;i<=6000000;i++) power[i]=power[i-1]*2%mod;
    for(int i=1;i<=n;i++)
    {
        if(a[i]<0) flag[i]=1;
        a[i]=abs(a[i]);
        int t=1;
        for(int j=2;j*j<=a[i];j++)
        {
            if(!stat[j])
            {
                int cnt=0;
                while(a[i]%j==0) a[i]/=j,cnt^=1;
                if(cnt==0) continue;
                t+=power[pos[j]],t%=mod;
            }
        }
        
        if(a[i]==1)
        {
            b[i]=f[i]=t;
            continue;
        }
        b[i]=f[i]=t;
        if(a[i]>1e4) tmp[++tc]=a[i];
        else
        {
            b[i]=(b[i]+power[pos[a[i]]])%mod;
            f[i]=(f[i]+power[pos[a[i]]])%mod;
        }
        
    }
    sort(tmp+1,tmp+1+tc),tc=unique(tmp+1,tmp+1+tc)-tmp-1;
    for(int i=1;i<=n;i++)
    {
        if(a[i]<=1e4) continue;
        int p=lower_bound(tmp+1,tmp+1+tc,a[i])-tmp;
        f[i]=(f[i]+power[p+10000])%mod;
        b[i]=(b[i]+power[p+10000])%mod;
    }
    for(int i=1;i<=n;i++)
    {
        if(flag[i]) b[i]=-b[i],f[i]=-f[i];
    }
    int tot=0;
    sort(b+1,b+1+n),tot=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++) f[i]=lower_bound(b+1,b+1+tot,f[i])-b;
    for(int i=1;i<=n;i++)
    {
        for(int j=i;j<=n;j++) vis[f[j]]=0;
        int c=0;
        bool flag=0;
        for(int j=i;j<=n;j++)
        {
            if(a[j]==0)
            {
                if(c==0) c++;
                ans[c]++;
                continue;
            }
            if(!flag&&i!=j)
            {
                flag=1;
                ans[c]++;
                vis[f[j]]=1;
                continue;
            }
            flag=1;
            if(!vis[f[j]]) c++;
            vis[f[j]]=1;
            ans[c]++;
        }
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
    cout<<endl;
    return 0;
}

```


---

## 作者：fanypcd (赞：2)

令一个数的**特征值**为**这个数除以它最大的平方因子的商**，手玩一下样例，比较显然的性质就能划分到同一组的数的**特征值**都相同。（如 2 的特征值是 2，8 的特征值是 2，故 2，8 可以划分到同一组）。

那么 $O(n \sqrt{V} + n^2 \log n)$ 的做法就非常的显然了，计算出每个数的**特征值**，然后 $O(n^2)$ 地模拟字串的扩展（定住开头的位置，从小到大枚举结尾），对于每次加入的数，如果之前的串中出现过相同的特征值，那么可以与之划分进同一个集合，否则需要单独为其划分一个集合。理论上**特征值**的值域是 $10^8$，但是考虑到至多只有 $10^4$ 个数，用一个 ```map``` 来模拟桶即可。

不难写出如下的代码：

```cpp
#define N 5005
int n, a[N], b[N];//b[i] 表示第 i 个元素的最大平方因子
map<int, int> cnt;
int ans[N];
signed main()
{
	read(n);
	for(int i = 1; i <= n; i++)
	{
		read(a[i]);
		b[i] = 1;
		for(int j = 2; j * j <= abs(a[i]); j++)
		{
			if(abs(a[i]) % (j * j) == 0)
			{
				b[i] = max(b[i], j * j);
			}
		}
		a[i] /= b[i];
	}
	int nowtot;
	for(int i = 1; i <= n; i++)
	{
		cnt.clear();
		nowtot = 0;
		for(int j = i; j <= n; j++)
		{
			nowtot += 1 - cnt[a[j]];
			cnt[a[j]] = 1;
			ans[nowtot]++;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		printf("%d ", ans[i]);
	}
}
```

理所当然会 T 掉。

我们贪心地看问题，对于某一个元素，在扩展的过程中，我们是不是要尝试把它和它之前的某个元素划分到同一个集合，那么显然划分给尽量靠后的位置的元素是最优的（这样更小的字串也能少划分一个）。

于是考虑记录每个位置的元素前面第一个**特征值**与之相等的位置 ```pre[i]```。

可以在求特征值的同时方便地求出 ```pre[i]```，复杂度 $O(n^2)$。

截至现在，我们嘴上 AC 了这道题。

---

但是还需要考虑 0 的情况。

发现 0 是‘万金油’类的元素，任何划分它都可以划进去，那我们可以特殊地，将当前字串内所有的 0 划在一起，如果还有非 0 的组，那么还可以与之合并。

只需要枚举字串的时候开两个变量记录从枚举的开头到当前位置是否出现了 0 / 非 0 的元素。

```cpp
for(int i = 1; i <= n; i++)
{
	read(a[i]);
	if(!a[i])
	{
		continue;
	}
	b[i] = 1;
	for(int j = 2; j * j <= abs(a[i]); j++)
	{
		if(abs(a[i]) % (j * j) == 0)
		{
			b[i] = max(b[i], j * j);
		}
	}
	a[i] /= b[i];
	for(int j = i - 1; j >= 1; j--)
	{
		if(a[j] == a[i])
		{
			pre[i] = j;
			break;
		}
	}
}
int nowtot, flag, flagzero;
for(int i = 1; i <= n; i++)
{
	nowtot = flag = flagzero = 0;
	for(int j = i; j <= n; j++)
	{
		if(!a[j])
		{
			nowtot += 1 - flagzero;//前面出现了 0 就可以划分到一起
			flagzero = 1;
		}
		else
		{
			flag = 1;
			nowtot += 1 - (pre[j] >= i);
		}
		ans[nowtot - (flagzero && flag)]++;//如果 0 和 非 0 都有出现，那么可以合并成一组，组数少 1
	}
}
for(int i = 1; i <= n; i++)
{
	printf("%d ", ans[i]);
}
```

总的复杂度 $O(n \sqrt{V} + n^2)$，完整代码就不放了。

---

## 作者：Arghariza (赞：2)

首先需要证明的是 $\forall\ a,b,c\in \mathbb{N}^+,ab=n^2,bc=m^2$，有 $ac=k^2$，其中 $n,m,k\in\mathbb{N^+}$。


应用唯一分解定理，设：

$$a=\prod\limits_{k=1}^{m_a}p_{a_k}^{q_{a_k}}$$

$$b=\prod\limits_{k=1}^{m_b}p_{b_k}^{q_{b_k}}$$

$$c=\prod\limits_{k=1}^{m_c}p_{c_k}^{q_{c_k}}$$

然后你会惊奇地发现 $\forall k, q_{a_k}+q_{b_k}\equiv q_{c_k}+q_{b_k}\equiv 0(\text{mod}\  2)$。

于是会有 $q_{a_k}+q_{c_k}\equiv 0(\text{mod}\  2)$。

于是 $\exists k\in \mathbb{N^+},ac=k^2$。

然后这些平方数就可以用**并查集**维护了，区间查询子串的时候直接暴力查，开一个桶计算答案即可。

注意要开 $long\ long$。

```cpp
int getf(int x) {
	if (pre[x] == x) return x;
	else return pre[x] = getf(pre[x]);
}

void merge(int x, int y) {
	x = getf(x);
	y = getf(y);
	if (x != y) pre[x] = y;
}

signed main() {
	n = read();
	for (int i = 1; i <= n; i++) {
		s[i] = read();
		pre[i] = i;
	}
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			int t = s[i] * s[j];
			if (t > 0 && (int)sqrt(t) * (int)sqrt(t) == t) {
				merge(i, j);
			}
		}
	}
	for (int i = 1, cnt = 0; i <= n; i++, cnt = 0) {
		memset(v, 0, sizeof(v));
		for (int j = i; j <= n; j++) {
			if (!s[j]) {
				if (cnt >= 1) ans[cnt]++;
				else ans[1]++;
			} else {
				if (!v[getf(j)]) v[getf(j)] = 1, cnt++;
				ans[cnt]++;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		write(ans[i]), putchar(' ');
	}
	return 0;
}
```

---

## 作者：龙潜月十五 (赞：2)

## 一、前言

本题是一道很妙的题，我在考场上也没做出来。这里提供一种 **并查集** 的做法。

## 二、题意

有一个长度为 $n$ 的序列，对于其每一个 **子串**（子串是 **连续** 的）定义答案为将这个子串分成若干组，使每组中的数两两乘积为平方数 **最少** 的划分组数。求出答案为 $k$ 的子串个数。

## 三、思路

首先有一个定理：若 $a\times b$ 为平方数，$b\times c$ 为平方数，则 $a\times c$ 为平方数。

**证明**：将 $a,b,c$ 分解质因数，得

$$a=p_1^{x_1}\times p_2^{x_2}\times\cdots\times p_k^{x_k}$$

$$b=p_1^{y_1}\times p_2^{y_2}\times\cdots\times p_k^{y_k}$$

$$c=p_1^{z_1}\times p_2^{z_2}\times\cdots\times p_k^{z_k}$$

因为 $a\times b$ 为平方数，所以

$$x_1+y_1\equiv 0 \ (\bmod \ 2)$$

$$\cdots$$

$$x_k+y_k\equiv 0 \ (\bmod \ 2)$$


因为 $b\times c$ 为平方数，所以

$$y_1+z_1\equiv 0 \ (\bmod \ 2)$$

$$\cdots$$

$$y_k+z_k\equiv 0 \ (\bmod \ 2)$$

因此可得

$$x_1+z_1\equiv 0 \ (\bmod \ 2)$$

$$\cdots$$

$$x_k+z_k\equiv 0 \ (\bmod \ 2)$$

因此 $a\times c$ 为平方数，定理得证。

有了这个定理之后，我们就可以将所有相乘为平方数的数通过 **并查集** 放到同一个集合中。由于我们要求的是 **最少** 划分组数，因此直接将一个集合分成一组一定是最优的。

接下来因为 $n \leq 5000$，我们可以直接 $O(n^2)$ 暴力枚举序列的每一个子串，再求出其答案，累加个数即可。

我们还需特判一下 $0$ 的情况。因为 $0$ 乘上任何一个数都是平方数，因此 $0$ 放在任何一组都可以，并不会使组数增加。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read() {
    ll sum = 0, ff = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') {
            ff = -1;
        }
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
    	sum = sum * 10 + ch - 48;
        ch = getchar();
    }
    return sum * ff;
}

void write(ll x) {
	 if(x < 0) {
		putchar('-');
		x = -x;
	 }
	 if(x > 9)
		write(x / 10);
	 putchar(x % 10 | 48);
}

const int N = 5007;
int n, fa[N], sum, ans[N];
ll a[N];
bool mp[N];

int find(int x) {
	if(x == fa[x]) 
		return x;
	return fa[x] = find(fa[x]);
}

int main() {
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	n = read();
	for(register int i = 1; i <= n; ++i) {
		fa[i] = i;
		a[i] = read();
		for(register int j = 1; j < i; ++j)
			if(a[i] * a[j] > 0)
				if((ll)sqrt(a[i] * a[j]) * (ll)sqrt(a[i] * a[j]) == a[i] * a[j])//若两数相乘为平方数 
					fa[find(i)] = find(j);//放到同一个集合里 
	}	
	
	for(register int i = 1; i <= n; ++i) {
		for(register int j = 1; j <= n; ++j)
			mp[j] = false;
		
		sum = 0;//当前子串最少分成几组 
		
		for(register int j = i; j <= n; ++j)	
			if(!a[j])//特判0 
				++ans[max(sum, 1)];
			else {
				if(!mp[fa[j]])//若该集合每分成一组 
					++sum;//组数增加 
				mp[fa[j]] = true;
				++ans[sum];
			}
	}
	
	for(register int i = 1; i <= n; ++i)
		write(ans[i]), printf(" ");
		
    return 0;
}
```


---

## 作者：charm1 (赞：2)

## 性质

本题主要用到一个性质：
$a*b=k^2,a*c=j^2(a\neq0)$，则 $b*c=n^2$

## 证明

前两式相乘得 $a^2*b*c=(k*j)^2$

移项 $b*c=( \frac{k*j}{a})^2$

把 $\frac{k*j}{a}$ 带换成 $n$ 即得 $b*c=n^2$

## 做法

直接将 $a_k*a_j=x^2$ 的 $k$ 和 $j$ 染为同色，枚举子区间即可。

## tips
前面排除了 $0$ 的情况，遇到 $0$ 忽略即可，但只有 $0$ 时答案为 $1$ 。

上代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5005;
const double eps=1e-1;
const int INF=(int)(1e9)+7;
int n,tot;
int col[maxn],a[maxn],sum[maxn];
bool vis[maxn];
inline int read(){
	int ret=0,f=1;	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
bool check(int x){
	if(x<0) return 0;
	int p=sqrt(x+eps);
	return p*p==x;
}//校验是否为完全平方数
void scan(){
	n=read();
	for(int k=1;k<=n;k++){
		int x=read();
		a[k]=x;
		if(!x)  continue;//0时特判
		for(int j=1;j<k;j++)
		if(check(x*a[j])&&a[j]){
			col[k]=col[j];
			break;
		}//染色
		if(!col[k]) col[k]=++tot;
	}
}
void solve(){
	for(int k=1;k<=n;k++){
		memset(vis,0,sizeof(vis));
		int now=0;
		for(int j=k;j<=n;j++){
			if(!vis[col[j]]&&a[j]){
				vis[col[j]]=1;
				now++;
			}
			sum[max(now,1ll)]++;//特判答案为0时改为1
		}
	}
	for(int k=1;k<=n;k++)   printf("%lld ",sum[k]);
	puts("");
}
signed main(){
	scan(); solve();
	return 1;//防抄
}
```


---

## 作者：SegTree (赞：1)

### 题意

对于一个长度为 $n$ 的序列答案定义为**最小划分的组数**以使得每个组中的数两两乘积为平方数。

对于所有 $k$ 求答案为 $k$ 的子区间 $[l,r]$ 的数量。

### 题解

和其它题解做法都不一样（？）。

如果两个数乘在一起是平方数，则需要满足：

+ 正负号相同。

+ 每个质数的次方奇偶性相同。即，若 $n=p_1^{b_1}\cdots p_k^{b_k},m=p_1^{c_1}\cdots p_k^{c_k}$，则需要对于 $i\in[1,k],b_i\bmod 2=c_i\bmod 2$。

不难判断每个质数的次方奇偶性相当于把 $1$ 到 $10^8$ 所有质数在分解结果的出现次数模 $2$ 形成的 $01$ 串是相同的。

不难想到对每个数求出哈希值，问题转化为区间颜色数。这个 $01$ 串的长度实际上是 $10^8$ 以内质数数量，所以肯定不能模拟去计算一遍哈希值，只需要考虑这个 $01$ 串中值为 $1$ 的下标就行了。

区间颜色数暴力统计就行，因为 $n\le 5000$ 所以直接 $\mathcal{O}(n^2)$ 算一遍。注意特判 $0$ 即可。

[CF Record](https://codeforces.com/contest/980/submission/220115610)。

---

## 作者：WZKQWQ (赞：1)

### 前言

首先，$\text{DP}$ 标签是什么鬼？

其次这是一篇不用并查集的题解。

### 正文

两个**正整**数 $a,b$ 相乘等于平方数代表什么？

根据唯一分解定律每个正整数 $x$ 都可以写成一个无穷数列：$r_1,r_2,r_3,\dots,x = p_1^{r1}p_2^{r2}p_3^{r3}\dots$，其中 $p_i$ 表示从小到大第 $i$ 个质数。平方数对应的无穷数列每个值都是偶数，两个**正整**数 $a,b$ 相乘等于平方数代表他们对应的无穷数列每一位奇偶性相同。

我们定义函数 $f(x)$ 是对 $x$ 对应的无穷数列每一位模二后的数列对应的数（有点绕），那么 $a,b$ 相乘等于平方数代表 $f(a)=f(b)$。

问题来了，$f(x)$ 怎么求？两个方法：

1. 质因数分解然后暴力求，复杂度 $O(\sqrt{V})$。

2. 直接从大到小，试除每一个平方数（试除：如果可以整除就除），复杂度 $O(\sqrt{V})$。

看个人喜好，我写的二，方便。

然后用桶暴力统计相等就行，记得特判 $0$，我用的 $\text{bitset}$ 当桶。

时间复杂度 $O(n(n + \sqrt{V}))$，空间复杂度 $O(V)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5005,INF = 1e8;
int n,a[N],ans[N];
bitset<2 * INF + 1> s;
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;++i){
		scanf("%d",&a[i]);
		for(int j = 10000;j >= 2;--j) if(abs(a[i]) % (j * j) == 0) a[i] /= j * j;
	}
	for(int i = 1;i <= n;++i){
		int tmp = 0,cnt0 = 0;
		for(int j = i;j <= n;++j){
			if(a[j] == 0) ++cnt0;
			if(!s[a[j] + INF]) ++tmp;
			s[a[j] + INF] = 1;
			if(cnt0 != 0 && cnt0 != j - i + 1) ++ans[tmp - 1];
			else ++ans[tmp];
		}
		for(int j = i;j <= n;++j) s[a[j] + INF] = 0;
	}
	for(int i = 1;i <= n;++i) printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：rainygame (赞：0)

考虑划分的性质，发现将一些数放在一组当且仅当它们的质因子的幂次在模 $2$ 意义下是完全相同的。例如 $2$ 和 $8$ 可以放在同一组，因为 $2=2^1,8=2^3$，$[1]$ 和 $[3]$ 在模 $2$ 意义下是相同的。

这样就容易想出一种做法，枚举区间的同时动态维护区间内的数的质因子幂次，然后直接计算有多少个不同的即可。注意同一组必须正负性相同，特别地，$0$ 可以随意塞入任何一组。

判断不同可以使用哈希（有点卡哈希），注意有点卡常，可以将哈希值离散化之后在判断个数，同时将 $10^4$ 以内的素数筛出来方便质因子分解。时间复杂度 $O(n^2+n\frac{\sqrt V}{\ln V})$，可以通过。

[submission](https://codeforces.com/contest/980/submission/293587964)

---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF980)

&nbsp;

### 题目大意
给定一个长度为 $n$ 的序列，试将其划分成若干组，使得每组中的数两两相乘均为平方数，同时保证组数尽可能小。

对于该序列的每个子串均进行这样的划分操作，统计并从 $1$ 到 $n$ 输出有多少个子串被划分为了 $i$ 组。

&nbsp;

### 解题思路
设有三个数 $a$，$b$，$c$，满足下列关系：

$$a \times b = d^2$$
$$a \times c = e^2$$

由于 $d^2$ 和 $e^2$ 中出现的质因数指数均为偶数，那么对于 $a$ 的质因数 $x_i$，若其指数为 $y_i$，且 $y_i$ 为奇数， 则$b$ 和 $c$ 中均有质因数 $x_i$，且指数同样为奇数。

则对于 $b \times c$，因为 $b$ 中指数为奇数的质因数在 $c$ 中指数同样为奇数，所以 $b \times c$ 也是一个平方数。

于是可以得出结论，一组和某一个数相乘为完全平方数的数中，一定满足两两相乘也为平方数。

所以就可以用并查集来维护集合数量，将 $a_i \times a_j$为平方数的 $i$，$j$ 合并。之后枚举子串的左端点与右端点，统计出答案个数后输出即可。

代码如下：
```
int main(){
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		fa[i]=i;
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			int x=find_root(i);
			int y=find_root(j);
			if(x==y||a[x]*a[y]<=0) continue;//判断是否能够合并
			ll tmp=sqrt(a[x]*a[y]);
			//cout<<tmp<<" "<<a[x]<<" "<<a[y]<<endl;
			if(a[x]*a[y]==tmp*tmp) fa[x]=y;
		}
	}
	
	for(int i=1;i<=n;i++){//枚举左端点
		int pos=0;
		for(int j=i;j<=n;j++){//调整右端点
			if(!a[j]) ans[max(pos,1)]++;//特判0
			else{
				int x=find_root(j);
				if(cnt[x]!=i){//如果出现了新的集合
					pos++;
					cnt[x]=i;
				}
				ans[pos]++;
			}
		}
	}
	
	for(int i=1;i<=n;i++){
		printf("%d ",ans[i]);
	}
	return 0;
}
```
完结撒花 OvO


---

## 作者：NaN_HQJ2007_NaN (赞：0)

有个显然的小 trick：如果两个数相乘为平方数，那么消去平方因子后这两个数相等。

于是我们可以暴力枚举，每出现一个新数就加一，用 unordered_map 维护，然后就 T 了。

考虑优化。我们对于每个数预处理出上一个与它相等的数的位置。这样每次枚举的时候只需要看 $pre_i$ 是否小于左边界即可。

注意特判一下 $0$。

复杂度 $O(n^2)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5000+5;
int n,a[N],ans[N],pre[N];
int fen(int x){
  int flag=(x>=0?1:-1);
  x=abs(x);
  for(ll i=2;i*i<=x;++i){
    ll t=i*i;
    while(x%t==0)x/=t;
  }
  return x*flag;
}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n;
  for(int i=1;i<=n;++i){
    cin>>a[i];
    a[i]=fen(a[i]);
    for(int j=i-1;j>=1;--j){
      if(a[i]==a[j]){
        pre[i]=j;
        break;
      }
    }
  }
  for(int i=1;i<=n;++i){
    bool flag=0;
    int cnt=0;
    for(int j=i;j<=n;++j){
      if(a[j]==0)flag=1;
      if(pre[j]<i)++cnt;
      if(flag)++ans[max(cnt-1,1)];
      else ++ans[cnt];
    }
  }
  for(int i=1;i<=n;++i)cout<<ans[i]<<" ";
  cout<<endl;
  return 0;
}

```


---

## 作者：OrezTsim (赞：0)

看到题，最小划分组一定有确定性方案。

考虑如果两个数 $x,y$ 满足怎样的条件才能使其被分为同一组。

显然对于组大小 $\text{siz}=2$，有 $x \cdot y$ 为平方数才能满足为同一组。

考虑拓展到 $\text{siz}>2$ 的情况。

假设当前 $x=\prod\limits p_i^{k_i},\space y=\prod\limits P_i^{K_i}$，且 $x \cdot y$ 为平方数。

那么有，对于相同的质因子 $p_i,P_j$，有 $\forall [k_i+K_j\equiv0\space(\bmod\space2)]$。

对于不同的质因子 $p_i$，有 $\forall [k_i\equiv0\space(\bmod\space2)]$。对于 $P_j$ 同理。

那么假设当前已经合并 $x,y$，且 $z$ 可以与 $x$ 合并。

现在探讨 $y,z$ 匹配是否合法。令 $z=\prod g_i^{l_i}$。

那么对于与 $x,y$ 共同的质因子，幂和显然为偶数，合法。

对于和 $x,y$ 均不相同的质因子，由于和 $x$ 合并时合法，它的幂一定本来就是偶数。

对于仅和 $y$ 相同的质因子，由于 $y$ 的幂本来就是偶数（因为和 $x$ 合并时合法），且因为 $x,z$ 合并时合法，$z$ 的幂本来也是偶数。也就是说，$z$ 的这个质因子若和 $y$ 相同，偶 $+$ 偶 $=$ 偶，仍然合法。

拿并查集维护它的性质即可。复杂度 $O(n^2 \log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e3 + 10;
int n, cnt, a[N], res[N], fa[N]; bool vis[N];
inline int getf(int x) { return fa[x] == x? x : fa[x] = getf(fa[x]); }

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    cin >> n; for (int i = 1; i <= n; ++i) cin >> a[i], fa[i] = i;
    for (int i = 1; i < n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            int tmp = a[i] * a[j]; if (tmp <= 0) continue;
            int sq = sqrt(tmp); if (sq * sq == tmp) fa[getf(i)] = getf(j);
        }
    for (int i = 1; i <= n; ++i) {
        fill(vis + 1, vis + 1 + n, false); cnt = 0;
        for (int j = i; j <= n; ++j) {
            if (!a[j]) { ++res[max(cnt, 1ll)]; continue; }
            int f = getf(j); if (!vis[f]) vis[f] = true, ++cnt;
            ++res[cnt];
        }
    }
    for (int i = 1; i <= n; ++i) cout << res[i] << ' ';
    return 0;
}
```

---

## 作者：vvauted (赞：0)

- [CF980D Perfect Groups](https://www.luogu.com.cn/problem/CF980D)

易得结论：当 $xy$ 为完全平方数，$yz$ 为完全平方数，且三者皆非 0 时， $xz$ 也为完全平方数。

> 证明： 

>设 $f(y)$ 为 $y$ 的最小完全平方倍数，易得：

>$$f(y)\mid x,y$$

>且由于完全平方数的性质，可得：

>$$\frac x {f(y)}, \frac z {f(y)} \text{ 均为完全平方数}$$

>那么：

>$$xz=\frac x {f(y)} \frac z {f(y)}f^2(y)$$

>显然也为完全平方数。

那么根据这个，我们维护两两乘积为完全平方数的最大集合，$O(n^2)$ 的枚举每一个区间判断由多少个集合组成即可。

我的维护方法是：维护每一个节点下一个和它同集合元素的位置 $R_i$，那么我们固定右端点，区间从右向左扫过来时，计算新加入节点 $x$ 的贡献即为判断 $R(x)$ 是否大于当前右端点。

考虑对 $0$ 单独处理，显然区间包含 $0$ 的情况分为两种：

> 区间全部为 $0$，把所有的 $0$ 放入一个集合，否则把 $0$ 随便放入任何一个集合即可。

**Code**

```cpp
#include <bits/stdc++.h>
#define Maxn 5005
#define Nep(i, l, r) for(int i = l; i != r; ++ i)
#define Rep(i, l, r) for(int i = l; i <= r; ++ i)
#define rep(i, l, r) for(int i = l; i < r; ++ i)
#define Lep(i, l, r) for(int i = l; i >= r; -- i)
#define lep(i, l, r) for(int i = l; i > r; -- i)
#define ll long long
#define ull unsigned long long
#define int long long

int a[Maxn], R[Maxn], ans[Maxn];

bool judge(int x) {
    if(x < 0) return 0;
    int y = sqrt(x);
    return y * y == x;
}

int read() {
	int x = 1, res = 0, ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') x = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
	return x * res;
}

int fa[Maxn]; 
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }

signed main() {
    int n = read(); Rep(i, 1, n) a[i] = read(), fa[i] = i;
    Rep(i, 1, n) if(fa[i] == i) Rep(j, i + 1, n) if(a[i] && a[j] && judge(a[i] * a[j])) merge(i, j);
    Rep(i, 1, n) if(a[i]) Rep(j, i + 1, n) if(find(i) == find(j)) { R[i] = j; break; }
    Rep(i, 1, n) if(! R[i]) R[i] = n + 1; int res = 0;
    Rep(r, 1, n) {
        res = 0;
        Lep(l, r, 1) if(a[l]) res += R[l] > r, ans[res] ++;
        else ans[std :: max(res, 1LL)] ++;
    } Rep(i, 1, n) printf("%lld ", ans[i]);
}
```

---

## 作者：qfpjm (赞：0)

# 题解

- 首先由一个结论：如果 $a\times b$ 和 $b\times c$ 都为完全平方数，那么 $a\times c$ 也为完全平方数。（证明可以去网上搜）

- 那么，这题的的做法就显然了。由于 $n$ 只有 $5000$，所以可以使用 $O(n^2)$ 的做法.

- 首先，我们要把积为完全平方数的两个数放进一个集合中，这里使用并查集比较简洁（当然你也可以使用一些 STL）。然后，我们枚举每个区间里的集合数，累加入每一答案即可，最后还要注意 $a_i=0$ 的情况。

- 这样的做法时间复杂度为 $O(n^2)$，但是 $|a_i|\leq 10^8$，平方后会炸 int，所以需要开 long long。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, a[5005], fa[5005], num[5005], ans[5005];

int find(int x)
{
	if (fa[x] == x)
	{
		return x;
	}
	return fa[x] = find(fa[x]);
}

void _union(int x, int y)
{
	fa[find(x)] = find(y);
}

signed main()
{
	cin >> n;
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i];
		fa[i] = i;
	}
	for (int i = 1 ; i <= n ; i ++)
	{
		for (int j = 1 ; j < i ; j ++)
		{
			if (a[i] * a[j] > 0)
			{
				int tmp = (int)sqrt(a[i] * a[j]);
				if (tmp * tmp == a[i] * a[j])
				{
					_union(i, j);
				}
			}
		}
	}
	for (int i = 1 ; i <= n ; i ++)
	{
		int tot = 0;
		memset(num, 0, sizeof(num));
		for (int j = i ; j <= n ; j ++)
		{
			if (a[j] == 0)
			{
				ans[max(tot, 1ll)] ++;
			}
			else
			{
				if (!num[find(j)])
				{
					num[find(j)] = 1;
					tot ++;
				}
				ans[tot] ++;
			}
		}
	}
	for (int i = 1 ; i <= n ; i ++)
	{
		cout << ans[i] << " ";
	}
}
```


---

## 作者：orz_z (赞：0)

## 题目大意

将一个串划分为多个子集（不要求连续），要求同一子集内两任意元素的积为平方数。

定义一个串的答案为所需的最少子集个数。

一个长度为 $n$ 的串有 $\frac{n(n+1)}{2}$ 个**非空子串**，求答案为 $1,2,3,\cdots ,n$ 的非空子串个数。

## 解题思路

结论：

若 $ab$ 为平方数，$bc$ 为平方数，则 $ac$ 为平方数。

证明：

根据唯一分解定理，有：
$$
a=\prod_{i=1}^{k}p_i^{a_i}\\
b=\prod_{i=1}^{k}p_i^{b_i}\\
c=\prod_{i=1}^{k}p_i^{c_i}
$$


上述 $p_i$ 为质数。

因为 $ab$ 为平方数，$bc$ 为平方数，那么有：
$$
\forall i\in[1,k],2|a_i+b_i\\
\forall i\in[1,k],2|b_i+c_i
$$
得：
$$
\forall i\in[1,k],2|a_i+c_i
$$
那么 $ac$ 为平方数。

证毕。

------

再看原题。

根据上面得结论，我们可以把 $a_i \times a_j$ 为平方数的用并查集维护。

那么在同一个集内的数都满足两任意元素的积为平方数。

那么逐个区间求即可，时间复杂度 $\mathcal O(n^2)$。

注意 $a_i=0$ 的情况。

## CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

const int _ = 5007;

int n, a[_], fa[_], vis[_], ans[_];

int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

signed main()
{
	n = read();
	for(int i = 1; i <= n; ++i)
	{
		a[i] = read();
		fa[i] = i;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j < i; ++j)
			if(a[i] * a[j] > 0)
			{
				int tmp = (int)sqrt(a[i] * a[j]);
				if(tmp * tmp == a[i] * a[j])
					fa[find(j)] = find(i);
			}
	for(int i = 1; i <= n; ++i)
	{
		int tot = 0;
		memset(vis, 0, sizeof vis);
		for(int j = i; j <= n; ++j)
			if(!a[j])
				ans[max(1ll, tot)]++;
			else
			{
				if(!vis[find(j)])
				{
					vis[find(j)] = 1;
					tot++;
				}
				ans[tot]++;
			}
	}
	for(int i = 1; i <= n; ++i) printf("%lld ", ans[i]);
	return 0;
}
```



---

## 作者：lgswdn_SA (赞：0)

不得不说这题挺喵的。

有一个重要的转换。我们设 $a=p^2x,b=q^2y$，其中 $x,y$ 皆不含平方因子，**则 $ab$ 为完全平方数相当于 $x=y$**。因为对于任意一个质因数 $m$，若是 $a,b$ 中的一个数的约数，那么必定导致 $xy$ 会有指数为奇数的质因数 $m$。

然后接下来就好处理多了。我们相当于要求**每个连续子序列中，有多少个不同的数**。要求复杂度 $O(n^2)$。这就可以用一个计数器数组增量维护统计。还有就是注意之前还要离散化一下即可。

还有一个细节：**0 乘上任何一个数都是完全平方数**，所以需要加上一个小特判。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=5009;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,a[N],cnt,c[N],tot,ans[N];

struct dc {int val,id;} b[N];
bool cmp(const dc &a,const dc &b) {return a.val<b.val;}
void discrete() {
	rep(i,1,n) b[i]=(dc){a[i],i};
	sort(b+1,b+n+1,cmp);
	a[0]=-0x3f3f3f3f;
	rep(i,1,n) {
		if(b[i].val!=b[i-1].val) cnt++;
		if(b[i].val) a[b[i].id]=cnt;
		else a[b[i].id]=0;
	}
}

signed main() {
	n=read();
	rep(i,1,n) a[i]=read();
	rep(i,1,n) {
		for(int j=2;j*j<=abs(a[i]);j++) while(a[i]%(j*j)==0) a[i]/=(j*j);
	}
	discrete();
	rep(l,1,n) {
		tot=0;
		rep(i,1,n) c[i]=0;
		rep(r,l,n) {
			if(c[a[r]]==0&&a[r]) tot++;
			c[a[r]]++;
			ans[max(tot,1ll)]++;
		}
	}
	rep(i,1,n) printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：0)

傻题。 可以把一个数表示成 质数幂次的乘积

可以发现只与幂次的奇偶有关。。

然后就把所有的平方因子都除掉。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1e5+5;
int n,tot,pri[N];
bool mark[N<<1];
inline void pre(){
	for (int i=2;i<1e5;i++){
		if (!mark[i]) pri[++tot]=i;
		for (int j=1;j<=tot&&pri[j]*i<1e5;j++) {
			mark[i*pri[j]]=1;
			if (i%pri[j]) break;
		}
	}
}
struct node{
	int x,id;
}b[N];
int a[N][2];
inline void init(){
	pre();
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int x;
		scanf("%d",&x); int flag=0;
		if (x<0) x=-x,flag=1;
		if (x==0) flag=2;
		for (int j=1;j<=tot&&pri[j]*pri[j]<=x;j++){
			if (x%(pri[j]*pri[j])==0){
				while (x%(pri[j]*pri[j])==0){
					x/=pri[j]*pri[j];
				}
			}
		}
		a[i][0]=x; a[i][1]=flag;
		b[i]=(node){x,i};
	}
}
inline bool cmp(node A,node B){return A.x<B.x;}
int ans[N],ton[2][N],sum,cnt;
inline void upd(int i,int v){
	if (a[i][1]==2) cnt+=v;
		else {
			if (!ton[a[i][1]][a[i][0]]&&v==1) sum++;
			ton[a[i][1]][a[i][0]]+=v;
		}
}
inline void solve(){
	sort(b+1,b+1+n,cmp); int tmp=0; b[0].x=-1;
	for (int i=1;i<=n;i++){
		if (b[i].x!=b[i-1].x) tmp++;
		a[b[i].id][0]=tmp;
	}
	for (int i=1;i<=n;i++){
		cnt=0; sum=0; upd(i,1); sum=max(sum,1); ans[sum]++;
		for (int j=i+1;j<=n;j++){
			upd(j,1); sum=max(sum,1);
			ans[sum]++;
		}
		memset(ton,0,sizeof ton);
	}
	for (int i=1;i<=n;i++){
		printf("%d ",ans[i]);
	}
}
int main(){
	init();
	solve();
	return 0;
}
```

---

