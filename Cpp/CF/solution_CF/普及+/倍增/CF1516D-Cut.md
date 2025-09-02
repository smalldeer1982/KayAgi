# Cut

## 题目描述

This time Baby Ehab will only cut and not stick. He starts with a piece of paper with an array $ a $ of length $ n $ written on it, and then he does the following:

- he picks a range $ (l, r) $ and cuts the subsegment $ a_l, a_{l + 1}, \ldots, a_r $ out, removing the rest of the array.
- he then cuts this range into multiple subranges.
- to add a number theory spice to it, he requires that the elements of every subrange must have their product equal to their [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple).

Formally, he partitions the elements of $ a_l, a_{l + 1}, \ldots, a_r $ into contiguous subarrays such that the product of every subarray is equal to its LCM. Now, for $ q $ independent ranges $ (l, r) $ , tell Baby Ehab the minimum number of subarrays he needs.

## 说明/提示

The first query asks about the whole array. You can partition it into $ [2] $ , $ [3,10,7] $ , and $ [5,14] $ . The first subrange has product and LCM equal to $ 2 $ . The second has product and LCM equal to $ 210 $ . And the third has product and LCM equal to $ 70 $ . Another possible partitioning is $ [2,3] $ , $ [10,7] $ , and $ [5,14] $ .

The second query asks about the range $ (2,4) $ . Its product is equal to its LCM, so you don't need to partition it further.

The last query asks about the range $ (3,5) $ . You can partition it into $ [10,7] $ and $ [5] $ .

## 样例 #1

### 输入

```
6 3
2 3 10 7 5 14
1 6
2 4
3 5```

### 输出

```
3
1
2```

# 题解

## 作者：Plozia (赞：10)

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/120208279)

一道套路题，做过同类型的题目应该能够直接看出做法。

这道题首先询问方式很像 DS 题的询问方式，但是实际上你会发现这道题做法是不能纯 DS 的，或者说这道题根本就不需要 DS。

发现如果乘积和 LCM 要相同的话需要满足这个区间内没有任意两个数最大公约数大于 1，而最大公约数可以归约到质因数上。

所以首先对每个数做一个质因数分解，然后考虑预处理出 $r_i$ 表示第 $i$ 个位置不断往右边扩展，能够扩展到的最右边的位置是什么，满足 $[i,r_i]$ 合法，且 $[i,r_i+1]$ 不合法或者是 $r_i<n$。

这个实际上开一个 $cnt$ 数组双指针扫一遍就可以了，没必要使用什么高端 DS 技巧。

然后就是套路倍增了，设 $f_{i,j}$ 表示 $i$ 往右边跳 $2^j$ 个区间之后能够到达的右端点，那么 $f_{i,j}=f_{\min\{f_{i,j-1}+1,n\},j-1}$。

然后查询的时候我们直接仿照倍增求 LCA 的时候往右边跳就可以了。

Code：[GitHub CodeBase-of-Plozia CF1516D Cut.cpp](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/Codeforces%20%E5%88%B7%E9%A2%98%E5%90%88%E9%9B%86/CF1516D%20Cut.cpp)

