# Shuffle Window

## 题目描述

[problemUrl]: https://atcoder.jp/contests/acl1/tasks/acl1_e

$ (1,\ 2,\ ...,\ N) $ の順列 $ p_1,\ p_2,\ \dots,\ p_N $ と整数 $ K $ が与えられます。 maroonくんは $ i\ =\ 1,\ 2,\ \dots,\ N\ -\ K\ +\ 1 $ について、次の操作を順番に行います。

- $ p_i,\ p_{i\ +\ 1},\ \dots,\ p_{i\ +\ K\ -\ 1} $ を一様ランダムにシャッフルする。

すべての操作の後の数列の転倒数の期待値を求め、$ \bmod\ 998244353 $ で出力してください。

より正確には、期待値が有理数、つまりある既約分数 $ \frac{P}{Q} $ で表せること、更に $ R\ \times\ Q\ \equiv\ P\ \pmod{998244353},\ 0\ \leq\ R\ <\ 998244353 $ を満たす整数 $ R $ が一意に定まることがこの問題の制約より証明できます。よって、この $ R $ を出力してください。

また、数列 $ a_1,\ a_2,\ \dots,\ a_N $ の転倒数とは、$ i\ <\ j,\ a_i\ >\ a_j $ を満たす順序対 $ (i,\ j) $ の個数とします。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 200,000 $
- $ 2\ \leq\ K\ \leq\ N $
- $ (p_1,\ p_2,\ \dots,\ p_N) $ は $ (1,\ 2,\ \dots,\ N) $ の並び替え
- 入力される数は全て整数である．

### Sample Explanation 1

$ (1,\ 2,\ 3) $, $ (2,\ 1,\ 3) $, $ (1,\ 3,\ 2) $, $ (2,\ 3,\ 1) $ が、それぞれ $ \frac{1}{4} $ の確率で最終的な数列になります。 これらの転倒数は $ 0,\ 1,\ 1,\ 2 $ なので、期待値は $ 1 $ です。

## 样例 #1

### 输入

```
3 2
1 2 3```

### 输出

```
1```

## 样例 #2

### 输入

```
10 3
1 8 4 9 2 3 7 10 5 6```

### 输出

```
164091855```

# 题解

## 作者：良心WA题人 (赞：5)

## 前言

赛时看这个题感觉做过类似的，所以做了很久，但没玩出来。赛后听讲解仔细思考了一下发现并不是特别难。可能考场降智了吧。

## 题意

给定一个序列 $a$ 和 $k$，按 $i$ 从小到大随机打乱 $i,i+1,i+2\ldots k$。问最后逆序对的期望是多少。

## 思路

不难发现，若两个数出现在了同一个区间内，那么无论随机打乱了多少次，二者的位置关系一定是被最后一次打乱所影响，二者交换的概率为 $\dfrac{1}{2}$。现在考虑二者出现在同一个区间内的概率。不难发现，每次如果一个数没有被放到第一个位置，那么他被放在哪里在下一次操作都是没有关系的。所以，能够继续操作的概率为 $\dfrac{k-1}{k}$。这样一直操作，直到遇到第二个数。那么交换序列内两个数的概率就是：

$$\dfrac{1}{2}\times(\dfrac{k-1}{k})^{\max(r-k,0)-\max(l-k,0)}$$

所以令 $f_{l,r}$ 表示若 $a_l<a_r$ 则为 $1$，反之为 $-1$，则逆序对变化的期望为：

$$\displaystyle\sum_{l=1}^{n}\sum_{r=l+1}^{n}\dfrac{1}{2}\times(\dfrac{k-1}{k})^{\max(r-k,0)-\max(l-k,0)}\times f_{l,r}$$

$$=\displaystyle\sum_{l=1}^{n}\dfrac{1}{2}\times\dfrac{\displaystyle\sum_{r=l+1}^{n}f_{l,r}\times(\dfrac{k-1}{k})^{\max(r-k,0)}}{(\dfrac{k-1}{k})^{\max(l-k,0)}}$$

