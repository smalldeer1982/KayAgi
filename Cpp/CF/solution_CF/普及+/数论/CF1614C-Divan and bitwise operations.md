# Divan and bitwise operations

## 题目描述

Once Divan analyzed a sequence $ a_1, a_2, \ldots, a_n $ consisting of $ n $ non-negative integers as follows. He considered each non-empty subsequence of the sequence $ a $ , computed the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of its elements and added up all the XORs, obtaining the coziness of the sequence $ a $ .

A sequence $ c $ is a subsequence of a sequence $ d $ if $ c $ can be obtained from $ d $ by deletion of several (possibly, zero or all) elements. For example, $ [1, \, 2, \, 3, \, 4] $ , $ [2, \, 4] $ , and $ [2] $ are subsequences of $ [1, \, 2, \, 3, \, 4] $ , but $ [4, \, 3] $ and $ [0] $ are not.

Divan was very proud of his analysis, but now he lost the sequence $ a $ , and also the coziness value! However, Divan remembers the value of [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) on $ m $ contiguous subsegments of the sequence $ a $ . It turns out that each element of the original sequence is contained in at least one of these $ m $ segments.

Divan asks you to help find the coziness of the sequence $ a $ using the information he remembers. If several coziness values are possible, print any.

As the result can be very large, print the value modulo $ 10^9 + 7 $ .

## 说明/提示

In first example, one of the sequences that fits the constraints is $ [0, 2] $ . Consider all its non-empty subsequences:

- $ [0] $ : the bitwise XOR of this subsequence is $ 0 $ ;
- $ [2] $ : the bitwise XOR of this subsequence is $ 2 $ ;
- $ [0, 2] $ : the bitwise XOR of this subsequence is $ 2 $ .

The sum of all results is $ 4 $ , so it is the answer.

In second example, one of the sequences that fits the constraints is $ [0, \, 5, \, 5] $ .

In third example, one of the sequences that fits the constraints is $ [5, \, 6, \, 7, \, 0, \, 2] $ .

## 样例 #1

### 输入

```
3
2 1
1 2 2
3 2
1 3 5
2 3 5
5 4
1 2 7
3 3 7
4 4 0
4 5 2```

### 输出

```
4
20
112```

# 题解

## 作者：VinstaG173 (赞：22)

这个萌萌题我竟然做了 30min。

显然首先我们每一位能取 $1$ 就取 $1$ 是一定满足条件的。因此就变成了初始全部数是 $2^{30}-1$，每次 `l r x` 代表将 $a_l$ 到 $a_r$ 与 $x$ 取 `and`。容易想到拆位用区间加维护。

然而这是不必要的。下面直接给出结论：答案就是所有 $x$ 的 `or` 和乘以 $2^{n-1}$。

由于题目给的条件一定能成立，那么只要有某个 $x$ 在某一二进制位上为 $1$，那么必然有某个 $a_i$ 在此位上也为 $1$。

由于题目保证每个 $a_i$ 至少被一个限制条件所覆盖，所以只要某一个二进制位所有 $a_i$ 值均为 $0$，那么所有 $x$ 在此位上也均为 $0$。

在上面两个条件下，两个结论的逆命题也均成立。

因此所有 $a_i$ 的 `or` 和等于所有 $x$ 的 `or` 和。

然后，我们设某一位有 $s$ 个 $a_i$ 为 $1$，剩下 $n-s$ 个为 $0$。那么考虑计算这一位对答案的贡献。首先贡献肯定是这一位的值（即 $2^j$）的倍数，下面计算这个倍数的值。显然就是选出奇数个 $1$ 与任意个 $0$ 的方案数，首先 $n-s$ 个 $0$ 有 $2^{n-s}$ 种选择方法，然后 $s$ 个 $1$ 有

$$\sum_{i=0}^{\left\lfloor\frac{s-1}{2}\right\rfloor}\binom{s}{2i+1}=[s>0]2^{s-1}$$

种选择方法。由乘法原理，这个倍数的值为 $[s>0]2^{n-1}$。

因此最终答案就是 $a_i$ 的 `or` 和乘以 $2^{n-1}$，即 $x$ 的 `or` 和乘以 $2^{n-1}$。

Code 懒得放了。

---

## 作者：orz_z (赞：3)