```cpp
/*
========= Plozia =========
	Author:Plozia
	Problem:CF1516D Cut
	Date:2021/9/8
========= Plozia =========
*/

#include <bits/stdc++.h>
using std::vector;

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, q, a[MAXN], f[MAXN][21], book[MAXN];
vector <int> v[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum * 10) + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void init()
{
	int l = 0, r = 0, sum = 0;
	while (l <= n)
	{
		++l; ++r;
		for (int i = 0; i < v[l - 1].size(); ++i)
		{
			--book[v[l - 1][i]];
			if (book[v[l - 1][i]] == 1) --sum;
		}
		while (r <= n)
		{
			for (int i = 0; i < v[r].size(); ++i)
			{
				++book[v[r][i]];
				if (book[v[r][i]] > 1) ++sum;
			}
			if (sum != 0)
			{
				for (int i = 0; i < v[r].size(); ++i)
				{
					--book[v[r][i]];
					if (book[v[r][i]] == 1) --sum;
				}
				--r; break ;
			}
			++r;
		}
		if (r > n) f[l][0] = n;
		else f[l][0] = r;
		// printf("(%d, %d)\n", l, Min(r, n));
	}
	for (int j = 1; j <= 20; ++j)
		for (int i = 1; i <= n; ++i)
			f[i][j] = f[Min(f[i][j - 1] + 1, n)][j - 1];
}

int main()
{
	n = Read(), q = Read();
	for (int i = 1; i <= n; ++i) a[i] = Read();
	for (int i = 1; i <= n; ++i)
	{
		int tmp = a[i];
		for (int j = 2; j * j <= tmp; ++j)
		{
			if (tmp % j == 0)
			{
				v[i].push_back(j);
				while (tmp % j == 0) tmp /= j;
			}
		}
		if (tmp != 1) v[i].push_back(tmp);
	}
	init();
// 
	// for (int i = 1; i <= n; ++i)
	// {
		// printf("%d %d %d\n", f[i][0], f[i][1], f[i][2]);
	// }
// 
	for (int i = 1; i <= q; ++i)
	{
		int l = Read(), r = Read(), sum = 0;
		for (int j = 20; j >= 0; --j)
			if (f[l][j] < r) l = f[l][j] + 1, sum += (1 << j);
		printf("%d\n", sum + 1);
	}
	return 0;
}
```

---

## 作者：Priori_Incantatem (赞：8)