上面那个式子可以从大到小枚举 $l$，用一个树状数组维护，每次在 $a_i$ 加入 $(\dfrac{k-1}{k})^{\max(l-k,0)}$。每次计算的时候，分 $f_{l,r}$ 为 $1$ 和 $-1$ 用树状数组分别计算和，然后用 $f_{l,r}=1$ 的和减去 $f_{l,r}=-1$ 的和即可。剩下的式子都可以 $O(\log_2 n)$ 算。总的时间复杂度为 $O(n\log_2 n)$，预处理可以达到 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4,P=998244353;
int a[NN];
int qmi(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=1ll*res*a%P;
		a=1ll*a*a%P;
		b>>=1;
	}
	return res;
}
struct bit
{
	int tr[NN];
	int lowbit(int x)
	{
		return x&-x;
	}
	void add(int u,int v)
	{
		while(u<NN)
		{
			tr[u]=(tr[u]+v)%P;
			u+=lowbit(u);
		}
	}
	int ask(int u)
	{
		int res=0;
		while(u)
		{
			res=(res+tr[u])%P;
			u-=lowbit(u);
		}
		return res;
	}
	int sum(int l,int r)
	{
		return (ask(r)-ask(l-1)+P)%P;
	}
}A,B;
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int res=0;
	for(int i=n;i>=1;i--)
	{
		int t=qmi(1ll*(k-1)*qmi(k,P-2)%P,max(0,i-k));
		res=(A.sum(1,a[i])+1ll*qmi(t,P-2)*(B.sum(a[i],n)-B.sum(1,a[i])+P)%P*qmi(2,P-2)+res)%P;
		A.add(a[i],1);
		B.add(a[i],t);
	}
	printf("%d",res);
	return 0;
}
```

---

## 作者：3_14 (赞：1)

## 思路

当 $P_L,P_{L+1},\dots,P_R$ 被洗牌时，反转数会发生怎样的变化？

- 区块 $X$ $\dots$ $P_1,P_2,\dots,P_{L-1}$
- 区块 $Y$ $\dots$ $P_L,P_{L+1},\dots,P_R$
- 区块 $Z$ $\dots$ $P_{R+1},P_{R+2},\dots,P_N$

考虑元素 $P_i$ 和 $P_j$ 的相对位置。 $i < j$ 的相对位置。

- 如果 $P_i$ 属于图块 $X$ ，而 $P_j$ 属于图块 $X$ $\dots$ 洗牌后， $P_i$ 仍然早于 $P_j$ 。
- 如果 $P_i$ 属于图块 $X$ ，而 $P_j$ 属于图块 $Y$ $\dots$ 洗牌后， $P_i$ 仍然早于 $P_j$ 。
- 如果 $P_i$ 属于图块 $X$ ，而 $P_j$ 属于图块 $Z$ $\dots$ 洗牌后， $P_i$ 仍然早于 $P_j$ 。
- 如果 $P_i$ 属于图块 $Y$ ，而 $P_j$ 属于图块 $Y$ $\dots$ 洗牌后， $P_i$ 早于 $P_j$ 的概率为 $1/2$ ，而 $P_j$ 早于 $P_i$ 的概率为 $1/2$ 。
- 如果 $P_i$ 属于图块 $Y$ ， $P_j$ 属于图块 $Z$ $\dots$ 那么洗牌后 $P_i$ 仍然早于 $P_j$ 。
- 如果 $P_i$ 属于图块 $Z$ ，而 $P_j$ 属于图块 $Z$ $\dots$ 洗牌后， $P_i$ 仍然早于 $P_j$ 。

因此，两个元素的相对位置是保留的，除非它们都在 Y 块中，而 Y 块是随机均匀洗牌的。  
通过以上讨论，可以得出预期的反转数是（原 $P$ 的反转数） $-$ （原 $P_L,P_{L+1},\dots,P_R$ $+$ $((_{R-L+1}C_2)/2)$ 的反转数）。

剩下的就是找出所有 $1 \le i \le N-K+1$ 的反转数 $P_i,P_{i+1},\dots,P_{i+K-1}$ 。

计算公式如下

- 首先，求出 $P_1,P_2,\dots,P_K$ 的反转数，用 $I$ 表示。
- 然后，对于 $i=K+1,K+2,\dots,N$ ，重复以下步骤：
    - 从 $I$ 中减去 $P_{i-K+1},P_{i-K+2},\dots,P_{i-1}$ 中小于 $P_{i-K}$ 的元素个数。
    - 然后，在 $I$ 中加上 $P_{i-K+1},P_{i-K+2},\dots,P_{i-1}$ 中大于 $P_{i-K+1},P_{i-K+2},\dots,P_{i-1}$ 的元素个数。
    - 此时， $I$ 就是 $P_{i-K+1},P_{i-K+2},\dots,P_i$ 的反转数。

这可以通过处理分段求和查询（使用类似分段树的数据结构）。

---

## 作者：Komomo (赞：1)

期望容易题！

首先容易想到枚举有贡献的对。

Observation A：对于一对 $(l,r)$，如果他们在同一个长度为 $k$ 的区间内，不管操作几次，我们只关心一次。

> 因为每个操作是独立的，所以其实只要考虑最后一次就好了。

Observation B：对于一对 $(l,r)$，如果他们不在同一个区间，则交换之后他们在同一个区间的概率为 $\left(\dfrac {k-1}k\right)^{pos_r-pos_l}$，其中 $pos_x$ 表示 $x$ 第一次被交换是在第几个区间。

> 这个是易证的。因为我们只希望他们在同一个区间，所以只要不交换到第一个数就好，中间一共要交换 $pos_r-pos_l$ 次。

然后我们就得到了 $\mathcal O(n^2)$ 的算法，然后把式子列出来：

$$\begin{aligned}ans&=\sum\limits_{l=1}^n\sum\limits_{r=l+1}^n\dfrac 1 2\Delta_{l,r}K^{pos_r-pos_l}\\
&=\dfrac 1 2\sum\limits_{l=1}^n\dfrac{\sum\limits_{r=l+1}^n\Delta_{l,r}k^{pos_r}}{K^{pos_l}}\end{aligned}$$

其中 $K=\dfrac {k-1}k$，$\Delta_{l,r}$ 表示如果 $l,r$ 相对位置变化的变化量，为 $1$ 或 $-1$。

发现可以用 BIT 维护，时间复杂度 $\mathcal O(n\log n)$。

---

## 作者：_Arahc_ (赞：0)

> 给定一个排列 $p_{1...n}$ 和一个整数 $K$，进行如下操作 $n-K+1$ 次：
> 
> 第 $i$ 次操作时，随机打乱 $p_{i},p_{i+1},p_{i+2},\cdots,p_{i+K-1}$ 这些数字。
> 
> 求操作完成后序列逆序对数的期望，对 $998244353$ 取模。

_管理审题解的时候能不能顺便把这个题翻译也加上 qwq 辛苦了！_

每次随机打乱一个区间长得很丑，我们发现相邻两个操作的区间是相邻的。考虑转化一下操作的形式：

1. 初始时有一个空序列 $a$ 和一个集合 $S = \{p_i | 1\leq i\leq K\}$。
2. 第 $i$ 次操作时，随机选择 $S$ 中的一个数字加入到 $a$ 序列的末尾，然后把 $p_{i+K}$ 加入到 $S$ 中。
3. 将 $S$ 中剩余的数字随机打乱，依次加入 $a$ 末尾。

于是我们可以求出 $f_i = \max\{0,i-K\}$ 表示 $p_i$ 会在第几次操作中加入到 $S$ 内。下面考虑计算某两个数 $p_i,p_j$ 的相对位置**改变**的概率。不妨设 $i<j$。

当两个数都在 $S$ 内时，概率等价于 $p_j$ 比 $p_i$ 先选的概率，显然为 $\frac{1}{2}$。而这两个数能同时出现在 $S$ 内的概率为 $(\frac{K-1}{K})^{f_{j}-f_{i}}$。因此两数交换的概率为 $\frac{1}{2}(\frac{K-1}{K})^{f_{j}-f_{i}}$。

于是我们先求出原序列有多少逆序对，再求出逆序对的期望变化量即可。前者一个 BIT 就可以了，求后者的关键在于对于满足 $i<j$ 且 $a_{i}>a_{j}$（或反过来）的下标数对 $i,j$，求 $(\frac{K-1}{K})^{f_{j}-f_{i}}$ 的和。也是一个 BIT 就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool Begin;
const int max_n=200005,mod=998244353,iv2=499122177;
inline int read(){
    int x=0;bool w=0;char c=getchar();
    while(c<'0' || c>'9') w|=c=='-',c=getchar();
    while(c>='0' && c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return w?-x:x;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
}
inline int Plus(int &x,int y){return x=(x+y>=mod?x+y-mod:x+y);}
inline int Minu(int &x,int y){return x=(x<y?x-y+mod:x-y);}
inline int MOD(int x){return x>=mod?x-mod:x;}
inline int mi(int a,int p=mod-2){
    int res=1;
    while(p){
        if(p&1) res=res*a%mod;
        a=a*a%mod,p>>=1;
    }
    return res;
}

int n,K,P,a[max_n],ans;

struct BIT{
    int a[max_n];
    inline void add(int i,int x){
        for(;i<=n;i+=i&-i) Plus(a[i],x);
    }
    inline int pre(int i){
        int res=0;
        for(;i;i-=i&-i) Plus(res,a[i]);
        return res;
    }
    inline int ask(int l,int r){
        return MOD(pre(r)-pre(l-1)+mod);
    }
}bit1,bit2;

int mip[max_n],inv[max_n],f[max_n];

bool End;
#define File ""
signed main(){
    // #ifndef ONLINE_JUDGE
    // freopen(File ".in","r",stdin);
    // freopen(File ".out","w",stdout);
    // #endif
    n=read(),K=read(),P=(K-1)*mi(K)%mod;
    mip[0]=inv[0]=1;
    for(int i=1;i<=n;++i)
        mip[i]=mip[i-1]*P%mod;
    inv[n]=mi(mip[n]);
    for(int i=n-1,ip=mi(P);i;--i)
        inv[i]=inv[i+1]*P%mod;
    iota(f+K+1,f+n+1,1);
    for(int i=1;i<=n;++i){
        a[i]=read();
        ans=MOD((ans+mip[f[i]]*bit1.pre(a[i])-mip[f[i]]*bit1.ask(a[i],n)+bit2.ask(a[i],n))%mod+mod);
        bit1.add(a[i],iv2*inv[f[i]]%mod);
        bit2.add(a[i],1);
    }
    write(ans);
    return 0;
}
```



---