## 题目大意

有一个未知的序列 $a$，现知道 $m$ 个信息，每个星信息为 `l r x` 的形式给出，表示区间 $[l,r]$ 的按位或为 $x$，保证 $a$ 中每一个数都被包含在区间 $[l,r]$ 至少一次。

请输出序列 $a$ 的所有子序列的异或和 $\bmod (10^9+7)$。

共 $T$ 组数据。

对于 $100\%$ 的数据，保证 $1\leq T \leq 10^3,1 \leq n,m \leq 2*10^5,1 \leq l \leq r \leq n,0 \leq x \leq 2^{30}-1$。

## 解题思路

显然，我们可以得到整个序列的按位或就是所有 $x$ 的按位或，设为 $S$。

如果 $S$ 的第 $i$ 位为 $0$，贡献即为 $0$。

否则总有一个 $1$，当中恰有一个对应贡献为 $2^{i}$，总贡献为 $2^{i}\times2^{n-1}$。

那么 $Ans=S \times 2^{n-1}$。

时间复杂度 $\mathcal O(Tn)$。

具体实现见代码。

## CODE

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

inline int read()
{
    int s = 0, w = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            w = -1;
    for (; isdigit(c); c = getchar())
        s = (s << 1) + (s << 3) + (c ^ 48);
    return s * w;
}

const int mod = 1e9 + 7;