[题目链接](https://www.luogu.com.cn/problem/CF1516D)  
[在我的Blog查看](https://blog.csdn.net/Brian_Pan_/article/details/116000580)

### 题目大意

给出一个长度为 $n$ 的序列 $a$，以及 $q$ 次询问  
每次询问给出 $l,r$，问最少需要把区间 $[l,r]$ 划分成多少段，满足每段内元素的 LCM 等于元素的乘积

----

~~这数据范围，这询问方式，一看就是DS题~~

首先，我们考虑 LCM 的性质。如果一段区间内的数的 LCM 等于所有元素之积，那么这个区间中的数一定两两互质。

我们设 $nxt_i$ 表示 $i$ 后面第一个与 $a_i$ **不**互质的数的位置  
同时，记 $f_i$ 为以 $i$ 为左端点时，满足区间内数两两互质的最远右端点 $+1$，也就是下一个互质区间的左端点

我们考虑从后往前计算 $nxt_i$
对于每个质数 $p_k$，我们维护 $c_k$ 表示 $p_k$ 的倍数出现的最近位置  
那么，$nxt_i$ 就是所有 $a_i$ 的质因数的 $c$ 的最小值

那么显然 $f_i=\min\limits_{k=i}^{nxt_i-1}nxt_k$，可用线段树解决

最后，我们考虑将 $f_i$ 进行倍增。$f_{i,k}$ 表示 $i$ 后面第 $2^k$ 个互质区间的左端点。最终在询问时，只需要尽可能地倍增向后跳，并统计答案即可。

时间复杂度 $\mathcal O(n+ n\sqrt n + n \log n + n \log n)=\mathcal O(n\sqrt n)$  
一个小优化：我们可以用埃氏筛寻找质数，并预处理每个树的质因子。由于 $10^5$ 内的数的不同质因子数不超过 $6$，所以计算 $nxt$ 的复杂度变为 $\mathcal O(n)$，总复杂度 $\mathcal O(n \log n)$


```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int Maxn=1e5+10;
const int Maxm=Maxn<<2;
const int inf=0x3f3f3f3f;
vector <int> c[Maxn];
int b[Maxn],a[Maxn];
int f[Maxn][30];
int p[Maxn],id[Maxn];
bool vis[Maxn];
int minv[Maxm];
int n,m,q,cnt;
int gcd(int x,int y)
{
	if(!y)return x;
	return gcd(y,x%y);
}
inline void push_up(int k)
{
	minv[k]=min(minv[k<<1],minv[k<<1|1]);
}
void build(int k,int l,int r)
{
	if(l==r)
	{
		minv[k]=f[l][0];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	push_up(k);
}
int query(int k,int l,int r,int x,int y)
{
	if(x<=l && r<=y)return minv[k];
	int mid=(l+r)>>1,ret=inf;
	if(x<=mid)ret=query(k<<1,l,mid,x,y);
	if(mid<y)ret=min(ret,query(k<<1|1,mid+1,r,x,y));
	return ret;
}
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
	// freopen("in.txt","r",stdin);
	n=read(),q=read();
	for(int i=1;i<=n;++i)
	a[i]=read(),m=max(m,a[i]);
	vis[1]=1;
	for(int i=2;i<=m;++i)
	{
		if(vis[i])continue;
		b[++cnt]=i,id[i]=cnt;
		c[i].push_back(cnt);
		for(int j=(i<<1);j<=m;j+=i)
		vis[j]=1,c[j].push_back(cnt);
	}
	for(int i=1;i<=cnt;++i)
	p[i]=n+1;
	fill(f[n+1],f[n+1]+25,n+1);
	for(int i=n;i;--i)
	{
		f[i][0]=n+1;
		for(int j=0;j<c[a[i]].size();++j)
		{
			f[i][0]=min(f[i][0],p[c[a[i]][j]]);
			p[c[a[i]][j]]=i;
		}
	}
	build(1,1,n);
	for(int i=n;i;--i)
	{
		f[i][0]=query(1,1,n,i,f[i][0]-1);
		for(int j=1;j<=20;++j)
		f[i][j]=f[f[i][j-1]][j-1];
	}
	while(q--)
	{
		int l=read(),r=read();
		int x=l,ret=0;
		for(int i=20;i>=0;--i)
		if(f[x][i]<=r)
		ret+=(1<<i),x=f[x][i];
		++ret;
		printf("%d\n",ret);
	}
	return 0;
}

```

---

## 作者：tommymio (赞：6)

考虑直接对每个数质因数分解。考虑到每个数 $a_i$ 向后总会有一些质因子重合。设 $nxt_i$ 为 $i$ 向右所能延伸到的右端点，满足都不与 $a_i$ 质因子重合，此处为开区间。处理出 $\text{nxt}$ 值，将 $nxt_i$ 与 $nxt_{i+1}$ 取 $\min$。然后倍增跳 $nxt_i$ 即可。

我也不是很清楚为什么有些人的做法那么麻烦，这题分明很 $\text{naive}$ 啊（

赛时代码略显凌乱。吐槽一下你谷搬题效率，过了这么多天才爬好 CF 的题。

```cpp
#include<cstdio>
#define int ll
typedef long long ll;
int num;
int a[100005],rev[100005],pre[100005];
int v[100005],p[100005],skip[100005][25];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline int min(const int &x,const int &y) {return x<y? x:y;}
inline int gcd(int a,int b) {return b==0? a:gcd(b,a%b);}
inline int lcm(int a,int b) {return a/gcd(a,b)*b;}
inline int ask(int x,int R) {
    int res=0;
    for(register int i=20;i>=0;--i) if(skip[x][i]&&skip[x][i]<=R) {res+=(1<<i); x=skip[x][i];}
    return res+1;
}
inline void makePrime(int N=100000) {
    for(register int i=2;i<=N;++i) {
        if(!v[i]) {p[++num]=i;rev[i]=num;}
        for(register int j=1;j<=num&&i*p[j]<=N;++j) {
            v[i*p[j]]=1; 
            if(i%p[j]==0) break;
        }
    }
}
signed main() {
    makePrime(); int n=read(),Q=read();
    for(register int i=1;i<=n;++i) a[i]=read();
    for(register int i=1;i<=num;++i) pre[i]=n+1;
    for(register int j=0;j<=20;++j) skip[n+1][j]=n+1;
    for(register int i=n;i>=1;--i) {
        int tmp=a[i]; int nxt=n+1;
        for(register int j=2;j*j<=tmp;++j) {
            if(tmp%j==0) {
                nxt=min(nxt,pre[rev[j]]);
                while(tmp%j==0) {tmp/=j;}
                pre[rev[j]]=i;
            }
        }
        if(tmp!=1) {nxt=min(nxt,pre[rev[tmp]]); pre[rev[tmp]]=i;}
        // printf("\n");
        skip[i][0]=min(skip[i+1][0],nxt); 
    }
    for(register int i=n;i>=1;--i) {
        for(register int j=1;j<=20;++j) {
            skip[i][j]=skip[skip[i][j-1]][j-1];
        }
    }
    while(Q--) {
        int l=read(),r=read(),cnt=0;
        printf("%lld\n",ask(l,r));
    }
    return 0;
}
```

---

## 作者：Godzilla (赞：3)

### $\mathtt{Description:}$

给定 $n$ 个数的序列和 $q$ 次询问，每次询问给定区间 $[l,r]$ ，求出至少将其分割成几个子区间，才使得每个子区间的 $\operatorname{lcm}$ 等于区间内所有数的乘积。

### $\mathtt{Solution:}$

区间 $[l,r]$ 内所有数的乘积等于其 $\operatorname{lcm}$ 当且仅当 $\gcd(a_i,a_j)=1$ ，其中 $i\neq j,\; i,j \in [l,r]$ 。

那么可以对于每次给出的区间 $[l,r]$ 从左到右暴力扫一遍，过不去，考虑优化。

可以预处理每个左端点 $i$ 所对应的最靠右的右端点 $nex(i)$ 。

从左到右枚举 $i$ ，发现 $nex(i) \ge nex(i-1)$ ，因为少了 $1$ 个数，右端点必定不会更近。

那么就可以 $O(n)$ 双指针预处理 $nex(i)$ 。

对于如何判断两两互质，可以用线性筛预处理出 $10^5$ 以内的质数，再枚举每个质数 $j$ ，对于其倍数 $i$ ，$i \le 10^5$ ，将 $j$ 加入 $i$ 的 质因数集合，换个顺序，就可以从 $O(n\sqrt{n})$ 变成 $O(n\log n)$ 。

如果从 $l$ 开始，往右边跳的话，如果它们都互相不互质，单次就变成 $O(n)$ 了。

容易想到，可以用倍增优化，单次就变成 $O(\log n)$ 。

总时间复杂度 $O(n)+O(n\log n)+O(n\log n)=O(n\log n)$ 。

$\mathtt{Ps:}$ 

$nex(i)$ 表示的不是以 $i$ 为左端点的最靠右的右端点，而是下一个区间的左端点。

预处理 $st(i,j)$ 时，必须要加上 $st(k,n+1)$ 为 $n+1$ ，否则其值为 $0$ ，可能会一直跳到 $2^m$ 。

### $\mathtt{Code:}$

`Prime` 预处理质数

`Calc` 判断当前的 $a_j$ 能否加入

`Del` 删除 $a_{i-1}$ 

`Ask` 倍增查询答案，注意最后一定要加 $1$ 

```c++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

#define LL long long
#define PR pair<LL,int>

using namespace std;

const int kN = 1e5;

int n, a[kN + 10], q;
int prime[kN + 10], tot;
int nex[kN + 10], st[30][kN + 10];
int _2[30], num[kN + 10];

vector<int> e[kN + 10];

bool isp[kN + 10];

void Prime() {
    isp[1] = 1;

    for (int i = 2; i <= kN; ++i) {
        if (!isp[i]) {
            prime[++tot] = i;
        }

        for (int j = 1; j <= tot && prime[j]*i <= kN; ++j) {
            isp[i * prime[j]] = 1;

            if (i % prime[j] == 0) {
                break;
            }
        }
    }

    for (int i = 1; i <= tot; ++i) {
        for (int j = prime[i]; j <= kN; j += prime[i]) {
            e[j].push_back(i);
        }
    }
}

bool Calc(int x) {
    for (int i = 0; i < e[x].size(); ++i) {
        int k = e[x][i];

        if (num[k]) {
            return 0;
        }
    }

    for (int i = 0; i < e[x].size(); ++i) {
        int k = e[x][i];
        num[k] = 1;
    }

    return 1;
}

void Del(int x) {
    if (!x) {
        return;
    }

    for (int i = 0; i < e[x].size(); ++i) {
        int k = e[x][i];
        num[k] = 0;
    }
}

int Ask(int l, int r) {
    int cnt = 0;

    for (int i = 20; i >= 0; --i) {
        if (st[i][l] <= r) {
            l = st[i][l];
            cnt += _2[i];
        }
    }

    return cnt + 1;
}

int main() {
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    Prime();
    _2[0] = 1;

    for (int i = 1; i <= 20; ++i) {
        _2[i] = _2[i - 1] * 2;
    }

    for (int i = 1, j = 0; i <= n; ++i) {
        Del(a[i - 1]);

        while (j < n && Calc(a[j + 1])) {
            j++;
        }

        nex[i] = j + 1;
        st[0][i] = nex[i];
    }

    st[0][n + 1] = n + 1;

    for (int i = 1; i <= 20; ++i) {
        st[i][n + 1] = n + 1;

        for (int j = 1; j <= n; ++j) {
            st[i][j] = st[i - 1][st[i - 1][j]];
        }
    }

    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", Ask(l, r));
    }

    return 0;
}
```



---

## 作者：WitheredZeal (赞：3)

## 题意  
给你一个 $n$ 个数的序列 $\{a_i\}$，和 $q$ 次询问，每次询问一段区间 $[l,r]$，问至少要把这个区间分为几个子区间，使得每个子区间内的数的乘积等于这个子区间内所有数的 $\text{LCM}$。  
$n,a_i,q\le 10^5$。

## 题解  
首先，分成子区间的条件，等价于 $\forall i,j \in [l,r],\gcd(a_i,a_j)=1$。  
再转换一下，就是说，整个子区间**没有相同的素因子**。  
当区间 $[i,j]$ 是合法的时，我们称“$i$ 能达到 $j$”。  
然后我们发现，每个点能达到的最远的点是**单调递增**的。  

那么考虑求出每个点能达到的最远的点**的后面一个点**，然后询问的时候暴力跳，能保证答案是正确的。  
那怎么快速得出一个询问的答案？  
倍增即可。 

然后就考虑如何求出每个点能达到的最远的点的后面一个点。  
首先埃氏筛处理出 $10^5$ 内所有数的素因子。  
然后考虑到这个值有单调性，用双指针进行维护。  

每次加入一个数，就把它的所有素因子加进去。如果发现有重复的，那么重新删掉，然后立刻返回。  
删去一个数的时候就把所有素因子删去即可。  
想清楚了代码还是比较好写的。  
时间复杂度 $O((n+q)\log n)$。  
```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register signed
#define rd(x) x=read()
using namespace std;
const int N=1e5+5;
const int M=21;
const int mod=998244353;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline int ksm(int x,int y=mod-2,int z=mod){int ret=1;while (y){if (y&1) ret=(ret*x)%z;x=(x*x)%z;y>>=1;}return ret;}
int n,k,q;
int a[N];
int v[N],p[N],cnt;
vector<int> V[N];
int c[N];
int nxt[N][M];
void init(int n)
{
	for (int i=2;i<=n;i++)
	{
		if (!v[i]) {p[++cnt]=i;
		for (int j=i+i;j<=n;j+=i)v[j]=1;}
	}
	for (int i=1;i<=cnt;i++) for (int j=p[i];j<=n;j+=p[i]) V[j].push_back(i);
}
signed main()
{
	init(100000);
    rd(n);rd(q);for (int i=1;i<=n;i++) rd(a[i]);
	int k=0;
	for (int i=1;i<=n;i++)
	{
		if (i!=1) for (int j:V[a[i-1]]) c[j]--;
		while (k<=n)
		{
			k++;
			if (k==n+1) break;
			for (int j:V[a[k]]) c[j]++;
			bool flag=0;
			for (int j:V[a[k]]) if (c[j]==2) flag=1;
			if (flag){for (int j:V[a[k]]) c[j]--;break;}
		}
		nxt[i][0]=k;k--;
	}
	nxt[n+1][0]=n+1;
	for (int k=1;k<=20;k++)
	{
		nxt[n+1][k]=n+1;
		for (int i=1;i<=n;i++) nxt[i][k]=nxt[nxt[i][k-1]][k-1];
	}
	while (q--)
	{
		int l,r,ans=0;
		rd(l);rd(r);
		int x=l;
		for (int k=20;k>=0;k--) if (nxt[x][k]<=r) ans+=(1<<k),x=nxt[x][k];
		cout<<ans+1<<endl;
	}

}
```

---

## 作者：RainsAFO (赞：2)

在博客园查看：[https://www.cnblogs.com/treap/p/14691686.html](https://www.cnblogs.com/treap/p/14691686.html)

感觉我的做法好复杂，但可能思考起来比较自然。

首先 $a_l\times a_{l+1} \times...\times a_r = lcm\{a_l,a_{l+1},...,a_r\}$ 意味着 $\{a_l,a_{l+1},...,a_r\}$ 两两互质。

贪心地，考虑对每个左端点 $l$ 求出最大的右端点 $r$ 使得这个区间内的数两两互质，设为 $f$ 。

记 $P_k$ 为前 $k$ 个质数组成的集合，考察 $\prod_{p \in P_k} p>10^5$ ，在 $k=7$ 时已经成立，这意味着序列 $a$ 中每个数的不同质因子个数不超过 $6$ 。

根据互质的定义以及上面的性质，可以从 $a$ 的质因子这个角度来考虑。

做一遍埃氏筛，求出每个 $a$ 的质因子集合（实际上是求了 $2$ 到 $\max_{a}$）。

记 $nxt_{i,j}$ 为下标 $>i$ ， $j$ 的倍数第一次出现的位置， $to_i$ 表示第一个下标 $>i$ ，且不与 $a_i$ 互质的数的位置。

对每个作为任意 $a$ 的质因子的质数维护一个 $vector$ 表示其出现位置，求 $nxt$ 可以在 $vector$ 内二分。

假设 $a_i$ 的质因子集合为 $\{p_1,p_2,...,p_k \}$，$to_i$ 就是 $\min_{j=1}^k nxt_{i,j}$ 。

做完这些来考虑如何求 $f$ 。

固定了左端点 $l$ ， 一个右端点 $r$ 合法的条件是 $\min_{i=l}^r to_i>r$ ， 现在要最大化 $r$ ，这个问题可以在线段树上二分：

from _rqy ：

假设现在中间是 $m$，$l$ ~ $m$ 的 $\min$ 是 $x$，
1. $x\leq m$，那 $r$ 只能在左边选，不用递归右子树了，
2. $x>r$ ，往右子树递归，但是加一个 $r<x$ 的限制。

最后对 $f$ 进行倍增 , 询问时把区间长度二进制分解然后跳倍增数组，总复杂度 $O(n\log n)$ 。

---

## 作者：寒鸽儿 (赞：1)

根号暴力吊打 $\log$  
划分在一个区间内的数要求两两互质  
比较容易求出每一个数下一个与它不互素的数:  
1) 预处理出素数和最小质因子, 可以在 $\log$ 的时间分解质因数。  
2) 倒顺枚举 , 记录每个素数作为因子最早出现的位置。分解当前数时将每个素因子最早出现的位置取 $\min$  

考虑暴力怎么做。给定一个固定的询问区间 , 从左到右贪心选择最靠右的端点满足题意。记从 $x$ 位置开始的最大区间右端点 $+1$ 为 $f(x)$ , 每个数右边第一个与它不互素的数为 $p(x)$。  
则有:  
$$
f(x) = \min\{f(x+1) , p(x)\}
$$
这个可以 $\mathcal{O(n)}$ 求。  
如果要预处理出所有 $g(x,y)$ 表示 $x$ 到 $y$ 的段数状态数是 $\mathcal{O(n^2)}$ 的。  
借助 $f(x)$ 暴力跳很容易单次卡到 $\mathcal{O(n)}$。  
这个借助 $f(x)$ 暴力跳的过程非常类似在树上跳链, 很容易想到倍增优化。  
当然考场犯浑选手想的是分块维护跳的过程, 还写挂了。  
需要维护两个值, $nstp(x)$ 表示 $x$ 跳出所在块需要的步数, $nexb(x)$ 表示跳出所在块后跳到的节点。这两个值很容易用 $f(x)$ 非常快地求出来。  
然后就是经典的跳法了, 不在同一块就整块跳过, 在同一块就一步步跳, 理论上一次查询复杂度是 $\mathcal(\sqrt n)$ 的。  
然而跑得飞快, 基本上吊打倍增写法。  
```cpp
#include <iostream>
#include <cmath>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)

using namespace std;

const int maxn = 1e5+10;
int Prime[maxn], vp[maxn], minf[maxn], tot;
void seive(int n) {
    minf[1] = 1;
    rep(i,2,n) {
        if(!vp[i]) vp[i] = 1, Prime[++tot] = i, minf[i] = i;
        for(int j = 1; 1ll * i * Prime[j] <= n; ++j) {
            vp[i*Prime[j]] = 1, minf[i*Prime[j]] = Prime[j];
            if(i % Prime[j] == 0) break;
        }
    }
}

#define gb(x) ((x-1)/blk+1)
#define hob(x) ((x-1)*blk+1)
#define eob(x) (min(n,(x)*blk))
int a[maxn], n;
int lp[maxn], nex[maxn];
int nstp[maxn], nxp[maxn], blk;
void prework() {
    blk =  min(n, (int)sqrt(n)+1);
    rep(i,1,1e5) lp[i] = n + 1; rep(i,1,n+1) nex[i] = n + 1;
    seive(1e5);
    per(i,n,1) {
        int m = a[i]; nex[i] = nex[i+1];
        while(m != 1) {
            int t = minf[m];
            while(m % t == 0) m /= t;
            nex[i] = min(nex[i], lp[t]); lp[t] = i;
        }
    }
    per(i,n,1) {
        nex[i] <= eob(gb(i)) ?
            (nstp[i] = nstp[nex[i]] + 1, nxp[i] = nxp[nex[i]]) :
            (nstp[i] = 1, nxp[i] = nex[i]);
    }
}

int main() {
    if(fopen("yl.in", "r")) {
        freopen("yl.in", "r", stdin);
        freopen("yl.out", "w", stdout);
    }
    int q; scanf("%d %d", &n, &q);
    rep(i,1,n) scanf("%d", a + i);
    prework();
    int l, r;
    rep(qr,1,q) {
        int ans = 0;
        scanf("%d %d", &l, &r);
        while(gb(l) < gb(r)) ans += nstp[l], l = nxp[l];
        while(l <= r) ++ans, l = nex[l];
        printf("%d\n", ans);
    }
    return 0;
}

```
 

---

