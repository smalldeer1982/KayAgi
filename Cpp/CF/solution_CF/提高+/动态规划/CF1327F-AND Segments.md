# AND Segments

## 题目描述

你有三个整数 $n, k, m$ 以及 $m$ 个限制 $(l_1, r_1, x_1), (l_2, r_2, x_2), \ldots, (l_m, r_m, x_m)$。

计算满足下列条件的，长度为 $n$ 的序列 $a$ 的个数：

- 对于每个 $1 \le i \le n$，$0 \le a_i \lt 2 ^ k$。
- 对于每个 $1 \le i \le m$，数字的按位与 $a[l_i] \text{ and } a_[l_i + 1] \text{ and } \ldots \text{ and } a[r_i] = x_i$。

两个序列 $a, b$ 被认为是不同的，当且仅当存在一个位置 $i$ 满足 $a_i \neq b_i$。

由于答案可能过大，请输出其对 $998\ 244\ 353$ 取模的结果。

## 说明/提示

你可以在 [这里](https://en.wikipedia.org/wiki/Bitwise_operation#AND) 获得有关按位与的信息。

在一个样例中，合法的序列 $a$ 有：$[3, 3, 7, 6]$，$[3, 7, 7, 6]$ 以及 $[7, 3, 7, 6]$。

## 样例 #1

### 输入

```
4 3 2
1 3 3
3 4 6```

### 输出

```
3```

## 样例 #2

### 输入

```
5 2 3
1 3 2
2 5 0
3 3 3```

### 输出

```
33```

# 题解

## 作者：AutumnKite (赞：26)

不错，最后 5min 开始写代码，没调出来，直接死在这题上了。

---

上面是一个菜鸡 xjb BB，不要管他。

首先看到这题，一看是位运算，先考虑每位是否独立。

因为只有 and 运算的限制，所以很显然每一位是独立的。那么我们只需要求出每一位满足限制的方案数，然后乘起来即可。

对于当前位，有若干个限制，每个限制规定了一个区间的 and 和是 $0$ 还是 $1$。

对于限制为 $1$ 的区间，直接强制每一位必须填 $1$。而对于限制为 $0$ 的区间，看上去非常难搞。

一开始我以为可以容斥，但是若干区间取并这玩意非常难处理。

突然想到了联赛前的一道作业题：[P4229 某位歌姬的故事](https://www.luogu.com.cn/problem/P4229)。

那题由于需要离散，并且限制比较宽，所以 DP 是 $O(nq)$ 的。

然而这题不需要离散，并且只有 $0$ 和 $1$，所以我们尝试去优化这个 DP。

预处理 $\operatorname{pos}[i]$ 表示 $i$ 之前（不包括 $i$）第一个 $0$ 至少填在 $\operatorname{pos}[i]$ 位置。这个预处理可以参考 P4229 中的预处理。

考虑 DP，$f[i][j]$ 表示前 $i$ 位，最后一个 $0$ 的位置为 $j$ 时满足限制的方案数。分三种情况进行转移：

- $j<\operatorname{pos}[i]$ 时，有 $f[i][j]=0$；
- $\operatorname{pos}[i]\le j < i$ 时，有 $f[i][j]=f[i-1][j]$；
- $j=i$ 时，若根据 $1$ 的限制，第 $i$ 位强制选 $1$，那么 $f[i][j]=0$；否则 $f[i][j]=\sum\limits_{k=\operatorname{pos}[i]}^{i-1} f[i-1][k]$。

对于第一种情况，我们只需要维护一个最左边不为 $0$ 的指针，每次把 $< \operatorname{pos}[i]$ 的位置刷成 $0$ 即可。

对于第二种情况，由于没有任何改变，所以我们不需要进行任何处理。

对于第三种情况，我们只要单点修改第 $i$ 个位置的值即可。注意需要实时维护当前行的和。

于是这个 DP 的复杂度变成了 $O(n)$。

每一位预处理复杂度为 $O(m)$，所以总时间复杂度 $O(k(n+m))$。

```cpp
const int N = 500005, P = 998244353;
int n, k, m, a[N], l[N], r[N], x[N], f[N], pos[N];
void inc(int &a, int b){ (a += b) >= P ? a -= P : 0; }
void dec(int &a, int b){ a < b ? a += P - b : a -= b; }
void solve(){
	read(n), read(k), read(m);
	for (register int i = 1; i <= m; ++i)
		read(l[i]), read(r[i]), ++r[i], read(x[i]);
	int ans = 1;
	for (register int p = 0; p < k; ++p){
		for (register int i = 1; i <= n + 1; ++i) pos[i] = 0, a[i] = 0;
		for (register int i = 1; i <= m; ++i)
			if (x[i] >> p & 1) ++a[l[i]], --a[r[i]]; // 差分实现区间加
			else pos[r[i]] = std::max(pos[r[i]], l[i]);
		for (register int i = 2; i <= n + 1; ++i) a[i] += a[i - 1], pos[i] = std::max(pos[i], pos[i - 1]);
		// a 预处理第 i 位是否强制选 1
		// pos 预处理 i 之前第一个 0 至少选在哪里
		for (register int i = 0; i <= n + 1; ++i) f[0] = 0;
		f[0] = 1;
		int sum = 1, l = 0;
		for (register int i = 1; i <= n + 1; ++i){
			while (l < pos[i]) dec(sum, f[l]), f[l] = 0, ++l; // 把 < pos[i] 的位置刷成 0
			f[i] = a[i] ? 0 : sum, inc(sum, f[i]); // 修改第 i 个位置的 dp 值
		}
		ans = 1ll * ans * f[n + 1] % P;
	}
	print(ans);
}
```

---

## 作者：ix35 (赞：21)

## CF 1327 F AND Segments

首先发现：每一位都是完全独立的，可以分别算，最后乘起来。

所以我们现在将问题转化为了 $k$ 个只含 $0,1$ 的子任务，注意由于 $n$ 比较大，所以你在多了个 $k$ 的情况下，接下来的做法必须是线性的，只要带一个 $\log$ 就难以通过。

如果告诉你某个区间的 $\operatorname{and}$ 是 $1$，那么当然这个区间就没有选择，必须全部是 $1$。

如果告诉你某个区间的 $\operatorname{ans}$ 是 $0$，那么这个区间就至少需要包含一个 $0$。

考虑如何进行计数，我们先考虑一个特殊情况：没有区间与等于 $1$ 的限制，只有区间与等于 $0$ 的限制时，如何处理？

---

我们先写一个暴力 DP，设 $dp(i,j)$ 表示填到第 $i$ 个位置，最后一个 $0$ 的位置为 $j$（即从右往左数的第一个 $0$）时，满足 $i$ 以前所有限制的方案数。

首先对于每个 $i$，可以求出一个 $l_i$ 表示上一个 $0$ 的最靠前位置，其实就是右端点在 $i$ 之前的所有区间的左端点最大值（因为这个区间里至少有一个 $0$，所以最后一个 $0$ 不能在这之前）。

对于 $j\in [1,l_i)$，有 $dp(i,j)=0$，因为这种情况不可能。

对于 $j\in [l_i,i-1]$，有 $dp(i,j)=dp(i-1,j)$，因为 $i$ 这里没有决策，只能填 $1$（填 $0$ 的话最后一个 $0$ 就是 $i$ 本身）。

对于 $dp(i,i)$，实际上之前任何一种满足要求的填发都可以，所以：

$$dp(i,i)=\sum\limits_{x=l_{i-1}}^{i-1} dp(i-1,x)$$

我们发现很多的 $dp(i,j)$ 是没有变化或者只是赋值为 $0$ 的，这启发我们把 $dp(i,j)$ 看成一个以 $j$ 为下标的序列 $dp_i$，我们只需要考虑如何从 $dp_{i-1}$ 得到 $dp_i$ 即可。

赋值为 $0$ 的操作根本不用理会：我们只需在进行统计时直接屏蔽 $j<l_i$ 的情况即可。

于是我们只是增加了一个 $dp_{i,i}$ 的值，观察上面那个转移方程，其实是求了一个 $dp_{i-1}$ 的某后缀和。

我们可以拆一下这个后缀和，设 $s_{i,j}$ 表示 $\sum\limits_{k=1}^j dp_{i,k}$，那么实际上：

$$dp_{i,i}=s_{i-1,i-1}-s_{i-1,l_{i-1}-1}$$

而且，$l_i$ 具有单调性，所以我们只需用一个指针维护 $l_i$（根据 $i$ 的变化而变化），然后可以 $O(1)$ 求出 $dp_{i,i}$。

---

再考虑有限制区间与等于 $1$ 的条件。发现此时有些位置必须是 $1$，是不能动的，但这并不影响，我们只需把所有已经限定为 $1$ 的位置扔掉，剩下的位置做上面的过程即可。

---

考虑一下每一位做的复杂度，我们要求做到线性：

1. 统计出哪些位置必须填 $1$：就是若干次区间覆盖，可以用差分数组记录，最后统计差分数组前缀和，可以做到线性。

2. 处理 $l_i$：一开始就将每个询问挂在右端点的一个 vector 中，然后就不用排序，直接扫描一次统计即可，可以做到线性。

3. 处理 $dp_{i,j}$：用一个指针维护当前 $l_i$ 以及当前 $l_i$ 的前缀和，再用一个变量维护当且所有 $dp_{i,j}$ 的和，由于 $l_i$ 的单调性，这个过程是均摊线性的。

所以整个题的复杂度是 $O((n+m)k)$。

核心代码（$x$ 为当前在哪一位，$d$ 为差分数组，$nt$ 就是当前的 $dp$ 数组，$cur$ 是 $l_i$ 指针，$al,res$ 分别是全部和以及 $l_i$ 的前缀和）：

```cpp
int calc (int x) {
	memset(d,0,sizeof(d));
	memset(nt,0,sizeof(nt));
	for (int i=1;i<=n;i++) {
		int tmp=v[i].size();
		for (int j=0;j<tmp;j++) {
			int l=v[i][j].first,p=v[i][j].second;
			if (p&(1<<x)) {d[l]++,d[i+1]--;}
		}
	}
	int tot=0,cur=0,res=0,al=1;
	nt[0]=1;
	for (int i=1;i<=n;i++) {d[i]+=d[i-1];}
	for (int i=1;i<=n;i++) {
		if (!d[i]) {mp[i]=++tot;}
		else {mp[i]=tot;}
		int tmp=v[i].size();
		if (!d[i]) {
			nt[tot]=(al-res+P)%P;
			al=(al+nt[tot])%P;
		}
		for (int j=0;j<tmp;j++) {
			int l=v[i][j].first,p=v[i][j].second;
			if (!(p&(1<<x))) {
				if (d[i]&&d[l]&&mp[i]==mp[l]) {return 0;}
				int vl=(d[l]?mp[l]+1:mp[l]);
				while (cur<vl) {res=(res+nt[cur])%P;cur++;}
			}
		}
	}
	int ans=0;
	for (int i=cur;i<=tot;i++) {ans=(ans+nt[i])%P;}
	return ans;
}
```








---

## 作者：是个汉子 (赞：9)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1327F)	[CF传送门](http://codeforces.com/problemset/problem/1327/F)

感谢同机房大神[ql12345](https://www.luogu.com.cn/user/286239)指导

### Solution

因为位运算每一位之间是互不影响的，所以可以按位考虑然后将每一位的方案数相乘得到最终答案。

对于题目中的限制也可以按位拆成小限制，对于 $(l_i,r_i,x_i)$ ，如果 $x_i$ 这一位上是 $1$  ，那么第 ${l_i}$ 个数到第 ${r_i}$ 数的这一位也全得为 $1$ 。

但是 $x$ 这一位是 $0$ 就不好考虑了，可以考虑DP。

先要预处理出来 $pos$ 和 $a$ 数组，其中 $pos_i$ 为 $i$ 之前最靠近 $i$ 的 $0$ 的位置**至少**要填在 $pos_i$， $a_i$ 为第 $i$ 个数这一位是否强制为 $1$ 。

其中 $pos$ 预处理为：如果 $x_i$ 这一位为 $0$ ， $pos_{r_i+1}=\max(pos_{r_i+1},l_i)$ ，因为在 $(l_i,r_i)$ 这个区间中至少有一个 $0$ ，所以如果要 $r_i+1$ 之前全部满足条件，那么至少要在 $l_i$ 放一个 $0$ 。然后再 $pos_i=\max(pos_i,pos_{i-1})$ 即可。

 $a$ 的预处理这里用的是差分，可以做到在 $O(n+m)$ 的时间预处理出来。（详情看代码^o^）

预处理完了，说DP。

设 $f_{i,j}$ 表示现在到 $i$ 位，其中最后一个 $0$ 填在 $j$ 且满足条件的方案数，有三种情况的转移：

1. 当 $j<pos_i$ 时，因为无法满足 $pos$ 的条件，所以 $f_{i,j}=0$ 
2. 当 $pos_i\leq j<i$ 时，因为第 $i$ 位只能填 $1$ ，不然填 $0$ 那么此时 $j=i$ ，所以 $f_{i,j}=f_{i-1,j}$ 
3. 当 $j=i$ 时，如果 $a_i=1$ ，那么 $f_{i,j}=0$ ，不然 $f_{i,j}=\sum\limits_{x=pos_i}^{i-1}f_{i-1,x}$ ，因为 $pos_i$ 到 $i-1$ 的每一种填法都能满足。

我们发现第一维没有什么影响，可以考虑将数组 $f_{i,j}$ 简化为 $f_j$ ，因为 $pos_i$ 是有单调性的，所以可以维护一个 $sum$ ，及时更新。

时间复杂度： $O(k\cdot(n+m))$ 

### Code

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long

using namespace std;
const int N=5e5+10,mod=998244353;
int n,k,m,l[N],r[N],x[N],f[N];
int pos[N],a[N];//pos表示i之前最后一个0的位置 a是这一位是否强制选1

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

inline void add(int &x,const int y){ x=(x+y>=mod?x+y-mod:x+y);}
inline void sub(int &x,const int y){ x=(x<y?x-y+mod:x-y);}

inline void init(int p){    //p是你按位DP到哪一位了
    for(int i=1;i<=n+1;i++) pos[i]=a[i]=0;
    for(int i=1;i<=m;i++)
        if((x[i]>>p)&1) ++a[l[i]],--a[r[i]+1];
        else pos[r[i]+1]=max(pos[r[i]+1],l[i]);
    for(int i=2;i<=n+1;i++)
        a[i]+=a[i-1],pos[i]=max(pos[i],pos[i-1]);
}

inline void dp(){
    for(int i=0;i<=n+1;i++) f[i]=0;
    f[0]=1;
    int sum=1,l=0;
    for(int i=1;i<=n+1;i++){
        while(l<pos[i]) sub(sum,f[l]),f[l]=0,++l;
        f[i]=a[i]?0:sum,add(sum,f[i]);
    }
}

int main(){
    n=read(),k=read(),m=read();
    for(int i=1;i<=m;i++) l[i]=read(),r[i]=read(),x[i]=read();
    int ans=1;
    for(int p=0;p<k;p++){
        init(p);
        dp();
        ans=1ll*ans*f[n+1]%mod;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：g1ove (赞：5)

发现题解区没有人写容斥。

## CF1327F

按位考虑。猜测时间复杂度为 $O((n+m)k)$。如果按位考虑，每一位都是独立的，最后把所有情况乘起来即可。那么问题转化为下面的情况：

> 有一个长度为 $n$ 的 $01$ 序列。有 $m$ 个限制：
>
> + $1.$ $l\sim r$ 存在 $0$。
> + $2.$ $l\sim r$ 全为 $1$。

上面的存在比较难搞，因为有多个区间存在交集的情况，考虑容斥是最先想到的方法。即对于限制 $1$，若强制某个子集 $l\sim r$ 全取 $1$，那么方案数就是 $2^{n-|[l_1,r_1]\cup[l_2,r_2]...|}$。 

考虑挖掘题目性质：

+ $\text{Observation}$

  对于条件 $1$，若 $[l_1,r_1]\subseteq[l_2,r_2]$，可以去掉 $[l_2,r_2]$。经过处理后，所有的区间不存在包含关系。

我们考虑一个 dp。在不管条件 $2$ 的情况下，我们把区间排序，此时 $l,r$ 都是递增的，这样子我们就可以优化容斥了，我们并不关心选了几个区间，只关心选的区间个数的奇偶性，定义 $f_{i,0/1}$ 表示强制选区间 $i$，此时有奇数/偶数个区间的方案，那么有转移：
$$
f_{i,p}=\sum_{j=1}^{i-1} f_{j,\lnot p}\times 2^{count(r_j+1\sim l_i-1)}
$$

其中 $count(l,r)$ 表示 $(l,r)$ 中不强制取 $1$ 的位置个数。

最后算贡献时处理出这个区间后面有几个可以任意取数的位置个数 $p$，乘上 $2^p$ 即可。

那么使用一些一般的手段对这个 dp 进行优化即可。时间复杂度 $O((n+m)k)$。带个 $\log n$ 会被卡掉。具体双指针即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb emplace_back
#define N 500005
using namespace std;
const int mod=998244353;
int n,k,m;
struct node{
	int l,r,w;
}a[N];
ll f[N][2],res=1;
int d[N],cnt[N];
int R[N],lim,tag[N];
ll s1,s2,r1,r2;
ll pw[N];
ll solve(int bit)
{
	lim=n+1;s1=s2=r1=r2=0;
	memset(R,127/3,sizeof R);
	memset(f,0,sizeof f);
	memset(d,0,sizeof d);
	for(int i=1;i<=m;i++)
		if(a[i].w&(1<<bit)) d[a[i].l]++,d[a[i].r+1]--;
		else R[a[i].l]=min(R[a[i].l],a[i].r);
	for(int i=1;i<=n;i++) d[i]+=d[i-1];
	for(int i=n;i>=1;i--) cnt[i]=cnt[i+1]+(!d[i]);
	for(int i=n;i>=1;i--) if(R[i]<lim) lim=R[i],tag[i]=1; else tag[i]=0;
	ll sum=pw[cnt[1]];
	int l=1;
	s1=1; 
	for(int i=1;i<=n;i++)
	{
		while(l<=i&&(!tag[l]||R[l]<i))
		{
			if(tag[l])
			{
				s1=(s1+f[l][0])%mod;
				s2=(s2+f[l][1])%mod;
				r1=(r1+mod-f[l][0])%mod;
				r2=(r2+mod-f[l][1])%mod;
			}
			++l;
		}
		if(tag[i])
		{
			f[i][0]=(s2+r2)%mod;
			f[i][1]=(s1+r1)%mod;
			r1=(r1+f[i][0])%mod;
			r2=(r2+f[i][1])%mod;
			sum=(sum+(f[i][0]-f[i][1]+mod)*pw[cnt[R[i]+1]])%mod;
		}
		if(!d[i]) s1=s1*2%mod,s2=s2*2%mod;
	}
	return sum;
}
int main()
{
	scanf("%d%d%d",&n,&k,&m);
	pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*2%mod;
	for(int i=1;i<=m;i++) scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].w);
	for(int i=0;i<k;i++) res=res*solve(i)%mod;
	printf("%lld",res);
	return 0;
}
```

---

## 作者：Tony102 (赞：4)

[Link](https://www.luogu.com.cn/problem/CF1327F)

[New Blog阅读效果更佳](https://tony102.com/index.php/archives/109/)

## Sol

首先看到这种位运算的题目，就先看看它给的二进制操作是否独立（一般都会独立），独立的话就可以拆位做了。显然，这道题的操作只有 $\mathrm{AND}$ 操作，可以拆位。

考虑区间 $[l,r]$ 内的数的第 $k$ 位，假如限制给的 $a_i$ 在这一位上要求是 $1$ ，那么这个区间内所有的数这一位上都必须是 $1$，不用考虑贡献。

加入要求是 $0$ ，则这一段至少有一个 $0$。这一部分就是我们要计算的。考虑我们对每一位算出一个 $pos_i$ ，表示第 $i$ 位不放 $0$ 的情况下最早放 $0$ 的位置。设 $f_{i,j}$ 表示前 $i$ 位最后一个 $0$ 放在 $j$ 的位置上的方案数。

若 $j \in [pos_i, i)$ ，那么方案数不变直接从上一位继承过来。$f_{i,j} = f_{i-1,j}$

若 $j = i$ ，则前面 $[pos_{i-1}, i - 1]$ 的 $f$ 都可以贡献到 $f_{i,j}$ 上，即 $f_{i,j} = \sum\limits_{j = pos_{i-1}}^{i-1} f_{i-1,j}$

可以发现 $pos_i$ 单调不降，每次把 $f_{i,j}$ 加进来的时候把前面要出去的 $f$ 刷成 $0$ 即可。

## Code

见 Blog

---

## 作者：zhendelan (赞：2)

[CF1327F AND Segments](https://www.luogu.com.cn/problemnew/show/CF1327F)  

拆位之后就是序列上的[NOI2020命运](https://www.luogu.com.cn/problem/P6773)。    

如果要求$\text{and}$起来之后是$1$，那么连续的都是$1$。可以用差分处理，否则可以用下面的dp。

设$f_{i,j}$为前$i-1$位都满足限制，限制的最左右端点为$j$的方案数。  

取$0$:

$f_{i,n+1}\gets \sum_{k=i}^{n+1} f_{i-1,k}$  

设$ed_j$为左端点恰好在$j$的区间限制的最左 右端点。

取$1$：

$f_{i,ed_i}\gets f_{i-1,j},j\gt ed_i$     

$f_{i,j}\gets f_{i-1,j} ,j\le ed_i$  

可以用线段树维护。  

复杂度$O(kn\log n )$ 
 
不出意外的过不去。    


听说有线性做法：     

观察到其实$ed_i$可以往后取，对答案没有影响。  

就是令$ed_i = \min(ed_i,ed_j),j\gt i$。  

那么现在$ed_i$就是单调不降的了。  

且$ed_i \ge i$。  

而且观察到$f_i$只有在$[1,ed_i] \cup \{n+1\}$间有值。

所以上面这个式子  

$f_{i,ed_i} \gets f_{i-1,j},j\gt ed_i$变成了： $f_{i,ed_i} \gets f_{i-1,n+1}$ 。    

同时单独维护后缀和与$f_{i,n+1}$即可。  

复杂度$O(kn)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define debug(x) cout<<#x<<':'<<x<<endl
const int mod = 998244353;
int n,k,m;
const int N = 5e5+20;
int l[N],r[N],lim[N];
int cf[N],ed[N],f[N];
int main()
{
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&l[i],&r[i],&lim[i]);
	int ans = 1;
	for(int bit=0;bit<k;bit++)
	{
		for(int i=0;i<=n+1;i++)
			cf[i]=f[i]=0,ed[i]=n+1;
		for(int i=1;i<=m;i++)
		{
			if((lim[i]>>bit)&1)
			{
				cf[l[i]]++;
				cf[r[i]+1]--;
			}
			else
				ed[l[i]]=min(ed[l[i]],r[i]);
		}
		for(int i=n-1;i>=1;i--)	ed[i] = min(ed[i],ed[i+1]);
		f[n+1] = 1;int sum = 1; 
		for(int i=1;i<=n;i++)
		{
			sum=(sum-f[i-1])%mod;
			cf[i]+=cf[i-1];
			if(cf[i]==0)
			{
				if(ed[i]!=n+1)
				{
					f[ed[i]] = (f[ed[i]]+f[n+1])%mod;
					f[n+1] = sum;
					sum = (sum+sum)%mod;
				}
				else 
				{
					f[n+1] = (f[n+1]+sum)%mod;
					sum = (sum+sum)%mod;
				}
			}
			else
			{
				if(ed[i]==n+1)continue;
				f[ed[i]] = (f[ed[i]]+f[n+1])%mod;
				f[n+1] = 0;
			}
		}
		ans = 1ll * ans * f[n+1]%mod;
	}
	ans = (ans+mod)%mod;
	cout << ans;
	return 0;
}
/*
*/

```

---

## 作者：傅思维666 (赞：2)


## 题解：

对于这种题目，一般都是从位运算按位独立这里入手。这题也不例外。

既然位运算相互独立，且本题只有与运算，那么很容易得出这样的一个性质：对于某个约束区间$[l,r]$的约束值$x$，对$x$二进制拆分，$x$的某位如果为1，那么这个区间的数的对应位全部为1。反之如果为0，那么这个区间的数的对应位至少有一个为0.

推到此处狂喜，然后觉得可以用排列组合来做，或者是个容斥什么的。但是这是不现实的，因为区间的并实在太难处理了。

但是想到排列组合却能给我们一个启发。那就是计数原理的乘法原理。既然这些位都是互相独立的，那么每位的合法方案的方案数乘到一起就是答案。

每位的合法方案数......既然排列组合容斥啥的都没戏，那就只能考虑DP，毕竟对于计数类问题我们也并没有什么其他的方法。这个不行就试那个。

设$dp[i]$表示处理到前i个数，且第$i$个数的对应位为0的方案数。不需要再开一维来存第几位，每次做的时候清空即可。

那么很显然，如果某个约束条件使得一个区间内的数字的对应位为1，那么这段区间的dp值应该都为0.

这个0可以用多种方法维护，我选择的是差分。

如果某个约束条件使得一个区间内的数字的对应位至少有一个为0，这种情况该怎么办呢？

分类讨论：首先如果某个区间的右端点比当前枚举到的点大，那么这个条件已经被满足，不用考虑。

如果某个区间$[l,r]$的右端点比当前枚举到的点$i$小，那么这个条件要被满足，一定会在这里填一个0，所以就可以转移：
$$
dp[i]=\sum_{j=l}^{i-1}dp[j]
$$
为什么要到$i-1$而不是到$r$呢？因为我们统计的$dp[i]$已经被叫做合法方案，所以在这个区间的都合法，也就都要统计进来。

那么我们敏锐地发现，这样统计会导致很多区间被重复算进去。那么我们为了不重复统计，就采用一个$lmx[i]$数组，表示在$i$左边最大的$l$值。这样的话每次转移只会从最大的开始累加，而前面的已经在前面的转移被累加过了。这样就完成了这道题。

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=5e5+5;
const int mod=998244353;
int n,k,m;
int l[maxn],r[maxn],x[maxn];
int lmx[maxn],dp[maxn],cf[maxn];
int calc(int a)
{
	memset(lmx,0,sizeof(lmx));
	memset(cf,0,sizeof(cf));
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=m;i++)
	{
		if(x[i]>>a&1)
			cf[l[i]]++,cf[r[i]+1]--;
		else
			lmx[r[i]]=max(lmx[r[i]],l[i]);
	}
	for(int i=1;i<=n+1;i++)
	{
		lmx[i]=max(lmx[i],lmx[i-1]);
		cf[i]+=cf[i-1];
	}
	int sum=1,j=0;
	dp[0]=1;
	for(int i=1;i<=n+1;i++)
	{
		if(cf[i])
		{
			dp[i]=0;
			continue;
		}
		while(j<lmx[i-1])
		{
			sum=(sum-dp[j]+mod)%mod;
			j++;
		}
		dp[i]=sum;
		sum=(sum+dp[i])%mod;
	}
	return dp[n+1];
}
int main()
{
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&l[i],&r[i],&x[i]);
	int ans=1;
	for(int i=0;i<k;i++)
		ans=1ll*ans*calc(i)%mod;
	printf("%d\n",ans);
	return 0;
}
```




---

## 作者：Mihari (赞：1)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF1327F)

# 题解

考虑对于一个区间 $[l,r]$，其并值为 $x$ 会有什么限制：

1. 如果 $x$ 的第 $i$ 位为 $1$，则要求 $[l,r]$ 所有数字的第 $i$ 位为 $1$；
2. 如果 $x$ 的第 $i$ 位为 $0$，则要求 $[l,r]$ 的所有数字第 $i$ 位不全为 $1$；

由于所有数字的每个二进制位都是独立的，我们可以考虑先将所有数每个二进制位的选择算出来，最后累乘即可得到答案。

考虑每个二进制位进行 $DP$，令 $f[i]$ 表示前一个 $0$ 填在第 $i$ 个数字上的合法方案。

首先，如果 $\exist t,i\in [l_t,r_t]_1$ （此处区间下标是指要求的类别），那么 $f[i]$ 为 $0$，这个我们可以在初始化时搞定。

其次，考虑如何进行转移，由于我们已经经过初始化，相当于自动满足要求一，只需考虑如何满足要求二，进行分类讨论：

1. 对于 $[l_t,r_t]_2$，如果 $r_t\ge i$，由于 $f[i]$ 的定义，这个要求一定可以被满足（因为我们已经在 $i$ 填了 $0$，满足一个区间不全为 $1$） ；
2. 对于 $[l_t,r_t]_2$，如果 $r_t<i$，那么我们一定要在 $[l_t,r_t]_2$ 中填一个 $0$，那么 $f[i]=\sum_{j=l_t}^{j\le i-1}f[j]$，为什么是到 $i-1$ 而非 $r_t$ 呢？因为 $f[j]$ 已经是所谓的“合法方案”，那么对于 $j\in [r_t+1,i-1]$ 也是一定满足了 $[l_r,r_t]_2$ 这个区间要求的方案数。
3. 由于我们要满足所有的条件二，那么我们就必须在 $2$ 中的所有 $l_t$ 中，找到最大的 $l_t'$，然后求 $\sum_{j=l_t'}^{i-1}f[j]$，发现这是一个连续区间求和，可以考虑维护一个前缀数组。

对于每一位都这样做，然后累乘 $f[n]$ 的值即可。

# 代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int MAXN=5e5;
const int MOD=998244353;

struct require{int l,r;
	inline bool operator <(const require rhs)const{
		if(r==rhs.r)return l<rhs.l;
		return r<rhs.r;
	}
};
vector<require>q[35];
vector<require>make[35];

int n,k,m;

inline bool cmp(const require lhs,const require rhs){
	if(lhs.l==rhs.l)return lhs.r<rhs.r;
	return lhs.l<rhs.l;
}

inline void Init(){
	scanf("%d %d %d",&n,&k,&m);
	for(int i=1,l,r,s;i<=m;++i){
		scanf("%d %d %d",&l,&r,&s);
		for(int i=0;i<k;++i){
			if((s>>i)&1)make[i].push_back(require{l,r});
			else q[i].push_back(require{l,r});
		}
	}
	for(int i=0;i<k;++i)
		sort(q[i].begin(),q[i].end()),
		sort(make[i].begin(),make[i].end(),cmp);
}

int f[MAXN+5];
int pre[MAXN+5];

inline int calc(const int t){
	// memset(f,0,sizeof f);
	for(int i=0;i<=n+1;++i)f[i]=0;
	int pos=0;
	for(int i=0,sz=make[t].size();i<sz;++i){
		pos=max(pos,make[t][i].l);
		for(;pos<=make[t][i].r;++pos)f[pos]=-1;
	}

	f[0]=pre[0]=1;
	int p=0,maxl=0,sz=q[t].size();//指向要求的最后一个
	// printf("Now sz == %d\n",sz);
	for(int i=1;i<=n+1;++i){
		pre[i]=pre[i-1];
		if(f[i]==-1)continue;
		while(p<sz && q[t][p].r<i)maxl=max(maxl,q[t][p++].l);
		if(maxl==0)f[i]=pre[i-1];
		else{
			f[i]=pre[i-1]-pre[maxl-1];
			if(f[i]<0)f[i]+=MOD;
		}
		pre[i]+=f[i];
		if(pre[i]>=MOD)pre[i]-=MOD;
		// printf("f[%d] == %d\n",i,f[i]);
	}return f[n+1];
}

int ans=1;

signed main(){
	Init();
	for(int i=0;i<k;++i){
		// printf("calc(%d) == %d\n",i,calc(i));
		ans=1ll*ans*calc(i)%MOD;
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：NaCN (赞：1)


让你求一个序列$a[l_i]\&a[l_i+1]....a[r_i]=x$的方案数。$0\leq a^i<2^k$

二进制位之间独立,按位讨论。若$(l,r,x),x=1$则里面都是$1$。若$(l,r,x),x=1$，至少出现是$1$。

拿样例$2$的第$1$位解释

$5\ 2\ 3$

$1\ 3\ 2$

$2\ 5\ 0$

$3\ 3\ 3$

分解就是$??1??$,$(1,3)和(2,5)$至少有一个$0$。

设$dp[i][j]$为前第$i$数，最前面的$0$在第$j$位的填法。

若搜到出现边界$r$,
+ $[r,l_x],[r,l_y]$取$min(l_x,l_y)$
+ 若这一位填$0$,$dp[i][i]=\sum dp[i-1][j]$
+ 若这一位填$1$,需要$(l,r)$之间有$0$。$dp[i][j]=\sum_l^{r-1} dp[i-1][j]$
+ 发现了$i-1$这一唯独不需要。


$$
dp_i=\sum dp[j]\\
dp[j] =\sum_l^{r-1} dp[j]
$$

$\sum dp[j]-\sum_0^{l-1}dp[j]=\sum_l^{r-1} dp[j]$

假设$r_x>r_y$,若$l_x<l_y$，则之前的方案已经保证了$[l_x,r_x]$不需要重新计算，所以只需记录下$\sum dp$，每次需要减去的指针一定不会向后移动。

<details>
  <summary>代码</summary>

```c++
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
    using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
const int mod = 998244353;
int l[N], r[N], x[N];
int ans = 1;
int n, s[N], mx[N];
int m, k;
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++)
        scanf("%d%d%d", l + i, r + i, x + i);

    for (int i = 0; i < m; i++)
    {

        for (int j = 1; j <= n; j++)
            s[j] = 0, mx[j] = 0;
        for (int j = 1; j <= k; j++)
        {

            if (x[j] & (1 << i))
                s[l[j]]++, s[r[j] + 1]--;
            else
                mx[r[j]] = max(mx[r[j]], l[j]);
        }
        for (int j = 1; j <= n; j++)
            s[j] += s[j - 1];
        int dp[N];
        dp[0] = 1;
        int t = 0;
        ll dps = 1;

        for (int j = 1; j <= n; j++)
        {
            if (s[j] > 0)
            {
                dp[j] = 0;
            }
            else
            {
                dp[j] = dps;
            }
            while (t < mx[j])
            {
                dps = (dps + mod - dp[t]) % mod;
                t++;
            }
            dps += dp[j];
            dps %= mod;
        }
        //cout << dps << endl;
        ans = 1ll * dps * ans % mod;
    }
    printf("%d\n", ans);
}
```
</details>

---