inline int qpow(int x, int y)
{
    int res = 1;
    while (y)
    {
        if (y & 1)
            res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

int T, n, m;

signed main()
{
    T = read();
    while (T--)
    {
        n = read(), m = read();
        int ans = 0;
        while (m--)
        {
            read(), read();
            ans = ans | read();
        }
        ans = ans * qpow(2, n - 1) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：zjrdmd (赞：3)

分享一种不太需要动脑子但是比较麻烦的做法。

我们考虑先构造序列，第 $i$ 个位置的数字可以是所有包含 $i$ 的区间限制的与，于是这一部分可以利用线段树来解决。

那么如何计算答案？这是个很经典的套路，观察到每位独立，于是将贡献拆开算，那么若第 $x$ 位共 $y$ 个 $1$，则有 $n-y$ 个 $0$，那么这一位的贡献即为 $2^x\times 2^{(n-1)}$，最后将贡献累加即可。

code：(头文件部分略去）

```cpp
void build(int u,int l,int r){
	if(l==r){tree[u]=a[l];return;}
	int mid=(l+r)>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	tree[u]=tree[u<<1]&tree[u<<1|1]; 
} 

void push_down(int u,int l,int r,int mid){
	tree[u<<1]&=add[u],tree[u<<1|1]&=add[u];
	add[u<<1]&=add[u],add[u<<1|1]&=add[u]; 
}

void Add(int u,int l,int r,int x,int y,int k){//[x,y]是目标区间,[l,r]是现在的区间 
	if(l>y||r<x)return ;
	if(l>=x&&r<=y){add[u]&=k,tree[u]&=k;return;}
	int mid=(l+r)>>1;
	push_down(u,l,r,mid);
	if(x<=mid)Add(u<<1,l,mid,x,y,k);
	if(mid<y)Add(u<<1|1,mid+1,r,x,y,k);
	tree[u]=tree[u<<1]&tree[u<<1|1];
}

int Query(int u,int l,int r,int x,int y){
  if(l>y||r<x)return inf;
	if(l>=x&&r<=y)return tree[u];
	int mid=(l+r)>>1;
	push_down(u,l,r,mid);
	int tmp=0;
	if(x<=mid)tmp=Query(u<<1,l,mid,x,y);
	if(mid<y)tmp=Query(u<<1|1,mid+1,r,x,y); 
	return tmp;
}

void Work(int x){
	int cnt=0;
	while(x)sum[++cnt]+=x%2,x/=2;
}

int kpow(int x,int y){
	if(!y)return 1;
	if(y==1)return x;
	int tmp=kpow(x,y/2);
	if(y&1)return tmp*tmp%mod*x%mod;
	else return tmp*tmp%mod;
}

signed main(void){
	int T=read();
	while(T--){
		n=read(),m=read();
  	for(ri i=1;i<=n*4;i++)add[i]=inf,tree[i]=inf;
  	for(ri i=1;i<=m;i++){
  		int l=read(),r=read(),k=read();
  		Add(1,1,n,l,r,k);
		}
		for(ri i=1;i<=n;i++)b[i]=Query(1,1,n,i,i);
//		printf("\n");
		std::memset(sum,0,sizeof(sum));
		for(ri i=1;i<=n;i++)Work(b[i]);
		int ans=0;
		for(ri i=1;i<=30;i++){
			if(sum[i]==0)continue;
			ans+=kpow(2,sum[i]-1)*kpow(2,n-sum[i])%mod*(1ll<<(i-1))%mod,ans%=mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：_Diu_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1614C)

题目大意:

有一个 $n$ 个数的序列 $a_1,a_2,\dots,a_n$，$m$ 个限制，$l,r,x$ 表示 $a_l\ or\ a_{l+1}\ or\ \dots\ or\ a_r=x$，求一种合法序列每个子集的异或和的和，保证至少存在一种合法序列，保证序列中每个数至少被一个限制覆盖，若有多个合法序列，则输出任意一种的答案即可，有多组数据。

---

这一题显然可以分成两个部分，一部分是构造出一个合法的序列，另一个部分是根据构造出的数列统计答案。

## 构造数列

我们可以这样思考，对于一个数，有 $k$ 个限制条件，分别为 $x_1,x_2,x_3,\dots,x_k$，那么这个数最大是 $x_1\&x_2\&x_3\&\dots\&x_k$，或者是这个数的子集。

那么，我们就可以对于每一次的操作 $l,r,x$，把 $a_l,a_{l+1},\dots,a_r$ 全部 $\&x$，这样最后统计出来的就是其中一组合法序列。

因为题目保证有解，所以不需要判无解。

上述过程可以随便来个数据结构维护一下。

本人使用线段树来维护的，但由于操作是静态的，也就是说我们不需要实时知道答案，用优先队列之类的也是可以维护的。

```cpp
void build(int o,int l,int r){
	tr[o]=(1ll<<30)-1;
	if(l==r)return;
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void push_down(int o){
	tr[ls]&=tr[o],tr[rs]&=tr[o];
}
void update(int o,int l,int r,int x,int y,int v){
	if(x<=l&&r<=y)return (void)(tr[o]&=v);
	push_down(o);
	int mid=l+r>>1;
	if(x<=mid)update(ls,l,mid,x,y,v);
	if(y>mid)update(rs,mid+1,r,x,y,v);
}
void down(int o,int l,int r){
	if(l==r)return (void)(x[l]=tr[o]);
	int mid=l+r>>1;
	push_down(o);
	down(ls,l,mid);
	down(rs,mid+1,r);
}

for(int l,r,x,i=1;i<=m;i++){
	scanf("%lld%lld%lld",&l,&r,&x);
	update(1,1,n,l,r,x);
}
```

## 统计答案

构造完成后，接下来的问题就变成了：

给出一个序列，求这个序列每个子集的异或和之和。

### 简单的递推

一个很显然的结论，我们可以把答案拆成每一个二进制位来统计。

设 $sum_{i,j,0/1}$ 表示前 $i$ 个数所构成的子集中，第 $j$ 位是 $0$ 或 $1$ 的数量。

那么对 $sum_{i+1,j,0/1}$，首先不包括这一个数的情况，也就是只考虑前 $i$ 个数的情况还是可以用，不考虑前 $i$ 个，只靠率第 $i+1$ 个数也可以单独计算。

那么考虑在前面一个集合的基础上再加上一个数。

如果这个数当前位是 $1$，原集合当前位是 $k$，那么新集合当前位就是 $k\ xor\ 1$；

如果这个数当前位是 $0$，原集合当前位是 $k$，那么新集合当前位就是 $k$。

每次暴力转移即可，最后统计每一位对答案的贡献即可，时间复杂度 $O(30n)$，再加上前面线段树，总时间复杂度在 $O(n\log n)$ 以内。

```cpp
void push(int x){
	for(int i=29;i>=0;i--){
		if(x>>i&1)sum[i][0]=sum[i][1]=sum[i][0]+sum[i][1];
		else sum[i][0]*=2,sum[i][1]*=2;
		sum[i][x>>i&1]++;
		sum[i][0]%=p,sum[i][1]%=p;
	}
}
	for(int i=1;i<=n;i++)push(x[i]);
	for(int i=0;i<30;i++)ans=(ans+sum[i][1]*_2[i]%p)%p;//只有1对答案有贡献
```
## code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls (o<<1)
#define rs (o<<1|1)
using namespace std;
const int N=2e5+10,p=1e9+7;
int t,n,m,ans,x[N],tr[N<<2],sum[50][2],_2[50];
void build(int o,int l,int r){
	tr[o]=(1ll<<30)-1;
	if(l==r)return;
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void push_down(int o){
	tr[ls]&=tr[o],tr[rs]&=tr[o];
}
void update(int o,int l,int r,int x,int y,int v){
	if(x<=l&&r<=y)return (void)(tr[o]&=v);
	push_down(o);
	int mid=l+r>>1;
	if(x<=mid)update(ls,l,mid,x,y,v);
	if(y>mid)update(rs,mid+1,r,x,y,v);
}
void down(int o,int l,int r){
	if(l==r)return (void)(x[l]=tr[o]);
	int mid=l+r>>1;
	push_down(o);
	down(ls,l,mid);
	down(rs,mid+1,r);
}
void push(int x){
	for(int i=29;i>=0;i--){
		if(x>>i&1)sum[i][0]=sum[i][1]=sum[i][0]+sum[i][1];
		else sum[i][0]*=2,sum[i][1]*=2;
		sum[i][x>>i&1]++;
		sum[i][0]%=p,sum[i][1]%=p;
	}
}
signed main(){
	scanf("%lld",&t);
	_2[0]=1;
	for(int i=1;i<30;i++)_2[i]=_2[i-1]*2ll%p;
	for(;t--;){
		scanf("%lld%lld",&n,&m),ans=0;
		build(1,1,n);
		for(int l,r,x,i=1;i<=m;i++){
			scanf("%lld%lld%lld",&l,&r,&x);
			update(1,1,n,l,r,x);
		}
		down(1,1,n);
		memset(sum,0,sizeof(sum));
		for(int i=1;i<=n;i++)push(x[i]);
		for(int i=0;i<30;i++)ans=(ans+sum[i][1]*_2[i]%p)%p;
		printf("%lld\n",ans);
	}
}
```

---

## 作者：Shxt_Plus (赞：1)

## ~~诈骗题~~
看到这题第一眼以为是构造序列，但是想到构造方法后，发现仍需要 $2^n$ 的时间复杂度来计算答案，所以考虑拆位计算。

对于第 $i$ 位，假设有 $x$ 个数此位为 $1$，如果想要让这一位为 $1$，那就要选奇数个此位为 $1$ 的数，而此位为 $0$ 的数可选可不选，对答案没有影响，所以方案数为 $2^{n-x}\times\sum_{i=1}^{\lceil \frac{x}{2} \rceil}C_x^{2i-1}$，众所周知 $\sum_{i=1}^{\lceil \frac{n}{2} \rceil}C_n^{2i-1}=2^{n-1}$，所以方案数就是 $2^{n-x}\times2^{x-1}=2^{n-1}$ ，那它对答案的贡献是 $2^i\times2^{n-1}$。

这时我们会发现答案与这个序列到底是什么完全没有关系，我们只在乎每一位有没有 $1$，那题目给了区间或和，全部或起来我们就能得到那些位一定有 $1$，然后算一下贡献就做完了。

~~模拟赛上因没输出换行喜提 $0$ 分的好成绩~~

## Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int t,n,m;
int po(int x,int n)
{
	int tmp=1;
	while(n)
	{
		if(n&1)tmp=tmp*x%mod;
		x=x*x%mod;
		n>>=1;
	}
	return tmp;
}
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&m);
		int p=0,ans=0;
		for(int i=1;i<=m;i++)
		{
			int s,t,v;
			scanf("%lld%lld%lld",&s,&t,&v);
			p|=v;
		}
		for(int i=0;i<=60;i++)
		{
			if(p&(1ll<<i))
			{
				ans+=(1ll<<i)%mod;
				ans%=mod;
			}
		}
		printf("%lld\n",ans*po(2,n-1)%mod);
	}
	return 0;
}
```

---

